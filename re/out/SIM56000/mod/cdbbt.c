/* ==== cdb_build_backtrace @ 0046c000 ==== */

void cdb_build_backtrace(void)

{
  char cVar1;
  code *pcVar2;
  char cVar3;
  char *pcVar4;
  long lVar5;
  undefined4 *extraout_EAX;
  uint uVar6;
  undefined3 extraout_var;
  int iVar7;
  char *extraout_EAX_00;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  char *extraout_EAX_01;
  char *extraout_EAX_02;
  ulong cpc;
  uint uVar8;
  ulong pc;
  long lVar9;
  char *pcVar10;
  char *pcVar11;
  ulong uStack_128;
  ulong local_124;
  uint uStack_120;
  int local_11c;
  int local_118;
  int local_114;
  long local_110;
  int iStack_10c;
  undefined1 auStack_108 [4];
  long lStack_104;
  char acStack_100 [256];
  
  pc = *(ulong *)(cur_dev + 0x1c);
  iVar7 = *(int *)(cur_dev + 4);
  lVar9 = 0;
  local_118 = 0;
  local_11c = 0;
  if ((*(int *)(cur_itype + 0x1c) == 0) ||
     (pcVar2 = *(code **)(*(int *)(cur_itype + 0x1c) + 0x14), pcVar2 == (code *)0x0)) {
    if (cdb_arch == 0x2c7) {
      pcVar4 = &DAT_004b2940;
      lVar9 = cdb_frame_adjust(pc);
    }
    else {
      pcVar4 = &DAT_004b2948;
    }
    lVar5 = periph_find_reg(iVar7,pcVar4,&local_114,&local_110);
    if (lVar5 == 0) {
      cdb_internal_error(0x4d4060,0x25c);
      return;
    }
    lVar5 = periph_call(iVar7,local_114,local_110,(long)&local_124);
    if (lVar5 == 0) {
      cdb_c_error(s_unable_to_read_frame_register_004d4040);
      return;
    }
    local_124 = local_124 + lVar9;
  }
  else {
    local_124 = (*pcVar2)();
  }
  if ((*(int *)(cur_itype + 0x1c) == 0) ||
     (pcVar2 = *(code **)(*(int *)(cur_itype + 0x1c) + 0x10), pcVar2 == (code *)0x0)) {
    lVar9 = cdb_frame_adjust(pc);
    pcVar4 = &DAT_004b2940;
    if (cdb_arch != 0x2c7) {
      pcVar4 = &DAT_004b2930;
    }
    lVar5 = periph_find_reg(iVar7,pcVar4,&local_114,&local_110);
    if (lVar5 == 0) {
      cdb_internal_error(0x4d4060,0x27e);
      return;
    }
    lVar5 = periph_call(iVar7,local_114,local_110,(long)&uStack_128);
    if (lVar5 == 0) {
      cdb_c_error(s_unable_to_read_stack_register_004d4020);
      return;
    }
    uStack_128 = uStack_128 + lVar9;
  }
  else {
    uStack_128 = (*pcVar2)();
  }
  lVar9 = periph_find_reg(iVar7,&DAT_004b2928,&iStack_10c,&lStack_104);
  if ((lVar9 != 0) &&
     (lVar9 = periph_call(iVar7,iStack_10c,lStack_104,(long)auStack_108), lVar9 == 0)) {
    cdb_c_error(s_unable_to_read_hardware_sp_004d4004);
    return;
  }
  cdb_free_frames();
  do {
    cdb_malloc(0x1c);
    uVar6 = cdb_func_of_pc(pc);
    uStack_120 = uVar6;
    if (((int)uVar6 < 1) || (*(int *)(cur_sim + 0x3fd8) <= (int)uVar6)) {
      sprintf(acStack_100,s____2d_p_0x_lx_in___50s___004d3fe8,local_11c,pc,&DAT_004d3fdc);
LAB_0046c263:
      local_118 = 1;
    }
    else {
      cVar3 = cdb_sym_name(uVar6);
      sprintf(acStack_100,s____2d_p_0x_lx_in___50s___004d3fe8,local_11c,pc,
              CONCAT31(extraout_var,cVar3));
      iVar7 = cdb_sym_name_eq(&DAT_004d3fe0,(void *)(*(int *)(cur_sim + 0x3fe0) + uVar6 * 0x20));
      if (iVar7 != 0) goto LAB_0046c263;
    }
    uVar6 = 0xffffffff;
    pcVar4 = acStack_100;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar3 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar3 != '\0');
    cdb_malloc(~uVar6);
    uVar6 = 0xffffffff;
    *extraout_EAX = extraout_EAX_00;
    pcVar4 = acStack_100;
    do {
      pcVar11 = pcVar4;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar11 = pcVar4 + 1;
      cVar3 = *pcVar4;
      pcVar4 = pcVar11;
    } while (cVar3 != '\0');
    uVar6 = ~uVar6;
    pcVar4 = pcVar11 + -uVar6;
    pcVar11 = extraout_EAX_00;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar11 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar11 = pcVar11 + 1;
    }
    extraout_EAX[1] = pc;
    extraout_EAX[2] = local_124;
    extraout_EAX[3] = uStack_128;
    cVar3 = cdb_scan_prologue(pc,uStack_128);
    extraout_EAX[4] = CONCAT31(extraout_var_00,cVar3);
    extraout_EAX[6] = 0;
    extraout_EAX[5] = 0;
    if (*(int *)(cur_sim + 0x3fac) == 0) {
      *(undefined4 **)(cur_sim + 0x3fb0) = extraout_EAX;
      *(undefined4 **)(cur_sim + 0x3fac) = extraout_EAX;
      *(undefined4 **)(cur_sim + 0x3fb4) = extraout_EAX;
    }
    else {
      *(undefined4 **)(*(int *)(cur_sim + 0x3fb0) + 0x18) = extraout_EAX;
      *(int *)(*(int *)(*(int *)(cur_sim + 0x3fb0) + 0x18) + 0x14) = *(int *)(cur_sim + 0x3fb0);
      *(undefined4 *)(cur_sim + 0x3fb0) = *(undefined4 *)(*(int *)(cur_sim + 0x3fb0) + 0x18);
      *(undefined4 *)(cur_sim + 0x3fb4) = *(undefined4 *)(cur_sim + 0x3fb0);
    }
    if (((int)uStack_120 < 1) || (*(int *)(cur_sim + 0x3fd8) <= (int)uStack_120)) {
      uVar6 = 0xffffffff;
      pcVar4 = (char *)*extraout_EAX;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar3 != '\0');
      cdb_realloc((char *)*extraout_EAX,~uVar6 + 1);
      uVar6 = 0xffffffff;
      *extraout_EAX = extraout_EAX_02;
      pcVar4 = &DAT_004d3fd8;
      do {
        pcVar11 = pcVar4;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar11;
      } while (cVar3 != '\0');
      uVar6 = ~uVar6;
      iVar7 = -1;
      pcVar4 = extraout_EAX_02;
      do {
        pcVar10 = pcVar4;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar10 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar10;
      } while (cVar3 != '\0');
      pcVar4 = pcVar11 + -uVar6;
      pcVar11 = pcVar10 + -1;
      for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar11 = pcVar11 + 4;
      }
    }
    else {
      cVar3 = frame_locals_string(uStack_120,local_124);
      uVar6 = 0xffffffff;
      pcVar4 = (char *)CONCAT31(extraout_var_01,cVar3);
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      uStack_120 = ~uVar6 - 1;
      uVar6 = 0xffffffff;
      pcVar4 = (char *)*extraout_EAX;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      cdb_realloc((char *)*extraout_EAX,uStack_120 + ~uVar6 + 1);
      uStack_120 = 0xffffffff;
      *extraout_EAX = extraout_EAX_01;
      pcVar4 = (char *)CONCAT31(extraout_var_01,cVar3);
      do {
        pcVar11 = pcVar4;
        if (uStack_120 == 0) break;
        uStack_120 = uStack_120 - 1;
        pcVar11 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar11;
      } while (cVar3 != '\0');
      uStack_120 = ~uStack_120;
      iVar7 = -1;
      pcVar4 = extraout_EAX_01;
      do {
        pcVar10 = pcVar4;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar10 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar10;
      } while (cVar3 != '\0');
      pcVar4 = pcVar11 + -uStack_120;
      pcVar11 = pcVar10 + -1;
      for (uVar6 = uStack_120 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar6 = uStack_120 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar11 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar11 = pcVar11 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar4 = &DAT_004d3fd8;
      do {
        pcVar11 = pcVar4;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar11;
      } while (cVar3 != '\0');
      uVar6 = ~uVar6;
      iVar7 = -1;
      pcVar4 = (char *)*extraout_EAX;
      do {
        pcVar10 = pcVar4;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar10 = pcVar4 + 1;
        cVar3 = *pcVar4;
        pcVar4 = pcVar10;
      } while (cVar3 != '\0');
      pcVar4 = pcVar11 + -uVar6;
      pcVar11 = pcVar10 + -1;
      for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar11 = pcVar11 + 4;
      }
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar11 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar11 = pcVar11 + 1;
    }
    if (local_118 != 0) {
      *(undefined4 *)(cur_sim + 0x3fb4) = *(undefined4 *)(cur_sim + 0x3fac);
      return;
    }
    cpc = cdb_caller_pc(pc,local_124,uStack_128,auStack_108);
    local_124 = cdb_caller_fp(pc,local_124,uStack_128,cpc);
    uStack_128 = cdb_caller_sp(pc,uStack_128,cpc);
    local_11c = local_11c + 1;
    pc = cpc;
  } while( true );
}


