/* ==== main @ 00401000 ==== */

int __cdecl main(int argc,char **argv,char **envp)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  undefined *extraout_EAX;
  undefined **extraout_EAX_00;
  
  bVar1 = false;
  signal(2,FUN_00404b31);
  signal(0xb,FUN_00404b31);
  iVar2 = FUN_00404594('q',argc,argv);
  DAT_004134b0 = iVar2 != 0;
  if (!(bool)DAT_004134b0) {
    fprintf(&DAT_004109d0,s__s__s__s_0040efbc,s_DSP_COFF_File_Dump_Utility_0040e078,
            s_Version_6_3_0040e098,s__C__Copyright_Motorola__Inc__199_0040e0a8);
  }
  while (iVar2 = FUN_00404670(argc,(int)argv,s_CcD_d_FfHhLlOoQqRrSsTtVvXx_0040efc8), iVar2 != -1) {
    if ((!bVar1) && (pcVar3 = _strchr(s_DdQqVvXx_0040efe4,iVar2), pcVar3 == (char *)0x0)) {
      FUN_0040131b();
      bVar1 = true;
    }
    if (__mb_cur_max < 2) {
      uVar4 = *(ushort *)(_pctype + iVar2 * 2) & 1;
    }
    else {
      uVar4 = _isctype(iVar2,1);
    }
    if (uVar4 != 0) {
      iVar2 = tolower(iVar2);
    }
    switch(iVar2) {
    case 99:
      DAT_0040e0e8 = 1;
      break;
    case 100:
      DAT_004134a8 = DAT_00413488;
      break;
    default:
      FUN_00404b95();
      break;
    case 0x66:
      DAT_0040e0ec = 1;
      break;
    case 0x68:
      DAT_0040e0f0 = 1;
      break;
    case 0x6c:
      DAT_0040e0f4 = 1;
      break;
    case 0x6f:
      DAT_0040e0f8 = 1;
      break;
    case 0x71:
      DAT_004134b0 = 1;
      break;
    case 0x72:
      DAT_0040e0fc = 1;
      break;
    case 0x73:
      DAT_0040e100 = 1;
      break;
    case 0x74:
      DAT_0040e104 = 1;
      break;
    case 0x76:
      DAT_004134ac = 1;
      break;
    case 0x78:
      DAT_00413490 = 1;
    }
  }
  if (DAT_004134a8 == (char *)0x0) {
    DAT_004134a4 = &DAT_004109b0;
  }
  else {
    fopen(DAT_004134a8,&DAT_0040eff0);
    DAT_004134a4 = extraout_EAX;
    if (extraout_EAX == (undefined *)0x0) {
      FUN_00404ce9(s_cannot_open_output_file__s_0040eff4,DAT_004134a8);
    }
    FUN_00404836(DAT_004134a8,&DAT_0040f018,&DAT_0040f010);
  }
  if (argc <= DAT_0041348c) {
    FUN_00404b95();
  }
  if (*argv[DAT_0041348c] == '-') {
    DAT_004134a0 = s_stdin_0040f020;
    DAT_0041349c = &PTR_DAT_00410990;
    FUN_00401375();
  }
  else {
    while (DAT_0041348c < argc) {
      DAT_004134a0 = argv[DAT_0041348c];
      DAT_0041348c = DAT_0041348c + 1;
      fopen(DAT_004134a0,&DAT_0040f028);
      DAT_0041349c = extraout_EAX_00;
      if (extraout_EAX_00 == (undefined **)0x0) {
        FUN_00404ce9(s_cannot_open_input_file__s_0040f02c,DAT_004134a0);
      }
      FUN_00401375();
      fclose(DAT_0041349c);
    }
  }
  exit(0);
  return 0;
}


/* ==== FUN_0040131b @ 0040131b ==== */

void FUN_0040131b(void)

{
  DAT_0040e104 = 0;
  DAT_0040e100 = 0;
  DAT_0040e0fc = 0;
  DAT_0040e0f8 = 0;
  DAT_0040e0f4 = 0;
  DAT_0040e0f0 = 0;
  DAT_0040e0ec = 0;
  DAT_0040e0e8 = 0;
  return;
}


/* ==== FUN_00401375 @ 00401375 ==== */

void FUN_00401375(void)

{
  FUN_004013f5();
  FUN_0040156e();
  if (DAT_0040e0ec != '\0') {
    FUN_004016b1();
  }
  if (DAT_0040e0f8 != '\0') {
    FUN_00401b2f();
  }
  if ((((DAT_0040e0f0 != '\0') || (DAT_0040e0fc != '\0')) || (DAT_0040e0f4 != '\0')) ||
     (DAT_0040e100 != '\0')) {
    FUN_00402332();
  }
  if (DAT_0040e104 != '\0') {
    FUN_00402f34();
  }
  if (DAT_0040e0e8 != '\0') {
    FUN_004044a4();
  }
  return;
}


/* ==== FUN_004013f5 @ 004013f5 ==== */

void FUN_004013f5(void)

{
  uint uVar1;
  
  uVar1 = FUN_00404840((char *)&DAT_00413880,0x1c,1,DAT_0041349c);
  if (uVar1 != 1) {
    FUN_00404ce9(s_cannot_read_file_header_0040f048);
  }
  if (((((DAT_00413880 != 0x2c5) && (DAT_00413880 != 0x2c6)) && (DAT_00413880 != 0x2c7)) &&
      ((DAT_00413880 != 0x2c8 && (DAT_00413880 != 0x2c9)))) &&
     ((DAT_00413880 != 0x2ca && ((DAT_00413880 != 0x2cb && (DAT_00413880 != 0x2cc)))))) {
    FUN_00404ce9(s_invalid_object_file_format_0040f060);
  }
  DAT_00413828 = DAT_00413884;
  DAT_004138d8 = DAT_00413890;
  DAT_004138e0 = DAT_0041388c;
  DAT_0041387c = (uint)((DAT_00413898 & 1) != 0);
  DAT_00413494 = (uint)(DAT_00413894 != 0x28);
  DAT_00413498 = (uint)((DAT_00413898 & 0x20000) != 0);
  if (DAT_00413894 != 0) {
    if (DAT_0041387c == 0) {
      uVar1 = FUN_00404840((char *)&DAT_004138a0,DAT_00413894,1,DAT_0041349c);
      if (uVar1 != 1) {
        FUN_00404ce9(s_cannot_read_linker_file_header_0040f0a0);
      }
    }
    else {
      uVar1 = FUN_00404840((char *)&DAT_00413840,DAT_00413894,1,DAT_0041349c);
      if (uVar1 != 1) {
        FUN_00404ce9(s_cannot_read_optional_file_header_0040f07c);
      }
    }
  }
  DAT_004138e4 = DAT_00413894 + 0x1c;
  return;
}


/* ==== FUN_0040156e @ 0040156e ==== */

void FUN_0040156e(void)

{
  int iVar1;
  uint uVar2;
  char *extraout_EAX;
  int offset;
  
  if (DAT_004138d8 != 0) {
    offset = DAT_004138e0 + DAT_004138d8 * 0x20;
    iVar1 = fseek(DAT_0041349c,offset,0);
    if (iVar1 != 0) {
      FUN_00404ce9(s_cannot_seek_to_string_table_leng_0040f0c0);
    }
    uVar2 = FUN_00404840((char *)&DAT_0041389c,4,1,DAT_0041349c);
    if ((uVar2 != 1) && ((DAT_0041349c[3] & 0x10U) == 0)) {
      FUN_00404ce9(s_cannot_read_string_table_length_0040f0e4);
    }
    if ((DAT_0041349c[3] & 0x10U) == 0) {
      if (DAT_0041389c != 0) {
        DAT_0041389c = DAT_0041389c - 4;
        if ((int)DAT_0041389c < 0) {
          FUN_00404ce9(s_invalid_string_table_length_0040f104);
        }
        malloc(DAT_0041389c);
        DAT_004138dc = extraout_EAX;
        iVar1 = fseek(DAT_0041349c,offset + 4,0);
        if (iVar1 != 0) {
          FUN_00404ce9(s_cannot_seek_to_string_table_0040f120);
        }
        uVar2 = FUN_00405520(DAT_004138dc,DAT_0041389c,1,DAT_0041349c);
        if (uVar2 != 1) {
          FUN_00404ce9(s_cannot_read_string_table_0040f13c);
        }
      }
    }
    else {
      DAT_0041389c = 0;
    }
  }
  return;
}


/* ==== FUN_004016b1 @ 004016b1 ==== */

void FUN_004016b1(void)

{
  int *piVar1;
  undefined *va0;
  char *local_8;
  
  FUN_00404caf(DAT_004134a4,s_FILE_HEADER_0040f158);
  if (DAT_00413490 == 0) {
    FUN_00404caf(DAT_004134a4,s_FOR_FILE__s_0040f16c,DAT_004134a0);
  }
  else {
    FUN_00404caf(DAT_004134a4,&DAT_0040f168);
  }
  FUN_00404caf(DAT_004134a4,&DAT_0040f17c,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_f_magic___0_lo_0040f180,DAT_00413880);
  if (DAT_004134ac == '\0') {
    FUN_00404caf(DAT_004134a4,&DAT_0040f190);
  }
  else {
    local_8 = (char *)0x0;
    switch(DAT_00413880) {
    case 0x2c5:
      local_8 = s_DSP56000_0040f194;
      break;
    case 0x2c6:
      local_8 = s_DSP96000_0040f1a0;
      break;
    case 0x2c7:
      local_8 = s_DSP56100_0040f1ac;
      break;
    case 0x2c8:
      local_8 = s_DSP56300_0040f1b8;
      break;
    case 0x2c9:
      local_8 = s_DSP56800_0040f1c4;
      break;
    case 0x2ca:
      local_8 = s_DSP56600_0040f1d0;
      break;
    case 0x2cb:
      local_8 = &DAT_0040f1dc;
      break;
    case 0x2cc:
      local_8 = s_DSP56700_0040f1e0;
    }
    if (local_8 == (char *)0x0) {
      FUN_00404caf(DAT_004134a4,&DAT_0040f1ec);
    }
    else {
      FUN_00404caf(DAT_004134a4,s___s__0040f1f0,local_8);
    }
  }
  FUN_00404caf(DAT_004134a4,&DAT_0040f1f8,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_f_nscns____lu_0040f1fc,DAT_00413884);
  if ((DAT_004134ac == '\0') || (DAT_00413490 != 0)) {
    FUN_00404caf(DAT_004134a4,&DAT_0040f20c,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_f_timdat___0x_08lX_0040f210,DAT_00413888);
  }
  else {
    FUN_00404caf(DAT_004134a4,&DAT_0040f224,&DAT_0040e108);
    piVar1 = FUN_004048f0(&DAT_00413888);
    va0 = FUN_004057b0(piVar1);
    FUN_00404caf(DAT_004134a4,s_f_timdat____s_0040f228,va0);
  }
  FUN_00404caf(DAT_004134a4,&DAT_0040f238,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_f_symptr____ld_0040f23c,DAT_0041388c);
  FUN_00404caf(DAT_004134a4,&DAT_0040f24c,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_f_nsyms____ld_0040f250,DAT_00413890);
  FUN_00404caf(DAT_004134a4,&DAT_0040f260,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_f_opthdr____lu_0040f264,DAT_00413894);
  if (DAT_004134ac == '\0') {
    FUN_00404caf(DAT_004134a4,&DAT_0040f274,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_f_flags___0_lo__0x_lX__0040f278,DAT_00413898,DAT_00413898);
  }
  else {
    FUN_00404caf(DAT_004134a4,&DAT_0040f294,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_f_flags___0040f298);
    if (DAT_00413898 == 0) {
      FUN_00404caf(DAT_004134a4,s_NONE_0040f2a4);
    }
    else {
      if ((DAT_00413898 & 1) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_RELFLG_0040f2ac);
      }
      if ((DAT_00413898 & 2) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_EXEC_0040f2b8);
      }
      if ((DAT_00413898 & 4) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_LNNO_0040f2c0);
      }
      if ((DAT_00413898 & 8) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_LSYMS_0040f2c8);
      }
      if ((DAT_00413898 & 0x10) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_MINMAL_0040f2d4);
      }
      if ((DAT_00413898 & 0x20) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_UPDATE_0040f2e0);
      }
      if ((DAT_00413898 & 0x10000) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_CC_0040f2ec);
      }
      if ((DAT_00413898 & 0x20000) != 0) {
        FUN_00404caf(DAT_004134a4,s_F_SDI_0040f2f4);
      }
      FUN_00404caf(DAT_004134a4,&DAT_0040f2fc);
    }
  }
  return;
}


/* ==== FUN_00401b2f @ 00401b2f ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00401b2f(void)

{
  if (DAT_00413894 != 0) {
    if (DAT_0041387c == 0) {
      FUN_00404caf(DAT_004134a4,s_LINKER_HEADER_0040f4dc);
      if (DAT_00413490 == 0) {
        FUN_00404caf(DAT_004134a4,s_FOR_FILE__s_0040f4f0,DAT_004134a0);
      }
      else {
        FUN_00404caf(DAT_004134a4,&DAT_0040f4ec);
      }
      FUN_00404caf(DAT_004134a4,&DAT_0040f500,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_modsize____ld_0040f504,DAT_004138a0);
      FUN_00404caf(DAT_004134a4,&DAT_0040f518,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_datasize____ld_0040f51c,DAT_004138a4);
      if (DAT_004134ac == '\0') {
        FUN_00404caf(DAT_004134a4,&DAT_0040f530,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_endstr____ld_0040f534,DAT_004138a8);
      }
      else if (DAT_004138a8 < 0) {
        FUN_00404caf(DAT_004134a4,&DAT_0040f548,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_endstr___NONE_0040f54c);
      }
      else {
        if ((DAT_004138a8 < 4) || (DAT_0041389c < DAT_004138a8)) {
          FUN_00404ce9(s_invalid_string_table_offset_for_e_0040f560);
        }
        FUN_00404caf(DAT_004134a4,&DAT_0040f598,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_endstr____s_0040f59c,DAT_004138dc + -4 + DAT_004138a8);
      }
      FUN_00404caf(DAT_004134a4,&DAT_0040f5b0,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_secnt____ld_0040f5b4,DAT_004138ac);
      FUN_00404caf(DAT_004134a4,&DAT_0040f5c8,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_ctrcnt____ld_0040f5cc,DAT_004138b0);
      FUN_00404caf(DAT_004134a4,&DAT_0040f5e0,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_relocnt____ld_0040f5e4,DAT_004138b4);
      FUN_00404caf(DAT_004134a4,&DAT_0040f5f8,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_lnocnt____ld_0040f5fc,DAT_004138b8);
      FUN_00404caf(DAT_004134a4,&DAT_0040f610,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_bufcnt____ld_0040f614,DAT_004138bc);
      FUN_00404caf(DAT_004134a4,&DAT_0040f628,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_ovlcnt____ld_0040f62c,DAT_004138c0);
      if (DAT_00413494 != 0) {
        FUN_00404caf(DAT_004134a4,&DAT_0040f640,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_majver____ld_0040f644,
                     ~-(uint)(DAT_00413490 != 0) & _DAT_004138c4);
        FUN_00404caf(DAT_004134a4,&DAT_0040f658,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_minver____ld_0040f65c,
                     ~-(uint)(DAT_00413490 != 0) & _DAT_004138c8);
        FUN_00404caf(DAT_004134a4,&DAT_0040f670,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_revno____ld_0040f674,~-(uint)(DAT_00413490 != 0) & _DAT_004138cc
                    );
      }
      if (DAT_00413498 != 0) {
        FUN_00404caf(DAT_004134a4,&DAT_0040f688,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_sditot____ld_0040f68c,DAT_004138d4);
      }
    }
    else {
      FUN_00404caf(DAT_004134a4,s_OPTIONAL_HEADER_0040f300);
      if (DAT_00413490 == 0) {
        FUN_00404caf(DAT_004134a4,s_FOR_FILE__s_0040f318,DAT_004134a0);
      }
      else {
        FUN_00404caf(DAT_004134a4,&DAT_0040f314);
      }
      FUN_00404caf(DAT_004134a4,&DAT_0040f328,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_magic___0_lo_0040f32c,DAT_00413840);
      FUN_00404caf(DAT_004134a4,&DAT_0040f340,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_vstamp____ld_0040f344,DAT_00413844);
      FUN_00404caf(DAT_004134a4,&DAT_0040f358,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_tsize____ld_0040f35c,DAT_00413848);
      FUN_00404caf(DAT_004134a4,&DAT_0040f370,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_dsize____ld_0040f374,DAT_0041384c);
      FUN_00404caf(DAT_004134a4,&DAT_0040f388,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_bsize____ld_0040f38c,DAT_00413850);
      FUN_00404caf(DAT_004134a4,&DAT_0040f3a0,&DAT_0040e108);
      if ((((((DAT_004134ac == '\0') || (DAT_00413858 < 0)) || (DAT_0040e600 <= DAT_00413858)) ||
           ((DAT_00413860 < 0 || (DAT_0040e600 <= DAT_00413860)))) ||
          ((DAT_00413868 < 0 || ((DAT_0040e600 <= DAT_00413868 || (DAT_00413870 < 0)))))) ||
         ((DAT_0040e600 <= DAT_00413870 || ((DAT_00413878 < 0 || (DAT_0040e600 <= DAT_00413878))))))
      {
        FUN_00404caf(DAT_004134a4,s_entry___0x_08lX_0x_08lX_0040f3a4,DAT_00413858,DAT_00413854);
        FUN_00404caf(DAT_004134a4,&DAT_0040f3c4,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_text_start___0x_08lX_0x_08lX_0040f3c8,DAT_00413860,DAT_0041385c)
        ;
        FUN_00404caf(DAT_004134a4,&DAT_0040f3e8,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_data_start___0x_08lX_0x_08lX_0040f3ec,DAT_00413868,DAT_00413864)
        ;
        FUN_00404caf(DAT_004134a4,&DAT_0040f40c,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_text_end___0x_08lX_0x_08lX_0040f410,DAT_00413870,DAT_0041386c);
        FUN_00404caf(DAT_004134a4,&DAT_0040f430,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_data_end___0x_08lX_0x_08lX_0040f434,DAT_00413878,DAT_00413874);
      }
      else {
        FUN_00404caf(DAT_004134a4,s_entry____s0x_08lX_0040f454,(&PTR_DAT_0040e178)[DAT_00413858],
                     DAT_00413854);
        FUN_00404caf(DAT_004134a4,&DAT_0040f46c,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_text_start____s0x_08lX_0040f470,
                     (&PTR_DAT_0040e178)[DAT_00413860],DAT_0041385c);
        FUN_00404caf(DAT_004134a4,&DAT_0040f488,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_data_start____s0x_08lX_0040f48c,
                     (&PTR_DAT_0040e178)[DAT_00413868],DAT_00413864);
        FUN_00404caf(DAT_004134a4,&DAT_0040f4a4,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_text_end____s0x_08lX_0040f4a8,(&PTR_DAT_0040e178)[DAT_00413870],
                     DAT_0041386c);
        FUN_00404caf(DAT_004134a4,&DAT_0040f4c0,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_data_end____s0x_08lX_0040f4c4,(&PTR_DAT_0040e178)[DAT_00413878],
                     DAT_00413874);
      }
    }
  }
  return;
}


/* ==== FUN_00402332 @ 00402332 ==== */

void FUN_00402332(void)

