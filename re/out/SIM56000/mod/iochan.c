/* ==== io_emit @ 00448740 ==== */

void __cdecl io_emit(void *io,char *text)

{
  char *pcVar1;
  char *pcVar2;
  char local_100 [256];
  
  if (*(void **)((int)io + 0x150) == (void *)0x0) {
    if (*text != '#') {
      sprintf(local_100,s__s_cyc__lu__s_004cb140,(int)io + 0x100,*(undefined4 *)(cur_dev + 0x20),
              text);
      pcVar2 = local_100;
      while (local_100[0] != '\0') {
        if (local_100[0] == '\n') {
          *pcVar2 = ' ';
        }
        pcVar1 = pcVar2 + 1;
        pcVar2 = pcVar2 + 1;
        local_100[0] = *pcVar1;
      }
      out_text(local_100,1);
    }
    return;
  }
  fprintf(*(void **)((int)io + 0x150),text);
  fflush(*(void **)((int)io + 0x150));
  return;
}


/* ==== io_out_poll @ 004487f0 ==== */

void io_out_poll(void)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  char local_200 [256];
  char local_100 [256];
  
  for (pvVar1 = *(void **)(cur_sim + 0x158); pvVar1 != (void *)0x0;
      pvVar1 = *(void **)((int)pvVar1 + 0x1e0)) {
    iVar3 = *(int *)((int)pvVar1 + 0x154);
    if ((((iVar3 == 4) || (iVar3 == 3)) || (iVar3 == 8)) &&
       (iVar3 = io_pin_state_str(pvVar1,local_100), iVar3 != 0)) {
      if (*(int *)((int)pvVar1 + 0x150) == 0) {
        sprintf(local_200,&DAT_004cb15c,local_100);
      }
      else {
        sprintf(local_200,s__01lu__s_004cb160,*(undefined4 *)(cur_dev + 0x20),local_100);
      }
      io_emit(pvVar1,local_200);
    }
  }
  for (pvVar1 = *(void **)(cur_sim + 0x154); pvVar1 != (void *)0x0;
      pvVar1 = *(void **)((int)pvVar1 + 0x1e0)) {
    iVar3 = *(int *)((int)pvVar1 + 0x154);
    if ((((iVar3 == 4) || (iVar3 == 3)) || (iVar3 == 8)) &&
       ((iVar3 = io_pin_state_str(pvVar1,local_100), iVar3 != 0 ||
        (*(int *)((int)pvVar1 + 0x1d0) != 0)))) {
      iVar3 = *(int *)(cur_dev + 0x20);
      iVar2 = *(int *)((int)pvVar1 + 0x1d8);
      *(int *)((int)pvVar1 + 0x1d8) = iVar3;
      iVar3 = iVar3 - iVar2;
      if ((*(int *)((int)pvVar1 + 0x150) != 0) &&
         ((*(int *)((int)pvVar1 + 0x1d0) == 0 && (1 < iVar3)))) {
        sprintf(local_200,s___01ld_004cb154,iVar3);
        io_emit(pvVar1,local_200);
      }
      sprintf(local_200,&DAT_004cb150,local_100);
      io_emit(pvVar1,local_200);
      *(undefined4 *)((int)pvVar1 + 0x1d0) = 0;
    }
  }
  return;
}


/* ==== io_pin_state_str @ 00448980 ==== */

int __cdecl io_pin_state_str(void *io,char *buf)

{
  uint *puVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  char cVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  bool bVar19;
  int local_30;
  undefined4 local_18;
  undefined4 uStack_14;
  
  iVar4 = *(int *)(cur_dtype + 0x3c);
  iVar5 = *(int *)(cur_dev + 0x18);
  uVar6 = *(uint *)(cur_dtype + 8);
  iVar12 = *(int *)((int)io + 0x15c);
  iVar7 = *(int *)((int)io + 0x160);
  iVar14 = ((iVar12 <= iVar7) - 1 & 0xfffffffe) + 1;
  local_30 = 0;
  bVar19 = *(int *)((int)io + 0x154) != 8;
  while( true ) {
    iVar13 = iVar4 + iVar12 * 0x18;
    uVar8 = *(uint *)(iVar13 + 0x10);
    iVar17 = iVar5 + *(int *)(iVar13 + 0xc) * 0x128;
    uVar18 = (uint)((*(uint *)(iVar5 + *(int *)(iVar13 + 0xc) * 0x128) & uVar8) != 0);
    uVar15 = (uint)((*(uint *)(iVar17 + 0x94) & uVar8) != 0);
    if ((uVar8 & *(uint *)(iVar17 + 4)) == 0) {
      uVar18 = 2;
    }
    if ((*(uint *)(iVar17 + 0x98) & uVar8) == 0) {
      uVar15 = 2;
    }
    uVar9 = (uint)((*(uint *)(iVar17 + 8) & uVar8) != 0);
    uVar10 = (uint)((*(uint *)(iVar17 + 0xc) & uVar8) != 0);
    if (bVar19) {
      if (((uVar9 != ((*(uint *)(iVar17 + 0x9c) & uVar8) != 0)) ||
          (-(uint)((*(uint *)(iVar17 + 0xa0) & uVar8) != 0) != -uVar10)) || (uVar18 != uVar15)) {
        local_30 = 1;
      }
      if (uVar10 == 0) {
        cVar11 = *(char *)(uVar18 + 0x4caa78);
      }
      else {
        cVar11 = (&DAT_004caa7c)[uVar9];
      }
      *buf = cVar11;
      buf = buf + 1;
    }
    else {
      iVar16 = 0;
      while (uVar8 = uVar8 >> 1, uVar8 != 0) {
        iVar16 = iVar16 + 1;
      }
      fVar2 = *(float *)(iVar17 + 0x14 + iVar16 * 4);
      dVar3 = (double)fVar2;
      if ((fVar2 != *(float *)(iVar17 + 0xa8 + iVar16 * 4)) || (*(int *)((int)io + 0x1d0) != 0)) {
        uStack_14 = (undefined4)((ulonglong)dVar3 >> 0x20);
        local_18 = SUB84(dVar3,0);
        local_30 = 1;
        sprintf(buf,&DAT_004cb16c,local_18,uStack_14);
      }
    }
    if (iVar12 == iVar7) break;
    iVar17 = iVar14 * 0x18;
    iVar13 = iVar13 + 0x14;
    do {
      puVar1 = (uint *)(iVar13 + iVar17);
      iVar13 = iVar13 + iVar17;
      iVar12 = iVar12 + iVar14;
    } while ((*puVar1 & uVar6) == 0);
  }
  if (bVar19) {
    *buf = '\0';
  }
  return local_30;
}


/* ==== io_out_mem_write @ 00448b60 ==== */

void __cdecl io_out_mem_write(int space,ulong addr,ulong value)

{
  int id;
  void *io;
  void *io_00;
  char *text;
  char local_164 [100];
  char local_100 [256];
  
  id = rangemap_get((void *)(*(int *)(cur_sim + 4) + 0xc + space * 300),addr);
  if (id != 0) {
    iolist_find_id(*(void **)(cur_sim + 0x154),id);
    if (io != (void *)0x0) {
      if (*(int *)((int)io + 0x1d4) == 5) {
        io_read_string(space,value,local_164);
      }
      else {
        fmt_word(space,addr,*(int *)((int)io + 0x1d4),local_164,value);
      }
      if (*(int *)((int)io + 0x15c) == *(int *)((int)io + 0x160)) {
        sprintf(local_100,&DAT_004c5990,local_164);
      }
      else {
        sprintf(local_100,s__lx__s_004cb180,addr,local_164);
      }
      io_emit(io,local_100);
    }
    iolist_find_id(*(void **)(cur_sim + 0x158),id);
    if (io_00 != (void *)0x0) {
      if (*(int *)((int)io_00 + 0x1d4) == 5) {
        io_read_string(space,value,local_164);
      }
      else {
        fmt_word(space,addr,*(int *)((int)io_00 + 0x1d4),local_164,value);
      }
      if (*(int *)((int)io_00 + 0x150) != 0) {
        if (*(int *)((int)io_00 + 0x15c) == *(int *)((int)io_00 + 0x160)) {
          sprintf(local_100,s__01lu__s_004cb160,*(undefined4 *)(cur_dev + 0x20),local_164);
          io_emit(io_00,local_100);
          return;
        }
        sprintf(local_100,s__01lu__lx__s_004cb170,*(undefined4 *)(cur_dev + 0x20),addr,local_164);
        io_emit(io_00,local_100);
        return;
      }
      if (*(int *)((int)io_00 + 0x15c) == *(int *)((int)io_00 + 0x160)) {
        text = local_164;
      }
      else {
        sprintf(local_100,s__lx__s_004cb180,addr,local_164);
        text = local_100;
      }
      io_emit(io_00,text);
    }
  }
  return;
}


/* ==== io_read_string @ 00448d80 ==== */

void __cdecl io_read_string(int space,int addr,char *buf)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  
  iVar1 = 0;
  iVar4 = space * 0x2c;
  iVar2 = addr - (int)buf;
  pcVar3 = buf;
  do {
    (*(code *)**(undefined4 **)(cur_dtype + 0x28))
              (*(undefined4 *)(*(int *)(cur_dtype + 0x20) + 4 + iVar4),pcVar3 + iVar2,&space);
    if (space == 0) break;
    *pcVar3 = (char)space;
    iVar1 = iVar1 + 1;
    pcVar3 = pcVar3 + 1;
  } while (iVar1 < 99);
  buf[iVar1] = '\0';
  return;
}


/* ==== io_out_reg_write @ 00448de0 ==== */

void __cdecl io_out_reg_write(int reg,ulong *value,int delta)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  void *io;
  int iVar5;
  undefined3 extraout_var;
  void *io_00;
  undefined3 extraout_var_00;
  int iVar6;
  uint *puVar7;
  int iVar8;
  char *fmt;
  char *va1;
  char acStack_1c0 [20];
  int iStack_1ac;
  undefined4 uStack_1a8;
  ulong uStack_1a4;
  char acStack_184 [256];
  char acStack_84 [132];
  
  iVar8 = *(int *)(cur_dev + 0x20);
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar4 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar4 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iolist_find(*(void **)(cur_sim + 0x154),2,reg,0);
  if (io != (void *)0x0) {
    if (delta < 0) {
      iVar5 = *(int *)((int)io + 0x1d8);
      *(int *)((int)io + 0x1d8) = iVar8;
      delta = iVar8 - iVar5;
      if (*(int *)((int)io + 0x1d0) != 0) {
        *(undefined4 *)((int)io + 0x1d0) = 0;
        delta = 0;
      }
    }
    if ((*(int *)((int)io + 0x150) != 0) && (0 < delta)) {
      sprintf(acStack_184,s___01ld_004cb154,delta);
      io_emit(io,acStack_184);
    }
    switch(*(undefined4 *)((int)io + 0x1d4)) {
    case 0:
      if ((uVar4 & 0x10000000) == 0) {
        iVar5 = (-(uint)((uVar4 & 0x2000000) != 0) & 8) + 0x18;
      }
      else {
        iVar5 = 0x10;
      }
      iVar6 = 0;
      if (iVar5 != 0) {
        puVar7 = &abort_flag + iVar5;
        uVar1 = *value;
        do {
          uVar2 = *puVar7;
          puVar7 = puVar7 + -1;
          acStack_84[iVar6] = ((uVar1 & uVar2) != 0) + '0';
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar5);
      }
      acStack_84[iVar5] = '\0';
      sprintf(acStack_184,&DAT_004cb150,acStack_84);
      break;
    case 1:
      sprintf(acStack_184,s__01ld_004cb1d4,*value);
      break;
    case 2:
      uStack_1a4 = *value;
      word_to_frac(uVar4,&iStack_1ac);
      if ((uVar4 & 0x80) == 0) {
        sprintf(acStack_184,s__1_7f_004cb1c4,iStack_1ac,uStack_1a8);
      }
      else {
        cVar3 = fmt_float_exp(s__15_15s_004cb1cc,&iStack_1ac);
        sprintf(acStack_184,&DAT_004cb150,CONCAT31(extraout_var,cVar3));
      }
      break;
    case 3:
    case 4:
      sprintf(acStack_184,s__01lx_004cb1bc,*value);
      break;
    default:
      goto switchD_00448ea9_default;
    }
    io_emit(io,acStack_184);
  }
switchD_00448ea9_default:
  iolist_find(*(void **)(cur_sim + 0x158),1,reg,0);
  if (io_00 != (void *)0x0) {
    if (*(int *)((int)io_00 + 0x150) == 0) {
      acStack_1c0[0] = '\0';
    }
    else {
      sprintf(acStack_1c0,s__01lu_004cb1b4,iVar8);
    }
    switch(*(undefined4 *)((int)io_00 + 0x1d4)) {
    case 0:
      if ((uVar4 & 0x10000000) == 0) {
        iVar8 = (-(uint)((uVar4 & 0x2000000) != 0) & 8) + 0x18;
      }
      else {
        iVar8 = 0x10;
      }
      iVar5 = 0;
      if (iVar8 != 0) {
        uVar4 = *value;
        puVar7 = &abort_flag + iVar8;
        do {
          uVar1 = *puVar7;
          puVar7 = puVar7 + -1;
          acStack_84[iVar5] = ((uVar1 & uVar4) != 0) + '0';
          iVar5 = iVar5 + 1;
        } while (iVar5 < iVar8);
      }
      va1 = acStack_84;
      acStack_84[iVar8] = '\0';
      fmt = s__s_s_004cb1ac;
      break;
    case 1:
      sprintf(acStack_184,s__s_01ld_004cb1a0,acStack_1c0,*value);
      io_emit(io_00,acStack_184);
      return;
    case 2:
      uStack_1a4 = *value;
      word_to_frac(uVar4,&iStack_1ac);
      if ((uVar4 & 0x80) == 0) {
        sprintf(acStack_184,s__s_1_7f_004cb194,acStack_1c0,iStack_1ac,uStack_1a8);
        io_emit(io_00,acStack_184);
        return;
      }
      cVar3 = fmt_float_exp(s__15_15s_004cb1cc,&iStack_1ac);
      sprintf(acStack_184,s__s_s_004cb1ac,acStack_1c0,CONCAT31(extraout_var_00,cVar3));
      io_emit(io_00,acStack_184);
      return;
    case 3:
    case 4:
      va1 = (char *)*value;
      fmt = s__s_01lx_004cb188;
      break;
    default:
      goto switchD_0044904e_default;
    }
    sprintf(acStack_184,fmt,acStack_1c0,va1);
    io_emit(io_00,acStack_184);
  }
