/* dsplnk: 24 functions from DSPLNK */

/* ==== main @ 00401a20 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl main(int argc,char **argv,char **envp)

{
  char cVar1;
  char *s;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  
  signal(2,FUN_0040303c);
  signal(0xb,FUN_0040303c);
  signal(8,FUN_0040303c);
  s = thunk_FUN_0042e468(*argv);
  cVar1 = strrchr(s,0x2e);
  if ((undefined1 *)CONCAT31(extraout_var,cVar1) != (undefined1 *)0x0) {
    *(undefined1 *)CONCAT31(extraout_var,cVar1) = 0;
  }
  cVar1 = getenv(s_DSPLNKOPT_00457f28);
  if ((CONCAT31(extraout_var_00,cVar1) != 0) ||
     (iVar2 = FUN_0040287b('f',argc,(int *)argv), iVar2 != 0)) {
    argc = FUN_0040343e(argc,(int *)&argv);
  }
  iVar2 = FUN_0040287b('c',argc,(int *)argv);
  DAT_0046120c = iVar2 != 0;
  iVar2 = FUN_0040287b('q',argc,(int *)argv);
  DAT_00461264 = iVar2 != 0;
  iVar2 = FUN_0040294c('e',argc,(int *)argv);
  if (iVar2 != 0) {
    FUN_00402a24((int)argv,iVar2);
  }
  PTR_s_dsplnk_00457ed0 = s;
  sscanf(s_6_3_7_00457ee0,s__ld__ld__ld_00453a64,&DAT_00461fdc,&DAT_00461fe0,&DAT_00461fe4);
  if ((DAT_0046120c == '\0') && (DAT_00461264 == '\0')) {
    fprintf(PTR_DAT_00457c08,s_DSP__s_Version__s__s_00453a70,s_Linker_00457ed8,s_6_3_7_00457ee0,
            s__C__Copyright_Motorola__Inc__198_00457ee8);
  }
  if ((DAT_004611f4 == '\0') && (argc < 2)) {
    FUN_00401dfe();
  }
  _DAT_00461d44 = FUN_00404bba(&DAT_00461d48,&DAT_00461d58);
  DAT_00461f34 = &DAT_0045d650;
  PTR_DAT_00457bf0 = (undefined *)FUN_00403172(argc,(int)argv);
  FUN_00402b44();
  DAT_00461da4 = argv;
  DAT_00461da0 = argc;
  if ((DAT_004611f4 == '\0') && (FUN_00402017(), DAT_00461da0 == 0)) {
    thunk_FUN_0040a0ca(s_Missing_object_filename_00453a88);
  }
  if (DAT_0046125c != '\0') {
    fprintf(PTR_DAT_00457c08,s__s__Beginning_pass_1_00453aa0,PTR_s_dsplnk_00457ed0);
  }
  thunk_FUN_00414110();
  thunk_FUN_0040d4e0();
  FUN_00402cd2();
  DAT_00461da4 = argv;
  DAT_00461da0 = argc;
  if (DAT_004611f4 == '\0') {
    FUN_00402017();
  }
  if (DAT_00461f38 == 0) {
    FUN_00403385();
  }
  if (DAT_0046125c != '\0') {
    fprintf(PTR_DAT_00457c08,s__s__Beginning_pass_2_00453ab8,PTR_s_dsplnk_00457ed0);
  }
  thunk_FUN_00414110();
  thunk_FUN_00402e52(0);
  if ((((DAT_00461fa0 == 0x2cb) && (DAT_00461248 == '\0')) && (DAT_0046120c != '\0')) &&
     (DAT_00461d64 != (uint *)0x0)) {
    if (((char)*DAT_00461d64 == DAT_00453ad0) &&
       (iVar2 = strcmp((char *)DAT_00461d64,&DAT_00453ad4), iVar2 == 0)) {
      thunk_FUN_00409d88(s_Object_file_redirected_to_stdout_00453ad8);
    }
    else {
      FUN_00401fe0(DAT_00461d64,(uint *)&stack0xfffffdec);
      strcat(&stack0xfffffdec,&DAT_00453b34);
      if (DAT_0046125c != '\0') {
        fprintf(PTR_DAT_00457c08,s__s__Creating_ELF_debug_informati_00453b3c,PTR_s_dsplnk_00457ed0,
                &stack0xfffffdec);
      }
      iVar2 = thunk_FUN_00432799((LPCSTR)DAT_00461d64,&stack0xfffffdec);
      if (iVar2 != 0) {
        thunk_FUN_00409d88(s_Failed_to_create_debug_informati_00453b6c);
      }
    }
  }
  if (DAT_00461234 != '\0') {
    DAT_004612ec = DAT_004612ec + DAT_004612f0;
  }
  if (DAT_004611ec != 0) {
    fprintf(&DAT_0045d650,s__s__errors___d_warnings___d_00453b94,PTR_s_dsplnk_00457ed0,DAT_004612ec,
            DAT_004612f0);
  }
  exit(DAT_004612ec);
  return DAT_004612ec;
}


/* ==== FUN_00401dfe @ 00401dfe ==== */

void FUN_00401dfe(void)

