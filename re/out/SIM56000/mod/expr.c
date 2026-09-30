/* ==== eval_int_addr @ 00459250 ==== */

void __cdecl eval_int_addr(ulong mode)

{
  void *node;
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  expr_mode = mode;
  if ((mode & 0x400) == 0) {
    if ((mode & 0x200) == 0) {
      uVar2 = -(uint)((mode & 8) != 0) & 0xffff0000;
    }
    else {
      uVar2 = 0xff000000;
    }
  }
  else {
    uVar2 = 0xfff80000;
  }
  if (*optr == '<') {
    optr = optr + 1;
    uVar3 = 0x20;
    if (*optr != '<') goto LAB_004592b9;
    uVar3 = 0x40;
  }
  else {
    if (*optr != '>') goto LAB_004592b9;
    uVar3 = 0x10;
  }
  optr = optr + 1;
LAB_004592b9:
  eval_expr(mode);
  if (node != (void *)0x0) {
    if ((*(uint *)((int)node + 0x1c) & 0x200) != 0) {
      node_free(node);
      expr_error(s_Expression_result_must_be_intege_004d29b0);
      return;
    }
    uVar1 = node_word(node);
    if (((uVar2 & uVar1) != 0) && ((uVar2 & uVar1) != uVar2)) {
      node_free(node);
      expr_error(s_Expression_result_too_large_004d2994);
      return;
    }
    *(uint *)((int)node + 0x1c) = *(uint *)((int)node + 0x1c) | uVar3;
  }
  return;
}


/* ==== node_word @ 00459330 ==== */

ulong __cdecl node_word(void *node)

{
  uint uVar1;
  
  uVar1 = *(uint *)((int)node + 8);
  if ((expr_mode & 0x14000000) != 0) {
    uVar1 = uVar1 | *(int *)((int)node + 0xc) << ((~(byte)(expr_mode >> 0x18) & 0x10 | 0x20) >> 1);
  }
  return uVar1;
}


/* ==== eval_int_masked @ 00459360 ==== */

void __cdecl eval_int_masked(ulong mode,ulong mask)

{
  void *node;
  ulong uVar1;
  uint uVar2;
  
  expr_mode = mode;
  eval_expr(mode);
  if (node != (void *)0x0) {
    if ((*(uint *)((int)node + 0x1c) & 0x200) != 0) {
      node_free(node);
      expr_error(s_Expression_result_must_be_intege_004d29b0);
      return;
    }
    uVar1 = node_word(node);
    uVar2 = uVar1 & ~mask;
    if ((uVar2 != 0) && (uVar2 != ~mask)) {
      node_free(node);
      expr_error(s_Expression_result_too_large_004d2994);
      return;
    }
  }
  return;
}


/* ==== eval_data_word @ 004593e0 ==== */

void __cdecl eval_data_word(ulong mode)

{
  void *node;
  ulong uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  expr_mode = mode;
  if ((mode & 0x10000000) == 0) {
    uVar3 = -(uint)((mode & 0x4000000) != 0) & 0xff000000;
  }
  else {
    uVar3 = 0xffff0000;
  }
  if (*optr == '<') {
    uVar2 = 0x20;
  }
  else {
    if (*optr != '>') goto LAB_00459432;
    uVar2 = 0x10;
  }
  optr = optr + 1;
LAB_00459432:
  eval_expr(mode);
  if (node != (void *)0x0) {
    if ((*(uint *)((int)node + 0x1c) & 0x100) != 0) {
      uVar1 = node_word(node);
      if (((uVar1 & uVar3) != 0) && ((uVar1 & uVar3) != uVar3)) {
        node_free(node);
        expr_error(s_Expression_result_too_large_004d2994);
        return;
      }
    }
    *(uint *)((int)node + 0x1c) = *(uint *)((int)node + 0x1c) | uVar2;
  }
  return;
}


/* ==== eval_expr @ 00459480 ==== */

void __cdecl eval_expr(ulong mode)

{
  char cVar1;
  void *node;
  
  expr_mode = mode;
  if (optr == (char *)0x0) {
    expr_error(s_sv_optr_pointing_to_NULL_address_004d2a0c);
    return;
  }
  for (; (*optr == ' ' || (*optr == '\t')); optr = optr + 1) {
  }
  if (*optr == '\0') {
    expr_error(s_Missing_expression_004d29f8);
    return;
  }
  parse_expr();
  cVar1 = *optr;
  if ((((cVar1 != '\0') && (cVar1 != ',')) && (cVar1 != ')')) && (cVar1 != ';')) {
    expr_error(s_Extra_characters_beyond_expressi_004d29d4);
    node_free(node);
    return;
  }
  return;
}


/* ==== parse_expr @ 00459510 ==== */

void parse_expr(void)

{
  void *lhs;
  
  parse_primary();
  if (lhs == (void *)0x0) {
    return;
  }
  parse_binop_rhs(lhs,0xb);
  return;
}


/* ==== parse_binop_rhs @ 00459530 ==== */

void __cdecl parse_binop_rhs(void *lhs,int minprec)

{
  int op;
  int minprec_00;
  void *lhs_00;
  int iVar1;
  void *extraout_EAX;
  void *b;
  int iVar2;
  
  iVar2 = 0;
  op = peek_binop();
  if (op != 0) {
    while (minprec_00 = binop_prec(op), minprec_00 < minprec) {
      if ((((op == 10) || (op == 9)) || (op == 0xd)) ||
         (((op == 0xe || (op == 0xf)) || ((op == 0x10 || ((op == 0x11 || (op == 0x12)))))))) {
        optr = optr + 2;
      }
      else {
        optr = optr + 1;
      }
      parse_primary();
      if ((lhs_00 == (void *)0x0) ||
         (((iVar1 = peek_binop(), b = lhs_00, iVar1 != 0 &&
           (iVar1 = binop_prec(iVar1), iVar1 < minprec_00)) &&
          (parse_binop_rhs(lhs_00,minprec_00), b = extraout_EAX, extraout_EAX == (void *)0x0)))) {
LAB_00459753:
        node_free(lhs);
        return;
      }
      if (((byte)expr_mode & 0x80) == 0) {
        switch(op + -1) {
        case 0:
          iVar2 = op_add(lhs,b);
          break;
        case 1:
          iVar2 = op_sub(lhs,b);
          break;
        case 2:
          iVar2 = op_mul(lhs,b);
          break;
        case 3:
          iVar2 = op_div(lhs,b);
          break;
        case 4:
          iVar2 = op_or(lhs,b);
          break;
        case 5:
          iVar2 = op_and(lhs,b);
          break;
        case 6:
          iVar2 = op_mod(lhs,b);
          break;
        case 7:
          iVar2 = op_xor(lhs,b);
          break;
        case 8:
          iVar2 = op_shl(lhs,b);
          break;
        case 9:
          iVar2 = op_shr(lhs,b);
          break;
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x12:
          iVar2 = op_compare(lhs,b,op);
          break;
        case 0x10:
          iVar2 = op_land(lhs,b);
          break;
        case 0x11:
          iVar2 = op_lor(lhs,b);
        }
      }
      else {
        switch(op + -1) {
        case 0:
          iVar2 = op_add32(lhs,b);
          break;
        case 1:
          iVar2 = op_sub32(lhs,b);
          break;
        case 2:
          iVar2 = op_mul32(lhs,b);
          break;
        case 3:
          iVar2 = op_div32(lhs,b);
          break;
        case 4:
          iVar2 = op_or32(lhs,b);
          break;
        case 5:
          iVar2 = op_and32(lhs,b);
          break;
        case 6:
          iVar2 = op_mod32(lhs,b);
          break;
        case 7:
          iVar2 = op_xor32(lhs,b);
          break;
        case 8:
          iVar2 = op_shl32(lhs,b);
          break;
        case 9:
          iVar2 = op_shr32(lhs,b);
          break;
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x12:
          iVar2 = op_compare32(lhs,b,op);
          break;
        case 0x10:
          iVar2 = op_land32(lhs,b);
          break;
        case 0x11:
          iVar2 = op_lor32(lhs,b);
        }
      }
      if (iVar2 == 0) {
        node_free(b);
        goto LAB_00459753;
      }
      node_free(b);
      op = peek_binop();
      if (op == 0) {
        return;
      }
    }
  }
  return;
}


/* ==== peek_binop @ 00459810 ==== */

int peek_binop(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  for (; (*optr == ' ' || (*optr == '\t')); optr = optr + 1) {
  }
  if (*optr == '\0') {
    cVar1 = ' ';
  }
  else {
    cVar1 = optr[1];
  }
  switch(*optr) {
  case '!':
    if (cVar1 == '=') {
      return 0x10;
    }
    break;
  case '%':
    return 7;
  case '&':
    iVar2 = (-(uint)(cVar1 != '&') & 0xfffffff5) + 0x11;
    break;
  case '*':
    return 3;
  case '+':
    if (cVar1 != '+') {
      return 1;
    }
    break;
  case '-':
    return 2;
  case '/':
    return 4;
  case '<':
    if (cVar1 == '<') {
      return 9;
    }
    return (-(uint)(cVar1 != '=') & 0xfffffffd) + 0xe;
  case '=':
    return (-(uint)(cVar1 != '=') & 6) + 0xd;
  case '>':
    if (cVar1 == '>') {
      return 10;
    }
    return (-(uint)(cVar1 != '=') & 0xfffffffd) + 0xf;
  case '^':
    return 8;
  case '|':
    return (-(uint)(cVar1 != '|') & 0xfffffff3) + 0x12;
  }
  return iVar2;
}


/* ==== binop_prec @ 004599c0 ==== */

int __cdecl binop_prec(int op)

{
  if (((op == 3) || (op == 4)) || (op == 7)) {
    return 1;
  }
  if ((op == 1) || (op == 2)) {
    return 2;
  }
  if ((op == 9) || (op == 10)) {
    return 3;
  }
  if ((((op == 0xb) || (op == 0xc)) || (op == 0xe)) || (op == 0xf)) {
    return 4;
  }
  if (((op != 0xd) && (op != 0x13)) && (op != 0x10)) {
    if (op == 6) {
      return 6;
    }
    if (op == 8) {
      return 7;
    }
    if (op == 5) {
      return 8;
    }
    if (op == 0x11) {
      return 9;
    }
    return (op != 0x12) - 1 & 10;
  }
  return 5;
}


/* ==== parse_primary @ 00459a70 ==== */

void parse_primary(void)