switchD_0044904e_default:
  return;
}


/* ==== io_out_note @ 00449200 ==== */

int __cdecl io_out_note(char *text)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  void *io;
  void *io_00;
  char *pcVar4;
  byte *pbVar5;
  bool bVar6;
  char local_100 [256];
  
  if (profiler_hook != (undefined *)0x0) {
    pcVar4 = s_stall_004cb204;
    pbVar2 = (byte *)text;
    do {
      bVar1 = *pbVar2;
      bVar6 = bVar1 < (byte)*pcVar4;
      if (bVar1 != *pcVar4) {
LAB_00449253:
        iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_00449258;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar6 = bVar1 < (byte)pcVar4[1];
      if (bVar1 != pcVar4[1]) goto LAB_00449253;
      pbVar2 = pbVar2 + 2;
      pcVar4 = pcVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00449258:
    if (iVar3 != 0) {
      pbVar5 = &DAT_004cb1fc;
      pbVar2 = (byte *)text;
      do {
        bVar1 = *pbVar2;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_0044928b:
          iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_00449290;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_0044928b;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00449290:
      if (iVar3 != 0) {
        pbVar5 = &DAT_004b3428;
        pbVar2 = (byte *)text;
        do {
          bVar1 = *pbVar2;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_004492c3:
            iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_004492c8;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_004492c3;
          pbVar2 = pbVar2 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_004492c8:
        if (iVar3 != 0) goto LAB_004492d2;
      }
    }
    *(int *)(cur_sim + 0x47c) = *(int *)(cur_sim + 0x47c) + 1;
  }
LAB_004492d2:
  iVar3 = 0;
  iolist_find(*(void **)(cur_sim + 0x154),6,0,0);
  iolist_find(*(void **)(cur_sim + 0x158),6,0,0);
  if ((io == (void *)0x0) && (io_00 == (void *)0x0)) {
    return 0;
  }
  if ((io != (void *)0x0) && (*(int *)((int)io + 0x160) == 1)) {
    if (text != (char *)0x0) {
      sprintf(local_100,s______s_004cb1f4,text);
      io_emit(io,local_100);
    }
    iVar3 = 1;
  }
  if ((io_00 != (void *)0x0) && (*(int *)((int)io_00 + 0x160) == 1)) {
    if (text != (char *)0x0) {
      if (*(int *)((int)io_00 + 0x150) == 0) {
        sprintf(local_100,s______s_004cb1dc,text);
      }
      else {
        sprintf(local_100,s__01lu______s_004cb1e4,*(undefined4 *)(cur_dev + 0x20),text);
      }
      io_emit(io_00,local_100);
    }
    iVar3 = 1;
  }
  return iVar3;
}


/* ==== io_out_insn_trace @ 004493d0 ==== */

void __cdecl io_out_insn_trace(int idx)

{
  char cVar1;
  uint uVar2;
  void *extraout_EAX;
  void *extraout_EAX_00;
  long lVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  void *io;
  int iStack_31c;
  long lStack_318;
  undefined4 local_314;
  uint uStack_310;
  void *pvStack_30c;
  void *pvStack_308;
  undefined4 uStack_304;
  char acStack_300 [256];
  char acStack_200 [256];
  undefined1 auStack_100 [256];
  
  local_314 = 0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar2 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar2 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iolist_find(*(void **)(cur_sim + 0x154),6,0,0);
  pvStack_308 = extraout_EAX;
  iolist_find(*(void **)(cur_sim + 0x158),6,0,0);
  iVar5 = cur_sim;
  pvStack_30c = extraout_EAX_00;
  if ((extraout_EAX == (void *)0x0) && (io = extraout_EAX, extraout_EAX_00 == (void *)0x0))
  goto LAB_004495ff;
  periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2924,&iStack_31c,&lStack_318);
  periph_call(*(int *)(cur_dev + 4),iStack_31c,lStack_318,(long)&uStack_304);
  lVar3 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2950,&iStack_31c,&lStack_318);
  if (lVar3 != 0) {
    periph_call(*(int *)(cur_dev + 4),iStack_31c,lStack_318,(long)&local_314);
  }
  puVar8 = (undefined4 *)(*(int *)(iVar5 + 0x3fc8) + idx * 0x2c);
  uStack_310 = uVar2 & 0x10000000;
  if ((uStack_310 == 0) || ((uVar2 & 0x4000000) == 0)) {
    if (uStack_310 == 0) {
      if ((uVar2 & 0x200) == 0) {
        pcVar4 = s_P___08lx__08lx_004cb23c;
        if ((uVar2 & 0x2000000) == 0) goto LAB_0044952b;
      }
      else {
        pcVar4 = s_P___06lx__06lx_004cb24c;
      }
    }
    else {
      pcVar4 = s_P___04lx__04lx_004cb25c;
    }
  }
  else {
LAB_0044952b:
    pcVar4 = s_P___04lx__06lx_004cb22c;
  }
  sprintf(acStack_300,pcVar4,*puVar8,puVar8[1]);
  uVar6 = 0xffffffff;
  pcVar4 = acStack_300;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar7 = ~uVar6 - 1;
  iVar5 = (**(code **)(cur_itype + 0x10))(puVar8 + 1,auStack_100,uStack_304,local_314,0);
  if (1 < iVar5) {
    puVar8 = puVar8 + 2;
    iVar5 = iVar5 + -1;
    do {
      if (uStack_310 == 0) {
LAB_0044959c:
        if (((uVar2 & 0x200) != 0) || (pcVar4 = s__08lx_004cb21c, (uVar2 & 0x2000000) == 0)) {
LAB_004495b1:
          pcVar4 = s__06lx_004cb214;
        }
      }
      else {
        if ((uVar2 & 0x4000000) != 0) goto LAB_004495b1;
        if (uStack_310 == 0) goto LAB_0044959c;
        pcVar4 = s__04lx_004cb224;
      }
      sprintf(acStack_300 + iVar7,pcVar4,*puVar8);
      uVar6 = 0xffffffff;
      pcVar4 = acStack_300;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      iVar7 = ~uVar6 - 1;
      puVar8 = puVar8 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  sprintf(acStack_300 + iVar7,&DAT_004cb20c,auStack_100);
  io = pvStack_308;
LAB_004495ff:
  if (io != (void *)0x0) {
    sprintf(acStack_200,&DAT_004cb150,acStack_300);
    io_emit(io,acStack_200);
  }
  if (pvStack_30c != (void *)0x0) {
    if (*(int *)((int)pvStack_30c + 0x150) == 0) {
      sprintf(acStack_200,&DAT_004cb15c,acStack_300);
    }
    else {
      sprintf(acStack_200,s__01lu__s_004cb160,*(undefined4 *)(cur_dev + 0x20),acStack_300);
    }
    io_emit(pvStack_30c,acStack_200);
  }
  return;
}


/* ==== io_out_pin_write @ 004496a0 ==== */

void __cdecl io_out_pin_write(int pin,ulong *value,int delta)

{
  code *pcVar1;
  uint uVar2;
  uint uVar3;
  void *io;
  int iVar4;
  int iVar5;
  void *io_00;
  int iVar6;
  uint *puVar7;
  bool bVar8;
  char *pcVar9;
  char *pcVar10;
  char *va1;
  char acStack_23c [20];
  undefined4 uStack_228;
  undefined4 uStack_224;
  char *pcStack_220;
  char acStack_200 [256];
  char acStack_100 [256];
  
  va1 = (char *)*value;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar3 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar3 = (**(code **)(cur_dtype + 0x4e8))();
  }
  cur_itype = *(int *)(itype_tab + *cur_dev * 4);
  iVar6 = cur_dev[8];
  iolist_find(*(void **)(cur_sim + 0x154),1,pin,0);
  if (io != (void *)0x0) {
    bVar8 = false;
    if (delta < 0) {
      iVar4 = *(int *)((int)io + 0x1d8);
      *(int *)((int)io + 0x1d8) = iVar6;
      delta = iVar6 - iVar4;
      if (*(int *)((int)io + 0x1d0) != 0) {
        *(undefined4 *)((int)io + 0x1d0) = 0;
        delta = 0;
      }
      bVar8 = delta < 0;
    }
    if (delta != 0 && !bVar8) {
      sprintf(acStack_200,s___01ld_004cb154,delta);
      io_emit(io,acStack_200);
    }
    pcVar1 = *(code **)(*(int *)(*(int *)(cur_itype + 8) + *(int *)((int)io + 0x158) * 4) + 0xc);
    if ((pcVar1 == (code *)0x0) || (iVar4 = (*pcVar1)(io,value,acStack_100), iVar4 == 0)) {
      switch(*(undefined4 *)((int)io + 0x1d4)) {
      case 0:
        if ((uVar3 & 0x10000000) == 0) {
          iVar4 = (-(uint)((uVar3 & 0x2000000) != 0) & 8) + 0x18;
        }
        else {
          iVar4 = 0x10;
        }
        iVar5 = 0;
        if (iVar4 != 0) {
          puVar7 = &abort_flag + iVar4;
          do {
            uVar2 = *puVar7;
            puVar7 = puVar7 + -1;
            acStack_100[iVar5] = (((uint)va1 & uVar2) != 0) + '0';
            iVar5 = iVar5 + 1;
          } while (iVar5 < iVar4);
        }
        pcVar9 = acStack_100;
        acStack_100[iVar4] = '\0';
        pcVar10 = &DAT_004cb150;
        break;
      case 1:
        pcVar10 = s__01ld_004cb1d4;
        pcVar9 = va1;
        goto LAB_0044982c;
      case 2:
        pcStack_220 = va1;
        word_to_frac(uVar3,&uStack_228);
        sprintf(acStack_200,s__1_7f_004cb1c4,uStack_228,uStack_224);
        goto LAB_0044988d;
      case 3:
      case 4:
        pcVar10 = s__01lx_004cb1bc;
        pcVar9 = va1;
        break;
      default:
        goto switchD_004497ba_default;
      }
      sprintf(acStack_200,pcVar10,pcVar9);
    }
    else {
      pcVar10 = &DAT_004cb150;
      pcVar9 = acStack_100;
LAB_0044982c:
      sprintf(acStack_200,pcVar10,pcVar9);
    }
LAB_0044988d:
    io_emit(io,acStack_200);
  }
switchD_004497ba_default:
  iolist_find(*(void **)(cur_sim + 0x158),1,pin,0);
  if (io_00 == (void *)0x0) {
    return;
  }
  if (*(int *)((int)io_00 + 0x150) == 0) {
    acStack_23c[0] = '\0';
  }
  else {
    sprintf(acStack_23c,s__01lu_004cb1b4,iVar6);
  }
  pcVar1 = *(code **)(*(int *)(*(int *)(cur_itype + 8) + *(int *)((int)io_00 + 0x158) * 4) + 0xc);
  if ((pcVar1 != (code *)0x0) && (iVar6 = (*pcVar1)(io_00,value,acStack_100), iVar6 != 0)) {
    sprintf(acStack_200,s__s_s_004cb1ac,acStack_23c,acStack_100);
    io_emit(io_00,acStack_200);
    return;
  }
  switch(*(undefined4 *)((int)io_00 + 0x1d4)) {
  case 0:
    if ((uVar3 & 0x10000000) == 0) {
      iVar6 = (-(uint)((uVar3 & 0x2000000) != 0) & 8) + 0x18;
    }
    else {
      iVar6 = 0x10;
    }
    iVar4 = 0;
    if (iVar6 != 0) {
      puVar7 = &abort_flag + iVar6;
      do {
        uVar3 = *puVar7;
        puVar7 = puVar7 + -1;
        acStack_100[iVar4] = (((uint)va1 & uVar3) != 0) + '0';
        iVar4 = iVar4 + 1;
      } while (iVar4 < iVar6);
    }
    va1 = acStack_100;
    acStack_100[iVar6] = '\0';
    pcVar9 = s__s_s_004cb1ac;
    break;
  case 1:
    pcVar9 = s__s_01ld_004cb1a0;
    break;
  case 2:
    pcStack_220 = va1;
    word_to_frac(uVar3,&uStack_228);
    sprintf(acStack_200,s__s_1_7f_004cb194,acStack_23c,uStack_228,uStack_224);
    goto LAB_00449a28;
  case 3:
  case 4:
    pcVar9 = s__s_01lx_004cb188;
    break;
  default:
    goto switchD_0044995f_default;
  }
  sprintf(acStack_200,pcVar9,acStack_23c,va1);
LAB_00449a28:
  io_emit(io_00,acStack_200);
switchD_0044995f_default:
  return;
}


/* ==== io_out_periph_write @ 00449a70 ==== */

void __cdecl io_out_periph_write(int a,int b)

{
  int va0;
  void *io;
  void *io_00;
  char local_214 [20];
  char local_200 [256];
  char local_100 [256];
  
  cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
  va0 = cur_dev[8];
  local_200[0] = '\0';
  iolist_find(*(void **)(cur_sim + 0x154),9,a,b);
  iolist_find(*(void **)(cur_sim + 0x158),9,a,b);
  if (io != (void *)0x0) {
    fmt_register(a,b,*(int *)((int)io + 0x1d4),local_100);
    sprintf(local_200,&DAT_004c5990,local_100);
    io_emit(io,local_200);
  }
  if (io_00 != (void *)0x0) {
    if (*(int *)((int)io_00 + 0x150) == 0) {
      local_214[0] = '\0';
    }
    else {
      sprintf(local_214,s__01lu_004cb1b4,va0);
    }
    fmt_register(a,b,*(int *)((int)io_00 + 0x1d4),local_100);
    sprintf(local_200,s__s_s_004cb1ac,local_214,local_100);
    io_emit(io_00,local_200);
  }
  return;
}


/* ==== cmd_output_parse @ 00449bb0 ==== */

undefined ** cmd_output_parse(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int iStack_4;
  
  iStack_4 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    iStack_4 = 0;
    goto LAB_00449e01;
  }
  iVar1 = parm_break_number(2);
  iVar2 = parm_keyword1((iVar1 != 0) + 2,&DAT_004c16b8);
  iVar4 = (uint)(iVar1 != 0) + (uint)(iVar2 != 0);
  iVar1 = iVar4 + 2;
  iVar2 = parm_keyword1(iVar1,&DAT_004c6aec);
  if (iVar2 == 0) {
    iVar2 = parm_keyword1(iVar1,s_ehistory_004cb280);
    if (iVar2 == 0) {
      iVar2 = parm_keyword1(iVar1,s_dhistory_004cb274);
      if ((iVar2 != 0) || (iVar3 = parm_keyword1(iVar1,s_history_004cb26c), iVar3 != 0)) {
        cVar5 = (-(iVar2 != 0) & 2U) + 0x4a;
        goto LAB_00449d5e;
      }
      iVar1 = parm_mem_or_reg_y(iVar1);
      if (iVar1 == 0) goto LAB_00449e01;
      iVar1 = iVar4 + 4;
      iVar2 = parm_kw_r3_radix_opt(iVar1);
      if (((((iVar2 == 0) || (iVar2 = parm_check_too_many(iVar4 + 5), iVar2 == 0)) &&
           ((iVar2 = parm_kw_o_options(iVar1), iVar2 == 0 ||
            (iVar2 = parm_check_too_many(iVar4 + 5), iVar2 == 0)))) &&
          (((iVar2 = parm_kw_r3_radix_opt(iVar1), iVar2 == 0 ||
            (iVar2 = parm_kw_o_options(iVar4 + 5), iVar2 == 0)) ||
           (iVar2 = parm_check_too_many(iVar4 + 6), iVar2 == 0)))) &&
         (iVar1 = parm_check_too_many(iVar1), iVar1 == 0)) goto LAB_00449e01;
      iVar4 = iVar4 + 3;
      iVar1 = parm_keyword1(iVar4,&DAT_004c6aec);
      if (iVar1 != 0) {
        iStack_4 = 1;
        goto LAB_00449e01;
      }
      iVar1 = parm_keyword1(iVar4,&DAT_004cb138);
      if (iVar1 != 0) {
        iStack_4 = 3;
        goto LAB_00449e01;
      }
      iVar1 = parm_any_token(iVar4);
joined_r0x00449df7:
      if (iVar1 == 0) goto LAB_00449e01;
    }
    else {
      cVar5 = 'K';
LAB_00449d5e:
      iVar1 = iVar4 + 3;
      (&DAT_004a93ea)[iVar4] = cVar5;
      iVar2 = parm_keyword1(iVar1,&DAT_004c6aec);
      if (iVar2 != 0) {
        iVar4 = iVar4 + 4;
        goto LAB_00449d7c;
      }
      iVar2 = parm_keyword1(iVar1,&DAT_004cb138);
      if (iVar2 != 0) {
        iVar1 = parm_check_too_many(iVar4 + 4);
        if (iVar1 != 0) {
          iStack_4 = 3;
        }
        goto LAB_00449e01;
      }
      iVar1 = parm_any_token(iVar1);
      if (iVar1 == 0) goto LAB_00449e01;
      iVar1 = parm_check_too_many(iVar4 + 4);
      if (iVar1 == 0) {
        iVar1 = parm_kw_o_options(iVar4 + 4);
        if (iVar1 == 0) goto LAB_00449e01;
        iVar1 = parm_check_too_many(iVar4 + 5);
        goto joined_r0x00449df7;
      }
    }
    iStack_4 = 2;
  }
  else {
    iVar4 = iVar4 + 3;
LAB_00449d7c:
    iVar1 = parm_check_too_many(iVar4);
    if (iVar1 != 0) {
      iStack_4 = 1;
    }
  }
LAB_00449e01:
  if (iStack_4 != -1) {
    return &PTR_cmd_output_h0_004caa80 + iStack_4 * 2;
  }
  return (undefined **)0x0;
}


/* ==== cmd_more_h0 @ 00449e20 ==== */

void cmd_more_h0(void)

{
  more_flag = 1;
  return;
}


/* ==== cmd_more_h1 @ 00449e30 ==== */

void cmd_more_h1(void)

{
  more_flag = 0;
  return;
}


/* ==== cmd_more_parse @ 00449e40 ==== */

undefined ** cmd_more_parse(void)

{
  int iVar1;
  
  iVar1 = parm_check_too_many(2);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004c6aec);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(3);
      if (iVar1 != 0) {
        iVar1 = 1;
        goto LAB_00449e7d;
      }
    }
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
  }
