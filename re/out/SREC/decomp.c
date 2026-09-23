/* ==== main @ 00401000 ==== */

int __cdecl main(int argc,char **argv,char **envp)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  char *extraout_EAX;
  size_t sVar4;
  char *extraout_EAX_00;
  uint local_28;
  uint local_24;
  uint local_1c;
  char *local_18;
  uint local_10;
  char *local_8;
  
  local_18 = (char *)0x0;
  signal(2,FUN_004057f6);
  signal(0xb,FUN_004057f6);
  pcVar1 = FUN_0040541b(*argv);
  pcVar2 = _strrchr(pcVar1,0x2e);
  if (pcVar2 != (char *)0x0) {
    *pcVar2 = '\0';
  }
  iVar3 = FUN_0040554c('q',argc,argv);
  DAT_00411fe4 = (uint)(iVar3 != 0);
  PTR_DAT_0040e070 = pcVar1;
  if (DAT_00411fe4 == 0) {
    fprintf(&DAT_0040f308,s__s__s__s_0040e104,s_DSP_S_Record_Conversion_Utility_0040e078,
            s_Version_6_3_0040e098,s__C__Copyright_Motorola__Inc__198_0040e0a8);
  }
  if (DAT_00411fc4 == 0) {
    DAT_00411fb0 = (char *)0x0;
    DAT_00411fb4 = 0;
    while (local_10 = FUN_00405628(argc,(int)argv,s_A_a_BbCcLlMmO_o_P_p_QqRrSsT_t_Uu_0040e110),
          local_10 != 0xffffffff) {
      if (__mb_cur_max < 2) {
        local_1c = *(ushort *)(_pctype + local_10 * 2) & 1;
      }
      else {
        local_1c = _isctype(local_10,1);
      }
      if (local_1c != 0) {
        local_10 = FUN_00406060(local_10);
      }
      switch(local_10) {
      case 0x61:
        iVar3 = sscanf(DAT_00411fb0,&DAT_0040e138,&DAT_00412628);
        if (iVar3 == 0) {
          FUN_0040585a();
        }
        break;
      case 0x62:
        DAT_00411fd8 = 1;
        break;
      case 99:
        DAT_00411fec = 1;
        break;
      default:
        FUN_0040585a();
        break;
      case 0x6c:
        DAT_00411fe0 = 1;
        break;
      case 0x6d:
        DAT_00411fcc = 1;
        break;
      case 0x6f:
        local_8 = _strchr(PTR_s_xylpedXYLPED_0040e0f0,(int)*DAT_00411fb0);
        if ((local_8 == (char *)0x0) || (DAT_00411fb0[1] != ':')) {
          FUN_0040585a();
        }
        if (__mb_cur_max < 2) {
          local_24 = *(ushort *)(_pctype + *local_8 * 2) & 1;
        }
        else {
          local_24 = _isctype((int)*local_8,1);
        }
        if (local_24 != 0) {
          local_8 = local_8 + -6;
        }
        iVar3 = sscanf(DAT_00411fb0 + 2,&DAT_0040e13c,
                       &DAT_00412660 + ((int)local_8 - (int)PTR_s_xylpedXYLPED_0040e0f0) * 4);
        if (iVar3 == 0) {
          FUN_0040585a();
        }
        break;
      case 0x70:
        local_18 = DAT_00411fb0;
        break;
      case 0x71:
        DAT_00411fe4 = 1;
        break;
      case 0x72:
        DAT_00411fd0 = 1;
        break;
      case 0x73:
        DAT_00411fc8 = 1;
        break;
      case 0x74:
        iVar3 = sscanf(DAT_00411fb0,&DAT_0040e140,&DAT_0041262c);
        if (iVar3 == 0) {
          FUN_0040585a();
        }
        break;
      case 0x75:
        DAT_00411fd4 = 1;
        break;
      case 0x77:
        DAT_00411fdc = 1;
        break;
      case 0x78:
        DAT_00411fe8 = 1;
      }
    }
    argc = argc - DAT_00411fb4;
    argv = argv + DAT_00411fb4;
    if ((((argc < 1) || ((DAT_00411fc8 != 0 && (DAT_00411fcc != 0)))) ||
        ((DAT_00411fec != 0 && (DAT_00411fcc != 0)))) ||
       ((DAT_00411fd8 != 0 && (DAT_00411fdc != 0)))) {
      FUN_0040585a();
    }
  }
  if ((local_18 != (char *)0x0) && (DAT_004125f8 = FUN_00404662(local_18), DAT_004125f8 == 0)) {
    FUN_004059a7(s_invalid_machine_type_0040e144);
  }
  if ((DAT_00412628 != 0) && ((DAT_00412628 < 2 || (4 < DAT_00412628)))) {
    FUN_004059a7(s_invalid__a_command_line_argument_0040e15c);
  }
  if ((DAT_0041262c != 0) && ((DAT_0041262c < 2 || (4 < DAT_0041262c)))) {
    FUN_004059a7(s_invalid__t_command_line_argument_0040e180);
  }
  if ((DAT_00411fe0 != 0) && (DAT_00411fe8 != 0)) {
    DAT_00411fe0 = 0;
  }
  while( true ) {
    if (DAT_00411fc4 == 0) {
      local_28 = argc;
    }
    else {
      iVar3 = FUN_004057ec((undefined4 *)&DAT_00412988);
      local_28 = (uint)(iVar3 != 0);
    }
    if (local_28 == 0) break;
    if (DAT_00411fc4 == 0) {
      pcVar1 = *argv;
    }
    else {
      pcVar1 = &DAT_00411bb0;
    }
    iVar3 = _strcmp(pcVar1,&DAT_0040e1a4);
    if (iVar3 == 0) {
      malloc(0x200);
      DAT_00411fb8 = extraout_EAX;
      if (extraout_EAX == (char *)0x0) {
        FUN_004059a7(s_cannot_allocate_file_name_0040e1a8);
      }
      DAT_00411fbc = &PTR_DAT_0040f2c8;
      FUN_004016e0(&PTR_DAT_0040f2c8);
    }
    else {
      sVar4 = _strlen(pcVar1);
      malloc(sVar4 + 5);
      DAT_00411fb8 = extraout_EAX_00;
      if (extraout_EAX_00 == (char *)0x0) {
        FUN_004059a7(s_cannot_allocate_file_name_0040e1c4);
      }
      FID_conflict___mbscpy(DAT_00411fb8,pcVar1);
      DAT_00411fc0 = FUN_004015b6(DAT_00411fb8);
      pcVar1 = _strrchr(DAT_00411fb8,0x2e);
      if (pcVar1 != (char *)0x0) {
        *pcVar1 = '\0';
      }
      FUN_004016e0(DAT_00411fbc);
      fclose(DAT_00411fbc);
    }
    free(DAT_00411fb8);
    if (DAT_00411fc4 == 0) {
      argv = argv + 1;
      argc = argc + -1;
    }
  }
  exit(0);
  return 0;
}


/* ==== FUN_004015b6 @ 004015b6 ==== */

int __cdecl FUN_004015b6(char *param_1)

{
  int iVar1;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  char *local_210;
  char local_204 [512];
  
  FID_conflict___mbscpy(local_204,param_1);
  iVar1 = FUN_0040513a(param_1);
  if (iVar1 == 1) {
    local_210 = &DAT_0040e1e0;
  }
  else {
    local_210 = &DAT_0040e1e4;
  }
  fopen(param_1,local_210);
  DAT_00411fbc = extraout_EAX;
  if (extraout_EAX == 0) {
    if (DAT_00411fc0 != 0) {
      FUN_00405a02(s_cannot_open_input_file__s_0040e1e8,local_204);
    }
    FUN_0040524b(param_1,&DAT_0040e204);
    fopen(param_1,&DAT_0040e20c);
    if (extraout_EAX_00 == 0) {
      FUN_0040524b(param_1,&DAT_0040e210);
      fopen(param_1,&DAT_0040e218);
      DAT_00411fbc = extraout_EAX_01;
      if (extraout_EAX_01 == 0) {
        FUN_00405a02(s_cannot_open_input_file__s_0040e21c,local_204);
        iVar1 = 0;
      }
      else {
        iVar1 = 1;
      }
    }
    else {
      iVar1 = 2;
      DAT_00411fbc = extraout_EAX_00;
    }
  }
  return iVar1;
}


/* ==== FUN_004016e0 @ 004016e0 ==== */

void __cdecl FUN_004016e0(undefined **param_1)

{
  uint uVar1;
  
  if (DAT_00411fc0 == 2) {
    FUN_0040177a((int *)param_1);
  }
  else if (DAT_00411fc0 == 1) {
    FUN_0040288c(param_1);
  }
  else {
    do {
      uVar1 = FUN_00406610((int *)param_1);
      if ((uVar1 == 0xffffffff) || (uVar1 == 0x5f)) break;
    } while (uVar1 != 0);
    rewind(param_1);
    if (uVar1 == 0xffffffff) {
      FUN_004059a7(s_invalid_object_file_type_0040e238);
    }
    if (uVar1 == 0) {
      FUN_0040177a((int *)param_1);
    }
    else {
      FUN_0040288c(param_1);
    }
  }
  return;
}


/* ==== FUN_0040177a @ 0040177a ==== */

void __cdecl FUN_0040177a(int *param_1)

{
  int iVar1;
  char *p;
  int iVar2;
  uint uVar3;
  code *pcVar4;
  char *local_18;
  int local_10;
  
  FUN_00401902(param_1);
  iVar1 = DAT_00411b94;
  malloc(DAT_00411b94 * 0x34);
  if (p == (char *)0x0) {
    FUN_004059a7(s_cannot_allocate_section_headers_0040e254);
  }
  iVar2 = fseek(param_1,DAT_00411ba4 + 0x1c,0);
  if (iVar2 != 0) {
    FUN_004059a7(s_cannot_seek_to_section_headers_0040e274);
  }
  uVar3 = FUN_0040549c(p,iVar1 * 0x34,1,param_1);
  if (uVar3 != 1) {
    FUN_004059a7(s_cannot_read_section_headers_0040e294);
  }
  local_18 = p;
  for (local_10 = 1; local_10 <= iVar1; local_10 = local_10 + 1) {
    if ((*(int *)(local_18 + 0x1c) != 0) && (*(int *)(local_18 + 0x18) != 0)) {
      iVar2 = FUN_00404e75(*(int *)(local_18 + 0xc));
      if (iVar2 < 0) {
        FUN_004059a7(s_invalid_memory_space_specifier_0040e2b0);
      }
      if ((*(uint *)(local_18 + 0x30) & 0x400) == 0) {
        pcVar4 = FUN_00401a6f;
      }
      else {
        pcVar4 = FUN_004020aa;
      }
      if ((iVar2 == 2) && (DAT_00411fe8 != 0)) {
        (*pcVar4)(local_18,local_10,2,0);
        (*pcVar4)(local_18,local_10,2,1);
      }
      else {
        (*pcVar4)(local_18,local_10,iVar2,iVar2);
      }
    }
    local_18 = local_18 + 0x34;
  }
  free(p);
  FUN_004026c8();
  return;
}


/* ==== FUN_00401902 @ 00401902 ==== */

void __cdecl FUN_00401902(int *param_1)

{
  uint uVar1;
  char *local_8;
  
  local_8 = (char *)0x0;
  uVar1 = FUN_0040549c((char *)&DAT_00411b90,0x1c,1,param_1);
  if (uVar1 != 1) {
    FUN_004059a7(s_cannot_read_file_header_0040e2d0);
  }
  if ((DAT_00411ba8 & 1) == 0) {
    FUN_004059a7(s_invalid_object_file_type_0040e2e8);
  }
  switch(DAT_00411b90) {
  case 0x2c5:
    local_8 = s_56000_0040e304;
    break;
  case 0x2c6:
    local_8 = s_96000_0040e30c;
    break;
  case 0x2c7:
    local_8 = s_56100_0040e314;
    break;
  case 0x2c8:
    local_8 = s_56300_0040e31c;
    break;
  case 0x2c9:
    local_8 = s_56800_0040e324;
    break;
  case 0x2ca:
    local_8 = s_56600_0040e32c;
    break;
  case 0x2cb:
    local_8 = &DAT_0040e334;
    break;
  case 0x2cc:
    local_8 = s_56700_0040e338;
    break;
  default:
    FUN_004059a7(s_invalid_machine_type_0040e340);
  }
  if ((DAT_004125f8 == 0) && (DAT_004125f8 = FUN_00404662(local_8), DAT_004125f8 == 0)) {
    FUN_004059a7(s_invalid_machine_type_0040e358);
  }
  if ((DAT_00411ba4 != 0) &&
     (uVar1 = FUN_0040549c(&DAT_00411950,DAT_00411ba4,1,param_1), uVar1 != 1)) {
    FUN_004059a7(s_cannot_read_optional_header_0040e370);
  }
  FUN_00404600(0);
  if (DAT_00411fc8 != 0) {
    FUN_00403fc9(0);
  }
  return;
}


/* ==== FUN_00401a6f @ 00401a6f ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00401a6f(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  uint *extraout_EAX;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  bool bVar5;
  uint local_70;
  uint local_6c;
  undefined *local_68;
  undefined1 *local_64;
  uint local_5c;
  char *local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  int local_3c;
  uint local_38;
  uint *local_34;
  uint local_30;
  char local_2c [16];
  uint local_1c;
  int local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  local_18 = param_4;
  if (DAT_00411fd4 == 0) {
    bVar5 = param_4 == 0;
  }
  else {
    bVar5 = param_4 != 0;
  }
  local_38 = (uint)bVar5;
  local_1c = local_38;
  local_c = 0;
  if (DAT_00411fc8 == 0) {
    if ((&DAT_00412648)[param_4] == (undefined4 *)0x0) {
      FUN_00403fc9(param_4);
    }
  }
  else {
    local_14 = param_4 + 1;
    local_18 = 0;
    if (DAT_004125f0 != local_14) {
      FUN_00404600(local_14);
      iVar1 = FUN_00406750(&DAT_00411db0,(int *)*DAT_00412648);
      if (iVar1 == -1) {
        FUN_004059a7(s_cannot_write_S0_record_0040e38c);
      }
      DAT_004125f0 = local_14;
    }
  }
  local_30 = *(int *)(param_1 + 8) + *(int *)(&DAT_00412660 + param_4 * 4);
  if ((DAT_00411b90 == 0x2ca) && ((*(uint *)(param_1 + 0x30) & 0x4000) != 0)) {
    local_3c = 1;
  }
  else {
    local_3c = 0;
  }
  DAT_00412608 = local_3c;
  if ((param_4 == 3) || (local_3c != 0)) {
    local_40 = DAT_00412604;
  }
  else {
    local_40 = DAT_0041260c;
  }
  DAT_004125fc = local_40;
  if ((DAT_00411b90 == 0x2ca) && (param_4 == 4)) {
    local_44 = DAT_00412600;
  }
  else {
    local_44 = local_40;
  }
  local_10 = local_44;
  if ((DAT_00411fcc == 0) && (DAT_00411fd8 != 0)) {
    local_30 = local_30 * local_44;
  }
  if (((DAT_00411fe0 != 0) && (param_4 == 2)) && (DAT_00411fd8 != 0)) {
    local_30 = local_30 << 1;
  }
  sprintf(local_2c,&DAT_0040e3a4,param_2);
  malloc(*(int *)(param_1 + 0x18) << 2);
  if (extraout_EAX == (uint *)0x0) {
    FUN_00405a02(s_cannot_allocate_data_block_for_s_0040e3a8,local_2c);
  }
  iVar1 = fseek(DAT_00411fbc,*(long *)(param_1 + 0x1c),0);
  if (iVar1 != 0) {
    FUN_00405a02(s_cannot_seek_to_raw_data_in_secti_0040e3d4,local_2c);
  }
  uVar2 = FUN_0040549c((char *)extraout_EAX,*(uint *)(param_1 + 0x18),4,DAT_00411fbc);
  if (uVar2 != 4) {
    FUN_00405a02(s_cannot_read_raw_data_in_section___0040e3fc,local_2c);
  }
  if ((param_4 == 3) || (DAT_00412608 != 0)) {
    local_48 = DAT_00412604;
  }
  else {
    local_48 = DAT_0041260c;
  }
  DAT_004125fc = local_48;
  local_14 = 0;
  local_8 = (int)(&DAT_00412648)[local_18];
  while( true ) {
    if (DAT_00411fcc == 0) {
      local_4c = 1;
    }
    else {
      local_4c = DAT_004125fc;
    }
    if ((int)local_4c <= (int)local_14) break;
    *(undefined4 *)(local_8 + 4) = 0;
    *(int *)(local_8 + 8) = local_8 + 0xc;
    local_14 = local_14 + 1;
    local_8 = local_8 + 0x5c;
  }
  local_34 = extraout_EAX;
  for (local_14 = 0; (int)local_14 < *(int *)(param_1 + 0x18); local_14 = local_14 + 1) {
    if ((param_3 == param_4) || (((local_14 ^ local_1c) & 1) == 0)) {
      if ((param_4 == 3) || (DAT_00412608 != 0)) {
        local_50 = DAT_0041261c;
      }
      else {
        local_50 = DAT_00412620;
      }
      _DAT_00412618 = local_50;
      if ((param_4 == 3) || (DAT_00412608 != 0)) {
        local_54 = DAT_00412634;
      }
      else {
        local_54 = DAT_00412638;
      }
      DAT_00412630 = local_54;
      puVar4 = local_34 + 1;
      sprintf(&DAT_00411ff0,local_54,*local_34 & local_50);
      FUN_004052db(&DAT_00411ff0);
      if ((param_4 == 3) || (DAT_00412608 != 0)) {
        local_5c = DAT_00412604;
      }
      else {
        local_5c = DAT_0041260c;
      }
      DAT_004125fc = local_5c;
      sVar3 = _strlen(&DAT_00411ff0);
      if (sVar3 != DAT_004125fc * 2) {
        FUN_004059a7(s_improper_number_of_bytes_in_word_0040e420);
      }
      if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
        FUN_00403e89(&DAT_00411ff0,param_4);
      }
      if (param_4 == 2) {
        local_34 = local_34 + 2;
        sprintf(&DAT_004121f0,DAT_00412630,*puVar4 & _DAT_00412618);
        FUN_004052db(&DAT_004121f0);
        sVar3 = _strlen(&DAT_004121f0);
        if (sVar3 != DAT_004125fc * 2) {
          FUN_004059a7(s_improper_number_of_bytes_in_word_0040e444);
        }
        if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
          FUN_00403e89(&DAT_004121f0,2);
        }
        local_14 = local_14 + 1;
      }
      else {
        FID_conflict___mbscpy(&DAT_004121f0,&DAT_00411ff0);
        local_34 = puVar4;
      }
      if (DAT_00411fd4 == 0) {
        local_64 = &DAT_004121f0;
      }
      else {
        local_64 = &DAT_00411ff0;
      }
      FUN_00403b31(local_18,local_64);
      if (param_4 == 2) {
        if (DAT_00411fd4 == 0) {
          local_68 = &DAT_00411ff0;
        }
        else {
          local_68 = &DAT_004121f0;
        }
        FUN_00403b31(local_18,local_68);
      }
      if (param_4 == 2) {
        if ((DAT_00411fcc == 0) && (DAT_00411fec == 0)) {
          local_70 = DAT_004125fc << 1;
        }
        else {
          local_6c = 2;
          local_70 = local_6c;
        }
      }
      else if ((DAT_00411fcc != 0) || (local_70 = DAT_004125fc, DAT_00411fec != 0)) {
        local_70 = 1;
      }
      local_c = local_c + local_70;
      if (((local_c & 1) == 0) && (0x1d < local_c)) {
        FUN_00403c48(local_18,local_30,local_c);
        if ((DAT_00411fd8 == 0) && ((DAT_00411fcc == 0 && (DAT_00411fec == 0)))) {
          if ((DAT_00411fe0 == 0) || (param_4 != 2)) {
            local_c = local_c / local_10;
          }
          else {
            local_c = local_c / local_10 >> 1;
          }
        }
        local_30 = local_30 + local_c;
        local_c = 0;
      }
    }
    else {
      local_34 = local_34 + 1;
    }
  }
  free(local_34 + -local_14);
  if (*(int *)((int)(&DAT_00412648)[local_18] + 8) != (int)(&DAT_00412648)[local_18] + 0xc) {
    FUN_00403c48(local_18,local_30,local_c);
  }
  return;
}


/* ==== FUN_004020aa @ 004020aa ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004020aa(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  size_t sVar3;
  bool bVar4;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  undefined *local_68;
  undefined1 *local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  char *local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  int local_40;
  uint local_3c [3];
  char local_30 [16];
  uint local_20;
  int local_1c;
  int local_18;
  uint local_14;
  uint local_10;
  int local_c;
  int local_8;
  
  local_1c = param_4;
  local_20 = 0;
  local_10 = 0;
  if (DAT_00411fc8 == 0) {
    if ((&DAT_00412648)[param_4] == (undefined4 *)0x0) {
      FUN_00403fc9(param_4);
    }
  }
  else {
    local_18 = param_4 + 1;
    local_1c = 0;
    if (DAT_004125f0 != local_18) {
      FUN_00404600(local_18);
      iVar1 = FUN_00406750(&DAT_00411db0,(int *)*DAT_00412648);
      if (iVar1 == -1) {
        FUN_004059a7(s_cannot_write_S0_record_0040e468);
      }
      DAT_004125f0 = local_18;
    }
  }
  local_3c[2] = *(int *)(param_1 + 8) + *(int *)(&DAT_00412660 + param_4 * 4);
  if ((DAT_00411b90 == 0x2ca) && ((*(uint *)(param_1 + 0x30) & 0x4000) != 0)) {
    local_40 = 1;
  }
  else {
    local_40 = 0;
  }
  DAT_00412608 = local_40;
  if ((param_4 == 3) || (local_40 != 0)) {
    local_44 = DAT_00412604;
  }
  else {
    local_44 = DAT_0041260c;
  }
  DAT_004125fc = local_44;
  if ((DAT_00411b90 == 0x2ca) && (param_4 == 4)) {
    local_48 = DAT_00412600;
  }
  else {
    local_48 = local_44;
  }
  local_14 = local_48;
  if ((DAT_00411fcc == 0) && (DAT_00411fd8 != 0)) {
    local_3c[2] = local_3c[2] * local_48;
  }
  if (((DAT_00411fe0 != 0) && (param_4 == 2)) && (DAT_00411fd8 != 0)) {
    local_3c[2] = local_3c[2] << 1;
  }
  local_c = *(int *)(param_1 + 0x10);
  sprintf(local_30,&DAT_0040e480,param_2);
  iVar1 = fseek(DAT_00411fbc,*(long *)(param_1 + 0x1c),0);
  if (iVar1 != 0) {
    FUN_00405a02(s_cannot_seek_to_raw_data_in_secti_0040e484,local_30);
  }
  uVar2 = FUN_0040549c((char *)local_3c,*(uint *)(param_1 + 0x18),4,DAT_00411fbc);
  if (uVar2 != 4) {
    FUN_00405a02(s_cannot_read_raw_data_in_section___0040e4ac,local_30);
  }
  if (param_3 != param_4) {
    if (DAT_00411fd4 == 0) {
      bVar4 = param_4 != 0;
    }
    else {
      bVar4 = param_4 == 0;
    }
    local_4c = (uint)bVar4;
    local_20 = local_4c;
  }
  if ((param_4 == 3) || (DAT_00412608 != 0)) {
    local_50 = DAT_0041261c;
  }
  else {
    local_50 = DAT_00412620;
  }
  _DAT_00412618 = local_50;
  if ((param_4 == 3) || (DAT_00412608 != 0)) {
    local_54 = DAT_00412634;
  }
  else {
    local_54 = DAT_00412638;
  }
  DAT_00412630 = local_54;
  sprintf(&DAT_00411ff0,local_54,local_3c[local_20] & local_50);
  FUN_004052db(&DAT_00411ff0);
  if ((param_4 == 3) || (DAT_00412608 != 0)) {
    local_58 = DAT_00412604;
  }
  else {
    local_58 = DAT_0041260c;
  }
  DAT_004125fc = local_58;
  sVar3 = _strlen(&DAT_00411ff0);
  if (sVar3 != DAT_004125fc * 2) {
    FUN_004059a7(s_improper_number_of_bytes_in_word_0040e4d0);
  }
  if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
    FUN_00403e89(&DAT_00411ff0,param_4);
  }
  if (param_4 == 2) {
    sprintf(&DAT_004121f0,DAT_00412630,local_3c[1] & _DAT_00412618);
    FUN_004052db(&DAT_004121f0);
    sVar3 = _strlen(&DAT_004121f0);
    if (sVar3 != DAT_004125fc * 2) {
      FUN_004059a7(s_improper_number_of_bytes_in_word_0040e4f4);
    }
    if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
      FUN_00403e89(&DAT_004121f0,2);
    }
  }
  else {
    FID_conflict___mbscpy(&DAT_004121f0,&DAT_00411ff0);
  }
  if ((param_4 == 3) || (DAT_00412608 != 0)) {
    local_5c = DAT_00412604;
  }
  else {
    local_5c = DAT_0041260c;
  }
  DAT_004125fc = local_5c;
  local_18 = 0;
  local_8 = (int)(&DAT_00412648)[local_1c];
  while( true ) {
    if (DAT_00411fcc == 0) {
      local_60 = 1;
    }
    else {
      local_60 = DAT_004125fc;
    }
    if ((int)local_60 <= local_18) break;
    *(undefined4 *)(local_8 + 4) = 0;
    *(int *)(local_8 + 8) = local_8 + 0xc;
    local_18 = local_18 + 1;
    local_8 = local_8 + 0x5c;
  }
  for (local_18 = 0; local_18 < local_c; local_18 = local_18 + 1) {
    if (DAT_00411fd4 == 0) {
      local_64 = &DAT_004121f0;
    }
    else {
      local_64 = &DAT_00411ff0;
    }
    FUN_00403b31(local_1c,local_64);
    if (param_4 == 2) {
      if (DAT_00411fd4 == 0) {
        local_68 = &DAT_00411ff0;
      }
      else {
        local_68 = &DAT_004121f0;
      }
      FUN_00403b31(local_1c,local_68);
    }
    if ((param_4 == 3) || (DAT_00412608 != 0)) {
      local_6c = DAT_00412604;
    }
    else {
      local_6c = DAT_0041260c;
    }
    DAT_004125fc = local_6c;
    if ((DAT_00411b90 == 0x2ca) && (param_4 == 4)) {
      local_70 = DAT_00412600;
    }
    else {
      local_70 = local_6c;
    }
    local_14 = local_70;
    if (param_4 == 2) {
      if ((DAT_00411fcc == 0) && (DAT_00411fec == 0)) {
        local_78 = local_6c << 1;
      }
      else {
        local_74 = 2;
        local_78 = local_74;
      }
    }
    else if ((DAT_00411fcc != 0) || (local_78 = local_6c, DAT_00411fec != 0)) {
      local_78 = 1;
    }
    local_10 = local_10 + local_78;
    if (((local_10 & 1) == 0) && (0x1d < local_10)) {
      FUN_00403c48(local_1c,local_3c[2],local_10);
      if ((DAT_00411fd8 == 0) && ((DAT_00411fcc == 0 && (DAT_00411fec == 0)))) {
        if ((DAT_00411fe0 == 0) || (param_3 != 2)) {
          local_10 = local_10 / local_14;
        }
        else {
          local_10 = local_10 / local_14 >> 1;
        }
      }
      local_3c[2] = local_3c[2] + local_10;
      local_10 = 0;
    }
  }
  if (*(int *)((int)(&DAT_00412648)[local_1c] + 8) != (int)(&DAT_00412648)[local_1c] + 0xc) {
    FUN_00403c48(local_1c,local_3c[2],local_10);
  }
  return;
}


/* ==== FUN_004026c8 @ 004026c8 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004026c8(void)

{
  int va0;
  int iVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  int local_24;
  undefined4 *local_20;
  uint local_1c;
  int local_18;
  int local_14;
  undefined4 *local_8;
  
  local_1c = DAT_00411964 + _DAT_0041266c;
  DAT_004125fc = DAT_00412604;
  if ((DAT_00411fcc == 0) && (DAT_00411fd8 != 0)) {
    local_1c = local_1c * DAT_00412604;
  }
  sprintf(&DAT_00411ff0,DAT_0041263c,local_1c & _DAT_00412624);
  iVar1 = FUN_00403ae9(local_1c & _DAT_00412624);
  va0 = DAT_00412614;
  if (DAT_00412628 == 0) {
    FUN_00403d8f(local_1c);
  }
  for (local_14 = 0; local_14 < (int)((-(uint)(DAT_00411fc8 != 0) & 0xfffffffb) + 6);
      local_14 = local_14 + 1) {
    if ((&DAT_00412648)[local_14] != (undefined4 *)0x0) {
      local_18 = 0;
      if (DAT_00411fc8 == 0) {
        local_20 = (&DAT_00412648)[local_14];
      }
      else {
        local_20 = DAT_00412648;
      }
      local_8 = local_20;
      while( true ) {
        if (DAT_00411fcc == 0) {
          local_24 = 1;
        }
        else {
          local_24 = DAT_004125fc;
        }
        if (local_24 <= local_18) break;
        sprintf(&DAT_004123f0,DAT_00412644,va0,&DAT_00411ff0,~(iVar1 + va0) & 0xff);
        piVar4 = (int *)*local_8;
        pcVar2 = FUN_004052db(&DAT_004123f0);
        iVar3 = FUN_00406750(pcVar2,piVar4);
        if (iVar3 == -1) {
          FUN_004059a7(s_cannot_write_end_S_record_0040e518);
        }
        fclose((void *)*local_8);
        local_18 = local_18 + 1;
        local_8 = local_8 + 0x17;
      }
      free((&DAT_00412648)[local_14]);
      (&DAT_00412648)[local_14] = (undefined4 *)0x0;
    }
  }
  return;
}


/* ==== FUN_0040288c @ 0040288c ==== */