{
  int iVar1;
  uint uVar2;
  int local_40 [13];
  int local_c;
  int local_8;
  
  for (local_c = 0; local_c < DAT_00413828; local_c = local_c + 1) {
    iVar1 = fseek(DAT_0041349c,DAT_004138e4,0);
    if (iVar1 != 0) {
      FUN_00404ce9(s_cannot_seek_to_section_headers_0040f6a0);
    }
    uVar2 = FUN_00404840((char *)local_40,0x34,1,DAT_0041349c);
    if (uVar2 != 1) {
      FUN_00404ce9(s_cannot_read_section_headers_0040f6c0);
    }
    if (local_40[0] != 0) {
      FUN_0040487a((undefined1 *)local_40,4,2);
    }
    DAT_004138e4 = DAT_004138e4 + 0x34;
    local_8 = local_c + 1;
    if (DAT_0040e0f0 != '\0') {
      FUN_0040244d(local_40,local_8);
    }
    if (DAT_0040e100 != '\0') {
      FUN_00402a0e(local_40,local_8);
    }
    if (DAT_0040e0fc != '\0') {
      FUN_00402bd9(local_40,local_8);
    }
    if (DAT_0040e0f4 != '\0') {
      FUN_00402d7e(local_40,local_8);
    }
  }
  return;
}


/* ==== FUN_0040244d @ 0040244d ==== */

void __cdecl FUN_0040244d(int *param_1)

{
  int *va0;
  undefined4 in_stack_00000008;
  
  va0 = FUN_004029bc(param_1);
  FUN_00404caf(DAT_004134a4,s_SECTION_HEADER_FOR_SECTION__s____0040f6dc,va0,in_stack_00000008);
  if (DAT_00413490 == 0) {
    FUN_00404caf(DAT_004134a4,s_IN_FILE__s_0040f704,DAT_004134a0);
  }
  else {
    FUN_00404caf(DAT_004134a4,&DAT_0040f700);
  }
  FUN_00404caf(DAT_004134a4,&DAT_0040f714,&DAT_0040e108);
  if ((((DAT_004134ac == '\0') || (param_1[3] < 0)) || (DAT_0040e600 <= param_1[3])) ||
     ((param_1[5] < 0 || (DAT_0040e600 <= param_1[5])))) {
    FUN_00404caf(DAT_004134a4,s_s_paddr___0x_08lX_0x_08lX_0040f718,param_1[3],param_1[2]);
    FUN_00404caf(DAT_004134a4,&DAT_0040f738,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_s_vaddr___0x_08lX_0x_08lX_0040f73c,param_1[5],param_1[4]);
  }
  else {
    FUN_00404caf(DAT_004134a4,s_s_paddr____s0x_08lX_0040f75c,(&PTR_DAT_0040e178)[param_1[3]],
                 param_1[2]);
    FUN_00404caf(DAT_004134a4,&DAT_0040f774,&DAT_0040e108);
    if ((param_1[0xc] & 0x400U) == 0) {
      FUN_00404caf(DAT_004134a4,s_s_vaddr____s0x_08lX_0040f78c,(&PTR_DAT_0040e178)[param_1[5]],
                   param_1[4]);
    }
    else {
      FUN_00404caf(DAT_004134a4,s_s_vaddr____ld_0040f778,param_1[4]);
    }
  }
  FUN_00404caf(DAT_004134a4,&DAT_0040f7a4,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_s_size____ld_0040f7a8,param_1[6]);
  FUN_00404caf(DAT_004134a4,&DAT_0040f7bc,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_s_scnptr____ld_0040f7c0,param_1[7]);
  FUN_00404caf(DAT_004134a4,&DAT_0040f7d4,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_s_relptr____ld_0040f7d8,param_1[8]);
  FUN_00404caf(DAT_004134a4,&DAT_0040f7ec,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_s_lnnoptr____ld_0040f7f0,param_1[9]);
  FUN_00404caf(DAT_004134a4,&DAT_0040f804,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_s_nreloc____lu_0040f808,param_1[10]);
  FUN_00404caf(DAT_004134a4,&DAT_0040f81c,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,s_s_nlnno____lu_0040f820,param_1[0xb]);
  if (DAT_004134ac == '\0') {
    FUN_00404caf(DAT_004134a4,&DAT_0040f834,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_s_flags___0_lo__0x_lX__0040f838,param_1[0xc],param_1[0xc]);
  }
  else {
    FUN_00404caf(DAT_004134a4,&DAT_0040f854,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_s_flags___0040f858);
    if ((param_1[0xc] & 1U) == 0) {
      if ((param_1[0xc] & 2U) == 0) {
        if ((param_1[0xc] & 4U) == 0) {
          if ((param_1[0xc] & 8U) == 0) {
            if ((param_1[0xc] & 0x10U) == 0) {
              FUN_00404caf(DAT_004134a4,s_STYP_REG_0040f8a8);
              if ((param_1[0xc] & 0x80U) == 0) {
                if ((param_1[0xc] & 0x20U) == 0) {
                  if ((param_1[0xc] & 0x40U) != 0) {
                    FUN_00404caf(DAT_004134a4,s_STYP_DATA_0040f8cc);
                  }
                }
                else {
                  FUN_00404caf(DAT_004134a4,s_STYP_TEXT_0040f8c0);
                }
              }
              else {
                FUN_00404caf(DAT_004134a4,s_STYP_BSS_0040f8b4);
              }
              if ((param_1[0xc] & 0x400U) != 0) {
                FUN_00404caf(DAT_004134a4,s_STYP_BLOCK_0040f8d8);
              }
              if ((param_1[0xc] & 0x800U) != 0) {
                FUN_00404caf(DAT_004134a4,s_STYP_OVERLAY_0040f8e4);
              }
              if ((param_1[0xc] & 0x4000U) != 0) {
                FUN_00404caf(DAT_004134a4,s_STYP_OVERLAYP_0040f8f4);
              }
              if ((param_1[0xc] & 0x1000U) != 0) {
                FUN_00404caf(DAT_004134a4,s_STYP_MACRO_0040f904);
              }
              if ((param_1[0xc] & 0x2000U) != 0) {
                FUN_00404caf(DAT_004134a4,s_STYP_BW_0040f910);
              }
              if ((param_1[0xc] & 0x100U) != 0) {
                FUN_00404caf(DAT_004134a4,s_STYP_DEBUG_0040f91c);
              }
            }
            else {
              FUN_00404caf(DAT_004134a4,s_STYP_COPY_0040f89c);
            }
          }
          else {
            FUN_00404caf(DAT_004134a4,s_STYP_PAD_0040f890);
          }
        }
        else {
          FUN_00404caf(DAT_004134a4,s_STYP_GROUP_0040f884);
        }
      }
      else {
        FUN_00404caf(DAT_004134a4,s_STYP_NOLOAD_0040f874);
      }
    }
    else {
      FUN_00404caf(DAT_004134a4,s_STYP_DSECT_0040f868);
    }
    FUN_00404caf(DAT_004134a4,&DAT_0040f928);
  }
  return;
}


/* ==== FUN_004029bc @ 004029bc ==== */

int * __cdecl FUN_004029bc(int *param_1)

{
  int *local_8;
  
  if (*param_1 == 0) {
    if ((param_1[1] < 4) || (DAT_0041389c < param_1[1])) {
      FUN_00404ce9(s_invalid_string_table_offset_for_s_0040f92c);
    }
    local_8 = (int *)(DAT_004138dc + -4 + param_1[1]);
  }
  else {
    local_8 = param_1;
  }
  return local_8;
}


/* ==== FUN_00402a0e @ 00402a0e ==== */

void __cdecl FUN_00402a0e(int *param_1)

{
  int *va0;
  char *extraout_EAX;
  int iVar1;
  uint uVar2;
  undefined4 in_stack_00000008;
  char *local_c;
  uint local_8;
  
  if ((param_1[7] != 0) && (param_1[6] != 0)) {
    va0 = FUN_004029bc(param_1);
    FUN_00404caf(DAT_004134a4,s_RAW_DATA_FOR_SECTION__s___d__0040f960,va0,in_stack_00000008);
    if (DAT_00413490 == 0) {
      FUN_00404caf(DAT_004134a4,s_IN_FILE__s_0040f984,DAT_004134a0);
    }
    else {
      FUN_00404caf(DAT_004134a4,&DAT_0040f980);
    }
    if (param_1[6] < 0) {
      FUN_00404ce9(s_invalid_raw_data_size_in_section_0040f994,va0);
    }
    malloc(param_1[6] << 2);
    iVar1 = fseek(DAT_0041349c,param_1[7],0);
    if (iVar1 != 0) {
      FUN_00404ce9(s_cannot_seek_to_raw_data_in_secti_0040f9b8,va0);
    }
    uVar2 = FUN_00404840(extraout_EAX,param_1[6],4,DAT_0041349c);
    if (uVar2 != 4) {
      FUN_00404ce9(s_cannot_read_raw_data_in_section___0040f9e0,va0);
    }
    local_8 = 0;
    FUN_00404caf(DAT_004134a4,&DAT_0040fa04,&DAT_0040e108);
    local_c = extraout_EAX;
    while ((int)local_8 < param_1[6]) {
      FUN_00404caf(DAT_004134a4,s__08lX_0040fa08,*(undefined4 *)local_c);
      local_c = local_c + 4;
      local_8 = local_8 + 1;
      uVar2 = (int)local_8 >> 0x1f;
      if ((((local_8 ^ uVar2) - uVar2 & 3 ^ uVar2) == uVar2) && ((int)local_8 < param_1[6])) {
        FUN_00404caf(DAT_004134a4,&DAT_0040fa10,&DAT_0040e108);
      }
    }
    FUN_00404caf(DAT_004134a4,&DAT_0040fa14);
    free(local_c + local_8 * -4);
  }
  return;
}


/* ==== FUN_00402bd9 @ 00402bd9 ==== */

void __cdecl FUN_00402bd9(int *param_1)

{
  int *va0;
  int iVar1;
  uint uVar2;
  undefined4 in_stack_00000008;
  int local_14;
  undefined4 local_10;
  int local_c;
  
  if ((param_1[8] != 0) && (param_1[10] != 0)) {
    va0 = FUN_004029bc(param_1);
    FUN_00404caf(DAT_004134a4,s_RELOCATION_ENTRIES_FOR_SECTION___0040fa18,va0,in_stack_00000008);
    if (DAT_00413490 == 0) {
      FUN_00404caf(DAT_004134a4,s_IN_FILE__s_0040fa44,DAT_004134a0);
    }
    else {
      FUN_00404caf(DAT_004134a4,&DAT_0040fa40);
    }
    iVar1 = fseek(DAT_0041349c,param_1[8],0);
    if (iVar1 != 0) {
      FUN_00404ce9(s_cannot_seek_to_relocation_entrie_0040fa54,va0);
    }
    for (local_14 = 0; local_14 < param_1[10]; local_14 = local_14 + 1) {
      uVar2 = FUN_00404840((char *)&local_10,0xc,1,DAT_0041349c);
      if (uVar2 != 1) {
        FUN_00404ce9(s_cannot_read_relocation_entry__d_i_0040fa84,local_14,va0);
      }
      FUN_00404caf(DAT_004134a4,&DAT_0040fab4,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_r_vaddr___0x_08lX_0040fab8,local_10);
      if (DAT_004134ac == '\0') {
        FUN_00404caf(DAT_004134a4,s_r_symndx____ld_0040facc,local_c);
      }
      else {
        if ((local_c < 4) || (DAT_0041389c < local_c)) {
          FUN_00404ce9(s_invalid_string_table_offset_for_r_0040fadc,local_14,va0);
        }
        FUN_00404caf(DAT_004134a4,s_r_symndx____s_0040fb20,DAT_004138dc + -4 + local_c);
      }
    }
  }
  return;
}


/* ==== FUN_00402d7e @ 00402d7e ==== */

void __cdecl FUN_00402d7e(int *param_1)

{
  int *va0;
  int iVar1;
  uint uVar2;
  undefined4 in_stack_00000008;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((param_1[9] != 0) && (param_1[0xb] != 0)) {
    va0 = FUN_004029bc(param_1);
    FUN_00404caf(DAT_004134a4,s_LINE_NUMBER_ENTRIES_FOR_SECTION___0040fb30,va0,in_stack_00000008);
    if (DAT_00413490 == 0) {
      FUN_00404caf(DAT_004134a4,s_IN_FILE__s_0040fb60,DAT_004134a0);
    }
    else {
      FUN_00404caf(DAT_004134a4,&DAT_0040fb5c);
    }
    iVar1 = fseek(DAT_0041349c,param_1[9],0);
    if (iVar1 != 0) {
      FUN_00404ce9(s_cannot_seek_to_line_number_entri_0040fb70,va0);
    }
    for (local_8 = 0; local_8 < param_1[0xb]; local_8 = local_8 + 1) {
      uVar2 = FUN_00404840((char *)&local_14,0xc,1,DAT_0041349c);
      if (uVar2 != 1) {
        FUN_00404ce9(s_cannot_read_line_number_entry__d_0040fba4,local_8,va0);
      }
      FUN_00404caf(DAT_004134a4,&DAT_0040fbd4,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_l_lnno_____4lu_0040fbd8,local_c);
      if (local_c == 0) {
        FUN_00404caf(DAT_004134a4,s_l_symndx____ld_0040fbec,local_14);
      }
      else if (((DAT_004134ac == '\0') || (local_10 < 0)) || (DAT_0040e600 <= local_10)) {
        FUN_00404caf(DAT_004134a4,s_l_paddr___0x_08lX_0x_08lX_0040fbfc,local_10,local_14);
      }
      else {
        FUN_00404caf(DAT_004134a4,s_l_paddr____s0x_08lX_0040fc18,(&PTR_DAT_0040e178)[local_10],
                     local_14);
      }
    }
  }
  return;
}


/* ==== FUN_00402f34 @ 00402f34 ==== */

void FUN_00402f34(void)

{
  int iVar1;
  uint uVar2;
  char local_4c [32];
  int local_2c;
  int local_28;
  int local_24 [7];
  int local_8;
  
  if ((DAT_004138e0 != 0) && (DAT_004138d8 != 0)) {
    FUN_00404caf(DAT_004134a4,s_SYMBOL_TABLE_0040fc30);
    if (DAT_00413490 == 0) {
      FUN_00404caf(DAT_004134a4,s_FOR_FILE__s_0040fc44,DAT_004134a0);
    }
    else {
      FUN_00404caf(DAT_004134a4,&DAT_0040fc40);
    }
    iVar1 = fseek(DAT_0041349c,DAT_004138e0,0);
    if (iVar1 != 0) {
      FUN_00404ce9(s_cannot_seek_to_symbol_table_0040fc54);
    }
    local_28 = 0;
    while (local_28 < DAT_004138d8) {
      uVar2 = FUN_00404840((char *)local_24,0x20,1,DAT_0041349c);
      if (uVar2 != 1) {
        FUN_00404ce9(s_cannot_read_symbol_table_entry___0040fc70,local_28);
      }
      FUN_00403098(local_24,local_28);
      for (local_2c = 0; local_28 = local_28 + 1, local_2c < local_8; local_2c = local_2c + 1) {
        uVar2 = FUN_00404840(local_4c,0x20,1,DAT_0041349c);
        if (uVar2 != 1) {
          FUN_00404ce9(s_cannot_read_auxiliary_entry__d_f_0040fc94,local_2c,local_28);
        }
        FUN_004038e7((int)local_24,local_4c,local_28,local_2c);
      }
    }
  }
  return;
}


/* ==== FUN_00403098 @ 00403098 ==== */

void __cdecl FUN_00403098(int *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 in_stack_00000008;
  undefined *local_28;
  int *local_14;
  uint local_10;
  char *local_c;
  char *local_8;
  
  if (*param_1 == 0) {
    if ((param_1[1] < 4) || (DAT_0041389c < param_1[1])) {
      FUN_00404ce9(s_invalid_string_table_offset_for_s_0040fcc8,in_stack_00000008);
    }
    local_14 = (int *)(DAT_004138dc + -4 + param_1[1]);
  }
  else {
    FUN_0040487a((undefined1 *)param_1,4,2);
    local_14 = param_1;
  }
  FUN_00404caf(DAT_004134a4,s___6d_0040fd04,in_stack_00000008);
  FUN_00404caf(DAT_004134a4,s_n_name_____16s_0040fd0c,local_14);
  switch(param_1[6]) {
  case 0:
    local_8 = s_C_NULL_0040fd28;
    break;
  case 1:
    local_8 = s_C_AUTO_0040fd30;
    break;
  case 2:
    local_8 = s_C_EXT_0040fd38;
    break;
  case 3:
    local_8 = s_C_STAT_0040fd40;
    break;
  case 4:
    local_8 = s_C_REG_0040fd48;
    break;
  case 5:
    local_8 = s_C_EXTDEF_0040fd50;
    break;
  case 6:
    local_8 = s_C_LABEL_0040fd5c;
    break;
  case 7:
    local_8 = s_C_REG_0040fd64;
    break;
  case 8:
    local_8 = s_C_MOS_0040fd6c;
    break;
  case 9:
    local_8 = s_C_ARG_0040fd74;
    break;
  case 10:
    local_8 = s_C_STRTAG_0040fd7c;
    break;
  case 0xb:
    local_8 = s_C_MOU_0040fd88;
    break;
  case 0xc:
    local_8 = s_C_UNTAG_0040fd90;
    break;
  case 0xd:
    local_8 = s_C_TPDEF_0040fd98;
    break;
  case 0xe:
    local_8 = s_C_USTATIC_0040fda0;
    break;
  case 0xf:
    local_8 = s_C_ENTAG_0040fdac;
    break;
  case 0x10:
    local_8 = s_C_MOE_0040fdb4;
    break;
  case 0x11:
    local_8 = s_C_REGPARM_0040fdbc;
    break;
  case 0x12:
    local_8 = s_C_FIELD_0040fdc8;
    break;
  case 0x13:
    local_8 = s_C_MEMREG_0040fdd0;
    break;
  case 0x14:
    local_8 = s_C_OPTIMIZED_0040fddc;
    break;
  default:
    local_8 = s_<unknown>_0040fe94;
    break;
  case 100:
    local_8 = s_C_BLOCK_0040fde8;
    break;
  case 0x65:
    local_8 = s_C_FCN_0040fdf0;
    break;
  case 0x66:
    local_8 = s_C_EOS_0040fdf8;
    break;
  case 0x67:
    local_8 = s_C_FILE_0040fe00;
    break;
  case 0x68:
    local_8 = s_C_LINE_0040fe08;
    break;
  case 0x69:
    local_8 = s_C_ALIAS_0040fe10;
    break;
  case 0x6a:
    local_8 = s_C_HIDDEN_0040fe18;
    break;
  case 0x80:
    local_8 = s_C_SECT_0040fe24;
    break;
  case 0x81:
    local_8 = s_C_SDI_0040fe2c;
    break;
  case 200:
    local_8 = s_A_FILE_0040fe34;
    break;
  case 0xc9:
    local_8 = s_A_SECT_0040fe3c;
    break;
  case 0xca:
    local_8 = s_A_BLOCK_0040fe44;
    break;
  case 0xcb:
    local_8 = s_A_MACRO_0040fe4c;
    break;
  case 0xd2:
    local_8 = s_A_GLOBAL_0040fe54;
    break;
  case 0xd3:
    local_8 = s_A_XDEF_0040fe60;
    break;
  case 0xd4:
    local_8 = s_A_XREF_0040fe68;
    break;
  case 0xd5:
    local_8 = s_A_SLOCAL_0040fe70;
    break;
  case 0xd6:
    local_8 = s_A_ULOCAL_0040fe7c;
    break;
  case 0xd7:
    local_8 = s_A_MLOCAL_0040fe88;
    break;
  case -1:
    local_8 = s_C_EFCN_0040fd20;
  }
  if (DAT_004134ac == '\0') {
    FUN_00404caf(DAT_004134a4,s_n_value___0x_08lX_0x_08lX_0040fea0,param_1[3],param_1[2]);
  }
  else if ((param_1[5] & 0x1000fU) == 6) {
    FUN_00404caf(DAT_004134a4,s_n_value______6E_0040febc,param_1[2],param_1[3]);
  }
  else if ((param_1[5] & 0x1000fU) == 5) {
    FUN_00404caf(DAT_004134a4,s_n_value___0x_08lX_0x_08lX_0040fed0,param_1[3],param_1[2]);
  }
  else if ((((param_1[3] < 0) || (0x123 < param_1[3])) || (param_1[3] == 4)) ||
          ((param_1[3] < 0 || (DAT_0040e600 <= param_1[3])))) {
    FUN_00404caf(DAT_004134a4,s_n_value___0x_08lX_0040ff04,param_1[2]);
  }
  else {
    FUN_00404caf(DAT_004134a4,s_n_value____s0x_08lX_0040feec,(&PTR_DAT_0040e178)[param_1[3]],
                 param_1[2]);
  }
  FUN_00404caf(DAT_004134a4,&DAT_0040ff18,&DAT_0040e108);
  FUN_00404caf(DAT_004134a4,&DAT_0040ff1c,&DAT_0040e108);
  iVar1 = param_1[4];
  if (iVar1 == -2) {
    local_c = s_N_DEBUG_0040ff20;
  }
  else if (iVar1 == -1) {
    local_c = s_N_ABS_0040ff28;
  }
  else if (iVar1 == 0) {
    local_c = s_N_UNDEF_0040ff30;
  }
  else {
    local_c = &DAT_004134c0;
  }
  if ((DAT_004134ac == '\0') || (*local_c == '\0')) {
    FUN_00404caf(DAT_004134a4,s_n_scnum_____5d_0040ff48,param_1[4]);
  }
  else {
    FUN_00404caf(DAT_004134a4,s_n_scnum____s_0040ff38,local_c);
  }
  if (((DAT_004134ac == '\0') ||
      (((param_1[6] == 0x67 || (param_1[6] == 200)) &&
       (DAT_0040e670 < (int)(param_1[5] & 0xfU | (param_1[5] & 0x10000U) >> 0xc))))) ||
     (((param_1[6] != 0x67 && (param_1[6] != 200)) &&
      (DAT_0040e660 < (int)(param_1[5] & 0xfU | (param_1[5] & 0x10000U) >> 0xc))))) {
    FUN_00404caf(DAT_004134a4,s_n_type___0_lo__0x_lX__0040ff5c,param_1[5],param_1[5]);
  }
  else {
    if ((param_1[6] == 0x67) || (param_1[6] == 200)) {
      local_28 = (&PTR_s_T_NULL_0040e668)[param_1[5] & 0xfU | (param_1[5] & 0x10000U) >> 0xc];
    }
    else {
      local_28 = (&PTR_s_T_NULL_0040e608)[param_1[5] & 0xfU | (param_1[5] & 0x10000U) >> 0xc];
    }
    FUN_00404caf(DAT_004134a4,s_n_type____s_0040ff74,local_28);
    uVar2 = param_1[5];
    while (local_10 = uVar2 & 0xfffefff0, local_10 != 0) {
      if ((uVar2 & 0x30) == 0x20) {
        FUN_00404caf(DAT_004134a4,s__DT_FCN_0040ff80);
      }
      else if ((uVar2 & 0x30) == 0x10) {
        FUN_00404caf(DAT_004134a4,s__DT_PTR_0040ff88);
      }
      else if ((uVar2 & 0x30) == 0x30) {
        FUN_00404caf(DAT_004134a4,s__DT_ARY_0040ff90);
        DAT_004134b4 = 1;
      }
      uVar2 = local_10 >> 2;
    }
    FUN_00404caf(DAT_004134a4,&DAT_0040ff98);
  }
  if (DAT_004134ac == '\0') {
    FUN_00404caf(DAT_004134a4,s_n_sclass____ld_0040ff9c,param_1[6]);
  }
  else {
    FUN_00404caf(DAT_004134a4,s_n_sclass____s_0040ffb0,local_8);
  }
  FUN_00404caf(DAT_004134a4,s_n_numaux____ld_0040ffc0,param_1[7]);
  return;
}


