/* ==== snap_reloc_add @ 0043e080 ==== */

void __cdecl snap_reloc_add(ulong *slot,int kind)

{
  ulong uVar1;
  int iVar2;
  int extraout_EAX;
  int *item;
  ulong *puVar3;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  if ((slot != (ulong *)0x0) && (*slot != 0)) {
    iVar2 = snap_find_block(*slot,&local_8);
    if (iVar2 == 1) {
      iVar2 = snap_find_block((ulong)slot,&local_10);
      if (iVar2 == 0) {
        local_c = (int)slot - prof_ctx;
        local_10 = -1;
      }
      avl_find(snap_reloc_list,&local_10,1);
      if (extraout_EAX != 0) {
        return;
      }
      prof_malloc(0x10);
      *item = local_10;
      item[1] = local_c;
      item[2] = local_8;
      item[3] = local_4;
      avl_insert(snap_reloc_list,item,0);
    }
    switch(kind) {
    case 1:
      uVar1 = *slot;
      DAT_00502060 = 4;
      snap_reloc_add((ulong *)(uVar1 + 8),2);
      DAT_00502060 = 6;
      snap_reloc_add((ulong *)(uVar1 + 0xc),2);
      DAT_00502060 = 0;
      snap_reloc_add((ulong *)(uVar1 + 4),2);
      snap_reloc_add((ulong *)(uVar1 + 0x58),0);
      snap_reloc_add((ulong *)(uVar1 + 0x5c),0);
      snap_reloc_add((ulong *)(uVar1 + 0x60),0);
      snap_reloc_add((ulong *)(uVar1 + 0x68),0);
      snap_reloc_add((ulong *)(uVar1 + 0x3510),0);
      iVar2 = 0;
      if (0 < *(int *)(uVar1 + 0x3508)) {
        do {
          snap_reloc_add((ulong *)(*(ulong *)(uVar1 + 0x3510) + iVar2 * 4),0);
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(uVar1 + 0x3508));
      }
      snap_reloc_add((ulong *)(uVar1 + 0x350c),0);
      iVar2 = 0;
      if (0 < *(int *)(uVar1 + 0x3508)) {
        do {
          snap_reloc_add((ulong *)(*(ulong *)(uVar1 + 0x350c) + iVar2 * 4),0);
          iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(uVar1 + 0x3508));
      }
      DAT_00502060 = 7;
      snap_reloc_add((ulong *)(uVar1 + 0x3514),2);
      snap_reloc_add((ulong *)(uVar1 + 0x3518),0);
      snap_reloc_add((ulong *)(uVar1 + 0x3798),0);
      snap_reloc_add((ulong *)(uVar1 + 0x379c),0);
      snap_reloc_add((ulong *)(uVar1 + 0x378c),0);
      iVar2 = 0;
      if (-1 < *(int *)(uVar1 + 0x3788)) {
        puVar3 = (ulong *)(uVar1 + 0x352c);
        do {
          snap_reloc_add(puVar3 + -3,0);
          snap_reloc_add(puVar3,0);
          snap_reloc_add(puVar3 + 1,0);
          snap_reloc_add(puVar3 + 2,0);
          iVar2 = iVar2 + 1;
          puVar3 = puVar3 + 7;
        } while (iVar2 <= *(int *)(uVar1 + 0x3788));
        return;
      }
      break;
    case 2:
      snap_reloc_add((ulong *)*slot,3);
      return;
    case 3:
      uVar1 = *slot;
      snap_reloc_add((ulong *)(uVar1 + 4),3);
      snap_reloc_add((ulong *)(uVar1 + 0xc),3);
      snap_reloc_add((ulong *)(uVar1 + 8),DAT_00502060);
      return;
    case 4:
      uVar1 = *slot;
      snap_reloc_add((ulong *)(uVar1 + 0xa0),0);
      snap_reloc_add((ulong *)(uVar1 + 0xa4),0);
      snap_reloc_add((ulong *)(uVar1 + 0x9c),0);
      snap_reloc_add((ulong *)(uVar1 + 0x94),0);
      snap_reloc_add((ulong *)(uVar1 + 0x98),0);
      return;
    case 6:
      puVar3 = (ulong *)*slot;
      snap_reloc_add(puVar3,0);
      if (puVar3[3] == 4) {
        snap_reloc_add(puVar3 + 4,0);
        return;
      }
      if (puVar3[3] == 3) {
        snap_reloc_add(puVar3 + 7,0);
        return;
      }
      break;
    case 7:
      uVar1 = *slot;
      snap_reloc_add((ulong *)(uVar1 + 4),0);
      DAT_00502060 = 0;
      snap_reloc_add((ulong *)(uVar1 + 8),2);
      snap_reloc_add((ulong *)(uVar1 + 0xc),2);
      DAT_00502060 = 10;
      snap_reloc_add((ulong *)(uVar1 + 0x10),2);
      DAT_00502060 = 0xb;
      snap_reloc_add((ulong *)(uVar1 + 0x14),2);
      DAT_00502060 = 7;
      return;
    case 10:
    case 0xb:
      snap_reloc_add((ulong *)*slot,0);
    }
  }
  return;
}