/* ==== cdb_free_frames @ 0046c4c0 ==== */

void cdb_free_frames(void)

{
  undefined4 *puVar1;
  void *pvVar2;
  void *p;
  undefined4 *p_00;
  
  p_00 = *(undefined4 **)(cur_sim + 0x3fac);
  while (p_00 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)p_00[6];
    if ((void *)*p_00 != (void *)0x0) {
      cdb_free((void *)*p_00);
    }
    p = (void *)p_00[4];
    while (p != (void *)0x0) {
      pvVar2 = *(void **)((int)p + 0x10);
      cdb_free(p);
      p = pvVar2;
    }
    cdb_free(p_00);
    p_00 = puVar1;
  }
  *(undefined4 *)(cur_sim + 0x3fb4) = 0;
  *(undefined4 *)(cur_sim + 0x3fb0) = 0;
  *(undefined4 *)(cur_sim + 0x3fac) = 0;
  return;
}


/* ==== cdb_frame_first @ 0046c540 ==== */

void cdb_frame_first(void)

{
  return;
}


/* ==== cdb_frame_last @ 0046c550 ==== */

void cdb_frame_last(void)

{
  return;
}


/* ==== cdb_frame_current @ 0046c560 ==== */

void cdb_frame_current(void)

{
  return;
}


/* ==== cdb_set_frame_current @ 0046c570 ==== */

void __cdecl cdb_set_frame_current(void *frame)

{
  *(void **)(cur_sim + 0x3fb4) = frame;
  return;
}


/* ==== cdb_frame_refresh_text @ 0046c590 ==== */

