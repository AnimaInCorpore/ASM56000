/* ==== str_icmp @ 004340f0 ==== */

int __cdecl str_icmp(char *a,char *b)

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


/* ==== str_nicmp @ 004341a0 ==== */

int __cdecl str_nicmp(char *a,char *b,int n)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  
  if (n == 0) {
    return 0;
  }
  do {
    cVar1 = *a;
    cVar2 = *b;
    a = a + 1;
    b = b + 1;
    if (cVar1 != cVar2) {
      iVar4 = (int)cVar1;
      if (__mb_cur_max < 2) {
        uVar3 = (byte)_pctype[iVar4 * 2] & 1;
      }
      else {
        uVar3 = _isctype(iVar4,1);
      }
      if (uVar3 != 0) {
        iVar4 = tolower(iVar4);
        cVar1 = (char)iVar4;
      }
      iVar4 = (int)cVar2;
      if (__mb_cur_max < 2) {
        uVar3 = (byte)_pctype[iVar4 * 2] & 1;
      }
      else {
        uVar3 = _isctype(iVar4,1);
      }
      if (uVar3 != 0) {
        iVar4 = tolower(iVar4);
        cVar2 = (char)iVar4;
      }
    }
    n = n + -1;
  } while ((((cVar1 != '\0') && (cVar2 != '\0')) && (cVar1 == cVar2)) && (n != 0));
  return (int)cVar1 - (int)cVar2;
}


/* ==== dev_write_reg @ 00434270 ==== */

int __cdecl dev_write_reg(int dev,int bank,int reg,long *val)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  cur_dev = *(int **)(dev_tab + dev * 4);
  cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
  iVar1 = *(int *)(cur_dtype + 0x18) + bank * 0x48;
  iVar3 = *(int *)(iVar1 + 0x2c);
  if ((reg < *(int *)(iVar3 + 0x28)) &&
     (iVar2 = *(int *)(iVar3 + 0x2c) + reg * 0x1c, (*(byte *)(iVar2 + 0x10) & 0x80) != 0)) {
    dev_spaces_call_c(*(int *)(iVar1 + 0x1c) + *(int *)(iVar2 + 8),*val,1);
    return 1;
  }
  (**(code **)(iVar3 + 4))(bank,reg,val);
  return 1;
}


/* ==== str_tolower @ 00434300 ==== */

int __cdecl str_tolower(char *s)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  
  cVar2 = *s;
  while (cVar2 != '\0') {
    iVar4 = (int)cVar2;
    if (__mb_cur_max < 2) {
      uVar3 = (byte)_pctype[iVar4 * 2] & 1;
    }
    else {
      uVar3 = _isctype(iVar4,1);
    }
    if (uVar3 != 0) {
      iVar4 = tolower(iVar4);
      *s = (char)iVar4;
    }
    pcVar1 = s + 1;
    s = s + 1;
    cVar2 = *pcVar1;
  }
  return 1;
}


/* ==== cmd_load_h0_sub_434350 @ 00434350 ==== */

uint cmd_load_h0_sub_434350(int param_1,char *param_2,int param_3)

{
  uint uVar1;
  undefined uVar2;
  undefined3 extraout_var;
  void *stream;
  int iVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  uint uVar7;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  long lStack_60;
  long lStack_5c;
  undefined4 uStack_58;
  char cStack_54;
  char acStack_53 [83];
  
  uVar2 = cmd_load_h0_sub_45d360(param_1,param_2);
  if (CONCAT31(extraout_var,uVar2) != 0) {
    return CONCAT31(extraout_var,uVar2);
  }
  if ((((param_1 < 0) || (max_devices <= param_1)) ||
      (cur_dev = *(int *)(dev_tab + param_1 * 4), cur_dev == 0)) ||
     (fopen(param_2,&DAT_004c5574), stream == (void *)0x0)) {
    return 0;
  }
  iVar3 = fscanf(stream,&DAT_004c556c,&cStack_54);
  uVar7 = (uint)(cStack_54 == '_');
  iStack_6c = -1;
joined_r0x004343e5:
  do {
    iVar6 = param_1;
    if ((uVar7 == 0) || (iVar3 == -1)) {
LAB_004347ee:
      fclose(stream);
      return uVar7;
    }
    if (cStack_54 == '_') {
      iStack_6c = sorted_table_lookup(acStack_53,&PTR_s_blockdata_004c5500,DAT_004c5518);
    }
    switch(iStack_6c) {
    case 0:
      iVar4 = fscanf(stream,&DAT_004c556c,&cStack_54);
      if (iVar4 == -1) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      uVar7 = dev_find_space(iVar6,&cStack_54,&iStack_70);
      if (uVar7 == 0) goto LAB_004347ee;
      iVar4 = fscanf(stream,&DAT_004c556c,&cStack_54);
      if (iVar4 == -1) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      iVar4 = sscanf(&cStack_54,&DAT_004c5568,&iStack_74);
      if (iVar4 == 0) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      iVar4 = fscanf(stream,&DAT_004c556c,&cStack_54);
      if (iVar4 == -1) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      iVar4 = sscanf(&cStack_54,&DAT_004c5568,&lStack_60);
      if (iVar4 == 0) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      if ((*(byte *)(*(int *)(cur_dtype + 0x20) + 0x24 +
                    *(int *)(cur_dtype + 0x4c + iStack_70 * 4) * 0x2c) & 2) != 0) {
        iVar4 = sscanf(&cStack_54,&DAT_004c5568,&uStack_58);
        if (iVar4 == 0) {
          uVar7 = 0;
          param_1 = param_3;
          break;
        }
        iVar4 = fscanf(stream,&DAT_004c556c,&cStack_54);
        if (iVar4 == -1) {
          uVar7 = 0;
          param_1 = param_3;
          break;
        }
      }
      iVar4 = fscanf(stream,&DAT_004c556c,&cStack_54);
      if (iVar4 == -1) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      iVar4 = sscanf(&cStack_54,&DAT_004c5568,&lStack_5c);
      if (iVar4 == 0) {
        uVar7 = 0;
        param_1 = param_3;
        break;
      }
      dev_call_slot2(iVar6,iStack_70,iStack_74,lStack_60,(long)&lStack_5c);
    default:
      iVar3 = fscanf(stream,&DAT_004c556c,&cStack_54);
      while ((param_1 = param_3, iVar3 != -1 && (param_1 = param_3, cStack_54 != '_'))) {
        iVar3 = fscanf(stream,&DAT_004c556c,&cStack_54);
      }
      break;
    case 2:
      iVar4 = fscanf(stream,&DAT_004c556c,&cStack_54);
      if (iVar4 == -1) {
        uVar7 = 0;
        param_1 = param_3;
      }
      else {
        uVar7 = dev_find_space(iVar6,&cStack_54,&iStack_70);
        if (uVar7 == 0) goto LAB_004347ee;
        iVar6 = fscanf(stream,&DAT_004c556c,&cStack_54);
        if (iVar6 == -1) {
          uVar7 = 0;
          param_1 = param_3;
        }
        else {
          iVar6 = sscanf(&cStack_54,&DAT_004c5568,&iStack_74);
          if (iVar6 == 0) {
            uVar7 = 0;
            param_1 = param_3;
          }
          else {
            uVar1 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 +
                             *(int *)(cur_dtype + 0x4c + iStack_70 * 4) * 0x2c);
            iVar3 = fscanf(stream,&DAT_004c556c,&cStack_54);
            while ((param_1 = param_3, iVar3 != -1 && (param_1 = param_3, cStack_54 != '_'))) {
              if ((((uVar1 & 2) != 0) &&
                  ((iVar6 = sscanf(&cStack_54,&DAT_004c5568,&uStack_58), iVar6 == 0 ||
                   (iVar6 = fscanf(stream,&DAT_004c556c,&cStack_54), iVar6 == -1)))) ||
                 (iVar6 = sscanf(&cStack_54,&DAT_004c5568,&lStack_5c), iVar6 == 0))
              goto switchD_00434430_caseD_ffffffff;
              iVar3 = dev_call_slot1(param_3,iStack_70,iStack_74,(long)&lStack_5c);
              if (iVar3 == 0) {
                iVar3 = 1;
              }
              iStack_74 = iStack_74 + iVar3;
              iVar3 = fscanf(stream,&DAT_004c556c,&cStack_54);
            }
          }
        }
      }
      break;
    case 3:
      goto switchD_00434430_caseD_3;
    case -1:
switchD_00434430_caseD_ffffffff:
      uVar7 = 0;
      param_1 = param_3;
    }
  } while( true );
switchD_00434430_caseD_3:
  iVar3 = fscanf(stream,&DAT_004c556c,&cStack_54);
  param_1 = param_3;
  if (((iVar3 != -1) &&
      (iVar4 = sscanf(&cStack_54,&DAT_004c5568,&lStack_5c), param_1 = param_3, iVar4 != 0)) &&
     (lVar5 = periph_find_reg(iVar6,&DAT_004b294c,&iStack_64,&iStack_68), param_1 = param_3,
     lVar5 != 0)) {
    uStack_58 = 0;
    iVar6 = dev_write_reg(iVar6,iStack_64,iStack_68,&lStack_5c);
    param_1 = param_3;
    if (iVar6 == 0) {
      sim_error(s_Error_writing_register_004c5550);
      return 0;
    }
  }
  goto joined_r0x004343e5;
}


/* ==== sorted_table_lookup @ 00434830 ==== */

int __cdecl sorted_table_lookup(char *s,char **table,int n)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 1;
  if (0 < n) {
    do {
      iVar1 = str_icmp(s,*table);
      if (iVar1 < 1) break;
      iVar2 = iVar2 + 1;
      table = table + 1;
    } while (iVar2 < n);
  }
  if ((iVar2 != n) && (iVar1 == 0)) {
    return iVar2;
  }
  return -1;
}


/* ==== save_state_all @ 00434880 ==== */

void __cdecl save_state_all(char *filename)

{
  save_state(filename,0,max_devices + -1);
  return;
}


