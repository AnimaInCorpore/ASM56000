/* ==== parm_match_port @ 00466950 ==== */

int __cdecl parm_match_port(int idx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_10;
  char *local_8;
  
  iVar1 = *(int *)(cur_dtype + 0x44);
  local_8 = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
  if ((((*local_8 == 'p') && (local_8[1] == 'o')) && (local_8[2] == 'r')) &&
     ((local_8[3] == 't' && (local_8[4] == ':')))) {
    local_8 = local_8 + 5;
  }
  local_10 = 0;
  iVar2 = *(int *)(cur_dtype + 0x40);
  while ((local_10 < iVar2 &&
         (iVar3 = strcmp(*(char **)(iVar1 + local_10 * 0x14),local_8), iVar3 != 0))) {
    local_10 = local_10 + 1;
  }
  if (local_10 != iVar2) {
    *(int *)(parm_ctx + 0x488 + idx * 0x28) = local_10;
    *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = *(undefined2 *)(cur_dev + 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x55;
  }
  return (uint)(local_10 != iVar2);
}


/* ==== parm_match_periph_reg @ 00466a5c ==== */

int __cdecl parm_match_periph_reg(int idx)

{
  int iVar1;
  int iVar2;
  int local_c;
  
  iVar1 = *(int *)(cur_dtype + 0x20);
  iVar2 = parm_need_more(idx);
  if (iVar2 != -1) {
    for (local_c = 0; local_c < *(int *)(cur_dtype + 0x1c); local_c = local_c + 1) {
      iVar2 = str_icmp_ascii((char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4)),
                             *(char **)(iVar1 + local_c * 0x2c));
      if (iVar2 == 0) {
        *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = (undefined2)local_c;
        *(undefined1 *)(parm_ctx + idx + 0x200) = 0x7c;
        return 1;
      }
    }
    parm_errmsg = PTR_s_Invalid_parameter_004d344c;
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  }
  return 0;
}


/* ==== parm_match_space_sym @ 00466b2b ==== */

int __cdecl parm_match_space_sym(int idx,int dev)

{
  char *s;
  int *piVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *node;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int local_28;
  ulong local_24;
  
  piVar1 = *(int **)(dev_tab + dev * 4);
  if (piVar1 == (int *)0x0) {
    local_28 = 0;
  }
  else {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    iVar6 = parm_need_more(idx);
    uVar5 = cur_dev;
    uVar4 = cur_itype;
    uVar3 = cur_dtype;
    uVar2 = cur_sim;
    if (iVar6 == -1) {
      local_28 = 0;
      cur_sim = uVar2;
      cur_dtype = uVar3;
      cur_itype = uVar4;
      cur_dev = (int *)uVar5;
    }
    else {
      cur_dtype = *(int *)(chiptype_tab + *piVar1 * 4);
      cur_itype = *(undefined4 *)(itype_tab + *piVar1 * 4);
      cur_sim = *(undefined4 *)(dev_state_tab + dev * 4);
      local_28 = 0;
      cur_dev = piVar1;
      iVar6 = parse_line_spec(idx);
      if (iVar6 == 0) {
        s = (char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4));
        optr = s;
        uVar7 = strlen(s);
        if (*(int *)(cur_dtype + 0x4e8) == 0) {
          local_24 = *(ulong *)(cur_dtype + 0xc);
        }
        else {
          local_24 = (**(code **)(cur_dtype + 0x4e8))();
        }
        eval_expr(local_24);
        if (node != (undefined4 *)0x0) {
          if (((node[7] & 0x4000) != 0) && (optr == s + uVar7)) {
            node[2] = node[5];
            puVar8 = node;
            puVar9 = (undefined4 *)(parm_ctx + 0x480 + idx * 0x28);
            for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar9 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar9 = puVar9 + 1;
            }
            *(undefined1 *)(parm_ctx + idx + 0x200) = 0x70;
            *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = (undefined2)dev;
            local_28 = 1;
          }
          node_free(node);
        }
        cur_sim = uVar2;
        cur_dtype = uVar3;
        cur_itype = uVar4;
        cur_dev = (int *)uVar5;
        if (local_28 == 0) {
          *(int *)(parm_ctx + 0x1884) = (int)optr - (parm_ctx + 0x100);
        }
      }
      else {
        *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = (undefined2)dev;
        local_28 = 1;
        cur_sim = uVar2;
        cur_dtype = uVar3;
        cur_itype = uVar4;
        cur_dev = (int *)uVar5;
      }
    }
  }
  return local_28;
}


/* ==== parm_match_space_cur @ 00466d71 ==== */

int __cdecl parm_match_space_cur(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_space_sym(idx,*(int *)(cur_dev + 4));
  return iVar1;
}


/* ==== parm_match_space_any @ 00466d8b ==== */

int __cdecl parm_match_space_any(int idx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *local_c;
  
  iVar1 = parm_match_space_cur(idx);
  if (iVar1 == 0) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
    iVar3 = parm_ctx + iVar1;
    local_c = (char *)(iVar3 + 2);
    if (((*local_c == ':') || (local_c = (char *)(iVar3 + 3), *local_c == ':')) ||
       (local_c = (char *)(iVar3 + 4), *local_c == ':')) {
      *local_c = '\0';
      iVar2 = parm_device_name(idx);
      if (iVar2 == 0) {
        *local_c = ':';
        iVar1 = 0;
      }
      else {
        iVar2 = *(int *)(parm_ctx + 0x488 + idx * 0x28);
        *local_c = ':';
        *(char **)(parm_ctx + 0x280 + idx * 4) = local_c + ((iVar1 + 1) - iVar3);
        iVar3 = parm_match_space_sym(idx,iVar2);
        if (iVar3 == 0) {
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          iVar1 = 0;
        }
        else {
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          iVar1 = 1;
        }
      }
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}


/* ==== parm_kw_A @ 00466ed6 ==== */

int __cdecl parm_kw_A(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3458,0x41,8);
  return (uint)(iVar1 != -1);
}


/* ==== parm_match_c_test @ 00466efa ==== */

int __cdecl parm_match_c_test(int idx)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_8;
  
  local_8 = 0;
  iVar2 = *(int *)(parm_ctx + 0x280 + idx * 4);
  uVar3 = strlen((char *)(parm_ctx + iVar2));
  iVar1 = iVar2 + -1 + uVar3;
  if (((*(char *)(parm_ctx + iVar2) == 't') && (*(char *)(parm_ctx + iVar2 + 1) == '(')) &&
     (*(char *)(parm_ctx + iVar1) == ')')) {
    *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2 + 2;
    *(undefined1 *)(parm_ctx + iVar1) = 0;
    *(undefined1 *)(parm_ctx + iVar1 + 0x100) = 0;
    iVar4 = parm_match_condition(idx);
    if (iVar4 == 0) {
      iVar4 = parm_brace_block(idx);
      if (iVar4 == 0) {
        *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
        *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
      }
      else {
        iVar4 = parm_bp_expr(idx);
        if (iVar4 != 0) {
          *(undefined1 *)(parm_ctx + idx + 0x200) = 0x44;
        }
        local_8 = (uint)(iVar4 != 0);
      }
    }
    else {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x61;
      local_8 = 1;
    }
    *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2;
    *(undefined1 *)(parm_ctx + iVar1) = 0x29;
    *(undefined1 *)(parm_ctx + iVar1 + 0x100) = 0x29;
  }
  return local_8;
}


/* ==== parm_match_condition @ 0046706c ==== */

int __cdecl parm_match_condition(int idx)