void __cdecl cdb_frame_refresh_text(void *frame)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  char *extraout_EAX;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  if (((frame != (void *)0x0) && (iVar3 = cdb_func_of_pc(*(ulong *)((int)frame + 4)), 0 < iVar3)) &&
     (iVar3 < *(int *)(cur_sim + 0x3fd8))) {
    strtok(*(char **)frame,&DAT_004d4068);
    cVar2 = frame_locals_string(iVar3,*(int *)((int)frame + 8));
    uVar4 = 0xffffffff;
    pcVar6 = (char *)CONCAT31(extraout_var,cVar2);
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    uVar5 = 0xffffffff;
    pcVar6 = *(char **)frame;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    cdb_realloc(*(char **)frame,~uVar4 + ~uVar5 + 1);
    uVar4 = 0xffffffff;
    *(char **)frame = extraout_EAX;
    pcVar6 = &DAT_004d4068;
    do {
      pcVar8 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar3 = -1;
    pcVar6 = extraout_EAX;
    do {
      pcVar7 = pcVar6;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    pcVar6 = pcVar8 + -uVar4;
    pcVar8 = pcVar7 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar6 = (char *)CONCAT31(extraout_var,cVar2);
    do {
      pcVar8 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    iVar3 = -1;
    pcVar6 = *(char **)frame;
    do {
      pcVar7 = pcVar6;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar7 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar2 != '\0');
    pcVar6 = pcVar8 + -uVar4;
    pcVar8 = pcVar7 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar6 = &DAT_004d3fd8;
    do {
      pcVar8 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    iVar3 = -1;
    pcVar6 = *(char **)frame;
    do {
      pcVar7 = pcVar6;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar7 = pcVar6 + 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar2 != '\0');
    pcVar6 = pcVar8 + -uVar4;
    pcVar8 = pcVar7 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  return;
}


/* ==== cdb_frame_pc @ 0046c6a0 ==== */

ulong cdb_frame_pc(void)

{
  int extraout_EAX;
  
  cdb_frame_current();
  if (extraout_EAX == 0) {
    return *(ulong *)(cur_dev + 0x1c);
  }
  return *(ulong *)(extraout_EAX + 4);
}


/* ==== cdb_frame_fp @ 0046c6c0 ==== */

ulong cdb_frame_fp(void)

{
  int devidx;
  code *pcVar1;
  int extraout_EAX;
  ulong uVar2;
  long lVar3;
  char *name;
  long lVar4;
  long local_c;
  int local_8;
  int local_4;
  
  lVar4 = 0;
  cdb_frame_current();
  cdb_frame_current();
  devidx = *(int *)(cur_dev + 4);
  if (extraout_EAX != 0) {
    return *(ulong *)(extraout_EAX + 8);
  }
  if ((*(int *)(cur_itype + 0x1c) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_itype + 0x1c) + 0x14), pcVar1 != (code *)0x0)) {
    uVar2 = (*pcVar1)();
    return uVar2;
  }
  if (cdb_arch == 0x2c7) {
    name = &DAT_004b2940;
  }
  else {
    if (cdb_arch == 0x2c5) {
LAB_0046c737:
      if ((cdb_arch != 0x2c8) && ((cdb_arch != 0x2cb && (cdb_arch != 0x2ca)))) {
        name = &DAT_004b2948;
        goto LAB_0046c768;
      }
    }
    else if (cdb_arch != 0x2c8) {
      if ((cdb_arch != 0x2cb) && (cdb_arch != 0x2ca)) {
        name = &DAT_004b2948;
        goto LAB_0046c768;
      }
      goto LAB_0046c737;
    }
    name = &DAT_004b2930;
  }
  uVar2 = cdb_frame_pc();
  lVar4 = cdb_frame_adjust(uVar2);
LAB_0046c768:
  lVar3 = periph_find_reg(devidx,name,&local_8,&local_c);
  if (lVar3 == 0) {
    cdb_internal_error(0x4d4060,0x3be);
    return 0;
  }
  lVar3 = periph_call(devidx,local_8,local_c,(long)&local_4);
  if (lVar3 == 0) {
    cdb_c_error(s_unable_to_read_frame_register_004d4040);
    return 0;
  }
  return lVar4 + local_4;
}


/* ==== cdb_caller_pc @ 0046c7f0 ==== */

ulong __cdecl cdb_caller_pc(ulong pc,ulong fp,ulong sp,void *regs)

{
  code *pcVar1;
  ulong uVar2;
  
  if ((*(int *)(cur_itype + 0x1c) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_itype + 0x1c) + 4), pcVar1 != (code *)0x0)) {
    uVar2 = (*pcVar1)(pc,fp,sp,regs);
    return uVar2;
  }
  if (cdb_arch == 0x2c7) {
    uVar2 = cdb_caller_pc_56100(pc,fp,sp);
    return uVar2;
  }
  if (cdb_arch == 0x2c5) {
    uVar2 = cdb_caller_pc_56000(pc,fp,sp);
    return uVar2;
  }
  if (cdb_arch == 0x2c6) {
    uVar2 = cdb_caller_pc_96000(pc,fp,sp);
    return uVar2;
  }
  return 0;
}


/* ==== cdb_caller_pc_56100 @ 0046c890 ==== */

ulong __cdecl cdb_caller_pc_56100(ulong pc,ulong fp,ulong sp)