LAB_00449e7d:
  if (iVar1 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_more_h0_004cb2c8 + iVar1 * 2;
}


/* ==== cmd_log_h0 @ 00449e90 ==== */

void cmd_log_h0(void)

{
  char cVar1;
  char cVar2;
  char acStack_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  cVar2 = DAT_004a93ea;
  cVar1 = (&cmd_tokbuf)[DAT_004a9470];
  if (((DAT_004a93ea == 'e') || (cVar1 == 'c')) && (cmdlog_fp != 0)) {
    sprintf(acStack_100,s_Logging_commands_to___s__004cb930,&cmdlog_name);
    out_text(acStack_100,1);
  }
  if (((cVar2 == 'e') || (cVar1 == 's')) && (*(int *)(cur_sim + 0x48) != 0)) {
    sprintf(acStack_100,s_Logging_session_to___s__004cb918,cur_sim + 0x4c);
    out_text(acStack_100,1);
  }
  if (profiler_hook != (undefined *)0x0) {
    if (((int *)(cur_sim + 0x188) != (int *)0x0) && (*(int *)(cur_sim + 0x188) != 0)) {
      sprintf(acStack_100,s_Profiling_to___s__004cb904,cur_sim + 0x18c);
      out_text(acStack_100,1);
    }
  }
  return;
}


/* ==== cmd_log_h6 @ 00449f80 ==== */

void cmd_log_h6(void)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = cur_sim;
  piVar1 = (int *)(cur_sim + 0x188);
  if ((profiler_hook != (undefined *)0x0) && (*piVar1 != 0)) {
    out_text(s_Generating_profile__Please_wait__004cb954,1);
    screen_flush();
    prof_report(*(long *)(iVar2 + 0x28c));
    *piVar1 = 0;
    out_text(s_Done__004cb94c,1);
    screen_flush();
  }
  return;
}


/* ==== cmd_log_h5 @ 00449fe0 ==== */

void cmd_log_h5(int param_1)

{
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  void *stream;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  undefined4 *puVar9;
  char *pcVar10;
  undefined4 uStack_204;
  char acStack_200 [256];
  char acStack_100 [256];
  
  iVar4 = cur_sim;
  puVar1 = (undefined4 *)(cur_sim + 0x188);
  if (profiler_hook == (undefined *)0x0) {
    sim_error(s_Profiler_not_available_in_this_s_004cb9b4);
    return;
  }
  uVar5 = 0xffffffff;
  pcVar8 = &cmd_tokbuf + DAT_004a9474;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar2 != '\0');
  strncpy(acStack_200,(char *)(DAT_004a9474 + param_1),~uVar5 - 1);
  acStack_200[~uVar5 - 1] = '\0';
  if (DAT_004a93ec == 'o') {
    iVar6 = DAT_004a9710 + 1;
  }
  else {
    iVar6 = 0;
  }
  path_combine((char *)(cur_dev + 0x58),acStack_200,PTR_DAT_004cb484,acStack_100);
  sprintf(acStack_200,s_Output_profile__s_004cb9a0,acStack_100);
  out_text(acStack_200,1);
  uStack_204 = confirm_overwrite(acStack_100,iVar6);
  if (uStack_204 != -1) {
    fopen(acStack_100,(&PTR_DAT_004cb478)[uStack_204]);
    if (stream == (void *)0x0) {
      sim_error(s_Error_opening_file__004c59d8);
      return;
    }
    fclose(stream);
    puVar9 = puVar1;
    for (iVar6 = 0xeab; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    uVar5 = 0xffffffff;
    pcVar8 = acStack_100;
    do {
      pcVar10 = pcVar8;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar10 = pcVar8 + 1;
      cVar2 = *pcVar8;
      pcVar8 = pcVar10;
    } while (cVar2 != '\0');
    uVar5 = ~uVar5;
    pcVar8 = pcVar10 + -uVar5;
    pcVar10 = (char *)(iVar4 + 0x18c);
    for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar10 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar10 = pcVar10 + 1;
    }
    *puVar1 = 1;
    *(undefined4 *)(iVar4 + 0x28c) = 0;
    uVar3 = *(undefined4 *)(cur_dev + 0x1c);
    *(undefined4 *)(iVar4 + 0x480) = 0;
    *(undefined4 *)(iVar4 + 0x290) = uVar3;
    *(undefined4 *)(iVar4 + 0x484) = 0;
    *(undefined4 *)(iVar4 + 0x488) = 1;
    *(undefined4 *)(iVar4 + 0x48c) = 0;
    out_text(s_Initializing_profiler__Please_wa_004cb978,1);
    screen_flush();
    prof_start(*(char **)(cur_sim + 0x4018),(char *)(iVar4 + 0x18c),(&PTR_DAT_004cb478)[uStack_204])
    ;
    *(undefined4 *)(iVar4 + 0x428) = 0;
    out_text(s_Done__004cb94c,1);
    screen_flush();
  }
  return;
}


/* ==== cmd_log_h1 @ 0044a1d0 ==== */

void cmd_log_h1(int param_1)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  int *piVar7;
  byte *pbVar8;
  char *pcVar9;
  bool bVar10;
  char cStack_302;
  char acStack_301 [257];
  byte abStack_200 [256];
  byte abStack_100 [256];
  
  cStack_302 = 'e';
  acStack_301[0] = 'x';
  if (DAT_004a93eb != 'e') {
    puVar6 = &DAT_004a93eb;
    piVar7 = &DAT_004a9474;
    cVar2 = DAT_004a93eb;
    do {
      if (cVar2 == 'N') {
        uVar5 = 0xffffffff;
        acStack_301[0] = 'N';
        pcVar9 = &cmd_tokbuf + *piVar7;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar2 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar2 != '\0');
        strncpy(acStack_301 + 1,(char *)(*piVar7 + param_1),~uVar5 - 1);
        acStack_301[~uVar5] = '\0';
        path_combine((char *)(cur_dev + 0x58),acStack_301 + 1,&DAT_004c5fc0,(char *)abStack_200);
        path_combine((char *)(cur_dev + 0x58),acStack_301 + 1,&DAT_004cb4f0,(char *)abStack_100);
      }
      else if (cVar2 == 'j') {
        cStack_302 = (&cmd_tokbuf)[*piVar7];
      }
      cVar2 = puVar6[1];
      piVar7 = piVar7 + 1;
      puVar6 = puVar6 + 1;
    } while (cVar2 != 'e');
  }
  if (((cStack_302 == 'e') || (cStack_302 == 'c')) && (cmdlog_fp != (void *)0x0)) {
    if (acStack_301[0] == 'x') {
LAB_0044a309:
      fclose(cmdlog_fp);
      cmdlog_fp = (void *)0x0;
    }
    else if (acStack_301[0] == 'N') {
      pbVar8 = abStack_200;
      pbVar3 = &cmdlog_name;
      do {
        bVar1 = *pbVar3;
        bVar10 = bVar1 < *pbVar8;
        if (bVar1 != *pbVar8) {
LAB_0044a300:
          iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_0044a305;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar10 = bVar1 < pbVar8[1];
        if (bVar1 != pbVar8[1]) goto LAB_0044a300;
        pbVar3 = pbVar3 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_0044a305:
      if (iVar4 == 0) goto LAB_0044a309;
    }
  }
  if (((cStack_302 != 'e') && (cStack_302 != 's')) || (*(void **)(cur_sim + 0x48) == (void *)0x0))
  goto LAB_0044a392;
  if (acStack_301[0] != 'x') {
    if (acStack_301[0] != 'N') goto LAB_0044a392;
    pbVar8 = abStack_100;
    pbVar3 = (byte *)(cur_sim + 0x4c);
    do {
      bVar1 = *pbVar3;
      bVar10 = bVar1 < *pbVar8;
      if (bVar1 != *pbVar8) {
LAB_0044a374:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_0044a379;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar10 = bVar1 < pbVar8[1];
      if (bVar1 != pbVar8[1]) goto LAB_0044a374;
      pbVar3 = pbVar3 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_0044a379:
    if (iVar4 != 0) goto LAB_0044a392;
  }
  fclose(*(void **)(cur_sim + 0x48));
  *(undefined4 *)(cur_sim + 0x48) = 0;
LAB_0044a392:
  cmd_log_h6(param_1);
  return;
}


/* ==== cmd_log_h2 @ 0044a3b0 ==== */

void cmd_log_h2(int param_1)

{
  char cVar1;
  void *stream;
  int iVar2;
  void *stream_00;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char acStack_200 [256];
  char acStack_100 [256];
  
  uVar4 = (uint)((&cmd_tokbuf)[DAT_004a9470] != 'c');
  uVar3 = 0xffffffff;
  pcVar5 = &cmd_tokbuf + DAT_004a9474;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  strncpy(acStack_200,(char *)(DAT_004a9474 + param_1),~uVar3 - 1);
  acStack_200[~uVar3 - 1] = '\0';
  if (DAT_004a93ec == 'o') {
    iVar2 = DAT_004a9710 + 1;
  }
  else {
    iVar2 = 0;
  }
  path_combine((char *)(cur_dev + 0x58),acStack_200,(&PTR_DAT_004cb488)[uVar4],acStack_100);
  sprintf(acStack_200,s_Output_log_file__s_004cb9e0,acStack_100);
  out_text(acStack_200,1);
  stream = cmdlog_fp;
  if (uVar4 != 0) {
    stream = *(void **)(cur_sim + 0x48);
  }
  if (stream != (void *)0x0) {
    fclose(stream);
  }
  iVar2 = confirm_overwrite(acStack_100,iVar2);
  if (iVar2 != -1) {
    fopen(acStack_100,(&PTR_DAT_004cb478)[iVar2]);
    if (stream_00 == (void *)0x0) {
      sim_error(s_Error_opening_file__004c59d8);
      return;
    }
    if (iVar2 == 1) {
      fseek(stream_00,0,2);
    }
    if (uVar4 == 0) {
      pcVar5 = &cmdlog_name;
      cmdlog_fp = stream_00;
    }
    else {
      *(void **)(cur_sim + 0x48) = stream_00;
      pcVar5 = (char *)(cur_sim + 0x4c);
    }
    uVar3 = 0xffffffff;
    pcVar6 = acStack_100;
    do {
      pcVar7 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar7 + -uVar3;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar5 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar5 = pcVar5 + 1;
    }
  }
  return;
}


/* ==== cmd_log_h3 @ 0044a540 ==== */

void cmd_log_h3(void)

{
  *(undefined4 *)(cur_sim + 0x184) = 1;
  return;
}


/* ==== cmd_log_h4 @ 0044a550 ==== */

void cmd_log_h4(void)

{
  *(undefined4 *)(cur_sim + 0x184) = 0;
  return;
}


/* ==== cmd_log_parse @ 0044a560 ==== */

undefined ** cmd_log_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_check_too_many(2);
  if (iVar1 != 0) {
    iVar2 = 0;
    goto LAB_0044a782;
  }
  iVar1 = parm_keyword1(2,&DAT_004c6aec);
  if (iVar1 == 0) {
    iVar1 = parm_keyword1(2,&DAT_004a86c0);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(2,&DAT_004cb9f4);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(2,&DAT_004c7e04);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(2,&DAT_004c73d8);
          if (iVar1 != 0) {
            iVar1 = parm_check_too_many(3);
            if (iVar1 != 0) {
              iVar2 = 3;
            }
          }
          goto LAB_0044a782;
        }
      }
      iVar1 = parm_check_too_many(3);
      if (iVar1 == 0) {
        iVar1 = parm_any_token(3);
        if (iVar1 != 0) {
          iVar1 = parm_check_too_many(4);
          if (iVar1 == 0) {
            iVar1 = parm_kw_o_options(4);
            if (iVar1 == 0) goto LAB_0044a782;
            iVar1 = parm_check_too_many(5);
            if (iVar1 == 0) goto LAB_0044a782;
          }
          iVar2 = 2;
        }
      }
      else {
        iVar2 = 0;
      }
    }
    else {
      iVar1 = parm_any_token(3);
      if (iVar1 != 0) {
        iVar1 = parm_check_too_many(4);
        if (iVar1 != 0) {
          iVar2 = 5;
          goto LAB_0044a782;
        }
      }
      iVar1 = parm_any_token(3);
      if (iVar1 != 0) {
        iVar1 = parm_kw_o_options(4);
        if (iVar1 != 0) {
          iVar1 = parm_check_too_many(5);
          if (iVar1 != 0) {
            iVar2 = 5;
          }
        }
      }
    }
  }
  else {
    iVar1 = parm_check_too_many(3);
    if (iVar1 == 0) {
      iVar1 = parm_keyword1(3,&DAT_004c73d8);
      if (iVar1 == 0) {
        iVar1 = parm_keyword1(3,&DAT_004a86c0);
        if (iVar1 == 0) {
          iVar1 = parm_keyword1(3,&DAT_004cb9f4);
          if (iVar1 == 0) {
            iVar1 = parm_keyword1(3,&DAT_004c7e04);
            if (iVar1 == 0) goto LAB_0044a782;
          }
          iVar1 = parm_check_too_many(4);
          if (iVar1 == 0) {
            iVar1 = parm_any_token(4);
            if (iVar1 == 0) goto LAB_0044a782;
            iVar1 = parm_check_too_many(5);
            if (iVar1 == 0) goto LAB_0044a782;
          }
          iVar2 = 1;
        }
        else {
          iVar1 = parm_check_too_many(4);
          if (iVar1 != 0) {
            iVar2 = 6;
          }
        }
      }
      else {
        iVar1 = parm_check_too_many(4);
        if (iVar1 != 0) {
          iVar2 = 4;
        }
      }
    }
    else {
      iVar2 = 1;
    }
  }