/* ==== save_state @ 004348a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl save_state(char *filename,int first_dev,int last_dev)

{
  int iVar1;
  void *node;
  char cVar2;
  void *stream;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  void *stream_00;
  long lVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int *piVar12;
  char *pcVar13;
  char *pcVar14;
  int local_228;
  int local_224;
  int local_220;
  int local_21c;
  int local_218;
  int *local_214;
  int local_210;
  int local_20c;
  int local_208;
  int local_204;
  char local_200;
  undefined4 local_1ff;
  char local_1fb [2];
  char local_1f9;
  char local_100 [256];
  
  local_204 = 0;
  fopen(filename,&DAT_004c59ec);
  if (stream == (void *)0x0) {
    sim_error(s_Error_opening_file__004c59d8);
    return 1;
  }
  fprintf(stream,&DAT_004c59d4,0x2c4);
  fprintf(stream,s___s__004c59cc,banner_ptr);
  fprintf(stream,s__source_path__004c59bc);
  if (source_path_list == (char *)0x0) {
    fprintf(stream,&DAT_004c59ac);
  }
  else {
    uVar4 = 0xffffffff;
    pcVar13 = source_path_list;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar2 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar2 != '\0');
    fprintf(stream,s__d___s_004c59b4,~uVar4 - 1,source_path_list);
  }
  fprintf(stream,s__profiler__004c599c);
  local_200 = '\0';
  if (profiler_hook != (undefined *)0x0) {
    local_1ff = _DAT_004c5994;
    local_1fb[0] = s_null__004c5995[3];
    local_1fb[1] = s_null__004c5995[4];
    local_1f9 = s_null__004c5995[5];
    piVar12 = (int *)(dev_state_tab + first_dev * 4);
    for (iVar6 = first_dev; (iVar6 <= last_dev && (iVar6 < max_devices)); iVar6 = iVar6 + 1) {
      if ((*piVar12 != 0) && (*(int *)(*piVar12 + 0x188) != 0)) goto LAB_004349e4;
      piVar12 = piVar12 + 1;
    }
    goto LAB_00434a64;
  }
  fprintf(stream,s__null__004c5988);
LAB_00434a87:
  fprintf(stream,s__numdevices__004c5978);
  fprintf(stream,&DAT_004c59d4,(last_dev - first_dev) + 1);
  local_21c = 1;
  do {
    local_210 = first_dev;
    if ((last_dev < first_dev) || (max_devices <= first_dev)) break;
    cur_dev = *(int **)(dev_tab + first_dev * 4);
    if (cur_dev == (int *)0x0) {
      iVar6 = -1;
    }
    else {
      iVar6 = *cur_dev;
    }
    local_214 = cur_dev;
    fprintf(stream,s__devindex_devtype__004c5960);
    if ((iVar6 < 0) || (*(int *)(*(int *)(chiptype_tab + iVar6 * 4) + 0x4dc) == 0)) {
      fprintf(stream,s__d__d_004c5948,first_dev,iVar6);
    }
    else {
      fprintf(stream,s__d__2_004c5958,first_dev);
      fprintf(stream,&DAT_004c5950,**(undefined4 **)(chiptype_tab + iVar6 * 4));
      fprintf(stream,&DAT_004c5950,*(undefined4 *)(*(int *)(chiptype_tab + iVar6 * 4) + 0x4dc));
    }
    if (cur_dev != (int *)0x0) {
      local_220 = 0;
      iVar9 = *(int *)(dev_state_tab + first_dev * 4);
      cur_dtype = *(int *)(chiptype_tab + iVar6 * 4);
      cur_sim = iVar9;
      local_21c = cur_dtype;
      if (0 < *(int *)(cur_dtype + 0x14)) {
        local_218 = 0;
        do {
          iVar7 = local_220;
          iVar8 = local_214[2];
          iVar6 = local_220 * 4;
          iVar1 = *(int *)(local_218 + 0x2c + *(int *)(local_21c + 0x18));
          fprintf(stream,s__perattr__004c593c);
          local_224 = *(int *)(iVar9 + 8) + iVar7 * 8;
          fprintf(stream,&DAT_004c5934,*(undefined4 *)(*(int *)(iVar9 + 8) + iVar7 * 8));
          fprintf(stream,s__regattr__004c5928);
          iVar7 = 0;
          if (0 < *(int *)(iVar1 + 0x28)) {
            do {
              fprintf(stream,&DAT_004c5934,*(undefined4 *)(*(int *)(local_224 + 4) + iVar7 * 4));
              iVar7 = iVar7 + 1;
            } while (iVar7 < *(int *)(iVar1 + 0x28));
          }
          fprintf(stream,s__regval__004c591c);
          iVar7 = 0;
          if (0 < *(int *)(iVar1 + 0x24)) {
            do {
              fprintf(stream,&DAT_004c5934,*(undefined4 *)(*(int *)(iVar8 + iVar6) + iVar7 * 4));
              iVar7 = iVar7 + 1;
            } while (iVar7 < *(int *)(iVar1 + 0x24));
          }
          local_218 = local_218 + 0x48;
          local_220 = local_220 + 1;
        } while (local_220 < *(int *)(local_21c + 0x14));
      }
      if (*(code **)(cur_dtype + 0x4e8) != (code *)0x0) {
        (**(code **)(cur_dtype + 0x4e8))();
      }
      local_220 = 0;
      if (0 < *(int *)(local_21c + 0x1c)) {
        local_228 = 0;
        local_208 = 0;
        local_20c = 0;
        do {
          puVar10 = (undefined4 *)(local_20c + *(int *)(iVar9 + 4));
          iVar6 = local_208 + local_214[3];
          local_224 = local_228 + *(int *)(local_21c + 0x20);
          fprintf(stream,s__mem_disabled__004c5908);
          fprintf(stream,&DAT_004c5934,*(undefined4 *)(iVar6 + 0xc));
          fprintf(stream,s__memval__004c58fc);
          local_218 = 0;
          if (0 < *(int *)(local_224 + 0x14)) {
            do {
              fprintf(stream,&DAT_004c5934,*(undefined4 *)(*(int *)(iVar6 + 8) + local_218 * 4));
              local_218 = local_218 + 1;
            } while (local_218 < *(int *)(local_224 + 0x14));
          }
          fprintf(stream,s__memory_display_tags__004c58e4);
          save_maplist((void *)*puVar10,stream);
          save_maplist((void *)puVar10[2],stream);
          save_maplist((void *)puVar10[4],stream);
          save_maplist((void *)puVar10[3],stream);
          local_20c = local_20c + 300;
          local_220 = local_220 + 1;
          local_208 = local_208 + 0x10;
          local_228 = local_228 + 0x2c;
        } while (local_220 < *(int *)(local_21c + 0x1c));
      }
      fprintf(stream,s__global_signals__004c58d0);
      piVar12 = local_214;
      iVar6 = 0;
      if (0 < *(int *)(local_21c + 0x2c)) {
        do {
          fprintf(stream,&DAT_004c5934,*(undefined4 *)(piVar12[0x10] + iVar6 * 4));
          iVar6 = iVar6 + 1;
        } while (iVar6 < *(int *)(local_21c + 0x2c));
      }
      fprintf(stream,s__port_values__004c58c0);
      local_220 = 0;
      if (0 < *(int *)(local_21c + 0x30)) {
        local_228 = 0;
        do {
          puVar11 = (undefined4 *)(local_228 + local_214[6]);
          fprintf(stream,s__lx__lx__lx__lx__lx__lx__lx__lx___004c5894,*puVar11,puVar11[1],puVar11[2]
                  ,puVar11[3],puVar11[4],puVar11[0x25],puVar11[0x26],
                  *(undefined4 *)(local_228 + 0x9c + local_214[6]),puVar11[0x28],puVar11[0x29]);
          fprintf(stream,&DAT_004c5890);
          fprintf(stream,s__analog_pc_aval_values__004c5874);
          puVar10 = puVar11 + 5;
          local_224 = 0x20;
          do {
            fprintf(stream,&DAT_004c586c,*puVar10);
            puVar10 = puVar10 + 1;
            local_224 = local_224 + -1;
          } while (local_224 != 0);
          fprintf(stream,&DAT_004c5890);
          fprintf(stream,s__analog_pp_aval_values__004c5850);
          puVar11 = puVar11 + 0x2a;
          iVar6 = 0x20;
          do {
            fprintf(stream,&DAT_004c586c,*puVar11);
            puVar11 = puVar11 + 1;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          local_220 = local_220 + 1;
          local_228 = local_228 + 0x128;
          piVar12 = local_214;
        } while (local_220 < *(int *)(local_21c + 0x30));
      }
      fprintf(stream,s__reg_exec_reg_cycl_reg_icnt_flg__004c5828);
      fprintf(stream,s__lx__lx__lx__d__d_004c5814,piVar12[7],piVar12[8],piVar12[9],piVar12[0x11],
              piVar12[0x12]);
      fprintf(stream,s__sv_var_stat__004c5804);
      iVar6 = cur_sim;
      fprintf(stream,s__d__d__lx__lx__d__d__d__d__lx__d_004c57cc,*(undefined4 *)(cur_sim + 0x3c34),
              *(undefined4 *)(cur_sim + 0x184),*(undefined4 *)(cur_sim + 0xc),
              *(undefined4 *)(cur_sim + 0x10),*(undefined4 *)(cur_sim + 0x18),
              *(undefined4 *)(cur_sim + 0x1c),*(undefined4 *)(cur_sim + 0x20),
              *(undefined4 *)(cur_sim + 0x24),*(undefined4 *)(cur_sim + 0x28),
              *(undefined4 *)(cur_sim + 0x2c),*(undefined4 *)(cur_sim + 0x30),
              *(undefined4 *)(cur_sim + 0x34),*(undefined4 *)(cur_sim + 0x40),
              *(undefined4 *)(cur_sim + 0x44),(uint)(*(int *)(cur_sim + 0x48) != 0),cur_sim + 0x4c);
      fprintf(stream,s__pathwork__004c57bc);
      fprintf(stream,&DAT_004c5950,cur_dev + 0x16);
      fprintf(stream,s__counters_and_history__004c57a0);
      fprintf(stream,s__lx__lx__lx__lx__lx__d__d_004c5784,*(undefined4 *)(iVar6 + 0x15c),
              *(undefined4 *)(iVar6 + 0x160),*(undefined4 *)(iVar6 + 0x164),
              *(undefined4 *)(iVar6 + 0x168),*(undefined4 *)(cur_sim + 0x3fc0),
              *(undefined4 *)(cur_sim + 0x3fc4),*(undefined4 *)(cur_sim + 0x4400));
      fprintf(stream,s__histsz_and_hist_log__004c576c);
      fprintf(stream,&DAT_004c5764,history_size);
      local_220 = 0;
      if (0 < history_size) {
        local_228 = 0;
        do {
          fprintf(stream,&DAT_004c5934,*(undefined4 *)(*(int *)(cur_sim + 0x3fc8) + local_228));
          iVar8 = 10;
          iVar6 = local_228;
          do {
            iVar6 = iVar6 + 4;
            fprintf(stream,&DAT_004c575c,*(undefined4 *)(*(int *)(cur_sim + 0x3fc8) + iVar6));
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          local_220 = local_220 + 1;
          local_228 = local_228 + 0x2c;
        } while (local_220 < history_size);
      }
      iVar8 = 0;
      for (iVar6 = *(int *)(cur_sim + 0x3e78); iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x240)) {
        iVar8 = iVar8 + 1;
      }
      fprintf(stream,s__breakpoint_count__004c5744);
      fprintf(stream,&DAT_004c5740,iVar8);
      fprintf(stream,s__breakpoint_info__004c572c);
      puVar10 = *(undefined4 **)(cur_sim + 0x3e78);
      if (0 < iVar8) {
        do {
          fprintf(stream,s__d__d__d__d___s___s__d__lx__lx___004c56fc,*puVar10,puVar10[1],puVar10[2],
                  puVar10[3],puVar10 + 4,puVar10 + 0x44,puVar10[0x84],puVar10[0x88],puVar10[0x89],
                  puVar10[0x8a],(uint)*(ushort *)(puVar10 + 0x8e),
                  (uint)*(ushort *)((int)puVar10 + 0x23a),(uint)*(ushort *)(puVar10 + 0x8f),
                  (uint)*(ushort *)((int)puVar10 + 0x23e));
          if (puVar10[1] == 0xc) {
            if ((void *)puVar10[0x91] == (void *)0x0) {
              fprintf(stream,&DAT_004c56f8);
            }
            else {
              local_224 = 0;
              iVar6 = expr_tree_size((void *)puVar10[0x91],0,&local_224);
              fprintf(stream,&DAT_004c5740,iVar6 + 1);
              fprintf(stream,&DAT_004c5740,local_224);
              save_expr_tree(stream,(void *)puVar10[0x91],0);
              fprintf(stream,s__d__d_004c56f0,puVar10[0x92],puVar10[0x93]);
            }
          }
          puVar10 = (undefined4 *)puVar10[0x90];
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      local_228 = 0;
      fprintf(stream,s__watch_list__004c56e0);
      for (iVar6 = *(int *)(iVar9 + 0x3fa8); iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x120)) {
        local_228 = local_228 + 1;
      }
      fprintf(stream,&DAT_004c5740,local_228);
      puVar10 = *(undefined4 **)(iVar9 + 0x3fa8);
      if (0 < local_228) {
        do {
          node = (void *)puVar10[0x45];
          fprintf(stream,s__u___s__d__d__lu__lu_004c56c8,*puVar10,puVar10 + 1,puVar10[0x41],
                  puVar10[0x42],puVar10[0x43],puVar10[0x44]);
          if (puVar10[0x41] == 0) {
            if (node == (void *)0x0) {
              fprintf(stream,&DAT_004c56f8);
            }
            else {
              local_224 = 0;
              iVar6 = expr_tree_size(node,0,&local_224);
              fprintf(stream,&DAT_004c5740,iVar6 + 1);
              fprintf(stream,&DAT_004c5740,local_224);
              save_expr_tree(stream,node,0);
              fprintf(stream,s__d__d_004c56f0,puVar10[0x47],puVar10[0x46]);
            }
          }
          puVar10 = (undefined4 *)puVar10[0x48];
          local_228 = local_228 + -1;
        } while (local_228 != 0);
      }
      fprintf(stream,s__hio_enabled__004c56b8);
      fprintf(stream,&DAT_004c5740,*(undefined4 *)(iVar9 + 0x404c));
      fprintf(stream,s__send_buffer__004c56a8);
      fprintf(stream,s__d__lu__lu_004c569c,*(undefined4 *)(iVar9 + 0x4050),
              *(undefined4 *)(iVar9 + 0x4054),*(undefined4 *)(iVar9 + 0x4058));
      uVar4 = 0;
      if (*(int *)(iVar9 + 0x4058) != 0) {
        do {
          fprintf(stream,&DAT_004c5694,*(undefined4 *)(*(int *)(iVar9 + 0x405c) + uVar4 * 4));
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(iVar9 + 0x4058));
      }
      fprintf(stream,s__recv_buffer__004c5684);
      fprintf(stream,s__d__lu__lu_004c569c,*(undefined4 *)(iVar9 + 0x4060),
              *(undefined4 *)(iVar9 + 0x4064),*(undefined4 *)(iVar9 + 0x4068));
      uVar4 = 0;
      if (*(int *)(iVar9 + 0x4068) != 0) {
        do {
          fprintf(stream,&DAT_004c5694,*(undefined4 *)(*(int *)(iVar9 + 0x406c) + uVar4 * 4));
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(iVar9 + 0x4068));
      }
      fprintf(stream,s__send_address_recv_address__004c5664);
      fprintf(stream,s__d__lu_004c565c,*(undefined4 *)(iVar9 + 0x4074),
              *(undefined4 *)(iVar9 + 0x4070));
      fprintf(stream,s__d__lu_004c565c,*(undefined4 *)(iVar9 + 0x407c),
              *(undefined4 *)(iVar9 + 0x4078));
      fprintf(stream,s__afi_ufi__004c5650);
      fprintf(stream,s__d__d_004c56f0,*(undefined4 *)(iVar9 + 0x4088),
              *(undefined4 *)(iVar9 + 0x4084));
      local_220 = 0;
      if (0 < *(int *)(iVar9 + 0x4088)) {
        iVar6 = 0;
        do {
          iVar8 = *(int *)(iVar9 + 0x4080) + iVar6;
          fprintf(stream,s__d__d_004c56f0,*(undefined4 *)(iVar8 + 8),*(undefined4 *)(iVar8 + 0xc));
          iVar8 = *(int *)(iVar6 + 4 + *(int *)(iVar9 + 0x4080));
          if (iVar8 == 0) {
            fprintf(stream,&DAT_004c5640);
          }
          else {
            fprintf(stream,&DAT_004c5648,iVar8);
            lVar3 = _lseek(*(int *)(iVar6 + *(int *)(iVar9 + 0x4080)),0,1);
            fprintf(stream,&DAT_004c5694,lVar3);
            _close(*(int *)(iVar6 + *(int *)(iVar9 + 0x4080)));
            iVar8 = iVar6 + *(int *)(iVar9 + 0x4080);
            iVar8 = _open(*(char **)(iVar8 + 4),*(uint *)(iVar8 + 8) & 0xfffffdff,
                          *(undefined4 *)(iVar6 + 0xc + *(int *)(iVar9 + 0x4080)));
            *(int *)(iVar6 + *(int *)(iVar9 + 0x4080)) = iVar8;
            iVar8 = *(int *)(iVar6 + *(int *)(iVar9 + 0x4080));
            if (iVar8 != -1) {
              _lseek(iVar8,lVar3,0);
            }
          }
          local_220 = local_220 + 1;
          iVar6 = iVar6 + 0x10;
        } while (local_220 < *(int *)(iVar9 + 0x4088));
      }
      fprintf(stream,s__redirect_flag__filename__filepo_004c5614);
      puVar10 = (undefined4 *)(iVar9 + 0x4098);
      pcVar13 = (char *)(iVar9 + 0x40a4);
      local_224 = 3;
      do {
        fprintf(stream,&DAT_004c5740,puVar10[-3]);
        fprintf(stream,&DAT_004c5648,pcVar13);
        if (*pcVar13 == '\0') {
          fprintf(stream,&DAT_004c56f8);
        }
        else {
          lVar3 = ftell((void *)*puVar10);
          fprintf(stream,&DAT_004c5694,lVar3);
        }
        puVar10 = puVar10 + 1;
        pcVar13 = pcVar13 + 0x100;
        local_224 = local_224 + -1;
      } while (local_224 != 0);
      fprintf(stream,s__FOPEN_MAX__004c5604);
      fprintf(stream,&DAT_004c5740,0x14);
      puVar10 = (undefined4 *)(iVar9 + 0x43a4);
      iVar6 = 0x14;
      do {
        fprintf(stream,&DAT_004c5740,*puVar10);
        puVar10 = puVar10 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      fprintf(stream,s__state__004c55f8);
      fprintf(stream,&DAT_004c5740,*(undefined4 *)(iVar9 + 0x43f4));
      fprintf(stream,s__win_next__head__004c55e4);
      puVar10 = *(undefined4 **)(iVar9 + 0x3fbc);
      fprintf(stream,s__d__d_004c55dc,*puVar10,puVar10[1]);
      fprintf(stream,s__winsz__004c55d0);
      fprintf(stream,&DAT_004c59d4,scrollback_lines);
      iVar6 = 0;
      if (0 < scrollback_lines) {
        iVar9 = 0;
        do {
          fprintf(stream,&DAT_004c5950,iVar9 + puVar10[2]);
          iVar6 = iVar6 + 1;
          iVar9 = iVar9 + 0x100;
        } while (iVar6 < scrollback_lines);
      }
      fprintf(stream,s__io_files_and_external_memory__004c55ac);
      save_io_files(stream);
      if ((extraout_EAX == 0) || (mdisk_save_all(local_210,stream), extraout_EAX_00 == 0)) {
        local_21c = 0;
      }
      else {
        local_21c = 1;
        if (*(int *)(cur_sim + 0x4018) == 0) {
          fprintf(stream,&DAT_004c59ac);
        }
        else {
          fprintf(stream,s_1___s_004c55a4,*(int *)(cur_sim + 0x4018));
        }
      }
      if (((profiler_hook != (undefined *)0x0) && (local_200 != '\0')) &&
         (*(code **)(profiler_hook + 4) != (code *)0x0)) {
        (**(code **)(profiler_hook + 4))(&local_1ff,local_210,local_204);
        local_204 = 1;
      }
    }
    first_dev = local_210 + 1;
    local_210 = first_dev;
  } while (local_21c != 0);
  if (((profiler_hook != (undefined *)0x0) && (local_200 != '\0')) &&
     ((*(code **)(profiler_hook + 4) != (code *)0x0 && (local_204 != 0)))) {
    (**(code **)(profiler_hook + 4))(0,0,1);
  }
  iVar6 = local_21c;
  if (local_21c != 0) {
    fprintf(stream,s__viewdev__004c5598);
    fprintf(stream,&DAT_004c5590,cur_dev_index);
    if (iVar6 != 0) {
      rewind(stream);
      fprintf(stream,&DAT_004c5578,0x2c7);
      fseek(stream,0,2);
      goto LAB_00435881;
    }
  }
  sim_error(s_Error_writing_file_004c557c);
LAB_00435881:
  fflush(stream);
  fclose(stream);
  cur_dev = (int *)*(undefined4 *)(dev_tab + cur_dev_index * 4);
  return (uint)(iVar6 == 0);
LAB_004349e4:
  cVar2 = tmpnam(local_100);
  if (CONCAT31(extraout_var,cVar2) != 0) {
    cVar2 = strrchr(local_100,0x5c);
    pcVar13 = (char *)(CONCAT31(extraout_var_00,cVar2) + 1);
    if (CONCAT31(extraout_var_00,cVar2) == 0) {
      pcVar13 = local_100;
    }
    uVar4 = 0xffffffff;
    do {
      pcVar14 = pcVar13;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar14 = pcVar13 + 1;
      cVar2 = *pcVar13;
      pcVar13 = pcVar14;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    pcVar13 = pcVar14 + -uVar4;
    pcVar14 = (char *)&local_1ff;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar14 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      pcVar14 = pcVar14 + 1;
    }
    local_1ff = CONCAT22(local_1ff._2_2_,0x6670);
  }
  fopen((char *)&local_1ff,&DAT_004c5574);
  if (stream_00 == (void *)0x0) goto code_r0x00434a58;
  fclose(stream_00);
  goto LAB_004349e4;
code_r0x00434a58:
  local_200 = '\x01';
LAB_00434a64:
  fprintf(stream,&DAT_004c5990,&local_1ff);
  goto LAB_00434a87;
}


/* ==== save_maplist @ 004358d0 ==== */