{
  undefined4 uVar1;
  uint uVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  int a;
  ulong uVar6;
  int func_sym;
  int iVar7;
  long lVar8;
  uint uVar9;
  int local_18;
  ulong local_c [3];
  
  uVar6 = pc;
  bVar3 = false;
  local_18 = 0;
  iVar5 = cdb_func_of_pc_checked(pc);
  if (iVar5 != -1) {
    uVar1 = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x34 + iVar5 * 0x20);
    iVar5 = *(int *)(cur_dev + 4);
    a = cdb_default_space();
    switch(uVar1) {
    case 0:
    case 1:
    case 4:
    case 5:
    case 0xc:
    case 0xd:
    case 0x10:
    case 0x11:
    case 0x14:
    case 0x15:
    case 0x1c:
    case 0x1d:
      uVar6 = cdb_hwstack_pop();
      return uVar6;
    }
    func_sym = cdb_func_of_pc(uVar6);
    if (((func_sym != -1) && (iVar7 = cdb_func_bf_sym(func_sym), func_sym != -1)) && (iVar7 != -1))
    {
      uVar2 = *(uint *)(iVar7 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
      uVar4 = *(uint *)(func_sym * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
      while (uVar4 < uVar2) {
        uVar9 = uVar4 + 1;
        lVar8 = dev_mem_read(iVar5,0,uVar4,(long)&pc);
        if (lVar8 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        uVar4 = uVar9;
        if (bVar3) {
          if (((pc & 0xfc1f) == 0x3806) || (pc == 0x1e6)) {
            local_18 = local_18 + 1;
          }
        }
        else if (pc == 0x3b06) {
          bVar3 = true;
        }
      }
      lVar8 = dev_mem_read(iVar5,a,(sp - local_18) + -1,(long)local_c);
      if (lVar8 != 0) {
        return local_c[0];
      }
      cdb_c_error(s_error_reading_from_memory_004d4090);
      return 0;
    }
  }
  return 0;
}


/* ==== cdb_hwstack_pop @ 0046ca50 ==== */

ulong cdb_hwstack_pop(void)

{
  uint uVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_34;
  long local_30;
  int local_2c;
  uint local_28;
  uint local_24;
  long local_20;
  int local_1c;
  long local_18;
  int local_14;
  long local_10;
  int local_c;
  int local_8;
  ulong local_4;
  
  iVar4 = *(int *)(cur_dev + 4);
  if (((((cdb_arch == 0x2c7) || (cdb_arch == 0x2c9)) || (cdb_arch == 0x2c5)) ||
      ((cdb_arch == 0x2cb || (cdb_arch == 0x2ca)))) || (uVar5 = 0x80000000, cdb_arch == 0x2c8)) {
    uVar5 = 0x8000;
  }
  lVar2 = periph_find_reg(iVar4,&DAT_004b2924,&local_1c,&local_20);
  if ((lVar2 != 0) && (lVar2 = periph_call(iVar4,local_1c,local_20,(long)&local_24), lVar2 == 0)) {
    cdb_c_error(s_unable_to_read_sr_004d40fc);
    return 0;
  }
  if ((local_24 & uVar5) != 0) {
    lVar2 = periph_find_reg(iVar4,&DAT_004b2928,&local_2c,&local_30);
    if ((lVar2 != 0) && (lVar2 = periph_call(iVar4,local_2c,local_30,(long)&local_34), lVar2 == 0))
    {
      cdb_c_error(s_unable_to_read_sp_004d40e8);
      return 0;
    }
    local_8 = local_34;
    lVar2 = periph_find_reg(iVar4,&DAT_004b291c,&local_14,&local_18);
    local_28 = uVar5;
    uVar1 = uVar5;
    if (lVar2 == 0) {
      cdb_internal_error(0x4d4060,0x414);
      return 0;
    }
    while (uVar1 != 0) {
      lVar2 = periph_call(iVar4,local_14,local_18,(long)&local_28);
      if (lVar2 == 0) {
        cdb_c_error(s_unable_to_read_ssl_004d40ac);
        return 0;
      }
      local_34 = local_34 + -2;
      if (local_34 == 0) {
        cdb_internal_error(0x4d4060,0x428);
        return 0;
      }
      iVar3 = dev_write_reg(iVar4,local_2c,local_30,&local_34);
      if (iVar3 == 0) goto LAB_0046cc45;
      uVar1 = local_28 & uVar5;
    }
  }
  lVar2 = periph_find_reg(iVar4,&DAT_004b2920,&local_c,&local_10);
  if ((lVar2 != 0) && (lVar2 = periph_call(iVar4,local_c,local_10,(long)&local_4), lVar2 == 0)) {
    cdb_c_error(s_unable_to_read_ssh_004d40d4);
    return 0;
  }
  if (((local_24 & uVar5) == 0) ||
     (iVar4 = dev_write_reg(iVar4,local_2c,local_30,&local_8), iVar4 != 0)) {
    return local_4;
  }
LAB_0046cc45:
  cdb_c_error(s_unable_to_write_sp_004d40c0);
  return 0;
}


/* ==== cdb_caller_pc_56000 @ 0046cca0 ==== */

ulong __cdecl cdb_caller_pc_56000(ulong pc,ulong fp,ulong sp)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  int func_sym;
  int iVar7;
  long lVar8;
  uint uVar9;
  int local_18;
  uint local_10;
  ulong local_c [3];
  
  uVar6 = pc;
  bVar4 = false;
  local_18 = 0;
  iVar5 = cdb_func_of_pc_checked(pc);
  if (iVar5 == -1) {
    return 0;
  }
  uVar1 = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x34 + iVar5 * 0x20);
  iVar5 = *(int *)(cur_dev + 4);
  pc = cdb_default_space();
  if (pc == 3) {
    pc = 2;
  }
  switch(uVar1) {
  case 0:
  case 1:
  case 4:
  case 5:
  case 0xc:
  case 0xd:
  case 0x10:
  case 0x11:
  case 0x14:
  case 0x15:
  case 0x1c:
  case 0x1d:
    uVar6 = cdb_hwstack_pop();
    return uVar6;
  default:
    func_sym = cdb_func_of_pc(uVar6);
    if (func_sym == -1) {
      return 0;
    }
    iVar7 = cdb_func_bf_sym(func_sym);
    if (func_sym == -1) {
      return 0;
    }
    if (iVar7 == -1) {
      return 0;
    }
    uVar2 = *(uint *)(iVar7 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
    uVar3 = *(uint *)(func_sym * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
    while (uVar3 < uVar2) {
      uVar9 = uVar3 + 1;
      lVar8 = dev_mem_read(iVar5,0,uVar3,(long)&local_10);
      if (lVar8 == 0) {
        cdb_c_error(s_error_reading_from_program_memor_004d406c);
        return 0;
      }
      uVar3 = uVar9;
      if (bVar4) {
        if ((((local_10 & 0xc0ffff) == 0x405e00) || ((local_10 & 0xf4ffff) == 0x405e00)) ||
           (local_10 == 0x205e00)) {
          local_18 = local_18 + 1;
        }
      }
      else if ((local_10 & 0xffff3f) == 0x55e3c) {
        bVar4 = true;
      }
    }
    lVar8 = dev_mem_read(iVar5,pc,(sp - local_18) + -1,(long)local_c);
    if (lVar8 == 0) {
      cdb_c_error(s_error_reading_from_memory_004d4090);
      return 0;
    }
    break;
  case 0xffffffff:
  case 3:
  case 6:
  case 7:
  case 0xe:
  case 0xf:
  case 0x13:
  case 0x16:
  case 0x17:
  case 0x1e:
  case 0x1f:
    lVar8 = dev_mem_read(iVar5,pc,fp - 1,(long)local_c);
    if (lVar8 == 0) {
      cdb_c_error(s_error_reading_from_software_stac_004d4110);
      return 0;
    }
  }
  return local_c[0];
}


/* ==== cdb_caller_pc_96000 @ 0046cee0 ==== */

ulong __cdecl cdb_caller_pc_96000(ulong pc,ulong fp,ulong sp)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  ulong uVar6;
  int func_sym;
  int iVar7;
  long lVar8;
  uint uVar9;
  int local_18;
  uint local_10;
  ulong local_c [3];
  
  uVar6 = pc;
  bVar4 = false;
  local_18 = 0;
  iVar5 = cdb_func_of_pc_checked(pc);
  if (iVar5 == -1) {
    return 0;
  }
  uVar1 = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x34 + iVar5 * 0x20);
  iVar5 = *(int *)(cur_dev + 4);
  pc = cdb_default_space();
  if (pc == 3) {
    pc = 2;
  }
  switch(uVar1) {
  case 0:
  case 1:
  case 4:
  case 5:
  case 0xc:
  case 0xd:
  case 0x10:
  case 0x11:
  case 0x14:
  case 0x15:
  case 0x1c:
  case 0x1d:
    uVar6 = cdb_hwstack_pop();
    return uVar6;
  default:
    func_sym = cdb_func_of_pc(uVar6);
    if (func_sym == -1) {
      return 0;
    }
    iVar7 = cdb_func_bf_sym(func_sym);
    if (func_sym == -1) {
      return 0;
    }
    if (iVar7 == -1) {
      return 0;
    }
    uVar2 = *(uint *)(iVar7 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
    uVar3 = *(uint *)(func_sym * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
    while (uVar3 < uVar2) {
      uVar9 = uVar3 + 1;
      lVar8 = dev_mem_read(iVar5,0,uVar3,(long)&local_10);
      if (lVar8 == 0) {
        cdb_c_error(s_error_reading_from_program_memor_004d406c);
        return 0;
      }
      uVar3 = uVar9;
      if (bVar4) {
        if ((local_10 & 0xe00ffff8) == 0x2007a000) {
          local_18 = local_18 + 1;
        }
      }
      else if ((local_10 & 0xfffff6ff) == 0x137a07c) {
        bVar4 = true;
      }
    }
    lVar8 = dev_mem_read(iVar5,pc,(sp - local_18) + -1,(long)local_c);
    if (lVar8 == 0) {
      cdb_c_error(s_error_reading_from_memory_004d4090);
      return 0;
    }
    break;
  case 0xffffffff:
  case 3:
  case 6:
  case 7:
  case 0xe:
  case 0xf:
  case 0x13:
  case 0x16:
  case 0x17:
  case 0x1e:
  case 0x1f:
    lVar8 = dev_mem_read(iVar5,pc,fp - 1,(long)local_c);
    if (lVar8 == 0) {
      cdb_c_error(s_error_reading_from_software_stac_004d4110);
      return 0;
    }
  }
  return local_c[0];
}


/* ==== cdb_caller_fp @ 0046d100 ==== */

ulong __cdecl cdb_caller_fp(ulong pc,ulong fp,ulong sp,ulong cpc)

{
  code *pcVar1;
  ulong uVar2;
  
  if ((*(int *)(cur_itype + 0x1c) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_itype + 0x1c) + 0xc), pcVar1 != (code *)0x0)) {
    uVar2 = (*pcVar1)(pc,fp,sp,cpc);
    return uVar2;
  }
  if (cdb_arch == 0x2c7) {
    uVar2 = cdb_caller_fp_56100(pc,fp,sp,cpc);
    return uVar2;
  }
  if (cdb_arch == 0x2c5) {
    uVar2 = cdb_caller_fp_56000(pc,fp,sp,cpc);
    return uVar2;
  }
  if (cdb_arch == 0x2c6) {
    uVar2 = cdb_caller_fp_96000(pc,fp,sp,cpc);
    return uVar2;
  }
  return 0;
}


