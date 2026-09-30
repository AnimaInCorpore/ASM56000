/* ==== cdb_find_file_index @ 00464e30 ==== */

int __cdecl cdb_find_file_index(char *name)

{
  uint uVar1;
  char cVar2;
  char *s;
  undefined3 extraout_var;
  int iVar3;
  ulong addr;
  int iVar4;
  int iVar5;
  uint n;
  
  n = 0;
  cVar2 = *name;
  while ((cVar2 != '\0' && (cVar2 != '@'))) {
    iVar5 = n + 1;
    n = n + 1;
    cVar2 = name[iVar5];
  }
  if (name[n] == '\0') {
    n = 0xffffffff;
  }
  if ((n == 0xffffffff) || (*name == '@')) {
    addr = cdb_frame_pc();
    iVar5 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr);
    iVar5 = dbg_addr_to_file_sym(addr,iVar5);
    return iVar5;
  }
  iVar5 = 0;
  iVar4 = cur_sim;
  if (*(int *)(cur_sim + 0x3fd8) < 1) {
    return -1;
  }
  do {
    if (*(int *)(*(int *)(iVar4 + 0x3fe0) + 0x18 + iVar5 * 0x20) == 0x67) {
      s = (char *)((iVar5 + 1) * 0x20 + *(int *)(iVar4 + 0x3fe0));
      uVar1 = *(uint *)(s + 0x10);
      if (uVar1 != 0) {
        if (*(uint *)(iVar4 + 0x3fe8) < uVar1) {
          return -1;
        }
        s = (char *)(*(int *)(iVar4 + 0x3fe4) + uVar1);
      }
      cVar2 = strrchr(s,0x2f);
      if (CONCAT31(extraout_var,cVar2) != 0) {
        s = (char *)(CONCAT31(extraout_var,cVar2) + 1);
      }
      iVar3 = strncmp(s,name,n);
      iVar4 = cur_sim;
      if (iVar3 == 0) {
        return iVar5;
      }
    }
    iVar5 = iVar5 + 1 + *(int *)(*(int *)(iVar4 + 0x3fe0) + 0x1c + iVar5 * 0x20);
    if (*(int *)(iVar4 + 0x3fd8) <= iVar5) {
      return -1;
    }
  } while( true );
}


/* ==== cdb_find_function @ 00464f40 ==== */

int __cdecl cdb_find_function(char *name,int file_sym)

{
  void *sym;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *name_00;
  
  iVar2 = 0;
  iVar5 = 0;
  iVar3 = 0;
  iVar6 = cur_sim;
  if (*(int *)(cur_sim + 0x3fd8) < 1) {
    return -1;
  }
  do {
    iVar4 = iVar5 * 0x20;
    iVar1 = *(int *)(*(int *)(iVar6 + 0x3fe0) + 0x18 + iVar4);
    if (iVar1 == 100) {
      name_00 = &DAT_004d3408;
LAB_00464f87:
      iVar1 = cdb_symname_is(name_00,(void *)(*(int *)(iVar6 + 0x3fe0) + iVar4));
      iVar6 = cur_sim;
      if (iVar1 == 0) {
        iVar3 = iVar3 + -1;
      }
      else {
        iVar3 = iVar3 + 1;
      }
    }
    else {
      if (iVar1 == 0x65) {
        name_00 = &DAT_004c7c28;
        goto LAB_00464f87;
      }
      if (iVar1 == 0x67) {
        iVar2 = iVar5;
      }
    }
    if ((((iVar3 == 0) &&
         (sym = (void *)(*(int *)(iVar6 + 0x3fe0) + iVar4),
         ((byte)*(undefined4 *)(*(int *)(iVar6 + 0x3fe0) + 0x14 + iVar4) & 0x30) == 0x20)) &&
        (*(int *)((int)sym + 0x10) != -2)) &&
       ((*(int *)((int)sym + 0x18) == 2 || (*(int *)((int)sym + 0x18) == 3)))) {
      iVar1 = cdb_sym_name_eq(name,sym);
      iVar6 = cur_sim;
      if ((iVar1 != 0) &&
         ((*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar4) != 3 || (file_sym == iVar2)))) {
        iVar6 = iVar5 + 1;
        if (iVar6 < *(int *)(cur_sim + 0x3fd8)) {
          while( true ) {
            iVar2 = cdb_symname_is(&DAT_004c7c28,(void *)(*(int *)(cur_sim + 0x3fe0) + iVar6 * 0x20)
                                  );
            if (iVar2 != 0) {
              return iVar6;
            }
            iVar2 = *(int *)(cur_sim + 0x3fe0) + iVar6 * 0x20;
            if (((byte)*(undefined4 *)(iVar2 + 0x14) & 0x30) == 0x20) break;
            iVar6 = iVar6 + 1 + *(int *)(iVar2 + 0x1c);
            if (*(int *)(cur_sim + 0x3fd8) <= iVar6) {
              return iVar5;
            }
          }
        }
        return iVar5;
      }
    }
    iVar5 = iVar5 + 1 + *(int *)(*(int *)(iVar6 + 0x3fe0) + 0x1c + iVar4);
    if (*(int *)(iVar6 + 0x3fd8) <= iVar5) {
      return -1;
    }
  } while( true );
}


/* ==== cdb_lookup_scoped @ 004650a0 ==== */

int __cdecl cdb_lookup_scoped(char *name,int sclass)

{
  ulong pc;
  int block_sym;
  int iVar1;
  
  iVar1 = -1;
  pc = cdb_frame_pc();
  block_sym = cdb_enclosing_block(pc);
  while( true ) {
    if (block_sym == -1) {
      if (iVar1 == -1) {
        iVar1 = cdb_lookup_global(name,sclass);
      }
      return iVar1;
    }
    if (iVar1 != -1) break;
    iVar1 = cdb_find_in_block(block_sym,name,sclass);
    if (iVar1 == -1) {
      block_sym = cdb_parent_block(block_sym);
    }
  }
  return iVar1;
}


/* ==== cdb_struct_size @ 00465110 ==== */

ulong __cdecl cdb_struct_size(int sym)

{
  int iVar1;
  
  if (sym < *(int *)(cur_sim + 0x3fd8)) {
    iVar1 = sym << 5;
    while (0 < iVar1) {
      if (*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar1) == 0x66) {
        return *(ulong *)(*(int *)(cur_sim + 0x3fe0) + 8 + (sym + 1) * 0x20);
      }
      sym = sym + 1;
      iVar1 = iVar1 + 0x20;
      if (*(int *)(cur_sim + 0x3fd8) <= sym) {
        return 1;
      }
    }
  }
  return 1;
}