void __cdecl save_maplist(void *list,void *fp)

{
  void *pvVar1;
  int va0;
  
  va0 = 0;
  for (pvVar1 = list; pvVar1 != (void *)0x0; pvVar1 = *(void **)((int)pvVar1 + 0xc)) {
    va0 = va0 + 1;
  }
  fprintf(fp,&DAT_004c5740,va0);
  for (; va0 != 0; va0 = va0 + -1) {
    fprintf(fp,s__d__lx__lx_004c59f0,*(undefined4 *)list,*(undefined4 *)((int)list + 4),
            *(undefined4 *)((int)list + 8));
    list = *(void **)((int)list + 0xc);
  }
  return;
}


/* ==== save_io_files @ 00435930 ==== */

void __cdecl save_io_files(void *fp)

{
  int iVar1;
  
  iVar1 = save_io_list(fp,(void *)(cur_sim + 0x14c));
  if (iVar1 != 0) {
    iVar1 = save_io_list(fp,(void *)(cur_sim + 0x150));
    if (iVar1 != 0) {
      iVar1 = save_io_list(fp,(void *)(cur_sim + 0x154));
      if (iVar1 != 0) {
        save_io_list(fp,(void *)(cur_sim + 0x158));
      }
    }
  }
  return;
}


/* ==== save_io_list @ 004359a0 ==== */

int __cdecl save_io_list(void *fp,void *list_head)

{
  undefined4 *puVar1;
  long lVar2;
  int iVar3;
  
  for (iVar3 = *(int *)list_head; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x1e0)) {
    fprintf(fp,&DAT_004c5a5c);
    if (*(void **)(iVar3 + 0x150) != (void *)0x0) {
      lVar2 = ftell(*(void **)(iVar3 + 0x150));
      *(long *)(iVar3 + 0x178) = lVar2;
    }
    fprintf(fp,s___s___s__d__lx__lx__lx__lx__lx___004c5a28,iVar3,iVar3 + 0x100,
            *(undefined4 *)(iVar3 + 0x154),*(undefined4 *)(iVar3 + 0x158),
            *(undefined4 *)(iVar3 + 0x15c),*(undefined4 *)(iVar3 + 0x160),
            *(undefined4 *)(iVar3 + 0x164),*(undefined4 *)(iVar3 + 0x168),
            *(undefined4 *)(iVar3 + 0x16c),*(undefined4 *)(iVar3 + 0x170),
            *(undefined4 *)(iVar3 + 0x174),*(undefined4 *)(iVar3 + 0x178),
            *(undefined4 *)(iVar3 + 0x1e4));
    fprintf(fp,s__lx__lx__d__d__ld__d_004c5a10,*(undefined4 *)(iVar3 + 0x188),
            *(undefined4 *)(iVar3 + 0x1b0),*(undefined4 *)(iVar3 + 0x1d0),
            *(undefined4 *)(iVar3 + 0x1d4),*(undefined4 *)(iVar3 + 0x1d8),
            (uint)(*(int *)(iVar3 + 0x150) != 0));
    for (puVar1 = *(undefined4 **)(iVar3 + 0x1dc); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)puVar1[3]) {
      fprintf(fp,&DAT_004c5a5c);
      fprintf(fp,s__lx__lx__ld_004c5a00,*puVar1,puVar1[1],puVar1[2]);
    }
    fprintf(fp,&DAT_004c59fc);
  }
  iVar3 = fprintf(fp,&DAT_004c59d4,0);
  return (uint)(iVar3 != -1);
}


/* ==== save_expr_tree @ 00435b00 ==== */

void __cdecl save_expr_tree(void *fp,void *node,int code)

{
  undefined4 *puVar1;
  
  if (node != (void *)0x0) {
    while (puVar1 = *(undefined4 **)((int)node + 0x10), puVar1 != (undefined4 *)0x0) {
      fprintf(fp,&DAT_004c5aa4,code);
      fprintf(fp,&DAT_004c5aa4,*(undefined4 *)((int)node + 0xc));
      fprintf(fp,s__lu__lu_004c5a98,puVar1[1],*puVar1);
      fprintf(fp,s__hu__hu_004c5a8c,(uint)*(ushort *)((int)puVar1 + 10),
              (uint)*(ushort *)(puVar1 + 2));
      fprintf(fp,s__lu__lu_004c5a98,puVar1[3],puVar1[4]);
      fprintf(fp,s__d__lu__hu_004c5a80,puVar1[7],puVar1[6],(uint)*(ushort *)(puVar1 + 0xf));
      fprintf(fp,s__lu__ld__ld__lu__lu__lu__lu_004c5a60,puVar1[8],puVar1[9],puVar1[10],puVar1[0xb],
              puVar1[0xc],puVar1[0xd],puVar1[0xe]);
      if (*(void **)node != (void *)0x0) {
        save_expr_tree(fp,*(void **)node,code * 3 + 1);
      }
      if (*(void **)((int)node + 4) != (void *)0x0) {
        save_expr_tree(fp,*(void **)((int)node + 4),code * 3 + 2);
      }
      node = *(void **)((int)node + 8);
      if (node == (undefined4 *)0x0) {
        return;
      }
      code = (code + 1) * 3;
      if (node == (undefined4 *)0x0) {
        return;
      }
    }
  }
  return;
}


/* ==== expr_tree_size @ 00435c20 ==== */

int __cdecl expr_tree_size(void *node,int code,int *count)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar2 = 0;
  local_4 = 0;
  local_8 = 0;
  *count = *count + 1;
  if (*(void **)node != (void *)0x0) {
    local_4 = expr_tree_size(*(void **)node,code * 3 + 1,count);
  }
  if (*(void **)((int)node + 4) != (void *)0x0) {
    local_8 = expr_tree_size(*(void **)((int)node + 4),code * 3 + 2,count);
  }
  if (*(void **)((int)node + 8) != (void *)0x0) {
    iVar2 = expr_tree_size(*(void **)((int)node + 8),(code + 1) * 3,count);
  }
  iVar3 = code;
  if (code <= local_4) {
    iVar3 = local_4;
  }
  iVar1 = local_8;
  if (local_8 <= iVar2) {
    iVar1 = iVar2;
  }
  if (iVar1 < iVar3) {
    if (local_4 < code) {
      return code;
    }
  }
  else {
    local_4 = local_8;
    if (local_8 <= iVar2) {
      local_4 = iVar2;
    }
  }
  return local_4;
}


/* ==== devtype_find @ 00435ce0 ==== */

int __cdecl devtype_find(char *name1,char *name2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((devtype_find_hook == (undefined *)0x0) ||
     (iVar1 = (*(code *)devtype_find_hook)(name1,name2), iVar1 < 0)) {
    iVar1 = -1;
  }
  else {
    cur_dtype = *(int *)(chiptype_tab + iVar1 * 4);
    iVar2 = *(int *)(cur_dtype + 0x1c) + -1;
    if (-1 < iVar2) {
      iVar3 = iVar2 * 0x2c;
      do {
        iVar3 = iVar3 + -0x2c;
        *(int *)(cur_dtype + 0x4c + *(int *)(*(int *)(cur_dtype + 0x20) + 0x30 + iVar3) * 4) = iVar2
        ;
        iVar2 = iVar2 + -1;
      } while (-1 < iVar2);
      return iVar1;
    }
  }
  return iVar1;
}


/* ==== dev_create @ 00435d40 ==== */

int __cdecl dev_create(int dev,char *devtype_name)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  void *extraout_EAX;
  int *p;
  undefined4 extraout_EAX_00;
  undefined4 extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 extraout_EAX_03;
  int extraout_EAX_04;
  int extraout_EAX_05;
  int extraout_EAX_06;
  int iVar4;
  int bank;
  
  if ((dev < 0) || (max_devices <= dev)) {
    return 0;
  }
  iVar4 = 0;
  if (0 < num_chiptypes) {
    do {
      if ((*(undefined4 **)(chiptype_tab + iVar4 * 4) == (undefined4 *)0x0) ||
         (iVar3 = str_icmp(devtype_name,(char *)**(undefined4 **)(chiptype_tab + iVar4 * 4)),
         iVar3 == 0)) break;
      iVar4 = iVar4 + 1;
    } while (iVar4 < num_chiptypes);
  }
  if (iVar4 == num_chiptypes) {
    return 0;
  }
  if (*(int *)(chiptype_tab + iVar4 * 4) == 0) {
    return 0;
  }
  if (*(int *)(dev_tab + dev * 4) != 0) {
    dev_destroy(dev);
  }
  cur_itype = *(undefined4 *)(itype_tab + iVar4 * 4);
  cur_dtype = *(int *)(chiptype_tab + iVar4 * 4);
  dsp_alloc(0x4408,1);
  cur_sim = extraout_EAX;
  dsp_alloc(0x168,1);
  iVar3 = *(int *)(cur_dtype + 0x14);
  if ((cur_sim == (void *)0x0) || (p == (int *)0x0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  cur_dev = p;
  if (bVar2) {
    *p = iVar4;
    cur_dev[1] = dev;
  }
  else {
    if (p != (int *)0x0) {
      dsp_free(p);
      cur_dev = (int *)0x0;
    }
    if (cur_sim != (void *)0x0) {
      dsp_free(cur_sim);
      cur_sim = (void *)0x0;
    }
  }
  if (bVar2) {
    dsp_alloc(0xc,1);
    *(undefined4 *)((int)cur_sim + 0x3fbc) = extraout_EAX_00;
    if (*(int *)((int)cur_sim + 0x3fbc) == 0) goto LAB_00435ed2;
    dsp_alloc(scrollback_lines << 8,1);
    *(undefined4 *)(*(int *)((int)cur_sim + 0x3fbc) + 8) = extraout_EAX_01;
    if (*(int *)(*(int *)((int)cur_sim + 0x3fbc) + 8) == 0) goto LAB_00435ed2;
    bVar2 = true;
  }
  else {
LAB_00435ed2:
    bVar2 = false;
  }
  if (bVar2) {
    dsp_alloc(history_size * 0x2c,1);
    *(undefined4 *)((int)cur_sim + 0x3fc8) = extraout_EAX_02;
    if (*(int *)((int)cur_sim + 0x3fc8) == 0) goto LAB_00435f14;
    bVar2 = true;
  }
  else {
LAB_00435f14:
    bVar2 = false;
  }
  if (bVar2) {
    if (iVar3 != 0) {
      dsp_alloc(iVar3 * 8,1);
      *(undefined4 *)((int)cur_sim + 8) = extraout_EAX_03;
      if (*(int *)((int)cur_sim + 8) != 0) {
        dsp_alloc(iVar3 * 4,1);
        cur_dev[2] = extraout_EAX_04;
        if (cur_dev[2] != 0) goto LAB_00435f6e;
      }
      goto LAB_00435f75;
    }
LAB_00435f6e:
    iVar4 = 1;
  }
  else {
LAB_00435f75:
    iVar4 = 0;
  }
  bank = 0;
  if (iVar4 != 0) {
    do {
      if (iVar3 <= bank) break;
      iVar4 = dev_alloc_regbank(bank);
      bank = bank + 1;
    } while (iVar4 != 0);
    if (iVar4 != 0) {
      iVar4 = dev_alloc_memmaps();
      if ((iVar4 == 0) || (iVar4 = dev_alloc_periph(), iVar4 == 0)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        dsp_alloc(*(int *)(cur_dtype + 0x2c) << 2,1);
        cur_dev[0x10] = extraout_EAX_05;
        if (cur_dev[0x10] != 0) {
          iVar4 = 1;
          goto LAB_00435fe6;
        }
      }
    }
  }
  iVar4 = 0;
LAB_00435fe6:
  *(int **)(dev_tab + dev * 4) = cur_dev;
  if (iVar4 != 0) {
    hio_buf_alloc((void *)((int)cur_sim + 0x4050),0x80);
    hio_buf_alloc((void *)((int)cur_sim + 0x4060),0x80);
  }
  *(void **)(dev_state_tab + dev * 4) = cur_sim;
  piVar1 = *(int **)(cur_dtype + 0x4e0);
  if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
    dsp_alloc(piVar1[2] << 2,1);
    cur_dev[0x56] = extraout_EAX_06;
    (*(code *)**(undefined4 **)(cur_dtype + 0x4e4))(dev);
  }
  if (iVar4 != 0) {
    dev_state_init();
    return iVar4;
  }
  dev_destroy(dev);
  return 0;
}


/* ==== dev_alloc_regbank @ 004360b0 ==== */