/* ==== FUN_004038e7 @ 004038e7 ==== */

void __cdecl FUN_004038e7(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  int local_14;
  uint local_10;
  char *local_c;
  char *local_8;
  
  local_c = param_2;
  FUN_00404caf(DAT_004134a4,s___6d_0040ffd0,param_3);
  if (DAT_004134ac == '\0') {
    FUN_0040487a(param_2,1,0x20);
    for (local_10 = 0; local_10 < 0x20; local_10 = local_10 + 1) {
      FUN_00404caf(DAT_004134a4,&DAT_0040ffd8,(int)*local_c >> 4 & 0xf);
      FUN_00404caf(DAT_004134a4,&DAT_0040ffdc,(int)*local_c & 0xf);
      local_c = local_c + 1;
    }
    FUN_00404caf(DAT_004134a4,&DAT_0040ffe4);
  }
  else {
    if ((*(int *)(param_1 + 0x18) == 0x67) || (*(int *)(param_1 + 0x18) == 200)) {
      if (*(int *)(param_2 + 0x10) == 0) {
        FUN_0040487a(param_2,1,0x10);
        local_8 = param_2;
      }
      else {
        if ((*(uint *)(param_2 + 0x10) < 4) || (DAT_0041389c < *(int *)(param_2 + 0x10))) {
          FUN_00404ce9(s_invalid_string_table_offset_for_f_0040ffe8);
        }
        local_8 = (char *)(DAT_004138dc + -4 + *(int *)(param_2 + 0x10));
      }
      if (DAT_00413490 != 0) {
        FUN_00403e11(local_8);
      }
      FUN_00404caf(DAT_004134a4,s_fname____s_00410014,local_8);
      if (*(int *)(param_2 + 0x14) != 0) {
        FUN_00404caf(DAT_004134a4,s_x_ftype___0x_04lX_00410024,*(undefined4 *)(param_2 + 0x14));
      }
    }
    else if ((*(int *)(param_1 + 0x18) == 3) && ((*(uint *)(param_1 + 0x14) & 0x1000f) == 0)) {
      FUN_00403ee2((int)param_2,param_4);
    }
    else if ((*(int *)(param_1 + 0x18) == 10) ||
            ((*(int *)(param_1 + 0x18) == 0xc || (*(int *)(param_1 + 0x18) == 0xf)))) {
      FUN_00404caf(DAT_004134a4,s_size____4lu_00410038,*(undefined4 *)(param_2 + 8));
      FUN_00404caf(DAT_004134a4,s_endndx____6ld_00410048,*(undefined4 *)(param_2 + 0x10));
    }
    else if (*(int *)(param_1 + 0x18) == 0x66) {
      FUN_00404caf(DAT_004134a4,s_tagndx____6ld_00410058,*(undefined4 *)param_2);
      FUN_00404caf(DAT_004134a4,s_size____4d_00410068,*(undefined4 *)(param_2 + 8));
    }
    else if ((*(int *)(param_1 + 0x18) == 0x65) || (*(int *)(param_1 + 0x18) == 100)) {
      FUN_00404caf(DAT_004134a4,s_lnno____4ld_00410078,*(undefined4 *)(param_2 + 4));
      FUN_00404caf(DAT_004134a4,s_endndx____6ld_00410088,*(undefined4 *)(param_2 + 0x10));
      if ((*(int *)(param_1 + 0x18) == 0x65) && (*(int *)(param_2 + 0x14) != 0)) {
        FUN_00404caf(DAT_004134a4,s_x_type___0x_04lX_00410098,*(undefined4 *)(param_2 + 0x14));
      }
    }
    else if (*(int *)(param_1 + 0x18) == 0xc9) {
      FUN_00404caf(DAT_004134a4,s_tagndx____6ld_004100ac,*(undefined4 *)param_2);
      FUN_00404caf(DAT_004134a4,s_lnno____4ld_004100bc,*(undefined4 *)(param_2 + 4));
      FUN_00404caf(DAT_004134a4,s_endndx____6ld_004100cc,*(undefined4 *)(param_2 + 0x10));
    }
    else if (*(int *)(param_1 + 0x18) == 0xcb) {
      FUN_00404caf(DAT_004134a4,s_lnno____4ld_004100dc,*(undefined4 *)(param_2 + 4));
      FUN_00404caf(DAT_004134a4,s_endndx____6ld_004100ec,*(undefined4 *)(param_2 + 0x10));
    }
    else if (*(int *)(param_1 + 0x18) == 0x12) {
      FUN_00404caf(DAT_004134a4,s_size____4lu_004100fc,*(undefined4 *)(param_2 + 8));
    }
    else if ((*(uint *)(param_1 + 0x14) & 0x30) == 0x20) {
      FUN_00404caf(DAT_004134a4,s_tagndx____6ld_0041010c,*(undefined4 *)param_2);
      FUN_00404caf(DAT_004134a4,s_fsize____6ld_0041011c,*(undefined4 *)(param_2 + 4));
      FUN_00404caf(DAT_004134a4,s_lnnoptr____6ld_0041012c,*(undefined4 *)(param_2 + 0xc));
      FUN_00404caf(DAT_004134a4,s_endndx____6ld_00410140,*(undefined4 *)(param_2 + 0x10));
    }
    else if (DAT_004134b4 == '\0') {
      if (((*(int *)(param_1 + 0x14) == 8) || (*(int *)(param_1 + 0x14) == 9)) ||
         (*(int *)(param_1 + 0x14) == 10)) {
        FUN_00404caf(DAT_004134a4,s_tagndx____6ld_00410194,*(undefined4 *)param_2);
        FUN_00404caf(DAT_004134a4,s_size____4d_004101a4,*(undefined4 *)(param_2 + 8));
      }
    }
    else {
      DAT_004134b4 = '\0';
      FUN_00404caf(DAT_004134a4,s_tagndx____6ld_00410150,*(undefined4 *)param_2);
      FUN_00404caf(DAT_004134a4,s_lnno____4ld_00410160,*(undefined4 *)(param_2 + 4));
      FUN_00404caf(DAT_004134a4,s_size____4lu_00410170,*(undefined4 *)(param_2 + 8));
      local_14 = 0;
      while ((local_14 < 4 && (*(int *)(param_2 + local_14 * 4 + 0xc) != 0))) {
        FUN_00404caf(DAT_004134a4,s_dimen__d_____4lu_00410180,local_14,
                     *(undefined4 *)(param_2 + local_14 * 4 + 0xc));
        local_14 = local_14 + 1;
      }
    }
    FUN_00404caf(DAT_004134a4,&DAT_004101b0);
  }
  return;
}


/* ==== FUN_00403e11 @ 00403e11 ==== */

void __cdecl FUN_00403e11(char *param_1)

{
  bool bVar1;
  char *local_c;
  char *local_8;
  
  bVar1 = false;
  if (*param_1 != ':') {
    if (*param_1 != '[') goto LAB_00403e7a;
    bVar1 = true;
  }
  local_8 = param_1;
  local_c = param_1;
  while (local_c = local_c + 1, *local_c != '\0') {
    *local_8 = *local_c;
    local_8 = local_8 + 1;
  }
  *local_8 = '\0';
LAB_00403e7a:
  for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (((*local_8 == '\\') || (*local_8 == ':')) || ((*local_8 == '.' && (bVar1)))) {
      *local_8 = '/';
    }
    else if (*local_8 == ']') {
      bVar1 = false;
      *local_8 = '/';
    }
  }
  return;
}


/* ==== FUN_00403ee2 @ 00403ee2 ==== */

void __cdecl FUN_00403ee2(int param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
    FUN_00404caf(DAT_004134a4,s_scnlen____6ld_004101b4,*(undefined4 *)param_1);
    FUN_00404caf(DAT_004134a4,s_nreloc____4lu_004101c4,*(undefined4 *)(param_1 + 4));
    FUN_00404caf(DAT_004134a4,s_nlinno____4lu_004101d4,*(undefined4 *)(param_1 + 8));
    break;
  case 1:
    if (DAT_00413494 == 0) {
      FUN_00404caf(DAT_004134a4,s_secno____4ld_004101e4,*(undefined4 *)param_1);
      FUN_00404caf(DAT_004134a4,s_rsecno____4ld_004101f4,*(undefined4 *)(param_1 + 4));
      FUN_00404caf(DAT_004134a4,s_mem___0x_04lX_00410204,*(undefined4 *)(param_1 + 8));
      FUN_00404caf(DAT_004134a4,s_flags___0x_08lX_00410214,*(undefined4 *)(param_1 + 0xc));
      if ((*(uint *)(param_1 + 0xc) & 0x6000) != 0) {
        FUN_00404caf(DAT_004134a4,&DAT_00410228);
        FUN_00404caf(DAT_004134a4,&DAT_0041022c,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,&DAT_00410230,&DAT_0040e108);
        if ((*(uint *)(param_1 + 0xc) & 0x2000) == 0) {
          if ((*(uint *)(param_1 + 0xc) & 0x4000) != 0) {
            FUN_00404caf(DAT_004134a4,s_ovlcnt____4ld_00410268,*(undefined4 *)(param_1 + 0x10));
            FUN_00404caf(DAT_004134a4,s_ovlmem___0x_04lX_00410278,*(undefined4 *)(param_1 + 0x14));
            FUN_00404caf(DAT_004134a4,s_ovlstr____6ld_0041028c,*(undefined4 *)(param_1 + 0x18));
          }
        }
        else {
          FUN_00404caf(DAT_004134a4,s_bufcnt____4ld_00410234,*(undefined4 *)(param_1 + 0x10));
          FUN_00404caf(DAT_004134a4,s_buftyp___0x_04lX_00410244,*(undefined4 *)(param_1 + 0x14));
          FUN_00404caf(DAT_004134a4,s_buflim____6ld_00410258,*(undefined4 *)(param_1 + 0x18));
        }
      }
    }
    else {
      DAT_00413484 = *(uint *)(param_1 + 8);
      FUN_00404caf(DAT_004134a4,s_secno____4ld_0041029c,*(undefined4 *)param_1);
      FUN_00404caf(DAT_004134a4,s_rsecno____4ld_004102ac,*(undefined4 *)(param_1 + 4));
      FUN_00404caf(DAT_004134a4,s_flags___0x_08lX_004102bc,*(undefined4 *)(param_1 + 8));
      FUN_00404caf(DAT_004134a4,&DAT_004102d0);
      FUN_00404caf(DAT_004134a4,&DAT_004102d4,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,&DAT_004102d8,&DAT_0040e108);
      FUN_00404caf(DAT_004134a4,s_mspace____4ld_004102dc,*(undefined4 *)(param_1 + 0xc));
      FUN_00404caf(DAT_004134a4,s_mmap____4ld_004102ec,*(undefined4 *)(param_1 + 0x10));
      FUN_00404caf(DAT_004134a4,s_mcntr____4ld_004102fc,*(undefined4 *)(param_1 + 0x14));
      FUN_00404caf(DAT_004134a4,s_mclass____4ld_0041030c,*(undefined4 *)(param_1 + 0x18));
    }
    break;
  case 2:
    if ((DAT_00413484 & 0x2000) == 0) {
      if ((DAT_00413484 & 0x4000) != 0) {
        FUN_00404caf(DAT_004134a4,s_ovlcnt____4ld_00410350,*(undefined4 *)(param_1 + 0x10));
        FUN_00404caf(DAT_004134a4,s_ovlstr____6ld_00410360,*(undefined4 *)(param_1 + 0x14));
        FUN_00404caf(DAT_004134a4,s_ovloff___0x_08lX_00410370,*(undefined4 *)(param_1 + 0x18));
        FUN_00404caf(DAT_004134a4,&DAT_00410384);
        FUN_00404caf(DAT_004134a4,&DAT_00410388,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,&DAT_0041038c,&DAT_0040e108);
        FUN_00404caf(DAT_004134a4,s_ovlmem_mspace____4ld_00410390,*(undefined4 *)param_1);
        FUN_00404caf(DAT_004134a4,s_ovlmem_mmap____4ld_004103a8,*(undefined4 *)(param_1 + 4));
        FUN_00404caf(DAT_004134a4,s_ovlmem_mcntr____4ld_004103c0,*(undefined4 *)(param_1 + 8));
        FUN_00404caf(DAT_004134a4,s_ovlmem_mclass____4ld_004103d8,*(undefined4 *)(param_1 + 0xc));
      }
    }
    else {
      FUN_00404caf(DAT_004134a4,s_bufcnt____4ld_0041031c,*(undefined4 *)param_1);
      FUN_00404caf(DAT_004134a4,s_buftyp___0x_04lX_0041032c,*(undefined4 *)(param_1 + 4));
      FUN_00404caf(DAT_004134a4,s_buflim____6ld_00410340,*(undefined4 *)(param_1 + 8));
    }
    break;
  case 3:
    FUN_00404caf(DAT_004134a4,s_ovlcnt____4ld_004103f0,*(undefined4 *)(param_1 + 0x10));
    FUN_00404caf(DAT_004134a4,s_ovlstr____6ld_00410400,*(undefined4 *)(param_1 + 0x14));
    FUN_00404caf(DAT_004134a4,s_ovloff___0x_08lX_00410410,*(undefined4 *)(param_1 + 0x18));
    FUN_00404caf(DAT_004134a4,&DAT_00410424);
    FUN_00404caf(DAT_004134a4,&DAT_00410428,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,&DAT_0041042c,&DAT_0040e108);
    FUN_00404caf(DAT_004134a4,s_ovlmem_mspace____4ld_00410430,*(undefined4 *)param_1);
    FUN_00404caf(DAT_004134a4,s_ovlmem_mmap____4ld_00410448,*(undefined4 *)(param_1 + 4));
    FUN_00404caf(DAT_004134a4,s_ovlmem_mcntr____4ld_00410460,*(undefined4 *)(param_1 + 8));
    FUN_00404caf(DAT_004134a4,s_ovlmem_mclass____4ld_00410478,*(undefined4 *)(param_1 + 0xc));
  }
  return;
}


/* ==== FUN_004044a4 @ 004044a4 ==== */

void FUN_004044a4(void)

{
  size_t sVar1;
  char *local_10;
  int local_8;
  
  if (DAT_0041389c != 0) {
    FUN_00404caf(DAT_004134a4,s_STRING_TABLE_00410490);
    if (DAT_00413490 == 0) {
      FUN_00404caf(DAT_004134a4,s_FOR_FILE__s_004104a4,DAT_004134a0);
    }
    else {
      FUN_00404caf(DAT_004134a4,&DAT_004104a0);
    }
    FUN_00404caf(DAT_004134a4,s___8ld_ld__string_table_length__004104b4,0,DAT_0041389c);
    local_8 = 4;
    local_10 = DAT_004138dc;
    do {
      FUN_00404caf(DAT_004134a4,s___8ld_s_004104d8,local_8,local_10);
      sVar1 = _strlen(local_10);
      local_8 = local_8 + 1 + sVar1;
      local_10 = local_10 + sVar1 + 1;
    } while (local_10 < DAT_004138dc + DAT_0041389c);
  }
  return;
}


/* ==== FUN_00404594 @ 00404594 ==== */

undefined4 __cdecl FUN_00404594(char param_1,int param_2,undefined4 *param_3)

{
  int local_10;
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
        local_10 = (int)*local_8;
      }
      else {
        local_10 = tolower((int)*local_8);
      }
      if (local_10 == param_1) {
        return *param_3;
      }
    }
  } while( true );
}


/* ==== FUN_00404670 @ 00404670 ==== */

