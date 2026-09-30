/* ==== bitrev16 @ 004240d0 ==== */

void __cdecl bitrev16(ulong v,ulong *out)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = 0x8000;
  uVar1 = 1;
  uVar4 = 0;
  iVar3 = 0x10;
  do {
    if ((v & uVar2) != 0) {
      uVar4 = uVar4 | uVar1;
    }
    uVar1 = uVar1 << 1;
    uVar2 = uVar2 >> 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *out = uVar4;
  return;
}


/* ==== dis_reset @ 00424100 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void dis_reset(void)

{
  dis_sel_e = 0;
  dis_sel_d = 0;
  dis_sel_c = 0;
  dis_sel_b = 0;
  dis_sel_a = 0;
  _dis_effect_flags = 0;
  return;
}


/* ==== hid_424130 @ 00424130 ==== */

void hid_424130(ulong *param_1,char *param_2,long param_3,long param_4,void *param_5)

{
  dis_cpu_level = 4;
  disassemble(param_1,param_2,param_3,param_4,param_5);
  return;
}


/* ==== disassemble_l1 @ 00424160 ==== */

void __cdecl disassemble_l1(ulong *insn,char *text,long a3,long a4,void *info)

{
  dis_cpu_level = 1;
  disassemble(insn,text,a3,a4,info);
  return;
}


/* ==== str_find_token @ 00424190 ==== */

ulong __cdecl str_find_token(char *hay,char *needle,char **pos)

{
  char cVar1;
  char cVar2;
  undefined3 extraout_var;
  int iVar4;
  undefined3 extraout_var_00;
  uint uVar5;
  char *pcVar3;
  
  cVar1 = *needle;
  uVar5 = 0xffffffff;
  pcVar3 = needle;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar2 != '\0');
  cVar2 = strchr(hay,(int)cVar1);
  pcVar3 = (char *)CONCAT31(extraout_var,cVar2);
  if (pcVar3 == (char *)0x0) {
    return 0;
  }
  do {
    iVar4 = strncmp(needle,pcVar3,~uVar5 - 1);
    if (iVar4 == 0) {
      *pos = pcVar3;
      return ~uVar5 - 1;
    }
    cVar2 = strchr(pcVar3 + 1,(int)cVar1);
    pcVar3 = (char *)CONCAT31(extraout_var_00,cVar2);
  } while (pcVar3 != (char *)0x0);
  return 0;
}


/* ==== fmt_hex_dollar @ 00424200 ==== */

void __cdecl fmt_hex_dollar(ulong v,char *out)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char acStack_c [12];
  
  iVar2 = 9;
  do {
    iVar3 = iVar2;
    uVar5 = v & 0xf;
    v = v >> 4;
    (&stack0xfffffff3)[iVar3] = hex_digits[uVar5];
    if (v == 0) break;
    iVar2 = iVar3 + -1;
  } while (1 < iVar3 + -1);
  uVar5 = 0xffffffff;
  (&stack0xfffffff2)[iVar3] = '$';
  pcVar6 = &stack0xfffffff2 + iVar3;
  do {
    pcVar7 = pcVar6;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar6 = pcVar7 + -uVar5;
  for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)out = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    out = out + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *out = *pcVar6;
    pcVar6 = pcVar6 + 1;
    out = out + 1;
  }
  return;
}


/* ==== fmt_hex24 @ 00424260 ==== */

void __cdecl fmt_hex24(ulong v,char *out)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  undefined1 auStack_c [12];
  
  uVar4 = v & 0xffffff;
  iVar2 = 9;
  do {
    iVar3 = iVar2;
    uVar5 = uVar4 & 0xf;
    uVar4 = uVar4 >> 4;
    (&stack0xfffffff3)[iVar3] = hex_digits[uVar5];
    if (uVar4 == 0) break;
    iVar2 = iVar3 + -1;
  } while (0 < iVar3 + -1);
  uVar4 = 0xffffffff;
  pcVar6 = &stack0xfffffff3 + iVar3;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)out = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    out = out + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *out = *pcVar6;
    pcVar6 = pcVar6 + 1;
    out = out + 1;
  }
  return;
}


/* ==== dis_ea_tokens @ 004242c0 ==== */

int __cdecl dis_ea_tokens(ulong opw,long *tok)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  long lVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  uVar6 = opw & 0xff;
  uVar8 = (int)uVar6 >> 4 & 7;
  if ((int)uVar6 >> 7 == 0) {
    if (((uVar6 == 0xc) || (uVar6 == 4)) || (iVar2 = (opw & 7) + uVar8 * 8, uVar6 == 8)) {
      iVar2 = 0x40;
    }
    lVar5 = *(long *)(&DAT_004c09d8 + iVar2 * 4);
    iVar7 = *(int *)(&DAT_004c0af0 + uVar6 * 4);
    iVar9 = 0;
    if (*(int *)(&DAT_004c10f0 + iVar2 * 4) != 0) goto LAB_00424359;
    iVar2 = 0;
  }
  else {
    lVar5 = *(long *)(&DAT_004c0ae0 + (opw & 3) * 4);
    iVar9 = *(int *)(&DAT_004c1248 + uVar8 * 4);
    iVar7 = *(int *)(&DAT_004c1208 + (((int)(char)(opw & 7) & 4U) << 1 | uVar8) * 4);
LAB_00424359:
    iVar2 = (((int)uVar6 >> 3 & 1U) != 0) + 0xb;
  }
  *tok = lVar5;
  bVar1 = false;
  piVar4 = tok + 1;
  if (iVar7 != 0) {
    *piVar4 = 0x9a;
    bVar1 = true;
    tok[2] = iVar7 + 0x57;
    piVar4 = tok + 3;
    if ((iVar9 != 0) || (iVar2 != 0)) {
      *piVar4 = 0x99;
      piVar4 = tok + 4;
    }
  }
  if (iVar9 != 0) {
    piVar3 = piVar4;
    if (!bVar1) {
      *piVar4 = 0x9a;
      bVar1 = true;
      piVar3 = piVar4 + 1;
    }
    *piVar3 = iVar9 + 0x57;
    piVar4 = piVar3 + 1;
    if (iVar2 == 0) goto LAB_004243dd;
    *piVar4 = 0x99;
    piVar4 = piVar3 + 2;
  }
  if (iVar2 != 0) {
    if (!bVar1) {
      *piVar4 = 0x9a;
      piVar4 = piVar4 + 1;
    }
    *piVar4 = iVar2 + 0x57;
    piVar4 = piVar4 + 1;
  }
LAB_004243dd:
  *piVar4 = 0x9a;
  return (int)piVar4 + (4 - (int)tok) >> 2;
}


/* ==== hid_4243f0 @ 004243f0 ==== */

void hid_4243f0(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  cVar1 = *param_1;
  while (cVar1 != '\0') {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[cVar1 * 2] & 8;
    }
    else {
      uVar2 = _isctype((int)cVar1,8);
    }
    if (uVar2 == 0) break;
    pcVar4 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar1 = *pcVar4;
  }
  if ((*param_1 == '\0') || (*param_1 == ';')) {
    asm_result = 0;
    return;
  }
  uVar2 = 0xffffffff;
  asm_line_buf._0_1_ = 0x20;
  do {
    pcVar4 = param_1;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar4 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar4;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar4 + -uVar2;
  pcVar5 = (char *)((int)&asm_line_buf + 1);
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  asm_split_fields();
  asm_line();
  return;
}


/* ==== asm_split_fields @ 00424480 ==== */

void asm_split_fields(void)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  pcVar7 = &asm_label;
  if (((char)asm_line_buf != ';') && ((char)asm_line_buf != '\0')) {
    pcVar2 = skip_to_space((char *)&asm_line_buf);
    pcVar6 = (char *)&asm_line_buf;
    if (pcVar2 != (char *)&asm_line_buf) {
      puVar8 = &asm_line_buf;
      puVar9 = (undefined4 *)&asm_label;
      for (uVar4 = (uint)(pcVar2 + -0x4dbf08) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar9 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar9 = puVar9 + 1;
      }
      pcVar7 = pcVar2 + 0x108;
      for (uVar4 = (uint)(pcVar2 + -0x4dbf08) & 3; pcVar6 = pcVar2, uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
    }
    *pcVar7 = '\0';
    pcVar7 = pcVar7 + 1;
    while( true ) {
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*pcVar6 * 2] & 8;
      }
      else {
        uVar4 = _isctype((int)*pcVar6,8);
      }
      if (uVar4 == 0) break;
      pcVar6 = pcVar6 + 1;
    }
    pcVar2 = pcVar6;
    asm_mnem_field = pcVar7;
    if ((*pcVar6 != ';') && (pcVar3 = skip_to_space(pcVar6), pcVar6 != pcVar3)) {
      uVar4 = (int)pcVar3 - (int)pcVar6;
      pcVar2 = pcVar6 + uVar4;
      pcVar3 = pcVar7;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar3 = pcVar3 + 4;
      }
      pcVar7 = pcVar7 + uVar4;
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar3 = pcVar3 + 1;
      }
    }
    *pcVar7 = '\0';
    pcVar7 = pcVar7 + 1;
    while( true ) {
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*pcVar2 * 2] & 8;
      }
      else {
        uVar4 = _isctype((int)*pcVar2,8);
      }
      if (uVar4 == 0) break;
      pcVar2 = pcVar2 + 1;
    }
    pcVar6 = pcVar2;
    asm_op1_field = pcVar7;
    if ((*pcVar2 != ';') && (pcVar3 = skip_to_space(pcVar2), pcVar2 != pcVar3)) {
      uVar4 = (int)pcVar3 - (int)pcVar2;
      pcVar6 = pcVar2 + uVar4;
      pcVar3 = pcVar7;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      pcVar7 = pcVar7 + uVar4;
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar3 = pcVar3 + 1;
      }
    }
    *pcVar7 = '\0';
    pcVar7 = pcVar7 + 1;
    while( true ) {
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*pcVar6 * 2] & 8;
      }
      else {
        uVar4 = _isctype((int)*pcVar6,8);
      }
      if (uVar4 == 0) break;
      pcVar6 = pcVar6 + 1;
    }
    pcVar2 = pcVar6;
    asm_op2_field = pcVar7;
    if ((*pcVar6 != ';') && (pcVar3 = skip_to_space(pcVar6), pcVar6 != pcVar3)) {
      uVar4 = (int)pcVar3 - (int)pcVar6;
      pcVar2 = pcVar6 + uVar4;
      pcVar3 = pcVar7;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar3 = pcVar3 + 4;
      }
      pcVar7 = pcVar7 + uVar4;
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar3 = pcVar3 + 1;
      }
    }
    *pcVar7 = '\0';
    pcVar7 = pcVar7 + 1;
    while( true ) {
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*pcVar2 * 2] & 8;
      }
      else {
        uVar4 = _isctype((int)*pcVar2,8);
      }
      if (uVar4 == 0) break;
      pcVar2 = pcVar2 + 1;
    }
    pcVar6 = pcVar2;
    asm_op3_field = pcVar7;
    if ((*pcVar2 != ';') && (pcVar3 = skip_to_space(pcVar2), pcVar2 != pcVar3)) {
      uVar4 = (int)pcVar3 - (int)pcVar2;
      pcVar6 = pcVar2 + uVar4;
      pcVar3 = pcVar7;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      pcVar7 = pcVar7 + uVar4;
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar3 = pcVar3 + 1;
      }
    }
    *pcVar7 = '\0';
    pcVar7 = pcVar7 + 1;
    while( true ) {
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*pcVar6 * 2] & 8;
      }
      else {
        uVar4 = _isctype((int)*pcVar6,8);
      }
      if (uVar4 == 0) break;
      pcVar6 = pcVar6 + 1;
    }
    if (pcVar6[1] != ';') {
      cVar1 = *pcVar6;
      while (cVar1 != '\0') {
        *pcVar7 = cVar1;
        pcVar2 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
        pcVar6 = pcVar6 + 1;
        cVar1 = *pcVar2;
      }
    }
    *pcVar7 = '\0';
  }
  return;
}


/* ==== skip_to_space @ 004246e0 ==== */

char * __cdecl skip_to_space(char *s)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = *s;
  while( true ) {
    if (cVar1 == '\0') {
      return s;
    }
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[cVar1 * 2] & 8;
    }
    else {
      uVar2 = _isctype((int)cVar1,8);
    }
    if (uVar2 != 0) break;
    cVar1 = s[1];
    s = s + 1;
  }
  return s;
}


/* ==== asm_line @ 00424730 ==== */

void asm_line(void)

{
  char cVar1;
  char *pcVar2;
  void *ientry;
  uint uVar3;
  
  optr = 0;
  if (*asm_mnem_field != '\0') {
    uVar3 = 0xffffffff;
    pcVar2 = asm_mnem_field;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (~uVar3 - 1 < 0x10) {
      pcVar2 = str_lower_copy(asm_mnem_field);
      ientry = find_mnemonic(pcVar2);
      if (ientry != (void *)0x0) {
        proc_instr(ientry);
        return;
      }
    }
    expr_error(s_Unrecognized_mnemonic_004c1f48);
  }
  return;
}


/* ==== str_lower_copy @ 00424790 ==== */

char * __cdecl str_lower_copy(char *s)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = &asm_mnem_lower;
  cVar1 = *s;
  if (cVar1 != '\0') {
    do {
      cVar1 = lower_char(cVar1);
      *pcVar2 = cVar1;
      cVar1 = pcVar2[(int)(s + -0x4dc11f)];
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
  }
  *pcVar2 = '\0';
  return &asm_mnem_lower;
}


/* ==== lower_char @ 004247d0 ==== */

char __cdecl lower_char(char c)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = (int)c;
  if (__mb_cur_max < 2) {
    uVar1 = (byte)_pctype[iVar2 * 2] & 1;
  }
  else {
    uVar1 = _isctype(iVar2,1);
  }
  if (uVar1 != 0) {
    iVar2 = tolower(iVar2);
    c = (char)iVar2;
  }
  return c;
}


/* ==== find_mnemonic @ 00424810 ==== */

void * __cdecl find_mnemonic(char *name)

{
  void *pvVar1;
  
  pvVar1 = bsearch_cb(name,(char *)&asm_mnem_table,asm_mnem_count,0xc,hid_4248a0);
  return pvVar1;
}


/* ==== bsearch_cb @ 00424830 ==== */

void * __cdecl bsearch_cb(char *key,char *base,long count,long size,void *cmp)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = base + (count + -1) * size;
  if (pcVar2 < base) {
    return (void *)0x0;
  }
  do {
    pcVar3 = base + (((int)pcVar2 - (int)base) / size >> 1) * size;
    iVar1 = (*cmp)(key,pcVar3);
    if (iVar1 < 0) {
      pcVar2 = pcVar3 + -size;
    }
    else {
      if (iVar1 < 1) {
        return pcVar3;
      }
      base = pcVar3 + size;
    }
  } while (base <= pcVar2);
  return (void *)0x0;
}


/* ==== hid_4248a0 @ 004248a0 ==== */

int hid_4248a0(byte *param_1,undefined4 *param_2)

{
  byte bVar1;
  byte *pbVar2;
  bool bVar3;
  
  pbVar2 = (byte *)*param_2;
  while( true ) {
    bVar1 = *param_1;
    bVar3 = bVar1 < *pbVar2;
    if (bVar1 != *pbVar2) break;
    if (bVar1 == 0) {
      return 0;
    }
    bVar1 = param_1[1];
    bVar3 = bVar1 < pbVar2[1];
    if (bVar1 != pbVar2[1]) break;
    param_1 = param_1 + 2;
    pbVar2 = pbVar2 + 2;
    if (bVar1 == 0) {
      return 0;
    }
  }
  return (1 - (uint)bVar3) - (uint)(bVar3 != 0);
}


/* ==== proc_instr @ 004248e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl proc_instr(void *ientry)

{
  int pmclass;
  int iVar1;
  int iclass;
  int local_a0;
  uint local_9c;
  undefined4 local_98;
  undefined1 local_60 [24];
  undefined1 local_48 [24];
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  iclass = (int)*(char *)((int)ientry + 4);
  asm_clear_flags();
  local_9c = *(uint *)((int)ientry + 8);
  iVar1 = 0;
  local_a0 = 1;
  local_98 = 0;
  asm_result = 1;
  optr = asm_op1_field;
  switch(iclass) {
  case 1:
    iVar1 = p_addl(&local_a0);
    break;
  case 2:
  case 3:
  case 0x27:
  case 0x28:
    iVar1 = p_alu1(iclass,&local_a0);
    break;
  case 4:
    iVar1 = p_and_or(&local_a0);
    break;
  case 5:
    iVar1 = p_bitop(&local_a0);
    break;
  default:
    expr_error(s_Error_in_mnemonic_table_004c1f8c);
    break;
  case 7:
  case 0x22:
  case 0x23:
    iVar1 = p_alu2(iclass,&local_a0);
    break;
  case 8:
    iVar1 = p_div(&local_a0);
    break;
  case 9:
    iVar1 = p_do(&local_a0);
    break;
  case 10:
    iVar1 = p_enddo();
    break;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0x1b:
  case 0x29:
    iVar1 = p_noarg();
    break;
  case 0xe:
  case 0x13:
    iVar1 = p_jmp(iclass,&local_a0);
    break;
  case 0xf:
  case 0x11:
    iVar1 = p_jbit(&local_a0);
    break;
  case 0x10:
  case 0x12:
    iVar1 = p_jsr(iclass,&local_a0);
    break;
  case 0x14:
    iVar1 = p_lua(&local_a0);
    break;
  case 0x15:
  case 0x1a:
  case 0x2a:
  case 0x2b:
    iVar1 = p_mul(iclass,&local_a0);
    break;
  case 0x16:
  case 0x17:
  case 0x18:
    iVar1 = p_move();
    break;
  case 0x19:
    iVar1 = p_movep(&local_a0);
    break;
  case 0x1c:
    iVar1 = p_norm(&local_a0);
    break;
  case 0x1d:
    iVar1 = p_rep(&local_a0);
    break;
  case 0x1e:
  case 0x1f:
    iVar1 = p_rts();
    break;
  case 0x20:
  case 0x24:
    iVar1 = p_eor_adc(iclass,&local_a0);
    break;
  case 0x25:
    iVar1 = p_andi(&local_a0);
    break;
  case 0x26:
    iVar1 = p_tcc(&local_a0);
  }
  if (*(char *)((int)ientry + 5) == '\x03') {
    pmclass = iVar1;
    iVar1 = 1;
  }
  else {
    pmclass = (int)*(char *)((int)ientry + 5);
  }
  if (pmclass == 0) {
    if (((*asm_op2_field != '\0') && (iclass != 0x19)) && (iclass != 0x26)) {
      expr_error(s_Too_many_fields_specified_for_in_004c1f60);
      iVar1 = 0;
    }
  }
  else if (*asm_op2_field == '\0') {
    local_9c = local_9c | 0x200000;
  }
  else {
    if (*asm_op3_field == '\0') {
      asm_xy_swapped = 0;
    }
    else {
      asm_xy_swapped = canon_xy_fields();
    }
    iVar1 = do_xy(&local_a0,pmclass,local_48,local_60,local_18,local_30);
    if (asm_xy_swapped != 0) {
      swap_op2_op3();
    }
  }
  if (0 < asm_result) {
    asm_result = local_a0;
    _DAT_005059e4 = local_9c;
    _DAT_005059e8 = local_98;
  }
  return iVar1;
}


/* ==== do_xy @ 00424c50 ==== */