int __cdecl dev_alloc_regbank(int bank)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar4;
  
  piVar1 = (int *)(*(int *)(cur_dev + 8) + bank * 4);
  iVar4 = *(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + bank * 0x48);
  iVar2 = *(int *)(cur_sim + 8);
  *(undefined4 *)(iVar2 + 4 + bank * 8) = 0;
  iVar3 = *(int *)(iVar4 + 0x24);
  iVar4 = *(int *)(iVar4 + 0x28);
  *piVar1 = 0;
  if (iVar4 == 0) {
LAB_0043610f:
    if (iVar3 != 0) {
      dsp_alloc(iVar3 * 4,1);
      *piVar1 = extraout_EAX_00;
      if (extraout_EAX_00 == 0) goto LAB_0043612b;
    }
    iVar4 = 1;
  }
  else {
    dsp_alloc(iVar4 * 4,1);
    *(int *)(iVar2 + bank * 8 + 4) = extraout_EAX;
    if (extraout_EAX != 0) goto LAB_0043610f;
LAB_0043612b:
    iVar4 = 0;
  }
  if (iVar4 != 0) {
    dev_init_regbank(bank);
  }
  return iVar4;
}


/* ==== dev_init_regbank @ 00436150 ==== */

void __cdecl dev_init_regbank(int bank)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = *(int *)(cur_dev + 8);
  iVar4 = *(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + bank * 0x48);
  puVar1 = (undefined4 *)(*(int *)(cur_sim + 8) + bank * 8);
  *puVar1 = *(undefined4 *)(iVar4 + 0x20);
  iVar5 = 0;
  if (0 < *(int *)(iVar4 + 0x28)) {
    iVar6 = 0;
    do {
      iVar5 = iVar5 + 1;
      puVar2 = (undefined4 *)(*(int *)(iVar4 + 0x2c) + 0xc + iVar6);
      iVar6 = iVar6 + 0x1c;
      *(undefined4 *)(puVar1[1] + -4 + iVar5 * 4) = *puVar2;
    } while (iVar5 < *(int *)(iVar4 + 0x28));
  }
  if ((((*(int **)(cur_dtype + 0x4e0) == (int *)0x0) || (**(int **)(cur_dtype + 0x4e0) == 0)) ||
      (*(int *)(iVar4 + 0x3c) == 0)) && (iVar5 = 0, 0 < *(int *)(iVar4 + 0x24))) {
    do {
      iVar5 = iVar5 + 1;
      *(undefined4 *)(*(int *)(iVar3 + bank * 4) + -4 + iVar5 * 4) = 0;
    } while (iVar5 < *(int *)(iVar4 + 0x24));
  }
  return;
}


/* ==== dev_alloc_memmaps @ 004361f0 ==== */

int dev_alloc_memmaps(void)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  uint uVar3;
  int extraout_EAX_01;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = *(int *)(cur_dtype + 0x1c);
  if (iVar1 == 0) {
LAB_0043625a:
    uVar3 = 1;
  }
  else {
    dsp_alloc(iVar1 * 300,1);
    *(undefined4 *)(cur_sim + 4) = extraout_EAX;
    if (*(int *)(cur_sim + 4) != 0) {
      dsp_alloc(iVar1 << 4,1);
      *(undefined4 *)(cur_dev + 0xc) = extraout_EAX_00;
      if (*(int *)(cur_dev + 0xc) != 0) goto LAB_0043625a;
    }
    uVar3 = 0;
  }
  if (uVar3 != 0) {
    iVar5 = 0;
    if (0 < iVar1) {
      iVar4 = 0;
      iVar7 = 0;
      do {
        if (uVar3 == 0) {
          return 0;
        }
        iVar2 = *(int *)(*(int *)(cur_dtype + 0x20) + 0x14 + iVar7);
        iVar6 = *(int *)(cur_dev + 0xc) + iVar4;
        if (iVar2 == 0) {
          *(undefined4 *)(iVar6 + 8) = 0;
        }
        else {
          dsp_alloc(iVar2 * 4,0);
          uVar3 = (uint)(extraout_EAX_01 != 0);
          *(int *)(iVar6 + 8) = extraout_EAX_01;
        }
        iVar5 = iVar5 + 1;
        iVar7 = iVar7 + 0x2c;
        iVar4 = iVar4 + 0x10;
      } while (iVar5 < iVar1);
    }
    if ((uVar3 != 0) && (iVar1 != 0)) {
      dev_init_memmaps();
      uVar3 = mdisk_init();
    }
  }
  return uVar3;
}


/* ==== dev_init_memmaps @ 004362e0 ==== */

void dev_init_memmaps(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_c;
  int local_8;
  int local_4;
  
  local_4 = 0;
  if (0 < *(int *)(cur_dtype + 0x1c)) {
    local_8 = 0;
    local_c = 0;
    iVar5 = 0;
    do {
      iVar3 = *(int *)(cur_sim + 4);
      *(undefined4 *)(iVar3 + 0xc + iVar5) = 0;
      puVar1 = (undefined4 *)(iVar3 + iVar5);
      puVar1[4] = 0;
      puVar1[2] = 0;
      puVar1[1] = 0;
      *puVar1 = 0;
      puVar1[0x2a] = 0;
      puVar1[7] = 0;
      puVar1[0x29] = 0;
      puVar1[0x28] = 0;
      puVar1[6] = 0;
      puVar1[5] = 0;
      iVar3 = *(int *)(cur_dev + 0xc) + local_c;
      *(undefined4 *)(iVar3 + 0xc) = 0;
      if (*(int *)(iVar3 + 8) != 0) {
        iVar2 = *(int *)(cur_dtype + 0x20) + local_8;
        if (*(int *)(iVar2 + 0x1c) == 0) {
          iVar4 = 0;
          if (0 < *(int *)(iVar2 + 0x14)) {
            do {
              iVar4 = iVar4 + 1;
              *(undefined4 *)(*(int *)(iVar3 + 8) + -4 + iVar4 * 4) = 0;
            } while (iVar4 < *(int *)(iVar2 + 0x14));
          }
        }
        else {
          iVar4 = 0;
          if (0 < *(int *)(iVar2 + 0x14)) {
            do {
              *(undefined4 *)(*(int *)(iVar3 + 8) + iVar4 * 4) =
                   *(undefined4 *)(*(int *)(iVar2 + 0x1c) + iVar4 * 4);
              iVar4 = iVar4 + 1;
            } while (iVar4 < *(int *)(iVar2 + 0x14));
          }
        }
      }
      local_4 = local_4 + 1;
      iVar5 = iVar5 + 300;
      local_c = local_c + 0x10;
      local_8 = local_8 + 0x2c;
    } while (local_4 < *(int *)(cur_dtype + 0x1c));
  }
  return;
}


/* ==== dev_alloc_periph @ 004363e0 ==== */

int dev_alloc_periph(void)

{
  undefined4 extraout_EAX;
  int iVar1;
  
  if (*(int *)(cur_dtype + 0x30) != 0) {
    dsp_alloc(*(int *)(cur_dtype + 0x30) * 0x128,0);
    *(undefined4 *)(cur_dev + 0x18) = extraout_EAX;
    if (*(int *)(cur_dev + 0x18) == 0) {
      iVar1 = 0;
      goto LAB_00436420;
    }
  }
  iVar1 = 1;
LAB_00436420:
  if (iVar1 != 0) {
    dev_init_periph();
  }
  return iVar1;
}


/* ==== dev_init_periph @ 00436430 ==== */

void dev_init_periph(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar3 = *(undefined4 **)(cur_dev + 0x18);
  iVar1 = 0;
  if (0 < *(int *)(cur_dtype + 0x30)) {
    do {
      iVar1 = iVar1 + 1;
      puVar4 = &DAT_004dc148;
      puVar5 = puVar3;
      for (iVar2 = 0x4a; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = puVar3 + 0x4a;
    } while (iVar1 < *(int *)(cur_dtype + 0x30));
  }
  return;
}


/* ==== dev_reset @ 00436470 ==== */

void __cdecl dev_reset(int dev,int arg)

{
  cur_sim = *(int *)(dev_state_tab + dev * 4);
  cur_dev = *(int *)(dev_tab + dev * 4);
  if (cur_dev != 0) {
    dev_clear_memory(*(int *)(cur_dev + 4));
    dev_free_program_info();
    free_io_lists();
    break_list_free();
    if (*(void **)(cur_sim + 0x48) != (void *)0x0) {
      fclose(*(void **)(cur_sim + 0x48));
    }
    dev_state_init();
    if (0 < arg) {
      **(int **)(cur_dev + 0x40) = arg;
    }
  }
  return;
}


/* ==== dev_free_program_info @ 004364f0 ==== */

void dev_free_program_info(void)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = cur_sim;
  if (*(void **)(cur_sim + 0x3fdc) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x3fdc));
  }
  if (*(void **)(iVar2 + 0x3fe4) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x3fe4));
  }
  if (*(void **)(iVar2 + 0x3ff0) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x3ff0));
  }
  if (*(void **)(iVar2 + 0x4048) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4048));
  }
  if (*(void **)(iVar2 + 0x4014) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4014));
  }
  if (*(void **)(iVar2 + 0x4018) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4018));
  }
  if (*(void **)(iVar2 + 0x4038) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4038));
    *(undefined4 *)(iVar2 + 0x4038) = 0;
    *(undefined4 *)(iVar2 + 0x4034) = 0;
  }
  if (*(void **)(iVar2 + 0x4040) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4040));
    *(undefined4 *)(iVar2 + 0x4040) = 0;
    *(undefined4 *)(iVar2 + 0x403c) = 0;
  }
  iVar3 = 0;
  if (0 < *(int *)(iVar2 + 0x401c)) {
    iVar4 = 0;
    do {
      pvVar1 = *(void **)(iVar4 + 4 + *(int *)(iVar2 + 0x4020));
      if (pvVar1 != (void *)0x0) {
        dsp_free(pvVar1);
      }
      pvVar1 = *(void **)(iVar4 + 8 + *(int *)(iVar2 + 0x4020));
      if (pvVar1 != (void *)0x0) {
        free(pvVar1);
        *(undefined4 *)(iVar4 + 8 + *(int *)(iVar2 + 0x4020)) = 0;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar3 < *(int *)(iVar2 + 0x401c));
  }
  if (*(void **)(iVar2 + 0x4020) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4020));
  }
  if (*(void **)(iVar2 + 0x402c) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x402c));
  }
  if (*(void **)(iVar2 + 0x4030) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x4030));
  }
  if (*(void **)(iVar2 + 0x3fe0) != (void *)0x0) {
    dsp_free(*(void **)(iVar2 + 0x3fe0));
  }
  *(undefined4 *)(iVar2 + 0x3fd8) = 0;
  return;
}


/* ==== dev_clear_memory @ 00436620 ==== */

void __cdecl dev_clear_memory(int devtype_unused)

{
  free_memtags();
  dev_init_memmaps();
  mdisk_close(devtype_unused);
  return;
}


/* ==== free_memtags @ 00436640 ==== */

void free_memtags(void)

{
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_4;
  
  if (((cur_sim != 0) && (*(int *)(cur_sim + 4) != 0)) &&
     (local_4 = 0, 0 < *(int *)(cur_dtype + 0x1c))) {
    iVar3 = 0;
    do {
      puVar4 = (undefined4 *)(*(int *)(cur_sim + 4) + iVar3);
      pvVar2 = *(void **)(*(int *)(cur_sim + 4) + iVar3);
      while (pvVar2 != (void *)0x0) {
        pvVar1 = *(void **)((int)pvVar2 + 0xc);
        dsp_free(pvVar2);
        pvVar2 = pvVar1;
      }
      *puVar4 = 0;
      pvVar2 = (void *)puVar4[1];
      while (pvVar2 != (void *)0x0) {
        pvVar1 = *(void **)((int)pvVar2 + 0xc);
        dsp_free(pvVar2);
        pvVar2 = pvVar1;
      }
      puVar4[1] = 0;
      pvVar2 = (void *)puVar4[2];
      while (pvVar2 != (void *)0x0) {
        pvVar1 = *(void **)((int)pvVar2 + 0xc);
        dsp_free(pvVar2);
        pvVar2 = pvVar1;
      }
      puVar4[2] = 0;
      pvVar2 = (void *)puVar4[4];
      while (pvVar2 != (void *)0x0) {
        pvVar1 = *(void **)((int)pvVar2 + 0xc);
        dsp_free(pvVar2);
        pvVar2 = pvVar1;
      }
      puVar4[4] = 0;
      pvVar2 = (void *)puVar4[3];
      while (pvVar2 != (void *)0x0) {
        pvVar1 = *(void **)((int)pvVar2 + 0xc);
        dsp_free(pvVar2);
        pvVar2 = pvVar1;
      }
      puVar4[3] = 0;
      local_4 = local_4 + 1;
      iVar3 = iVar3 + 300;
    } while (local_4 < *(int *)(cur_dtype + 0x1c));
  }
  return;
}


/* ==== free_io_lists @ 00436730 ==== */

void free_io_lists(void)

{
  iolist_remove((void *)(cur_sim + 0x14c),&empty_str,1);
  iolist_remove((void *)(cur_sim + 0x150),&empty_str,1);
  iolist_remove((void *)(cur_sim + 0x154),&empty_str,1);
  iolist_remove((void *)(cur_sim + 0x158),&empty_str,1);
  return;
}


/* ==== dev_destroy @ 004367a0 ==== */

void __cdecl dev_destroy(int dev)

{
  int iVar1;
  void *p;
  void *pvVar2;
  int iVar3;
  int iVar4;
  
  if ((-1 < dev) && (dev < max_devices)) {
    iVar1 = dev * 4;
    cur_sim = *(void **)(dev_state_tab + iVar1);
    cur_dev = *(int **)(dev_tab + iVar1);
    if (cur_dev != (int *)0x0) {
      cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
      if ((*(int **)(cur_dtype + 0x4e0) != (int *)0x0) && (**(int **)(cur_dtype + 0x4e0) != 0)) {
        if ((void *)cur_dev[0x56] != (void *)0x0) {
          dsp_free((void *)cur_dev[0x56]);
        }
        (**(code **)(*(int *)(cur_dtype + 0x4e4) + 0x14))(dev);
      }
      if (*(int *)((int)cur_sim + 0x3fbc) != 0) {
        pvVar2 = *(void **)(*(int *)((int)cur_sim + 0x3fbc) + 8);
        if (pvVar2 != (void *)0x0) {
          dsp_free(pvVar2);
        }
        dsp_free(*(void **)((int)cur_sim + 0x3fbc));
      }
      if (*(void **)((int)cur_sim + 0x3fc8) != (void *)0x0) {
        dsp_free(*(void **)((int)cur_sim + 0x3fc8));
      }
      hio_buf_free((void *)((int)cur_sim + 0x4050));
      hio_buf_free((void *)((int)cur_sim + 0x4060));
      iVar4 = 0;
      pvVar2 = cur_sim;
      if (0 < *(int *)((int)cur_sim + 0x4088)) {
        iVar3 = 0;
        do {
          p = *(void **)(*(int *)((int)pvVar2 + 0x4080) + 4 + iVar3);
          if (p != (void *)0x0) {
            dsp_free(p);
            pvVar2 = cur_sim;
          }
          iVar4 = iVar4 + 1;
          iVar3 = iVar3 + 0x10;
        } while (iVar4 < *(int *)((int)pvVar2 + 0x4088));
      }
      dsp_free(*(void **)((int)pvVar2 + 0x4080));
      mdisk_free_all(dev);
      iVar4 = 0;
      if (0 < *(int *)(cur_dtype + 0x14)) {
        do {
          dev_free_regbank(iVar4);
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(cur_dtype + 0x14));
      }
      if (iVar4 != 0) {
        if ((void *)cur_dev[2] != (void *)0x0) {
          dsp_free((void *)cur_dev[2]);
        }
        if (*(void **)((int)cur_sim + 8) != (void *)0x0) {
          dsp_free(*(void **)((int)cur_sim + 8));
        }
      }
      if ((*(int *)(cur_dtype + 0x2c) != 0) && ((void *)cur_dev[0x10] != (void *)0x0)) {
        dsp_free((void *)cur_dev[0x10]);
      }
      if ((*(int *)(cur_dtype + 0x30) != 0) && ((void *)cur_dev[6] != (void *)0x0)) {
        dsp_free((void *)cur_dev[6]);
      }
      free_memtags();
      free_io_lists();
      dev_free_memmaps();
      if (*(int *)(cur_dtype + 0x1c) != 0) {
        if (*(void **)((int)cur_sim + 4) != (void *)0x0) {
          dsp_free(*(void **)((int)cur_sim + 4));
        }
        if ((void *)cur_dev[3] != (void *)0x0) {
          dsp_free((void *)cur_dev[3]);
        }
      }
      dev_free_program_info();
      break_list_free();
      if (*(void **)((int)cur_sim + 0x48) != (void *)0x0) {
        fclose(*(void **)((int)cur_sim + 0x48));
      }
      dsp_free(cur_sim);
      dsp_free(cur_dev);
    }
    *(undefined4 *)(dev_state_tab + iVar1) = 0;
    cur_sim = (void *)0x0;
    *(undefined4 *)(dev_tab + iVar1) = 0;
    cur_dev = (int *)0x0;
  }
  return;
}