int __cdecl FUN_00404670(int param_1,int param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  DAT_00413488 = (char *)0x0;
  if ((DAT_004134b8 == (char *)0x0) || (*DAT_004134b8 == '\0')) {
    if (DAT_0041348c == 0) {
      DAT_0041348c = 1;
    }
    if (((param_1 <= DAT_0041348c) || (**(char **)(param_2 + DAT_0041348c * 4) != '-')) ||
       (*(char *)(*(int *)(param_2 + DAT_0041348c * 4) + 1) == '\0')) {
      DAT_00413488 = (char *)0x0;
      return -1;
    }
    iVar2 = _strcmp(*(char **)(param_2 + DAT_0041348c * 4),&DAT_004104e4);
    if (iVar2 == 0) {
      DAT_0041348c = DAT_0041348c + 1;
      return -1;
    }
    DAT_004134b8 = (char *)(*(int *)(param_2 + DAT_0041348c * 4) + 1);
    DAT_0041348c = DAT_0041348c + 1;
  }
  cVar1 = *DAT_004134b8;
  DAT_004134b8 = DAT_004134b8 + 1;
  pcVar3 = _strchr(param_3,(int)cVar1);
  if ((pcVar3 == (char *)0x0) || (cVar1 == ':')) {
    fprintf(&DAT_004109d0,s__s__unknown_option___c_004104e8,PTR_s_cofdmp_0040e070,(int)cVar1);
    iVar2 = 0x3f;
  }
  else {
    if (pcVar3[1] == ':') {
      if (*DAT_004134b8 == '\0') {
        if (param_1 <= DAT_0041348c) {
          fprintf(&DAT_004109d0,s__s____c_argument_missing_00410500,PTR_s_cofdmp_0040e070,(int)cVar1
                 );
          return 0x3f;
        }
        DAT_00413488 = *(char **)(param_2 + DAT_0041348c * 4);
        DAT_0041348c = DAT_0041348c + 1;
      }
      else {
        DAT_00413488 = DAT_004134b8;
        DAT_004134b8 = (char *)0x0;
      }
    }
    iVar2 = (int)cVar1;
  }
  return iVar2;
}


/* ==== FUN_00404836 @ 00404836 ==== */

undefined4 FUN_00404836(void)

{
  return 1;
}


/* ==== FUN_00404840 @ 00404840 ==== */

uint __cdecl FUN_00404840(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = FUN_00405520(param_1,param_2,param_3,param_4);
  FUN_0040487a(param_1,param_2,param_3);
  return uVar1;
}


/* ==== FUN_0040487a @ 0040487a ==== */

void __cdecl FUN_0040487a(undefined1 *param_1,int param_2,int param_3)

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


/* ==== FUN_004048f0 @ 004048f0 ==== */

undefined4 * __cdecl FUN_004048f0(int *param_1)

{
  int iVar1;
  uint uVar2;
  int local_24;
  int local_20;
  int local_1c;
  uint local_14;
  int local_10;
  int local_8;
  
  local_1c = *param_1 / 0x15180;
  for (local_8 = *param_1 % 0x15180; local_8 < 0; local_8 = local_8 + 0x15180) {
    local_1c = local_1c + -1;
  }
  for (; 0x1517f < local_8; local_8 = local_8 + -0x15180) {
    local_1c = local_1c + 1;
  }
  DAT_00413468 = local_8 / 0xe10;
  DAT_00413464 = (local_8 % 0xe10) / 0x3c;
  DAT_00413460 = (local_8 % 0xe10) % 0x3c;
  DAT_00413478 = (local_1c + 4) % 7;
  if (DAT_00413478 < 0) {
    DAT_00413478 = DAT_00413478 + 7;
  }
  local_14 = 0x7b2;
  if (local_1c < 0) {
    do {
      local_14 = local_14 - 1;
      uVar2 = (int)local_14 >> 0x1f;
      if (((((local_14 ^ uVar2) - uVar2 & 3 ^ uVar2) == uVar2) && ((int)local_14 % 100 != 0)) ||
         ((int)local_14 % 400 == 0)) {
        local_24 = 1;
      }
      else {
        local_24 = 0;
      }
      local_10 = local_24;
      local_1c = local_1c + *(int *)(&DAT_0040e170 + local_24 * 4);
    } while (local_1c < 0);
  }
  else {
    while( true ) {
      uVar2 = (int)local_14 >> 0x1f;
      if (((((local_14 ^ uVar2) - uVar2 & 3 ^ uVar2) == uVar2) && ((int)local_14 % 100 != 0)) ||
         ((int)local_14 % 400 == 0)) {
        local_20 = 1;
      }
      else {
        local_20 = 0;
      }
      local_10 = local_20;
      if (local_1c < *(int *)(&DAT_0040e170 + local_20 * 4)) break;
      local_14 = local_14 + 1;
      local_1c = local_1c - *(int *)(&DAT_0040e170 + local_20 * 4);
    }
  }
  DAT_00413474 = local_14 - 0x76c;
  DAT_0041347c = local_1c;
  DAT_00413470 = 0;
  for (; *(int *)(&DAT_0040e110 + DAT_00413470 * 4 + local_10 * 0x30) <= local_1c;
      local_1c = local_1c - *(int *)(&DAT_0040e110 + iVar1 + local_10 * 0x30)) {
    iVar1 = DAT_00413470 * 4;
    DAT_00413470 = DAT_00413470 + 1;
  }
  DAT_0041346c = local_1c + 1;
  DAT_00413480 = 0;
  return &DAT_00413460;
}


/* ==== FUN_00404b31 @ 00404b31 ==== */

void __cdecl FUN_00404b31(int param_1)

{
  if (param_1 == 2) {
    fprintf(&DAT_004109d0,s__s__Interrupted_0041051c,PTR_s_cofdmp_0040e070);
    exit(1);
  }
  else if (param_1 == 0xb) {
    fprintf(&DAT_004109d0,s__s__Fatal_segmentation_or_protec_00410530,PTR_s_cofdmp_0040e070);
    exit(1);
  }
  return;
}


/* ==== FUN_00404b95 @ 00404b95 ==== */

void FUN_00404b95(void)

{
  if (DAT_004134b0 != '\0') {
    fprintf(&DAT_004109d0,s__s__s__s_00410578,s_DSP_COFF_File_Dump_Utility_0040e078,
            s_Version_6_3_0040e098,s__C__Copyright_Motorola__Inc__199_0040e0a8);
  }
  fprintf(&DAT_004109d0,s_Usage___s___cfhloqrstv____d_<fil_00410584,PTR_s_cofdmp_0040e070);
  fprintf(&DAT_004109d0,s_c___dump_string_table_004105b0);
  fprintf(&DAT_004109d0,s_d___dump_to_output_file_004105d0);
  fprintf(&DAT_004109d0,s_f___dump_file_header_004105f4);
  fprintf(&DAT_004109d0,s_h___dump_section_headers_00410614);
  fprintf(&DAT_004109d0,s_l___dump_line_number_information_00410638);
  fprintf(&DAT_004109d0,s_o___dump_optional_header_00410664);
  fprintf(&DAT_004109d0,s_q___do_not_display_signon_banner_00410688);
  fprintf(&DAT_004109d0,s_r___dump_relocation_information_004106b4);
  fprintf(&DAT_004109d0,s_s___dump_section_contents_004106e0);
  fprintf(&DAT_004109d0,s_t___dump_symbol_table_00410704);
  fprintf(&DAT_004109d0,s_v___dump_symbolically_00410724);
  exit(1);
  return;
}


/* ==== FUN_00404caf @ 00404caf ==== */

void __cdecl FUN_00404caf(int *param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00405ab0(param_1,param_2,(undefined4 *)&stack0x0000000c);
  if (iVar1 < 0) {
    FUN_00404ce9(s_cannot_write_to_output_file_00410744);
  }
  return;
}


/* ==== FUN_00404ce9 @ 00404ce9 ==== */

void __cdecl FUN_00404ce9(char *param_1)

{
  int iVar1;
  
  iVar1 = errno;
  fprintf(&DAT_004109d0,&DAT_00410760,PTR_s_cofdmp_0040e070);
  FUN_00405ab0((int *)&DAT_004109d0,param_1,(undefined4 *)&stack0x00000008);
  fprintf(&DAT_004109d0,&DAT_00410768);
  if (iVar1 != 0) {
    errno = iVar1;
    FUN_00405af0(PTR_s_cofdmp_0040e070);
  }
  exit(1);
  return;
}


/* ==== _cinit @ 00404d70 ==== */

void _cinit(void)

{
  if (_FPinit != (undefined *)0x0) {
    (*(code *)_FPinit)();
  }
  _initterm(&DAT_0040e008,&DAT_0040e010);
  _initterm(&DAT_0040e000,&DAT_0040e004);
  return;
}


/* ==== exit @ 00404da0 ==== */

void __cdecl exit(int status)

{
  doexit(status,0,0);
  return;
}


/* ==== __exit @ 00404dc0 ==== */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __exit(int _Code)

{
  doexit(_Code,1,0);
  return;
}


/* ==== doexit @ 00404de0 ==== */

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


/* ==== _initterm @ 00404e90 ==== */

void __cdecl _initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != (code *)0x0) {
      (**(code **)begin)();
    }
  }
  return;
}


/* ==== fclose @ 00404eb0 ==== */

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


/* ==== _fsopen @ 00404f30 ==== */

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


/* ==== fopen @ 00404f60 ==== */

void __cdecl fopen(char *name,char *mode)

{
  _fsopen(name,mode,0x40);
  return;
}


/* ==== tolower @ 00404f80 ==== */

int __cdecl tolower(int c)

{
  int iVar1;
  uint uVar2;
  LPCWSTR pWVar3;
  int iVar4;
  uint local_8 [2];
  
  iVar1 = c;
  if (DAT_00413568 == 0) {
    if ((0x40 < c) && (c < 0x5b)) {
      return c + 0x20;
    }
  }
  else {
    if (c < 0x100) {
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[c * 2] & 1;
      }
      else {
        uVar2 = _isctype(c,1);
      }
      if (uVar2 == 0) {
        return iVar1;
      }
    }
    iVar4 = c;
    if ((_pctype[(iVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      c._0_2_ = (ushort)(byte)iVar1;
      pWVar3 = (LPCWSTR)0x1;
    }
    else {
      c._0_2_ = CONCAT11((byte)iVar1,(char)((uint)iVar1 >> 8));
      c._3_1_ = SUB41(iVar4,3);
      c._0_3_ = (uint3)(ushort)c;
      pWVar3 = (LPCWSTR)0x2;
    }
    iVar4 = FUN_00406190(DAT_00413568,0x100,(char *)&c,pWVar3,(LPWSTR)local_8,3,0);
    if (iVar4 == 0) {
      return iVar1;
    }
    if (iVar4 == 1) {
      return local_8[0] & 0xff;
    }
    c = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return c;
}


/* ==== _isctype @ 00405080 ==== */

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
  BVar2 = FUN_004063e0(1,(LPCSTR)&c,iVar1,(LPWORD)&local_4,0,0);
  if (BVar2 == 0) {
    return 0;
  }
  return local_4 & 0xffff & mask;
}


/* ==== _strchr @ 00405130 ==== */

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


/* ==== fprintf @ 004051f0 ==== */

int __cdecl fprintf(void *stream,char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(stream);
  iVar1 = _output(stream,fmt,&stack0x0000000c);
  _ftbuf(flag,stream);
  return iVar1;
}


/* ==== signal @ 00405310 ==== */

void __cdecl signal(int sig,void *func)

{
  int *piVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  BOOL BVar3;
  
  if ((func == (void *)0x4) || (func == (void *)0x3)) {
    errno = 0x16;
    return;
  }
  if (sig != 2) {
    if (((sig != 0x15) && (sig != 0x16)) && (sig != 0xf)) {
      if (((sig != 8) && (sig != 4)) && (sig != 0xb)) {
        errno = 0x16;
        return;
      }
      siglookup(sig);
      if (extraout_EAX == (undefined4 *)0x0) {
        errno = 0x16;
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
    if ((sig != 2) && (sig != 0x15)) goto LAB_004053c4;
  }
  if (DAT_00413524 == 0) {
    BVar3 = SetConsoleCtrlHandler((PHANDLER_ROUTINE)&LAB_00405480,1);
    if (BVar3 != 1) {
      _doserrno = GetLastError();
      errno = 0x16;
      return;
    }
    DAT_00413524 = 1;
  }
LAB_004053c4:
  switch(sig) {
  case 2:
    DAT_00413514 = func;
    return;
  default:
    return;
  case 0xf:
    DAT_00413520 = func;
    return;
  case 0x15:
    DAT_00413518 = func;
    return;
  case 0x16:
    DAT_0041351c = func;
    return;
  }
}


/* ==== siglookup @ 004054d0 ==== */

void __cdecl siglookup(int sig)

{
  int *piVar1;
  undefined4 *puVar2;
  
  if (DAT_00410c4c != sig) {
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


/* ==== FUN_00405520 @ 00405520 ==== */

uint __cdecl FUN_00405520(char *param_1,uint param_2,uint param_3,int *param_4)

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


/* ==== malloc @ 00405660 ==== */

void __cdecl malloc(uint size)

{
  _nh_malloc(size,_newmode);
  return;
}


/* ==== _nh_malloc @ 00405680 ==== */

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


/* ==== _heap_alloc @ 004056d0 ==== */

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


/* ==== fseek @ 00405710 ==== */

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
  errno = 0x16;
  return -1;
}


/* ==== FUN_004057b0 @ 004057b0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __cdecl FUN_004057b0(int *param_1)

{
  char *pcVar1;
  
  DAT_0041352b = 0x20;
  DAT_0041352f = 0x20;
  _DAT_0041352c = *(undefined2 *)("JanFebMarAprMayJunJulAugSepOctNovDec" + param_1[4] * 3);
  _DAT_00413528 = *(undefined2 *)("SunMonTueWedThuFriSat" + param_1[6] * 3);
  DAT_0041352e = "JanFebMarAprMayJunJulAugSepOctNovDec"[param_1[4] * 3 + 2];
  DAT_0041352a = "SunMonTueWedThuFriSat"[param_1[6] * 3 + 2];
  pcVar1 = FUN_004058a0(&DAT_00413530,param_1[3]);
  *pcVar1 = ' ';
  pcVar1 = FUN_004058a0(pcVar1 + 1,param_1[2]);
  *pcVar1 = ':';
  pcVar1 = FUN_004058a0(pcVar1 + 1,param_1[1]);
  *pcVar1 = ':';
  pcVar1 = FUN_004058a0(pcVar1 + 1,*param_1);
  *pcVar1 = ' ';
  pcVar1 = FUN_004058a0(pcVar1 + 1,param_1[5] / 100 + 0x13);
  pcVar1 = FUN_004058a0(pcVar1,param_1[5] % 100);
  *pcVar1 = '\n';
  pcVar1[1] = '\0';
  return &DAT_00413528;
}


/* ==== FUN_004058a0 @ 004058a0 ==== */

char * __cdecl FUN_004058a0(char *param_1,int param_2)

{
  *param_1 = (((char)(param_2 / 10) + (char)(param_2 >> 0x1f)) -
             (char)((longlong)param_2 * 0x66666667 >> 0x3f)) + '0';
  param_1[1] = (char)(param_2 % 10) + '0';
  return param_1 + 2;
}


/* ==== free @ 004058e0 ==== */

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


/* ==== __fpmath @ 00405930 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __fpmath
   
   Library: Visual Studio 1998 Release */

void __cdecl __fpmath(int param_1)

{
  _cfltcvt_init();
  __adjust_fdiv = _ms_p5_mp_test_fdiv();
  __setdefaultprecision();
  return;
}


/* ==== _cfltcvt_init @ 00405960 ==== */

void _cfltcvt_init(void)

{
  PTR__fptrap_00412d9c = _cropzeros;
  _cfltcvt_tab = _cfltcvt;
  PTR__fptrap_00412da0 = _fassign;
  PTR__fptrap_00412da4 = _forcdecpt;
  PTR__fptrap_00412da8 = _positive;
  PTR__fptrap_00412dac = _cfltcvt;
  return;
}


/* ==== _strlen @ 004059a0 ==== */

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
    if (((uint)puVar2 & 3) == 0) goto LAB_004059c0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_004059f3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_004059c0:
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
  goto LAB_004059f3;
}


/* ==== _strcmp @ 00405a20 ==== */

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
      if (bVar4 != *_Str2) goto LAB_00405a64;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_00405a30;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_00405a64;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_00405a64;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_00405a30:
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
LAB_00405a64:
  return (uint)bVar5 * -2 + 1;
}


/* ==== FUN_00405ab0 @ 00405ab0 ==== */

int __cdecl FUN_00405ab0(int *param_1,char *param_2,undefined4 *param_3)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(param_1);
  iVar1 = _output(param_1,param_2,param_3);
  _ftbuf(flag,param_1);
  return iVar1;
}


/* ==== FUN_00405af0 @ 00405af0 ==== */

void __cdecl FUN_00405af0(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    uVar3 = 0xffffffff;
    pcVar4 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    _write(2,param_1,~uVar3 - 1);
    _write(2,&DAT_0040d004,2);
  }
  if ((errno < 0) || (iVar2 = errno, DAT_00412e60 <= errno)) {
    iVar2 = DAT_00412e60;
  }
  uVar3 = 0xffffffff;
  pcVar4 = (&PTR_s_No_error_00412db0)[iVar2];
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  _write(2,(&PTR_s_No_error_00412db0)[iVar2],~uVar3 - 1);
  _write(2,&DAT_0040d000,1);
  return;
}


/* ==== entry @ 00405b70 ==== */

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
  puStack_c = &DAT_0040d008;
  puStack_10 = &LAB_00409388;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  DVar1 = GetVersion();
  _DAT_004134dc = DVar1 >> 8 & 0xff;
  _DAT_004134d8 = DVar1 & 0xff;
  _DAT_004134d4 = _DAT_004134d8 * 0x100 + _DAT_004134dc;
  _DAT_004134d0 = DVar1 >> 0x10;
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


/* ==== _amsg_exit @ 00405c90 ==== */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _amsg_exit(int rterrnum)

{
  if (DAT_00413554 != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
  (*(code *)PTR___exit_00410c30)(0xff);
  return;
}


/* ==== _close @ 00405cc0 ==== */

int __cdecl _close(int fh)

{
  long lVar1;
  long lVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD oserrno;
  int iVar4;
  
  if (_nhandle <= (uint)fh) {
    errno = 9;
    _doserrno = 0;
    return -1;
  }
  iVar4 = (fh & 0x1fU) * 8;
  if ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar4) & 1) == 0) {
    errno = 9;
    _doserrno = 0;
    return -1;
  }
  lVar1 = _get_osfhandle(fh);
  if (lVar1 != -1) {
    if ((fh == 1) || (fh == 2)) {
      lVar1 = _get_osfhandle(2);
      lVar2 = _get_osfhandle(1);
      if (lVar2 == lVar1) goto LAB_00405d47;
    }
    hObject = (HANDLE)_get_osfhandle(fh);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      oserrno = GetLastError();
      goto LAB_00405d49;
    }
  }
LAB_00405d47:
  oserrno = 0;
LAB_00405d49:
  _free_osfhnd(fh);
  *(undefined1 *)((&__pioinfo)[fh >> 5] + 4 + iVar4) = 0;
  if (oserrno == 0) {
    return 0;
  }
  _dosmaperr(oserrno);
  return -1;
}


/* ==== _freebuf @ 00405da0 ==== */

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


/* ==== _flush @ 00405e30 ==== */

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


