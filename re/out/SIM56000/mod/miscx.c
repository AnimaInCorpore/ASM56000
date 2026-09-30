/* ==== val_to_dec_parts2 @ 0045d120 ==== */

void __cdecl val_to_dec_parts2(ulong mode,ulong *in,ulong *out)

{
  ulong *den;
  int iVar1;
  ulong local_18;
  int local_14;
  ulong local_c;
  int local_8;
  
  if ((mode & 0x80) != 0) {
    *out = *in;
    out[1] = 0;
    return;
  }
  expr_mode = mode;
  iVar1 = (-(uint)((mode & 0x10000000) != 0) & 0xff010000) + 0x1000000;
  den = (ulong *)&dec_split_16;
  if ((mode & 0x10000000) == 0) {
    den = (ulong *)&dec_split_24;
  }
  mp_divmod(in,den,&local_c,&local_18);
  *out = iVar1 * local_14 + local_18;
  out[1] = iVar1 * local_8 + local_c;
  return;
}


/* ==== val_to_dec_parts @ 0045d1b0 ==== */

void __cdecl val_to_dec_parts(ulong mode,ulong *in,long *out)

{
  ulong *den;
  int iVar1;
  uint local_24;
  uint local_20;
  uint local_1c;
  ulong local_18;
  int local_14;
  ulong local_c;
  int local_8;
  
  if ((mode & 0x2000000) == 0) {
    local_1c = 0;
    local_24 = *in;
    local_20 = in[1];
  }
  else {
    local_1c = in[1] >> 0x10;
    local_20 = (in[1] & 0xffff) << 8 | *in >> 0x18;
    local_24 = *in & 0xffffff;
  }
  expr_mode = mode;
  iVar1 = (-(uint)((mode & 0x10000000) != 0) & 0xff010000) + 0x1000000;
  den = (ulong *)&dec_split_16;
  if ((mode & 0x10000000) == 0) {
    den = (ulong *)&dec_split_24;
  }
  mp_divmod(&local_24,den,&local_c,&local_18);
  *out = iVar1 * local_14 + local_18;
  out[1] = iVar1 * local_8 + local_c;
  return;
}


/* ==== dsp_free_ext @ 0045d280 ==== */

void dsp_free_ext(void *p)

{
  return;
}


/* ==== ret_true @ 0045d290 ==== */

int ret_true(void)

{
  return 1;
}


/* ==== ret_false @ 0045d2a0 ==== */

int ret_false(void)

{
  return 0;
}


/* ==== sim_error @ 0045d2b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl sim_error(char *msg)

{
  char local_100 [256];
  
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  strncpy(&status1_buf,msg,0xff);
  _last_error_code = 0xffffffff;
  sprintf(local_100,&DAT_004d2b80,msg);
  out_text(local_100,1);
  screen_flush();
  if ((macro_active != 0) && (quit_on_error != 0)) {
    on_error_active = 1;
    cmd_execute(cur_dev_index,s_quit__on_error_004d2b70);
  }
  return;
}


/* ==== ret_99 @ 0045d350 ==== */

int ret_99(void)

{
  undefined4 in_EAX;
  
  return CONCAT31((int3)((uint)in_EAX >> 8),99);
}


/* ==== cmd_load_h0_sub_45d360 @ 0045d360 ==== */

bool cmd_load_h0_sub_45d360(int param_1,char *param_2)

{
  bool bVar1;
  void *stream;
  int3 extraout_var;
  int3 extraout_var_00;
  int3 extraout_var_01;
  undefined4 uStack_3c;
  undefined1 auStack_34 [52];
  
  bVar1 = true;
  cur_dev = *(int **)(dev_tab + param_1 * 4);
  cur_dtype = *(undefined4 *)(chiptype_tab + *cur_dev * 4);
  fopen(param_2,&DAT_004c5ff4);
  if (stream != (void *)0x0) {
    cmd_save_h1_sub_45d400(stream,&stack0xffffffa8);
    if (-1 < extraout_var) {
      cmd_save_h1_sub_45d4c0(stream,auStack_34,uStack_3c);
      if (-1 < extraout_var_00) {
        cmd_load_h0_sub_45d510(param_1,stream);
        if (-1 < extraout_var_01) {
          bVar1 = false;
        }
      }
    }
    if (stream != (void *)0x0) {
      fclose(stream);
    }
  }
  return !bVar1;
}