int __cdecl do_xy(void *insn,int pmclass,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  
  optr = asm_op2_field;
  parse_space(xs,6);
  if (*(int *)xs == 0) {
    iVar1 = parse_xfield_src(xs);
    if (iVar1 == 0) {
      *(undefined4 *)insn = 2;
      return 0;
    }
    iVar1 = *(int *)((int)xs + 4);
    if ((2 < iVar1) && (iVar1 < 7)) {
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_pm_update(insn,xs);
        return 1;
      }
      return 0;
    }
    if (((1 < iVar1) && (iVar1 < 9)) || ((0xd < iVar1 && (iVar1 < 0x11)))) {
      expr_error(s_Missing_memory_space_specifier_004c1fa4);
      *(undefined4 *)insn = 2;
      return 0;
    }
    if (iVar1 == 0xb) {
      iVar1 = xy_imm_short(pmclass,insn,xs,xd,ys,yd);
      return iVar1;
    }
    if (iVar1 == 9) {
      iVar1 = xy_imm_long(pmclass,insn,xs,xd,ys,yd);
      return iVar1;
    }
    switch(*(undefined4 *)((int)xs + 0x14)) {
    case 0:
    case 1:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
      iVar1 = xy_lreg(insn,xs,xd);
      return iVar1;
    case 2:
    case 3:
      iVar1 = xy_acc(pmclass,insn,xs,xd,ys,yd);
      return iVar1;
    case 4:
    case 6:
      iVar1 = xy_xreg(pmclass,insn,xs,xd,ys,yd);
      return iVar1;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = xy_reg(pmclass,insn,xs,xd,ys,yd);
      return iVar1;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      iVar1 = xy_mreg(pmclass,insn,xs,xd);
      return iVar1;
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      iVar1 = xy_ctlreg(pmclass,insn,xs,xd);
      return iVar1;
    }
  }
  iVar1 = *(int *)xs;
  if ((iVar1 == 1) || (iVar1 == 2)) {
    iVar1 = parse_operand(1,xs,0,1,9,0);
    if (iVar1 == 0) {
      *(uint *)insn = 2 - (uint)((*(uint *)((int)xs + 0xc) & 0x20) != 0);
      return 0;
    }
    iVar1 = *(int *)xs;
    if (iVar1 == 1) {
      iVar1 = xy_xsrc(pmclass,insn,xs,xd,ys,yd);
      return iVar1;
    }
    if (iVar1 == 2) {
      iVar1 = xy_ysrc(pmclass,insn,xs,xd);
      return iVar1;
    }
  }
  if (iVar1 != 4) {
    iVar1 = parse_operand(1,xs,0,1,9,0);
    if (iVar1 != 0) {
      iVar1 = xy_psrc(pmclass,insn,xs,xd);
      return iVar1;
    }
    *(undefined4 *)insn = 2;
    return 0;
  }
  iVar1 = parse_operand(1,xs,0,1,9,0);
  if (iVar1 != 0) {
    iVar1 = xy_lsrc(insn,xs,xd);
    return iVar1;
  }
  *(undefined4 *)insn = 2;
  return 0;
}


/* ==== parse_space @ 00424f60 ==== */

int __cdecl parse_space(long *space,int cls)

{
  char c;
  int iVar1;
  bool bVar2;
  
  iVar1 = 0;
  if ((*optr != '\0') && (optr[1] == ':')) {
    c = *optr;
    optr = optr + 2;
    iVar1 = space_code(c);
    if (iVar1 == -1) {
      expr_error(s_Illegal_memory_space_specified_004c2054);
      return 0;
    }
  }
  *space = iVar1;
  switch(cls) {
  case 0:
    goto switchD_00424fad_caseD_0;
  case 1:
    if (iVar1 == 1) {
      return 1;
    }
    break;
  case 2:
    goto switchD_00424fad_caseD_2;
  case 3:
    if (iVar1 == 4) {
      return 1;
    }
    break;
  case 4:
    if (iVar1 == 8) {
      return 1;
    }
    break;
  case 5:
    if (iVar1 == 1) {
      return 1;
    }
    goto switchD_00424fad_caseD_2;
  case 6:
    if (iVar1 == 1) {
      return 1;
    }
    if (iVar1 == 2) {
      return 1;
    }
    if (iVar1 == 4) {
      return 1;
    }
    goto LAB_0042500a;
  case 7:
    if (iVar1 == 1) {
      return 1;
    }
    bVar2 = iVar1 == 2;
    goto LAB_0042500d;
  case 8:
    bVar2 = iVar1 == 2;
    goto LAB_0042500d;
  case 9:
    if (iVar1 == 1) {
      return 1;
    }
    if (iVar1 == 2) {
      return 1;
    }
LAB_0042500a:
    bVar2 = iVar1 == 8;
LAB_0042500d:
    if (!bVar2) {
switchD_00424fad_caseD_0:
      if (iVar1 != 0) break;
    }
    return 1;
  }
switchD_0042501e_switchD:
  switch(iVar1) {
  case 0:
    expr_error(s_Missing_memory_space_specifier_004c1fa4);
    break;
  case 1:
    expr_error(s_Illegal_memory_space_specified___004c2030);
    return 0;
  case 2:
    expr_error(s_Illegal_memory_space_specified___004c200c);
    return 0;
  case 4:
    expr_error(s_Illegal_memory_space_specified___004c1fc4);
    return 0;
  case 8:
    expr_error(s_Illegal_memory_space_specified___004c1fe8);
    return 0;
  }
  return 0;
switchD_00424fad_caseD_2:
  if (iVar1 == 2) {
    return 1;
  }
  goto switchD_0042501e_switchD;
}


/* ==== space_code @ 004250d0 ==== */

int __cdecl space_code(char c)

{
  char cVar1;
  
  cVar1 = lower_char(c);
  switch(cVar1) {
  case 'l':
    return 4;
  default:
    return -1;
  case 'n':
    return 0;
  case 'p':
    return 8;
  case 'x':
    return 1;
  case 'y':
    return 2;
  }
}


/* ==== parse_xfield_src @ 00425140 ==== */

int __cdecl parse_xfield_src(void *op)

{
  char cVar1;
  int iVar2;
  
  iVar2 = get_amode(0,op,0x12,1,6,6);
  if (iVar2 == 0) {
    return 0;
  }
  if (((*(int *)op == 0) && (2 < *(int *)((int)op + 4))) && (*(int *)((int)op + 4) < 7)) {
    if (*optr != '\0') {
      expr_error(s_Address_mode_syntax_error___extr_004c20a0);
      return 0;
    }
  }
  else {
    cVar1 = *optr;
    optr = optr + 1;
    if (cVar1 != ',') {
      expr_error(s_Address_mode_syntax_error___expe_004c2074);
      return 0;
    }
  }
  return 1;
}


/* ==== parse_operand @ 004251c0 ==== */

int __cdecl parse_operand(ulong flags,void *op,int regclass,int eaclass,int absclass,int immclass)

{
  char cVar1;
  int iVar2;
  
  iVar2 = get_amode(flags,op,regclass,eaclass,absclass,immclass);
  if (iVar2 == 0) {
    return 0;
  }
  if ((flags & 1) == 0) {
    if (*optr != '\0') {
      expr_error(s_Address_mode_syntax_error___extr_004c20a0);
      return 0;
    }
  }
  else {
    cVar1 = *optr;
    optr = optr + 1;
    if (cVar1 != ',') {
      expr_error(s_Address_mode_syntax_error___expe_004c2074);
      return 0;
    }
  }
  return 1;
}


/* ==== get_amode @ 00425230 ==== */

int __cdecl get_amode(ulong flags,void *op,int regclass,int eaclass,int absclass,int immclass)

{
  int iVar1;
  
  *(undefined4 *)((int)op + 4) = 0;
  *(undefined4 *)((int)op + 0x10) = 0;
  *(undefined4 *)((int)op + 0xc) = 0;
  *(undefined4 *)((int)op + 0x14) = 0xffffffff;
  if (*optr == '\0') {
    expr_error(s_Syntax_error___missing_address_m_004c216c);
    return 0;
  }
  if (regclass != 0) {
    iVar1 = amode_register(regclass,op);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      iVar1 = note_reg_direct(flags,regclass,*(int *)((int)op + 0x14));
      return (uint)(iVar1 != 0);
    }
  }
  if (((immclass == 0) && (eaclass == 0)) && (absclass == 0)) {
    expr_error(s_Only_register_direct_addressing_a_004c2144);
    return 0;
  }
  if (immclass != 0) {
    iVar1 = amode_immediate(immclass,op);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      return 1;
    }
  }
  if (eaclass == 0) {
    if (absclass == 0) {
      if (regclass == 0) {
        expr_error(s_Only_immediate_addressing_allowe_004c2120);
        return 0;
      }
      if (immclass != 0) {
        expr_error(s_Only_immediate_and_register_dire_004c20e8);
        return 0;
      }
      expr_error(s_Only_register_direct_addressing_a_004c2144);
      return 0;
    }
  }
  else {
    iVar1 = amode_indirect(eaclass,op);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      return 1;
    }
  }
  if (absclass != 0) {
    iVar1 = amode_absolute(absclass,op);
    if (iVar1 == -1) {
      return 0;
    }
    if (iVar1 == 1) {
      return 1;
    }
  }
  expr_error(s_Invalid_addressing_mode_004c20d0);
  return 0;
}


/* ==== amode_indirect @ 00425390 ==== */

int __cdecl amode_indirect(int eaclass,void *op)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = optr;
  if ((*optr == '-') && (optr[1] == '(')) {
    optr = optr + 2;
    iVar2 = parse_addr_reg();
    *(int *)((int)op + 0x14) = iVar2;
    if (iVar2 == -1) {
      optr = pcVar3;
      return 0;
    }
    cVar1 = *optr;
    optr = optr + 1;
    pcVar3 = optr;
    if (cVar1 == ')') {
      if (eaclass == 1) {
        *(undefined4 *)((int)op + 4) = 8;
        return 1;
      }
      expr_error(s_Pre_decrement_addressing_mode_no_004c2264);
      return -1;
    }
  }
  else {
    if (*optr != '(') {
      return 0;
    }
    optr = optr + 1;
    iVar2 = parse_addr_reg();
    *(int *)((int)op + 0x14) = iVar2;
    if (iVar2 == -1) {
      optr = pcVar3;
      return 0;
    }
    if (*optr == '+') {
      optr = optr + 1;
      iVar2 = parse_offset_reg(*(int *)((int)op + 0x14));
      pcVar3 = optr;
      if (iVar2 != -1) {
        cVar1 = *optr;
        optr = optr + 1;
        pcVar3 = optr;
        if (cVar1 == ')') {
          if ((*optr == ',') || (*optr == '\0')) {
            if (eaclass == 1) {
              *(undefined4 *)((int)op + 4) = 7;
              return 1;
            }
            expr_error(s_Indexed_address_mode_not_allowed_004c2240);
            return -1;
          }
          goto LAB_00425516;
        }
      }
    }
    else {
      pcVar3 = optr + 1;
      if (*optr == ')') {
        cVar1 = *pcVar3;
        if ((cVar1 == '\0') || (cVar1 == ',')) {
          optr = pcVar3;
          if ((eaclass != 1) && (eaclass != 2)) {
            expr_error(s_No_update_mode_not_allowed_004c219c);
            return -1;
          }
          *(undefined4 *)((int)op + 4) = 2;
          return 1;
        }
        if ((cVar1 == '+') || (cVar1 == '-')) {
          optr = optr + 2;
          if ((*optr == '\0') || (*optr == ',')) {
            if (cVar1 == '+') {
              *(undefined4 *)((int)op + 4) = 3;
              return 1;
            }
            *(undefined4 *)((int)op + 4) = 4;
            return 1;
          }
          iVar2 = parse_offset_reg(*(int *)((int)op + 0x14));
          pcVar3 = optr;
          if ((iVar2 != 0) && ((*optr == '\0' || (*optr == ',')))) {
            if (cVar1 == '+') {
              *(undefined4 *)((int)op + 4) = 5;
              return 1;
            }
            if ((eaclass != 1) && (eaclass != 3)) {
              expr_error(s_Post_decrement_by_offset_address_004c21b8);
              return -1;
            }
            *(undefined4 *)((int)op + 4) = 6;
            return 1;
          }
        }
LAB_00425516:
        optr = pcVar3;
        expr_error(s_Address_mode_syntax_error_004c21f0);
        return -1;
      }
    }
  }
  optr = pcVar3;
  expr_error(s_Address_mode_syntax_error___prob_004c220c);
  return -1;
}


/* ==== parse_addr_reg @ 004255d0 ==== */

int parse_addr_reg(void)

{
  int iVar1;
  
  iVar1 = match_register_name((char **)&optr);
  if (((iVar1 == -1) || (iVar1 < 0xe)) || (0x15 < iVar1)) {
    iVar1 = -1;
  }
  return iVar1;
}


/* ==== parse_offset_reg @ 004255f0 ==== */

int __cdecl parse_offset_reg(int areg)

{
  int iVar1;
  
  iVar1 = match_register_name(&optr);
  if (iVar1 == -1) {
    if ((*optr == 'N') || (*optr == 'n')) {
      optr = optr + 1;
      return 1;
    }
  }
  else if ((0x15 < iVar1) && (iVar1 < 0x1e)) {
    if (iVar1 + -0x16 == areg + -0xe) {
      return 1;
    }
    expr_error(s_Offset_register_number_must_be_t_004c2290);
  }
  return 0;
}


/* ==== match_register_name @ 00425650 ==== */