{
  if ((DAT_0046120c != '\0') || (DAT_00461264 != '\0')) {
    fprintf(PTR_DAT_00457c08,s_DSP__s_Version__s__s_00453bb4,s_Linker_00457ed8,s_6_3_7_00457ee0,
            s__C__Copyright_Motorola__Inc__198_00457ee8);
  }
  fprintf(PTR_DAT_00457c08,s_Usage___s___a____b_<objfil>______00453bcc,PTR_s_dsplnk_00457ed0);
  fprintf(PTR_DAT_00457c08,s_where__00453cb4);
  fprintf(PTR_DAT_00457c08,s__a_auto_align_buffers__n_ignore_s_00453cbc);
  fprintf(PTR_DAT_00457c08,s__b_object_file__o_memory_origin_00453cfc);
  fprintf(PTR_DAT_00457c08,s_<objfil>_object_file_name_<mem>_m_00453d38);
  fprintf(PTR_DAT_00457c08,s__ea_append_to_error_file_<ctr>_l_00453d78);
  fprintf(PTR_DAT_00457c08,s_<errfil>_error_file_name_<map>_m_00453dbc);
  fprintf(PTR_DAT_00457c08,s__ew_write_to_error_file_<origin>_00453e00);
  fprintf(PTR_DAT_00457c08,s_<errfil>_error_file_name__p_libr_00453e40);
  fprintf(PTR_DAT_00457c08,s__f_command_file_<lpath>_library_p_00453e7c);
  fprintf(PTR_DAT_00457c08,s_<argfil>_command_file_name__q_su_00453ec4);
  fprintf(PTR_DAT_00457c08,s__g_debug_mode__r_memory_control_f_00453f00);
  fprintf(PTR_DAT_00457c08,s__i_incremental_link_<memfil>_con_00453f40);
  fprintf(PTR_DAT_00457c08,s__l_library_file__u_define_symbol_00453f88);
  fprintf(PTR_DAT_00457c08,s_<library>_library_file_name_<sym_00453fc4);
  fprintf(PTR_DAT_00457c08,s__m_map_file__v_verbose_mode_00454008);
  fprintf(PTR_DAT_00457c08,s_<mapfil>_map_file_name__x_linker_00454044);
  fprintf(PTR_DAT_00457c08,s_<opt>_linker_option_argument_00454080);
  fprintf(PTR_DAT_00457c08,s_<lnkfil>_link_input_file_name_s__004540cc);
  fprintf(PTR_DAT_00457c08,s__s_command_environment_variable__00454110,s_Linker_00457ed8,
          s_DSPLNKOPT_00457f28);
  exit(-1);
  return;
}


/* ==== FUN_00401fe0 @ 00401fe0 ==== */

void __cdecl FUN_00401fe0(uint *param_1,uint *param_2)

{
  char cVar1;
  undefined3 extraout_var;
  
  strcpy((char *)param_2,(char *)param_1);
  cVar1 = strrchr((char *)param_2,0x2e);
  if ((undefined1 *)CONCAT31(extraout_var,cVar1) != (undefined1 *)0x0) {
    *(undefined1 *)CONCAT31(extraout_var,cVar1) = 0;
  }
  return;
}


/* ==== FUN_00402017 @ 00402017 ==== */

void FUN_00402017(void)