/* ==== _openfile @ 00405f30 ==== */

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
      uVar7 = DAT_004137e4 | 1;
      goto LAB_00405f6d;
    }
    if (cVar1 != 'w') {
      return;
    }
    oflag = 0x301;
  }
  uVar7 = DAT_004137e4 | 2;
LAB_00405f6d:
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
      goto LAB_0040601e;
    case 'D':
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_0040601e;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x10;
        goto LAB_0040601e;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x20;
        goto LAB_0040601e;
      }
      break;
    case 'T':
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_0040601e;
      }
      break;
    case 'b':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x8000;
        goto LAB_0040601e;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_0040601e;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_0040601e;
      }
      break;
    case 't':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x4000;
        goto LAB_0040601e;
      }
    }
    bVar2 = false;
LAB_0040601e:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}


/* ==== _getstream @ 00406100 ==== */

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


/* ==== FUN_00406190 @ 00406190 ==== */

int __cdecl
FUN_00406190(LCID param_1,uint param_2,char *param_3,LPCWSTR param_4,LPWSTR param_5,int param_6,
            UINT param_7)

{
  int iVar1;
  LPCWSTR cbMultiByte;
  LPCWSTR lpWideCharStr;
  int iVar2;
  LPCWSTR lpDestStr;
  
  if (DAT_0041355c == 0) {
    iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_0041355c = 1;
    }
    else {
      DAT_0041355c = 2;
    }
  }
  cbMultiByte = param_4;
  if (0 < (int)param_4) {
    cbMultiByte = (LPCWSTR)__ansicp((int)param_3);
  }
  if (DAT_0041355c == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,(int)cbMultiByte,(LPSTR)param_5,param_6);
    return iVar1;
  }
  if (DAT_0041355c != 1) {
    return DAT_0041355c;
  }
  param_4 = (LPCWSTR)0x0;
  if (param_7 == 0) {
    param_7 = DAT_00413578;
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
      goto LAB_0040638f;
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
      if (param_6 == 0) goto LAB_004062f4;
      if (param_6 < iVar2) goto LAB_0040638f;
      iVar1 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,param_5,param_6);
    }
    if (iVar1 != 0) {
LAB_004062f4:
      free(lpWideCharStr);
      free(param_4);
      return iVar2;
    }
  }
LAB_0040638f:
  free(lpWideCharStr);
  free(param_4);
  return 0;
}


/* ==== __ansicp @ 004063b0 ==== */

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


/* ==== FUN_004063e0 @ 004063e0 ==== */

BOOL __cdecl
FUN_004063e0(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6)

{
  BOOL BVar1;
  uint size;
  LPCWSTR lpWideCharStr;
  int cchSrc;
  LPCWSTR p;
  WORD local_2;
  
  p = (LPCWSTR)0x0;
  if (DAT_00413580 == 0) {
    BVar1 = GetStringTypeA(0,1,"",1,&local_2);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeW(1,L"",1,&local_2);
      if (BVar1 == 0) {
        return 0;
      }
      DAT_00413580 = 1;
    }
    else {
      DAT_00413580 = 2;
    }
  }
  if (DAT_00413580 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_00413568;
    }
    BVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return BVar1;
  }
  param_6 = DAT_00413580;
  if (DAT_00413580 == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = DAT_00413578;
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


/* ==== _stbuf @ 00406510 ==== */

int __cdecl _stbuf(void *stream)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = _isatty(*(int *)((int)stream + 0x10));
  if (iVar2 != 0) {
    if (stream == &DAT_004109b0) {
      iVar2 = 0;
    }
    else {
      if (stream != &DAT_004109d0) {
        return 0;
      }
      iVar2 = 1;
    }
    _cflush = _cflush + 1;
    if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
      if ((&DAT_00413588)[iVar2] == 0) {
        malloc(0x1000);
        (&DAT_00413588)[iVar2] = extraout_EAX;
        if (extraout_EAX == 0) {
          return 0;
        }
      }
      uVar1 = (&DAT_00413588)[iVar2];
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


/* ==== _ftbuf @ 004065b0 ==== */

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


/* ==== _output @ 00406610 ==== */

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
      uVar2 = (byte)(&DAT_0040d000)[cVar7] & 0xf;
    }
    local_220 = (int)(char)(&DAT_0040d020)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_0040668d_caseD_0:
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
          goto switchD_0040668d_caseD_0;
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
          (*(code *)PTR__fptrap_00412da4)(&local_204);
        }
        if ((cVar7 == 'g') && ((unaff_EBX & 0x80) == 0)) {
          (*(code *)PTR__fptrap_00412d9c)(local_200);
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
            puVar5 = (ushort *)PTR_DAT_00410c38;
            local_248 = (ushort *)PTR_DAT_00410c38;
          }
          for (; (iVar10 != 0 && (iVar10 = iVar10 + -1, (char)*puVar5 != '\0'));
              puVar5 = (ushort *)((int)puVar5 + 1)) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_00410c3c;
          }
          local_230 = 1;
          for (puVar5 = local_248; (iVar10 != 0 && (iVar10 = iVar10 + -1, *puVar5 != 0));
              puVar5 = puVar5 + 1) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_004068a1_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg(&argptr);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_00410c38;
          pcVar9 = PTR_DAT_00410c38;
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
        goto LAB_00406bd7;
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
        goto LAB_00406bd7;
      case 'p':
        local_244 = 8;
switchD_004068a1_caseD_58:
        local_224 = 7;
LAB_00406b92:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_00406bd7;
      case 'u':
        local_22c = 10;
LAB_00406bd7:
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
        goto LAB_00406b92;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_00406d6f;
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
LAB_00406d6f:
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


/* ==== write_char @ 00406fa0 ==== */

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


/* ==== write_multi_char @ 00406ff0 ==== */

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


/* ==== write_string @ 00407030 ==== */

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


/* ==== get_int_arg @ 00407070 ==== */

int __cdecl get_int_arg(void *pargptr)

{
  int *piVar1;
  
  piVar1 = *(int **)pargptr;
  *(int **)pargptr = piVar1 + 1;
  return *piVar1;
}


/* ==== get_int64_arg @ 00407090 ==== */

longlong __cdecl get_int64_arg(void *pargptr)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)pargptr;
  *(longlong **)pargptr = plVar1 + 1;
  return *plVar1;
}


/* ==== get_short_arg @ 004070b0 ==== */

short __cdecl get_short_arg(void *pargptr)

{
  short *psVar1;
  
  psVar1 = *(short **)pargptr;
  *(short **)pargptr = psVar1 + 2;
  return *psVar1;
}


/* ==== _ioinit @ 004070d0 ==== */

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
      piVar6 = &DAT_00413904;
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
        goto LAB_004072ab;
      }
      *puVar2 = hFile;
      if ((DVar3 & 0xff) == 2) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_004072ab;
      }
      if ((DVar3 & 0xff) == 3) {
        bVar1 = *(byte *)(puVar2 + 1) | 8;
        goto LAB_004072ab;
      }
    }
    else {
      bVar1 = *(byte *)(puVar2 + 1) | 0x80;
LAB_004072ab:
      *(byte *)(puVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(_nhandle);
      return;
    }
  } while( true );
}


/* ==== calloc @ 004072d0 ==== */

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
LAB_00407330:
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
          goto LAB_00407330;
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


/* ==== _XcptFilter @ 004073e0 ==== */

int __cdecl _XcptFilter(ulong xcptnum,void *pxcptptrs)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  undefined4 *puVar6;
  int iVar7;
  
  piVar4 = FUN_00407520(xcptnum);
  uVar3 = DAT_00413590;
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    LVar5 = UnhandledExceptionFilter(pxcptptrs);
    return LVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 != (code *)0x1) {
    DAT_00413590 = pxcptptrs;
    if (piVar4[1] == 8) {
      if (DAT_00410cc0 < DAT_00410cc4 + DAT_00410cc0) {
        iVar7 = (DAT_00410cc4 + DAT_00410cc0) - DAT_00410cc0;
        puVar6 = (undefined4 *)(DAT_00410cc0 * 0xc + 0x410c50);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar2 = DAT_00410ccc;
      iVar7 = *piVar4;
      if (iVar7 == -0x3fffff72) {
        DAT_00410ccc = 0x83;
      }
      else if (iVar7 == -0x3fffff70) {
        DAT_00410ccc = 0x81;
      }
      else if (iVar7 == -0x3fffff6f) {
        DAT_00410ccc = 0x84;
      }
      else if (iVar7 == -0x3fffff6d) {
        DAT_00410ccc = 0x85;
      }
      else if (iVar7 == -0x3fffff73) {
        DAT_00410ccc = 0x82;
      }
      else if (iVar7 == -0x3fffff71) {
        DAT_00410ccc = 0x86;
      }
      else if (iVar7 == -0x3fffff6e) {
        DAT_00410ccc = 0x8a;
      }
      (*pcVar1)(8,DAT_00410ccc);
      DAT_00410ccc = uVar2;
      DAT_00413590 = (void *)uVar3;
      return -1;
    }
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    DAT_00413590 = (void *)uVar3;
    return -1;
  }
  return -1;
}


/* ==== FUN_00407520 @ 00407520 ==== */

int * __cdecl FUN_00407520(int param_1)

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


/* ==== _filbuf @ 00407570 ==== */

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


/* ==== _read @ 00407660 ==== */

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
          errno = 9;
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
                  goto LAB_00407848;
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
                      goto LAB_00407848;
                    }
                    _lseek(fh,-1,1);
                    if ((char)cnt != '\n') goto LAB_00407845;
                  }
                  else {
                    if ((char)cnt == '\n') {
                      *pcVar8 = '\n';
                      goto LAB_00407848;
                    }
                    *pcVar8 = '\r';
                    pcVar8 = pcVar8 + 1;
                    *(char *)(iVar6 + 5 + *local_8) = (char)cnt;
                  }
                }
                else {
LAB_00407845:
                  *pcVar8 = '\r';
LAB_00407848:
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
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _callnewh @ 004078c0 ==== */

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


/* ==== _heap_init @ 004078e0 ==== */

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


/* ==== __sbh_new_region @ 00407920 ==== */

void __sbh_new_region(void)

{
  bool bVar1;
  undefined4 *lpAddress;
  LPVOID pvVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **lpMem;
  undefined4 *puVar5;
  
  if (DAT_00410ce8 == -1) {
    lpMem = &PTR_LOOP_00410cd8;
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
      if (lpMem == &PTR_LOOP_00410cd8) {
        if (PTR_LOOP_00410cd8 == (undefined *)0x0) {
          PTR_LOOP_00410cd8 = (undefined *)&PTR_LOOP_00410cd8;
        }
        if (PTR_LOOP_00410cdc == (undefined *)0x0) {
          PTR_LOOP_00410cdc = (undefined *)&PTR_LOOP_00410cd8;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_00410cd8;
        lpMem[1] = PTR_LOOP_00410cdc;
        PTR_LOOP_00410cdc = (undefined *)lpMem;
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
  if (lpMem != &PTR_LOOP_00410cd8) {
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== __sbh_release_region @ 00407a90 ==== */

void __cdecl __sbh_release_region(void *preg)

{
  VirtualFree(*(LPVOID *)((int)preg + 0x10),0,0x8000);
  if (PTR_LOOP_00412cf8 == preg) {
    PTR_LOOP_00412cf8 = *(undefined **)((int)preg + 4);
  }
  if (preg != &PTR_LOOP_00410cd8) {
    **(undefined4 **)((int)preg + 4) = *(undefined4 *)preg;
    *(undefined4 *)(*(int *)preg + 4) = *(undefined4 *)((int)preg + 4);
    HeapFree(_crtheap,0,preg);
    return;
  }
  DAT_00410ce8 = 0xffffffff;
  return;
}


/* ==== __sbh_decommit_pages @ 00407af0 ==== */

void __cdecl __sbh_decommit_pages(int count)

{
  BOOL BVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *preg;
  undefined *puVar5;
  
  preg = PTR_LOOP_00410cdc;
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
            DAT_0041359c = DAT_0041359c + -1;
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
    if ((puVar5 == PTR_LOOP_00410cdc) || (preg = puVar5, count < 1)) {
      return;
    }
  } while( true );
}


/* ==== __sbh_find_block @ 00407bc0 ==== */

void __cdecl __sbh_find_block(void *pblock,void *ppreg,void *pppage)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_00410cd8;
  while ((pblock <= ppuVar1[4] || (ppuVar1[5] <= pblock))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_00410cd8) {
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


/* ==== __sbh_free_block @ 00407c20 ==== */

void __cdecl __sbh_free_block(void *preg,void *ppage,void *pmap)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (int)ppage - *(int *)((int)preg + 0x10) >> 0xc;
  piVar1 = (int *)((int)preg + iVar2 * 8 + 0x18);
  *piVar1 = *(int *)((int)preg + iVar2 * 8 + 0x18) + (uint)*(byte *)pmap;
  *(undefined1 *)pmap = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_0041359c = DAT_0041359c + 1, DAT_0041359c == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}


/* ==== __sbh_alloc_block @ 00407c80 ==== */

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
  
  piVar11 = (int *)PTR_LOOP_00412cf8;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      pvVar8 = (void *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX != 0) {
            PTR_LOOP_00412cf8 = (undefined *)piVar11;
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
            PTR_LOOP_00412cf8 = (undefined *)piVar11;
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
  } while (piVar11 != (int *)PTR_LOOP_00412cf8);
  ppuVar7 = &PTR_LOOP_00410cd8;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_00410cd8) {
      __sbh_new_region();
      if (extraout_EAX_01 == (undefined *)0x0) {
        return;
      }
      piVar11 = *(int **)(extraout_EAX_01 + 0x10);
      *(char *)(piVar11 + 2) = (char)para_req;
      PTR_LOOP_00412cf8 = extraout_EAX_01;
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
  PTR_LOOP_00412cf8 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)para_req;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -para_req;
  piVar11[1] = piVar11[1] - para_req;
  *piVar11 = (int)piVar11 + para_req + 8;
  return;
}


/* ==== __sbh_alloc_block_from_page @ 00407ec0 ==== */

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
            goto LAB_0040800f;
          }
          *(byte **)ppage = pbVar6 + para_req;
          *(uint *)((int)ppage + 4) = uVar5 - para_req;
          goto LAB_00408016;
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
LAB_0040800f:
            *(undefined4 *)((int)ppage + 4) = 0;
          }
LAB_00408016:
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


/* ==== _lseek @ 00408040 ==== */

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
        errno = 9;
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
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== ftell @ 00408100 ==== */

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
      errno = 0x16;
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
  if ((*(byte *)((int)stream + 0xc) & 1) == 0) goto LAB_00408275;
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
LAB_0040826c:
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
      if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 4) != 0) goto LAB_0040826c;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_00408275:
  return local_4 + local_8;
}


/* ==== __setdefaultprecision @ 004082b0 ==== */

/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 1998 Release */

void __setdefaultprecision(void)

{
  FUN_0040a520((void *)0x10000,0x30000);
  return;
}


/* ==== _ms_p5_test_fdiv @ 004082d0 ==== */

/* WARNING: Removing unreachable block (ram,0x00408311) */

int _ms_p5_test_fdiv(void)

{
  return 0;
}


/* ==== _ms_p5_mp_test_fdiv @ 00408320 ==== */

int _ms_p5_mp_test_fdiv(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  
  hModule = GetModuleHandleA("KERNEL32");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent");
    if (pFVar1 != (FARPROC)0x0) {
      iVar2 = (*pFVar1)(0);
      return iVar2;
    }
  }
  iVar2 = _ms_p5_test_fdiv();
  return iVar2;
}


/* ==== _forcdecpt @ 00408350 ==== */

void __cdecl _forcdecpt(char *buffer)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = tolower((int)*buffer);
  if (iVar3 != 0x65) {
    do {
      buffer = buffer + 1;
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*buffer * 2] & 4;
      }
      else {
        uVar4 = _isctype((int)*buffer,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *buffer;
  *buffer = __decimal_point;
  do {
    buffer = buffer + 1;
    cVar1 = *buffer;
    *buffer = cVar2;
    cVar2 = cVar1;
  } while (*buffer != '\0');
  return;
}


/* ==== _cropzeros @ 004083b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _cropzeros(char *buf)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  cVar1 = *buf;
  while ((cVar1 != '\0' && (cVar1 != __decimal_point))) {
    pcVar2 = buf + 1;
    buf = buf + 1;
    cVar1 = *pcVar2;
  }
  pcVar2 = buf + 1;
  if (*buf != '\0') {
    cVar1 = *pcVar2;
    while (((cVar1 != '\0' && (cVar1 != 'e')) && (cVar1 != 'E'))) {
      pcVar3 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar3;
    }
    cVar1 = pcVar2[-1];
    pcVar3 = pcVar2;
    while (pcVar4 = pcVar3 + -1, cVar1 == '0') {
      cVar1 = pcVar3[-2];
      pcVar3 = pcVar4;
    }
    if (*pcVar4 == __decimal_point) {
      pcVar4 = pcVar3 + -2;
    }
    cVar1 = *pcVar2;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
    while (cVar1 != '\0') {
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar4 = pcVar4 + 1;
      *pcVar4 = cVar1;
    }
  }
  return;
}


/* ==== _positive @ 00408420 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _positive(double *arg)

{
  if (0.0 <= *arg) {
    return 1;
  }
  return 0;
}


/* ==== _fassign @ 00408440 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _fassign(int flag,char *argument,char *number)

{
  uint uStack_8;
  undefined4 uStack_4;
  
  if (flag != 0) {
    FUN_0040ab10(&uStack_8,(byte *)number);
    *(uint *)argument = uStack_8;
    *(undefined4 *)(argument + 4) = uStack_4;
    return;
  }
  FUN_0040ab50((uint *)&number,(byte *)number);
  *(char **)argument = number;
  return;
}


/* ==== _cftoe @ 004084a0 ==== */

char __cdecl _cftoe(double *pvalue,char *buf,int ndec,int caps)

{
  int *pflt;
  char *pcVar1;
  int iVar2;
  char *unaff_ESI;
  char *pcVar3;
  void *unaff_EDI;
  int *piVar4;
  
  piVar4 = DAT_004135a0;
  if (DAT_004135a4 == '\0') {
    _fltout2(*pvalue,unaff_EDI,unaff_ESI);
    _fptostr(buf + (uint)(*pflt == 0x2d) + (uint)(0 < ndec),ndec + 1,pflt);
    piVar4 = pflt;
  }
  else {
    _shift(buf + (*DAT_004135a0 == 0x2d),(uint)(0 < ndec));
  }
  pcVar1 = buf;
  if (*piVar4 == 0x2d) {
    *buf = '-';
    pcVar1 = buf + 1;
  }
  if (0 < ndec) {
    *pcVar1 = pcVar1[1];
    pcVar1 = pcVar1 + 1;
    *pcVar1 = __decimal_point;
  }
  pcVar3 = pcVar1 + ndec + (uint)(DAT_004135a4 == '\0');
  builtin_strncpy(pcVar1 + ndec + (uint)(DAT_004135a4 == '\0'),"e+000",6);
  if (caps != 0) {
    *pcVar3 = 'E';
  }
  if (*(char *)piVar4[3] != '0') {
    iVar2 = piVar4[1] + -1;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
      pcVar3[1] = '-';
    }
    if (99 < iVar2) {
      pcVar3[2] = pcVar3[2] +
                  (((char)(iVar2 / 100) + (char)(iVar2 >> 0x1f)) -
                  (char)((longlong)iVar2 * 0x51eb851f >> 0x3f));
      iVar2 = iVar2 % 100;
    }
    if (9 < iVar2) {
      pcVar3[3] = pcVar3[3] +
                  (((char)(iVar2 / 10) + (char)(iVar2 >> 0x1f)) -
                  (char)((longlong)iVar2 * 0x66666667 >> 0x3f));
      iVar2 = iVar2 % 10;
    }
    pcVar3[4] = pcVar3[4] + (char)iVar2;
  }
  return (char)buf;
}