/* ==== cdb_types_match @ 00465170 ==== */

int __cdecl cdb_types_match(ulong type1,int tag1,ulong type2,int tag2)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = (byte)type1;
  for (; ((bVar1 & 0x30) == 0x10 && (((byte)type2 & 0x30) == 0x10));
      type2 = type2 & 0x1000f | type2 >> 2 & 0x3ffebff0) {
    type1 = type1 & 0x1000f | type1 >> 2 & 0x3ffebff0;
    bVar1 = (byte)type1;
  }
  if (type1 == type2) {
    if (((byte)type1 & 0x30) != 0x30) {
      if (type1 == 8) goto LAB_004651de;
      if (type1 != 10) {
        return 1;
      }
    }
    if (type1 == 8) {
LAB_004651de:
      iVar2 = cdb_struct_layout_eq(tag1,tag2);
      return iVar2;
    }
    if (type1 == 9) {
      iVar2 = cdb_union_layout_eq(tag1,tag2);
      return iVar2;
    }
    if (type1 == 10) {
      iVar2 = cdb_enum_layout_eq(tag1,tag2);
      return iVar2;
    }
  }
  return 0;
}


/* ==== cdb_lookup_variable @ 00465230 ==== */

void __cdecl cdb_lookup_variable(char *name)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *buf;
  int extraout_EAX;
  uint uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  
  if (name == (char *)0x0) {
    return;
  }
  iVar3 = cdb_lookup_symbol(name);
  if (iVar3 != -1) {
    new_node();
    if (extraout_EAX == 0) {
      return;
    }
    iVar2 = *(int *)(extraout_EAX + 0x10);
    iVar6 = *(int *)(cur_sim + 0x3fe0);
    iVar5 = iVar3 * 0x20;
    *(undefined4 *)(iVar2 + 0x18) = *(undefined4 *)(iVar6 + 8 + iVar5);
    *(undefined4 *)(iVar2 + 0x1c) = *(undefined4 *)(iVar6 + 0xc + iVar5);
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x20) =
         *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x14 + iVar5);
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x24) =
         *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar5);
    iVar2 = *(int *)(extraout_EAX + 0x10);
    uVar4 = *(uint *)(iVar2 + 0x20) & 0x1000f;
    if (((uVar4 == 8) || (uVar4 == 9)) || (uVar4 == 10)) {
      *(undefined4 *)(iVar2 + 0x28) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + (iVar3 + 1) * 0x20);
    }
    else {
      *(undefined4 *)(iVar2 + 0x28) = 0;
    }
    iVar2 = *(int *)(extraout_EAX + 0x10);
    if (((byte)*(undefined4 *)(iVar2 + 0x20) & 0x30) == 0x30) {
      iVar6 = *(int *)(cur_sim + 0x3fe0) + (iVar3 + 1) * 0x20;
      iVar3 = *(int *)(iVar6 + 0xc);
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      *(int *)(iVar2 + 0x2c) = iVar3;
      iVar3 = *(int *)(iVar6 + 0x10);
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      *(int *)(*(int *)(extraout_EAX + 0x10) + 0x30) = iVar3;
      iVar3 = *(int *)(iVar6 + 0x14);
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      *(int *)(*(int *)(extraout_EAX + 0x10) + 0x34) = iVar3;
      iVar3 = *(int *)(iVar6 + 0x18);
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      *(int *)(*(int *)(extraout_EAX + 0x10) + 0x38) = iVar3;
      *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 1;
      return;
    }
    *(undefined4 *)(iVar2 + 0x2c) = 1;
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x30) = 1;
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x34) = 1;
    *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x38) = 1;
    *(undefined2 *)(*(int *)(extraout_EAX + 0x10) + 0x3c) = 1;
    return;
  }
  uVar4 = 0xffffffff;
  pcVar7 = name;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  dsp_alloc(~uVar4 + 0x17,1);
  if (buf != (char *)0x0) {
    sprintf(buf,s_undeclared_identifier__s_004d3424,name);
    cdb_error(buf);
    dsp_free(buf);
    return;
  }
  cdb_error(s_undeclared_identifier_004d340c);
  return;
}


/* ==== cdb_sym_name @ 004653d0 ==== */

char __cdecl cdb_sym_name(int sym)

{
  char cVar1;
  undefined3 extraout_var;
  char *pcVar2;
  
  cVar1 = cdb_symname_ptr((void *)(*(int *)(cur_sim + 0x3fe0) + sym * 0x20));
  pcVar2 = (char *)CONCAT31(extraout_var,cVar1);
  if (*pcVar2 == 'F') {
    pcVar2 = pcVar2 + 1;
  }
  return (char)pcVar2;
}


/* ==== cdb_next_member @ 00465400 ==== */

int __cdecl cdb_next_member(int sym)

{
  int iVar1;
  
  iVar1 = sym + 1 + *(int *)(sym * 0x20 + 0x1c + *(int *)(cur_sim + 0x3fe0));
  if (*(int *)(iVar1 * 0x20 + 0x18 + *(int *)(cur_sim + 0x3fe0)) == 0x66) {
    iVar1 = -1;
  }
  return iVar1;
}


/* ==== cdb_find_member @ 00465430 ==== */

int __cdecl cdb_find_member(int struct_sym,char *name)

{
  void *sym;
  int iVar1;
  int iVar2;
  
  if (struct_sym != 0) {
    iVar1 = *(int *)(cur_sim + 0x3fe0);
    iVar2 = *(int *)(struct_sym * 0x20 + 0x1c + iVar1) + 1 + struct_sym;
    if (iVar2 < *(int *)(cur_sim + 0x3fd8)) {
      while( true ) {
        sym = (void *)(iVar1 + iVar2 * 0x20);
        if (*(int *)((int)sym + 0x18) == 0x66) break;
        iVar1 = cdb_sym_name_eq(name,sym);
        if (iVar1 != 0) {
          return iVar2;
        }
        iVar1 = *(int *)(cur_sim + 0x3fe0);
        iVar2 = iVar2 + 1 + *(int *)(iVar2 * 0x20 + 0x1c + iVar1);
        if (*(int *)(cur_sim + 0x3fd8) <= iVar2) {
          return -1;
        }
      }
    }
  }
  return -1;
}


/* ==== cdb_lookup_typedef @ 004654c0 ==== */