{
  char cVar1;
  uint addr;
  code *pcVar2;
  bool bVar3;
  void *node;
  void *node_00;
  int iVar4;
  void *node_01;
  void *node_02;
  int iVar5;
  double *value;
  uint uVar6;
  long lVar7;
  void *node_03;
  int iVar8;
  double *node_04;
  byte bVar9;
  undefined *extraout_ECX;
  undefined *extraout_ECX_00;
  undefined *extraout_ECX_01;
  undefined *extraout_ECX_02;
  undefined *extraout_ECX_03;
  undefined *puVar10;
  uint uVar11;
  char cVar12;
  undefined2 uVar13;
  undefined4 *puVar14;
  uint uVar15;
  undefined2 uVar16;
  char *pcVar17;
  char *pcVar18;
  char *pcVar19;
  double dVar20;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  char *local_c;
  int local_8;
  uint local_4;
  
  for (; (*optr == ' ' || (*optr == '\t')); optr = optr + 1) {
  }
  cVar1 = *optr;
  if (cVar1 == '+') {
    optr = optr + 1;
    parse_primary();
    return;
  }
  if (cVar1 == '-') {
    optr = optr + 1;
    parse_primary();
    if (node == (void *)0x0) {
      return;
    }
    if ((expr_mode & 0x80) != 0) {
      node_neg32(node);
      return;
    }
    node_neg(node);
    return;
  }
  if (cVar1 == '~') {
    optr = optr + 1;
    parse_primary();
    if (node_00 == (void *)0x0) {
      return;
    }
    if ((expr_mode & 0x80) == 0) {
      iVar4 = node_not(node_00);
      if (iVar4 != 0) {
        return;
      }
      node_free(node_00);
      return;
    }
    node_not32(node_00);
    return;
  }
  if (cVar1 == '!') {
    optr = optr + 1;
    parse_primary();
    if (node_01 == (void *)0x0) {
      return;
    }
    if ((expr_mode & 0x80) != 0) {
      node_lnot32(node_01);
      return;
    }
    node_lnot(node_01);
    return;
  }
  if (cVar1 == '(') {
    optr = optr + 1;
    parse_expr();
    if (node_02 == (void *)0x0) {
      return;
    }
    if (*optr != ')') {
      node_free(node_02);
      expr_error(s_Missing_____in_expression_004d2ae0);
      return;
    }
    optr = optr + 1;
    return;
  }
  if ((expr_mode & 0x10000000) == 0) {
    if ((expr_mode & 0x4000000) == 0) {
      local_14 = 0x80000000;
      local_1c = 0xffffffff;
      local_20 = 0x20;
    }
    else {
      local_14 = 0x800000;
      local_1c = 0xffffff;
      local_20 = 0x18;
    }
    local_18 = 0xff;
  }
  else {
    local_14 = 0x8000;
    local_1c = 0xffff;
    local_20 = 0x10;
    local_18 = (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff10) + 0xff;
  }
  pcVar17 = optr + 1;
  if (optr[1] == ':') {
LAB_00459c9f:
    iVar4 = 0;
    puVar14 = *(undefined4 **)(cur_dtype + 0x20);
    *pcVar17 = '\0';
    if (0 < *(int *)(cur_dtype + 0x1c)) {
      do {
        iVar5 = stricmp_ci2(optr,(char *)*puVar14);
        if (iVar5 == 0) {
          iVar8 = iVar4 * 0x2c;
          iVar5 = *(int *)(cur_dtype + 0x20) + iVar8;
          local_c = (char *)(*(uint *)(iVar5 + 0x24) & 0xff400003);
          local_20 = *(uint *)(iVar5 + 0x20);
          if ((expr_mode & 0x800) != 0) {
            local_20 = local_20 & 0xffff;
          }
          *pcVar17 = ':';
          optr = pcVar17 + 1;
          parse_primary();
          if (node_04 != (double *)0x0) {
            uVar6 = *(uint *)(node_04 + 1);
            *(short *)((int)node_04 + 0x24) = (short)iVar4;
            if ((expr_mode & 0x10000000) == 0) {
              if ((expr_mode & 0x4000000) != 0) {
                uVar6 = uVar6 | *(int *)((int)node_04 + 0xc) << 0x18;
              }
            }
            else {
              uVar6 = uVar6 | *(int *)((int)node_04 + 0xc) << 0x10;
            }
            uVar6 = uVar6 & local_20;
            pcVar2 = (code *)(*(undefined4 **)(cur_dtype + 0x28))[0xb];
            if (pcVar2 == (code *)0x0) {
              (*(code *)**(undefined4 **)(cur_dtype + 0x28))
                        (*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + iVar8),uVar6,node_04 + 1);
            }
            else {
              (*pcVar2)(*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + iVar8),uVar6,node_04 + 1);
            }
            *(uint *)((int)node_04 + 0x14) = uVar6;
            *(uint *)((int)node_04 + 0x1c) = (uint)local_c | 0x4100;
            *(undefined4 *)(node_04 + 3) = *(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + iVar8);
            iVar4 = mem_addr_check(iVar4,uVar6);
            if (iVar4 != 2) {
              return;
            }
            if (((*(byte *)((int)node_04 + 0x1c) & 2) != 0) && ((expr_mode & 0x1000) != 0)) {
              *(uint *)(node_04 + 1) =
                   *(uint *)(node_04 + 1) & 0xffff | *(uint *)((int)node_04 + 0xc) << 0x10;
              *(uint *)((int)node_04 + 0xc) = *(uint *)((int)node_04 + 0xc) >> 8;
            }
            dVar20 = node_get_double(expr_mode,node_04);
            *node_04 = dVar20;
            *(uint *)((int)node_04 + 0x1c) = (uint)local_c | 0x4200;
            return;
          }
          return;
        }
        iVar4 = iVar4 + 1;
        puVar14 = puVar14 + 0xb;
      } while (iVar4 < *(int *)(cur_dtype + 0x1c));
    }
    *pcVar17 = ':';
  }
  else if (optr[1] != '\0') {
    pcVar17 = optr + 2;
    if (optr[2] == ':') goto LAB_00459c9f;
    if (optr[2] != '\0') {
      pcVar17 = optr + 3;
      if ((optr[3] == ':') || ((optr[3] != '\0' && (pcVar17 = optr + 4, optr[4] == ':'))))
      goto LAB_00459c9f;
    }
  }
  dsp_alloc(0x28,1);
  if (value == (double *)0x0) {
    return;
  }
  *(undefined4 *)((int)value + 0x1c) = 0x101;
  pcVar17 = optr;
  if ((expr_mode & 0x10000) == 0) {
    if ((((*optr == 'r') || (*optr == 'R')) && ((optr[1] == 'e' || (optr[1] == 'E')))) &&
       (((optr[2] == 'g' || (optr[2] == 'G')) && (optr[3] == ':')))) {
      optr = optr + 4;
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (__mb_cur_max < 2) {
      uVar6 = *(ushort *)(_pctype + *optr * 2) & 0x103;
    }
    else {
      uVar6 = _isctype((int)*optr,0x103);
    }
    pcVar17 = optr;
    if ((uVar6 != 0) || (*optr == '_')) {
      pcVar18 = (char *)0x0;
      local_c = (char *)0x0;
      do {
        cVar12 = pcVar18[(int)pcVar17];
        if ((cVar12 != '_') && (cVar12 != '.')) {
          if (__mb_cur_max < 2) {
            uVar6 = *(ushort *)(_pctype + cVar12 * 2) & 0x107;
          }
          else {
            uVar6 = _isctype((int)cVar12,0x107);
            pcVar17 = optr;
          }
          if (uVar6 == 0) goto LAB_00459de2;
        }
        pcVar18 = pcVar18 + 1;
      } while( true );
    }
    goto LAB_00459ef3;
  }
LAB_00459f17:
  pcVar18 = pcVar17;
  if ((*pcVar17 == '@') && (pcVar18 = pcVar17 + 1, pcVar17 != (char *)0x0)) {
LAB_00459f7e:
    iVar4 = 0;
    do {
      cVar12 = pcVar18[iVar4];
      if (cVar12 != '_') {
        if (__mb_cur_max < 2) {
          uVar6 = *(ushort *)(_pctype + cVar12 * 2) & 0x107;
          puVar10 = _pctype;
        }
        else {
          uVar6 = _isctype((int)cVar12,0x107);
          puVar10 = extraout_ECX_00;
          pcVar17 = optr;
        }
        if ((uVar6 == 0) && ((cVar12 != '.' || (pcVar18[iVar4 + 1] == '.')))) goto LAB_00459fcf;
      }
      iVar4 = iVar4 + 1;
    } while( true );
  }
  puVar10 = cur_sim;
  if (*(int *)(cur_sim + 0x3fd8) != 0) {
    if (__mb_cur_max < 2) {
      uVar6 = *(ushort *)(_pctype + *pcVar18 * 2) & 0x103;
      puVar10 = _pctype;
    }
    else {
      uVar6 = _isctype((int)*pcVar18,0x103);
      puVar10 = extraout_ECX;
      pcVar17 = optr;
    }
    if ((uVar6 != 0) || (*pcVar18 == '_')) goto LAB_00459f7e;
  }
LAB_0045a1e1:
  cVar12 = *pcVar17;
  uVar6 = 0;
  if (cVar12 == '*') {
    optr = pcVar17 + 1;
    *(undefined4 *)(value + 1) = *(undefined4 *)(cur_sim + 0xc);
    return;
  }
  local_4 = *(uint *)(cur_sim + 0x30);
  pcVar18 = pcVar17;
  if ((cVar1 == '%') || (local_4 == 0)) {
    if (cVar1 == '%') {
      pcVar18 = pcVar17 + 1;
      optr = pcVar18;
    }
    cVar12 = *pcVar18;
    local_c = pcVar17;
    if ((cVar12 != '0') && (cVar12 != '1')) goto LAB_0045a243;
    while ((*pcVar18 == '0' || (*pcVar18 == '1'))) {
      iVar4 = *(int *)(value + 2);
      uVar6 = uVar6 + 1;
      *(int *)(value + 2) = iVar4 << 1;
      if ((*(uint *)((int)value + 0xc) & local_14) != 0) {
        *(uint *)(value + 2) = iVar4 << 1 | 1;
      }
      uVar15 = *(uint *)((int)value + 0xc) * 2;
      *(uint *)((int)value + 0xc) = uVar15;
      if ((*(uint *)(value + 1) & local_14) != 0) {
        *(uint *)((int)value + 0xc) = uVar15 | 1;
      }
      *(uint *)(value + 1) = *optr + -0x30 + *(uint *)(value + 1) * 2;
      pcVar18 = optr + 1;
      optr = pcVar18;
    }
    if ((*pcVar18 == '.') && (cVar1 != '%')) goto LAB_0045a5e3;
    if (uVar6 == 0) {
      node_free(value);
      expr_error(s_Binary_constant_expected_004d2a30);
      return;
    }
    if (uVar6 <= local_20) {
      return;
    }
    if (local_20 < uVar6 - local_20) {
      *(uint *)((int)value + 0x1c) = *(uint *)((int)value + 0x1c) & 0xfffffffc | 4;
      goto LAB_0045a647;
    }
LAB_0045a63b:
    *(uint *)((int)value + 0x1c) = *(uint *)((int)value + 0x1c) & 0xfffffffa | 2;
LAB_0045a647:
    *(uint *)(value + 1) = *(uint *)(value + 1) & local_1c;
    *(uint *)((int)value + 0xc) = *(uint *)((int)value + 0xc) & local_1c;
    return;
  }
LAB_0045a243:
  if (cVar1 == '$') {
LAB_0045a256:
    pcVar18 = pcVar18 + 1;
    optr = pcVar18;
LAB_0045a25d:
    bVar9 = (char)local_20 - 4;
    local_c = pcVar18;
    iVar4 = str_index1(CONCAT31((int3)((uint)puVar10 >> 8),*pcVar18),
                       s_0123456789abcdefABCDEF_004d2a84);
    pcVar18 = optr;
    while (optr = pcVar18, iVar4 != 0) {
      if (0x10 < iVar4) {
        iVar4 = iVar4 + -6;
      }
      uVar6 = uVar6 + 4;
      uVar15 = *(uint *)((int)value + 0xc) << 4;
      *(uint *)(value + 2) =
           *(uint *)((int)value + 0xc) >> (bVar9 & 0x1f) & 0xf | *(int *)(value + 2) << 4;
      *(uint *)((int)value + 0xc) = *(uint *)(value + 1) >> (bVar9 & 0x1f) & 0xf | uVar15;
      *(uint *)(value + 1) = iVar4 - 1U | *(uint *)(value + 1) << 4;
      optr = optr + 1;
      iVar4 = str_index1(CONCAT31((int3)(uVar15 >> 8),*optr),s_0123456789abcdefABCDEF_004d2a84);
      pcVar18 = optr;
    }
    cVar12 = *pcVar18;
    if ((cVar12 == '.') && (pcVar17 = local_c, cVar1 != '$')) goto LAB_0045a5e3;
    if (uVar6 != 0) {
      if (uVar6 <= local_20) {
        return;
      }
      if (local_20 < uVar6 - local_20) {
        *(uint *)((int)value + 0x1c) = *(uint *)((int)value + 0x1c) & 0xfffffffc | 4;
        goto LAB_0045a647;
      }
      goto LAB_0045a63b;
    }
    if (cVar1 != '`') {
      node_free(value);
      expr_error(s_Hex_constant_expected_004d2a4c);
      return;
    }
  }
  else if (local_4 == 3) {
    if (cVar1 == '$') goto LAB_0045a256;
    goto LAB_0045a25d;
  }
  if (cVar1 == '`') {
LAB_0045a33f:
    pcVar18 = pcVar18 + 1;
    optr = pcVar18;
LAB_0045a346:
    cVar12 = *pcVar18;
    if (('/' < cVar12) && (cVar12 < ':')) {
      iVar4 = 0;
      pcVar19 = pcVar18;
      do {
        if ('9' < cVar12) break;
        iVar4 = iVar4 * 10;
        *(int *)(value + 1) = cVar12 + -0x30 + *(int *)(value + 1) * 10;
        optr = optr + 1;
        iVar5 = *(int *)(value + 2);
        uVar6 = *(uint *)(value + 1);
        iVar8 = *(int *)((int)value + 0xc) * 10;
        *(int *)((int)value + 0xc) = iVar8;
        *(int *)(value + 2) = iVar5 * 10;
        if (0xfffffff < uVar6) {
          *(uint *)((int)value + 0xc) = (uVar6 >> 0x1c) + iVar8;
          *(uint *)(value + 1) = uVar6 & 0xfffffff;
        }
        uVar6 = *(uint *)((int)value + 0xc);
        if (0xfffffff < uVar6) {
          *(uint *)(value + 2) = (uVar6 >> 0x1c) + iVar5 * 10;
          *(uint *)((int)value + 0xc) = uVar6 & 0xfffffff;
        }
        uVar6 = *(uint *)(value + 2);
        if (0xfffffff < uVar6) {
          iVar4 = iVar4 + (uVar6 >> 0x1c);
          *(uint *)(value + 2) = uVar6 & 0xfffffff;
        }
        cVar12 = *optr;
        pcVar19 = optr;
      } while ('/' < cVar12);
      pcVar17 = pcVar18;
      if ((*pcVar19 != '.') && (*pcVar19 != 'e')) {
        if ((expr_mode & 0x10000000) == 0) {
          uVar6 = *(uint *)((int)value + 0xc);
          if ((expr_mode & 0x4000000) == 0) {
            *(uint *)(value + 1) = *(uint *)(value + 1) | uVar6 << 0x1c;
            *(uint *)((int)value + 0xc) = *(uint *)(value + 2) << 0x18 | uVar6 >> 4;
            *(uint *)(value + 2) = iVar4 << 0x14 | *(uint *)(value + 2) >> 8;
          }
          else {
            *(uint *)(value + 2) = uVar6 >> 0x14 & local_18;
            *(uint *)((int)value + 0xc) =
                 (uVar6 & 0xfffff) << 4 | *(uint *)(value + 1) >> 0x18 & 0xf;
            *(uint *)(value + 1) = *(uint *)(value + 1) & 0xffffff;
          }
        }
        else {
          *(uint *)(value + 2) = *(uint *)((int)value + 0xc) >> 4 & local_18;
          *(uint *)((int)value + 0xc) =
               *(uint *)(value + 1) >> 0x10 & 0xfff | (*(uint *)((int)value + 0xc) & 0xf) << 0xc;
          *(uint *)(value + 1) = *(uint *)(value + 1) & 0xffff;
        }
        if (*(int *)(value + 2) == 0) {
          if (*(int *)((int)value + 0xc) == 0) {
            return;
          }
          *(uint *)((int)value + 0x1c) = *(uint *)((int)value + 0x1c) & 0xfffffffa | 2;
          return;
        }
        *(uint *)((int)value + 0x1c) = *(uint *)((int)value + 0x1c) & 0xfffffffc | 4;
        return;
      }
      goto LAB_0045a5e3;
    }
  }
  else if (((local_4 == 1) || (local_4 == 2)) || (local_4 == 4)) {
    if (cVar1 == '`') goto LAB_0045a33f;
    goto LAB_0045a346;
  }
  if ((cVar12 != '.') ||
     (iVar4 = str_index1(CONCAT31((int3)((uint)pcVar18 >> 8),pcVar18[1]),s_0123456789_004d2a78),
     pcVar17 = optr, iVar4 == 0)) {
    node_free(value);
    expr_error(s_Invalid_expression_004d2a64);
    return;
  }
LAB_0045a5e3:
  optr = pcVar17;
  parse_float(value);
  *(undefined4 *)((int)value + 0x1c) = 0x204;
  return;
LAB_00459de2:
  local_c = pcVar18;
  if (0 < (int)pcVar18) {
    pcVar18[(int)pcVar17] = '\0';
    lVar7 = periph_find_reg(*(int *)(cur_dev + 4),optr,&local_8,&local_10);
    pcVar18[(int)optr] = cVar12;
    pcVar17 = optr;
    if (lVar7 != 0) {
      puVar14 = *(undefined4 **)(*(int *)(cur_dtype + 0x18) + 0x2c + local_8 * 0x48);
      iVar4 = *(int *)(cur_sim + 8);
      (*(code *)*puVar14)(local_8,local_10,value + 1);
      uVar6 = *(uint *)(puVar14[0xb] + 0x10 + local_10 * 0x1c);
      uVar15 = uVar6 & 0xfffc0007;
      if ((((expr_mode & 0x14000000) != 0) && ((uVar6 & 1) != 0)) && ((uVar6 & 0x2000000) != 0)) {
        uVar15 = 0x2000002;
        node_normalize(value);
      }
      uVar16 = (undefined2)(uVar15 >> 0x10);
      uVar13 = CONCAT11(1,(char)uVar15);
      *(uint *)((int)value + 0x1c) = CONCAT22(uVar16,uVar13);
      uVar6 = *(uint *)(*(int *)(iVar4 + local_8 * 8 + 4) + local_10 * 4);
      if ((uVar6 & 0x2000000) == 0) {
        if ((uVar6 & 0x2000) != 0) {
          node_get_double(expr_mode,value);
          *(uint *)((int)value + 0x1c) = *(uint *)((int)value + 0x1c) | 0x200;
        }
      }
      else {
        *(uint *)((int)value + 0x1c) = CONCAT22(uVar16,uVar13) | 0x2000;
      }
      optr = optr + (int)local_c;
      return;
    }
  }
LAB_00459ef3:
  if (bVar3) {
    node_free(value);
    expr_error(s_Invalid_register_name_004d2ac8);
    return;
  }
  goto LAB_00459f17;
LAB_00459fcf:
  if (cVar12 == '@') {
    do {
      do {
        cVar12 = pcVar18[iVar4 + 1];
        iVar4 = iVar4 + 1;
      } while (cVar12 == '_');
      if (__mb_cur_max < 2) {
        uVar6 = *(ushort *)(_pctype + cVar12 * 2) & 0x107;
        puVar10 = _pctype;
      }
      else {
        uVar6 = _isctype((int)cVar12,0x107);
        puVar10 = extraout_ECX_01;
        pcVar17 = optr;
      }
    } while (uVar6 != 0);
  }
  if (0 < iVar4) {
    pcVar19 = pcVar18 + iVar4;
    *pcVar19 = '\0';
    local_c = pcVar19;
    iVar4 = dbg_resolve_symbol(pcVar18,value);
    puVar10 = extraout_ECX_02;
    if (iVar4 == 0) {
      iVar4 = dbg_parse_file_line(pcVar18,value,&local_4);
      bVar3 = false;
      puVar10 = extraout_ECX_03;
      if (iVar4 != 0) goto LAB_0045a049;
    }
    else {
LAB_0045a049:
      bVar3 = true;
    }
    *pcVar19 = cVar12;
    pcVar17 = optr;
    if (bVar3) {
      if (*(int *)(value + 3) == 4) {
        uVar6 = *(uint *)((int)value + 0x14);
        *(uint *)(value + 1) = uVar6;
        if ((uVar6 & local_14) != 0) {
          *(uint *)(value + 1) = ~local_1c | uVar6;
        }
        *(uint *)((int)value + 0x1c) = expr_mode & 0x16100000 | 0x101;
        optr = pcVar19;
        return;
      }
      iVar4 = memmap_find(*(int *)(value + 3),*(ulong *)((int)value + 0x14));
      *(short *)((int)value + 0x24) = (short)iVar4;
      uVar15 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar4 * 0x2c) & 0xff400003;
      uVar6 = ~*(uint *)(*(int *)(cur_dtype + 0x20) + iVar4 * 0x2c + 0x20);
      optr = local_c;
      if ((cVar12 == '+') || (cVar12 == '-')) {
        optr = local_c + 1;
        parse_primary();
        if (node_03 == (void *)0x0) {
          node_free(value);
          expr_error(s_Address_offset_expected_004d2ab0);
          return;
        }
        if (cVar12 == '+') {
          *(int *)((int)value + 0x14) = *(int *)((int)value + 0x14) + *(int *)((int)node_03 + 8);
        }
        else {
          *(int *)((int)value + 0x14) = *(int *)((int)value + 0x14) - *(int *)((int)node_03 + 8);
        }
        node_free(node_03);
      }
      addr = *(uint *)((int)value + 0x14);
      uVar11 = uVar6 & addr;
      if ((uVar11 != 0) && (uVar11 != uVar6)) {
        node_free(value);
        expr_error(s_Address_too_large_004d2a9c);
        return;
      }
      *(uint *)(value + 1) = addr;
      *(uint *)((int)value + 0x1c) = CONCAT22((short)(uVar15 >> 0x10),CONCAT11(0x41,(char)uVar15));
      iVar4 = mem_addr_check(iVar4,addr);
      if (iVar4 != 2) {
        return;
      }
      if (((*(byte *)((int)value + 0x1c) & 2) != 0) && ((expr_mode & 0x1000) != 0)) {
        *(uint *)(value + 1) = *(uint *)(value + 1) & 0xffff | *(uint *)((int)value + 0xc) << 0x10;
        *(uint *)((int)value + 0xc) = *(uint *)((int)value + 0xc) >> 8;
      }
      dVar20 = node_get_double(expr_mode,value);
      *value = dVar20;
      *(uint *)((int)value + 0x1c) = uVar15 | 0x4200;
      return;
    }
  }
  goto LAB_0045a1e1;
}