/* ==== snap_find_block @ 0043e4a0 ==== */

int __cdecl snap_find_block(ulong addr,int *out_block_off)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = *(int *)(prof_ctx + 0x34e8);
  if (*(int *)(prof_ctx + 0x34fc) < 1) {
    return 0;
  }
  while ((addr < *(uint *)(iVar1 + 8) || (*(uint *)(iVar1 + 0xc) <= addr))) {
    iVar1 = *(int *)(iVar1 + 0x10);
    iVar2 = iVar2 + 1;
    if (*(int *)(prof_ctx + 0x34fc) <= iVar2) {
      return 0;
    }
  }
  *out_block_off = iVar2;
  out_block_off[1] = addr - *(int *)(iVar1 + 8);
  return 1;
}


/* ==== snap_restore @ 0043e4f0 ==== */

void __cdecl snap_restore(char *filename,int unused,int reopen)

{
  undefined4 *puVar1;
  ulong uVar2;
  ulong uVar3;
  int *piVar4;
  int iVar5;
  void *extraout_EAX;
  void *p;
  ulong *buf;
  void *buf_00;
  void *buf_01;
  int iVar6;
  ulong local_8;
  
  iVar6 = 0;
  if (filename == (char *)0x0) {
    if (snap_file != (void *)0x0) {
      fclose(snap_file);
      return;
    }
  }
  else {
    piVar4 = (int *)(cur_sim + 0x188);
    prof_ctx = cur_sim + 0x490;
    iVar5 = _setjmp3(&prof_jmpbuf,0);
    if ((iVar5 == 0) && (snap_error != 1)) {
      if (reopen == 0) {
        snap_error = 0;
        snap_file = (void *)0x0;
        prof_fopen(filename,&DAT_004c5ff4,(char *)0x0,1);
        snap_file = extraout_EAX;
      }
      if (*(int *)(prof_ctx + 0x37a0) != 0) {
        *(undefined4 *)(prof_ctx + 0x37a0) = 4;
        prof_reset();
      }
      prof_fread(piVar4,0x3aac,1,snap_file,1);
      iVar5 = prof_ctx;
      if (*piVar4 != 0) {
        puVar1 = (undefined4 *)(prof_ctx + 0x34e8);
        prof_malloc(*(int *)(prof_ctx + 0x34fc) << 2);
        if (0 < *(int *)(iVar5 + 0x34fc)) {
          do {
            prof_malloc(0x14);
            prof_fread(buf,0x14,1,snap_file,1);
            uVar2 = buf[3];
            uVar3 = buf[2];
            prof_malloc(*buf);
            buf[2] = (ulong)buf_00;
            prof_fread(buf_00,*buf,1,snap_file,(uint)(buf[1] != 1));
            *(ulong *)((int)p + iVar6 * 4) = buf[2];
            buf[3] = (uVar2 - uVar3) + buf[2];
            if (iVar6 == 0) {
              *puVar1 = buf;
            }
            else {
              *(ulong **)(*(int *)(iVar5 + 0x34ec) + 0x10) = buf;
            }
            *(ulong **)(iVar5 + 0x34ec) = buf;
            if (buf[1] == 1) {
              *(ulong **)(iVar5 + 0x34f4) = buf;
            }
            else {
              *(ulong **)(iVar5 + 0x34f0) = buf;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 < *(int *)(iVar5 + 0x34fc));
        }
        prof_fread(&local_8,4,1,snap_file,1);
        prof_malloc(local_8 << 4);
        prof_fread(buf_01,0x10,local_8,snap_file,1);
        iVar6 = 0;
        if (0 < (int)local_8) {
          piVar4 = (int *)((int)buf_01 + 0xc);
          do {
            iVar5 = prof_ctx;
            if (piVar4[-3] != -1) {
              iVar5 = *(int *)((int)p + piVar4[-3] * 4);
            }
            iVar6 = iVar6 + 1;
            *(int *)(piVar4[-2] + iVar5) = *(int *)((int)p + piVar4[-1] * 4) + *piVar4;
            piVar4 = piVar4 + 4;
          } while (iVar6 < (int)local_8);
        }
        dsp_free(buf_01);
        dsp_free(p);
        return;
      }
    }
    else {
      *piVar4 = 0;
      snap_error = 1;
    }
  }
  return;
}


/* ==== cmd_where_h0 @ 0043e750 ==== */

void cmd_where_h0(void)

{
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *extraout_EAX_01;
  undefined4 *puVar1;
  undefined4 *puVar2;
  char *text;
  char *prefix_first;
  
  cdb_frame_current();
  puVar2 = extraout_EAX;
  if (extraout_EAX == (undefined4 *)0x0) {
    cdb_build_backtrace();
    cdb_frame_current();
    puVar2 = extraout_EAX_00;
    if (extraout_EAX_00 == (undefined4 *)0x0) {
      return;
    }
  }
  cdb_frame_first();
  if (extraout_EAX_01 != (undefined4 *)0x0) {
    *(undefined4 *)(cur_sim + 0x4400) = 0;
    puVar1 = extraout_EAX_01;
    do {
      if (puVar1 == puVar2) {
        text = (char *)*puVar1;
        prefix_first = &DAT_004c6554;
      }
      else {
        text = (char *)*puVar1;
        prefix_first = &DAT_004c61b0;
      }
      cdb_print_wrapped(text,prefix_first,&DAT_004c61b0,4,0);
      puVar1 = (undefined4 *)puVar1[6];
    } while (puVar1 != (undefined4 *)0x0);
  }
  return;
}


/* ==== cmd_where_h1 @ 0043e7c0 ==== */

void cmd_where_h1(void)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *extraout_EAX_01;
  undefined4 *extraout_EAX_02;
  undefined4 *puVar3;
  uint uVar4;
  bool bVar5;
  char *text;
  char *prefix_first;
  
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar2 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar2 = (**(code **)(cur_dtype + 0x4e8))();
  }
  uVar4 = DAT_004a96c0;
  if ((uVar2 & 0x10000000) == 0) {
    if (((uVar2 & 0x4000000) != 0) && ((DAT_004a96c0 & 0x800000) != 0)) {
      uVar4 = DAT_004a96c0 | 0xff000000;
    }
  }
  else if ((DAT_004a96c0 & 0x8000) != 0) {
    uVar4 = DAT_004a96c0 | 0xffff0000;
  }
  cdb_frame_current();
  puVar3 = extraout_EAX;
  if (extraout_EAX == (undefined4 *)0x0) {
    cdb_build_backtrace();
    cdb_frame_current();
    puVar3 = extraout_EAX_00;
    if (extraout_EAX_00 == (undefined4 *)0x0) {
      return;
    }
  }
  bVar5 = -1 < (int)uVar4;
  if (bVar5) {
    cdb_frame_first();
    puVar1 = extraout_EAX_02;
  }
  else {
    uVar4 = -uVar4;
    cdb_frame_last();
    puVar1 = extraout_EAX_01;
  }
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined4 *)(cur_sim + 0x4400) = 0;
    while ((uVar4 != 0 && (puVar1 != (undefined4 *)0x0))) {
      uVar4 = uVar4 - 1;
      if (puVar1 == puVar3) {
        text = (char *)*puVar1;
        prefix_first = &DAT_004c6554;
      }
      else {
        text = (char *)*puVar1;
        prefix_first = &DAT_004c61b0;
      }
      cdb_print_wrapped(text,prefix_first,&DAT_004c61b0,4,0);
      if (bVar5) {
        puVar1 = (undefined4 *)puVar1[6];
      }
      else {
        puVar1 = (undefined4 *)puVar1[5];
      }
    }
  }
  return;
}