int __cdecl cdb_lookup_typedef(char *name)

{
  int iVar1;
  
  iVar1 = cdb_lookup_scoped(name,0xd);
  return iVar1;
}


/* ==== cdb_lookup_enum_member @ 004654d0 ==== */

int __cdecl cdb_lookup_enum_member(char *name)

{
  int iVar1;
  
  iVar1 = cdb_lookup_scoped(name,0x10);
  return iVar1;
}


/* ==== cdb_sym_to_value @ 004654e0 ==== */

void __cdecl cdb_sym_to_value(void *v,int sym)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if ((-1 < sym) && (sym < *(int *)(cur_sim + 0x3fd8))) {
    iVar4 = sym * 0x20;
    *(undefined4 *)((int)v + 0x20) = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x14 + iVar4);
    if (*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar4) == 0x12) {
      *(undefined4 *)((int)v + 0x24) = 0x12;
    }
    else {
      *(undefined4 *)((int)v + 0x24) = 2;
    }
    *(undefined4 *)((int)v + 0x18) = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar4);
    iVar1 = cdb_default_space();
    *(int *)((int)v + 0x1c) = iVar1;
    uVar2 = *(uint *)((int)v + 0x20) & 0x1000f;
    if (((uVar2 == 8) || (uVar2 == 9)) || (uVar2 == 10)) {
      *(undefined4 *)((int)v + 0x28) =
           *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + (sym + 1) * 0x20);
    }
    else {
      *(undefined4 *)((int)v + 0x28) = 0;
    }
    if (((byte)*(uint *)((int)v + 0x20) & 0x30) == 0x30) {
      iVar3 = *(int *)(cur_sim + 0x3fe0) + (sym + 1) * 0x20;
      iVar1 = *(int *)(iVar3 + 0xc);
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)((int)v + 0x2c) = iVar1;
      iVar1 = *(int *)(iVar3 + 0x10);
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)((int)v + 0x30) = iVar1;
      iVar1 = *(int *)(iVar3 + 0x14);
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)((int)v + 0x34) = iVar1;
      iVar1 = *(int *)(iVar3 + 0x18);
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)((int)v + 0x38) = iVar1;
    }
    else {
      *(undefined4 *)((int)v + 0x2c) = 1;
      *(undefined4 *)((int)v + 0x30) = 1;
      *(undefined4 *)((int)v + 0x34) = 1;
      *(undefined4 *)((int)v + 0x38) = 1;
    }
    if (*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar4) == 0x12) {
      *(undefined4 *)((int)v + 0x2c) =
           *(undefined4 *)(sym * 0x20 + 0x28 + *(int *)(cur_sim + 0x3fe0));
    }
    *(undefined2 *)((int)v + 0x3c) = 1;
  }
  return;
}


/* ==== cdb_default_space @ 00465620 ==== */

int cdb_default_space(void)

{
  if (*(int *)(cur_dtype + 4) == 0x2cb) {
    return 0;
  }
  return *(int *)(cur_sim + 0x3fb8);
}


/* ==== cdb_detect_space_model @ 00465640 ==== */

void cdb_detect_space_model(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar3 = 0xffff;
  if (0 < *(int *)(cur_sim + 0x3fd8)) {
    do {
      iVar4 = iVar5 * 0x20;
      iVar1 = cdb_symname_is(s__file_004d3440,(void *)(*(int *)(cur_sim + 0x3fe0) + iVar4));
      if ((iVar1 != 0) && (*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar4) == 0x67)) break;
      iVar5 = iVar5 + 1 + *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x1c + iVar4);
    } while (iVar5 < *(int *)(cur_sim + 0x3fd8));
  }
  if (iVar5 + 1 < *(int *)(cur_sim + 0x3fd8)) {
    iVar3 = *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x14 + (iVar5 + 1) * 0x20);
  }
  if (iVar3 == 1) {
    if ((*(int *)(cur_dtype + 4) == 0x2c7) || (uVar2 = 2, *(int *)(cur_dtype + 4) == 0x2c9)) {
      uVar2 = 1;
    }
    *(undefined4 *)(cur_sim + 0x3fb8) = uVar2;
    return;
  }
  if (iVar3 == 2) {
LAB_00465713:
    *(undefined4 *)(cur_sim + 0x3fb8) = 1;
    return;
  }
  if (iVar3 != 3) {
    iVar5 = *(int *)(cur_dtype + 4);
    if (((iVar5 == 0x2c5) || (iVar5 == 0x2c8)) || (iVar5 == 0x2ca)) {
      *(undefined4 *)(cur_sim + 0x3fb8) = 2;
      return;
    }
    if (iVar5 != 0x2c6) goto LAB_00465713;
  }
  *(undefined4 *)(cur_sim + 0x3fb8) = 3;
  return;
}


/* ==== cdb_pc_in_function @ 00465750 ==== */

int __cdecl cdb_pc_in_function(int func_sym,int block_depth)

{
  ulong pc;
  int iVar1;
  
  if ((func_sym == -1) && (block_depth == -1)) {
    return 1;
  }
  pc = cdb_frame_pc();
  if (block_depth == -1) {
    iVar1 = cdb_func_of_pc_checked(pc);
    return (uint)(func_sym == iVar1);
  }
  iVar1 = cdb_func_of_pc_checked(pc);
  if (func_sym == iVar1) {
    iVar1 = cdb_enclosing_block(pc);
    if (block_depth <= iVar1) {
      return 1;
    }
  }
  return 0;
}


/* ==== cdb_line_index @ 004657c0 ==== */

int __cdecl cdb_line_index(ulong addr)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar5 = *(int *)(cur_sim + 0x3fec) + -1;
  if (*(int *)(cur_sim + 0x3fd8) == 0) {
    return 1;
  }
  iVar3 = iVar5 / 2;
  if (iVar5 < 0) {
    return 0;
  }
  iVar1 = *(int *)(cur_sim + 0x3ff0);
  do {
    uVar2 = *(uint *)(iVar1 + iVar3 * 0xc);
    if (addr < uVar2) {
      iVar5 = iVar3 + -1;
      iVar3 = (iVar5 + iVar6) / 2;
      if (iVar3 != 0) {
        piVar4 = (int *)(iVar1 + 8 + iVar3 * 0xc);
        do {
          if ((iVar3 < iVar6) || (*piVar4 != 0)) break;
          iVar3 = iVar3 + -1;
          piVar4 = piVar4 + -3;
        } while (iVar3 != 0);
      }
      if (iVar3 == 0) {
        return 0;
      }
      if (iVar3 < iVar6) {
        return 0;
      }
    }
    else {
      if (addr <= uVar2) {
        return 1;
      }
      iVar6 = iVar3 + 1;
      iVar3 = (iVar5 + iVar6) / 2;
      if (iVar3 != 0) {
        piVar4 = (int *)(iVar1 + 8 + iVar3 * 0xc);
        do {
          if ((iVar5 < iVar3) || (*piVar4 != 0)) break;
          iVar3 = iVar3 + 1;
          piVar4 = piVar4 + 3;
        } while (iVar3 != 0);
      }
      if (iVar3 == 0) {
        return 0;
      }
      if (iVar5 < iVar3) {
        return 0;
      }
    }
    if (iVar5 < iVar6) {
      return 0;
    }
  } while( true );
}


