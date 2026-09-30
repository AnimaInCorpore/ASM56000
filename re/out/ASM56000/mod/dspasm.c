/* dspasm: 33 functions from ASM56000 */

/* ==== main @ 00401190 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl main(int argc,char **argv,char **envp)

{
  char cVar1;
  char *s;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  
  signal(2,FUN_00405db4);
  signal(0xb,FUN_00405db4);
  signal(8,FUN_00405db4);
  s = FUN_00439bd4(*argv);
  cVar1 = strrchr(s,0x2e);
  if ((undefined1 *)CONCAT31(extraout_var,cVar1) != (undefined1 *)0x0) {
    *(undefined1 *)CONCAT31(extraout_var,cVar1) = 0;
  }
  cVar1 = getenv(s_DSPASMOPT_0044fa58);
  if (CONCAT31(extraout_var_00,cVar1) == 0) {
    iVar2 = FUN_00403aa7('f',argc,(int *)argv);
    if (iVar2 == 0) goto LAB_0040122b;
  }
  argc = FUN_00402dfa(argc,(int *)&argv);
LAB_0040122b:
  iVar2 = FUN_00403aa7('a',argc,(int *)argv);
  DAT_0044f790 = '\x01' - (iVar2 != 0);
  DAT_0044f794 = DAT_0044f790;
  DAT_0044f798 = DAT_0044f790;
  iVar2 = FUN_00403aa7('c',argc,(int *)argv);
  DAT_0045ea98 = iVar2 != 0;
  DAT_0045ea9c = DAT_0045ea98;
  iVar2 = FUN_00403aa7('q',argc,(int *)argv);
  DAT_0045eb54 = iVar2 != 0;
  iVar2 = FUN_00403aa7('j',argc,(int *)argv);
  DAT_0045eb34 = iVar2 != 0;
  iVar2 = FUN_00403b78('e',argc,(int *)argv);
  if (iVar2 != 0) {
    FUN_00403c50((int)argv,iVar2);
  }
  if ((DAT_0045ea98 != '\0') && (DAT_0044f790 == '\0')) {
    FUN_004137f6(s_Options_for_both_absolute_and_C_m_00450c20);
    DAT_0045ea9c = 0;
    DAT_0045ea98 = '\0';
  }
  PTR_s_asm56000_0044e084 = s;
  sscanf(s_6_3_0_0044f9b8,s__ld__ld__ld_00450c60,&DAT_0045fcb0,&DAT_0045fcb4,&DAT_0045fcb8);
  if ((DAT_0045ea98 == '\0') && (DAT_0045eb54 == '\0')) {
    fprintf(PTR_DAT_0044f9a4,s_Motorola__s__s_Version__s__s_00450c6c,s_DSP56000_0044e068,
            s_Assembler_0044f9a8,s_6_3_0_0044f9b8,s_Copyright_Motorola__Inc__1987_19_0044f9c0);
  }
  if ((DAT_0045ea78 == '\0') && (argc < 2)) {
    FUN_00401437();
  }
  _DAT_0045f834 = FUN_00405eea(&DAT_0045f838,&DAT_0045f848);
  DAT_0045fcac = &DAT_0045a470;
  PTR_DAT_0044f808 = (undefined *)FUN_00402a99(argc,(int)argv);
  if (DAT_0045ea98 == '\0') {
    FUN_00401c97(argc,argv);
  }
  else {
    FUN_004015e3(argc,argv);
  }
  if (DAT_0045eb18 != '\0') {
    DAT_0045eb84 = DAT_0045eb84 + DAT_0045eb88;
  }
  exit(DAT_0045eb84);
  return DAT_0045eb84;
}


/* ==== FUN_00401437 @ 00401437 ==== */

void FUN_00401437(void)

{
  if ((DAT_0045ea98 != '\0') || (DAT_0045eb54 != '\0')) {
    fprintf(PTR_DAT_0044f9a4,s_Motorola__s__s_Version__s__s_00450c8c,s_DSP56000_0044e068,
            s_Assembler_0044f9a8,s_6_3_0_0044f9b8,s_Copyright_Motorola__Inc__1987_19_0044f9c0);
  }
  fprintf(PTR_DAT_0044f9a4,s_Usage___s___a____b_<objfil>______00450cac,PTR_s_asm56000_0044e084);
  fprintf(PTR_DAT_0044f9a4,s_where__00450d74);
  fprintf(PTR_DAT_0044f9a4,s__a_absolute_mode__l_listing_file_00450d7c);
  fprintf(PTR_DAT_0044f9a4,s__b_object_file_<lstfil>_listing_f_00450db8);
  fprintf(PTR_DAT_0044f9a4,s_<objfil>_object_file_name__m_mac_00450e00);
  fprintf(PTR_DAT_0044f9a4,s__d_define_symbol_<mpath>_library_00450e3c);
  fprintf(PTR_DAT_0044f9a4,s_<symbol>_symbol_name__o_assemble_00450e84);
  fprintf(PTR_DAT_0044f9a4,s_<string>_value_of_symbol_<opt>_o_00450ec4);
  fprintf(PTR_DAT_0044f9a4,s__ea_append_to_error_file__p_proc_00450f08);
  fprintf(PTR_DAT_0044f9a4,s_<errfil>_error_file_name_<proc>_p_00450f48);
  fprintf(PTR_DAT_0044f9a4,s__ew_write_to_error_file__q_suppr_00450f94);
  fprintf(PTR_DAT_0044f9a4,s_<errfil>_error_file_name__r_supp_00450fd0);
  fprintf(PTR_DAT_0044f9a4,s__f_command_file_<rev>_revision_d_00451010);
  fprintf(PTR_DAT_0044f9a4,s_<argfil>_command_file_name__v_ve_00451058);
  fprintf(PTR_DAT_0044f9a4,s__g_debug_mode__z_strip_absolute_o_00451094);
  fprintf(PTR_DAT_0044f9a4,s__i_include_path_<srcfil>_assembl_004510d8);
  fprintf(PTR_DAT_0044f9a4,s__s_command_environment_variable__00451124,s_Assembler_0044f9a8,
          s_DSPASMOPT_0044fa58);
  exit(-1);
  return;
}


/* ==== FUN_004015e3 @ 004015e3 ==== */

void __cdecl FUN_004015e3(int param_1,undefined4 *param_2)

{
  int *extraout_EAX;
  uint *puVar1;
  int iVar2;
  undefined *extraout_EAX_00;
  bool bVar3;
  undefined *va0;
  undefined1 local_208 [512];
  uint *local_8;
  
  DAT_0045f908 = param_2;
  DAT_0045f904 = param_1;
  do {
    FUN_00401b35();
    FUN_004197d0();
    FUN_0043ce03();
    FUN_004059f6();
    FUN_004047e0();
    DAT_0045ea34 = DAT_0045ea9c;
    FUN_00402a0d();
    if (DAT_0045eb4c != '\0') {
      fprintf(PTR_DAT_0044f9a4,s__s__Beginning_pass_1_0045114c,PTR_s_asm56000_0044e084);
    }
    if (DAT_0045ea78 == '\0') {
      strcpy(local_208,(char *)*DAT_0045f908);
    }
    FUN_00401a16((uint *)local_208);
    if (DAT_0045eb4c != '\0') {
      fprintf(PTR_DAT_0044f9a4,s__s__Opening_source_file__s_00451164,PTR_s_asm56000_0044e084,
              local_208);
    }
    FUN_0043b8f1(DAT_0045f900,0);
    FUN_00402cde((uint *)local_208);
    local_208[0] = '\0';
    fgets(&DAT_0045f220,0x200,DAT_0045f900);
    rewind(DAT_0045f900);
    FUN_004197d0();
    FUN_0043ce03();
    if (DAT_0045eb34 != '\0') {
      FUN_00434430();
    }
    FUN_00404ef2();
    DAT_0045ea34 = DAT_0045ea9c;
    FUN_00402a0d();
    strcpy(local_208,(char *)*DAT_0045f908);
    FUN_00401a16((uint *)local_208);
    FUN_00402cde((uint *)local_208);
    local_8 = (uint *)FUN_00439bd4(local_208);
    if (local_8 != (uint *)0x0) {
      FUN_00401ad4((char *)local_8);
    }
    if (DAT_0045ea9c == '\0') {
      if (DAT_0045f85c == (char *)0x0) {
        puVar1 = FUN_00439760(local_8,&DAT_00451180,0);
        strcpy(&DAT_0045f220,(char *)puVar1);
        FUN_004398b5((undefined *)puVar1);
      }
      else {
        strcpy(&DAT_0045f220,DAT_0045f85c);
        DAT_0045f85c = (char *)0x0;
      }
      fopen(&DAT_0045f220,&DAT_00451188);
      DAT_0045fcac = extraout_EAX;
      if (extraout_EAX == (int *)0x0) {
        FUN_004137c6(s_Cannot_open_listing_file_0045118c,&DAT_0045f220);
      }
      FUN_00405f6a(&DAT_0045f220,&DAT_004511b0,&DAT_004511a8);
      FUN_0043b8f1(DAT_0045fcac,1);
    }
    strcpy(&DAT_0045f220,(char *)local_8);
    if (DAT_0045f950 == '\0') {
      strcpy(&DAT_0045f950,(char *)local_8);
      FUN_0043b7aa(&DAT_0045f950);
    }
    if (DAT_0045f854 == (char *)0x0) {
      if (DAT_0044f790 == '\0') {
        va0 = &DAT_0044faa8;
      }
      else {
        va0 = &DAT_0044faa0;
      }
      puVar1 = FUN_00439760(local_8,va0,0);
      strcpy(&DAT_0045f220,(char *)puVar1);
      FUN_004398b5((undefined *)puVar1);
    }
    else {
      strcpy(&DAT_0045f220,DAT_0045f854);
    }
    iVar2 = strcmp(&DAT_0045f220,&DAT_004511b8);
    if (iVar2 == 0) {
      DAT_0045fca8 = &DAT_0045a470;
    }
    else {
      fopen(&DAT_0045f220,&DAT_004511bc);
      DAT_0045fca8 = extraout_EAX_00;
      if (extraout_EAX_00 == (undefined *)0x0) {
        FUN_004137c6(s_Cannot_open_object_file_004511c0,&DAT_0045f220);
      }
    }
    FUN_00405f6a(&DAT_0045f220,&DAT_004511e0,&DAT_004511d8);
    if (DAT_0045eb4c != '\0') {
      fprintf(PTR_DAT_0044f9a4,s__s__Beginning_pass_2_004511e8,PTR_s_asm56000_0044e084);
    }
    FUN_004197d0();
    FUN_00405b98(0);
    if (DAT_0045ea78 == '\0') {
      DAT_0044f958 = DAT_0044f958 + 1;
      bVar3 = DAT_0044f958 <= DAT_0045f904;
    }
    else {
      iVar2 = FUN_00402a03(&DAT_00465a88);
      bVar3 = iVar2 != 0;
    }
  } while (bVar3);
  return;
}


/* ==== FUN_00401a16 @ 00401a16 ==== */

void __cdecl FUN_00401a16(uint *param_1)

{
  int extraout_EAX;
  int iVar1;
  uint *name;
  int extraout_EAX_00;
  
  fopen((char *)param_1,&DAT_00451200);
  DAT_0045f900 = extraout_EAX;
  if (extraout_EAX == 0) {
    iVar1 = FUN_00401af9((char *)param_1,&DAT_00451204);
    if (iVar1 == 0) {
      name = FUN_00439760(param_1,&DAT_0045120c,0);
      fopen((char *)name,&DAT_00451214);
      DAT_0045f900 = extraout_EAX_00;
      if (extraout_EAX_00 == 0) {
        FUN_004137c6(s_Cannot_open_source_file_00451218,name);
      }
      else {
        strcpy((char *)param_1,(char *)name);
      }
      FUN_004398b5((undefined *)name);
    }
    else {
      FUN_004137c6(s_Cannot_open_source_file_00451230,param_1);
    }
  }
  return;
}