int __cdecl match_register_name(char **pp)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  
  pcVar1 = *pp;
  cVar2 = *pcVar1;
  *pp = pcVar1 + 1;
  cVar2 = lower_char(cVar2);
  switch(cVar2) {
  case 'a':
    if (__mb_cur_max < 2) {
      uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
    }
    else {
      uVar3 = _isctype((int)**pp,0x107);
    }
    if ((uVar3 == 0) && (**pp != '_')) {
      return 2;
    }
    cVar2 = **pp;
    *pp = *pp + 1;
    cVar2 = lower_char(cVar2);
    switch(cVar2) {
    case '0':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 8;
      }
      break;
    case '1':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 10;
      }
      cVar2 = **pp;
      pcVar4 = *pp + 1;
      *pp = pcVar4;
      if (cVar2 == '0') {
        if (__mb_cur_max < 2) {
          uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
        }
        else {
          uVar3 = _isctype((int)*pcVar4,0x107);
        }
        if ((uVar3 == 0) && (**pp != '_')) {
          return 0x28;
        }
      }
      break;
    case '2':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0xc;
      }
      break;
    case 'b':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x26;
      }
    }
    break;
  case 'b':
    if (__mb_cur_max < 2) {
      uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
    }
    else {
      uVar3 = _isctype((int)**pp,0x107);
    }
    if ((uVar3 == 0) && (**pp != '_')) {
      return 3;
    }
    cVar2 = **pp;
    *pp = *pp + 1;
    cVar2 = lower_char(cVar2);
    switch(cVar2) {
    case '0':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 9;
      }
      break;
    case '1':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0xb;
      }
      cVar2 = **pp;
      pcVar4 = *pp + 1;
      *pp = pcVar4;
      if (cVar2 == '0') {
        if (__mb_cur_max < 2) {
          uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
        }
        else {
          uVar3 = _isctype((int)*pcVar4,0x107);
        }
        if ((uVar3 == 0) && (**pp != '_')) {
          return 0x29;
        }
      }
      break;
    case '2':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0xd;
      }
      break;
    case 'a':
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x27;
      }
    }
    break;
  case 'c':
    cVar2 = **pp;
    *pp = *pp + 1;
    cVar2 = lower_char(cVar2);
    if (cVar2 == 'c') {
      cVar2 = **pp;
      *pp = *pp + 1;
      cVar2 = lower_char(cVar2);
      if (cVar2 == 'r') {
        if (__mb_cur_max < 2) {
          uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
        }
        else {
          uVar3 = _isctype((int)**pp,0x107);
        }
        if ((uVar3 == 0) && (**pp != '_')) {
          return 0x32;
        }
      }
    }
    break;
  case 'l':
    cVar2 = **pp;
    *pp = *pp + 1;
    cVar2 = lower_char(cVar2);
    if (cVar2 == 'a') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x2c;
      }
    }
    else if (cVar2 == 'c') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x2d;
      }
    }
    break;
  case 'm':
    cVar2 = **pp;
    pcVar4 = *pp + 1;
    *pp = pcVar4;
    if (('/' < cVar2) && (cVar2 < '8')) {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return cVar2 + -0x12;
      }
    }
    cVar2 = lower_char(cVar2);
    if (cVar2 == 'r') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x31;
      }
    }
    break;
  case 'n':
    cVar2 = **pp;
    pcVar4 = *pp + 1;
    *pp = pcVar4;
    if (('/' < cVar2) && (cVar2 < '8')) {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return cVar2 + -0x1a;
      }
    }
    break;
  case 'o':
    cVar2 = **pp;
    *pp = *pp + 1;
    cVar2 = lower_char(cVar2);
    if (cVar2 == 'm') {
      cVar2 = **pp;
      *pp = *pp + 1;
      cVar2 = lower_char(cVar2);
      if (cVar2 == 'r') {
        if (__mb_cur_max < 2) {
          uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
        }
        else {
          uVar3 = _isctype((int)**pp,0x107);
        }
        if ((uVar3 == 0) && (**pp != '_')) {
          return 0x2a;
        }
      }
    }
    break;
  case 'r':
    cVar2 = **pp;
    pcVar4 = *pp + 1;
    *pp = pcVar4;
    if (('/' < cVar2) && (cVar2 < '8')) {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return cVar2 + -0x22;
      }
    }
    break;
  case 's':
    cVar2 = **pp;
    *pp = *pp + 1;
    cVar2 = lower_char(cVar2);
    if (cVar2 == 'p') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x30;
      }
    }
    else if (cVar2 == 'r') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)**pp,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 0x2b;
      }
    }
    else if (cVar2 == 's') {
      cVar2 = **pp;
      *pp = *pp + 1;
      cVar2 = lower_char(cVar2);
      if (cVar2 == 'h') {
        if (__mb_cur_max < 2) {
          uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
        }
        else {
          uVar3 = _isctype((int)**pp,0x107);
        }
        if ((uVar3 == 0) && (**pp != '_')) {
          return 0x2e;
        }
      }
      else if (cVar2 == 'l') {
        if (__mb_cur_max < 2) {
          uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
        }
        else {
          uVar3 = _isctype((int)**pp,0x107);
        }
        if ((uVar3 == 0) && (**pp != '_')) {
          return 0x2f;
        }
      }
    }
    break;
  case 'x':
    if (__mb_cur_max < 2) {
      uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
    }
    else {
      uVar3 = _isctype((int)**pp,0x107);
    }
    if ((uVar3 == 0) && (**pp != '_')) {
      return 0;
    }
    cVar2 = **pp;
    pcVar4 = *pp + 1;
    *pp = pcVar4;
    if (cVar2 == '0') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 4;
      }
    }
    else if (cVar2 == '1') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 6;
      }
    }
    break;
  case 'y':
    if (__mb_cur_max < 2) {
      uVar3 = *(ushort *)(_pctype + **pp * 2) & 0x107;
    }
    else {
      uVar3 = _isctype((int)**pp,0x107);
    }
    if ((uVar3 == 0) && (**pp != '_')) {
      return 1;
    }
    cVar2 = **pp;
    pcVar4 = *pp + 1;
    *pp = pcVar4;
    if (cVar2 == '0') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 5;
      }
    }
    else if (cVar2 == '1') {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + *pcVar4 * 2) & 0x107;
      }
      else {
        uVar3 = _isctype((int)*pcVar4,0x107);
      }
      if ((uVar3 == 0) && (**pp != '_')) {
        return 7;
      }
    }
  }
  *pp = pcVar1;
  return -1;
}


/* ==== amode_immediate @ 00426210 ==== */

int __cdecl amode_immediate(int immclass,void *op)

{
  void *node;
  uint uVar1;
  
  if (*optr != '#') {
    return 0;
  }
  if (immclass == 0) {
    expr_error(s_Immediate_addressing_mode_not_al_004c22f0);
    return -1;
  }
  optr = optr + 1;
  node = (void *)get_imm_expr(immclass);
  if (node == (void *)0x0) {
    return -1;
  }
  *(undefined4 *)((int)op + 0x10) = *(undefined4 *)((int)node + 8);
  uVar1 = *(uint *)((int)node + 0x1c) & 0x70;
  *(uint *)((int)op + 0xc) = uVar1;
  switch(immclass) {
  case 2:
    *(undefined4 *)((int)op + 4) = 10;
    if (0xfff < *(uint *)((int)op + 0x10)) {
      node_free(node);
LAB_004262e9:
      expr_error(s_Immediate_value_too_large_004c22d4);
      return -1;
    }
    break;
  case 3:
    *(undefined4 *)((int)op + 4) = 0xb;
    if (0xff < *(uint *)((int)op + 0x10)) {
      node_free(node);
      goto LAB_004262e9;
    }
    break;
  case 4:
    *(undefined4 *)((int)op + 4) = 0xc;
    if (0x17 < *(uint *)((int)op + 0x10)) {
      node_free(node);
      goto LAB_004262e9;
    }
    break;
  case 5:
    *(undefined4 *)((int)op + 4) = 0xd;
    uVar1 = *(uint *)((int)op + 0x10);
    if ((int)uVar1 < 0) {
      uVar1 = -uVar1;
    }
    if (0x17 < uVar1) goto LAB_004262e9;
    break;
  case 6:
    if (uVar1 != 0x10) {
      if (uVar1 == 0x20) {
        *(undefined4 *)((int)op + 4) = 0xb;
        if (*(uint *)((int)op + 0x10) < 0x100) break;
      }
      else if (*(uint *)((int)op + 0x10) < 0x100) {
        *(undefined4 *)((int)op + 4) = 0xb;
        node_free(node);
        return 1;
      }
    }
  case 1:
    *(undefined4 *)((int)op + 4) = 9;
  }
  node_free(node);
  return 1;
}


/* ==== get_imm_expr @ 00426370 ==== */

int __cdecl get_imm_expr(int immclass)

{
  void *node;
  
  eval_data_word(0x4000008);
  if (node == (void *)0x0) {
    return 0;
  }
  if ((*(uint *)((int)node + 0x1c) & 0x100) == 0) {
    if ((immclass != 1) && (immclass != 6)) {
      node_free(node);
      expr_error(s_Floating_point_value_not_allowed_004c2318);
      return 0;
    }
    *(uint *)((int)node + 0x1c) = *(uint *)((int)node + 0x1c) | 0x101;
    frac_to_word(0x4000008,node);
  }
  else if (((((*(uint *)((int)node + 8) & 0x80000000) != 0) && (immclass != 5)) && (immclass != 1))
          && (immclass != 6)) {
    node_free(node);
    expr_error(s_Negative_immediate_value_not_all_004c233c);
    return 0;
  }
  return (int)node;
}


/* ==== amode_absolute @ 00426410 ==== */

int __cdecl amode_absolute(int absclass,void *op)

{
  void *node;
  uint uVar1;
  bool bVar2;
  bool bVar3;
  
  if (absclass == 0) {
    expr_error(s_Absolute_addressing_mode_not_all_004c2460);
    return -1;
  }
  eval_int_addr(0x4000008);
  if (node == (void *)0x0) {
    return -1;
  }
  *(undefined4 *)((int)op + 0x10) = *(undefined4 *)((int)node + 8);
  uVar1 = *(uint *)((int)node + 0x1c) & 0x70;
  *(uint *)((int)op + 0xc) = uVar1;
  node_free(node);
  switch(absclass) {
  case 1:
    break;
  case 2:
    *(undefined4 *)((int)op + 4) = 0x11;
    if ((0xffbf < *(uint *)((int)op + 0x10)) && (*(uint *)((int)op + 0x10) < 0x10000)) {
      return 1;
    }
    expr_error(s_Short_I_O_absolute_address_too_s_004c2438);
    return -1;
  case 3:
    *(undefined4 *)((int)op + 4) = 0xf;
    bVar2 = *(uint *)((int)op + 0x10) < 0xfff;
    bVar3 = *(uint *)((int)op + 0x10) == 0xfff;
    goto LAB_004264c6;
  case 4:
    *(undefined4 *)((int)op + 4) = 0x10;
    bVar2 = *(uint *)((int)op + 0x10) < 0x3f;
    bVar3 = *(uint *)((int)op + 0x10) == 0x3f;
LAB_004264c6:
    if (bVar2 || bVar3) {
      return 1;
    }
    expr_error(s_Short_absolute_address_too_large_004c2414);
    return -1;
  case 5:
    if (uVar1 != 0x10) {
      if (uVar1 == 0x20) {
        *(undefined4 *)((int)op + 4) = 0xf;
        if (*(uint *)((int)op + 0x10) < 0x1000) {
          return 1;
        }
        *(undefined4 *)((int)op + 4) = 0xe;
        return 1;
      }
      if (*(uint *)((int)op + 0x10) < 0x1000) {
        *(undefined4 *)((int)op + 4) = 0xf;
        return 1;
      }
    }
    break;
  case 6:
    if (uVar1 != 0x10) {
      if (uVar1 == 0x40) {
        uVar1 = *(uint *)((int)op + 0x10);
        *(undefined4 *)((int)op + 4) = 0x11;
        if ((0x3f < uVar1) && (uVar1 < 0x80)) {
          *(uint *)((int)op + 0x10) = uVar1 | 0xffc0;
        }
        if (0xffbf < *(uint *)((int)op + 0x10)) {
          if (*(uint *)((int)op + 0x10) < 0x10000) {
            return 1;
          }
          *(undefined4 *)((int)op + 4) = 0xe;
          return 1;
        }
      }
      else {
        if (uVar1 == 0x20) {
          *(undefined4 *)((int)op + 4) = 0x10;
          if (*(uint *)((int)op + 0x10) < 0x40) {
            return 1;
          }
          *(undefined4 *)((int)op + 4) = 0xe;
          return 1;
        }
        uVar1 = *(uint *)((int)op + 0x10);
        if (uVar1 < 0x40) {
          *(undefined4 *)((int)op + 4) = 0x10;
          return 1;
        }
        if ((0xffbf < uVar1) && (uVar1 < 0x10000)) {
          *(undefined4 *)((int)op + 4) = 0x11;
          return 1;
        }
      }
    }
    break;
  case 7:
    if (uVar1 == 0x10) {
      uVar1 = *(uint *)((int)op + 0x10);
      if (uVar1 < 0x40) {
        *(undefined4 *)((int)op + 4) = 0x10;
        return 1;
      }
      if ((0xffbf < uVar1) && (uVar1 < 0x10000)) {
        *(undefined4 *)((int)op + 4) = 0x11;
        return 1;
      }
      expr_error(s_Long_absolute_address_cannot_be_u_004c23ec);
      return -1;
    }
    if (uVar1 == 0x40) {
      uVar1 = *(uint *)((int)op + 0x10);
      *(undefined4 *)((int)op + 4) = 0x11;
      if ((0x3f < uVar1) && (uVar1 < 0x80)) {
        *(uint *)((int)op + 0x10) = uVar1 | 0xffc0;
      }
      if ((0xffbf < *(uint *)((int)op + 0x10)) && (*(uint *)((int)op + 0x10) < 0x10000)) {
        return 1;
      }
      expr_error(s_Absolute_address_too_small_to_us_004c23c0);
      return -1;
    }
    if (uVar1 == 0x20) {
      *(undefined4 *)((int)op + 4) = 0x10;
      if (*(uint *)((int)op + 0x10) < 0x40) {
        return 1;
      }
      expr_error(s_Absolute_address_too_large_to_us_004c2398);
      return -1;
    }
    uVar1 = *(uint *)((int)op + 0x10);
    if (uVar1 < 0x40) {
      *(undefined4 *)((int)op + 4) = 0x10;
      return 1;
    }
    if ((0xffbf < uVar1) && (uVar1 < 0x10000)) {
      *(undefined4 *)((int)op + 4) = 0x11;
      return 1;
    }
    expr_error(s_Absolute_address_must_be_either_s_004c2364);
    return -1;
  case 8:
    if (uVar1 != 0x10) {
      if (uVar1 == 0x40) {
        uVar1 = *(uint *)((int)op + 0x10);
        *(undefined4 *)((int)op + 4) = 0x11;
        if ((0x3f < uVar1) && (uVar1 < 0x80)) {
          *(uint *)((int)op + 0x10) = uVar1 | 0xffc0;
        }
        if (0xffbf < *(uint *)((int)op + 0x10)) {
          if (*(uint *)((int)op + 0x10) < 0x10000) {
            return 1;
          }
          *(undefined4 *)((int)op + 4) = 0xe;
          return 1;
        }
      }
      else if (((uVar1 != 0x20) && (0xffbf < *(uint *)((int)op + 0x10))) &&
              (*(uint *)((int)op + 0x10) < 0x10000)) {
        *(undefined4 *)((int)op + 4) = 0x11;
        return 1;
      }
    }
    break;
  case 9:
    if (uVar1 != 0x10) {
      if (uVar1 == 0x20) {
        *(undefined4 *)((int)op + 4) = 0x10;
        if (*(uint *)((int)op + 0x10) < 0x40) {
          return 1;
        }
        *(undefined4 *)((int)op + 4) = 0xe;
        return 1;
      }
      if ((uVar1 != 0x40) && (*(uint *)((int)op + 0x10) < 0x40)) {
        *(undefined4 *)((int)op + 4) = 0x10;
        return 1;
      }
    }
    break;
  default:
    goto switchD_0042646f_default;
  }
  *(undefined4 *)((int)op + 4) = 0xe;
switchD_0042646f_default:
  return 1;
}


/* ==== amode_register @ 004267d0 ==== */