/* ==== dev_free_regbank @ 00436a50 ==== */

void __cdecl dev_free_regbank(int bank)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  
  iVar2 = *(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + bank * 0x48);
  iVar3 = *(int *)(iVar2 + 0x24);
  if ((((*(int *)(iVar2 + 0x28) != 0) && (cur_sim != 0)) && (*(int *)(cur_sim + 8) != 0)) &&
     ((iVar2 = *(int *)(cur_sim + 8) + bank * 8, iVar2 != 0 &&
      (pvVar4 = *(void **)(iVar2 + 4), pvVar4 != (void *)0x0)))) {
    dsp_free(pvVar4);
  }
  if (((iVar3 != 0) && (cur_dev != 0)) &&
     ((*(int *)(cur_dev + 8) != 0 &&
      ((puVar1 = (undefined4 *)(*(int *)(cur_dev + 8) + bank * 4), puVar1 != (undefined4 *)0x0 &&
       (pvVar4 = (void *)*puVar1, pvVar4 != (void *)0x0)))))) {
    dsp_free(pvVar4);
  }
  return;
}


/* ==== dev_free_memmaps @ 00436ad0 ==== */

void dev_free_memmaps(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (((cur_dev != 0) && (*(int *)(cur_dev + 0xc) != 0)) &&
     (iVar3 = 0, 0 < *(int *)(cur_dtype + 0x1c))) {
    iVar4 = 0;
    puVar2 = (undefined4 *)(*(int *)(cur_dev + 0xc) + 8);
    iVar1 = cur_dtype;
    do {
      if ((*(int *)(*(int *)(iVar1 + 0x20) + 0x14 + iVar4) != 0) && ((void *)*puVar2 != (void *)0x0)
         ) {
        dsp_free((void *)*puVar2);
        iVar1 = cur_dtype;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x2c;
      puVar2 = puVar2 + 4;
    } while (iVar3 < *(int *)(iVar1 + 0x1c));
  }
  return;
}


/* ==== chip_reset_regs @ 00436b30 ==== */

int __cdecl chip_reset_regs(int mode,long arg)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  uVar1 = *(undefined4 *)(cur_dev + 0x158);
  iVar2 = *(int *)(cur_dtype + 0x14);
  if (0 < iVar2) {
    iVar6 = 0;
    do {
      iVar3 = *(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar6);
      iVar4 = *(int *)(iVar3 + 0x3c);
      if (((*(int **)(cur_dtype + 0x4e0) == (int *)0x0) || (**(int **)(cur_dtype + 0x4e0) == 0)) ||
         (iVar4 == 0)) {
        (**(code **)(iVar3 + 0x14))(iVar5,mode,arg);
      }
      else {
        (**(code **)(iVar4 + 0x18))(uVar1,iVar5);
      }
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 0x48;
    } while (iVar5 < iVar2);
  }
  return 0;
}


/* ==== dev_state_init @ 00436bb0 ==== */