/* ==== FUN_00401ad4 @ 00401ad4 ==== */

void __cdecl FUN_00401ad4(char *param_1)

{
  char cVar1;
  undefined3 extraout_var;
  
  cVar1 = strrchr(param_1,0x2e);
  if ((undefined1 *)CONCAT31(extraout_var,cVar1) != (undefined1 *)0x0) {
    *(undefined1 *)CONCAT31(extraout_var,cVar1) = 0;
  }
  return;
}


/* ==== FUN_00401af9 @ 00401af9 ==== */

undefined4 __cdecl FUN_00401af9(char *param_1,char *param_2)

{
  char cVar1;
  undefined3 extraout_var;
  int iVar2;
  
  cVar1 = strrchr(param_1,0x2e);
  if (((char *)CONCAT31(extraout_var,cVar1) != (char *)0x0) &&
     (iVar2 = strcmp((char *)CONCAT31(extraout_var,cVar1),param_2), iVar2 == 0)) {
    return 1;
  }
  return 0;
}


/* ==== FUN_00401b35 @ 00401b35 ==== */

void FUN_00401b35(void)

{
  int *extraout_EAX;
  int iVar1;
  int *extraout_EAX_00;
  undefined *puVar2;
  undefined *va1;
  uint *puVar3;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  FUN_004040b4();
  FUN_0040201b();
  FUN_00401ffb();
  if (DAT_0045f904 == 0) {
    FUN_0041379a(s_Missing_source_filename_00451248);
  }
  puVar2 = (undefined *)0x401b76;
  FUN_00402a0d();
  if (DAT_0045eb4c != '\0') {
    puVar2 = PTR_s_asm56000_0044e084;
    fprintf(PTR_DAT_0044f9a4,s__s__Beginning_pre_pass_00451260,PTR_s_asm56000_0044e084);
  }
  if (DAT_0045eb4c != '\0') {
    fprintf(PTR_DAT_0044f9a4,s__s__Opening_source_file__s_00451278,PTR_s_asm56000_0044e084,puVar2);
  }
  puVar2 = &DAT_00451294;
  fopen(&DAT_00451294,&DAT_00451294);
  DAT_0045f900 = extraout_EAX;
  if (extraout_EAX == (int *)0x0) {
    va1 = &DAT_00451298;
    iVar1 = FUN_00401af9(&DAT_00451298,&DAT_00451298);
    local_8 = puVar2;
    if (iVar1 == 0) {
      FUN_00439760((uint *)0x0,&DAT_004512a0,0);
      puVar2 = &DAT_004512a8;
      fopen(&DAT_004512a8,&DAT_004512a8);
      DAT_0045f900 = extraout_EAX_00;
      if (extraout_EAX_00 == (int *)0x0) {
        FUN_004137c6(s_Cannot_open_source_file_004512ac,puVar2);
      }
    }
    else {
      FUN_004137c6(s_Cannot_open_source_file_004512c4,va1);
    }
  }
  puVar3 = (uint *)0x0;
  FUN_0043b8f1(DAT_0045f900,0);
  FUN_00402cde(puVar3);
  FUN_004398b5((undefined *)puVar3);
  if (local_8 != (undefined *)0x0) {
    FUN_004398b5(local_8);
  }
  return;
}


/* ==== FUN_00401c97 @ 00401c97 ==== */

void __cdecl FUN_00401c97(int param_1,undefined4 *param_2)

{
  char cVar1;
  int iVar2;
  int *extraout_EAX;
  uint uVar3;
  int *extraout_EAX_00;
  int *extraout_EAX_01;
  int *extraout_EAX_02;
  undefined3 extraout_var;
  char *src;
  undefined1 *puVar4;
  
  DAT_0045f908 = param_2;
  DAT_0045f904 = param_1;
  FUN_00401b35();
  FUN_004197d0();
  FUN_0043ce03();
  FUN_004059f6();
  FUN_004047e0();
  DAT_0045f908 = param_2;
  DAT_0045f904 = param_1;
  if (DAT_0045ea78 == '\0') {
    FUN_00402025();
    if (DAT_0045f904 == 0) {
      FUN_0041379a(s_Missing_source_filename_004512f4);
    }
  }
  else {
    FUN_004029fe();
    iVar2 = FUN_00402a03(&DAT_00465a88);
    if (iVar2 == 0) {
      FUN_0041379a(s_Missing_source_filename_004512dc);
    }
  }
  FUN_00402a0d();
  if (DAT_0045eb4c != '\0') {
    fprintf(PTR_DAT_0044f9a4,s__s__Beginning_pass_1_0045130c,PTR_s_asm56000_0044e084);
  }
  if (DAT_0045ea78 == '\0') {
    strcpy(&DAT_0045f220,(char *)*DAT_0045f908);
  }
  if (DAT_0045eb4c != '\0') {
    fprintf(PTR_DAT_0044f9a4,s__s__Opening_source_file__s_00451324,PTR_s_asm56000_0044e084,
            &DAT_0045f220);
  }
  fopen(&DAT_0045f220,&DAT_00451340);
  DAT_0045f900 = extraout_EAX;
  if ((extraout_EAX == (int *)0x0) &&
     ((uVar3 = FUN_00402bfa((uint *)&DAT_00451344), uVar3 == 0 ||
      (fopen(&DAT_0045f220,&DAT_0045134c), DAT_0045f900 = extraout_EAX_00,
      extraout_EAX_00 == (int *)0x0)))) {
    FUN_004137c6(s_Cannot_open_source_file_00451350,&DAT_0045f220);
  }
  FUN_0043b8f1(DAT_0045f900,0);
  FUN_00402cde((uint *)&DAT_0045f220);
  DAT_0045f220 = 0;
  fgets(&DAT_0045f220,0x200,DAT_0045f900);
  rewind(DAT_0045f900);
  FUN_004197d0();
  FUN_0043ce03();
  if (DAT_0045eb34 != '\0') {
    FUN_00434430();
  }
  FUN_00404ef2();
  DAT_0045f908 = param_2;
  DAT_0045f904 = param_1;
  if (DAT_0045ea78 == '\0') {
    FUN_00402025();
    strcpy(&DAT_0045f220,(char *)*DAT_0045f908);
  }
  else {
    FUN_004029fe();
    FUN_00402a03(&DAT_00465a88);
  }
  FUN_00402a0d();
  if (DAT_0045eb4c != '\0') {
    fprintf(PTR_DAT_0044f9a4,s__s__Beginning_pass_2_00451368,PTR_s_asm56000_0044e084);
  }
  if (DAT_0045eb4c != '\0') {
    fprintf(PTR_DAT_0044f9a4,s__s__Opening_source_file__s_00451380,PTR_s_asm56000_0044e084,
            &DAT_0045f220);
  }
  fopen(&DAT_0045f220,&DAT_0045139c);
  DAT_0045f900 = extraout_EAX_01;
  if ((extraout_EAX_01 == (int *)0x0) &&
     ((uVar3 = FUN_00402bfa((uint *)&DAT_004513a0), uVar3 == 0 ||
      (fopen(&DAT_0045f220,&DAT_004513a8), DAT_0045f900 = extraout_EAX_02,
      extraout_EAX_02 == (int *)0x0)))) {
    FUN_004137c6(s_Cannot_open_source_file_004513ac,&DAT_0045f220);
  }
  FUN_0043b8f1(DAT_0045f900,0);
  FUN_00402cde((uint *)&DAT_0045f220);
  if (DAT_0045fca8 != 0) {
    cVar1 = strrchr(&DAT_0045f220,0x2e);
    puVar4 = (undefined1 *)CONCAT31(extraout_var,cVar1);
    if (puVar4 != (undefined1 *)0x0) {
      *puVar4 = 0;
    }
    if (DAT_0045f950 == '\0') {
      src = FUN_00439bd4(&DAT_0045f220);
      strcpy(&DAT_0045f950,src);
      puVar4 = &DAT_0045f950;
      FUN_0043b7aa(&DAT_0045f950);
    }
    if (puVar4 != (undefined1 *)0x0) {
      *puVar4 = 0x2e;
    }
  }
  FUN_004197d0();
  FUN_00405b98(0);
  return;
}


/* ==== FUN_00401ffb @ 00401ffb ==== */

uint * FUN_00401ffb(void)

{
  uint *puVar1;
  
  puVar1 = FUN_00439760((uint *)*DAT_0045f908,0);
  return puVar1;
}


/* ==== FUN_0040201b @ 0040201b ==== */

void FUN_0040201b(void)

{
  FUN_00402025();
  return;
}