{
  char cVar1;
  char cVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  undefined2 uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined2 local_30;
  char local_28;
  uint local_1c;
  char *local_10;
  undefined2 local_c;
  char *local_8;
  
  local_30 = 0;
  uVar6 = local_30;
  local_30 = 0;
  uVar3 = 0;
  uVar4 = 0;
  local_1c = 0xffffffff;
  iVar10 = *(int *)(parm_ctx + 0x280 + idx * 4);
  uVar5 = *(undefined4 *)(cur_dev + 4);
  iVar11 = *(int *)(cur_sim + 0x30);
  pcVar8 = (char *)(parm_ctx + iVar10);
  for (local_10 = pcVar8;
      (((cVar1 = *local_10, cVar1 != '\0' && (cVar1 != '!')) && (cVar1 != '<')) &&
      ((cVar1 != '>' && (cVar1 != '=')))); local_10 = local_10 + 1) {
  }
  local_8 = pcVar8;
  if (cVar1 != '\0') {
    *local_10 = '\0';
    iVar9 = parm_reg_is_pcvalue(idx);
    if (iVar9 == 0) {
      local_1c = 0xffffffff;
      local_30 = uVar6;
    }
    else {
      uVar3 = *(undefined2 *)(parm_ctx + 0x4a0 + idx * 0x28);
      uVar4 = *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28);
      local_1c = 0xffffffff;
      cVar2 = local_10[1];
      switch(cVar1) {
      case '!':
        if (cVar2 == '=') {
          local_1c = 0;
        }
        break;
      case '<':
        local_1c = (cVar2 != '=') + 1;
        break;
      case '=':
        local_1c = (cVar2 != '=') + 5;
        break;
      case '>':
        local_1c = (cVar2 != '=') + 3;
      }
      local_30 = (undefined2)local_1c;
      if (local_1c < 6) {
        iVar10 = (**(code **)(&DAT_00467563 + local_1c * 4))();
        return iVar10;
      }
      local_8 = local_10 + 1;
    }
    *local_10 = cVar1;
  }
  pcVar7 = local_8;
  *(char **)(parm_ctx + 0x280 + idx * 4) = local_8 + (iVar10 - (int)pcVar8);
  iVar9 = parm_register(idx);
  if (iVar9 != 0) {
    local_1c = 0xffffffff;
  }
  if (local_1c != 0xffffffff) {
    local_c = (undefined2)uVar5;
    if ((*local_8 == '$') || (iVar11 == 3)) {
      if (*local_8 == '$') {
        local_8 = local_8 + 1;
      }
      local_28 = '\0';
      for (; ((cVar1 = *local_8, '`' < cVar1 && (cVar1 < 'g')) || (('/' < cVar1 && (cVar1 < ':'))));
          local_8 = local_8 + 1) {
        local_28 = local_28 + '\x01';
      }
      if ((('\0' < local_28) && (*local_8 == '\0')) && (iVar9 = parm_integer_expr(idx), iVar9 != 0))
      {
        *(int *)(parm_ctx + 0x280 + idx * 4) = iVar10;
        *(undefined1 *)(parm_ctx + idx + 0x200) = 0x59;
        *(undefined2 *)(parm_ctx + 0x4a0 + idx * 0x28) = uVar3;
        *(undefined2 *)(parm_ctx + 0x4a2 + idx * 0x28) = local_30;
        *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = uVar4;
        *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = local_c;
        return 1;
      }
    }
    if (((iVar11 == 1) || (iVar11 == 2)) || ((iVar11 == 4 || (*pcVar7 == '`')))) {
      local_8 = pcVar7;
      if (*pcVar7 == '`') {
        local_8 = pcVar7 + 1;
      }
      local_28 = '\0';
      for (; ('/' < *local_8 && (*local_8 < ':')); local_8 = local_8 + 1) {
        local_28 = local_28 + '\x01';
      }
      if ((('\0' < local_28) && (*local_8 == '\0')) &&
         (iVar11 = parm_integer_expr(idx), iVar11 != 0)) {
        *(int *)(parm_ctx + 0x280 + idx * 4) = iVar10;
        *(undefined1 *)(parm_ctx + idx + 0x200) = 0x59;
        *(undefined2 *)(parm_ctx + 0x4a0 + idx * 0x28) = uVar3;
        *(undefined2 *)(parm_ctx + 0x4a2 + idx * 0x28) = local_30;
        *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = uVar4;
        *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = local_c;
        return 1;
      }
    }
  }
  *(int *)(parm_ctx + 0x280 + idx * 4) = iVar10;
  iVar10 = parm_match_space_cur(idx);
  if ((iVar10 == 0) ||
     ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x18 +
                (uint)*(ushort *)(parm_ctx + 0x4a4 + idx * 0x28) * 0x2c) & 0x1000) == 0)) {
    iVar10 = parm_float_expr(idx);
  }
  else {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x45;
    iVar10 = 1;
  }
  return iVar10;
}


/* ==== parm_reg_is_pcvalue @ 0046757b ==== */

int __cdecl parm_reg_is_pcvalue(int idx)

{
  uint uVar1;
  int iVar2;
  uint local_8;
  
  iVar2 = parm_register(idx);
  if (iVar2 != 0) {
    uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c +
                                       (uint)*(ushort *)(parm_ctx + 0x4a4 + idx * 0x28) * 0x48) +
                              0x2c) + 0x10 + (uint)*(ushort *)(parm_ctx + 0x4a0 + idx * 0x28) * 0x1c
                     );
    if (*(int *)(cur_dtype + 0x4e8) == 0) {
      local_8 = *(uint *)(cur_dtype + 0xc);
    }
    else {
      local_8 = (**(code **)(cur_dtype + 0x4e8))();
    }
    if (((uVar1 & 7) == 1) && (((local_8 & 0x2000000) != 0 || ((uVar1 & 0x2000000) == 0)))) {
      return 1;
    }
  }
  return 0;
}


/* ==== parm_kw_M_rw @ 00467652 ==== */

int __cdecl parm_kw_M_rw(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3478,0x4d,3);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_N_drw @ 00467676 ==== */

int __cdecl parm_kw_N_drw(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3488,0x4e,3);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_H_cmp @ 0046769a ==== */

int __cdecl parm_kw_H_cmp(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3498,0x48,4);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_O_logic @ 004676be ==== */

int __cdecl parm_kw_O_logic(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d34a8,0x4f,3);
  return (uint)(iVar1 != -1);
}


/* ==== parm_break_number @ 004676e2 ==== */