void __cdecl FUN_0040288c(undefined **param_1)

{
  int iVar1;
  uint uVar2;
  long offset;
  code *pcVar3;
  
  iVar1 = FUN_00402a1b(param_1);
  if (iVar1 == 0) {
    FUN_004059a7(s_no_START_record_0040e534);
  }
  do {
    if (((uint)param_1[3] & 0x10) != 0) {
      if (((uint)param_1[3] & 0x10) != 0) {
        FUN_00403882();
      }
      return;
    }
    uVar2 = FUN_00402ce7();
    switch(uVar2) {
    case 1:
      FUN_004059a7(s_duplicate_START_record_0040e544);
    case 2:
      FUN_00403882();
      return;
    case 3:
    case 4:
      if (uVar2 == 3) {
        pcVar3 = FUN_00402de2;
      }
      else {
        pcVar3 = FUN_004033aa;
      }
      uVar2 = FUN_00404267();
      if ((int)uVar2 < 0) {
        FUN_004059a7(s_invalid_DATA_BLOCKDATA_record_0040e55c);
      }
      iVar1 = FUN_00405011();
      if (iVar1 < 0) {
        FUN_004059a7(s_invalid_memory_space_specifier_0040e57c);
      }
      if ((iVar1 == 2) && (DAT_00411fe8 != 0)) {
        offset = ftell(DAT_00411fbc);
        (*pcVar3)(2,0);
        iVar1 = fseek(DAT_00411fbc,offset,0);
        if (iVar1 != 0) {
          FUN_004059a7(s_cannot_reset_data_pointer_in_L_m_0040e59c);
        }
        (*pcVar3)(2,1);
      }
      else {
        (*pcVar3)(iVar1,iVar1);
      }
      break;
    case 5:
      DAT_00411ff0 = 0;
      break;
    case 6:
      FUN_004043b4();
      break;
    default:
      if (((uint)param_1[3] & 0x10) == 0) {
        FUN_004059a7(s_invalid_record_type_0040e5c4);
      }
    }
  } while( true );
}


/* ==== FUN_00402a1b @ 00402a1b ==== */

undefined4 __cdecl FUN_00402a1b(undefined **param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *local_18;
  char *local_10;
  byte *local_c;
  
  local_c = &DAT_00411ff0;
  local_18 = &DAT_00411db0;
  do {
    uVar1 = FUN_00402ce7();
    if (0 < (int)uVar1) break;
  } while (uVar1 != 0xffffffff);
  if (uVar1 == 0xffffffff) {
    uVar2 = 0;
  }
  else if (uVar1 == 1) {
    iVar3 = FUN_004044b0();
    if (iVar3 < 0) {
      FUN_004059a7(s_invalid_START_record_0040e600);
    }
    pcVar4 = FUN_00404520(&DAT_004123f0);
    if (pcVar4 == (char *)0x0) {
      FUN_004059a7(s_invalid_START_record_0040e618);
    }
    if (param_1 == &PTR_DAT_0040f2c8) {
      FUN_0040524b(&DAT_00411ff0,&DAT_0040e630);
      pcVar5 = _strrchr(DAT_00411fb8,0x2e);
      if (pcVar5 != (char *)0x0) {
        *pcVar5 = '\0';
      }
    }
    for (; *local_c != 0; local_c = local_c + 1) {
      sprintf(local_18,&DAT_0040e638,(int)(char)*local_c);
      DAT_004125f4 = DAT_004125f4 + (uint)*local_c;
      local_18 = local_18 + 2;
      DAT_0040e0ec = DAT_0040e0ec + 1;
    }
    FUN_00404600(0);
    local_10 = FUN_00404520(pcVar4);
    if (((local_10 == (char *)0x0) ||
        (pcVar4 = FUN_00404520(local_10), local_10 = pcVar4, pcVar4 == (char *)0x0)) ||
       (local_10 = FUN_00404520(pcVar4), local_10 == (char *)0x0)) {
      pcVar4 = (char *)0x1;
    }
    if (pcVar4 == (char *)0x0) {
      pcVar4 = FUN_00404520(local_10);
      if (pcVar4 == (char *)0x0) {
        FUN_004059a7(s_invalid_START_record_0040e668);
      }
      iVar3 = _strncmp(&DAT_00411ff0,&DAT_0040e680,3);
      if (iVar3 != 0) {
        FUN_004059a7(s_invalid_START_record_0040e684);
      }
      if ((DAT_004125f8 == 0) && (DAT_004125f8 = FUN_00404662(&DAT_00411ff3), DAT_004125f8 == 0)) {
        FUN_004059a7(s_invalid_machine_type_0040e69c);
      }
      pcVar4 = FUN_00404520(pcVar4);
      if (pcVar4 == (char *)0x0) {
        FUN_004059a7(s_invalid_START_record_0040e6b4);
      }
    }
    else if ((DAT_004125f8 == 0) &&
            (DAT_004125f8 = FUN_00404662(s_56000_0040e640), DAT_004125f8 == 0)) {
      FUN_004059a7(s_cannot_initialize_machine_type_0040e648);
    }
    iVar3 = FUN_004043b4();
    if (iVar3 < 0) {
      FUN_004059a7(s_invalid_START_record_0040e6cc);
    }
    if (DAT_00411fc8 != 0) {
      FUN_00403fc9(0);
    }
    uVar2 = 1;
  }
  else {
    if ((DAT_004125f8 == 0) && (DAT_004125f8 = FUN_00404662(s_56000_0040e5d8), DAT_004125f8 == 0)) {
      FUN_004059a7(s_cannot_initialize_machine_type_0040e5e0);
    }
    FUN_00404600(0);
    if (DAT_00411fc8 != 0) {
      FUN_00403fc9(0);
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ==== FUN_00402ce7 @ 00402ce7 ==== */

uint FUN_00402ce7(void)

{
  int iVar1;
  uint local_c;
  
  local_c = 0;
  do {
    if (DAT_00411ff0 == '_') break;
    local_c = FUN_00404267();
  } while (local_c == 0);
  if (-1 < (int)local_c) {
    FUN_004052db(&DAT_00411ff1);
    iVar1 = _strcmp(&DAT_00411ff1,&DAT_0040e6e4);
    if (iVar1 == 0) {
      local_c = 3;
    }
    else {
      iVar1 = _strcmp(&DAT_00411ff1,s_BLOCKDATA_0040e6ec);
      if (iVar1 == 0) {
        local_c = 4;
      }
      else {
        iVar1 = _strcmp(&DAT_00411ff1,s_START_0040e6f8);
        if (iVar1 == 0) {
          local_c = 1;
        }
        else {
          iVar1 = _strcmp(&DAT_00411ff1,&DAT_0040e700);
          if (iVar1 == 0) {
            local_c = 2;
          }
          else {
            iVar1 = _strcmp(&DAT_00411ff1,s_SYMBOL_0040e704);
            if (iVar1 == 0) {
              local_c = 5;
            }
            else {
              iVar1 = _strcmp(&DAT_00411ff1,s_COMMENT_0040e70c);
              if (iVar1 == 0) {
                local_c = 6;
              }
              else {
                local_c = 0;
              }
            }
          }
        }
      }
    }
  }
  return local_c;
}


/* ==== FUN_00402de2 @ 00402de2 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00402de2(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  size_t sVar3;
  undefined3 extraout_var_01;
  bool bVar4;
  uint local_54;
  uint local_50;
  undefined *local_4c;
  undefined1 *local_48;
  uint local_44;
  uint local_40;
  char *local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  int local_c;
  uint local_8;
  
  local_1c = param_2;
  if (DAT_00411fd4 == 0) {
    bVar4 = param_2 == 0;
  }
  else {
    bVar4 = param_2 != 0;
  }
  local_28 = (uint)bVar4;
  local_20 = local_28;
  local_10 = 0;
  if (DAT_00411fc8 == 0) {
    if ((&DAT_00412648)[param_2] == (undefined4 *)0x0) {
      FUN_00403fc9(param_2);
    }
  }
  else {
    local_18 = param_2 + 1;
    local_1c = 0;
    if (DAT_004125f0 != local_18) {
      FUN_00404600(local_18);
      iVar1 = FUN_00406750(&DAT_00411db0,(int *)*DAT_00412648);
      if (iVar1 == -1) {
        FUN_004059a7(s_cannot_write_S0_record_0040e714);
      }
      DAT_004125f0 = local_18;
    }
  }
  uVar2 = FUN_00404267();
  if ((int)uVar2 < 0) {
    FUN_004059a7(s_invalid_DATA_record_0040e72c);
  }
  bVar4 = FUN_0040539e();
  if (CONCAT31(extraout_var,bVar4) == 0) {
    FUN_004059a7(s_invalid_address_value_0040e740);
  }
  sscanf(&DAT_00411ff0,&DAT_0040e758,&local_24);
  local_24 = local_24 + *(int *)(&DAT_00412660 + param_2 * 4);
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_2c = DAT_00412604;
  }
  else {
    local_2c = DAT_0041260c;
  }
  DAT_004125fc = local_2c;
  if ((DAT_00411b90 == 0x2ca) && (param_2 == 4)) {
    local_30 = DAT_00412600;
  }
  else {
    local_30 = local_2c;
  }
  local_14 = local_30;
  if ((DAT_00411fcc == 0) && (DAT_00411fd8 != 0)) {
    local_24 = local_24 * local_30;
  }
  if (((DAT_00411fe0 != 0) && (param_2 == 2)) && (DAT_00411fd8 != 0)) {
    local_24 = local_24 << 1;
  }
  local_18 = 0;
  local_c = (int)(&DAT_00412648)[local_1c];
  while( true ) {
    if (DAT_00411fcc == 0) {
      local_34 = 1;
    }
    else {
      local_34 = DAT_004125fc;
    }
    if ((int)local_34 <= (int)local_18) break;
    *(undefined4 *)(local_c + 4) = 0;
    *(int *)(local_c + 8) = local_c + 0xc;
    local_18 = local_18 + 1;
    local_c = local_c + 0x5c;
  }
  local_18 = 0;
  while (uVar2 = FUN_00404267(), uVar2 == 0) {
    if ((param_1 == param_2) || (((local_18 ^ local_20) & 1) == 0)) {
      bVar4 = FUN_0040539e();
      if (CONCAT31(extraout_var_00,bVar4) == 0) {
        FUN_004059a7(s_invalid_data_value_0040e75c);
      }
      sscanf(&DAT_00411ff0,&DAT_0040e770,&local_8);
      if ((param_2 == 3) || (DAT_00412608 != 0)) {
        local_38 = DAT_0041261c;
      }
      else {
        local_38 = DAT_00412620;
      }
      _DAT_00412618 = local_38;
      if ((param_2 == 3) || (DAT_00412608 != 0)) {
        local_3c = DAT_00412634;
      }
      else {
        local_3c = DAT_00412638;
      }
      DAT_00412630 = local_3c;
      sprintf(&DAT_00411ff0,local_3c,local_8 & local_38);
      FUN_004052db(&DAT_00411ff0);
      if ((param_2 == 3) || (DAT_00412608 != 0)) {
        local_40 = DAT_00412604;
      }
      else {
        local_40 = DAT_0041260c;
      }
      DAT_004125fc = local_40;
      if ((DAT_00411b90 == 0x2ca) && (param_2 == 4)) {
        local_44 = DAT_00412600;
      }
      else {
        local_44 = local_40;
      }
      local_14 = local_44;
      sVar3 = _strlen(&DAT_00411ff0);
      if (sVar3 != DAT_004125fc * 2) {
        FUN_004059a7(s_improper_number_of_bytes_in_word_0040e774);
      }
      if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
        FUN_00403e89(&DAT_00411ff0,param_2);
      }
      FID_conflict___mbscpy(&DAT_004121f0,&DAT_00411ff0);
      if (param_2 == 2) {
        uVar2 = FUN_00404267();
        if (uVar2 != 0) {
          FUN_004059a7(s_data_synchronization_error_0040e798);
        }
        bVar4 = FUN_0040539e();
        if (CONCAT31(extraout_var_01,bVar4) == 0) {
          FUN_004059a7(s_invalid_data_value_0040e7b4);
        }
        sscanf(&DAT_00411ff0,&DAT_0040e7c8,&local_8);
        sprintf(&DAT_00411ff0,DAT_00412630,local_8 & _DAT_00412618);
        FUN_004052db(&DAT_00411ff0);
        sVar3 = _strlen(&DAT_00411ff0);
        if (sVar3 != DAT_004125fc * 2) {
          FUN_004059a7(s_improper_number_of_bytes_in_word_0040e7cc);
        }
        if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
          FUN_00403e89(&DAT_00411ff0,2);
        }
      }
      if (DAT_00411fd4 == 0) {
        local_48 = &DAT_004121f0;
      }
      else {
        local_48 = &DAT_00411ff0;
      }
      FUN_00403b31(local_1c,local_48);
      if (param_2 == 2) {
        if (DAT_00411fd4 == 0) {
          local_4c = &DAT_00411ff0;
        }
        else {
          local_4c = &DAT_004121f0;
        }
        FUN_00403b31(local_1c,local_4c);
      }
      if (param_2 == 2) {
        if ((DAT_00411fcc == 0) && (DAT_00411fec == 0)) {
          local_54 = DAT_004125fc << 1;
        }
        else {
          local_50 = 2;
          local_54 = local_50;
        }
      }
      else if ((DAT_00411fcc != 0) || (local_54 = DAT_004125fc, DAT_00411fec != 0)) {
        local_54 = 1;
      }
      local_10 = local_10 + local_54;
      if (((local_10 & 1) == 0) && (0x1d < local_10)) {
        FUN_00403c48(local_1c,local_24,local_10);
        if ((DAT_00411fd8 == 0) && ((DAT_00411fcc == 0 && (DAT_00411fec == 0)))) {
          if ((DAT_00411fe0 == 0) || (param_2 != 2)) {
            local_10 = local_10 / local_14;
          }
          else {
            local_10 = local_10 / local_14 >> 1;
          }
        }
        local_24 = local_24 + local_10;
        local_10 = 0;
      }
    }
    local_18 = local_18 + 1;
  }
  if (*(int *)((int)(&DAT_00412648)[local_1c] + 8) != (int)(&DAT_00412648)[local_1c] + 0xc) {
    FUN_00403c48(local_1c,local_24,local_10);
  }
  return;
}


/* ==== FUN_004033aa @ 004033aa ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004033aa(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  size_t sVar4;
  undefined3 extraout_var_02;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  char *local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_20 = param_2;
  local_14 = 0;
  if (DAT_00411fc8 == 0) {
    if ((&DAT_00412648)[param_2] == (undefined4 *)0x0) {
      FUN_00403fc9(param_2);
    }
  }
  else {
    local_1c = param_2 + 1;
    local_20 = 0;
    if (DAT_004125f0 != local_1c) {
      FUN_00404600(local_1c);
      iVar2 = FUN_00406750(&DAT_00411db0,(int *)*DAT_00412648);
      if (iVar2 == -1) {
        FUN_004059a7(s_cannot_write_S0_record_0040e7f0);
      }
      DAT_004125f0 = local_1c;
    }
  }
  uVar3 = FUN_00404267();
  if ((int)uVar3 < 0) {
    FUN_004059a7(s_invalid_BLOCKDATA_record_0040e808);
  }
  bVar1 = FUN_0040539e();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    FUN_004059a7(s_invalid_address_value_0040e824);
  }
  sscanf(&DAT_00411ff0,&DAT_0040e83c,&local_28);
  local_28 = local_28 + *(int *)(&DAT_00412660 + param_2 * 4);
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_2c = DAT_00412604;
  }
  else {
    local_2c = DAT_0041260c;
  }
  DAT_004125fc = local_2c;
  if ((DAT_00411b90 == 0x2ca) && (param_2 == 4)) {
    local_30 = DAT_00412600;
  }
  else {
    local_30 = local_2c;
  }
  local_18 = local_30;
  if ((DAT_00411fcc == 0) && (DAT_00411fd8 != 0)) {
    local_28 = local_28 * local_30;
  }
  if (((DAT_00411fe0 != 0) && (param_2 == 2)) && (DAT_00411fd8 != 0)) {
    local_28 = local_28 << 1;
  }
  uVar3 = FUN_00404267();
  if ((int)uVar3 < 0) {
    FUN_004059a7(s_invalid_BLOCKDATA_record_0040e840);
  }
  bVar1 = FUN_0040539e();
  if (CONCAT31(extraout_var_00,bVar1) == 0) {
    FUN_004059a7(s_invalid_count_value_0040e85c);
  }
  sscanf(&DAT_00411ff0,&DAT_0040e870,&local_10);
  uVar3 = FUN_00404267();
  if ((int)uVar3 < 0) {
    FUN_004059a7(s_invalid_BLOCKDATA_record_0040e874);
  }
  bVar1 = FUN_0040539e();
  if (CONCAT31(extraout_var_01,bVar1) == 0) {
    FUN_004059a7(s_invalid_data_value_0040e890);
  }
  sscanf(&DAT_00411ff0,&DAT_0040e8a4,&local_8);
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_34 = DAT_0041261c;
  }
  else {
    local_34 = DAT_00412620;
  }
  _DAT_00412618 = local_34;
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_38 = DAT_00412634;
  }
  else {
    local_38 = DAT_00412638;
  }
  DAT_00412630 = local_38;
  sprintf(&DAT_00411ff0,local_38,local_8 & local_34);
  FUN_004052db(&DAT_00411ff0);
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_3c = DAT_00412604;
  }
  else {
    local_3c = DAT_0041260c;
  }
  DAT_004125fc = local_3c;
  sVar4 = _strlen(&DAT_00411ff0);
  if (sVar4 != DAT_004125fc * 2) {
    FUN_004059a7(s_improper_number_of_bytes_in_word_0040e8a8);
  }
  bVar1 = FUN_0040539e();
  if (CONCAT31(extraout_var_02,bVar1) == 0) {
    FUN_004059a7(s_invalid_data_value_0040e8cc);
  }
  if ((DAT_00411fd0 == 0) && (DAT_00411fcc == 0)) {
    FUN_00403e89(&DAT_00411ff0,param_2);
  }
  local_1c = 0;
  local_c = (int)(&DAT_00412648)[local_20];
  while( true ) {
    if (DAT_00411fcc == 0) {
      local_40 = 1;
    }
    else {
      local_40 = DAT_004125fc;
    }
    if ((int)local_40 <= local_1c) break;
    *(undefined4 *)(local_c + 4) = 0;
    *(int *)(local_c + 8) = local_c + 0xc;
    local_1c = local_1c + 1;
    local_c = local_c + 0x5c;
  }
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_44 = DAT_00412604;
  }
  else {
    local_44 = DAT_0041260c;
  }
  DAT_004125fc = local_44;
  if ((DAT_00411b90 == 0x2ca) && (param_2 == 4)) {
    local_48 = DAT_00412600;
  }
  else {
    local_48 = local_44;
  }
  local_18 = local_48;
  for (local_24 = 0; local_24 < local_10; local_24 = local_24 + 1) {
    FUN_00403b31(local_20,&DAT_00411ff0);
    if ((DAT_00411fcc == 0) && (DAT_00411fec == 0)) {
      local_4c = DAT_004125fc;
    }
    else {
      local_4c = 1;
    }
    local_14 = local_14 + local_4c;
    if (((local_14 & 1) == 0) && (0x1d < local_14)) {
      FUN_00403c48(local_20,local_28,local_14);
      if ((DAT_00411fd8 == 0) && ((DAT_00411fcc == 0 && (DAT_00411fec == 0)))) {
        if ((DAT_00411fe0 == 0) || (param_2 != 2)) {
          local_14 = local_14 / local_18;
        }
        else {
          local_14 = local_14 / local_18 >> 1;
        }
      }
      local_28 = local_28 + local_14;
      local_14 = 0;
    }
  }
  if (*(int *)((int)(&DAT_00412648)[local_20] + 8) != (int)(&DAT_00412648)[local_20] + 0xc) {
    FUN_00403c48(local_20,local_28,local_14);
  }
  return;
}


/* ==== FUN_00403882 @ 00403882 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00403882(void)

{
  bool bVar1;
  undefined3 extraout_var;
  char *pcVar2;
  int iVar3;
  uint va1;
  int *piVar4;
  int local_30;
  undefined4 *local_2c;
  int local_28;
  uint local_24;
  int local_20;
  int local_1c;
  int local_14;
  uint local_10;
  int local_c;
  undefined4 *local_8;
  
  local_14 = 1;
  local_c = 0;
  local_10 = FUN_00404267();
  if (0 < (int)local_10) {
    FUN_004059a7(s_invalid_END_record_0040e8e0);
  }
  if (local_10 == 0) {
    bVar1 = FUN_0040539e();
    if (CONCAT31(extraout_var,bVar1) == 0) {
      FUN_004059a7(s_invalid_address_value_0040e8f4);
    }
    sscanf(&DAT_00411ff0,&DAT_0040e90c,&local_24);
    local_24 = local_24 + _DAT_0041266c;
    DAT_004125fc = DAT_00412604;
    if ((DAT_00411fcc == 0) && (DAT_00411fd8 != 0)) {
      local_24 = local_24 * DAT_00412604;
    }
    sprintf(&DAT_00411ff0,DAT_0041263c,local_24 & _DAT_00412624);
    local_c = FUN_00403ae9(local_24 & _DAT_00412624);
    local_14 = DAT_00412614;
    if (DAT_00412628 == 0) {
      FUN_00403d8f(local_24);
    }
  }
  for (local_1c = 0; local_1c < (int)((-(uint)(DAT_00411fc8 != 0) & 0xfffffffb) + 6);
      local_1c = local_1c + 1) {
    if ((&DAT_00412648)[local_1c] != (undefined4 *)0x0) {
      if ((local_1c == 3) || (DAT_00412608 != 0)) {
        local_28 = DAT_00412604;
      }
      else {
        local_28 = DAT_0041260c;
      }
      DAT_004125fc = local_28;
      local_20 = 0;
      if (DAT_00411fc8 == 0) {
        local_2c = (&DAT_00412648)[local_1c];
      }
      else {
        local_2c = DAT_00412648;
      }
      local_8 = local_2c;
      while( true ) {
        if (DAT_00411fcc == 0) {
          local_30 = 1;
        }
        else {
          local_30 = DAT_004125fc;
        }
        if (local_30 <= local_20) break;
        va1 = ~(local_c + local_14) & 0xff;
        sprintf(&DAT_004123f0,DAT_00412644,local_14,va1,va1);
        piVar4 = (int *)*local_8;
        pcVar2 = FUN_004052db(&DAT_004123f0);
        iVar3 = FUN_00406750(pcVar2,piVar4);
        if (iVar3 == -1) {
          FUN_004059a7(s_cannot_write_end_S_record_0040e910);
        }
        fclose((void *)*local_8);
        local_20 = local_20 + 1;
        local_8 = local_8 + 0x17;
      }
      free((&DAT_00412648)[local_1c]);
      (&DAT_00412648)[local_1c] = (undefined4 *)0x0;
    }
  }
  return;
}


/* ==== FUN_00403ae9 @ 00403ae9 ==== */

int __cdecl FUN_00403ae9(uint param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    local_8 = local_8 + (param_1 & 0xff);
    param_1 = param_1 >> 8;
  }
  return local_8;
}


/* ==== FUN_00403b31 @ 00403b31 ==== */

void __cdecl FUN_00403b31(int param_1,undefined1 *param_2)

{
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  if ((param_1 == 3) || (DAT_00412608 != 0)) {
    local_18 = DAT_00412604;
  }
  else {
    local_18 = DAT_0041260c;
  }
  DAT_004125fc = local_18;
  local_10 = 0;
  local_c = (&DAT_00412648)[param_1];
  for (; local_10 < DAT_004125fc; local_10 = local_10 + 1) {
    if ((DAT_00411fec == 0) || (DAT_004125fc + -1 <= local_10)) {
      local_8 = *(undefined1 **)(local_c + 8);
      *local_8 = *param_2;
      local_8[1] = param_2[1];
      local_8 = local_8 + 2;
      *local_8 = 0;
      sscanf(*(char **)(local_c + 8),&DAT_0040e92c,&local_14);
      *(int *)(local_c + 4) = *(int *)(local_c + 4) + local_14;
      *(undefined1 **)(local_c + 8) = local_8;
    }
    param_2 = param_2 + 2;
    local_c = local_c + (uint)(DAT_00411fcc != 0) * 0x5c;
  }
  return;
}


/* ==== FUN_00403c48 @ 00403c48 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00403c48(int param_1,uint param_2)

{
  int iVar1;
  char *pcVar2;
  int va0;
  int in_stack_0000000c;
  int *piVar3;
  int local_14;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  if (DAT_00412628 == 0) {
    FUN_00403d8f(param_2);
  }
  va0 = in_stack_0000000c + DAT_00412614;
  if ((param_1 == 3) || (DAT_00412608 != 0)) {
    local_10 = DAT_00412604;
  }
  else {
    local_10 = DAT_0041260c;
  }
  DAT_004125fc = local_10;
  local_c = 0;
  local_8 = (undefined4 *)(&DAT_00412648)[param_1];
  while( true ) {
    if (DAT_00411fcc == 0) {
      local_14 = 1;
    }
    else {
      local_14 = DAT_004125fc;
    }
    if (local_14 <= local_c) break;
    iVar1 = FUN_00403ae9(param_2 & _DAT_00412624);
    local_8[1] = local_8[1] + iVar1;
    sprintf(&DAT_004123f0,DAT_00412640,va0,param_2 & _DAT_00412624,local_8 + 3,
            ~(local_8[1] + va0) & 0xff);
    piVar3 = (int *)*local_8;
    pcVar2 = FUN_004052db(&DAT_004123f0);
    iVar1 = FUN_00406750(pcVar2,piVar3);
    if (iVar1 == -1) {
      FUN_004059a7(s_cannot_write_start_S_record_0040e930);
    }
    local_8[1] = 0;
    local_8[2] = local_8 + 3;
    local_c = local_c + 1;
    local_8 = local_8 + 0x17;
  }
  return;
}


/* ==== FUN_00403d8f @ 00403d8f ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00403d8f(uint param_1)

{
  if (param_1 < 0x10000) {
    if (DAT_00412610 != 2) {
      DAT_00412610 = 2;
      _DAT_00412624 = 0xffff;
      DAT_0041263c = s__04lx_0040e94c;
      DAT_00412640 = s_S1_02lx_04lx_s_02x_0040e954;
      DAT_00412644 = s_S9_02lx_s_02x_0040e968;
    }
    DAT_00412614 = DAT_00412610 + 1;
  }
  else if (param_1 < 0x1000000) {
    if (DAT_00412610 != 3) {
      DAT_00412610 = 3;
      _DAT_00412624 = 0xffffff;
      DAT_0041263c = s__06lx_0040e978;
      DAT_00412640 = s_S2_02lx_06lx_s_02x_0040e980;
      DAT_00412644 = s_S8_02lx_s_02x_0040e994;
    }
    DAT_00412614 = DAT_00412610 + 1;
  }
  else {
    if (DAT_00412610 != 4) {
      DAT_00412610 = 4;
      _DAT_00412624 = 0xffffffff;
      DAT_0041263c = s__08lx_0040e9a4;
      DAT_00412640 = s_S3_02lx_08lx_s_02x_0040e9ac;
      DAT_00412644 = s_S7_02lx_s_02x_0040e9c0;
    }
    DAT_00412614 = DAT_00412610 + 1;
  }
  return;
}


/* ==== FUN_00403e89 @ 00403e89 ==== */

void __cdecl FUN_00403e89(undefined1 *param_1,int param_2)

{
  undefined1 uVar1;
  int local_c;
  
  if ((param_2 == 3) || (DAT_00412608 != 0)) {
    local_c = DAT_00412604;
  }
  else {
    local_c = DAT_0041260c;
  }
  DAT_004125fc = local_c;
  if (local_c == 2) {
    uVar1 = *param_1;
    *param_1 = param_1[2];
    param_1[2] = uVar1;
    uVar1 = param_1[1];
    param_1[1] = param_1[3];
    param_1[3] = uVar1;
  }
  else if (local_c == 4) {
    uVar1 = *param_1;
    *param_1 = param_1[6];
    param_1[6] = uVar1;
    uVar1 = param_1[1];
    param_1[1] = param_1[7];
    param_1[7] = uVar1;
    uVar1 = param_1[2];
    param_1[2] = param_1[4];
    param_1[4] = uVar1;
    uVar1 = param_1[3];
    param_1[3] = param_1[5];
    param_1[5] = uVar1;
  }
  else {
    uVar1 = *param_1;
    *param_1 = param_1[4];
    param_1[4] = uVar1;
    uVar1 = param_1[1];
    param_1[1] = param_1[5];
    param_1[5] = uVar1;
  }
  return;
}


/* ==== FUN_00403fc9 @ 00403fc9 ==== */

void __cdecl FUN_00403fc9(int param_1)

{
  int *extraout_EAX;
  undefined4 uVar1;
  size_t sVar2;
  int extraout_EAX_00;
  int iVar3;
  int extraout_EAX_01;
  uint local_220;
  uint local_21c;
  uint local_218;
  char local_214 [512];
  uint local_14;
  char local_10;
  int *local_c;
  char *local_8;
  
  local_8 = (char *)0x0;
  if (param_1 == 4) {
    local_218 = DAT_00412600;
  }
  else {
    if (param_1 == 3) {
      local_21c = DAT_00412604;
    }
    else {
      local_21c = DAT_0041260c;
    }
    local_218 = local_21c;
  }
  DAT_004125fc = local_218;
  if (DAT_00411fcc == 0) {
    local_220 = 1;
  }
  else {
    local_220 = local_218;
  }
  calloc(local_220,0x5c);
  local_c = extraout_EAX;
  if (extraout_EAX == (int *)0x0) {
    FUN_004059a7(s_cannot_allocate_S_record_structu_0040e9d0);
  }
  (&DAT_00412648)[param_1] = local_c;
  if (DAT_00411fb8 != 0) {
    if (DAT_00411fc8 == 0) {
      uVar1 = FUN_004050d8(param_1);
      local_10 = (char)uVar1;
    }
    else {
      local_10 = 's';
    }
    sprintf(local_214,s__s__c_0040e9f4,DAT_00411fb8,(int)local_10);
    sVar2 = _strlen(local_214);
    local_8 = local_214 + sVar2;
  }
  local_14 = DAT_004125fc;
  if (DAT_00411fcc == 0) {
    if (DAT_00411fb8 == 0) {
      *local_c = (int)&DAT_0040f2e8;
    }
    else {
      fopen(local_214,&DAT_0040e9fc);
      *local_c = extraout_EAX_00;
      if (*local_c == 0) {
        FUN_00405a02(s_cannot_open_output_file__s_0040ea00,local_214);
      }
      FUN_00405492(local_214,&DAT_0040ea24,&DAT_0040ea1c);
    }
    if ((DAT_00411fc8 == 0) && (iVar3 = FUN_00406750(&DAT_00411db0,(int *)*local_c), iVar3 == -1)) {
      FUN_004059a7(s_cannot_write_S0_record_0040ea2c);
    }
  }
  else {
    (&DAT_00412648)[param_1] = local_c;
    while (local_14 = local_14 - 1, -1 < (int)local_14) {
      if (DAT_00411fb8 == 0) {
        *local_c = (int)&DAT_0040f2e8;
      }
      else {
        *local_8 = (char)local_14 + '0';
        local_8[1] = '\0';
        fopen(local_214,&DAT_0040ea44);
        *local_c = extraout_EAX_01;
        if (*local_c == 0) {
          FUN_00405a02(s_cannot_open_output_file__s_0040ea48,local_214);
        }
        FUN_00405492(local_214,&DAT_0040ea6c,&DAT_0040ea64);
      }
      iVar3 = FUN_00406750(&DAT_00411db0,(int *)*local_c);
      if (iVar3 == -1) {
        FUN_004059a7(s_cannot_write_S0_record_0040ea74);
      }
      local_c = local_c + 0x17;
    }
  }
  return;
}


/* ==== FUN_00404267 @ 00404267 ==== */

uint FUN_00404267(void)

{
  uint uVar1;
  uint local_14;
  uint local_10;
  char local_c;
  undefined1 *local_8;
  
  while (uVar1 = FUN_00406610(DAT_00411fbc), uVar1 != 0xffffffff) {
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + uVar1 * 2) & 8;
    }
    else {
      local_10 = _isctype(uVar1,8);
    }
    if (local_10 == 0) break;
    if (uVar1 == 10) {
      DAT_0040e0e8 = DAT_0040e0e8 + 1;
    }
  }
  if (uVar1 == 0xffffffff) {
    uVar1 = 0xffffffff;
  }
  else {
    local_c = (char)uVar1;
    DAT_00411ff0 = local_c;
    local_8 = &DAT_00411ff1;
    while (uVar1 = FUN_00406610(DAT_00411fbc), uVar1 != 0xffffffff) {
      if (__mb_cur_max < 2) {
        local_14 = *(ushort *)(_pctype + uVar1 * 2) & 8;
      }
      else {
        local_14 = _isctype(uVar1,8);
      }
      if (local_14 != 0) break;
      local_c = (char)uVar1;
      if ((undefined1 *)0x1fd < local_8 + -0x411ff0) {
        *local_8 = local_c;
        local_8 = local_8 + 1;
        break;
      }
      *local_8 = local_c;
      local_8 = local_8 + 1;
    }
    *local_8 = 0;
    if (uVar1 != 0xffffffff) {
      ungetc(uVar1,DAT_00411fbc);
    }
    uVar1 = (uint)(DAT_00411ff0 == '_');
  }
  return uVar1;
}