/* ==== cmd_save_h1_sub_45d400 @ 0045d400 ==== */

int cmd_save_h1_sub_45d400(void *param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  fseek(param_1,0,0);
  uVar1 = fread(param_2,0x1c,1,param_1);
  if (uVar1 == 1) {
    fn_45d910_sub_45d480(param_2,0x1c);
    if (*param_2 == *(int *)(cur_dtype + 4)) {
      return param_2[4];
    }
    piVar3 = *(int **)(cur_dtype + 0x48);
    if ((piVar3 != (int *)0x0) && (iVar2 = *piVar3, iVar2 != 0)) {
      do {
        piVar3 = piVar3 + 1;
        if (iVar2 == *param_2) {
          return param_2[4];
        }
        iVar2 = *piVar3;
      } while (iVar2 != 0);
      return -1;
    }
  }
  return -1;
}


/* ==== fn_45d910_sub_45d480 @ 0045d480 ==== */

void fn_45d910_sub_45d480(int param_1,uint param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  
  param_2 = param_2 >> 2;
  if (param_2 != 0) {
    puVar3 = (undefined1 *)(param_1 + 2);
    do {
      uVar1 = puVar3[-2];
      puVar3[-2] = puVar3[1];
      uVar2 = *puVar3;
      *puVar3 = puVar3[-1];
      puVar3[-1] = uVar2;
      puVar3[1] = uVar1;
      puVar3 = puVar3 + 4;
      param_2 = param_2 - 1;
    } while (param_2 != 0);
  }
  return;
}


/* ==== cmd_save_h1_sub_45d4c0 @ 0045d4c0 ==== */

undefined4 cmd_save_h1_sub_45d4c0(void *param_1,void *param_2,int param_3)

{
  uint uVar1;
  
  fseek(param_1,0x1c,0);
  if (param_3 != 0x3c) {
    return 0xffffffff;
  }
  uVar1 = fread(param_2,0x3c,1,param_1);
  if (uVar1 != 1) {
    return 0xffffffff;
  }
  fn_45d910_sub_45d480(param_2,0x3c);
  return 0;
}