int __cdecl parm_break_number(int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = parm_need_more(idx);
  if (iVar1 != 0) {
    iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
    if (*(char *)(parm_ctx + iVar1) == '#') {
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1 + 1;
      iVar2 = parm_number(idx,0xffffffff);
      if (iVar2 != 0) {
        iVar2 = *(int *)(parm_ctx + 0x488 + idx * 0x28);
        if (0 < iVar2) {
          *(int *)(parm_ctx + 0x48c + idx * 0x28) = iVar2;
          *(undefined1 *)(parm_ctx + idx + 0x200) = 0x23;
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          return 1;
        }
        parm_errmsg = PTR_s_Range_of_Break_Number_is_1_99_004d3454;
        *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
      }
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
    }
    else {
      parm_errmsg = PTR_s_Invalid_parameter_004d344c;
      *(int *)(parm_ctx + 0x1884) = iVar1;
    }
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  return 0;
}


/* ==== parm_kw_cond_code @ 00467816 ==== */

int __cdecl parm_kw_cond_code(int idx)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint local_10;
  
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_10 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    local_10 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((((local_10 & 0x10000000) == 0) || ((local_10 & 0x4000000) != 0)) ||
     ((local_10 & 0x1000000) != 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    iVar2 = parm_match_keyword(idx,&PTR_DAT_004d3630,0x62,0x11);
    uVar3 = (uint)(iVar2 != -1);
  }
  else if ((local_10 & 0x1000000) == 0) {
    if ((local_10 & 0x80) == 0) {
      iVar2 = parm_match_keyword(idx,&PTR_DAT_004d35e8,0x62,0x11);
      uVar3 = (uint)(iVar2 != -1);
    }
    else {
      iVar2 = parm_match_keyword(idx,&PTR_DAT_004d3678,0x62,0x24);
      uVar3 = (uint)(iVar2 != -1);
    }
  }
  else {
    iVar2 = parm_match_keyword(idx,&PTR_DAT_004d3674,0x62,1);
    uVar3 = (uint)(iVar2 != -1);
  }
  return uVar3;
}


/* ==== parm_kw_bus_name @ 0046793e ==== */

int __cdecl parm_kw_bus_name(int idx)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint local_18;
  
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_18 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    local_18 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((((local_18 & 0x10000000) == 0) || ((local_18 & 0x4000000) != 0)) ||
     ((local_18 & 0x1000000) != 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (((local_18 & 0x10000000) == 0) || ((local_18 & 0x4000000) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar1) {
    iVar3 = parm_match_keyword(idx,&PTR_DAT_004d35a8,0x42,4);
    uVar4 = (uint)(iVar3 != -1);
  }
  else if ((local_18 & 0x1000000) == 0) {
    if ((local_18 & 0x80) == 0) {
      if ((local_18 & 0x200) == 0) {
        if (bVar2) {
          iVar3 = parm_match_keyword(idx,&PTR_DAT_004d3598,0x42,3);
          uVar4 = (uint)(iVar3 != -1);
        }
        else {
          iVar3 = parm_match_keyword(idx,&PTR_DAT_004d3568,0x42,7);
          uVar4 = (uint)(iVar3 != -1);
        }
      }
      else {
        iVar3 = parm_match_keyword(idx,&PTR_DAT_004d3588,0x42,4);
        uVar4 = (uint)(iVar3 != -1);
      }
    }
    else {
      iVar3 = parm_match_keyword(idx,&PTR_DAT_004d35c8,0x42,8);
      uVar4 = (uint)(iVar3 != -1);
    }
  }
  else {
    iVar3 = parm_match_keyword(idx,&PTR_DAT_004d35b8,0x42,3);
    uVar4 = (uint)(iVar3 != -1);
  }
  return uVar4;
}


/* ==== parm_break_number_list @ 00467afb ==== */

int __cdecl parm_break_number_list(int idx)

{
  bool bVar1;
  int iVar2;
  int local_18;
  char *local_14;
  int local_10;
  long local_c;
  char *local_8;
  
  iVar2 = parm_need_more(idx);
  if (iVar2 != 0) {
    local_10 = *(int *)(parm_ctx + 0x280 + idx * 4);
    bVar1 = false;
    if (*(char *)(parm_ctx + local_10) == '#') {
      local_8 = (char *)(parm_ctx + 1 + local_10);
      local_18 = idx;
      while (local_c = strtol(local_8,&local_14,10), local_8 != local_14) {
        *(undefined1 *)(parm_ctx + local_18 + 0x200) = 0x23;
        if (bVar1) {
          *(long *)(parm_ctx + 0x48c + local_18 * 0x28) = local_c;
        }
        else {
          *(long *)(parm_ctx + 0x488 + local_18 * 0x28) = local_c;
          *(long *)(parm_ctx + 0x48c + local_18 * 0x28) = local_c;
        }
        if (*local_14 == ',') {
          bVar1 = false;
          local_14 = local_14 + 1;
        }
        else {
          if (((bVar1) || (*local_14 != '.')) || (local_14[1] != '.')) {
            if (*local_14 == '\0') {
              *(undefined1 *)(parm_ctx + local_18 + 0x201) = 0x65;
              return 1;
            }
            break;
          }
          bVar1 = true;
          local_14 = local_14 + 2;
          local_18 = local_18 + -1;
        }
        local_8 = local_14;
        local_18 = local_18 + 1;
      }
    }
    parm_errmsg = PTR_s_Invalid_parameter_004d344c;
    *(int *)(parm_ctx + 0x1884) = local_10;
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  return 0;
}


/* ==== parm_colon_number @ 00467c98 ==== */

int __cdecl parm_colon_number(int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
  iVar2 = parm_need_more(idx);
  if ((iVar2 != 0) && (*(char *)(parm_ctx + iVar1) == ':')) {
    *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1 + 1;
    iVar2 = parm_integer_expr(idx);
    if ((iVar2 != 0) && (*(int *)(parm_ctx + 0x488 + idx * 0x28) != 0)) {
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x3a;
      return 1;
    }
  }
  parm_errmsg = PTR_s_Invalid_parameter_004d344c;
  *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  return 0;
}


/* ==== parm_c_expr @ 00467d69 ==== */

int __cdecl parm_c_expr(int idx)

{
  int iVar1;
  
  iVar1 = parm_c_expr_check(idx,0);
  return iVar1;
}


/* ==== parm_c_expr_check @ 00467d7c ==== */

int __cdecl parm_c_expr_check(int idx,int forbid_calls)

{
  char *text;
  int iVar1;
  void *tree;
  int iVar2;
  int local_10;
  
  local_10 = 0;
  iVar1 = parm_need_more(idx);
  if (iVar1 != 0) {
    text = (char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4));
    parse_c_expression(text);
    if (tree == (void *)0x0) {
      local_10 = 0;
    }
    else {
      if (forbid_calls == 0) {
        local_10 = 1;
      }
      else {
        iVar1 = cdb_expr_has_call(tree);
        local_10 = (-(uint)(iVar1 != 0) & 0xfffffffe) + 1;
      }
      cdb_free_expr(tree);
    }
    if (local_10 == 0) {
      iVar2 = parm_ctx + 0x100;
      iVar1 = lex_get_column();
      *(char **)(parm_ctx + 0x1884) = text + (iVar1 - iVar2);
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    }
    else {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x43;
    }
  }
  return local_10;
}


/* ==== parm_bp_expr @ 00467e61 ==== */

int __cdecl parm_bp_expr(int idx)

{
  int iVar1;
  
  iVar1 = parm_c_expr_check(idx,1);
  if (iVar1 == -1) {
    cdb_error(s_breakpoint_expressions_cannot_co_004d3a70);
    iVar1 = 0;
  }
  else if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}


/* ==== parm_type_expr @ 00467ea0 ==== */

int __cdecl parm_type_expr(int idx)

{
  int iVar1;
  
  iVar1 = parm_c_expr_check(idx,1);
  if (iVar1 == -1) {
    cdb_error(s_type_expressions_cannot_contain_f_004d3aa8);
    iVar1 = 0;
  }
  else if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}


/* ==== parm_watch_expr @ 00467edf ==== */

int __cdecl parm_watch_expr(int idx)

{
  int iVar1;
  
  iVar1 = parm_c_expr_check(idx,1);
  if (iVar1 == -1) {
    cdb_error(s_watch_expressions_cannot_contain_004d3ad8);
    iVar1 = 0;
  }
  else if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}


/* ==== parm_brace_block @ 00467f1e ==== */

int __cdecl parm_brace_block(int idx)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = parm_need_more(idx);
  if ((iVar1 != 0) && (*(char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4)) == '{')) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x43;
    local_8 = 1;
  }
  if (local_8 == 0) {
    *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  }
  return local_8;
}


/* ==== parm_command_name @ 00467fa9 ==== */

int __cdecl parm_command_name(int idx)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  uint n;
  uint uVar4;
  char *a;
  int local_14;
  int *local_c;
  
  puVar2 = command_table;
  iVar1 = num_commands;
  a = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
  local_14 = 0;
  local_c = (int *)command_table;
  while ((local_14 < iVar1 && (iVar3 = strcmp(a,*(char **)*local_c), iVar3 != 0))) {
    local_c = local_c + 1;
    local_14 = local_14 + 1;
  }
  if (local_14 == iVar1) {
    local_14 = 0;
    local_c = (int *)puVar2;
    while ((local_14 < iVar1 && (iVar3 = strcmp(a,*(char **)(*local_c + 4)), iVar3 != 0))) {
      local_c = local_c + 1;
      local_14 = local_14 + 1;
    }
  }
  if (local_14 == iVar1) {
    local_14 = 0;
    local_c = (int *)puVar2;
    n = strlen(a);
    while ((local_14 < iVar1 &&
           ((iVar3 = strncmp(a,*(char **)*local_c,n), iVar3 != 0 ||
            (uVar4 = strlen(*(char **)(*local_c + 4)), n < uVar4))))) {
      local_c = local_c + 1;
      local_14 = local_14 + 1;
    }
  }
  if (local_14 != iVar1) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 99;
    *(int *)(parm_ctx + 0x488 + idx * 0x28) = local_14;
  }
  return (uint)(local_14 != iVar1);
}


/* ==== parm_device_name @ 00468115 ==== */