/* ==== FUN_004043b4 @ 004043b4 ==== */

undefined4 FUN_004043b4(void)

{
  uint uVar1;
  undefined4 uVar2;
  uint local_10;
  undefined1 local_c;
  undefined1 *local_8;
  
  do {
    uVar1 = FUN_00406610(DAT_00411fbc);
    if ((uVar1 == 0xffffffff) || (uVar1 == 10)) break;
    if (__mb_cur_max < 2) {
      local_10 = *(ushort *)(_pctype + uVar1 * 2) & 8;
    }
    else {
      local_10 = _isctype(uVar1,8);
    }
  } while (local_10 != 0);
  if ((uVar1 == 0xffffffff) || (uVar1 != 10)) {
    uVar2 = 0xffffffff;
  }
  else {
    DAT_0040e0e8 = DAT_0040e0e8 + 1;
    local_8 = &DAT_00411ff0;
    while( true ) {
      uVar1 = FUN_00406610(DAT_00411fbc);
      if ((uVar1 == 0xffffffff) || (uVar1 == 10)) goto LAB_0040448f;
      local_c = (undefined1)uVar1;
      if ((undefined1 *)0x1fd < local_8 + -0x411ff0) break;
      *local_8 = local_c;
      local_8 = local_8 + 1;
    }
    *local_8 = local_c;
    local_8 = local_8 + 1;
LAB_0040448f:
    if (uVar1 == 10) {
      DAT_0040e0e8 = DAT_0040e0e8 + 1;
    }
    *local_8 = 0;
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_004044b0 @ 004044b0 ==== */

undefined4 FUN_004044b0(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_c;
  undefined1 *local_8;
  
  local_8 = &DAT_004123f0;
  while( true ) {
    uVar1 = FUN_00406610(DAT_00411fbc);
    if ((uVar1 == 0xffffffff) || (uVar1 == 10)) break;
    local_c = (undefined1)uVar1;
    *local_8 = local_c;
    local_8 = local_8 + 1;
  }
  if ((uVar1 == 0xffffffff) || (uVar1 != 10)) {
    uVar2 = 0xffffffff;
  }
  else {
    *local_8 = 0;
    ungetc(10,DAT_00411fbc);
    uVar2 = 0;
  }
  return uVar2;
}


/* ==== FUN_00404520 @ 00404520 ==== */

char * __cdecl FUN_00404520(char *param_1)

{
  uint local_10;
  uint local_c;
  char *local_8;
  
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *param_1 * 2) & 8;
    }
    else {
      local_c = _isctype((int)*param_1,8);
    }
    if (local_c == 0) break;
  }
  if (*param_1 == '\0') {
    param_1 = (char *)0x0;
  }
  else {
    local_8 = &DAT_00411ff0;
    for (; *param_1 != '\0'; param_1 = param_1 + 1) {
      if (__mb_cur_max < 2) {
        local_10 = *(ushort *)(_pctype + *param_1 * 2) & 8;
      }
      else {
        local_10 = _isctype((int)*param_1,8);
      }
      if (local_10 != 0) break;
      *local_8 = *param_1;
      local_8 = local_8 + 1;
    }
    *local_8 = '\0';
  }
  return param_1;
}


/* ==== FUN_00404600 @ 00404600 ==== */

void __cdecl FUN_00404600(int param_1)

{
  if (param_1 == 0) {
    FID_conflict___mbscpy(&DAT_00411990,&DAT_00411db0);
  }
  sprintf(&DAT_00411db0,s_S0_02x_04x_s_02x_0040ea8c,DAT_0040e0ec,param_1,&DAT_00411990,
          ~(DAT_004125f4 + DAT_0040e0ec + param_1) & 0xff);
  FUN_004052db(&DAT_00411db0);
  return;
}


/* ==== FUN_00404662 @ 00404662 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_00404662(char *param_1)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = _strcmp(param_1,s_56000_0040eaa0);
  if (iVar1 == 0) {
    local_8 = 1;
    DAT_0041260c = 3;
    DAT_00412604 = 3;
    DAT_004125fc = 3;
    DAT_00412610 = 2;
    DAT_0041261c = 0xffffff;
    DAT_00412620 = 0xffffff;
    _DAT_00412618 = 0xffffff;
    _DAT_00412624 = 0xffff;
    DAT_00412634 = s__06lx_0040eaa8;
    DAT_00412638 = s__06lx_0040eaa8;
    DAT_00412630 = s__06lx_0040eaa8;
    DAT_0041263c = s__04lx_0040eab0;
    DAT_00412640 = s_S1_02lx_04lx_s_02x_0040eab8;
    DAT_00412644 = s_S9_02lx_s_02x_0040eacc;
  }
  else {
    iVar1 = _strcmp(param_1,s_96000_0040eadc);
    if (iVar1 == 0) {
      local_8 = 2;
      DAT_0041260c = 4;
      DAT_00412604 = 4;
      DAT_004125fc = 4;
      DAT_00412610 = 4;
      DAT_0041261c = 0xffffffff;
      DAT_00412620 = 0xffffffff;
      _DAT_00412618 = 0xffffffff;
      _DAT_00412624 = 0xffffffff;
      DAT_00412634 = s__08lx_0040eae4;
      DAT_00412638 = s__08lx_0040eae4;
      DAT_00412630 = s__08lx_0040eae4;
      DAT_0041263c = s__08lx_0040eaec;
      DAT_00412640 = s_S3_02lx_08lx_s_02x_0040eaf4;
      DAT_00412644 = s_S7_02lx_s_02x_0040eb08;
    }
    else {
      iVar1 = _strcmp(param_1,&DAT_0040eb18);
      if (iVar1 == 0) {
        local_8 = 7;
        DAT_0041260c = 2;
        DAT_00412604 = 2;
        DAT_004125fc = 2;
        DAT_00412610 = 4;
        DAT_0041261c = 0xffff;
        DAT_00412620 = 0xffff;
        _DAT_00412618 = 0xffff;
        _DAT_00412624 = 0xffffffff;
        DAT_00412634 = s__04lx_0040eb1c;
        DAT_00412638 = s__04lx_0040eb1c;
        DAT_00412630 = s__04lx_0040eb1c;
        DAT_0041263c = s__08lx_0040eb24;
        DAT_00412640 = s_S3_02lx_08lx_s_02x_0040eb2c;
        DAT_00412644 = s_S9_02lx_s_02x_0040eb40;
      }
      else {
        iVar1 = _strcmp(param_1,s_56700_0040eb50);
        if (iVar1 == 0) {
          local_8 = 8;
          DAT_0041260c = 2;
          DAT_00412604 = 2;
          DAT_004125fc = 2;
          DAT_00412610 = 4;
          DAT_0041261c = 0xffff;
          DAT_00412620 = 0xffff;
          _DAT_00412618 = 0xffff;
          _DAT_00412624 = 0xffffffff;
          DAT_00412634 = s__04lx_0040eb58;
          DAT_00412638 = s__04lx_0040eb58;
          DAT_00412630 = s__04lx_0040eb58;
          DAT_0041263c = s__08lx_0040eb60;
          DAT_00412640 = s_S3_02lx_08lx_s_02x_0040eb68;
          DAT_00412644 = s_S9_02lx_s_02x_0040eb7c;
        }
        else {
          iVar1 = _strcmp(param_1,&DAT_0040eb8c);
          if ((iVar1 == 0) || (iVar1 = _strcmp(param_1,s_56100_0040eb94), iVar1 == 0)) {
            local_8 = 3;
            DAT_0041260c = 2;
            DAT_00412604 = 2;
            DAT_004125fc = 2;
            DAT_00412610 = 2;
            DAT_0041261c = 0xffff;
            DAT_00412620 = 0xffff;
            _DAT_00412618 = 0xffff;
            _DAT_00412624 = 0xffff;
            DAT_00412634 = s__04lx_0040eb9c;
            DAT_00412638 = s__04lx_0040eb9c;
            DAT_00412630 = s__04lx_0040eb9c;
            DAT_0041263c = s__04lx_0040eba4;
            DAT_00412640 = s_S1_02lx_04lx_s_02x_0040ebac;
            DAT_00412644 = s_S9_02lx_s_02x_0040ebc0;
          }
          else {
            iVar1 = _strcmp(param_1,s_56300_0040ebd0);
            if (iVar1 == 0) {
              local_8 = 4;
              DAT_0041260c = 3;
              DAT_00412604 = 3;
              DAT_004125fc = 3;
              DAT_00412610 = 3;
              DAT_0041261c = 0xffffff;
              DAT_00412620 = 0xffffff;
              _DAT_00412618 = 0xffffff;
              _DAT_00412624 = 0xffffff;
              DAT_00412634 = s__06lx_0040ebd8;
              DAT_00412638 = s__06lx_0040ebd8;
              DAT_00412630 = s__06lx_0040ebd8;
              DAT_0041263c = s__06lx_0040ebe0;
              DAT_00412640 = s_S2_02lx_06lx_s_02x_0040ebe8;
              DAT_00412644 = s_S8_02lx_s_02x_0040ebfc;
            }
            else {
              iVar1 = _strcmp(param_1,s_56800_0040ec0c);
              if (iVar1 == 0) {
                local_8 = 5;
                DAT_0041260c = 2;
                DAT_00412604 = 2;
                DAT_004125fc = 2;
                DAT_00412610 = 3;
                DAT_0041261c = 0xffff;
                DAT_00412620 = 0xffff;
                _DAT_00412618 = 0xffff;
                _DAT_00412624 = 0xffff;
                DAT_00412634 = s__04lx_0040ec14;
                DAT_00412638 = s__04lx_0040ec14;
                DAT_00412630 = s__04lx_0040ec14;
                DAT_0041263c = s__04lx_0040ec1c;
                DAT_00412640 = s_S1_02lx_04lx_s_02x_0040ec24;
                DAT_00412644 = s_S9_02lx_s_02x_0040ec38;
              }
              else {
                iVar1 = _strcmp(param_1,s_56600_0040ec48);
                if (iVar1 == 0) {
                  local_8 = 6;
                  DAT_00412600 = 1;
                  DAT_0041260c = 2;
                  DAT_004125fc = 2;
                  DAT_00412604 = 3;
                  DAT_00412610 = 3;
                  DAT_00412620 = 0xffff;
                  _DAT_00412618 = 0xffff;
                  DAT_0041261c = 0xffffff;
                  _DAT_00412624 = 0xffff;
                  DAT_00412638 = s__04lx_0040ec50;
                  DAT_00412630 = s__04lx_0040ec50;
                  DAT_00412634 = s__06lx_0040ec58;
                  DAT_0041263c = s__04lx_0040ec60;
                  DAT_00412640 = s_S1_02lx_04lx_s_02x_0040ec68;
                  DAT_00412644 = s_S9_02lx_s_02x_0040ec7c;
                }
              }
            }
          }
        }
      }
    }
  }
  if (DAT_00412628 == 2) {
    DAT_00412610 = DAT_00412628;
    _DAT_00412624 = 0xffff;
    DAT_0041263c = s__04lx_0040ec8c;
    DAT_00412640 = s_S1_02lx_04lx_s_02x_0040ec94;
    DAT_00412644 = s_S9_02lx_s_02x_0040eca8;
  }
  else if (DAT_00412628 == 3) {
    DAT_00412610 = DAT_00412628;
    _DAT_00412624 = 0xffffff;
    DAT_0041263c = s__06lx_0040ecb8;
    DAT_00412640 = s_S2_02lx_06lx_s_02x_0040ecc0;
    DAT_00412644 = s_S8_02lx_s_02x_0040ecd4;
  }
  else if (DAT_00412628 == 4) {
    DAT_00412610 = DAT_00412628;
    _DAT_00412624 = 0xffffffff;
    DAT_0041263c = s__08lx_0040ece4;
    DAT_00412640 = s_S3_02lx_08lx_s_02x_0040ecec;
    DAT_00412644 = s_S7_02lx_s_02x_0040ed00;
  }
  if (DAT_0041262c == 2) {
    DAT_00412604 = DAT_0041262c;
    DAT_0041260c = DAT_0041262c;
    DAT_004125fc = DAT_0041262c;
    DAT_0041261c = 0xffff;
    DAT_00412620 = 0xffff;
    _DAT_00412618 = 0xffff;
    DAT_00412634 = s__04lx_0040ed10;
    DAT_00412638 = s__04lx_0040ed10;
    DAT_00412630 = s__04lx_0040ed10;
  }
  else if (DAT_0041262c == 3) {
    DAT_00412604 = DAT_0041262c;
    DAT_0041260c = DAT_0041262c;
    DAT_004125fc = DAT_0041262c;
    DAT_0041261c = 0xffffff;
    DAT_00412620 = 0xffffff;
    _DAT_00412618 = 0xffffff;
    DAT_00412634 = s__06lx_0040ed18;
    DAT_00412638 = s__06lx_0040ed18;
    DAT_00412630 = s__06lx_0040ed18;
  }
  else if (DAT_0041262c == 4) {
    DAT_00412604 = DAT_0041262c;
    DAT_0041260c = DAT_0041262c;
    DAT_004125fc = DAT_0041262c;
    DAT_0041261c = 0xffffffff;
    DAT_00412620 = 0xffffffff;
    _DAT_00412618 = 0xffffffff;
    DAT_00412634 = s__08lx_0040ed20;
    DAT_00412638 = s__08lx_0040ed20;
    DAT_00412630 = s__08lx_0040ed20;
  }
  DAT_00412614 = DAT_00412610 + 1;
  return local_8;
}


/* ==== FUN_00404e75 @ 00404e75 ==== */

undefined4 __cdecl FUN_00404e75(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0x11d) {
    if (0x1b < param_1) {
      if (((DAT_004125f8 != 1) && (DAT_004125f8 != 4)) && (DAT_004125f8 != 6)) {
        return 0xffffffff;
      }
      return 4;
    }
    switch(param_1) {
    case 0:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
      uVar1 = 3;
      break;
    case 1:
    case 0x12:
    case 0x13:
    case 0x14:
      uVar1 = 0;
      break;
    case 2:
    case 0x17:
    case 0x18:
    case 0x19:
      if (((DAT_004125f8 == 1) || (DAT_004125f8 == 4)) ||
         ((DAT_004125f8 == 6 || (DAT_004125f8 == 2)))) {
        uVar1 = 1;
      }
      else {
        uVar1 = 0xffffffff;
      }
      break;
    case 3:
    case 9:
    case 10:
      if (((DAT_004125f8 == 1) || (DAT_004125f8 == 4)) ||
         ((DAT_004125f8 == 6 || (DAT_004125f8 == 2)))) {
        uVar1 = 2;
      }
      else {
        uVar1 = 0xffffffff;
      }
      break;
    case 4:
      uVar1 = 0;
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      if (DAT_004125f8 == 2) {
        uVar1 = 2;
      }
      else {
        uVar1 = 0xffffffff;
      }
      break;
    case 0x10:
    case 0x11:
      if (DAT_004125f8 == 2) {
        uVar1 = 0;
      }
      else {
        uVar1 = 0xffffffff;
      }
      break;
    case 0x15:
    case 0x16:
      if (DAT_004125f8 == 2) {
        uVar1 = 1;
      }
      else {
        uVar1 = 0xffffffff;
      }
      break;
    default:
      goto switchD_00404ea7_default;
    }
  }
  else {
    if (param_1 == 0x11d) {
      if (DAT_004125f8 != 1) {
        return 0xffffffff;
      }
      return 5;
    }
switchD_00404ea7_default:
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


/* ==== FUN_00405011 @ 00405011 ==== */

undefined4 FUN_00405011(void)

{
  undefined4 uVar1;
  
  switch(DAT_00411ff0) {
  case 0x44:
  case 100:
    uVar1 = 5;
    break;
  case 0x45:
  case 0x65:
    uVar1 = 4;
    break;
  default:
    uVar1 = 0xffffffff;
    break;
  case 0x4c:
  case 0x6c:
    uVar1 = 2;
    break;
  case 0x50:
  case 0x70:
    uVar1 = 3;
    break;
  case 0x58:
  case 0x78:
    uVar1 = 0;
    break;
  case 0x59:
  case 0x79:
    uVar1 = 1;
  }
  return uVar1;
}


/* ==== FUN_004050d8 @ 004050d8 ==== */

undefined4 __cdecl FUN_004050d8(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0:
    uVar1 = 0x78;
    break;
  case 1:
    uVar1 = 0x79;
    break;
  case 2:
    uVar1 = 0x6c;
    break;
  case 3:
    uVar1 = 0x70;
    break;
  case 4:
    uVar1 = 0x65;
    break;
  case 5:
    uVar1 = 100;
    break;
  default:
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0040513a @ 0040513a ==== */

undefined4 __cdecl FUN_0040513a(char *param_1)

{
  uint uVar1;
  int iVar2;
  char local_20;
  uint local_1c;
  char local_18 [8];
  char *local_10;
  char *local_c;
  int local_8;
  
  local_10 = FUN_0040541b(param_1);
  if ((local_10 == (char *)0x0) || (local_c = _strrchr(local_10,0x2e), local_c == (char *)0x0)) {
    return 0;
  }
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_1c = *(ushort *)(_pctype + local_c[local_8] * 2) & 1;
    }
    else {
      local_1c = _isctype((int)local_c[local_8],1);
    }
    if (local_1c == 0) {
      local_20 = local_c[local_8];
    }
    else {
      uVar1 = FUN_00406060((int)local_c[local_8]);
      local_20 = (char)uVar1;
    }
    local_18[local_8] = local_20;
  }
  local_18[local_8] = '\0';
  iVar2 = _strncmp(local_18,&DAT_0040ed28,4);
  if (iVar2 == 0) {
    return 1;
  }
  iVar2 = _strncmp(local_18,&DAT_0040ed30,4);
  if (iVar2 == 0) {
    return 2;
  }
  return 0xffffffff;
}


/* ==== FUN_0040524b @ 0040524b ==== */

uint __cdecl FUN_0040524b(char *param_1,char *param_2)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  char *local_10;
  
  pcVar1 = FUN_0040541b(param_1);
  sVar2 = _strlen(param_1);
  local_10 = _strrchr(param_1,0x2e);
  if ((local_10 == (char *)0x0) || (local_10 < pcVar1)) {
    local_10 = param_1 + sVar2;
  }
  iVar3 = _strncmp(local_10,param_2,4);
  if (iVar3 != 0) {
    FID_conflict___mbscpy(local_10,param_2);
  }
  return -(uint)(iVar3 != 0) & (uint)local_10;
}


/* ==== FUN_004052db @ 004052db ==== */

char * __cdecl FUN_004052db(char *param_1)

{
  uint uVar1;
  uint local_10;
  uint local_c;
  char *local_8;
  
  for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 0x103;
    }
    else {
      local_c = _isctype((int)*local_8,0x103);
    }
    if (local_c != 0) {
      if (__mb_cur_max < 2) {
        local_10 = *(ushort *)(_pctype + *local_8 * 2) & 2;
      }
      else {
        local_10 = _isctype((int)*local_8,2);
      }
      if (local_10 != 0) {
        uVar1 = FUN_00406ac0((int)*local_8);
        *local_8 = (char)uVar1;
      }
    }
  }
  return param_1;
}


/* ==== FUN_0040539e @ 0040539e ==== */

bool FUN_0040539e(void)

{
  uint local_c;
  char *local_8;
  
  for (local_8 = &DAT_00411ff0; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 0x80;
    }
    else {
      local_c = _isctype((int)*local_8,0x80);
    }
    if (local_c == 0) break;
  }
  return *local_8 == '\0';
}


/* ==== FUN_0040541b @ 0040541b ==== */

char * __cdecl FUN_0040541b(char *param_1)

{
  size_t sVar1;
  char *local_8;
  
  if (param_1 == (char *)0x0) {
    param_1 = (char *)0x0;
  }
  else {
    sVar1 = _strlen(param_1);
    for (local_8 = param_1 + sVar1;
        ((param_1 <= local_8 && (*local_8 != '\\')) && (*local_8 != ':')); local_8 = local_8 + -1) {
    }
    if (param_1 <= local_8) {
      param_1 = local_8 + 1;
    }
  }
  return param_1;
}


/* ==== FUN_00405492 @ 00405492 ==== */

undefined4 FUN_00405492(void)

{
  return 1;
}


/* ==== FUN_0040549c @ 0040549c ==== */

uint __cdecl FUN_0040549c(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = FUN_00406bc0(param_1,param_2,param_3,param_4);
  FUN_004054d6(param_1,param_2,param_3);
  return uVar1;
}


/* ==== FUN_004054d6 @ 004054d6 ==== */

void __cdecl FUN_004054d6(undefined1 *param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 *local_c;
  
  for (local_c = param_1; local_c < param_1 + (param_2 * param_3 & 0xfffffffc);
      local_c = local_c + 4) {
    uVar1 = *local_c;
    *local_c = local_c[3];
    local_c[3] = uVar1;
    uVar1 = local_c[1];
    local_c[1] = local_c[2];
    local_c[2] = uVar1;
  }
  return;
}


/* ==== FUN_0040554c @ 0040554c ==== */

undefined4 __cdecl FUN_0040554c(char param_1,int param_2,undefined4 *param_3)

{
  uint local_10;
  uint local_c;
  char *local_8;
  
  do {
    do {
      param_3 = param_3 + 1;
      param_2 = param_2 + -1;
      if (param_2 < 1) {
        return 0;
      }
    } while (*(char *)*param_3 != '-');
    local_8 = (char *)*param_3;
    while (local_8 = local_8 + 1, *local_8 != '\0') {
      if (__mb_cur_max < 2) {
        local_c = *(ushort *)(_pctype + *local_8 * 2) & 1;
      }
      else {
        local_c = _isctype((int)*local_8,1);
      }
      if (local_c == 0) {
        local_10 = (uint)*local_8;
      }
      else {
        local_10 = FUN_00406060((int)*local_8);
      }
      if (local_10 == (int)param_1) {
        return *param_3;
      }
    }
  } while( true );
}


/* ==== FUN_00405628 @ 00405628 ==== */

int __cdecl FUN_00405628(int param_1,int param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  DAT_00411fb0 = (char *)0x0;
  if ((DAT_00412678 == (char *)0x0) || (*DAT_00412678 == '\0')) {
    if (DAT_00411fb4 == 0) {
      DAT_00411fb4 = 1;
    }
    if (((param_1 <= DAT_00411fb4) || (**(char **)(param_2 + DAT_00411fb4 * 4) != '-')) ||
       (*(char *)(*(int *)(param_2 + DAT_00411fb4 * 4) + 1) == '\0')) {
      DAT_00411fb0 = (char *)0x0;
      return -1;
    }
    iVar2 = _strcmp(*(char **)(param_2 + DAT_00411fb4 * 4),&DAT_0040ed38);
    if (iVar2 == 0) {
      DAT_00411fb4 = DAT_00411fb4 + 1;
      return -1;
    }
    DAT_00412678 = (char *)(*(int *)(param_2 + DAT_00411fb4 * 4) + 1);
    DAT_00411fb4 = DAT_00411fb4 + 1;
  }
  cVar1 = *DAT_00412678;
  DAT_00412678 = DAT_00412678 + 1;
  pcVar3 = _strchr(param_3,(int)cVar1);
  if ((pcVar3 == (char *)0x0) || (cVar1 == ':')) {
    fprintf(&DAT_0040f308,s__s__unknown_option___c_0040ed3c,*(undefined4 *)param_2,(int)cVar1);
    iVar2 = 0x3f;
  }
  else {
    if (pcVar3[1] == ':') {
      if (*DAT_00412678 == '\0') {
        if (param_1 <= DAT_00411fb4) {
          fprintf(&DAT_0040f308,s__s____c_argument_missing_0040ed54,*(undefined4 *)param_2,
                  (int)cVar1);
          return 0x3f;
        }
        DAT_00411fb0 = *(char **)(param_2 + DAT_00411fb4 * 4);
        DAT_00411fb4 = DAT_00411fb4 + 1;
      }
      else {
        DAT_00411fb0 = DAT_00412678;
        DAT_00412678 = (char *)0x0;
      }
    }
    iVar2 = (int)cVar1;
  }
  return iVar2;
}


/* ==== FUN_004057ec @ 004057ec ==== */

undefined4 __cdecl FUN_004057ec(undefined4 *param_1)

{
  return *param_1;
}


/* ==== FUN_004057f6 @ 004057f6 ==== */

void __cdecl FUN_004057f6(int param_1)

{
  if (param_1 == 2) {
    fprintf(&DAT_0040f308,s__s__Interrupted_0040ed70,PTR_DAT_0040e070);
    exit(-1);
  }
  else if (param_1 == 0xb) {
    fprintf(&DAT_0040f308,s__s__Fatal_segmentation_or_protec_0040ed84,PTR_DAT_0040e070);
    exit(-1);
  }
  return;
}


/* ==== FUN_0040585a @ 0040585a ==== */

void FUN_0040585a(void)

{
  if (DAT_00411fe4 != 0) {
    fprintf(&DAT_0040f308,s__s__s__s_0040edcc,s_DSP_S_Record_Conversion_Utility_0040e078,
            s_Version_6_3_0040e098,s__C__Copyright_Motorola__Inc__198_0040e0a8);
  }
  fprintf(&DAT_0040f308,s_Usage___s___blmqrsuwx____a_<alen_0040edd8,PTR_DAT_0040e070);
  fprintf(&DAT_0040f308,s_a___<alen>_S_record_address_leng_0040ee40);
  fprintf(&DAT_0040f308,s_b___byte_addressing_0040ee6c);
  fprintf(&DAT_0040f308,s_c___truncate_words_to_bytes_0040ee8c);
  fprintf(&DAT_0040f308,s_l___long__double_word__addressin_0040eeb4);
  fprintf(&DAT_0040f308,s_m___multiple_output_files_0040eee0);
  fprintf(&DAT_0040f308,s_o___add_<offset>_to_<mem>_addres_0040ef04);
  fprintf(&DAT_0040f308,s_p___<procno>_load_file_format_0040ef34);
  fprintf(&DAT_0040f308,s_q___do_not_display_signon_banner_0040ef5c);
  fprintf(&DAT_0040f308,s_r___reverse_bytes_in_word_0040ef88);
  fprintf(&DAT_0040f308,s_s___single_output_file_0040efac);
  fprintf(&DAT_0040f308,s_t___<tlen>_target_word_length_0040efcc);
  fprintf(&DAT_0040f308,s_u___reverse_words_in_L_memory_0040eff4);
  fprintf(&DAT_0040f308,s_w___word_addressing_0040f01c);
  fprintf(&DAT_0040f308,s_x___convert_L_records_to_X_and_Y_0040f03c);
  exit(-1);
  return;
}