{
  char cVar1;
  undefined *extraout_EAX;
  uint uVar2;
  undefined *extraout_EAX_00;
  int iVar3;
  undefined3 extraout_var;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar4;
  bool bVar5;
  int local_3c;
  uint local_38;
  int *local_30;
  char *local_2c;
  int local_28 [4];
  undefined4 *local_18;
  int local_14;
  int local_10;
  undefined1 *local_c;
  char *local_8;
  
  local_c = (undefined1 *)0x0;
  local_14 = 0;
  local_2c = (char *)0x0;
  local_8 = (char *)0x0;
  FUN_004040eb(0,0,(char *)0x0);
  iVar4 = DAT_00461da8;
  while ((DAT_00461da8 = iVar4, local_14 == 0 &&
         (local_10 = FUN_004040eb(DAT_00461da0,(int)DAT_00461da4,
                                  s_AaB_b_CcE__e__F_f_GgIiL_l_M_m_Nn_00457f38), local_10 != -1))) {
    if (__mb_cur_max < 2) {
      local_38 = *(ushort *)(_pctype + local_10 * 2) & 1;
    }
    else {
      local_38 = _isctype(local_10,1);
    }
    if (local_38 == 0) {
      local_3c = local_10;
    }
    else {
      local_3c = tolower(local_10);
    }
    iVar4 = DAT_00461da8;
    switch(local_3c) {
    case 0x61:
      if (DAT_00461248 == '\0') {
        DAT_0046126c = '\x01';
      }
      break;
    case 0x62:
      if ((DAT_00461dac == (uint *)0x0) && (DAT_00461248 != '\0')) {
        thunk_FUN_0040a0ca(s_Default_object_file_not_allowed_i_00454138);
      }
      iVar4 = DAT_00461da8;
      if (DAT_00461294 != 1) {
        if (DAT_00461f38 == (undefined *)0x0) {
          bVar5 = DAT_00461dac == (uint *)0x0;
          if (bVar5) {
            DAT_00461dac = (uint *)PTR_DAT_00457bf0;
          }
          strcpy(&DAT_00461528,(char *)DAT_00461dac);
          if (bVar5) {
            thunk_FUN_004032e9((uint *)&DAT_00457fe0);
          }
          uVar2 = strlen(&DAT_00461528);
          local_2c = (char *)thunk_FUN_0042e170(uVar2 + 1);
          strcpy(local_2c,&DAT_00461528);
          DAT_00461d64 = local_2c;
          if ((DAT_00461528 == DAT_00454198) &&
             (iVar4 = strcmp(&DAT_00461528,&DAT_0045419c), iVar4 == 0)) {
            DAT_00461f38 = &DAT_0045d650;
          }
          else {
            fopen(&DAT_00461528,&DAT_004541a0);
            DAT_00461f38 = extraout_EAX;
            if (extraout_EAX == (undefined *)0x0) {
              thunk_FUN_0040a0f6(s_Cannot_open_object_file_004541a4,&DAT_00461528);
            }
          }
          FUN_00404c3a(&DAT_00461528,&DAT_004541c4,&DAT_004541bc);
          iVar4 = DAT_00461da8;
        }
        else {
          thunk_FUN_0040a126(s_Duplicate_object_file_specified___0045416c);
          iVar4 = DAT_00461da8;
        }
      }
      break;
    case 99:
      break;
    default:
      thunk_FUN_0040a0ca(s_Illegal_command_line_option_004542cc);
      iVar4 = DAT_00461da8;
      break;
    case 0x65:
      break;
    case 0x66:
      break;
    case 0x67:
      DAT_0046124c = '\x01';
      break;
    case 0x69:
      DAT_00461248 = '\x01';
      break;
    case 0x6c:
      if (DAT_00461294 != 2) {
        local_14 = 1;
        iVar4 = DAT_00461da8 + -1;
        if (**(char **)((int)DAT_00461da4 + (DAT_00461da8 + -1) * 4) != '-') {
          iVar4 = DAT_00461da8 + -2;
        }
      }
      break;
    case 0x6d:
      if (DAT_00461294 != 1) {
        if (DAT_00461f3c == (undefined *)0x0) {
          bVar5 = DAT_00461dac == (uint *)0x0;
          if (bVar5) {
            DAT_00461dac = (uint *)PTR_DAT_00457bf0;
          }
          strcpy(&DAT_00461528,(char *)DAT_00461dac);
          if (bVar5) {
            thunk_FUN_004032e9((uint *)&DAT_004541f4);
          }
          if (DAT_00461260 != '\0') {
            thunk_FUN_00430037(&DAT_00461528);
          }
          strcpy(&DAT_00461730,&DAT_00461528);
          uVar2 = strlen(&DAT_00461528);
          local_8 = (char *)thunk_FUN_0042e170(uVar2 + 1);
          strcpy(local_8,&DAT_00461528);
          if ((DAT_00461528 == DAT_004541fc) &&
             (iVar4 = strcmp(&DAT_00461528,&DAT_00454200), iVar4 == 0)) {
            DAT_00461f3c = &DAT_0045d650;
          }
          else {
            fopen(&DAT_00461528,&DAT_00454204);
            DAT_00461f3c = extraout_EAX_00;
            if (extraout_EAX_00 == (undefined *)0x0) {
              thunk_FUN_0040a0f6(s_Cannot_open_map_file_00454208,&DAT_00461528);
            }
          }
          FUN_00404c3a(&DAT_00461528,&DAT_00454228,&DAT_00454220);
          iVar4 = DAT_00461da8;
        }
        else {
          thunk_FUN_0040a126(s_Duplicate_map_file_specified___i_004541cc);
          iVar4 = DAT_00461da8;
        }
      }
      break;
    case 0x6e:
      DAT_00461214 = 1;
      break;
    case 0x6f:
      DAT_00461d68 = DAT_00461dac;
      iVar3 = thunk_FUN_0042e743(local_28);
      iVar4 = DAT_00461da8;
      if (iVar3 != 0) {
        if ((char)*DAT_00461d68 == '$') {
          DAT_00461d68 = (uint *)((int)DAT_00461d68 + 1);
        }
        local_18 = thunk_FUN_0042c4e2(DAT_00461dcc,local_28,0);
        sscanf((char *)DAT_00461d68,&DAT_00454230,local_18 + 7);
        local_18[2] = local_18[2] | 0x100000;
        iVar4 = DAT_00461da8;
      }
      break;
    case 0x70:
      if (DAT_00461294 != 2) {
        DAT_004611f0 = 1;
        FUN_004044bd(DAT_00461dac);
        DAT_004611f0 = 0;
        iVar4 = DAT_00461da8;
      }
      break;
    case 0x71:
      break;
    case 0x72:
      if (DAT_00461294 != 2) {
        if (DAT_00461f40 == 0) {
          bVar5 = DAT_00461dac == (uint *)0x0;
          if (bVar5) {
            DAT_00461dac = (uint *)PTR_DAT_00457bf0;
          }
          strcpy(&DAT_00461528,(char *)DAT_00461dac);
          if (bVar5) {
            thunk_FUN_004032e9((uint *)&DAT_00454268);
            cVar1 = strrchr(&DAT_00461528,0x2e);
            local_c = (undefined1 *)CONCAT31(extraout_var,cVar1);
          }
          strcpy(&DAT_00461730,&DAT_00461528);
          fopen(&DAT_00461528,&DAT_00454270);
          DAT_00461f40 = extraout_EAX_01;
          if (((extraout_EAX_01 == 0) && (bVar5)) && (local_c != (undefined1 *)0x0)) {
            *local_c = 0;
            thunk_FUN_004032e9((uint *)&DAT_00454274);
            fopen(&DAT_00461528,&DAT_0045427c);
            DAT_00461f40 = extraout_EAX_02;
          }
          iVar4 = DAT_00461da8;
          if (DAT_00461f40 == 0) {
            thunk_FUN_0040a0f6(s_Cannot_open_memory_control_file_00454280,&DAT_00461528);
            iVar4 = DAT_00461da8;
          }
        }
        else {
          thunk_FUN_0040a126(s_Duplicate_memory_control_file_sp_00454234);
          iVar4 = DAT_00461da8;
        }
      }
      break;
    case 0x73:
      DAT_004611ec = 1;
      break;
    case 0x74:
      DAT_00461260 = '\x01';
      break;
    case 0x75:
      if (DAT_00461294 != 2) {
        thunk_FUN_0042cae9(DAT_00461dac,1,0);
        iVar4 = DAT_00461da8;
      }
      break;
    case 0x76:
      DAT_0046125c = 1;
      if (DAT_00461dac != (uint *)0x0) {
        sscanf((char *)DAT_00461dac,&DAT_004542a0,&DAT_00457ba0);
        iVar4 = DAT_00461da8;
      }
      break;
    case 0x78:
      DAT_004611f0 = 1;
      iVar4 = thunk_FUN_00425cf1((char *)DAT_00461dac);
      if (iVar4 == 0) {
        thunk_FUN_0040a0f6(s_Illegal_command_line__X_option_a_004542a4,DAT_00461dac);
      }
      DAT_004611f0 = 0;
      iVar4 = DAT_00461da8;
      break;
    case 0x7a:
      DAT_00461250 = '\x01';
    }
  }
  DAT_00461da0 = DAT_00461da0 - DAT_00461da8;
  DAT_00461da4 = (int *)((int)DAT_00461da4 + DAT_00461da8 * 4);
  if ((DAT_0046124c != '\0') && (DAT_00461250 != '\0')) {
    thunk_FUN_0040a126(s_Options_for_both_debug_and_strip_004542e8);
    DAT_00461250 = '\0';
  }
  if ((DAT_00461248 != '\0') && (DAT_00461250 != '\0')) {
    thunk_FUN_0040a126(s_Strip_not_valid_with_incremental_00454324);
    DAT_00461250 = '\0';
  }
  if ((DAT_00461248 != '\0') && (DAT_0046126c != '\0')) {
    thunk_FUN_0040a126(s_Align_not_valid_with_incremental_00454354);
    DAT_0046126c = '\0';
  }
  if ((local_2c != (char *)0x0) || (local_8 != (char *)0x0)) {
    for (local_30 = DAT_00461da4; *local_30 != 0; local_30 = local_30 + 1) {
      if (((local_2c != (char *)0x0) && (*local_2c == *(char *)*local_30)) &&
         (iVar4 = strcmp(local_2c,(char *)*local_30), iVar4 == 0)) {
        thunk_FUN_0040a0f6(s_Object_file_name_same_as_executa_00454384,local_2c);
      }
      if (((local_8 != (char *)0x0) && (*local_8 == *(char *)*local_30)) &&
         (iVar4 = strcmp(local_8,(char *)*local_30), iVar4 == 0)) {
        thunk_FUN_0040a0f6(s_Object_file_name_same_as_map_fil_004543b4,local_8);
      }
    }
    if (local_8 != (char *)0x0) {
      thunk_FUN_0042e1ce(local_8);
    }
  }
  return;
}