/* ==== stricmp_ci2 @ 0045a7b0 ==== */

int __cdecl stricmp_ci2(char *a,char *b)

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


/* ==== node_free @ 0045a860 ==== */

void __cdecl node_free(void *node)

{
  if (node != (void *)0x0) {
    dsp_free(node);
  }
  return;
}


/* ==== parse_float @ 0045a880 ==== */

void __cdecl parse_float(void *node)

{
  void *pvVar1;
  double dVar2;
  
  pvVar1 = node;
  *(undefined4 *)node = 0;
  *(undefined4 *)((int)node + 4) = 0;
  dVar2 = strtod(optr,&node);
  *(double *)pvVar1 = dVar2;
  optr = node;
  return;
}


/* ==== expr_error @ 0045a8c0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl expr_error(char *msg)

{
  asm_result = 0xffffffff;
  parm_errmsg = msg;
  _expr_err_msg = msg;
  return;
}


/* ==== expr_error2 @ 0045a8e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void expr_error2(char *prefix,char *msg)

{
  sprintf(&status1_buf,s__s___s_004d2afc,prefix,msg);
  parm_errmsg = &status1_buf;
  _expr_err_msg = &status1_buf;
  asm_result = 0xffffffff;
  return;
}


/* ==== str_index1 @ 0045a920 ==== */

int __cdecl str_index1(int c,char *set)

{
  char *pcVar1;
  char cVar2;
  
  cVar2 = *set;
  if (cVar2 == '\0') {
    return 0;
  }
  pcVar1 = set;
  do {
    pcVar1 = pcVar1 + 1;
    if (cVar2 == (char)c) {
      return (int)pcVar1 - (int)set;
    }
    cVar2 = *pcVar1;
  } while (cVar2 != '\0');
  return 0;
}


/* ==== node_to_double @ 0045a950 ==== */

void __cdecl node_to_double(ulong mode,void *node)

{
  expr_mode = mode;
  if ((*(uint *)((int)node + 0x1c) & 4) != 0) {
    long_to_frac(node);
    return;
  }
  if ((*(uint *)((int)node + 0x1c) & 2) != 0) {
    dword_to_frac(mode,node);
    return;
  }
  word_to_frac(mode,node);
  return;
}


/* ==== node_get_double @ 0045a990 ==== */

double __cdecl node_get_double(ulong mode,void *node)

{
  expr_mode = mode;
  if ((*(uint *)((int)node + 0x1c) & 0x200) == 0) {
    node_to_double(mode,node);
  }
  return *(double *)node;
}


/* ==== node_from_double @ 0045a9c0 ==== */

void __cdecl node_from_double(ulong mode,void *node)