/* ==== cdb_enum_tag_sym @ 00465890 ==== */

int __cdecl cdb_enum_tag_sym(int member_sym)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = -1;
  iVar2 = 0;
  if (0 < member_sym) {
    do {
      if (iVar1 == -1) {
        iVar3 = iVar2 * 0x20 + *(int *)(cur_sim + 0x3fe0);
        if (*(int *)(iVar3 + 0x18) == 0xf) {
          iVar1 = iVar2;
        }
      }
      else {
        iVar3 = iVar2 * 0x20 + *(int *)(cur_sim + 0x3fe0);
        if (*(int *)(iVar3 + 0x18) != 0x10) {
          iVar1 = -1;
        }
      }
      iVar2 = iVar2 + 1 + *(int *)(iVar3 + 0x1c);
    } while (iVar2 < member_sym);
  }
  return iVar1;
}


/* ==== cdb_enum_member_by_value @ 004658f0 ==== */

int __cdecl cdb_enum_member_by_value(int enum_sym,long value)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(enum_sym * 0x20 + 0x1c + *(int *)(cur_sim + 0x3fe0)) + 1 + enum_sym;
  while ((iVar1 < *(int *)(cur_sim + 0x3fd8) &&
         (iVar2 = iVar1 * 0x20 + *(int *)(cur_sim + 0x3fe0), *(int *)(iVar2 + 0x18) == 0x10))) {
    if (*(int *)(iVar2 + 8) == value) {
      return iVar1;
    }
    iVar1 = iVar1 + 1 + *(int *)(iVar2 + 0x1c);
  }
  return -1;
}


/* ==== cdb_func_body_addr @ 00465950 ==== */

ulong __cdecl cdb_func_body_addr(ulong pc)

{
  int iVar1;
  
  iVar1 = cdb_func_of_pc(pc);
  if (iVar1 == -1) {
    return 0;
  }
  iVar1 = cdb_func_bf_sym(iVar1);
  if (iVar1 == -1) {
    return 0;
  }
  return *(ulong *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar1 * 0x20);
}


/* ==== cdb_sym_name_eq @ 00465990 ==== */

int __cdecl cdb_sym_name_eq(char *name,void *sym)

{
  byte bVar1;
  char cVar2;
  undefined3 extraout_var;
  byte *pbVar3;
  bool bVar4;
  
  cVar2 = cdb_symname_ptr(sym);
  if (*(char *)CONCAT31(extraout_var,cVar2) != 'F') {
    return 0;
  }
  pbVar3 = (byte *)((char *)CONCAT31(extraout_var,cVar2) + 1);
  while( true ) {
    bVar1 = *name;
    bVar4 = bVar1 < *pbVar3;
    if (bVar1 != *pbVar3) break;
    if (bVar1 == 0) {
      return 1;
    }
    bVar1 = name[1];
    bVar4 = bVar1 < pbVar3[1];
    if (bVar1 != pbVar3[1]) break;
    name = name + 2;
    pbVar3 = pbVar3 + 2;
    if (bVar1 == 0) {
      return 1;
    }
  }
  return (uint)(1 - bVar4 == (uint)(bVar4 != 0));
}


/* ==== cdb_func_of_pc @ 00465a00 ==== */

int __cdecl cdb_func_of_pc(ulong pc)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_10;
  
  iVar3 = 0;
  if (0 < *(int *)(cur_sim + 0x3fd8)) {
    iVar2 = *(int *)(cur_sim + 0x3fe0);
    do {
      iVar1 = iVar3 * 0x20 + iVar2;
      if (((byte)*(undefined4 *)(iVar3 * 0x20 + 0x14 + iVar2) & 0x30) == 0x20) {
        if (*(uint *)(iVar1 + 8) <= pc) {
          iVar4 = (iVar3 + 1) * 0x20 + iVar2;
          iVar5 = *(int *)(iVar4 + 0x10) * 0x20;
          if (((byte)*(undefined4 *)(iVar5 + 0x14 + iVar2) & 0x30) == 0x20) {
            local_10 = *(uint *)(iVar5 + iVar2 + 8);
          }
          else {
            iVar4 = *(int *)(iVar4 + 4);
            if (iVar4 != 0) {
              local_10 = *(uint *)(iVar1 + 8) + iVar4;
            }
          }
          if (pc < local_10) {
            return iVar3;
          }
        }
        if (*(int *)(iVar1 + 0x1c) < 1) {
          iVar3 = iVar3 + 1;
        }
        else {
          iVar1 = *(int *)((iVar3 + 1) * 0x20 + 0x10 + iVar2);
          iVar3 = iVar3 + 1;
          if (0 < iVar1) {
            iVar3 = iVar1;
          }
        }
      }
      else {
        iVar3 = iVar3 + 1 + *(int *)(iVar1 + 0x1c);
      }
    } while (iVar3 < *(int *)(cur_sim + 0x3fd8));
  }
  return -1;
}


/* ==== cdb_func_of_pc_checked @ 00465ad0 ==== */

int __cdecl cdb_func_of_pc_checked(ulong pc)

{
  int func_sym;
  int iVar1;
  int iVar2;
  
  func_sym = cdb_func_of_pc(pc);
  if (func_sym != -1) {
    iVar1 = cdb_func_bf_sym(func_sym);
    if (iVar1 != -1) {
      iVar2 = cdb_next_eos_marker(func_sym);
      func_sym = iVar1;
      if ((iVar2 != -1) && (*(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20) < pc)) {
        func_sym = -1;
      }
    }
  }
  return func_sym;
}


/* ==== cdb_next_eos_marker @ 00465b30 ==== */