/* ==== FUN_00402871 @ 00402871 ==== */

undefined4 __cdecl FUN_00402871(undefined4 *param_1)

{
  return *param_1;
}


/* ==== FUN_0040287b @ 0040287b ==== */

int __cdecl FUN_0040287b(char param_1,int param_2,int *param_3)

{
  int iVar1;
  int local_c;
  uint local_8;
  
  if (DAT_004611f4 == '\0') {
    do {
      do {
        param_3 = param_3 + 1;
        param_2 = param_2 + -1;
        if (param_2 < 1) goto LAB_00402946;
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
LAB_00402946:
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== FUN_0040294c @ 0040294c ==== */

int __cdecl FUN_0040294c(char param_1,int param_2,int *param_3)

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


/* ==== FUN_00402a24 @ 00402a24 ==== */

void __cdecl FUN_00402a24(int param_1,int param_2)

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
    thunk_FUN_0040a0ca(s_Illegal_command_line__E_option_004543dc);
  }
  if (*(char *)(*(int *)(param_1 + param_2 * 4) + 3) != '\0') {
    thunk_FUN_0040a0ca(s_Invalid_syntax_for_command_line___004543fc);
  }
  local_8 = *(char **)(param_1 + 4 + param_2 * 4);
  if (*local_8 == '-') {
    thunk_FUN_0040a0ca(s_Missing_argument_for_command_lin_00454428);
  }
  if ((PTR_DAT_00457c08 != (undefined *)0x0) && (PTR_DAT_00457c08 != &DAT_0045d670)) {
    fclose(PTR_DAT_00457c08);
  }
  fopen(local_8,local_c);
  PTR_DAT_00457c08 = extraout_EAX;
  if (extraout_EAX == (undefined *)0x0) {
    PTR_DAT_00457c08 = &DAT_0045d670;
    thunk_FUN_0040a0ca(s_Cannot_open_error_file_00454454);
  }
  return;
}


/* ==== FUN_00402b44 @ 00402b44 ==== */

void FUN_00402b44(void)

{
  DAT_00461dbc = DAT_00461db8;
  DAT_004612f0 = 0;
  DAT_004612ec = 0;
  DAT_00457c00 = 0xffffffff;
  DAT_00461e7c = 0;
  DAT_00461318 = 0;
  DAT_00461e98 = (-(uint)(DAT_00461248 != '\0') & 0xfffffffe) + 2;
  DAT_004612d0 = 0;
  DAT_004612cc = 0;
  DAT_004612b4 = 0;
  DAT_004612b0 = 0;
  DAT_0046129c = 0;
  DAT_00461298 = 0;
  DAT_00461ef4 = 0;
  DAT_00457ba4 = 10;
  DAT_00457b74 = 1;
  DAT_00457b80 = 1;
  DAT_00457b7c = 1;
  DAT_00457b78 = 1;
  DAT_00461234 = 0;
  DAT_00461290 = 0;
  DAT_0046128c = 0;
  DAT_00461244 = 0;
  DAT_00461240 = 0;
  DAT_0046123c = 0;
  DAT_0046122c = 0;
  DAT_00461238 = 0;
  DAT_00461230 = 0;
  DAT_00461228 = 0;
  DAT_00457b84 = 1;
  DAT_00461f08 = 0;
  DAT_00461f0c = 0;
  DAT_00461dcc = thunk_FUN_0042c373((uint *)s_DEFAULT_00457f80);
  DAT_00461dd0 = DAT_00461dcc;
  FUN_00404859();
  DAT_00461294 = 1;
  return;
}


/* ==== FUN_00402cd2 @ 00402cd2 ==== */

void FUN_00402cd2(void)

{
  DAT_004611f4 = DAT_004611f8;
  DAT_00461dbc = DAT_00461db8;
  DAT_00457c00 = 0xffffffff;
  DAT_00461e7c = 0;
  DAT_00461318 = 0;
  DAT_00461310 = 1;
  DAT_00461de0 = 0;
  DAT_00461ddc = 0;
  DAT_00461d80 = 0;
  DAT_00461d70 = 0;
  DAT_004612d0 = 0;
  DAT_004612cc = 0;
  DAT_004612b4 = 0;
  DAT_004612b0 = 0;
  DAT_00461298 = 0;
  DAT_00461ef4 = 0;
  DAT_00457ba4 = 10;
  DAT_00457b74 = 1;
  DAT_00457b80 = 1;
  DAT_00457b7c = 1;
  DAT_00457b78 = 1;
  DAT_00461234 = 0;
  DAT_00461290 = 0;
  DAT_0046128c = 0;
  DAT_00461244 = 0;
  DAT_00461240 = 0;
  DAT_0046123c = 0;
  DAT_0046122c = 0;
  DAT_00461238 = 0;
  DAT_00461230 = 0;
  DAT_00461228 = 0;
  DAT_00457b84 = 1;
  DAT_00461f08 = -(uint)(DAT_00461f04 != 0) & DAT_00461f04;
  DAT_00461f0c = 0;
  DAT_00461294 = 2;
  return;
}


/* ==== FUN_00402e52 @ 00402e52 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_00402e52(int param_1)

{
  int *piVar1;
  
  thunk_FUN_0043a394();
  if (DAT_00461dc4 == (uint *)0x0) {
    if (DAT_00461248 != '\0') {
      _DAT_0046c348 = -1;
    }
  }
  else {
    DAT_00461dbc = 0;
    DAT_00461d68 = DAT_00461dc4;
    piVar1 = thunk_FUN_0040a370();
    if (piVar1 != (int *)0x0) {
      DAT_004612fc = thunk_FUN_00407988((int)piVar1);
      DAT_00457ba8 = piVar1[7];
    }
    if (DAT_00461248 != '\0') {
      _DAT_0046c348 = thunk_FUN_00429716(DAT_00461dc4);
    }
  }
  DAT_00461dbc = 0;
  if ((DAT_00461248 == '\0') && (DAT_004612e0 != 0)) {
    DAT_004612ec = DAT_004612ec + DAT_004612e0;
    thunk_FUN_00421791();
  }
  thunk_FUN_0040df91();
  if (DAT_00461f38 != (undefined *)0x0) {
    if (param_1 == 0) {
      thunk_FUN_0042785f();
    }
    if (DAT_00461f38 != &DAT_0045d650) {
      fclose(DAT_00461f38);
      DAT_00461f38 = (undefined *)0x0;
    }
    if ((((DAT_004612ec != 0) || ((DAT_00461234 != '\0' && (DAT_004612f0 != 0)))) &&
        (DAT_00461d64 != (char *)0x0)) && (DAT_0046123c == '\0')) {
      remove(DAT_00461d64);
      thunk_FUN_0042e1ce(DAT_00461d64);
      DAT_00461d64 = (char *)0x0;
    }
  }
  thunk_FUN_0042d519();
  thunk_FUN_0042d5a4();
  if ((DAT_00461238 != '\0') && (param_1 == 0)) {
    thunk_FUN_0041df05();
  }
  if (DAT_00461f3c != (undefined *)0x0) {
    if (param_1 == 0) {
      thunk_FUN_0041d7d0();
    }
    if (DAT_00461f3c != &DAT_0045d650) {
      fclose(DAT_00461f3c);
      DAT_00461f3c = (undefined *)0x0;
    }
  }
  thunk_FUN_0042d10b();
  thunk_FUN_0042d175();
  thunk_FUN_0042d229();
  thunk_FUN_0042d3ef();
  thunk_FUN_0042d484();
  thunk_FUN_0042d73f();
  thunk_FUN_0041c470();
  return;
}


/* ==== FUN_0040303c @ 0040303c ==== */

void __cdecl FUN_0040303c(int param_1)

{
  if (param_1 == 2) {
    if (DAT_0046120c == '\0') {
      fprintf(PTR_DAT_00457c08,s__s__Interrupted_0045446c,PTR_s_dsplnk_00457ed0);
    }
    if (DAT_00461234 != '\0') {
      DAT_004612ec = DAT_004612ec + DAT_004612f0;
    }
    if (DAT_004612ec == 0) {
      exit(-1);
    }
    else {
      exit(DAT_004612ec);
    }
  }
  else if (param_1 == 8) {
    signal(8,FUN_0040303c);
    if (DAT_00461f30 != '\0') {
      thunk_FUN_00409a25(s_Arithmetic_exception_004544e0);
                    /* WARNING: Subroutine does not return */
      longjmp(&DAT_0046c300,-1);
    }
    thunk_FUN_004098b0(s_Arithmetic_exception_004544c8);
  }
  else if (param_1 == 0xb) {
    fprintf(PTR_DAT_00457c08,s__s__Fatal_segmentation_or_protec_00454480,PTR_s_dsplnk_00457ed0);
    if (DAT_00461234 != '\0') {
      DAT_004612ec = DAT_004612ec + DAT_004612f0;
    }
    if (DAT_004612ec == 0) {
      exit(-1);
    }
    else {
      exit(DAT_004612ec);
    }
  }
  return;
}


/* ==== FUN_00403172 @ 00403172 ==== */

uint * __cdecl FUN_00403172(int param_1,int param_2)

{
  bool bVar1;
  char cVar2;
  char *s;
  uint uVar3;
  uint *dst;
  undefined3 extraout_var;
  int local_20;
  int local_1c;
  uint local_18;
  char *local_8;
  uint *puVar4;
  
  bVar1 = false;
  FUN_004040eb(0,0,(char *)0x0);
  do {
    local_1c = FUN_004040eb(param_1,param_2,s_AaB_b_CcE__e__F_f_GgIiL_l_M_m_Nn_00457f38);
    if (local_1c == -1) goto LAB_0040320a;
    if (__mb_cur_max < 2) {
      local_18 = *(ushort *)(_pctype + local_1c * 2) & 1;
    }
    else {
      local_18 = _isctype(local_1c,1);
    }
    if (local_18 != 0) {
      local_1c = tolower(local_1c);
    }
  } while (local_1c != 0x6c);
  bVar1 = true;
LAB_0040320a:
  if (bVar1) {
    local_20 = DAT_00461da8 + -1;
  }
  else {
    local_20 = DAT_00461da8;
  }
  if (param_1 - local_20 < 1) {
    thunk_FUN_0040a0ca(s_Cannot_open_object_file_004544f8);
  }
  if (bVar1) {
    local_8 = *(char **)(param_2 + -4 + DAT_00461da8 * 4);
  }
  else {
    local_8 = *(char **)(param_2 + DAT_00461da8 * 4);
  }
  if (*local_8 == '-') {
    local_8 = local_8 + 2;
  }
  s = thunk_FUN_0042e468(local_8);
  uVar3 = strlen(s);
  dst = (uint *)thunk_FUN_0042e170(uVar3 + 1);
  strcpy((char *)dst,s);
  cVar2 = strrchr((char *)dst,0x2e);
  puVar4 = (uint *)CONCAT31(extraout_var,cVar2);
  if ((puVar4 != (uint *)0x0) && (puVar4 != dst)) {
    *(char *)puVar4 = '\0';
  }
  return dst;
}


/* ==== FUN_004032e9 @ 004032e9 ==== */

uint __cdecl FUN_004032e9(uint *param_1)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  undefined3 extraout_var;
  int iVar5;
  char *local_10;
  
  bVar1 = 0;
  pcVar3 = thunk_FUN_0042e468(&DAT_00461528);
  uVar4 = strlen(&DAT_00461528);
  cVar2 = strrchr(&DAT_00461528,0x2e);
  local_10 = (char *)CONCAT31(extraout_var,cVar2);
  if ((local_10 == (char *)0x0) || (local_10 < pcVar3)) {
    local_10 = &DAT_00461528 + uVar4;
  }
  if (*local_10 == (char)*param_1) {
    iVar5 = strcmp(local_10,(char *)param_1);
    if (iVar5 == 0) goto LAB_00403376;
  }
  strcpy(local_10,(char *)param_1);
  bVar1 = 1;
LAB_00403376:
  return -(uint)bVar1 & (uint)local_10;
}


/* ==== FUN_00403385 @ 00403385 ==== */

void FUN_00403385(void)

{
  uint uVar1;
  int extraout_EAX;
  
  if (DAT_00461248 != '\0') {
    thunk_FUN_0040a0ca(s_Default_object_file_not_allowed_i_00454510);
  }
  strcpy(&DAT_00461528,PTR_DAT_00457bf0);
  thunk_FUN_004032e9((uint *)&DAT_00457fe0);
  uVar1 = strlen(&DAT_00461528);
  DAT_00461d64 = (char *)thunk_FUN_0042e170(uVar1 + 1);
  strcpy(DAT_00461d64,&DAT_00461528);
  fopen(&DAT_00461528,&DAT_00454544);
  DAT_00461f38 = extraout_EAX;
  if (extraout_EAX == 0) {
    thunk_FUN_0040a0f6(s_Cannot_open_object_file_00454548,&DAT_00461528);
  }
  FUN_00404c3a(&DAT_00461528,&DAT_00454568,&DAT_00454560);
  return;
}


/* ==== FUN_0040343e @ 0040343e ==== */

int __cdecl FUN_0040343e(int param_1,int *param_2)

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
  
  puVar2 = (undefined4 *)thunk_FUN_0042e170(8);
  *puVar2 = *(undefined4 *)*param_2;
  puVar2[1] = 0;
  local_10 = 1;
  local_14 = puVar2;
  cVar1 = getenv(s_DSPLNKOPT_00457f28);
  local_8 = (uint *)CONCAT31(extraout_var,cVar1);
  if (local_8 != (uint *)0x0) {
    iVar3 = FUN_004036b4(local_8,(int *)&local_14);
    local_10 = local_10 + iVar3;
  }
  if (DAT_004611f4 == '\0') {
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
        if (local_28 != 0x66) goto LAB_004035fb;
        if (*(char *)((int)local_8 + 2) == '\0') {
          local_1c = local_1c + 1;
          if (param_1 <= local_1c) {
            thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_00454574,&DAT_00454570);
          }
          local_8 = *(uint **)(*param_2 + local_1c * 4);
          if (((local_8 == (uint *)0x0) || ((char)*local_8 == '\0')) || ((char)*local_8 == '-')) {
            thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_004545a0,&DAT_0045459c);
          }
        }
        else {
          local_8 = (uint *)((int)local_8 + 2);
        }
        iVar3 = FUN_004039e5((LPCSTR)local_8,(int *)&local_14);
        local_10 = local_10 + iVar3;
      }
      else {
LAB_004035fb:
        local_c = (undefined4 *)thunk_FUN_0042e170(8);
        *local_c = local_8;
        local_c[1] = 0;
        local_14[1] = local_c;
        local_10 = local_10 + 1;
        local_14 = local_c;
      }
    }
  }
  else {
    iVar3 = FUN_004039e5(&DAT_00461528,(int *)&local_14);
    local_10 = local_10 + iVar3;
  }
  iVar3 = thunk_FUN_0042e170(local_10 * 4 + 4);
  local_14 = puVar2;
  for (local_1c = 0; puVar2 = local_14, local_1c < local_10; local_1c = local_1c + 1) {
    *(undefined4 *)(iVar3 + local_1c * 4) = *local_14;
    local_c = local_14;
    local_14 = (undefined4 *)local_14[1];
    thunk_FUN_0042e1ce((undefined *)puVar2);
  }
  *(undefined4 *)(iVar3 + local_1c * 4) = 0;
  *param_2 = iVar3;
  return local_10;
}