int __cdecl parm_device_name(int idx)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *local_8;
  
  iVar3 = *(int *)(parm_ctx + 0x280 + idx * 4);
  iVar2 = parm_need_more(idx);
  if ((((iVar2 != 0) && (local_8 = (char *)(parm_ctx + iVar3), *local_8 == 'd')) &&
      (local_8[1] == 'v')) && (local_8 = local_8 + 2, *local_8 != '\0')) {
    iVar3 = atoi(local_8);
    do {
      cVar1 = *local_8;
      local_8 = local_8 + 1;
      if (cVar1 == '\0') {
        if ((-1 < iVar3) && (iVar3 < max_devices)) {
          *(undefined1 *)(parm_ctx + idx + 0x200) = 0x6e;
          *(int *)(parm_ctx + 0x488 + idx * 0x28) = iVar3;
          return 1;
        }
        return 0;
      }
    } while (('/' < cVar1) && (cVar1 < ':'));
  }
  return 0;
}


/* ==== parm_device_type @ 00468218 ==== */

int __cdecl parm_device_type(int idx)

{
  int iVar1;
  int iVar2;
  char *b;
  int local_c;
  
  iVar1 = num_chiptypes;
  b = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
  local_c = 0;
  while ((local_c < iVar1 &&
         ((*(int *)(chiptype_tab + local_c * 4) == 0 ||
          (iVar2 = strcmp((char *)**(undefined4 **)(chiptype_tab + local_c * 4),b), iVar2 != 0)))))
  {
    local_c = local_c + 1;
  }
  if (local_c != iVar1) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x74;
    *(int *)(parm_ctx + 0x488 + idx * 0x28) = local_c;
  }
  return (uint)(local_c != iVar1);
}


/* ==== parm_kw_d_onoff @ 004682c6 ==== */

int __cdecl parm_kw_d_onoff(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d34f8,100,5);
  return (uint)(iVar1 != -1);
}


/* ==== parm_check_too_many @ 004682ea ==== */

int __cdecl parm_check_too_many(int idx)

{
  int iVar1;
  
  iVar1 = *(int *)(parm_ctx + 0x280);
  if (iVar1 < idx) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x65;
  }
  else {
    parm_errmsg = PTR_s_Too_many_parameters_004d3450;
    *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
  }
  return (uint)(iVar1 < idx);
}


/* ==== parm_kw_r_radix @ 0046833d ==== */

int __cdecl parm_kw_r_radix(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d34b8,0x72,5);
  return (uint)(iVar1 != -1);
}


/* ==== parm_number_expr @ 00468361 ==== */

int __cdecl parm_number_expr(int idx)

{
  char *s;
  int iVar1;
  uint uVar2;
  undefined4 *node;
  undefined4 *puVar3;
  undefined4 *puVar4;
  ulong local_10;
  
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_10 = *(ulong *)(cur_dtype + 0xc);
  }
  else {
    local_10 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar1 = parm_need_more(idx);
  if (iVar1 != 0) {
    s = (char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4));
    optr = s;
    uVar2 = strlen(s);
    eval_expr(local_10);
    if (node != (undefined4 *)0x0) {
      if ((node[7] & 0x200) == 0) {
        node_get_double(local_10,node);
        *(undefined1 *)(parm_ctx + idx + 0x200) = 0x49;
        puVar3 = node;
        puVar4 = (undefined4 *)(parm_ctx + 0x480 + idx * 0x28);
        for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar4 = puVar4 + 1;
        }
      }
      else {
        *(undefined1 *)(parm_ctx + idx + 0x200) = 0x46;
        node_from_double(local_10,node);
        puVar3 = node;
        puVar4 = (undefined4 *)(parm_ctx + 0x480 + idx * 0x28);
        for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar4 = puVar4 + 1;
        }
      }
      node_free(node);
      if (optr == s + uVar2) {
        return 1;
      }
    }
    *(int *)(parm_ctx + 0x1884) = (int)optr - (parm_ctx + 0x100);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  }
  return 0;
}


/* ==== parm_number_addr @ 004684ed ==== */

int __cdecl parm_number_addr(int idx)

{
  int iVar1;
  undefined4 local_14;
  
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_14 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    local_14 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar1 = parm_number(idx,*(uint *)(*(int *)(cur_dtype + 0x20) + 0x10) &
                          (-(uint)((local_14 & 0x800) != 0) & 0x10000) - 1);
  return iVar1;
}


/* ==== parm_number_or_end @ 00468562 ==== */

int __cdecl parm_number_or_end(int idx)

{
  int iVar1;
  
  iVar1 = parm_need_more(idx);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = parm_integer_expr(idx);
  }
  return iVar1;
}


/* ==== parm_any_token @ 00468587 ==== */

int __cdecl parm_any_token(int idx)

{
  int iVar1;
  
  iVar1 = parm_need_more(idx);
  if (iVar1 != 0) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x4e;
  }
  return (uint)(iVar1 != 0);
}


/* ==== parm_need_more @ 004685b5 ==== */

int __cdecl parm_need_more(int idx)

{
  int iVar1;
  
  iVar1 = *(int *)(parm_ctx + 0x280);
  if (idx <= iVar1) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x4b;
  }
  else {
    parm_errmsg = PTR_s_Need_more_parameters_004d3448;
    *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x284 + iVar1 * 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  }
  return (uint)(idx <= iVar1);
}


/* ==== parm_frame_number @ 00468620 ==== */

int __cdecl parm_frame_number(int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = parm_need_more(idx);
  if (iVar1 != 0) {
    iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
    if (*(char *)(parm_ctx + iVar1) == '#') {
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1 + 1;
      iVar2 = parm_number(idx,0xffff);
      if (iVar2 != 0) {
        iVar2 = *(int *)(parm_ctx + 0x488 + idx * 0x28);
        if (-1 < iVar2) {
          *(int *)(parm_ctx + 0x48c + idx * 0x28) = iVar2;
          *(undefined1 *)(parm_ctx + idx + 0x200) = 0x66;
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          return 1;
        }
        parm_errmsg = s_Frame_number_must_be_positive_004d3b08;
        *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
      }
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
    }
    else {
      parm_errmsg = PTR_s_Invalid_parameter_004d344c;
      *(int *)(parm_ctx + 0x1884) = iVar1;
    }
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  return 0;
}


/* ==== parm_mem_or_reg_x @ 00468758 ==== */

int __cdecl parm_mem_or_reg_x(int idx)

{
  int iVar1;
  
  iVar1 = parm_address_spec(idx);
  if ((((iVar1 == 0) && (iVar1 = parm_memspace_name(idx), iVar1 == 0)) &&
      (iVar1 = parm_match_port(idx), iVar1 == 0)) &&
     ((iVar1 = parm_port_range(idx), iVar1 == 0 && (iVar1 = parm_reg_flag_x(idx), iVar1 == 0)))) {
    return 0;
  }
  return 1;
}


/* ==== parm_reg_flag_x @ 004687c3 ==== */

int __cdecl parm_reg_flag_x(int idx)

{
  int iVar1;
  
  iVar1 = parm_reg_flag(idx,0x800);
  return iVar1;
}


/* ==== parm_reg_flag @ 004687d9 ==== */

int __cdecl parm_reg_flag(int idx,ulong flag)

{
  int iVar1;
  
  iVar1 = parm_register(idx);
  if (iVar1 != 0) {
    if ((*(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c +
                                    (uint)*(ushort *)(parm_ctx + 0x4a4 + idx * 0x28) * 0x48) + 0x2c)
                   + 0x10 + (uint)*(ushort *)(parm_ctx + 0x4a0 + idx * 0x28) * 0x1c) & flag) != 0) {
      return 1;
    }
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x55;
  }
  return 0;
}


/* ==== parm_mem_or_reg_y @ 00468877 ==== */

int __cdecl parm_mem_or_reg_y(int idx)

{
  int iVar1;
  
  iVar1 = parm_address_spec(idx);
  if ((((iVar1 == 0) && (iVar1 = parm_memspace_name(idx), iVar1 == 0)) &&
      (iVar1 = parm_match_port(idx), iVar1 == 0)) &&
     ((iVar1 = parm_port_range(idx), iVar1 == 0 && (iVar1 = parm_reg_flag_y(idx), iVar1 == 0)))) {
    return 0;
  }
  return 1;
}


/* ==== parm_reg_flag_y @ 004688e2 ==== */