int __cdecl cdb_next_eos_marker(int sym)

{
  int iVar1;
  int *piVar2;
  
  if (-1 < sym) {
    iVar1 = sym + 1 + *(int *)(sym * 0x20 + 0x1c + *(int *)(cur_sim + 0x3fe0));
    if (iVar1 < *(int *)(cur_sim + 0x3fd8)) {
      piVar2 = (int *)(iVar1 * 0x20 + 0x18 + *(int *)(cur_sim + 0x3fe0));
      do {
        if (*piVar2 == -1) {
          return iVar1;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 8;
      } while (iVar1 < *(int *)(cur_sim + 0x3fd8));
    }
  }
  return -1;
}


/* ==== cdb_func_bf_sym @ 00465b80 ==== */

int __cdecl cdb_func_bf_sym(int func_sym)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if ((-1 < func_sym) && (iVar2 = *(int *)(cur_sim + 0x3fd8), func_sym < iVar2)) {
    iVar1 = *(int *)(cur_sim + 0x3fe0);
    iVar4 = func_sym + 1 + *(int *)(func_sym * 0x20 + 0x1c + iVar1);
    if (iVar4 < iVar2) {
      piVar3 = (int *)(iVar4 * 0x20 + 0x18 + iVar1);
      while (*piVar3 != 100) {
        if (*piVar3 == 0x65) {
          iVar2 = cdb_symname_is(&DAT_004c7c28,(void *)(iVar4 * 0x20 + iVar1));
          if (iVar2 == 0) {
            return -1;
          }
          return iVar4;
        }
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 8;
        if (iVar2 <= iVar4) {
          return -1;
        }
      }
    }
  }
  return -1;
}


/* ==== cdb_func_ef_sym @ 00465c00 ==== */

int __cdecl cdb_func_ef_sym(int func_sym)

{
  void *sym;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  if ((func_sym < 0) ||
     (iVar4 = func_sym + 1 + *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x1c + func_sym * 0x20),
     *(int *)(cur_sim + 0x3fd8) <= iVar4)) {
    return -1;
  }
  iVar3 = iVar4 * 0x20;
  iVar1 = cur_sim;
  do {
    sym = (void *)(*(int *)(iVar1 + 0x3fe0) + iVar3);
    if (*(int *)((int)sym + 0x18) == 0x65) {
      iVar1 = cdb_symname_is(&DAT_004c7c28,sym);
      if (iVar1 == 0) {
        if (iVar2 != 1) {
          return -1;
        }
        return iVar4;
      }
      iVar2 = iVar2 + 1;
      iVar1 = cur_sim;
      if (1 < iVar2) {
        return -1;
      }
    }
    iVar4 = iVar4 + 1;
    iVar3 = iVar3 + 0x20;
    if (*(int *)(iVar1 + 0x3fd8) <= iVar4) {
      return -1;
    }
  } while( true );
}


/* ==== cdb_struct_layout_eq @ 00465c90 ==== */

int __cdecl cdb_struct_layout_eq(int sym1,int sym2)

{
  byte bVar1;
  char cVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  
  iVar6 = *(int *)(cur_sim + 0x3fd8);
  if ((((sym1 < iVar6) && (-1 < sym1)) && (sym2 < iVar6)) && (-1 < sym2)) {
    if (sym1 == sym2) {
      return 1;
    }
    iVar4 = *(int *)(cur_sim + 0x3fe0);
    iVar5 = sym1 + 1 + *(int *)(sym1 * 0x20 + 0x1c + iVar4);
    iVar8 = sym2 + 1 + *(int *)(sym2 * 0x20 + 0x1c + iVar4);
    if (((iVar5 < iVar6) && (-1 < iVar5)) && ((iVar8 < iVar6 && (-1 < iVar8)))) {
      while (iVar8 < iVar6) {
        iVar6 = iVar5 * 0x20;
        if (*(int *)(iVar4 + 0x18 + iVar6) == 0x66) {
          return (uint)(*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar8 * 0x20) == 0x66);
        }
        iVar9 = iVar8 * 0x20;
        if (*(int *)(iVar4 + iVar9 + 0x18) == 0x66) {
          return 0;
        }
        cVar2 = cdb_symname_ptr((void *)(iVar4 + iVar9));
        pbVar7 = (byte *)CONCAT31(extraout_var,cVar2);
        cVar2 = cdb_symname_ptr((void *)(*(int *)(cur_sim + 0x3fe0) + iVar6));
        pbVar3 = (byte *)CONCAT31(extraout_var_00,cVar2);
        do {
          bVar1 = *pbVar3;
          bVar10 = bVar1 < *pbVar7;
          if (bVar1 != *pbVar7) {
LAB_00465d8f:
            iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
            goto LAB_00465d94;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar10 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_00465d8f;
          pbVar3 = pbVar3 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_00465d94:
        if (iVar4 != 0) {
          return 0;
        }
        iVar4 = *(int *)(cur_sim + 0x3fe0);
        iVar4 = cdb_types_match(*(ulong *)(iVar4 + 0x14 + iVar6),
                                *(int *)((iVar5 + 1) * 0x20 + iVar4),
                                *(ulong *)(iVar9 + 0x14 + iVar4),
                                *(int *)((iVar8 + 1) * 0x20 + iVar4));
        if (iVar4 == 0) {
          return 0;
        }
        iVar4 = *(int *)(cur_sim + 0x3fe0);
        iVar5 = iVar5 + 1 + *(int *)(iVar4 + 0x1c + iVar6);
        iVar8 = iVar8 + 1 + *(int *)(iVar9 + 0x1c + iVar4);
        iVar6 = *(int *)(cur_sim + 0x3fd8);
        if (iVar6 <= iVar5) {
          return 0;
        }
      }
    }
  }
  return 0;
}


/* ==== cdb_union_layout_eq @ 00465e30 ==== */

int __cdecl cdb_union_layout_eq(int sym1,int sym2)

{
  int iVar1;
  char cVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined3 extraout_var_00;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = *(int *)(cur_sim + 0x3fd8);
  if ((((sym1 < iVar4) && (-1 < sym1)) && (sym2 < iVar4)) && (-1 < sym2)) {
    if (sym1 == sym2) {
      return 1;
    }
    iVar3 = *(int *)(cur_sim + 0x3fe0);
    iVar7 = *(int *)(sym1 * 0x20 + 0x1c + iVar3) + 1 + sym1;
    iVar5 = *(int *)(sym2 * 0x20 + 0x1c + iVar3) + 1 + sym2;
    if (((iVar7 < iVar4) && (-1 < iVar7)) && ((iVar5 < iVar4 && (-1 < iVar5)))) {
      while (iVar5 < iVar4) {
        iVar4 = iVar7 * 0x20;
        if (*(int *)(iVar4 + 0x18 + iVar3) == 0x66) {
          return (uint)(*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar5 * 0x20) == 0x66);
        }
        iVar6 = iVar5 * 0x20;
        if (*(int *)(iVar6 + 0x18 + iVar3) == 0x66) {
          return 0;
        }
        cVar2 = cdb_symname_ptr((void *)(iVar4 + iVar3));
        iVar3 = cdb_find_member(sym2,(char *)CONCAT31(extraout_var,cVar2));
        if (iVar3 == -1) {
          return 0;
        }
        iVar1 = *(int *)(cur_sim + 0x3fe0);
        iVar3 = cdb_types_match(*(ulong *)(iVar4 + 0x14 + iVar1),
                                *(int *)((iVar7 + 1) * 0x20 + iVar1),
                                *(ulong *)(iVar3 * 0x20 + 0x14 + iVar1),
                                *(int *)((iVar3 + 1) * 0x20 + iVar1));
        if (iVar3 == 0) {
          return 0;
        }
        cVar2 = cdb_symname_ptr((void *)(*(int *)(cur_sim + 0x3fe0) + iVar6));
        iVar3 = cdb_find_member(sym1,(char *)CONCAT31(extraout_var_00,cVar2));
        if (iVar3 == -1) {
          return 0;
        }
        iVar1 = *(int *)(cur_sim + 0x3fe0);
        iVar3 = cdb_types_match(*(ulong *)(iVar6 + 0x14 + iVar1),
                                *(int *)((iVar5 + 1) * 0x20 + iVar1),
                                *(ulong *)(iVar3 * 0x20 + 0x14 + iVar1),
                                *(int *)((iVar3 + 1) * 0x20 + iVar1));
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = *(int *)(cur_sim + 0x3fe0);
        iVar7 = iVar7 + 1 + *(int *)(iVar4 + 0x1c + iVar3);
        iVar5 = iVar5 + 1 + *(int *)(iVar6 + 0x1c + iVar3);
        iVar4 = *(int *)(cur_sim + 0x3fd8);
        if (iVar4 <= iVar7) {
          return 0;
        }
      }
    }
  }
  return 0;
}