/* ==== cmd_load_h0_sub_45d510 @ 0045d510 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 cmd_load_h0_sub_45d510(undefined4 param_1,void *param_2)

{
  int3 extraout_var;
  int3 extraout_var_00;
  int iVar1;
  uint uVar2;
  void *extraout_EAX;
  void *extraout_EAX_00;
  int iVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  int in_stack_00000018;
  void *in_stack_0000001c;
  int iStack_8c;
  uint uStack_88;
  int iStack_84;
  long lStack_80;
  undefined4 uStack_7c;
  undefined1 auStack_78 [8];
  long lStack_70;
  uint uStack_6c;
  int aiStack_68 [2];
  uint uStack_60;
  undefined1 auStack_58 [8];
  int iStack_50;
  long lStack_4c;
  uint uStack_48;
  uint uStack_40;
  undefined4 uStack_3c;
  undefined1 auStack_34 [4];
  int iStack_30;
  long lStack_14;
  
  cmd_save_h1_sub_45d400(param_2,auStack_58);
  if (extraout_var < 0) {
    return 0xffffffff;
  }
  cmd_save_h1_sub_45d4c0(param_2,auStack_34,uStack_3c);
  if (extraout_var_00 < 0) {
    return 0xffffffff;
  }
  uStack_88 = 0;
  if (uStack_40 != 0) {
    iStack_84 = 0;
    do {
      iVar1 = fseek(param_2,iStack_30 + 0x1c + iStack_84,0);
      if (iVar1 != 0) {
        return 0xffffffff;
      }
      uVar2 = fread(auStack_78,0x34,1,param_2);
      if (uVar2 != 1) {
        return 0xffffffff;
      }
      fn_45d910_sub_45d480(auStack_78,0x34);
      fn_45d910_sub_45d480(&lStack_70,8);
      iVar1 = strncmp((char *)aiStack_68,&DAT_004d2c20,8);
      if ((iVar1 == 0) || (iVar1 = strncmp((char *)aiStack_68,&DAT_004d2c18,8), iVar1 == 0)) {
        if (_DAT_00502a18 < iStack_50) {
          if (_DAT_00502a1c == (void *)0x0) {
            dsp_alloc(iStack_50 * 8,0);
            _DAT_00502a1c = extraout_EAX_00;
          }
          else {
            dsp_realloc(_DAT_00502a1c,iStack_50 * 8);
            _DAT_00502a1c = extraout_EAX;
          }
          _DAT_00502a18 = iStack_50 * 2;
        }
        iVar1 = fseek(param_2,lStack_4c,0);
        if (iVar1 != 0) {
          return 0xffffffff;
        }
        if ((iStack_50 != 0) && (uVar2 = fread(_DAT_00502a1c,iStack_50 * 4,1,param_2), uVar2 != 1))
        {
          return 0xffffffff;
        }
        fn_45d910_sub_45d480(_DAT_00502a1c,iStack_50 << 2);
        uVar2 = uStack_6c;
        if ((((*(int *)(cur_dtype + 4) == 0x2ca) && (uStack_6c == 0x1e)) &&
            ((uStack_48 & 0x800) != 0)) && ((uStack_48 & 0x4000) == 0)) {
          uVar2 = 0x1d;
        }
        if ((uStack_48 & 0x400) == 0) {
          if ((uVar2 < 0xb) && (*(char *)(uVar2 + 0x4d2b88) != '\0')) {
            iVar1 = 2;
            uVar6 = uStack_60 >> 1;
          }
          else {
            iVar1 = 1;
            uVar6 = uStack_60;
          }
          param_2 = in_stack_0000001c;
          if ((*(int *)(*(int *)(cur_dtype + 0x28) + 0x18) == 0) || ((uStack_48 & 0x4000) == 0)) {
            if (uVar6 != 0) {
              iVar4 = 0;
              iStack_8c = iVar1 << 2;
              lVar5 = lStack_70;
              do {
                iVar1 = dev_call_slot1(in_stack_00000018,uVar2,lVar5,(int)_DAT_00502a1c + iVar4);
                if (iVar1 == 0) {
                  iVar1 = 1;
                }
                lVar5 = lVar5 + iVar1;
                iVar4 = iVar4 + iStack_8c;
                uVar6 = uVar6 - 1;
              } while (uVar6 != 0);
            }
          }
          else if (uVar6 != 0) {
            iVar4 = 0;
            iStack_8c = iVar1 << 2;
            lVar5 = lStack_70;
            do {
              iVar1 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x18))
                                (uVar2,lVar5,(int)_DAT_00502a1c + iVar4,0);
              if (iVar1 == 0) {
                iVar1 = 1;
              }
              lVar5 = lVar5 + iVar1;
              iVar4 = iVar4 + iStack_8c;
              uVar6 = uVar6 - 1;
            } while (uVar6 != 0);
          }
        }
        else {
          lVar5 = lStack_70;
          iVar1 = aiStack_68[0];
          if ((*(int *)(*(int *)(cur_dtype + 0x28) + 0x18) == 0) ||
             (iVar4 = lStack_70, (uStack_48 & 0x4000) == 0)) {
            for (; iVar1 != 0; iVar1 = iVar1 + -1) {
              iVar4 = dev_call_slot1(in_stack_00000018,uVar2,lVar5,(long)_DAT_00502a1c);
              if (iVar4 == 0) {
                iVar4 = 1;
              }
              lVar5 = lVar5 + iVar4;
            }
          }
          else {
            for (; iVar1 != 0; iVar1 = iVar1 + -1) {
              iVar3 = (**(code **)(*(int *)(cur_dtype + 0x28) + 0x18))(uVar2,iVar4,_DAT_00502a1c,0);
              if (iVar3 == 0) {
                iVar3 = 1;
              }
              iVar4 = iVar4 + iVar3;
            }
          }
        }
      }
      uStack_88 = uStack_88 + 1;
      iStack_84 = iStack_84 + 0x34;
    } while (uStack_88 < uStack_40);
  }
  lVar5 = periph_find_reg(in_stack_00000018,&DAT_004b294c,(int *)&uStack_88,&iStack_8c);
  if (lVar5 != 0) {
    lStack_80 = lStack_14;
    uStack_7c = 0;
    iVar1 = dev_write_reg(in_stack_00000018,uStack_88,iStack_8c,&lStack_80);
    if (iVar1 == 0) {
      sim_error(s_Error_writing_pc_004d2c04);
      if (_DAT_00502a1c != (void *)0x0) {
        dsp_free(_DAT_00502a1c);
        _DAT_00502a18 = 0;
        _DAT_00502a1c = (void *)0x0;
      }
      return 0xffffffff;
    }
  }
  if (_DAT_00502a1c != (void *)0x0) {
    dsp_free(_DAT_00502a1c);
    _DAT_00502a18 = 0;
    _DAT_00502a1c = (void *)0x0;
  }
  return 0;
}


/* ==== cmd_save_h1_sub_45d910 @ 0045d910 ==== */