/* ==== FUN_00402025 @ 00402025 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402025(void)

{
  int iVar1;
  undefined *extraout_EAX;
  int *extraout_EAX_00;
  int *piVar2;
  char *a;
  uint uVar3;
  char *pcVar4;
  bool bVar5;
  uint *local_44;
  uint local_38;
  char *local_30;
  int *local_2c;
  char *local_24;
  int local_18;
  int local_14;
  
  local_24 = (char *)0x0;
  local_30 = (char *)0x0;
  FUN_00403d70(0,0,(char *)0x0);
  while (iVar1 = FUN_00403d70(DAT_0045f904,(int)DAT_0045f908,
                              s_AaB_b_CcD__d__E__e__F_f_GgI_i_Jj_0044fa08), iVar1 != -1) {
    if (__mb_cur_max < 2) {
      local_38 = *(ushort *)(_pctype + iVar1 * 2) & 1;
    }
    else {
      local_38 = _isctype(iVar1,1);
    }
    if (local_38 != 0) {
      iVar1 = tolower(iVar1);
    }
    switch(iVar1) {
    case 0x61:
      break;
    case 0x62:
      if ((DAT_0045ea98 != '\0') || (1 < DAT_0045f8fc)) {
        if (DAT_0045fca8 == (undefined *)0x0) {
          bVar5 = DAT_0045f910 == (uint *)0x0;
          if (bVar5) {
            DAT_0045f910 = (uint *)PTR_DAT_0044f808;
          }
          strcpy(&DAT_0045f220,(char *)DAT_0045f910);
          if (bVar5) {
            if (DAT_0044f790 == '\0') {
              local_44 = (uint *)&DAT_0044faa8;
            }
            else {
              local_44 = (uint *)&DAT_0044faa0;
            }
            FUN_00402b5e(local_44);
          }
          if (DAT_0045f854 == (char *)0x0) {
            uVar3 = strlen(&DAT_0045f220);
            pcVar4 = (char *)FUN_00439857(uVar3 + 1);
            strcpy(pcVar4,&DAT_0045f220);
            DAT_0045f854 = pcVar4;
          }
          local_24 = DAT_0045f854;
          if (DAT_0045ea98 == '\0') {
            if ((DAT_0045f220 == DAT_004513f0) &&
               (iVar1 = strcmp(&DAT_0045f220,&DAT_004513f4), iVar1 == 0)) {
              DAT_0045fca8 = &DAT_0045a470;
            }
            else {
              fopen(&DAT_0045f220,&DAT_004513f8);
              DAT_0045fca8 = extraout_EAX;
              if (extraout_EAX == (undefined *)0x0) {
                FUN_004137c6(s_Cannot_open_object_file_004513fc,&DAT_0045f220);
              }
            }
            FUN_00405f6a(&DAT_0045f220,&DAT_0045141c,&DAT_00451414);
          }
        }
        else {
          FUN_004137f6(s_Duplicate_object_file_specified___004513c4);
        }
      }
      break;
    case 99:
      break;
    case 100:
      DAT_0045ea50 = 1;
      if ((*DAT_0045f914 != '\'') && (*DAT_0045f914 != '\"')) {
        sprintf(&DAT_0045f428,s__c_s_c_00451424,0x27,DAT_0045f914,0x27);
        DAT_0045f914 = &DAT_0045f428;
      }
      iVar1 = FUN_0042bba2(DAT_0045f910,DAT_0045f914,1);
      if (iVar1 == 0) {
        FUN_004137c6(s_Illegal_command_line__D_option_a_0045142c,DAT_0045f910);
      }
      DAT_0045ea50 = 0;
      break;
    case 0x65:
      break;
    case 0x66:
      break;
    case 0x67:
      DAT_0045eadc = '\x01';
      break;
    default:
      FUN_0041379a(s_Illegal_command_line_option_004515b4);
      break;
    case 0x69:
      if (DAT_0045f8fc != 2) {
        DAT_0045ea50 = 1;
        iVar1 = FUN_0042c542(DAT_0045f910);
        if (iVar1 == 0) {
          FUN_004137c6(s_Illegal_command_line__I_option_a_00451454,DAT_0045f910);
        }
        DAT_0045ea50 = 0;
      }
      break;
    case 0x6a:
      break;
    case 0x6c:
      if (DAT_0045ea98 != '\0') {
        DAT_0045ea34 = 0;
        DAT_0045ea9c = 0;
      }
      if ((DAT_0045fcac == (int *)0x0) || (DAT_0045fcac == (int *)&DAT_0045a470)) {
        bVar5 = DAT_0045f910 == (uint *)0x0;
        if (bVar5) {
          DAT_0045f910 = (uint *)PTR_DAT_0044f808;
        }
        strcpy(&DAT_0045f220,(char *)DAT_0045f910);
        if (bVar5) {
          FUN_00402b5e((uint *)&DAT_004514a8);
        }
        if (DAT_0045f858 == (char *)0x0) {
          uVar3 = strlen(&DAT_0045f220);
          pcVar4 = (char *)FUN_00439857(uVar3 + 1);
          strcpy(pcVar4,&DAT_0045f220);
          DAT_0045f858 = pcVar4;
        }
        local_30 = DAT_0045f858;
        if ((DAT_0045ea98 == '\0') && (DAT_0045f8fc != 1)) {
          if ((DAT_0045f220 == DAT_004514b0) &&
             (iVar1 = strcmp(&DAT_0045f220,&DAT_004514b4), iVar1 == 0)) {
            DAT_0045fcac = (int *)&DAT_0045a470;
          }
          else {
            fopen(&DAT_0045f220,&DAT_004514b8);
            DAT_0045fcac = extraout_EAX_00;
            if (extraout_EAX_00 == (int *)0x0) {
              FUN_004137c6(s_Cannot_open_listing_file_004514bc,&DAT_0045f220);
            }
          }
          FUN_00405f6a(&DAT_0045f220,&DAT_004514e0,&DAT_004514d8);
          if (DAT_0045fcac != (int *)&DAT_0045a470) {
            FUN_0043b8f1(DAT_0045fcac,1);
          }
        }
        else {
          DAT_0045f85c = DAT_0045f858;
          local_30 = (char *)0x0;
        }
      }
      else {
        FUN_004137f6(s_Duplicate_listing_file_specified_0045147c);
      }
      break;
    case 0x6d:
      if (DAT_0045f8fc != 2) {
        DAT_0045ea50 = 1;
        iVar1 = FUN_0042c457(DAT_0045f910,1);
        if (iVar1 == 0) {
          FUN_004137c6(s_Illegal_command_line__M_option_a_004514e8,DAT_0045f910);
        }
        DAT_0045ea50 = 0;
      }
      break;
    case 0x6f:
      if (DAT_0045f8fc != 2) {
        piVar2 = (int *)FUN_00439857(8);
        uVar3 = strlen((char *)DAT_0045f910);
        iVar1 = FUN_00439857(uVar3 + 1);
        *piVar2 = iVar1;
        strcpy((char *)*piVar2,(char *)DAT_0045f910);
        piVar2[1] = (int)DAT_0045fc6c;
        DAT_0045fc6c = piVar2;
      }
      break;
    case 0x70:
      if (DAT_0045f8fc != 2) {
        DAT_0045ea50 = 1;
        iVar1 = FUN_0042fb7e((char *)DAT_0045f910);
        if (iVar1 == 0) {
          FUN_004137c6(s_Illegal_command_line__P_option_a_00451510,DAT_0045f910);
        }
        DAT_0045ea50 = 0;
      }
      break;
    case 0x71:
      break;
    case 0x72:
      if (DAT_0045f8fc != 2) {
        DAT_0045ea50 = 1;
        iVar1 = FUN_0042f9fb((char *)DAT_0045f910);
        if (iVar1 == 0) {
          FUN_004137c6(s_Illegal_command_line__R_option_a_00451538,DAT_0045f910);
        }
        _DAT_0045da34 = 1;
        _DAT_0045da38 = DAT_0045fcbc;
      }
      break;
    case 0x73:
      DAT_0045d61c = FUN_0043c9d4(&DAT_0045d620,&DAT_00451560,0x4658a0,100);
      for (local_14 = 0; bVar5 = false, local_14 < DAT_0045d61c; local_14 = local_14 + 1) {
        for (local_18 = 0; local_18 < DAT_0044f74c; local_18 = local_18 + 1) {
          pcVar4 = (&PTR_DAT_0044f6a0)[local_18];
          a = FUN_0043b836(*(char **)(&DAT_004658a0 + local_14 * 4));
          iVar1 = strcmp(a,pcVar4);
          if (iVar1 == 0) {
            bVar5 = true;
          }
        }
        if (!bVar5) {
          FUN_004137c6(s_Illegal__s_option_00451564,*(undefined4 *)(&DAT_004658a0 + local_14 * 4));
        }
      }
      break;
    case 0x74:
      DAT_0045eb50 = 1;
      break;
    case 0x76:
      DAT_0045eb4c = 1;
      if (DAT_0045f910 != (uint *)0x0) {
        DAT_0044f7c8 = strtol((char *)DAT_0045f910,(char **)0x0,10);
      }
      break;
    case 0x77:
      if (DAT_0045eac8 != '\0') {
        FUN_00405fbe(0);
      }
      if (DAT_0045f8fc != 2) {
        if ((DAT_0045eb8c == 0) || (DAT_0045f8fc != 0)) {
          bVar5 = DAT_0045f910 == (uint *)0x0;
          if (bVar5) {
            DAT_0045f910 = (uint *)PTR_DAT_0044f808;
          }
          strcpy(&DAT_0045f220,(char *)DAT_0045f910);
          if (bVar5) {
            FUN_00402b5e((uint *)&DAT_004515ac);
          }
          if (DAT_0045eb90 == (char *)0x0) {
            uVar3 = strlen(&DAT_0045f220);
            pcVar4 = (char *)FUN_00439857(uVar3 + 1);
            strcpy(pcVar4,&DAT_0045f220);
            DAT_0045eb90 = pcVar4;
          }
          if (!bVar5) {
            strcpy(&DAT_0045d830,DAT_0045eb90);
          }
          DAT_0045eb8c = 1;
        }
        else {
          FUN_004137f6(s_Lint_input_warning_file_already_s_00451578);
        }
      }
      break;
    case 0x79:
      _DAT_0045d828 = 1;
      break;
    case 0x7a:
      DAT_0045ead8 = '\x01';
    }
  }
  DAT_0045f904 = DAT_0045f904 - DAT_0045f90c;
  DAT_0045f908 = (int *)((int)DAT_0045f908 + DAT_0045f90c * 4);
  if ((DAT_0045eadc != '\0') && (DAT_0045ead8 != '\0')) {
    FUN_004137f6(s_Options_for_both_debug_and_strip_004515d0);
    DAT_0045ead8 = '\0';
  }
  if ((DAT_0044f790 != '\0') && (DAT_0045ead8 != '\0')) {
    FUN_004137f6(s_Strip_not_valid_in_relocatable_m_0045160c);
    DAT_0045ead8 = '\0';
  }
  if ((local_24 != (char *)0x0) || (local_30 != (char *)0x0)) {
    for (local_2c = DAT_0045f908; *local_2c != 0; local_2c = local_2c + 1) {
      if (((local_24 != (char *)0x0) && (*local_24 == *(char *)*local_2c)) &&
         (iVar1 = strcmp(local_24,(char *)*local_2c), iVar1 == 0)) {
        FUN_004137c6(s_Source_file_name_same_as_object_f_0045163c,local_24);
      }
      if (((local_30 != (char *)0x0) && (*local_30 == *(char *)*local_2c)) &&
         (iVar1 = strcmp(local_30,(char *)*local_2c), iVar1 == 0)) {
        FUN_004137c6(s_Source_file_name_same_as_listing_00451668,local_30);
      }
    }
  }
  return;
}


/* ==== FUN_004029fe @ 004029fe ==== */

void FUN_004029fe(void)

{
  return;
}


/* ==== FUN_00402a03 @ 00402a03 ==== */

undefined4 __cdecl FUN_00402a03(undefined4 *param_1)

{
  return *param_1;
}


/* ==== FUN_00402a0d @ 00402a0d ==== */

void FUN_00402a0d(void)

{
  int iVar1;
  char *local_c;
  undefined4 *local_8;
  
  DAT_0045ea50 = 1;
  for (local_8 = DAT_0045fc6c; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)local_8[1]) {
    iVar1 = FUN_0042ec12((char *)*local_8);
    if (iVar1 == 0) {
      if (DAT_0045ea78 == '\0') {
        local_c = &DAT_0045169c;
      }
      else {
        local_c = s_OPTION_00451694;
      }
      fprintf(&DAT_0045a470,s__s__Illegal_command_line__s_opti_004516a0,PTR_s_asm56000_0044e084,
              local_c,*local_8);
      exit(-1);
    }
  }
  DAT_0045ea50 = 0;
  return;
}


/* ==== FUN_00402a99 @ 00402a99 ==== */

uint * __cdecl FUN_00402a99(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint *dst;
  undefined3 extraout_var;
  uint *puVar5;
  
  FUN_00403d70(0,0,(char *)0x0);
  do {
    iVar2 = FUN_00403d70(param_1,param_2,s_AaB_b_CcD__d__E__e__F_f_GgI_i_Jj_0044fa08);
  } while (iVar2 != -1);
  iVar2 = DAT_0045f90c * 4;
  if (param_1 - DAT_0045f90c < 1) {
    FUN_0041379a(s_Cannot_open_source_file_004516c8);
  }
  pcVar3 = FUN_00439bd4(*(char **)(param_2 + iVar2));
  uVar4 = strlen(pcVar3);
  pcVar3 = (char *)(uVar4 + 1);
  dst = (uint *)FUN_00439857((uint)pcVar3);
  strcpy((char *)dst,pcVar3);
  cVar1 = strrchr((char *)dst,0x2e);
  puVar5 = (uint *)CONCAT31(extraout_var,cVar1);
  if ((puVar5 != (uint *)0x0) && (puVar5 != dst)) {
    *(char *)puVar5 = '\0';
  }
  return dst;
}


/* ==== FUN_00402b5e @ 00402b5e ==== */