/* ==== FUN_004059a7 @ 004059a7 ==== */

void FUN_004059a7(void)

{
  undefined4 in_stack_00000004;
  
  if (DAT_00411fc0 == 1) {
    fprintf(&DAT_0040f308,s__s__at_line__d___s_0040f068,PTR_DAT_0040e070,DAT_0040e0e8,
            in_stack_00000004);
  }
  else {
    fprintf(&DAT_0040f308,s__s___s_0040f07c,PTR_DAT_0040e070,in_stack_00000004);
  }
  exit(-1);
  return;
}


/* ==== FUN_00405a02 @ 00405a02 ==== */

void __cdecl FUN_00405a02(char *param_1)

{
  undefined4 in_stack_00000008;
  
  if (DAT_00411fc0 == 1) {
    fprintf(&DAT_0040f308,s__s__at_line__d__0040f084,PTR_DAT_0040e070,DAT_0040e0e8);
  }
  else {
    fprintf(&DAT_0040f308,&DAT_0040f098,PTR_DAT_0040e070);
  }
  fprintf(&DAT_0040f308,param_1,in_stack_00000008);
  fprintf(&DAT_0040f308,&DAT_0040f0a0);
  exit(-1);
  return;
}


/* ==== _cinit @ 00405a80 ==== */

void _cinit(void)

{
  if (_FPinit != (code *)0x0) {
    (*_FPinit)();
  }
  _initterm(&DAT_0040e008,&DAT_0040e010);
  _initterm(&DAT_0040e000,&DAT_0040e004);
  return;
}


/* ==== exit @ 00405ab0 ==== */

void __cdecl exit(int status)

{
  doexit(status,0,0);
  return;
}


/* ==== __exit @ 00405ad0 ==== */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __exit(int _Code)

{
  doexit(_Code,1,0);
  return;
}


/* ==== doexit @ 00405af0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl doexit(int code,int quick,int retcaller)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  undefined4 *puVar2;
  UINT uExitCode;
  
  if (_C_Exit_Done == 1) {
    uExitCode = code;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  __C_Termination_Done = 1;
  _exitflag = (undefined1)retcaller;
  if (quick == 0) {
    if ((__onexitbegin != (undefined4 *)0x0) &&
       (puVar2 = (undefined4 *)(__onexitend + -4), puVar1 = __onexitbegin, __onexitbegin <= puVar2))
    {
      do {
        if ((code *)*puVar2 != (code *)0x0) {
          (*(code *)*puVar2)();
          puVar1 = __onexitbegin;
        }
        puVar2 = puVar2 + -1;
      } while (puVar1 <= puVar2);
    }
    _initterm(&DAT_0040e014,&DAT_0040e01c);
  }
  _initterm(&DAT_0040e020,&DAT_0040e024);
  if (retcaller == 0) {
    _C_Exit_Done = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(code);
  }
  return;
}


/* ==== _initterm @ 00405ba0 ==== */

void __cdecl _initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != (code *)0x0) {
      (**(code **)begin)();
    }
  }
  return;
}


/* ==== free @ 00405bc0 ==== */

void __cdecl free(void *p)

{
  void *lpMem;
  void *pmap;
  void *local_4;
  
  lpMem = p;
  if (p != (void *)0x0) {
    __sbh_find_block(p,&local_4,&p);
    if (pmap != (void *)0x0) {
      __sbh_free_block(local_4,p,pmap);
      return;
    }
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== fclose @ 00405c10 ==== */

int __cdecl fclose(void *stream)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  if ((*(uint *)((int)stream + 0xc) & 0x40) != 0) {
    *(undefined4 *)((int)stream + 0xc) = 0;
    return -1;
  }
  if ((*(uint *)((int)stream + 0xc) & 0x83) != 0) {
    iVar2 = _flush(stream);
    _freebuf(stream);
    iVar1 = _close(*(int *)((int)stream + 0x10));
    if (iVar1 < 0) {
      *(undefined4 *)((int)stream + 0xc) = 0;
      return -1;
    }
    if (*(void **)((int)stream + 0x1c) != (void *)0x0) {
      free(*(void **)((int)stream + 0x1c));
      *(undefined4 *)((int)stream + 0x1c) = 0;
    }
  }
  *(undefined4 *)((int)stream + 0xc) = 0;
  return iVar2;
}


/* ==== FID_conflict:__mbscpy @ 00405c90 ==== */

/* Library Function - Multiple Matches With Different Base Names
    __mbscpy
    _strcpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl FID_conflict___mbscpy(char *_Dest,char *_Source)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = (uint *)_Dest;
  while (((uint)_Source & 3) != 0) {
    bVar1 = (byte)*(uint *)_Source;
    uVar3 = (uint)bVar1;
    _Source = (char *)((int)_Source + 1);
    if (bVar1 == 0) goto LAB_00405d78;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *(uint *)_Source;
    uVar3 = *(uint *)_Source;
    _Source = (char *)((int)_Source + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_00405d78:
        *(byte *)puVar4 = (byte)uVar3;
        return _Dest;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return _Dest;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return _Dest;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return _Dest;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}


/* ==== _strlen @ 00405d80 ==== */

/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_00405da0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00405dd3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_00405da0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_00405dd3;
}


/* ==== malloc @ 00405e00 ==== */

void __cdecl malloc(uint size)

{
  _nh_malloc(size,_newmode);
  return;
}


/* ==== _nh_malloc @ 00405e20 ==== */

void __cdecl _nh_malloc(uint size,int nhFlag)

{
  int extraout_EAX;
  int iVar1;
  
  if (size < 0xffffffe1) {
    if (size == 0) {
      size = 1;
    }
    do {
      if (size < 0xffffffe1) {
        _heap_alloc(size);
        iVar1 = extraout_EAX;
      }
      else {
        iVar1 = 0;
      }
    } while (((iVar1 == 0) && (nhFlag != 0)) && (iVar1 = _callnewh(size), iVar1 != 0));
  }
  return;
}


/* ==== _heap_alloc @ 00405e70 ==== */

void __cdecl _heap_alloc(uint size)

{
  int extraout_EAX;
  uint dwBytes;
  
  dwBytes = size + 0xf & 0xfffffff0;
  if ((dwBytes <= __sbh_threshold) && (__sbh_alloc_block(size + 0xf >> 4), extraout_EAX != 0)) {
    return;
  }
  HeapAlloc(_crtheap,0,dwBytes);
  return;
}


/* ==== _strcmp @ 00405eb0 ==== */

/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      bVar4 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar5 = bVar4 < (byte)*_Str2;
      if (bVar4 != *_Str2) goto LAB_00405ef4;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_00405ec0;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_00405ef4;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_00405ef4;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_00405ec0:
  while( true ) {
    uVar2 = *(undefined4 *)_Str1;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 0x10);
    bVar5 = bVar4 < (byte)_Str2[2];
    if (bVar4 != _Str2[2]) break;
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < (byte)_Str2[3];
    if (bVar3 != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_00405ef4:
  return (uint)bVar5 * -2 + 1;
}


/* ==== _strchr @ 00405f50 ==== */

/* Library Function - Single Match
    _strchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strchr(char *_Str,int _Val)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)_Str & 3) != 0) {
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    _Str = (char *)((int)_Str + 1);
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *(uint *)_Str;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11((char)_Val,(char)_Val),CONCAT11((char)_Val,(char)_Val));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = (uint *)((int)_Str + 4);
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      _Str = (char *)puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (char *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (char *)0x0;
        }
      }
    }
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 1);
    }
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 3);
    }
    _Str = (char *)puVar5;
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}


/* ==== sscanf @ 00406010 ==== */

int __cdecl sscanf(char *buf,char *fmt,...)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 local_14;
  
  uVar3 = 0xffffffff;
  local_18 = buf;
  local_20 = buf;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *buf;
    buf = buf + 1;
  } while (cVar1 != '\0');
  local_1c = ~uVar3 - 1;
  local_14 = 0x49;
  iVar2 = _input(&local_20,fmt,&stack0x0000000c);
  return iVar2;
}


/* ==== FUN_00406060 @ 00406060 ==== */

uint __cdecl FUN_00406060(uint param_1)