/* ==== FUN_004036b4 @ 004036b4 ==== */

int __cdecl FUN_004036b4(uint *param_1,int *param_2)

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
LAB_004036c7:
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
            thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_004545cc,&DAT_004545c8);
          }
        }
        else {
          local_c = (uint *)((int)local_c + 2);
        }
        iVar4 = FUN_004039e5((LPCSTR)local_c,param_2);
        local_14 = local_14 + iVar4;
        *(char *)local_8 = cVar1;
        goto LAB_004036c7;
      }
    }
    if ((char)*local_c != '\0') {
      piVar3 = (int *)thunk_FUN_0042e170(8);
      iVar4 = thunk_FUN_0042e170(local_1c + 1);
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


/* ==== FUN_004039e5 @ 004039e5 ==== */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int __cdecl FUN_004039e5(LPCSTR param_1,int *param_2)

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
  fopen(param_1,&DAT_004545f4);
  if (stream == (int *)0x0) {
    thunk_FUN_0040a0f6(s_Cannot_open_command_file_004545f8,param_1);
  }
LAB_00403a29:
  do {
    if ((stream[3] & 0x10U) != 0) {
LAB_004040d2:
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
    if ((stream[3] & 0x10U) != 0) goto LAB_004040d2;
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
              thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_00454618,&DAT_00454614);
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
              goto LAB_00403a29;
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
              thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_00454644,&DAT_00454640);
            }
          }
          else {
            local_8 = local_20a;
          }
          iVar2 = FUN_004039e5(local_8,param_2);
          local_210 = local_210 + iVar2;
          goto LAB_00403a29;
        }
      }
      if (local_20c != '\0') {
        local_c = (int *)thunk_FUN_0042e170(8);
        iVar2 = thunk_FUN_0042e170(local_218 + 1);
        *local_c = iVar2;
        strcpy((char *)*local_c,&local_20c);
        local_c[1] = 0;
        *(int **)(*param_2 + 4) = local_c;
        *param_2 = (int)local_c;
        local_210 = local_210 + 1;
      }
      local_20c = '\0';
      goto LAB_00403a29;
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