uint __cdecl FUN_00402b5e(uint *param_1)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  undefined3 extraout_var;
  int iVar5;
  char *local_10;
  
  bVar1 = 0;
  pcVar3 = FUN_00439bd4(&DAT_0045f220);
  uVar4 = strlen(&DAT_0045f220);
  cVar2 = strrchr(&DAT_0045f220,0x2e);
  local_10 = (char *)CONCAT31(extraout_var,cVar2);
  if ((local_10 == (char *)0x0) || (local_10 < pcVar3)) {
    local_10 = &DAT_0045f220 + uVar4;
  }
  if (*local_10 == (char)*param_1) {
    iVar5 = strcmp(local_10,(char *)param_1);
    if (iVar5 == 0) goto LAB_00402beb;
  }
  strcpy(local_10,(char *)param_1);
  bVar1 = 1;
LAB_00402beb:
  return -(uint)bVar1 & (uint)local_10;
}


/* ==== FUN_00402bfa @ 00402bfa ==== */

uint __cdecl FUN_00402bfa(uint *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  undefined3 extraout_var;
  char *local_10;
  
  pcVar2 = FUN_00439bd4(&DAT_0045f220);
  uVar3 = strlen(&DAT_0045f220);
  cVar1 = strrchr(&DAT_0045f220,0x2e);
  local_10 = (char *)CONCAT31(extraout_var,cVar1);
  if ((local_10 == (char *)0x0) || (local_10 < pcVar2)) {
    local_10 = &DAT_0045f220 + uVar3;
  }
  cVar1 = *local_10;
  if (cVar1 == '\0') {
    strcpy(local_10,(char *)param_1);
  }
  return -(uint)(cVar1 == '\0') & (uint)local_10;
}


/* ==== FUN_00402c7c @ 00402c7c ==== */

void FUN_00402c7c(void)

{
  uint uVar1;
  char *local_8;
  
  uVar1 = strlen(&DAT_0045f220);
  if (0 < (int)uVar1) {
    local_8 = &DAT_0045f21f + uVar1;
    if ((*local_8 != '\\') && (*local_8 != ':')) {
      local_8 = &DAT_0045f220 + uVar1;
      *local_8 = '\\';
    }
    local_8[1] = '\0';
  }
  return;
}


/* ==== FUN_00402cde @ 00402cde ==== */

void __cdecl FUN_00402cde(uint *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *local_c;
  int *local_8;
  
  if (DAT_0045eb50 != '\0') {
    FUN_0043b836((char *)param_1);
  }
  if (DAT_0045f8fc == 0) {
    piVar1 = (int *)FUN_00439857(8);
    uVar2 = strlen((char *)param_1);
    iVar3 = FUN_00439857(uVar2 + 1);
    *piVar1 = iVar3;
    strcpy((char *)*piVar1,(char *)param_1);
    PTR_DAT_0044f80c = (undefined *)*piVar1;
    piVar1[1] = 0;
    if (DAT_0045fc24 != (int *)0x0) {
      for (local_8 = DAT_0045fc24; local_8[1] != 0; local_8 = (int *)local_8[1]) {
      }
      local_8[1] = (int)piVar1;
      piVar1 = DAT_0045fc24;
    }
  }
  else {
    piVar1 = DAT_0045fc24;
    if (0 < DAT_0045f8fc) {
      local_c = DAT_0045fc24;
      while (((char)*param_1 != *(char *)*local_c ||
             (iVar3 = strcmp((char *)param_1,(char *)*local_c), iVar3 != 0))) {
        local_c = (int *)local_c[1];
        if (local_c == (int *)0x0) {
          FUN_00412fa0((uint *)s_File_not_encountered_on_pass_1_004516e0);
        }
      }
      PTR_DAT_0044f80c = (undefined *)*local_c;
      piVar1 = DAT_0045fc24;
    }
  }
  DAT_0045fc24 = piVar1;
  return;
}


/* ==== FUN_00402dfa @ 00402dfa ==== */

int __cdecl FUN_00402dfa(int param_1,int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined3 extraout_var;
  int iVar3;
  int local_28;
  uint local_24;
  int local_1c;
  undefined4 *local_14;
  int local_10;
  undefined4 *local_c;
  uint *local_8;
  
  puVar2 = (undefined4 *)FUN_00439857(8);
  *puVar2 = *(undefined4 *)*param_2;
  puVar2[1] = 0;
  local_10 = 1;
  local_14 = puVar2;
  cVar1 = getenv(s_DSPASMOPT_0044fa58);
  local_8 = (uint *)CONCAT31(extraout_var,cVar1);
  if (local_8 != (uint *)0x0) {
    iVar3 = FUN_00403070(local_8,(int *)&local_14);
    local_10 = local_10 + iVar3;
  }
  if (DAT_0045ea78 == '\0') {
    for (local_1c = 1; local_1c < param_1; local_1c = local_1c + 1) {
      local_8 = *(uint **)(*param_2 + local_1c * 4);
      if ((char)*local_8 == '-') {
        if (__mb_cur_max < 2) {
          local_24 = *(ushort *)(_pctype + *(char *)((int)local_8 + 1) * 2) & 1;
        }
        else {
          local_24 = _isctype((int)*(char *)((int)local_8 + 1),1);
        }
        if (local_24 == 0) {
          local_28 = (int)*(char *)((int)local_8 + 1);
        }
        else {
          local_28 = tolower((int)*(char *)((int)local_8 + 1));
        }
        if (local_28 != 0x66) goto LAB_00402fb7;
        if (*(char *)((int)local_8 + 2) == '\0') {
          local_1c = local_1c + 1;
          if (param_1 <= local_1c) {
            FUN_004137c6(s_Missing_command_line_option_argu_00451704,&DAT_00451700);
          }
          local_8 = *(uint **)(*param_2 + local_1c * 4);
          if (((local_8 == (uint *)0x0) || ((char)*local_8 == '\0')) || ((char)*local_8 == '-')) {
            FUN_004137c6(s_Missing_command_line_option_argu_00451730,&DAT_0045172c);
          }
        }
        else {
          local_8 = (uint *)((int)local_8 + 2);
        }
        iVar3 = FUN_004033a1((LPCSTR)local_8,(int *)&local_14);
        local_10 = local_10 + iVar3;
      }
      else {
LAB_00402fb7:
        local_c = (undefined4 *)FUN_00439857(8);
        *local_c = local_8;
        local_c[1] = 0;
        local_14[1] = local_c;
        local_10 = local_10 + 1;
        local_14 = local_c;
      }
    }
  }
  else {
    iVar3 = FUN_004033a1(&DAT_0045f220,(int *)&local_14);
    local_10 = local_10 + iVar3;
  }
  iVar3 = FUN_00439857(local_10 * 4 + 4);
  local_14 = puVar2;
  for (local_1c = 0; puVar2 = local_14, local_1c < local_10; local_1c = local_1c + 1) {
    *(undefined4 *)(iVar3 + local_1c * 4) = *local_14;
    local_c = local_14;
    local_14 = (undefined4 *)local_14[1];
    FUN_004398b5((undefined *)puVar2);
  }
  *(undefined4 *)(iVar3 + local_1c * 4) = 0;
  *param_2 = iVar3;
  return local_10;
}


/* ==== FUN_00403070 @ 00403070 ==== */

int __cdecl FUN_00403070(uint *param_1,int *param_2)

{
  char cVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  uint local_34;
  uint local_30;
  int local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  int local_14;
  uint *local_c;
  uint *local_8;
  
  local_14 = 0;
  local_8 = param_1;
LAB_00403083:
  do {
    if ((char)*local_8 == '\0') {
      return local_14;
    }
    for (; local_c = local_8, iVar4 = (int)(char)*local_8, iVar4 != 0;
        local_8 = (uint *)((int)local_8 + 1)) {
      if (__mb_cur_max < 2) {
        local_20 = *(ushort *)(_pctype + iVar4 * 2) & 0x157;
      }
      else {
        local_20 = _isctype(iVar4,0x157);
      }
      if ((local_20 != 0) && (iVar4 != 0x20)) break;
    }
    local_1c = 1;
    for (; iVar4 = (int)(char)*local_8, iVar4 != 0; local_8 = (uint *)((int)local_8 + 1)) {
      if (__mb_cur_max < 2) {
        local_24 = *(ushort *)(_pctype + iVar4 * 2) & 0x157;
      }
      else {
        local_24 = _isctype(iVar4,0x157);
      }
      if ((local_24 == 0) || (iVar4 == 0x20)) break;
      local_1c = local_1c + 1;
    }
    cVar1 = (char)*local_8;
    *(char *)local_8 = '\0';
    if ((char)*local_c == '-') {
      if (__mb_cur_max < 2) {
        local_28 = *(ushort *)(_pctype + *(char *)((int)local_c + 1) * 2) & 1;
      }
      else {
        local_28 = _isctype((int)*(char *)((int)local_c + 1),1);
      }
      if (local_28 == 0) {
        local_2c = (int)*(char *)((int)local_c + 1);
      }
      else {
        local_2c = tolower((int)*(char *)((int)local_c + 1));
      }
      if (local_2c == 0x66) {
        if (*(char *)((int)local_c + 2) == '\0') {
          *(char *)local_8 = cVar1;
          for (; puVar2 = local_8, iVar4 = (int)(char)*local_8, iVar4 != 0;
              local_8 = (uint *)((int)local_8 + 1)) {
            if (__mb_cur_max < 2) {
              local_30 = *(ushort *)(_pctype + iVar4 * 2) & 0x157;
            }
            else {
              local_30 = _isctype(iVar4,0x157);
            }
            if ((local_30 != 0) && (iVar4 != 0x20)) break;
          }
          local_c = local_8;
          for (; iVar4 = (int)(char)*local_8, iVar4 != 0; local_8 = (uint *)((int)local_8 + 1)) {
            if (__mb_cur_max < 2) {
              local_34 = *(ushort *)(_pctype + iVar4 * 2) & 0x157;
            }
            else {
              local_34 = _isctype(iVar4,0x157);
            }
            if ((local_34 == 0) || (iVar4 == 0x20)) break;
          }
          cVar1 = (char)*local_8;
          *(char *)local_8 = '\0';
          if ((puVar2 == (uint *)0x0) || (((char)*puVar2 == '\0' || ((char)*puVar2 == '-')))) {
            FUN_004137c6(s_Missing_command_line_option_argu_0045175c,&DAT_00451758);
          }
        }
        else {
          local_c = (uint *)((int)local_c + 2);
        }
        iVar4 = FUN_004033a1((LPCSTR)local_c,param_2);
        local_14 = local_14 + iVar4;
        *(char *)local_8 = cVar1;
        goto LAB_00403083;
      }
    }
    if ((char)*local_c != '\0') {
      piVar3 = (int *)FUN_00439857(8);
      iVar4 = FUN_00439857(local_1c + 1);
      *piVar3 = iVar4;
      strcpy((char *)*piVar3,(char *)local_c);
      piVar3[1] = 0;
      *(int **)(*param_2 + 4) = piVar3;
      *param_2 = (int)piVar3;
      local_14 = local_14 + 1;
    }
    *(char *)local_8 = cVar1;
  } while( true );
}


/* ==== FUN_004033a1 @ 004033a1 ==== */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int __cdecl FUN_004033a1(LPCSTR param_1,int *param_2)