{
  uint uVar1;
  uint uVar2;
  LPCWSTR pWVar3;
  int iVar4;
  uint local_8 [2];
  
  uVar1 = param_1;
  if (DAT_00412710 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      return param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[param_1 * 2] & 1;
      }
      else {
        uVar2 = _isctype(param_1,1);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((_pctype[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      param_1._0_2_ = (ushort)(byte)uVar1;
      pWVar3 = (LPCWSTR)0x1;
    }
    else {
      param_1._0_2_ = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      param_1._3_1_ = SUB41(uVar2,3);
      param_1._0_3_ = (uint3)(ushort)param_1;
      pWVar3 = (LPCWSTR)0x2;
    }
    iVar4 = FUN_00408660(DAT_00412710,0x100,(char *)&param_1,pWVar3,(LPWSTR)local_8,3,0);
    if (iVar4 == 0) {
      return uVar1;
    }
    if (iVar4 == 1) {
      return local_8[0] & 0xff;
    }
    param_1 = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return param_1;
}


/* ==== _isctype @ 00406160 ==== */

int __cdecl _isctype(int c,int mask)

{
  int iVar1;
  BOOL BVar2;
  uint local_4;
  
  iVar1 = c;
  if (c + 1U < 0x101) {
    return (uint)*(ushort *)(_pctype + c * 2) & mask;
  }
  if ((_pctype[(c >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
    c._0_2_ = (ushort)(byte)c;
    iVar1 = 1;
  }
  else {
    c._0_2_ = CONCAT11((byte)c,(char)((uint)c >> 8));
    c._3_1_ = SUB41(iVar1,3);
    c._0_3_ = (uint3)(ushort)c;
    iVar1 = 2;
  }
  BVar2 = FUN_004088b0(1,(LPCSTR)&c,iVar1,(LPWORD)&local_4,0,0);
  if (BVar2 == 0) {
    return 0;
  }
  return local_4 & 0xffff & mask;
}


/* ==== fprintf @ 00406200 ==== */

int __cdecl fprintf(void *stream,char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(stream);
  iVar1 = _output(stream,fmt,&stack0x0000000c);
  _ftbuf(flag,stream);
  return iVar1;
}


/* ==== _strrchr @ 00406320 ==== */

/* Library Function - Single Match
    _strrchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strrchr(char *_Str,int _Ch)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = _Str;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = _Str + 1;
    cVar1 = *_Str;
    _Str = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while ((char)_Ch != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != (char)_Ch) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}


/* ==== signal @ 00406350 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl signal(int sig,void *func)

{
  int *piVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  BOOL BVar3;
  
  if ((func == (void *)0x4) || (func == (void *)0x3)) {
    _errno = 0x16;
    return;
  }
  if (sig != 2) {
    if (((sig != 0x15) && (sig != 0x16)) && (sig != 0xf)) {
      if (((sig != 8) && (sig != 4)) && (sig != 0xb)) {
        _errno = 0x16;
        return;
      }
      siglookup(sig);
      if (extraout_EAX == (undefined4 *)0x0) {
        _errno = 0x16;
        return;
      }
      puVar2 = extraout_EAX;
      if (extraout_EAX[1] != sig) {
        return;
      }
      do {
        puVar2[2] = func;
        if (&_XcptActTab + _XcptActTabCount * 3 <= puVar2 + 3) {
          return;
        }
        piVar1 = puVar2 + 4;
        puVar2 = puVar2 + 3;
      } while (*piVar1 == sig);
      return;
    }
    if ((sig != 2) && (sig != 0x15)) goto LAB_00406404;
  }
  if (DAT_004126e0 == 0) {
    BVar3 = SetConsoleCtrlHandler((PHANDLER_ROUTINE)&LAB_004064c0,1);
    if (BVar3 != 1) {
      _doserrno = GetLastError();
      _errno = 0x16;
      return;
    }
    DAT_004126e0 = 1;
  }
LAB_00406404:
  switch(sig) {
  case 2:
    DAT_004126d0 = func;
    return;
  default:
    return;
  case 0xf:
    DAT_004126dc = func;
    return;
  case 0x15:
    DAT_004126d4 = func;
    return;
  case 0x16:
    DAT_004126d8 = func;
    return;
  }
}


/* ==== siglookup @ 00406510 ==== */

void __cdecl siglookup(int sig)

{
  int *piVar1;
  undefined4 *puVar2;
  
  if (DAT_004115ac != sig) {
    puVar2 = &_XcptActTab;
    do {
      if (&_XcptActTab + _XcptActTabCount * 3 <= puVar2 + 3) {
        return;
      }
      piVar1 = puVar2 + 4;
      puVar2 = puVar2 + 3;
    } while (*piVar1 != sig);
  }
  return;
}


/* ==== _fsopen @ 00406560 ==== */

void __cdecl _fsopen(char *name,char *mode,int shflag)

{
  void *stream;
  
  _getstream();
  if (stream == (void *)0x0) {
    return;
  }
  _openfile(name,mode,shflag,stream);
  return;
}


/* ==== fopen @ 00406590 ==== */

void __cdecl fopen(char *name,char *mode)

{
  _fsopen(name,mode,0x40);
  return;
}


/* ==== rewind @ 004065b0 ==== */

void __cdecl rewind(void *stream)

{
  uint fh;
  undefined *puVar1;
  
  fh = *(uint *)((int)stream + 0x10);
  _flush(stream);
  *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffffcf;
  if (fh == 0xffffffff) {
    puVar1 = &__badioinfo;
  }
  else {
    puVar1 = (undefined *)((&__pioinfo)[(int)fh >> 5] + (fh & 0x1f) * 8);
  }
  puVar1[4] = puVar1[4] & 0xfd;
  if ((*(uint *)((int)stream + 0xc) & 0x80) != 0) {
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xfffffffc;
  }
  _lseek(fh,0,0);
  return;
}


/* ==== FUN_00406610 @ 00406610 ==== */

uint __cdecl FUN_00406610(int *param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_1[1];
  param_1[1] = iVar2 + -1;
  if (-1 < iVar2 + -1) {
    bVar1 = *(byte *)*param_1;
    *param_1 = (int)((byte *)*param_1 + 1);
    return (uint)bVar1;
  }
  uVar3 = _filbuf(param_1);
  return uVar3;
}


/* ==== fseek @ 00406640 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl fseek(void *stream,long offset,int origin)

{
  uint uVar1;
  long lVar2;
  
  if (((*(uint *)((int)stream + 0xc) & 0x83) != 0) &&
     (((origin == 0 || (origin == 1)) || (origin == 2)))) {
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffffef;
    if (origin == 1) {
      lVar2 = ftell(stream);
      offset = offset + lVar2;
      origin = 0;
    }
    _flush(stream);
    uVar1 = *(uint *)((int)stream + 0xc);
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        *(undefined4 *)((int)stream + 0x18) = 0x200;
      }
    }
    else {
      *(uint *)((int)stream + 0xc) = uVar1 & 0xfffffffc;
    }
    lVar2 = _lseek(*(int *)((int)stream + 0x10),offset,origin);
    return (lVar2 != -1) - 1;
  }
  _errno = 0x16;
  return -1;
}


/* ==== sprintf @ 004066e0 ==== */

int __cdecl sprintf(char *buf,char *fmt,...)

{
  int iVar1;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 local_14;
  
  local_18 = buf;
  local_20 = buf;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = _output(&local_20,fmt,&stack0x0000000c);
  local_1c = local_1c + -1;
  if (-1 < local_1c) {
    *local_20 = '\0';
    return iVar1;
  }
  _flsbuf(0,&local_20);
  return iVar1;
}


/* ==== FUN_00406750 @ 00406750 ==== */

int __cdecl FUN_00406750(char *param_1,int *param_2)

{
  char cVar1;
  int flag;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0xffffffff;
  pcVar4 = param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  flag = _stbuf(param_2);
  uVar2 = fwrite(param_1,1,~uVar3 - 1,param_2);
  _ftbuf(flag,param_2);
  return -(uint)(uVar2 != ~uVar3 - 1);
}


/* ==== ftell @ 004067a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long __cdecl ftell(void *stream)

{
  uint fh;
  uint uVar1;
  char *pcVar2;
  int iVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  int local_8;
  int local_4;
  
  fh = *(uint *)((int)stream + 0x10);
  if (*(int *)((int)stream + 4) < 0) {
    *(undefined4 *)((int)stream + 4) = 0;
  }
  local_4 = _lseek(fh,0,1);
  if (local_4 < 0) {
    return -1;
  }
  uVar1 = *(uint *)((int)stream + 0xc);
  if ((uVar1 & 0x108) == 0) {
    return local_4 - *(int *)((int)stream + 4);
  }
  pcVar7 = *(char **)stream;
  pcVar2 = *(char **)((int)stream + 8);
  local_8 = (int)pcVar7 - (int)pcVar2;
  iVar3 = (int)fh >> 5;
  if ((uVar1 & 3) == 0) {
    if ((uVar1 & 0x80) == 0) {
      _errno = 0x16;
      return -1;
    }
  }
  else {
    pcVar5 = pcVar2;
    if ((*(byte *)((&__pioinfo)[iVar3] + 4 + (fh & 0x1f) * 8) & 0x80) != 0) {
      for (; pcVar5 < pcVar7; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          local_8 = local_8 + 1;
        }
      }
    }
  }
  if (local_4 == 0) {
    return local_8;
  }
  if ((*(byte *)((int)stream + 0xc) & 1) == 0) goto LAB_00406915;
  if (*(int *)((int)stream + 4) == 0) {
    return local_4;
  }
  pcVar7 = pcVar7 + (*(int *)((int)stream + 4) - (int)pcVar2);
  iVar6 = (fh & 0x1f) * 8;
  if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 0x80) != 0) {
    lVar4 = _lseek(fh,0,2);
    if (lVar4 == local_4) {
      pcVar5 = *(char **)((int)stream + 8);
      pcVar2 = pcVar5 + (int)pcVar7;
      for (; pcVar5 < pcVar2; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          pcVar7 = pcVar7 + 1;
        }
      }
      if ((*(uint *)((int)stream + 0xc) & 0x2000) != 0) {
LAB_0040690c:
        pcVar7 = pcVar7 + 1;
      }
    }
    else {
      _lseek(fh,local_4,0);
      if (((pcVar7 < (char *)0x201) && ((*(uint *)((int)stream + 0xc) & 8) != 0)) &&
         ((*(uint *)((int)stream + 0xc) & 0x400) == 0)) {
        pcVar7 = (char *)0x200;
      }
      else {
        pcVar7 = *(char **)((int)stream + 0x18);
      }
      if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 4) != 0) goto LAB_0040690c;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_00406915:
  return local_4 + local_8;
}


/* ==== _strncmp @ 00406950 ==== */

/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  sVar3 = _MaxCount;
  pcVar6 = _Str1;
  if (_MaxCount != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = _MaxCount - sVar3;
    do {
      pcVar6 = _Str2;
      pcVar7 = _Str1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = _Str1 + 1;
      pcVar6 = _Str2 + 1;
      cVar2 = *_Str1;
      cVar1 = *_Str2;
      _Str2 = pcVar6;
      _Str1 = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}


/* ==== calloc @ 00406990 ==== */

void __cdecl calloc(uint num,uint size)

{
  undefined4 *extraout_EAX;
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint dwBytes;
  undefined4 *puVar4;
  
  dwBytes = size * num;
  if (dwBytes < 0xffffffe1) {
    if (dwBytes == 0) {
      dwBytes = 0x10;
    }
    else {
      dwBytes = dwBytes + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar3 = (undefined4 *)0x0;
    if (dwBytes < 0xffffffe1) {
      if (__sbh_threshold < dwBytes) {
LAB_004069f0:
        if (puVar3 != (undefined4 *)0x0) {
          return;
        }
      }
      else {
        __sbh_alloc_block(dwBytes >> 4);
        if (extraout_EAX != (undefined4 *)0x0) {
          puVar4 = extraout_EAX;
          for (uVar2 = dwBytes >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          for (uVar2 = dwBytes & 3; puVar3 = extraout_EAX, uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar4 = 0;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
          goto LAB_004069f0;
        }
      }
      puVar3 = HeapAlloc(_crtheap,8,dwBytes);
    }
    if ((puVar3 != (undefined4 *)0x0) || (_newmode == 0)) {
      return;
    }
    iVar1 = _callnewh(dwBytes);
    if (iVar1 == 0) {
      return;
    }
  } while( true );
}


/* ==== ungetc @ 00406a30 ==== */

int __cdecl ungetc(int c,void *stream)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  
  if ((c != -1) &&
     ((uVar1 = *(uint *)((int)stream + 0xc), (uVar1 & 1) != 0 ||
      (((uVar1 & 0x80) != 0 && ((uVar1 & 2) == 0)))))) {
    if (*(int *)((int)stream + 8) == 0) {
      _getbuf(stream);
    }
    if (*(int *)stream == *(int *)((int)stream + 8)) {
      if (*(int *)((int)stream + 4) != 0) {
        return -1;
      }
      *(int *)stream = *(int *)stream + 1;
    }
    if ((*(byte *)((int)stream + 0xc) & 0x40) == 0) {
      iVar2 = *(int *)stream;
      *(char **)stream = (char *)(iVar2 + -1);
      *(char *)(iVar2 + -1) = (char)c;
    }
    else {
      iVar2 = *(int *)stream;
      pcVar3 = (char *)(iVar2 + -1);
      *(char **)stream = pcVar3;
      if (*pcVar3 != (char)c) {
        *(int *)stream = iVar2;
        return -1;
      }
    }
    *(int *)((int)stream + 4) = *(int *)((int)stream + 4) + 1;
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffffef | 1;
    return c & 0xff;
  }
  return -1;
}


/* ==== FUN_00406ac0 @ 00406ac0 ==== */

uint __cdecl FUN_00406ac0(uint param_1)

{
  uint uVar1;
  uint uVar2;
  LPCWSTR pWVar3;
  int iVar4;
  uint local_8 [2];
  
  uVar1 = param_1;
  if (DAT_00412710 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      return param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[param_1 * 2] & 2;
      }
      else {
        uVar2 = _isctype(param_1,2);
      }
      if (uVar2 == 0) {
        return uVar1;
      }
    }
    uVar2 = param_1;
    if ((_pctype[((int)uVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      param_1._0_2_ = (ushort)(byte)uVar1;
      pWVar3 = (LPCWSTR)0x1;
    }
    else {
      param_1._0_2_ = CONCAT11((byte)uVar1,(char)(uVar1 >> 8));
      param_1._3_1_ = SUB41(uVar2,3);
      param_1._0_3_ = (uint3)(ushort)param_1;
      pWVar3 = (LPCWSTR)0x2;
    }
    iVar4 = FUN_00408660(DAT_00412710,0x200,(char *)&param_1,pWVar3,(LPWSTR)local_8,3,0);
    if (iVar4 == 0) {
      return uVar1;
    }
    if (iVar4 == 1) {
      return local_8[0] & 0xff;
    }
    param_1 = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return param_1;
}


/* ==== FUN_00406bc0 @ 00406bc0 ==== */

uint __cdecl FUN_00406bc0(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *stream;
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  char *pcVar9;
  
  stream = param_4;
  piVar5 = (int *)(param_3 * param_2);
  if (piVar5 == (int *)0x0) {
    return 0;
  }
  piVar6 = piVar5;
  if ((param_4[3] & 0x10cU) == 0) {
    param_4 = (int *)0x1000;
    piVar8 = (int *)0x1000;
  }
  else {
    piVar8 = (int *)param_4[6];
    param_4 = piVar8;
  }
  do {
    if (((stream[3] & 0x10cU) == 0) || (piVar1 = (int *)stream[1], piVar1 == (int *)0x0)) {
      if (piVar6 < piVar8) {
        iVar3 = _filbuf(stream);
        if (iVar3 == -1) {
          return (uint)((int)piVar5 - (int)piVar6) / param_2;
        }
        *param_1 = (char)iVar3;
        piVar8 = (int *)stream[6];
        param_1 = param_1 + 1;
        iVar3 = -1;
        param_4 = piVar8;
      }
      else {
        piVar1 = piVar6;
        if (piVar8 != (int *)0x0) {
          piVar1 = (int *)((int)piVar6 - (uint)piVar6 % (uint)piVar8);
        }
        iVar2 = _read(stream[4],param_1,(uint)piVar1);
        if (iVar2 == 0) {
          stream[3] = stream[3] | 0x10;
          return (uint)((int)piVar5 - (int)piVar6) / param_2;
        }
        if (iVar2 == -1) {
          stream[3] = stream[3] | 0x20;
          return (uint)((int)piVar5 - (int)piVar6) / param_2;
        }
        iVar3 = -iVar2;
        param_1 = param_1 + iVar2;
      }
    }
    else {
      if (piVar6 < piVar1) {
        piVar1 = piVar6;
      }
      iVar3 = -(int)piVar1;
      pcVar7 = (char *)*stream;
      pcVar9 = param_1;
      for (uVar4 = (uint)piVar1 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = (uint)piVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      param_1 = param_1 + (int)piVar1;
      stream[1] = stream[1] - (int)piVar1;
      *stream = *stream + (int)piVar1;
      piVar8 = param_4;
    }
    piVar6 = (int *)((int)piVar6 + iVar3);
    if (piVar6 == (int *)0x0) {
      return param_3;
    }
  } while( true );
}


/* ==== entry @ 00406d00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  int extraout_EAX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0040d000;
  puStack_10 = &LAB_0040abc8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  DVar1 = GetVersion();
  _DAT_00412698 = DVar1 >> 8 & 0xff;
  _DAT_00412694 = DVar1 & 0xff;
  _DAT_00412690 = _DAT_00412694 * 0x100 + _DAT_00412698;
  _DAT_0041268c = DVar1 >> 0x10;
  iVar2 = _heap_init();
  if (iVar2 == 0) {
    _amsg_exit(0x1c);
  }
  local_8 = 0;
  _ioinit();
  __initmbctable();
  _acmdln = GetCommandLineA();
  __crtGetEnvironmentStringsA();
  _aenvptr = extraout_EAX;
  if ((extraout_EAX == 0) || (_acmdln == (LPSTR)0x0)) {
    exit(-1);
  }
  _setargv();
  _setenvp();
  _cinit();
  ___initenv = _environ;
  iVar2 = main(__argc,__argv,_environ);
  exit(iVar2);
  *unaff_FS_OFFSET = local_14;
  return;
}


/* ==== _amsg_exit @ 00406e20 ==== */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _amsg_exit(int rterrnum)

{
  if (DAT_004126ec != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
  (*(code *)PTR___exit_0040f550)(0xff);
  return;
}


/* ==== _heap_init @ 00406e50 ==== */

int _heap_init(void)

{
  int extraout_EAX;
  
  _crtheap = HeapCreate(1,0x1000,0);
  if (_crtheap == (HANDLE)0x0) {
    return 0;
  }
  __sbh_new_region();
  if (extraout_EAX == 0) {
    HeapDestroy(_crtheap);
    return 0;
  }
  return 1;
}


/* ==== __sbh_new_region @ 00406e90 ==== */

void __sbh_new_region(void)

{
  bool bVar1;
  undefined4 *lpAddress;
  LPVOID pvVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **lpMem;
  undefined4 *puVar5;
  
  if (DAT_0040f570 == -1) {
    lpMem = &PTR_LOOP_0040f560;
  }
  else {
    lpMem = HeapAlloc(_crtheap,0,0x2020);
    if (lpMem == (undefined **)0x0) {
      return;
    }
  }
  lpAddress = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (lpAddress != (undefined4 *)0x0) {
    pvVar2 = VirtualAlloc(lpAddress,0x10000,0x1000,4);
    if (pvVar2 != (LPVOID)0x0) {
      if (lpMem == &PTR_LOOP_0040f560) {
        if (PTR_LOOP_0040f560 == (undefined *)0x0) {
          PTR_LOOP_0040f560 = (undefined *)&PTR_LOOP_0040f560;
        }
        if (PTR_LOOP_0040f564 == (undefined *)0x0) {
          PTR_LOOP_0040f564 = (undefined *)&PTR_LOOP_0040f560;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_0040f560;
        lpMem[1] = PTR_LOOP_0040f564;
        PTR_LOOP_0040f564 = (undefined *)lpMem;
        *(undefined ***)lpMem[1] = lpMem;
      }
      lpMem[5] = (undefined *)(lpAddress + 0x100000);
      lpMem[4] = (undefined *)lpAddress;
      lpMem[2] = (undefined *)(lpMem + 6);
      lpMem[3] = (undefined *)(lpMem + 0x26);
      iVar3 = 0;
      ppuVar4 = lpMem + 6;
      do {
        bVar1 = 0xf < iVar3;
        iVar3 = iVar3 + 1;
        *ppuVar4 = (undefined *)((bVar1 - 1 & 0xf1) - 1);
        ppuVar4[1] = (undefined *)0xf1;
        ppuVar4 = ppuVar4 + 2;
      } while (iVar3 < 0x400);
      puVar5 = lpAddress;
      for (iVar3 = 0x4000; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      if (lpAddress < lpMem[4] + 0x10000) {
        do {
          lpAddress[1] = 0xf0;
          *lpAddress = lpAddress + 2;
          *(undefined1 *)(lpAddress + 0x3e) = 0xff;
          lpAddress = lpAddress + 0x400;
        } while (lpAddress < lpMem[4] + 0x10000);
      }
      return;
    }
    VirtualFree(lpAddress,0,0x8000);
  }
  if (lpMem != &PTR_LOOP_0040f560) {
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== __sbh_release_region @ 00407000 ==== */

void __cdecl __sbh_release_region(void *preg)

{
  VirtualFree(*(LPVOID *)((int)preg + 0x10),0,0x8000);
  if (PTR_LOOP_00411580 == preg) {
    PTR_LOOP_00411580 = *(undefined **)((int)preg + 4);
  }
  if (preg != &PTR_LOOP_0040f560) {
    **(undefined4 **)((int)preg + 4) = *(undefined4 *)preg;
    *(undefined4 *)(*(int *)preg + 4) = *(undefined4 *)((int)preg + 4);
    HeapFree(_crtheap,0,preg);
    return;
  }
  DAT_0040f570 = 0xffffffff;
  return;
}


/* ==== __sbh_decommit_pages @ 00407060 ==== */

void __cdecl __sbh_decommit_pages(int count)

{
  BOOL BVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *preg;
  undefined *puVar5;
  
  preg = PTR_LOOP_0040f564;
  do {
    puVar5 = preg;
    if (*(int *)(preg + 0x10) != -1) {
      iVar4 = 0;
      piVar2 = (int *)(preg + 0x2010);
      iVar3 = 0x3ff000;
      do {
        if (*piVar2 == 0xf0) {
          BVar1 = VirtualFree((LPVOID)(*(int *)(preg + 0x10) + iVar3),0x1000,0x4000);
          if (BVar1 != 0) {
            *piVar2 = -1;
            DAT_004126f0 = DAT_004126f0 + -1;
            if ((*(int **)(preg + 0xc) == (int *)0x0) || (piVar2 < *(int **)(preg + 0xc))) {
              *(int **)(preg + 0xc) = piVar2;
            }
            iVar4 = iVar4 + 1;
            count = count + -1;
            if (count == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        piVar2 = piVar2 + -2;
      } while (-1 < iVar3);
      puVar5 = *(undefined **)(preg + 4);
      if ((iVar4 != 0) && (*(int *)(preg + 0x18) == -1)) {
        iVar3 = 1;
        piVar2 = (int *)(preg + 0x20);
        do {
          if (*piVar2 != -1) break;
          iVar3 = iVar3 + 1;
          piVar2 = piVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          __sbh_release_region(preg);
        }
      }
    }
    if ((puVar5 == PTR_LOOP_0040f564) || (preg = puVar5, count < 1)) {
      return;
    }
  } while( true );
}


/* ==== __sbh_find_block @ 00407130 ==== */

void __cdecl __sbh_find_block(void *pblock,void *ppreg,void *pppage)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_0040f560;
  while ((pblock <= ppuVar1[4] || (ppuVar1[5] <= pblock))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_0040f560) {
      return;
    }
  }
  if (((uint)pblock & 0xf) != 0) {
    return;
  }
  if (((uint)pblock & 0xfff) < 0x100) {
    return;
  }
  *(undefined ***)ppreg = ppuVar1;
  *(uint *)pppage = (uint)pblock & 0xfffff000;
  return;
}


/* ==== __sbh_free_block @ 00407190 ==== */

void __cdecl __sbh_free_block(void *preg,void *ppage,void *pmap)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (int)ppage - *(int *)((int)preg + 0x10) >> 0xc;
  piVar1 = (int *)((int)preg + iVar2 * 8 + 0x18);
  *piVar1 = *(int *)((int)preg + iVar2 * 8 + 0x18) + (uint)*(byte *)pmap;
  *(undefined1 *)pmap = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_004126f0 = DAT_004126f0 + 1, DAT_004126f0 == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}


/* ==== __sbh_alloc_block @ 004071f0 ==== */

void __cdecl __sbh_alloc_block(uint para_req)

{
  undefined **ppuVar1;
  uint *puVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  int *piVar5;
  undefined *extraout_EAX_01;
  undefined **ppuVar6;
  undefined **ppuVar7;
  void *pvVar8;
  int iVar9;
  uint *puVar10;
  int *piVar11;
  bool bVar12;
  
  piVar11 = (int *)PTR_LOOP_00411580;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      pvVar8 = (void *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX != 0) {
            PTR_LOOP_00411580 = (undefined *)piVar11;
            *puVar10 = *puVar10 - para_req;
            piVar11[2] = (int)puVar10;
            return;
          }
          puVar10[1] = para_req;
        }
        pvVar8 = (void *)((int)pvVar8 + 0x1000);
      }
      puVar2 = (uint *)piVar11[2];
      pvVar8 = (void *)piVar11[4];
      for (puVar10 = (uint *)(piVar11 + 6); puVar10 < puVar2; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX_00 != 0) {
            PTR_LOOP_00411580 = (undefined *)piVar11;
            *puVar10 = *puVar10 - para_req;
            piVar11[2] = (int)puVar10;
            return;
          }
          puVar10[1] = para_req;
        }
        pvVar8 = (void *)((int)pvVar8 + 0x1000);
      }
    }
    piVar11 = (int *)*piVar11;
  } while (piVar11 != (int *)PTR_LOOP_00411580);
  ppuVar7 = &PTR_LOOP_0040f560;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_0040f560) {
      __sbh_new_region();
      if (extraout_EAX_01 == (undefined *)0x0) {
        return;
      }
      piVar11 = *(int **)(extraout_EAX_01 + 0x10);
      *(char *)(piVar11 + 2) = (char)para_req;
      PTR_LOOP_00411580 = extraout_EAX_01;
      *piVar11 = (int)piVar11 + para_req + 8;
      piVar11[1] = 0xf0 - para_req;
      *(uint *)(extraout_EAX_01 + 0x18) = *(int *)(extraout_EAX_01 + 0x18) - (para_req & 0xff);
      return;
    }
  }
  ppuVar3 = (undefined **)ppuVar7[3];
  puVar4 = *ppuVar3;
  piVar11 = (int *)(ppuVar7[4] + ((int)ppuVar3 + (-0x18 - (int)ppuVar7) >> 3) * 0x1000);
  ppuVar6 = ppuVar3;
  for (iVar9 = 0; (puVar4 == (undefined *)0xffffffff && (iVar9 < 0x10)); iVar9 = iVar9 + 1) {
    puVar4 = ppuVar6[2];
    ppuVar6 = ppuVar6 + 2;
  }
  piVar5 = VirtualAlloc(piVar11,iVar9 << 0xc,0x1000,4);
  if (piVar5 != piVar11) {
    return;
  }
  ppuVar6 = ppuVar3;
  if (0 < iVar9) {
    piVar5 = piVar11 + 1;
    do {
      *piVar5 = 0xf0;
      piVar5[-1] = (int)(piVar5 + 1);
      *(undefined1 *)(piVar5 + 0x3d) = 0xff;
      *ppuVar6 = (undefined *)0xf0;
      ppuVar6[1] = (undefined *)0xf1;
      piVar5 = piVar5 + 0x400;
      ppuVar6 = ppuVar6 + 2;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  ppuVar1 = ppuVar7 + 0x806;
  bVar12 = false;
  if (ppuVar6 < ppuVar1) {
    do {
      if (*ppuVar6 == (undefined *)0xffffffff) break;
      ppuVar6 = ppuVar6 + 2;
    } while (ppuVar6 < ppuVar1);
    bVar12 = ppuVar6 < ppuVar1;
  }
  PTR_LOOP_00411580 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)para_req;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -para_req;
  piVar11[1] = piVar11[1] - para_req;
  *piVar11 = (int)piVar11 + para_req + 8;
  return;
}


/* ==== __sbh_alloc_block_from_page @ 00407430 ==== */

void __cdecl __sbh_alloc_block_from_page(void *ppage,uint free_para_count,uint para_req)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = *(byte **)ppage;
  if (para_req <= *(uint *)((int)ppage + 4)) {
    *pbVar2 = (byte)para_req;
    if (pbVar2 + para_req < (byte *)((int)ppage + 0xf8U)) {
      *(uint *)ppage = *(int *)ppage + para_req;
      *(uint *)((int)ppage + 4) = *(int *)((int)ppage + 4) - para_req;
    }
    else {
      *(undefined4 *)((int)ppage + 4) = 0;
      *(int *)ppage = (int)ppage + 8;
    }
    return;
  }
  pbVar6 = pbVar2;
  if (pbVar2[*(uint *)((int)ppage + 4)] != 0) {
    pbVar6 = pbVar2 + *(uint *)((int)ppage + 4);
  }
  if (pbVar6 + para_req < (byte *)((int)ppage + 0xf8U)) {
    do {
      if (*pbVar6 == 0) {
        pbVar3 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar3 = pbVar3 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar3;
        }
        if (para_req <= uVar5) {
          if ((byte *)((int)ppage + 0xf8U) <= pbVar6 + para_req) {
            *(int *)ppage = (int)ppage + 8;
            goto LAB_0040757f;
          }
          *(byte **)ppage = pbVar6 + para_req;
          *(uint *)((int)ppage + 4) = uVar5 - para_req;
          goto LAB_00407586;
        }
        if (pbVar6 == pbVar2) {
          *(uint *)((int)ppage + 4) = uVar5;
        }
        else {
          free_para_count = free_para_count - uVar5;
          if (free_para_count < para_req) {
            return;
          }
        }
      }
      else {
        pbVar3 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar3;
    } while (pbVar3 + para_req < (byte *)((int)ppage + 0xf8U));
  }
  pbVar3 = (byte *)((int)ppage + 8);
  pbVar6 = pbVar3;
  if (pbVar3 < pbVar2) {
    while (pbVar6 + para_req < (byte *)((int)ppage + 0xf8U)) {
      if (*pbVar6 == 0) {
        pbVar4 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar4 = pbVar4 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar4;
        }
        if (para_req <= uVar5) {
          if (pbVar6 + para_req < (byte *)((int)ppage + 0xf8U)) {
            *(byte **)ppage = pbVar6 + para_req;
            *(uint *)((int)ppage + 4) = uVar5 - para_req;
          }
          else {
            *(byte **)ppage = pbVar3;
LAB_0040757f:
            *(undefined4 *)((int)ppage + 4) = 0;
          }
LAB_00407586:
          *pbVar6 = (byte)para_req;
          return;
        }
        free_para_count = free_para_count - uVar5;
        if (free_para_count < para_req) {
          return;
        }
      }
      else {
        pbVar4 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar4;
      if (pbVar2 <= pbVar4) {
        return;
      }
    }
  }
  return;
}


/* ==== _close @ 004075b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _close(int fh)

{
  long lVar1;
  long lVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD oserrno;
  int iVar4;
  
  if (_nhandle <= (uint)fh) {
    _errno = 9;
    _doserrno = 0;
    return -1;
  }
  iVar4 = (fh & 0x1fU) * 8;
  if ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar4) & 1) == 0) {
    _errno = 9;
    _doserrno = 0;
    return -1;
  }
  lVar1 = _get_osfhandle(fh);
  if (lVar1 != -1) {
    if ((fh == 1) || (fh == 2)) {
      lVar1 = _get_osfhandle(2);
      lVar2 = _get_osfhandle(1);
      if (lVar2 == lVar1) goto LAB_00407637;
    }
    hObject = (HANDLE)_get_osfhandle(fh);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      oserrno = GetLastError();
      goto LAB_00407639;
    }
  }
LAB_00407637:
  oserrno = 0;
LAB_00407639:
  _free_osfhnd(fh);
  *(undefined1 *)((&__pioinfo)[fh >> 5] + 4 + iVar4) = 0;
  if (oserrno == 0) {
    return 0;
  }
  _dosmaperr(oserrno);
  return -1;
}


/* ==== _freebuf @ 00407690 ==== */

void __cdecl _freebuf(void *stream)

{
  if (((*(uint *)((int)stream + 0xc) & 0x83) != 0) && ((*(uint *)((int)stream + 0xc) & 8) != 0)) {
    free(*(void **)((int)stream + 8));
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xfffffbf7;
    *(undefined4 *)stream = 0;
    *(undefined4 *)((int)stream + 8) = 0;
    *(undefined4 *)((int)stream + 4) = 0;
  }
  return;
}


/* ==== _flush @ 00407720 ==== */

int __cdecl _flush(void *stream)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint cnt;
  
  iVar3 = 0;
  if ((((byte)*(uint *)((int)stream + 0xc) & 3) == 2) &&
     ((*(uint *)((int)stream + 0xc) & 0x108) != 0)) {
    cnt = *(int *)stream - (int)*(void **)((int)stream + 8);
    if (0 < (int)cnt) {
      uVar2 = _write(*(int *)((int)stream + 0x10),*(void **)((int)stream + 8),cnt);
      uVar1 = *(uint *)((int)stream + 0xc);
      if (uVar2 == cnt) {
        if ((uVar1 & 0x80) != 0) {
          *(undefined4 *)((int)stream + 4) = 0;
          *(uint *)((int)stream + 0xc) = uVar1 & 0xfffffffd;
          *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
          return 0;
        }
      }
      else {
        iVar3 = -1;
        *(uint *)((int)stream + 0xc) = uVar1 | 0x20;
      }
    }
  }
  *(undefined4 *)((int)stream + 4) = 0;
  *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
  return iVar3;
}


/* ==== _callnewh @ 00407820 ==== */

int __cdecl _callnewh(uint size)

{
  int iVar1;
  
  if (_pnhNewHandler != (code *)0x0) {
    iVar1 = (*_pnhNewHandler)(size);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}


/* ==== _input @ 00407840 ==== */

int __cdecl _input(void *stream,char *fmt,void *arglist)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  ushort *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *chr;
  byte bVar8;
  byte *pbVar9;
  int iVar10;
  char *pcVar11;
  ushort *puVar12;
  char *pcVar13;
  ushort *puVar14;
  bool bVar15;
  longlong lVar16;
  void *stream_00;
  char local_1cd;
  int local_1cc;
  char local_1c7;
  char local_1c6;
  char local_1c5;
  int local_1c4;
  char local_1c0;
  char local_1bf;
  char local_1be;
  byte local_1bd;
  uint local_1bc;
  ushort *local_1b8;
  uint local_1b4;
  int local_1b0;
  int local_1ac;
  int local_1a8;
  int local_1a4;
  byte local_19e;
  undefined1 local_19d;
  undefined8 local_19c;
  undefined4 local_194;
  ushort local_18e;
  undefined4 *local_18c;
  int local_188;
  undefined4 local_184;
  byte local_180 [11];
  undefined1 local_175;
  char local_160;
  char local_15f [351];
  
  local_1bf = '\0';
  local_1cc = 0;
  local_1ac = 0;
  bVar8 = *fmt;
  chr = local_18c;
  do {
    if (bVar8 == 0) {
LAB_00408496:
      if ((chr == (undefined4 *)0xffffffff) && ((local_1ac == 0 && (local_1bf == '\0')))) {
        local_1ac = -1;
      }
      return local_1ac;
    }
    iVar10 = 0;
    if ((int)__mb_cur_max < 2) {
      uVar5 = (byte)_pctype[(uint)bVar8 * 2] & 8;
    }
    else {
      uVar5 = _isctype((uint)bVar8,8);
    }
    if (uVar5 != 0) {
      local_1cc = local_1cc + -1;
      stream_00 = stream;
      iVar6 = _whiteout(&local_1cc,stream);
      _un_inc(iVar6,stream_00);
      fmt = fmt + 1;
      iVar6 = isspace((uint)(byte)*fmt);
      while (iVar6 != 0) {
        fmt = fmt + 1;
        iVar6 = isspace((uint)(byte)*fmt);
      }
    }
    if (*fmt != '%') {
      local_1cc = local_1cc + 1;
      chr = (undefined4 *)_inc(stream);
      if ((undefined4 *)(uint)(byte)*fmt != chr) goto LAB_0040847d;
      pbVar9 = (byte *)(fmt + 1);
      if ((_pctype[((uint)chr & 0xff) * 2 + 1] & 0x80) != 0) {
        local_1cc = local_1cc + 1;
        uVar5 = _inc(stream);
        if ((byte)fmt[1] != uVar5) {
          local_1cc = local_1cc + -1;
          _un_inc(uVar5,stream);
          goto LAB_0040847d;
        }
        local_1cc = local_1cc + -1;
        pbVar9 = (byte *)(fmt + 2);
      }
      goto LAB_00408443;
    }
    local_1a4 = 0;
    local_1b4 = local_1b4 & 0xffffff00;
    local_1a8 = 0;
    local_1b0 = 0;
    local_1c4 = 0;
    local_1bd = 0;
    local_1be = '\0';
    local_1c5 = '\0';
    local_1cd = '\0';
    local_1c0 = '\0';
    local_1c7 = '\0';
    local_1c6 = '\x01';
    local_188 = 0;
    do {
      pbVar9 = (byte *)(fmt + 1);
      uVar5 = (uint)*pbVar9;
      if ((int)__mb_cur_max < 2) {
        uVar7 = (byte)_pctype[uVar5 * 2] & 4;
      }
      else {
        uVar7 = _isctype(uVar5,4);
      }
      if (uVar7 == 0) {
        switch(uVar5) {
        case 0x2a:
          local_1c5 = local_1c5 + '\x01';
          break;
        default:
switchD_004079c0_caseD_2b:
          local_1cd = local_1cd + '\x01';
          break;
        case 0x46:
        case 0x4e:
          break;
        case 0x49:
          if ((fmt[2] != '6') || (fmt[3] != '4')) goto switchD_004079c0_caseD_2b;
          iVar10 = iVar10 + 1;
          local_19c = 0;
          pbVar9 = (byte *)(fmt + 3);
          break;
        case 0x4c:
          local_1c6 = local_1c6 + '\x01';
          break;
        case 0x68:
          local_1c6 = local_1c6 + -1;
          local_1c7 = local_1c7 + -1;
          break;
        case 0x6c:
          local_1c6 = local_1c6 + '\x01';
        case 0x77:
          local_1c7 = local_1c7 + '\x01';
        }
      }
      else {
        local_1b0 = local_1b0 + 1;
        local_1c4 = (uVar5 - 0x30) + local_1c4 * 10;
      }
      fmt = (char *)pbVar9;
    } while (local_1cd == '\0');
    puVar3 = arglist;
    if (local_1c5 == '\0') {
      local_1b8 = *(ushort **)arglist;
      puVar3 = (undefined4 *)((int)arglist + 4);
      local_18c = arglist;
    }
    arglist = puVar3;
    bVar15 = false;
    if ((local_1c7 == '\0') && ((*fmt == 'S' || (local_1c7 = -1, *fmt == 'C')))) {
      local_1c7 = '\x01';
    }
    local_1bc = (byte)*fmt | 0x20;
    local_188 = iVar10;
    if (local_1bc != 0x6e) {
      if ((local_1bc == 99) || (local_1bc == 0x7b)) {
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
      }
      else {
        chr = (undefined4 *)_whiteout(&local_1cc,stream);
      }
    }
    puVar12 = local_1b8;
    uVar5 = local_1bc;
    if ((local_1b0 != 0) && (local_1c4 == 0)) {
LAB_0040847d:
      local_1cc = local_1cc + -1;
      _un_inc((int)chr,stream);
      goto LAB_00408496;
    }
    switch(local_1bc) {
    case 99:
      if (local_1b0 == 0) {
        local_1b0 = 1;
        local_1c4 = local_1c4 + 1;
      }
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar11 = &DAT_00411590;
      goto LAB_00407b3e;
    case 100:
    case 0x6f:
    case 0x75:
      goto switchD_00407ad8_caseD_64;
    case 0x65:
    case 0x66:
    case 0x67:
      pcVar11 = &local_160;
      if (chr == (undefined4 *)0x2d) {
        local_160 = '-';
        pcVar11 = local_15f;
LAB_00408183:
        local_1c4 = local_1c4 + -1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00408183;
      iVar10 = local_1a8;
      if ((local_1b0 == 0) || (0x15d < local_1c4)) {
        local_1c4 = 0x15d;
      }
      while( true ) {
        if ((int)__mb_cur_max < 2) {
          uVar5 = (byte)_pctype[(int)chr * 2] & 4;
        }
        else {
          uVar5 = _isctype((int)chr,4);
        }
        if ((uVar5 == 0) ||
           (iVar6 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar6, bVar15)) break;
        *pcVar11 = (char)chr;
        pcVar11 = pcVar11 + 1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        iVar10 = iVar10 + 1;
      }
      if ((__decimal_point == (char)chr) &&
         (iVar6 = local_1c4 + -1, bVar15 = local_1c4 != 0, local_1c4 = iVar6, bVar15)) {
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        *pcVar11 = __decimal_point;
        while( true ) {
          pcVar11 = pcVar11 + 1;
          if ((int)__mb_cur_max < 2) {
            uVar5 = (byte)_pctype[(int)chr * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)chr,4);
          }
          if ((uVar5 == 0) ||
             (iVar6 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar6, bVar15)) break;
          *pcVar11 = (char)chr;
          iVar10 = iVar10 + 1;
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      pcVar13 = pcVar11;
      if ((iVar10 != 0) &&
         (((chr == (undefined4 *)0x65 || (chr == (undefined4 *)0x45)) &&
          (iVar6 = local_1c4 + -1, bVar15 = local_1c4 != 0, local_1c4 = iVar6, bVar15)))) {
        *pcVar11 = 'e';
        pcVar13 = pcVar11 + 1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        if (chr == (undefined4 *)0x2d) {
          *pcVar13 = '-';
          pcVar13 = pcVar11 + 2;
LAB_004082de:
          iVar6 = local_1c4 + -1;
          if (local_1c4 != 0) goto LAB_004082f3;
        }
        else if (chr == (undefined4 *)0x2b) goto LAB_004082de;
        while( true ) {
          if ((int)__mb_cur_max < 2) {
            uVar5 = (byte)_pctype[(int)chr * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)chr,4);
          }
          if ((uVar5 == 0) ||
             (iVar6 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar6, bVar15)) break;
          iVar10 = iVar10 + 1;
          *pcVar13 = (char)chr;
          pcVar13 = pcVar13 + 1;
LAB_004082f3:
          local_1c4 = iVar6;
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      local_1cc = local_1cc + -1;
      _un_inc((int)chr,stream);
      if (iVar10 == 0) goto LAB_00408496;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        *pcVar13 = '\0';
        (*(code *)PTR__fptrap_00411938)(local_1c6 + -1,local_1b8,&local_160);
      }
      break;
    default:
      if ((undefined4 *)(uint)(byte)*fmt != chr) goto LAB_0040847d;
      local_1bf = local_1bf + -1;
      if (local_1c5 == '\0') {
        arglist = local_18c;
      }
      break;
    case 0x69:
      local_1bc = 100;
    case 0x78:
      uVar5 = local_1bc;
      if (chr == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_00407d92:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar15 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00407d92;
      if (chr == (undefined4 *)0x30) {
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        if (((char)chr == 'x') || ((char)chr == 'X')) {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
          uVar5 = 0x78;
          local_1bc = 0x78;
        }
        else {
          local_1a8 = 1;
          if (uVar5 == 0x78) {
            local_1cc = local_1cc + -1;
            _un_inc((int)chr,stream);
            chr = (undefined4 *)0x30;
          }
          else {
            uVar5 = 0x6f;
            local_1bc = 0x6f;
          }
        }
      }
      goto LAB_00407e74;
    case 0x6e:
      iVar6 = local_1cc;
      if (local_1c5 != '\0') break;
      goto LAB_00408135;
    case 0x70:
      local_1c6 = '\x01';
switchD_00407ad8_caseD_64:
      if (chr == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_00407e4a:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar15 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00407e4a;
LAB_00407e74:
      iVar6 = local_1a4;
      lVar16 = local_19c;
      if (iVar10 == 0) {
        while (!bVar15) {
          if ((uVar5 == 0x78) || (uVar5 == 0x70)) {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 0x80;
            }
            else {
              uVar7 = _isctype((int)chr,0x80);
            }
            if (uVar7 != 0) {
              iVar6 = iVar6 << 4;
              chr = (undefined4 *)_hextodec((int)chr);
              goto LAB_0040806a;
            }
LAB_00408066:
            bVar15 = true;
          }
          else {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 4;
            }
            else {
              uVar7 = _isctype((int)chr,4);
            }
            if (uVar7 == 0) goto LAB_00408066;
            if (uVar5 == 0x6f) {
              if (0x37 < (int)chr) goto LAB_00408066;
              iVar6 = iVar6 << 3;
            }
            else {
              iVar6 = iVar6 * 10;
            }
          }
LAB_0040806a:
          if (bVar15) {
            local_1cc = local_1cc + -1;
            _un_inc((int)chr,stream);
          }
          else {
            local_1a8 = local_1a8 + 1;
            iVar6 = iVar6 + -0x30 + (int)chr;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 + -1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              chr = (undefined4 *)_inc(stream);
            }
            else {
              bVar15 = true;
            }
          }
        }
        local_1a4 = iVar6;
        if (local_1be != '\0') {
          local_1a4 = -iVar6;
        }
      }
      else {
        while( true ) {
          uVar5 = (uint)lVar16;
          iVar10 = (int)((ulonglong)lVar16 >> 0x20);
          if (bVar15) break;
          if (local_1bc == 0x78) {
            if ((int)__mb_cur_max < 2) {
              uVar5 = (byte)_pctype[(int)chr * 2] & 0x80;
            }
            else {
              uVar5 = _isctype((int)chr,0x80);
            }
            if (uVar5 != 0) {
              lVar16 = __allshl(4,iVar10);
              chr = (undefined4 *)_hextodec((int)chr);
              goto LAB_00407f41;
            }
LAB_00407f3d:
            bVar15 = true;
          }
          else {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 4;
            }
            else {
              uVar7 = _isctype((int)chr,4);
            }
            if (uVar7 == 0) goto LAB_00407f3d;
            if (local_1bc == 0x6f) {
              if (0x37 < (int)chr) goto LAB_00407f3d;
              lVar16 = __allshl(3,iVar10);
            }
            else {
              lVar16 = __allmul(uVar5,iVar10,10,0);
            }
          }
LAB_00407f41:
          if (bVar15) {
            local_1cc = local_1cc + -1;
            _un_inc((int)chr,stream);
          }
          else {
            puVar3 = chr + -0xc;
            local_1a8 = local_1a8 + 1;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 + -1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              chr = (undefined4 *)_inc(stream);
              lVar16 = lVar16 + (int)puVar3;
            }
            else {
              bVar15 = true;
              lVar16 = lVar16 + (int)puVar3;
            }
          }
        }
        local_19c = lVar16;
        if (local_1be != '\0') {
          local_19c = CONCAT44(-(iVar10 + (uint)(uVar5 != 0)),-uVar5);
        }
      }
      iVar10 = local_1a8;
      if (local_1bc == 0x46) {
        iVar10 = 0;
      }
      if (iVar10 == 0) goto LAB_00408496;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        iVar6 = local_1a4;
        iVar10 = local_188;
LAB_00408135:
        if (iVar10 == 0) {
          if (local_1c6 == '\0') {
            *local_1b8 = (ushort)iVar6;
          }
          else {
            *(int *)local_1b8 = iVar6;
          }
        }
        else {
          *(undefined4 *)local_1b8 = (undefined4)local_19c;
          *(undefined4 *)(local_1b8 + 2) = local_19c._4_4_;
        }
      }
      break;
    case 0x73:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar11 = s_____00411588;
LAB_00407b3e:
      local_1bd = 0xff;
      pbVar9 = (byte *)fmt;
LAB_00407b43:
      fmt = (char *)pbVar9;
      pbVar9 = local_180;
      for (iVar10 = 8; iVar10 != 0; iVar10 = iVar10 + -1) {
        pbVar9[0] = 0;
        pbVar9[1] = 0;
        pbVar9[2] = 0;
        pbVar9[3] = 0;
        pbVar9 = pbVar9 + 4;
      }
      if ((local_1bc == 0x7b) && (*pcVar11 == 0x5d)) {
        local_1b4 = CONCAT31(local_1b4._1_3_,0x5d);
        pcVar11 = pcVar11 + 1;
        local_175 = 0x20;
      }
      bVar8 = *pcVar11;
      uVar5 = local_1b4;
      while (bVar8 != 0x5d) {
        pbVar9 = (byte *)(pcVar11 + 1);
        uVar7 = (uint)local_184 >> 8;
        local_184 = CONCAT31((int3)uVar7,bVar8);
        local_1b4._1_3_ = (undefined3)(uVar5 >> 8);
        if (((bVar8 == 0x2d) &&
            (local_1b4._0_1_ = (byte)uVar5, bVar2 = (byte)local_1b4, (byte)local_1b4 != 0)) &&
           (bVar1 = *pbVar9, bVar1 != 0x5d)) {
          pbVar9 = (byte *)(pcVar11 + 2);
          uVar7 = (uint)local_194 >> 8;
          bVar8 = (byte)local_1b4;
          if (bVar1 <= (byte)local_1b4) {
            local_1b4 = CONCAT31(local_1b4._1_3_,bVar1);
            bVar8 = bVar1;
            uVar5 = local_1b4;
            bVar1 = bVar2;
          }
          local_1b4 = uVar5;
          local_194 = CONCAT31((int3)uVar7,bVar1);
          if (bVar8 <= bVar1) {
            uVar5 = local_1b4 & 0xff;
            iVar10 = (bVar1 - uVar5) + 1;
            do {
              uVar7 = uVar5 >> 3;
              bVar8 = (byte)uVar5;
              uVar5 = uVar5 + 1;
              iVar10 = iVar10 + -1;
              local_180[uVar7] = local_180[uVar7] | '\x01' << (bVar8 & 7);
            } while (iVar10 != 0);
          }
          local_1b4 = local_1b4 & 0xffffff00;
        }
        else {
          local_1b4 = CONCAT31(local_1b4._1_3_,bVar8);
          local_180[bVar8 >> 3] = local_180[bVar8 >> 3] | '\x01' << (bVar8 & 7);
        }
        pcVar11 = (char *)pbVar9;
        uVar5 = local_1b4;
        bVar8 = *pbVar9;
      }
      if (*pcVar11 == 0) goto LAB_00408496;
      if (local_1bc == 0x7b) {
        fmt = pcVar11;
      }
      local_1cc = local_1cc + -1;
      local_1b4 = uVar5;
      _un_inc((int)chr,stream);
      puVar14 = puVar12;
      while( true ) {
        if ((local_1b0 != 0) &&
           (iVar10 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar10, puVar4 = puVar14,
           bVar15)) goto LAB_00407d2c;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        if ((chr == (undefined4 *)0xffffffff) ||
           (bVar8 = (byte)chr,
           ((int)(char)(local_180[(int)chr >> 3] ^ local_1bd) & 1 << (bVar8 & 7)) == 0)) break;
        if (local_1c5 == '\0') {
          if (local_1c0 == '\0') {
            *(byte *)puVar14 = bVar8;
            puVar14 = (ushort *)((int)puVar14 + 1);
          }
          else {
            local_19e = bVar8;
            if ((_pctype[((uint)chr & 0xff) * 2 + 1] & 0x80) != 0) {
              local_1cc = local_1cc + 1;
              iVar10 = _inc(stream);
              local_19d = (undefined1)iVar10;
            }
            mbtowc(&local_18e,(char *)&local_19e,__mb_cur_max);
            *puVar14 = local_18e;
            puVar14 = puVar14 + 1;
          }
        }
        else {
          puVar12 = (ushort *)((int)puVar12 + 1);
        }
      }
      local_1cc = local_1cc + -1;
      local_1b8 = puVar14;
      _un_inc((int)chr,stream);
      puVar4 = local_1b8;
LAB_00407d2c:
      local_1b8 = puVar4;
      if (puVar12 == puVar14) goto LAB_00408496;
      if ((local_1c5 == '\0') && (local_1ac = local_1ac + 1, local_1bc != 99)) {
        if (local_1c0 == '\0') {
          *(byte *)local_1b8 = 0;
        }
        else {
          *local_1b8 = 0;
        }
      }
      break;
    case 0x7b:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pbVar9 = (byte *)(fmt + 1);
      pcVar11 = (char *)pbVar9;
      if (*pbVar9 == 0x5e) {
        pcVar11 = fmt + 2;
        fmt = (char *)pbVar9;
        goto LAB_00407b3e;
      }
      goto LAB_00407b43;
    }
    local_1bf = local_1bf + '\x01';
    pbVar9 = (byte *)(fmt + 1);
LAB_00408443:
    fmt = (char *)pbVar9;
    if ((chr == (undefined4 *)0xffffffff) && ((*fmt != '%' || (fmt[1] != 'n')))) goto LAB_00408496;
    bVar8 = *fmt;
  } while( true );
}


/* ==== _hextodec @ 00408580 ==== */

int __cdecl _hextodec(int chr)

{
  uint uVar1;
  
  if (__mb_cur_max < 2) {
    uVar1 = (byte)_pctype[chr * 2] & 4;
  }
  else {
    uVar1 = _isctype(chr,4);
  }
  if (uVar1 == 0) {
    chr = (chr & 0xffffffdfU) - 7;
  }
  return chr;
}


/* ==== _inc @ 004085c0 ==== */

int __cdecl _inc(void *stream)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)stream + 4) + -1;
  *(int *)((int)stream + 4) = iVar2;
  if (-1 < iVar2) {
    bVar1 = **(byte **)stream;
    *(byte **)stream = *(byte **)stream + 1;
    return (uint)bVar1;
  }
  iVar2 = _filbuf(stream);
  return iVar2;
}


/* ==== _un_inc @ 004085f0 ==== */

void __cdecl _un_inc(int chr,void *stream)

{
  if (chr != -1) {
    ungetc(chr,stream);
  }
  return;
}


/* ==== _whiteout @ 00408610 ==== */

int __cdecl _whiteout(int *counter,void *stream)

{
  int c;
  int iVar1;
  
  *counter = *counter + 1;
  c = _inc(stream);
  iVar1 = isspace(c);
  while (iVar1 != 0) {
    *counter = *counter + 1;
    c = _inc(stream);
    iVar1 = isspace(c);
  }
  return c;
}


/* ==== FUN_00408660 @ 00408660 ==== */

int __cdecl
FUN_00408660(LCID param_1,uint param_2,char *param_3,LPCWSTR param_4,LPWSTR param_5,int param_6,
            UINT param_7)

{
  int iVar1;
  LPCWSTR cbMultiByte;
  LPCWSTR lpWideCharStr;
  int iVar2;
  LPCWSTR lpDestStr;
  
  if (DAT_00412700 == 0) {
    iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_00412700 = 1;
    }
    else {
      DAT_00412700 = 2;
    }
  }
  cbMultiByte = param_4;
  if (0 < (int)param_4) {
    cbMultiByte = (LPCWSTR)__ansicp((int)param_3);
  }
  if (DAT_00412700 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,(int)cbMultiByte,(LPSTR)param_5,param_6);
    return iVar1;
  }
  if (DAT_00412700 != 1) {
    return DAT_00412700;
  }
  param_4 = (LPCWSTR)0x0;
  if (param_7 == 0) {
    param_7 = DAT_00412720;
  }
  iVar1 = MultiByteToWideChar(param_7,9,param_3,(int)cbMultiByte,(LPWSTR)0x0,0);
  if (iVar1 == 0) {
    return 0;
  }
  malloc(iVar1 * 2);
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return 0;
  }
  iVar2 = MultiByteToWideChar(param_7,1,param_3,(int)cbMultiByte,lpWideCharStr,iVar1);
  if ((iVar2 != 0) &&
     (iVar2 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,(LPWSTR)0x0,0), iVar2 != 0)) {
    if ((param_2 & 0x400) == 0) {
      malloc(iVar2 * 2);
      param_4 = lpDestStr;
      if ((lpDestStr == (LPCWSTR)0x0) ||
         (iVar1 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,lpDestStr,iVar2), iVar1 == 0))
      goto LAB_0040885f;
      if (param_6 == 0) {
        iVar2 = WideCharToMultiByte(param_7,0x220,lpDestStr,iVar2,(LPSTR)0x0,0,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        iVar1 = iVar2;
      }
      else {
        iVar2 = WideCharToMultiByte(param_7,0x220,lpDestStr,iVar2,(LPSTR)param_5,param_6,(LPCSTR)0x0
                                    ,(LPBOOL)0x0);
        iVar1 = iVar2;
      }
    }
    else {
      if (param_6 == 0) goto LAB_004087c4;
      if (param_6 < iVar2) goto LAB_0040885f;
      iVar1 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,param_5,param_6);
    }
    if (iVar1 != 0) {
LAB_004087c4:
      free(lpWideCharStr);
      free(param_4);
      return iVar2;
    }
  }