/* ==== cdb_caller_fp_56100 @ 0046d1b0 ==== */

ulong __cdecl cdb_caller_fp_56100(ulong pc,ulong fp,ulong sp,ulong cpc)

{
  ulong uVar1;
  
  uVar1 = cdb_caller_sp_56100(pc,sp,cpc);
  return uVar1;
}


/* ==== cdb_caller_fp_56000 @ 0046d1d0 ==== */

ulong __cdecl cdb_caller_fp_56000(ulong pc,ulong fp)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  long b;
  ulong local_c [3];
  
  iVar2 = cdb_func_of_pc_checked(pc);
  if (iVar2 == -1) {
    return 0;
  }
  uVar1 = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x34 + iVar2 * 0x20);
  iVar2 = *(int *)(cur_dev + 4);
  lVar3 = cdb_default_space();
  if (lVar3 == 3) {
    lVar3 = 2;
  }
  switch(uVar1) {
  case 0:
  case 2:
  case 0x10:
  case 0x12:
    return fp;
  case 4:
  case 0xc:
  case 0x14:
  case 0x1c:
    b = fp - 1;
    break;
  default:
    return 0;
  case 0xffffffff:
  case 1:
  case 3:
  case 5:
  case 6:
  case 7:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x11:
  case 0x13:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x1d:
  case 0x1e:
  case 0x1f:
    b = fp - 2;
  }
  lVar3 = dev_mem_read(iVar2,lVar3,b,(long)local_c);
  if (lVar3 != 0) {
    return local_c[0];
  }
  cdb_c_error(s_error_reading_from_software_stac_004d4110);
  return 0;
}


/* ==== cdb_caller_fp_96000 @ 0046d300 ==== */

ulong __cdecl cdb_caller_fp_96000(ulong pc,ulong fp)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  long b;
  ulong local_c [3];
  
  iVar2 = cdb_func_of_pc_checked(pc);
  if (iVar2 == -1) {
    return 0;
  }
  uVar1 = *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 0x34 + iVar2 * 0x20);
  iVar2 = *(int *)(cur_dev + 4);
  lVar3 = cdb_default_space();
  if (lVar3 == 3) {
    lVar3 = 2;
  }
  switch(uVar1) {
  case 0:
  case 2:
  case 0x10:
  case 0x12:
    return fp;
  case 4:
  case 0xc:
  case 0x14:
  case 0x1c:
    b = fp - 1;
    break;
  default:
    return 0;
  case 0xffffffff:
  case 1:
  case 3:
  case 5:
  case 6:
  case 7:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x11:
  case 0x13:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x1d:
  case 0x1e:
  case 0x1f:
    b = fp - 2;
  }
  lVar3 = dev_mem_read(iVar2,lVar3,b,(long)local_c);
  if (lVar3 != 0) {
    return local_c[0];
  }
  cdb_c_error(s_error_reading_from_software_stac_004d4110);
  return 0;
}


/* ==== cdb_caller_sp_56100 @ 0046d430 ==== */

ulong __cdecl cdb_caller_sp_56100(ulong pc,ulong sp,ulong cpc)

{
  int iVar1;
  long lVar2;
  
  iVar1 = cdb_func_of_pc(pc);
  if (iVar1 == -1) {
    return 0;
  }
  iVar1 = cdb_count_pushes_56100(*(ulong *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar1 * 0x20));
  lVar2 = cdb_frame_adjust_56100(cpc);
  return sp - (iVar1 - lVar2);
}


/* ==== cdb_count_pushes_56100 @ 0046d480 ==== */

int __cdecl cdb_count_pushes_56100(ulong pc)