LAB_0044a782:
  if (iVar2 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_log_h0_004cb490 + iVar2 * 2;
}


/* ==== cmd_load_h1 @ 0044a7a0 ==== */

void cmd_load_h1(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char acStack_200 [256];
  char acStack_100 [256];
  
  uVar3 = 0xffffffff;
  pcVar5 = &g_cmdline + DAT_004a9474;
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
  pcVar6 = acStack_200;
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
  cdb_free_frames();
  path_search(acStack_200,&DAT_004c97ec,acStack_100);
  sprintf(acStack_200,s_Loading_State_file__s_004cbda8,acStack_100);
  log_echo(acStack_200,1);
  screen_flush();
  iVar2 = load_state(acStack_100);
  if (iVar2 != 0) {
    sprintf(acStack_200,s_Error_reading_file__s_004cbd90,acStack_100);
    sim_error(acStack_200);
  }
  return;
}


/* ==== cmd_load_h0 @ 0044a870 ==== */

void cmd_load_h0(int param_1)

{
  char cVar1;
  byte bVar2;
  undefined uVar3;
  int iVar4;
  undefined3 extraout_var;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  byte *pbVar8;
  char *pcVar9;
  bool bVar10;
  char acStack_200 [3];
  byte abStack_1fd [5];
  char acStack_1f8 [247];
  char acStack_101 [257];
  
  cdb_free_frames();
  uVar7 = 0xffffffff;
  pcVar9 = &cmd_tokbuf + DAT_004a9470;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  strncpy(acStack_101 + 1,(char *)(DAT_004a9470 + param_1),~uVar7 - 1);
  acStack_101[~uVar7] = '\0';
  iVar4 = path_search(acStack_101 + 1,(char *)0x4c9840,acStack_200);
  if (iVar4 == 0) {
    path_search(acStack_101 + 1,(char *)0x4cbe0c,acStack_200);
  }
  sprintf(acStack_101 + 1,s_Loading_file__s_004cbdfc,acStack_200);
  log_echo(acStack_101 + 1,1);
  screen_flush();
  uVar3 = cmd_load_h0_sub_434350(*(undefined4 *)(cur_dev + 4),acStack_200);
  if (CONCAT31(extraout_var,uVar3) == 0) {
    sim_error(s_Error_reading_input_file_004cbde0);
    return;
  }
  uVar7 = 0xffffffff;
  pcVar9 = acStack_1f8;
  do {
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (4 < (int)(~uVar7 - 1)) {
    pbVar6 = abStack_1fd + ~uVar7;
    pbVar8 = (byte *)0x4cbe0c;
    pbVar5 = pbVar6;
    do {
      bVar2 = *pbVar5;
      bVar10 = bVar2 < *pbVar8;
      if (bVar2 != *pbVar8) {
LAB_0044a99e:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_0044a9a3;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar5[1];
      bVar10 = bVar2 < pbVar8[1];
      if (bVar2 != pbVar8[1]) goto LAB_0044a99e;
      pbVar5 = pbVar5 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar2 != 0);
    iVar4 = 0;
LAB_0044a9a3:
    if (iVar4 != 0) {
      pbVar5 = (byte *)0x4cbdd8;
      do {
        bVar2 = *pbVar6;
        bVar10 = bVar2 < *pbVar5;
        if (bVar2 != *pbVar5) {
LAB_0044a9d6:
          iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_0044a9db;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar6[1];
        bVar10 = bVar2 < pbVar5[1];
        if (bVar2 != pbVar5[1]) goto LAB_0044a9d6;
        pbVar6 = pbVar6 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_0044a9db:
      if (iVar4 != 0) {
        return;
      }
    }
    iVar4 = dbg_load_cld(*(int *)(cur_dev + 4),acStack_1f8);
    if (iVar4 == -1) {
      sim_error(s_Error_reading_symbols_004cbdc0);
    }
  }
  return;
}


/* ==== cmd_load_h3 @ 0044aa20 ==== */

void cmd_load_h3(int param_1)

{
  char cVar1;
  undefined uVar2;
  int iVar3;
  undefined3 extraout_var;
  uint uVar4;
  char *pcVar5;
  char acStack_200 [256];
  char acStack_100 [256];
  
  cdb_free_frames();
  uVar4 = 0xffffffff;
  pcVar5 = &cmd_tokbuf + DAT_004a9474;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  strncpy(acStack_200,(char *)(DAT_004a9474 + param_1),~uVar4 - 1);
  acStack_200[~uVar4 - 1] = '\0';
  iVar3 = path_search(acStack_200,(char *)0x4c9840,acStack_100);
  if (iVar3 == 0) {
    path_search(acStack_200,(char *)0x4cbe0c,acStack_100);
  }
  sprintf(acStack_200,s_Loading_file__s_004cbdfc,acStack_100);
  log_echo(acStack_200,1);
  screen_flush();
  uVar2 = cmd_load_h0_sub_434350(*(undefined4 *)(cur_dev + 4),acStack_100);
  if (CONCAT31(extraout_var,uVar2) == 0) {
    sim_error(s_Error_reading_input_file_004cbde0);
  }
  return;
}


/* ==== cmd_load_h2 @ 0044ab00 ==== */

void cmd_load_h2(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char acStack_200 [256];
  char acStack_100 [256];
  
  cdb_free_frames();
  uVar3 = 0xffffffff;
  pcVar4 = &cmd_tokbuf + DAT_004a9474;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  strncpy(acStack_200,(char *)(DAT_004a9474 + param_1),~uVar3 - 1);
  acStack_200[~uVar3 - 1] = '\0';
  path_search(acStack_200,(char *)0x4cbe0c,acStack_100);
  sprintf(acStack_200,s_Loading_Debug_info_from_file__s_004cbe24,acStack_100);
  log_echo(acStack_200,1);
  screen_flush();
  iVar2 = dbg_load_cld(*(int *)(cur_dev + 4),acStack_100);
  if (iVar2 == -1) {
    sim_error(s_Error_reading_symbols_004cbdc0);
  }
  if (*(int *)(cur_sim + 0x3fd8) == 0) {
    *(undefined4 *)(cur_sim + 0x4400) = 0;
    out_text(s__No_Debug_Info__004cbe14,1);
  }
  return;
}


/* ==== cmd_load_parse @ 0044abf0 ==== */

int cmd_load_parse(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  iVar1 = parm_keyword1(2,&DAT_004c7e04);
  if (iVar1 != 0) {
    iVar1 = parm_any_token(3);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(4);
      if (iVar1 != 0) {
        iVar2 = 1;
        goto LAB_0044acb7;
      }
    }
  }
  iVar1 = parm_keyword1(2,&DAT_004c6ab4);
  if (iVar1 != 0) {
    iVar1 = parm_any_token(3);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(4);
      if (iVar1 != 0) {
        iVar2 = 2;
        goto LAB_0044acb7;
      }
    }
  }
  iVar1 = parm_keyword1(2,&DAT_004cb2f8);
  if (iVar1 != 0) {
    iVar1 = parm_any_token(3);
    if (iVar1 != 0) {
      iVar1 = parm_check_too_many(4);
      if (iVar1 != 0) {
        iVar2 = 3;
        goto LAB_0044acb7;
      }
    }
  }
  iVar1 = parm_any_token(2);
  if (iVar1 != 0) {
    iVar1 = parm_check_too_many(3);
    if (iVar1 != 0) {
      iVar2 = 0;
    }
  }
LAB_0044acb7:
  if (iVar2 == -1) {
    return 0;
  }
  return iVar2 * 8 + 0x4cba58;
}


/* ==== cmd_input_h0 @ 0044acd0 ==== */

void cmd_input_h0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char acStack_100 [256];
  
  iVar1 = io_next_free_id(0,(void **)(cur_sim + 0x150));
  iVar2 = io_next_free_id(0,(void **)(cur_sim + 0x14c));
  if (iVar1 <= iVar2) {
    iVar1 = iVar2;
  }
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  iVar2 = 1;
  if (0 < iVar1) {
    do {
      iVar3 = io_next_free_id(iVar2,(void **)(cur_sim + 0x14c));
      if (iVar3 == iVar2) {
        iVar3 = *(int *)(cur_sim + 0x14c);
        if (iVar3 == 0) {
LAB_0044ae00:
          iVar3 = iVar2 + 1;
        }
        else {
          do {
            if (*(int *)(iVar3 + 0x1e4) == iVar2) {
              sprintf(acStack_100,s__d__Untimed_reads_of__s_from__s_004cc408,iVar2,iVar3 + 0x100,
                      iVar3);
              log_echo(acStack_100,1);
              iVar3 = iVar2 + 1;
              goto LAB_0044ae1a;
            }
            iVar3 = *(int *)(iVar3 + 0x1e0);
          } while (iVar3 != 0);
          iVar3 = iVar2 + 1;
        }
      }
      else {
        iVar4 = io_next_free_id(iVar2,(void **)(cur_sim + 0x150));
        if (iVar4 == iVar2) {
          iVar3 = *(int *)(cur_sim + 0x150);
          if (iVar3 == 0) goto LAB_0044ae00;
          do {
            if (*(int *)(iVar3 + 0x1e4) == iVar2) {
              sprintf(acStack_100,s__d__Timed_reads_of__s_from__s_004cc3e8,iVar2,iVar3 + 0x100,iVar3
                     );
              log_echo(acStack_100,1);
              goto LAB_0044ae00;
            }
            iVar3 = *(int *)(iVar3 + 0x1e0);
          } while (iVar3 != 0);
          iVar3 = iVar2 + 1;
        }
        else if ((iVar4 == 0) || (iVar3 == 0)) {
          iVar3 = iVar3 + iVar4;
        }
        else if (iVar4 < iVar3) {
          iVar3 = iVar4;
        }
      }
LAB_0044ae1a:
      iVar2 = iVar3;
    } while (iVar3 <= iVar1);
  }
  return;
}


/* ==== io_next_free_id @ 0044ae30 ==== */

int __cdecl io_next_free_id(int id,void **list)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  pvVar1 = *list;
  iVar3 = 0;
  iVar4 = 0;
  while( true ) {
    if (pvVar1 == (void *)0x0) {
      if (id == 0) {
        iVar3 = iVar4;
      }
      return iVar3;
    }
    iVar2 = *(int *)((int)pvVar1 + 0x1e4);
    if (iVar2 == id) break;
    if (iVar4 < iVar2) {
      iVar4 = iVar2;
    }
    if ((id < iVar2) && ((iVar2 < iVar3 || (iVar3 == 0)))) {
      iVar3 = iVar2;
    }
    pvVar1 = *(void **)((int)pvVar1 + 0x1e0);
  }
  return iVar2;
}


/* ==== cmd_input_h1 @ 0044ae80 ==== */

void cmd_input_h1(void)