LAB_0040885f:
  free(lpWideCharStr);
  free(param_4);
  return 0;
}


/* ==== __ansicp @ 00408880 ==== */

int __cdecl __ansicp(int lcid)

{
  char *pcVar1;
  int iVar2;
  int in_stack_00000008;
  
  iVar2 = in_stack_00000008;
  for (pcVar1 = (char *)lcid; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0'));
      pcVar1 = pcVar1 + 1) {
  }
  if (*pcVar1 != '\0') {
    return in_stack_00000008;
  }
  return (int)pcVar1 - lcid;
}


/* ==== FUN_004088b0 @ 004088b0 ==== */

BOOL __cdecl
FUN_004088b0(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6)

{
  BOOL BVar1;
  uint size;
  LPCWSTR lpWideCharStr;
  int cchSrc;
  LPCWSTR p;
  WORD local_2;
  
  p = (LPCWSTR)0x0;
  if (DAT_00412728 == 0) {
    BVar1 = GetStringTypeA(0,1,"",1,&local_2);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeW(1,L"",1,&local_2);
      if (BVar1 == 0) {
        return 0;
      }
      DAT_00412728 = 1;
    }
    else {
      DAT_00412728 = 2;
    }
  }
  if (DAT_00412728 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_00412710;
    }
    BVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return BVar1;
  }
  param_6 = DAT_00412728;
  if (DAT_00412728 == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = DAT_00412720;
    }
    size = MultiByteToWideChar(param_5,9,param_2,param_3,(LPWSTR)0x0,0);
    if (size != 0) {
      calloc(2,size);
      p = lpWideCharStr;
      if (lpWideCharStr != (LPCWSTR)0x0) {
        cchSrc = MultiByteToWideChar(param_5,1,param_2,param_3,lpWideCharStr,size);
        if (cchSrc != 0) {
          BVar1 = GetStringTypeW(param_1,lpWideCharStr,cchSrc,param_4);
          free(lpWideCharStr);
          return BVar1;
        }
      }
    }
    free(p);
  }
  return param_6;
}


/* ==== _stbuf @ 004089e0 ==== */

int __cdecl _stbuf(void *stream)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = _isatty(*(int *)((int)stream + 0x10));
  if (iVar2 != 0) {
    if (stream == &DAT_0040f2e8) {
      iVar2 = 0;
    }
    else {
      if (stream != &DAT_0040f308) {
        return 0;
      }
      iVar2 = 1;
    }
    _cflush = _cflush + 1;
    if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
      if ((&DAT_00412730)[iVar2] == 0) {
        malloc(0x1000);
        (&DAT_00412730)[iVar2] = extraout_EAX;
        if (extraout_EAX == 0) {
          return 0;
        }
      }
      uVar1 = (&DAT_00412730)[iVar2];
      *(undefined4 *)((int)stream + 0x18) = 0x1000;
      *(undefined4 *)((int)stream + 8) = uVar1;
      *(undefined4 *)stream = uVar1;
      *(undefined4 *)((int)stream + 4) = 0x1000;
      *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 0x1102;
      return 1;
    }
  }
  return 0;
}


/* ==== _ftbuf @ 00408a80 ==== */

void __cdecl _ftbuf(int flag,void *stream)

{
  if (flag == 0) {
    if ((*(uint *)((int)stream + 0xc) & 0x1000) != 0) {
      _flush(stream);
    }
  }
  else if ((*(uint *)((int)stream + 0xc) & 0x1000) != 0) {
    _flush(stream);
    *(undefined4 *)((int)stream + 0x18) = 0;
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffeeff;
    *(undefined4 *)stream = 0;
    *(undefined4 *)((int)stream + 8) = 0;
    return;
  }
  return;
}


/* ==== _output @ 00408ae0 ==== */

int __cdecl _output(void *stream,char *fmt,void *argptr)

{
  ushort uVar1;
  uint uVar2;
  short *psVar3;
  int *piVar4;
  ushort *puVar5;
  int iVar6;
  char cVar7;
  uint unaff_EBX;
  undefined1 *puVar8;
  undefined1 *len;
  char *pcVar9;
  int iVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  longlong lVar13;
  uint uVar14;
  uint local_24c;
  ushort *local_248;
  int local_244;
  int local_240;
  char local_23a;
  char local_239;
  int local_238;
  int local_234;
  int local_230;
  uint local_22c;
  int local_228;
  int local_224;
  int local_220;
  uint local_21c;
  undefined4 local_218;
  char local_214 [4];
  undefined4 local_210;
  undefined4 local_20c;
  uint local_204;
  undefined1 local_200 [511];
  undefined1 uStack_1;
  
  local_220 = 0;
  len = (undefined1 *)0x0;
  local_240 = 0;
  cVar7 = *fmt;
  local_21c = CONCAT31(local_21c._1_3_,cVar7);
  pcVar9 = fmt;
  do {
    if ((cVar7 == '\0') || (fmt = pcVar9 + 1, local_240 < 0)) {
      return local_240;
    }
    if ((cVar7 < ' ') || ('x' < cVar7)) {
      uVar2 = 0;
    }
    else {
      uVar2 = *(byte *)(cVar7 + 0x40cff8) & 0xf;
    }
    local_220 = (int)(char)(&DAT_0040d018)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_00408b5d_caseD_0:
      local_230 = 0;
      if ((_pctype[(local_21c & 0xff) * 2 + 1] & 0x80) != 0) {
        write_char((int)cVar7,stream,&local_240);
        cVar7 = *fmt;
        fmt = pcVar9 + 2;
      }
      write_char((int)cVar7,stream,&local_240);
      break;
    case 1:
      local_218 = 0;
      local_228 = 0;
      local_234 = 0;
      local_238 = 0;
      local_24c = 0;
      local_244 = -1;
      local_230 = 0;
      break;
    case 2:
      switch(cVar7) {
      case ' ':
        local_24c = local_24c | 2;
        break;
      case '#':
        local_24c = local_24c | 0x80;
        break;
      case '+':
        local_24c = local_24c | 1;
        break;
      case '-':
        local_24c = local_24c | 4;
        break;
      case '0':
        local_24c = local_24c | 8;
      }
      break;
    case 3:
      if (cVar7 == '*') {
        local_234 = get_int_arg(&argptr);
        if (local_234 < 0) {
          local_24c = local_24c | 4;
          local_234 = -local_234;
        }
      }
      else {
        local_234 = cVar7 + -0x30 + local_234 * 10;
      }
      break;
    case 4:
      local_244 = 0;
      break;
    case 5:
      if (cVar7 == '*') {
        local_244 = get_int_arg(&argptr);
        if (local_244 < 0) {
          local_244 = -1;
        }
      }
      else {
        local_244 = cVar7 + -0x30 + local_244 * 10;
      }
      break;
    case 6:
      switch(cVar7) {
      case 'I':
        if ((*fmt != '6') || (pcVar9[2] != '4')) {
          local_220 = 0;
          goto switchD_00408b5d_caseD_0;
        }
        fmt = pcVar9 + 3;
        local_24c = local_24c | 0x8000;
        break;
      case 'h':
        local_24c = local_24c | 0x20;
        break;
      case 'l':
        local_24c = local_24c | 0x10;
        break;
      case 'w':
        local_24c = local_24c | 0x800;
      }
      break;
    case 7:
      switch(cVar7) {
      case 'C':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 'c':
        if ((local_24c & 0x810) == 0) {
          iVar10 = get_int_arg(&argptr);
          local_200[0] = (char)iVar10;
          len = (undefined1 *)0x1;
        }
        else {
          uVar1 = get_short_arg(&argptr);
          len = (undefined1 *)wctomb(local_200,uVar1);
          if ((int)len < 0) {
            local_248 = (ushort *)local_200;
            local_228 = 1;
            break;
          }
        }
        local_248 = (ushort *)local_200;
        break;
      case 'E':
      case 'G':
        local_218 = 1;
        cVar7 = cVar7 + ' ';
      case 'e':
      case 'f':
      case 'g':
        local_248 = (ushort *)local_200;
        if (local_244 < 0) {
          local_244 = 6;
        }
        else if ((local_244 == 0) && (cVar7 == 'g')) {
          local_244 = 1;
        }
        local_210 = *(undefined4 *)argptr;
        local_20c = *(undefined4 *)((int)argptr + 4);
        argptr = (undefined4 *)((int)argptr + 8);
        (*(code *)_cfltcvt_tab)(&local_210,local_200,(int)cVar7,local_244,local_218);
        if (((unaff_EBX & 0x80) != 0) && (local_244 == 0)) {
          (*(code *)PTR__fptrap_0041193c)(&local_204);
        }
        if ((cVar7 == 'g') && ((unaff_EBX & 0x80) == 0)) {
          (*(code *)PTR__fptrap_00411934)(local_200);
        }
        uVar2 = local_24c | 0x40;
        if (local_200[0] == '-') {
          local_248 = (ushort *)(local_200 + 1);
          uVar2 = local_24c | 0x140;
        }
        local_24c = uVar2;
        uVar2 = 0xffffffff;
        puVar5 = local_248;
        do {
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          uVar1 = *puVar5;
          puVar5 = (ushort *)((int)puVar5 + 1);
        } while ((char)uVar1 != '\0');
        len = (undefined1 *)(~uVar2 - 1);
        break;
      case 'S':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 's':
        iVar10 = 0x7fffffff;
        if (local_244 != -1) {
          iVar10 = local_244;
        }
        local_248 = (ushort *)get_int_arg(&argptr);
        if ((local_24c & 0x810) == 0) {
          puVar5 = local_248;
          if (local_248 == (ushort *)0x0) {
            puVar5 = (ushort *)PTR_DAT_00411594;
            local_248 = (ushort *)PTR_DAT_00411594;
          }
          for (; (iVar10 != 0 && (iVar10 = iVar10 + -1, (char)*puVar5 != '\0'));
              puVar5 = (ushort *)((int)puVar5 + 1)) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_00411598;
          }
          local_230 = 1;
          for (puVar5 = local_248; (iVar10 != 0 && (iVar10 = iVar10 + -1, *puVar5 != 0));
              puVar5 = puVar5 + 1) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_00408d71_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg(&argptr);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_00411594;
          pcVar9 = PTR_DAT_00411594;
          do {
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            cVar7 = *pcVar9;
            pcVar9 = pcVar9 + 1;
          } while (cVar7 != '\0');
          len = (undefined1 *)(~uVar2 - 1);
        }
        else if ((local_24c & 0x800) == 0) {
          len = (undefined1 *)(int)*psVar3;
          local_230 = 0;
        }
        else {
          local_230 = 1;
          len = (undefined1 *)((uint)(int)*psVar3 >> 1);
        }
        break;
      case 'd':
      case 'i':
        local_22c = 10;
        local_24c = local_24c | 0x40;
        goto LAB_004090a7;
      case 'n':
        piVar4 = (int *)get_int_arg(&argptr);
        if ((local_24c & 0x20) == 0) {
          local_228 = 1;
          *piVar4 = local_240;
        }
        else {
          local_228 = 1;
          *(undefined2 *)piVar4 = (undefined2)local_240;
        }
        break;
      case 'o':
        local_22c = 8;
        if ((local_24c & 0x80) != 0) {
          local_24c = local_24c | 0x200;
        }
        goto LAB_004090a7;
      case 'p':
        local_244 = 8;
switchD_00408d71_caseD_58:
        local_224 = 7;
LAB_00409062:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_004090a7;
      case 'u':
        local_22c = 10;
LAB_004090a7:
        if ((local_24c & 0x8000) == 0) {
          if ((local_24c & 0x20) == 0) {
            if ((local_24c & 0x40) == 0) {
              uVar2 = get_int_arg(&argptr);
              uVar11 = (ulonglong)uVar2;
            }
            else {
              iVar10 = get_int_arg(&argptr);
              uVar11 = (ulonglong)iVar10;
            }
          }
          else if ((local_24c & 0x40) == 0) {
            uVar2 = get_int_arg(&argptr);
            uVar11 = (ulonglong)uVar2 & 0xffffffff0000ffff;
          }
          else {
            iVar10 = get_int_arg(&argptr);
            uVar11 = (ulonglong)(int)(short)iVar10;
          }
        }
        else {
          uVar11 = get_int64_arg(&argptr);
        }
        iVar10 = (int)(uVar11 >> 0x20);
        if ((((local_24c & 0x40) != 0) && (iVar10 == 0 || (longlong)uVar11 < 0)) &&
           ((longlong)uVar11 < 0)) {
          local_24c = local_24c | 0x100;
          uVar11 = CONCAT44(-(iVar10 + (uint)((int)uVar11 != 0)),-(int)uVar11);
        }
        iVar10 = (int)(uVar11 >> 0x20);
        if ((local_24c & 0x8000) == 0) {
          iVar10 = 0;
        }
        lVar13 = CONCAT44(iVar10,(int)uVar11);
        if (local_244 < 0) {
          local_244 = 1;
        }
        else {
          local_24c = local_24c & 0xfffffff7;
        }
        local_248 = (ushort *)register0x00000010;
        if ((int)uVar11 == 0 && iVar10 == 0) {
          local_238 = 0;
        }
        while( true ) {
          uVar2 = local_22c;
          puVar5 = (ushort *)((int)local_248 + -1);
          iVar10 = local_244 + -1;
          if ((local_244 < 1) && (lVar13 == 0)) break;
          local_204 = (int)local_22c >> 0x1f;
          uVar14 = (uint)((ulonglong)lVar13 >> 0x20);
          uVar12 = __aullrem((uint)lVar13,uVar14,local_22c,local_204);
          iVar6 = (int)uVar12 + 0x30;
          lVar13 = __aulldiv((uint)lVar13,uVar14,uVar2,local_204);
          if (0x39 < iVar6) {
            iVar6 = iVar6 + local_224;
          }
          *(char *)puVar5 = (char)iVar6;
          local_244 = iVar10;
          local_248 = puVar5;
        }
        len = &uStack_1 + -(int)puVar5;
        local_244 = iVar10;
        if (((local_24c & 0x200) != 0) && (((char)*local_248 != '0' || (len == (undefined1 *)0x0))))
        {
          len = &stack0x00000000 + -(int)puVar5;
          *(char *)puVar5 = '0';
          local_248 = puVar5;
        }
        break;
      case 'x':
        local_224 = 0x27;
        goto LAB_00409062;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_0040923f;
              local_23a = ' ';
            }
            else {
              local_23a = '+';
            }
          }
          else {
            local_23a = '-';
          }
          local_238 = 1;
        }
LAB_0040923f:
        iVar10 = (local_234 - local_238) - (int)len;
        if ((local_24c & 0xc) == 0) {
          write_multi_char(0x20,iVar10,stream,&local_240);
        }
        write_string(&local_23a,local_238,stream,&local_240);
        if (((local_24c & 8) != 0) && ((local_24c & 4) == 0)) {
          write_multi_char(0x30,iVar10,stream,&local_240);
        }
        if ((local_230 == 0) || (puVar5 = local_248, puVar8 = len, (int)len < 1)) {
          write_string((char *)local_248,(int)len,stream,&local_240);
        }
        else {
          do {
            puVar8 = puVar8 + -1;
            iVar6 = wctomb(local_214,*puVar5);
            if (iVar6 < 1) break;
            write_string(local_214,iVar6,stream,&local_240);
            puVar5 = puVar5 + 1;
          } while (puVar8 != (undefined1 *)0x0);
        }
        if ((local_24c & 4) != 0) {
          write_multi_char(0x20,iVar10,stream,&local_240);
        }
      }
    }
    cVar7 = *fmt;
    local_21c = CONCAT31(local_21c._1_3_,cVar7);
    pcVar9 = fmt;
  } while( true );
}


/* ==== write_char @ 00409470 ==== */

void __cdecl write_char(int ch,void *stream,int *pnumwritten)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)((int)stream + 4) + -1;
  *(int *)((int)stream + 4) = iVar1;
  if (iVar1 < 0) {
    uVar2 = _flsbuf(ch,stream);
  }
  else {
    **(undefined1 **)stream = (char)ch;
    uVar2 = ch & 0xff;
    *(int *)stream = *(int *)stream + 1;
  }
  if (uVar2 == 0xffffffff) {
    *pnumwritten = -1;
    return;
  }
  *pnumwritten = *pnumwritten + 1;
  return;
}


/* ==== write_multi_char @ 004094c0 ==== */

void __cdecl write_multi_char(int ch,int num,void *stream,int *pnumwritten)

{
  do {
    if (num < 1) {
      return;
    }
    num = num + -1;
    write_char(ch,stream,pnumwritten);
  } while (*pnumwritten != -1);
  return;
}


/* ==== write_string @ 00409500 ==== */

void __cdecl write_string(char *string,int len,void *stream,int *pnumwritten)

{
  char cVar1;
  
  do {
    if (len < 1) {
      return;
    }
    len = len + -1;
    cVar1 = *string;
    string = string + 1;
    write_char((int)cVar1,stream,pnumwritten);
  } while (*pnumwritten != -1);
  return;
}


/* ==== get_int_arg @ 00409540 ==== */

int __cdecl get_int_arg(void *pargptr)

{
  int *piVar1;
  
  piVar1 = *(int **)pargptr;
  *(int **)pargptr = piVar1 + 1;
  return *piVar1;
}


/* ==== get_int64_arg @ 00409560 ==== */

longlong __cdecl get_int64_arg(void *pargptr)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)pargptr;
  *(longlong **)pargptr = plVar1 + 1;
  return *plVar1;
}


/* ==== get_short_arg @ 00409580 ==== */

short __cdecl get_short_arg(void *pargptr)

{
  short *psVar1;
  
  psVar1 = *(short **)pargptr;
  *(short **)pargptr = psVar1 + 2;
  return *psVar1;
}


/* ==== _ioinit @ 004095a0 ==== */

void _ioinit(void)

{
  byte bVar1;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar2;
  DWORD DVar3;
  HANDLE hFile;
  int iVar4;
  byte *pbVar5;
  int *piVar6;
  uint uVar7;
  UINT *pUVar8;
  UINT local_48;
  _STARTUPINFOA local_44;
  
  malloc(0x100);
  if (extraout_EAX == (undefined4 *)0x0) {
    _amsg_exit(0x1b);
  }
  _nhandle = 0x20;
  puVar2 = extraout_EAX;
  __pioinfo = extraout_EAX;
  if (extraout_EAX < extraout_EAX + 0x40) {
    do {
      *(undefined1 *)(puVar2 + 1) = 0;
      *puVar2 = 0xffffffff;
      *(undefined1 *)((int)puVar2 + 5) = 10;
      puVar2 = puVar2 + 2;
    } while (puVar2 < __pioinfo + 0x40);
  }
  GetStartupInfoA(&local_44);
  if ((local_44.cbReserved2 != 0) && ((UINT *)local_44.lpReserved2 != (UINT *)0x0)) {
    local_48 = *(UINT *)local_44.lpReserved2;
    pUVar8 = (UINT *)((int)local_44.lpReserved2 + 4);
    pbVar5 = (byte *)((int)pUVar8 + local_48);
    if (0x7ff < (int)local_48) {
      local_48 = 0x800;
    }
    if ((int)_nhandle < (int)local_48) {
      piVar6 = &DAT_004129a4;
      do {
        malloc(0x100);
        if (extraout_EAX_00 == (undefined4 *)0x0) {
          local_48 = _nhandle;
          break;
        }
        *piVar6 = (int)extraout_EAX_00;
        _nhandle = _nhandle + 0x20;
        puVar2 = extraout_EAX_00;
        if (extraout_EAX_00 < extraout_EAX_00 + 0x40) {
          do {
            *(undefined1 *)(puVar2 + 1) = 0;
            *puVar2 = 0xffffffff;
            *(undefined1 *)((int)puVar2 + 5) = 10;
            puVar2 = puVar2 + 2;
          } while (puVar2 < (undefined4 *)(*piVar6 + 0x100));
        }
        piVar6 = piVar6 + 1;
      } while ((int)_nhandle < (int)local_48);
    }
    uVar7 = 0;
    if (0 < (int)local_48) {
      do {
        if (((*(HANDLE *)pbVar5 != (HANDLE)0xffffffff) && ((*pUVar8 & 1) != 0)) &&
           (((*pUVar8 & 8) != 0 || (DVar3 = GetFileType(*(HANDLE *)pbVar5), DVar3 != 0)))) {
          iVar4 = (int)(&__pioinfo)[(int)uVar7 >> 5];
          *(undefined4 *)(iVar4 + (uVar7 & 0x1f) * 8) = *(undefined4 *)pbVar5;
          *(byte *)(iVar4 + (uVar7 & 0x1f) * 8 + 4) = (byte)*pUVar8;
        }
        uVar7 = uVar7 + 1;
        pUVar8 = (UINT *)((int)pUVar8 + 1);
        pbVar5 = pbVar5 + 4;
      } while ((int)uVar7 < (int)local_48);
    }
  }
  iVar4 = 0;
  do {
    puVar2 = __pioinfo + iVar4 * 2;
    if (__pioinfo[iVar4 * 2] == -1) {
      *(undefined1 *)(puVar2 + 1) = 0x81;
      if (iVar4 == 0) {
        DVar3 = 0xfffffff6;
      }
      else {
        DVar3 = 0xfffffff5 - (iVar4 != 1);
      }
      hFile = GetStdHandle(DVar3);
      if ((hFile == (HANDLE)0xffffffff) || (DVar3 = GetFileType(hFile), DVar3 == 0)) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_0040977b;
      }
      *puVar2 = hFile;
      if ((DVar3 & 0xff) == 2) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_0040977b;
      }
      if ((DVar3 & 0xff) == 3) {
        bVar1 = *(byte *)(puVar2 + 1) | 8;
        goto LAB_0040977b;
      }
    }
    else {
      bVar1 = *(byte *)(puVar2 + 1) | 0x80;
LAB_0040977b:
      *(byte *)(puVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(_nhandle);
      return;
    }
  } while( true );
}


/* ==== _XcptFilter @ 00409810 ==== */

int __cdecl _XcptFilter(ulong xcptnum,void *pxcptptrs)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  undefined4 *puVar6;
  int iVar7;
  
  piVar4 = FUN_00409950(xcptnum);
  uVar3 = DAT_00412738;
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    LVar5 = UnhandledExceptionFilter(pxcptptrs);
    return LVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 != (code *)0x1) {
    DAT_00412738 = pxcptptrs;
    if (piVar4[1] == 8) {
      if (DAT_00411620 < DAT_00411624 + DAT_00411620) {
        iVar7 = (DAT_00411624 + DAT_00411620) - DAT_00411620;
        puVar6 = (undefined4 *)(DAT_00411620 * 0xc + 0x4115b0);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar2 = DAT_0041162c;
      iVar7 = *piVar4;
      if (iVar7 == -0x3fffff72) {
        DAT_0041162c = 0x83;
      }
      else if (iVar7 == -0x3fffff70) {
        DAT_0041162c = 0x81;
      }
      else if (iVar7 == -0x3fffff6f) {
        DAT_0041162c = 0x84;
      }
      else if (iVar7 == -0x3fffff6d) {
        DAT_0041162c = 0x85;
      }
      else if (iVar7 == -0x3fffff73) {
        DAT_0041162c = 0x82;
      }
      else if (iVar7 == -0x3fffff71) {
        DAT_0041162c = 0x86;
      }
      else if (iVar7 == -0x3fffff6e) {
        DAT_0041162c = 0x8a;
      }
      (*pcVar1)(8,DAT_0041162c);
      DAT_0041162c = uVar2;
      DAT_00412738 = (void *)uVar3;
      return -1;
    }
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    DAT_00412738 = (void *)uVar3;
    return -1;
  }
  return -1;
}


/* ==== FUN_00409950 @ 00409950 ==== */

int * __cdecl FUN_00409950(int param_1)