int __cdecl parm_reg_flag_y(int idx)

{
  int iVar1;
  
  iVar1 = parm_reg_flag(idx,0x1000);
  return iVar1;
}


/* ==== parm_integer_expr @ 004688f8 ==== */

int __cdecl parm_integer_expr(int idx)

{
  char *s;
  uint uVar1;
  undefined4 *node;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  ulong local_10;
  
  s = (char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4));
  optr = s;
  uVar1 = strlen(s);
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_10 = *(ulong *)(cur_dtype + 0xc);
  }
  else {
    local_10 = (**(code **)(cur_dtype + 0x4e8))();
  }
  eval_expr(local_10);
  if (node != (undefined4 *)0x0) {
    if ((((node[7] & 0x100) != 0) && (s + uVar1 == optr)) && ((node[7] & 0x2000) == 0)) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x49;
      puVar3 = node;
      puVar4 = (undefined4 *)(parm_ctx + 0x480 + idx * 0x28);
      for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      node_free(node);
      return 1;
    }
    node_free(node);
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  *(int *)(parm_ctx + 0x1884) = (int)optr - (parm_ctx + 0x100);
  return 0;
}


/* ==== parm_float_expr @ 00468a2f ==== */

int __cdecl parm_float_expr(int idx)

{
  char *s;
  uint uVar1;
  undefined4 *node;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  ulong local_10;
  
  s = (char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4));
  optr = s;
  uVar1 = strlen(s);
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_10 = *(ulong *)(cur_dtype + 0xc);
  }
  else {
    local_10 = (**(code **)(cur_dtype + 0x4e8))();
  }
  eval_expr(local_10);
  if (node != (undefined4 *)0x0) {
    if (((node[7] & 0x2000) != 0) && (s + uVar1 == optr)) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x49;
      puVar3 = node;
      puVar4 = (undefined4 *)(parm_ctx + 0x480 + idx * 0x28);
      for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      node_free(node);
      return 1;
    }
    node_free(node);
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  *(int *)(parm_ctx + 0x1884) = (int)optr - (parm_ctx + 0x100);
  return 0;
}


/* ==== parm_address_spec @ 00468b59 ==== */

int __cdecl parm_address_spec(int idx)

{
  undefined2 uVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  uint local_30;
  uint local_28;
  ushort local_24;
  uint local_1c;
  uint local_10;
  int local_8;
  
  local_28 = 0;
  local_10 = 0;
  local_24 = 0;
  uVar3 = local_24;
  local_24 = 0;
  uVar1 = 0;
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_1c = *(uint *)(cur_dtype + 0xc);
  }
  else {
    local_1c = (**(code **)(cur_dtype + 0x4e8))();
  }
  local_8 = 0;
  iVar2 = *(int *)(parm_ctx + 0x280 + idx * 4);
  iVar4 = parm_match_space_cur(idx);
  if (iVar4 == 0) {
    iVar4 = parm_need_more(idx);
    if (iVar4 != 0) {
      iVar4 = str_find_char((char *)(parm_ctx + iVar2),0x23);
      if (iVar4 == -1) {
        iVar4 = str_find_word((char *)(parm_ctx + iVar2),&DAT_004d3b28);
        if (iVar4 != -1) {
          *(undefined1 *)(parm_ctx + iVar2 + iVar4) = 0;
          *(undefined1 *)(parm_ctx + 0x100 + iVar2 + iVar4) = 0;
          iVar5 = parm_match_space_cur(idx);
          local_24 = uVar3;
          if (iVar5 != 0) {
            uVar1 = *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28);
            local_24 = *(ushort *)(parm_ctx + 0x4a4 + idx * 0x28);
            local_30 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x20 + (uint)local_24 * 0x2c);
            if ((local_1c & 0x800) != 0) {
              local_30 = local_30 & 0xffff;
            }
            local_10 = *(uint *)(parm_ctx + 0x488 + idx * 0x28) & local_30;
            *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2 + 2 + iVar4;
            iVar5 = parm_number_or_end(idx);
            if (iVar5 != 0) {
              local_8 = 1;
              local_28 = *(uint *)(parm_ctx + 0x488 + idx * 0x28);
              if ((local_1c & 0x10000000) == 0) {
                if ((local_1c & 0x4000000) != 0) {
                  local_28 = local_28 | *(int *)(parm_ctx + 0x48c + idx * 0x28) << 0x18;
                }
              }
              else {
                local_28 = local_28 | *(int *)(parm_ctx + 0x48c + idx * 0x28) << 0x10;
              }
              local_28 = local_28 & local_30;
              *(undefined1 *)(parm_ctx + idx + 0x200) = 0x50;
            }
          }
          *(undefined1 *)(parm_ctx + iVar2 + iVar4) = 0x2e;
          *(undefined1 *)(parm_ctx + 0x100 + iVar2 + iVar4) = 0x2e;
        }
      }
      else {
        *(undefined1 *)(parm_ctx + iVar2 + iVar4) = 0;
        *(undefined1 *)(parm_ctx + 0x100 + iVar2 + iVar4) = 0;
        iVar5 = parm_match_space_cur(idx);
        local_24 = uVar3;
        if (iVar5 != 0) {
          uVar1 = *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28);
          local_24 = *(ushort *)(parm_ctx + 0x4a4 + idx * 0x28);
          local_10 = *(uint *)(parm_ctx + 0x488 + idx * 0x28);
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2 + 1 + iVar4;
          iVar5 = parm_count_expr(idx);
          if (iVar5 != 0) {
            local_28 = (local_10 - 1) + *(int *)(parm_ctx + 0x488 + idx * 0x28);
            local_8 = 1;
            *(undefined1 *)(parm_ctx + idx + 0x200) = 0x58;
          }
        }
        *(undefined1 *)(parm_ctx + iVar2 + iVar4) = 0x23;
        *(undefined1 *)(parm_ctx + 0x100 + iVar2 + iVar4) = 0x23;
      }
    }
    *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2;
    if (local_8 == 0) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    }
    else {
      *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = uVar1;
      *(ushort *)(parm_ctx + 0x4a4 + idx * 0x28) = local_24;
      *(uint *)(parm_ctx + 0x488 + idx * 0x28) = local_10;
      *(uint *)(parm_ctx + 0x48c + idx * 0x28) = local_28;
    }
  }
  else {
    local_8 = 1;
  }
  return local_8;
}


/* ==== parm_kw_m_memmode @ 00468f5f ==== */

int __cdecl parm_kw_m_memmode(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d34d0,0x6d,9);
  return (uint)(iVar1 != -1);
}


/* ==== parm_filename @ 00468f83 ==== */

int __cdecl parm_filename(int idx)

{
  bool bVar1;
  char local_104 [256];
  
  strncpy(local_104,(char *)(*(int *)(parm_ctx + 0x1880) + *(int *)(parm_ctx + 0x280 + idx * 4)),
          0xff);
  *(undefined4 *)(cur_sim + 0xc) = *(undefined4 *)(parm_ctx + 0x4d8);
  (**(code **)(cur_itype + 0xc))(local_104,*(undefined4 *)(cur_sim + 0xc));
  bVar1 = -1 < asm_result;
  if (bVar1) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x6d;
  }
  else {
    *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  }
  return (uint)bVar1;
}


/* ==== parm_count_expr @ 0046903c ==== */

int __cdecl parm_count_expr(int idx)

{
  int iVar1;
  
  iVar1 = parm_need_more(idx);
  if ((iVar1 != 0) && (iVar1 = parm_integer_expr(idx), iVar1 != 0)) {
    if (0 < *(int *)(parm_ctx + 0x488 + idx * 0x28)) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x69;
      return 1;
    }
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    parm_errmsg = PTR_s_Invalid_parameter_004d344c;
    *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
  }
  return 0;
}


/* ==== parm_port_name @ 004690cf ==== */