{
  int *stream;
  uint c;
  uint uVar1;
  int iVar2;
  uint local_244;
  uint local_240;
  uint local_23c;
  int local_238;
  uint local_234;
  uint local_230;
  uint local_22c;
  uint local_228;
  uint local_224;
  uint local_220;
  int local_218;
  char local_214;
  int local_210;
  CHAR local_20c;
  char local_20b;
  char local_20a [510];
  int *local_c;
  char *local_8;
  
  local_210 = 0;
  fopen(param_1,&DAT_00451784);
  if (stream == (int *)0x0) {
    FUN_004137c6(s_Cannot_open_command_file_00451788,param_1);
  }
LAB_004033e5:
  do {
    if ((stream[3] & 0x10U) != 0) {
LAB_00403a8e:
      fclose(stream);
      return local_210;
    }
    do {
      stream[1] = stream[1] + -1;
      if (stream[1] < 0) {
        local_220 = _filbuf(stream);
      }
      else {
        local_220 = (uint)*(byte *)*stream;
        *stream = *stream + 1;
      }
      if (local_220 == 0xffffffff) break;
      if (__mb_cur_max < 2) {
        local_224 = *(ushort *)(_pctype + local_220 * 2) & 0x157;
      }
      else {
        local_224 = _isctype(local_220,0x157);
      }
    } while ((local_224 == 0) || (local_220 == 0x20));
    if ((stream[3] & 0x10U) != 0) goto LAB_00403a8e;
    if (local_220 != 0x3b) {
      local_214 = (char)local_220;
      local_20c = local_214;
      local_8 = &local_20b;
      local_218 = 1;
      while( true ) {
        stream[1] = stream[1] + -1;
        if (stream[1] < 0) {
          local_22c = _filbuf(stream);
        }
        else {
          local_22c = (uint)*(byte *)*stream;
          *stream = *stream + 1;
        }
        if (local_22c == 0xffffffff) break;
        if (__mb_cur_max < 2) {
          local_230 = *(ushort *)(_pctype + local_22c * 2) & 0x157;
        }
        else {
          local_230 = _isctype(local_22c,0x157);
        }
        if ((local_230 == 0) || (local_22c == 0x20)) break;
        local_214 = (char)local_22c;
        *local_8 = local_214;
        local_8 = local_8 + 1;
        local_218 = local_218 + 1;
      }
      *local_8 = '\0';
      if (local_20c == '-') {
        if (__mb_cur_max < 2) {
          local_234 = *(ushort *)(_pctype + local_20b * 2) & 1;
        }
        else {
          local_234 = _isctype((int)local_20b,1);
        }
        if (local_234 == 0) {
          local_238 = (int)local_20b;
        }
        else {
          local_238 = tolower((int)local_20b);
        }
        if (local_238 == 0x66) {
          if (local_20a[0] == '\0') {
            do {
              stream[1] = stream[1] + -1;
              if (stream[1] < 0) {
                local_23c = _filbuf(stream);
              }
              else {
                local_23c = (uint)*(byte *)*stream;
                *stream = *stream + 1;
              }
              if (local_23c == 0xffffffff) break;
              if (__mb_cur_max < 2) {
                local_240 = *(ushort *)(_pctype + local_23c * 2) & 0x157;
              }
              else {
                local_240 = _isctype(local_23c,0x157);
              }
            } while ((local_240 == 0) || (local_23c == 0x20));
            if ((stream[3] & 0x10U) != 0) {
              FUN_004137c6(s_Missing_command_line_option_argu_004517a8,&DAT_004517a4);
            }
            if (local_23c == 0x3b) {
              do {
                stream[1] = stream[1] + -1;
                if (stream[1] < 0) {
                  local_244 = _filbuf(stream);
                }
                else {
                  local_244 = (uint)*(byte *)*stream;
                  *stream = *stream + 1;
                }
              } while ((local_244 != 0xffffffff) && (local_244 != 10));
              goto LAB_004033e5;
            }
            local_214 = (char)local_23c;
            local_20c = local_214;
            local_8 = &local_20b;
            while( true ) {
              stream[1] = stream[1] + -1;
              if (stream[1] < 0) {
                c = _filbuf(stream);
              }
              else {
                c = (uint)*(byte *)*stream;
                *stream = *stream + 1;
              }
              if (c == 0xffffffff) break;
              if (__mb_cur_max < 2) {
                uVar1 = *(ushort *)(_pctype + c * 2) & 0x157;
              }
              else {
                uVar1 = _isctype(c,0x157);
              }
              if ((uVar1 == 0) || (c == 0x20)) break;
              local_214 = (char)c;
              *local_8 = local_214;
              local_8 = local_8 + 1;
            }
            *local_8 = '\0';
            local_8 = &local_20c;
            if ((local_8 == (CHAR *)0x0) || ((local_20c == '\0' || (local_20c == '-')))) {
              FUN_004137c6(s_Missing_command_line_option_argu_004517d4,&DAT_004517d0);
            }
          }
          else {
            local_8 = local_20a;
          }
          iVar2 = FUN_004033a1(local_8,param_2);
          local_210 = local_210 + iVar2;
          goto LAB_004033e5;
        }
      }
      if (local_20c != '\0') {
        local_c = (int *)FUN_00439857(8);
        iVar2 = FUN_00439857(local_218 + 1);
        *local_c = iVar2;
        strcpy((char *)*local_c,&local_20c);
        local_c[1] = 0;
        *(int **)(*param_2 + 4) = local_c;
        *param_2 = (int)local_c;
        local_210 = local_210 + 1;
      }
      local_20c = '\0';
      goto LAB_004033e5;
    }
    do {
      stream[1] = stream[1] + -1;
      if (stream[1] < 0) {
        local_228 = _filbuf(stream);
      }
      else {
        local_228 = (uint)*(byte *)*stream;
        *stream = *stream + 1;
      }
    } while ((local_228 != 0xffffffff) && (local_228 != 10));
  } while( true );
}


/* ==== FUN_00403aa7 @ 00403aa7 ==== */

int __cdecl FUN_00403aa7(char param_1,int param_2,int *param_3)