{
  int mode;
  
  if (DAT_004a93ea == '#') {
    mode = g_io_id_arg + 2;
    iolist_remove((void *)(cur_sim + 0x14c),&empty_str,mode);
    iolist_remove((void *)(cur_sim + 0x150),&empty_str,mode);
    return;
  }
  if (DAT_004a93eb == 'e') {
    iolist_remove((void *)(cur_sim + 0x14c),&empty_str,1);
    iolist_remove((void *)(cur_sim + 0x150),&empty_str,1);
    return;
  }
  if (DAT_004a93ea == 'j') {
    iolist_remove((void *)(cur_sim + 0x150),&g_cmdline + DAT_004a9474,0);
    return;
  }
  iolist_remove((void *)(cur_sim + 0x14c),&g_cmdline + DAT_004a9470,0);
  return;
}


/* ==== io_lists_reset @ 0044af20 ==== */

void io_lists_reset(void)

{
  int mode;
  
  mode = g_io_id_arg + 2;
  iolist_remove((void *)(cur_sim + 0x14c),&empty_str,mode);
  iolist_remove((void *)(cur_sim + 0x150),&empty_str,mode);
  return;
}


/* ==== parse_num_dec @ 0044af70 ==== */

void __cdecl parse_num_dec(char *s,void *val,ulong type)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  char *pcVar7;
  
  uVar6 = 0;
  uVar2 = 0;
  cVar5 = *s;
  iVar4 = 0;
  if (cVar5 == '$') {
    parse_num_hex(s,val,type);
    return;
  }
  if (cVar5 != '%') {
    pcVar7 = s;
    if (cVar5 == '`') {
      cVar5 = s[1];
      pcVar7 = s + 1;
    }
    if (cVar5 == '-') {
      pcVar7 = pcVar7 + 1;
    }
    cVar1 = *pcVar7;
    while (('/' < cVar1 && (pcVar7 = pcVar7 + 1, cVar1 < ':'))) {
      uVar6 = cVar1 + -0x30 + uVar6 * 10;
      uVar2 = uVar2 * 10;
      iVar4 = iVar4 * 10;
      if (0xfffffff < uVar6) {
        uVar2 = uVar2 + (uVar6 >> 0x1c);
        uVar6 = uVar6 & 0xfffffff;
      }
      if (0xfffffff < uVar2) {
        iVar4 = iVar4 + (uVar2 >> 0x1c);
        uVar2 = uVar2 & 0xfffffff;
      }
      cVar1 = *pcVar7;
    }
    if ((cVar1 == '.') && (*s != '`')) {
      parse_num_float(s,val,type);
      return;
    }
    uVar6 = uVar6 | uVar2 << 0x1c;
    uVar2 = uVar2 >> 4 | iVar4 << 0x18;
    if (cVar5 == '-') {
      uVar6 = ~uVar6 + 1;
      uVar2 = ~uVar2;
      if (uVar6 == 0) {
        uVar2 = uVar2 + 1;
      }
    }
    if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
      uVar3 = *(uint *)(cur_dtype + 0xc);
    }
    else {
      uVar3 = (**(code **)(cur_dtype + 0x4e8))();
    }
    if ((uVar3 & 0x4000000) != 0) {
      uVar2 = uVar2 << 8 | uVar6 >> 0x18;
    }
    *(uint *)((int)val + 0xc) = uVar2;
    *(uint *)((int)val + 8) = uVar6;
    *(ulong *)((int)val + 0x1c) = type | 0x100;
    return;
  }
  parse_num_bin(s,val,type);
  return;
}


/* ==== parse_num_hex @ 0044b0b0 ==== */

void __cdecl parse_num_hex(char *s,void *val,ulong type)

{
  char cVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  cVar1 = *s;
  if (cVar1 == '$') {
    pcVar4 = s + 1;
  }
  else {
    if (cVar1 == '`') {
      parse_num_dec(s,val,type);
      return;
    }
    pcVar4 = s;
    if (cVar1 == '%') {
      parse_num_bin(s,val,type);
      return;
    }
  }
  cVar1 = *pcVar4;
  if (cVar1 == '-') {
    pcVar4 = pcVar4 + 1;
  }
  uVar6 = 0;
  uVar7 = 0;
  cVar2 = *pcVar4;
  while (cVar2 != '\0') {
    pcVar4 = pcVar4 + 1;
    if ((cVar2 < 'a') || ('f' < cVar2)) {
      if ((cVar2 < 'A') || ('F' < cVar2)) {
        if ((cVar2 < '0') || ('9' < cVar2)) break;
        iVar3 = cVar2 + -0x30;
      }
      else {
        iVar3 = cVar2 + -0x37;
      }
    }
    else {
      iVar3 = cVar2 + -0x57;
    }
    uVar5 = uVar6 >> 0x1c;
    uVar6 = uVar6 * 0x10 + iVar3;
    uVar7 = uVar7 << 4 | uVar5;
    cVar2 = *pcVar4;
  }
  if ((cVar2 == '.') && (*s != '$')) {
    parse_num_float(s,val,type);
    return;
  }
  if (cVar1 == '-') {
    uVar6 = ~uVar6 + 1;
    uVar7 = ~uVar7;
    if (uVar6 == 0) {
      uVar7 = uVar7 + 1;
    }
  }
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar5 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar5 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((uVar5 & 0x4000000) != 0) {
    uVar7 = uVar7 << 8 | uVar6 >> 0x18;
  }
  *(ulong *)((int)val + 0x1c) = type | 0x100;
  *(uint *)((int)val + 8) = uVar6;
  *(uint *)((int)val + 0xc) = uVar7;
  return;
}


/* ==== parse_num_bin @ 0044b1d0 ==== */

void __cdecl parse_num_bin(char *s,void *val,ulong type)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  
  cVar1 = *s;
  if (cVar1 == '%') {
    pcVar6 = s + 1;
  }
  else {
    pcVar6 = s;
    if (cVar1 == '$') {
      parse_num_hex(s,val,type);
    }
    else if (cVar1 == '`') {
      parse_num_dec(s,val,type);
      return;
    }
  }
  cVar1 = *pcVar6;
  if (cVar1 == '-') {
    pcVar6 = pcVar6 + 1;
  }
  uVar7 = 0;
  uVar5 = 0;
  cVar2 = *pcVar6;
  while (cVar2 != '\0') {
    pcVar6 = pcVar6 + 1;
    if (cVar2 == '1') {
      iVar3 = 1;
    }
    else {
      if (cVar2 != '0') break;
      iVar3 = 0;
    }
    uVar4 = uVar7 >> 0x1f;
    uVar7 = iVar3 + uVar7 * 2;
    uVar5 = uVar5 * 2 | uVar4;
    cVar2 = *pcVar6;
  }
  if ((cVar2 == '.') && (*s != '%')) {
    parse_num_float(s,val,type);
    return;
  }
  if (cVar1 == '-') {
    uVar7 = ~uVar7 + 1;
    uVar5 = ~uVar5;
    if (uVar7 == 0) {
      uVar5 = uVar5 + 1;
    }
  }
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar4 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar4 = (**(code **)(cur_dtype + 0x4e8))();
  }
  if ((uVar4 & 0x4000000) != 0) {
    uVar5 = uVar5 << 8 | uVar7 >> 0x18;
  }
  *(ulong *)((int)val + 0x1c) = type | 0x100;
  *(uint *)((int)val + 8) = uVar7;
  *(uint *)((int)val + 0xc) = uVar5;
  return;
}


/* ==== parse_num_float @ 0044b2e0 ==== */

void __cdecl parse_num_float(char *s,void *val,ulong type)

{
  char cVar1;
  ulong mode;
  double dVar2;
  
  cVar1 = *s;
  if (cVar1 == '`') {
    parse_num_dec(s,val,type);
    return;
  }
  if (cVar1 == '$') {
    parse_num_hex(s,val,type);
    return;
  }
  if (cVar1 == '%') {
    parse_num_bin(s,val,type);
    return;
  }
  *(ulong *)((int)val + 0x1c) = type | 0x200;
  dVar2 = strtod(s,(char **)&type);
  *(double *)val = dVar2;
  if (*(code **)(cur_dtype + 0x4e8) != (code *)0x0) {
    mode = (**(code **)(cur_dtype + 0x4e8))();
    node_from_double(mode,val);
    return;
  }
  node_from_double(*(ulong *)(cur_dtype + 0xc),val);
  return;
}


/* ==== io_parse_value @ 0044b380 ==== */

void __cdecl io_parse_value(char *s,void *io,ulong type)

{
  switch(*(undefined4 *)((int)io + 0x1d4)) {
  case 0:
    parse_num_bin(s,(void *)((int)io + 0x180),type);
    return;
  case 1:
  case 4:
    parse_num_dec(s,(void *)((int)io + 0x180),type);
    return;
  case 2:
    parse_num_float(s,(void *)((int)io + 0x180),type);
    return;
  case 3:
    parse_num_hex(s,(void *)((int)io + 0x180),type);
  }
  return;
}


/* ==== io_in_mem_read @ 0044b410 ==== */

int __cdecl io_in_mem_read(int space,ulong addr,ulong *value)

{
  int id;
  void *io;
  ulong uVar1;
  
  uVar1 = 0;
  id = rangemap_get((void *)(*(int *)(cur_sim + 4) + 0x10 + space * 300),addr);
  if (id != 0) {
    iolist_find_id(*(void **)(cur_sim + 0x14c),id);
    if (io != (void *)0x0) {
      if (*(int *)((int)io + 0x154) == 7) {
        if (*(int **)(dev_tab + *(int *)((int)io + 0x174) * 4) != (int *)0x0) {
          dev_mem_read(*(int *)((int)io + 0x174),
                       *(long *)(*(int *)(*(int *)(chiptype_tab +
                                                  **(int **)(dev_tab + *(int *)((int)io + 0x174) * 4
                                                            ) * 4) + 0x20) + 4 +
                                *(int *)((int)io + 0x168) * 0x2c),*(long *)((int)io + 0x16c),
                       (int)io + 0x188);
          *value = *(ulong *)((int)io + 0x188);
          return id;
        }
      }
      else {
        io_in_next(io);
      }
      uVar1 = *(ulong *)((int)io + 0x188);
    }
    *value = uVar1;
  }
  return id;
}


/* ==== io_in_next @ 0044b4f0 ==== */

void __cdecl io_in_next(void *io)

{
  void *io_00;
  int iVar1;
  void *pvVar2;
  
  io_00 = io;
  pvVar2 = *(void **)((int)io + 0x1d8);
  if (*(void **)((int)io + 0x1d8) == (void *)0x0) {
    if (*(int *)((int)io + 0x150) == 0) {
      return;
    }
    io_in_skip_loops(io);
    io_in_read_token(io_00,s__89__________004cc430);
    iVar1 = fscanf(*(void **)((int)io_00 + 0x150),s____ld_004cc428,&io);
    if (iVar1 < 1) {
      return;
    }
    pvVar2 = io;
    if ((int)io < 2) {
      return;
    }
  }
  *(int *)((int)io_00 + 0x1d8) = (int)pvVar2 + -1;
  return;
}


/* ==== io_in_read_token @ 0044b550 ==== */

void __cdecl io_in_read_token(void *io,char *fmt)

{
  char cVar1;
  code *pcVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int va0;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char local_200 [255];
  char acStack_101 [257];
  
  local_200[0] = '\0';
  iVar3 = fscanf(*(void **)((int)io + 0x150),s___t__004cc478,local_200);
  if (iVar3 < 1) {
    fscanf(*(void **)((int)io + 0x150),fmt,local_200);
  }
  else {
    help_lines_cur = &PTR_s__CR__change___U__ln_up___N__ln_d_004cbec8;
    prompt_help_cycle(-1);
    if ((*(int *)((int)io + 0x154) < 3) || (*(int *)((int)io + 0x154) == 9)) {
      sprintf(acStack_101 + 1,s_Enter__s_value_for__s__004cc448,
              (&g_radix_names)[*(int *)((int)io + 0x1d4)],(int)io + 0x100);
    }
    else {
      sprintf(acStack_101 + 1,s_Enter_pin_data_for__s__004cc460,(int)io + 0x100);
    }
    pcVar7 = acStack_101;
    uVar5 = 0xffffffff;
    do {
      pcVar7 = pcVar7 + 1;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
    } while (*pcVar7 != '\0');
    va0 = ~uVar5 - 1;
    iVar3 = help_line_edit(acStack_101 + 1,va0,va0,&DAT_004cc440);
    while (iVar3 != 0xd) {
      if (iVar3 == 0x1b) {
        *(undefined4 *)((int)io + 0x1d0) = 0;
        *(undefined4 *)((int)io + 0x1d8) = 0xffffffff;
        *(undefined4 *)(cur_sim + 0x1c) = 1;
        break;
      }
      iVar3 = help_line_edit(acStack_101 + 1,va0,va0,&DAT_004cc440);
    }
    uVar6 = 0xffffffff;
    pcVar7 = acStack_101 + ~uVar5;
    do {
      pcVar8 = pcVar7;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar7 = pcVar8 + -uVar6;
    pcVar8 = local_200;
    for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  if (local_200[0] != '\0') {
    switch(*(undefined4 *)((int)io + 0x154)) {
    case 0:
      io_parse_value(local_200,io,
                     *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + *(int *)((int)io + 0x158) * 0x2c)
                     & 0xff400003);
      return;
    case 1:
      str_tolower(local_200);
      cur_itype = *(int *)(itype_tab + *cur_dev * 4);
      pcVar2 = *(code **)(*(int *)(*(int *)(cur_itype + 8) + *(int *)((int)io + 0x158) * 4) + 8);
      if ((pcVar2 == (code *)0x0) || (iVar3 = (*pcVar2)(local_200,io), iVar3 == 0))
      goto switchD_0044b6c6_caseD_2;
      break;
    case 2:
switchD_0044b6c6_caseD_2:
      if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
        uVar4 = *(undefined4 *)(cur_dtype + 0xc);
      }
      else {
        uVar4 = (**(code **)(cur_dtype + 0x4e8))();
      }
      io_parse_value(local_200,io,CONCAT31((uint3)((uint)uVar4 >> 8) & 0x161000,1));
      return;
    case 3:
    case 4:
      str_tolower(local_200);
    case 8:
      io_pin_set_from_text
                (*(int *)((int)io + 0x15c),*(int *)((int)io + 0x160),local_200,
                 (uint)(*(int *)((int)io + 0x154) == 8));
      return;
    case 9:
      io_parse_value(local_200,io,
                     *(uint *)(*(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c +
                                                *(int *)((int)io + 0x158) * 0x48) + 0x2c) + 0x10 +
                              *(int *)((int)io + 0x15c) * 0x1c) & 0xfffc0007);
    }
  }
  return;
}