int __cdecl parm_port_name(int idx,int dev)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_1c;
  char *local_8;
  
  if (*(int **)(dev_tab + dev * 4) == (int *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(chiptype_tab + **(int **)(dev_tab + dev * 4) * 4);
    iVar1 = *(int *)(iVar3 + 0x3c);
    iVar2 = *(int *)(iVar3 + 0x38);
    local_8 = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
    if ((((*local_8 == 'p') && (local_8[1] == 'i')) && (local_8[2] == 'n')) && (local_8[3] == ':'))
    {
      local_8 = local_8 + 4;
    }
    local_1c = 0;
    while ((local_1c < iVar2 &&
           ((((iVar4 = strcmp(*(char **)(iVar1 + local_1c * 0x18),local_8), iVar4 != 0 &&
              ((*(int *)(iVar1 + 4 + local_1c * 0x18) == 0 ||
               (iVar4 = strcmp(*(char **)(iVar1 + 4 + local_1c * 0x18),local_8), iVar4 != 0)))) &&
             ((*(int *)(iVar1 + 8 + local_1c * 0x18) == 0 ||
              (iVar4 = strcmp(*(char **)(iVar1 + 8 + local_1c * 0x18),local_8), iVar4 != 0)))) ||
            ((*(uint *)(iVar3 + 8) & *(uint *)(iVar1 + 0x14 + local_1c * 0x18)) == 0))))) {
      local_1c = local_1c + 1;
    }
    if (local_1c == iVar2) {
      iVar3 = 0;
    }
    else {
      *(int *)(parm_ctx + 0x488 + idx * 0x28) = local_1c;
      *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = (undefined2)dev;
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x73;
      iVar3 = 1;
    }
  }
  return iVar3;
}


/* ==== parm_port_name_dev @ 00469271 ==== */

int __cdecl parm_port_name_dev(int idx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *local_c;
  
  iVar1 = parm_port_name(idx,*(int *)(cur_dev + 4));
  if (iVar1 == 0) {
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
    iVar2 = parm_ctx + iVar1;
    local_c = (char *)(iVar2 + 2);
    if (((*local_c == ':') || (local_c = (char *)(iVar2 + 3), *local_c == ':')) ||
       (local_c = (char *)(iVar2 + 4), *local_c == ':')) {
      *local_c = '\0';
      iVar3 = parm_device_name(idx);
      if (iVar3 == 0) {
        *local_c = ':';
        iVar1 = 0;
      }
      else {
        iVar3 = *(int *)(parm_ctx + 0x488 + idx * 0x28);
        *local_c = ':';
        *(char **)(parm_ctx + 0x280 + idx * 4) = local_c + ((iVar1 + 1) - iVar2);
        iVar2 = parm_port_name(idx,iVar3);
        if (iVar2 == 0) {
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          iVar1 = 0;
        }
        else {
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          iVar1 = 1;
        }
      }
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}


/* ==== parm_port_range @ 004693bf ==== */

int __cdecl parm_port_range(int idx)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_8;
  
  local_8 = 0;
  iVar5 = *(int *)(cur_dev + 4);
  iVar2 = parm_port_name(idx,iVar5);
  if (iVar2 == 0) {
    iVar2 = parm_need_more(idx);
    if (iVar2 != 0) {
      iVar2 = *(int *)(parm_ctx + 0x280 + idx * 4);
      iVar3 = str_find_word((char *)(parm_ctx + iVar2),&DAT_004d3b2c);
      if (iVar3 != -1) {
        *(undefined1 *)(parm_ctx + iVar2 + iVar3) = 0;
        iVar4 = parm_port_name(idx,iVar5);
        if (iVar4 != 0) {
          uVar1 = *(undefined4 *)(parm_ctx + 0x488 + idx * 0x28);
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2 + 2 + iVar3;
          iVar5 = parm_port_name(idx,iVar5);
          if (iVar5 != 0) {
            *(undefined4 *)(parm_ctx + 0x48c + idx * 0x28) =
                 *(undefined4 *)(parm_ctx + 0x488 + idx * 0x28);
            *(undefined4 *)(parm_ctx + 0x488 + idx * 0x28) = uVar1;
            *(undefined1 *)(parm_ctx + idx + 0x200) = 0x53;
          }
          local_8 = (uint)(iVar5 != 0);
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar2;
        }
        *(undefined1 *)(parm_ctx + iVar2 + iVar3) = 0x2e;
      }
    }
    if (local_8 == 0) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    }
  }
  else {
    local_8 = 1;
  }
  return local_8;
}


/* ==== parm_periph_name @ 0046953e ==== */

int __cdecl parm_periph_name(int idx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_10;
  char *local_c;
  
  iVar1 = *(int *)(cur_dtype + 0x18);
  local_c = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
  if ((((*local_c == 'p') && (local_c[1] == 'e')) && (local_c[2] == 'r')) && (local_c[3] == ':')) {
    local_c = local_c + 4;
  }
  local_10 = 0;
  iVar2 = *(int *)(cur_dtype + 0x14);
  while ((local_10 < iVar2 &&
         (iVar3 = strcmp(*(char **)(iVar1 + local_10 * 0x48),local_c), iVar3 != 0))) {
    local_10 = local_10 + 1;
  }
  if (local_10 != iVar2) {
    *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = (undefined2)local_10;
    *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = *(undefined2 *)(cur_dev + 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x74;
  }
  return (uint)(local_10 != iVar2);
}


/* ==== parm_memspace_name @ 0046963f ==== */

int __cdecl parm_memspace_name(int idx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *b;
  int local_10;
  
  iVar1 = *(int *)(cur_dtype + 0x18);
  b = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
  local_10 = 0;
  iVar2 = *(int *)(cur_dtype + 0x14);
  while ((local_10 < iVar2 &&
         ((iVar3 = strcmp(*(char **)(iVar1 + local_10 * 0x48),b), iVar3 != 0 ||
          ((*(uint *)(*(int *)(iVar1 + 0x2c + local_10 * 0x48) + 0x20) & 4) == 0))))) {
    local_10 = local_10 + 1;
  }
  if (local_10 != iVar2) {
    *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = (undefined2)local_10;
    *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = *(undefined2 *)(cur_dev + 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x74;
  }
  return (uint)(local_10 != iVar2);
}


/* ==== parm_addr_or_expr @ 00469720 ==== */

int __cdecl parm_addr_or_expr(int idx)

{
  int iVar1;
  
  iVar1 = parm_register_range(idx);
  if ((iVar1 == 0) && (iVar1 = parm_address_spec(idx), iVar1 == 0)) {
    return 0;
  }
  return 1;
}


/* ==== parm_addr_list @ 0046975b ==== */

int __cdecl parm_addr_list(int idx)

{
  int iVar1;
  int iVar2;
  int local_c;
  
  iVar1 = *(int *)(parm_ctx + 0x280);
  local_c = idx;
  while( true ) {
    if (iVar1 < local_c) {
      return (uint)(idx <= iVar1);
    }
    iVar2 = parm_address_spec(local_c);
    if (((iVar2 == 0) && (iVar2 = parm_register_range(local_c), iVar2 == 0)) &&
       (iVar2 = parm_periph_or_group(local_c), iVar2 == 0)) break;
    local_c = local_c + 1;
  }
  return 0;
}


/* ==== parm_addr_list_simple @ 004697da ==== */

int __cdecl parm_addr_list_simple(int idx)

{
  int iVar1;
  int iVar2;
  int local_c;
  
  iVar1 = *(int *)(parm_ctx + 0x280);
  local_c = idx;
  while( true ) {
    if (iVar1 < local_c) {
      return (uint)(idx <= iVar1);
    }
    iVar2 = parm_address_spec(local_c);
    if ((iVar2 == 0) && (iVar2 = parm_register_range(local_c), iVar2 == 0)) break;
    local_c = local_c + 1;
  }
  return 0;
}


/* ==== parm_register @ 00469849 ==== */

int __cdecl parm_register(int idx)

{
  long lVar1;
  undefined2 local_10 [2];
  undefined2 local_c [2];
  char *local_8;
  
  local_8 = (char *)(parm_ctx + *(int *)(parm_ctx + 0x280 + idx * 4));
  if ((((*local_8 == 'r') && (local_8[1] == 'e')) && (local_8[2] == 'g')) && (local_8[3] == ':')) {
    local_8 = local_8 + 4;
  }
  lVar1 = periph_find_reg(*(int *)(cur_dev + 4),local_8,(int *)local_c,(int *)local_10);
  if (lVar1 != 0) {
    *(undefined2 *)(parm_ctx + 0x4a0 + idx * 0x28) = local_10[0];
    *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = local_c[0];
    *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = *(undefined2 *)(cur_dev + 4);
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x67;
  }
  return (uint)(lVar1 != 0);
}


/* ==== parm_kw_R_radix @ 0046992e ==== */

int __cdecl parm_kw_R_radix(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3510,0x52,5);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_r2_radix_opt @ 00469952 ==== */

int __cdecl parm_kw_r2_radix_opt(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3528,0x72,5);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_pullup @ 00469976 ==== */

int __cdecl parm_kw_pullup(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_s_pullup_004d353c,0x75,1);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_r3_radix_opt @ 0046999a ==== */

int __cdecl parm_kw_r3_radix_opt(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3540,0x72,6);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_o_options @ 004699be ==== */

int __cdecl parm_kw_o_options(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_DAT_004d3558,0x6f,3);
  return (uint)(iVar1 != -1);
}


/* ==== parm_register_range @ 004699e2 ==== */

int __cdecl parm_register_range(int idx)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  uint local_38 [4];
  uint local_28;
  int local_10;
  uint *local_c;
  int local_8;
  
  local_8 = 0;
  iVar1 = parm_register(idx);
  if (iVar1 == 0) {
    iVar1 = parm_need_more(idx);
    if (iVar1 != 0) {
      local_c = (uint *)(parm_ctx + 0x480 + idx * 0x28);
      local_10 = *(int *)(parm_ctx + 0x280 + idx * 4);
      iVar1 = str_find_word((char *)(parm_ctx + local_10),&DAT_004d3b30);
      if (iVar1 != -1) {
        *(undefined1 *)(parm_ctx + local_10 + iVar1) = 0;
        iVar2 = parm_register(idx);
        if (iVar2 != 0) {
          puVar3 = local_c;
          puVar4 = local_38;
          for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          *(int *)(parm_ctx + 0x280 + idx * 4) = local_10 + 2 + iVar1;
          iVar2 = parm_register(idx);
          if (iVar2 != 0) {
            *(undefined1 *)(parm_ctx + idx + 0x200) = 0x47;
            local_38[2] = (uint)(ushort)local_c[8];
            local_28 = (uint)(ushort)local_c[9];
            puVar3 = local_38;
            for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
              *local_c = *puVar3;
              puVar3 = puVar3 + 1;
              local_c = local_c + 1;
            }
            local_8 = 1;
          }
          *(int *)(parm_ctx + 0x280 + idx * 4) = local_10;
        }
        *(undefined1 *)(parm_ctx + local_10 + iVar1) = 0x2e;
      }
    }
    if (local_8 == 0) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
    }
  }
  else {
    local_8 = 1;
  }
  return local_8;
}