/* ==== FUN_004040eb @ 004040eb ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_004040eb(int param_1,int param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  undefined3 extraout_var;
  uint uVar3;
  char local_10 [4];
  char *local_c;
  char local_8;
  
  if (((param_1 == 0) && (param_2 == 0)) && (param_3 == (char *)0x0)) {
    DAT_00461da8 = 0;
    DAT_00461130 = (char *)0x0;
  }
  DAT_00461dac = (char *)0x0;
  _DAT_00461db0 = 0;
  if ((DAT_00461130 == (char *)0x0) || (*DAT_00461130 == '\0')) {
    if (DAT_00461da8 == 0) {
      DAT_00461da8 = 1;
    }
    if (((param_1 <= DAT_00461da8) || (**(char **)(param_2 + DAT_00461da8 * 4) != '-')) ||
       (*(char *)(*(int *)(param_2 + DAT_00461da8 * 4) + 1) == '\0')) {
      DAT_00461dac = (char *)0x0;
      _DAT_00461db0 = 0;
      return -1;
    }
    iVar2 = strcmp(*(char **)(param_2 + DAT_00461da8 * 4),&DAT_0045466c);
    if (iVar2 == 0) {
      DAT_00461da8 = DAT_00461da8 + 1;
      return -1;
    }
    DAT_00461130 = (char *)(*(int *)(param_2 + DAT_00461da8 * 4) + 1);
    DAT_00461da8 = DAT_00461da8 + 1;
  }
  local_8 = *DAT_00461130;
  DAT_00461130 = DAT_00461130 + 1;
  cVar1 = strchr(param_3,(int)local_8);
  local_c = (char *)CONCAT31(extraout_var,cVar1);
  if (((local_c == (char *)0x0) || (local_8 == ':')) || (local_8 == '?')) {
    sprintf(local_10,&DAT_00454670,(int)local_8);
    thunk_FUN_0040a0f6(s_Illegal_command_line_option_00454674,local_10);
  }
  local_c = (char *)((int)local_c + 1);
  if (*local_c == ':') {
    if (*DAT_00461130 == '\0') {
      if (DAT_00461da8 < param_1) {
        DAT_00461dac = *(char **)(param_2 + DAT_00461da8 * 4);
        DAT_00461da8 = DAT_00461da8 + 1;
      }
      else {
        sprintf(local_10,&DAT_00454690,(int)local_8);
        thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_00454694,local_10);
      }
    }
    else {
      DAT_00461dac = DAT_00461130;
      DAT_00461130 = (char *)0x0;
    }
    local_c = local_c + 1;
    if (*local_c == ':') {
      if (DAT_00461da8 < param_1) {
        _DAT_00461db0 = *(undefined4 *)(param_2 + DAT_00461da8 * 4);
        DAT_00461da8 = DAT_00461da8 + 1;
      }
      else {
        sprintf(local_10,&DAT_004546bc,(int)local_8);
        thunk_FUN_0040a0f6(s_Missing_command_line_option_argu_004546c0,local_10);
      }
    }
  }
  else if (*local_c == '?') {
    if (*DAT_00461130 == '\0') {
      if (DAT_00461da8 < param_1) {
        if (**(char **)(param_2 + DAT_00461da8 * 4) == '-') {
          if (*(char *)(*(int *)(param_2 + DAT_00461da8 * 4) + 1) == '\0') {
            DAT_00461dac = *(char **)(param_2 + DAT_00461da8 * 4);
            DAT_00461da8 = DAT_00461da8 + 1;
          }
        }
        else if ((DAT_00461da8 + 1 < param_1) &&
                (**(char **)(param_2 + 4 + DAT_00461da8 * 4) == '-')) {
          if (__mb_cur_max < 2) {
            uVar3 = *(ushort *)
                     (_pctype + *(char *)(*(int *)(param_2 + 4 + DAT_00461da8 * 4) + 1) * 2) & 1;
          }
          else {
            uVar3 = _isctype((int)*(char *)(*(int *)(param_2 + 4 + DAT_00461da8 * 4) + 1),1);
          }
          if (uVar3 == 0) {
            iVar2 = (int)*(char *)(*(int *)(param_2 + 4 + DAT_00461da8 * 4) + 1);
          }
          else {
            iVar2 = tolower((int)*(char *)(*(int *)(param_2 + 4 + DAT_00461da8 * 4) + 1));
          }
          if (iVar2 != 0x6c) {
            DAT_00461dac = *(char **)(param_2 + DAT_00461da8 * 4);
            DAT_00461da8 = DAT_00461da8 + 1;
          }
        }
      }
    }
    else {
      DAT_00461dac = DAT_00461130;
      DAT_00461130 = (char *)0x0;
    }
  }
  return (int)local_8;
}


/* ==== FUN_004044bd @ 004044bd ==== */