/* ==== io_pin_set_from_text @ 0044b840 ==== */

void __cdecl io_pin_set_from_text(int first,int last,char *text,int analog)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  double dVar10;
  char *local_4;
  
  iVar2 = *(int *)(cur_dtype + 0x3c);
  uVar3 = *(uint *)(cur_dtype + 8);
  iVar4 = *(int *)(cur_dev + 0x18);
  if (analog != 0) {
    dVar10 = strtod(text,&local_4);
    iVar7 = 0;
    uVar3 = *(uint *)(iVar2 + first * 0x18 + 0x10);
    while (uVar3 = uVar3 >> 1, uVar3 != 0) {
      iVar7 = iVar7 + 1;
    }
    *(float *)(iVar4 + 0x14 + (iVar7 + *(int *)(iVar2 + 0xc + first * 0x18) * 0x4a) * 4) =
         (float)dVar10;
    return;
  }
  iVar7 = ((first <= last) - 1 & 0xfffffffe) + 1;
  cVar1 = *text;
  do {
    if (cVar1 == '\0') {
      return;
    }
    text = text + 1;
    uVar8 = *(uint *)(iVar2 + 0x10 + first * 0x18);
    iVar6 = *(int *)(iVar2 + 0xc + first * 0x18);
    if (((cVar1 == '0') || (cVar1 == 'l')) || (cVar1 == 'p')) {
      puVar5 = (uint *)(iVar4 + iVar6 * 0x128);
LAB_0044b91f:
      *puVar5 = *puVar5 & ~uVar8;
    }
    else if (cVar1 == 'n') {
      puVar5 = (uint *)(iVar4 + 0x94 + iVar6 * 0x128);
      goto LAB_0044b91f;
    }
    if (cVar1 == 'p') {
      puVar5 = (uint *)(iVar4 + 0x94 + iVar6 * 0x128);
LAB_0044b952:
      *puVar5 = *puVar5 | uVar8;
    }
    else if (((cVar1 == '1') || (cVar1 == 'h')) || (cVar1 == 'n')) {
      puVar5 = (uint *)(iVar4 + iVar6 * 0x128);
      goto LAB_0044b952;
    }
    if (cVar1 == 'x') {
      uVar8 = *(uint *)(iVar4 + 4 + iVar6 * 0x128) & ~uVar8;
      puVar5 = (uint *)(iVar4 + 4 + iVar6 * 0x128);
    }
    else {
      uVar8 = *(uint *)(iVar4 + 4 + iVar6 * 0x128) | uVar8;
      puVar5 = (uint *)(iVar4 + 4 + iVar6 * 0x128);
    }
    *puVar5 = uVar8;
    if (first == last) {
      return;
    }
    iVar6 = iVar2 + first * 0x18 + 0x14;
    iVar9 = iVar7 * 0x18;
    do {
      puVar5 = (uint *)(iVar6 + iVar9);
      iVar6 = iVar6 + iVar9;
      first = first + iVar7;
    } while ((*puVar5 & uVar3) == 0);
    cVar1 = *text;
  } while( true );
}


/* ==== io_in_skip_loops @ 0044b9d0 ==== */

void __cdecl io_in_skip_loops(void *io)

{
  long *p;
  int iVar1;
  long *extraout_EAX;
  long lVar2;
  undefined1 local_5c;
  char local_5b;
  
  iVar1 = fscanf(*(void **)((int)io + 0x150),s______004cc498,&local_5c);
  do {
    if (iVar1 < 1) {
LAB_0044bab0:
      iVar1 = fscanf(*(void **)((int)io + 0x150),s______004cc490,&local_5c);
      while (0 < iVar1) {
        fscanf(*(void **)((int)io + 0x150),s________004cc488);
        iVar1 = fscanf(*(void **)((int)io + 0x150),s______004cc490,&local_5c);
      }
      iVar1 = fscanf(*(void **)((int)io + 0x150),s__1____004cc480,&local_5c);
      while (0 < iVar1) {
        dsp_alloc(0x10,0);
        if (extraout_EAX != (long *)0x0) {
          extraout_EAX[3] = *(long *)((int)io + 0x1dc);
          *(long **)((int)io + 0x1dc) = extraout_EAX;
          lVar2 = ftell(*(void **)((int)io + 0x150));
          *extraout_EAX = lVar2;
          extraout_EAX[1] = 0;
        }
        iVar1 = fscanf(*(void **)((int)io + 0x150),s__1____004cc480,&local_5c);
      }
      if (iVar1 == -1) {
        *(undefined4 *)((int)io + 0x1d8) = 0xffffffff;
        *(undefined4 *)(cur_sim + 0x1c) = 1;
      }
      return;
    }
    p = *(long **)((int)io + 0x1dc);
    if (p != (long *)0x0) {
      if ((p[1] == 0) &&
         ((p[1] = 1, local_5b == ')' ||
          (iVar1 = fscanf(*(void **)((int)io + 0x150),s____ld_004cc428,p + 2), iVar1 < 1)))) {
        p[2] = -1;
      }
      if ((p[2] == -1) || (iVar1 = p[2] + -1, p[2] = iVar1, 0 < iVar1)) {
        fseek(*(void **)((int)io + 0x150),*p,0);
        goto LAB_0044bab0;
      }
      *(long *)((int)io + 0x1dc) = p[3];
      fscanf(*(void **)((int)io + 0x150),s____ld_004cc428,p + 2);
      dsp_free(p);
    }
    iVar1 = fscanf(*(void **)((int)io + 0x150),s______004cc498,&local_5c);
  } while( true );
}


/* ==== io_in_reg_read @ 0044bb90 ==== */

int __cdecl io_in_reg_read(int reg,ulong *value)

{
  void *io;
  
  iolist_find(*(void **)(cur_sim + 0x14c),2,reg,0);
  if (io != (void *)0x0) {
    io_in_next(io);
    *value = *(ulong *)((int)io + 0x188);
    return 1;
  }
  return 0;
}


/* ==== io_in_periph_read @ 0044bbe0 ==== */

int __cdecl io_in_periph_read(int a,int b,ulong *value)

{
  void *io;
  
  iolist_find(*(void **)(cur_sim + 0x14c),9,a,b);
  if (io != (void *)0x0) {
    io_in_next(io);
    *value = *(ulong *)((int)io + 0x188);
    return 1;
  }
  return 0;
}


/* ==== io_in_pin_read @ 0044bc30 ==== */

int __cdecl io_in_pin_read(int pin,ulong *value)

{
  void *io;
  int iVar1;
  ulong *puVar2;
  
  iolist_find(*(void **)(cur_sim + 0x14c),1,pin,0);
  if (io != (void *)0x0) {
    io_in_next(io);
    puVar2 = (ulong *)((int)io + 0x180);
    for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *value = *puVar2;
      puVar2 = puVar2 + 1;
      value = value + 1;
    }
    return 1;
  }
  return 0;
}


/* ==== io_in_timed_pin_read @ 0044bc80 ==== */

int __cdecl io_in_timed_pin_read(int pin,ulong *value)

{
  void *io;
  int iVar1;
  ulong *puVar2;
  
  iolist_find(*(void **)(cur_sim + 0x150),1,pin,0);
  if (io != (void *)0x0) {
    iVar1 = io_in_timed_next(io);
    if (iVar1 != 0) {
      puVar2 = (ulong *)((int)io + 0x180);
      for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *value = *puVar2;
        puVar2 = puVar2 + 1;
        value = value + 1;
      }
      return 1;
    }
  }
  return 0;
}


/* ==== io_in_timed_next @ 0044bce0 ==== */

int __cdecl io_in_timed_next(void *io)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = *(int *)((int)io + 0x1d0);
  uVar2 = *(uint *)((int)io + 0x1d8);
  if (iVar1 != 0) {
    if (*(uint *)(cur_dev + 0x20) < uVar2) {
      return 0;
    }
    if (iVar1 != 0) goto LAB_0044bd21;
  }
  if (1 < (int)uVar2) {
    *(uint *)((int)io + 0x1d8) = uVar2 - 1;
    return 0;
  }
  if ((iVar1 == 0) && (uVar2 == 0xffffffff)) {
    return 0;
  }
LAB_0044bd21:
  if (*(int *)((int)io + 0x150) != 0) {
    iVar3 = 1;
    io_in_read_token(io,s__89_________004cc4a0);
    if (*(int *)((int)io + 0x1d8) != -1) {
      io_in_timed_advance(io);
    }
  }
  return iVar3;
}


/* ==== io_in_timed_advance @ 0044bd60 ==== */

void __cdecl io_in_timed_advance(void *io)

{
  int iVar1;
  undefined1 local_5c [92];
  
  io_in_skip_loops(io);
  iVar1 = fscanf(*(void **)((int)io + 0x150),s______004cc4b8,local_5c);
  *(uint *)((int)io + 0x1d0) = (uint)(iVar1 < 1);
  iVar1 = fscanf(*(void **)((int)io + 0x150),&DAT_004cc4b0,(undefined4 *)((int)io + 0x1d8));
  if (iVar1 == -1) {
    *(undefined4 *)((int)io + 0x1d0) = 0;
    *(undefined4 *)((int)io + 0x1d8) = 0xffffffff;
    *(undefined4 *)(cur_sim + 0x1c) = 1;
  }
  return;
}


/* ==== io_in_poll @ 0044bde0 ==== */

void io_in_poll(void)

{
  uint *puVar1;
  void *pvVar2;
  code *pcVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  
  for (pvVar2 = *(void **)(cur_sim + 0x150); pvVar2 != (void *)0x0;
      pvVar2 = *(void **)((int)pvVar2 + 0x1e0)) {
    puVar5 = (uint *)((int)pvVar2 + 0x188);
    switch(*(undefined4 *)((int)pvVar2 + 0x154)) {
    case 0:
      iVar4 = io_in_timed_next(pvVar2);
      if (iVar4 != 0) {
        (**(code **)(*(int *)(cur_dtype + 0x28) + 4))
                  (*(undefined4 *)
                    (*(int *)(cur_dtype + 0x20) + 4 + *(int *)((int)pvVar2 + 0x158) * 0x2c),
                   *(undefined4 *)((int)pvVar2 + 0x15c),puVar5);
      }
      break;
    case 1:
      puVar1 = (uint *)(*(int *)(cur_sim + 8) + *(int *)((int)pvVar2 + 0x158) * 8);
      uVar7 = *(uint *)(*(int *)(cur_sim + 8) + *(int *)((int)pvVar2 + 0x158) * 8);
      if ((uVar7 & 1) != 0) {
        if ((uVar7 & 2) == 0) {
          io_in_timed_next(pvVar2);
          iVar4 = *(int *)((int)pvVar2 + 0x158);
          pcVar3 = *(code **)(*(int *)(*(int *)(cur_itype + 8) + iVar4 * 4) + 0x10);
          if (pcVar3 == (code *)0x0) {
            uVar7 = *puVar5;
            uVar6 = *(uint *)(*(int *)(cur_dtype + 0x18) + iVar4 * 0x48 + 8);
            puVar5 = (uint *)(*(int *)(cur_dev + 0x18) +
                             *(int *)(*(int *)(cur_dtype + 0x18) + 4 + iVar4 * 0x48) * 0x128);
            goto LAB_0044bf2e;
          }
          (*pcVar3)(iVar4,(int)pvVar2 + 0x180);
        }
        else if (((uVar7 & 8) == 0) && (iVar4 = io_in_timed_next(pvVar2), iVar4 != 0)) {
          *puVar1 = *puVar1 | 0x18;
        }
      }
      break;
    case 2:
      iVar4 = *(int *)(cur_dtype + 0x44) + *(int *)((int)pvVar2 + 0x158) * 0x14;
      io_in_timed_next(pvVar2);
      uVar7 = *puVar5;
      puVar5 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(iVar4 + 4) * 0x128);
      uVar6 = *(uint *)(iVar4 + 8);
LAB_0044bf2e:
      puVar5[1] = uVar6;
      *puVar5 = uVar6 & uVar7 | ~uVar6 & *puVar5;
      break;
    case 3:
    case 4:
    case 8:
      io_in_timed_next(pvVar2);
      break;
    case 9:
      iVar4 = io_in_timed_next(pvVar2);
      if (iVar4 != 0) {
        (**(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c +
                             *(int *)((int)pvVar2 + 0x158) * 0x48) + 4))
                  (*(int *)((int)pvVar2 + 0x158),*(undefined4 *)((int)pvVar2 + 0x15c),puVar5);
      }
    }
  }
  pvVar2 = *(void **)(cur_sim + 0x14c);
  do {
    if (pvVar2 == (void *)0x0) {
      return;
    }
    switch(*(undefined4 *)((int)pvVar2 + 0x154)) {
    case 1:
      uVar7 = *(uint *)(*(int *)(cur_sim + 8) + *(int *)((int)pvVar2 + 0x158) * 8);
      if (((uVar7 & 1) != 0) && ((uVar7 & 0x20) == 0)) {
        io_in_next(pvVar2);
        iVar4 = *(int *)((int)pvVar2 + 0x158);
        pcVar3 = *(code **)(*(int *)(*(int *)(cur_itype + 8) + iVar4 * 4) + 0x10);
        if (pcVar3 == (code *)0x0) {
          uVar7 = *(uint *)((int)pvVar2 + 0x188);
          iVar4 = *(int *)(cur_dtype + 0x18) + iVar4 * 0x48;
          uVar6 = *(uint *)(iVar4 + 8);
          puVar5 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(iVar4 + 4) * 0x128);
          goto LAB_0044c07b;
        }
        (*pcVar3)(iVar4,(int)pvVar2 + 0x180);
      }
      break;
    case 2:
      iVar4 = *(int *)(cur_dtype + 0x44) + *(int *)((int)pvVar2 + 0x158) * 0x14;
      io_in_next(pvVar2);
      uVar7 = *(uint *)((int)pvVar2 + 0x188);
      puVar5 = (uint *)(*(int *)(cur_dev + 0x18) + *(int *)(iVar4 + 4) * 0x128);
      uVar6 = *(uint *)(iVar4 + 8);
LAB_0044c07b:
      puVar5[1] = uVar6;
      *puVar5 = uVar6 & uVar7 | ~uVar6 & *puVar5;
      break;
    case 3:
    case 4:
    case 8:
      io_in_next(pvVar2);
      break;
    case 5:
      io_pin_copy(*(int *)((int)pvVar2 + 0x174),*(int *)((int)pvVar2 + 0x16c),
                  *(int *)((int)pvVar2 + 0x15c),(uint)(*(int *)((int)pvVar2 + 0x1d4) == 2));
      break;
    case 0xb:
      io_pin_copy_tri(*(int *)((int)pvVar2 + 0x174),*(int *)((int)pvVar2 + 0x16c),
                      *(int *)((int)pvVar2 + 0x15c));
    }
    pvVar2 = *(void **)((int)pvVar2 + 0x1e0);
  } while( true );
}