int __cdecl amode_register(int regclass,void *op)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = match_register_name((char **)&optr);
  if (iVar1 == -1) {
    return 0;
  }
  bVar2 = false;
  switch(regclass) {
  case 0:
    break;
  case 1:
    if ((iVar1 != 2) && (iVar1 != 3)) {
      bVar2 = false;
      goto switchD_004267f4_default;
    }
    goto LAB_00426a66;
  case 2:
    if ((iVar1 != 5) && (iVar1 != 7)) {
      bVar2 = false;
      goto switchD_004267f4_default;
    }
    goto LAB_00426a66;
  case 3:
    if (iVar1 != 4) {
      bVar2 = iVar1 == 6;
LAB_00426847:
      if (((!bVar2) && (iVar1 != 2)) && (iVar1 != 3)) {
        bVar2 = false;
        goto switchD_004267f4_default;
      }
    }
    goto LAB_00426a66;
  case 4:
    if (iVar1 != 5) {
      bVar2 = iVar1 == 7;
      goto LAB_00426847;
    }
    goto LAB_00426a66;
  case 5:
    if ((((iVar1 != 0) && (iVar1 != 1)) && (iVar1 != 2)) && (iVar1 != 3)) {
      if (iVar1 < 0x26) break;
      if (0x29 < iVar1) {
        bVar2 = false;
        goto switchD_004267f4_default;
      }
    }
    goto LAB_00426a66;
  case 6:
    if ((iVar1 < 2) || (0x25 < iVar1)) goto switchD_004267f4_caseD_7;
    goto LAB_00426a66;
  case 7:
switchD_004267f4_caseD_7:
    if ((0x29 < iVar1) && (iVar1 < 0x31)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 8:
    if ((0x1d < iVar1) && (iVar1 < 0x20)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 9:
    if ((1 < iVar1) && (iVar1 < 8)) goto LAB_00426a66;
    if ((0xd < iVar1) && (iVar1 < 0x1e)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 10:
    if ((iVar1 != 0) && (iVar1 != 1)) {
      bVar2 = false;
      goto switchD_004267f4_default;
    }
    goto LAB_00426a66;
  case 0xb:
    if ((3 < iVar1) && (iVar1 < 8)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0xc:
    if ((iVar1 != 0) && (iVar1 != 1)) {
      if (iVar1 < 4) break;
      if (7 < iVar1) {
        bVar2 = false;
        goto switchD_004267f4_default;
      }
    }
    goto LAB_00426a66;
  case 0xd:
    bVar2 = iVar1 == 2;
    goto switchD_004267f4_default;
  case 0xe:
    bVar2 = iVar1 == 3;
    goto switchD_004267f4_default;
  case 0xf:
    if ((1 < iVar1) && (iVar1 < 8)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0x10:
    if ((0xd < iVar1) && (iVar1 < 0x16)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0x11:
    if ((1 < iVar1) && (iVar1 < 0x26)) goto LAB_00426a66;
    if ((0x29 < iVar1) && (iVar1 < 0x31)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0x12:
    if ((-1 < iVar1) && (iVar1 < 0x31)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0x13:
    if (((iVar1 != 0x31) && (iVar1 != 0x32)) && (iVar1 != 0x2a)) {
      bVar2 = false;
      goto switchD_004267f4_default;
    }
    goto LAB_00426a66;
  case 0x14:
    if ((0xd < iVar1) && (iVar1 < 0x1e)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0x15:
    if ((-1 < iVar1) && (iVar1 < 8)) {
      bVar2 = true;
      goto switchD_004267f4_default;
    }
    break;
  case 0x16:
    if ((iVar1 != 4) && ((iVar1 != 2 && (iVar1 != 3)))) {
      bVar2 = false;
      goto switchD_004267f4_default;
    }
LAB_00426a66:
    bVar2 = true;
    goto switchD_004267f4_default;
  case 0x17:
    if (((iVar1 == 4) || (iVar1 == 5)) || ((iVar1 == 7 || ((iVar1 == 2 || (iVar1 == 3))))))
    goto LAB_00426a66;
    break;
  case 0x18:
    if ((((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 10)) || (iVar1 == 0xb)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (iVar1 == 10) {
      iVar1 = 2;
    }
    else if (iVar1 == 0xb) {
      iVar1 = 3;
    }
  default:
    goto switchD_004267f4_default;
  }
  bVar2 = false;
switchD_004267f4_default:
  if (bVar2) {
    *(int *)((int)op + 0x14) = iVar1;
    *(undefined4 *)((int)op + 4) = 1;
    return 1;
  }
  if (regclass != 0) {
    expr_error(s_Invalid_register_specified_004c2488);
    return -1;
  }
  expr_error(s_Register_direct_addressing_not_a_004c24a4);
  return -1;
}


/* ==== note_reg_direct @ 00426b50 ==== */

int __cdecl note_reg_direct(ulong flags,int regclass,int reg)

{
  int iVar1;
  
  if ((flags & 2) != 0) {
    iVar1 = check_dup_dest(regclass,reg);
    if (iVar1 != 0) {
      return 0;
    }
  }
  return 1;
}


/* ==== check_dup_dest @ 00426b80 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl check_dup_dest(int regclass,int reg)

{
  uint uVar1;
  
  switch(reg) {
  case 2:
    uVar1 = (-(uint)(regclass != 0x18) & 5) + 2;
    break;
  case 3:
    uVar1 = (-(uint)(regclass != 0x18) & 0x50) + 0x20;
    break;
  default:
    goto switchD_00426b98_caseD_4;
  case 8:
    uVar1 = 1;
    break;
  case 9:
    uVar1 = 0x10;
    break;
  case 10:
    uVar1 = 2;
    break;
  case 0xb:
    uVar1 = 0x20;
    break;
  case 0xc:
    uVar1 = 4;
    break;
  case 0xd:
    uVar1 = 0x40;
    break;
  case 0x26:
  case 0x27:
    uVar1 = 0x66;
    break;
  case 0x28:
    uVar1 = 3;
    break;
  case 0x29:
    uVar1 = 0x30;
  }
  if ((_asm_flags & uVar1) != 0) {
    expr_error(s_Duplicate_destination_register_n_004c24cc);
    return 1;
  }
  _asm_flags = _asm_flags | uVar1;
switchD_00426b98_caseD_4:
  return 0;
}


/* ==== chk_no_yfield @ 00426c90 ==== */

int chk_no_yfield(void)

{
  undefined4 uVar1;
  
  uVar1 = optr;
  if (*asm_op3_field != '\0') {
    optr = asm_op3_field;
    expr_error(s_Too_many_fields_specified_for_in_004c1f60);
    optr = (char *)uVar1;
    return 0;
  }
  return 1;
}


/* ==== xy_imm_short @ 00426cd0 ==== */

int __cdecl xy_imm_short(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  
  iVar1 = parse_operand(2,xd,0x12,0,0,0);
  if (iVar1 != 0) {
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 6:
      if (*asm_op3_field == '\0') {
LAB_00426dc6:
        enc_pm_imm(insn,xs,xd);
        return 1;
      }
      optr = asm_op3_field;
      iVar1 = parse_operand(1,ys,1,0,0,0);
      if ((iVar1 != 0) && (iVar1 = parse_operand(0,yd,2,0,0,0), iVar1 != 0)) {
        *(undefined4 *)((int)xs + 4) = 9;
        enc_pm_xr_w(insn,xs,xd,ys,yd);
        return 1;
      }
      break;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) goto LAB_00426dc6;
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_imm(insn,xs,xd);
        return 1;
      }
      break;
    default:
      expr_error(s_Illegal_X_field_destination_regi_004c24f8);
    }
  }
  return 0;
}


/* ==== xy_imm_long @ 00426e50 ==== */

int __cdecl xy_imm_long(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  
  iVar1 = parse_operand(2,xd,0x12,0,0,0);
  if (iVar1 != 0) {
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 6:
      if (*asm_op3_field == '\0') {
        enc_pm_x_ea_w(insn,xs,xd);
        return 1;
      }
      optr = asm_op3_field;
      iVar1 = parse_operand(1,ys,1,0,0,0);
      if ((iVar1 != 0) && (iVar1 = parse_operand(0,yd,2,0,0,0), iVar1 != 0)) {
        enc_pm_xr_w(insn,xs,xd,ys,yd);
        return 1;
      }
      break;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_pm_x_ea_w(insn,xs,xd);
        return 1;
      }
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_ea2_w(insn,xs,xd);
        return 1;
      }
      break;
    default:
      expr_error(s_Illegal_X_field_destination_regi_004c24f8);
      break;
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_ea_w(insn,xs,xd);
        return 1;
      }
    }
  }
  return 0;
}


/* ==== xy_lreg @ 00427020 ==== */

int __cdecl xy_lreg(void *insn,void *xs,void *xd)

{
  int iVar1;
  
  iVar1 = parse_space(xd,3);
  if (iVar1 != 0) {
    iVar1 = parse_operand(0,xd,0,1,9,0);
    if (iVar1 == 0) {
      *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 4)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 0xe:
      iVar1 = chk_no_yfield();
      if (iVar1 == 0) {
        *(undefined4 *)insn = 2;
        return 0;
      }
      enc_pm_l_ea(insn,xs,xd);
      return 1;
    case 0x10:
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_pm_l_abs(insn,xs,xd);
        return 1;
      }
    }
  }
  return 0;
}


/* ==== xy_acc @ 00427100 ==== */

int __cdecl xy_acc(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  
  iVar1 = parse_space(xd,6);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)xd != 0) {
    iVar1 = xdst_mem(pmclass,insn,xs,xd,ys,yd);
    return iVar1;
  }
  iVar1 = parse_operand(2,xd,0x12,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  switch(*(undefined4 *)((int)xd + 0x14)) {
  case 2:
  case 3:
  case 5:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    iVar1 = chk_no_yfield();
    if (iVar1 == 0) {
      return 0;
    }
    enc_pm_reg(insn,xs,xd);
    return 1;
  case 4:
  case 6:
    break;
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    if (pmclass != 1) {
      expr_error(s_Instruction_does_not_allow_data_m_004c2528);
      return 0;
    }
    iVar1 = chk_no_yfield();
    if (iVar1 == 0) {
      return 0;
    }
    enc_movec_reg_w(insn,xs,xd);
    return 1;
  default:
    expr_error(s_Illegal_X_field_destination_regi_004c24f8);
    return 0;
  }
  if (*asm_op3_field == '\0') {
    enc_pm_reg(insn,xs,xd);
    return 1;
  }
  optr = asm_op3_field;
  iVar1 = parse_space(ys,8);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)ys == 0) {
    iVar1 = parse_operand(1,ys,4,0,0,1);
    if (iVar1 == 0) {
      *(undefined4 *)insn = 2;
      return 0;
    }
    if (*(int *)((int)ys + 4) != 9) {
      iVar1 = parse_space(yd,2);
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = parse_operand(0,yd,0,1,1,0);
      if (iVar1 == 0) {
        *(undefined4 *)insn = 2;
        return 0;
      }
      enc_pm_ry(insn,xs,xd,ys,yd);
      return 1;
    }
    iVar1 = parse_operand(2,yd,4,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  else {
    iVar1 = parse_operand(1,ys,0,1,1,0);
    if (iVar1 == 0) {
      *(undefined4 *)insn = 2;
      return 0;
    }
    iVar1 = parse_operand(2,yd,4,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  enc_pm_ry_w(insn,xs,xd,ys,yd);
  return 1;
}


/* ==== xy_xreg @ 004273b0 ==== */

int __cdecl xy_xreg(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  
  iVar1 = parse_space(xd,9);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)xd == 0) {
    iVar1 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = chk_no_yfield();
      if (iVar1 == 0) {
        return 0;
      }
      enc_pm_reg(insn,xs,xd);
      return 1;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      goto switchD_004273fb_caseD_1e;
    default:
      expr_error(s_Illegal_X_field_destination_regi_004c24f8);
      return 0;
    }
  }
  iVar1 = xdst_mem(pmclass,insn,xs,xd,ys,yd);
  return iVar1;
switchD_004273fb_caseD_1e:
  if (pmclass != 1) {
    expr_error(s_Instruction_does_not_allow_data_m_004c2528);
    return 0;
  }
  iVar1 = chk_no_yfield();
  if (iVar1 == 0) {
    return 0;
  }
  enc_movec_reg_w(insn,xs,xd);
  return 1;
}


/* ==== xdst_mem @ 004274e0 ==== */

int __cdecl xdst_mem(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)xd;
  if (iVar2 == 1) {
    iVar2 = parse_operand(0,xd,0,1,9,0);
    if (iVar2 != 0) {
      switch(*(undefined4 *)((int)xd + 4)) {
      case 2:
      case 3:
      case 4:
      case 5:
        if (*asm_op3_field == '\0') {
LAB_0042785e:
          enc_pm_x_ea(insn,xs,xd);
          return 1;
        }
        optr = asm_op3_field;
        iVar2 = parse_space(ys,8);
        if (iVar2 != 0) {
          if (*(int *)ys == 0) {
            iVar2 = parse_operand(1,ys,0x17,0,0,0);
            if (iVar2 != 0) {
              switch(*(undefined4 *)((int)ys + 0x14)) {
              case 2:
              case 3:
                iVar2 = parse_space(yd,8);
                if (iVar2 != 0) {
                  if (*(int *)yd == 0) {
                    iVar2 = parse_operand(0,yd,2,0,0,0);
                    if (iVar2 != 0) {
                      enc_pm_xr(insn,xs,xd,ys,yd);
                      return 1;
                    }
                  }
                  else {
                    iVar2 = parse_operand(0,yd,0,2,0,0);
                    if ((iVar2 != 0) &&
                       (iVar2 = chk_xy_regs(*(int *)((int)xd + 0x14),*(int *)((int)yd + 0x14)),
                       iVar2 == 0)) {
                      enc_pm_xy(insn,xs,xd,ys,yd);
                      return 1;
                    }
                  }
                }
                break;
              case 4:
                iVar2 = *(int *)((int)xs + 0x14);
                if ((iVar2 != 2) && (iVar2 != 3)) {
                  expr_error(s_Invalid_addressing_mode_004c20d0);
                  return 0;
                }
                iVar2 = parse_operand(2,yd,(iVar2 != 2) + 0xd,0,0,0);
                if (iVar2 != 0) {
                  enc_pm_xr2(insn,xs,xd);
                  return 1;
                }
                break;
              case 5:
              case 7:
                iVar2 = parse_space(yd,2);
                if (((iVar2 != 0) && (iVar2 = parse_operand(0,yd,0,2,0,0), iVar2 != 0)) &&
                   (iVar2 = chk_xy_regs(*(int *)((int)xd + 0x14),*(int *)((int)yd + 0x14)),
                   iVar2 == 0)) {
                  enc_pm_xy(insn,xs,xd,ys,yd);
                  return 1;
                }
                break;
              default:
                goto switchD_00427a81_caseD_9;
              }
            }
          }
          else {
            iVar2 = parse_operand(1,ys,0,2,0,0);
            if (((iVar2 != 0) &&
                (iVar2 = chk_xy_regs(*(int *)((int)xd + 0x14),*(int *)((int)ys + 0x14)), iVar2 == 0)
                ) && (iVar2 = parse_operand(2,yd,4,0,0,0), iVar2 != 0)) {
              enc_pm_xy_wy(insn,xs,xd,ys,yd);
              return 1;
            }
          }
        }
        break;
      case 6:
      case 7:
      case 8:
        if (*asm_op3_field == '\0') {
          enc_pm_x_ea(insn,xs,xd);
          return 1;
        }
        optr = asm_op3_field;
        iVar2 = parse_operand(1,ys,0x16,0,0,0);
        if (iVar2 != 0) {
          if (*(int *)((int)ys + 0x14) == 4) {
            iVar2 = (*(int *)((int)xs + 0x14) != 2) + 0xd;
          }
          else {
            iVar2 = 2;
          }
          iVar2 = parse_operand(0,yd,iVar2,0,0,0);
          if (iVar2 != 0) {
            if (*(int *)((int)ys + 0x14) != 4) {
              enc_pm_xr(insn,xs,xd,ys,yd);
              return 1;
            }
            if ((*(int *)((int)xs + 0x14) != 2) && (*(int *)((int)xs + 0x14) != 3)) {
              expr_error(s_Invalid_addressing_mode_004c20d0);
              return 0;
            }
            enc_pm_xr2(insn,xs,xd);
            return 1;
          }
        }
        break;
      default:
        expr_error(s_xdst_mem_failure_004c2584);
        return 1;
      case 0xe:
        if (*asm_op3_field == '\0') goto LAB_0042785e;
        optr = asm_op3_field;
        iVar2 = parse_operand(1,ys,1,0,0,0);
        if ((iVar2 != 0) && (iVar2 = parse_operand(0,yd,2,0,0,0), iVar2 != 0)) {
          enc_pm_xr(insn,xs,xd,ys,yd);
          return 1;
        }
        break;
      case 0x10:
        if (*asm_op3_field == '\0') {
          enc_pm_x_abs(insn,xs,xd);
          return 1;
        }
        *(undefined4 *)((int)xd + 4) = 0xe;
        optr = asm_op3_field;
        iVar2 = parse_operand(1,ys,1,0,0,0);
        if ((iVar2 != 0) && (iVar2 = parse_operand(0,yd,2,0,0,0), iVar2 != 0)) {
          enc_pm_xr(insn,xs,xd,ys,yd);
          return 1;
        }
      }
      return 0;
    }
  }
  else {
    if (iVar2 == 2) {
      iVar2 = parse_operand(0,xd,0,1,9,0);
      if (iVar2 == 0) {
        *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
        return 0;
      }
      iVar2 = chk_no_yfield();
      uVar1 = asm_op2_field;
      if (iVar2 != 0) {
        asm_op2_field = &empty_str;
        asm_op3_field = (char *)uVar1;
        if (*(int *)((int)xd + 4) != 0x10) {
          enc_pm_y_ea(insn,xs,xd);
          return 1;
        }
        enc_pm_y_abs(insn,xs,xd);
        return 1;
      }
      *(undefined4 *)insn = 2;
      return 0;
    }
    if (iVar2 != 4) {
      if (iVar2 != 8) {
        expr_error(s_Illegal_X_field_destination_spec_004c255c);
        return 0;
      }
      iVar2 = chk_move_class(pmclass,(long)insn,xs,xd);
      return iVar2;
    }
    iVar2 = parse_operand(0,xd,0,1,9,0);
    if (iVar2 != 0) {
      switch(*(undefined4 *)((int)xd + 4)) {
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 0xe:
        iVar2 = chk_no_yfield();
        if (iVar2 != 0) {
          enc_pm_l_ea(insn,xs,xd);
          return 1;
        }
        *(undefined4 *)insn = 2;
        return 0;
      case 0x10:
        iVar2 = chk_no_yfield();
        if (iVar2 == 0) {
          return 0;
        }
        enc_pm_l_abs(insn,xs,xd);
      }
switchD_00427a81_caseD_9:
      return 1;
    }
  }
  *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
  return 0;
}


/* ==== chk_move_class @ 00427b80 ==== */

int __cdecl chk_move_class(int pmclass,long mask,void *insn)

{
  int iVar1;
  void *in_stack_00000010;
  
  if (pmclass != 1) {
    expr_error(s_Instruction_does_not_allow_data_m_004c2528);
    return 0;
  }
  iVar1 = parse_operand(0,in_stack_00000010,0,1,9,0);
  if (iVar1 == 0) {
    *(uint *)mask = 2 - (uint)((*(uint *)((int)in_stack_00000010 + 0xc) & 0x20) != 0);
    return 0;
  }
  iVar1 = chk_no_yfield();
  if (iVar1 == 0) {
    *(undefined4 *)mask = 2;
    return 0;
  }
  if (*(int *)((int)in_stack_00000010 + 4) == 0x10) {
    enc_movem_abs((void *)mask,insn,in_stack_00000010);
    return 1;
  }
  enc_movem_ea((void *)mask,insn,in_stack_00000010);
  return 1;
}


/* ==== xy_reg @ 00427c20 ==== */

int __cdecl xy_reg(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = parse_space(xd,9);
  if (iVar2 != 0) {
    iVar2 = *(int *)xd;
    if (iVar2 == 0) {
      iVar2 = parse_operand(2,xd,0x12,0,0,0);
      if (iVar2 != 0) {
        switch(*(undefined4 *)((int)xd + 0x14)) {
        case 2:
        case 3:
          if (*asm_op3_field == '\0') {
LAB_00427d6b:
            enc_pm_reg(insn,xs,xd);
            return 1;
          }
          if (*(int *)((int)xs + 0x14) != 5) {
            expr_error(s_Invalid_addressing_mode_004c20d0);
            return 0;
          }
          optr = asm_op3_field;
          iVar2 = parse_operand(1,ys,(*(int *)((int)xd + 0x14) != 2) + 0xd,0,0,0);
          if (((iVar2 != 0) && (iVar2 = parse_space(yd,2), iVar2 != 0)) &&
             (iVar2 = parse_operand(0,yd,0,1,0,0), iVar2 != 0)) {
            enc_pm_xr2(insn,ys,yd);
            return 1;
          }
          break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1d:
          iVar2 = chk_no_yfield();
          if (iVar2 != 0) goto LAB_00427d6b;
          break;
        case 0x1e:
        case 0x1f:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x30:
          if (pmclass != 1) {
            expr_error(s_Instruction_does_not_allow_data_m_004c2528);
            return 0;
          }
          iVar2 = chk_no_yfield();
          if (iVar2 != 0) {
            enc_movec_reg_w(insn,xs,xd);
            return 1;
          }
          break;
        default:
          expr_error(s_Illegal_X_field_destination_regi_004c24f8);
          return 0;
        }
      }
    }
    else {
      if (iVar2 == 1) {
        iVar2 = parse_operand(0,xd,0,1,9,0);
        if (iVar2 == 0) {
          *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
          return 0;
        }
        iVar2 = chk_no_yfield();
        if (iVar2 == 0) {
          *(undefined4 *)insn = 2;
          return 0;
        }
        if (*(int *)((int)xd + 4) == 0x10) {
          enc_pm_x_abs(insn,xs,xd);
          return 1;
        }
        enc_pm_x_ea(insn,xs,xd);
        return 1;
      }
      if (iVar2 == 2) {
        iVar2 = parse_operand(0,xd,0,1,9,0);
        if (iVar2 == 0) {
          *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
          return 0;
        }
        iVar2 = chk_no_yfield();
        uVar1 = asm_op2_field;
        if (iVar2 == 0) {
          *(undefined4 *)insn = 2;
          return 0;
        }
        asm_op2_field = &empty_str;
        asm_op3_field = (char *)uVar1;
        if (*(int *)((int)xd + 4) == 0x10) {
          enc_pm_y_abs(insn,xs,xd);
          return 1;
        }
        enc_pm_y_ea(insn,xs,xd);
        return 1;
      }
      if (iVar2 == 8) {
        iVar2 = chk_move_class(pmclass,(long)insn,xs,xd);
        return iVar2;
      }
      expr_error(s_Illegal_X_field_destination_spec_004c255c);
    }
  }
  return 0;
}