{
  int *piVar1;
  
  piVar1 = &_XcptActTab;
  if (_XcptActTab != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (&_XcptActTab + _XcptActTabCount * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((&_XcptActTab + _XcptActTabCount * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}


/* ==== _openfile @ 004099a0 ==== */

void __cdecl _openfile(char *name,char *mode,int shflag,void *stream)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint oflag;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  
  cVar1 = *mode;
  bVar3 = false;
  bVar4 = false;
  if (cVar1 == 'a') {
    oflag = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      oflag = 0;
      uVar7 = DAT_00412974 | 1;
      goto LAB_004099dd;
    }
    if (cVar1 != 'w') {
      return;
    }
    oflag = 0x301;
  }
  uVar7 = DAT_00412974 | 2;
LAB_004099dd:
  pcVar6 = mode + 1;
  bVar2 = true;
  cVar1 = *pcVar6;
  do {
    if ((cVar1 == '\0') || (!bVar2)) {
      iVar5 = _sopen(name,oflag,shflag,0x1a4);
      if (-1 < iVar5) {
        _cflush = _cflush + 1;
        *(uint *)((int)stream + 0xc) = uVar7;
        *(undefined4 *)((int)stream + 4) = 0;
        *(undefined4 *)stream = 0;
        *(undefined4 *)((int)stream + 8) = 0;
        *(undefined4 *)((int)stream + 0x1c) = 0;
        *(int *)((int)stream + 0x10) = iVar5;
        return;
      }
      return;
    }
    switch(cVar1) {
    case '+':
      if ((oflag & 2) != 0) break;
      oflag = oflag & 0xfffffffe | 2;
      uVar7 = uVar7 & 0xfffffffc | 0x80;
      goto LAB_00409a8e;
    case 'D':
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_00409a8e;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x10;
        goto LAB_00409a8e;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x20;
        goto LAB_00409a8e;
      }
      break;
    case 'T':
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_00409a8e;
      }
      break;
    case 'b':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x8000;
        goto LAB_00409a8e;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_00409a8e;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_00409a8e;
      }
      break;
    case 't':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x4000;
        goto LAB_00409a8e;
      }
    }
    bVar2 = false;
LAB_00409a8e:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}


/* ==== _getstream @ 00409b70 ==== */

void _getstream(void)

{
  int extraout_EAX;
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)0x0;
  iVar1 = 0;
  piVar2 = __piob;
  if (0 < _nstream) {
    do {
      if (*piVar2 == 0) {
        malloc(0x20);
        __piob[iVar1] = extraout_EAX;
        if ((undefined4 *)__piob[iVar1] != (undefined4 *)0x0) {
          puVar3 = (undefined4 *)__piob[iVar1];
        }
        break;
      }
      if ((*(byte *)(*piVar2 + 0xc) & 0x83) == 0) {
        puVar3 = (undefined4 *)__piob[iVar1];
        break;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < _nstream);
  }
  if (puVar3 != (undefined4 *)0x0) {
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[2] = 0;
    *puVar3 = 0;
    puVar3[7] = 0;
    puVar3[4] = 0xffffffff;
  }
  return;
}


/* ==== _lseek @ 00409c00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long __cdecl _lseek(int fh,long pos,int mthd)

{
  HANDLE hFile;
  DWORD DVar1;
  ulong oserrno;
  int iVar2;
  
  if ((uint)fh < _nhandle) {
    iVar2 = (fh & 0x1fU) * 8;
    if ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar2) & 1) != 0) {
      hFile = (HANDLE)_get_osfhandle(fh);
      if (hFile == (HANDLE)0xffffffff) {
        _errno = 9;
        return -1;
      }
      DVar1 = SetFilePointer(hFile,pos,(PLONG)0x0,mthd);
      if (DVar1 == 0xffffffff) {
        oserrno = GetLastError();
      }
      else {
        oserrno = 0;
      }
      if (oserrno != 0) {
        _dosmaperr(oserrno);
        return -1;
      }
      *(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar2) =
           *(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar2) & 0xfd;
      return DVar1;
    }
  }
  _errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _filbuf @ 00409cc0 ==== */

int __cdecl _filbuf(void *stream)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar2 = *(uint *)((int)stream + 0xc);
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) != 0) {
      *(uint *)((int)stream + 0xc) = uVar2 | 0x20;
      return -1;
    }
    *(uint *)((int)stream + 0xc) = uVar2 | 1;
    if ((uVar2 & 0x10c) == 0) {
      _getbuf(stream);
    }
    else {
      *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    }
    iVar3 = _read(*(int *)((int)stream + 0x10),*(void **)((int)stream + 8),
                  *(uint *)((int)stream + 0x18));
    *(int *)((int)stream + 4) = iVar3;
    if ((iVar3 != 0) && (iVar3 != -1)) {
      if ((*(uint *)((int)stream + 0xc) & 0x82) == 0) {
        uVar2 = *(uint *)((int)stream + 0x10);
        if (uVar2 == 0xffffffff) {
          puVar4 = &__badioinfo;
        }
        else {
          puVar4 = (undefined *)((&__pioinfo)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 8);
        }
        if ((puVar4[4] & 0x82) == 0x82) {
          *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 0x2000;
        }
      }
      if (((*(int *)((int)stream + 0x18) == 0x200) && ((*(uint *)((int)stream + 0xc) & 8) != 0)) &&
         ((*(uint *)((int)stream + 0xc) & 0x400) == 0)) {
        *(undefined4 *)((int)stream + 0x18) = 0x1000;
      }
      *(int *)((int)stream + 4) = iVar3 + -1;
      bVar1 = **(byte **)stream;
      *(byte **)stream = *(byte **)stream + 1;
      return (uint)bVar1;
    }
    *(undefined4 *)((int)stream + 4) = 0;
    *(uint *)((int)stream + 0xc) =
         *(uint *)((int)stream + 0xc) | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
  }
  return -1;
}


/* ==== _flsbuf @ 00409db0 ==== */

int __cdecl _flsbuf(int c,void *stream)

{
  uint fh;
  void *buf;
  void *stream_00;
  int iVar1;
  undefined *puVar2;
  uint uVar3;
  uint uVar4;
  
  stream_00 = stream;
  uVar4 = *(uint *)((int)stream + 0xc);
  fh = *(uint *)((int)stream + 0x10);
  if (((uVar4 & 0x82) == 0) || ((uVar4 & 0x40) != 0)) {
LAB_00409ed0:
    *(uint *)((int)stream + 0xc) = uVar4 | 0x20;
    return -1;
  }
  uVar3 = 0;
  if ((uVar4 & 1) != 0) {
    *(undefined4 *)((int)stream + 4) = 0;
    if ((uVar4 & 0x10) == 0) goto LAB_00409ed0;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(uint *)((int)stream + 0xc) = uVar4 & 0xfffffffe;
  }
  uVar4 = *(uint *)((int)stream + 0xc);
  *(undefined4 *)((int)stream + 4) = 0;
  *(uint *)((int)stream + 0xc) = uVar4 & 0xffffffef | 2;
  if ((uVar4 & 0x10c) == 0) {
    if ((stream == &DAT_0040f2e8) || (stream == &DAT_0040f308)) {
      iVar1 = _isatty(fh);
      if (iVar1 != 0) goto LAB_00409e23;
    }
    _getbuf(stream_00);
  }
LAB_00409e23:
  if ((*(uint *)((int)stream_00 + 0xc) & 0x108) == 0) {
    uVar4 = 1;
    uVar3 = _write(fh,&c,1);
  }
  else {
    buf = *(void **)((int)stream_00 + 8);
    uVar4 = *(int *)stream_00 - (int)buf;
    *(int *)stream_00 = (int)buf + 1;
    *(int *)((int)stream_00 + 4) = *(int *)((int)stream_00 + 0x18) + -1;
    if ((int)uVar4 < 1) {
      if (fh == 0xffffffff) {
        puVar2 = &__badioinfo;
      }
      else {
        puVar2 = (undefined *)((&__pioinfo)[(int)fh >> 5] + (fh & 0x1f) * 8);
      }
      if ((puVar2[4] & 0x20) != 0) {
        _lseek(fh,0,2);
      }
      **(undefined1 **)((int)stream_00 + 8) = (undefined1)c;
    }
    else {
      uVar3 = _write(fh,buf,uVar4);
      **(undefined1 **)((int)stream_00 + 8) = (undefined1)c;
    }
  }
  if (uVar3 != uVar4) {
    *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x20;
    return -1;
  }
  return c & 0xff;
}


/* ==== fwrite @ 00409ee0 ==== */

uint __cdecl fwrite(void *buf,uint size,uint n,void *stream)