void dev_state_init(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_EAX;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  char *pcVar10;
  void *unaff_EDI;
  char *pcVar11;
  
  puVar8 = (undefined4 *)(cur_sim + 0xc);
  for (iVar4 = 0xf0b; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined4 *)(cur_sim + 0x30) = 1;
  *(undefined4 *)(cur_sim + 0x3e78) = 0;
  *(undefined4 *)(cur_sim + 0x3c38) = 0;
  *(undefined4 *)(cur_sim + 0x3fa8) = 0;
  *(undefined4 *)(cur_sim + 0x3e88) = 0;
  *(undefined4 *)(cur_sim + 0x3fac) = 0;
  *(undefined4 *)(cur_sim + 0x3fb4) = 0;
  *(undefined4 *)(cur_sim + 0x3fb0) = 0;
  *(undefined4 *)(cur_sim + 0x404c) = 1;
  hio_buf_clear((void *)(cur_sim + 0x4050));
  hio_buf_clear((void *)(cur_sim + 0x4060));
  *(undefined4 *)(cur_sim + 0x4074) = 0;
  *(undefined4 *)(cur_sim + 0x4070) = 0;
  *(undefined4 *)(cur_sim + 0x407c) = 0;
  *(undefined4 *)(cur_sim + 0x4078) = 0;
  *(undefined4 *)(cur_sim + 0x408c) = 0;
  *(undefined4 *)(cur_sim + 0x4098) = 0;
  *(undefined1 *)(cur_sim + 0x40a4) = 0;
  *(undefined4 *)(cur_sim + 0x4090) = 0;
  *(undefined4 *)(cur_sim + 0x409c) = 0;
  *(undefined1 *)(cur_sim + 0x41a4) = 0;
  *(undefined4 *)(cur_sim + 0x4094) = 0;
  iVar4 = 0x43a4;
  *(undefined4 *)(cur_sim + 0x40a0) = 0;
  *(undefined1 *)(cur_sim + 0x42a4) = 0;
  do {
    iVar4 = iVar4 + 4;
    *(undefined4 *)(cur_sim + -4 + iVar4) = 1;
  } while (iVar4 < 0x43b0);
  iVar4 = 0x43b0;
  do {
    iVar4 = iVar4 + 4;
    *(undefined4 *)(cur_sim + -4 + iVar4) = 0;
  } while (iVar4 < 0x43f4);
  *(undefined4 *)(cur_sim + 0x43f4) = 0;
  *(undefined4 *)(cur_sim + 0x4084) = 3;
  *(undefined4 *)(cur_sim + 0x4088) = 3;
  if (*(void **)(cur_sim + 0x4080) != (void *)0x0) {
    dsp_free(*(void **)(cur_sim + 0x4080));
  }
  dsp_alloc(*(int *)(cur_sim + 0x4088) << 4,0);
  *(undefined4 *)(cur_sim + 0x4080) = extraout_EAX;
  puVar8 = *(undefined4 **)(cur_sim + 0x4080);
  if (puVar8 != (undefined4 *)0x0) {
    *puVar8 = 0;
    puVar8[1] = 0;
    puVar8[3] = 0;
    puVar8[2] = 0;
    puVar8[4] = 1;
    puVar8[5] = 0;
    puVar8[7] = 0;
    puVar8[6] = 0;
    puVar8[8] = 2;
    puVar8[9] = 0;
    puVar8[0xb] = 0;
    puVar8[10] = 0;
  }
  *(undefined4 *)(cur_sim + 0x3fc4) = 0;
  *(undefined4 *)(cur_sim + 0x3fc0) = 0;
  *(undefined4 *)(cur_sim + 0x4400) = 0;
  *(undefined4 *)(cur_sim + 0x4404) = 0;
  cdb_detect_space_model();
  cdb_arch_init();
  iVar4 = 0;
  puVar8 = (undefined4 *)(cur_sim + 0x3fcc);
  for (iVar5 = 0x20; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  if (0 < *(int *)(cur_dtype + 0x2c)) {
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)(cur_dev + 0x40) + -4 + iVar4 * 4) = 0;
    } while (iVar4 < *(int *)(cur_dtype + 0x2c));
  }
  iVar4 = 0;
  if (0 < *(int *)(cur_dtype + 0x14)) {
    do {
      dev_init_regbank(iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(cur_dtype + 0x14));
  }
  if (gui_mode == 0) {
    uVar6 = 0xffffffff;
    pcVar10 = &DAT_004c551c;
    do {
      pcVar11 = pcVar10;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar11 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar11;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar10 = pcVar11 + -uVar6;
    pcVar11 = (char *)(cur_dev + 0x58);
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar11 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar11 = pcVar11 + 1;
    }
  }
  else {
    dsp_free_ext(unaff_EDI);
  }
  *(undefined4 *)(*(int *)(cur_sim + 0x3fbc) + 4) = 0;
  **(undefined4 **)(cur_sim + 0x3fbc) = 0;
  iVar4 = 0;
  if (0 < scrollback_lines) {
    iVar5 = 0;
    do {
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 0x100;
      *(undefined1 *)(*(int *)(*(int *)(cur_sim + 0x3fbc) + 8) + -0x100 + iVar5) = 0;
    } while (iVar4 < scrollback_lines);
  }
  cursor_row = text_rows;
  puVar8 = *(undefined4 **)(cur_dtype + 0x34);
  puVar3 = *(undefined4 **)(cur_dev + 0x18);
  iVar4 = 0;
  if (0 < *(int *)(cur_dtype + 0x30)) {
    do {
      uVar2 = puVar8[1];
      iVar5 = 0x20;
      puVar3[0x26] = uVar2;
      puVar3[1] = uVar2;
      uVar2 = *puVar8;
      puVar3[0x25] = uVar2;
      *puVar3 = uVar2;
      uVar2 = puVar8[3];
      puVar3[0x28] = uVar2;
      puVar3[3] = uVar2;
      uVar2 = puVar8[2];
      puVar3[0x27] = uVar2;
      puVar3[2] = uVar2;
      uVar2 = puVar8[4];
      puVar3[0x29] = uVar2;
      puVar3[4] = uVar2;
      puVar9 = puVar3 + 5;
      do {
        puVar9[0x25] = 0;
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 0x4a;
      puVar8 = puVar8 + 0x25;
    } while (iVar4 < *(int *)(cur_dtype + 0x30));
  }
  chip_reset_regs(1,*(long *)(cur_dtype + 0x10));
  *(undefined4 *)(*(int *)(cur_dev + 0x40) + 8) = 0;
  periph_reset();
  return;
}


/* ==== load_state @ 00436f90 ==== */

int __cdecl load_state(char *filename)

{
  int iVar1;
  void *listp;
  byte bVar2;
  void *stream;
  int iVar3;
  void *va0;
  undefined4 extraout_EAX;
  int va0_00;
  int extraout_EAX_00;
  byte *va0_01;
  int extraout_EAX_01;
  undefined4 extraout_EAX_02;
  int iVar4;
  undefined4 extraout_EAX_03;
  uint *puVar5;
  undefined4 extraout_EAX_04;
  undefined4 extraout_EAX_05;
  undefined1 *puVar6;
  int extraout_EAX_06;
  int extraout_EAX_07;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  bool bVar11;
  uint local_3c8;
  int local_3c4;
  ulong uStack_3c0;
  int local_3bc;
  uint local_3b8;
  int iStack_3b4;
  int local_3b0;
  int local_3ac;
  undefined4 uStack_3a8;
  int local_3a4;
  int local_3a0;
  undefined4 uStack_39c;
  long lStack_398;
  undefined4 uStack_394;
  long lStack_390;
  int iStack_38c;
  undefined4 uStack_388;
  undefined2 auStack_384 [2];
  undefined4 uStack_380;
  undefined2 auStack_37c [2];
  undefined2 auStack_378 [2];
  int iStack_374;
  undefined2 auStack_370 [2];
  undefined1 auStack_36c [4];
  undefined1 local_368 [256];
  byte abStack_268 [256];
  char local_168 [52];
  char local_134 [52];
  char local_100 [256];
  
  local_3ac = 0;
  fopen(filename,&DAT_004c5574);
  if (((stream == (void *)0x0) || (iVar3 = fscanf(stream,&DAT_004c5c10,&local_3c8), iVar3 == 0)) ||
     (local_3c8 != 0x2c7)) {
    return 1;
  }
  fscanf(stream,s________004c5c04,local_368);
  fscanf(stream,s________004c5c04,local_368);
  iVar3 = fscanf(stream,&DAT_004c5bfc,&local_3c8);
  local_3bc = iVar3;
  if (iVar3 != 0) {
    if (source_path_list != (void *)0x0) {
      dsp_free(source_path_list);
      source_path_list = (void *)0x0;
    }
    if (local_3c8 == 0) {
      fscanf(stream,s_________004c5be4);
    }
    else {
      dsp_alloc(local_3c8 + 1,0);
      source_path_list = va0;
      if ((va0 == (void *)0x0) || (iVar3 = fscanf(stream,s________004c5bf0,va0), iVar3 == 0)) {
        iVar3 = 0;
        local_3bc = 0;
      }
      else {
        iVar3 = 1;
        local_3bc = 1;
      }
    }
  }
  fscanf(stream,s________004c5c04,local_368);
  fscanf(stream,&DAT_004c5be0,local_100);
  if ((profiler_hook != (undefined *)0x0) && (local_100[0] == '(')) {
    local_100[0] = '\0';
  }
  fscanf(stream,s________004c5c04,local_368);
  fscanf(stream,&DAT_004c5c10,&local_3a0);
  local_3a4 = 0;
  if (0 < local_3a0) {
    do {
      iVar3 = 0;
      if (local_3bc == 0) break;
      fscanf(stream,s________004c5c04,local_368);
      iVar3 = fscanf(stream,s__d__d_004c5bd8,&local_3c8,&local_3b0);
      if ((iVar3 == 0) || (num_chiptypes <= local_3b0)) {
        iVar3 = 0;
      }
      else {
        iVar3 = 1;
      }
      if (((int)local_3c8 < 0) || (max_devices <= (int)local_3c8)) {
        iVar3 = 0;
        local_3b8 = 0;
        local_3bc = 0;
      }
      else {
        local_3b8 = local_3c8;
        local_3bc = iVar3;
        dev_destroy(local_3c8);
      }
      if ((iVar3 != 0) && (local_3b0 == -2)) {
        iVar3 = fscanf(stream,s________004c5bf0,local_134);
        if ((iVar3 == 0) ||
           (((iVar3 = fscanf(stream,s________004c5bf0,local_168), iVar3 == 0 ||
             (local_3b0 = devtype_find(local_134,local_168), local_3b0 < 0)) ||
            (num_chiptypes <= local_3b0)))) {
          iVar3 = 0;
          local_3bc = iVar3;
        }
        else {
          iVar3 = 1;
          local_3bc = iVar3;
        }
      }
      if (((-1 < local_3b0) && (local_3b0 < num_chiptypes)) &&
         (*(int *)(chiptype_tab + local_3b0 * 4) == 0)) {
        iVar3 = 0;
        local_3bc = 0;
      }
      if ((-1 < local_3b0) && (iVar3 != 0)) {
        local_3bc = dev_create(local_3b8,(char *)**(undefined4 **)(chiptype_tab + local_3b0 * 4));
        cur_sim = *(int *)(dev_state_tab + local_3b8 * 4);
        cur_dev = *(int **)(dev_tab + local_3b8 * 4);
        cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
        if (local_3bc != 0) {
          local_3c8 = 0;
          if (0 < *(int *)(cur_dtype + 0x14)) {
            do {
              iVar4 = cur_dev[2];
              iVar3 = local_3c8 * 4;
              fscanf(stream,s________004c5c04,local_368);
              iVar1 = *(int *)(cur_sim + 8) + local_3c8 * 8;
              fscanf(stream,&DAT_004c575c,iVar1);
              fscanf(stream,s________004c5c04,local_368);
              local_3c4 = 0;
              if (0 < *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + local_3c8 * 0x48) + 0x28
                              )) {
                do {
                  fscanf(stream,&DAT_004c575c,*(int *)(iVar1 + 4) + local_3c4 * 4);
                  local_3c4 = local_3c4 + 1;
                } while (local_3c4 <
                         *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + local_3c8 * 0x48) +
                                 0x28));
              }
              fscanf(stream,s________004c5c04,local_368);
              local_3c4 = 0;
              if (0 < *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + local_3c8 * 0x48) + 0x24
                              )) {
                do {
                  fscanf(stream,&DAT_004c575c,*(int *)(iVar4 + iVar3) + local_3c4 * 4);
                  local_3c4 = local_3c4 + 1;
                } while (local_3c4 <
                         *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + local_3c8 * 0x48) +
                                 0x24));
              }
              local_3c8 = local_3c8 + 1;
            } while ((int)local_3c8 < *(int *)(cur_dtype + 0x14));
          }
          if (*(code **)(cur_dtype + 0x4e8) != (code *)0x0) {
            (**(code **)(cur_dtype + 0x4e8))();
          }
          local_3c8 = 0;
          if (0 < *(int *)(cur_dtype + 0x1c)) {
            do {
              listp = (void *)(*(int *)(cur_sim + 4) + local_3c8 * 300);
              iVar3 = local_3c8 * 0x10 + cur_dev[3];
              fscanf(stream,s________004c5c04,local_368);
              fscanf(stream,&DAT_004c575c,iVar3 + 0xc);
              fscanf(stream,s________004c5c04,local_368);
              local_3c4 = 0;
              if (0 < *(int *)(*(int *)(cur_dtype + 0x20) + 0x14 + local_3c8 * 0x2c)) {
                do {
                  fscanf(stream,&DAT_004c575c,*(int *)(iVar3 + 8) + local_3c4 * 4);
                  local_3c4 = local_3c4 + 1;
                } while (local_3c4 < *(int *)(*(int *)(cur_dtype + 0x20) + 0x14 + local_3c8 * 0x2c))
                ;
              }
              fscanf(stream,s________004c5c04,local_368);
              load_maplist(listp,stream);
              load_maplist((void *)((int)listp + 8),stream);
              load_maplist((void *)((int)listp + 0x10),stream);
              load_maplist((void *)((int)listp + 0xc),stream);
              local_3c8 = local_3c8 + 1;
            } while ((int)local_3c8 < *(int *)(cur_dtype + 0x1c));
          }
          fscanf(stream,s________004c5c04,local_368);
          local_3c8 = 0;
          if (0 < *(int *)(cur_dtype + 0x2c)) {
            do {
              fscanf(stream,&DAT_004c575c,cur_dev[0x10] + local_3c8 * 4);
              local_3c8 = local_3c8 + 1;
            } while ((int)local_3c8 < *(int *)(cur_dtype + 0x2c));
          }
          fscanf(stream,s________004c5c04,local_368);
          local_3c8 = 0;
          if (0 < *(int *)(cur_dtype + 0x30)) {
            do {
              iVar3 = cur_dev[6] + local_3c8 * 0x128;
              fscanf(stream,s__lx__lx__lx__lx__lx__lx__lx__lx___004c5bac,iVar3,iVar3 + 4,iVar3 + 8,
                     iVar3 + 0xc,iVar3 + 0x10,iVar3 + 0x94,iVar3 + 0x98,iVar3 + 0x9c,iVar3 + 0xa0,
                     iVar3 + 0xa4);
              fscanf(stream,s________004c5c04,local_368);
              local_3c4 = 0;
              do {
                fscanf(stream,s__lx_004c5ba4,iVar3 + 0x14 + local_3c4 * 4);
                local_3c4 = local_3c4 + 1;
              } while (local_3c4 < 0x20);
              fscanf(stream,s________004c5c04,local_368);
              local_3c4 = 0;
              do {
                fscanf(stream,s__lx_004c5ba4,iVar3 + 0xa8 + local_3c4 * 4);
                local_3c4 = local_3c4 + 1;
              } while (local_3c4 < 0x20);
              local_3c8 = local_3c8 + 1;
            } while ((int)local_3c8 < *(int *)(cur_dtype + 0x30));
          }
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,s__lx__lx__lx__d__d_004c5b90,cur_dev + 7,cur_dev + 8,cur_dev + 9,
                 cur_dev + 0x11,cur_dev + 0x12);
          fscanf(stream,s________004c5c04,local_368);
          iVar3 = cur_sim;
          fscanf(stream,s__d__d__lx__lx__d__d__d__d__lx__d_004c5b5c,cur_sim + 0x3c34,cur_sim + 0x184
                 ,cur_sim + 0xc,cur_sim + 0x10,cur_sim + 0x18,cur_sim + 0x1c,cur_sim + 0x20,
                 cur_sim + 0x24,cur_sim + 0x28,cur_sim + 0x2c,cur_sim + 0x30,cur_sim + 0x34,
                 cur_sim + 0x40,cur_sim + 0x44,&iStack_38c);
          fscanf(stream,s_______004c5b54,abStack_268);
          uVar7 = 0xffffffff;
          pbVar9 = abStack_268 + 1;
          do {
            pbVar10 = pbVar9;
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            pbVar10 = pbVar9 + 1;
            bVar2 = *pbVar9;
            pbVar9 = pbVar10;
          } while (bVar2 != 0);
          uVar7 = ~uVar7;
          pbVar9 = pbVar10 + -uVar7;
          pbVar10 = (byte *)(iVar3 + 0x4c);
          for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
            pbVar9 = pbVar9 + 4;
            pbVar10 = pbVar10 + 4;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *pbVar10 = *pbVar9;
            pbVar9 = pbVar9 + 1;
            pbVar10 = pbVar10 + 1;
          }
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,s_______004c5b54,abStack_268);
          uVar7 = 0xffffffff;
          pbVar9 = abStack_268 + 1;
          do {
            pbVar10 = pbVar9;
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            pbVar10 = pbVar9 + 1;
            bVar2 = *pbVar9;
            pbVar9 = pbVar10;
          } while (bVar2 != 0);
          uVar7 = ~uVar7;
          pbVar9 = pbVar10 + -uVar7;
          pbVar10 = (byte *)(cur_dev + 0x16);
          for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(int *)pbVar10 = *(int *)pbVar9;
            pbVar9 = pbVar9 + 4;
            pbVar10 = pbVar10 + 4;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *pbVar10 = *pbVar9;
            pbVar9 = pbVar9 + 1;
            pbVar10 = pbVar10 + 1;
          }
          if (iStack_38c != 0) {
            fopen((char *)(iVar3 + 0x4c),&DAT_004c5b50);
            *(undefined4 *)(iVar3 + 0x48) = extraout_EAX;
          }
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,s__lx__lx__lx__lx__lx__d__d_004c5b34,iVar3 + 0x15c,iVar3 + 0x160,
                 iVar3 + 0x164,iVar3 + 0x168,cur_sim + 0x3fc0,cur_sim + 0x3fc4,&uStack_394);
          *(undefined4 *)(cur_sim + 0x4400) = uStack_394;
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,&DAT_004c5bfc,&local_3c4);
          local_3c8 = 0;
          if (0 < local_3c4) {
            do {
              fscanf(stream,&DAT_004c575c,&uStack_380);
              if ((int)local_3c8 < history_size) {
                *(undefined4 *)(*(int *)(cur_sim + 0x3fc8) + local_3c8 * 0x2c) = uStack_380;
              }
              iVar3 = 0;
              do {
                fscanf(stream,&DAT_004c575c,&uStack_39c);
                if ((int)local_3c8 < history_size) {
                  *(undefined4 *)(*(int *)(cur_sim + 0x3fc8) + 4 + (iVar3 + local_3c8 * 0xb) * 4) =
                       uStack_39c;
                }
                iVar3 = iVar3 + 1;
              } while (iVar3 < 10);
              local_3c8 = local_3c8 + 1;
            } while ((int)local_3c8 < local_3c4);
          }
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,&DAT_004c5c10,&local_3c8);
          fscanf(stream,s________004c5c04,local_368);
          iStack_3b4 = cur_sim + 0x3c38;
          for (; 0 < (int)local_3c8; local_3c8 = local_3c8 - 1) {
            dsp_alloc(0x250,1);
            if (va0_00 == 0) {
              local_3bc = 0;
              break;
            }
            *(int *)(iStack_3b4 + 0x240) = va0_00;
            fscanf(stream,s__d__d__d__d_004c5b24,va0_00,va0_00 + 4,va0_00 + 8,va0_00 + 0xc);
            fscanf(stream,s_______004c5b54,abStack_268);
            uVar7 = 0xffffffff;
            pbVar9 = abStack_268 + 1;
            do {
              pbVar10 = pbVar9;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pbVar10 = pbVar9 + 1;
              bVar2 = *pbVar9;
              pbVar9 = pbVar10;
            } while (bVar2 != 0);
            uVar7 = ~uVar7;
            pbVar9 = pbVar10 + -uVar7;
            pbVar10 = (byte *)(va0_00 + 0x10);
            for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
              pbVar9 = pbVar9 + 4;
              pbVar10 = pbVar10 + 4;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pbVar10 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              pbVar10 = pbVar10 + 1;
            }
            fscanf(stream,s_______004c5b54,abStack_268);
            uVar7 = 0xffffffff;
            pbVar9 = abStack_268 + 1;
            do {
              pbVar10 = pbVar9;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pbVar10 = pbVar9 + 1;
              bVar2 = *pbVar9;
              pbVar9 = pbVar10;
            } while (bVar2 != 0);
            uVar7 = ~uVar7;
            pbVar9 = pbVar10 + -uVar7;
            pbVar10 = (byte *)(va0_00 + 0x110);
            for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
              pbVar9 = pbVar9 + 4;
              pbVar10 = pbVar10 + 4;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pbVar10 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              pbVar10 = pbVar10 + 1;
            }
            fscanf(stream,s__d__lx__lx__lx__d__d__d__d_004c5b08,va0_00 + 0x210,va0_00 + 0x220,
                   va0_00 + 0x224,va0_00 + 0x228,auStack_378,auStack_384,auStack_370,auStack_37c);
            *(undefined2 *)(va0_00 + 0x238) = auStack_378[0];
            *(undefined2 *)(va0_00 + 0x23a) = auStack_384[0];
            *(undefined2 *)(va0_00 + 0x23c) = auStack_370[0];
            *(undefined2 *)(va0_00 + 0x23e) = auStack_37c[0];
            if (*(int *)(va0_00 + 4) == 0xc) {
              load_expr_tree(stream);
              *(int *)(va0_00 + 0x244) = extraout_EAX_00;
              if (extraout_EAX_00 != 0) {
                fscanf(stream,s__d__d_004c5b00,va0_00 + 0x248,va0_00 + 0x24c);
              }
            }
            iStack_3b4 = *(int *)(iStack_3b4 + 0x240);
          }
          *(undefined4 *)(iStack_3b4 + 0x240) = 0;
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,&DAT_004c5bfc,&local_3c8);
          iStack_3b4 = cur_sim + 0x3e88;
          iVar3 = cur_sim;
          for (; cur_sim = iVar3, 0 < (int)local_3c8; local_3c8 = local_3c8 - 1) {
            dsp_alloc(0x124,0);
            if (va0_01 == (byte *)0x0) {
              return 1;
            }
            *(byte **)(iStack_3b4 + 0x120) = va0_01;
            va0_01[0x120] = 0;
            va0_01[0x121] = 0;
            va0_01[0x122] = 0;
            va0_01[0x123] = 0;
            fscanf(stream,&DAT_004c5af8,va0_01);
            fscanf(stream,s_______004c5b54,abStack_268);
            uVar7 = 0xffffffff;
            pbVar9 = abStack_268 + 1;
            do {
              pbVar10 = pbVar9;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pbVar10 = pbVar9 + 1;
              bVar2 = *pbVar9;
              pbVar9 = pbVar10;
            } while (bVar2 != 0);
            uVar7 = ~uVar7;
            pbVar10 = pbVar10 + -uVar7;
            pbVar9 = va0_01;
            for (uVar8 = uVar7 >> 2; pbVar9 = pbVar9 + 4, uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pbVar9 = *(undefined4 *)pbVar10;
              pbVar10 = pbVar10 + 4;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pbVar9 = *pbVar10;
              pbVar10 = pbVar10 + 1;
              pbVar9 = pbVar9 + 1;
            }
            fscanf(stream,s__d__d__lu__lu_004c5ae8,&iStack_374,va0_01 + 0x108,va0_01 + 0x10c,
                   va0_01 + 0x110);
            *(int *)(va0_01 + 0x104) = iStack_374;
            if (iStack_374 == 0) {
              load_expr_tree(stream);
              *(int *)(va0_01 + 0x114) = extraout_EAX_01;
              if (extraout_EAX_01 != 0) {
                fscanf(stream,s__d__d_004c5b00,va0_01 + 0x11c,va0_01 + 0x118);
              }
            }
            iStack_3b4 = *(int *)(iStack_3b4 + 0x120);
            iVar3 = cur_sim;
          }
          iVar1 = iVar3 + 0x404c;
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,&DAT_004c5bfc,iVar1);
          fscanf(stream,s________004c5c04,local_368);
          if (*(int *)(iVar3 + 0x405c) != 0) {
            hio_buf_free((void *)(iVar3 + 0x4050));
          }
          fscanf(stream,s__d__lu__lu_004c5ad8,(void *)(iVar3 + 0x4050),iVar3 + 0x4054,&uStack_3c0);
          *(ulong *)(iVar3 + 0x4058) = uStack_3c0;
          hio_buf_alloc((void *)(iVar3 + 0x4050),uStack_3c0);
          local_3c8 = 0;
          if (uStack_3c0 != 0) {
            do {
              fscanf(stream,s__ld_004c5ad0,*(int *)(iVar3 + 0x405c) + local_3c8 * 4);
              local_3c8 = local_3c8 + 1;
            } while (local_3c8 < uStack_3c0);
          }
          fscanf(stream,s________004c5c04,local_368);
          if (*(int *)(iVar3 + 0x406c) != 0) {
            hio_buf_free((void *)(iVar3 + 0x4060));
          }
          fscanf(stream,s__d__lu__lu_004c5ad8,(void *)(iVar3 + 0x4060),iVar3 + 0x4064,&uStack_3c0);
          *(ulong *)(iVar3 + 0x4068) = uStack_3c0;
          hio_buf_alloc((void *)(iVar3 + 0x4060),uStack_3c0);
          local_3c8 = 0;
          if (uStack_3c0 != 0) {
            do {
              fscanf(stream,s__ld_004c5ad0,*(int *)(iVar3 + 0x406c) + local_3c8 * 4);
              local_3c8 = local_3c8 + 1;
            } while (local_3c8 < uStack_3c0);
          }
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,s__d__ld_004c5ac4,&uStack_3a8,iVar3 + 0x4070);
          *(undefined4 *)(iVar3 + 0x4074) = uStack_3a8;
          fscanf(stream,s__d__ld_004c5ac4,&uStack_3a8,iVar3 + 0x4078);
          *(undefined4 *)(iVar3 + 0x407c) = uStack_3a8;
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,s__ld__d_004c5ab8,&uStack_3c0,iVar3 + 0x4084);
          *(ulong *)(iVar3 + 0x4088) = uStack_3c0;
          if (*(void **)(iVar3 + 0x4080) != (void *)0x0) {
            dsp_free(*(void **)(iVar3 + 0x4080));
          }
          if (uStack_3c0 == 0) {
            *(undefined4 *)(iVar3 + 0x4080) = 0;
          }
          else {
            dsp_alloc(uStack_3c0 << 4,0);
            *(undefined4 *)(iVar3 + 0x4080) = extraout_EAX_02;
          }
          local_3c8 = 0;
          if (uStack_3c0 != 0) {
            do {
              iVar4 = local_3c8 * 0x10 + *(int *)(iVar3 + 0x4080);
              fscanf(stream,s__d__d_004c5b00,iVar4 + 8,iVar4 + 0xc);
              fscanf(stream,s_______004c5ab0,abStack_268);
              pbVar10 = &DAT_004c5aac;
              pbVar9 = abStack_268;
              do {
                bVar2 = *pbVar9;
                bVar11 = bVar2 < *pbVar10;
                if (bVar2 != *pbVar10) {
LAB_00437e75:
                  iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
                  goto LAB_00437e7a;
                }
                if (bVar2 == 0) break;
                bVar2 = pbVar9[1];
                bVar11 = bVar2 < pbVar10[1];
                if (bVar2 != pbVar10[1]) goto LAB_00437e75;
                pbVar9 = pbVar9 + 2;
                pbVar10 = pbVar10 + 2;
              } while (bVar2 != 0);
              iVar4 = 0;
LAB_00437e7a:
              if (iVar4 == 0) {
                *(undefined4 *)(local_3c8 * 0x10 + 4 + *(int *)(iVar3 + 0x4080)) = 0;
              }
              else {
                uVar7 = 0xffffffff;
                pbVar9 = abStack_268;
                do {
                  if (uVar7 == 0) break;
                  uVar7 = uVar7 - 1;
                  bVar2 = *pbVar9;
                  pbVar9 = pbVar9 + 1;
                } while (bVar2 != 0);
                dsp_alloc(~uVar7 - 1,0);
                *(undefined4 *)(local_3c8 * 0x10 + 4 + *(int *)(iVar3 + 0x4080)) = extraout_EAX_03;
                uVar7 = 0xffffffff;
                iStack_3b4 = local_3c8 * 0x10;
                pbVar9 = abStack_268 + 1;
                do {
                  pbVar10 = pbVar9;
                  if (uVar7 == 0) break;
                  uVar7 = uVar7 - 1;
                  pbVar10 = pbVar9 + 1;
                  bVar2 = *pbVar9;
                  pbVar9 = pbVar10;
                } while (bVar2 != 0);
                uVar7 = ~uVar7;
                pbVar9 = pbVar10 + -uVar7;
                pbVar10 = *(byte **)(iStack_3b4 + 4 + *(int *)(iVar3 + 0x4080));
                for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                  *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
                  pbVar9 = pbVar9 + 4;
                  pbVar10 = pbVar10 + 4;
                }
                for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                  *pbVar10 = *pbVar9;
                  pbVar9 = pbVar9 + 1;
                  pbVar10 = pbVar10 + 1;
                }
              }
              fscanf(stream,s__ld_004c5ad0,&lStack_398);
              puVar5 = (uint *)(*(int *)(iVar3 + 0x4080) + local_3c8 * 0x10);
              if ((char *)puVar5[1] == (char *)0x0) {
                *puVar5 = local_3c8;
              }
              else {
                iVar4 = _open((char *)puVar5[1],puVar5[2] & 0xfffffdff,puVar5[3]);
                *(int *)(local_3c8 * 0x10 + *(int *)(iVar3 + 0x4080)) = iVar4;
                iVar4 = *(int *)(local_3c8 * 0x10 + *(int *)(iVar3 + 0x4080));
                if (iVar4 != -1) {
                  _lseek(iVar4,lStack_398,0);
                }
              }
              local_3c8 = local_3c8 + 1;
            } while (local_3c8 < uStack_3c0);
          }
          fscanf(stream,s________004c5c04,local_368);
          local_3c8 = 0;
          do {
            fscanf(stream,&DAT_004c5bfc,iVar3 + 0x408c + local_3c8 * 4);
            fscanf(stream,s_______004c5ab0,abStack_268);
            fscanf(stream,s__ld_004c5ad0,&lStack_390);
            uVar7 = 0xffffffff;
            pbVar9 = abStack_268 + 1;
            do {
              pbVar10 = pbVar9;
              if (uVar7 == 0) break;
              uVar7 = uVar7 - 1;
              pbVar10 = pbVar9 + 1;
              bVar2 = *pbVar9;
              pbVar9 = pbVar10;
            } while (bVar2 != 0);
            uVar7 = ~uVar7;
            pbVar9 = pbVar10 + -uVar7;
            pbVar10 = (byte *)(local_3c8 * 0x100 + 0x58 + iVar1);
            for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
              pbVar9 = pbVar9 + 4;
              pbVar10 = pbVar10 + 4;
            }
            for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
              *pbVar10 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              pbVar10 = pbVar10 + 1;
            }
            if (*(char *)(local_3c8 * 0x100 + 0x58 + iVar1) != '\0') {
              if (local_3c8 == 0) {
                fopen((char *)(iVar3 + 0x40a4),&DAT_004c5574);
                *(undefined4 *)(iVar3 + 0x4098 + local_3c8 * 4) = extraout_EAX_04;
              }
              else {
                fopen((char *)(local_3c8 * 0x100 + 0x58 + iVar1),&DAT_004b29b4);
                *(undefined4 *)(iVar3 + 0x4098 + local_3c8 * 4) = extraout_EAX_05;
              }
              fseek(*(void **)(iVar3 + 0x4098 + local_3c8 * 4),lStack_390,0);
            }
            local_3c8 = local_3c8 + 1;
          } while ((int)local_3c8 < 3);
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,s__ld_004c5ad0,&uStack_3c0);
          local_3c8 = 0;
          if (uStack_3c0 != 0) {
            do {
              puVar6 = (undefined1 *)(iVar3 + 0x43a4 + local_3c8 * 4);
              if (0x13 < (int)local_3c8) {
                puVar6 = auStack_36c;
              }
              fscanf(stream,&DAT_004c5bfc,puVar6);
              local_3c8 = local_3c8 + 1;
            } while (local_3c8 < uStack_3c0);
          }
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,&DAT_004c5bfc,&uStack_388);
          *(undefined4 *)(iVar3 + 0x43f4) = uStack_388;
          fscanf(stream,s________004c5c04,local_368);
          iVar3 = *(int *)(cur_sim + 0x3fbc);
          fscanf(stream,s__d__d_004c5b00,iVar3,iVar3 + 4);
          fscanf(stream,s________004c5c04,local_368);
          fscanf(stream,&DAT_004c5bfc,&local_3c4);
          local_3c8 = 0;
          if (0 < local_3c4) {
            do {
              fscanf(stream,s_______004c5b54,abStack_268);
              if ((int)local_3c8 < scrollback_lines) {
                uVar7 = 0xffffffff;
                pbVar9 = abStack_268 + 1;
                do {
                  pbVar10 = pbVar9;
                  if (uVar7 == 0) break;
                  uVar7 = uVar7 - 1;
                  pbVar10 = pbVar9 + 1;
                  bVar2 = *pbVar9;
                  pbVar9 = pbVar10;
                } while (bVar2 != 0);
                uVar7 = ~uVar7;
                pbVar9 = pbVar10 + -uVar7;
                pbVar10 = (byte *)(local_3c8 * 0x100 + *(int *)(iVar3 + 8));
                for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                  *(undefined4 *)pbVar10 = *(undefined4 *)pbVar9;
                  pbVar9 = pbVar9 + 4;
                  pbVar10 = pbVar10 + 4;
                }
                for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                  *pbVar10 = *pbVar9;
                  pbVar9 = pbVar9 + 1;
                  pbVar10 = pbVar10 + 1;
                }
              }
              local_3c8 = local_3c8 + 1;
            } while ((int)local_3c8 < local_3c4);
          }
        }
        fscanf(stream,s________004c5c04,local_368);
        if (local_3bc != 0) {
          load_io_files(stream);
          if ((extraout_EAX_06 == 0) || (mdisk_load_all(local_3b8,stream), extraout_EAX_07 == 0)) {
            local_3bc = 0;
          }
          else {
            local_3bc = 1;
          }
          if (local_3bc != 0) {
            fscanf(stream,&DAT_004c5bfc,&local_3c4);
            fscanf(stream,s_______004c5b54,abStack_268);
            if (local_3c4 != 0) {
              dbg_load_cld(local_3b8,(char *)(abStack_268 + 1));
            }
          }
        }
        if (((profiler_hook != (undefined *)0x0) && (local_100[0] != '\0')) &&
           (*(code **)(profiler_hook + 8) != (code *)0x0)) {
          (**(code **)(profiler_hook + 8))(local_100,local_3b8,local_3ac);
          local_3ac = 1;
        }
      }
      local_3a4 = local_3a4 + 1;
      iVar3 = local_3bc;
    } while (local_3a4 < local_3a0);
  }
  if (((profiler_hook != (undefined *)0x0) && (local_100[0] != '\0')) &&
     ((*(code **)(profiler_hook + 8) != (code *)0x0 && (local_3ac != 0)))) {
    (**(code **)(profiler_hook + 8))(0,0,1);
  }
  if (iVar3 == 0) {
    bVar11 = false;
  }
  else {
    fscanf(stream,s________004c5c04,local_368);
    fscanf(stream,&DAT_004c5bfc,&local_3b8);
    if ((((int)local_3b8 < 0) || (max_devices <= (int)local_3b8)) ||
       (*(int *)(dev_tab + local_3b8 * 4) == 0)) {
      bVar11 = false;
    }
    else {
      bVar11 = true;
    }
  }
  if (!bVar11) {
    local_3c8 = 0;
    if (0 < max_devices) {
      do {
        dev_destroy(local_3c8);
        local_3c8 = local_3c8 + 1;
      } while ((int)local_3c8 < max_devices);
    }
    dev_create(0,(char *)**(undefined4 **)chiptype_tab);
    local_3b8 = 0;
  }
  cur_dev_index = local_3b8;
  run_dev_index = local_3b8;
  *(undefined4 *)(*(int *)(dev_state_tab + local_3b8 * 4) + 0x40) = 0;
  scrollback_end(local_3b8);
  fclose(stream);
  return (uint)!bVar11;
}