/* ==== io_pin_copy @ 0044c150 ==== */

void __cdecl io_pin_copy(int dev,int src,int dst,int analog)

{
  uint *puVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  uVar2 = 0;
  piVar3 = *(int **)(dev_tab + dev * 4);
  uVar9 = 0;
  uVar8 = 0;
  if (piVar3 == (int *)0x0) {
    return;
  }
  iVar4 = piVar3[6];
  iVar6 = *(int *)(*(int *)(chiptype_tab + *piVar3 * 4) + 0x3c) + src * 0x18;
  iVar7 = *(int *)(iVar6 + 0xc);
  uVar5 = *(uint *)(iVar6 + 0x10);
  if (analog == 0) {
    uVar8 = *(uint *)(iVar4 + 8 + iVar7 * 0x128) & uVar5;
    uVar9 = *(uint *)(iVar4 + 0xc + iVar7 * 0x128) & uVar5;
  }
  else {
    iVar6 = 0;
    while (uVar5 = uVar5 >> 1, uVar5 != 0) {
      iVar6 = iVar6 + 1;
    }
    uVar2 = *(undefined4 *)(iVar4 + 0x14 + (iVar6 + iVar7 * 0x4a) * 4);
  }
  iVar6 = *(int *)(cur_dev + 0x18);
  iVar4 = *(int *)(*(int *)(cur_dtype + 0x3c) + 0xc + dst * 0x18);
  uVar5 = *(uint *)(*(int *)(cur_dtype + 0x3c) + dst * 0x18 + 0x10);
  if (analog != 0) {
    iVar7 = 0;
    while (uVar5 = uVar5 >> 1, uVar5 != 0) {
      iVar7 = iVar7 + 1;
    }
    *(undefined4 *)(iVar6 + 0x14 + (iVar7 + iVar4 * 0x4a) * 4) = uVar2;
    return;
  }
  if (uVar9 == 0) {
    *(uint *)(iVar6 + 4 + iVar4 * 0x128) = *(uint *)(iVar6 + 4 + iVar4 * 0x128) & ~uVar5;
    return;
  }
  if (uVar8 == 0) {
    puVar1 = (uint *)(iVar6 + iVar4 * 0x128);
    *puVar1 = *puVar1 & ~uVar5;
    puVar1[1] = puVar1[1] | uVar5;
    return;
  }
  puVar1 = (uint *)(iVar6 + iVar4 * 0x128);
  *puVar1 = *(uint *)(iVar6 + iVar4 * 0x128) | uVar5;
  puVar1[1] = puVar1[1] | uVar5;
  return;
}


/* ==== io_pin_copy_tri @ 0044c280 ==== */

void __cdecl io_pin_copy_tri(int dev,int src,int dst)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  piVar4 = *(int **)(dev_tab + dev * 4);
  if (piVar4 == (int *)0x0) {
    return;
  }
  uVar5 = *(uint *)(*(int *)(*(int *)(chiptype_tab + *piVar4 * 4) + 0x3c) + 0x10 + src * 0x18);
  iVar1 = piVar4[6] +
          *(int *)(*(int *)(*(int *)(chiptype_tab + *piVar4 * 4) + 0x3c) + src * 0x18 + 0xc) * 0x128
  ;
  iVar2 = *(int *)(cur_dtype + 0x3c) + dst * 0x18;
  iVar6 = *(int *)(iVar2 + 0xc);
  uVar7 = *(uint *)(iVar2 + 0x10);
  puVar3 = (uint *)(*(int *)(cur_dev + 0x18) + iVar6 * 0x128);
  if ((*(uint *)(iVar1 + 0xc) & uVar5) != 0) {
    if (((puVar3[3] & uVar7) != 0) &&
       ((*(uint *)(*(int *)(cur_dev + 0x18) + 8 + iVar6 * 0x128) & uVar7) == 0)) goto LAB_0044c328;
    if ((*(uint *)(iVar1 + 8) & uVar5) == 0) {
      *puVar3 = *puVar3 & ~uVar7;
      puVar3[1] = puVar3[1] | uVar7;
      return;
    }
  }
  *puVar3 = *puVar3 | uVar7;
LAB_0044c328:
  puVar3[1] = puVar3[1] | uVar7;
  return;
}


/* ==== cmd_input_open @ 0044c340 ==== */

void cmd_input_open(void)

{
  uint *puVar1;
  int iVar2;
  char cVar3;
  ushort uVar4;
  ushort uVar5;
  ulong lo;
  ulong hi;
  undefined4 uVar6;
  bool bVar7;
  char *out;
  int iVar8;
  int extraout_EAX;
  uint uVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  char *pcVar13;
  char *pcVar14;
  undefined4 *local_114;
  int local_108;
  int local_104;
  char local_100 [256];
  
  dsp_alloc(0x1e8,1);
  if (out == (char *)0x0) {
    return;
  }
  if (DAT_004a93ea == '#') {
    local_108 = g_io_id_arg;
    io_lists_reset();
    iVar8 = 3;
    local_104 = 3;
  }
  else {
    local_104 = 2;
    local_108 = 0;
    iVar8 = 2;
  }
  pcVar13 = &g_tok_type + iVar8;
  if (*pcVar13 != 'j') {
    local_114 = (undefined4 *)(cur_sim + 0x14c);
  }
  else {
    local_114 = (undefined4 *)(cur_sim + 0x150);
    iVar8 = iVar8 + 1;
  }
  bVar7 = *pcVar13 == 'j';
  iVar2 = iVar8 * 0x28;
  uVar9 = 0xffffffff;
  pcVar13 = &g_cmdline + (&g_tok_start)[iVar8];
  do {
    pcVar14 = pcVar13;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar14 = pcVar13 + 1;
    cVar3 = *pcVar13;
    pcVar13 = pcVar14;
  } while (cVar3 != '\0');
  uVar9 = ~uVar9;
  pcVar13 = pcVar14 + -uVar9;
  pcVar14 = out + 0x100;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
    pcVar13 = pcVar13 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar14 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    pcVar14 = pcVar14 + 1;
  }
  iolist_remove(local_114,out + 0x100,0);
  if (local_108 == 0) {
    local_108 = io_alloc_id();
  }
  *(int *)(out + 0x1e4) = local_108;
  *(undefined4 *)(out + 0x1e0) = *local_114;
  puVar12 = &g_null_value;
  pcVar13 = out + 0x180;
  for (iVar11 = 10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *(undefined4 *)pcVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    pcVar13 = pcVar13 + 4;
  }
  puVar12 = &g_null_value;
  pcVar13 = out + 0x1a8;
  for (iVar11 = 10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *(undefined4 *)pcVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    pcVar13 = pcVar13 + 4;
  }
  out[0x1d4] = '\x03';
  out[0x1d5] = '\0';
  out[0x1d6] = '\0';
  out[0x1d7] = '\0';
  *(int *)(cur_sim + 0x44) = *(int *)(cur_sim + 0x44) + 1;
  *(undefined4 *)(out + 0x164) = *(undefined4 *)(cur_sim + 0x44);
  if ((&DAT_004a93ea)[iVar8] == 'r') {
    *(undefined4 *)(out + 0x1d4) = (&DAT_004a96c0)[iVar8 * 10];
  }
  if ((&DAT_004a93e9)[iVar8] == 's') {
    uVar9 = 0xffffffff;
    pcVar13 = &cmd_tokbuf + (&DAT_004a946c)[iVar8];
    do {
      pcVar14 = pcVar13;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      pcVar14 = pcVar13 + 1;
      cVar3 = *pcVar13;
      pcVar13 = pcVar14;
    } while (cVar3 != '\0');
    uVar9 = ~uVar9;
    pcVar13 = pcVar14 + -uVar9;
    pcVar14 = out;
    for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar14 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar14 = pcVar14 + 1;
    }
    if ((&DAT_004a93ea)[iVar8] == 'u') {
      out[0x154] = '\v';
      out[0x155] = '\0';
      out[0x156] = '\0';
      out[0x157] = '\0';
    }
    else {
      out[0x154] = '\x05';
      out[0x155] = '\0';
      out[0x156] = '\0';
      out[0x157] = '\0';
    }
    *(undefined4 *)(out + 0x15c) = *(undefined4 *)(&g_tok_val + iVar2);
    *(uint *)(out + 0x174) = (uint)*(ushort *)(iVar2 + 0x4a96b6);
    *(int *)(out + 0x16c) = (&DAT_004a9698)[iVar8 * 10];
    *local_114 = out;
    goto switchD_0044c6a8_caseD_51;
  }
  if ((&DAT_004a93e9)[iVar8] == 'p') {
    uVar9 = 0xffffffff;
    pcVar13 = &g_cmdline + (&DAT_004a946c)[iVar8];
    do {
      pcVar14 = pcVar13;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      pcVar14 = pcVar13 + 1;
      cVar3 = *pcVar13;
      pcVar13 = pcVar14;
    } while (cVar3 != '\0');
    uVar9 = ~uVar9;
    pcVar13 = pcVar14 + -uVar9;
    pcVar14 = out;
    for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar14 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar14 = pcVar14 + 1;
    }
    out[0x154] = '\a';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(uint *)(out + 0x158) = (uint)*(ushort *)(&DAT_004a968c + iVar2);
    *(undefined4 *)(out + 0x15c) = *(undefined4 *)(&g_tok_val + iVar2);
    *(uint *)(out + 0x174) = (uint)*(ushort *)(iVar2 + 0x4a96b6);
    *(int *)(out + 0x16c) = (&DAT_004a9698)[iVar8 * 10];
    *(uint *)(out + 0x168) = (uint)*(ushort *)(iVar2 + 0x4a96b4);
    *local_114 = out;
    memtag_add(2,*(int *)(out + 0x158),*(ulong *)(out + 0x15c),*(ulong *)(out + 0x15c),
               *(int *)(out + 0x164));
    goto switchD_0044c6a8_caseD_51;
  }
  uVar9 = 0xffffffff;
  if (DAT_004a9698 == -1) {
    pcVar13 = &g_cmdline + (&DAT_004a946c)[iVar8];
    do {
      pcVar14 = pcVar13;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      pcVar14 = pcVar13 + 1;
      cVar3 = *pcVar13;
      pcVar13 = pcVar14;
    } while (cVar3 != '\0');
    uVar9 = ~uVar9;
    pcVar13 = pcVar14 + -uVar9;
    pcVar14 = out;
    for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar14 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar14 = pcVar14 + 1;
    }
  }
  else {
    pcVar13 = &g_cmdline + (&DAT_004a946c)[iVar8];
    do {
      pcVar14 = pcVar13;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      pcVar14 = pcVar13 + 1;
      cVar3 = *pcVar13;
      pcVar13 = pcVar14;
    } while (cVar3 != '\0');
    uVar9 = ~uVar9;
    pcVar13 = pcVar14 + -uVar9;
    pcVar14 = local_100;
    for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar14 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar14 = pcVar14 + 1;
    }
    path_search(local_100,*(char **)((iVar8 - local_104) * 4 + 0x4cbee8),out);
  }
  fopen(out,&DAT_004c5ff4);
  *(int *)(out + 0x150) = extraout_EAX;
  if (extraout_EAX == 0) {
    sprintf(local_100,s__Error_opening__s__004c5c7c,out);
    out_text(local_100,1);
    dsp_free(out);
    return;
  }
  *local_114 = out;
  switch((&g_tok_type)[iVar8]) {
  case 0x50:
  case 0x58:
    out[0x154] = '\0';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(uint *)(out + 0x158) = (uint)*(ushort *)(&DAT_004a968c + iVar2);
    lo = *(ulong *)(&g_tok_val + iVar2);
    *(ulong *)(out + 0x15c) = lo;
    hi = *(ulong *)(&DAT_004a9674 + iVar2);
    *(ulong *)(out + 0x160) = hi;
    if (!bVar7) {
      memtag_add(2,*(int *)(out + 0x158),lo,hi,*(int *)(out + 0x164));
      break;
    }
    goto LAB_0044c82e;
  case 0x53:
    out[0x154] = '\x04';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(undefined4 *)(out + 0x15c) = *(undefined4 *)(&g_tok_val + iVar2);
    *(undefined4 *)(out + 0x160) = *(undefined4 *)(&DAT_004a9674 + iVar2);
    break;
  case 0x55:
    out[0x154] = '\x02';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(undefined4 *)(out + 0x158) = *(undefined4 *)(&g_tok_val + iVar2);
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    break;
  case 0x67:
    out[0x154] = '\t';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    uVar4 = *(ushort *)(&DAT_004a968c + iVar2);
    uVar5 = *(ushort *)(iVar2 + 0x4a9688);
    *(uint *)(out + 0x158) = (uint)uVar4;
    *(uint *)(out + 0x15c) = (uint)uVar5;
    uVar9 = (-(uint)bVar7 & 0x3c00000) + 0x400000;
    *(uint *)(out + 0x160) = uVar9;
    puVar1 = (uint *)(*(int *)(*(int *)(cur_sim + 8) + 4 + (uint)uVar4 * 8) + (uint)uVar5 * 4);
    *puVar1 = *puVar1 | uVar9;
    break;
  case 0x70:
    out[0x154] = '\0';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    *(uint *)(out + 0x158) = (uint)*(ushort *)(&DAT_004a968c + iVar2);
    *(undefined4 *)(out + 0x15c) = *(undefined4 *)(&g_tok_val + iVar2);
    *(undefined4 *)(out + 0x160) = *(undefined4 *)(&g_tok_val + iVar2);
    if (bVar7) goto LAB_0044c82e;
    memtag_add(2,*(int *)(out + 0x158),*(ulong *)(out + 0x15c),*(ulong *)(out + 0x15c),
               *(int *)(out + 0x164));
    break;
  case 0x73:
    *(uint *)(out + 0x154) = (-(uint)(*(int *)(out + 0x1d4) != 2) & 0xfffffffb) + 8;
    uVar6 = *(undefined4 *)(&g_tok_val + iVar2);
    *(undefined4 *)(out + 0x15c) = uVar6;
    *(undefined4 *)(out + 0x160) = uVar6;
    break;
  case 0x74:
    out[0x154] = '\x01';
    out[0x155] = '\0';
    out[0x156] = '\0';
    out[0x157] = '\0';
    uVar4 = *(ushort *)(&DAT_004a968c + iVar2);
    out[0x15c] = '\0';
    out[0x15d] = '\0';
    out[0x15e] = '\0';
    out[0x15f] = '\0';
    *(uint *)(out + 0x158) = (uint)uVar4;
  }