/* ==== _cftof @ 004085e0 ==== */

char __cdecl _cftof(double *pvalue,char *buf,int ndec)

{
  int iVar1;
  int *pflt;
  uint uVar2;
  char *unaff_ESI;
  int *piVar3;
  void *unaff_EDI;
  char *pcVar4;
  
  piVar3 = DAT_004135a0;
  if (DAT_004135a4 == '\0') {
    _fltout2(*pvalue,unaff_EDI,unaff_ESI);
    _fptostr(buf + (*pflt == 0x2d),pflt[1] + ndec,pflt);
    piVar3 = pflt;
  }
  else if (DAT_004135a8 == ndec) {
    iVar1 = DAT_004135a8 + (uint)(*DAT_004135a0 == 0x2d);
    buf[iVar1] = '0';
    (buf + iVar1)[1] = '\0';
  }
  pcVar4 = buf;
  if (*piVar3 == 0x2d) {
    *buf = '-';
    pcVar4 = buf + 1;
  }
  if (piVar3[1] < 1) {
    _shift(pcVar4,1);
    *pcVar4 = '0';
    pcVar4 = pcVar4 + 1;
  }
  else {
    pcVar4 = pcVar4 + piVar3[1];
  }
  if (0 < ndec) {
    _shift(pcVar4,1);
    *pcVar4 = __decimal_point;
    iVar1 = piVar3[1];
    if (iVar1 < 0) {
      if ((DAT_004135a4 != '\0') || (-iVar1 <= ndec)) {
        ndec = -iVar1;
      }
      _shift(pcVar4 + 1,ndec);
      uVar2 = (uint)ndec >> 2;
      pcVar4 = pcVar4 + 1;
      while (uVar2 != 0) {
        uVar2 = uVar2 - 1;
        builtin_strncpy(pcVar4,"0000",4);
        pcVar4 = pcVar4 + 4;
      }
      for (uVar2 = ndec & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar4 = '0';
        pcVar4 = pcVar4 + 1;
      }
    }
  }
  return (char)buf;
}


/* ==== _cftog @ 004086e0 ==== */

char __cdecl _cftog(double *pvalue,char *buf,int ndec,int caps)

{
  char cVar1;
  int *pflt;
  char *buf_00;
  char *unaff_ESI;
  void *unaff_EDI;
  
  _fltout2(*pvalue,unaff_EDI,unaff_ESI);
  DAT_004135a8 = pflt[1] + -1;
  buf_00 = buf + (*pflt == 0x2d);
  DAT_004135a0 = pflt;
  _fptostr(buf_00,ndec,pflt);
  DAT_004135ac = DAT_004135a8 < DAT_004135a0[1] + -1;
  DAT_004135a8 = DAT_004135a0[1] + -1;
  if ((-5 < DAT_004135a8) && (DAT_004135a8 < ndec)) {
    if ((bool)DAT_004135ac) {
      cVar1 = *buf_00;
      while (cVar1 != '\0') {
        cVar1 = buf_00[1];
        buf_00 = buf_00 + 1;
      }
      buf_00[-1] = '\0';
    }
    cVar1 = FUN_004087c0(pvalue,buf,ndec);
    return cVar1;
  }
  cVar1 = FUN_00408790(pvalue,buf,ndec,caps);
  return cVar1;
}


/* ==== FUN_00408790 @ 00408790 ==== */

void __cdecl FUN_00408790(double *param_1,undefined1 *param_2,int param_3,int param_4)

{
  DAT_004135a4 = 1;
  _cftoe(param_1,param_2,param_3,param_4);
  DAT_004135a4 = 0;
  return;
}


/* ==== FUN_004087c0 @ 004087c0 ==== */

void __cdecl FUN_004087c0(double *param_1,char *param_2,uint param_3)

{
  DAT_004135a4 = 1;
  _cftof(param_1,param_2,param_3);
  DAT_004135a4 = 0;
  return;
}


/* ==== _cfltcvt @ 004087f0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _cfltcvt(double *arg,char *buffer,int format,int precision,int caps)

{
  if ((format != 0x65) && (format != 0x45)) {
    if (format == 0x66) {
      _cftof(arg,buffer,precision);
      return;
    }
    _cftog(arg,buffer,precision,caps);
    return;
  }
  _cftoe(arg,buffer,precision,caps);
  return;
}


/* ==== _shift @ 00408860 ==== */

void __cdecl _shift(char *s,int dist)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if (dist != 0) {
    uVar2 = 0xffffffff;
    pcVar3 = s;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    memmove(s + dist,s,~uVar2);
  }
  return;
}


/* ==== _write @ 00408890 ==== */

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
        errno = 0x1c;
        _doserrno = 0;
        return -1;
      }
      if (local_414 == 5) {
        _doserrno = local_414;
        errno = 9;
        return -1;
      }
      _dosmaperr(local_414);
      return -1;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _setenvp @ 00408ab0 ==== */

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


/* ==== _setargv @ 00408ba0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _setargv(void)

{
  char **argv;
  char *cmdstart;
  int local_8;
  int local_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_004135b0,0x104);
  _DAT_004134fc = &DAT_004135b0;
  cmdstart = _acmdln;
  if (*_acmdln == '\0') {
    cmdstart = &DAT_004135b0;
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


/* ==== parse_cmdline @ 00408c40 ==== */

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
      if (((*(byte *)((int)&DAT_004136c0 + bVar2 + 1) & 4) != 0) &&
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
      if ((*(byte *)((int)numchars + 0x4136c1) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if ((byte *)args != (byte *)0x0) {
          *args = *pbVar7;
          args = args + 1;
        }
        pbVar7 = (byte *)(cmdstart + 2);
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_00408d19;
      cmdstart = (char *)pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_00408d19:
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
          if ((*(byte *)((int)&DAT_004136c0 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_00408e15;
        }
        if ((*(byte *)((int)&DAT_004136c0 + bVar2 + 1) & 4) != 0) {
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
LAB_00408e15:
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


/* ==== __crtGetEnvironmentStringsA @ 00408e50 ==== */

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
  if (DAT_004136b8 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr == (LPWCH)0x0) {
      pCVar8 = GetEnvironmentStrings();
      if (pCVar8 == (LPCH)0x0) {
        return;
      }
      DAT_004136b8 = 2;
    }
    else {
      DAT_004136b8 = 1;
    }
  }
  if (DAT_004136b8 == 1) {
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
  else if ((DAT_004136b8 == 2) &&
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


/* ==== _setmbcp @ 00408fb0 ==== */

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
  
  CodePage = FUN_004091a0(codepage);
  if (CodePage == DAT_004137c4) {
    return 0;
  }
  if (CodePage == 0) {
    FUN_00409250();
    return 0;
  }
  iVar10 = 0;
  pUVar5 = &DAT_00412e70;
  do {
    if (*pUVar5 == CodePage) {
      puVar14 = &DAT_004136c0;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined1 *)puVar14 = 0;
      uVar7 = 0;
      iVar10 = iVar10 * 0x30;
      pbVar12 = (byte *)(iVar10 + 0x412e80);
      do {
        bVar3 = *pbVar12;
        for (pbVar13 = pbVar12; (bVar3 != 0 && (bVar3 = pbVar13[1], bVar3 != 0));
            pbVar13 = pbVar13 + 2) {
          uVar8 = (uint)*pbVar13;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_00412e68)[uVar7];
            do {
              pbVar2 = (byte *)((int)&DAT_004136c0 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          bVar3 = pbVar13[2];
        }
        uVar7 = uVar7 + 1;
        pbVar12 = pbVar12 + 8;
      } while (uVar7 < 4);
      DAT_004137c4 = CodePage;
      _DAT_004137c8 = FUN_004091f0(CodePage);
      _DAT_004137d0 = *(undefined4 *)(iVar10 + 0x412e74);
      _DAT_004137d4 = *(undefined4 *)(iVar10 + 0x412e78);
      _DAT_004137d8 = *(undefined4 *)(iVar10 + 0x412e7c);
      return 0;
    }
    pUVar5 = pUVar5 + 0xc;
    iVar10 = iVar10 + 1;
  } while (pUVar5 < &DAT_00412f60);
  BVar6 = GetCPInfo(CodePage,&local_14);
  if (BVar6 != 1) {
    if (DAT_004137dc == 0) {
      return -1;
    }
    FUN_00409250();
    return 0;
  }
  puVar14 = &DAT_004136c0;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined1 *)puVar14 = 0;
  if (local_14.MaxCharSize < 2) {
    DAT_004137c4 = 0;
    _DAT_004137c8 = 0;
  }
  else {
    if (local_14.LeadByte[0] != '\0') {
      pBVar11 = local_14.LeadByte + 1;
      do {
        bVar3 = *pBVar11;
        if (bVar3 == 0) break;
        for (uVar7 = (uint)pBVar11[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
          *(byte *)((int)&DAT_004136c0 + uVar7 + 1) = *(byte *)((int)&DAT_004136c0 + uVar7 + 1) | 4;
        }
        pBVar1 = pBVar11 + 1;
        pBVar11 = pBVar11 + 2;
      } while (*pBVar1 != 0);
    }
    uVar7 = 1;
    do {
      *(byte *)((int)&DAT_004136c0 + uVar7 + 1) = *(byte *)((int)&DAT_004136c0 + uVar7 + 1) | 8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0xff);
    DAT_004137c4 = CodePage;
    _DAT_004137c8 = FUN_004091f0(CodePage);
  }
  _DAT_004137d0 = 0;
  _DAT_004137d4 = 0;
  _DAT_004137d8 = 0;
  return 0;
}


/* ==== FUN_004091a0 @ 004091a0 ==== */

int __cdecl FUN_004091a0(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_004137dc = 1;
                    /* WARNING: Could not recover jumptable at 0x004091bd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_004137dc = 1;
                    /* WARNING: Could not recover jumptable at 0x004091d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_00413578;
  }
  DAT_004137dc = (uint)bVar2;
  return param_1;
}


/* ==== FUN_004091f0 @ 004091f0 ==== */

undefined4 __cdecl FUN_004091f0(undefined4 param_1)

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


/* ==== FUN_00409250 @ 00409250 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00409250(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_004136c0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_004137c4 = 0;
  _DAT_004137c8 = 0;
  _DAT_004137d0 = 0;
  _DAT_004137d4 = 0;
  _DAT_004137d8 = 0;
  return;
}


/* ==== __initmbctable @ 00409280 ==== */

int __initmbctable(void)

{
  int iVar1;
  
  iVar1 = _setmbcp(-3);
  return iVar1;
}


/* ==== __global_unwind2 @ 00409290 ==== */

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x4092a8,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


/* ==== __local_unwind2 @ 004092d2 ==== */

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
  puStack_18 = &LAB_004092b0;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_00409366();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}


/* ==== FUN_00409366 @ 00409366 ==== */

void FUN_00409366(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_00412f68 = *(undefined4 *)(unaff_EBP + 8);
  DAT_00412f64 = in_EAX;
  DAT_00412f6c = unaff_EBP;
  return;
}


/* ==== FUN_00409445 @ 00409445 ==== */

void FUN_00409445(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* ==== _FF_MSGBANNER @ 00409460 ==== */

void _FF_MSGBANNER(void)

{
  if ((DAT_00413554 == 1) || ((DAT_00413554 == 0 && (DAT_00410c34 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_004137e0 != (code *)0x0) {
      (*DAT_004137e0)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}


/* ==== _NMSG_WRITE @ 004094a0 ==== */

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
  
  piVar2 = &DAT_00412f70;
  iVar8 = 0;
  do {
    if (rterrnum == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar8 = iVar8 + 1;
  } while (piVar2 < &DAT_00413000);
  if (rterrnum == (&DAT_00412f70)[iVar8 * 2]) {
    if ((DAT_00413554 == 1) || ((DAT_00413554 == 0 && (DAT_00410c34 == 1)))) {
      if ((__pioinfo == 0) || (hFile = *(HANDLE *)(__pioinfo + 0x10), hFile == (HANDLE)0xffffffff))
      {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar7 = *(char **)(iVar8 * 8 + 0x412f74);
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
      pcVar7 = *(char **)(iVar8 * 8 + 0x412f74);
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


/* ==== _dosmaperr @ 00409680 ==== */

void __cdecl _dosmaperr(ulong oserrno)

{
  ulong *puVar1;
  int iVar2;
  
  _doserrno = oserrno;
  iVar2 = 0;
  puVar1 = &DAT_00413000;
  do {
    if (oserrno == *puVar1) {
      errno = *(undefined4 *)(iVar2 * 8 + 0x413004);
      return;
    }
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + 1;
  } while (puVar1 < &DAT_00413168);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    errno = 0xd;
    return;
  }
  if ((oserrno < 0xbc) || (errno = 8, 0xca < oserrno)) {
    errno = 0x16;
  }
  return;
}


/* ==== _alloc_osfhnd @ 004096f0 ==== */

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
    if (0x4139ff < (int)piVar3) {
      return -1;
    }
  } while( true );
}


/* ==== _set_osfhnd @ 004097b0 ==== */

int __cdecl _set_osfhnd(int fh,long value)

{
  int iVar1;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (*(int *)((&__pioinfo)[fh >> 5] + iVar1) == -1) {
      if (DAT_00410c34 == 1) {
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
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _free_osfhnd @ 00409860 ==== */

int __cdecl _free_osfhnd(int fh)

{
  int iVar1;
  DWORD nStdHandle;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar1) & 1) != 0) &&
       (*(int *)((&__pioinfo)[fh >> 5] + iVar1) != -1)) {
      if (DAT_00410c34 == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_004098ca;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_004098ca:
      *(undefined4 *)((&__pioinfo)[fh >> 5] + iVar1) = 0xffffffff;
      return 0;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _get_osfhandle @ 00409900 ==== */

long __cdecl _get_osfhandle(int fh)

{
  if (((uint)fh < _nhandle) && ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 1) != 0))
  {
    return *(long *)((&__pioinfo)[fh >> 5] + (fh & 0x1fU) * 8);
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _sopen @ 004099b0 ==== */

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
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_00413824 != 0x8000)))) {
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
      errno = 0x16;
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
    goto switchD_00409a48_caseD_11;
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
      goto LAB_00409adb;
    }
    if (uVar1 != 0) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00409ab6:
    dwCreationDisposition = 3;
    goto LAB_00409adb;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      dwCreationDisposition = 2;
      goto LAB_00409adb;
    }
    if (uVar1 != 0x200) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00409ad6:
    dwCreationDisposition = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_00409a48_caseD_11:
          _doserrno = 0;
          errno = 0x16;
          return -1;
        }
        goto LAB_00409ab6;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_00409ad6;
      if (uVar1 != 0x700) {
        errno = 0x16;
        _doserrno = 0;
        return -1;
      }
    }
    dwCreationDisposition = 1;
  }
LAB_00409adb:
  dwFlagsAndAttributes = 0x80;
  if (((oflag & 0x100U) != 0) && (((byte)pmode & ~(byte)DAT_004134cc & 0x80) == 0)) {
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
    errno = 0x18;
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


/* ==== strncpy @ 00409d70 ==== */

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
        goto joined_r0x00409dae;
      }
    }
    do {
      if (((uint)dst & 3) == 0) {
        uVar5 = n >> 2;
        cVar4 = '\0';
        if (uVar5 == 0) goto LAB_00409deb;
        goto LAB_00409e59;
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
joined_r0x00409e55:
          while( true ) {
            uVar5 = uVar5 - 1;
            dst = (char *)((int)dst + 4);
            if (uVar5 == 0) break;
LAB_00409e59:
            *(uint *)dst = 0;
          }
          cVar4 = '\0';
          n = n & 3;
          if (n != 0) goto LAB_00409deb;
          return cVar3;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *(uint *)dst = uVar2 & 0xff;
          goto joined_r0x00409e55;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *(uint *)dst = uVar2 & 0xffff;
          goto joined_r0x00409e55;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *(uint *)dst = uVar2;
          goto joined_r0x00409e55;
        }
      }
      *(uint *)dst = uVar2;
      dst = (char *)((int)dst + 4);
      uVar5 = uVar5 - 1;
joined_r0x00409dae:
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
LAB_00409deb:
        *dst = cVar4;
        dst = (char *)((int)dst + 1);
      }
      return cVar3;
    }
    n = n - 1;
  } while (n != 0);
  return cVar3;
}


/* ==== memmove @ 00409e70 ==== */

void __cdecl memmove(void *dst,void *src,uint n)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((src < dst) && (dst < (void *)(n + (int)src))) {
    puVar3 = (undefined4 *)((n - 4) + (int)src);
    puVar4 = (undefined4 *)((n - 4) + (int)dst);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = n >> 2;
      uVar2 = n & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return;
        case 2:
          goto switchD_0040a027_caseD_2;
        case 3:
          goto switchD_0040a027_caseD_3;
        }
        goto switchD_0040a027_caseD_1;
      }
    }
    else {
      switch(n) {
      case 0:
        goto switchD_0040a027_caseD_0;
      case 1:
        goto switchD_0040a027_caseD_1;
      case 2:
        goto switchD_0040a027_caseD_2;
      case 3:
        goto switchD_0040a027_caseD_3;
      default:
        uVar1 = n - ((uint)puVar4 & 3);
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
              return;
            case 2:
              goto switchD_0040a027_caseD_2;
            case 3:
              goto switchD_0040a027_caseD_3;
            }
            goto switchD_0040a027_caseD_1;
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
              return;
            case 2:
              goto switchD_0040a027_caseD_2;
            case 3:
              goto switchD_0040a027_caseD_3;
            }
            goto switchD_0040a027_caseD_1;
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
              return;
            case 2:
              goto switchD_0040a027_caseD_2;
            case 3:
              goto switchD_0040a027_caseD_3;
            }
            goto switchD_0040a027_caseD_1;
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
switchD_0040a027_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return;
    case 2:
switchD_0040a027_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return;
    case 3:
switchD_0040a027_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return;
    }