/* ==== cdb_enum_layout_eq @ 00466000 ==== */

int __cdecl cdb_enum_layout_eq(int sym1,int sym2)

{
  int iVar1;
  char cVar2;
  undefined3 extraout_var;
  int iVar3;
  undefined3 extraout_var_00;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar4 = *(int *)(cur_sim + 0x3fd8);
  if ((((sym1 < iVar4) && (-1 < sym1)) && (sym2 < iVar4)) && (-1 < sym2)) {
    if (sym1 == sym2) {
      return 1;
    }
    iVar3 = *(int *)(cur_sim + 0x3fe0);
    iVar5 = *(int *)(sym1 * 0x20 + 0x1c + iVar3) + 1 + sym1;
    iVar6 = *(int *)(sym2 * 0x20 + 0x1c + iVar3) + 1 + sym2;
    if (((iVar5 < iVar4) && (-1 < iVar5)) && ((iVar6 < iVar4 && (-1 < iVar6)))) {
      while (iVar6 < iVar4) {
        iVar4 = iVar5 * 0x20;
        if (*(int *)(iVar4 + 0x18 + iVar3) == 0x66) {
          return (uint)(*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar6 * 0x20) == 0x66);
        }
        iVar7 = iVar6 * 0x20;
        if (*(int *)(iVar7 + 0x18 + iVar3) == 0x66) {
          return 0;
        }
        cVar2 = cdb_symname_ptr((void *)(iVar4 + iVar3));
        iVar3 = cdb_find_member(sym2,(char *)CONCAT31(extraout_var,cVar2));
        if (iVar3 == -1) {
          return 0;
        }
        iVar8 = iVar3 * 0x20;
        iVar1 = *(int *)(cur_sim + 0x3fe0);
        iVar3 = cdb_types_match(*(ulong *)(iVar4 + 0x14 + iVar1),
                                *(int *)((iVar5 + 1) * 0x20 + iVar1),
                                *(ulong *)(iVar8 + 0x14 + iVar1),
                                *(int *)((iVar3 + 1) * 0x20 + iVar1));
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = *(int *)(cur_sim + 0x3fe0);
        if (*(int *)(iVar4 + 0xc + iVar3) != *(int *)(iVar8 + 0xc + iVar3)) {
          return 0;
        }
        if (*(int *)(iVar4 + 8 + iVar3) != *(int *)(iVar8 + 8 + iVar3)) {
          return 0;
        }
        cVar2 = cdb_symname_ptr((void *)(iVar3 + iVar7));
        iVar3 = cdb_find_member(sym1,(char *)CONCAT31(extraout_var_00,cVar2));
        if (iVar3 == -1) {
          return 0;
        }
        iVar8 = iVar3 * 0x20;
        iVar1 = *(int *)(cur_sim + 0x3fe0);
        iVar3 = cdb_types_match(*(ulong *)(iVar7 + 0x14 + iVar1),
                                *(int *)((iVar6 + 1) * 0x20 + iVar1),
                                *(ulong *)(iVar8 + 0x14 + iVar1),
                                *(int *)((iVar3 + 1) * 0x20 + iVar1));
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = *(int *)(cur_sim + 0x3fe0);
        if (*(int *)(iVar7 + 0xc + iVar3) != *(int *)(iVar8 + 0xc + iVar3)) {
          return 0;
        }
        if (*(int *)(iVar7 + 8 + iVar3) != *(int *)(iVar8 + 8 + iVar3)) {
          return 0;
        }
        iVar5 = iVar5 + 1 + *(int *)(iVar4 + 0x1c + iVar3);
        iVar6 = iVar6 + 1 + *(int *)(iVar7 + 0x1c + iVar3);
        iVar4 = *(int *)(cur_sim + 0x3fd8);
        if (iVar4 <= iVar5) {
          return 0;
        }
      }
    }
  }
  return 0;
}


/* ==== cdb_lookup_global @ 00466220 ==== */

int __cdecl cdb_lookup_global(char *name,int sclass)