/* ==== xy_mreg @ 00427f40 ==== */

int __cdecl xy_mreg(int pmclass,void *insn,void *xs,void *xd)

{
  undefined1 *puVar1;
  int iVar2;
  
  if (pmclass != 1) {
    expr_error(s_Instruction_does_not_allow_data_m_004c2528);
    return 0;
  }
  iVar2 = chk_no_yfield();
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = parse_space(xd,9);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = *(int *)xd;
  if (iVar2 == 0) {
    iVar2 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    enc_movec_reg(insn,xs,xd);
    return 1;
  }
  if ((iVar2 != 1) && (iVar2 != 2)) {
    if (iVar2 == 8) {
      iVar2 = chk_move_class(1,(long)insn,xs,xd);
      return iVar2;
    }
    expr_error(s_Illegal_X_field_destination_spec_004c255c);
    return 0;
  }
  iVar2 = parse_operand(0,xd,0,1,9,0);
  if (iVar2 == 0) {
    *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
    return 0;
  }
  if (*(int *)((int)xd + 4) == 0x10) {
    enc_movec_abs(insn,xs,xd);
  }
  else {
    enc_movec_ea2(insn,xs,xd);
  }
  puVar1 = asm_op2_field;
  if (*(int *)xd == 2) {
    asm_op2_field = &empty_str;
    asm_op3_field = puVar1;
  }
  return 1;
}


/* ==== xy_ctlreg @ 00428070 ==== */

int __cdecl xy_ctlreg(int pmclass,void *insn,void *xs,void *xd)

{
  undefined1 *puVar1;
  int iVar2;
  
  if (pmclass != 1) {
    expr_error(s_Instruction_does_not_allow_data_m_004c2528);
    return 0;
  }
  iVar2 = chk_no_yfield();
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = parse_space(xd,9);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = *(int *)xd;
  if (iVar2 == 0) {
    iVar2 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar2 == 0) {
      return 0;
    }
    if ((*(int *)((int)xs + 0x14) == 0x2e) && (*(int *)((int)xd + 0x14) == 0x2e)) {
      expr_error(s_SSH_cannot_be_both_source_and_de_004c2598);
      return 0;
    }
    enc_movec_reg(insn,xs,xd);
    return 1;
  }
  if ((iVar2 == 1) || (iVar2 == 2)) {
    iVar2 = parse_operand(0,xd,0,1,9,0);
    if (iVar2 == 0) {
      *(uint *)insn = 2 - (uint)((*(uint *)((int)xd + 0xc) & 0x20) != 0);
      return 0;
    }
    if (*(int *)((int)xd + 4) == 0x10) {
      enc_movec_abs(insn,xs,xd);
    }
    else {
      enc_movec_ea(insn,xs,xd);
    }
    puVar1 = asm_op2_field;
    if (*(int *)xd == 2) {
      asm_op2_field = &empty_str;
      asm_op3_field = puVar1;
    }
  }
  else {
    if (iVar2 != 8) {
      expr_error(s_Illegal_X_field_destination_spec_004c255c);
      return 0;
    }
    iVar2 = chk_move_class(1,(long)insn,xs,xd);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}


/* ==== xy_xsrc @ 004281c0 ==== */

int __cdecl xy_xsrc(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  void *unaff_EDI;
  
  switch(*(undefined4 *)((int)xs + 4)) {
  case 2:
  case 3:
  case 4:
  case 5:
    iVar1 = parse_space(xd,0);
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)xd != 0) {
      return 1;
    }
    iVar1 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 6:
      iVar1 = xy_xsrc_acc((int)insn,xs,xd,ys,yd,unaff_EDI);
      if (iVar1 != 0) {
        return 1;
      }
      return 0;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_pm_x_ea_w(insn,xs,xd);
        return 1;
      }
      return 0;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_ea2_w(insn,xs,xd);
        return 1;
      }
      return 0;
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_ea_w(insn,xs,xd);
        return 1;
      }
      return 0;
    }
    break;
  case 6:
  case 7:
  case 8:
  case 0xe:
    iVar1 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 6:
      if (*asm_op3_field == '\0') {
        enc_pm_x_ea_w(insn,xs,xd);
        return 1;
      }
      optr = asm_op3_field;
      iVar1 = parse_operand(1,ys,1,0,0,0);
      if (iVar1 != 0) {
        iVar1 = parse_operand(0,yd,2,0,0,0);
        if (iVar1 != 0) {
          enc_pm_xr_w(insn,xs,xd,ys,yd);
          return 1;
        }
        return 0;
      }
      return 0;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_pm_x_ea_w(insn,xs,xd);
        return 1;
      }
      return 0;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_ea2_w(insn,xs,xd);
        return 1;
      }
      return 0;
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_ea_w(insn,xs,xd);
        return 1;
      }
      return 0;
    }
    break;
  default:
    return 1;
  case 0x10:
    iVar1 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 6:
      if (*asm_op3_field == '\0') {
        enc_pm_x_abs_w(insn,xs,xd);
        return 1;
      }
      optr = asm_op3_field;
      iVar1 = parse_operand(1,ys,1,0,0,0);
      if (iVar1 != 0) {
        iVar1 = parse_operand(0,yd,2,0,0,0);
        if (iVar1 != 0) {
          *(undefined4 *)((int)xs + 4) = 0xe;
          enc_pm_xr_w(insn,xs,xd,ys,yd);
          return 1;
        }
        return 0;
      }
      return 0;
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_pm_x_abs_w(insn,xs,xd);
        return 1;
      }
      return 0;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      iVar1 = chk_no_yfield();
      if (iVar1 != 0) {
        enc_movec_abs_w(insn,xs,xd);
        return 1;
      }
      return 0;
    }
  }
  expr_error(s_Illegal_X_field_destination_regi_004c24f8);
  return 0;
}


/* ==== xy_xsrc_acc @ 004286e0 ==== */

int __cdecl xy_xsrc_acc(int pmclass,void *insn,void *xs,void *xd,void *ys,void *yd)

{
  int iVar1;
  
  if (*asm_op3_field == '\0') {
    enc_pm_x_ea_w((void *)pmclass,insn,xs);
    return 1;
  }
  optr = asm_op3_field;
  iVar1 = parse_space(xd,8);
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)xd == 0) {
    iVar1 = parse_operand(1,xd,4,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
      iVar1 = parse_space(ys,8);
      if (iVar1 == 0) {
        return 0;
      }
      if (*(int *)ys == 0) {
        iVar1 = parse_operand(0,ys,2,0,0,0);
        if (iVar1 == 0) {
          return 0;
        }
        enc_pm_xr_w((void *)pmclass,insn,xs,xd,ys);
        return 1;
      }
      iVar1 = parse_operand(0,ys,0,2,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = chk_xy_regs(*(int *)((int)insn + 0x14),*(int *)((int)ys + 0x14));
      if (iVar1 != 0) {
        return 0;
      }
      enc_pm_xy_wx((void *)pmclass,insn,xs,xd,ys);
      return 1;
    case 5:
    case 7:
      iVar1 = parse_space(ys,2);
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = parse_operand(0,ys,0,2,0,0);
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = chk_xy_regs(*(int *)((int)insn + 0x14),*(int *)((int)ys + 0x14));
      if (iVar1 != 0) {
        return 0;
      }
      enc_pm_xy_wx((void *)pmclass,insn,xs,xd,ys);
      return 1;
    }
  }
  else {
    iVar1 = parse_operand(1,xd,0,2,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    iVar1 = chk_xy_regs(*(int *)((int)insn + 0x14),*(int *)((int)xd + 0x14));
    if (iVar1 != 0) {
      return 0;
    }
    iVar1 = parse_operand(2,ys,4,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    enc_pm_xy_wxy((void *)pmclass,insn,xs,xd,ys);
  }
  return 1;
}


/* ==== xy_ysrc @ 00428910 ==== */

int __cdecl xy_ysrc(int pmclass,void *insn,void *xs,void *xd)

{
  int iVar1;
  
  iVar1 = chk_no_yfield();
  if (iVar1 == 0) {
    return 0;
  }
  asm_op3_field = asm_op2_field;
  asm_op2_field = &empty_str;
  switch(*(undefined4 *)((int)xs + 4)) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 0xe:
    iVar1 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      enc_pm_y_ea_w(insn,xs,xd);
      return 1;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      enc_movec_ea2_w(insn,xs,xd);
      return 1;
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      enc_movec_ea_w(insn,xs,xd);
      return 1;
    }
    break;
  default:
    return 1;
  case 0x10:
    iVar1 = parse_operand(2,xd,0x12,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      enc_pm_y_abs_w(insn,xs,xd);
      return 1;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      if (pmclass != 1) {
        expr_error(s_Instruction_does_not_allow_data_m_004c2528);
        return 0;
      }
      enc_movec_abs_w(insn,xs,xd);
      return 1;
    }
  }
  expr_error(s_Illegal_X_field_destination_regi_004c24f8);
  return 0;
}


/* ==== xy_lsrc @ 00428b40 ==== */

int __cdecl xy_lsrc(void *insn,void *xs,void *xd)

{
  int iVar1;
  
  iVar1 = chk_no_yfield();
  if (iVar1 == 0) {
    return 0;
  }
  if (*(int *)((int)xs + 4) == 0x10) {
    iVar1 = parse_operand(2,xd,5,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    enc_pm_l_abs_w(insn,xs,xd);
    return 1;
  }
  iVar1 = parse_operand(2,xd,5,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  enc_pm_l_ea_w(insn,xs,xd);
  return 1;
}


/* ==== xy_psrc @ 00428bc0 ==== */

int __cdecl xy_psrc(int pmclass,void *insn,void *xs,void *xd)

{
  int iVar1;
  
  iVar1 = chk_no_yfield();
  if (iVar1 != 0) {
    switch(*(undefined4 *)((int)xs + 4)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 0xe:
    case 0x10:
      goto switchD_00428be9_caseD_2;
    default:
      return 1;
    }
  }
  return 0;
switchD_00428be9_caseD_2:
  iVar1 = parse_operand(2,xd,0x12,0,0,0);
  if (iVar1 != 0) {
    switch(*(undefined4 *)((int)xd + 0x14)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
      goto switchD_00428c21_caseD_2;
    default:
      expr_error(s_Illegal_X_field_destination_regi_004c24f8);
      return 0;
    }
  }
  return 0;
switchD_00428c21_caseD_2:
  if (pmclass != 1) {
    expr_error(s_Instruction_does_not_allow_data_m_004c2528);
    return 0;
  }
  if (*(int *)((int)xs + 4) == 0x10) {
    enc_movem_abs_w(insn,xs,xd);
    return 1;
  }
  enc_movem_ea_w(insn,xs,xd);
  return 1;
}


/* ==== chk_xy_regs @ 00428cf0 ==== */

int __cdecl chk_xy_regs(int xreg,int yreg)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  switch(xreg) {
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
    if (yreg < 0xe) {
      return 0;
    }
    bVar3 = SBORROW4(yreg,0x11);
    iVar1 = yreg + -0x11;
    bVar2 = yreg == 0x11;
    break;
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
    if (yreg < 0x12) {
      return 0;
    }
    bVar3 = SBORROW4(yreg,0x15);
    iVar1 = yreg + -0x15;
    bVar2 = yreg == 0x15;
    break;
  default:
    goto switchD_00428d04_default;
  }
  if (bVar2 || bVar3 != iVar1 < 0) {
    expr_error(s_Invalid_XY_address_register_spec_004c25cc);
    return 1;
  }
switchD_00428d04_default:
  return 0;
}


/* ==== canon_xy_fields @ 00428d60 ==== */

int canon_xy_fields(void)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  
  cVar2 = *asm_op2_field;
  pcVar3 = asm_op2_field;
  while (cVar2 != '\0') {
    if (((cVar2 == 'Y') || (cVar2 == 'y')) &&
       (pcVar1 = pcVar3 + 1, pcVar3 = pcVar3 + 1, *pcVar1 == ':')) goto LAB_00428daa;
    pcVar1 = pcVar3 + 1;
    pcVar3 = pcVar3 + 1;
    cVar2 = *pcVar1;
  }
  cVar2 = *asm_op3_field;
  pcVar3 = asm_op3_field;
  if (cVar2 == '\0') {
    return 0;
  }
  while (((cVar2 != 'X' && (cVar2 != 'x')) || (pcVar3[1] != ':'))) {
    cVar2 = pcVar3[1];
    pcVar3 = pcVar3 + 1;
    if (cVar2 == '\0') {
      return 0;
    }
  }
LAB_00428daa:
  swap_op2_op3();
  return 1;
}


/* ==== swap_op2_op3 @ 00428dc0 ==== */

void swap_op2_op3(void)

{
  undefined4 uVar1;
  
  uVar1 = asm_op2_field;
  asm_op2_field = asm_op3_field;
  asm_op3_field = uVar1;
  return;
}


/* ==== asm_clear_flags @ 00428de0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void asm_clear_flags(void)

{
  _asm_flags = 0;
  return;
}


/* ==== p_noarg @ 00428df0 ==== */

int p_noarg(void)

{
  asm_op3_field = asm_op2_field;
  optr = asm_op1_field;
  asm_op2_field = asm_op1_field;
  asm_op1_field = &empty_str;
  return 1;
}


/* ==== p_rts @ 00428e20 ==== */

int p_rts(void)

{
  asm_op3_field = asm_op2_field;
  optr = asm_op1_field;
  asm_op2_field = asm_op1_field;
  asm_op1_field = &empty_str;
  return 1;
}


/* ==== p_andi @ 00428e50 ==== */

int __cdecl p_andi(void *insn)

{
  int iVar1;
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  if (*optr != '#') {
    expr_error(s_Immediate_operand_required_004c25f8);
    return 0;
  }
  iVar1 = parse_operand(1,local_18,0,0,0,3);
  if (iVar1 != 0) {
    iVar1 = parse_operand(0,local_30,0x13,0,0,0);
    if (iVar1 != 0) {
      enc_andi(insn,local_18,local_30);
      return 1;
    }
  }
  return 0;
}


/* ==== p_and_or @ 00428ed0 ==== */

int __cdecl p_and_or(void *insn)

{
  int *va1;
  int iVar1;
  int iVar2;
  undefined1 local_30 [4];
  int local_2c;
  undefined4 local_1c;
  undefined1 local_18 [20];
  undefined4 local_4;
  
  iVar2 = 0;
  iVar1 = parse_operand(1,local_30,0xb,0,0,3);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_2c == 0xb) {
    iVar1 = parse_operand(0,local_18,0x13,0,0,0);
    if (iVar1 != 0) {
      enc_andi(insn,local_30,local_18);
      return 0;
    }
  }
  else {
    iVar2 = 2;
    va1 = (int *)((int)insn + 4);
    *va1 = (-(uint)(*(int *)((int)insn + 4) != 0) & 0xfffffffc) + 0x46;
    p_alu_dst(1,local_1c,va1);
    iVar1 = parse_operand(2,local_18,0x18,0,0,0);
    if (iVar1 != 0) {
      p_alu_dst(2,local_4,va1);
    }
  }
  return iVar2;
}


/* ==== p_alu_dst @ 00428fa0 ==== */

int __cdecl p_alu_dst(int cls)

{
  uint uVar1;
  int in_stack_00000008;
  uint *in_stack_0000000c;
  
  uVar1 = 0;
  if (cls == 2) {
    uVar1 = -(uint)(in_stack_00000008 != 2) & 8;
    *in_stack_0000000c = *in_stack_0000000c | uVar1;
    return uVar1;
  }
  switch(in_stack_00000008) {
  case 0:
    *in_stack_0000000c = *in_stack_0000000c | 0x20;
    return 0x20;
  case 1:
    *in_stack_0000000c = *in_stack_0000000c | 0x30;
    return 0x30;
  case 2:
  case 3:
    uVar1 = *in_stack_0000000c & 7;
    switch(uVar1) {
    case 0:
    case 4:
      uVar1 = 0x10;
      break;
    case 1:
    case 5:
    case 7:
      *in_stack_0000000c = *in_stack_0000000c;
      return 0;
    }
    break;
  case 4:
    *in_stack_0000000c = *in_stack_0000000c | 0x40;
    return 0x40;
  case 5:
    *in_stack_0000000c = *in_stack_0000000c | 0x50;
    return 0x50;
  case 6:
    *in_stack_0000000c = *in_stack_0000000c | 0x60;
    return 0x60;
  case 7:
    *in_stack_0000000c = *in_stack_0000000c | 0x70;
    return 0x70;
  }
  *in_stack_0000000c = *in_stack_0000000c | uVar1;
  return uVar1;
}


/* ==== p_alu1 @ 00429080 ==== */

int __cdecl p_alu1(int iclass,void *insn)