undefined4 __cdecl FUN_004044bd(uint *param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  piVar1 = DAT_00461f10;
  piVar2 = DAT_00461f14;
  if (DAT_00461294 != 2) {
    strcpy(&DAT_00461528,(char *)param_1);
    FUN_0040456e();
    piVar2 = (int *)thunk_FUN_0042e170(8);
    uVar3 = strlen(&DAT_00461528);
    iVar4 = thunk_FUN_0042e170(uVar3 + 1);
    *piVar2 = iVar4;
    piVar2[1] = 0;
    strcpy((char *)*piVar2,&DAT_00461528);
    piVar1 = piVar2;
    if (DAT_00461f10 != (int *)0x0) {
      DAT_00461f14[1] = (int)piVar2;
      piVar1 = DAT_00461f10;
    }
  }
  DAT_00461f14 = piVar2;
  DAT_00461f10 = piVar1;
  return 1;
}


/* ==== FUN_0040456e @ 0040456e ==== */

void FUN_0040456e(void)

{
  uint uVar1;
  char *local_8;
  
  uVar1 = strlen(&DAT_00461528);
  if (0 < (int)uVar1) {
    local_8 = &DAT_00461527 + uVar1;
    if ((*local_8 != '\\') && (*local_8 != ':')) {
      local_8 = &DAT_00461528 + uVar1;
      *local_8 = '\\';
    }
    local_8[1] = '\0';
  }
  return;
}