switchD_0044c6a8_caseD_51:
  if (bVar7) {
LAB_0044c82e:
    io_in_timed_advance(out);
  }
  return;
}


/* ==== io_alloc_id @ 0044c890 ==== */

int io_alloc_id(void)

{
  int iVar1;
  int id;
  
  id = 1;
  do {
    iVar1 = io_next_free_id(id,(void **)(cur_sim + 0x14c));
    if (iVar1 != id) {
      iVar1 = io_next_free_id(id,(void **)(cur_sim + 0x150));
      if (iVar1 != id) {
        return id;
      }
    }
    id = id + 1;
  } while( true );
}


/* ==== cmd_input_h3 @ 0044c8d0 ==== */

void cmd_input_h3(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined uVar2;
  undefined3 extraout_var;
  void *stream;
  int iVar3;
  char *extraout_EAX;
  int iVar4;
  char *extraout_EAX_00;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  int iStack_210;
  char *pcStack_20c;
  char *pcStack_208;
  int iStack_200;
  char acStack_1f8 [248];
  undefined1 auStack_100 [8];
  char acStack_f8 [248];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  uVar2 = cmd_input_h3_sub_44cbd0
                    (auStack_100,
                     (&PTR_s_termXXXX_io_004cbef0)[(&DAT_004a93ea)[DAT_004a93ea == '#'] == 'j']);
  if (CONCAT31(extraout_var,uVar2) == 0) {
    return;
  }
  log_echo(acStack_f8,1);
  fopen(acStack_f8,&DAT_004c6b48);
  if (stream == (void *)0x0) {
    return;
  }
  help_lines_cur = 0x4cbec0;
  prompt_help_cycle(-1);
  sprintf(acStack_1f8,PTR_s__03d_Data__004cbef8,0);
  iVar3 = str_find_char(acStack_1f8,0x3a);
  iVar3 = iVar3 + 1;
  dsp_alloc(0x108,1);
  pcVar7 = extraout_EAX;
  pcStack_20c = extraout_EAX;
  pcStack_208 = extraout_EAX;
  if (extraout_EAX == (char *)0x0) {
    fclose(stream);
    return;
  }
  do {
    iVar4 = help_line_edit(acStack_1f8);
    switch(iVar4) {
    case 0xd:
    case 0xe:
    case 0x15:
      uVar5 = 0xffffffff;
      pcVar8 = acStack_1f8 + iVar3;
      do {
        pcVar9 = pcVar8;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar8 = pcVar9 + -uVar5;
      pcVar9 = pcVar7;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      if (iVar4 == 0x15) {
        pcVar7 = *(char **)(pcVar7 + 0x100);
        iStack_210 = iStack_210 + -1;
      }
      else {
        pcVar7 = *(char **)(pcVar7 + 0x104);
        iStack_210 = iStack_210 + 1;
      }
      if (pcVar7 == (char *)0x0) {
        dsp_alloc(0x108,1);
        if (extraout_EAX_00 == (char *)0x0) {
          fclose(stream);
          return;
        }
        if (iVar4 == 0x15) {
          extraout_EAX_00[0x100] = '\0';
          extraout_EAX_00[0x101] = '\0';
          extraout_EAX_00[0x102] = '\0';
          extraout_EAX_00[0x103] = '\0';
          *(char **)(extraout_EAX_00 + 0x104) = pcStack_20c;
          iStack_210 = 0;
          *(char **)(pcStack_20c + 0x100) = extraout_EAX_00;
          pcStack_208 = extraout_EAX_00;
        }
        else {
          extraout_EAX_00[0x104] = '\0';
          extraout_EAX_00[0x105] = '\0';
          extraout_EAX_00[0x106] = '\0';
          extraout_EAX_00[0x107] = '\0';
          *(char **)(extraout_EAX_00 + 0x100) = pcStack_20c;
          *(char **)(pcStack_20c + 0x104) = extraout_EAX_00;
        }
        *extraout_EAX_00 = '\0';
        pcVar7 = extraout_EAX_00;
      }
      log_echo(acStack_1f8,1);
      sprintf(acStack_1f8,PTR_s__03d_Data__004cbef8,iStack_210);
      iVar4 = str_find_char(acStack_1f8,0x3a);
      uVar5 = 0xffffffff;
      iVar3 = iVar4 + 1;
      pcVar8 = pcVar7;
      do {
        pcVar9 = pcVar8;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar8 + 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar8 = pcVar9 + -uVar5;
      pcVar9 = acStack_1f8 + iVar4 + 1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; pcStack_20c = pcVar7, uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      break;
    case 0x1b:
      goto switchD_0044c9f6_caseD_1b;
    }
  } while( true );
switchD_0044c9f6_caseD_1b:
  while (pcStack_208 != (char *)0x0) {
    pcVar7 = *(char **)(pcStack_208 + 0x104);
    fprintf(stream,&DAT_004c5990,pcStack_208);
    dsp_free(pcStack_208);
    pcStack_208 = pcVar7;
  }
  fclose(stream);
  uVar5 = 0xffffffff;
  DAT_004a9698 = 0xffffffff;
  pcVar7 = acStack_f8;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = &g_cmdline + (&DAT_004a9474)[iStack_200];
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  cmd_input_open(param_3);
  return;
}


/* ==== cmd_input_h3_sub_44cbd0 @ 0044cbd0 ==== */

undefined4 cmd_input_h3_sub_44cbd0(char *param_1,char *param_2)

{
  char cVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  int va0;
  char acStack_1c [12];
  char acStack_10 [16];
  
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar6 = acStack_10;
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
  cVar1 = strchr(acStack_10,0x58);
  va0 = 0;
  while( true ) {
    sprintf(acStack_1c,(char *)0x4cc4c0,va0);
    strncpy((char *)CONCAT31(extraout_var,cVar1),acStack_1c,4);
    path_combine((char *)(cur_dev + 0x58),acStack_10,&empty_str,param_1);
    iVar2 = _access(param_1,0);
    if ((iVar2 != 0) && (errno == 2)) break;
    va0 = va0 + 1;
  }
  return 1;
}


/* ==== cmd_input_parse @ 0044cc80 ==== */

undefined ** cmd_input_parse(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(cur_dev + 4);
  iVar5 = -1;
  iVar2 = parm_check_too_many(2);
  if (iVar2 != 0) {
    iVar5 = 0;
    goto LAB_0044ce8e;
  }
  iVar2 = parm_break_number(2);
  uVar1 = (uint)(iVar2 != 0);
  iVar2 = uVar1 + 2;
  iVar3 = parm_keyword1(iVar2,&DAT_004c6aec);
  if (iVar3 != 0) {
    iVar4 = parm_check_too_many(uVar1 + 3);
    if (iVar4 != 0) {
      iVar5 = 1;
    }
    goto LAB_0044ce8e;
  }
  iVar3 = parm_match_space_cur(iVar2);
  if ((iVar3 == 0) || (iVar3 = parm_match_space_any(uVar1 + 3), iVar3 == 0)) {
    iVar3 = parm_keyword1(iVar2,&DAT_004c16b8);
    if (iVar3 != 0) {
      iVar4 = parm_mem_or_reg_x(uVar1 + 3);
      if (iVar4 == 0) goto LAB_0044ce8e;
      iVar4 = parm_kw_r2_radix_opt(uVar1 + 5);
      if (((iVar4 == 0) || (iVar4 = parm_check_too_many(uVar1 + 6), iVar4 == 0)) &&
         (iVar4 = parm_check_too_many(uVar1 + 5), iVar4 == 0)) goto LAB_0044ce8e;
      iVar2 = uVar1 + 4;
      iVar4 = parm_keyword1(iVar2,&DAT_004c6aec);
      if (iVar4 != 0) {
        iVar5 = 1;
        goto LAB_0044ce8e;
      }
      iVar4 = parm_keyword1(iVar2,&DAT_004cb138);
      if (iVar4 != 0) {
        iVar5 = 3;
        goto LAB_0044ce8e;
      }
      iVar4 = parm_any_token(iVar2);
      goto joined_r0x0044ce87;
    }
    iVar4 = parm_port_name(iVar2,iVar4);
    if ((iVar4 == 0) && (iVar2 = parm_mem_or_reg_x(iVar2), iVar2 == 0)) goto LAB_0044ce8e;
    iVar2 = uVar1 + 4;
    iVar3 = parm_kw_r2_radix_opt(iVar2);
    if (((iVar3 == 0) || (iVar3 = parm_check_too_many(uVar1 + 5), iVar3 == 0)) &&
       (((iVar3 = parm_kw_pullup(iVar2), iVar3 == 0 ||
         (iVar3 = parm_check_too_many(uVar1 + 5), iVar3 == 0)) &&
        (iVar2 = parm_check_too_many(iVar2), iVar2 == 0)))) goto LAB_0044ce8e;
    iVar3 = uVar1 + 3;
    iVar2 = parm_keyword1(iVar3,&DAT_004c6aec);
    if (iVar2 != 0) {
      iVar5 = 1;
      goto LAB_0044ce8e;
    }
    if ((iVar4 == 0) || (iVar4 = parm_port_name_dev(iVar3), iVar4 == 0)) {
      iVar4 = parm_keyword1(iVar3,&DAT_004cb138);
      if (iVar4 != 0) {
        iVar5 = 3;
        goto LAB_0044ce8e;
      }
      iVar4 = parm_any_token(iVar3);
      goto joined_r0x0044ce87;
    }
  }
  else {
    iVar4 = parm_check_too_many(uVar1 + 4);
joined_r0x0044ce87:
    if (iVar4 == 0) goto LAB_0044ce8e;
  }
  iVar5 = 2;
LAB_0044ce8e:
  if (iVar5 == -1) {
    return (undefined **)0x0;
  }
  return &PTR_cmd_input_h0_004cbf00 + iVar5 * 2;
}


/* ==== cmd_history_h0 @ 0044ceb0 ==== */

void cmd_history_h0(void)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  undefined4 *puVar11;
  long lStack_21c;
  int iStack_218;
  uint uStack_214;
  undefined4 uStack_210;
  int iStack_20c;
  int *piStack_208;
  undefined4 uStack_204;
  char acStack_200 [256];
  undefined1 auStack_100 [256];
  
  iVar9 = cur_sim;
  uStack_210 = 0;
  piVar10 = (int *)(cur_sim + 0x3fc0);
  piStack_208 = piVar10;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar3 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar3 = (**(code **)(cur_dtype + 0x4e8))();
  }
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2924,&iStack_218,&lStack_21c);
  periph_call(*(int *)(cur_dev + 4),iStack_218,lStack_21c,(long)&uStack_204);
  lVar4 = periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2950,&iStack_218,&lStack_21c);
  if (lVar4 != 0) {
    periph_call(*(int *)(cur_dev + 4),iStack_218,lStack_21c,(long)&uStack_210);
  }
  iStack_20c = *piVar10;
  if (history_size < *piVar10) {
    iStack_20c = history_size;
  }
  iVar9 = *(int *)(iVar9 + 0x3fc4) - iStack_20c;
  if (iVar9 < 0) {
    iVar9 = iVar9 + history_size;
  }
  if (0 < iStack_20c) {
    uStack_214 = uVar3 & 0x10000000;
    do {
      iVar9 = iVar9 + 1;
      if (history_size <= iVar9) {
        iVar9 = 0;
      }
      iVar1 = piVar10[2] + iVar9 * 0x2c;
      if (uStack_214 == 0) {
LAB_0044cff8:
        if ((uVar3 & 0x2000000) == 0) {
          pcVar5 = s_P___06lx__06lx_004cb24c;
          if ((uVar3 & 0x200) == 0) goto LAB_0044d014;
        }
        else {
          pcVar5 = s_P___08lx__08lx_004cb23c;
        }
      }
      else if ((uVar3 & 0x4000000) == 0) {
        if (uStack_214 == 0) goto LAB_0044cff8;
        pcVar5 = s_P___04lx__04lx_004cb25c;
      }
      else {
LAB_0044d014:
        pcVar5 = s_P___04lx__06lx_004cb22c;
      }
      sprintf(acStack_200,pcVar5,*(undefined4 *)(piVar10[2] + iVar9 * 0x2c),
              *(undefined4 *)(iVar1 + 4));
      uVar7 = 0xffffffff;
      pcVar5 = acStack_200;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      iVar8 = ~uVar7 - 1;
      iVar6 = (**(code **)(cur_itype + 0x10))(iVar1 + 4,auStack_100,uStack_204,uStack_210,0);
      if (1 < iVar6) {
        puVar11 = (undefined4 *)(iVar1 + 8);
        iVar6 = iVar6 + -1;
        do {
          if ((uStack_214 == 0) || ((uVar3 & 0x4000000) == 0)) {
            if (uStack_214 == 0) {
              if (((uVar3 & 0x200) != 0) || (pcVar5 = s__08lx_004cb21c, (uVar3 & 0x2000000) == 0))
              goto LAB_0044d09b;
            }
            else {
              pcVar5 = s__04lx_004cb224;
            }
          }
          else {
LAB_0044d09b:
            pcVar5 = s__06lx_004cb214;
          }
          sprintf(acStack_200 + iVar8,pcVar5,*puVar11);
          uVar7 = 0xffffffff;
          pcVar5 = acStack_200;
          do {
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            cVar2 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar2 != '\0');
          iVar8 = ~uVar7 - 1;
          puVar11 = puVar11 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      sprintf(acStack_200 + iVar8,&DAT_004cb20c,auStack_100);
      out_text(acStack_200,1);
      uVar7 = 0xffffffff;
      pcVar5 = acStack_200;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      if (screen_cols - 1U < ~uVar7 - 1) {
        out_text(acStack_200 + screen_cols,1);
      }
      iStack_20c = iStack_20c + -1;
      piVar10 = piStack_208;
    } while (iStack_20c != 0);
  }
  return;
}