{
  int dev;
  uint uVar1;
  uint b;
  int func_sym;
  int iVar2;
  long lVar3;
  ulong uVar4;
  int iVar5;
  ulong b_00;
  
  b_00 = pc;
  dev = *(int *)(cur_dev + 4);
  iVar5 = 0;
  func_sym = cdb_func_of_pc(pc);
  iVar2 = cdb_func_bf_sym(func_sym);
  if ((func_sym == -1) || (iVar2 == -1)) {
    return 0;
  }
  uVar1 = *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20);
joined_r0x0046d4d2:
  b = b_00;
  if (uVar1 <= b) {
    return iVar5;
  }
  b_00 = b + 1;
  lVar3 = dev_mem_read(dev,0,b,(long)&pc);
  if (lVar3 != 0) {
    if (pc != 0x3fdc) {
      if (((pc & 0xfc1f) == 0x3806) || (pc == 0x1e6)) {
        iVar5 = iVar5 + 1;
      }
      goto joined_r0x0046d4d2;
    }
    lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
    if (lVar3 == 0) goto LAB_0046d59d;
    uVar4 = pc;
    if ((pc & 0x8000) != 0) {
      uVar4 = pc | 0xffff0000;
    }
    lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
    if (lVar3 != 0) {
      b_00 = b + 3;
      if (pc != 0) goto joined_r0x0046d4d2;
      lVar3 = dev_mem_read(dev,0,b + 3,(long)&pc);
      if (lVar3 != 0) {
        b_00 = b + 4;
        if (pc == 0x3611) {
          iVar5 = iVar5 + uVar4;
        }
        goto joined_r0x0046d4d2;
      }
    }
  }
LAB_0046d59d:
  cdb_c_error(s_error_reading_from_program_memor_004d406c);
  return 0;
}


/* ==== cdb_frame_adjust_56100 @ 0046d5c0 ==== */

long __cdecl cdb_frame_adjust_56100(ulong pc)

{
  int dev;
  uint uVar1;
  ulong b;
  int iVar2;
  long lVar3;
  ulong uVar4;
  uint uVar5;
  uint b_00;
  
  b = pc;
  dev = *(int *)(cur_dev + 4);
  uVar5 = 0;
  iVar2 = cdb_func_of_pc(pc);
  iVar2 = cdb_func_ef_sym(iVar2);
  if (iVar2 == -1) {
    return 0;
  }
  uVar1 = *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20);
  if (b < uVar1) {
    b_00 = b + 1;
    lVar3 = dev_mem_read(dev,0,b,(long)&pc);
    if (lVar3 == 0) {
      cdb_c_error(s_error_reading_from_program_memor_004d406c);
      return 0;
    }
    if (pc == 0x3211) {
      uVar5 = 0xffffffff;
      if (b_00 < uVar1) {
        lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
        if (lVar3 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        if ((pc == 0x3211) && (uVar5 = 0xfffffffe, b + 2 < uVar1)) {
          lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
          if (lVar3 == 0) {
            cdb_c_error(s_error_reading_from_program_memor_004d406c);
            return 0;
          }
          if (pc == 0x3211) {
            return -3;
          }
        }
      }
    }
    else if (pc == 0x3fdc) {
      lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
      if (lVar3 == 0) {
        cdb_c_error(s_error_reading_from_program_memor_004d406c);
        return 0;
      }
      uVar4 = pc;
      if ((pc & 0x8000) != 0) {
        uVar4 = pc | 0xffff0000;
      }
      lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
      if (lVar3 == 0) {
        cdb_c_error(s_error_reading_from_program_memor_004d406c);
        return 0;
      }
      if (pc == 0) {
        lVar3 = dev_mem_read(dev,0,b + 3,(long)&pc);
        if (lVar3 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        if (pc == 0x3611) {
          uVar5 = uVar4;
        }
      }
    }
  }
  return uVar5;
}


/* ==== cdb_frame_adjust @ 0046d7a0 ==== */

long __cdecl cdb_frame_adjust(ulong pc)

{
  long lVar1;
  
  if (cdb_arch == 0x2c7) {
    lVar1 = cdb_frame_adjust_56100(pc);
    return lVar1;
  }
  if (cdb_arch == 0x2c5) {
    lVar1 = cdb_frame_adjust_56000(pc);
    return lVar1;
  }
  lVar1 = cdb_frame_adjust_96000(pc);
  return lVar1;
}


/* ==== cdb_frame_adjust_56000 @ 0046d7e0 ==== */

long __cdecl cdb_frame_adjust_56000(ulong pc)

{
  int dev;
  uint uVar1;
  ulong b;
  int iVar2;
  long lVar3;
  int iVar4;
  uint b_00;
  
  b = pc;
  dev = *(int *)(cur_dev + 4);
  iVar4 = 0;
  iVar2 = cdb_func_of_pc(pc);
  iVar2 = cdb_func_ef_sym(iVar2);
  if (iVar2 == -1) {
    return 0;
  }
  uVar1 = *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20);
  if (b < uVar1) {
    b_00 = b + 1;
    lVar3 = dev_mem_read(dev,0,b,(long)&pc);
    if (lVar3 == 0) {
      cdb_c_error(s_error_reading_from_program_memor_004d406c);
      return 0;
    }
    if (pc == 0x205600) {
      iVar4 = -1;
      if (b_00 < uVar1) {
        lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
        if (lVar3 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        if ((pc == 0x205600) && (iVar4 = -2, b + 2 < uVar1)) {
          lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
          if (lVar3 == 0) {
            cdb_c_error(s_error_reading_from_program_memor_004d406c);
            return 0;
          }
          if (pc == 0x205600) {
            return -3;
          }
        }
      }
    }
    else if ((pc & 0xff00ff) == 0x3e0000) {
      uVar1 = pc >> 8;
      lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
      if (lVar3 == 0) {
        cdb_c_error(s_error_reading_from_program_memor_004d406c);
        return 0;
      }
      if (pc == 0) {
        lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
        if (lVar3 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        if (pc == 0x204600) {
          iVar4 = -(uVar1 & 0xff);
        }
      }
    }
  }
  return iVar4;
}


/* ==== cdb_frame_adjust_96000 @ 0046d990 ==== */

long __cdecl cdb_frame_adjust_96000(ulong pc)

{
  int dev;
  uint uVar1;
  ulong b;
  int iVar2;
  long lVar3;
  int iVar4;
  uint b_00;
  
  b = pc;
  dev = *(int *)(cur_dev + 4);
  iVar4 = 0;
  iVar2 = cdb_func_of_pc(pc);
  iVar2 = cdb_func_ef_sym(iVar2);
  if (iVar2 == -1) {
    return 0;
  }
  uVar1 = *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20);
  if (b < uVar1) {
    b_00 = b + 1;
    lVar3 = dev_mem_read(dev,0,b,(long)&pc);
    if (lVar3 == 0) {
      cdb_c_error(s_error_reading_from_program_memor_004d406c);
      return 0;
    }
    if (pc == 0x15b5a000) {
      iVar4 = -1;
      if (b_00 < uVar1) {
        lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
        if (lVar3 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        if ((pc == 0x15b5a000) && (iVar4 = -2, b + 2 < uVar1)) {
          lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
          if (lVar3 == 0) {
            cdb_c_error(s_error_reading_from_program_memor_004d406c);
            return 0;
          }
          if (pc == 0x15b5a000) {
            return -3;
          }
        }
      }
    }
    else if ((pc & 0xff80007f) == 0x800036) {
      uVar1 = pc >> 8;
      lVar3 = dev_mem_read(dev,0,b_00,(long)&pc);
      if (lVar3 == 0) {
        cdb_c_error(s_error_reading_from_program_memor_004d406c);
        return 0;
      }
      if (pc == 0) {
        lVar3 = dev_mem_read(dev,0,b + 2,(long)&pc);
        if (lVar3 == 0) {
          cdb_c_error(s_error_reading_from_program_memor_004d406c);
          return 0;
        }
        if (pc == 0x15b1a000) {
          iVar4 = -(uVar1 & 0xff);
        }
      }
    }
  }
  return iVar4;
}


/* ==== cdb_caller_sp @ 0046db40 ==== */

ulong __cdecl cdb_caller_sp(ulong pc,ulong sp,ulong cpc)

{
  code *pcVar1;
  ulong uVar2;
  
  if ((*(int *)(cur_itype + 0x1c) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_itype + 0x1c) + 8), pcVar1 != (code *)0x0)) {
    uVar2 = (*pcVar1)(pc,sp,cpc);
    return uVar2;
  }
  if (cdb_arch == 0x2c7) {
    uVar2 = cdb_caller_sp_56100(pc,sp,cpc);
    return uVar2;
  }
  if (cdb_arch == 0x2c5) {
    uVar2 = cdb_caller_sp_56000(pc,sp,cpc);
    return uVar2;
  }
  if (cdb_arch == 0x2c6) {
    uVar2 = cdb_caller_sp_96000(pc,sp,cpc);
    return uVar2;
  }
  return 0;
}