bool cmd_save_h1_sub_45d910(char *param_1,int param_2)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  void *va0;
  undefined3 extraout_var;
  void *extraout_EAX;
  int3 extraout_var_00;
  int3 extraout_var_01;
  uint uVar4;
  void *extraout_EAX_00;
  int iVar5;
  void *stream;
  void *stream_00;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint *puVar11;
  int *piVar12;
  uint *puVar13;
  int *piVar14;
  char *pcVar15;
  bool bVar16;
  void *pvStack_4f8;
  undefined4 *puStack_4f4;
  void *pvStack_4f0;
  char *pcStack_4ec;
  int *piStack_4e8;
  undefined1 uStack_4e1;
  uint uStack_4e0;
  char *pcStack_4dc;
  uint uStack_4d8;
  uint *puStack_4d4;
  char *pcStack_4d0;
  uint uStack_4cc;
  int iStack_4c8;
  int iStack_4c4;
  int iStack_4c0;
  uint auStack_4bc [4];
  int iStack_4ac;
  int iStack_4a8;
  undefined4 uStack_4a4;
  int aiStack_4a0 [4];
  undefined1 auStack_490 [8];
  uint uStack_488;
  int iStack_484;
  int iStack_480;
  int iStack_47c;
  undefined4 uStack_478;
  int iStack_474;
  undefined4 uStack_470;
  uint uStack_46c;
  undefined1 auStack_468 [8];
  int aiStack_460 [5];
  uint uStack_44c;
  undefined4 uStack_448;
  uint uStack_444;
  undefined4 uStack_440;
  uint uStack_43c;
  uint uStack_438;
  uint uStack_434;
  undefined4 uStack_430;
  uint uStack_42c;
  undefined4 uStack_428;
  undefined1 auStack_424 [12];
  uint auStack_418 [8];
  char acStack_3f8 [16];
  undefined1 auStack_3e8 [1000];
  
  uVar9 = 0;
  pvStack_4f8 = (void *)0x0;
  pvStack_4f0 = (void *)0x0;
  bVar16 = true;
  pcStack_4d0 = (char *)0x0;
  uStack_46c = 0;
  pcStack_4ec = (char *)0x0;
  iStack_4c0 = 0;
  if (param_2 == 0) {
    fopen(param_1,&DAT_004c63b4);
    pvStack_4f8 = extraout_EAX_00;
    if (extraout_EAX_00 != (void *)0x0) {
      puVar11 = (uint *)0x5029f8;
      puVar13 = auStack_4bc;
      for (iVar8 = 7; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar13 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar13 = puVar13 + 1;
      }
      auStack_4bc[0] = *(uint *)(cur_dtype + 4);
      iStack_4a8 = 0x3c;
      auStack_4bc[2] = time((long *)0x0);
      auStack_4bc[3] = iStack_4a8 + 0x1c;
      uStack_4a4 = 0xf;
      uStack_4e0 = 0xffffffff;
      piVar12 = (int *)0x502a20;
      piVar14 = aiStack_460;
      for (iVar8 = 0xf; iVar8 != 0; iVar8 = iVar8 + -1) {
        *piVar14 = *piVar12;
        piVar12 = piVar12 + 1;
        piVar14 = piVar14 + 1;
      }
LAB_0045daf8:
      bVar16 = true;
      iStack_4c8 = 0;
      iStack_4c4 = 0;
      if (DAT_004a93ea != 'N') {
        pcStack_4dc = &DAT_004a93ea;
        puStack_4d4 = &DAT_004a96c0;
        cVar3 = DAT_004a93ea;
        do {
          if (((cVar3 == 'p') || (cVar3 == 'X')) || (cVar3 == 'P')) {
            uVar9 = *puStack_4d4;
            uVar4 = puStack_4d4[cVar3 != 'p'];
            iVar10 = (uint)(ushort)puStack_4d4[7] * 0x2c;
            iVar5 = *(int *)(cur_dtype + 0x20) + iVar10;
            uStack_4cc = *(uint *)(iVar5 + 0x18);
            iVar8 = *(int *)(iVar5 + 0x28);
            uVar6 = (uVar4 - uVar9) + 1;
            if ((*(byte *)(iVar5 + 0x24) & 2) != 0) {
              uVar6 = uVar6 * 2;
            }
            if (1 < iVar8) {
              uVar6 = (int)((iVar8 - (int)uVar6 % iVar8) + uVar6) / iVar8;
            }
            uVar6 = uVar6 & *(uint *)(iVar5 + 0x20);
            iStack_4c8 = iStack_4c8 + uVar6;
            iStack_4c4 = iStack_4c4 + 1;
            if ((uStack_4cc & 0x1000) == 0) {
              aiStack_460[3] = aiStack_460[3] + uVar6;
              if (uVar9 < uStack_43c) {
                uStack_43c = uVar9;
                uStack_438 = *(uint *)(iVar10 + 4 + *(int *)(cur_dtype + 0x20));
              }
              if (uStack_42c < uVar4) {
                uStack_42c = uVar4;
                uStack_428 = *(undefined4 *)(iVar10 + 4 + *(int *)(cur_dtype + 0x20));
              }
            }
            else {
              aiStack_460[2] = aiStack_460[2] + uVar6;
              if (uVar9 < uStack_4e0) {
                uStack_44c = uVar9;
                uStack_448 = *(undefined4 *)(iVar10 + 4 + *(int *)(cur_dtype + 0x20));
                uStack_4e0 = uVar9;
              }
              if (uVar9 < uStack_444) {
                uStack_444 = uVar9;
                uStack_440 = *(undefined4 *)(iVar10 + 4 + *(int *)(cur_dtype + 0x20));
              }
              if (uStack_434 < uVar4) {
                uStack_434 = uVar4;
                uStack_430 = *(undefined4 *)(iVar10 + 4 + *(int *)(cur_dtype + 0x20));
              }
            }
          }
          puStack_4d4 = puStack_4d4 + 10;
          pcStack_4dc = pcStack_4dc + 1;
          cVar3 = *pcStack_4dc;
        } while (cVar3 != 'N');
      }
      uStack_4e0 = auStack_4bc[1];
      auStack_4bc[1] = auStack_4bc[1] + iStack_4c4;
      iVar8 = iStack_4a8 + 0x1c + auStack_4bc[1] * 0x34;
      puStack_4d4 = (uint *)auStack_4bc[3];
      iVar5 = iVar8 + (iStack_4c8 + iStack_4c0) * 4;
      auStack_4bc[3] = iVar5 + (int)pcStack_4ec * 0xc;
      puVar11 = auStack_4bc;
      puVar13 = auStack_418;
      for (iVar10 = 7; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar13 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar13 = puVar13 + 1;
      }
      fn_45d910_sub_45d480(auStack_4bc,0x1c);
      uVar9 = fwrite(auStack_4bc,0x1c,1,pvStack_4f8);
      if (uVar9 == 1) {
        puVar11 = auStack_418;
        puVar13 = auStack_4bc;
        for (iVar10 = 7; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar13 = puVar13 + 1;
        }
        fn_45d910_sub_45d480(aiStack_460,0x3c);
        uVar9 = fwrite(aiStack_460,0x3c,1,pvStack_4f8);
        if ((uVar9 == 1) &&
           ((param_2 == 0 || (iVar10 = fseek(pvStack_4f0,iStack_4a8 + 0x1c,0), iVar10 == 0)))) {
          iVar10 = 0;
          bVar16 = false;
          do {
            puStack_4f4 = (undefined4 *)iVar8;
            if ((int)uStack_4e0 <= iVar10) break;
            uVar9 = fread(aiStack_4a0,0x34,1,pvStack_4f0);
            if (uVar9 != 1) {
              bVar16 = true;
            }
            fn_45d910_sub_45d480(aiStack_4a0,0x34);
            fn_45d910_sub_45d480(aiStack_4a0 + 2,8);
            uStack_478 = 0;
            uStack_470 = 0;
            if (iStack_47c != 0) {
              puStack_4f4 = (undefined4 *)(iVar8 + iStack_480 * 4);
              iStack_47c = iVar8;
            }
            iVar8 = iVar5;
            if (iStack_474 != 0) {
              iVar8 = iVar5 + uStack_46c * 0xc;
              iStack_474 = iVar5;
            }
            fn_45d910_sub_45d480(aiStack_4a0 + 2,0x34);
            fn_45d910_sub_45d480(auStack_490,8);
            uVar9 = fwrite(aiStack_4a0,0x34,1,pvStack_4f8);
            if (uVar9 != 1) {
              bVar16 = true;
            }
            iVar10 = iVar10 + 1;
            iVar5 = iVar8;
            iVar8 = (int)puStack_4f4;
          } while (!bVar16);
          if (!bVar16) {
            pcStack_4ec = &DAT_004a93ea;
            piStack_4e8 = &DAT_004a96c0;
            bVar16 = false;
            do {
              cVar3 = *pcStack_4ec;
              if (cVar3 == 'N') break;
              if ((cVar3 == 'P') || (cVar3 == 'X')) {
LAB_0045decd:
                iVar8 = *piStack_4e8;
                iVar5 = piStack_4e8[1];
                iVar10 = (uint)*(ushort *)(piStack_4e8 + 7) * 0x2c;
                uStack_4cc = *(uint *)(iVar10 + 0x24 + *(int *)(cur_dtype + 0x20));
                iVar7 = 0xd;
                if ((*(uint *)(iVar10 + *(int *)(cur_dtype + 0x20) + 0x18) & 0x1000) == 0) {
                  piVar12 = (int *)0x4d2bd0;
                  piVar14 = aiStack_4a0;
                  for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                    *piVar14 = *piVar12;
                    piVar12 = piVar12 + 1;
                    piVar14 = piVar14 + 1;
                  }
                  uStack_470 = 0x40;
                }
                else {
                  piVar12 = (int *)0x4d2b98;
                  piVar14 = aiStack_4a0;
                  for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                    *piVar14 = *piVar12;
                    piVar12 = piVar12 + 1;
                    piVar14 = piVar14 + 1;
                  }
                  uStack_470 = 0x20;
                }
                aiStack_4a0[3] = *(undefined4 *)(iVar10 + 4 + *(int *)(cur_dtype + 0x20));
                iVar10 = iVar10 + *(int *)(cur_dtype + 0x20);
                iVar7 = *(int *)(iVar10 + 0x28);
                uStack_488 = (iVar5 - iVar8) + 1U & *(uint *)(iVar10 + 0x20);
                if (1 < iVar7) {
                  uStack_488 = (int)((iVar7 - (int)uStack_488 % iVar7) + uStack_488) / iVar7;
                }
                if ((uStack_4cc & 2) != 0) {
                  uStack_488 = uStack_488 * 2;
                }
                iStack_484 = (int)puStack_4f4;
                puStack_4f4 = (undefined4 *)((int)puStack_4f4 + uStack_488 * 4);
                aiStack_4a0[2] = iVar8;
                fn_45d910_sub_45d480(aiStack_4a0,0x34);
                fn_45d910_sub_45d480(aiStack_4a0 + 2,8);
                uVar9 = fwrite(aiStack_4a0,0x34,1,pvStack_4f8);
                if (uVar9 != 1) {
                  bVar16 = true;
                }
              }
              else if (cVar3 == 'p') {
                piStack_4e8[1] = *piStack_4e8;
                goto LAB_0045decd;
              }
              pcStack_4ec = pcStack_4ec + 1;
              piStack_4e8 = piStack_4e8 + 10;
            } while (!bVar16);
          }
          iVar5 = 0;
          bVar16 = false;
          iVar8 = 0;
          do {
            if ((int)uStack_4e0 <= iVar5) break;
            iVar10 = fseek(pvStack_4f0,iStack_4a8 + 0x1c + iVar8,0);
            if (iVar10 == 0) {
              uVar9 = fread(aiStack_4a0,0x34,1,pvStack_4f0);
              if (uVar9 == 1) {
                if ((iStack_484 != 0) && (uStack_488 != 0)) {
                  fn_45d910_sub_45d480(aiStack_4a0,0x34);
                  iVar10 = fseek(pvStack_4f0,iStack_484,0);
                  if (iVar10 == 0) {
                    for (; (!bVar16 && (uStack_488 != 0)); uStack_488 = uStack_488 - 1) {
                      uVar9 = fread(auStack_468,4,1,pvStack_4f0);
                      if ((uVar9 != 1) || (uVar9 = fwrite(auStack_468,4,1,pvStack_4f8), uVar9 != 1))
                      {
                        bVar16 = true;
                      }
                    }
                  }
                  else {
                    bVar16 = true;
                  }
                }
              }
              else {
                bVar16 = true;
              }
            }
            else {
              bVar16 = true;
            }
            iVar5 = iVar5 + 1;
            iVar8 = iVar8 + 0x34;
          } while (!bVar16);
          if (!bVar16) {
            pcStack_4ec = &DAT_004a93ea;
            puStack_4f4 = &DAT_004a96c0;
            iVar8 = cur_dtype;
            do {
              cVar3 = *pcStack_4ec;
              if (cVar3 == 'N') break;
              if ((cVar3 == 'P') || (cVar3 == 'X')) {
LAB_0045e141:
                pcVar15 = (char *)*puStack_4f4;
                pcStack_4dc = (char *)puStack_4f4[1];
                iVar5 = (uint)*(ushort *)(puStack_4f4 + 7) * 0x2c;
                uStack_4d8 = (-(uint)((*(uint *)(iVar5 + 0x24 + *(int *)(iVar8 + 0x20)) & 2) != 0) &
                             4) + 4;
                uVar9 = *(uint *)(iVar5 + 0x20 + *(int *)(iVar8 + 0x20));
                while (!bVar16) {
                  pcVar15 = (char *)((uint)pcVar15 & uVar9);
                  pcVar1 = (code *)(*(undefined4 **)(iVar8 + 0x28))[10];
                  if (pcVar1 == (code *)0x0) {
                    iVar10 = (*(code *)**(undefined4 **)(iVar8 + 0x28))
                                       (*(undefined4 *)(*(int *)(iVar8 + 0x20) + 4 + iVar5),pcVar15,
                                        auStack_468);
                  }
                  else {
                    iVar10 = (*pcVar1)(*(undefined4 *)(*(int *)(iVar8 + 0x20) + 4 + iVar5),pcVar15,
                                       auStack_468);
                  }
                  if (iVar10 == 0) {
                    iVar10 = 1;
                  }
                  fn_45d910_sub_45d480(auStack_468,uStack_4d8);
                  uVar4 = fwrite(auStack_468,uStack_4d8,1,pvStack_4f8);
                  bVar16 = uVar4 != 1;
                  iVar8 = iVar10;
                  while (iVar8 = iVar8 + -1, 0 < iVar8) {
                    if ((char *)((uint)(pcVar15 + iVar8) & uVar9) == pcStack_4dc) {
                      pcVar15 = pcStack_4dc;
                    }
                  }
                  iVar8 = cur_dtype;
                  if (pcVar15 == pcStack_4dc) break;
                  pcVar15 = pcVar15 + iVar10;
                }
              }
              else if (cVar3 == 'p') {
                puStack_4f4[1] = *puStack_4f4;
                goto LAB_0045e141;
              }
              pcStack_4ec = pcStack_4ec + 1;
              puStack_4f4 = puStack_4f4 + 10;
            } while (!bVar16);
          }
          bVar16 = false;
          iVar8 = 0;
          iVar5 = 0;
          do {
            if ((int)uStack_4e0 <= iVar8) break;
            iVar10 = fseek(pvStack_4f0,iStack_4a8 + 0x1c + iVar5,0);
            if (iVar10 == 0) {
              uVar9 = fread(aiStack_4a0,0x34,1,pvStack_4f0);
              if (uVar9 == 1) {
                if ((iStack_47c != 0) && (iStack_474 != 0)) {
                  fn_45d910_sub_45d480(aiStack_4a0,0x34);
                  iVar10 = fseek(pvStack_4f0,iStack_47c,0);
                  if (iVar10 == 0) {
                    for (; (!bVar16 && (iStack_474 != 0)); iStack_474 = iStack_474 + -1) {
                      uVar9 = fread(auStack_424,0xc,1,pvStack_4f0);
                      if ((uVar9 != 1) ||
                         (uVar9 = fwrite(auStack_424,0xc,1,pvStack_4f8), uVar9 != 1)) {
                        bVar16 = true;
                      }
                    }
                  }
                  else {
                    bVar16 = true;
                  }
                }
              }
              else {
                bVar16 = true;
              }
            }
            else {
              bVar16 = true;
            }
            iVar8 = iVar8 + 1;
            iVar5 = iVar5 + 0x34;
          } while (!bVar16);
          if (param_2 != 0) {
            if ((puStack_4d4 != (uint *)0x0) &&
               (iVar8 = fseek(pvStack_4f0,(long)puStack_4d4,0), iVar8 != 0)) {
              bVar16 = true;
            }
            if ((param_2 != 0) && (iStack_4ac != 0)) {
              for (iVar8 = 0; (!bVar16 && (iVar8 < iStack_4ac)); iVar8 = iVar8 + 1) {
                uVar9 = fread(auStack_418,0x20,1,pvStack_4f0);
                if (uVar9 != 1) {
                  bVar16 = true;
                }
                uVar9 = fwrite(auStack_418,0x20,1,pvStack_4f8);
                if (uVar9 != 1) {
                  bVar16 = true;
                }
              }
            }
          }
          if (param_2 == 0) {
            uStack_4d8 = 0;
            uVar9 = fwrite(&uStack_4d8,4,1,pvStack_4f8);
            if (uVar9 != 1) {
              bVar16 = true;
            }
          }
          else {
            while ((!bVar16 && (uVar9 = fread(&uStack_4e1,1,1,pvStack_4f0), uVar9 == 1))) {
              uVar9 = fwrite(&uStack_4e1,1,1,pvStack_4f8);
              if (uVar9 != 1) {
                bVar16 = true;
              }
            }
            uStack_46c = ftell(pvStack_4f8);
          }
        }
      }
    }
  }
  else {
    fopen(param_1,&DAT_004c5ff4);
    pvStack_4f0 = va0;
    if (va0 != (void *)0x0) {
      cVar3 = tmpnam(acStack_3f8);
      pcStack_4d0 = (char *)CONCAT31(extraout_var,cVar3);
      fopen(pcStack_4d0,&DAT_004c63b4);
      pvStack_4f8 = extraout_EAX;
      if ((extraout_EAX != (void *)0x0) &&
         (cmd_save_h1_sub_45d400(va0,auStack_4bc), -1 < extraout_var_00)) {
        iStack_4ac = time((long *)0x0);
        cmd_save_h1_sub_45d4c0(piStack_4e8,aiStack_460 + 2,aiStack_4a0[0]);
        pcVar15 = pcStack_4dc;
        if (-1 < extraout_var_01) {
          bVar2 = false;
          uStack_4cc = uStack_438;
          iVar8 = 0;
          do {
            if (auStack_4bc[1] <= uVar9) break;
            uVar4 = fread(aiStack_4a0,0x34,1,pcVar15);
            if (uVar4 != 1) {
              bVar2 = true;
            }
            fn_45d910_sub_45d480(aiStack_4a0,0x34);
            if (iStack_484 != 0) {
              iStack_4c0 = iStack_4c0 + uStack_488;
            }
            if (iStack_47c != 0) {
              iVar8 = iVar8 + iStack_474;
              pcStack_4ec = (char *)iVar8;
            }
            uVar9 = uVar9 + 1;
          } while (!bVar2);
          bVar16 = true;
          if (!bVar2) goto LAB_0045daf8;
        }
      }
    }
  }
  if (pvStack_4f8 != (void *)0x0) {
    fclose(pvStack_4f8);
  }
  if (param_2 == 0) goto LAB_0045e57e;
  if (!bVar16) {
    fclose(pvStack_4f0);
    fopen(pcStack_4d0,&DAT_004c5ff4);
    fopen(param_1,&DAT_004c63b4);
    pvStack_4f0 = stream;
    if (stream != (void *)0x0) {
      uVar9 = uStack_46c;
      if (stream_00 == (void *)0x0) goto LAB_0045e564;
      for (; 0 < (int)uVar9; uVar9 = uVar9 - uVar4) {
        uVar4 = 1000;
        if ((int)uVar9 < 1000) {
          uVar4 = uVar9;
        }
        fread(auStack_3e8,uVar4,1,stream);
        fwrite(auStack_3e8,uVar4,1,stream_00);
      }
    }
    if (stream_00 != (void *)0x0) {
      fclose(stream_00);
    }
  }
LAB_0045e564:
  if (pvStack_4f0 != (void *)0x0) {
    fclose(pvStack_4f0);
    _unlink(pcStack_4d0);
  }
LAB_0045e57e:
  return !bVar16;
}