{
  int iVar1;
  undefined1 local_18 [20];
  int local_4;
  
  iVar1 = parse_operand(-(uint)(iclass != 0x27) & 2,local_18,
                        (-(uint)(iclass != 0x28) & 0xffffffe9) + 0x18,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  if (iclass == 2) {
    *(uint *)((int)insn + 4) = *(uint *)((int)insn + 4) | (uint)(local_4 != 2);
    return 1;
  }
  p_alu_dst(2,local_4,(int)insn + 4);
  return 1;
}


/* ==== p_addl @ 00429110 ==== */

int __cdecl p_addl(void *insn)

{
  int iVar1;
  undefined1 local_30 [20];
  int local_1c;
  undefined1 local_18 [20];
  undefined4 local_4;
  
  iVar1 = parse_operand(1,local_30,1,0,0,0);
  if (iVar1 != 0) {
    iVar1 = parse_operand(2,local_18,(local_1c == 2) + 0xd,0,0,0);
    if (iVar1 != 0) {
      p_alu_dst(2,local_4,(int)insn + 4);
      return 1;
    }
  }
  return 0;
}


/* ==== p_eor_adc @ 00429180 ==== */

int __cdecl p_eor_adc(int iclass,void *insn)

{
  int iVar1;
  undefined1 local_30 [24];
  undefined1 local_18 [20];
  undefined4 local_4;
  
  iVar1 = parse_operand(1,local_30,(iclass != 0x24) + 10,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  p_alu_dst(1);
  iVar1 = parse_operand(2,local_18,(-(uint)(iclass != 0x24) & 0x17) + 1,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  p_alu_dst(2,local_4,(int)insn + 4);
  return 1;
}


/* ==== p_alu2 @ 00429220 ==== */

int __cdecl p_alu2(int iclass,void *insn)

{
  int iVar1;
  undefined1 local_30 [20];
  int local_1c;
  undefined1 local_18 [20];
  undefined4 local_4;
  
  iVar1 = parse_operand(1,local_30,(-(uint)(iclass != 0x22) & 0xfffffffa) + 0x15,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  p_alu_dst(1);
  if (local_1c == 2) {
    iVar1 = 0xe;
  }
  else if (local_1c == 3) {
    iVar1 = 0xd;
  }
  else {
    iVar1 = 1;
  }
  iVar1 = parse_operand(-(uint)(iclass != 7) & 2,local_18,iVar1,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  p_alu_dst(2,local_4,(int)insn + 4);
  return 1;
}


/* ==== p_norm @ 004292e0 ==== */

int __cdecl p_norm(void *insn)

{
  int iVar1;
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  iVar1 = parse_operand(1,local_18,0x10,0,0,0);
  if (iVar1 != 0) {
    iVar1 = parse_operand(0,local_30,1,0,0,0);
    if (iVar1 != 0) {
      enc_norm(insn,local_18,local_30);
      return 1;
    }
  }
  return 0;
}


/* ==== p_lua @ 00429340 ==== */

int __cdecl p_lua(void *insn)

{
  int iVar1;
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  iVar1 = parse_operand(1,local_18,0,3,0,0);
  if (iVar1 != 0) {
    iVar1 = parse_operand(2,local_30,0x14,0,0,0);
    if (iVar1 != 0) {
      enc_lua(insn,local_18,local_30);
      return 1;
    }
  }
  return 0;
}


/* ==== p_div @ 004293a0 ==== */

int __cdecl p_div(void *insn)

{
  int iVar1;
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  iVar1 = parse_operand(1,local_18,0xb,0,0,0);
  if (iVar1 != 0) {
    iVar1 = parse_operand(0,local_30,1,0,0,0);
    if (iVar1 != 0) {
      enc_div(insn,local_18,local_30);
      return 1;
    }
  }
  return 0;
}


/* ==== p_bitop @ 00429400 ==== */

int __cdecl p_bitop(void *insn)

{
  int iVar1;
  uint uVar2;
  int local_30;
  int local_2c;
  uint local_24;
  undefined1 local_18 [24];
  
  iVar1 = parse_operand(1,local_18,0,0,0,4);
  if (iVar1 == 0) {
    skip_comma();
  }
  uVar2 = (uint)(iVar1 != 0);
  iVar1 = parse_space(&local_30,7);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_30 == 0) {
    iVar1 = parse_operand(0,&local_30,0x11,0,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    if (uVar2 == 0) {
      return 0;
    }
    enc_bit_reg(insn,local_18,&local_30);
    return uVar2;
  }
  iVar1 = parse_operand(0,&local_30,0,1,6,0);
  if (iVar1 == 0) {
    *(uint *)insn = 2 - (uint)((local_24 & 0x60) != 0);
    return 0;
  }
  if (uVar2 == 0) {
    *(undefined4 *)insn = 2;
    return 0;
  }
  if (local_2c == 0x10) {
    enc_bit_abs(insn,local_18,&local_30);
    return uVar2;
  }
  if (local_2c != 0x11) {
    enc_bit_ea(insn,local_18,&local_30);
    return uVar2;
  }
  enc_bit_pp(insn,local_18,&local_30);
  return uVar2;
}


/* ==== p_do @ 00429540 ==== */

int __cdecl p_do(void *insn)

{
  int iVar1;
  uint uVar2;
  int local_30;
  int local_2c;
  int local_1c;
  undefined1 local_18 [24];
  
  optr = asm_op1_field;
  *(undefined4 *)insn = 2;
  iVar1 = parse_space(&local_30,7);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_30 != 0) {
    iVar1 = parse_operand(1,&local_30,0,1,4,0);
    if (iVar1 == 0) {
      skip_comma();
    }
    uVar2 = (uint)(iVar1 != 0);
    iVar1 = parse_operand(0,local_18,0,0,1,0);
    if (iVar1 == 0) {
      return 0;
    }
    if (uVar2 == 0) {
      return 0;
    }
    if (local_2c == 0x10) {
      enc_do_abs(insn,&local_30,local_18);
      *(int *)((int)insn + 8) = *(int *)((int)insn + 8) + -1;
      return uVar2;
    }
    enc_do_ea(insn,&local_30,local_18);
    *(int *)((int)insn + 8) = *(int *)((int)insn + 8) + -1;
    return uVar2;
  }
  iVar1 = parse_operand(1,&local_30,0x11,0,0,2);
  if (iVar1 == 0) {
    skip_comma();
  }
  uVar2 = (uint)(iVar1 != 0);
  if ((local_2c == 1) && (local_1c == 0x2e)) {
    expr_error(s_Illegal_use_of_SSH_as_loop_count_004c2614);
    return 0;
  }
  iVar1 = parse_operand(0,local_18,0,0,1,0);
  if (iVar1 == 0) {
    return 0;
  }
  if (uVar2 == 0) {
    return 0;
  }
  if (local_2c == 10) {
    enc_do_imm(insn,&local_30,local_18);
    *(int *)((int)insn + 8) = *(int *)((int)insn + 8) + -1;
    return uVar2;
  }
  enc_do_reg(insn,&local_30,local_18);
  *(int *)((int)insn + 8) = *(int *)((int)insn + 8) + -1;
  return uVar2;
}


/* ==== p_enddo @ 004296e0 ==== */

int p_enddo(void)

{
  asm_op3_field = asm_op2_field;
  optr = asm_op1_field;
  asm_op2_field = asm_op1_field;
  asm_op1_field = &empty_str;
  return 1;
}


/* ==== p_rep @ 00429710 ==== */

int __cdecl p_rep(void *insn)

{
  int iVar1;
  int local_18;
  int local_14;
  
  optr = asm_op1_field;
  iVar1 = parse_space(&local_18,7);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_18 == 0) {
    iVar1 = parse_operand(0,&local_18,0x11,0,0,2);
    if (iVar1 == 0) {
      return 0;
    }
    if (local_14 == 1) {
      enc_loop_reg(insn,&local_18);
      return 1;
    }
    if (local_14 == 10) {
      enc_loop_imm(insn,&local_18);
      return 1;
    }
  }
  else {
    iVar1 = parse_operand(0,&local_18,0,1,4,0);
    if (iVar1 == 0) {
      return 0;
    }
    if (local_14 == 0x10) {
      enc_loop_abs(insn,&local_18);
      return 1;
    }
    enc_loop_ea(insn,&local_18);
  }
  return 1;
}


/* ==== p_jmp @ 00429800 ==== */

int __cdecl p_jmp(int iclass,void *insn)

{
  int iVar1;
  undefined1 local_18 [4];
  int local_14;
  uint local_c;
  
  optr = asm_op1_field;
  iVar1 = parse_operand(0,local_18,0,1,5,0);
  if (iVar1 == 0) {
    *(uint *)insn = 2 - (uint)((local_c & 0x20) != 0);
    return 0;
  }
  if (local_14 == 0xf) {
    if (iclass == 0x13) {
      enc_jmp_abs(insn,local_18);
      return 1;
    }
    enc_jcc_abs(insn,local_18);
    return 1;
  }
  if (iclass == 0x13) {
    enc_jmp_ea(insn,local_18);
    return 1;
  }
  enc_jcc_ea(insn,local_18);
  return 1;
}


/* ==== p_jsr @ 004298d0 ==== */

int __cdecl p_jsr(int iclass,void *insn)

{
  int iVar1;
  undefined1 local_18 [4];
  int local_14;
  uint local_c;
  
  optr = asm_op1_field;
  iVar1 = parse_operand(0,local_18,0,1,5,0);
  if (iVar1 == 0) {
    *(uint *)insn = 2 - (uint)((local_c & 0x20) != 0);
    return 0;
  }
  if (local_14 == 0xf) {
    if (iclass == 0x12) {
      enc_jmp_abs(insn,local_18);
      return 1;
    }
    enc_jcc_abs(insn,local_18);
    return 1;
  }
  if (iclass == 0x12) {
    enc_jmp_ea(insn,local_18);
    return 1;
  }
  enc_jcc_ea(insn,local_18);
  return 1;
}


/* ==== p_jbit @ 004299a0 ==== */

int __cdecl p_jbit(void *insn)

{
  int iVar1;
  uint uVar2;
  int local_48;
  int local_44;
  undefined4 local_30 [6];
  undefined1 local_18 [24];
  
  optr = asm_op1_field;
  *(undefined4 *)insn = 2;
  iVar1 = parse_operand(1,local_18,0,0,0,4);
  if (iVar1 == 0) {
    skip_comma();
  }
  uVar2 = (uint)(iVar1 != 0);
  iVar1 = parse_space(&local_48,7);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_48 == 0) {
    iVar1 = parse_operand(1,&local_48,0x11,0,0,0);
  }
  else {
    iVar1 = parse_operand(1,&local_48,0,1,7,0);
  }
  if (iVar1 == 0) {
    uVar2 = 0;
    skip_comma();
  }
  local_30[0] = 0;
  iVar1 = parse_operand(0,local_30,0,0,1,0);
  if (iVar1 == 0) {
    return 0;
  }
  if (uVar2 == 0) {
    return 0;
  }
  if (local_44 == 1) {
    enc_jbit_reg(insn,local_18,&local_48,local_30);
    return uVar2;
  }
  if (local_44 == 0x10) {
    enc_jbit_abs(insn,local_18,&local_48,local_30);
    return uVar2;
  }
  if (local_44 == 0x11) {
    enc_jbit_pp(insn,local_18,&local_48,local_30);
    return uVar2;
  }
  enc_jbit_ea(insn,local_18,&local_48,local_30);
  return uVar2;
}


/* ==== p_tcc @ 00429b00 ==== */

int __cdecl p_tcc(void *insn)

{
  int iVar1;
  undefined1 local_60 [20];
  int local_4c;
  undefined1 local_48 [24];
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  iVar1 = parse_operand(1,local_60,0xf,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  if (local_4c == 2) {
    iVar1 = 0xe;
  }
  else {
    iVar1 = (-(uint)(local_4c != 3) & 0xfffffff4) + 0xd;
  }
  iVar1 = parse_operand(0,local_48,iVar1,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  if (*asm_op2_field == '\0') {
    enc_tcc(insn,local_60,local_48);
    return 1;
  }
  if (*asm_op3_field != '\0') {
    expr_error(s_Too_many_fields_specified_for_in_004c1f60);
    return 0;
  }
  optr = asm_op2_field;
  iVar1 = parse_operand(1,local_18,0x10,0,0,0);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = parse_operand(0,local_30,0x10,0,0,0);
  if (iVar1 != 0) {
    enc_tcc_r(insn,local_60,local_48,local_18,local_30);
  }
  return 1;
}


/* ==== p_mul @ 00429c10 ==== */

int __cdecl p_mul(int iclass,void *insn)

{
  bool bVar1;
  int iVar2;
  undefined1 local_48 [4];
  int local_44;
  int local_38;
  int local_34;
  undefined1 local_30 [20];
  int local_1c;
  undefined1 local_18 [20];
  int local_4;
  
  bVar1 = false;
  if (*optr == '+') {
    optr = optr + 1;
  }
  else if (*optr == '-') {
    bVar1 = true;
    optr = optr + 1;
  }
  iVar2 = parse_operand(1,local_18,0xb,0,0,0);
  if (((iVar2 != 0) && (iVar2 = parse_operand(1,local_48,0xb,0,0,4), iVar2 != 0)) &&
     (iVar2 = parse_operand(2,local_30,1,0,0,0), iVar2 != 0)) {
    if (local_44 == 1) {
      if (bVar1) {
        *(uint *)((int)insn + 4) = *(uint *)((int)insn + 4) | 4;
      }
      mulreg(local_4,local_34,local_1c,(ulong *)((int)insn + 4));
      return 2;
    }
    if (local_38 == 0) {
      expr_error(s_Invalid_shift_amount_004c265c);
      return 0;
    }
    switch(iclass) {
    case 0x15:
      *(undefined4 *)((int)insn + 4) = 0x100c2;
      break;
    default:
      expr_error(s_Invalid_instruction_class_004c2640);
      break;
    case 0x1a:
      *(undefined4 *)((int)insn + 4) = 0x100c0;
      break;
    case 0x2a:
      *(undefined4 *)((int)insn + 4) = 0x100c3;
      break;
    case 0x2b:
      *(undefined4 *)((int)insn + 4) = 0x100c1;
    }
    if (bVar1) {
      *(uint *)((int)insn + 4) = *(uint *)((int)insn + 4) | 4;
    }
    enc_mul_imm(insn,local_18,local_48,local_30);
  }
  return 0;
}


/* ==== mulreg @ 00429da0 ==== */

int __cdecl mulreg(int s1,int s2,int d,ulong *word)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = 0;
  switch(s1) {
  case 4:
    switch(s2) {
    case 4:
      break;
    case 5:
switchD_00429df0_caseD_4:
      uVar1 = 0x50;
      break;
    case 6:
      goto switchD_00429dc5_caseD_6;
    case 7:
      goto switchD_00429dc5_caseD_7;
    default:
      goto switchD_00429df0_default;
    }
    break;
  case 5:
    switch(s2) {
    case 4:
      goto switchD_00429df0_caseD_4;
    case 5:
      uVar1 = 0x10;
      break;
    case 6:
switchD_00429df0_caseD_6:
      uVar1 = 0x60;
      break;
    case 7:
switchD_00429df0_caseD_7:
      uVar1 = 0x30;
      break;
    default:
      goto switchD_00429df0_default;
    }
  case 6:
    if (s2 != 4) {
      if (s2 != 5) {
        bVar2 = s2 == 7;
LAB_00429e19:
        if (!bVar2) {
switchD_00429df0_default:
          expr_error(s_Invalid_register_combination_004c2684);
          return 0;
        }
        uVar1 = 0x70;
        break;
      }
      goto switchD_00429df0_caseD_6;
    }
switchD_00429dc5_caseD_6:
    uVar1 = 0x20;
    break;
  case 7:
    if (s2 != 4) {
      if (s2 != 5) {
        bVar2 = s2 == 6;
        goto LAB_00429e19;
      }
      goto switchD_00429df0_caseD_7;
    }
switchD_00429dc5_caseD_7:
    uVar1 = 0x40;
    break;
  default:
    expr_error(s_mulreg_failure_004c2674);
    return 0;
  }
  if (d == 3) {
    uVar1 = uVar1 | 8;
  }
  *word = *word | uVar1;
  return 1;
}


/* ==== p_move @ 00429ea0 ==== */

int p_move(void)

{
  char *pcVar1;
  
  pcVar1 = asm_op1_field;
  if (*asm_op3_field != '\0') {
    expr_error(s_Too_many_fields_specified_for_in_004c1f60);
    return 0;
  }
  asm_op3_field = asm_op2_field;
  asm_op2_field = asm_op1_field;
  asm_op1_field = &empty_str;
  if (*pcVar1 == '\0') {
    expr_error(s_Not_enough_fields_specified_for_i_004c26a4);
    return 0;
  }
  return 1;
}


/* ==== p_movep @ 00429f00 ==== */

int __cdecl p_movep(void *insn)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int immclass;
  int local_30;
  int local_2c;
  int local_24;
  uint local_20;
  int local_18;
  int local_14;
  int local_c;
  uint local_8;
  
  pcVar1 = asm_op1_field;
  iVar3 = 5;
  if (*asm_op2_field != '\0') {
    expr_error(s_Too_many_fields_specified_for_in_004c1f60);
    return 0;
  }
  asm_op3_field = asm_op2_field;
  asm_op2_field = asm_op1_field;
  asm_op1_field = &empty_str;
  if (*pcVar1 == '\0') {
    expr_error(s_Not_enough_fields_specified_for_i_004c26a4);
    return 0;
  }
  iVar2 = parse_space(&local_30,9);
  if (iVar2 == 0) {
    return 0;
  }
  if (local_30 == 0) {
    immclass = 1;
    iVar5 = 0;
    iVar4 = 0;
    iVar2 = 0x11;
  }
  else if (local_30 == 8) {
    immclass = 0;
    iVar5 = 1;
    iVar4 = 1;
    iVar2 = 0;
  }
  else {
    immclass = 0;
    iVar5 = 8;
    iVar4 = 1;
    iVar2 = 0;
    iVar3 = 9;
  }
  iVar2 = parse_operand(1,&local_30,iVar2,iVar4,iVar5,immclass);
  if (iVar2 == 0) {
    *(undefined4 *)insn = 2;
    skip_comma();
  }
  iVar3 = parse_space(&local_18,iVar3);
  if (iVar3 == 0) {
    return 0;
  }
  if ((((local_18 == 0) || (local_18 == 8)) && (local_30 != 1)) && (local_30 != 2)) {
    expr_error(s_Either_source_or_destination_mem_004c2714);
    return 0;
  }
  if (local_18 == 0) {
    iVar5 = 0;
    iVar4 = 0;
    iVar3 = 0x11;
  }
  else if (local_18 == 8) {
    iVar5 = 1;
    iVar4 = 1;
    iVar3 = 0;
  }
  else {
    iVar5 = 8;
    iVar4 = 1;
    iVar3 = 0;
  }
  iVar3 = parse_operand(2,&local_18,iVar3,iVar4,iVar5,0);
  if (iVar3 == 0) {
    *(undefined4 *)insn = 2;
    return 0;
  }
  if (iVar2 == 0) {
    return 0;
  }
  if ((local_2c == 0x11) && (local_14 == 0x11)) {
    if (local_24 == 0) {
      if (local_c == 0) {
        if (local_30 == 8) {
          local_2c = 0xe;
        }
        else {
          local_14 = 0xe;
        }
      }
      else {
        local_2c = 0xe;
      }
    }
    else {
      local_14 = 0xe;
    }
    goto LAB_0042a0b8;
  }
  if (local_2c == 0x11) goto LAB_0042a0bd;
  if (local_14 == 0x11) goto LAB_0042a0b8;
  if (local_2c == 0xe) {
LAB_0042a1b8:
    if (local_14 == 0xe) {
      if ((local_24 != 0) && (local_c != 0)) {
        expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
        return 0;
      }
      if (local_24 == 0) {
        local_2c = 0x11;
        local_18 = local_30;
        if (local_c == 0) {
          if (((local_20 < 0xffc0) || (0xffff < local_20)) &&
             ((local_20 < 0x40 || (0x7f < local_20)))) {
            if (((local_8 < 0xffc0) || (0xffff < local_8)) && ((local_8 < 0x40 || (0x7f < local_8)))
               ) goto LAB_0042a2b7;
            local_14 = 0x11;
            local_2c = 0xe;
          }
          goto LAB_0042a0b8;
        }
      }
      else {
        local_14 = 0x11;
        local_20 = local_8;
      }
      if (local_18 == 8) {
LAB_0042a2b7:
        expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
        *(undefined4 *)insn = 2;
        return 0;
      }
      if ((local_20 < 0xffc0) || (0xffff < local_20)) {
        if (local_20 < 0x40) goto LAB_0042a2b7;
        if (0x7f < local_20) {
          expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
          *(undefined4 *)insn = 2;
          return 0;
        }
      }
    }
    else {
      if (local_2c != 0xe) goto LAB_0042a31f;
      if (local_24 != 0) {
        expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
        return 0;
      }
      local_2c = 0x11;
      if ((0xffbf < local_20) && (local_20 < 0x10000)) goto LAB_0042a0b8;
joined_r0x0042a31b:
      if (local_20 < 0x40) {
LAB_0042a37a:
        expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
        return 0;
      }
      if (0x7f < local_20) {
        expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
        return 0;
      }
    }
  }
  else {
    if (local_14 != 0xe) {
      expr_error(s_I_O_short_addressing_must_be_use_004c26d0);
      return 0;
    }
    if (local_2c == 0xe) goto LAB_0042a1b8;
LAB_0042a31f:
    if (local_14 == 0xe) {
      if ((local_c != 0) || (local_18 == 8)) goto LAB_0042a37a;
      local_14 = 0x11;
      local_20 = local_8;
      if ((local_8 < 0xffc0) || (0xffff < local_8)) goto joined_r0x0042a31b;
    }
  }
LAB_0042a0b8:
  if (local_2c != 0x11) {
    if (local_2c != 1) {
      enc_movep_mem_w(insn,&local_30,&local_18);
      return 1;
    }
    enc_movep_reg_w(insn,&local_30,&local_18);
    return 1;
  }
LAB_0042a0bd:
  if (local_14 != 1) {
    enc_movep_mem(insn,&local_30,&local_18);
    return 1;
  }
  enc_movep_reg(insn,&local_30,&local_18);
  return 1;
}


/* ==== skip_comma @ 0042a3a0 ==== */

void skip_comma(void)

{
  if (((optr != (char *)0x0) && (*optr != '\0')) && (*optr == ',')) {
    optr = optr + 1;
  }
  return;
}


/* ==== enc_andi @ 0042a3c0 ==== */

void __cdecl enc_andi(void *insn,void *imm,void *dst)

{
  uint uVar1;
  ulong uVar2;
  int pos;
  int width;
  
  width = 2;
  uVar1 = *(uint *)((int)insn + 4);
  pos = 0;
  uVar2 = ee_code(*(int *)((int)dst + 0x14));
  uVar2 = insert_bits(uVar1 | 0xb8,uVar2,pos,width);
  uVar2 = insert_bits(uVar2,*(ulong *)((int)imm + 0x10),8,8);
  *(ulong *)((int)insn + 4) = uVar2;
  return;
}


/* ==== insert_bits @ 0042a410 ==== */

ulong __cdecl insert_bits(ulong word,ulong val,int pos,int width)

{
  uint uVar1;
  
  uVar1 = ~(-1 << ((byte)width & 0x1f));
  return ~(uVar1 << ((byte)pos & 0x1f)) & word | (val & uVar1) << ((byte)pos & 0x1f);
}


/* ==== ee_code @ 0042a440 ==== */

int __cdecl ee_code(int reg)

{
  if (reg == 0x2a) {
    return 2;
  }
  if (reg != 0x31) {
    if (reg != 0x32) {
      expr_error(s_EE_encoding_failure_004c2750);
      return 0;
    }
    return 1;
  }
  return 0;
}


/* ==== enc_div @ 0042a470 ==== */

void __cdecl enc_div(void *insn,void *src,void *dst)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  iVar2 = 3;
  uVar1 = d_code(*(int *)((int)dst + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar2,iVar3);
  iVar3 = 2;
  iVar2 = 4;
  val = jjj_code(*(int *)((int)src + 0x14));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== d_code @ 0042a4c0 ==== */

int __cdecl d_code(int reg)

{
  if (reg == 2) {
    return 0;
  }
  if (reg != 3) {
    expr_error(s_D_encoding_failure_004c2764);
    return 0;
  }
  return 1;
}


/* ==== jjj_code @ 0042a4f0 ==== */

int __cdecl jjj_code(int reg)

{
  switch(reg) {
  case 2:
  case 3:
    break;
  case 4:
    return 4;
  case 5:
    return 5;
  case 6:
    return 6;
  case 7:
    return 7;
  default:
    expr_error(s_DXY_encoding_failure_004c2778);
  }
  return 0;
}


/* ==== enc_norm @ 0042a550 ==== */

void __cdecl enc_norm(void *insn,void *src,void *dst)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  iVar2 = 3;
  uVar1 = d_code(*(int *)((int)dst + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar2,iVar3);
  iVar3 = 3;
  iVar2 = 8;
  val = rrr_code(*(int *)((int)src + 4),*(int *)((int)src + 0x14));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== rrr_code @ 0042a5b0 ==== */

int __cdecl rrr_code(int mode,int reg)

{
  if (mode != 0xe) {
    if (mode == 9) {
      return 4;
    }
    switch(reg) {
    case 0xe:
      break;
    case 0xf:
      return 1;
    case 0x10:
      return 2;
    case 0x11:
      return 3;
    case 0x12:
      return 4;
    case 0x13:
      return 5;
    case 0x14:
      return 6;
    case 0x15:
      return 7;
    default:
      expr_error(s_RRR_encoding_failure_004c2790);
    }
  }
  return 0;
}


/* ==== enc_loop_ea @ 0042a640 ==== */

void __cdecl enc_loop_ea(void *insn,void *op)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 1;
  iVar3 = 6;
  uVar1 = s_code(*(int *)op);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)op + 4),*(int *)((int)op + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)op + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== mmm_code @ 0042a6c0 ==== */

int __cdecl mmm_code(int mode)

{
  switch(mode) {
  case 2:
    return 4;
  case 3:
    return 3;
  case 4:
    return 2;
  case 5:
    return 1;
  case 6:
    break;
  case 7:
    return 5;
  case 8:
    return 7;
  case 9:
  case 0xe:
    return 6;
  default:
    expr_error(s_MMM_encoding_failure_004c27a8);
  }
  return 0;
}


/* ==== s_code @ 0042a750 ==== */

int __cdecl s_code(int space)

{
  return (uint)(space == 2);
}


/* ==== enc_loop_abs @ 0042a760 ==== */

void __cdecl enc_loop_abs(void *insn,void *op)

{
  ulong uVar1;
  int pos;
  int width;
  
  width = 1;
  pos = 6;
  uVar1 = s_code(*(int *)op);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,pos,width);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)op + 0x10),8,6);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_loop_reg @ 0042a7a0 ==== */