{
  void *sym;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0;
  if (*(int *)(cur_sim + 0x3fd8) < 1) {
    return -1;
  }
  do {
    iVar3 = iVar4 * 0x20;
    sym = (void *)(*(int *)(cur_sim + 0x3fe0) + iVar3);
    if (*(int *)((int)sym + 0x18) == 100) {
      iVar1 = cdb_symname_is(&DAT_004d3408,sym);
      if (iVar1 == 0) {
LAB_00466283:
        iVar2 = iVar2 + -1;
      }
      else {
        iVar2 = iVar2 + 1;
      }
    }
    else if (*(int *)((int)sym + 0x18) == 0x65) {
      iVar1 = cdb_symname_is(&DAT_004c7c28,sym);
      if (iVar1 == 0) goto LAB_00466283;
      iVar2 = iVar2 + 1;
    }
    if (((iVar2 == 0) && (*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar3) == sclass)) &&
       (iVar1 = cdb_sym_name_eq(name,(void *)(*(int *)(cur_sim + 0x3fe0) + iVar3)), iVar1 != 0)) {
      return iVar4;
    }
    iVar4 = iVar4 + 1 + *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x1c + iVar3);
    if (*(int *)(cur_sim + 0x3fd8) <= iVar4) {
      return -1;
    }
  } while( true );
}


/* ==== cdb_lookup_symbol @ 004662f0 ==== */

int __cdecl cdb_lookup_symbol(char *name)

{
  ulong pc;
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  if (name == (char *)0x0) {
    return -1;
  }
  pc = cdb_frame_pc();
  iVar1 = cdb_enclosing_block(pc);
  iVar2 = iVar1;
  if (iVar1 != -1) {
    do {
      if (iVar3 != -1) break;
      iVar3 = cdb_find_local(iVar2,name);
      if (iVar3 == -1) {
        iVar1 = cdb_parent_block(iVar2);
        iVar2 = iVar1;
      }
    } while (iVar2 != -1);
    if (iVar2 != -1) {
      iVar2 = cdb_func_of_pc_checked(pc);
      goto LAB_00466381;
    }
  }
  iVar2 = cdb_func_of_pc_checked(pc);
  iVar1 = -1;
  if (iVar2 != -1) {
    iVar3 = cdb_find_arg(iVar2,name);
  }
LAB_00466381:
  if (iVar3 == -1) {
    iVar3 = cdb_lookup_static_or_ext(name);
    iVar1 = -1;
    iVar2 = -1;
  }
  if (iVar1 == -1) {
    if ((iVar2 != -1) && (cdb_lookup_cache_depth == -1)) {
      cdb_lookup_cache_sym = iVar2;
    }
  }
  else if (cdb_lookup_cache_depth < iVar1) {
    cdb_lookup_cache_depth = iVar1;
    cdb_lookup_cache_sym = iVar2;
    return iVar3;
  }
  return iVar3;
}


/* ==== cdb_lookup_static_or_ext @ 004663e0 ==== */

int __cdecl cdb_lookup_static_or_ext(char *name)

{
  void *sym;
  ulong addr;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *name_00;
  
  iVar5 = 0;
  addr = cdb_frame_pc();
  iVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0xc))(0,addr);
  iVar2 = dbg_addr_to_file_sym(addr,iVar1);
  iVar1 = 0;
  iVar4 = 0;
  if (*(int *)(cur_sim + 0x3fd8) < 1) {
    return -1;
  }
  do {
    iVar6 = iVar1 * 0x20;
    iVar3 = *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar6);
    if (iVar3 == 100) {
      name_00 = &DAT_004d3408;
LAB_0046644d:
      iVar3 = cdb_symname_is(name_00,(void *)(*(int *)(cur_sim + 0x3fe0) + iVar6));
      if (iVar3 == 0) {
        iVar4 = iVar4 + -1;
      }
      else {
        iVar4 = iVar4 + 1;
      }
    }
    else {
      if (iVar3 == 0x65) {
        name_00 = &DAT_004c7c28;
        goto LAB_0046644d;
      }
      if (iVar3 == 0x67) {
        iVar5 = iVar1;
      }
    }
    if (((iVar4 == 0) &&
        (sym = (void *)(*(int *)(cur_sim + 0x3fe0) + iVar6),
        *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x10 + iVar6) != -2)) &&
       ((iVar3 = *(int *)((int)sym + 0x18), iVar3 == 2 || (iVar3 == 3)))) {
      iVar3 = cdb_sym_name_eq(name,sym);
      if ((iVar3 != 0) &&
         ((*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar6) == 2 || (iVar5 == iVar2)))) {
        return iVar1;
      }
    }
    iVar1 = iVar1 + 1 + *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x1c + iVar6);
    if (*(int *)(cur_sim + 0x3fd8) <= iVar1) {
      return -1;
    }
  } while( true );
}


/* ==== cdb_enclosing_block @ 00466500 ==== */

int __cdecl cdb_enclosing_block(ulong pc)

{
  int iVar1;
  int iVar2;
  void *sym;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_400 [256];
  
  iVar4 = 0;
  iVar3 = 0;
  local_400[0] = -1;
  if (*(int *)(cur_sim + 0x3fd8) < 1) {
    return -1;
  }
  piVar6 = local_400;
  iVar2 = cur_sim;
  do {
    iVar5 = iVar3 * 0x20;
    sym = (void *)(*(int *)(iVar2 + 0x3fe0) + iVar5);
    if (*(int *)((int)sym + 0x18) == 100) {
      iVar1 = cdb_symname_is(&DAT_004d3408,sym);
      iVar2 = cur_sim;
      if (iVar1 == 0) {
        if (*piVar6 != -1) {
          if (pc <= *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar5)) {
            return local_400[iVar4];
          }
          *piVar6 = -1;
        }
        iVar4 = iVar4 + -1;
        piVar6 = piVar6 + -1;
        if (iVar4 < 0) {
          return -1;
        }
      }
      else {
        iVar4 = iVar4 + 1;
        piVar6 = piVar6 + 1;
        if (0xff < iVar4) {
          return -1;
        }
        if (pc < *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar5)) {
          *piVar6 = -1;
        }
        else {
          *piVar6 = iVar3;
        }
      }
    }
    iVar3 = iVar3 + 1 + *(int *)(*(int *)(iVar2 + 0x3fe0) + 0x1c + iVar5);
    if (*(int *)(iVar2 + 0x3fd8) <= iVar3) {
      return -1;
    }
  } while( true );
}


/* ==== cdb_find_local @ 00466620 ==== */