{
  int iVar1;
  int local_c;
  uint local_8;
  
  if (DAT_0045ea78 == '\0') {
    do {
      do {
        param_3 = param_3 + 1;
        param_2 = param_2 + -1;
        if (param_2 < 1) goto LAB_00403b72;
      } while (*(char *)*param_3 != '-');
      if (__mb_cur_max < 2) {
        local_8 = *(ushort *)(_pctype + *(char *)(*param_3 + 1) * 2) & 1;
      }
      else {
        local_8 = _isctype((int)*(char *)(*param_3 + 1),1);
      }
      if (local_8 == 0) {
        local_c = (int)*(char *)(*param_3 + 1);
      }
      else {
        local_c = tolower((int)*(char *)(*param_3 + 1));
      }
    } while (local_c != param_1);
    iVar1 = *param_3;
  }
  else {
LAB_00403b72:
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== FUN_00403b78 @ 00403b78 ==== */

int __cdecl FUN_00403b78(char param_1,int param_2,int *param_3)

{
  int local_10;
  uint local_c;
  int local_8;
  
  local_8 = 1;
  do {
    param_3 = param_3 + 1;
    param_2 = param_2 + -1;
    if (param_2 < 1) {
      return 0;
    }
    if (*(char *)*param_3 == '-') {
      if (__mb_cur_max < 2) {
        local_c = *(ushort *)(_pctype + *(char *)(*param_3 + 1) * 2) & 1;
      }
      else {
        local_c = _isctype((int)*(char *)(*param_3 + 1),1);
      }
      if (local_c == 0) {
        local_10 = (int)*(char *)(*param_3 + 1);
      }
      else {
        local_10 = tolower((int)*(char *)(*param_3 + 1));
      }
      if (local_10 == param_1) {
        return local_8;
      }
    }
    local_8 = local_8 + 1;
  } while( true );
}


/* ==== FUN_00403c50 @ 00403c50 ==== */

void __cdecl FUN_00403c50(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined *extraout_EAX;
  char local_c [4];
  char *local_8;
  
  local_c[0] = *(char *)(*(int *)(param_1 + param_2 * 4) + 2);
  local_c[1] = 0;
  if (__mb_cur_max < 2) {
    uVar1 = *(ushort *)(_pctype + local_c[0] * 2) & 1;
  }
  else {
    uVar1 = _isctype((int)local_c[0],1);
  }
  if (uVar1 != 0) {
    iVar2 = tolower((int)local_c[0]);
    local_c[0] = (char)iVar2;
  }
  if ((local_c[0] != 'a') && (local_c[0] != 'w')) {
    FUN_0041379a(s_Illegal_command_line__E_option_004517fc);
  }
  if (*(char *)(*(int *)(param_1 + param_2 * 4) + 3) != '\0') {
    FUN_0041379a(s_Invalid_syntax_for_command_line___0045181c);
  }
  local_8 = *(char **)(param_1 + 4 + param_2 * 4);
  if (*local_8 == '-') {
    FUN_0041379a(s_Missing_argument_for_command_lin_00451848);
  }
  if ((PTR_DAT_0044f9a4 != (undefined *)0x0) && (PTR_DAT_0044f9a4 != &DAT_0045a490)) {
    fclose(PTR_DAT_0044f9a4);
  }
  fopen(local_8,local_c);
  PTR_DAT_0044f9a4 = extraout_EAX;
  if (extraout_EAX == (undefined *)0x0) {
    PTR_DAT_0044f9a4 = &DAT_0045a490;
    FUN_0041379a(s_Cannot_open_error_file_00451874);
  }
  return;
}


/* ==== FUN_00403d70 @ 00403d70 ==== */

int __cdecl FUN_00403d70(int param_1,int param_2,char *param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  char *va1;
  
  if (((param_1 == 0) && (param_2 == 0)) && (param_3 == (char *)0x0)) {
    DAT_0045f90c = 0;
    DAT_00463bdc = (char *)0x0;
    return -1;
  }
  DAT_0045f910 = (char *)0x0;
  DAT_0045f914 = 0;
  if ((DAT_00463bdc == (char *)0x0) || (*DAT_00463bdc == '\0')) {
    if (DAT_0045f90c == 0) {
      DAT_0045f90c = 1;
    }
    if (((param_1 <= DAT_0045f90c) || (**(char **)(param_2 + DAT_0045f90c * 4) != '-')) ||
       (*(char *)(*(int *)(param_2 + DAT_0045f90c * 4) + 1) == '\0')) {
      DAT_0045f910 = (char *)0x0;
      DAT_0045f914 = 0;
      return -1;
    }
    iVar3 = strcmp(*(char **)(param_2 + DAT_0045f90c * 4),&DAT_0045188c);
    if (iVar3 == 0) {
      DAT_0045f90c = DAT_0045f90c + 1;
      return -1;
    }
    DAT_00463bdc = (char *)(*(int *)(param_2 + DAT_0045f90c * 4) + 1);
    DAT_0045f90c = DAT_0045f90c + 1;
  }
  cVar1 = *DAT_00463bdc;
  DAT_00463bdc = DAT_00463bdc + 1;
  cVar2 = strchr(param_3,(int)cVar1);
  iVar3 = CONCAT31(extraout_var,cVar2);
  if (((iVar3 == 0) || (cVar1 == ':')) || (cVar1 == '?')) {
    sprintf(&stack0xfffffff0,&DAT_00451890,(int)cVar1);
    FUN_004137c6(s_Illegal_command_line_option_00451894,&stack0xfffffff0);
  }
  va1 = (char *)(iVar3 + 1);
  if (*va1 == ':') {
    if (*DAT_00463bdc == '\0') {
      if (DAT_0045f90c < param_1) {
        DAT_0045f910 = *(char **)(param_2 + DAT_0045f90c * 4);
        DAT_0045f90c = DAT_0045f90c + 1;
      }
      else {
        sprintf(&stack0xfffffff0,&DAT_004518b0,(int)cVar1);
        va1 = &stack0xfffffff0;
        FUN_004137c6(s_Missing_command_line_option_argu_004518b4,va1);
      }
    }
    else {
      DAT_0045f910 = DAT_00463bdc;
      DAT_00463bdc = (char *)0x0;
    }
    if (va1[1] == ':') {
      if (DAT_0045f90c < param_1) {
        DAT_0045f914 = *(undefined4 *)(param_2 + DAT_0045f90c * 4);
        DAT_0045f90c = DAT_0045f90c + 1;
      }
      else {
        sprintf(&stack0xfffffff0,&DAT_004518dc,(int)cVar1);
        FUN_004137c6(s_Missing_command_line_option_argu_004518e0,&stack0xfffffff0);
      }
    }
  }
  else if (*va1 == '?') {
    if (*DAT_00463bdc == '\0') {
      if (DAT_0045f90c < param_1) {
        if (**(char **)(param_2 + DAT_0045f90c * 4) == '-') {
          if (*(char *)(*(int *)(param_2 + DAT_0045f90c * 4) + 1) == '\0') {
            DAT_0045f910 = *(char **)(param_2 + DAT_0045f90c * 4);
            DAT_0045f90c = DAT_0045f90c + 1;
          }
        }
        else if ((DAT_0045f90c + 1 < param_1) &&
                (**(char **)(param_2 + 4 + DAT_0045f90c * 4) == '-')) {
          DAT_0045f910 = *(char **)(param_2 + DAT_0045f90c * 4);
          DAT_0045f90c = DAT_0045f90c + 1;
        }
      }
    }
    else {
      DAT_0045f910 = DAT_00463bdc;
      DAT_00463bdc = (char *)0x0;
    }
  }
  return (int)cVar1;
}


/* ==== FUN_004040b4 @ 004040b4 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004040b4(void)

{
  int iVar1;
  bool bVar2;
  
  DAT_0045f8fc = 0;
  DAT_0045eb80 = 0;
  DAT_0045eb7c = 0;
  DAT_0045d824 = 0;
  DAT_0045eb88 = 0;
  DAT_0045eb84 = 0;
  qsort(&PTR_DAT_0044f6a0,DAT_0044f74c,4,FUN_0043cab6);
  DAT_0045eb90 = 0;
  DAT_0045eb94 = 0;
  DAT_0045f934 = 0;
  DAT_0045eb68 = 0;
  DAT_0045ebec = 1;
  DAT_0045f930 = 0;
  DAT_0045ebf0 = 1;
  DAT_0045eba0 = 0;
  if (DAT_0045ea98 == '\0') {
    DAT_0044f954 = 1;
    DAT_0044f958 = 1;
  }
  else {
    DAT_0044f7a0 = 1;
  }
  bVar2 = DAT_0044f790 != '\0';
  if (bVar2) {
    PTR_DAT_0044f828 = &DAT_00451908;
    PTR_DAT_0044f82c = &DAT_0045ec04;
  }
  DAT_0045eab4 = !bVar2;
  DAT_0045ea90 = !bVar2;
  DAT_0044f920 = 0xffff;
  DAT_0044f91c = 0xffff;
  DAT_0045f8dc = &DAT_0045f88c;
  DAT_0045f8d4 = &DAT_0045f88c;
  DAT_0045f8e0 = &DAT_0044f854;
  DAT_0045f8d8 = &DAT_0044f854;
  DAT_0044f798 = DAT_0044f790;
  DAT_0044f794 = DAT_0044f790;
  FUN_00405611();
  DAT_0045fb98 = (-(uint)(DAT_0044f790 != '\0') & 0xfffffffe) + 2;
  DAT_0045fb9c = 0;
  DAT_0045f8b4 = 0;
  DAT_0045f8a4 = 0;
  DAT_0045f8b0 = 0;
  DAT_0045f8a0 = 0;
  DAT_0045f8b8 = 0;
  DAT_0045f8a8 = 0;
  DAT_0045f8bc = 0;
  DAT_0045f8ac = 0;
  FUN_0042c829(0x44f878,&DAT_0045f8a0,-(uint)(DAT_0044f790 != '\0') & 0x1000,1);
  DAT_0045fb8c = DAT_0044f8dc;
  DAT_0045fb88 = DAT_0044f8dc;
  DAT_0045f8c0 = *(int *)(DAT_0044f8dc + 0x24) + 0x10;
  DAT_0045f8d0 = 0;
  DAT_0045f8c4 = 0;
  DAT_0045f8cc = DAT_0045f8c0;
  FUN_0043b926(1);
  if (DAT_0045eb34 != '\0') {
    FUN_00433e78(0);
    FUN_00433f67(0x44f878);
  }
  DAT_0045f940 = 0;
  DAT_0045f944 = 0;
  DAT_0045f948 = 0;
  _DAT_0045f938 = 0;
  DAT_0045f93c = 0;
  DAT_0045ebb4 = 0;
  DAT_0045ebb8 = 0;
  DAT_0045fc40 = DAT_0045fc3c;
  DAT_0045fc50 = 0;
  DAT_0045fc4c = 0;
  DAT_0045fc48 = 0;
  DAT_0045f924 = 0;
  DAT_0045eba8 = 0;
  DAT_0045eba4 = 0;
  DAT_0044f7cc = 10;
  DAT_0045ebbc = 0;
  DAT_0045ebe8 = 0;
  DAT_0045ebc0 = 0;
  DAT_0045ebc4 = 0;
  DAT_00465b64 = 4;
  DAT_00465b60 = 4;
  DAT_00465b68 = 0;
  DAT_00465b6c = 0;
  DAT_0045ebe4 = 0;
  DAT_0044f7d0 = 8;
  DAT_0045fbe0 = 0;
  DAT_0045fbd0 = 0;
  DAT_0045fbc0 = 0;
  DAT_0045fbb0 = 0;
  DAT_0045fb90 = 0;
  DAT_0045fbac = 0;
  DAT_0045fb94 = 0;
  DAT_0045fbb4 = 0;
  DAT_0045fc14 = 0;
  DAT_0045fbc4 = 0;
  DAT_0045fbd4 = 0;
  DAT_0044f988 = 4;
  DAT_0045eaf0 = 0;
  DAT_0045fbec = 0;
  DAT_0045eaec = 0;
  DAT_0045eae8 = 0;
  DAT_0045eae4 = 0;
  DAT_0045fbf0 = 0;
  DAT_0045fbf4 = 0;
  DAT_0045fc00 = 0;
  DAT_0045fbfc = 0;
  DAT_0045fc18 = 0;
  DAT_0045fc08 = 0;
  DAT_0045fc0c = 0;
  DAT_0045fc10 = 0;
  DAT_0045ebb0 = 0;
  DAT_0045ebac = 0;
  DAT_0045fc20 = 0;
  DAT_0045fc1c = 0;
  DAT_0045fca4 = 0;
  DAT_0044f79c = '\x01' - (DAT_0045ea98 != '\0');
  DAT_0044f7a4 = DAT_0044f79c;
  DAT_0044f7b4 = DAT_0044f79c;
  if (DAT_0045ea98 == '\0') {
    FUN_00405fbe(0);
  }
  else {
    FUN_00405fbe(1);
  }
  iVar1 = FUN_00405fd4();
  DAT_0045ea88 = (undefined1)iVar1;
  DAT_0044f7a8 = 1;
  DAT_0044f7c4 = 1;
  DAT_0044f7c0 = 1;
  DAT_0044f7bc = 1;
  DAT_0044f7b8 = 1;
  DAT_0044f78c = 1;
  DAT_0044f7b0 = 1;
  DAT_0044f7ac = 1;
  DAT_0044f788 = 1;
  DAT_0044f780 = 1;
  DAT_0044f77c = 1;
  DAT_0044f784 = 1;
  DAT_0044f778 = 1;
  DAT_0045ea18 = 0;
  DAT_0045ea24 = 0;
  DAT_0045eb48 = 0;
  DAT_0045eb0c = 0;
  DAT_0045eab0 = 0;
  DAT_0045ea80 = 0;
  DAT_0045eb44 = 0;
  DAT_0045eae0 = 0;
  DAT_0045eb40 = 0;
  DAT_0045ead4 = 0;
  DAT_0045eb30 = 0;
  DAT_0045eb2c = 0;
  DAT_0045eb20 = 0;
  DAT_0045eb1c = 0;
  DAT_0045eb04 = 0;
  DAT_0045eafc = 0;
  DAT_0045eaf8 = 0;
  DAT_0045eaf4 = 0;
  DAT_0045eabc = 0;
  DAT_0045eab8 = 0;
  DAT_0045ead0 = 0;
  DAT_0045eac4 = 0;
  DAT_0045eaac = 0;
  DAT_0045eaa8 = 0;
  DAT_0045eaa4 = 0;
  DAT_0045eaa0 = 0;
  DAT_0045ea84 = 0;
  DAT_0045ea60 = 0;
  DAT_0045ea64 = 0;
  DAT_0045ea30 = 0;
  DAT_0045ea48 = 0;
  DAT_0045ea38 = 0;
  DAT_0045ea2c = 0;
  DAT_0045ea0c = 0;
  FUN_004392a1();
  FUN_004314ab();
  return;
}


/* ==== FUN_004047e0 @ 004047e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004047e0(void)

{
  int iVar1;
  bool bVar2;
  
  DAT_0045f8fc = 1;
  DAT_0045f8f0 = 0;
  DAT_0045ea28 = 0;
  DAT_0045eb80 = 0;
  DAT_0045eb7c = 0;
  DAT_0045d824 = 0;
  DAT_0045eb88 = 0;
  DAT_0045eb84 = 0;
  DAT_0045f934 = 0;
  DAT_0045eb68 = 0;
  DAT_0045ebec = 1;
  DAT_0045f930 = 0;
  DAT_0045ebf0 = 1;
  DAT_0045eba0 = 0;
  if (DAT_0045ea98 == '\0') {
    DAT_0044f954 = 1;
    DAT_0044f958 = 1;
  }
  else {
    DAT_0044f7a0 = 1;
  }
  bVar2 = DAT_0044f790 != '\0';
  if (bVar2) {
    PTR_DAT_0044f828 = &DAT_0045190c;
    PTR_DAT_0044f82c = &DAT_0045ec04;
  }
  DAT_0045eab4 = !bVar2;
  DAT_0045ea90 = !bVar2;
  DAT_0044f920 = 0xffff;
  DAT_0044f91c = 0xffff;
  DAT_0045f8dc = &DAT_0045f88c;
  DAT_0045f8d4 = &DAT_0045f88c;
  DAT_0045f8e0 = &DAT_0044f854;
  DAT_0045f8d8 = &DAT_0044f854;
  DAT_0044f798 = DAT_0044f790;
  DAT_0044f794 = DAT_0044f790;
  FUN_00405611();
  DAT_0045fb98 = (-(uint)(DAT_0044f790 != '\0') & 0xfffffffe) + 2;
  DAT_0045fb9c = 0;
  DAT_0045f8b4 = 0;
  DAT_0045f8a4 = 0;
  DAT_0045f8b0 = 0;
  DAT_0045f8a0 = 0;
  DAT_0045f8b8 = 0;
  DAT_0045f8a8 = 0;
  DAT_0045f8bc = 0;
  DAT_0045f8ac = 0;
  FUN_0042c829(0x44f878,&DAT_0045f8a0,-(uint)(DAT_0044f790 != '\0') & 0x1000,1);
  DAT_0045fb8c = DAT_0044f8dc;
  DAT_0045fb88 = DAT_0044f8dc;
  DAT_0045f8c0 = *(int *)(DAT_0044f8dc + 0x24) + 0x10;
  DAT_0045f8d0 = 0;
  DAT_0045f8c4 = 0;
  DAT_0045f8cc = DAT_0045f8c0;
  FUN_0043b926(1);
  if (DAT_0045eb34 != '\0') {
    FUN_00433e78(0);
    FUN_00433f67(0x44f878);
  }
  DAT_0045f940 = 0;
  DAT_0045f944 = 0;
  DAT_0045f948 = 0;
  _DAT_0045f938 = 0;
  DAT_0045f93c = 0;
  DAT_0045ebb4 = 0;
  DAT_0045ebb8 = 0;
  DAT_0045fc40 = DAT_0045fc3c;
  DAT_0045fc50 = 0;
  DAT_0045fc4c = 0;
  DAT_0045fc48 = 0;
  DAT_0045f924 = 0;
  DAT_0045eba8 = 0;
  DAT_0045eba4 = 0;
  DAT_0044f7cc = 10;
  DAT_0045ebbc = 0;
  DAT_0045ebe8 = 0;
  DAT_0045ebc0 = 0;
  DAT_0045ebc4 = 0;
  DAT_00465b64 = 4;
  DAT_00465b60 = 4;
  DAT_00465b68 = 0;
  DAT_00465b6c = 0;
  DAT_0045ebe4 = 0;
  DAT_0044f7d0 = 8;
  DAT_0045fbe0 = 0;
  DAT_0045fbd0 = 0;
  DAT_0045fbc0 = 0;
  DAT_0045fbb0 = 0;
  DAT_0045fb90 = 0;
  DAT_0045fbac = 0;
  DAT_0045fb94 = 0;
  DAT_0045fbb4 = 0;
  DAT_0045fc14 = 0;
  DAT_0045fbc4 = 0;
  DAT_0045fbd4 = 0;
  DAT_0044f988 = 4;
  DAT_0045eaf0 = 0;
  DAT_0045fbec = 0;
  DAT_0045eaec = 0;
  DAT_0045eae8 = 0;
  DAT_0045eae4 = 0;
  DAT_0045fbf0 = 0;
  DAT_0045fbf4 = 0;
  DAT_0045fc00 = 0;
  DAT_0045fbfc = 0;
  DAT_0045fc18 = 0;
  DAT_0045fc08 = 0;
  DAT_0045fc0c = 0;
  DAT_0045fc10 = 0;
  DAT_0045ebb0 = 0;
  DAT_0045ebac = 0;
  DAT_0045fc20 = 0;
  DAT_0045fc1c = 0;
  DAT_0045fca4 = 0;
  DAT_0044f79c = '\x01' - (DAT_0045ea98 != '\0');
  DAT_0044f7a4 = DAT_0044f79c;
  DAT_0044f7b4 = DAT_0044f79c;
  if (DAT_0045ea98 == '\0') {
    FUN_00405fbe(0);
  }
  else {
    FUN_00405fbe(1);
  }
  iVar1 = FUN_00405fd4();
  DAT_0045ea88 = (undefined1)iVar1;
  DAT_0044f7a8 = 1;
  DAT_0044f7c4 = 1;
  DAT_0044f7c0 = 1;
  DAT_0044f7bc = 1;
  DAT_0044f7b8 = 1;
  DAT_0044f78c = 1;
  DAT_0044f7b0 = 1;
  DAT_0044f7ac = 1;
  DAT_0044f788 = 1;
  DAT_0044f780 = 1;
  DAT_0044f77c = 1;
  DAT_0044f784 = 1;
  DAT_0044f778 = 1;
  DAT_0045ea18 = 0;
  DAT_0045ea24 = 0;
  DAT_0045eb48 = 0;
  DAT_0045eb0c = 0;
  DAT_0045eab0 = 0;
  DAT_0045ea80 = 0;
  DAT_0045eb44 = 0;
  DAT_0045eae0 = 0;
  DAT_0045eb40 = 0;
  DAT_0045ead4 = 0;
  DAT_0045eb30 = 0;
  DAT_0045eb2c = 0;
  DAT_0045eb20 = 0;
  DAT_0045eb1c = 0;
  DAT_0045eb04 = 0;
  DAT_0045eafc = 0;
  DAT_0045eaf8 = 0;
  DAT_0045eaf4 = 0;
  DAT_0045eabc = 0;
  DAT_0045eab8 = 0;
  DAT_0045ead0 = 0;
  DAT_0045eac4 = 0;
  DAT_0045eaac = 0;
  DAT_0045eaa8 = 0;
  DAT_0045eaa4 = 0;
  DAT_0045eaa0 = 0;
  DAT_0045ea84 = 0;
  DAT_0045ea60 = 0;
  DAT_0045ea64 = 0;
  DAT_0045ea30 = 0;
  DAT_0045ea48 = 0;
  DAT_0045ea38 = 0;
  DAT_0045ea2c = 0;
  DAT_0045ea0c = 0;
  FUN_004392a1();
  FUN_004314ab();
  return;
}


/* ==== FUN_00404ef2 @ 00404ef2 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404ef2(void)

{
  int iVar1;
  uint uVar2;
  
  DAT_0045ea78 = DAT_0045ea7c;
  if (DAT_0045ea98 == '\0') {
    DAT_0044f954 = 1;
    DAT_0044f958 = 1;
  }
  else {
    DAT_0044f7a0 = 1;
  }
  DAT_0045eb80 = 0;
  DAT_0045eb7c = 0;
  DAT_0045d824 = 0;
  DAT_0045eb88 = 0;
  DAT_0045eb84 = 0;
  DAT_0045f934 = 0;
  DAT_0045eb68 = 0;
  if (DAT_0044f790 == '\0') {
    DAT_0045eab4 = 1;
    DAT_0045ea90 = 1;
  }
  else {
    DAT_0045eab4 = 0;
    DAT_0045ea90 = 0;
    PTR_DAT_0044f828 = &DAT_00451910;
    PTR_DAT_0044f82c = &DAT_0045ec04;
  }
  while (PTR_DAT_0044f978 != &DAT_0044f878) {
    FUN_00435924();
  }
  DAT_0044f920 = 0xffff;
  DAT_0044f91c = 0xffff;
  DAT_0045f8dc = &DAT_0045f88c;
  DAT_0045f8d4 = &DAT_0045f88c;
  DAT_0045f8e0 = &DAT_0044f854;
  DAT_0045f8d8 = &DAT_0044f854;
  DAT_0044f798 = DAT_0044f790;
  DAT_0044f794 = DAT_0044f790;
  FUN_00405611();
  DAT_0045fb8c = DAT_0044f8dc;
  DAT_0045fb88 = DAT_0044f8dc;
  DAT_0045f8c0 = *(int *)(DAT_0044f8dc + 0x24) + 0x10;
  DAT_0045f8d0 = 0;
  DAT_0045f8c4 = 0;
  DAT_0045f8cc = DAT_0045f8c0;
  FUN_0043b926(1);
  if (DAT_0044f790 == '\0') {
    DAT_0044f8e4 = DAT_0044f8e0;
  }
  DAT_0045f8b4 = 0;
  DAT_0045f8a4 = 0;
  DAT_0045f8b0 = 0;
  DAT_0045f8a0 = 0;
  DAT_0045f8b8 = 0;
  DAT_0045f8a8 = 0;
  DAT_0045f8bc = 0;
  DAT_0045f8ac = 0;
  DAT_0045f940 = 0;
  DAT_0045f944 = 0;
  DAT_0045f948 = 0;
  _DAT_0045f938 = 0;
  DAT_0045f93c = 0;
  DAT_0045ebb4 = 0;
  DAT_0045ebb8 = 0;
  DAT_0045f924 = 0;
  DAT_0045eba8 = 0;
  DAT_0045eba4 = 0;
  DAT_0044f7cc = 10;
  DAT_0045ebbc = 0;
  DAT_0045ebe8 = 0;
  DAT_0045ebc0 = 0;
  DAT_0045ebc4 = 0;
  DAT_00465b64 = 4;
  DAT_00465b60 = 4;
  DAT_00465b68 = 0;
  DAT_00465b6c = 0;
  DAT_0045ebe4 = 0;
  DAT_0044f7d0 = 8;
  DAT_0045fb90 = (-(uint)(DAT_0044f790 != '\0') & 0xfffffffc) + 0x58 + DAT_0045fb98 * 0x34;
  DAT_0045fbac = 0;
  DAT_0045fb94 = 0;
  DAT_0045fbb4 = 0;
  DAT_0045fc14 = 0;
  DAT_0045fbc4 = 0;
  DAT_0045fbd4 = 0;
  DAT_0044f988 = 4;
  DAT_0045eaf0 = 0;
  DAT_0045eae4 = 0;
  DAT_0045fbec = 0;
  DAT_0045fbf0 = 0;
  DAT_0045fbf4 = 0;
  DAT_0045fc18 = 0;
  DAT_0045fc08 = 0;
  DAT_0045fc10 = -(uint)(DAT_0045fc0c != 0) & DAT_0045fc0c;
  DAT_0045ebb0 = 0;
  DAT_0045ebac = 0;
  DAT_0045fc20 = 0;
  DAT_0045fc1c = 0;
  DAT_0045fca4 = 0;
  DAT_0044f79c = '\x01' - (DAT_0045ea98 != '\0');
  DAT_0044f7a4 = DAT_0044f79c;
  DAT_0044f7b4 = DAT_0044f79c;
  if (DAT_0045ea98 == '\0') {
    FUN_00405fbe(0);
  }
  else {
    FUN_00405fbe(1);
  }
  iVar1 = FUN_00405fd4();
  DAT_0045ea88 = (undefined1)iVar1;
  DAT_0044f7a8 = 1;
  DAT_0044f7c4 = 1;
  DAT_0044f7c0 = 1;
  DAT_0044f7bc = 1;
  DAT_0044f7b8 = 1;
  DAT_0044f78c = 1;
  DAT_0044f7b0 = 1;
  DAT_0044f7ac = 1;
  DAT_0044f788 = 1;
  DAT_0044f780 = 1;
  DAT_0044f77c = 1;
  DAT_0044f784 = 1;
  DAT_0044f778 = 1;
  DAT_0045ea18 = 0;
  DAT_0045ea24 = 0;
  DAT_0045eb48 = 0;
  DAT_0045eb0c = 0;
  DAT_0045eab0 = 0;
  DAT_0045ea80 = 0;
  DAT_0045eb44 = 0;
  DAT_0045eae0 = 0;
  DAT_0045eb40 = 0;
  DAT_0045ead4 = 0;
  DAT_0045eb30 = 0;
  DAT_0045eb2c = 0;
  DAT_0045eb20 = 0;
  DAT_0045eb1c = 0;
  DAT_0045eb04 = 0;
  DAT_0045eafc = 0;
  DAT_0045eaf8 = 0;
  DAT_0045eaf4 = 0;
  DAT_0045eabc = 0;
  DAT_0045eab8 = 0;
  DAT_0045ead0 = 0;
  DAT_0045eac4 = 0;
  DAT_0045eaac = 0;
  DAT_0045eaa8 = 0;
  DAT_0045eaa4 = 0;
  DAT_0045eaa0 = 0;
  DAT_0045ea84 = 0;
  DAT_0045ea60 = 0;
  DAT_0045ea64 = 0;
  DAT_0045ea30 = 0;
  DAT_0045ea48 = 0;
  DAT_0045ea38 = 0;
  DAT_0045ea2c = 0;
  DAT_0045ea0c = 0;
  DAT_0045ebec = 1;
  DAT_0045f930 = 0;
  DAT_0045ebf0 = 1;
  DAT_0045eba0 = 0;
  DAT_0045fc40 = DAT_0045fc3c;
  DAT_0045fc4c = DAT_0045fc48;
  DAT_0045fc50 = 0;
  FUN_00439317();
  FUN_0043055e();
  FUN_0041fa17();
  FUN_00421052();
  FUN_0042fe46();
  FUN_00433b90();
  uVar2 = -(uint)(DAT_0044f790 != '\0') & 0xfffffffe;
  DAT_0045fb98 = uVar2 + 3;
  if ((*(uint *)(*(int *)(DAT_0044f8dc + 0x24) + 0x30) & 1) == 0) {
    *(int *)(DAT_0044f8dc + 0x1c) = DAT_0045fb98;
    DAT_0045fb9c = DAT_0045fb98;
  }
  else {
    DAT_0045fb9c = uVar2 + 2;
  }
  PTR_DAT_0044f97c = PTR_DAT_0044f978;
  FUN_004375e6();
  FUN_004314ab();
  DAT_0045f630 = 0;
  if (DAT_0045f8fc == 0) {
    DAT_0045f8fc = 1;
  }
  else {
    DAT_0045f8fc = 2;
  }
  return;
}


/* ==== FUN_00405611 @ 00405611 ==== */

void FUN_00405611(void)

{
  bool bVar1;
  int local_1c;
  int local_18;
  int local_14;
  undefined *local_10;
  int *local_c;
  undefined *local_8;
  
  bVar1 = false;
  DAT_0045fb9c = (-(uint)(DAT_0044f790 != '\0') & 0xfffffffe) + 2;
  for (local_8 = PTR_DAT_0044f980; local_8 != (undefined *)0x0;
      local_8 = *(undefined **)(local_8 + 0x8c)) {
    *(uint *)(local_8 + 0xc) = -(uint)((*(uint *)(local_8 + 0xc) & 8) != 0) & 8;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) | -(uint)(DAT_0044f794 != '\0') & 0x10000;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) | -(uint)(DAT_0044f798 != '\0') & 0x20000;
    for (local_1c = *(int *)(local_8 + 0x10); local_1c != 0; local_1c = *(int *)(local_1c + 0xc)) {
      *(bool *)(local_1c + 9) = DAT_0044f790 != '\0';
    }
    memset(local_8 + 0x14,0,0x10);
    for (local_14 = 0; local_14 < 2; local_14 = local_14 + 1) {
      for (local_18 = 0; local_18 < 2; local_18 = local_18 + 1) {
        *(undefined4 *)(local_8 + local_18 * 0x10 + local_14 * 0x20 + 0x28) = 0;
        *(undefined4 *)(local_8 + local_18 * 0x10 + local_14 * 0x20 + 0x24) = 0;
        *(undefined4 *)(local_8 + local_18 * 0x10 + local_14 * 0x20 + 0x2c) = 0;
        *(undefined4 *)(local_8 + local_18 * 0x10 + local_14 * 0x20 + 0x30) = 0;
      }
    }
    for (local_c = *(int **)(local_8 + 100); local_c != (int *)0x0; local_c = (int *)local_c[0xb]) {
      if ((*(uint *)(local_c[9] + 0x30) & 0x400) == 0) {
        *(int *)(local_c[9] + 0x18) = *(int *)(local_c[9] + 0x10) - *(int *)(local_c[9] + 8);
        if (*(int *)(local_c[9] + 0x18) < 0) {
          local_10 = (undefined *)0xffff;
          if (*local_c == 0x1c) {
            local_10 = (&PTR_DAT_0044ed44)[local_c[1]];
          }
          *(uint *)(local_c[9] + 0x18) = *(uint *)(local_c[9] + 0x18) & (uint)local_10;
        }
        if ((local_c[3] & 0xfU) == 0) {
          if ((local_c[5] & 0x200U) != 0) {
            *(int *)(local_c[9] + 0x18) = *(int *)(local_c[9] + 0x18) / 3;
          }
        }
        else {
          *(int *)(local_c[9] + 0x18) =
               *(int *)(local_c[9] + 0x18) /
               (int)((local_c[3] >> 4) / (int)(local_c[3] & 0xfU) +
                    (local_c[3] >> 4 & (uint)((local_c[3] & 1U) == 0)));
        }
      }
      if (*local_c == 3) {
        *(int *)(local_c[9] + 0x18) = *(int *)(local_c[9] + 0x18) << 1;
      }
      *(undefined4 *)(local_c[9] + 0x10) = *(undefined4 *)(local_c[9] + 8);
      if (((*(int *)(local_c[9] + 0x18) == 0) && (local_c[8] == 0)) &&
         (*(int *)(local_c[9] + 0x2c) == 0)) {
        if (((local_c != DAT_0044f8dc) || (DAT_0044f790 == '\0')) || (bVar1)) {
          *(uint *)(local_c[9] + 0x30) = *(uint *)(local_c[9] + 0x30) | 1;
        }
        else {
          bVar1 = true;
          DAT_0045fb9c = DAT_0045fb9c + 1;
        }
      }
      else {
        DAT_0045fb9c = DAT_0045fb9c + 1;
      }
    }
    *(undefined **)(local_8 + 0x88) = local_8;
    *(undefined4 *)(local_8 + 0x74) = *(undefined4 *)(local_8 + 0x70);
  }
  DAT_0045fb98 = DAT_0045fb9c;
  for (local_14 = 0; local_14 < 6; local_14 = local_14 + 1) {
    *(undefined4 *)(&DAT_0045f874 + local_14 * 8) = 0;
    *(undefined4 *)(&DAT_0045f870 + local_14 * 8) = 0;
    *(undefined4 *)(&DAT_0044f83c + local_14 * 8) = 0xffff;
    *(undefined4 *)(&DAT_0044f838 + local_14 * 8) = 0xffff;
    if (local_14 == 4) {
      uRam0044f85c = 0x1fffff;
      uRam0044f858 = 0x1fffff;
    }
  }
  return;
}