/* ==== cdb_caller_sp_56000 @ 0046dbd0 ==== */

ulong __cdecl cdb_caller_sp_56000(ulong pc,ulong sp,ulong cpc)

{
  int iVar1;
  long lVar2;
  
  iVar1 = cdb_func_of_pc(pc);
  if (iVar1 == -1) {
    return 0;
  }
  iVar1 = cdb_count_pushes_56000(*(ulong *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar1 * 0x20));
  lVar2 = cdb_frame_adjust_56000(cpc);
  return sp - (iVar1 - lVar2);
}


/* ==== cdb_count_pushes_56000 @ 0046dc20 ==== */

int __cdecl cdb_count_pushes_56000(ulong pc)

{
  int dev;
  uint uVar1;
  int func_sym;
  int iVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  uint b;
  uint uVar6;
  
  uVar6 = pc;
  dev = *(int *)(cur_dev + 4);
  iVar4 = 0;
  func_sym = cdb_func_of_pc(pc);
  iVar2 = cdb_func_bf_sym(func_sym);
  if ((func_sym == -1) || (iVar2 == -1)) {
    return 0;
  }
  uVar1 = *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20);
joined_r0x0046dc72:
  while( true ) {
    if (uVar1 <= uVar6) {
      return iVar4;
    }
    uVar5 = uVar6 + 1;
    lVar3 = dev_mem_read(dev,0,uVar6,(long)&pc);
    if (lVar3 == 0) goto LAB_0046dd71;
    if ((pc & 0xff00ff) == 0x3e0000) break;
    if (pc == 0x76f400) goto LAB_0046dcf0;
    uVar6 = uVar5;
    if (((((pc & 0xc0ffff) == 0x405e00) || ((pc & 0xf4ffff) == 0x405e00)) ||
        ((pc & 0xffff3f) == 0x55e3c)) || (pc == 0x205e00)) {
      iVar4 = iVar4 + 1;
    }
  }
  if (pc == 0x76f400) {
LAB_0046dcf0:
    b = uVar6 + 2;
    lVar3 = dev_mem_read(dev,0,uVar5,(long)&pc);
    uVar5 = pc;
    if (lVar3 == 0) goto LAB_0046dd71;
  }
  else {
    b = uVar5;
    uVar5 = pc >> 8 & 0xff;
  }
  lVar3 = dev_mem_read(dev,0,b,(long)&pc);
  if (lVar3 != 0) {
    if ((pc != 0x22d000) && (pc != 0)) {
      return iVar4;
    }
    uVar6 = b + 2;
    lVar3 = dev_mem_read(dev,0,b + 1,(long)&pc);
    if (lVar3 != 0) {
      if (pc == 0x204e00) {
        iVar4 = iVar4 + uVar5;
      }
      goto joined_r0x0046dc72;
    }
  }
LAB_0046dd71:
  cdb_c_error(s_error_reading_from_program_memor_004d406c);
  return 0;
}


/* ==== cdb_caller_sp_96000 @ 0046dd90 ==== */

ulong __cdecl cdb_caller_sp_96000(ulong pc,ulong sp,ulong cpc)

{
  int iVar1;
  long lVar2;
  
  iVar1 = cdb_func_of_pc(pc);
  if (iVar1 == -1) {
    return 0;
  }
  iVar1 = cdb_count_pushes_96000(*(ulong *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar1 * 0x20));
  lVar2 = cdb_frame_adjust_96000(cpc);
  return sp - (iVar1 - lVar2);
}


/* ==== cdb_count_pushes_96000 @ 0046dde0 ==== */

int __cdecl cdb_count_pushes_96000(ulong pc)