int __cdecl cdb_find_local(int block_sym,char *name)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *(int *)(cur_sim + 0x3fe0);
  iVar5 = *(int *)(block_sym * 0x20 + 0x1c + iVar2) + 1 + block_sym;
  iVar3 = cur_sim;
  if (iVar5 < *(int *)(cur_sim + 0x3fd8)) {
    while( true ) {
      iVar4 = iVar5 * 0x20;
      iVar1 = *(int *)(iVar4 + 0x18 + iVar2);
      if (iVar1 == 100) break;
      if ((((*(int *)(iVar4 + iVar2 + 0x10) == -1) &&
           (((iVar1 == 1 || (iVar1 == 4)) || (iVar1 == 0x13)))) || (iVar1 == 3)) &&
         (iVar2 = cdb_sym_name_eq(name,(void *)(iVar4 + iVar2)), iVar3 = cur_sim, iVar2 != 0)) {
        return iVar5;
      }
      iVar2 = *(int *)(iVar3 + 0x3fe0);
      iVar5 = iVar5 + 1 + *(int *)(iVar4 + 0x1c + iVar2);
      if (*(int *)(iVar3 + 0x3fd8) <= iVar5) {
        return -1;
      }
    }
  }
  return -1;
}


/* ==== cdb_find_in_block @ 004666c0 ==== */

int __cdecl cdb_find_in_block(int block_sym,char *name,int sclass)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *(int *)(cur_sim + 0x3fe0);
  iVar5 = *(int *)(block_sym * 0x20 + 0x1c + iVar2) + 1 + block_sym;
  iVar3 = cur_sim;
  if (iVar5 < *(int *)(cur_sim + 0x3fd8)) {
    while( true ) {
      iVar4 = iVar5 * 0x20;
      iVar1 = *(int *)(iVar4 + 0x18 + iVar2);
      if (iVar1 == 100) break;
      if ((iVar1 == sclass) &&
         (iVar2 = cdb_sym_name_eq(name,(void *)(iVar4 + iVar2)), iVar3 = cur_sim, iVar2 != 0)) {
        return iVar5;
      }
      iVar2 = *(int *)(iVar3 + 0x3fe0);
      iVar5 = iVar5 + 1 + *(int *)(iVar4 + 0x1c + iVar2);
      if (*(int *)(iVar3 + 0x3fd8) <= iVar5) {
        return -1;
      }
    }
  }
  return -1;
}


/* ==== cdb_find_arg @ 00466750 ==== */

int __cdecl cdb_find_arg(int func_sym,char *name)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *(int *)(cur_sim + 0x3fe0);
  iVar5 = *(int *)(func_sym * 0x20 + 0x1c + iVar2) + 1 + func_sym;
  iVar3 = cur_sim;
  if (iVar5 < *(int *)(cur_sim + 0x3fd8)) {
    while( true ) {
      iVar4 = iVar5 * 0x20;
      iVar1 = *(int *)(iVar4 + 0x18 + iVar2);
      if ((iVar1 == 0x65) || (iVar1 == 100)) break;
      if (((iVar1 == 9) || ((iVar1 == 0x13 || (iVar1 == 0x11)))) &&
         (iVar2 = cdb_sym_name_eq(name,(void *)(iVar4 + iVar2)), iVar3 = cur_sim, iVar2 != 0)) {
        return iVar5;
      }
      iVar2 = *(int *)(iVar3 + 0x3fe0);
      iVar5 = iVar5 + 1 + *(int *)(iVar4 + 0x1c + iVar2);
      if (*(int *)(iVar3 + 0x3fd8) <= iVar5) {
        return -1;
      }
    }
  }
  return -1;
}


/* ==== cdb_parent_block @ 004667f0 ==== */

int __cdecl cdb_parent_block(int sym)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int local_400 [256];
  
  iVar2 = 0;
  iVar5 = 0;
  local_400[0] = -1;
  if (0 < sym) {
    piVar3 = local_400;
    do {
      iVar4 = iVar5 * 0x20;
      if (*(int *)(*(int *)(cur_sim + 0x3fe0) + 0x18 + iVar4) == 100) {
        iVar1 = cdb_symname_is(&DAT_004d3408,(void *)(*(int *)(cur_sim + 0x3fe0) + iVar4));
        if (iVar1 == 0) {
          iVar2 = iVar2 + -1;
          piVar3 = piVar3 + -1;
          if (iVar2 < 0) {
            return -1;
          }
        }
        else {
          iVar2 = iVar2 + 1;
          piVar3 = piVar3 + 1;
          if (0xff < iVar2) {
            return -1;
          }
          *piVar3 = iVar5;
        }
      }
      iVar5 = iVar5 + 1 + *(int *)(*(int *)(cur_sim + 0x3fe0) + 0x1c + iVar4);
    } while (iVar5 < sym);
  }
  if ((-1 < iVar2) && (iVar2 < 0x100)) {
    return local_400[iVar2];
  }
  return -1;
}


/* ==== cdb_symname_ptr @ 004668b0 ==== */

char __cdecl cdb_symname_ptr(void *sym)

{
  uint uVar1;
  
  if (*(int *)sym == 0) {
    uVar1 = *(uint *)((int)sym + 4);
    if ((3 < uVar1) && ((int)uVar1 <= *(int *)(cur_sim + 0x3fe8))) {
      return (char)*(undefined4 *)(cur_sim + 0x3fe4) + (char)uVar1;
    }
    expr_error(s_invalid_string_table_offset_004c7ad4);
    sym = &empty_str;
  }
  return (char)sym;
}


/* ==== cdb_symname_is @ 004668f0 ==== */

int __cdecl cdb_symname_is(char *name,void *sym)

{
  byte bVar1;
  char cVar2;
  undefined3 extraout_var;
  byte *pbVar3;
  bool bVar4;
  
  cVar2 = cdb_symname_ptr(sym);
  pbVar3 = (byte *)CONCAT31(extraout_var,cVar2);
  while( true ) {
    bVar1 = *name;
    bVar4 = bVar1 < *pbVar3;
    if (bVar1 != *pbVar3) break;
    if (bVar1 == 0) {
      return 1;
    }
    bVar1 = name[1];
    bVar4 = bVar1 < pbVar3[1];
    if (bVar1 != pbVar3[1]) break;
    name = name + 2;
    pbVar3 = pbVar3 + 2;
    if (bVar1 == 0) {
      return 1;
    }
  }
  return (uint)(1 - bVar4 == (uint)(bVar4 != 0));
}