/* ==== FUN_004059f6 @ 004059f6 ==== */

void FUN_004059f6(void)

{
  if (PTR_DAT_0044f978 != &DAT_0044f878) {
    while (PTR_DAT_0044f978 != &DAT_0044f878) {
      FUN_00435924();
    }
  }
  if (DAT_0045ebc4 != 0) {
    FUN_0040e572();
  }
  if (DAT_0045ea80 != '\0') {
    FUN_00410100();
  }
  if (DAT_0045ea98 == '\0') {
    FUN_00405f74(DAT_0045fc5c);
    DAT_0045fc60 = 0;
    DAT_0045fc5c = (int *)0x0;
    FUN_00420fd6();
    DAT_0045fc68 = 0;
    DAT_0045fc64 = 0;
  }
  FUN_00421052();
  DAT_0045fb78 = 0;
  FUN_004361d3();
  FUN_00434f48();
  FUN_004375e6();
  FUN_00433b90();
  if (DAT_0045ea4c == '\0') {
    FUN_00439547();
  }
  if ((DAT_0045fcac != (undefined *)0x0) && (DAT_0045fcac != &DAT_0045a470)) {
    fclose(DAT_0045fcac);
    DAT_0045fcac = (undefined *)0x0;
    if (DAT_0045f858 != (void *)0x0) {
      free(DAT_0045f858);
      DAT_0045f858 = (void *)0x0;
    }
  }
  if (DAT_0045eb94 != (void *)0x0) {
    fclose(DAT_0045eb94);
    DAT_0045eb94 = (void *)0x0;
    if (DAT_0045eb90 != (undefined *)0x0) {
      FUN_004398b5(DAT_0045eb90);
      DAT_0045eb90 = (undefined *)0x0;
    }
  }
  FUN_00439547();
  FUN_0043055e();
  FUN_0041fa17();
  FUN_00439431();
  FUN_004361d3();
  FUN_00439686();
  FUN_00439431();
  FUN_00439724();
  FUN_004393b2();
  FUN_004392a1();
  FUN_0041bdc0();
  DAT_0045fc78 = 0;
  DAT_0045fc7c = 0;
  FUN_0043d1e8();
  return;
}