{
  int dev;
  uint uVar1;
  uint uVar2;
  int func_sym;
  int iVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  uVar2 = pc;
  dev = *(int *)(cur_dev + 4);
  iVar6 = 0;
  func_sym = cdb_func_of_pc(pc);
  iVar3 = cdb_func_bf_sym(func_sym);
  if ((func_sym == -1) || (iVar3 == -1)) {
    return 0;
  }
  uVar1 = *(uint *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar3 * 0x20);
joined_r0x0046de32:
  if (uVar1 <= uVar2) {
    return iVar6;
  }
  uVar7 = uVar2 + 1;
  lVar4 = dev_mem_read(dev,0,uVar2,(long)&pc);
  if (lVar4 != 0) {
    if ((pc & 0xff80007f) != 0x800036) {
      uVar2 = uVar7;
      if ((((pc & 0xe00ffff8) == 0x2007a000) || ((pc & 0xfffff6ff) == 0x137a07c)) ||
         (pc == 0x15b7a000)) {
        iVar6 = iVar6 + 1;
      }
      goto joined_r0x0046de32;
    }
    uVar5 = pc >> 7;
    lVar4 = dev_mem_read(dev,0,uVar7,(long)&pc);
    if (lVar4 == 0) goto LAB_0046def1;
    if (pc != 0xaea2000) {
      return iVar6;
    }
    uVar7 = uVar2 + 3;
    lVar4 = dev_mem_read(dev,0,uVar2 + 2,(long)&pc);
    if (lVar4 != 0) {
      uVar2 = uVar7;
      if (pc == 0x15b3a000) {
        iVar6 = iVar6 + (uVar5 & 0xffff);
      }
      goto joined_r0x0046de32;
    }
  }
LAB_0046def1:
  cdb_c_error(s_error_reading_from_program_memor_004d406c);
  return 0;
}


/* ==== cdb_scan_prologue @ 0046df10 ==== */

char __cdecl cdb_scan_prologue(ulong pc,int fp)

{
  char cVar1;
  
  if (cdb_arch == 0x2c7) {
    cVar1 = cdb_scan_prologue_56100(pc,fp);
    return cVar1;
  }
  if (cdb_arch == 0x2c9) {
    cVar1 = scan_saved_regs_56800(pc,fp);
    return cVar1;
  }
  if ((((cdb_arch != 0x2c5) && (cdb_arch != 0x2c8)) && (cdb_arch != 0x2cb)) && (cdb_arch != 0x2ca))
  {
    if (cdb_arch != 0x2c6) {
      return '\0';
    }
    cVar1 = scan_saved_regs_96000(pc,fp);
    return cVar1;
  }
  cVar1 = scan_saved_regs_56000(pc,fp);
  return cVar1;
}


/* ==== cdb_scan_prologue_56100 @ 0046dfa0 ==== */

char __cdecl cdb_scan_prologue_56100(ulong pc,int fp)

{
  char cVar1;
  int dev;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  char *extraout_EAX;
  ulong uVar6;
  uint uVar7;
  uint uVar8;
  uint b;
  char *pcVar9;
  int iVar10;
  char *pcVar11;
  int local_c;
  char *local_8;
  
  dev = *(int *)(cur_dev + 4);
  iVar10 = 0;
  local_c = 0;
  local_8 = (char *)0x0;
  iVar3 = cdb_func_of_pc(pc);
  iVar4 = cdb_func_bf_sym(iVar3);
  if ((iVar3 == -1) || (iVar4 == -1)) {
    return '\0';
  }
  uVar2 = *(uint *)(iVar4 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
  b = *(uint *)(iVar3 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
joined_r0x0046e003:
  uVar7 = b;
  pcVar9 = local_8;
  if (uVar2 <= uVar7) {
    for (; pcVar9 != (char *)0x0; pcVar9 = *(char **)(pcVar9 + 0x10)) {
      *(int *)(pcVar9 + 8) = *(int *)(pcVar9 + 8) + (fp - iVar10);
    }
    return (char)local_8;
  }
  b = uVar7 + 1;
  lVar5 = dev_mem_read(dev,0,uVar7,(long)&pc);
  if (lVar5 != 0) {
    iVar3 = opcode_tab_search(&DAT_00492888,0xd,pc);
    if (iVar3 != -1) {
      cdb_malloc(0x14);
      *(int *)(extraout_EAX + 8) = iVar10;
      *(undefined4 *)(extraout_EAX + 0xc) = *(undefined4 *)(&DAT_0049288c + iVar3 * 0xc);
      uVar7 = 0xffffffff;
      pcVar9 = (&PTR_DAT_00492890)[iVar3 * 3];
      do {
        pcVar11 = pcVar9;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar9 = pcVar11 + -uVar7;
      pcVar11 = extraout_EAX;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar11 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar11 = pcVar11 + 1;
      }
      extraout_EAX[0x10] = '\0';
      extraout_EAX[0x11] = '\0';
      extraout_EAX[0x12] = '\0';
      extraout_EAX[0x13] = '\0';
      if (local_8 != (char *)0x0) {
        *(char **)(extraout_EAX + 0x10) = local_8;
      }
      iVar10 = local_c + 1;
      local_c = iVar10;
      local_8 = extraout_EAX;
      goto joined_r0x0046e003;
    }
    if (pc != 0x3fdc) {
      if (((pc & 0xfc1f) == 0x3806) || (pc == 0x1e6)) {
        iVar10 = iVar10 + 1;
        local_c = iVar10;
      }
      goto joined_r0x0046e003;
    }
    lVar5 = dev_mem_read(dev,0,b,(long)&pc);
    if (lVar5 != 0) {
      uVar6 = pc;
      if ((pc & 0x8000) != 0) {
        uVar6 = pc | 0xffff0000;
      }
      lVar5 = dev_mem_read(dev,0,uVar7 + 2,(long)&pc);
      if (lVar5 == 0) goto LAB_0046e185;
      b = uVar7 + 3;
      if (pc != 0) goto joined_r0x0046e003;
      lVar5 = dev_mem_read(dev,0,uVar7 + 3,(long)&pc);
      if (lVar5 != 0) {
        b = uVar7 + 4;
        if (pc == 0x3611) {
          iVar10 = iVar10 + uVar6;
          local_c = iVar10;
        }
        goto joined_r0x0046e003;
      }
    }
  }
LAB_0046e185:
  cdb_c_error(s_error_reading_from_program_memor_004d406c);
  return '\0';
}