/* ==== load_maplist @ 004383d0 ==== */

void __cdecl load_maplist(void *listp,void *fp)

{
  int extraout_EAX;
  int local_4;
  
  local_4 = 0;
  fscanf(fp,&DAT_004c5bfc,&local_4);
  while( true ) {
    if (local_4 == 0) {
      *(int *)listp = 0;
      return;
    }
    local_4 = local_4 + -1;
    dsp_alloc(0x10,1);
    if (extraout_EAX == 0) break;
    fscanf(fp,s__d__lx__lx_004c5c14,extraout_EAX,extraout_EAX + 4,extraout_EAX + 8);
    *(int *)listp = extraout_EAX;
    listp = (void *)(extraout_EAX + 0xc);
  }
  return;
}


/* ==== load_expr_tree @ 00438450 ==== */

void __cdecl load_expr_tree(void *fp)

{
  int iVar1;
  void *stream;
  int iVar2;
  undefined4 *p;
  undefined4 *puVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  undefined4 uVar4;
  int local_c;
  int local_8;
  undefined4 local_4;
  
  stream = fp;
  iVar2 = fscanf(fp,&DAT_004c5bfc,&fp);
  if (((iVar2 == 0) || (fp == (void *)0x0)) || (dsp_alloc((int)fp * 4,0), p == (undefined4 *)0x0)) {
    return;
  }
  iVar2 = 0;
  puVar3 = p;
  if (0 < (int)fp) {
    do {
      *puVar3 = 0;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < (int)fp);
  }
  fscanf(stream,&DAT_004c5bfc,&local_8);
  iVar2 = 0;
  if (0 < local_8) {
    do {
      fscanf(stream,&DAT_004c5bfc,&local_c);
      dsp_alloc(0x1c,0);
      if (extraout_EAX == 0) {
        return;
      }
      dsp_alloc(0x40,0);
      *(int *)(extraout_EAX + 0x10) = extraout_EAX_00;
      if (extraout_EAX_00 == 0) {
        return;
      }
      *(undefined4 *)(extraout_EAX + 0x14) = 0;
      p[local_c] = extraout_EAX;
      fscanf(stream,&DAT_004c5bfc,extraout_EAX + 0xc);
      fscanf(stream,s__lu__lu_004c5c60,*(int *)(extraout_EAX + 0x10) + 4,
             *(int *)(extraout_EAX + 0x10));
      fscanf(stream,s__hu__hu_004c5c54,*(int *)(extraout_EAX + 0x10) + 10,
             *(int *)(extraout_EAX + 0x10) + 8);
      fscanf(stream,s__lu__lu_004c5c60,*(int *)(extraout_EAX + 0x10) + 0xc,
             *(int *)(extraout_EAX + 0x10) + 0x10);
      fscanf(stream,s__d__lu__hu_004c5c44,&local_4,*(int *)(extraout_EAX + 0x10) + 0x18,
             *(int *)(extraout_EAX + 0x10) + 0x3c);
      *(undefined4 *)(*(int *)(extraout_EAX + 0x10) + 0x1c) = local_4;
      iVar1 = *(int *)(extraout_EAX + 0x10);
      fscanf(stream,s__lu__ld__ld__lu__lu__lu__lu_004c5c24,iVar1 + 0x20,iVar1 + 0x24,iVar1 + 0x28,
             iVar1 + 0x2c,iVar1 + 0x30,iVar1 + 0x34,iVar1 + 0x38);
      iVar2 = iVar2 + 1;
    } while (iVar2 < local_8);
  }
  local_c = 0;
  if (0 < (int)fp) {
    do {
      if ((undefined4 *)p[local_c] != (undefined4 *)0x0) {
        if (local_c * 3 + 1 < (int)fp) {
          uVar4 = p[local_c * 3 + 1];
        }
        else {
          uVar4 = 0;
        }
        *(undefined4 *)p[local_c] = uVar4;
        if (local_c * 3 + 2 < (int)fp) {
          uVar4 = p[local_c * 3 + 2];
        }
        else {
          uVar4 = 0;
        }
        *(undefined4 *)(p[local_c] + 4) = uVar4;
        if (local_c * 3 + 3 < (int)fp) {
          uVar4 = p[local_c * 3 + 3];
        }
        else {
          uVar4 = 0;
        }
        *(undefined4 *)(p[local_c] + 8) = uVar4;
      }
      local_c = local_c + 1;
    } while (local_c < (int)fp);
  }
  dsp_free(p);
  return;
}