void __cdecl enc_loop_reg(void *insn,void *op)

{
  ulong uVar1;
  int pos;
  int width;
  
  width = 6;
  pos = 8;
  uVar1 = d6_code(*(int *)((int)op + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,pos,width);
  uVar1 = insert_bits(uVar1,3,0xe,2);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== d6_code @ 0042a7e0 ==== */

int __cdecl d6_code(int reg)

{
  int iVar1;
  
  switch(reg) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    iVar1 = ddddd_code(reg);
    return iVar1;
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
    iVar1 = fff_code(reg);
    return iVar1 + 0x20;
  default:
    expr_error(s_D6_encoding_failure_004c27c0);
    return 0;
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    iVar1 = ccc_code(reg);
    return iVar1 + 0x38;
  }
}


/* ==== ccc_code @ 0042a870 ==== */

int __cdecl ccc_code(int reg)

{
  switch(reg) {
  case 0x2a:
    return 2;
  case 0x2b:
    return 1;
  case 0x2c:
    return 6;
  case 0x2d:
    return 7;
  case 0x2e:
    return 4;
  case 0x2f:
    return 5;
  case 0x30:
    return 3;
  default:
    expr_error(s_CCC_encoding_failure_004c27d4);
    return 0;
  }
}


/* ==== ddddd_code @ 0042a8e0 ==== */

int __cdecl ddddd_code(int reg)

{
  int iVar1;
  
  switch(reg) {
  case 2:
  case 3:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
    iVar1 = ddd_code(reg);
    return iVar1 + 8;
  case 4:
  case 5:
  case 6:
  case 7:
    iVar1 = dd_code(reg);
    return iVar1 + 4;
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
    iVar1 = rrr_code(0,reg);
    return iVar1 + 0x10;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
    iVar1 = nnn_code(reg);
    return iVar1 + 0x18;
  default:
    expr_error(s_DDDDD_encoding_failure_004c27ec);
    return 0;
  }
}


/* ==== dd_code @ 0042a980 ==== */

int __cdecl dd_code(int reg)

{
  switch(reg) {
  case 4:
    break;
  case 5:
    return 2;
  case 6:
    return 1;
  case 7:
    return 3;
  default:
    expr_error(s_DD_encoding_failure_004c2804);
  }
  return 0;
}


/* ==== nnn_code @ 0042a9d0 ==== */

int __cdecl nnn_code(int reg)

{
  switch(reg) {
  case 0x16:
    break;
  case 0x17:
    return 1;
  case 0x18:
    return 2;
  case 0x19:
    return 3;
  case 0x1a:
    return 4;
  case 0x1b:
    return 5;
  case 0x1c:
    return 6;
  case 0x1d:
    return 7;
  default:
    expr_error(s_NNN_encoding_failure_004c2818);
  }
  return 0;
}


/* ==== ddd_code @ 0042aa40 ==== */

int __cdecl ddd_code(int reg)

{
  switch(reg) {
  case 2:
    return 6;
  case 3:
    return 7;
  default:
    expr_error(s_DDD_encoding_failure_004c2830);
switchD_0042aa4c_caseD_8:
    return 0;
  case 8:
    goto switchD_0042aa4c_caseD_8;
  case 9:
    return 1;
  case 10:
    return 4;
  case 0xb:
    return 5;
  case 0xc:
    return 2;
  case 0xd:
    return 3;
  }
}


/* ==== fff_code @ 0042aac0 ==== */

int __cdecl fff_code(int reg)

{
  switch(reg) {
  case 0x1e:
    break;
  case 0x1f:
    return 1;
  case 0x20:
    return 2;
  case 0x21:
    return 3;
  case 0x22:
    return 4;
  case 0x23:
    return 5;
  case 0x24:
    return 6;
  case 0x25:
    return 7;
  default:
    expr_error(s_FFF_encoding_failure_004c2848);
  }
  return 0;
}


/* ==== enc_loop_imm @ 0042ab30 ==== */

void __cdecl enc_loop_imm(void *insn,void *op)

{
  ulong uVar1;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(int *)((int)op + 0x10) >> 8,0,4);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)op + 0x10),8,8);
  uVar1 = insert_bits(uVar1,1,7,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_do_ea @ 0042ab80 ==== */

void __cdecl enc_do_ea(void *insn,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_loop_ea(insn,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_do_abs @ 0042abb0 ==== */

void __cdecl enc_do_abs(void *insn,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_loop_abs(insn,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_do_reg @ 0042abe0 ==== */

void __cdecl enc_do_reg(void *insn,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_loop_reg(insn,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_do_imm @ 0042ac10 ==== */

void __cdecl enc_do_imm(void *insn,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_loop_imm(insn,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_jmp_abs @ 0042ac40 ==== */

void __cdecl enc_jmp_abs(void *insn,void *op)

{
  ulong uVar1;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)op + 0x10),0,0xc);
  uVar1 = insert_bits(uVar1,1,0x12,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_jmp_ea @ 0042ac80 ==== */

void __cdecl enc_jmp_ea(void *insn,void *op)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,7,1);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)op + 4),*(int *)((int)op + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)op + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,3,0xe,2);
  uVar1 = insert_bits(uVar1,1,0x11,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,op);
  return;
}


/* ==== set_ext_word @ 0042ad10 ==== */

void __cdecl set_ext_word(void *insn,void *op)

{
  if ((*(int *)((int)op + 4) == 0xe) || (*(int *)((int)op + 4) == 9)) {
    *(undefined4 *)((int)insn + 8) = *(undefined4 *)((int)op + 0x10);
    *(undefined4 *)insn = 2;
  }
  return;
}


/* ==== enc_jcc_abs @ 0042ad40 ==== */

void __cdecl enc_jcc_abs(void *insn,void *op)

{
  ulong uVar1;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)op + 0x10),0,0xc);
  uVar1 = insert_bits(uVar1,1,0x12,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_jcc_ea @ 0042ad80 ==== */

void __cdecl enc_jcc_ea(void *insn,void *op)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = insert_bits(*(uint *)((int)insn + 4) >> 0xc & 0xf | *(uint *)((int)insn + 4),5,5,3);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)op + 4),*(int *)((int)op + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)op + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,3,0xe,2);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,op);
  return;
}


/* ==== enc_tcc_r @ 0042ae10 ==== */

void __cdecl enc_tcc_r(void *insn,void *s1,void *d1,void *s2,void *d2)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 0;
  uVar1 = rrr_code(*(int *)((int)d2 + 4),*(int *)((int)d2 + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 3;
  uVar2 = d_code(*(int *)((int)d1 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 4;
  uVar2 = jjj_code(*(int *)((int)s1 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)s2 + 4),*(int *)((int)s2 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0x10,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_tcc @ 0042aec0 ==== */

void __cdecl enc_tcc(void *insn,void *s1,void *d1)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  iVar2 = 3;
  uVar1 = d_code(*(int *)((int)d1 + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar2,iVar3);
  iVar3 = 3;
  iVar2 = 4;
  val = jjj_code(*(int *)((int)s1 + 0x14));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_bit_ea @ 0042af10 ==== */

void __cdecl enc_bit_ea(void *insn,void *bitno,void *op)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)bitno + 0x10),0,5);
  iVar4 = 1;
  iVar3 = 6;
  uVar2 = s_code(*(int *)op);
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)op + 4),*(int *)((int)op + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)op + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,op);
  return;
}


/* ==== enc_bit_reg @ 0042afb0 ==== */

void __cdecl enc_bit_reg(void *insn,void *bitno,void *op)

{
  ulong uVar1;
  ulong val;
  int pos;
  int width;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),0x301,6,10);
  width = 6;
  pos = 8;
  val = d6_code(*(int *)((int)op + 0x14));
  uVar1 = insert_bits(uVar1,val,pos,width);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)bitno + 0x10),0,5);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_bit_abs @ 0042b010 ==== */

void __cdecl enc_bit_abs(void *insn,void *bitno,void *op)

{
  ulong uVar1;
  ulong val;
  int pos;
  int width;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)bitno + 0x10),0,5);
  width = 1;
  pos = 6;
  val = s_code(*(int *)op);
  uVar1 = insert_bits(uVar1,val,pos,width);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)op + 0x10),8,6);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_bit_pp @ 0042b070 ==== */

void __cdecl enc_bit_pp(void *insn,void *bitno,void *op)

{
  ulong uVar1;
  ulong val;
  int pos;
  int width;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)bitno + 0x10),0,5);
  width = 1;
  pos = 6;
  val = s_code(*(int *)op);
  uVar1 = insert_bits(uVar1,val,pos,width);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)op + 0x10),8,6);
  uVar1 = insert_bits(uVar1,1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_jbit_ea @ 0042b0e0 ==== */

void __cdecl enc_jbit_ea(void *insn,void *bitno,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_bit_ea(insn,bitno,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_jbit_reg @ 0042b110 ==== */

void __cdecl enc_jbit_reg(void *insn,void *bitno,void *op,void *target)

{
  ulong uVar1;
  ulong val;
  int pos;
  int width;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),0x180,7,9);
  width = 6;
  pos = 8;
  val = d6_code(*(int *)((int)op + 0x14));
  uVar1 = insert_bits(uVar1,val,pos,width);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)bitno + 0x10),0,5);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,target);
  return;
}


/* ==== enc_jbit_abs @ 0042b180 ==== */