/* ==== parm_periph_or_group @ 00469b40 ==== */

int __cdecl parm_periph_or_group(int idx)

{
  int iVar1;
  
  iVar1 = parm_periph_name(idx);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(idx,&DAT_004d3b34);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(idx,&DAT_004d3b38);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(idx,&DAT_004d3b3c);
        if (iVar1 == 0) {
          return 0;
        }
        *(short *)(parm_ctx + 0x4a4 + idx * 0x28) = (short)*(undefined4 *)(cur_dtype + 0x14) + 2;
      }
      else {
        *(short *)(parm_ctx + 0x4a4 + idx * 0x28) = (short)*(undefined4 *)(cur_dtype + 0x14) + 1;
      }
    }
    else {
      *(undefined2 *)(parm_ctx + 0x4a4 + idx * 0x28) = *(undefined2 *)(cur_dtype + 0x14);
    }
  }
  *(undefined2 *)(parm_ctx + 0x4a6 + idx * 0x28) = *(undefined2 *)(cur_dev + 4);
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x76;
  return 1;
}


/* ==== parm_number @ 00469c30 ==== */

int __cdecl parm_number(int idx,ulong max)

{
  char *s;
  uint uVar1;
  undefined4 *node;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  ulong local_10;
  
  s = (char *)(parm_ctx + 0x100 + *(int *)(parm_ctx + 0x280 + idx * 4));
  optr = s;
  uVar1 = strlen(s);
  if (*(int *)(cur_dtype + 0x4e8) == 0) {
    local_10 = *(ulong *)(cur_dtype + 0xc);
  }
  else {
    local_10 = (**(code **)(cur_dtype + 0x4e8))();
  }
  eval_int_masked(local_10,max);
  if (node != (undefined4 *)0x0) {
    puVar3 = node;
    puVar4 = (undefined4 *)(parm_ctx + 0x480 + idx * 0x28);
    for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined1 *)(parm_ctx + idx + 0x200) = 0x49;
    node_free(node);
    if (optr == s + uVar1) {
      return 1;
    }
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  *(int *)(parm_ctx + 0x1884) = (int)optr - (parm_ctx + 0x100);
  return 0;
}


/* ==== parm_keyword1 @ 00469d42 ==== */

int __cdecl parm_keyword1(int idx,char *kw)

{
  int iVar1;
  char *local_8;
  
  local_8 = kw;
  iVar1 = parm_match_keyword(idx,&local_8,0x6a,1);
  return (uint)(iVar1 != -1);
}


/* ==== parm_kw_h_stdio @ 00469d6e ==== */

int __cdecl parm_kw_h_stdio(int idx)

{
  int iVar1;
  
  iVar1 = parm_match_keyword(idx,&PTR_s_stdin_004d3708,0x68,3);
  return (uint)(iVar1 != -1);
}


/* ==== parm_window_name @ 00469d9d ==== */

int __cdecl parm_window_name(int idx)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *local_8;
  
  iVar3 = *(int *)(parm_ctx + 0x280 + idx * 4);
  iVar2 = parm_need_more(idx);
  if ((((iVar2 != 0) && (local_8 = (char *)(parm_ctx + iVar3), *local_8 == 'w')) &&
      (local_8[1] == 'i')) && ((local_8[2] == 'n' && (local_8 = local_8 + 3, *local_8 != '\0')))) {
    iVar3 = atoi(local_8);
    do {
      cVar1 = *local_8;
      local_8 = local_8 + 1;
      if (cVar1 == '\0') {
        if (0 < iVar3) {
          *(undefined1 *)(parm_ctx + idx + 0x200) = 0x57;
          *(int *)(parm_ctx + 0x488 + idx * 0x28) = iVar3;
          return 1;
        }
        return 0;
      }
    } while (('/' < cVar1) && (cVar1 < ':'));
  }
  return 0;
}


/* ==== parm_break_number_ff @ 00469eaa ==== */

int __cdecl parm_break_number_ff(int idx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = parm_need_more(idx);
  if (iVar1 != 0) {
    iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
    if (*(char *)(parm_ctx + iVar1) == '#') {
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1 + 1;
      iVar2 = parm_number(idx,0xff);
      if (iVar2 != 0) {
        iVar2 = *(int *)(parm_ctx + 0x488 + idx * 0x28);
        if (0 < iVar2) {
          *(int *)(parm_ctx + 0x48c + idx * 0x28) = iVar2;
          *(undefined1 *)(parm_ctx + idx + 0x200) = 0x77;
          *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
          return 1;
        }
        parm_errmsg = PTR_s_Range_of_Break_Number_is_1_99_004d3454;
        *(undefined4 *)(parm_ctx + 0x1884) = *(undefined4 *)(parm_ctx + 0x280 + idx * 4);
      }
      *(int *)(parm_ctx + 0x280 + idx * 4) = iVar1;
    }
    else {
      parm_errmsg = PTR_s_Invalid_parameter_004d344c;
      *(int *)(parm_ctx + 0x1884) = iVar1;
    }
  }
  *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
  return 0;
}


/* ==== parm_match_keyword @ 00469fe1 ==== */

int __cdecl parm_match_keyword(int idx,char **table,int letter,int count)