/* ==== dev_cycle_begin @ 00438690 ==== */

void __cdecl dev_cycle_begin(int dev)

{
  code *pcVar1;
  int iVar2;
  int devidx;
  long lVar3;
  undefined4 local_4;
  
  devidx = dev;
  if ((-1 < dev) && (dev < max_devices)) {
    cur_dev = *(int **)(dev_tab + dev * 4);
    if (cur_dev != (int *)0x0) {
      cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
      cur_itype = *(undefined4 *)(itype_tab + *cur_dev * 4);
      cur_sim = *(int *)(dev_state_tab + dev * 4);
      *(undefined4 *)(cur_sim + 0x40) = 1;
      io_in_poll();
      iVar2 = cur_sim;
      if ((profiler_hook != (undefined *)0x0) && (*(int *)(cur_sim + 0x488) != 0)) {
        dev = 0;
        if (DAT_004c5524 < 0) {
          periph_find_reg(0,&DAT_004b2924,&DAT_004c5520,&DAT_004c5524);
        }
        periph_call(devidx,DAT_004c5520,DAT_004c5524,(long)&local_4);
        if (DAT_004c552c < 0) {
          lVar3 = periph_find_reg(0,&DAT_004b2950,&DAT_004c5528,&DAT_004c552c);
          if (lVar3 != 0) {
            periph_call(devidx,DAT_004c5528,DAT_004c552c,(long)&dev);
          }
        }
        *(undefined4 *)(iVar2 + 0x480) = local_4;
        *(undefined4 *)(iVar2 + 0x488) = 0;
        *(int *)(iVar2 + 0x484) = dev;
        if (*(int *)(iVar2 + 0x48c) == 0) {
          *(undefined4 *)(iVar2 + 0x48c) = 1;
        }
      }
      if ((*(int *)(cur_dtype + 0x4e4) == 0) &&
         (pcVar1 = *(code **)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c) + 0x10),
         pcVar1 != (code *)0x0)) {
        (*pcVar1)(0);
      }
      if ((*(int *)(cur_dtype + 0x4e4) != 0) &&
         (pcVar1 = *(code **)(*(int *)(cur_dtype + 0x4e4) + 0x18), pcVar1 != (code *)0x0)) {
        (*pcVar1)(0,0);
      }
      if ((*(int **)(cur_dtype + 0x4e0) != (int *)0x0) && (**(int **)(cur_dtype + 0x4e0) != 0)) {
        (**(code **)(*(int *)(cur_dtype + 0x4e4) + 4))(devidx);
      }
    }
  }
  return;
}


/* ==== dev_cycle_stage1 @ 00438850 ==== */

void __cdecl dev_cycle_stage1(int dev)

{
  code *pcVar1;
  
  if ((*(int *)(cur_dtype + 0x4e4) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_dtype + 0x4e4) + 0x18), pcVar1 != (code *)0x0)) {
    (*pcVar1)(0,1);
  }
  if ((*(int **)(cur_dtype + 0x4e0) != (int *)0x0) && (**(int **)(cur_dtype + 0x4e0) != 0)) {
    (**(code **)(*(int *)(cur_dtype + 0x4e4) + 8))(dev);
  }
  return;
}


/* ==== dev_cycle_stage2 @ 004388a0 ==== */

void __cdecl dev_cycle_stage2(int dev)

{
  code *pcVar1;
  
  if ((*(int *)(cur_dtype + 0x4e4) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_dtype + 0x4e4) + 0x18), pcVar1 != (code *)0x0)) {
    (*pcVar1)(0,2);
  }
  if ((*(int **)(cur_dtype + 0x4e0) != (int *)0x0) && (**(int **)(cur_dtype + 0x4e0) != 0)) {
    (**(code **)(*(int *)(cur_dtype + 0x4e4) + 0xc))(dev);
  }
  return;
}


/* ==== dev_cycle_end @ 004388f0 ==== */

int __cdecl dev_cycle_end(int dev)

{
  code *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  
  if ((*(int *)(cur_dtype + 0x4e4) != 0) &&
     (pcVar1 = *(code **)(*(int *)(cur_dtype + 0x4e4) + 0x18), pcVar1 != (code *)0x0)) {
    (*pcVar1)(0,3);
  }
  if ((*(int **)(cur_dtype + 0x4e0) != (int *)0x0) && (**(int **)(cur_dtype + 0x4e0) != 0)) {
    (**(code **)(*(int *)(cur_dtype + 0x4e4) + 0x10))(dev);
  }
  iVar5 = *(int *)(cur_dtype + 0x14);
  iVar6 = 1;
  if (1 < iVar5) {
    iVar8 = 0x48;
    iVar3 = cur_dtype;
    do {
      pcVar1 = *(code **)(*(int *)(*(int *)(iVar3 + 0x18) + 0x2c + iVar8) + 0x10);
      if (pcVar1 != (code *)0x0) {
        (*pcVar1)(iVar6);
        iVar3 = cur_dtype;
      }
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + 0x48;
    } while (iVar6 < iVar5);
  }
  io_out_poll();
  iVar5 = *(int *)(cur_dtype + 0x30);
  if (0 < iVar5) {
    puVar2 = *(undefined4 **)(cur_dev + 0x18);
    puVar4 = *(undefined4 **)(cur_dev + 0x18) + 0x25;
    do {
      iVar5 = iVar5 + -1;
      puVar7 = puVar2;
      puVar9 = puVar4;
      for (iVar6 = 0x25; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar9 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar9 = puVar9 + 1;
      }
      puVar2 = puVar2 + 0x4a;
      puVar4 = puVar4 + 0x4a;
    } while (iVar5 != 0);
  }
  *(int *)(cur_dev + 0x20) = *(int *)(cur_dev + 0x20) + 1;
  iVar5 = sim_check_stop();
  if (iVar5 != 0) {
    *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) | 0x10;
  }
  if (((cur_dev != 0) && (cur_sim != 0)) && ((*(byte *)(cur_dev + 0x44) & 3) != 0)) {
    if (profiler_hook != (undefined *)0x0) {
      sim_profile_step(dev);
    }
    *(uint *)(cur_dev + 0x44) = *(uint *)(cur_dev + 0x44) & 0x10;
    if (*(int *)(cur_dev + 0x44) != 0) {
      *(undefined4 *)(cur_dev + 0x44) = 0;
      *(undefined4 *)(cur_sim + 0x40) = 0;
    }
  }
  return 0;
}


/* ==== dev_housekeeping @ 00438a30 ==== */

void __cdecl dev_housekeeping(int dev)

{
  if (((-1 < dev) && (dev < max_devices)) && (cur_dev = *(int *)(dev_tab + dev * 4), cur_dev != 0))
  {
    dev_cycle_begin(dev);
    dev_cycle_stage1(dev);
    dev_cycle_stage2(dev);
    dev_cycle_end(dev);
  }
  return;
}


/* ==== load_io_files @ 00438a80 ==== */

void __cdecl load_io_files(void *fp)

{
  int iVar1;
  
  iVar1 = load_io_list(fp,(void *)(cur_sim + 0x14c));
  if (iVar1 != 0) {
    iVar1 = load_io_list(fp,(void *)(cur_sim + 0x150));
    if (iVar1 != 0) {
      iVar1 = load_io_list(fp,(void *)(cur_sim + 0x154));
      if (iVar1 != 0) {
        load_io_list(fp,(void *)(cur_sim + 0x158));
      }
    }
  }
  return;
}


/* ==== load_io_list @ 00438af0 ==== */

int __cdecl load_io_list(void *fp,void *list_head_addr)

{
  char cVar1;
  void *stream;
  char *name;
  void *stream_00;
  int iVar2;
  int va0;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  char *local_68;
  int local_64;
  int local_60;
  char local_5c;
  char local_5b [91];
  
  local_68 = list_head_addr;
  stream = fp;
  list_head_addr = (void *)fscanf(fp,&DAT_004c5bfc,&local_64);
  while( true ) {
    if ((list_head_addr == (void *)0x0) || (local_64 == 0)) goto LAB_00438d4f;
    dsp_alloc(0x1e8,1);
    if (name == (char *)0x0) break;
    fscanf(stream,s_______004c5b54,&local_5c);
    uVar3 = 0xffffffff;
    pcVar6 = local_5b;
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
    pcVar7 = name;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    fscanf(stream,s_______004c5b54,&local_5c);
    uVar3 = 0xffffffff;
    pcVar6 = local_5b;
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
    pcVar7 = name + 0x100;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    fscanf(stream,s__d__lx__lx__lx__lx__lx__lx__lx___004c5c94,name + 0x154,name + 0x158,name + 0x15c
           ,name + 0x160,name + 0x164,name + 0x168,name + 0x16c,name + 0x170,name + 0x174,
           name + 0x178,name + 0x1e4,name + 0x188,name + 0x1b0,name + 0x1d0,name + 0x1d4,
           name + 0x1d8,&local_60);
    name[0x150] = '\0';
    name[0x151] = '\0';
    name[0x152] = '\0';
    name[0x153] = '\0';
    if (local_60 != 0) {
      fopen(name,&DAT_004c5c90);
      *(void **)(name + 0x150) = stream_00;
      if (stream_00 == (void *)0x0) {
        sprintf(&local_5c,s__Error_opening__s__004c5c7c,name);
        sim_error(&local_5c);
      }
      else {
        fseek(stream_00,*(long *)(name + 0x178),0);
      }
    }
    *(char **)local_68 = name;
    piVar5 = (int *)(name + 0x1dc);
    iVar2 = fscanf(stream,&DAT_004c5c10,&fp);
    while( true ) {
      if ((iVar2 == 0) || (fp == (void *)0x0)) goto LAB_00438d11;
      dsp_alloc(0x10,1);
      *piVar5 = va0;
      if (va0 == 0) break;
      fscanf(stream,s__lx__lx__ld_004c5c6c,va0,va0 + 4,va0 + 8);
      piVar5 = (int *)(va0 + 0xc);
      iVar2 = fscanf(stream,&DAT_004c5c10,&fp);
    }
    list_head_addr = (void *)0x0;
LAB_00438d11:
    local_68 = name + 0x1e0;
    if (list_head_addr == (void *)0x0) goto LAB_00438d4f;
    *piVar5 = 0;
    list_head_addr = (void *)fscanf(stream,&DAT_004c5bfc,&local_64);
  }
  list_head_addr = (void *)0x0;
LAB_00438d4f:
  local_68[0] = '\0';
  local_68[1] = '\0';
  local_68[2] = '\0';
  local_68[3] = '\0';
  return (int)list_head_addr;
}


/* ==== path_combine @ 00438d70 ==== */

void __cdecl path_combine(char *dir,char *name,char *ext,char *out)

{
  char cVar1;
  char cVar2;
  undefined3 extraout_var;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  
  if (((*name == '\\') || (*name == '/')) ||
     (cVar2 = strrchr(name,0x3a), CONCAT31(extraout_var,cVar2) != 0)) {
    *out = empty_str;
  }
  else {
    uVar3 = 0xffffffff;
    pcVar6 = dir;
    do {
      pcVar8 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar2 != cVar1);
    uVar3 = ~uVar3;
    pcVar6 = pcVar8 + -uVar3;
    pcVar8 = out;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar6 = dir;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar2 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    if (((~uVar3 != 1) && (cVar2 = dir[~uVar3 - 2], cVar2 != '\\')) &&
       ((cVar2 != '/' && (cVar2 != ':')))) {
      uVar3 = 0xffffffff;
      pcVar6 = (char *)&DAT_004c5cd4;
      do {
        pcVar8 = pcVar6;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar8 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar8;
      } while (cVar2 != '\0');
      uVar3 = ~uVar3;
      iVar5 = -1;
      pcVar6 = out;
      do {
        pcVar7 = pcVar6;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar7 = pcVar6 + 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar2 != '\0');
      pcVar6 = pcVar8 + -uVar3;
      pcVar8 = pcVar7 + -1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar8 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar8 = pcVar8 + 1;
      }
    }
  }
  uVar3 = 0xffffffff;
  pcVar6 = name;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar6 = out;
  do {
    pcVar7 = pcVar6;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar7 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar2 != '\0');
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar6 = out;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar2 != '\0');
  for (iVar5 = ~uVar3 - 2; 0 < iVar5; iVar5 = iVar5 + -1) {
    if (out[iVar5] == '/') {
      out[iVar5] = '\\';
    }
  }
  uVar3 = 0xffffffff;
  pcVar6 = name;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  while (((uVar3 = uVar3 - 1, 0 < (int)uVar3 && (cVar2 = name[uVar3], cVar2 != '\\')) &&
         (cVar2 != '/'))) {
    if (cVar2 == '.') {
      return;
    }
  }
  uVar3 = 0xffffffff;
  pcVar6 = out;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar2 != '\0');
  uVar3 = 0x100 - (~uVar3 - 1);
  if (0 < (int)uVar3) {
    strncat(out,ext,uVar3);
  }
  return;
}


/* ==== path_search @ 00438eb0 ==== */

int __cdecl path_search(char *name,char *defext,char *out)

{
  char cVar1;
  void *stream;
  int iVar2;
  void *stream_00;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char local_100 [256];
  
  path_combine((char *)(cur_dev + 0x58),name,defext,out);
  fopen(out,&DAT_004c5574);
  pcVar4 = source_path_list;
  if (stream != (void *)0x0) {
    fclose(stream);
    return 1;
  }
  if (source_path_list != (char *)0x0) {
    iVar2 = sscanf(source_path_list,s__255_____004c5cd8,local_100);
    while (iVar2 != 0) {
      path_combine(local_100,name,defext,out);
      fopen(out,&DAT_004c5574);
      if (stream_00 != (void *)0x0) {
        fclose(stream_00);
        return 1;
      }
      uVar3 = 0xffffffff;
      pcVar5 = local_100;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      if (pcVar4[~uVar3 - 1] == '\0') break;
      pcVar4 = pcVar4 + (~uVar3 - 1) + 1;
      iVar2 = sscanf(pcVar4,s__255_____004c5cd8,local_100);
    }
  }
  uVar3 = 0xffffffff;
  pcVar4 = name;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar2 = ~uVar3 - 3;
  if (iVar2 < 1) {
    return 0;
  }
  while ((name[iVar2] != '\\' && (name[iVar2] != '/'))) {
    iVar2 = iVar2 + -1;
    if (iVar2 < 1) {
      return 0;
    }
  }
  iVar2 = path_search(name + iVar2 + 1,defext,out);
  return iVar2;
}