{
  expr_mode = mode;
  if ((*(uint *)((int)node + 0x1c) & 4) != 0) {
    frac_to_long(node);
    return;
  }
  if ((*(uint *)((int)node + 0x1c) & 2) == 0) {
    frac_to_word(mode,node);
  }
  else {
    if ((mode & 0x80) != 0) {
      *(undefined4 *)((int)node + 8) = *(undefined4 *)node;
      *(undefined4 *)((int)node + 0xc) = *(undefined4 *)((int)node + 4);
      return;
    }
    frac_to_dword(mode,node);
    if ((*(uint *)((int)node + 0xc) &
        (-(uint)((expr_mode & 0x10000000) != 0) & 0xff808000) + 0x800000) != 0) {
      *(uint *)((int)node + 0x10) = (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff10) + 0xff;
      return;
    }
  }
  return;
}


/* ==== op_add @ 0045aa50 ==== */

int __cdecl op_add(void *a,void *b)

{
  double dVar1;
  double dVar2;
  
  if (((~*(uint *)((int)a + 0x1c) & 0x200) != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    *(int *)((int)a + 8) = *(int *)((int)a + 8) + *(int *)((int)b + 8);
    *(int *)((int)a + 0x10) = *(int *)((int)a + 0x10) + *(int *)((int)b + 0x10);
    *(int *)((int)a + 0xc) = *(int *)((int)a + 0xc) + *(int *)((int)b + 0xc);
    node_normalize(a);
    return 1;
  }
  dVar1 = node_get_double(expr_mode,a);
  dVar2 = node_get_double(expr_mode,b);
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  *(double *)a = dVar2 + dVar1;
  return 1;
}


/* ==== op_add32 @ 0045aaf0 ==== */

int __cdecl op_add32(void *a,void *b)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = ~*(uint *)((int)a + 0x1c) >> 9 & 1;
  if (((*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 6) != 0) {
    uVar1 = 0;
  }
  if ((uVar1 != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    *(int *)((int)a + 8) = *(int *)((int)a + 8) + *(int *)((int)b + 8);
    return 1;
  }
  dVar2 = node_get_double(expr_mode,b);
  dVar3 = node_get_double(expr_mode,a);
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  *(double *)a = dVar3 + dVar2;
  return 1;
}


/* ==== op_sub @ 0045ab90 ==== */

int __cdecl op_sub(void *a,void *b)

{
  double dVar1;
  double dVar2;
  
  if (((~*(uint *)((int)a + 0x1c) & 0x200) != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    node_neg(b);
    op_add(a,b);
    node_neg(b);
    return 1;
  }
  dVar1 = node_get_double(expr_mode,a);
  dVar2 = node_get_double(expr_mode,b);
  *(double *)a = dVar1 - dVar2;
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  return 1;
}


/* ==== op_sub32 @ 0045ac20 ==== */

int __cdecl op_sub32(void *a,void *b)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = ~*(uint *)((int)a + 0x1c) >> 9 & 1;
  if (((*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 6) != 0) {
    uVar1 = 0;
  }
  if ((uVar1 != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    node_neg32(b);
    op_add32(a,b);
    node_neg32(b);
    return 1;
  }
  dVar2 = node_get_double(expr_mode,a);
  dVar3 = node_get_double(expr_mode,b);
  *(double *)a = dVar2 - dVar3;
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  return 1;
}


/* ==== op_mul @ 0045acd0 ==== */

int __cdecl op_mul(void *a,void *b)

{
  ulong uVar1;
  int *piVar2;
  ulong *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  double dVar9;
  double dVar10;
  void *pvVar11;
  ulong local_60 [8];
  ulong local_40 [8];
  ulong local_20 [8];
  
  if (((~*(uint *)((int)a + 0x1c) & 0x200) != 0) &&
     (iVar5 = 0, (~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    uVar6 = (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff88) + 0x80;
    bVar8 = (uVar6 & *(uint *)((int)a + 0x10)) != 0;
    if ((bool)bVar8) {
      node_neg(a);
    }
    if ((*(uint *)((int)b + 0x10) & uVar6) != 0) {
      node_neg(b);
      bVar8 = bVar8 | 2;
    }
    mp_unpack((ulong *)((int)a + 8),local_60);
    mp_unpack((ulong *)((int)b + 8),local_40);
    uVar6 = 0;
    iVar4 = 0;
    do {
      if (-1 < iVar4) {
        puVar3 = local_60;
        piVar2 = (int *)((int)local_40 + iVar4);
        iVar7 = iVar5 + 1;
        do {
          uVar1 = *puVar3;
          puVar3 = puVar3 + 1;
          uVar6 = uVar6 + uVar1 * *piVar2;
          piVar2 = piVar2 + -1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      iVar7 = iVar4 + 4;
      *(uint *)((int)local_20 + iVar4) = uVar6 & 0xff;
      uVar6 = uVar6 >> 8;
      iVar5 = iVar5 + 1;
      iVar4 = iVar7;
    } while (iVar7 < 0x1c);
    mp_pack(local_20,(ulong *)((int)a + 8));
    pvVar11 = a;
    if (bVar8 != 1) {
      pvVar11 = b;
      if (bVar8 == 2) {
        node_neg(a);
      }
      else if (bVar8 != 3) {
        *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | *(uint *)((int)b + 0x1c);
        return 1;
      }
    }
    node_neg(pvVar11);
    *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | *(uint *)((int)b + 0x1c);
    return 1;
  }
  dVar9 = node_get_double(expr_mode,b);
  dVar10 = node_get_double(expr_mode,a);
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  *(double *)a = dVar10 * dVar9;
  return 1;
}


/* ==== op_mul32 @ 0045ae60 ==== */

int __cdecl op_mul32(void *a,void *b)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = ~*(uint *)((int)a + 0x1c) >> 9 & 1;
  if (((*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 6) != 0) {
    uVar1 = 0;
  }
  if ((uVar1 != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    *(int *)((int)a + 8) = *(int *)((int)b + 8) * *(int *)((int)a + 8);
    return 1;
  }
  dVar2 = node_get_double(expr_mode,a);
  dVar3 = node_get_double(expr_mode,b);
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  *(double *)a = dVar3 * dVar2;
  return 1;
}


/* ==== op_div @ 0045af00 ==== */

int __cdecl op_div(void *a,void *b)

{
  uint uVar1;
  byte bVar2;
  double dVar3;
  double dVar4;
  ulong local_18;
  undefined4 local_14;
  undefined4 local_10;
  ulong local_c [3];
  
  if (((~*(uint *)((int)a + 0x1c) & 0x200) == 0) || ((~*(uint *)((int)b + 0x1c) >> 9 & 1) == 0)) {
    dVar3 = node_get_double(expr_mode,b);
    if (dVar3 == 0.0) {
      expr_error(s_Divide_by_0_004d2b04);
      return 0;
    }
    dVar4 = node_get_double(expr_mode,a);
    *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
    *(double *)a = dVar4 / dVar3;
    return 1;
  }
  if (((*(int *)((int)b + 0x10) == 0) && (*(int *)((int)b + 0xc) == 0)) &&
     (*(int *)((int)b + 8) == 0)) {
    expr_error(s_Divide_by_0_004d2b04);
    return 0;
  }
  uVar1 = (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff88) + 0x80;
  bVar2 = (*(uint *)((int)a + 0x10) & uVar1) != 0;
  if ((bool)bVar2) {
    node_neg(a);
  }
  if ((*(uint *)((int)b + 0x10) & uVar1) != 0) {
    node_neg(b);
    bVar2 = bVar2 | 2;
  }
  mp_divmod((ulong *)((int)a + 8),(ulong *)((int)b + 8),&local_18,local_c);
  *(undefined4 *)((int)a + 0xc) = local_14;
  *(ulong *)((int)a + 8) = local_18;
  *(undefined4 *)((int)a + 0x10) = local_10;
  if (bVar2 != 1) {
    if (bVar2 == 2) {
      node_neg(a);
    }
    else if (bVar2 != 3) {
      return 1;
    }
    node_neg(b);
    return 1;
  }
  node_neg(a);
  return 1;
}


/* ==== op_div32 @ 0045b080 ==== */

int __cdecl op_div32(void *a,void *b)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = ~*(uint *)((int)a + 0x1c) >> 9 & 1;
  if (((*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 6) != 0) {
    uVar1 = 0;
  }
  if ((uVar1 != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    if (*(int *)((int)b + 8) == 0) {
      expr_error(s_Divide_by_0_004d2b04);
      return 0;
    }
    *(int *)((int)a + 8) = *(int *)((int)a + 8) / *(int *)((int)b + 8);
    return 1;
  }
  dVar2 = node_get_double(expr_mode,b);
  if (dVar2 == 0.0) {
    expr_error(s_Divide_by_0_004d2b04);
    return 0;
  }
  dVar3 = node_get_double(expr_mode,a);
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  *(double *)a = dVar3 / dVar2;
  return 1;
}


/* ==== op_mod @ 0045b160 ==== */

int __cdecl op_mod(void *a,void *b)

{
  double dVar1;
  ulong local_18;
  undefined4 local_14;
  undefined4 local_10;
  ulong local_c [3];
  
  if (((~*(uint *)((int)a + 0x1c) & 0x200) == 0) || ((~*(uint *)((int)b + 0x1c) >> 9 & 1) == 0)) {
    dVar1 = node_get_double(expr_mode,b);
    if (dVar1 == 0.0) {
      expr_error(s_Divide_by_0_004d2b04);
      return 0;
    }
    node_get_double(expr_mode,a);
    dVar1 = _CIfmod();
    *(double *)a = dVar1;
    *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
    return 1;
  }
  if (((*(int *)((int)b + 0x10) == 0) && (*(int *)((int)b + 0xc) == 0)) &&
     (*(int *)((int)b + 8) == 0)) {
    expr_error(s_Divide_by_0_004d2b04);
    return 0;
  }
  mp_divmod((ulong *)((int)a + 8),(ulong *)((int)b + 8),local_c,&local_18);
  *(ulong *)((int)a + 8) = local_18;
  *(undefined4 *)((int)a + 0xc) = local_14;
  *(undefined4 *)((int)a + 0x10) = local_10;
  return 1;
}


/* ==== op_mod32 @ 0045b250 ==== */

int __cdecl op_mod32(void *a,void *b)

{
  uint uVar1;
  double dVar2;
  
  uVar1 = ~*(uint *)((int)a + 0x1c) >> 9 & 1;
  if (((*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 6) != 0) {
    uVar1 = 0;
  }
  if ((uVar1 != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    if (*(int *)((int)b + 8) == 0) {
      expr_error(s_Divide_by_0_004d2b04);
      return 0;
    }
    *(int *)((int)a + 8) = *(int *)((int)a + 8) % *(int *)((int)b + 8);
    return 1;
  }
  dVar2 = node_get_double(expr_mode,b);
  if (dVar2 == 0.0) {
    expr_error(s_Divide_by_0_004d2b04);
    return 0;
  }
  node_get_double(expr_mode,a);
  dVar2 = _CIfmod();
  *(double *)a = dVar2;
  *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) | 0x200;
  return 1;
}


/* ==== op_or @ 0045b330 ==== */

int __cdecl op_or(void *a,void *b)

{
  if (((~*(uint *)((int)a + 0x1c) & 0x200) != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    *(uint *)((int)a + 0x10) = *(uint *)((int)a + 0x10) | *(uint *)((int)b + 0x10);
    *(uint *)((int)a + 0xc) = *(uint *)((int)a + 0xc) | *(uint *)((int)b + 0xc);
    *(uint *)((int)a + 8) = *(uint *)((int)a + 8) | *(uint *)((int)b + 8);
    *(uint *)((int)a + 0x1c) = *(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c);
    return 1;
  }
  expr_error(s_Illegal_operator_for_floating_po_004d2b10);
  return 0;
}


/* ==== op_or32 @ 0045b3a0 ==== */

int __cdecl op_or32(void *a,void *b)

{
  *(uint *)((int)a + 0x10) = *(uint *)((int)a + 0x10) | *(uint *)((int)b + 0x10);
  *(uint *)((int)a + 0xc) = *(uint *)((int)a + 0xc) | *(uint *)((int)b + 0xc);
  *(uint *)((int)a + 8) = *(uint *)((int)a + 8) | *(uint *)((int)b + 8);
  *(uint *)((int)a + 0x1c) =
       (*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 0xfffffdff | 0x100;
  return 1;
}


/* ==== op_and @ 0045b3f0 ==== */

int __cdecl op_and(void *a,void *b)

{
  if (((~*(uint *)((int)a + 0x1c) & 0x200) != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    *(uint *)((int)a + 0x10) = *(uint *)((int)a + 0x10) & *(uint *)((int)b + 0x10);
    *(uint *)((int)a + 0xc) = *(uint *)((int)a + 0xc) & *(uint *)((int)b + 0xc);
    *(uint *)((int)a + 8) = *(uint *)((int)a + 8) & *(uint *)((int)b + 8);
    *(uint *)((int)a + 0x1c) = *(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c);
    return 1;
  }
  expr_error(s_Illegal_operator_for_floating_po_004d2b10);
  return 0;
}


/* ==== op_and32 @ 0045b460 ==== */

int __cdecl op_and32(void *a,void *b)

{
  *(uint *)((int)a + 0x10) = *(uint *)((int)a + 0x10) & *(uint *)((int)b + 0x10);
  *(uint *)((int)a + 0xc) = *(uint *)((int)a + 0xc) & *(uint *)((int)b + 0xc);
  *(uint *)((int)a + 8) = *(uint *)((int)a + 8) & *(uint *)((int)b + 8);
  *(uint *)((int)a + 0x1c) =
       (*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 0xfffffdff | 0x100;
  return 1;
}


/* ==== op_xor @ 0045b4b0 ==== */

int __cdecl op_xor(void *a,void *b)

{
  if (((~*(uint *)((int)a + 0x1c) & 0x200) != 0) && ((~*(uint *)((int)b + 0x1c) >> 9 & 1) != 0)) {
    *(uint *)((int)a + 0x10) = *(uint *)((int)a + 0x10) ^ *(uint *)((int)b + 0x10);
    *(uint *)((int)a + 0xc) = *(uint *)((int)a + 0xc) ^ *(uint *)((int)b + 0xc);
    *(uint *)((int)a + 8) = *(uint *)((int)a + 8) ^ *(uint *)((int)b + 8);
    *(uint *)((int)a + 0x1c) = *(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c);
    return 1;
  }
  expr_error(s_Illegal_operator_for_floating_po_004d2b10);
  return 0;
}


/* ==== op_xor32 @ 0045b520 ==== */

int __cdecl op_xor32(void *a,void *b)

{
  *(uint *)((int)a + 0x10) = *(uint *)((int)a + 0x10) ^ *(uint *)((int)b + 0x10);
  *(uint *)((int)a + 0xc) = *(uint *)((int)a + 0xc) ^ *(uint *)((int)b + 0xc);
  *(uint *)((int)a + 8) = *(uint *)((int)a + 8) ^ *(uint *)((int)b + 8);
  *(uint *)((int)a + 0x1c) =
       (*(uint *)((int)b + 0x1c) | *(uint *)((int)a + 0x1c)) & 0xfffffdff | 0x100;
  return 1;
}


/* ==== op_shl @ 0045b570 ==== */

int __cdecl op_shl(void *a,void *b)

{
  ulong uVar1;
  uint uVar2;
  
  if (((~*(uint *)((int)a + 0x1c) & 0x200) == 0) || ((~*(uint *)((int)b + 0x1c) >> 9 & 1) == 0)) {
    expr_error(s_Illegal_operator_for_floating_po_004d2b10);
    return 0;
  }
  uVar2 = ~expr_mode;
  uVar1 = node_word(b);
  if ((-1 < (int)uVar1) && ((int)uVar1 <= (int)((uVar2 & 0x10000000 | 0x60000000) >> 0x19))) {
    if (0 < (int)uVar1) {
      do {
        *(int *)((int)a + 8) = *(int *)((int)a + 8) << 1;
        *(int *)((int)a + 0x10) = *(int *)((int)a + 0x10) << 1;
        *(int *)((int)a + 0xc) = *(int *)((int)a + 0xc) << 1;
        node_normalize(a);
        uVar1 = uVar1 - 1;
      } while (uVar1 != 0);
    }
    return 1;
  }
  expr_error(s_Invalid_shift_amount_004c265c);
  return 0;
}


/* ==== op_shl32 @ 0045b620 ==== */

int __cdecl op_shl32(void *a,void *b)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)b + 8);
  if ((-1 < iVar2) && (iVar2 < 0x61)) {
    if (0 < iVar2) {
      do {
        iVar1 = *(int *)((int)a + 0x10) * 2;
        *(int *)((int)a + 0x10) = iVar1;
        if ((*(uint *)((int)a + 0xc) & 0x80000000) != 0) {
          *(int *)((int)a + 0x10) = iVar1 + 1;
        }
        iVar1 = *(uint *)((int)a + 0xc) * 2;
        *(int *)((int)a + 0xc) = iVar1;
        if ((*(uint *)((int)a + 8) & 0x80000000) != 0) {
          *(int *)((int)a + 0xc) = iVar1 + 1;
        }
        iVar2 = iVar2 + -1;
        *(uint *)((int)a + 8) = *(uint *)((int)a + 8) * 2;
      } while (iVar2 != 0);
    }
    *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) & 0xfffffdff | 0x100;
    return 1;
  }
  expr_error(s_Invalid_shift_amount_004c265c);
  return 0;
}


/* ==== op_shr @ 0045b6a0 ==== */

int __cdecl op_shr(void *a,void *b)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = (-(uint)((expr_mode & 0x10000000) != 0) & 0xff808000) + 0x800000;
  if (((~*(uint *)((int)a + 0x1c) & 0x200) == 0) || ((~*(uint *)((int)b + 0x1c) >> 9 & 1) == 0)) {
    expr_error(s_Illegal_operator_for_floating_po_004d2b10);
    return 0;
  }
  uVar1 = ~expr_mode;
  b = (void *)node_word(b);
  if ((-1 < (int)b) && ((int)b <= (int)((uVar1 & 0x10000000 | 0x60000000) >> 0x19))) {
    uVar1 = (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff88) + 0x80;
    if (0 < (int)b) {
      do {
        uVar2 = *(uint *)((int)a + 8) >> 1;
        *(uint *)((int)a + 8) = uVar2;
        if ((*(uint *)((int)a + 0xc) & 1) != 0) {
          *(uint *)((int)a + 8) = uVar4 | uVar2;
        }
        uVar2 = *(uint *)((int)a + 0x10);
        uVar3 = *(uint *)((int)a + 0xc) >> 1;
        *(uint *)((int)a + 0xc) = uVar3;
        if ((uVar2 & 1) != 0) {
          *(uint *)((int)a + 0xc) = uVar4 | uVar3;
        }
        *(uint *)((int)a + 0x10) = uVar2 >> 1;
        if ((uVar2 & uVar1) != 0) {
          *(uint *)((int)a + 0x10) = uVar1 | uVar2 >> 1;
        }
        b = (void *)((int)b + -1);
      } while (b != (void *)0x0);
    }
    return 1;
  }
  expr_error(s_Invalid_shift_amount_004c265c);
  return 0;
}


/* ==== op_shr32 @ 0045b7b0 ==== */

int __cdecl op_shr32(void *a,void *b)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)b + 8);
  if ((-1 < iVar2) && (iVar2 < 0x61)) {
    if (0 < iVar2) {
      do {
        uVar1 = *(uint *)((int)a + 8) >> 1;
        *(uint *)((int)a + 8) = uVar1;
        if ((*(uint *)((int)a + 0xc) & 1) != 0) {
          *(uint *)((int)a + 8) = shr_fill_bit | uVar1;
        }
        uVar1 = *(uint *)((int)a + 0xc) >> 1;
        *(uint *)((int)a + 0xc) = uVar1;
        if ((*(uint *)((int)a + 0x10) & 1) != 0) {
          *(uint *)((int)a + 0xc) = shr_fill_bit | uVar1;
        }
        uVar1 = *(uint *)((int)a + 0x10) >> 1;
        *(uint *)((int)a + 0x10) = uVar1;
        if ((uVar1 & 0x40000000) != 0) {
          *(uint *)((int)a + 0x10) = shr_fill_bit | uVar1;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    *(uint *)((int)a + 0x1c) = *(uint *)((int)a + 0x1c) & 0xfffffdff | 0x100;
    return 1;
  }
  expr_error(s_Invalid_shift_amount_004c265c);
  return 0;
}


/* ==== op_land @ 0045b850 ==== */

int __cdecl op_land(void *a,void *b)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = node_sign(a);
  if (iVar1 != 0) {
    iVar1 = node_sign(b);
    if (iVar1 != 0) {
      uVar2 = 1;
      goto LAB_0045b87c;
    }
  }
  uVar2 = 0;
LAB_0045b87c:
  *(undefined4 *)((int)a + 8) = uVar2;
  *(undefined4 *)((int)a + 0xc) = 0;
  *(undefined4 *)((int)a + 0x10) = 0;
  *(undefined4 *)((int)a + 0x1c) = 0x2101;
  return 1;
}


/* ==== op_land32 @ 0045b8a0 ==== */

int __cdecl op_land32(void *a,void *b)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = node_sign32(a);
  if (iVar1 != 0) {
    iVar1 = node_sign32(b);
    if (iVar1 != 0) {
      uVar2 = 1;
      goto LAB_0045b8cc;
    }
  }
  uVar2 = 0;
LAB_0045b8cc:
  *(undefined4 *)((int)a + 8) = uVar2;
  *(undefined4 *)((int)a + 0xc) = 0;
  *(undefined4 *)((int)a + 0x10) = 0;
  *(undefined4 *)((int)a + 0x1c) = 0x2101;
  return 1;
}


/* ==== op_lor @ 0045b8f0 ==== */

int __cdecl op_lor(void *a,void *b)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = node_sign(a);
  if (iVar1 == 0) {
    iVar1 = node_sign(b);
    uVar2 = 0;
    if (iVar1 == 0) goto LAB_0045b918;
  }
  uVar2 = 1;
LAB_0045b918:
  *(undefined4 *)((int)a + 8) = uVar2;
  *(undefined4 *)((int)a + 0xc) = 0;
  *(undefined4 *)((int)a + 0x10) = 0;
  *(undefined4 *)((int)a + 0x1c) = 0x2101;
  return 1;
}


/* ==== op_lor32 @ 0045b940 ==== */

int __cdecl op_lor32(void *a,void *b)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = node_sign32(a);
  if (iVar1 == 0) {
    iVar1 = node_sign32(b);
    uVar2 = 0;
    if (iVar1 == 0) goto LAB_0045b968;
  }
  uVar2 = 1;
LAB_0045b968:
  *(undefined4 *)((int)a + 8) = uVar2;
  *(undefined4 *)((int)a + 0xc) = 0;
  *(undefined4 *)((int)a + 0x10) = 0;
  *(undefined4 *)((int)a + 0x1c) = 0x2101;
  return 1;
}


/* ==== node_neg @ 0045b990 ==== */

void __cdecl node_neg(void *node)

{
  if ((*(uint *)((int)node + 0x1c) & 0x200) != 0) {
    *(double *)node = -*(double *)node;
    return;
  }
  node_not(node);
  *(int *)((int)node + 8) = *(int *)((int)node + 8) + 1;
  node_normalize(node);
  return;
}


/* ==== node_neg32 @ 0045b9c0 ==== */

void __cdecl node_neg32(void *node)

{
  uint uVar1;
  
  if (((*(uint *)((int)node + 0x1c) & 6) != 0) && ((*(uint *)((int)node + 0x1c) & 0x200) == 0)) {
    node_get_double(expr_mode,node);
    *(uint *)((int)node + 0x1c) = *(uint *)((int)node + 0x1c) | 0x200;
  }
  if ((*(uint *)((int)node + 0x1c) & 0x200) != 0) {
    *(uint *)((int)node + 4) = *(uint *)((int)node + 4) ^ 0x80000000;
    return;
  }
  uVar1 = *(uint *)((int)node + 0xc);
  *(uint *)((int)node + 0xc) = ~uVar1;
  if (*(int *)((int)node + 8) == 0) {
    *(uint *)((int)node + 0xc) = ~uVar1 + 1;
    return;
  }
  *(int *)((int)node + 8) = -*(int *)((int)node + 8);
  return;
}


/* ==== node_not @ 0045ba20 ==== */

int __cdecl node_not(void *node)

{
  uint uVar1;
  
  if ((*(uint *)((int)node + 0x1c) & 0x200) != 0) {
    expr_error(s_Cannot_apply_____operator_to_flo_004d2b3c);
    return 0;
  }
  uVar1 = (-(uint)((expr_mode & 0x10000000) != 0) & 0xff010000) + 0xffffff;
  *(uint *)((int)node + 0x10) =
       (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff10) + 0xff & ~*(uint *)((int)node + 0x10);
  *(uint *)((int)node + 0xc) = uVar1 & ~*(uint *)((int)node + 0xc);
  *(uint *)((int)node + 8) = uVar1 & ~*(uint *)((int)node + 8);
  return 1;
}


/* ==== node_not32 @ 0045baa0 ==== */

int __cdecl node_not32(void *node)

{
  *(uint *)((int)node + 0xc) = ~*(uint *)((int)node + 0xc);
  *(uint *)((int)node + 0x10) = ~*(uint *)((int)node + 0x10);
  *(uint *)((int)node + 8) = ~*(uint *)((int)node + 8);
  *(uint *)((int)node + 0x1c) = *(uint *)((int)node + 0x1c) & 0xfffffdff | 0x100;
  return 1;
}


/* ==== node_lnot @ 0045bad0 ==== */

void __cdecl node_lnot(void *node)

{
  int iVar1;
  
  iVar1 = node_sign(node);
  *(undefined4 *)((int)node + 0x1c) = 0x2101;
  *(uint *)((int)node + 8) = (uint)(iVar1 == 0);
  *(undefined4 *)((int)node + 0xc) = 0;
  *(undefined4 *)((int)node + 0x10) = 0;
  return;
}


/* ==== node_lnot32 @ 0045bb00 ==== */

void __cdecl node_lnot32(void *node)

{
  int iVar1;
  
  iVar1 = node_sign32(node);
  *(undefined4 *)((int)node + 0x1c) = 0x2101;
  *(uint *)((int)node + 8) = (uint)(iVar1 == 0);
  *(undefined4 *)((int)node + 0xc) = 0;
  *(undefined4 *)((int)node + 0x10) = 0;
  return;
}


/* ==== node_sign @ 0045bb30 ==== */

int __cdecl node_sign(void *node)

{
  uint uVar1;
  
  if ((*(uint *)((int)node + 0x1c) & 0x200) == 0) {
    if (((*(uint *)((int)node + 0x10) == 0) && (*(int *)((int)node + 0xc) == 0)) &&
       (*(int *)((int)node + 8) == 0)) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
    if ((uVar1 != 0) &&
       ((*(uint *)((int)node + 0x10) & (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff88) + 0x80)
        != 0)) {
      uVar1 = 0xffffffff;
    }
  }
  else {
    uVar1 = (uint)(*(double *)node != 0.0);
    if ((uVar1 != 0) && (*(double *)node < 0.0)) {
      return -1;
    }
  }
  return uVar1;
}


/* ==== node_sign32 @ 0045bbc0 ==== */

int __cdecl node_sign32(void *node)

{
  int iVar1;
  
  if (((*(uint *)((int)node + 0x1c) & 6) != 0) && ((*(uint *)((int)node + 0x1c) & 0x200) == 0)) {
    node_get_double(expr_mode,node);
    *(uint *)((int)node + 0x1c) = *(uint *)((int)node + 0x1c) | 0x200;
  }
  if ((*(uint *)((int)node + 0x1c) & 0x200) == 0) {
    if (((*(uint *)((int)node + 0x10) == 0) && (*(int *)((int)node + 0xc) == 0)) &&
       (*(int *)((int)node + 8) == 0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
    if ((iVar1 != 0) && ((*(uint *)((int)node + 0x10) & 0x80000000) != 0)) {
      iVar1 = -1;
    }
  }
  else {
    if ((*(int *)node == 0) && ((*(uint *)((int)node + 4) & 0x7fffffff) == 0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
    if ((iVar1 != 0) && ((*(uint *)((int)node + 4) & 0x80000000) != 0)) {
      return -1;
    }
  }
  return iVar1;
}


/* ==== node_normalize @ 0045bc50 ==== */

void __cdecl node_normalize(void *node)

{
  sbyte sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = expr_mode & 0x1000000;
  if ((expr_mode & 0x10000000) == 0) {
    uVar3 = 0xffffff;
    uVar4 = 0xff;
    sVar1 = 0x18;
  }
  else {
    uVar3 = 0xffff;
    sVar1 = 0x10;
    uVar4 = 0xffff;
  }
  uVar2 = *(uint *)((int)node + 8);
  *(uint *)((int)node + 8) = uVar3 & uVar2;
  uVar2 = *(int *)((int)node + 0xc) + (uVar2 >> sVar1 & uVar4);
  *(uint *)((int)node + 0xc) = uVar2;
  *(uint *)((int)node + 0xc) = *(uint *)((int)node + 0xc) & uVar3;
  *(uint *)((int)node + 0x10) =
       (uVar2 >> sVar1 & uVar4) + *(int *)((int)node + 0x10) &
       (-(uint)(uVar5 != 0) & 0xffffff10) + 0xff;
  return;
}


/* ==== op_compare @ 0045bce0 ==== */

int __cdecl op_compare(void *a,void *b,int op)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  double dVar7;
  double dVar8;
  
  uVar3 = ~*(uint *)((int)a + 0x1c) >> 9 & 1;
  uVar2 = (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff88) + 0x80;
  uVar4 = ~*(uint *)((int)b + 0x1c) >> 9 & 1;
  if (uVar3 == 0) {
    if (0.0 <= *(double *)a) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
  }
  else {
    bVar5 = (*(uint *)((int)a + 0x10) & uVar2) != 0;
  }
  if (uVar4 == 0) {
    if (0.0 <= *(double *)b) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
  }
  else {
    bVar6 = (*(uint *)((int)b + 0x10) & uVar2) != 0;
  }
  iVar1 = (-(uint)(bVar5 != false) & 0xfffffffe) + 1;
  if (bVar5 == bVar6) {
    if ((uVar3 == 0) || (uVar4 == 0)) {
      dVar7 = node_get_double(expr_mode,b);
      dVar8 = node_get_double(expr_mode,a);
      if (dVar8 <= dVar7) {
        if (dVar7 <= dVar8) {
LAB_0045be81:
          iVar1 = 0;
        }
        else {
          iVar1 = -1;
        }
      }
      else {
        iVar1 = 1;
      }
    }
    else {
      if (((expr_mode & 0x10000000) != 0) && ((expr_mode & 0x4000000) != 0)) {
        if ((*(uint *)((int)b + 0x1c) & 0x4000) != 0) {
          uVar2 = *(uint *)((int)a + 0xc);
          *(undefined4 *)((int)a + 0xc) = 0;
          *(uint *)((int)a + 8) = *(uint *)((int)a + 8) & 0xffff | (uVar2 & 0xff) << 0x10;
        }
        if ((*(uint *)((int)a + 0x1c) & 0x4000) != 0) {
          uVar2 = *(uint *)((int)b + 0xc);
          *(undefined4 *)((int)b + 0xc) = 0;
          *(uint *)((int)b + 8) = *(uint *)((int)b + 8) & 0xffff | (uVar2 & 0xff) << 0x10;
        }
      }
      if (*(uint *)((int)a + 0x10) == *(uint *)((int)b + 0x10)) {
        if (*(uint *)((int)a + 0xc) == *(uint *)((int)b + 0xc)) {
          if (*(uint *)((int)a + 8) == *(uint *)((int)b + 8)) goto LAB_0045be81;
          if (*(uint *)((int)a + 8) < *(uint *)((int)b + 8)) {
            iVar1 = -iVar1;
          }
        }
        else if (*(uint *)((int)a + 0xc) < *(uint *)((int)b + 0xc)) {
          iVar1 = -iVar1;
        }
      }
      else if (*(uint *)((int)a + 0x10) < *(uint *)((int)b + 0x10)) {
        iVar1 = -iVar1;
      }
    }
  }
  switch(op) {
  case 0xb:
    *(uint *)((int)a + 8) = (uint)(iVar1 == -1);
    break;
  case 0xc:
    bVar5 = iVar1 == 1;
    goto LAB_0045bed4;
  case 0xd:
  case 0x13:
    *(uint *)((int)a + 8) = (uint)(iVar1 == 0);
    break;
  case 0xe:
    bVar5 = iVar1 == 1;
    goto LAB_0045bed1;
  case 0xf:
    *(uint *)((int)a + 8) = (uint)(iVar1 != -1);
    break;
  case 0x10:
    bVar5 = iVar1 == 0;
LAB_0045bed1:
    bVar5 = !bVar5;
LAB_0045bed4:
    *(uint *)((int)a + 8) = (uint)bVar5;
  }
  *(undefined4 *)((int)a + 0x1c) = 0x2101;
  *(undefined4 *)((int)a + 0xc) = 0;
  *(undefined4 *)((int)a + 0x10) = 0;
  return 1;
}


/* ==== op_compare32 @ 0045bf20 ==== */

int __cdecl op_compare32(void *a,void *b,int op)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  double local_10;
  double local_8;
  
  bVar5 = (*(uint *)((int)a + 0x1c) & 0x206) != 0;
  local_8 = 0.0;
  bVar6 = (*(uint *)((int)b + 0x1c) & 0x206) != 0;
  local_10 = 0.0;
  if (bVar5) {
    local_10 = node_get_double(expr_mode,a);
    iVar1 = *(int *)((int)a + 4);
  }
  else {
    iVar1 = *(int *)((int)a + 8);
  }
  if (bVar6) {
    local_8 = node_get_double(expr_mode,b);
    uVar2 = *(uint *)((int)b + 4);
  }
  else {
    uVar2 = *(uint *)((int)b + 8);
  }
  iVar4 = (-(uint)(-(iVar1 >> 0x1f) != 0) & 0xfffffffe) + 1;
  if (-(iVar1 >> 0x1f) == uVar2 >> 0x1f) {
    if (bVar5) {
      if (!bVar6) {
        local_8 = node_get_double(expr_mode,b);
      }
LAB_0045c00d:
      if (!bVar5) {
        local_10 = node_get_double(expr_mode,a);
      }
      uVar2 = *(uint *)((int)b + 4);
      if (((uVar2 & 0x7ff00000) == 0x7ff00000) && (((uVar2 & 0xfffff) != 0 || (*(int *)b != 0)))) {
        bVar5 = true;
      }
      else {
        bVar5 = false;
      }
      uVar3 = *(uint *)((int)a + 4);
      if (((uVar3 & 0x7ff00000) == 0x7ff00000) && (((uVar3 & 0xfffff) != 0 || (*(int *)a != 0)))) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if ((bVar6) && (bVar5)) {
        iVar4 = 0;
      }
      else if ((uVar3 == uVar2) && (*(int *)a == *(int *)b)) {
        iVar4 = 0;
      }
      else if ((bVar6) || (bVar5)) {
        iVar4 = 2;
      }
      else if (local_10 <= local_8) {
        if (local_8 <= local_10) goto LAB_0045c0c7;
        iVar4 = -1;
      }
      else {
        iVar4 = 1;
      }
    }
    else {
      if (bVar6) goto LAB_0045c00d;
      if (*(uint *)((int)a + 8) != *(uint *)((int)b + 8)) {
        if (*(uint *)((int)a + 8) < *(uint *)((int)b + 8)) {
          iVar4 = -iVar4;
        }
        goto LAB_0045c0d0;
      }
LAB_0045c0c7:
      iVar4 = 0;
    }
  }
LAB_0045c0d0:
  switch(op) {
  case 0xb:
    *(uint *)((int)a + 8) = (uint)(iVar4 == -1);
    break;
  case 0xc:
    bVar5 = iVar4 == 1;
    goto LAB_0045c130;
  case 0xd:
  case 0x13:
    *(uint *)((int)a + 8) = (uint)(iVar4 == 0);
    break;
  case 0xe:
    if (iVar4 != 0) {
      bVar5 = iVar4 == -1;
LAB_0045c116:
      if (!bVar5) {
        *(undefined4 *)((int)a + 8) = 0;
        break;
      }
    }
    goto LAB_0045c11f;
  case 0xf:
    if (iVar4 != 0) {
      bVar5 = iVar4 == 1;
      goto LAB_0045c116;
    }
LAB_0045c11f:
    *(undefined4 *)((int)a + 8) = 1;
    break;
  case 0x10:
    bVar5 = iVar4 != 0;
LAB_0045c130:
    *(uint *)((int)a + 8) = (uint)bVar5;
  }
  *(undefined4 *)((int)a + 0x1c) = 0x2101;
  *(undefined4 *)((int)a + 0xc) = 0;
  *(undefined4 *)((int)a + 0x10) = 0;
  return 1;
}


/* ==== mp_divmod @ 0045c180 ==== */

void __cdecl mp_divmod(ulong *num,ulong *den,ulong *quot,ulong *rem)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  ulong local_a0;
  ulong local_9c [7];
  ulong local_80 [8];
  ulong local_60 [8];
  ulong local_40 [8];
  ulong local_20 [8];
  
  iVar1 = mp_cmp(den,num);
  if (iVar1 < 1) {
    mp_unpack((ulong *)&mp_tmp,local_60);
    mp_unpack((ulong *)&mp_tmp,&local_a0);
    mp_unpack((ulong *)&mp_tmp,local_20);
    mp_unpack(num,local_40);
    mp_unpack(den,local_80);
    iVar1 = mp_len(local_80);
    iVar2 = mp_len(local_40);
    iVar2 = iVar2 + -2;
    if (-1 < iVar2) {
      do {
        mp_copy_limbs(&local_a0,local_9c,iVar1 + -1);
        local_a0 = local_40[iVar2];
        uVar3 = mp_div_digit(local_80,&local_a0,iVar1,local_20);
        local_60[iVar2] = uVar3;
        iVar2 = iVar2 + -1;
      } while (-1 < iVar2);
    }
    mp_pack(local_60,quot);
    mp_pack(&local_a0,rem);
    return;
  }
  *rem = *num;
  rem[1] = num[1];
  rem[2] = num[2];
  quot[2] = 0;
  quot[1] = 0;
  *quot = 0;
  return;
}


/* ==== mp_cmp @ 0045c2d0 ==== */

int __cdecl mp_cmp(ulong *a,ulong *b)

{
  if (b[2] != a[2]) {
    return (-(uint)(b[2] < a[2]) & 2) - 1;
  }
  if (b[1] != a[1]) {
    return (-(uint)(b[1] < a[1]) & 2) - 1;
  }
  if (*b != *a) {
    return (-(uint)(*b < *a) & 2) - 1;
  }
  return 0;
}


/* ==== mp_unpack @ 0045c320 ==== */

void __cdecl mp_unpack(ulong *val,ulong *limbs)

{
  uint uVar1;
  
  if ((expr_mode & 0x10000000) == 0) {
    limbs[7] = 0;
    limbs[6] = val[2] & 0xff;
    limbs[5] = (uint)*(byte *)((int)val + 6);
    limbs[4] = (uint)*(byte *)((int)val + 5);
    limbs[3] = val[1] & 0xff;
    uVar1 = (uint)*(byte *)((int)val + 2);
  }
  else {
    limbs[7] = 0;
    limbs[6] = 0;
    limbs[5] = 0;
    limbs[4] = val[2] & 0xff;
    limbs[3] = (uint)*(byte *)((int)val + 5);
    uVar1 = val[1] & 0xff;
  }
  limbs[2] = uVar1;
  limbs[1] = (uint)*(byte *)((int)val + 1);
  *limbs = *val & 0xff;
  return;
}


/* ==== mp_pack @ 0045c3b0 ==== */

void __cdecl mp_pack(ulong *limbs,ulong *val)

{
  ulong uVar1;
  uint uVar2;
  
  if ((expr_mode & 0x10000000) != 0) {
    val[2] = limbs[4];
    uVar1 = limbs[3];
    val[1] = uVar1 << 8;
    val[1] = limbs[2] | uVar1 << 8;
    uVar1 = limbs[1];
    *val = uVar1 << 8;
    *val = *limbs | uVar1 << 8;
    return;
  }
  val[2] = limbs[6];
  uVar1 = limbs[5];
  val[1] = uVar1 << 8;
  uVar2 = (limbs[4] | uVar1 << 8) << 8;
  val[1] = uVar2;
  val[1] = limbs[3] | uVar2;
  uVar1 = limbs[2];
  *val = uVar1 << 8;
  uVar2 = (limbs[1] | uVar1 << 8) << 8;
  *val = uVar2;
  *val = *limbs | uVar2;
  return;
}


/* ==== mp_copy_limbs @ 0045c430 ==== */

void __cdecl mp_copy_limbs(ulong *src,ulong *dst,int n)

{
  ulong *puVar1;
  
  if (-1 < n + -1) {
    puVar1 = dst + n + -1;
    do {
      *puVar1 = *(ulong *)(((int)src - (int)dst) + (int)puVar1);
      puVar1 = puVar1 + -1;
      n = n + -1;
    } while (n != 0);
  }
  return;
}


/* ==== mp_div_digit @ 0045c460 ==== */

ulong __cdecl mp_div_digit(ulong *den,ulong *rem,int n,ulong *tmp)

{
  int iVar1;
  ulong uVar2;
  ulong *puVar3;
  ulong d;
  
  iVar1 = n + -1;
  uVar2 = den[iVar1];
  puVar3 = den + iVar1;
  while( true ) {
    if (uVar2 != 0) {
      uVar2 = rem[iVar1] / den[iVar1];
      do {
        mp_mul_digit(uVar2,den,tmp,n);
        uVar2 = uVar2 - 1;
        iVar1 = mp_ge(tmp,rem,n);
      } while (iVar1 == 0);
      do {
        d = uVar2;
        mp_mul_digit(d + 1,den,tmp,n);
        iVar1 = mp_ge(tmp,rem,n);
        uVar2 = d + 1;
      } while (iVar1 != 0);
      mp_mul_digit(d,den,tmp,n);
      mp_sub(tmp,rem,n);
      return d;
    }
    iVar1 = iVar1 + -1;
    puVar3 = puVar3 + -1;
    if (iVar1 < 0) break;
    uVar2 = *puVar3;
  }
  return 0;
}


/* ==== mp_mul_digit @ 0045c510 ==== */

void __cdecl mp_mul_digit(ulong d,ulong *a,ulong *out,int n)

{
  ulong *puVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (n != 0) {
    puVar1 = out;
    do {
      uVar2 = uVar2 + *(int *)(((int)a - (int)out) + (int)puVar1) * d;
      *puVar1 = uVar2 & 0xff;
      uVar2 = uVar2 >> 8;
      n = n + -1;
      puVar1 = puVar1 + 1;
    } while (n != 0);
  }
  return;
}


/* ==== mp_ge @ 0045c550 ==== */

int __cdecl mp_ge(ulong *a,ulong *b,int n)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (n != 0) {
    iVar2 = (int)b - (int)a;
    do {
      uVar1 = (uint)((int)((*(int *)(iVar2 + (int)a) - uVar1) - *a) < 0);
      a = a + 1;
      n = n + -1;
    } while (n != 0);
  }
  return (uint)(uVar1 == 0);
}


/* ==== mp_sub @ 0045c590 ==== */

void __cdecl mp_sub(ulong *a,ulong *b,int n)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (n != 0) {
    iVar2 = (int)a - (int)b;
    do {
      uVar1 = (*b - *(int *)(iVar2 + (int)b)) - uVar1;
      *b = uVar1 & 0xff;
      uVar1 = (uint)((int)uVar1 < 0);
      b = b + 1;
      n = n + -1;
    } while (n != 0);
  }
  return;
}


/* ==== mp_len @ 0045c5d0 ==== */

int __cdecl mp_len(ulong *limbs)

{
  int iVar1;
  ulong *puVar2;
  
  iVar1 = 6;
  puVar2 = limbs + 6;
  do {
    if (*puVar2 != 0) break;
    iVar1 = iVar1 + -1;
    puVar2 = puVar2 + -1;
  } while (-1 < iVar1);
  return iVar1 + 2;
}


/* ==== ieee_single_to_double @ 0045c5f0 ==== */

void __cdecl ieee_single_to_double(ulong f,ulong *d)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = f & 0x80000000;
  if ((f & 0x7fffffff) == 0) {
    d[1] = uVar3;
    *d = 0;
    return;
  }
  if ((f & 0x7f800000) != 0x7f800000) {
    if ((f & 0x7f800000) != 0) {
      d[1] = f >> 3 & 0x7ffffff | (-(uint)((f & 0x40000000) != 0) & 0x8000000) + 0x38000000 | uVar3;
      *d = f << 0x1d;
      return;
    }
    uVar2 = 0x38000000;
    for (uVar1 = f & 0x7fffff; uVar1 < 0x400000; uVar1 = uVar1 << 1) {
      uVar2 = uVar2 - 0x100000;
    }
    d[1] = (uVar1 & 0x3fffff) >> 2 | uVar3 | uVar2;
    *d = uVar1 << 0x1e;
    return;
  }
  d[1] = f >> 3 | uVar3 | 0x7ff00000;
  *d = f << 0x1d;
  return;
}


/* ==== word_to_frac @ 0045c6c0 ==== */

void __cdecl word_to_frac(ulong mode,void *node)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  
  pvVar2 = node;
  if ((expr_mode & 0x80) != 0) {
    ieee_single_to_double(*(ulong *)((int)node + 8),node);
    return;
  }
  expr_mode = mode;
  uVar3 = *(uint *)((int)node + 0x1c);
  if ((uVar3 & 0x80000000) == 0) {
    if ((uVar3 & 0x40000000) == 0) {
      if ((uVar3 & 0x20000000) == 0) {
        if (((uVar3 & 0x10000000) == 0) && ((mode & 0x1000) == 0)) {
          if ((uVar3 & 0x8000000) == 0) {
            if ((uVar3 & 0x4000000) == 0) {
              if ((uVar3 & 0x2000000) == 0) {
                uVar3 = (-(uint)((mode & 0x10000000) != 0) & 0xff808000) + 0x7fffff;
              }
              else {
                uVar3 = 0x7fffffff;
              }
            }
            else {
              uVar3 = 0x7fffff;
            }
          }
          else {
            uVar3 = 0x7ffff;
          }
        }
        else {
          uVar3 = 0x7fff;
        }
      }
      else {
        uVar3 = 0x7ff;
      }
    }
    else {
      uVar3 = 0x7f;
    }
  }
  else {
    uVar3 = 7;
  }
  uVar1 = uVar3 + 1;
  node = (void *)((uVar1 | uVar3) & *(uint *)((int)node + 8));
  if (((uint)node & uVar1) != 0) {
    node = (void *)((uint)node | ~uVar3);
  }
  *(double *)pvVar2 = (double)(int)node / (double)uVar1;
  return;
}


/* ==== double_to_ieee_single @ 0045c7b0 ==== */

void __cdecl double_to_ieee_single(ulong *d)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = d[1];
  uVar2 = *d;
  uVar3 = uVar1 >> 0x14 & 0x7ff;
  uVar4 = uVar1 & 0x80000000;
  if (uVar3 == 0x7ff) {
    d[2] = (uVar1 & 0xfffff | 0xff00000) << 3 | uVar2 >> 0x1d | uVar4;
    return;
  }
  if (uVar3 < 0x36a) {
    d[2] = uVar4;
    return;
  }
  if (0x47e < uVar3) {
    d[2] = uVar4 | 0x7f800000;
    return;
  }
  if (uVar3 < 0x381) {
    d[2] = ((uVar1 & 0xfffff | 0x100000) << 3 | uVar2 >> 0x1d) >> (0x81U - (char)uVar3 & 0x1f) |
           uVar4;
    return;
  }
  uVar4 = (uVar1 & 0xfffff) << 3 | uVar2 >> 0x1d | (uVar3 + 0x80) * 0x800000 | uVar4;
  if ((0xfffffff < (uVar2 & 0x1fffffff)) && ((uVar2 & 0x2fffffff) != 0)) {
    uVar4 = uVar4 + 1;
  }
  d[2] = uVar4;
  return;
}


/* ==== frac_to_word @ 0045c890 ==== */

ulong __cdecl frac_to_word(ulong mode,void *node)

{
  uint uVar1;
  ulong extraout_EAX;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  float10 extraout_ST0;
  longlong lVar5;
  
  if ((mode & 0x80) != 0) {
    double_to_ieee_single(node);
    return extraout_EAX;
  }
  expr_mode = mode;
  uVar3 = *(uint *)((int)node + 0x1c);
  if ((uVar3 & 0x80000000) == 0) {
    if ((uVar3 & 0x40000000) == 0) {
      if ((uVar3 & 0x20000000) == 0) {
        if (((uVar3 & 0x10000000) == 0) && ((mode & 0x1000) == 0)) {
          if ((uVar3 & 0x8000000) == 0) {
            if ((uVar3 & 0x4000000) == 0) {
              if ((uVar3 & 0x2000000) == 0) {
                uVar3 = (-(uint)((mode & 0x10000000) != 0) & 0xff808000) + 0x7fffff;
              }
              else {
                uVar3 = 0x7fffffff;
              }
            }
            else {
              uVar3 = 0x7fffff;
            }
          }
          else {
            uVar3 = 0x7ffff;
          }
        }
        else {
          uVar3 = 0x7fff;
        }
      }
      else {
        uVar3 = 0x7ff;
      }
    }
    else {
      uVar3 = 0x7f;
    }
  }
  else {
    uVar3 = 7;
  }
  uVar1 = uVar3 + 1;
  uVar4 = uVar1 | uVar3;
  uVar2 = uVar1;
  if ((-1.0 < *(double *)node) && (uVar2 = uVar3, *(double *)node < 1.0)) {
    lVar5 = _ftol();
    uVar2 = (uint)lVar5;
    if (extraout_ST0 - (float10)(int)uVar2 == (float10)0.0) {
      uVar2 = uVar2 & 0xfffffffe;
    }
    if ((int)uVar3 < (int)uVar2) {
      uVar2 = uVar3;
    }
  }
  uVar2 = uVar2 & uVar4;
  *(uint *)((int)node + 8) = uVar2;
  if ((uVar2 & uVar1) != 0) {
    *(uint *)((int)node + 0x10) = (-(uint)((mode & 0x1000000) != 0) & 0xffffff10) + 0xff;
    *(uint *)((int)node + 0xc) = uVar4;
    return uVar4 & (uVar2 | ~uVar4);
  }
  *(undefined4 *)((int)node + 0x10) = 0;
  *(undefined4 *)((int)node + 0xc) = 0;
  return uVar4 & uVar2;
}


/* ==== dword_to_frac @ 0045ca20 ==== */

void __cdecl dword_to_frac(ulong mode,void *node)

{
  uint uVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  
  if ((mode & 0x80) != 0) {
    *(undefined4 *)((int)node + 4) = *(undefined4 *)((int)node + 0xc);
    *(undefined4 *)node = *(undefined4 *)((int)node + 8);
    return;
  }
  uVar3 = mode & 0x10000000;
  uVar7 = (-(uint)(uVar3 != 0) & 0xff010000) + 0x1000000;
  expr_mode = mode;
  uVar4 = (-(uint)(uVar3 != 0) & 0xff010000) + 0xffffff;
  if ((mode & 0x1000) == 0) {
    uVar3 = (-(uint)(uVar3 != 0) & 0xff808000) + 0x7fffff;
  }
  else {
    uVar3 = 0x7f;
  }
  uVar1 = uVar3 + 1;
  uVar6 = *(uint *)((int)node + 0xc);
  uVar5 = *(uint *)((int)node + 8);
  bVar8 = (uVar1 & uVar6) == 0;
  if (bVar8) {
    uVar6 = uVar6 & (uVar3 | uVar1);
  }
  else {
    uVar5 = (~uVar5 & uVar4) + 1;
    uVar6 = (~uVar6 & (uVar3 | uVar1)) + (uint)((uVar7 & uVar5) != 0);
  }
  dVar2 = (double)uVar6 / (double)uVar1 + (double)(uVar5 & uVar4) / ((double)uVar7 * (double)uVar1);
  if (!bVar8) {
    dVar2 = -dVar2;
  }
  *(double *)node = dVar2;
  return;
}


/* ==== long_to_frac @ 0045cb30 ==== */

void __cdecl long_to_frac(void *node)

{
  double dVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 local_18;
  
  if ((expr_mode & 0x80) != 0) {
    ext_to_double(node);
    return;
  }
  uVar9 = expr_mode & 0x10001000;
  uVar2 = -(uint)(uVar9 != 0) & 0xff010000;
  uVar3 = uVar2 + 0xffffff;
  uVar7 = uVar3 * 0x100 | uVar3;
  uVar8 = *(uint *)((int)node + 0x10);
  uVar5 = *(uint *)((int)node + 0xc);
  local_18 = *(uint *)((int)node + 8);
  uVar4 = uVar5;
  if ((expr_mode & 0x1000) != 0) {
    uVar4 = local_18 >> 0x10 | (uVar5 & 0xff) << 8;
    uVar8 = uVar5 >> 8;
    local_18 = local_18 & 0xffff;
  }
  uVar5 = expr_mode & 0x1000000;
  uVar6 = (-(uint)(uVar5 != 0) & 0xffffff88) + 0x80;
  if (uVar5 == 0) {
    dVar1 = -256.0;
  }
  else {
    dVar1 = -16.0;
  }
  if (((uVar8 != uVar6) || (uVar4 != 0)) || (local_18 != 0)) {
    uVar6 = uVar6 & uVar8;
    uVar4 = uVar4 | uVar8 << ((-(uVar9 != 0) & 0xf8U) + 0x18 & 0x1f);
    if (uVar6 == 0) {
      local_18 = local_18 & uVar3;
    }
    else {
      if (uVar5 != 0) {
        uVar4 = uVar4 | 0xf00000;
      }
      if (local_18 == 0) {
        uVar4 = (~uVar4 & uVar7) + 1;
      }
      else {
        local_18 = (~local_18 & uVar3) + 1;
        uVar4 = ~uVar4 & uVar7;
      }
    }
    dVar1 = (double)(int)((-(uint)(uVar9 != 0) & 0xff808000) + 0x800000);
    dVar1 = (double)uVar4 / dVar1 + (double)local_18 / ((double)(uVar2 + 0x1000000) * dVar1);
    if (uVar6 != 0) {
      dVar1 = -dVar1;
    }
  }
  *(double *)node = dVar1;
  return;
}


/* ==== ext_to_double @ 0045ccc0 ==== */

void __cdecl ext_to_double(ulong *v)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = v[4];
  uVar2 = v[3];
  if ((uVar1 & 0x40000000) != 0) {
    uVar3 = uVar1 & 0x7f;
    if ((uVar1 & 0x400) != 0) {
      uVar3 = (uint)(byte)((byte)uVar3 | 0x80);
    }
    ieee_single_to_double(uVar3 << 0x17 | uVar1 & 0x80000000 | uVar2 >> 8 & 0x7fffff,v);
    return;
  }
  *v = uVar2 << 0x15 | v[2] >> 0xb;
  v[1] = uVar2 >> 0xb & 0xfffff | uVar1 & 0x80000000 | (uVar1 & 0x7ff) << 0x14;
  return;
}


/* ==== frac_to_dword @ 0045cd40 ==== */

void __cdecl frac_to_dword(ulong mode,void *node)

{
  double dVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  longlong lVar6;
  
  uVar2 = mode & 0x10001000;
  uVar4 = (-(uint)(uVar2 != 0) & 0xff010000) + 0xffffff;
  dVar1 = *(double *)node;
  if (dVar1 <= -1.0) {
    if ((mode & 0x1000) != 0) {
      *(undefined4 *)((int)node + 0xc) = 0x80;
      *(undefined4 *)((int)node + 8) = 0;
      return;
    }
    *(uint *)((int)node + 0xc) = (-(uint)(uVar2 != 0) & 0xff808000) + 0x800000;
    *(undefined4 *)((int)node + 8) = 0;
    return;
  }
  if (1.0 <= dVar1) {
    if ((mode & 0x1000) != 0) {
      *(undefined4 *)((int)node + 0xc) = 0x7f;
      *(undefined4 *)((int)node + 8) = 0xffffff;
      return;
    }
    *(uint *)((int)node + 0xc) = (-(uint)(uVar2 != 0) & 0xff808000) + 0x7fffff;
    *(uint *)((int)node + 8) = uVar4;
    return;
  }
  lVar6 = _ftol();
  uVar2 = (uint)lVar6;
  lVar6 = _ftol();
  uVar3 = (uint)lVar6 & uVar4;
  if (dVar1 < 0.0) {
    bVar5 = uVar3 == 0;
    if (bVar5 == 0) {
      uVar3 = ~uVar3 & uVar4;
    }
    else {
      uVar3 = 0;
    }
    uVar2 = ~uVar2 + (uint)bVar5;
  }
  if ((mode & 0x1000) != 0) {
    *(uint *)((int)node + 0xc) = uVar2 >> 8 & 0xff;
    *(uint *)((int)node + 8) = uVar3 & 0xffffff | (uVar2 & 0xff) << 0x10;
    return;
  }
  *(uint *)((int)node + 8) = uVar3;
  *(uint *)((int)node + 0xc) = uVar4 & uVar2;
  return;
}


/* ==== frac_to_long @ 0045ced0 ==== */

void __cdecl frac_to_long(void *node)

{
  double dVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  longlong lVar7;
  
  if ((expr_mode & 0x80) != 0) {
    double_to_ext(node);
    return;
  }
  uVar4 = (-(uint)((expr_mode & 0x10001000) != 0) & 0xff010000) + 0xffffff;
  dVar1 = *(double *)node;
  if ((expr_mode & 0x1000000) == 0) {
    dVar2 = 256.0;
  }
  else {
    dVar2 = 16.0;
  }
  uVar5 = -(uint)((expr_mode & 0x1000000) != 0) & 0xffffff88;
  if (dVar1 <= -dVar2) {
    if ((expr_mode & 0x1000) == 0) {
      *(uint *)((int)node + 0x10) = uVar5 + 0x80;
      *(undefined4 *)((int)node + 8) = 0;
      *(undefined4 *)((int)node + 0xc) = 0;
      return;
    }
    *(undefined4 *)((int)node + 0xc) = 0x8000;
    *(undefined4 *)((int)node + 0x10) = 0;
    *(undefined4 *)((int)node + 8) = 0;
    return;
  }
  if (dVar2 <= dVar1) {
    if ((expr_mode & 0x1000) == 0) {
      *(uint *)((int)node + 8) = uVar4;
      *(uint *)((int)node + 0x10) = uVar5 + 0x7f;
      *(uint *)((int)node + 0xc) = uVar4;
      return;
    }
    *(undefined4 *)((int)node + 0x10) = 0;
    *(undefined4 *)((int)node + 0xc) = 0xffff;
    *(undefined4 *)((int)node + 8) = 0xffffff;
    return;
  }
  lVar7 = _ftol();
  uVar5 = (uint)lVar7;
  lVar7 = _ftol();
  uVar3 = (uint)lVar7 & uVar4;
  if (dVar1 < 0.0) {
    bVar6 = uVar3 == 0;
    if (bVar6 == 0) {
      uVar3 = ~uVar3 & uVar4;
    }
    else {
      uVar3 = 0;
    }
    uVar5 = ~uVar5 + (uint)bVar6;
  }
  if ((expr_mode & 0x1000) == 0) {
    *(uint *)((int)node + 8) = uVar3;
    *(uint *)((int)node + 0xc) = uVar4 & uVar5;
    *(uint *)((int)node + 0x10) =
         (int)uVar5 >> ((~(byte)(expr_mode >> 0x18) & 0x10 | 0x20) >> 1) &
         (-(uint)((expr_mode & 0x1000000) != 0) & 0xffffff10) + 0xff;
    return;
  }
  *(uint *)((int)node + 0xc) = (int)uVar5 >> 8 & 0xffff;
  *(uint *)((int)node + 8) = (uVar5 & 0xff) << 0x10 | uVar3;
  *(undefined4 *)((int)node + 0x10) = 0;
  return;
}


/* ==== double_to_ext @ 0045d0c0 ==== */

void __cdecl double_to_ext(ulong *v)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = v[1];
  v[2] = 0;
  uVar3 = uVar1 >> 0x14 & 0x7ff;
  uVar2 = uVar1 & 0x80000000 | uVar3;
  v[3] = (uVar1 & 0xfffff) << 0xb | *v >> 0x15;
  v[4] = uVar2;
  if (uVar3 == 0) {
    if (v[3] != 0) {
      v[4] = uVar2 | 0x20000000;
      return;
    }
  }
  else {
    v[3] = v[3] | 0x80000000;
  }
  return;
}