{
  int iVar1;
  int iVar2;
  char *a;
  int local_10;
  int local_8;
  
  iVar1 = *(int *)(parm_ctx + 0x280 + idx * 4);
  iVar2 = parm_need_more(idx);
  if (iVar2 == 0) {
    local_10 = -1;
  }
  else {
    a = (char *)(parm_ctx + iVar1);
    local_8 = 1;
    for (local_10 = 0; local_10 < count; local_10 = local_10 + 1) {
      local_8 = strcmp(a,*table);
      if (local_8 == 0) break;
      table = table + 1;
    }
    if ((local_10 == count) || (local_8 != 0)) {
      *(undefined1 *)(parm_ctx + idx + 0x200) = 0x75;
      parm_errmsg = PTR_s_Invalid_parameter_004d344c;
      *(int *)(parm_ctx + 0x1884) = iVar1;
      local_10 = -1;
    }
    else {
      *(undefined1 *)(parm_ctx + idx + 0x200) = (undefined1)letter;
      *(int *)(parm_ctx + 0x488 + idx * 0x28) = local_10;
    }
  }
  return local_10;
}


/* ==== str_find_char @ 0046a0d3 ==== */

int __cdecl str_find_char(char *s,int c)

{
  char cVar1;
  int local_10;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    cVar1 = *s;
    s = s + 1;
    if ((cVar1 == (char)c) || (cVar1 == '\0')) break;
    local_8 = local_8 + 1;
  }
  if (cVar1 == (char)c) {
    local_10 = local_8;
  }
  else {
    local_10 = -1;
  }
  return local_10;
}


/* ==== str_find_word @ 0046a134 ==== */

int __cdecl str_find_word(char *s,char *pat)

{
  char cVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  uint n;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint local_34;
  uint local_30;
  char *local_10;
  
  uVar4 = strlen(s);
  n = strlen(pat);
  cVar1 = *pat;
  local_10 = (char *)0x0;
  pcVar7 = pat;
  do {
    if (((int)(uVar4 - n) < (int)local_10) ||
       (iVar5 = str_find_char(s + (int)local_10,CONCAT31((int3)((uint)pcVar7 >> 8),cVar1)),
       iVar5 == -1)) {
      return -1;
    }
    iVar6 = strncmp(s + (int)local_10 + iVar5,pat,n);
    if (iVar6 == 0) {
      iVar6 = strcmp(pat,&DAT_004d3b40);
      if (iVar6 == 0) {
        return (int)(local_10 + iVar5);
      }
      pcVar7 = local_10 + iVar5;
      if (pcVar7 == (char *)0x0) {
        cVar2 = '\0';
      }
      else {
        cVar2 = (s + (int)pcVar7)[-1];
      }
      cVar3 = (s + 1)[(int)(pcVar7 + n)];
      if (__mb_cur_max < 2) {
        local_30 = *(ushort *)(_pctype + cVar2 * 2) & 0x107;
      }
      else {
        local_30 = _isctype((int)cVar2,0x107);
      }
      if (local_30 == 0) {
        if (__mb_cur_max < 2) {
          local_34 = *(ushort *)(_pctype + cVar3 * 2) & 0x107;
        }
        else {
          local_34 = _isctype((int)cVar3,0x107);
        }
        if (((local_34 == 0) && (cVar3 != '_')) && (cVar2 != '_')) {
          return (int)(local_10 + iVar5);
        }
      }
    }
    pcVar7 = local_10;
    local_10 = local_10 + iVar5 + 1;
  } while( true );
}


/* ==== parm_nop @ 0046a2cc ==== */

void parm_nop(void)

{
  return;
}


/* ==== parse_command_line @ 0046a2d1 ==== */

void __cdecl parse_command_line(char *line)

{
  int iVar1;
  
  parm_ctx = &cmd_tokbuf;
  parm_cmdline = line;
  parm_tokenize(line);
  iVar1 = parm_command_name(1);
  if (iVar1 == 0) {
    if ((*line != ';') && (iVar1 = parm_any_token(1), iVar1 != 0)) {
      parm_check_too_many(2);
    }
  }
  else {
    (**(code **)(*(int *)(command_table + *(int *)(parm_ctx + 0x4b0) * 4) + 0x14))();
  }
  return;
}


/* ==== parm_tokenize @ 0046a36a ==== */

void __cdecl parm_tokenize(char *line)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  uint local_2c;
  int local_14;
  int local_8;
  
  pcVar5 = parm_ctx;
  strncpy(parm_ctx,line,0xff);
  local_8 = 0;
  for (local_14 = 0; (pcVar5[local_14] == ' ' || (iVar7 = local_14, pcVar5[local_14] == '\t'));
      local_14 = local_14 + 1) {
  }
LAB_0046a3c1:
  do {
    local_14 = iVar7;
    cVar1 = pcVar5[local_14];
    if (cVar1 == '\0') {
LAB_0046a62a:
      iVar7 = local_14;
      *(int *)(parm_ctx + 0x280) = local_8;
      *(int *)(parm_ctx + (local_8 + 1) * 4 + 0x280) = local_14;
      parm_ctx[local_8 + 0x201] = 'e';
      pcVar6 = parm_ctx;
      for (local_14 = 0; local_14 <= iVar7; local_14 = local_14 + 1) {
        cVar1 = pcVar5[local_14];
        pcVar6[local_14 + 0x100] = cVar1;
        if (__mb_cur_max < 2) {
          local_2c = *(ushort *)(_pctype + cVar1 * 2) & 1;
        }
        else {
          local_2c = _isctype((int)cVar1,1);
        }
        if (local_2c != 0) {
          iVar8 = tolower((int)cVar1);
          pcVar5[local_14] = (char)iVar8;
        }
      }
      return;
    }
    if (cVar1 != '\"') {
      if (cVar1 == ';') {
        pcVar5[local_14] = '\0';
        if (local_8 == 0) {
          *(int *)(parm_ctx + 0x284) = local_14;
          parm_ctx[0x201] = ';';
          local_8 = 1;
        }
        goto LAB_0046a62a;
      }
      if ((cVar1 == ' ') || (cVar1 == '\t')) {
        pcVar5[local_14] = '\0';
        do {
          local_14 = local_14 + 1;
          cVar1 = pcVar5[local_14];
          iVar7 = local_14;
          if (cVar1 == '\0') break;
        } while ((cVar1 == ' ') || (cVar1 == '\t'));
      }
      else {
        iVar8 = local_8 + 1;
        *(int *)(parm_ctx + iVar8 * 4 + 0x280) = local_14;
        parm_ctx[local_8 + 0x201] = 'u';
        bVar3 = false;
        bVar4 = false;
        if (cVar1 == '{') {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
        do {
          while( true ) {
            while( true ) {
              iVar7 = local_14 + 1;
              cVar1 = pcVar5[iVar7];
              local_8 = iVar8;
              if (cVar1 == '\0') goto LAB_0046a3c1;
              if (bVar2) break;
              if (cVar1 == '{') {
                bVar2 = true;
                local_14 = iVar7;
              }
              else if (((cVar1 == ' ') || (cVar1 == '\t')) || (local_14 = iVar7, cVar1 == ';'))
              goto LAB_0046a3c1;
            }
            if (cVar1 == '\\') break;
            if (cVar1 == '\'') {
              bVar3 = !bVar3;
              local_14 = iVar7;
            }
            else if (cVar1 == '\"') {
              bVar4 = !bVar4;
              local_14 = iVar7;
            }
            else {
              local_14 = iVar7;
              if (((!bVar3) && (!bVar4)) && (cVar1 == '}')) {
                bVar2 = false;
              }
            }
          }
          local_14 = local_14 + 2;
          iVar7 = local_14;
        } while (pcVar5[local_14] != '\0');
      }
      goto LAB_0046a3c1;
    }
    pcVar5[local_14] = '\0';
    local_14 = local_14 + 1;
    iVar7 = local_8 + 1;
    *(int *)(parm_ctx + iVar7 * 4 + 0x280) = local_14;
    parm_ctx[local_8 + 0x201] = 'u';
    for (; (cVar1 = pcVar5[local_14], cVar1 != '\0' && (cVar1 != '\"')); local_14 = local_14 + 1) {
    }
    local_8 = iVar7;
    if (cVar1 == '\0') goto LAB_0046a62a;
    pcVar5[local_14] = '\0';
    iVar7 = local_14 + 1;
  } while( true );
}