void __cdecl enc_jbit_abs(void *insn,void *bitno,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_bit_abs(insn,bitno,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_jbit_pp @ 0042b1b0 ==== */

void __cdecl enc_jbit_pp(void *insn,void *bitno,void *op,void *target)

{
  undefined4 uVar1;
  
  enc_bit_pp(insn,bitno,op);
  uVar1 = *(undefined4 *)((int)target + 0x10);
  *(undefined4 *)insn = 2;
  *(undefined4 *)((int)insn + 8) = uVar1;
  return;
}


/* ==== enc_movep_reg @ 0042b1e0 ==== */

void __cdecl enc_movep_reg(void *insn,void *pp,void *reg)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)pp + 0x10),0,6);
  iVar4 = 6;
  iVar3 = 8;
  uVar2 = d6_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x10;
  uVar2 = s_code(*(int *)pp);
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movep_mem @ 0042b250 ==== */

void __cdecl enc_movep_mem(void *insn,void *pp,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)pp + 0x10),0,6);
  iVar4 = 1;
  iVar3 = 6;
  if (*(int *)mem != 8) {
    uVar2 = s_code(*(int *)mem);
    uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
    iVar3 = 7;
  }
  uVar1 = insert_bits(uVar1,1,iVar3,1);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x10;
  uVar2 = s_code(*(int *)pp);
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,mem);
  return;
}


/* ==== enc_movep_reg_w @ 0042b320 ==== */

void __cdecl enc_movep_reg_w(void *insn,void *reg,void *pp)

{
  ulong uVar1;
  
  enc_movep_reg(insn,pp,reg);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movep_mem_w @ 0042b350 ==== */

void __cdecl enc_movep_mem_w(void *insn,void *mem,void *pp)

{
  ulong uVar1;
  
  enc_movep_mem(insn,pp,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_ea @ 0042b380 ==== */

void __cdecl enc_movec_ea(void *insn,void *creg,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 6;
  iVar3 = 0;
  uVar1 = d6_code(*(int *)((int)creg + 0x14));
  uVar1 = insert_bits(*(uint *)((int)insn + 4) | 0x40000,uVar1,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 6;
  uVar2 = s_code(*(int *)mem);
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  uVar1 = insert_bits(uVar1,1,0x10,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,mem);
  return;
}


/* ==== enc_movec_ea_w @ 0042b440 ==== */

void __cdecl enc_movec_ea_w(void *insn,void *mem,void *creg)

{
  ulong uVar1;
  
  enc_movec_ea(insn,creg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_imm @ 0042b470 ==== */

void __cdecl enc_movec_imm(void *insn,void *imm,void *creg)

{
  ulong uVar1;
  int pos;
  int width;
  
  width = 6;
  pos = 0;
  uVar1 = d6_code(*(int *)((int)creg + 0x14));
  uVar1 = insert_bits(*(uint *)((int)insn + 4) | 0x40000,uVar1,pos,width);
  uVar1 = insert_bits(uVar1,1,7,1);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)imm + 0x10),8,8);
  uVar1 = insert_bits(uVar1,1,0x10,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_reg @ 0042b4e0 ==== */

void __cdecl enc_movec_reg(void *insn,void *creg,void *reg)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 6;
  iVar2 = 0;
  uVar1 = d6_code(*(int *)((int)creg + 0x14));
  uVar1 = insert_bits(*(uint *)((int)insn + 4) | 0x40000,uVar1,iVar2,iVar3);
  uVar1 = insert_bits(uVar1,1,7,1);
  iVar3 = 6;
  iVar2 = 8;
  val = d6_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_reg_w @ 0042b560 ==== */

void __cdecl enc_movec_reg_w(void *insn,void *reg,void *creg)

{
  ulong uVar1;
  
  enc_movec_reg(insn,creg,reg);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_abs @ 0042b590 ==== */

void __cdecl enc_movec_abs(void *insn,void *creg,void *abs)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 6;
  iVar2 = 0;
  uVar1 = d6_code(*(int *)((int)creg + 0x14));
  uVar1 = insert_bits(*(uint *)((int)insn + 4) | 0x40000,uVar1,iVar2,iVar3);
  iVar3 = 1;
  iVar2 = 6;
  val = s_code(*(int *)abs);
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)abs + 0x10),8,6);
  uVar1 = insert_bits(uVar1,1,0x10,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_abs_w @ 0042b610 ==== */

void __cdecl enc_movec_abs_w(void *insn,void *abs,void *creg)

{
  ulong uVar1;
  
  enc_movec_abs(insn,creg,abs);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movec_ea2 @ 0042b640 ==== */

void __cdecl enc_movec_ea2(void *insn,void *creg,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 6;
  iVar3 = 0;
  uVar1 = d6_code(*(int *)((int)creg + 0x14));
  uVar1 = insert_bits(*(uint *)((int)insn + 4) | 0x40000,uVar1,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 6;
  uVar2 = s_code(*(int *)mem);
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  uVar1 = insert_bits(uVar1,1,0x10,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,mem);
  return;
}


/* ==== enc_movec_ea2_w @ 0042b700 ==== */

void __cdecl enc_movec_ea2_w(void *insn,void *mem,void *creg)

{
  ulong uVar1;
  
  enc_movec_ea2(insn,creg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_xy @ 0042b730 ==== */

void __cdecl enc_pm_xy(void *insn,void *xreg,void *xmem,void *yreg,void *ymem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 8;
  uVar1 = rrr_code(*(int *)((int)xmem + 4),*(int *)((int)xmem + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)xmem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0xd;
  uVar2 = rrr_code(*(int *)((int)ymem + 4),*(int *)((int)ymem + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0x10;
  uVar2 = yy_code(*(int *)((int)yreg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0x12;
  uVar2 = xx_code(*(int *)((int)xreg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0x14;
  uVar2 = mmm_code(*(int *)((int)ymem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0x17,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== xx_code @ 0042b810 ==== */

int __cdecl xx_code(int reg)

{
  switch(reg) {
  case 2:
    return 2;
  case 3:
    return 3;
  case 4:
    goto switchD_0042b81c_caseD_4;
  default:
    expr_error(s_XX_encoding_failure_004c2860);
switchD_0042b81c_caseD_4:
    return 0;
  case 6:
    return 1;
  }
}


/* ==== yy_code @ 0042b860 ==== */

int __cdecl yy_code(int reg)

{
  switch(reg) {
  case 2:
    return 2;
  case 3:
    return 3;
  default:
    expr_error(s_YY_encoding_failure_004c2874);
switchD_0042b86c_caseD_5:
    return 0;
  case 5:
    goto switchD_0042b86c_caseD_5;
  case 7:
    return 1;
  }
}


/* ==== enc_pm_xy_wx @ 0042b8b0 ==== */

void __cdecl enc_pm_xy_wx(void *insn,void *xmem,void *xreg,void *yreg,void *ymem)

{
  ulong uVar1;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  enc_pm_xy(insn,xreg,xmem,yreg,ymem);
  return;
}


/* ==== enc_pm_xy_wy @ 0042b8f0 ==== */

void __cdecl enc_pm_xy_wy(void *insn,void *xreg,void *xmem,void *ymem,void *yreg)

{
  ulong uVar1;
  
  enc_pm_xy(insn,xreg,xmem,yreg,ymem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0x16,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_xy_wxy @ 0042b930 ==== */

void __cdecl enc_pm_xy_wxy(void *insn,void *xmem,void *xreg,void *ymem,void *yreg)

{
  ulong uVar1;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  uVar1 = insert_bits(uVar1,1,0x16,1);
  *(ulong *)((int)insn + 4) = uVar1;
  enc_pm_xy(insn,xreg,xmem,yreg,ymem);
  return;
}


/* ==== enc_pm_xr2 @ 0042b980 ==== */

void __cdecl enc_pm_xr2(void *insn,void *acc,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 8;
  uVar1 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0xf;
  uVar2 = s_code(*(int *)mem);
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x10;
  uVar2 = d_code(*(int *)((int)acc + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0x13,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_x_ea @ 0042ba20 ==== */

void __cdecl enc_pm_x_ea(void *insn,void *reg,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 8;
  uVar1 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  uVar2 = ddddd_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,0x10,3);
  uVar1 = insert_bits(uVar1,(int)uVar2 >> 3,0x14,2);
  uVar1 = insert_bits(uVar1,1,0x16,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,mem);
  return;
}


/* ==== enc_pm_x_ea_w @ 0042bad0 ==== */

void __cdecl enc_pm_x_ea_w(void *insn,void *mem,void *reg)

{
  ulong uVar1;
  
  enc_pm_x_ea(insn,reg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_y_ea @ 0042bb00 ==== */

void __cdecl enc_pm_y_ea(void *insn,void *reg,void *mem)

{
  ulong uVar1;
  
  enc_pm_x_ea(insn,reg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0x13,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_y_ea_w @ 0042bb30 ==== */

void __cdecl enc_pm_y_ea_w(void *insn,void *mem,void *reg)

{
  ulong uVar1;
  
  enc_pm_y_ea(insn,reg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_x_abs @ 0042bb60 ==== */

void __cdecl enc_pm_x_abs(void *insn,void *reg,void *abs)

{
  ulong uVar1;
  ulong val;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)abs + 0x10),8,6);
  val = ddddd_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(uVar1,val,0x10,3);
  uVar1 = insert_bits(uVar1,(int)val >> 3,0x14,2);
  uVar1 = insert_bits(uVar1,1,0x16,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_x_abs_w @ 0042bbd0 ==== */

void __cdecl enc_pm_x_abs_w(void *insn,void *abs,void *reg)

{
  ulong uVar1;
  
  enc_pm_x_abs(insn,reg,abs);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_y_abs @ 0042bc00 ==== */

void __cdecl enc_pm_y_abs(void *insn,void *reg,void *abs)

{
  ulong uVar1;
  
  enc_pm_x_abs(insn,reg,abs);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0x13,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_y_abs_w @ 0042bc30 ==== */

void __cdecl enc_pm_y_abs_w(void *insn,void *abs,void *reg)

{
  ulong uVar1;
  
  enc_pm_y_abs(insn,reg,abs);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_ry @ 0042bc60 ==== */

void __cdecl enc_pm_ry(void *insn,void *s1,void *d1,void *yreg,void *ymem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 8;
  uVar1 = rrr_code(*(int *)((int)ymem + 4),*(int *)((int)ymem + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)ymem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  iVar4 = 2;
  iVar3 = 0x10;
  uVar2 = yy_code(*(int *)((int)yreg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x12;
  uVar2 = x_code(*(int *)((int)d1 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x13;
  uVar2 = d_code(*(int *)((int)s1 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0x14,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,ymem);
  return;
}


/* ==== x_code @ 0042bd40 ==== */

int __cdecl x_code(int reg)

{
  if (reg == 4) {
    return 0;
  }
  if (reg != 6) {
    expr_error(s_X_encoding_failure_004c2888);
    return 0;
  }
  return 1;
}


/* ==== enc_pm_ry_w @ 0042bd70 ==== */

void __cdecl enc_pm_ry_w(void *insn,void *s1,void *d1,void *ymem,void *yreg)

{
  ulong uVar1;
  
  enc_pm_ry(insn,s1,d1,yreg,ymem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_xr @ 0042bdb0 ==== */

void __cdecl enc_pm_xr(void *insn,void *xreg,void *xmem,void *s2,void *d2)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 8;
  uVar1 = rrr_code(*(int *)((int)xmem + 4),*(int *)((int)xmem + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)xmem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x10;
  uVar2 = y_code(*(int *)((int)d2 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 1;
  iVar3 = 0x11;
  uVar2 = d_code(*(int *)((int)s2 + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0x12;
  uVar2 = xx_code(*(int *)((int)xreg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0x14,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,xmem);
  return;
}


/* ==== y_code @ 0042be80 ==== */

int __cdecl y_code(int reg)

{
  if (reg == 5) {
    return 0;
  }
  if (reg != 7) {
    expr_error(s_Y_encoding_failure_004c289c);
    return 0;
  }
  return 1;
}


/* ==== enc_pm_xr_w @ 0042beb0 ==== */

void __cdecl enc_pm_xr_w(void *insn,void *xmem,void *xreg,void *s2,void *d2)

{
  ulong uVar1;
  
  enc_pm_xr(insn,xreg,xmem,s2,d2);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_l_abs @ 0042bef0 ==== */

void __cdecl enc_pm_l_abs(void *insn,void *reg,void *abs)

{
  ulong uVar1;
  ulong val;
  int pos;
  int width;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)abs + 0x10),8,6);
  width = 4;
  pos = 0x10;
  val = lll_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(uVar1,val,pos,width);
  uVar1 = insert_bits(uVar1,1,0x16,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== lll_code @ 0042bf50 ==== */

int __cdecl lll_code(int reg)

{
  switch(reg) {
  case 0:
    return 2;
  case 1:
    return 3;
  case 2:
    return 8;
  case 3:
    return 9;
  default:
    expr_error(s_LLL_encoding_failure_004c28b0);
switchD_0042bf61_caseD_28:
    return 0;
  case 0x26:
    return 10;
  case 0x27:
    return 0xb;
  case 0x28:
    goto switchD_0042bf61_caseD_28;
  case 0x29:
    return 1;
  }
}


/* ==== enc_pm_l_abs_w @ 0042c000 ==== */

void __cdecl enc_pm_l_abs_w(void *insn,void *abs,void *reg)

{
  ulong uVar1;
  
  enc_pm_l_abs(insn,reg,abs);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_l_ea @ 0042c030 ==== */

void __cdecl enc_pm_l_ea(void *insn,void *reg,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 3;
  iVar3 = 8;
  uVar1 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  iVar4 = 4;
  iVar3 = 0x10;
  uVar2 = lll_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0x16,1);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,mem);
  return;
}


/* ==== enc_pm_l_ea_w @ 0042c0d0 ==== */

void __cdecl enc_pm_l_ea_w(void *insn,void *mem,void *reg)

{
  ulong uVar1;
  
  enc_pm_l_ea(insn,reg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_imm @ 0042c100 ==== */

void __cdecl enc_pm_imm(void *insn,void *imm,void *dst)

{
  ulong uVar1;
  ulong val;
  int pos;
  int width;
  
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),*(ulong *)((int)imm + 0x10),8,8);
  width = 5;
  pos = 0x10;
  val = ddddd_code(*(int *)((int)dst + 0x14));
  uVar1 = insert_bits(uVar1,val,pos,width);
  uVar1 = insert_bits(uVar1,1,0x15,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_reg @ 0042c160 ==== */

void __cdecl enc_pm_reg(void *insn,void *src,void *dst)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 5;
  iVar2 = 8;
  uVar1 = ddddd_code(*(int *)((int)dst + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar2,iVar3);
  iVar3 = 5;
  iVar2 = 0xd;
  val = ddddd_code(*(int *)((int)src + 0x14));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  uVar1 = insert_bits(uVar1,1,0x15,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_pm_update @ 0042c1c0 ==== */

void __cdecl enc_pm_update(void *insn,void *op)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 3;
  iVar2 = 8;
  uVar1 = rrr_code(*(int *)((int)op + 4),*(int *)((int)op + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar2,iVar3);
  iVar3 = 2;
  iVar2 = 0xb;
  val = mmm_code(*(int *)((int)op + 4));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  uVar1 = insert_bits(uVar1,0x81,0xe,8);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movem_ea @ 0042c230 ==== */

void __cdecl enc_movem_ea(void *insn,void *reg,void *mem)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 6;
  iVar3 = 0;
  uVar1 = d6_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,7,1);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  uVar1 = insert_bits(uVar1,1,0xe,1);
  uVar1 = insert_bits(uVar1,7,0x10,3);
  *(ulong *)((int)insn + 4) = uVar1;
  set_ext_word(insn,mem);
  return;
}


/* ==== enc_movem_ea_w @ 0042c2e0 ==== */

void __cdecl enc_movem_ea_w(void *insn,void *mem,void *reg)

{
  ulong uVar1;
  
  enc_movem_ea(insn,reg,mem);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movem_abs @ 0042c310 ==== */

void __cdecl enc_movem_abs(void *insn,void *reg,void *abs)

{
  ulong uVar1;
  int pos;
  int width;
  
  width = 6;
  pos = 0;
  uVar1 = d6_code(*(int *)((int)reg + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,pos,width);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)abs + 0x10),8,6);
  uVar1 = insert_bits(uVar1,7,0x10,3);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_movem_abs_w @ 0042c360 ==== */

void __cdecl enc_movem_abs_w(void *insn,void *abs,void *reg)

{
  ulong uVar1;
  
  enc_movem_abs(insn,reg,abs);
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),1,0xf,1);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_lua @ 0042c390 ==== */

void __cdecl enc_lua(void *insn,void *mem,void *dst)

{
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 4;
  iVar3 = 0;
  uVar1 = ddddd_code(*(int *)((int)dst + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar3,iVar4);
  iVar4 = 3;
  iVar3 = 8;
  uVar2 = rrr_code(*(int *)((int)mem + 4),*(int *)((int)mem + 0x14));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  iVar4 = 2;
  iVar3 = 0xb;
  uVar2 = mmm_code(*(int *)((int)mem + 4));
  uVar1 = insert_bits(uVar1,uVar2,iVar3,iVar4);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== enc_mul_imm @ 0042c400 ==== */

void __cdecl enc_mul_imm(void *insn,void *s1,void *imm,void *dst)

{
  ulong uVar1;
  ulong val;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  iVar2 = 3;
  uVar1 = d_code(*(int *)((int)dst + 0x14));
  uVar1 = insert_bits(*(ulong *)((int)insn + 4),uVar1,iVar2,iVar3);
  iVar3 = 2;
  iVar2 = 4;
  val = qq_code(*(int *)((int)s1 + 0x14));
  uVar1 = insert_bits(uVar1,val,iVar2,iVar3);
  uVar1 = insert_bits(uVar1,*(ulong *)((int)imm + 0x10),8,5);
  *(ulong *)((int)insn + 4) = uVar1;
  return;
}


/* ==== qq_code @ 0042c470 ==== */

int __cdecl qq_code(int reg)

{
  switch(reg) {
  case 4:
    return 1;
  case 5:
    return 2;
  case 6:
    return 3;
  case 7:
    break;
  default:
    expr_error(s_QQ_encoding_failure_004c28c8);
  }
  return 0;
}