/* ==== FUN_004045d0 @ 004045d0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004045d0(undefined *param_1)

{
  uint local_10;
  int local_c;
  undefined **local_8;
  
  for (local_8 = &PTR_s_DSP56000_00457c18; (*local_8 != (undefined *)0x0 && (param_1 != local_8[1]))
      ; local_8 = local_8 + 0x13) {
  }
  if (*local_8 == (undefined *)0x0) {
    thunk_FUN_004098b0(s_Invalid_object_file_for_target_p_004546e8);
  }
  DAT_00461f44 = (int)(local_8 + -0x115f06) / 0x4c;
  DAT_00461fc0 = &PTR_s_DSP56000_00457c18 + DAT_00461f44 * 0x13;
  DAT_00461f48 = *DAT_00461fc0;
  DAT_00461fa0 = (&DAT_00457c1c)[DAT_00461f44 * 0x13];
  DAT_00461f4c = (&DAT_00457c20)[DAT_00461f44 * 0x13];
  DAT_00461f50 = DAT_00461f4c << 1;
  DAT_00461f54 = DAT_00461f4c << 2;
  DAT_00461f58 = DAT_00461f4c << 3;
  DAT_00461f5c = DAT_00461f4c << 4;
  DAT_00461f64 = DAT_00461f4c << 1;
  DAT_00461f6c = (&DAT_00457c34)[DAT_00461f44 * 0x13];
  DAT_00461f70 = (&DAT_00457c38)[DAT_00461f44 * 0x13];
  _DAT_00457c0c = (&DAT_00457c3c)[DAT_00461f44 * 0x13];
  _DAT_00461f94 = (&DAT_00457c40)[DAT_00461f44 * 0x13];
  DAT_00461f74 = (&DAT_00457c24)[DAT_00461f44 * 0x13];
  DAT_00461f78 = (&DAT_00457c28)[DAT_00461f44 * 0x13];
  DAT_00461f7c = (&DAT_00457c2c)[DAT_00461f44 * 0x13];
  DAT_00461f84 = ~DAT_00461f7c + 1;
  DAT_00461f88 = ~DAT_00461f7c * 2 + 1 & DAT_00461f74;
  DAT_00461f8c = ~DAT_00461f80 + 1;
  DAT_00461f90 = ~DAT_00461f80 * 2 + 1 & DAT_00461f74;
  DAT_00461fa4 = (&DAT_00457c44)[DAT_00461f44 * 0x13];
  _DAT_00461fa8 = (&DAT_00457c48)[DAT_00461f44 * 0x13];
  _DAT_00461fac = (&DAT_00457c4c)[DAT_00461f44 * 0x13];
  _DAT_00461fb0 = (&DAT_00457c50)[DAT_00461f44 * 0x13];
  DAT_00461fb4 = (&PTR_s__06lX_00457c54)[DAT_00461f44 * 0x13];
  DAT_00461fb8 = (&PTR_s__06lX_00457c60)[DAT_00461f44 * 0x13];
  DAT_00461fbc = (&PTR_s__04lX_00457c58)[DAT_00461f44 * 0x13];
  DAT_00461f9c = ~DAT_00461f70 & DAT_00461f6c;
  DAT_00461f98 = ~DAT_00461f9c;
  DAT_00461f60 = DAT_00461f4c;
  _DAT_00461f68 = DAT_00461f50;
  if (DAT_00461dcc != 0) {
    for (local_c = *(int *)(DAT_00461dcc + 8); local_c != 0; local_c = *(int *)(local_c + 0x38)) {
      if (*(int *)(local_c + 0xc) == 0x1c) {
        local_10 = DAT_00461f78;
      }
      else {
        local_10 = DAT_00461f74;
      }
      *(uint *)(local_c + 0x20) = local_10;
    }
  }
  if (DAT_00461f44 == 5) {
    DAT_00461288 = 1;
  }
  return;
}


/* ==== FUN_00404859 @ 00404859 ==== */

void FUN_00404859(void)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  int local_6c [2];
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_44 = 0x240;
  local_3c = 4;
  local_40 = 4;
  local_34 = 0;
  local_38 = 0;
  local_30 = 0;
  local_20 = 0;
  local_24 = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  uVar2 = strlen(&DAT_00454714);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,&DAT_00454718);
  local_6c[0] = CONCAT31(extraout_var,cVar1);
  local_64 = 0;
  local_60 = 0x7ff00000;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(&DAT_0045471c);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,&DAT_00454724);
  local_6c[0] = CONCAT31(extraout_var_00,cVar1);
  local_60 = 0;
  local_64 = 0;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(&DAT_0045472c);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,&DAT_00454730);
  local_6c[0] = CONCAT31(extraout_var_01,cVar1);
  local_64 = 1;
  local_60 = 0x7ff00000;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(&DAT_00454734);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,&DAT_0045473c);
  local_6c[0] = CONCAT31(extraout_var_02,cVar1);
  local_60 = 0;
  local_64 = 1;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(&DAT_00454744);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,&DAT_0045474c);
  local_6c[0] = CONCAT31(extraout_var_03,cVar1);
  local_64 = 0;
  local_60 = 0x7ff00000;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(s__Huge_00454754);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,s__Huge_0045475c);
  local_6c[0] = CONCAT31(extraout_var_04,cVar1);
  local_60 = 0;
  local_64 = 0;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(&DAT_00454764);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,&DAT_0045476c);
  local_6c[0] = CONCAT31(extraout_var_05,cVar1);
  local_64 = 1;
  local_60 = 0;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  uVar2 = strlen(s__Tiny_00454774);
  pcVar3 = (char *)thunk_FUN_0042e170(uVar2 + 1);
  cVar1 = strcpy(pcVar3,s__Tiny_0045477c);
  local_6c[0] = CONCAT31(extraout_var_06,cVar1);
  local_60 = 0;
  local_64 = 1;
  thunk_FUN_0042c6c1(local_6c);
  thunk_FUN_0042e1ce(pcVar3);
  return;
}


/* ==== FUN_00404bba @ 00404bba ==== */

void __cdecl FUN_00404bba(undefined1 *param_1,undefined1 *param_2)

{
  int *extraout_EAX;
  long local_8;
  
  local_8 = time((long *)0x0);
  localtime(&local_8);
  sprintf(param_1,s__02d__02d__02d_00454784,extraout_EAX[5],extraout_EAX[4] + 1,extraout_EAX[3]);
  sprintf(param_2,s__02d__02d__02d_00454794,extraout_EAX[2],extraout_EAX[1],*extraout_EAX);
  thunk_FUN_0043084b(extraout_EAX);
  return;
}