switchD_0040a027_caseD_0:
    return;
  }
  if (((uint)dst & 3) == 0) {
    uVar1 = n >> 2;
    uVar2 = n & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined4 *)dst = *(undefined4 *)src;
        src = (undefined4 *)((int)src + 4);
        dst = (undefined4 *)((int)dst + 4);
      }
      switch(uVar2) {
      case 0:
        return;
      case 2:
        goto switchD_00409ea5_caseD_2;
      case 3:
        goto switchD_00409ea5_caseD_3;
      }
      goto switchD_00409ea5_caseD_1;
    }
  }
  else {
    switch(n) {
    case 0:
      goto switchD_00409ea5_caseD_0;
    case 1:
      goto switchD_00409ea5_caseD_1;
    case 2:
      goto switchD_00409ea5_caseD_2;
    case 3:
      goto switchD_00409ea5_caseD_3;
    default:
      uVar1 = (n - 4) + ((uint)dst & 3);
      switch((uint)dst & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
        src = (void *)((int)src + 3);
        dst = (void *)((int)dst + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined4 *)dst = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            dst = (undefined4 *)((int)dst + 4);
          }
          switch(uVar2) {
          case 0:
            return;
          case 2:
            goto switchD_00409ea5_caseD_2;
          case 3:
            goto switchD_00409ea5_caseD_3;
          }
          goto switchD_00409ea5_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        src = (void *)((int)src + 2);
        dst = (void *)((int)dst + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined4 *)dst = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            dst = (undefined4 *)((int)dst + 4);
          }
          switch(uVar2) {
          case 0:
            return;
          case 2:
            goto switchD_00409ea5_caseD_2;
          case 3:
            goto switchD_00409ea5_caseD_3;
          }
          goto switchD_00409ea5_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        src = (void *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        dst = (void *)((int)dst + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined4 *)dst = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            dst = (undefined4 *)((int)dst + 4);
          }
          switch(uVar2) {
          case 0:
            return;
          case 2:
            goto switchD_00409ea5_caseD_2;
          case 3:
            goto switchD_00409ea5_caseD_3;
          }
          goto switchD_00409ea5_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    *(undefined4 *)((int)dst + (uVar1 - 7) * 4) = *(undefined4 *)((int)src + (uVar1 - 7) * 4);
  case 6:
    *(undefined4 *)((int)dst + (uVar1 - 6) * 4) = *(undefined4 *)((int)src + (uVar1 - 6) * 4);
  case 5:
    *(undefined4 *)((int)dst + (uVar1 - 5) * 4) = *(undefined4 *)((int)src + (uVar1 - 5) * 4);
  case 4:
    *(undefined4 *)((int)dst + (uVar1 - 4) * 4) = *(undefined4 *)((int)src + (uVar1 - 4) * 4);
  case 3:
    *(undefined4 *)((int)dst + (uVar1 - 3) * 4) = *(undefined4 *)((int)src + (uVar1 - 3) * 4);
  case 2:
    *(undefined4 *)((int)dst + (uVar1 - 2) * 4) = *(undefined4 *)((int)src + (uVar1 - 2) * 4);
  case 1:
    *(undefined4 *)((int)dst + (uVar1 - 1) * 4) = *(undefined4 *)((int)src + (uVar1 - 1) * 4);
    src = (void *)((int)src + uVar1 * 4);
    dst = (void *)((int)dst + uVar1 * 4);
  }
  switch(uVar2) {
  case 1:
switchD_00409ea5_caseD_1:
    *(undefined1 *)dst = *(undefined1 *)src;
    return;
  case 2:
switchD_00409ea5_caseD_2:
    *(undefined1 *)dst = *(undefined1 *)src;
    *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
    return;
  case 3:
switchD_00409ea5_caseD_3:
    *(undefined1 *)dst = *(undefined1 *)src;
    *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
    *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
    return;
  }
switchD_00409ea5_caseD_0:
  return;
}


/* ==== _isatty @ 0040a1b0 ==== */

int __cdecl _isatty(int fh)

{
  if (_nhandle <= (uint)fh) {
    return 0;
  }
  return *(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 0x40;
}


/* ==== wctomb @ 0040a1e0 ==== */

int __cdecl wctomb(char *s,ushort wc)

{
  char *lpMultiByteStr;
  int iVar1;
  
  lpMultiByteStr = s;
  if (s == (char *)0x0) {
    return 0;
  }
  if (DAT_00413568 == 0) {
    if (wc < 0x100) {
      *s = (char)wc;
      return 1;
    }
  }
  else {
    s = (char *)0x0;
    iVar1 = WideCharToMultiByte(DAT_00413578,0x220,(LPCWSTR)&wc,1,lpMultiByteStr,__mb_cur_max,
                                (LPCSTR)0x0,(LPBOOL)&s);
    if ((iVar1 != 0) && (s == (char *)0x0)) {
      return iVar1;
    }
  }
  errno = 0x2a;
  return -1;
}


/* ==== __aulldiv @ 0040a260 ==== */

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


/* ==== __aullrem @ 0040a2d0 ==== */

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


/* ==== _flsbuf @ 0040a350 ==== */

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
LAB_0040a470:
    *(uint *)((int)stream + 0xc) = uVar4 | 0x20;
    return -1;
  }
  uVar3 = 0;
  if ((uVar4 & 1) != 0) {
    *(undefined4 *)((int)stream + 4) = 0;
    if ((uVar4 & 0x10) == 0) goto LAB_0040a470;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(uint *)((int)stream + 0xc) = uVar4 & 0xfffffffe;
  }
  uVar4 = *(uint *)((int)stream + 0xc);
  *(undefined4 *)((int)stream + 4) = 0;
  *(uint *)((int)stream + 0xc) = uVar4 & 0xffffffef | 2;
  if ((uVar4 & 0x10c) == 0) {
    if ((stream == &DAT_004109b0) || (stream == &DAT_004109d0)) {
      iVar1 = _isatty(fh);
      if (iVar1 != 0) goto LAB_0040a3c3;
    }
    _getbuf(stream_00);
  }
LAB_0040a3c3:
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


/* ==== _getbuf @ 0040a480 ==== */

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


/* ==== FUN_0040a4e0 @ 0040a4e0 ==== */

uint __thiscall FUN_0040a4e0(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_0040a540(local_8);
  uVar1 = param_2 & param_1 | ~param_2 & uVar1;
  FUN_0040a5e0(uVar1);
  return uVar1;
}


/* ==== FUN_0040a520 @ 0040a520 ==== */

void __cdecl FUN_0040a520(void *param_1,uint param_2)

{
  FUN_0040a4e0(param_1,(uint)param_1,param_2 & 0xfff7ffff);
  return;
}


/* ==== FUN_0040a540 @ 0040a540 ==== */

uint __cdecl FUN_0040a540(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 < 0x401) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
  }
  else if (uVar2 == 0x800) {
    uVar1 = uVar1 | 0x200;
  }
  else if (uVar2 == 0xc00) {
    uVar1 = uVar1 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}


/* ==== FUN_0040a5e0 @ 0040a5e0 ==== */

void FUN_0040a5e0(void)

{
  return;
}


/* ==== FUN_0040a670 @ 0040a670 ==== */

undefined4 __cdecl FUN_0040a670(int param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if ((*(uint *)(param_1 + iVar3 * 4) &
      ~(-1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f))) != 0) {
    return 0;
  }
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    piVar2 = (int *)(param_1 + iVar3 * 4);
    do {
      if (*piVar2 != 0) {
        return 0;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 3);
    return 1;
  }
  return 1;
}


/* ==== FUN_0040a6e0 @ 0040a6e0 ==== */

void __cdecl FUN_0040a6e0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = FUN_0040af90(*(uint *)(param_1 + iVar3 * 4),
                       1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) &
                            0x1f),(uint *)(param_1 + iVar3 * 4));
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (uint *)(param_1 + iVar3 * 4);
    do {
      if (iVar2 == 0) {
        return;
      }
      iVar2 = FUN_0040af90(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return;
}


/* ==== FUN_0040a750 @ 0040a750 ==== */

undefined4 __cdecl FUN_0040a750(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_4;
  
  local_4 = 0;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (((*(uint *)(param_1 + iVar3 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_0040a670(param_1,param_2 + 1), iVar1 == 0)) {
    local_4 = FUN_0040a6e0(param_1,param_2 + -1);
  }
  *(uint *)(param_1 + iVar3 * 4) = *(uint *)(param_1 + iVar3 * 4) & -1 << (bVar2 & 0x1f);
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
    for (iVar1 = 3 - iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  return local_4;
}


/* ==== FUN_0040a7f0 @ 0040a7f0 ==== */

void __cdecl FUN_0040a7f0(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 - (int)param_2;
  iVar2 = 3;
  do {
    *(undefined4 *)((int)param_2 + iVar1) = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* ==== FUN_0040a810 @ 0040a810 ==== */

void __cdecl FUN_0040a810(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


/* ==== FUN_0040a820 @ 0040a820 ==== */

undefined4 __cdecl FUN_0040a820(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  } while (iVar1 < 3);
  return 1;
}


/* ==== FUN_0040a840 @ 0040a840 ==== */

void __cdecl FUN_0040a840(uint *param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  
  iVar1 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  uVar5 = 0;
  bVar2 = (((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2;
  param_2 = 3;
  puVar6 = param_1;
  do {
    uVar4 = *puVar6 >> (bVar2 & 0x1f) | uVar5;
    uVar5 = (~(-1 << (bVar2 & 0x1f)) & *puVar6) << (0x20 - bVar2 & 0x1f);
    *puVar6 = uVar4;
    param_2 = param_2 + -1;
    puVar6 = puVar6 + 1;
  } while (param_2 != 0);
  iVar7 = 2;
  iVar3 = 8;
  do {
    if (iVar7 < iVar1) {
      *(undefined4 *)((int)param_1 + iVar3) = 0;
    }
    else {
      *(undefined4 *)((int)param_1 + iVar3) = *(undefined4 *)((int)param_1 + iVar3 + iVar1 * -4);
    }
    iVar7 = iVar7 + -1;
    iVar3 = iVar3 + -4;
  } while (-1 < iVar3);
  return;
}


/* ==== FUN_0040a900 @ 0040a900 ==== */

undefined4 __cdecl FUN_0040a900(ushort *param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint local_18;
  uint local_14;
  int local_10;
  undefined4 local_c [3];
  
  uVar1 = param_1[5];
  local_14 = *(uint *)(param_1 + 1);
  local_18 = *(uint *)(param_1 + 3);
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  local_10 = (uint)*param_1 << 0x10;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = FUN_0040a820((int *)&local_18);
    if (iVar2 == 0) {
      FUN_0040a810(&local_18);
      uVar3 = 2;
      goto LAB_0040aa81;
    }
  }
  else {
    FUN_0040a7f0((int)local_c,&local_18);
    iVar2 = FUN_0040a750((int)&local_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_0040a810(&local_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_0040aa81;
    }
    if (iVar5 <= iVar2) {
      FUN_0040a7f0((int)&local_18,local_c);
      FUN_0040a840(&local_18,iVar2 - iVar5);
      FUN_0040a750((int)&local_18,param_3[2]);
      FUN_0040a840(&local_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_0040aa81;
    }
    if (*param_3 <= iVar5) {
      FUN_0040a810(&local_18);
      local_18 = local_18 | 0x80000000;
      FUN_0040a840(&local_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_0040aa81;
    }
    iVar5 = param_3[5] + iVar5;
    local_18 = local_18 & 0x7fffffff;
    FUN_0040a840(&local_18,param_3[3]);
  }
  uVar3 = 0;
LAB_0040aa81:
  local_18 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | local_18;
  if (param_3[4] == 0x40) {
    param_2[1] = local_18;
    *param_2 = local_14;
    return uVar3;
  }
  if (param_3[4] == 0x20) {
    *param_2 = local_18;
  }
  return uVar3;
}


/* ==== FUN_0040aad0 @ 0040aad0 ==== */

void __cdecl FUN_0040aad0(ushort *param_1,uint *param_2)

{
  FUN_0040a900(param_1,param_2,(int *)&DAT_00413170);
  return;
}


/* ==== FUN_0040aaf0 @ 0040aaf0 ==== */

void __cdecl FUN_0040aaf0(ushort *param_1,uint *param_2)

{
  FUN_0040a900(param_1,param_2,(int *)&DAT_00413188);
  return;
}


/* ==== FUN_0040ab10 @ 0040ab10 ==== */

void __cdecl FUN_0040ab10(uint *param_1,byte *param_2)

{
  ushort local_c [6];
  
  __strgtold12(local_c,(char **)&param_2,(char *)param_2,0,0,0,0);
  FUN_0040aad0(local_c,param_1);
  return;
}


/* ==== FUN_0040ab50 @ 0040ab50 ==== */

void __cdecl FUN_0040ab50(uint *param_1,byte *param_2)

{
  ushort local_c [6];
  
  __strgtold12(local_c,(char **)&param_2,(char *)param_2,0,0,0,0);
  FUN_0040aaf0(local_c,param_1);
  return;
}


/* ==== _fptostr @ 0040ab90 ==== */

void __cdecl _fptostr(char *buf,int digits,void *pflt)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  
  pcVar5 = *(char **)((int)pflt + 0xc);
  pcVar7 = buf + 1;
  *buf = '0';
  pcVar1 = pcVar7;
  iVar6 = digits;
  if (0 < digits) {
    do {
      cVar2 = *pcVar5;
      if (cVar2 == '\0') {
        cVar2 = '0';
      }
      else {
        pcVar5 = pcVar5 + 1;
      }
      *pcVar1 = cVar2;
      pcVar1 = pcVar1 + 1;
      iVar6 = iVar6 + -1;
      digits = digits + -1;
    } while (digits != 0);
  }
  *pcVar1 = '\0';
  if ((-1 < iVar6) && ('4' < *pcVar5)) {
    cVar2 = pcVar1[-1];
    while (pcVar5 = pcVar1 + -1, cVar2 == '9') {
      *pcVar5 = '0';
      cVar2 = pcVar1[-2];
      pcVar1 = pcVar5;
    }
    *pcVar5 = *pcVar5 + '\x01';
  }
  if (*buf == '1') {
    *(int *)((int)pflt + 4) = *(int *)((int)pflt + 4) + 1;
    return;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar5;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  pcVar7 = pcVar5 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)buf = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    buf = buf + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *buf = *pcVar7;
    pcVar7 = pcVar7 + 1;
    buf = buf + 1;
  }
  return;
}


/* ==== _fltout2 @ 0040ac30 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _fltout2(double x,void *flt,char *resultstr)

{
  undefined4 in_stack_ffffffe4;
  undefined2 uVar1;
  uint local_c;
  uint local_8;
  undefined2 local_4;
  
  uVar1 = (undefined2)((uint)in_stack_ffffffe4 >> 0x10);
  FUN_0040acb0(&local_c,(uint *)&x);
  _DAT_00413810 = FUN_0040b920(local_c,local_8,CONCAT22(uVar1,local_4),0x11,0,&DAT_004137e8);
  _DAT_00413808 = (int)DAT_004137ea;
  _DAT_0041380c = (int)DAT_004137e8;
  _DAT_00413814 = &DAT_004137ec;
  return;
}


/* ==== FUN_0040acb0 @ 0040acb0 ==== */

void __cdecl FUN_0040acb0(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  
  uVar4 = 0x80000000;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  if (uVar3 == 0) {
    uVar4 = 0;
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    iVar6 = 0x3c01;
  }
  else if (uVar3 == 0x7ff) {
    iVar6 = 0x7fff;
  }
  else {
    iVar6 = uVar3 + 0x3c00;
  }
  uVar5 = (ushort)iVar6;
  uVar3 = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | uVar4;
  param_1[1] = uVar3;
  *param_1 = uVar2 << 0xb;
  for (; uVar4 == 0; uVar4 = uVar4 & 0x80000000) {
    uVar4 = uVar3 * 2;
    uVar3 = *param_1 >> 0x1f | uVar4;
    iVar6 = iVar6 + 0xffff;
    uVar5 = (ushort)iVar6;
    param_1[1] = uVar3;
    *param_1 = *param_1 * 2;
  }
  *(ushort *)(param_1 + 2) = uVar5 | uVar1 & 0x8000;
  return;
}


/* ==== _fptrap @ 0040ad70 ==== */

void _fptrap(void)

{
  _amsg_exit(2);
  return;
}


/* ==== __crtMessageBoxA @ 0040ad80 ==== */

int __cdecl __crtMessageBoxA(char *text,char *caption,uint type)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_00413818 != (FARPROC)0x0) {
LAB_0040add0:
    if (DAT_0041381c != (FARPROC)0x0) {
      iVar1 = (*DAT_0041381c)();
    }
    if ((iVar1 != 0) && (DAT_00413820 != (FARPROC)0x0)) {
      iVar1 = (*DAT_00413820)(iVar1);
    }
    iVar1 = (*DAT_00413818)(iVar1,text,caption,type);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_00413818 = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_00413818 != (FARPROC)0x0) {
      DAT_0041381c = GetProcAddress(hModule,"GetActiveWindow");
      DAT_00413820 = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_0040add0;
    }
  }
  return 0;
}


/* ==== _chsize @ 0040ae10 ==== */

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
  
  FUN_0040bd30();
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
            errno = 0xd;
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
      iVar4 = FUN_0040bcb0(in_stack_00001008,0x8000);
      while( true ) {
        cnt = 0x1000;
        if ((int)uVar6 < 0x1000) {
          cnt = uVar6;
        }
        iVar2 = _write(in_stack_00001008,&fh,cnt);
        if (iVar2 == -1) break;
        uVar6 = uVar6 - iVar2;
        if ((int)uVar6 < 1) {
LAB_0040aef1:
          FUN_0040bcb0(in_stack_00001008,iVar4);
          _lseek(in_stack_00001008,pos,0);
          return iVar5;
        }
      }
      if (_doserrno == 5) {
        errno = 0xd;
      }
      iVar5 = -1;
      goto LAB_0040aef1;
    }
  }
  else {
    errno = 9;
  }
  return -1;
}


/* ==== FUN_0040af90 @ 0040af90 ==== */

undefined4 __cdecl FUN_0040af90(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = param_2 + param_1;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}


/* ==== FUN_0040afc0 @ 0040afc0 ==== */

void __cdecl FUN_0040afc0(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = FUN_0040af90(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_0040af90(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = FUN_0040af90(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  FUN_0040af90(param_1[2],param_2[2],param_1 + 2);
  return;
}


/* ==== FUN_0040b030 @ 0040b030 ==== */

void __cdecl FUN_0040b030(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}


/* ==== FUN_0040b060 @ 0040b060 ==== */

void __cdecl FUN_0040b060(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}


/* ==== FUN_0040b090 @ 0040b090 ==== */

void __cdecl FUN_0040b090(char *param_1,int param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  short sVar3;
  uint local_c;
  uint local_8;
  uint local_4;
  
  puVar2 = param_3;
  sVar3 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      local_c = *puVar2;
      local_8 = puVar2[1];
      local_4 = puVar2[2];
      FUN_0040b030(puVar2);
      FUN_0040b030(puVar2);
      FUN_0040afc0(puVar2,&local_c);
      FUN_0040b030(puVar2);
      local_c = (uint)*param_1;
      local_8 = 0;
      local_4 = 0;
      FUN_0040afc0(puVar2,&local_c);
      param_1 = param_1 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  uVar1 = puVar2[2];
  while (uVar1 == 0) {
    sVar3 = sVar3 + -0x10;
    puVar2[2] = puVar2[1] >> 0x10;
    uVar1 = puVar2[2];
    puVar2[1] = *puVar2 >> 0x10 | puVar2[1] << 0x10;
    *puVar2 = *puVar2 << 0x10;
  }
  uVar1 = puVar2[2];
  while ((uVar1 & 0x8000) == 0) {
    FUN_0040b030(puVar2);
    sVar3 = sVar3 + -1;
    uVar1 = puVar2[2];
  }
  *(short *)((int)puVar2 + 10) = sVar3;
  return;
}


/* ==== __strgtold12 @ 0040b190 ==== */

uint __cdecl
__strgtold12(void *pld12,char **p_end_ptr,char *str,int mult12,int scale,int decpt,int implicit_E)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint uVar13;
  char *pcVar14;
  byte *pbVar15;
  int local_60;
  char *local_5c;
  uint local_54;
  byte *local_50;
  int local_4c;
  int local_48;
  uint local_30;
  ushort local_2c;
  undefined2 uStack_2a;
  undefined2 uStack_28;
  char *local_26;
  ushort local_22;
  char local_1c [23];
  char local_5;
  
  local_5c = local_1c;
  iVar8 = 0;
  uVar13 = 0;
  uVar7 = 0;
  local_4c = 1;
  local_54 = 0;
  bVar2 = false;
  bVar4 = false;
  bVar3 = false;
  bVar5 = false;
  bVar6 = false;
  local_48 = 0;
  local_60 = 0;
  local_30 = 0;
  local_50 = (byte *)str;
  for (pbVar11 = (byte *)str;
      (((bVar10 = *pbVar11, bVar10 == 0x20 || (bVar10 == 9)) || (bVar10 == 10)) ||
      (pbVar15 = (byte *)str, bVar10 == 0xd)); pbVar11 = pbVar11 + 1) {
  }
  do {
    bVar10 = *pbVar11;
    pbVar12 = pbVar11 + 1;
    str = (char *)CONCAT31(str._1_3_,bVar10);
    switch(iVar8) {
    case 0:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_0040b662;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 5;
      }
      else if (bVar10 == 0x2b) {
        iVar8 = 2;
        uVar7 = 0;
      }
      else if (bVar10 == 0x2d) {
        iVar8 = 2;
        uVar7 = 0x8000;
      }
      else {
        if (bVar10 != 0x30) goto switchD_0040b452_caseD_2c;
        iVar8 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_0040b662;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 4;
      }
      else {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_0040b452_caseD_2b;
        default:
          goto switchD_0040b452_caseD_2c;
        case 0x30:
switchD_0040b2c6_caseD_30:
          iVar8 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_0040b452_caseD_44;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_0040b662;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 5;
      }
      else {
        if (bVar10 == 0x30) goto switchD_0040b2c6_caseD_30;
        iVar8 = 10;
        pbVar12 = pbVar15;
      }
      break;
    case 3:
      while( true ) {
        bVar2 = true;
        if (__mb_cur_max < 2) {
          uVar9 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)str & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *local_5c = bVar10 - 0x30;
          bVar10 = *pbVar12;
          local_5c = local_5c + 1;
          str = (char *)CONCAT31(str._1_3_,bVar10);
          pbVar12 = pbVar12 + 1;
        }
        else {
          bVar10 = *pbVar12;
          local_60 = local_60 + 1;
          str = (char *)CONCAT31(str._1_3_,bVar10);
          pbVar12 = pbVar12 + 1;
        }
      }
      local_54 = uVar13;
      if (bVar10 != __decimal_point) {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_0040b452_caseD_2b;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_0040b452_caseD_44;
        }
switchD_0040b452_caseD_2c:
        iVar8 = 10;
        goto LAB_0040b662;
      }
      iVar8 = 4;
      break;
    case 4:
      bVar4 = true;
      if (uVar13 == 0) {
        while (bVar10 == 0x30) {
          bVar10 = *pbVar12;
          local_60 = local_60 + -1;
          pbVar12 = pbVar12 + 1;
          str._1_3_ = (undefined3)((uint)str >> 8);
          str = (char *)CONCAT31(str._1_3_,bVar10);
        }
      }
      while( true ) {
        bVar2 = true;
        if (__mb_cur_max < 2) {
          uVar9 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)str & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *local_5c = bVar10 - 0x30;
          local_5c = local_5c + 1;
          local_60 = local_60 + -1;
        }
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      local_54 = uVar13;
      switch(bVar10) {
      case 0x2b:
      case 0x2d:
switchD_0040b452_caseD_2b:
        bVar2 = true;
        pbVar12 = pbVar12 + -1;
        iVar8 = 0xb;
        break;
      default:
        goto switchD_0040b452_caseD_2c;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
switchD_0040b452_caseD_44:
        bVar2 = true;
        iVar8 = 6;
      }
      break;
    case 5:
      bVar4 = true;
      if (__mb_cur_max < 2) {
        uVar9 = (byte)_pctype[(uint)bVar10 * 2] & 4;
      }
      else {
        uVar9 = _isctype((uint)bVar10,4);
      }
      if (uVar9 == 0) {
        iVar8 = 10;
        pbVar12 = pbVar15;
      }
      else {
        iVar8 = 4;
        pbVar12 = pbVar11;
      }
      break;
    case 6:
      pbVar11 = pbVar11 + -1;
      pbVar15 = pbVar11;
      local_50 = pbVar11;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_0040b662;
      }
      if (bVar10 == 0x2b) {
LAB_0040b656:
        iVar8 = 7;
        pbVar15 = pbVar11;
        local_50 = pbVar11;
      }
      else {
        if (bVar10 != 0x2d) goto LAB_0040b546;
LAB_0040b647:
        iVar8 = 7;
        local_4c = -1;
        pbVar15 = pbVar11;
        local_50 = pbVar11;
      }
      break;
    case 7:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_0040b662;
      }
LAB_0040b546:
      if (bVar10 == 0x30) {
        iVar8 = 8;
      }
      else {
        iVar8 = 10;
        pbVar12 = pbVar15;
      }
      break;
    case 8:
      bVar3 = true;
      while (bVar10 == 0x30) {
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
      }
      if (((char)bVar10 < '1') || ('9' < (char)bVar10)) goto switchD_0040b452_caseD_2c;
      iVar8 = 9;
LAB_0040b662:
      pbVar12 = pbVar12 + -1;
      break;
    case 9:
      bVar3 = true;
      local_48 = 0;
      while( true ) {
        if (__mb_cur_max < 2) {
          uVar13 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)str & 0xff,4);
        }
        if (uVar13 == 0) goto LAB_0040b5ca;
        local_48 = (char)bVar10 + -0x30 + local_48 * 10;
        if (0x1450 < local_48) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      local_48 = 0x1451;
LAB_0040b5ca:
      while( true ) {
        if (__mb_cur_max < 2) {
          uVar13 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)str & 0xff,4);
        }
        if (uVar13 == 0) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      iVar8 = 10;
      pbVar12 = pbVar12 + -1;
      uVar13 = local_54;
      pbVar15 = local_50;
      break;
    case 0xb:
      if (implicit_E == 0) goto switchD_0040b452_caseD_2c;
      if (bVar10 == 0x2b) goto LAB_0040b656;
      if (bVar10 == 0x2d) goto LAB_0040b647;
      iVar8 = 10;
      pbVar12 = pbVar11;
      pbVar15 = pbVar11;
      local_50 = pbVar11;
    }
    pbVar11 = pbVar12;
  } while (iVar8 != 10);
  *p_end_ptr = (char *)pbVar12;
  if (bVar2) {
    if (0x18 < uVar13) {
      if ('\x04' < local_5) {
        local_5 = local_5 + '\x01';
      }
      local_5c = local_5c + -1;
      local_60 = local_60 + 1;
      uVar13 = 0x18;
    }
    if (uVar13 == 0) {
      local_2c = 0;
      local_22 = 0;
      str = (char *)0x0;
      pcVar14 = (char *)0x0;
      goto LAB_0040b734;
    }
    cVar1 = local_5c[-1];
    while (cVar1 == '\0') {
      uVar13 = uVar13 - 1;
      local_60 = local_60 + 1;
      cVar1 = local_5c[-2];
      local_5c = local_5c + -1;
    }
    FUN_0040b090(local_1c,uVar13,(uint *)&local_2c);
    if (local_4c < 0) {
      local_48 = -local_48;
    }
    uVar13 = local_48 + local_60;
    if (!bVar3) {
      uVar13 = uVar13 + scale;
    }
    if (!bVar4) {
      uVar13 = uVar13 - decpt;
    }
    if ((int)uVar13 < 0x1451) {
      if (-0x1451 < (int)uVar13) {
        FUN_0040c020((int *)&local_2c,uVar13,mult12);
        pcVar14 = (char *)CONCAT22(uStack_28,uStack_2a);
        str = local_26;
        goto LAB_0040b734;
      }
      bVar6 = true;
    }
    else {
      bVar5 = true;
    }
  }
  local_2c = (ushort)str;
  pcVar14 = str;
  local_22 = local_2c;