{
  void *stream_00;
  void *pvVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  void *pvVar5;
  void *pvVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  stream_00 = stream;
  pvVar5 = (void *)(n * size);
  if (pvVar5 == (void *)0x0) {
    return 0;
  }
  pvVar6 = pvVar5;
  if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
    stream = (void *)0x1000;
  }
  else {
    stream = *(void **)((int)stream + 0x18);
  }
  do {
    uVar4 = *(uint *)((int)stream_00 + 0xc) & 0x108;
    if ((uVar4 == 0) || (pvVar1 = *(void **)((int)stream_00 + 4), pvVar1 == (void *)0x0)) {
      if (pvVar6 < stream) {
        iVar2 = _flsbuf((int)*(char *)buf,stream_00);
        if (iVar2 == -1) goto LAB_0040a014;
        stream = *(void **)((int)stream_00 + 0x18);
        buf = (void *)((int)buf + 1);
        pvVar6 = (void *)((int)pvVar6 - 1);
        if ((int)stream < 1) {
          stream = (void *)0x1;
        }
      }
      else {
        if ((uVar4 != 0) && (iVar2 = _flush(stream_00), iVar2 != 0)) {
LAB_0040a014:
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        pvVar1 = pvVar6;
        if (stream != (void *)0x0) {
          pvVar1 = (void *)((int)pvVar6 - (uint)pvVar6 % (uint)stream);
        }
        pvVar3 = (void *)_write(*(int *)((int)stream_00 + 0x10),buf,(uint)pvVar1);
        if (pvVar3 == (void *)0xffffffff) {
LAB_00409ff9:
          *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x20;
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        pvVar6 = (void *)((int)pvVar6 - (int)pvVar3);
        buf = (void *)((int)buf + (int)pvVar3);
        if (pvVar3 < pvVar1) goto LAB_00409ff9;
      }
    }
    else {
      if (pvVar6 < pvVar1) {
        pvVar1 = pvVar6;
      }
      pvVar6 = (void *)((int)pvVar6 - (int)pvVar1);
      puVar7 = buf;
      puVar8 = *(undefined4 **)stream_00;
      for (uVar4 = (uint)pvVar1 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar4 = (uint)pvVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      buf = (void *)((int)buf + (int)pvVar1);
      *(int *)((int)stream_00 + 4) = *(int *)((int)stream_00 + 4) - (int)pvVar1;
      *(int *)stream_00 = *(int *)stream_00 + (int)pvVar1;
    }
    if (pvVar6 == (void *)0x0) {
      return n;
    }
  } while( true );
}


/* ==== _getbuf @ 0040a030 ==== */

void __cdecl _getbuf(void *stream)

{
  int extraout_EAX;
  
  _cflush = _cflush + 1;
  malloc(0x1000);
  *(int *)((int)stream + 8) = extraout_EAX;
  if (extraout_EAX != 0) {
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 8;
    *(undefined4 *)((int)stream + 0x18) = 0x1000;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(undefined4 *)((int)stream + 4) = 0;
    return;
  }
  *(undefined4 *)((int)stream + 0x18) = 2;
  *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 4;
  *(int *)((int)stream + 8) = (int)stream + 0x14;
  *(int *)stream = (int)stream + 0x14;
  *(undefined4 *)((int)stream + 4) = 0;
  return;
}


/* ==== _read @ 0040a090 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _read(int fh,void *buf,uint cnt)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  LPVOID lpBuffer;
  BOOL BVar4;
  DWORD DVar5;
  uint nNumberOfBytesToRead;
  int iVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  DWORD local_c;
  int *local_8;
  char *local_4;
  
  if ((uint)fh < _nhandle) {
    iVar6 = (fh & 0x1fU) * 8;
    piVar1 = &__pioinfo + (fh >> 5);
    local_c = iVar6 + (&__pioinfo)[fh >> 5];
    bVar3 = *(byte *)(local_c + 4);
    if ((bVar3 & 1) != 0) {
      iVar7 = 0;
      if ((cnt == 0) || ((bVar3 & 2) != 0)) {
        return 0;
      }
      lpBuffer = buf;
      nNumberOfBytesToRead = cnt;
      if (((bVar3 & 0x48) != 0) && (*(char *)(local_c + 5) != '\n')) {
        *(char *)buf = *(char *)(local_c + 5);
        lpBuffer = (LPVOID)((int)buf + 1);
        iVar7 = 1;
        nNumberOfBytesToRead = cnt - 1;
        *(undefined1 *)(iVar6 + 5 + *piVar1) = 10;
      }
      local_8 = piVar1;
      BVar4 = ReadFile(*(HANDLE *)(iVar6 + *piVar1),lpBuffer,nNumberOfBytesToRead,&local_c,
                       (LPOVERLAPPED)0x0);
      if (BVar4 == 0) {
        DVar5 = GetLastError();
        if (DVar5 == 5) {
          _doserrno = DVar5;
          _errno = 9;
          return -1;
        }
        if (DVar5 == 0x6d) {
          return 0;
        }
        _dosmaperr(DVar5);
        return -1;
      }
      iVar7 = iVar7 + local_c;
      bVar3 = *(byte *)(iVar6 + 4 + *piVar1);
      if ((bVar3 & 0x80) != 0) {
        if ((local_c == 0) || (*(char *)buf != '\n')) {
          bVar3 = bVar3 & 0xfb;
        }
        else {
          bVar3 = bVar3 | 4;
        }
        *(byte *)(iVar6 + 4 + *piVar1) = bVar3;
        local_4 = (char *)(iVar7 + (int)buf);
        pcVar8 = buf;
        pcVar9 = buf;
        if (buf < local_4) {
          while (cVar2 = *pcVar9, cVar2 != '\x1a') {
            if (cVar2 == '\r') {
              if (pcVar9 < local_4 + -1) {
                if (pcVar9[1] == '\n') {
                  pcVar9 = pcVar9 + 2;
                  *pcVar8 = '\n';
                  goto LAB_0040a278;
                }
                *pcVar8 = '\r';
                pcVar8 = pcVar8 + 1;
                pcVar9 = pcVar9 + 1;
              }
              else {
                DVar5 = 0;
                pcVar9 = pcVar9 + 1;
                BVar4 = ReadFile(*(HANDLE *)(iVar6 + *local_8),&cnt,1,&local_c,(LPOVERLAPPED)0x0);
                if (BVar4 == 0) {
                  DVar5 = GetLastError();
                }
                if ((DVar5 == 0) && (local_c != 0)) {
                  if ((*(byte *)(iVar6 + 4 + *local_8) & 0x48) == 0) {
                    if ((pcVar8 == buf) && ((char)cnt == '\n')) {
                      *pcVar8 = '\n';
                      goto LAB_0040a278;
                    }
                    _lseek(fh,-1,1);
                    if ((char)cnt != '\n') goto LAB_0040a275;
                  }
                  else {
                    if ((char)cnt == '\n') {
                      *pcVar8 = '\n';
                      goto LAB_0040a278;
                    }
                    *pcVar8 = '\r';
                    pcVar8 = pcVar8 + 1;
                    *(char *)(iVar6 + 5 + *local_8) = (char)cnt;
                  }
                }
                else {
LAB_0040a275:
                  *pcVar8 = '\r';
LAB_0040a278:
                  pcVar8 = pcVar8 + 1;
                }
              }
            }
            else {
              *pcVar8 = cVar2;
              pcVar8 = pcVar8 + 1;
              pcVar9 = pcVar9 + 1;
            }
            if (local_4 <= pcVar9) {
              return (int)pcVar8 - (int)buf;
            }
          }
          bVar3 = *(byte *)(iVar6 + 4 + *local_8);
          if ((bVar3 & 0x40) == 0) {
            *(byte *)(iVar6 + 4 + *local_8) = bVar3 | 2;
          }
        }
        iVar7 = (int)pcVar8 - (int)buf;
      }
      return iVar7;
    }
  }
  _errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _setenvp @ 0040a2f0 ==== */

void _setenvp(void)

{
  char cVar1;
  char cVar2;
  int *extraout_EAX;
  int extraout_EAX_00;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  int *piVar9;
  char *pcVar10;
  int *local_4;
  
  iVar7 = 0;
  cVar2 = *_aenvptr;
  pcVar6 = _aenvptr;
  while (cVar2 != '\0') {
    if (cVar2 != '=') {
      iVar7 = iVar7 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar8 = pcVar6;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar2 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar2 != '\0');
    pcVar8 = pcVar6 + ~uVar3;
    pcVar6 = pcVar6 + ~uVar3;
    cVar2 = *pcVar8;
  }
  malloc(iVar7 * 4 + 4);
  _environ = extraout_EAX;
  if (extraout_EAX == (int *)0x0) {
    _amsg_exit(9);
  }
  cVar2 = *_aenvptr;
  piVar9 = extraout_EAX;
  local_4 = extraout_EAX;
  pcVar6 = _aenvptr;
  do {
    if (cVar2 == '\0') {
      free(_aenvptr);
      _aenvptr = (char *)0x0;
      *piVar9 = 0;
      return;
    }
    uVar3 = 0xffffffff;
    pcVar8 = pcVar6;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    if (cVar2 != '=') {
      malloc(uVar3);
      *piVar9 = extraout_EAX_00;
      if (extraout_EAX_00 == 0) {
        _amsg_exit(9);
      }
      uVar4 = 0xffffffff;
      pcVar8 = pcVar6;
      do {
        pcVar10 = pcVar8;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar10 = pcVar8 + 1;
        cVar2 = *pcVar8;
        pcVar8 = pcVar10;
      } while (cVar2 != '\0');
      uVar4 = ~uVar4;
      pcVar8 = pcVar10 + -uVar4;
      pcVar10 = (char *)*local_4;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar10 = pcVar10 + 4;
      }
      piVar9 = local_4 + 1;
      for (uVar4 = uVar4 & 3; local_4 = piVar9, uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar10 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      }
    }
    cVar2 = pcVar6[uVar3];
    pcVar6 = pcVar6 + uVar3;
  } while( true );
}


/* ==== _setargv @ 0040a3e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _setargv(void)

{
  char **argv;
  char *cmdstart;
  int local_8;
  int local_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_00412740,0x104);
  _DAT_004126b8 = &DAT_00412740;
  cmdstart = _acmdln;
  if (*_acmdln == '\0') {
    cmdstart = &DAT_00412740;
  }
  parse_cmdline(cmdstart,(char **)0x0,(char *)0x0,&local_8,&local_4);
  malloc(local_4 + local_8 * 4);
  if (argv == (char **)0x0) {
    _amsg_exit(8);
  }
  parse_cmdline(cmdstart,argv,(char *)(argv + local_8),&local_8,&local_4);
  __argv = argv;
  __argc = local_8 + -1;
  return;
}


/* ==== parse_cmdline @ 0040a480 ==== */

void __cdecl parse_cmdline(char *cmdstart,char **argv,char *args,int *numargs,int *numchars)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  byte *pbVar7;
  uint uVar8;
  
  piVar6 = numchars;
  *numchars = 0;
  *numargs = 1;
  if (argv != (char **)0x0) {
    *argv = args;
    argv = argv + 1;
  }
  if (*cmdstart == '\"') {
    bVar2 = cmdstart[1];
    while ((pbVar7 = (byte *)(cmdstart + 1), bVar2 != 0x22 && (bVar2 != 0))) {
      if (((*(byte *)((int)&DAT_00412850 + bVar2 + 1) & 4) != 0) &&
         (*numchars = *numchars + 1, (byte *)args != (byte *)0x0)) {
        *args = *pbVar7;
        args = args + 1;
        pbVar7 = (byte *)(cmdstart + 2);
      }
      *numchars = *numchars + 1;
      if ((byte *)args != (byte *)0x0) {
        *args = *pbVar7;
        args = args + 1;
      }
      cmdstart = (char *)pbVar7;
      bVar2 = pbVar7[1];
    }
    *numchars = *numchars + 1;
    if ((byte *)args != (byte *)0x0) {
      *args = 0;
      args = args + 1;
    }
    if (*pbVar7 == 0x22) {
      pbVar7 = (byte *)(cmdstart + 2);
    }
  }
  else {
    do {
      *piVar6 = *piVar6 + 1;
      if ((byte *)args != (byte *)0x0) {
        *args = *cmdstart;
        args = args + 1;
      }
      bVar2 = *cmdstart;
      pbVar7 = (byte *)(cmdstart + 1);
      numchars = (int *)(uint)bVar2;
      if ((*(byte *)((int)numchars + 0x412851) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if ((byte *)args != (byte *)0x0) {
          *args = *pbVar7;
          args = args + 1;
        }
        pbVar7 = (byte *)(cmdstart + 2);
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_0040a559;
      cmdstart = (char *)pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_0040a559:
      pbVar7 = pbVar7 + -1;
    }
    else if ((byte *)args != (byte *)0x0) {
      args[-1] = 0;
    }
  }
  bVar4 = false;
  bVar5 = false;
  while (*pbVar7 != 0) {
    for (; (*pbVar7 == 0x20 || (*pbVar7 == 9)); pbVar7 = pbVar7 + 1) {
    }
    if (*pbVar7 == 0) break;
    if (argv != (char **)0x0) {
      *argv = args;
      argv = argv + 1;
    }
    *numargs = *numargs + 1;
    while( true ) {
      uVar8 = 0;
      bVar3 = true;
      bVar2 = *pbVar7;
      while (bVar2 == 0x5c) {
        pbVar1 = pbVar7 + 1;
        pbVar7 = pbVar7 + 1;
        uVar8 = uVar8 + 1;
        bVar2 = *pbVar1;
      }
      if (*pbVar7 == 0x22) {
        if ((uVar8 & 1) == 0) {
          if ((bVar4) && (pbVar7[1] == 0x22)) {
            pbVar7 = pbVar7 + 1;
          }
          else {
            bVar3 = false;
          }
          bVar4 = !bVar5;
          bVar5 = bVar4;
        }
        uVar8 = uVar8 >> 1;
      }
      for (; uVar8 != 0; uVar8 = uVar8 - 1) {
        if ((byte *)args != (byte *)0x0) {
          *args = 0x5c;
          args = args + 1;
        }
        *piVar6 = *piVar6 + 1;
      }
      bVar2 = *pbVar7;
      if ((bVar2 == 0) || ((!bVar4 && ((bVar2 == 0x20 || (bVar2 == 9)))))) break;
      if (bVar3) {
        if ((byte *)args == (byte *)0x0) {
          if ((*(byte *)((int)&DAT_00412850 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_0040a655;
        }
        if ((*(byte *)((int)&DAT_00412850 + bVar2 + 1) & 4) != 0) {
          *args = bVar2;
          args = args + 1;
          pbVar7 = pbVar7 + 1;
          *piVar6 = *piVar6 + 1;
        }
        *args = *pbVar7;
        args = args + 1;
        *piVar6 = *piVar6 + 1;
        pbVar7 = pbVar7 + 1;
      }
      else {
LAB_0040a655:
        pbVar7 = pbVar7 + 1;
      }
    }
    if ((byte *)args != (byte *)0x0) {
      *args = 0;
      args = args + 1;
    }
    *piVar6 = *piVar6 + 1;
  }
  if (argv != (char **)0x0) {
    *argv = (char *)0x0;
  }
  *numargs = *numargs + 1;
  return;
}


/* ==== __crtGetEnvironmentStringsA @ 0040a690 ==== */

void __crtGetEnvironmentStringsA(void)

{
  char cVar1;
  WCHAR WVar2;
  WCHAR *pWVar3;
  int iVar5;
  uint uVar6;
  LPSTR lpMultiByteStr;
  LPCH pCVar7;
  CHAR *extraout_EAX;
  LPCH pCVar8;
  LPWCH lpWideCharStr;
  LPCH pCVar9;
  CHAR *pCVar10;
  WCHAR *pWVar4;
  
  lpWideCharStr = (LPWCH)0x0;
  pCVar8 = (LPCH)0x0;
  if (DAT_00412848 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr == (LPWCH)0x0) {
      pCVar8 = GetEnvironmentStrings();
      if (pCVar8 == (LPCH)0x0) {
        return;
      }
      DAT_00412848 = 2;
    }
    else {
      DAT_00412848 = 1;
    }
  }
  if (DAT_00412848 == 1) {
    if ((lpWideCharStr != (LPWCH)0x0) ||
       (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr != (LPWCH)0x0)) {
      WVar2 = *lpWideCharStr;
      pWVar3 = lpWideCharStr;
      while (WVar2 != L'\0') {
        do {
          pWVar4 = pWVar3;
          pWVar3 = pWVar4 + 1;
        } while (*pWVar3 != L'\0');
        pWVar3 = pWVar4 + 2;
        WVar2 = *pWVar3;
      }
      iVar5 = ((int)pWVar3 - (int)lpWideCharStr >> 1) + 1;
      uVar6 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      if ((uVar6 != 0) && (malloc(uVar6), lpMultiByteStr != (LPSTR)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,lpMultiByteStr,uVar6,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        if (iVar5 == 0) {
          free(lpMultiByteStr);
        }
        FreeEnvironmentStringsW(lpWideCharStr);
        return;
      }
      FreeEnvironmentStringsW(lpWideCharStr);
      return;
    }
  }
  else if ((DAT_00412848 == 2) &&
          ((pCVar8 != (LPCH)0x0 || (pCVar8 = GetEnvironmentStrings(), pCVar8 != (LPCH)0x0)))) {
    cVar1 = *pCVar8;
    pCVar7 = pCVar8;
    while (cVar1 != '\0') {
      do {
        pCVar9 = pCVar7;
        pCVar7 = pCVar9 + 1;
      } while (pCVar9[1] != '\0');
      pCVar7 = pCVar9 + 2;
      cVar1 = pCVar9[2];
    }
    pCVar7 = pCVar7 + (1 - (int)pCVar8);
    malloc((uint)pCVar7);
    if (extraout_EAX != (CHAR *)0x0) {
      pCVar9 = pCVar8;
      pCVar10 = extraout_EAX;
      for (uVar6 = (uint)pCVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pCVar10 = *(undefined4 *)pCVar9;
        pCVar9 = pCVar9 + 4;
        pCVar10 = pCVar10 + 4;
      }
      for (uVar6 = (uint)pCVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pCVar10 = *pCVar9;
        pCVar9 = pCVar9 + 1;
        pCVar10 = pCVar10 + 1;
      }
      FreeEnvironmentStringsA(pCVar8);
      return;
    }
    FreeEnvironmentStringsA(pCVar8);
    return;
  }
  return;
}


/* ==== _setmbcp @ 0040a7f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _setmbcp(int codepage)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  UINT CodePage;
  UINT *pUVar5;
  BOOL BVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  BYTE *pBVar11;
  byte *pbVar12;
  byte *pbVar13;
  undefined4 *puVar14;
  _cpinfo local_14;
  
  CodePage = FUN_0040a9e0(codepage);
  if (CodePage == DAT_00412954) {
    return 0;
  }
  if (CodePage == 0) {
    FUN_0040aa90();
    return 0;
  }
  iVar10 = 0;
  pUVar5 = &DAT_00411638;
  do {
    if (*pUVar5 == CodePage) {
      puVar14 = &DAT_00412850;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined1 *)puVar14 = 0;
      uVar7 = 0;
      iVar10 = iVar10 * 0x30;
      pbVar12 = (byte *)(iVar10 + 0x411648);
      do {
        bVar3 = *pbVar12;
        for (pbVar13 = pbVar12; (bVar3 != 0 && (bVar3 = pbVar13[1], bVar3 != 0));
            pbVar13 = pbVar13 + 2) {
          uVar8 = (uint)*pbVar13;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_00411630)[uVar7];
            do {
              pbVar2 = (byte *)((int)&DAT_00412850 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          bVar3 = pbVar13[2];
        }
        uVar7 = uVar7 + 1;
        pbVar12 = pbVar12 + 8;
      } while (uVar7 < 4);
      DAT_00412954 = CodePage;
      _DAT_00412958 = FUN_0040aa30(CodePage);
      _DAT_00412960 = *(undefined4 *)(iVar10 + 0x41163c);
      _DAT_00412964 = *(undefined4 *)(iVar10 + 0x411640);
      _DAT_00412968 = *(undefined4 *)(iVar10 + 0x411644);
      return 0;
    }
    pUVar5 = pUVar5 + 0xc;
    iVar10 = iVar10 + 1;
  } while (pUVar5 < &DAT_00411728);
  BVar6 = GetCPInfo(CodePage,&local_14);
  if (BVar6 != 1) {
    if (DAT_0041296c == 0) {
      return -1;
    }
    FUN_0040aa90();
    return 0;
  }
  puVar14 = &DAT_00412850;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined1 *)puVar14 = 0;
  if (local_14.MaxCharSize < 2) {
    DAT_00412954 = 0;
    _DAT_00412958 = 0;
  }
  else {
    if (local_14.LeadByte[0] != '\0') {
      pBVar11 = local_14.LeadByte + 1;
      do {
        bVar3 = *pBVar11;
        if (bVar3 == 0) break;
        for (uVar7 = (uint)pBVar11[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
          *(byte *)((int)&DAT_00412850 + uVar7 + 1) = *(byte *)((int)&DAT_00412850 + uVar7 + 1) | 4;
        }
        pBVar1 = pBVar11 + 1;
        pBVar11 = pBVar11 + 2;
      } while (*pBVar1 != 0);
    }
    uVar7 = 1;
    do {
      *(byte *)((int)&DAT_00412850 + uVar7 + 1) = *(byte *)((int)&DAT_00412850 + uVar7 + 1) | 8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0xff);
    DAT_00412954 = CodePage;
    _DAT_00412958 = FUN_0040aa30(CodePage);
  }
  _DAT_00412960 = 0;
  _DAT_00412964 = 0;
  _DAT_00412968 = 0;
  return 0;
}


/* ==== FUN_0040a9e0 @ 0040a9e0 ==== */

int __cdecl FUN_0040a9e0(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_0041296c = 1;
                    /* WARNING: Could not recover jumptable at 0x0040a9fd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_0041296c = 1;
                    /* WARNING: Could not recover jumptable at 0x0040aa12. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_00412720;
  }
  DAT_0041296c = (uint)bVar2;
  return param_1;
}


/* ==== FUN_0040aa30 @ 0040aa30 ==== */

undefined4 __cdecl FUN_0040aa30(undefined4 param_1)

{
  switch(param_1) {
  case 0x3a4:
    return 0x411;
  default:
    return 0;
  case 0x3a8:
    return 0x804;
  case 0x3b5:
    return 0x412;
  case 0x3b6:
    return 0x404;
  }
}


/* ==== FUN_0040aa90 @ 0040aa90 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040aa90(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00412850;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_00412954 = 0;
  _DAT_00412958 = 0;
  _DAT_00412960 = 0;
  _DAT_00412964 = 0;
  _DAT_00412968 = 0;
  return;
}


/* ==== __initmbctable @ 0040aac0 ==== */

int __initmbctable(void)

{
  int iVar1;
  
  iVar1 = _setmbcp(-3);
  return iVar1;
}


/* ==== __global_unwind2 @ 0040aad0 ==== */

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x40aae8,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


/* ==== __local_unwind2 @ 0040ab12 ==== */

/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_0040aaf0;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_0040aba6();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}


/* ==== FUN_0040aba6 @ 0040aba6 ==== */

void FUN_0040aba6(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_00411730 = *(undefined4 *)(unaff_EBP + 8);
  DAT_0041172c = in_EAX;
  DAT_00411734 = unaff_EBP;
  return;
}


/* ==== FUN_0040ac85 @ 0040ac85 ==== */

void FUN_0040ac85(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* ==== _FF_MSGBANNER @ 0040aca0 ==== */

void _FF_MSGBANNER(void)

{
  if ((DAT_004126ec == 1) || ((DAT_004126ec == 0 && (DAT_0040f554 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_00412970 != (code *)0x0) {
      (*DAT_00412970)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}


/* ==== _NMSG_WRITE @ 0040ace0 ==== */

void __cdecl _NMSG_WRITE(int rterrnum)

{
  char cVar1;
  int *piVar2;
  DWORD DVar3;
  HANDLE hFile;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  CHAR *pCVar10;
  char *pcVar11;
  DWORD local_1a8;
  char local_1a4 [100];
  char acStack_140 [60];
  CHAR local_104 [260];
  
  piVar2 = &DAT_00411738;
  iVar8 = 0;
  do {
    if (rterrnum == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar8 = iVar8 + 1;
  } while (piVar2 < &DAT_004117c8);
  if (rterrnum == (&DAT_00411738)[iVar8 * 2]) {
    if ((DAT_004126ec == 1) || ((DAT_004126ec == 0 && (DAT_0040f554 == 1)))) {
      if ((__pioinfo == 0) || (hFile = *(HANDLE *)(__pioinfo + 0x10), hFile == (HANDLE)0xffffffff))
      {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar7 = *(char **)(iVar8 * 8 + 0x41173c);
      uVar5 = 0xffffffff;
      pcVar9 = pcVar7;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      WriteFile(hFile,pcVar7,~uVar5 - 1,&local_1a8,(LPOVERLAPPED)0x0);
    }
    else if (rterrnum != 0xfc) {
      DVar3 = GetModuleFileNameA((HMODULE)0x0,local_104,0x104);
      if (DVar3 == 0) {
        pcVar7 = "<program name unknown>";
        pCVar10 = local_104;
        for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
          *(undefined4 *)pCVar10 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pCVar10 = pCVar10 + 4;
        }
        *(undefined2 *)pCVar10 = *(undefined2 *)pcVar7;
        pCVar10[2] = pcVar7[2];
      }
      uVar5 = 0xffffffff;
      pcVar7 = local_104;
      pcVar9 = local_104;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      if (0x3c < ~uVar5) {
        uVar5 = 0xffffffff;
        pcVar7 = local_104;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        pcVar7 = acStack_140 + ~uVar5;
        strncpy(pcVar7,"...",3);
      }
      pcVar9 = "Runtime Error!\n\nProgram: ";
      pcVar11 = local_1a4;
      for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      *(undefined2 *)pcVar11 = *(undefined2 *)pcVar9;
      uVar5 = 0xffffffff;
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar4 = -1;
      pcVar7 = local_1a4;
      do {
        pcVar11 = pcVar7;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar11 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar11;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = pcVar11 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar7 = "\n\n";
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar4 = -1;
      pcVar7 = local_1a4;
      do {
        pcVar11 = pcVar7;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar11 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar11;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = pcVar11 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar7 = *(char **)(iVar8 * 8 + 0x41173c);
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar8 = -1;
      pcVar7 = local_1a4;
      do {
        pcVar11 = pcVar7;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar11 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar11;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = pcVar11 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      __crtMessageBoxA(local_1a4,"Microsoft Visual C++ Runtime Library",0x12010);
      return;
    }
  }
  return;
}


/* ==== _dosmaperr @ 0040aec0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl _dosmaperr(ulong oserrno)

{
  undefined **ppuVar1;
  int iVar2;
  
  _doserrno = oserrno;
  iVar2 = 0;
  ppuVar1 = (undefined **)&DAT_004117c8;
  do {
    if ((undefined *)oserrno == *ppuVar1) {
      _errno = *(undefined4 *)(iVar2 * 8 + 0x4117cc);
      return;
    }
    ppuVar1 = ppuVar1 + 2;
    iVar2 = iVar2 + 1;
  } while (ppuVar1 < &_cfltcvt_tab);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    _errno = 0xd;
    return;
  }
  if ((oserrno < 0xbc) || (_errno = 8, 0xca < oserrno)) {
    _errno = 0x16;
  }
  return;
}


/* ==== _alloc_osfhnd @ 0040af30 ==== */

int _alloc_osfhnd(void)

{
  undefined4 *puVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = -1;
  iVar5 = 0;
  iVar6 = 0;
  piVar3 = &__pioinfo;
  do {
    puVar2 = (undefined4 *)*piVar3;
    if (puVar2 == (undefined4 *)0x0) {
      malloc(0x100);
      if (extraout_EAX != (undefined4 *)0x0) {
        _nhandle = _nhandle + 0x20;
        (&__pioinfo)[iVar5] = extraout_EAX;
        puVar2 = extraout_EAX;
        if (extraout_EAX < extraout_EAX + 0x40) {
          do {
            *(undefined1 *)(puVar2 + 1) = 0;
            *puVar2 = 0xffffffff;
            *(undefined1 *)((int)puVar2 + 5) = 10;
            puVar2 = puVar2 + 2;
          } while (puVar2 < (undefined4 *)((&__pioinfo)[iVar5] + 0x100));
        }
        iVar4 = iVar5 << 5;
      }
      return iVar4;
    }
    puVar1 = puVar2 + 0x40;
    for (; puVar2 < puVar1; puVar2 = puVar2 + 2) {
      if ((*(byte *)(puVar2 + 1) & 1) == 0) {
        *puVar2 = 0xffffffff;
        iVar4 = ((int)puVar2 - *piVar3 >> 3) + iVar6;
        break;
      }
    }
    if (iVar4 != -1) {
      return iVar4;
    }
    piVar3 = piVar3 + 1;
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + 0x20;
    if (0x412a9f < (int)piVar3) {
      return -1;
    }
  } while( true );
}


/* ==== _set_osfhnd @ 0040aff0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _set_osfhnd(int fh,long value)

{
  int iVar1;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (*(int *)((&__pioinfo)[fh >> 5] + iVar1) == -1) {
      if (DAT_0040f554 == 1) {
        if (fh == 0) {
          SetStdHandle(0xfffffff6,(HANDLE)value);
        }
        else {
          if (fh == 1) {
            SetStdHandle(0xfffffff5,(HANDLE)value);
            *(long *)(__pioinfo + 8) = value;
            return 0;
          }
          if (fh == 2) {
            SetStdHandle(0xfffffff4,(HANDLE)value);
            *(long *)(__pioinfo + 0x10) = value;
            return 0;
          }
        }
      }
      *(long *)((&__pioinfo)[fh >> 5] + iVar1) = value;
      return 0;
    }
  }
  _errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _free_osfhnd @ 0040b0a0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _free_osfhnd(int fh)

{
  int iVar1;
  DWORD nStdHandle;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar1) & 1) != 0) &&
       (*(int *)((&__pioinfo)[fh >> 5] + iVar1) != -1)) {
      if (DAT_0040f554 == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_0040b10a;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0040b10a:
      *(undefined4 *)((&__pioinfo)[fh >> 5] + iVar1) = 0xffffffff;
      return 0;
    }
  }
  _errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _get_osfhandle @ 0040b140 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long __cdecl _get_osfhandle(int fh)

{
  if (((uint)fh < _nhandle) && ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 1) != 0))
  {
    return *(long *)((&__pioinfo)[fh >> 5] + (fh & 0x1fU) * 8);
  }
  _errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _write @ 0040b1f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _write(int fh,void *buf,uint cnt)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  char *pcVar4;
  BOOL BVar5;
  int iVar6;
  char *pcVar7;
  DWORD local_41c;
  ulong local_414;
  DWORD local_410;
  int local_40c;
  int *local_408;
  char local_404 [1028];
  
  if ((uint)fh < _nhandle) {
    piVar1 = &__pioinfo + (fh >> 5);
    iVar6 = (fh & 0x1fU) * 8;
    bVar2 = *(byte *)(iVar6 + 4 + (&__pioinfo)[fh >> 5]);
    if ((bVar2 & 1) != 0) {
      local_41c = 0;
      local_40c = 0;
      if (cnt == 0) {
        return 0;
      }
      local_408 = piVar1;
      if ((bVar2 & 0x20) != 0) {
        _lseek(fh,0,2);
      }
      if ((*(byte *)((undefined4 *)(*piVar1 + iVar6) + 1) & 0x80) == 0) {
        BVar5 = WriteFile(*(HANDLE *)(*piVar1 + iVar6),buf,cnt,&local_410,(LPOVERLAPPED)0x0);
        if (BVar5 == 0) {
          local_414 = GetLastError();
        }
        else {
          local_41c = local_410;
          local_414 = 0;
        }
      }
      else {
        local_414 = 0;
        pcVar7 = buf;
        if (cnt != 0) {
          do {
            pcVar4 = local_404;
            do {
              if (cnt <= (uint)((int)pcVar7 - (int)buf)) break;
              cVar3 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              if (cVar3 == '\n') {
                *pcVar4 = '\r';
                local_40c = local_40c + 1;
                pcVar4 = pcVar4 + 1;
              }
              *pcVar4 = cVar3;
              pcVar4 = pcVar4 + 1;
            } while ((int)pcVar4 - (int)local_404 < 0x400);
            BVar5 = WriteFile(*(HANDLE *)(iVar6 + *local_408),local_404,(int)pcVar4 - (int)local_404
                              ,&local_410,(LPOVERLAPPED)0x0);
            if (BVar5 == 0) {
              local_414 = GetLastError();
              break;
            }
            local_41c = local_41c + local_410;
            if (((int)local_410 < (int)pcVar4 - (int)local_404) ||
               (cnt <= (uint)((int)pcVar7 - (int)buf))) break;
          } while( true );
        }
      }
      if (local_41c != 0) {
        return local_41c - local_40c;
      }
      if (local_414 == 0) {
        if (((*(byte *)(iVar6 + 4 + *local_408) & 0x40) != 0) && (*(char *)buf == '\x1a')) {
          return 0;
        }
        _errno = 0x1c;
        _doserrno = 0;
        return -1;
      }
      if (local_414 == 5) {
        _doserrno = local_414;
        _errno = 9;
        return -1;
      }
      _dosmaperr(local_414);
      return -1;
    }
  }
  _errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== mbtowc @ 0040b410 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl mbtowc(ushort *pwc,char *s,uint n)

{
  byte bVar1;
  int iVar2;
  
  if ((s != (char *)0x0) && (n != 0)) {
    bVar1 = *s;
    if (bVar1 != 0) {
      if (DAT_00412710 == 0) {
        if (pwc == (ushort *)0x0) {
          return 1;
        }
        *pwc = (ushort)bVar1;
        return 1;
      }
      if ((_pctype[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(DAT_00412720,9,s,1,(LPWSTR)pwc,(uint)(pwc != (ushort *)0x0));
        if (iVar2 != 0) {
          return 1;
        }
        _errno = 0x2a;
        return -1;
      }
      if (((1 < (int)__mb_cur_max) && ((int)__mb_cur_max <= (int)n)) &&
         (iVar2 = MultiByteToWideChar(DAT_00412720,9,s,__mb_cur_max,(LPWSTR)pwc,
                                      (uint)(pwc != (ushort *)0x0)), iVar2 != 0)) {
        return __mb_cur_max;
      }
      if (n < __mb_cur_max) {
        _errno = 0x2a;
        return -1;
      }
      if (s[1] != '\0') {
        return __mb_cur_max;
      }
      _errno = 0x2a;
      return -1;
    }
    if (pwc != (ushort *)0x0) {
      *pwc = 0;
      return 0;
    }
  }
  return 0;
}


/* ==== isspace @ 0040b510 ==== */

int __cdecl isspace(int c)

{
  int iVar1;
  
  if (1 < __mb_cur_max) {
    iVar1 = _isctype(c,8);
    return iVar1;
  }
  return (byte)_pctype[c * 2] & 8;
}


/* ==== __allmul @ 0040b540 ==== */

/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio */

longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}


/* ==== __allshl @ 0040b580 ==== */

/* Library Function - Single Match
    __allshl
   
   Library: Visual Studio */

longlong __fastcall __allshl(byte param_1,int param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 << (param_1 & 0x1f) | in_EAX >> 0x20 - (param_1 & 0x1f),
                    in_EAX << (param_1 & 0x1f));
  }
  return (ulonglong)(in_EAX << (param_1 & 0x1f)) << 0x20;
}


/* ==== strncpy @ 0040b5a0 ==== */

/* Library Function - Single Match
    _strncpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strncpy(char *dst,char *src,uint n)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  
  cVar3 = (char)dst;
  if (n == 0) {
    return cVar3;
  }
  if (((uint)src & 3) != 0) {
    while( true ) {
      uVar5 = *(uint *)src;
      src = (char *)((int)src + 1);
      *dst = (char)uVar5;
      dst = (char *)((int)dst + 1);
      n = n - 1;
      if (n == 0) {
        return cVar3;
      }
      if ((char)uVar5 == '\0') break;
      if (((uint)src & 3) == 0) {
        uVar5 = n >> 2;
        goto joined_r0x0040b5de;
      }
    }
    do {
      if (((uint)dst & 3) == 0) {
        uVar5 = n >> 2;
        cVar4 = '\0';
        if (uVar5 == 0) goto LAB_0040b61b;
        goto LAB_0040b689;
      }
      *dst = '\0';
      dst = (char *)((int)dst + 1);
      n = n - 1;
    } while (n != 0);
    return cVar3;
  }
  uVar5 = n >> 2;
  if (uVar5 != 0) {
    do {
      uVar1 = *(uint *)src;
      uVar2 = *(uint *)src;
      src = (char *)((int)src + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *(uint *)dst = 0;
joined_r0x0040b685:
          while( true ) {
            uVar5 = uVar5 - 1;
            dst = (char *)((int)dst + 4);
            if (uVar5 == 0) break;
LAB_0040b689:
            *(uint *)dst = 0;
          }
          cVar4 = '\0';
          n = n & 3;
          if (n != 0) goto LAB_0040b61b;
          return cVar3;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *(uint *)dst = uVar2 & 0xff;
          goto joined_r0x0040b685;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *(uint *)dst = uVar2 & 0xffff;
          goto joined_r0x0040b685;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *(uint *)dst = uVar2;
          goto joined_r0x0040b685;
        }
      }
      *(uint *)dst = uVar2;
      dst = (char *)((int)dst + 4);
      uVar5 = uVar5 - 1;
joined_r0x0040b5de:
    } while (uVar5 != 0);
    n = n & 3;
    if (n == 0) {
      return cVar3;
    }
  }
  do {
    cVar4 = (char)*(uint *)src;
    src = (char *)((int)src + 1);
    *dst = cVar4;
    dst = (char *)((int)dst + 1);
    if (cVar4 == '\0') {
      while (n = n - 1, n != 0) {
LAB_0040b61b:
        *dst = cVar4;
        dst = (char *)((int)dst + 1);
      }
      return cVar3;
    }
    n = n - 1;
  } while (n != 0);
  return cVar3;
}


/* ==== FUN_0040b6a0 @ 0040b6a0 ==== */

undefined4 * __cdecl FUN_0040b6a0(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    puVar3 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar4 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = param_3 >> 2;
      uVar2 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return param_1;
        case 2:
          goto switchD_0040b857_caseD_2;
        case 3:
          goto switchD_0040b857_caseD_3;
        }
        goto switchD_0040b857_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_0040b857_caseD_0;
      case 1:
        goto switchD_0040b857_caseD_1;
      case 2:
        goto switchD_0040b857_caseD_2;
      case 3:
        goto switchD_0040b857_caseD_3;
      default:
        uVar1 = param_3 - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_0040b857_caseD_2;
            case 3:
              goto switchD_0040b857_caseD_3;
            }
            goto switchD_0040b857_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_0040b857_caseD_2;
            case 3:
              goto switchD_0040b857_caseD_3;
            }
            goto switchD_0040b857_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return param_1;
            case 2:
              goto switchD_0040b857_caseD_2;
            case 3:
              goto switchD_0040b857_caseD_3;
            }
            goto switchD_0040b857_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_0040b857_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return param_1;
    case 2:
switchD_0040b857_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return param_1;
    case 3:
switchD_0040b857_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return param_1;
    }
switchD_0040b857_caseD_0:
    return param_1;
  }
  puVar3 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    uVar2 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return param_1;
      case 2:
        goto switchD_0040b6d5_caseD_2;
      case 3:
        goto switchD_0040b6d5_caseD_3;
      }
      goto switchD_0040b6d5_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_0040b6d5_caseD_0;
    case 1:
      goto switchD_0040b6d5_caseD_1;
    case 2:
      goto switchD_0040b6d5_caseD_2;
    case 3:
      goto switchD_0040b6d5_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar3 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_0040b6d5_caseD_2;
          case 3:
            goto switchD_0040b6d5_caseD_3;
          }
          goto switchD_0040b6d5_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar3 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_0040b6d5_caseD_2;
          case 3:
            goto switchD_0040b6d5_caseD_3;
          }
          goto switchD_0040b6d5_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return param_1;
          case 2:
            goto switchD_0040b6d5_caseD_2;
          case 3:
            goto switchD_0040b6d5_caseD_3;
          }
          goto switchD_0040b6d5_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar3[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar3[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar3[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar3[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar3[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar3[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_0040b6d5_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_0040b6d5_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_0040b6d5_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_0040b6d5_caseD_0:
  return param_1;
}


/* ==== _isatty @ 0040b9e0 ==== */

int __cdecl _isatty(int fh)

{
  if (_nhandle <= (uint)fh) {
    return 0;
  }
  return *(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 0x40;
}


/* ==== wctomb @ 0040ba10 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl wctomb(char *s,ushort wc)

{
  char *lpMultiByteStr;
  int iVar1;
  
  lpMultiByteStr = s;
  if (s == (char *)0x0) {
    return 0;
  }
  if (DAT_00412710 == 0) {
    if (wc < 0x100) {
      *s = (char)wc;
      return 1;
    }
  }
  else {
    s = (char *)0x0;
    iVar1 = WideCharToMultiByte(DAT_00412720,0x220,(LPCWSTR)&wc,1,lpMultiByteStr,__mb_cur_max,
                                (LPCSTR)0x0,(LPBOOL)&s);
    if ((iVar1 != 0) && (s == (char *)0x0)) {
      return iVar1;
    }
  }
  _errno = 0x2a;
  return -1;
}


/* ==== __aulldiv @ 0040ba90 ==== */

/* Library Function - Single Match
    __aulldiv
   
   Library: Visual Studio */

undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}


/* ==== __aullrem @ 0040bb00 ==== */

/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio */

undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = param_1;
  uVar9 = param_4;
  uVar10 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar10 >> 1;
      uVar4 = (uint)(CONCAT14((uVar10 & 1) != 0,uVar4) >> 1);
      uVar9 = uVar5;
      uVar10 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}


/* ==== _sopen @ 0040bb80 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _sopen(char *path,int oflag,int shflag,int pmode)

{
  uint uVar1;
  HANDLE hFile;
  long lVar2;
  int iVar3;
  DWORD DVar4;
  DWORD dwCreationDisposition;
  DWORD dwFlagsAndAttributes;
  int iVar5;
  bool bVar6;
  byte local_11;
  uint local_10;
  _SECURITY_ATTRIBUTES local_c;
  
  bVar6 = (oflag & 0x80U) == 0;
  local_c.nLength = 0xc;
  local_c.lpSecurityDescriptor = (LPVOID)0x0;
  if (bVar6) {
    local_11 = 0;
  }
  else {
    local_11 = 0x10;
  }
  local_c.bInheritHandle = (BOOL)bVar6;
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_00412984 != 0x8000)))) {
    local_11 = local_11 | 0x80;
  }
  uVar1 = oflag & 3;
  if (uVar1 == 0) {
    local_10 = 0x80000000;
  }
  else if (uVar1 == 1) {
    local_10 = 0x40000000;
  }
  else {
    if (uVar1 != 2) {
      _errno = 0x16;
      _doserrno = 0;
      return -1;
    }
    local_10 = 0xc0000000;
  }
  switch(shflag) {
  case 0x10:
    DVar4 = 0;
    break;
  default:
    goto switchD_0040bc18_caseD_11;
  case 0x20:
    DVar4 = 1;
    break;
  case 0x30:
    DVar4 = 2;
    break;
  case 0x40:
    DVar4 = 3;
  }
  uVar1 = oflag & 0x700;
  if (uVar1 < 0x101) {
    if (uVar1 == 0x100) {
      dwCreationDisposition = 4;
      goto LAB_0040bcab;
    }
    if (uVar1 != 0) {
      _errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_0040bc86:
    dwCreationDisposition = 3;
    goto LAB_0040bcab;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      dwCreationDisposition = 2;
      goto LAB_0040bcab;
    }
    if (uVar1 != 0x200) {
      _errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_0040bca6:
    dwCreationDisposition = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_0040bc18_caseD_11:
          _doserrno = 0;
          _errno = 0x16;
          return -1;
        }
        goto LAB_0040bc86;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_0040bca6;
      if (uVar1 != 0x700) {
        _errno = 0x16;
        _doserrno = 0;
        return -1;
      }
    }
    dwCreationDisposition = 1;
  }
LAB_0040bcab:
  dwFlagsAndAttributes = 0x80;
  if (((oflag & 0x100U) != 0) && (((byte)pmode & ~(byte)DAT_00412688 & 0x80) == 0)) {
    dwFlagsAndAttributes = 1;
  }
  if ((oflag & 0x40U) != 0) {
    dwFlagsAndAttributes = dwFlagsAndAttributes | 0x4000000;
    local_10 = local_10 | 0x10000;
  }
  if ((oflag & 0x1000U) != 0) {
    dwFlagsAndAttributes = dwFlagsAndAttributes | 0x100;
  }
  if ((oflag & 0x20U) == 0) {
    if ((oflag & 0x10U) != 0) {
      dwFlagsAndAttributes = dwFlagsAndAttributes | 0x10000000;
    }
  }
  else {
    dwFlagsAndAttributes = dwFlagsAndAttributes | 0x8000000;
  }
  uVar1 = _alloc_osfhnd();
  if (uVar1 == 0xffffffff) {
    _errno = 0x18;
    _doserrno = 0;
    return -1;
  }
  hFile = CreateFileA(path,local_10,DVar4,&local_c,dwCreationDisposition,dwFlagsAndAttributes,
                      (HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    DVar4 = GetLastError();
    _dosmaperr(DVar4);
    return -1;
  }
  DVar4 = GetFileType(hFile);
  if (DVar4 != 0) {
    if (DVar4 == 2) {
      local_11 = local_11 | 0x40;
    }
    else if (DVar4 == 3) {
      local_11 = local_11 | 8;
    }
    _set_osfhnd(uVar1,(long)hFile);
    iVar5 = (uVar1 & 0x1f) * 8;
    *(byte *)(iVar5 + 4 + (&__pioinfo)[(int)uVar1 >> 5]) = local_11 | 1;
    if ((((local_11 & 0x48) == 0) && ((local_11 & 0x80) != 0)) && ((oflag & 2U) != 0)) {
      lVar2 = _lseek(uVar1,-1,2);
      if (lVar2 == -1) {
        if (_doserrno != 0x83) {
          _close(uVar1);
          return -1;
        }
      }
      else {
        shflag = shflag & 0xffffff00;
        iVar3 = _read(uVar1,&shflag,1);
        if (((iVar3 == 0) && ((char)shflag == '\x1a')) &&
           (iVar3 = _chsize(uVar1,lVar2), iVar3 == -1)) {
          _close(uVar1);
          return -1;
        }
        lVar2 = _lseek(uVar1,0,0);
        if (lVar2 == -1) {
          _close(uVar1);
          return -1;
        }
      }
    }
    if (((local_11 & 0x48) == 0) && ((oflag & 8U) != 0)) {
      *(byte *)(iVar5 + 4 + (&__pioinfo)[(int)uVar1 >> 5]) =
           *(byte *)(iVar5 + 4 + (&__pioinfo)[(int)uVar1 >> 5]) | 0x20;
    }
    return uVar1;
  }
  CloseHandle(hFile);
  DVar4 = GetLastError();
  _dosmaperr(DVar4);
  return -1;
}


/* ==== __crtMessageBoxA @ 0040bf40 ==== */

int __cdecl __crtMessageBoxA(char *text,char *caption,uint type)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_00412978 != (FARPROC)0x0) {
LAB_0040bf90:
    if (DAT_0041297c != (FARPROC)0x0) {
      iVar1 = (*DAT_0041297c)();
    }
    if ((iVar1 != 0) && (DAT_00412980 != (FARPROC)0x0)) {
      iVar1 = (*DAT_00412980)(iVar1);
    }
    iVar1 = (*DAT_00412978)(iVar1,text,caption,type);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_00412978 = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_00412978 != (FARPROC)0x0) {
      DAT_0041297c = GetProcAddress(hModule,"GetActiveWindow");
      DAT_00412980 = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_0040bf90;
    }
  }
  return 0;
}


/* ==== _fptrap @ 0040bfd0 ==== */

void _fptrap(void)

{
  _amsg_exit(2);
  return;
}


/* ==== _chsize @ 0040bfe0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int _chsize(int fh,long size)

{
  long pos;
  long lVar1;
  uint cnt;
  int iVar2;
  HANDLE hFile;
  BOOL BVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint in_stack_00001008;
  int in_stack_0000100c;
  
  FUN_0040c1e0();
  iVar5 = 0;
  if ((in_stack_00001008 < _nhandle) &&
     ((*(byte *)((&__pioinfo)[(int)in_stack_00001008 >> 5] + 4 + (in_stack_00001008 & 0x1f) * 8) & 1
      ) != 0)) {
    pos = _lseek(in_stack_00001008,0,1);
    if ((pos != -1) && (lVar1 = _lseek(in_stack_00001008,0,2), lVar1 != -1)) {
      uVar6 = in_stack_0000100c - lVar1;
      if ((int)uVar6 < 1) {
        if ((int)uVar6 < 0) {
          _lseek(in_stack_00001008,in_stack_0000100c,0);
          hFile = (HANDLE)_get_osfhandle(in_stack_00001008);
          BVar3 = SetEndOfFile(hFile);
          iVar5 = (BVar3 != 0) - 1;
          if (iVar5 == -1) {
            _errno = 0xd;
            _doserrno = GetLastError();
          }
        }
        _lseek(in_stack_00001008,pos,0);
        return iVar5;
      }
      puVar7 = (undefined4 *)register0x00000010;
      for (iVar4 = 0x400; puVar7 = puVar7 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = 0;
      }
      iVar4 = FUN_0040c160(in_stack_00001008,0x8000);
      while( true ) {
        cnt = 0x1000;
        if ((int)uVar6 < 0x1000) {
          cnt = uVar6;
        }
        iVar2 = _write(in_stack_00001008,&fh,cnt);
        if (iVar2 == -1) break;
        uVar6 = uVar6 - iVar2;
        if ((int)uVar6 < 1) {
LAB_0040c0c1:
          FUN_0040c160(in_stack_00001008,iVar4);
          _lseek(in_stack_00001008,pos,0);
          return iVar5;
        }
      }
      if (_doserrno == 5) {
        _errno = 0xd;
      }
      iVar5 = -1;
      goto LAB_0040c0c1;
    }
  }
  else {
    _errno = 9;
  }
  return -1;
}


/* ==== FUN_0040c160 @ 0040c160 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_0040c160(uint param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  if (param_1 < _nhandle) {
    bVar1 = *(byte *)((&__pioinfo)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8);
    if ((bVar1 & 1) != 0) {
      if (param_2 == 0x8000) {
        bVar2 = bVar1 & 0x7f;
      }
      else {
        if (param_2 != 0x4000) {
          _errno = 0x16;
          return -1;
        }
        bVar2 = bVar1 | 0x80;
      }
      *(byte *)((&__pioinfo)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) = bVar2;
      return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
    }
  }
  _errno = 9;
  return -1;
}


/* ==== FUN_0040c1e0 @ 0040c1e0 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_0040c1e0(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}


/* ==== RtlUnwind @ 0040c210 ==== */

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x0040c210. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