/* ==== FUN_00405b98 @ 00405b98 ==== */

void __cdecl FUN_00405b98(int param_1)

{
  if (PTR_DAT_0044f978 != &DAT_0044f878) {
    if (param_1 == 0) {
      FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00451914);
    }
    while (PTR_DAT_0044f978 != &DAT_0044f878) {
      FUN_00435924();
    }
  }
  if (DAT_0045ebc4 != 0) {
    FUN_00413085((uint *)s_Unexpected_end_of_file___missing_0045193c);
    FUN_0040e572();
  }
  if (DAT_0045ea80 != '\0') {
    FUN_00413085((uint *)s_Unexpected_end_of_file___missing_00451964);
    FUN_00410100();
  }
  if (DAT_0045ea98 == '\0') {
    FUN_00405f74(DAT_0045fc5c);
    FUN_00420fd6();
    DAT_0045fc60 = 0;
    DAT_0045fc5c = (int *)0x0;
    DAT_0045fc68 = 0;
    DAT_0045fc64 = 0;
  }
  FUN_00421052();
  DAT_0045fb78 = 0;
  FUN_00434f48();
  if (DAT_0045fca8 != (undefined *)0x0) {
    if (param_1 == 0) {
      FUN_004212f9();
    }
    if (DAT_0045fca8 != &DAT_0045a470) {
      fclose(DAT_0045fca8);
      DAT_0045fca8 = (undefined *)0x0;
    }
    if ((((DAT_0045eb84 != 0) || ((DAT_0045eb18 != '\0' && (DAT_0045eb88 != 0)))) &&
        (DAT_0045f854 != (char *)0x0)) && (DAT_0045eb1c == '\0')) {
      remove(DAT_0045f854);
      FUN_004398b5(DAT_0045f854);
      DAT_0045f854 = (char *)0x0;
    }
  }
  FUN_004375e6();
  FUN_00433b90();
  if (param_1 == 0) {
    if (DAT_0045ea4c == '\0') {
      FUN_00439547();
    }
    FUN_0041d23b();
  }
  if ((DAT_0045fcac != (undefined *)0x0) && (DAT_0045fcac != &DAT_0045a470)) {
    fclose(DAT_0045fcac);
    DAT_0045fcac = (undefined *)0x0;
    if (DAT_0045f858 != (void *)0x0) {
      free(DAT_0045f858);
      DAT_0045f858 = (void *)0x0;
    }
  }
  if (DAT_0045ea98 != '\0') {
    FUN_00439547();
    FUN_0043055e();
    FUN_0041fa17();
    FUN_00439431();
    FUN_004361d3();
    FUN_00439686();
    FUN_00439724();
    FUN_004393b2();
    FUN_004392a1();
  }
  FUN_0043cbfb();
  FUN_0043d422();
  FUN_00437837();
  return;
}


/* ==== FUN_00405db4 @ 00405db4 ==== */

void __cdecl FUN_00405db4(int param_1)

{
  if (param_1 == 2) {
    if (DAT_0045ea98 == '\0') {
      fprintf(PTR_DAT_0044f9a4,s__s__Interrupted_0045198c,PTR_s_asm56000_0044e084);
    }
    if (DAT_0045eb18 != '\0') {
      DAT_0045eb84 = DAT_0045eb84 + DAT_0045eb88;
    }
    if (DAT_0045eb84 == 0) {
      exit(-1);
    }
    else {
      exit(DAT_0045eb84);
    }
  }
  else if (param_1 == 8) {
    signal(8,FUN_00405db4);
    if (DAT_0045fca0 != '\0') {
      FUN_00413085((uint *)s_Arithmetic_exception_00451a00);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_00465b80,-1);
    }
    FUN_00412fa0((uint *)s_Arithmetic_exception_004519e8);
  }
  else if (param_1 == 0xb) {
    fprintf(PTR_DAT_0044f9a4,s__s__Fatal_segmentation_or_protec_004519a0,PTR_s_asm56000_0044e084);
    if (DAT_0045eb18 != '\0') {
      DAT_0045eb84 = DAT_0045eb84 + DAT_0045eb88;
    }
    if (DAT_0045eb84 == 0) {
      exit(-1);
    }
    else {
      exit(DAT_0045eb84);
    }
  }
  return;
}