/* ==== cmd_where_parse @ 0043e8b0 ==== */

undefined ** cmd_where_parse(void)

{
  uint uVar1;
  int iVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar3;
  uint uVar4;
  undefined **ppuVar5;
  
  ppuVar5 = (undefined **)0x0;
  if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
    uVar1 = *(uint *)(cur_dtype + 0xc);
  }
  else {
    uVar1 = (**(code **)(cur_dtype + 0x4e8))();
  }
  iVar2 = parm_check_too_many(2);
  if (iVar2 != 0) {
    return &PTR_cmd_where_h0_004c63f8;
  }
  iVar2 = parm_number_or_end(2);
  if (iVar2 != 0) {
    iVar2 = parm_check_too_many(3);
    if (iVar2 != 0) {
      cdb_frame_first();
      iVar2 = extraout_EAX;
      if (extraout_EAX == 0) {
        cdb_build_backtrace();
        cdb_frame_first();
        iVar2 = extraout_EAX_00;
        if (extraout_EAX_00 == 0) {
          return (undefined **)0x0;
        }
      }
      uVar4 = DAT_004a96c0;
      if ((uVar1 & 0x10000000) == 0) {
        if (((uVar1 & 0x4000000) != 0) && ((DAT_004a96c0 & 0x800000) != 0)) {
          uVar4 = DAT_004a96c0 | 0xff000000;
        }
      }
      else if ((DAT_004a96c0 & 0x8000) != 0) {
        uVar4 = DAT_004a96c0 | 0xffff0000;
      }
      if ((int)uVar4 < 0) {
        uVar4 = -uVar4;
      }
      uVar1 = uVar4;
      if (uVar4 != 0) {
        do {
          iVar3 = 0;
          if (iVar2 == 0) break;
          iVar2 = *(int *)(iVar2 + 0x18);
          uVar1 = uVar1 - 1;
          iVar3 = iVar2;
        } while (uVar1 != 0);
        if ((uVar1 != 0) && (iVar3 == 0)) {
          sprintf(&DAT_00502078,s_There_aren_t__ld_frames_004c655c,uVar4);
          expr_error(&DAT_00502078);
          g_err_tok = DAT_004a9470;
          return (undefined **)0x0;
        }
      }
      ppuVar5 = &PTR_cmd_where_h1_004c6400;
    }
  }
  return ppuVar5;
}