LAB_0040b734:
  if (bVar2) {
    if (bVar5) {
      pcVar14 = (char *)0x0;
      local_22 = 0x7fff;
      str = (char *)0x80000000;
      local_2c = 0;
      local_30 = 2;
    }
    else if (bVar6) {
      local_2c = 0;
      local_22 = 0;
      str = (char *)0x0;
      pcVar14 = (char *)0x0;
      local_30 = 1;
    }
  }
  else {
    local_2c = 0;
    local_22 = 0;
    str = (char *)0x0;
    pcVar14 = (char *)0x0;
    local_30 = 4;
  }
  *(ushort *)pld12 = local_2c;
  *(char **)((int)pld12 + 2) = pcVar14;
  *(char **)((int)pld12 + 6) = str;
  *(ushort *)((int)pld12 + 10) = local_22 | uVar7;
  return local_30;
}


/* ==== FUN_0040b920 @ 0040b920 ==== */

undefined4 __cdecl
FUN_0040b920(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  ushort uVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  short *psVar8;
  int iVar9;
  short sVar10;
  int iVar11;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  undefined2 local_10;
  undefined4 uStack_e;
  undefined4 uStack_a;
  undefined1 local_6;
  char cStack_5;
  
  psVar1 = param_6;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xcc;
  local_15 = 0xcc;
  local_14 = 0xcc;
  local_13 = 0xcc;
  uVar5 = param_3 & 0x7fff;
  local_12 = 0xfb;
  local_11 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar5 == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
LAB_0040bb2f:
    *(undefined1 *)(psVar1 + 1) = 0x20;
    *(undefined1 *)((int)psVar1 + 3) = 1;
    *(undefined1 *)(psVar1 + 2) = 0x30;
    *(undefined1 *)((int)psVar1 + 5) = 0;
    return 1;
  }
  if ((short)uVar5 == 0x7fff) {
    *param_6 = 1;
    if (((param_2 != 0x80000000) || (param_1 != 0)) && ((param_2 & 0x40000000) == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e53;
      param_6[4] = 0x4e41;
      *(undefined1 *)((int)param_6 + 3) = 6;
      *(undefined1 *)(param_6 + 5) = 0;
      return 0;
    }
    if ((((param_3 & 0x8000) != 0) && (param_2 == 0xc0000000)) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x44;
      return 0;
    }
    if ((param_2 == 0x80000000) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x46;
      return 0;
    }
    param_6[2] = 0x2331;
    param_6[3] = 0x4e51;
    param_6[4] = 0x4e41;
    *(undefined1 *)((int)param_6 + 3) = 6;
    *(undefined1 *)(param_6 + 5) = 0;
    return 0;
  }
  local_6 = (undefined1)uVar5;
  cStack_5 = (char)(uVar5 >> 8);
  local_10 = 0;
  sVar10 = (short)(((uVar5 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar5 * 0x4d10 >>
                  0x10);
  uStack_a = param_2;
  uStack_e = param_1;
  FUN_0040c020((int *)&local_10,-(int)sVar10,1);
  if (0x3ffe < CONCAT11(cStack_5,local_6)) {
    sVar10 = sVar10 + 1;
    FUN_0040bd60((int *)&local_10,(int *)&local_1c);
  }
  *psVar1 = sVar10;
  iVar9 = param_4;
  if (((param_5 & 1) != 0) && (iVar9 = param_4 + sVar10, param_4 + sVar10 < 1)) {
    *psVar1 = 0;
    goto LAB_0040bb2f;
  }
  if (0x15 < iVar9) {
    iVar9 = 0x15;
  }
  uVar2 = CONCAT11(cStack_5,local_6);
  local_6 = 0;
  cStack_5 = '\0';
  iVar6 = 8;
  iVar11 = uVar2 - 0x3ffe;
  do {
    FUN_0040b030((uint *)&local_10);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if (iVar11 < 0) {
    for (uVar5 = -iVar11 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
      FUN_0040b060((uint *)&local_10);
    }
  }
  psVar1 = psVar1 + 2;
  iVar9 = iVar9 + 1;
  psVar7 = psVar1;
  uVar5 = uStack_e;
  uVar3 = uStack_a;
  if (0 < iVar9) {
    do {
      uStack_a._2_2_ = (undefined2)(uVar3 >> 0x10);
      uStack_a._0_2_ = (undefined2)uVar3;
      uStack_e._2_2_ = (undefined2)(uVar5 >> 0x10);
      uStack_e._0_2_ = (undefined2)uVar5;
      param_1 = CONCAT22((undefined2)uStack_e,local_10);
      param_2 = CONCAT22((undefined2)uStack_a,uStack_e._2_2_);
      param_3 = CONCAT13(cStack_5,CONCAT12(local_6,uStack_a._2_2_));
      uStack_e = uVar5;
      uStack_a = uVar3;
      FUN_0040b030((uint *)&local_10);
      FUN_0040b030((uint *)&local_10);
      FUN_0040afc0((uint *)&local_10,&param_1);
      FUN_0040b030((uint *)&local_10);
      cVar4 = cStack_5 + '0';
      cStack_5 = '\0';
      *(char *)psVar7 = cVar4;
      psVar7 = (short *)((int)psVar7 + 1);
      iVar9 = iVar9 + -1;
      uVar5 = uStack_e;
      uVar3 = uStack_a;
    } while (iVar9 != 0);
  }
  psVar8 = psVar7 + -1;
  if (*(char *)((int)psVar7 + -1) < '5') {
    if (psVar1 <= psVar8) {
      do {
        if ((char)*psVar8 != '0') break;
        psVar8 = (short *)((int)psVar8 + -1);
      } while (psVar1 <= psVar8);
      if (psVar1 <= psVar8) goto LAB_0040bc86;
    }
    *(char *)psVar1 = '0';
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
    return 1;
  }
  if (psVar1 <= psVar8) {
    do {
      if ((char)*psVar8 != '9') break;
      *(char *)psVar8 = '0';
      psVar8 = (short *)((int)psVar8 + -1);
    } while (psVar1 <= psVar8);
    if (psVar1 <= psVar8) {
      *(char *)psVar8 = (char)*psVar8 + '\x01';
      goto LAB_0040bc86;
    }
  }
  psVar8 = (short *)((int)psVar8 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar8 = *(char *)psVar8 + '\x01';
LAB_0040bc86:
  cVar4 = ((char)psVar8 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar4;
  *(undefined1 *)((int)param_6 + cVar4 + 4) = 0;
  return 1;
}


/* ==== FUN_0040bcb0 @ 0040bcb0 ==== */

int __cdecl FUN_0040bcb0(uint param_1,int param_2)

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
          errno = 0x16;
          return -1;
        }
        bVar2 = bVar1 | 0x80;
      }
      *(byte *)((&__pioinfo)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) = bVar2;
      return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
    }
  }
  errno = 9;
  return -1;
}


/* ==== FUN_0040bd30 @ 0040bd30 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_0040bd30(void)

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


/* ==== FUN_0040bd60 @ 0040bd60 ==== */

void __cdecl FUN_0040bd60(int *param_1,int *param_2)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort uVar6;
  ushort *puVar7;
  ushort *puVar8;
  short *local_20;
  int local_18;
  int local_14;
  int local_10;
  byte local_c;
  undefined1 uStack_b;
  undefined2 uStack_a;
  short local_8;
  undefined2 uStack_6;
  undefined2 local_4;
  ushort uStack_2;
  
  local_14 = 0;
  local_c = 0;
  uStack_b = 0;
  uStack_a = 0;
  local_8 = 0;
  uStack_6 = 0;
  uVar3 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar1 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar6 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar4 = uVar3 + uVar1;
  local_4 = 0;
  uStack_2 = 0;
  if (((0x7ffe < uVar1) || (0x7ffe < uVar3)) || (0xbffd < uVar4)) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  if (uVar4 < 0x3fc0) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  if (((uVar1 == 0) && (uVar4 = uVar4 + 1, (param_1[2] & 0x7fffffffU) == 0)) &&
     ((param_1[1] == 0 && (*param_1 == 0)))) {
    *(undefined2 *)((int)param_1 + 10) = 0;
    return;
  }
  if (((uVar3 == 0) && (uVar4 = uVar4 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
     ((param_2[1] == 0 && (*param_2 == 0)))) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  local_20 = &local_8;
  local_18 = 0;
  iVar5 = 5;
  do {
    if (0 < iVar5) {
      puVar8 = (ushort *)(param_2 + 2);
      puVar7 = (ushort *)(local_18 * 2 + (int)param_1);
      local_10 = iVar5;
      do {
        iVar2 = FUN_0040af90(*(uint *)(local_20 + -2),(uint)*puVar8 * (uint)*puVar7,
                             (uint *)(local_20 + -2));
        if (iVar2 != 0) {
          *local_20 = *local_20 + 1;
        }
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + -1;
        local_10 = local_10 + -1;
      } while (local_10 != 0);
    }
    local_20 = local_20 + 1;
    local_18 = local_18 + 1;
    iVar5 = iVar5 + -1;
  } while (0 < iVar5);
  uVar4 = uVar4 + 0xc002;
  while ((0 < (short)uVar4 && ((uStack_2 & 0x8000) == 0))) {
    FUN_0040b030((uint *)&local_c);
    uVar4 = uVar4 - 1;
  }
  if ((short)uVar4 < 1) {
    uVar4 = uVar4 - 1;
    if ((short)uVar4 < 0) {
      iVar5 = -(int)(short)uVar4;
      uVar4 = uVar4 + (short)iVar5;
      do {
        if ((local_c & 1) != 0) {
          local_14 = local_14 + 1;
        }
        FUN_0040b060((uint *)&local_c);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (local_14 != 0) {
      local_c = local_c | 1;
    }
  }
  if ((0x8000 < CONCAT11(uStack_b,local_c)) ||
     (iVar2 = CONCAT22(local_4,uStack_6), iVar5 = CONCAT22(local_8,uStack_a),
     (CONCAT22(uStack_a,CONCAT11(uStack_b,local_c)) & 0x1ffff) == 0x18000)) {
    if (CONCAT22(local_8,uStack_a) == -1) {
      iVar5 = 0;
      if (CONCAT22(local_4,uStack_6) == -1) {
        if (uStack_2 == 0xffff) {
          uStack_2 = 0x8000;
          uVar4 = uVar4 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
        else {
          uStack_2 = uStack_2 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
      }
      else {
        iVar2 = CONCAT22(local_4,uStack_6) + 1;
      }
    }
    else {
      iVar5 = CONCAT22(local_8,uStack_a) + 1;
      iVar2 = CONCAT22(local_4,uStack_6);
    }
  }
  local_8 = (short)((uint)iVar5 >> 0x10);
  uStack_a = (undefined2)iVar5;
  local_4 = (undefined2)((uint)iVar2 >> 0x10);
  uStack_6 = (undefined2)iVar2;
  if (0x7ffe < uVar4) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  *(undefined2 *)param_1 = uStack_a;
  *(uint *)((int)param_1 + 2) = CONCAT22(uStack_6,local_8);
  *(uint *)((int)param_1 + 6) = CONCAT22(uStack_2,local_4);
  *(ushort *)((int)param_1 + 10) = uVar4 | uVar6;
  return;
}


/* ==== FUN_0040c020 @ 0040c020 ==== */

void __cdecl FUN_0040c020(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined2 local_c;
  undefined4 uStack_a;
  undefined2 uStack_6;
  int local_4;
  
  iVar3 = 0x413140;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = 0x4132a0;
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      iVar3 = iVar3 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        piVar2 = (int *)(iVar3 + uVar1 * 0xc);
        if (0x7fff < *(ushort *)(iVar3 + uVar1 * 0xc)) {
          local_c = (undefined2)*piVar2;
          uStack_a._0_2_ = (undefined2)((uint)*piVar2 >> 0x10);
          uStack_a._2_2_ = (undefined2)piVar2[1];
          uStack_6 = (undefined2)((uint)piVar2[1] >> 0x10);
          local_4 = piVar2[2];
          uStack_a = CONCAT22(uStack_a._2_2_,(undefined2)uStack_a) + -1;
          piVar2 = (int *)&local_c;
        }
        FUN_0040bd60(param_1,piVar2);
      }
    }
  }
  return;
}


/* ==== RtlUnwind @ 0040c0b0 ==== */

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x0040c0b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


