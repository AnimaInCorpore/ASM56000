/* ==== _setargv @ 00401000 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _setargv(void)

{
  undefined4 *extraout_EAX;
  int iVar1;
  byte *pbVar2;
  int iStack_8;
  int iStack_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_004136a8,0x104);
  _DAT_004137e8 = &DAT_004136a8;
  pbVar2 = _acmdln;
  if (*_acmdln == 0) {
    pbVar2 = &DAT_004136a8;
  }
  FUN_00404310(pbVar2,(undefined4 *)0x0,(byte *)0x0,&iStack_8,&iStack_4);
  malloc(iStack_4 + iStack_8 * 4);
  if (extraout_EAX == (undefined4 *)0x0) {
    _amsg_exit(8);
  }
  FUN_00404310(pbVar2,extraout_EAX,(byte *)(extraout_EAX + iStack_8),&iStack_8,&iStack_4);
  __argc = iStack_8 + -1;
  __argv = extraout_EAX;
  iVar1 = FUN_00406080();
  if (iVar1 != 0) {
    _amsg_exit(8);
  }
  return;
}


/* ==== main @ 00401010 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl main(int argc,char **argv,char **envp)

{
  char **ppcVar1;
  char cVar2;
  bool bVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  uint local_1c;
  int local_14;
  
  bVar3 = true;
  FUN_0040157b();
  signal(2,FUN_00402b62);
  signal(0xb,FUN_00402b62);
  pcVar4 = FUN_00402a70(*argv);
  pcVar5 = _strrchr(pcVar4,0x2e);
  if (pcVar5 != (char *)0x0) {
    *pcVar5 = '\0';
  }
  iVar6 = FUN_00403777('q',argc,argv);
  DAT_00413264 = (uint)(iVar6 != 0);
  iVar6 = FUN_00403853('e',argc,(int *)argv);
  if (iVar6 != 0) {
    FUN_0040391d((int)argv,iVar6);
  }
  PTR_s_dsplib_0040f148 = pcVar4;
  FUN_00403f7f();
  DAT_00413268 = &DAT_00413470;
  if (DAT_0041367c == 0) {
    DAT_00413680 = 0x2000;
    while ((0x1ff < (int)DAT_00413680 &&
           (DAT_0041367c = FUN_0040408c(DAT_00413680), DAT_0041367c == 0))) {
      DAT_00413680 = (int)DAT_00413680 >> 1;
    }
    if ((int)DAT_00413680 < 0x200) {
      FUN_00404167(s_cannot_allocate_copy_buffer_0040f208);
    }
  }
  if (DAT_00413684 == 0) {
    DAT_00413688 = 0x2000;
    while ((0x1ff < (int)DAT_00413688 &&
           (DAT_00413684 = FUN_0040408c(DAT_00413688), DAT_00413684 == 0))) {
      DAT_00413688 = (int)DAT_00413688 >> 1;
    }
    if ((int)DAT_00413688 < 0x200) {
      FUN_00404167(s_cannot_allocate_input_buffer_0040f224);
    }
  }
  if (DAT_0041368c == 0) {
    DAT_00413690 = 0x2000;
    while ((0x1ff < (int)DAT_00413690 &&
           (DAT_0041368c = FUN_0040408c(DAT_00413690), DAT_0041368c == 0))) {
      DAT_00413690 = (int)DAT_00413690 >> 1;
    }
    if ((int)DAT_00413690 < 0x200) {
      FUN_00404167(s_cannot_allocate_output_buffer_0040f244);
    }
  }
  if ((DAT_00413694 == 0) && (argc < 2)) {
    FUN_00401610();
  }
  DAT_00413040 = (char *)0x0;
  _DAT_00413044 = 0;
  DAT_00413048 = 0;
  if (DAT_00413694 == 0) {
    if (argc < 2) {
      FUN_00403e56();
    }
    while (local_14 = FUN_00403a3d(argc,(int)argv,s_AaCcDdE__e__F_f_LlQqRrUuVvXx__0040f264),
          local_14 != -1) {
      if (__mb_cur_max < 2) {
        local_1c = *(ushort *)(_pctype + local_14 * 2) & 1;
      }
      else {
        local_1c = _isctype(local_14,1);
      }
      if (local_1c != 0) {
        local_14 = tolower(local_14);
      }
      bVar3 = false;
      switch(local_14) {
      case 0x3f:
        FUN_00403e56();
        break;
      default:
        DAT_0040f064 = 7;
        bVar3 = true;
        break;
      case 0x61:
        DAT_0040f064 = 1;
        break;
      case 99:
        DAT_0040f064 = 2;
        break;
      case 100:
        DAT_0040f064 = 3;
        break;
      case 0x65:
        break;
      case 0x66:
        strcpy(&DAT_00413270,DAT_00413040);
        if (DAT_00413270 != '\0') {
          argc = FUN_00403263(argc,(int *)&argv);
        }
        break;
      case 0x6c:
        DAT_0040f064 = 5;
        break;
      case 0x71:
        DAT_00413264 = 1;
        break;
      case 0x72:
        DAT_0040f064 = 6;
        break;
      case 0x75:
        DAT_0040f064 = 7;
        break;
      case 0x76:
        exit(0);
        break;
      case 0x78:
        DAT_0040f064 = 4;
      }
    }
    if (argc <= DAT_00413048) {
      FUN_00403e56();
    }
  }
  if (DAT_00413694 == 0) {
    ppcVar1 = argv + DAT_00413048;
    DAT_00413048 = DAT_00413048 + 1;
    strcpy(&DAT_00413050,*ppcVar1);
    FUN_00402903(&DAT_00413050,&DAT_0040f090);
    pcVar4 = FUN_00402a70(&DAT_00413050);
    if ((pcVar4 != (char *)0x0) && (pcVar4 != &DAT_00413050)) {
      cVar2 = *pcVar4;
      *pcVar4 = '\0';
      strcpy(&DAT_00413470,&DAT_00413050);
      *pcVar4 = cVar2;
    }
    DAT_00413250 = argc - DAT_00413048;
    DAT_00413254 = argv + DAT_00413048;
  }
  else {
    FUN_0040325e();
  }
  FUN_004021c2();
  if ((bVar3) && (DAT_00413250 < 1)) {
    DAT_0040f064 = 5;
  }
  switch(DAT_0040f064) {
  case 1:
  case 2:
  case 6:
  case 7:
    FUN_0040178b();
    break;
  case 3:
    FUN_00401991();
    break;
  case 4:
    FUN_00401ab4();
    break;
  case 5:
    FUN_00401c78();
    break;
  default:
    FUN_0040178b();
  }
  exit(0);
  return 0;
}


/* ==== FUN_0040157b @ 0040157b ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040157b(void)

{
  DAT_00413040 = 0;
  _DAT_00413044 = 0;
  DAT_00413048 = 0;
  DAT_0040f064 = 7;
  DAT_00413050 = 0;
  PTR_DAT_0040f068 = &DAT_00413050;
  DAT_00413250 = 0;
  DAT_00413254 = 0;
  DAT_00413258 = 0;
  DAT_0041325c = 0;
  DAT_00413264 = 0;
  DAT_00413470 = 0;
  DAT_00413694 = 0;
  DAT_00413698 = 0;
  DAT_0041369c = 0;
  return;
}


/* ==== FUN_00401610 @ 00401610 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00401610(void)

{
  int iVar1;
  undefined1 *puVar2;
  void *in_stack_fffffdf4;
  char local_204 [512];
  
  iVar1 = FUN_0040d1a0(0x40fe58);
  iVar1 = _isatty(iVar1);
  DAT_00413698 = 1;
  _DAT_00413260 = _strlen(&DAT_0040f078);
  __setjmp3((undefined4 *)&DAT_00413000,0,in_stack_fffffdf4,iVar1);
  do {
    DAT_0040f064 = 7;
    DAT_00413270 = 0;
    DAT_00413050 = 0;
    PTR_DAT_0040f068 = &DAT_00413050;
    DAT_00413254 = 0;
    DAT_0041325c = 0;
    DAT_00413250 = 0;
    FUN_004021c2();
    if (iVar1 != 0) {
      fprintf(&DAT_0040fe78,&DAT_0040f284,&DAT_0040f078);
    }
    puVar2 = FUN_00404c40(local_204);
    if (puVar2 == (undefined1 *)0x0) {
      exit(0);
    }
    DAT_0040f064 = FUN_00402bbc(local_204);
    switch(DAT_0040f064) {
    case 1:
    case 2:
    case 6:
    case 7:
      FUN_0040178b();
      break;
    case 3:
      FUN_00401991();
      break;
    case 4:
      FUN_00401ab4();
      break;
    case 5:
      FUN_00401c78();
      break;
    case 8:
      exit(0);
    case 9:
      FUN_00403faf();
      break;
    case 10:
      FUN_00403f7f();
    }
  } while( true );
}


/* ==== FUN_0040178b @ 0040178b ==== */

void FUN_0040178b(void)

{
  uint *puVar1;
  int *piVar2;
  
  puVar1 = FUN_00403d88((uint *)&DAT_00413270);
  if (puVar1 == (uint *)0x0) {
    FUN_00404167(s_cannot_create_temporary_file_nam_0040f288);
  }
  DAT_00413678 = FUN_00402275(&DAT_00413270,&DAT_0040f2ac,1);
  if (DAT_00413678 == (int *)0x0) {
    FUN_0040420a(s_cannot_open_temporary_file__s_0040f2b0,&DAT_00413270);
  }
  if (DAT_0040f064 == 2) {
    piVar2 = FUN_00402275(PTR_DAT_0040f068,&DAT_0040f2d0,0);
    if (piVar2 != (int *)0x0) {
      FUN_0040420a(s_library_file__s_already_exists_0040f2d4,PTR_DAT_0040f068);
    }
  }
  else {
    if ((DAT_0040f064 == 1) && (DAT_00413250 < 1)) {
      FUN_00404167(s_add_requires_explicit_module_nam_0040f2f4);
    }
    DAT_00413670 = FUN_00402275(PTR_DAT_0040f068,&DAT_0040f318,1);
    if (DAT_00413670 == (int *)0x0) {
      FUN_0040420a(s_cannot_open_library_file__s_0040f31c,PTR_DAT_0040f068);
    }
    FUN_00401d51(DAT_00413670,DAT_00413678);
    fclose(DAT_00413670);
    DAT_00413670 = (int *)0x0;
  }
  for (piVar2 = (int *)0x0; (int)piVar2 < DAT_00413250; piVar2 = (int *)((int)piVar2 + 1)) {
    if ((char)piVar2[0x104a08] == '\0') {
      if (DAT_0040f064 == 6) {
        piVar2 = *(int **)(DAT_00413254 + (int)piVar2 * 4);
        FUN_00404107(s__s_not_in_library_0040f350,piVar2);
      }
      else {
        piVar2 = DAT_00413678;
        FUN_00401ebe(*(byte **)(DAT_00413254 + (int)DAT_00413678 * 4),DAT_00413678);
        *(undefined1 *)(piVar2 + 0x104a08) = 1;
      }
    }
    else if (DAT_0040f064 == 1) {
      piVar2 = *(int **)(DAT_00413254 + (int)piVar2 * 4);
      FUN_00404107(s__s_already_in_library_0040f338,piVar2);
    }
  }
  fclose(DAT_00413678);
  DAT_00413678 = (int *)0x0;
  if (DAT_0041325c == 0) {
    FUN_00401f58(&DAT_00413270,PTR_DAT_0040f068);
  }
  else {
    FUN_0040420a(s_fatal_errors____s_not_altered_0040f364,PTR_DAT_0040f068);
  }
  return;
}


/* ==== FUN_00401991 @ 00401991 ==== */

void FUN_00401991(void)

{
  uint *puVar1;
  
  if (DAT_00413250 < 1) {
    FUN_00404167(s_delete_requires_explicit_module_n_0040f384);
  }
  DAT_00413670 = FUN_00402275(PTR_DAT_0040f068,&DAT_0040f3ac,1);
  if (DAT_00413670 == (int *)0x0) {
    FUN_0040420a(s_cannot_open_library_file__s_0040f3b0,PTR_DAT_0040f068);
  }
  puVar1 = FUN_00403d88((uint *)&DAT_00413270);
  if (puVar1 == (uint *)0x0) {
    FUN_00404167(s_cannot_create_temporary_file_nam_0040f3cc);
  }
  DAT_00413678 = FUN_00402275(&DAT_00413270,&DAT_0040f3f0,1);
  if (DAT_00413678 == (int *)0x0) {
    FUN_0040420a(s_cannot_open_temporary_file__s_0040f3f4,&DAT_00413270);
  }
  FUN_00401d51(DAT_00413670,DAT_00413678);
  FUN_004028b4();
  fclose(DAT_00413670);
  fclose(DAT_00413678);
  DAT_00413678 = (int *)0x0;
  DAT_00413670 = (int *)0x0;
  if (DAT_0041325c == 0) {
    FUN_00401f58(&DAT_00413270,PTR_DAT_0040f068);
  }
  else {
    FUN_0040420a(s_fatal_errors____s_not_altered_0040f414,PTR_DAT_0040f068);
  }
  return;
}


/* ==== FUN_00401ab4 @ 00401ab4 ==== */

void FUN_00401ab4(void)

{
  char *pcVar1;
  int iVar2;
  char local_408 [512];
  char local_208 [512];
  int local_8;
  
  DAT_00413670 = FUN_00402275(PTR_DAT_0040f068,&DAT_0040f434,1);
  if (DAT_00413670 == (int *)0x0) {
    FUN_0040420a(s_cannot_open_library_file__s_0040f438,PTR_DAT_0040f068);
  }
  while( true ) {
    pcVar1 = FUN_004023e3(DAT_00413670,local_208);
    if (pcVar1 == (char *)0x0) break;
    sscanf(local_208,s___s__s__ld_0040f454,local_408,&local_8);
    iVar2 = FUN_004027e9(local_408);
    if (iVar2 == 0) {
      fseek(DAT_00413670,local_8 + DAT_00413258,1);
    }
    else {
      DAT_00413674 = FUN_00402275(local_408,&DAT_0040f460,0);
      if (DAT_00413674 == (int *)0x0) {
        FUN_00404107(s_cannot_open_module_file__s_0040f464,local_408);
        fseek(DAT_00413670,local_8 + DAT_00413258,1);
      }
      else {
        FUN_004020e6(DAT_00413670,DAT_00413674,local_8);
        if (DAT_00413258 != 0) {
          DAT_00413670[1] = DAT_00413670[1] + -1;
          if (DAT_00413670[1] < 0) {
            _filbuf(DAT_00413670);
          }
          else {
            *DAT_00413670 = *DAT_00413670 + 1;
          }
        }
        fclose(DAT_00413674);
        DAT_00413674 = (int *)0x0;
      }
    }
  }
  fclose(DAT_00413670);
  DAT_00413670 = (int *)0x0;
  FUN_004028b4();
  return;
}


/* ==== FUN_00401c78 @ 00401c78 ==== */

void FUN_00401c78(void)

{
  char *pcVar1;
  int iVar2;
  char local_408 [512];
  char local_208 [512];
  int local_8;
  
  DAT_00413670 = FUN_00402275(PTR_DAT_0040f068,&DAT_0040f480,1);
  if (DAT_00413670 == (int *)0x0) {
    FUN_0040420a(s_cannot_open_library_file__s_0040f484,PTR_DAT_0040f068);
  }
  while( true ) {
    pcVar1 = FUN_004023e3(DAT_00413670,local_208);
    if (pcVar1 == (char *)0x0) break;
    sscanf(local_208,s___s__s__ld_0040f4a0,local_408,&local_8);
    iVar2 = FUN_004027e9(local_408);
    if (iVar2 != 0) {
      FUN_00402762(local_208);
    }
    fseek(DAT_00413670,local_8 + DAT_00413258,1);
  }
  fclose(DAT_00413670);
  DAT_00413670 = (int *)0x0;
  FUN_004028b4();
  return;
}


/* ==== FUN_00401d51 @ 00401d51 ==== */

void __cdecl FUN_00401d51(int *param_1,int *param_2)

{
  char *pcVar1;
  size_t sVar2;
  char local_40c [512];
  char local_20c [512];
  int local_c;
  int local_8;
  
  while (pcVar1 = FUN_004023e3(param_1,local_20c), pcVar1 != (char *)0x0) {
    sscanf(local_20c,s___s__s__ld_0040f4ac,local_40c,&local_8);
    local_c = FUN_004027e9(local_40c);
    if (local_c == 0) {
      if (DAT_00413258 != 0) {
        sVar2 = _strlen(&DAT_0040f06c);
        sprintf(local_40c,&DAT_0040f4b8,&DAT_0040f070,local_20c + sVar2);
        strcpy(local_20c,local_40c);
      }
      FUN_0040260a(param_2,local_20c);
      FUN_004020e6(param_1,param_2,local_8);
      if (DAT_00413258 != 0) {
        param_1[1] = param_1[1] + -1;
        if (param_1[1] < 0) {
          _filbuf(param_1);
        }
        else {
          *param_1 = *param_1 + 1;
        }
      }
    }
    else {
      if (DAT_0040f064 != 3) {
        FUN_00401ebe(*(byte **)(DAT_00413254 + -4 + local_c * 4),param_2);
      }
      fseek(param_1,local_8 + DAT_00413258,1);
    }
  }
  return;
}


/* ==== FUN_00401ebe @ 00401ebe ==== */

void __cdecl FUN_00401ebe(byte *param_1,int *param_2)

{
  char local_204 [512];
  
  DAT_00413674 = FUN_00402275((LPCSTR)param_1,&DAT_0040f4c0,0);
  if (DAT_00413674 == (int *)0x0) {
    FUN_00404107(s_cannot_open_module_file__s_0040f4c4,param_1);
  }
  if (DAT_0041325c == 0) {
    FUN_0040233e(param_1,local_204);
    FUN_0040260a(param_2,local_204);
    FUN_0040205b(DAT_00413674,param_2);
    fclose(DAT_00413674);
    DAT_00413674 = (int *)0x0;
  }
  return;
}


/* ==== FUN_00401f58 @ 00401f58 ==== */

void __cdecl FUN_00401f58(LPCSTR param_1,LPCSTR param_2)

{
  int iVar1;
  
  iVar1 = FUN_004050e0(param_1,param_2);
  if (iVar1 != 0) {
    iVar1 = FUN_00401fa2(param_1,param_2);
    if (iVar1 != 0) {
      FUN_0040420a(s_cannot_rename__s_0040f4e0,param_1);
    }
  }
  remove(param_1);
  return;
}


/* ==== FUN_00401fa2 @ 00401fa2 ==== */

undefined4 __cdecl FUN_00401fa2(LPCSTR param_1,LPCSTR param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint *puVar3;
  
  iVar1 = FUN_004050e0(param_1,param_2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    puVar3 = FUN_00403d88((uint *)&stack0xfffffdfc);
    if (puVar3 == (uint *)0x0) {
      FUN_00404167(s_cannot_create_temporary_file_nam_0040f4f4);
    }
    iVar1 = FUN_004050e0(param_2,&stack0xfffffdfc);
    if (iVar1 == 0) {
      iVar1 = FUN_004050e0(param_1,param_2);
      if (iVar1 == 0) {
        remove(&stack0xfffffdfc);
        uVar2 = 0;
      }
      else {
        iVar1 = FUN_004050e0(&stack0xfffffdfc,param_2);
        if (iVar1 != 0) {
          FUN_0040420a(s_cannot_rename__s_0040f518,&stack0xfffffdfc);
        }
        uVar2 = 0xffffffff;
      }
    }
    else {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}


/* ==== FUN_0040205b @ 0040205b ==== */

void __cdecl FUN_0040205b(int *param_1,int *param_2)

{
  uint n;
  uint uVar1;
  
  FUN_004053b0((int)param_1);
  while (n = FUN_00405270(DAT_0041367c,1,DAT_00413680,param_1), 0 < (int)n) {
    uVar1 = fwrite(DAT_0041367c,1,n,param_2);
    if (uVar1 != n) {
      FUN_00404167(s_error_writing_file_0040f52c);
    }
  }
  if (((param_1[3] & 0x20U) != 0) && ((param_1[3] & 0x10U) == 0)) {
    FUN_00404167(s_error_reading_file_0040f540);
  }
  return;
}


/* ==== FUN_004020e6 @ 004020e6 ==== */

void __cdecl FUN_004020e6(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint n;
  int local_c;
  
  iVar1 = param_3 / (int)DAT_00413680;
  n = param_3 % (int)DAT_00413680;
  for (local_c = 0; local_c < iVar1; local_c = local_c + 1) {
    uVar2 = FUN_00405270(DAT_0041367c,1,DAT_00413680,param_1);
    if ((uVar2 != DAT_00413680) ||
       (uVar2 = fwrite(DAT_0041367c,1,DAT_00413680,param_2), uVar2 != DAT_00413680)) {
      FUN_00404167(s_file_I_O_error_0040f554);
    }
  }
  uVar2 = FUN_00405270(DAT_0041367c,1,n,param_1);
  if ((uVar2 == n) && (uVar2 = fwrite(DAT_0041367c,1,n,param_2), uVar2 == n)) {
    return;
  }
  FUN_00404167(s_file_I_O_error_0040f564);
  return;
}


/* ==== FUN_004021c2 @ 004021c2 ==== */

void FUN_004021c2(void)

{
  int iVar1;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 2000; local_8 = local_8 + 1) {
    (&DAT_00412820)[local_8] = 0;
  }
  for (local_8 = 0; local_c = local_8, local_8 < DAT_00413250 + -1; local_8 = local_8 + 1) {
    while (local_c = local_c + 1, local_c < DAT_00413250) {
      iVar1 = _strcmp(*(char **)(DAT_00413254 + local_8 * 4),*(char **)(DAT_00413254 + local_c * 4))
      ;
      if (iVar1 == 0) {
        FUN_00404107(s_duplicate_module_name__s_0040f574,*(undefined4 *)(DAT_00413254 + local_8 * 4)
                    );
      }
    }
  }
  return;
}


/* ==== FUN_00402275 @ 00402275 ==== */

int * __cdecl FUN_00402275(LPCSTR param_1,char *param_2,int param_3)

{
  int *stream;
  int *piVar1;
  int iVar2;
  
  fopen(param_1,param_2);
  if (stream == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    if (param_3 != 0) {
      iVar2 = _strcmp(param_2,&DAT_0040f590);
      if (iVar2 == 0) {
        setvbuf(stream,DAT_00413684,0,DAT_00413688);
      }
      else {
        iVar2 = _strcmp(param_2,&DAT_0040f594);
        if (iVar2 == 0) {
          setvbuf(stream,DAT_0041368c,0,DAT_00413690);
        }
      }
    }
    iVar2 = _strcmp(param_2,&DAT_0040f598);
    piVar1 = stream;
    if (iVar2 == 0) {
      FUN_00402334(param_1,&DAT_0040f5a4,&DAT_0040f59c);
    }
  }
  return piVar1;
}


/* ==== FUN_00402334 @ 00402334 ==== */

undefined4 FUN_00402334(void)

{
  return 1;
}


/* ==== FUN_0040233e @ 0040233e ==== */

undefined1 * __cdecl FUN_0040233e(byte *param_1,undefined1 *param_2)

{
  int iVar1;
  char *pcVar2;
  int local_38 [5];
  undefined4 local_24;
  long local_14;
  char *local_10;
  char *local_c;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = FUN_0040d280(param_1,local_38);
  if (iVar1 < 0) {
    FUN_0040420a(s_cannot_stat_module__s_0040f5ac,param_1);
  }
  else {
    local_8 = local_24;
  }
  pcVar2 = FUN_00402a70((char *)param_1);
  local_c = FUN_00402ae7(pcVar2);
  local_10 = _strrchr(local_c,0x3b);
  if (local_10 != (char *)0x0) {
    *local_10 = '\0';
  }
  local_14 = time((long *)0x0);
  sprintf(param_2,s__s__s__ld__ld_0040f5c4,&DAT_0040f070,local_c,local_8,local_14);
  return param_2;
}


/* ==== FUN_004023e3 @ 004023e3 ==== */

char * __cdecl FUN_004023e3(int *param_1,char *param_2)

{
  int iVar1;
  uint c;
  uint local_14;
  uint local_10;
  char local_c;
  char *local_8;
  
  FUN_004053b0((int)param_1);
  local_8 = param_2;
  while( true ) {
    param_1[1] = param_1[1] + -1;
    if (param_1[1] < 0) {
      local_10 = _filbuf(param_1);
    }
    else {
      local_10 = (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
    }
    local_c = (char)local_10;
    if ((local_10 == 0xffffffff) || (3 < (uint)((int)local_8 - (int)param_2))) break;
    *local_8 = local_c;
    local_8 = local_8 + 1;
  }
  if ((param_1[3] & 0x10U) == 0) {
    *local_8 = local_c;
    local_8 = local_8 + 1;
    *local_8 = '\0';
    iVar1 = _strncmp(param_2,&DAT_0040f070,4);
    if (iVar1 == 0) {
      DAT_00413258 = 0;
    }
    else {
      iVar1 = _strncmp(param_2,&DAT_0040f06c,3);
      if (iVar1 == 0) {
        DAT_00413258 = 1;
      }
      else {
        FUN_00404167(s_improper_module_header_format_0040f5d4);
      }
    }
    while( true ) {
      param_1[1] = param_1[1] + -1;
      if (param_1[1] < 0) {
        local_14 = _filbuf(param_1);
      }
      else {
        local_14 = (uint)*(byte *)*param_1;
        *param_1 = *param_1 + 1;
      }
      if (((local_14 == 0xffffffff) || (local_14 == 0xd)) || (local_14 == 10)) break;
      local_c = (char)local_14;
      *local_8 = local_c;
      local_8 = local_8 + 1;
    }
    *local_8 = '\0';
    if ((param_1[3] & 0x10U) == 0) {
      if ((param_1[3] & 0x20U) != 0) {
        FUN_00404167(s_cannot_read_module_header_0040f5f4);
      }
      if (local_14 == 0xd) {
        param_1[1] = param_1[1] + -1;
        if (param_1[1] < 0) {
          c = _filbuf(param_1);
        }
        else {
          c = (uint)*(byte *)*param_1;
          *param_1 = *param_1 + 1;
        }
        if ((c != 0xffffffff) && (c != 10)) {
          ungetc(c,param_1);
        }
      }
    }
    else {
      param_2 = (char *)0x0;
    }
  }
  else {
    param_2 = (char *)0x0;
  }
  return param_2;
}


/* ==== FUN_0040260a @ 0040260a ==== */

void __cdecl FUN_0040260a(int *param_1,char *param_2)

{
  int local_14;
  int local_10;
  uint local_c;
  char *local_8;
  
  for (local_8 = param_2; *local_8 != '\0'; local_8 = local_8 + 1) {
    param_1[1] = param_1[1] + -1;
    if (param_1[1] < 0) {
      local_c = _flsbuf((int)*local_8,param_1);
    }
    else {
      *(char *)*param_1 = *local_8;
      local_c = (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
    }
    if (local_c == 0xffffffff) {
      FUN_00404167(s_cannot_write_header_to_library_f_0040f610);
    }
  }
  param_1[1] = param_1[1] + -1;
  if (param_1[1] < 0) {
    local_10 = _flsbuf(0xd,param_1);
  }
  else {
    *(undefined1 *)*param_1 = 0xd;
    local_10 = 0xd;
    *param_1 = *param_1 + 1;
  }
  if (local_10 == -1) {
    FUN_00404167(s_cannot_write_header_to_library_f_0040f634);
  }
  param_1[1] = param_1[1] + -1;
  if (param_1[1] < 0) {
    local_14 = _flsbuf(10,param_1);
  }
  else {
    *(undefined1 *)*param_1 = 10;
    local_14 = 10;
    *param_1 = *param_1 + 1;
  }
  if (local_14 == -1) {
    FUN_00404167(s_cannot_write_header_to_library_f_0040f658);
  }
  return;
}


/* ==== FUN_00402762 @ 00402762 ==== */

void __cdecl FUN_00402762(char *param_1)

{
  undefined4 *extraout_EAX;
  undefined1 local_210 [512];
  long local_10 [2];
  undefined4 local_8;
  
  sscanf(param_1,s___s__s__ld__ld_0040f67c,local_210,&local_8,local_10);
  localtime(local_10);
  fprintf(&DAT_0040fe78,s____s__10ld__02d__02d__02d__02d___0040f68c,0xf,local_210,local_8,
          extraout_EAX[4] + 1,extraout_EAX[3],extraout_EAX[5],extraout_EAX[2],extraout_EAX[1],
          *extraout_EAX);
  return;
}


/* ==== FUN_004027e9 @ 004027e9 ==== */

int __cdecl FUN_004027e9(char *param_1)

{
  char *src;
  int iVar1;
  int local_20c;
  int local_208;
  char local_204 [512];
  
  local_20c = 0;
  if (DAT_00413250 < 1) {
    local_20c = 1;
  }
  else {
    for (local_208 = 0; (local_20c == 0 && (local_208 < DAT_00413250)); local_208 = local_208 + 1) {
      src = FUN_00402a70(*(char **)(DAT_00413254 + local_208 * 4));
      strcpy(local_204,src);
      iVar1 = _strcmp(param_1,local_204);
      if (iVar1 == 0) {
        (&DAT_00412820)[local_208] = 1;
        local_20c = local_208 + 1;
      }
    }
  }
  return local_20c;
}


/* ==== FUN_004028b4 @ 004028b4 ==== */

void FUN_004028b4(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < DAT_00413250; local_8 = local_8 + 1) {
    if ((&DAT_00412820)[local_8] == '\0') {
      FUN_00404107(s__s_not_in_library_0040f6bc,*(undefined4 *)(DAT_00413254 + local_8 * 4));
    }
  }
  return;
}


/* ==== FUN_00402903 @ 00402903 ==== */

void __cdecl FUN_00402903(char *param_1,char *param_2)

{
  bool bVar1;
  size_t sVar2;
  char *pcVar3;
  int iVar4;
  uint local_2c;
  uint local_28;
  char local_14 [8];
  char *local_c;
  char *local_8;
  
  bVar1 = false;
  _strlen(param_2);
  local_8 = FUN_00402a70(param_1);
  sVar2 = _strlen(param_1);
  pcVar3 = _strrchr(param_1,0x2e);
  if ((pcVar3 == (char *)0x0) || (pcVar3 < local_8)) {
    strncpy(local_14,param_2,5);
    for (local_c = local_8; *local_c != '\0'; local_c = local_c + 1) {
      if (__mb_cur_max < 2) {
        local_28 = *(ushort *)(_pctype + *local_c * 2) & 2;
      }
      else {
        local_28 = _isctype((int)*local_c,2);
      }
      if (local_28 != 0) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      for (local_c = local_14; *local_c != '\0'; local_c = local_c + 1) {
        if (__mb_cur_max < 2) {
          local_2c = *(ushort *)(_pctype + *local_c * 2) & 2;
        }
        else {
          local_2c = _isctype((int)*local_c,2);
        }
        if (local_2c != 0) {
          iVar4 = toupper((int)*local_c);
          *local_c = (char)iVar4;
        }
      }
    }
    strcpy(param_1 + sVar2,local_14);
  }
  return;
}


/* ==== FUN_00402a70 @ 00402a70 ==== */

char * __cdecl FUN_00402a70(char *param_1)

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


/* ==== FUN_00402ae7 @ 00402ae7 ==== */

char * __cdecl FUN_00402ae7(char *param_1)

{
  int iVar1;
  uint local_c;
  char *local_8;
  
  for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
    if (__mb_cur_max < 2) {
      local_c = *(ushort *)(_pctype + *local_8 * 2) & 1;
    }
    else {
      local_c = _isctype((int)*local_8,1);
    }
    if (local_c != 0) {
      iVar1 = tolower((int)*local_8);
      *local_8 = (char)iVar1;
    }
  }
  return param_1;
}


/* ==== FUN_00402b62 @ 00402b62 ==== */

void __cdecl FUN_00402b62(int param_1)

{
  if (param_1 == 2) {
    DAT_0041369c = 1;
    FUN_00404167(s_interrupted_0040f6d0);
  }
  else {
    if (param_1 == 0xb) {
      fprintf(PTR_DAT_0040f098,s__s__fatal_segmentation_or_protec_0040f6dc,PTR_s_dsplib_0040f148);
    }
    exit(1);
  }
  return;
}


/* ==== FUN_00402bbc @ 00402bbc ==== */

int __cdecl FUN_00402bbc(char *param_1)

{
  undefined4 *p;
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  uint local_24c;
  uint local_248;
  uint local_244;
  uint local_23c;
  char local_238;
  uint local_234;
  uint local_230;
  uint local_22c;
  undefined4 *local_228;
  undefined4 local_224;
  undefined4 *local_220;
  undefined4 *local_21c;
  undefined4 *local_218;
  int local_214;
  char *local_210;
  int local_20c;
  char local_208 [512];
  char *local_8;
  
  for (local_210 = param_1; *local_210 != '\0'; local_210 = local_210 + 1) {
    if (__mb_cur_max < 2) {
      local_22c = *(ushort *)(_pctype + *local_210 * 2) & 8;
    }
    else {
      local_22c = _isctype((int)*local_210,8);
    }
    if (local_22c == 0) break;
  }
  if (*local_210 == '\0') {
    local_20c = 0;
  }
  else {
    local_8 = local_208;
    for (; *local_210 != '\0'; local_210 = local_210 + 1) {
      if (__mb_cur_max < 2) {
        local_230 = *(ushort *)(_pctype + *local_210 * 2) & 8;
      }
      else {
        local_230 = _isctype((int)*local_210,8);
      }
      if (local_230 != 0) break;
      if (__mb_cur_max < 2) {
        local_234 = *(ushort *)(_pctype + *local_210 * 2) & 1;
      }
      else {
        local_234 = _isctype((int)*local_210,1);
      }
      if (local_234 == 0) {
        local_238 = *local_210;
      }
      else {
        iVar1 = tolower((int)*local_210);
        local_238 = (char)iVar1;
      }
      *local_8 = local_238;
      local_8 = local_8 + 1;
    }
    *local_8 = '\0';
    local_20c = FUN_004031c3(local_208);
    if (local_20c == 0) {
      local_20c = 0;
    }
    else {
      for (; *local_210 != '\0'; local_210 = local_210 + 1) {
        if (__mb_cur_max < 2) {
          local_23c = *(ushort *)(_pctype + *local_210 * 2) & 8;
        }
        else {
          local_23c = _isctype((int)*local_210,8);
        }
        if (local_23c == 0) break;
      }
      if (*local_210 == '\0') {
        if ((local_20c < 8) || (10 < local_20c)) {
          FUN_004040b9(s_command_requires_library_name_0040f724);
          local_20c = 0;
        }
      }
      else {
        local_8 = &DAT_00413050;
        for (; *local_210 != '\0'; local_210 = local_210 + 1) {
          if (__mb_cur_max < 2) {
            local_244 = *(ushort *)(_pctype + *local_210 * 2) & 8;
          }
          else {
            local_244 = _isctype((int)*local_210,8);
          }
          if (local_244 != 0) break;
          *local_8 = *local_210;
          local_8 = local_8 + 1;
        }
        *local_8 = '\0';
        FUN_00402903(&DAT_00413050,&DAT_0040f090);
        local_8 = FUN_00402a70(&DAT_00413050);
        if ((local_8 != (char *)0x0) && (local_8 != &DAT_00413050)) {
          local_214 = (int)*local_8;
          *local_8 = '\0';
          strcpy(&DAT_00413470,&DAT_00413050);
          *local_8 = (char)local_214;
        }
        local_224 = 0;
        local_220 = (undefined4 *)0x0;
        local_21c = &local_224;
        DAT_00413250 = 0;
LAB_00402f4e:
        for (; *local_210 != '\0'; local_210 = local_210 + 1) {
          if (__mb_cur_max < 2) {
            local_248 = *(ushort *)(_pctype + *local_210 * 2) & 8;
          }
          else {
            local_248 = _isctype((int)*local_210,8);
          }
          if (local_248 == 0) break;
        }
        if (*local_210 != '\0') {
          local_8 = local_208;
          for (; *local_210 != '\0'; local_210 = local_210 + 1) {
            if (__mb_cur_max < 2) {
              local_24c = *(ushort *)(_pctype + *local_210 * 2) & 8;
            }
            else {
              local_24c = _isctype((int)*local_210,8);
            }
            if (local_24c != 0) break;
            *local_8 = *local_210;
            local_8 = local_8 + 1;
          }
          *local_8 = '\0';
          local_218 = (undefined4 *)FUN_0040408c(8);
          if (local_218 == (undefined4 *)0x0) {
LAB_00403097:
            FUN_00404167(s_cannot_allocate_module_structure_0040f744);
          }
          else {
            sVar2 = _strlen(local_208);
            local_8 = (char *)FUN_0040408c(sVar2 + 1);
            if (local_8 == (char *)0x0) goto LAB_00403097;
          }
          strcpy(local_8,local_208);
          *local_218 = local_8;
          local_21c[1] = local_218;
          local_21c = local_218;
          local_218[1] = 0;
          DAT_00413250 = DAT_00413250 + 1;
          goto LAB_00402f4e;
        }
        if (DAT_00413250 == 0) {
          DAT_00413254 = (undefined4 *)0x0;
        }
        else {
          DAT_00413254 = (undefined4 *)FUN_0040408c(DAT_00413250 << 2);
          if (DAT_00413254 == (undefined4 *)0x0) {
            FUN_00404167(s_cannot_allocate_module_vector_0040f768);
          }
          local_21c = local_220;
          local_228 = DAT_00413254;
          while (local_21c != (undefined4 *)0x0) {
            pcVar3 = FUN_00402ae7((char *)*local_21c);
            p = local_21c;
            *local_228 = pcVar3;
            local_218 = local_21c;
            local_21c = (undefined4 *)local_21c[1];
            free(p);
            local_228 = local_228 + 1;
          }
        }
      }
    }
  }
  return local_20c;
}


/* ==== FUN_004031c3 @ 004031c3 ==== */

undefined4 __cdecl FUN_004031c3(char *param_1)

{
  size_t _MaxCount;
  int iVar1;
  int local_c;
  
  _MaxCount = _strlen(param_1);
  local_c = 0;
  while( true ) {
    if (DAT_0040f13c <= local_c) {
      FUN_00404107(s_invalid_command__s_0040f7a0,param_1);
      return 0;
    }
    iVar1 = _strncmp(param_1,(&PTR_DAT_0040f0a0)[local_c * 3],_MaxCount);
    if (iVar1 == 0) break;
    local_c = local_c + 1;
  }
  if (*(int *)(&DAT_0040f0a4 + local_c * 0xc) <= (int)_MaxCount) {
    return *(undefined4 *)(&DAT_0040f0a8 + local_c * 0xc);
  }
  FUN_00404107(s_ambiguous_command__s_0040f788,param_1);
  return 0;
}


/* ==== FUN_0040325e @ 0040325e ==== */

void FUN_0040325e(void)

{
  return;
}


/* ==== FUN_00403263 @ 00403263 ==== */

int __cdecl FUN_00403263(int param_1,int *param_2)

{
  int iVar1;
  char *pcVar2;
  int local_1c;
  char *local_14;
  int local_10;
  char *local_c;
  undefined4 local_8;
  
  local_14 = (char *)FUN_0040408c(8);
  if (local_14 == (char *)0x0) {
    FUN_00404167(s_cannot_save_command_file_argumen_0040f7b4);
  }
  *(undefined4 *)local_14 = *(undefined4 *)*param_2;
  local_14[4] = '\0';
  local_14[5] = '\0';
  local_14[6] = '\0';
  local_14[7] = '\0';
  local_10 = 1;
  for (local_1c = 1; local_1c < param_1; local_1c = local_1c + 1) {
    local_8 = *(undefined4 *)(*param_2 + local_1c * 4);
    local_c = (char *)FUN_0040408c(8);
    if (local_c == (char *)0x0) {
      FUN_00404167(s_cannot_save_command_file_argumen_0040f7d8);
    }
    *(undefined4 *)local_c = local_8;
    local_c[4] = '\0';
    local_c[5] = '\0';
    local_c[6] = '\0';
    local_c[7] = '\0';
    *(char **)(local_14 + 4) = local_c;
    local_14 = local_c;
    local_10 = local_10 + 1;
  }
  if (DAT_00413270 != '\0') {
    iVar1 = FUN_004033d4(&DAT_00413270,(int *)&local_14);
    local_10 = local_10 + iVar1;
  }
  pcVar2 = (char *)(local_10 * 4 + 4);
  iVar1 = FUN_0040408c((uint)pcVar2);
  if (iVar1 == 0) {
    pcVar2 = s_cannot_allocate_argument_vector_0040f7fc;
    FUN_00404167(s_cannot_allocate_argument_vector_0040f7fc);
  }
  local_14 = pcVar2;
  for (local_1c = 0; pcVar2 = local_14, local_1c < local_10; local_1c = local_1c + 1) {
    *(undefined4 *)(iVar1 + local_1c * 4) = *(undefined4 *)local_14;
    local_c = local_14;
    local_14 = *(char **)(local_14 + 4);
    free(pcVar2);
  }
  *(undefined4 *)(iVar1 + local_1c * 4) = 0;
  *param_2 = iVar1;
  return local_10;
}


/* ==== FUN_004033d4 @ 004033d4 ==== */

int __cdecl FUN_004033d4(LPCSTR param_1,int *param_2)

{
  int *stream;
  int iVar1;
  uint local_230;
  uint local_22c;
  uint local_228;
  uint local_224;
  uint local_220;
  int local_218;
  char local_214;
  int local_210;
  char local_20c;
  undefined1 local_20b [511];
  int *local_c;
  undefined1 *local_8;
  
  local_210 = 0;
  fopen(param_1,&DAT_0040f81c);
  if (stream == (int *)0x0) {
    FUN_0040420a(s_cannot_open_command_file_0040f820,param_1);
  }
  while ((stream[3] & 0x10U) == 0) {
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
    if ((stream[3] & 0x10U) != 0) break;
    if (local_220 == 0x3b) {
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
    }
    else {
      local_214 = (char)local_220;
      local_20c = local_214;
      local_8 = local_20b;
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
      *local_8 = 0;
      if (local_20c != '\0') {
        local_c = (int *)FUN_0040408c(8);
        if (local_c == (int *)0x0) {
LAB_00403704:
          FUN_00404167(s_cannot_save_command_file_argumen_0040f83c);
        }
        else {
          iVar1 = FUN_0040408c(local_218 + 1);
          *local_c = iVar1;
          if (*local_c == 0) goto LAB_00403704;
        }
        strcpy((char *)*local_c,&local_20c);
        local_c[1] = 0;
        *(int **)(*param_2 + 4) = local_c;
        *param_2 = (int)local_c;
        local_210 = local_210 + 1;
      }
      local_20c = '\0';
    }
  }
  fclose(stream);
  return local_210;
}


/* ==== FUN_00403777 @ 00403777 ==== */

undefined4 __cdecl FUN_00403777(char param_1,int param_2,undefined4 *param_3)

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


/* ==== FUN_00403853 @ 00403853 ==== */

int __cdecl FUN_00403853(char param_1,int param_2,int *param_3)

{
  int iVar1;
  uint local_10;
  int local_c;
  char local_8;
  
  local_c = 1;
  do {
    param_3 = param_3 + 1;
    param_2 = param_2 + -1;
    if (param_2 < 1) {
      return 0;
    }
    if (*(char *)*param_3 == '-') {
      local_8 = *(char *)(*param_3 + 1);
      if (__mb_cur_max < 2) {
        local_10 = *(ushort *)(_pctype + local_8 * 2) & 1;
      }
      else {
        local_10 = _isctype((int)local_8,1);
      }
      if (local_10 != 0) {
        iVar1 = tolower((int)local_8);
        local_8 = (char)iVar1;
      }
      if (local_8 == param_1) {
        return local_c;
      }
    }
    local_c = local_c + 1;
  } while( true );
}


/* ==== FUN_0040391d @ 0040391d ==== */

void __cdecl FUN_0040391d(int param_1,int param_2)

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
    FUN_00404167(s_Illegal_command_line__e_option_0040f860);
  }
  if (*(char *)(*(int *)(param_1 + param_2 * 4) + 3) != '\0') {
    FUN_00404167(s_Invalid_syntax_for_command_line___0040f880);
  }
  local_8 = *(char **)(param_1 + 4 + param_2 * 4);
  if (*local_8 == '-') {
    FUN_00404167(s_Missing_argument_for_command_lin_0040f8ac);
  }
  if ((PTR_DAT_0040f098 != (undefined *)0x0) && (PTR_DAT_0040f098 != &DAT_0040fe98)) {
    fclose(PTR_DAT_0040f098);
  }
  fopen(local_8,local_c);
  PTR_DAT_0040f098 = extraout_EAX;
  if (extraout_EAX == (undefined *)0x0) {
    PTR_DAT_0040f098 = &DAT_0040fe98;
    FUN_00404167(s_Cannot_open_error_file_0040f8d8);
  }
  return;
}


/* ==== FUN_00403a3d @ 00403a3d ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FUN_00403a3d(int param_1,int param_2,char *param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined3 extraout_var;
  
  if (((param_1 == 0) && (param_2 == 0)) && (param_3 == (char *)0x0)) {
    DAT_00413048 = 0;
    DAT_004136a0 = (char *)0x0;
    return -1;
  }
  DAT_00413040 = (char *)0x0;
  _DAT_00413044 = 0;
  if ((DAT_004136a0 == (char *)0x0) || (*DAT_004136a0 == '\0')) {
    if (DAT_00413048 == 0) {
      DAT_00413048 = 1;
    }
    if (((param_1 <= DAT_00413048) || (**(char **)(param_2 + DAT_00413048 * 4) != '-')) ||
       (*(char *)(*(int *)(param_2 + DAT_00413048 * 4) + 1) == '\0')) {
      DAT_00413040 = (char *)0x0;
      _DAT_00413044 = 0;
      return -1;
    }
    iVar3 = _strcmp(*(char **)(param_2 + DAT_00413048 * 4),&DAT_0040f8f0);
    if (iVar3 == 0) {
      DAT_00413048 = DAT_00413048 + 1;
      return -1;
    }
    DAT_004136a0 = (char *)(*(int *)(param_2 + DAT_00413048 * 4) + 1);
    DAT_00413048 = DAT_00413048 + 1;
  }
  cVar1 = *DAT_004136a0;
  DAT_004136a0 = DAT_004136a0 + 1;
  cVar2 = strchr(param_3,(int)cVar1);
  iVar3 = CONCAT31(extraout_var,cVar2);
  if (((iVar3 == 0) || (cVar1 == ':')) || (cVar1 == '?')) {
    fprintf(PTR_DAT_0040f098,s__s__unknown_option___c_0040f8f4,*(undefined4 *)param_2,(int)cVar1);
    iVar3 = 0x3f;
  }
  else {
    if (*(char *)(iVar3 + 1) == ':') {
      if (*DAT_004136a0 == '\0') {
        if (param_1 <= DAT_00413048) {
          fprintf(PTR_DAT_0040f098,s__s____c_argument_missing_0040f90c,*(undefined4 *)param_2,
                  (int)cVar1);
          return 0x3f;
        }
        DAT_00413040 = *(char **)(param_2 + DAT_00413048 * 4);
        DAT_00413048 = DAT_00413048 + 1;
      }
      else {
        DAT_00413040 = DAT_004136a0;
        DAT_004136a0 = (char *)0x0;
      }
      if (*(char *)(iVar3 + 2) == ':') {
        if (param_1 <= DAT_00413048) {
          fprintf(PTR_DAT_0040f098,s__s____c_argument_missing_0040f928,*(undefined4 *)param_2,
                  (int)cVar1);
          return 0x3f;
        }
        _DAT_00413044 = *(undefined4 *)(param_2 + DAT_00413048 * 4);
        DAT_00413048 = DAT_00413048 + 1;
      }
    }
    else if (*(char *)(iVar3 + 1) == '?') {
      if (*DAT_004136a0 == '\0') {
        if (DAT_00413048 < param_1) {
          if (**(char **)(param_2 + DAT_00413048 * 4) == '-') {
            if (*(char *)(*(int *)(param_2 + DAT_00413048 * 4) + 1) == '\0') {
              DAT_00413040 = *(char **)(param_2 + DAT_00413048 * 4);
              DAT_00413048 = DAT_00413048 + 1;
            }
          }
          else if ((DAT_00413048 + 1 < param_1) &&
                  (**(char **)(param_2 + 4 + DAT_00413048 * 4) == '-')) {
            DAT_00413040 = *(char **)(param_2 + DAT_00413048 * 4);
            DAT_00413048 = DAT_00413048 + 1;
          }
        }
      }
      else {
        DAT_00413040 = DAT_004136a0;
        DAT_004136a0 = (char *)0x0;
      }
    }
    iVar3 = (int)cVar1;
  }
  return iVar3;
}


/* ==== FUN_00403d88 @ 00403d88 ==== */

uint * __cdecl FUN_00403d88(uint *param_1)

{
  char cVar1;
  undefined3 extraout_var;
  byte *pbVar2;
  uint *local_8;
  
  strcpy(&DAT_00412ff0,s_lbXXXXXX_0040f080);
  strcpy((char *)param_1,DAT_00413268);
  for (local_8 = param_1; (char)*local_8 != '\0'; local_8 = (uint *)((int)local_8 + 1)) {
  }
  if (param_1 < local_8) {
    local_8 = (uint *)((int)local_8 + -1);
  }
  if ((((char)*local_8 != '\0') && ((char)*local_8 != ':')) && ((char)*local_8 != '\\')) {
    local_8 = (uint *)((int)local_8 + 1);
    *(char *)local_8 = '\\';
  }
  if (param_1 < local_8) {
    *(char *)((int)local_8 + 1) = '\0';
  }
  cVar1 = strcat((char *)param_1,&DAT_00412ff0);
  pbVar2 = FUN_0040d670((byte *)CONCAT31(extraout_var,cVar1));
  if (pbVar2 == (byte *)0x0) {
    FUN_00404167(s_cannot_create_temporary_file_nam_0040f944);
  }
  return param_1;
}


/* ==== FUN_00403e56 @ 00403e56 ==== */

void FUN_00403e56(void)

{
  fprintf(PTR_DAT_0040f098,s_Usage___s__command_library__file_0040f968,PTR_s_dsplib_0040f148);
  fprintf(PTR_DAT_0040f098,s_where__command_is_one_of_the_fol_0040f990);
  fprintf(PTR_DAT_0040f098,s__a_add_named_modules_to_library_0040f9bc);
  fprintf(PTR_DAT_0040f098,s__c_create_library_with_named_mod_0040f9ec);
  fprintf(PTR_DAT_0040f098,s__d_delete_named_modules_from_lib_0040fa20);
  fprintf(PTR_DAT_0040f098,s__ea_<errfil>_append_to_error_fil_0040fa54);
  fprintf(PTR_DAT_0040f098,s__ew_<errfil>_write_to_error_file_0040fa7c);
  fprintf(PTR_DAT_0040f098,s__f_<cmdfil>_get_module_names_fro_0040faa4);
  fprintf(PTR_DAT_0040f098,s__l_list_library_module_info_0040fad0);
  fprintf(PTR_DAT_0040f098,s__q_do_not_display_signon_banner_0040fafc);
  fprintf(PTR_DAT_0040f098,s__r_replace_named_modules_in_libr_0040fb2c);
  fprintf(PTR_DAT_0040f098,s__u_update_named_modules_or_add_a_0040fb60);
  fprintf(PTR_DAT_0040f098,s__v_display_librarian_version_0040fb94);
  fprintf(PTR_DAT_0040f098,s__x_extract_named_modules_from_li_0040fbc0);
  exit(1);
  return;
}


/* ==== FUN_00403f7f @ 00403f7f ==== */

void FUN_00403f7f(void)

{
  if (DAT_00413264 == 0) {
    fprintf(PTR_DAT_0040f098,s__s_Version__s__s_0040fbf4,s_DSP_Librarian_0040f150,&DAT_0040f160,
            s__C__Copyright_Motorola__Inc__198_0040f168);
  }
  return;
}


/* ==== FUN_00403faf @ 00403faf ==== */

void FUN_00403faf(void)

{
  fprintf(&DAT_0040fe78,s_Usage__command_library__files____0040fc08);
  fprintf(&DAT_0040fe78,s_where_command_is_one_of_the_foll_0040fc2c);
  fprintf(&DAT_0040fe78,s_add___add_named_modules_to_libra_0040fc58);
  fprintf(&DAT_0040fe78,s_create___create_library_with_nam_0040fc84);
  fprintf(&DAT_0040fe78,s_delete___delete_named_modules_fr_0040fcb8);
  fprintf(&DAT_0040fe78,s_extract___extract_named_modules_f_0040fcec);
  fprintf(&DAT_0040fe78,s_help___display_this_message_0040fd20);
  fprintf(&DAT_0040fe78,s_list___list_library_module_info_0040fd44);
  fprintf(&DAT_0040fe78,s_quit___exit_librarian_0040fd6c);
  fprintf(&DAT_0040fe78,s_replace___replace_named_modules_i_0040fd8c);
  fprintf(&DAT_0040fe78,s_update___update_named_modules_or_0040fdbc);
  fprintf(&DAT_0040fe78,s_version___display_librarian_vers_0040fdf0);
  return;
}


/* ==== FUN_0040408c @ 0040408c ==== */

int __cdecl FUN_0040408c(uint param_1)

{
  int extraout_EAX;
  
  malloc(param_1);
  if (extraout_EAX == 0) {
    FUN_00404167(s_out_of_memory___librarian_aborte_0040fe1c);
  }
  return extraout_EAX;
}


/* ==== FUN_004040b9 @ 004040b9 ==== */

void FUN_004040b9(void)

{
  undefined4 in_stack_00000004;
  
  DAT_0041325c = DAT_0041325c + 1;
  if (DAT_00413698 == 0) {
    fprintf(PTR_DAT_0040f098,&DAT_0040fe40,PTR_s_dsplib_0040f148);
  }
  fprintf(PTR_DAT_0040f098,&DAT_0040fe48,in_stack_00000004);
  return;
}


/* ==== FUN_00404107 @ 00404107 ==== */

void __cdecl FUN_00404107(char *param_1)

{
  undefined4 in_stack_00000008;
  
  DAT_0041325c = DAT_0041325c + 1;
  if (DAT_00413698 == 0) {
    fprintf(PTR_DAT_0040f098,&DAT_0040fe4c,PTR_s_dsplib_0040f148);
  }
  fprintf(PTR_DAT_0040f098,param_1,in_stack_00000008);
  fprintf(PTR_DAT_0040f098,&DAT_0040fe54);
  return;
}


/* ==== FUN_00404167 @ 00404167 ==== */

void FUN_00404167(void)

{
  undefined4 in_stack_00000004;
  
  FUN_004041a8();
  FUN_004040b9(in_stack_00000004);
  if ((DAT_00413698 != 0) && (DAT_0041369c == 0)) {
                    /* WARNING: Subroutine does not return */
    _longjmp((int *)&DAT_00413000,-1);
  }
  exit(1);
  return;
}


/* ==== FUN_004041a8 @ 004041a8 ==== */

void FUN_004041a8(void)

{
  if (DAT_00413670 != (void *)0x0) {
    fclose(DAT_00413670);
  }
  if (DAT_00413674 != (void *)0x0) {
    fclose(DAT_00413674);
  }
  if (DAT_00413678 != (void *)0x0) {
    fclose(DAT_00413678);
  }
  remove(&DAT_00413270);
  return;
}


/* ==== FUN_0040420a @ 0040420a ==== */

void __cdecl FUN_0040420a(char *param_1)

{
  undefined4 in_stack_00000008;
  
  FUN_004041a8();
  FUN_00404107(param_1,in_stack_00000008);
  if ((DAT_00413698 != 0) && (DAT_0041369c == 0)) {
                    /* WARNING: Subroutine does not return */
    _longjmp((int *)&DAT_00413000,-1);
  }
  exit(1);
  return;
}


/* ==== FUN_00404250 @ 00404250 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404250(void)

{
  undefined4 *extraout_EAX;
  int iVar1;
  byte *pbVar2;
  int local_8;
  int local_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_004136a8,0x104);
  _DAT_004137e8 = &DAT_004136a8;
  pbVar2 = _acmdln;
  if (*_acmdln == 0) {
    pbVar2 = &DAT_004136a8;
  }
  FUN_00404310(pbVar2,(undefined4 *)0x0,(byte *)0x0,&local_8,&local_4);
  malloc(local_4 + local_8 * 4);
  if (extraout_EAX == (undefined4 *)0x0) {
    _amsg_exit(8);
  }
  FUN_00404310(pbVar2,extraout_EAX,(byte *)(extraout_EAX + local_8),&local_8,&local_4);
  __argc = local_8 + -1;
  __argv = extraout_EAX;
  iVar1 = FUN_00406080();
  if (iVar1 != 0) {
    _amsg_exit(8);
  }
  return;
}


/* ==== FUN_00404310 @ 00404310 ==== */

void __cdecl FUN_00404310(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  int *piVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  
  piVar5 = param_5;
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (param_3 != (byte *)0x0) {
    *param_3 = *param_1;
    param_3 = param_3 + 1;
  }
  *param_5 = *param_5 + 1;
  if (*param_1 == 0x22) {
    bVar2 = param_1[1];
    while ((pbVar6 = param_1 + 1, bVar2 != 0x22 && (bVar2 != 0))) {
      if (((*(byte *)((int)&DAT_00413848 + bVar2 + 1) & 4) != 0) &&
         (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)) {
        *param_3 = *pbVar6;
        param_3 = param_3 + 1;
        pbVar6 = param_1 + 2;
      }
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *pbVar6;
        param_3 = param_3 + 1;
      }
      param_1 = pbVar6;
      bVar2 = pbVar6[1];
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar6 == 0x22) {
      pbVar6 = param_1 + 2;
    }
  }
  else {
    do {
      *piVar5 = *piVar5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      bVar2 = *param_1;
      pbVar6 = param_1 + 1;
      param_5 = (int *)(uint)bVar2;
      if ((*(byte *)((int)param_5 + 0x413849) & 4) != 0) {
        *piVar5 = *piVar5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar6;
          param_3 = param_3 + 1;
        }
        pbVar6 = param_1 + 2;
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_004043f9;
      param_1 = pbVar6;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_004043f9:
      pbVar6 = pbVar6 + -1;
    }
    else if (param_3 != (byte *)0x0) {
      param_3[-1] = 0;
    }
  }
  bVar4 = false;
  while (*pbVar6 != 0) {
    for (; (*pbVar6 == 0x20 || (*pbVar6 == 9)); pbVar6 = pbVar6 + 1) {
    }
    if (*pbVar6 == 0) break;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = *pbVar6;
      param_3 = param_3 + 1;
    }
    iVar7 = *piVar5 + 1;
    *piVar5 = iVar7;
    while( true ) {
      uVar8 = 0;
      bVar3 = true;
      bVar2 = *pbVar6;
      while (bVar2 == 0x5c) {
        pbVar1 = pbVar6 + 1;
        pbVar6 = pbVar6 + 1;
        uVar8 = uVar8 + 1;
        bVar2 = *pbVar1;
      }
      if (*pbVar6 == 0x22) {
        if ((uVar8 & 1) == 0) {
          if ((bVar4) && (pbVar6[1] == 0x22)) {
            pbVar6 = pbVar6 + 1;
          }
          else {
            bVar3 = false;
          }
          bVar4 = !bVar4;
        }
        uVar8 = uVar8 >> 1;
      }
      for (; uVar8 != 0; uVar8 = uVar8 - 1) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        iVar7 = *piVar5 + 1;
        *piVar5 = iVar7;
      }
      bVar2 = *pbVar6;
      if ((bVar2 == 0) || ((!bVar4 && ((bVar2 == 0x20 || (bVar2 == 9)))))) break;
      if (bVar3) {
        if (param_3 == (byte *)0x0) {
          if ((*(byte *)((int)&DAT_00413848 + bVar2 + 1) & 4) != 0) {
            pbVar6 = pbVar6 + 1;
            *piVar5 = iVar7 + 1;
          }
          iVar7 = *piVar5 + 1;
          *piVar5 = iVar7;
          goto LAB_00404515;
        }
        if ((*(byte *)((int)&DAT_00413848 + bVar2 + 1) & 4) != 0) {
          *param_3 = bVar2;
          param_3 = param_3 + 1;
          pbVar6 = pbVar6 + 1;
          *piVar5 = *piVar5 + 1;
        }
        *param_3 = *pbVar6;
        param_3 = param_3 + 1;
        iVar7 = *piVar5 + 1;
        *piVar5 = iVar7;
        pbVar6 = pbVar6 + 1;
      }
      else {
LAB_00404515:
        pbVar6 = pbVar6 + 1;
      }
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *piVar5 = *piVar5 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}


/* ==== _cinit @ 00404630 ==== */

void _cinit(void)

{
  if (_FPinit != (code *)0x0) {
    (*_FPinit)();
  }
  _initterm(&DAT_0040f008,&DAT_0040f010);
  _initterm(&DAT_0040f000,&DAT_0040f004);
  return;
}


/* ==== exit @ 00404660 ==== */

void __cdecl exit(int status)

{
  doexit(status,0,0);
  return;
}


/* ==== __exit @ 00404680 ==== */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __exit(int _Code)

{
  doexit(_Code,1,0);
  return;
}


/* ==== doexit @ 004046a0 ==== */

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
    _initterm(&DAT_0040f014,&DAT_0040f01c);
  }
  _initterm(&DAT_0040f020,&DAT_0040f024);
  if (retcaller == 0) {
    _C_Exit_Done = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(code);
  }
  return;
}


/* ==== _initterm @ 00404750 ==== */

void __cdecl _initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != (code *)0x0) {
      (**(code **)begin)();
    }
  }
  return;
}


/* ==== strcpy @ 00404770 ==== */

char __cdecl strcpy(char *dst,char *src)

{
  byte bVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  
  cVar3 = (char)dst;
  while (((uint)src & 3) != 0) {
    bVar1 = (byte)*(uint *)src;
    uVar4 = (uint)bVar1;
    src = (char *)((int)src + 1);
    if (bVar1 == 0) goto LAB_00404858;
    *dst = bVar1;
    dst = (char *)((int)dst + 1);
  }
  do {
    uVar2 = *(uint *)src;
    uVar4 = *(uint *)src;
    src = (char *)((int)src + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar4 == '\0') {
LAB_00404858:
        *dst = (byte)uVar4;
        return cVar3;
      }
      if ((char)(uVar4 >> 8) == '\0') {
        *(short *)dst = (short)uVar4;
        return cVar3;
      }
      if ((uVar4 & 0xff0000) == 0) {
        *(short *)dst = (short)uVar4;
        *(byte *)((int)dst + 2) = 0;
        return cVar3;
      }
      if ((uVar4 & 0xff000000) == 0) {
        *(uint *)dst = uVar4;
        return cVar3;
      }
    }
    *(uint *)dst = uVar4;
    dst = (char *)((int)dst + 4);
  } while( true );
}


/* ==== strcat @ 00404780 ==== */

char __cdecl strcat(char *dst,char *src)

{
  byte bVar1;
  uint uVar2;
  char cVar3;
  uint *puVar4;
  uint uVar5;
  uint *puVar6;
  
  puVar4 = (uint *)dst;
  do {
    if (((uint)puVar4 & 3) == 0) goto LAB_0040479c;
    uVar5 = *puVar4;
    puVar4 = (uint *)((int)puVar4 + 1);
  } while ((byte)uVar5 != 0);
  goto LAB_004047cf;
  while( true ) {
    if ((uVar5 & 0xff0000) == 0) {
      puVar6 = (uint *)((int)puVar6 + 2);
      goto LAB_004047e1;
    }
    if ((uVar5 & 0xff000000) == 0) break;
LAB_0040479c:
    do {
      puVar6 = puVar4;
      puVar4 = puVar6 + 1;
    } while (((*puVar6 ^ 0xffffffff ^ *puVar6 + 0x7efefeff) & 0x81010100) == 0);
    uVar5 = *puVar6;
    if ((char)uVar5 == '\0') goto LAB_004047e1;
    if ((char)(uVar5 >> 8) == '\0') {
      puVar6 = (uint *)((int)puVar6 + 1);
      goto LAB_004047e1;
    }
  }
LAB_004047cf:
  puVar6 = (uint *)((int)puVar4 + -1);
LAB_004047e1:
  cVar3 = (char)dst;
  while (((uint)src & 3) != 0) {
    bVar1 = (byte)*(uint *)src;
    uVar5 = (uint)bVar1;
    src = (char *)((int)src + 1);
    if (bVar1 == 0) goto LAB_00404858;
    *(byte *)puVar6 = bVar1;
    puVar6 = (uint *)((int)puVar6 + 1);
  }
  do {
    uVar2 = *(uint *)src;
    uVar5 = *(uint *)src;
    src = (char *)((int)src + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar5 == '\0') {
LAB_00404858:
        *(byte *)puVar6 = (byte)uVar5;
        return cVar3;
      }
      if ((char)(uVar5 >> 8) == '\0') {
        *(short *)puVar6 = (short)uVar5;
        return cVar3;
      }
      if ((uVar5 & 0xff0000) == 0) {
        *(short *)puVar6 = (short)uVar5;
        *(byte *)((int)puVar6 + 2) = 0;
        return cVar3;
      }
      if ((uVar5 & 0xff000000) == 0) {
        *puVar6 = uVar5;
        return cVar3;
      }
    }
    *puVar6 = uVar5;
    puVar6 = puVar6 + 1;
  } while( true );
}


/* ==== tolower @ 00404860 ==== */

int __cdecl tolower(int c)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint local_8 [2];
  
  iVar1 = c;
  if (DAT_00413a78 == 0) {
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
    iVar3 = c;
    if ((_pctype[(iVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      c._0_2_ = (ushort)(byte)iVar1;
      iVar3 = 1;
    }
    else {
      c._0_2_ = CONCAT11((byte)iVar1,(char)((uint)iVar1 >> 8));
      c._3_1_ = SUB41(iVar3,3);
      c._0_3_ = (uint3)(ushort)c;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_00413a78,0x100,(char *)&c,iVar3,(char *)local_8,3,0,1);
    if (iVar3 == 0) {
      return iVar1;
    }
    if (iVar3 == 1) {
      return local_8[0] & 0xff;
    }
    c = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return c;
}


/* ==== _isctype @ 00404960 ==== */

int __cdecl _isctype(int c,int mask)

{
  int iVar1;
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
  iVar1 = __crtGetStringTypeA(1,(char *)&c,iVar1,(ushort *)&local_4,0,0,1);
  if (iVar1 == 0) {
    return 0;
  }
  return local_4 & 0xffff & mask;
}


/* ==== _strrchr @ 00404a00 ==== */

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


/* ==== signal @ 00404a30 ==== */

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
    if ((sig != 2) && (sig != 0x15)) goto LAB_00404ae4;
  }
  if (DAT_0041380c == 0) {
    BVar3 = SetConsoleCtrlHandler((PHANDLER_ROUTINE)&LAB_00404ba0,1);
    if (BVar3 != 1) {
      _doserrno = GetLastError();
      errno = 0x16;
      return;
    }
    DAT_0041380c = 1;
  }
LAB_00404ae4:
  switch(sig) {
  case 2:
    DAT_004137fc = func;
    return;
  default:
    return;
  case 0xf:
    DAT_00413808 = func;
    return;
  case 0x15:
    DAT_00413800 = func;
    return;
  case 0x16:
    DAT_00413804 = func;
    return;
  }
}


/* ==== siglookup @ 00404bf0 ==== */

void __cdecl siglookup(int sig)

{
  int *piVar1;
  undefined4 *puVar2;
  
  if (DAT_0041040c != sig) {
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


/* ==== FUN_00404c40 @ 00404c40 ==== */

undefined1 * __cdecl FUN_00404c40(undefined1 *param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  
  puVar2 = param_1;
  while( true ) {
    DAT_0040fe5c = DAT_0040fe5c + -1;
    if (DAT_0040fe5c < 0) {
      uVar1 = _filbuf(&PTR_DAT_0040fe58);
    }
    else {
      uVar1 = (uint)(byte)*PTR_DAT_0040fe58;
      PTR_DAT_0040fe58 = PTR_DAT_0040fe58 + 1;
    }
    if (uVar1 == 10) goto LAB_00404c8f;
    if (uVar1 == 0xffffffff) break;
    *puVar2 = (char)uVar1;
    puVar2 = puVar2 + 1;
  }
  if (puVar2 == param_1) {
    return (undefined1 *)0x0;
  }
LAB_00404c8f:
  *puVar2 = 0;
  return param_1;
}


/* ==== fprintf @ 00404ca0 ==== */

int __cdecl fprintf(void *stream,char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(stream);
  iVar1 = _output(stream,fmt,&stack0x0000000c);
  _ftbuf(flag,stream);
  return iVar1;
}


/* ==== _strlen @ 00404ce0 ==== */

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
    if (((uint)puVar2 & 3) == 0) goto LAB_00404d00;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00404d33:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_00404d00:
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
  goto LAB_00404d33;
}


/* ==== __setjmp3 @ 00404d5c ==== */

/* Library Function - Single Match
    __setjmp3
   
   Library: Visual Studio */

undefined4 __cdecl __setjmp3(undefined4 *param_1,int param_2,void *param_3,undefined4 param_4)

{
  void *pvVar1;
  uint uVar2;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 *puVar3;
  undefined4 unaff_EDI;
  undefined4 *puVar4;
  undefined4 unaff_retaddr;
  
  *param_1 = unaff_EBP;
  param_1[1] = unaff_EBX;
  param_1[2] = unaff_EDI;
  param_1[3] = unaff_ESI;
  param_1[4] = register0x00000010;
  param_1[5] = unaff_retaddr;
  param_1[8] = 0x56433230;
  param_1[9] = 0;
  pvVar1 = ExceptionList;
  param_1[6] = ExceptionList;
  if (pvVar1 == (void *)0xffffffff) {
    param_1[7] = 0xffffffff;
  }
  else if ((param_2 == 0) || (param_1[9] = param_3, pvVar1 = param_3, param_2 == 1)) {
    param_1[7] = *(undefined4 *)((int)pvVar1 + 0xc);
  }
  else {
    param_1[7] = param_4;
    uVar2 = param_2 - 2;
    if (uVar2 != 0) {
      puVar3 = (undefined4 *)&stack0x00000014;
      puVar4 = param_1 + 10;
      if (6 < uVar2) {
        uVar2 = 6;
      }
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
    }
  }
  return 0;
}


/* ==== fclose @ 00404de0 ==== */

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


/* ==== _filbuf @ 00404e60 ==== */

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


/* ==== fseek @ 00404f50 ==== */

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


/* ==== sscanf @ 00404ff0 ==== */

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


/* ==== sprintf @ 00405040 ==== */

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


/* ==== remove @ 004050b0 ==== */

int __cdecl remove(char *path)

{
  BOOL BVar1;
  ulong oserrno;
  
  BVar1 = DeleteFileA(path);
  if (BVar1 == 0) {
    oserrno = GetLastError();
  }
  else {
    oserrno = 0;
  }
  if (oserrno != 0) {
    _dosmaperr(oserrno);
    return -1;
  }
  return 0;
}


/* ==== FUN_004050e0 @ 004050e0 ==== */

undefined4 __cdecl FUN_004050e0(LPCSTR param_1,LPCSTR param_2)

{
  BOOL BVar1;
  ulong oserrno;
  
  BVar1 = MoveFileA(param_1,param_2);
  if (BVar1 == 0) {
    oserrno = GetLastError();
  }
  else {
    oserrno = 0;
  }
  if (oserrno != 0) {
    _dosmaperr(oserrno);
    return 0xffffffff;
  }
  return 0;
}


/* ==== fwrite @ 00405120 ==== */

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
        if (iVar2 == -1) goto LAB_00405254;
        stream = *(void **)((int)stream_00 + 0x18);
        buf = (void *)((int)buf + 1);
        pvVar6 = (void *)((int)pvVar6 - 1);
        if ((int)stream < 1) {
          stream = (void *)0x1;
        }
      }
      else {
        if ((uVar4 != 0) && (iVar2 = _flush(stream_00), iVar2 != 0)) {
LAB_00405254:
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        pvVar1 = pvVar6;
        if (stream != (void *)0x0) {
          pvVar1 = (void *)((int)pvVar6 - (uint)pvVar6 % (uint)stream);
        }
        pvVar3 = (void *)_write(*(int *)((int)stream_00 + 0x10),buf,(uint)pvVar1);
        if (pvVar3 == (void *)0xffffffff) {
LAB_00405239:
          *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x20;
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        pvVar6 = (void *)((int)pvVar6 - (int)pvVar3);
        buf = (void *)((int)buf + (int)pvVar3);
        if (pvVar3 < pvVar1) goto LAB_00405239;
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


/* ==== FUN_00405270 @ 00405270 ==== */

uint __cdecl FUN_00405270(char *param_1,uint param_2,uint param_3,int *param_4)

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


/* ==== FUN_004053b0 @ 004053b0 ==== */

void __cdecl FUN_004053b0(int param_1)

{
  uint uVar1;
  
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffcf;
  uVar1 = *(uint *)(param_1 + 0x10);
  if (uVar1 != 0xffffffff) {
    *(byte *)((&__pioinfo)[(int)uVar1 >> 5] + (uVar1 & 0x1f) * 8 + 4) =
         *(byte *)((&__pioinfo)[(int)uVar1 >> 5] + 4 + (uVar1 & 0x1f) * 8) & 0xfd;
    return;
  }
  DAT_00410404 = DAT_00410404 & 0xfd;
  return;
}


/* ==== _strcmp @ 004053f0 ==== */

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
      if (bVar4 != *_Str2) goto LAB_00405434;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_00405400;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_00405434;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_00405434;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_00405400:
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
LAB_00405434:
  return (uint)bVar5 * -2 + 1;
}


/* ==== setvbuf @ 00405480 ==== */

int __cdecl setvbuf(void *stream,char *buf,int mode,uint size)

{
  char *extraout_EAX;
  uint uVar1;
  uint size_00;
  
  if ((mode != 4) && (((size < 2 || (0x7fffffff < size)) || ((mode != 0 && (mode != 0x40)))))) {
    return -1;
  }
  size_00 = size & 0xfffffffe;
  _flush(stream);
  _freebuf(stream);
  uVar1 = *(uint *)((int)stream + 0xc) & 0xffffc2f3;
  *(uint *)((int)stream + 0xc) = uVar1;
  if ((mode & 4U) == 0) {
    if (buf == (char *)0x0) {
      malloc(size_00);
      if (extraout_EAX == (char *)0x0) {
        _cflush = _cflush + 1;
        return -1;
      }
      uVar1 = *(uint *)((int)stream + 0xc) | 0x408;
      buf = extraout_EAX;
    }
    else {
      uVar1 = uVar1 | 0x500;
    }
    *(uint *)((int)stream + 0xc) = uVar1;
  }
  else {
    buf = (char *)((int)stream + 0x14);
    *(uint *)((int)stream + 0xc) = uVar1 | 4;
    size_00 = 2;
  }
  *(uint *)((int)stream + 0x18) = size_00;
  *(char **)((int)stream + 8) = buf;
  *(char **)stream = buf;
  *(undefined4 *)((int)stream + 4) = 0;
  return 0;
}


/* ==== _fsopen @ 00405540 ==== */

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


/* ==== fopen @ 00405570 ==== */

void __cdecl fopen(char *name,char *mode)

{
  _fsopen(name,mode,0x40);
  return;
}


/* ==== time @ 00405590 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long __cdecl time(long *timer)

{
  DWORD DVar1;
  long lVar2;
  _SYSTEMTIME local_cc;
  _SYSTEMTIME local_bc;
  _TIME_ZONE_INFORMATION local_ac;
  
  GetLocalTime(&local_bc);
  GetSystemTime(&local_cc);
  if (local_cc.wMinute == DAT_00413822) {
    if (local_cc.wHour == DAT_00413820) {
      if (local_cc.wDay == DAT_0041381e) {
        if (local_cc.wMonth == DAT_0041381a) {
          if (local_cc.wYear == DAT_00413818) goto LAB_0040565f;
        }
      }
    }
  }
  DVar1 = GetTimeZoneInformation(&local_ac);
  if (DVar1 == 0xffffffff) {
    DAT_00413810 = -1;
  }
  else if (((DVar1 == 2) && (local_ac.DaylightDate.wMonth != 0)) && (local_ac.DaylightBias != 0)) {
    DAT_00413810 = 1;
  }
  else {
    DAT_00413810 = 0;
  }
  DAT_00413818 = local_cc.wYear;
  DAT_0041381a = local_cc.wMonth;
  _DAT_0041381c = local_cc.wDayOfWeek;
  DAT_0041381e = local_cc.wDay;
  DAT_00413820 = local_cc.wHour;
  DAT_00413822 = local_cc.wMinute;
  _DAT_00413824 = local_cc.wSecond;
  DAT_00413824_2 = local_cc.wMilliseconds;
LAB_0040565f:
  lVar2 = __loctotime_t((uint)local_bc.wYear,(uint)local_bc.wMonth,(uint)local_bc.wDay,
                        (uint)local_bc.wHour,(uint)local_bc.wMinute,(uint)local_bc.wSecond,
                        DAT_00413810);
  if (timer != (long *)0x0) {
    *timer = lVar2;
  }
  return lVar2;
}


/* ==== ungetc @ 004056c0 ==== */

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


/* ==== _strncmp @ 00405750 ==== */

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


/* ==== _flsbuf @ 00405790 ==== */

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
LAB_004058b0:
    *(uint *)((int)stream + 0xc) = uVar4 | 0x20;
    return -1;
  }
  uVar3 = 0;
  if ((uVar4 & 1) != 0) {
    *(undefined4 *)((int)stream + 4) = 0;
    if ((uVar4 & 0x10) == 0) goto LAB_004058b0;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(uint *)((int)stream + 0xc) = uVar4 & 0xfffffffe;
  }
  uVar4 = *(uint *)((int)stream + 0xc);
  *(undefined4 *)((int)stream + 4) = 0;
  *(uint *)((int)stream + 0xc) = uVar4 & 0xffffffef | 2;
  if ((uVar4 & 0x10c) == 0) {
    if ((stream == &DAT_0040fe78) || (stream == &DAT_0040fe98)) {
      iVar1 = _isatty(fh);
      if (iVar1 != 0) goto LAB_00405803;
    }
    _getbuf(stream_00);
  }
LAB_00405803:
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


/* ==== localtime @ 004058c0 ==== */

void __cdecl localtime(long *timer)

{
  long *timer_00;
  void *tb;
  int iVar1;
  int extraout_EAX;
  int *tb_00;
  int iVar2;
  
  timer_00 = timer;
  if (*timer < 0) {
    return;
  }
  __tzset();
  iVar1 = *timer_00;
  if ((iVar1 < 0x3f481) || (0x7ffc0b7e < iVar1)) {
    gmtime(timer_00);
    iVar2 = _isindst(tb_00);
    iVar1 = *tb_00;
    if (iVar2 != 0) {
      iVar1 = iVar1 - _dstbias;
    }
    timer = (long *)(iVar1 - _timezone);
    iVar1 = (int)timer % 0x3c;
    *tb_00 = iVar1;
    if (iVar1 < 0) {
      *tb_00 = iVar1 + 0x3c;
      timer = timer + -0xf;
    }
    timer = (long *)((int)timer / 0x3c + tb_00[1]);
    iVar1 = (int)timer % 0x3c;
    tb_00[1] = iVar1;
    if (iVar1 < 0) {
      tb_00[1] = iVar1 + 0x3c;
      timer = timer + -0xf;
    }
    timer = (long *)((int)timer / 0x3c + tb_00[2]);
    iVar1 = (int)timer % 0x18;
    tb_00[2] = iVar1;
    if (iVar1 < 0) {
      tb_00[2] = iVar1 + 0x18;
      timer = timer + -6;
    }
    iVar1 = (int)timer / 0x18;
    if (0 < iVar1) {
      tb_00[6] = (iVar1 + tb_00[6]) % 7;
      tb_00[3] = tb_00[3] + iVar1;
      tb_00[7] = tb_00[7] + iVar1;
      return;
    }
    if (iVar1 < 0) {
      tb_00[6] = (iVar1 + 7 + tb_00[6]) % 7;
      iVar2 = tb_00[3] + iVar1;
      tb_00[3] = iVar2;
      if (iVar2 < 1) {
        tb_00[7] = 0x16c;
        tb_00[3] = iVar2 + 0x1f;
        tb_00[4] = 0xb;
        tb_00[5] = tb_00[5] + -1;
        return;
      }
      tb_00[7] = tb_00[7] + iVar1;
    }
  }
  else {
    timer = (long *)(iVar1 - _timezone);
    gmtime((long *)&timer);
    if (_daylight != 0) {
      iVar1 = _isindst(tb);
      if (iVar1 != 0) {
        timer = (long *)((int)timer - _dstbias);
        gmtime((long *)&timer);
        *(undefined4 *)(extraout_EAX + 0x20) = 1;
        return;
      }
    }
  }
  return;
}


/* ==== toupper @ 00405ab0 ==== */

int __cdecl toupper(int c)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint local_8 [2];
  
  iVar1 = c;
  if (DAT_00413a78 == 0) {
    if ((0x60 < c) && (c < 0x7b)) {
      return c + -0x20;
    }
  }
  else {
    if (c < 0x100) {
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[c * 2] & 2;
      }
      else {
        uVar2 = _isctype(c,2);
      }
      if (uVar2 == 0) {
        return iVar1;
      }
    }
    iVar3 = c;
    if ((_pctype[(iVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      c._0_2_ = (ushort)(byte)iVar1;
      iVar3 = 1;
    }
    else {
      c._0_2_ = CONCAT11((byte)iVar1,(char)((uint)iVar1 >> 8));
      c._3_1_ = SUB41(iVar3,3);
      c._0_3_ = (uint3)(ushort)c;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_00413a78,0x200,(char *)&c,iVar3,(char *)local_8,3,0,1);
    if (iVar3 == 0) {
      return iVar1;
    }
    if (iVar3 == 1) {
      return local_8[0] & 0xff;
    }
    c = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return c;
}


/* ==== strncpy @ 00405bb0 ==== */

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
        goto joined_r0x00405bee;
      }
    }
    do {
      if (((uint)dst & 3) == 0) {
        uVar5 = n >> 2;
        cVar4 = '\0';
        if (uVar5 == 0) goto LAB_00405c2b;
        goto LAB_00405c99;
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
joined_r0x00405c95:
          while( true ) {
            uVar5 = uVar5 - 1;
            dst = (char *)((int)dst + 4);
            if (uVar5 == 0) break;
LAB_00405c99:
            *(uint *)dst = 0;
          }
          cVar4 = '\0';
          n = n & 3;
          if (n != 0) goto LAB_00405c2b;
          return cVar3;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *(uint *)dst = uVar2 & 0xff;
          goto joined_r0x00405c95;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *(uint *)dst = uVar2 & 0xffff;
          goto joined_r0x00405c95;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *(uint *)dst = uVar2;
          goto joined_r0x00405c95;
        }
      }
      *(uint *)dst = uVar2;
      dst = (char *)((int)dst + 4);
      uVar5 = uVar5 - 1;
joined_r0x00405bee:
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
LAB_00405c2b:
        *dst = cVar4;
        dst = (char *)((int)dst + 1);
      }
      return cVar3;
    }
    n = n - 1;
  } while (n != 0);
  return cVar3;
}


/* ==== free @ 00405cb0 ==== */

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


/* ==== strchr @ 00405d10 ==== */

/* Library Function - Single Match
    _strchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strchr(char *s,int c)

{
  char cVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  while (((uint)s & 3) != 0) {
    uVar2 = *(uint *)s;
    if ((char)uVar2 == (char)c) {
      return (char)s;
    }
    s = (char *)((int)s + 1);
    if ((char)uVar2 == '\0') {
      return '\0';
    }
  }
  while( true ) {
    while( true ) {
      uVar2 = *(uint *)s;
      uVar5 = uVar2 ^ CONCAT22(CONCAT11((char)c,(char)c),CONCAT11((char)c,(char)c));
      uVar4 = uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff;
      puVar6 = (uint *)((int)s + 4);
      if (((uVar5 ^ 0xffffffff ^ uVar5 + 0x7efefeff) & 0x81010100) != 0) break;
      s = (char *)puVar6;
      if ((uVar4 & 0x81010100) != 0) {
        if ((uVar4 & 0x1010100) != 0) {
          return '\0';
        }
        if ((uVar2 + 0x7efefeff & 0x80000000) == 0) {
          return '\0';
        }
      }
    }
    uVar2 = *(uint *)s;
    cVar1 = (char)s;
    if ((char)uVar2 == (char)c) {
      return cVar1;
    }
    if ((char)uVar2 == '\0') {
      return '\0';
    }
    cVar3 = (char)(uVar2 >> 8);
    if (cVar3 == (char)c) {
      return cVar1 + '\x01';
    }
    if (cVar3 == '\0') {
      return '\0';
    }
    cVar3 = (char)(uVar2 >> 0x10);
    if (cVar3 == (char)c) {
      return cVar1 + '\x02';
    }
    if (cVar3 == '\0') break;
    cVar3 = (char)(uVar2 >> 0x18);
    if (cVar3 == (char)c) {
      return cVar1 + '\x03';
    }
    s = (char *)puVar6;
    if (cVar3 == '\0') {
      return '\0';
    }
  }
  return '\0';
}


/* ==== malloc @ 00405dd0 ==== */

void __cdecl malloc(uint size)

{
  _nh_malloc(size,_newmode);
  return;
}


/* ==== _nh_malloc @ 00405df0 ==== */

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


/* ==== _heap_alloc @ 00405e40 ==== */

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


/* ==== _longjmp @ 00405e80 ==== */

/* WARNING: Unable to track spacebase fully for stack */
/* Library Function - Single Match
    _longjmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl _longjmp(int *_Buf,int _Value)

{
  PVOID pvVar1;
  int iVar2;
  
  pvVar1 = (PVOID)_Buf[6];
  if (pvVar1 != ExceptionList) {
    __global_unwind2(pvVar1);
  }
  if (pvVar1 != (PVOID)0x0) {
    iVar2 = FUN_0040aac0();
    if ((iVar2 == 0) || (_Buf[8] != 0x56433230)) {
      __local_unwind2((int)pvVar1,_Buf[7]);
    }
    else if ((code *)_Buf[9] != (code *)0x0) {
      (*(code *)_Buf[9])(_Buf);
    }
  }
  FUN_00407f96();
                    /* WARNING: Could not recover jumptable at 0x00405ef5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)_Buf[5])();
  return;
}


/* ==== entry @ 00405f00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  int extraout_EAX;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0040e100;
  puStack_10 = &LAB_0040ad88;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  DVar1 = GetVersion();
  _DAT_004137c8 = DVar1 >> 8 & 0xff;
  _DAT_004137c4 = DVar1 & 0xff;
  _DAT_004137c0 = _DAT_004137c4 * 0x100 + _DAT_004137c8;
  _DAT_004137bc = DVar1 >> 0x10;
  iVar2 = _heap_init();
  if (iVar2 == 0) {
    fast_error_exit(0x1c);
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
  __initenv = _environ;
  iVar2 = main(__argc,__argv,_environ);
  exit(iVar2);
  ExceptionList = local_14;
  return;
}


/* ==== _amsg_exit @ 00406020 ==== */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _amsg_exit(int rterrnum)

{
  if (DAT_00413830 != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
  (*(code *)PTR___exit_00410300)(0xff);
  return;
}


/* ==== fast_error_exit @ 00406050 ==== */

void __cdecl fast_error_exit(int rterrnum)

{
  if (DAT_00413830 != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
                    /* WARNING: Subroutine does not return */
  ExitProcess(0xff);
}


/* ==== FUN_00406080 @ 00406080 ==== */

undefined4 FUN_00406080(void)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  int iVar6;
  undefined4 *extraout_EAX;
  undefined4 *puVar7;
  
  DAT_00413840 = 0;
  DAT_00413834 = (undefined4 *)0x0;
  pcVar2 = (char *)*__argv;
  puVar7 = __argv;
  while( true ) {
    if (pcVar2 == (char *)0x0) {
      iVar6 = 0;
      for (puVar7 = DAT_00413834; puVar7 != (undefined4 *)0x0; puVar7 = (undefined4 *)puVar7[1]) {
        iVar6 = iVar6 + 1;
      }
      malloc(iVar6 * 4 + 4);
      puVar7 = extraout_EAX;
      puVar4 = extraout_EAX;
      puVar3 = DAT_00413834;
      if (extraout_EAX == (undefined4 *)0x0) {
        return 0xffffffff;
      }
      for (; __argc = iVar6, __argv = puVar4, puVar3 != (undefined4 *)0x0;
          puVar3 = (undefined4 *)puVar3[1]) {
        *puVar7 = *puVar3;
        puVar7 = puVar7 + 1;
        puVar4 = __argv;
        iVar6 = __argc;
      }
      *puVar7 = 0;
      puVar7 = DAT_00413834;
      while (puVar7 != (undefined4 *)0x0) {
        DAT_00413834 = (undefined4 *)puVar7[1];
        free(puVar7);
        puVar7 = DAT_00413834;
      }
      DAT_00413834 = puVar7;
      return 0;
    }
    cVar1 = *pcVar2;
    pbVar5 = (byte *)(pcVar2 + 1);
    *puVar7 = pbVar5;
    if (cVar1 == '\"') {
      iVar6 = FUN_00406330(pbVar5);
    }
    else {
      pbVar5 = (byte *)FUN_0040b080(pbVar5,&DAT_0040e10c);
      if (pbVar5 == (byte *)0x0) {
        iVar6 = FUN_00406330(*puVar7);
      }
      else {
        iVar6 = FUN_00406180((byte *)*puVar7,pbVar5);
      }
    }
    if (iVar6 != 0) break;
    pcVar2 = (char *)puVar7[1];
    puVar7 = puVar7 + 1;
  }
  return 0xffffffff;
}


/* ==== FUN_00406180 @ 00406180 ==== */

undefined4 __cdecl FUN_00406180(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  char cVar4;
  byte *pbVar5;
  int iVar6;
  undefined3 extraout_var;
  byte *extraout_EAX;
  byte *pbVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  byte *pbVar12;
  int local_4;
  
  pbVar11 = (byte *)0x0;
  local_4 = 0;
  while ((((pbVar2 = param_2, pbVar2 != param_1 && (bVar1 = *pbVar2, bVar1 != 0x5c)) &&
          (bVar1 != 0x2f)) && (bVar1 != 0x3a))) {
    param_2 = pbVar2 + -1;
    if (param_1 < pbVar2 + -1) {
      param_2 = FUN_0040b2e0(param_1,pbVar2);
    }
  }
  bVar1 = *pbVar2;
  if ((bVar1 != 0x3a) || (pbVar2 == param_1 + 1)) {
    if ((bVar1 == 0x5c) || ((bVar1 == 0x2f || (bVar1 == 0x3a)))) {
      pbVar11 = pbVar2 + (1 - (int)param_1);
    }
    pbVar5 = (byte *)FUN_004063c0((LPCSTR)param_1);
    iVar3 = DAT_00413840;
    if (pbVar5 != (byte *)0x0) {
      do {
        iVar6 = FUN_0040b210(pbVar5,&DAT_0040e114);
        if ((iVar6 != 0) && (iVar6 = FUN_0040b210(pbVar5,&DAT_0040e110), iVar6 != 0)) {
          bVar1 = *pbVar2;
          if ((bVar1 == 0x5c) || ((bVar1 == 0x3a || (bVar1 == 0x2f)))) {
            uVar9 = 0xffffffff;
            pbVar7 = pbVar5;
            do {
              if (uVar9 == 0) break;
              uVar9 = uVar9 - 1;
              bVar1 = *pbVar7;
              pbVar7 = pbVar7 + 1;
            } while (bVar1 != 0);
            malloc((uint)(pbVar11 + ~uVar9));
            if (extraout_EAX == (byte *)0x0) {
              return 0xffffffff;
            }
            pbVar7 = FUN_0040b120(extraout_EAX,param_1,(uint)pbVar11);
            uVar9 = 0xffffffff;
            do {
              pbVar12 = pbVar5;
              if (uVar9 == 0) break;
              uVar9 = uVar9 - 1;
              pbVar12 = pbVar5 + 1;
              bVar1 = *pbVar5;
              pbVar5 = pbVar12;
            } while (bVar1 != 0);
            uVar9 = ~uVar9;
            pbVar5 = pbVar12 + -uVar9;
            pbVar12 = pbVar7 + (int)pbVar11;
            for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *(undefined4 *)pbVar12 = *(undefined4 *)pbVar5;
              pbVar5 = pbVar5 + 4;
              pbVar12 = pbVar12 + 4;
            }
            for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
              *pbVar12 = *pbVar5;
              pbVar5 = pbVar5 + 1;
              pbVar12 = pbVar12 + 1;
            }
            iVar6 = FUN_00406330((int)(pbVar7 + (int)pbVar11) - (int)pbVar11);
          }
          else {
            cVar4 = _strdup((char *)pbVar5);
            param_1 = (byte *)CONCAT31(extraout_var,cVar4);
            if (param_1 == (byte *)0x0) {
              return 0xffffffff;
            }
            iVar6 = FUN_00406330(param_1);
          }
          if (iVar6 != 0) {
            return 0xffffffff;
          }
          local_4 = local_4 + 1;
        }
        pbVar5 = (byte *)FUN_004063c0((LPCSTR)0x0);
      } while (pbVar5 != (byte *)0x0);
      if (local_4 != 0) {
        if (iVar3 != 0) {
          FUN_00406380(*(undefined4 **)(iVar3 + 4));
          return 0;
        }
        FUN_00406380(DAT_00413834);
        return 0;
      }
    }
  }
  uVar8 = FUN_00406330(param_1);
  return uVar8;
}


/* ==== FUN_00406330 @ 00406330 ==== */

undefined4 __cdecl FUN_00406330(undefined4 param_1)

{
  undefined4 *extraout_EAX;
  
  malloc(8);
  if (extraout_EAX == (undefined4 *)0x0) {
    return 0xffffffff;
  }
  extraout_EAX[1] = 0;
  *extraout_EAX = param_1;
  if (DAT_00413834 != (undefined4 *)0x0) {
    *(undefined4 **)((int)DAT_00413840 + 4) = extraout_EAX;
    DAT_00413840 = extraout_EAX;
    return 0;
  }
  DAT_00413834 = extraout_EAX;
  DAT_00413840 = extraout_EAX;
  return 0;
}


/* ==== FUN_00406380 @ 00406380 ==== */

void __cdecl FUN_00406380(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar3 = (undefined4 *)param_1[1];
    while (puVar3 != (undefined4 *)0x0) {
      do {
        iVar2 = FUN_0040b350((byte *)*puVar3,(byte *)*param_1);
        if (iVar2 < 0) {
          uVar1 = *param_1;
          *param_1 = *puVar3;
          *puVar3 = uVar1;
        }
        puVar3 = (undefined4 *)puVar3[1];
      } while (puVar3 != (undefined4 *)0x0);
      param_1 = (undefined4 *)param_1[1];
      puVar3 = (undefined4 *)param_1[1];
    }
  }
  return;
}


/* ==== FUN_004063c0 @ 004063c0 ==== */

CHAR * __cdecl FUN_004063c0(LPCSTR param_1)

{
  LPWIN32_FIND_DATAA extraout_EAX;
  BOOL BVar1;
  
  if (param_1 == (LPCSTR)0x0) {
    BVar1 = FindNextFileA(DAT_0041383c,DAT_00413838);
    if (BVar1 == 0) {
      FindClose(DAT_0041383c);
      DAT_0041383c = (HANDLE)0x0;
      return (CHAR *)0x0;
    }
  }
  else {
    if (DAT_00413838 == (LPWIN32_FIND_DATAA)0x0) {
      malloc(0x244);
      DAT_00413838 = extraout_EAX;
    }
    if (DAT_0041383c != (HANDLE)0x0) {
      FindClose(DAT_0041383c);
      DAT_0041383c = (HANDLE)0x0;
    }
    DAT_0041383c = FindFirstFileA(param_1,DAT_00413838);
    if (DAT_0041383c == (HANDLE)0xffffffff) {
      return (CHAR *)0x0;
    }
  }
  return DAT_00413838->cFileName;
}


/* ==== _setmbcp @ 00406460 ==== */

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
  
  CodePage = FUN_00406670(codepage);
  if (CodePage == DAT_00413a50) {
    return 0;
  }
  if (CodePage == 0) {
    FUN_00406720();
    FUN_00406760();
    return 0;
  }
  iVar10 = 0;
  pUVar5 = &DAT_00410310;
  do {
    if (*pUVar5 == CodePage) {
      puVar14 = &DAT_00413848;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined1 *)puVar14 = 0;
      uVar7 = 0;
      iVar10 = iVar10 * 0x30;
      pbVar12 = (byte *)(iVar10 + 0x410320);
      do {
        bVar3 = *pbVar12;
        for (pbVar13 = pbVar12; (bVar3 != 0 && (bVar3 = pbVar13[1], bVar3 != 0));
            pbVar13 = pbVar13 + 2) {
          uVar8 = (uint)*pbVar13;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_00410308)[uVar7];
            do {
              pbVar2 = (byte *)((int)&DAT_00413848 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          bVar3 = pbVar13[2];
        }
        uVar7 = uVar7 + 1;
        pbVar12 = pbVar12 + 8;
      } while (uVar7 < 4);
      _DAT_00413cc4 = 1;
      DAT_00413a50 = CodePage;
      DAT_00413a54 = FUN_004066c0(CodePage);
      _DAT_00413a58 = *(undefined4 *)(iVar10 + 0x410314);
      _DAT_00413a5c = *(undefined4 *)(iVar10 + 0x410318);
      _DAT_00413a60 = *(undefined4 *)(iVar10 + 0x41031c);
      FUN_00406760();
      return 0;
    }
    pUVar5 = pUVar5 + 0xc;
    iVar10 = iVar10 + 1;
  } while (pUVar5 < &__badioinfo);
  BVar6 = GetCPInfo(CodePage,&local_14);
  if (BVar6 != 1) {
    if (DAT_00413a64 == 0) {
      return -1;
    }
    FUN_00406720();
    FUN_00406760();
    return 0;
  }
  puVar14 = &DAT_00413848;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined1 *)puVar14 = 0;
  DAT_00413a54 = 0;
  if (local_14.MaxCharSize < 2) {
    _DAT_00413cc4 = 0;
    DAT_00413a50 = CodePage;
  }
  else {
    DAT_00413a50 = CodePage;
    if (local_14.LeadByte[0] != '\0') {
      pBVar11 = local_14.LeadByte + 1;
      do {
        bVar3 = *pBVar11;
        if (bVar3 == 0) break;
        for (uVar7 = (uint)pBVar11[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
          *(byte *)((int)&DAT_00413848 + uVar7 + 1) = *(byte *)((int)&DAT_00413848 + uVar7 + 1) | 4;
        }
        pBVar1 = pBVar11 + 1;
        pBVar11 = pBVar11 + 2;
      } while (*pBVar1 != 0);
    }
    uVar7 = 1;
    do {
      *(byte *)((int)&DAT_00413848 + uVar7 + 1) = *(byte *)((int)&DAT_00413848 + uVar7 + 1) | 8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0xff);
    DAT_00413a54 = FUN_004066c0(CodePage);
    _DAT_00413cc4 = 1;
  }
  _DAT_00413a58 = 0;
  _DAT_00413a5c = 0;
  _DAT_00413a60 = 0;
  FUN_00406760();
  return 0;
}


/* ==== FUN_00406670 @ 00406670 ==== */

int __cdecl FUN_00406670(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_00413a64 = 1;
                    /* WARNING: Could not recover jumptable at 0x0040668d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_00413a64 = 1;
                    /* WARNING: Could not recover jumptable at 0x004066a2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_00413a88;
  }
  DAT_00413a64 = (uint)bVar2;
  return param_1;
}


/* ==== FUN_004066c0 @ 004066c0 ==== */

undefined4 __cdecl FUN_004066c0(undefined4 param_1)

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


/* ==== FUN_00406720 @ 00406720 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00406720(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00413848;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_00413a50 = 0;
  _DAT_00413cc4 = 0;
  DAT_00413a54 = 0;
  _DAT_00413a58 = 0;
  _DAT_00413a5c = 0;
  _DAT_00413a60 = 0;
  return;
}


/* ==== FUN_00406760 @ 00406760 ==== */

void FUN_00406760(void)

{
  BOOL BVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  BYTE *pBVar5;
  ushort *puVar6;
  char *pcVar7;
  _cpinfo local_514;
  char local_500 [256];
  char local_400 [256];
  char local_300 [256];
  ushort local_200 [256];
  
  BVar1 = GetCPInfo(DAT_00413a50,&local_514);
  if (BVar1 == 1) {
    uVar2 = 0;
    do {
      local_500[uVar2] = (char)uVar2;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 0x100);
    local_500[0] = ' ';
    if (local_514.LeadByte[0] != 0) {
      pBVar5 = local_514.LeadByte + 1;
      do {
        uVar2 = (uint)local_514.LeadByte[0];
        if (uVar2 <= *pBVar5) {
          uVar3 = (*pBVar5 - uVar2) + 1;
          uVar4 = uVar3 >> 2;
          pcVar7 = local_500 + uVar2;
          while (uVar4 != 0) {
            uVar4 = uVar4 - 1;
            builtin_strncpy(pcVar7,"    ",4);
            pcVar7 = pcVar7 + 4;
          }
          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *pcVar7 = ' ';
            pcVar7 = pcVar7 + 1;
          }
        }
        local_514.LeadByte[0] = pBVar5[1];
        pBVar5 = pBVar5 + 2;
      } while (local_514.LeadByte[0] != 0);
    }
    __crtGetStringTypeA(1,local_500,0x100,local_200,DAT_00413a50,DAT_00413a54,0);
    __crtLCMapStringA(DAT_00413a54,0x100,local_500,0x100,local_400,0x100,DAT_00413a50,0);
    __crtLCMapStringA(DAT_00413a54,0x200,local_500,0x100,local_300,0x100,DAT_00413a50,0);
    uVar2 = 0;
    puVar6 = local_200;
    do {
      if ((*puVar6 & 1) == 0) {
        if ((*puVar6 & 2) == 0) {
          (&DAT_00413950)[uVar2] = 0;
        }
        else {
          *(byte *)((int)&DAT_00413848 + uVar2 + 1) =
               *(byte *)((int)&DAT_00413848 + uVar2 + 1) | 0x20;
          (&DAT_00413950)[uVar2] = local_300[uVar2];
        }
      }
      else {
        *(byte *)((int)&DAT_00413848 + uVar2 + 1) = *(byte *)((int)&DAT_00413848 + uVar2 + 1) | 0x10
        ;
        (&DAT_00413950)[uVar2] = local_400[uVar2];
      }
      uVar2 = uVar2 + 1;
      puVar6 = puVar6 + 1;
    } while (uVar2 < 0x100);
    return;
  }
  uVar2 = 0;
  do {
    if ((uVar2 < 0x41) || (0x5a < uVar2)) {
      if ((uVar2 < 0x61) || (0x7a < uVar2)) {
        (&DAT_00413950)[uVar2] = 0;
      }
      else {
        *(byte *)((int)&DAT_00413848 + uVar2 + 1) = *(byte *)((int)&DAT_00413848 + uVar2 + 1) | 0x20
        ;
        (&DAT_00413950)[uVar2] = (char)uVar2 + -0x20;
      }
    }
    else {
      *(byte *)((int)&DAT_00413848 + uVar2 + 1) = *(byte *)((int)&DAT_00413848 + uVar2 + 1) | 0x10;
      (&DAT_00413950)[uVar2] = (char)uVar2 + ' ';
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x100);
  return;
}


/* ==== __initmbctable @ 00406940 ==== */

int __initmbctable(void)

{
  int iVar1;
  
  iVar1 = _setmbcp(-3);
  return iVar1;
}


/* ==== _ioinit @ 00406950 ==== */

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
      piVar6 = &DAT_00413bc4;
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
        goto LAB_00406b2b;
      }
      *puVar2 = hFile;
      if ((DVar3 & 0xff) == 2) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_00406b2b;
      }
      if ((DVar3 & 0xff) == 3) {
        bVar1 = *(byte *)(puVar2 + 1) | 8;
        goto LAB_00406b2b;
      }
    }
    else {
      bVar1 = *(byte *)(puVar2 + 1) | 0x80;
LAB_00406b2b:
      *(byte *)(puVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(_nhandle);
      return;
    }
  } while( true );
}


/* ==== calloc @ 00406b50 ==== */

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
LAB_00406bb0:
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
          goto LAB_00406bb0;
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


/* ==== _flush @ 00406cb0 ==== */

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


/* ==== __crtLCMapStringA @ 00406db0 ==== */

int __cdecl
__crtLCMapStringA(ulong lcid,ulong flags,char *src,int cchsrc,char *dst,int cchdst,int codepage,
                 int berror)

{
  int iVar1;
  int iVar2;
  LPCWSTR lpWideCharStr;
  LPCWSTR lpDestStr;
  
  if (DAT_00413a6c == 0) {
    iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_00413a6c = 2;
    }
    else {
      DAT_00413a6c = 1;
    }
  }
  iVar1 = cchsrc;
  if (0 < cchsrc) {
    iVar1 = __ansicp((int)src);
  }
  if (DAT_00413a6c == 2) {
    iVar1 = LCMapStringA(lcid,flags,src,iVar1,dst,cchdst);
    return iVar1;
  }
  if (DAT_00413a6c != 1) {
    return DAT_00413a6c;
  }
  cchsrc = 0;
  if (codepage == 0) {
    codepage = DAT_00413a88;
  }
  iVar2 = MultiByteToWideChar(codepage,(-(uint)(berror != 0) & 8) + 1,src,iVar1,(LPWSTR)0x0,0);
  if (iVar2 == 0) {
    return 0;
  }
  malloc(iVar2 * 2);
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return 0;
  }
  iVar1 = MultiByteToWideChar(codepage,1,src,iVar1,lpWideCharStr,iVar2);
  if ((iVar1 != 0) &&
     (iVar1 = LCMapStringW(lcid,flags,lpWideCharStr,iVar2,(LPWSTR)0x0,0), iVar1 != 0)) {
    if ((flags & 0x400) == 0) {
      malloc(iVar1 * 2);
      cchsrc = (int)lpDestStr;
      if ((lpDestStr == (LPCWSTR)0x0) ||
         (iVar2 = LCMapStringW(lcid,flags,lpWideCharStr,iVar2,lpDestStr,iVar1), iVar2 == 0))
      goto LAB_00406fb8;
      if (cchdst == 0) {
        iVar1 = WideCharToMultiByte(codepage,0x220,lpDestStr,iVar1,(LPSTR)0x0,0,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        iVar2 = iVar1;
      }
      else {
        iVar1 = WideCharToMultiByte(codepage,0x220,lpDestStr,iVar1,dst,cchdst,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        iVar2 = iVar1;
      }
    }
    else {
      if (cchdst == 0) goto LAB_00406f1f;
      if (cchdst < iVar1) goto LAB_00406fb8;
      iVar2 = LCMapStringW(lcid,flags,lpWideCharStr,iVar2,(LPWSTR)dst,cchdst);
    }
    if (iVar2 != 0) {
LAB_00406f1f:
      free(lpWideCharStr);
      free((void *)cchsrc);
      return iVar1;
    }
  }
LAB_00406fb8:
  free(lpWideCharStr);
  free((void *)cchsrc);
  return 0;
}


/* ==== __ansicp @ 00406fe0 ==== */

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


/* ==== __crtGetStringTypeA @ 00407010 ==== */

int __cdecl
__crtGetStringTypeA(ulong type,char *src,int cchsrc,ushort *chartype,int codepage,int lcid,
                   int berror)

{
  BOOL BVar1;
  uint size;
  LPCWSTR lpWideCharStr;
  int cchSrc;
  LPCWSTR p;
  WORD local_2;
  
  p = (LPCWSTR)0x0;
  if (DAT_00413a90 == 0) {
    BVar1 = GetStringTypeW(1,L"",1,&local_2);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeA(0,1,"",1,&local_2);
      if (BVar1 == 0) {
        return 0;
      }
      DAT_00413a90 = 2;
    }
    else {
      DAT_00413a90 = 1;
    }
  }
  if (DAT_00413a90 == 2) {
    if (lcid == 0) {
      lcid = DAT_00413a78;
    }
    BVar1 = GetStringTypeA(lcid,type,src,cchsrc,chartype);
    return BVar1;
  }
  lcid = DAT_00413a90;
  if (DAT_00413a90 == 1) {
    lcid = 0;
    if (codepage == 0) {
      codepage = DAT_00413a88;
    }
    size = MultiByteToWideChar(codepage,(-(uint)(berror != 0) & 8) + 1,src,cchsrc,(LPWSTR)0x0,0);
    if (size != 0) {
      calloc(2,size);
      p = lpWideCharStr;
      if (lpWideCharStr != (LPCWSTR)0x0) {
        cchSrc = MultiByteToWideChar(codepage,1,src,cchsrc,lpWideCharStr,size);
        if (cchSrc != 0) {
          BVar1 = GetStringTypeW(type,lpWideCharStr,cchSrc,chartype);
          free(lpWideCharStr);
          return BVar1;
        }
      }
    }
    free(p);
  }
  return lcid;
}


/* ==== _XcptFilter @ 00407150 ==== */

int __cdecl _XcptFilter(ulong xcptnum,void *pxcptptrs)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  undefined4 *puVar6;
  int iVar7;
  
  piVar4 = FUN_00407290(xcptnum);
  uVar3 = DAT_00413a94;
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    LVar5 = UnhandledExceptionFilter(pxcptptrs);
    return LVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 != (code *)0x1) {
    DAT_00413a94 = pxcptptrs;
    if (piVar4[1] == 8) {
      if (DAT_00410480 < DAT_00410484 + DAT_00410480) {
        iVar7 = (DAT_00410484 + DAT_00410480) - DAT_00410480;
        puVar6 = (undefined4 *)(DAT_00410480 * 0xc + 0x410410);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar2 = DAT_0041048c;
      iVar7 = *piVar4;
      if (iVar7 == -0x3fffff72) {
        DAT_0041048c = 0x83;
      }
      else if (iVar7 == -0x3fffff70) {
        DAT_0041048c = 0x81;
      }
      else if (iVar7 == -0x3fffff6f) {
        DAT_0041048c = 0x84;
      }
      else if (iVar7 == -0x3fffff6d) {
        DAT_0041048c = 0x85;
      }
      else if (iVar7 == -0x3fffff73) {
        DAT_0041048c = 0x82;
      }
      else if (iVar7 == -0x3fffff71) {
        DAT_0041048c = 0x86;
      }
      else if (iVar7 == -0x3fffff6e) {
        DAT_0041048c = 0x8a;
      }
      (*pcVar1)(8,DAT_0041048c);
      DAT_0041048c = uVar2;
      DAT_00413a94 = (void *)uVar3;
      return -1;
    }
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    DAT_00413a94 = (void *)uVar3;
    return -1;
  }
  return -1;
}


/* ==== FUN_00407290 @ 00407290 ==== */

int * __cdecl FUN_00407290(int param_1)

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


/* ==== _stbuf @ 004072e0 ==== */

int __cdecl _stbuf(void *stream)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = _isatty(*(int *)((int)stream + 0x10));
  if (iVar2 == 0) {
    return 0;
  }
  if (stream == &DAT_0040fe78) {
    iVar2 = 0;
  }
  else {
    if (stream != &DAT_0040fe98) {
      return 0;
    }
    iVar2 = 1;
  }
  _cflush = _cflush + 1;
  if ((*(uint *)((int)stream + 0xc) & 0x10c) != 0) {
    return 0;
  }
  if ((&_stdbuf)[iVar2] == 0) {
    malloc(0x1000);
    (&_stdbuf)[iVar2] = extraout_EAX;
    if (extraout_EAX == 0) {
      *(int *)((int)stream + 8) = (int)stream + 0x14;
      *(int *)stream = (int)stream + 0x14;
      *(undefined4 *)((int)stream + 0x18) = 2;
      *(undefined4 *)((int)stream + 4) = 2;
      goto LAB_00407380;
    }
  }
  uVar1 = (&_stdbuf)[iVar2];
  *(undefined4 *)((int)stream + 0x18) = 0x1000;
  *(undefined4 *)((int)stream + 8) = uVar1;
  *(undefined4 *)stream = uVar1;
  *(undefined4 *)((int)stream + 4) = 0x1000;
LAB_00407380:
  *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 0x1102;
  return 1;
}


/* ==== _ftbuf @ 004073a0 ==== */

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


/* ==== _output @ 00407400 ==== */

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
      uVar2 = (byte)(&DAT_0040e100)[cVar7] & 0xf;
    }
    local_220 = (int)(char)(&DAT_0040e120)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_0040747d_caseD_0:
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
          goto switchD_0040747d_caseD_0;
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
          (*(code *)PTR__fptrap_0041279c)(&local_204);
        }
        if ((cVar7 == 'g') && ((unaff_EBX & 0x80) == 0)) {
          (*(code *)PTR__fptrap_00412794)(local_200);
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
            puVar5 = (ushort *)PTR_DAT_00410490;
            local_248 = (ushort *)PTR_DAT_00410490;
          }
          for (; (iVar10 != 0 && (iVar10 = iVar10 + -1, (char)*puVar5 != '\0'));
              puVar5 = (ushort *)((int)puVar5 + 1)) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_00410494;
          }
          local_230 = 1;
          for (puVar5 = local_248; (iVar10 != 0 && (iVar10 = iVar10 + -1, *puVar5 != 0));
              puVar5 = puVar5 + 1) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_00407691_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg(&argptr);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_00410490;
          pcVar9 = PTR_DAT_00410490;
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
        goto LAB_004079c7;
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
        goto LAB_004079c7;
      case 'p':
        local_244 = 8;
switchD_00407691_caseD_58:
        local_224 = 7;
LAB_00407982:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_004079c7;
      case 'u':
        local_22c = 10;
LAB_004079c7:
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
        goto LAB_00407982;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_00407b5f;
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
LAB_00407b5f:
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


/* ==== write_char @ 00407d90 ==== */

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


/* ==== write_multi_char @ 00407de0 ==== */

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


/* ==== write_string @ 00407e20 ==== */

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


/* ==== get_int_arg @ 00407e60 ==== */

int __cdecl get_int_arg(void *pargptr)

{
  int *piVar1;
  
  piVar1 = *(int **)pargptr;
  *(int **)pargptr = piVar1 + 1;
  return *piVar1;
}


/* ==== get_int64_arg @ 00407e80 ==== */

longlong __cdecl get_int64_arg(void *pargptr)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)pargptr;
  *(longlong **)pargptr = plVar1 + 1;
  return *plVar1;
}


/* ==== get_short_arg @ 00407ea0 ==== */

short __cdecl get_short_arg(void *pargptr)

{
  short *psVar1;
  
  psVar1 = *(short **)pargptr;
  *(short **)pargptr = psVar1 + 2;
  return *psVar1;
}


/* ==== __global_unwind2 @ 00407ec0 ==== */

/* Library Function - Single Match
    __global_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x407ed8,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


/* ==== __local_unwind2 @ 00407f02 ==== */

/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *pvStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_00407ee0;
  pvStack_1c = ExceptionList;
  ExceptionList = &pvStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_00407f96();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  ExceptionList = pvStack_1c;
  return;
}


/* ==== FUN_00407f96 @ 00407f96 ==== */

void FUN_00407f96(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_004104a0 = *(undefined4 *)(unaff_EBP + 8);
  DAT_0041049c = in_EAX;
  DAT_004104a4 = unaff_EBP;
  return;
}


/* ==== _close @ 00407fb0 ==== */

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
      if (lVar2 == lVar1) goto LAB_00408037;
    }
    hObject = (HANDLE)_get_osfhandle(fh);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      oserrno = GetLastError();
      goto LAB_00408039;
    }
  }
LAB_00408037:
  oserrno = 0;
LAB_00408039:
  _free_osfhnd(fh);
  *(undefined1 *)((&__pioinfo)[fh >> 5] + 4 + iVar4) = 0;
  if (oserrno == 0) {
    return 0;
  }
  _dosmaperr(oserrno);
  return -1;
}


/* ==== _freebuf @ 00408090 ==== */

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


/* ==== _read @ 004080d0 ==== */

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
                  goto LAB_004082b8;
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
                      goto LAB_004082b8;
                    }
                    _lseek(fh,-1,1);
                    if ((char)cnt != '\n') goto LAB_004082b5;
                  }
                  else {
                    if ((char)cnt == '\n') {
                      *pcVar8 = '\n';
                      goto LAB_004082b8;
                    }
                    *pcVar8 = '\r';
                    pcVar8 = pcVar8 + 1;
                    *(char *)(iVar6 + 5 + *local_8) = (char)cnt;
                  }
                }
                else {
LAB_004082b5:
                  *pcVar8 = '\r';
LAB_004082b8:
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


/* ==== _getbuf @ 00408330 ==== */

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


/* ==== _lseek @ 00408390 ==== */

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


/* ==== ftell @ 00408450 ==== */

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
  if ((*(byte *)((int)stream + 0xc) & 1) == 0) goto LAB_004085c5;
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
LAB_004085bc:
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
      if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 4) != 0) goto LAB_004085bc;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_004085c5:
  return local_4 + local_8;
}


/* ==== _input @ 00408600 ==== */

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
LAB_00409256:
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
      if ((undefined4 *)(uint)(byte)*fmt != chr) goto LAB_0040923d;
      pbVar9 = (byte *)(fmt + 1);
      if ((_pctype[((uint)chr & 0xff) * 2 + 1] & 0x80) != 0) {
        local_1cc = local_1cc + 1;
        uVar5 = _inc(stream);
        if ((byte)fmt[1] != uVar5) {
          local_1cc = local_1cc + -1;
          _un_inc(uVar5,stream);
          goto LAB_0040923d;
        }
        local_1cc = local_1cc + -1;
        pbVar9 = (byte *)(fmt + 2);
      }
      goto LAB_00409203;
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
switchD_00408780_caseD_2b:
          local_1cd = local_1cd + '\x01';
          break;
        case 0x46:
        case 0x4e:
          break;
        case 0x49:
          if ((fmt[2] != '6') || (fmt[3] != '4')) goto switchD_00408780_caseD_2b;
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
LAB_0040923d:
      local_1cc = local_1cc + -1;
      _un_inc((int)chr,stream);
      goto LAB_00409256;
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
      pcVar11 = &DAT_004104b0;
      goto LAB_004088fe;
    case 100:
    case 0x6f:
    case 0x75:
      goto switchD_00408898_caseD_64;
    case 0x65:
    case 0x66:
    case 0x67:
      pcVar11 = &local_160;
      if (chr == (undefined4 *)0x2d) {
        local_160 = '-';
        pcVar11 = local_15f;
LAB_00408f43:
        local_1c4 = local_1c4 + -1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00408f43;
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
LAB_0040909e:
          iVar6 = local_1c4 + -1;
          if (local_1c4 != 0) goto LAB_004090b3;
        }
        else if (chr == (undefined4 *)0x2b) goto LAB_0040909e;
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
LAB_004090b3:
          local_1c4 = iVar6;
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      local_1cc = local_1cc + -1;
      _un_inc((int)chr,stream);
      if (iVar10 == 0) goto LAB_00409256;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        *pcVar13 = '\0';
        (*(code *)PTR__fptrap_00412798)(local_1c6 + -1,local_1b8,&local_160);
      }
      break;
    default:
      if ((undefined4 *)(uint)(byte)*fmt != chr) goto LAB_0040923d;
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
LAB_00408b52:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar15 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00408b52;
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
      goto LAB_00408c34;
    case 0x6e:
      iVar6 = local_1cc;
      if (local_1c5 != '\0') break;
      goto LAB_00408ef5;
    case 0x70:
      local_1c6 = '\x01';
switchD_00408898_caseD_64:
      if (chr == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_00408c0a:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar15 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00408c0a;
LAB_00408c34:
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
              goto LAB_00408e2a;
            }
LAB_00408e26:
            bVar15 = true;
          }
          else {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 4;
            }
            else {
              uVar7 = _isctype((int)chr,4);
            }
            if (uVar7 == 0) goto LAB_00408e26;
            if (uVar5 == 0x6f) {
              if (0x37 < (int)chr) goto LAB_00408e26;
              iVar6 = iVar6 << 3;
            }
            else {
              iVar6 = iVar6 * 10;
            }
          }
LAB_00408e2a:
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
              goto LAB_00408d01;
            }
LAB_00408cfd:
            bVar15 = true;
          }
          else {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 4;
            }
            else {
              uVar7 = _isctype((int)chr,4);
            }
            if (uVar7 == 0) goto LAB_00408cfd;
            if (local_1bc == 0x6f) {
              if (0x37 < (int)chr) goto LAB_00408cfd;
              lVar16 = __allshl(3,iVar10);
            }
            else {
              lVar16 = __allmul(uVar5,iVar10,10,0);
            }
          }
LAB_00408d01:
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
      if (iVar10 == 0) goto LAB_00409256;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        iVar6 = local_1a4;
        iVar10 = local_188;
LAB_00408ef5:
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
      pcVar11 = s_____004104a8;
LAB_004088fe:
      local_1bd = 0xff;
      pbVar9 = (byte *)fmt;
LAB_00408903:
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
      if (*pcVar11 == 0) goto LAB_00409256;
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
           bVar15)) goto LAB_00408aec;
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
LAB_00408aec:
      local_1b8 = puVar4;
      if (puVar12 == puVar14) goto LAB_00409256;
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
        goto LAB_004088fe;
      }
      goto LAB_00408903;
    }
    local_1bf = local_1bf + '\x01';
    pbVar9 = (byte *)(fmt + 1);
LAB_00409203:
    fmt = (char *)pbVar9;
    if ((chr == (undefined4 *)0xffffffff) && ((*fmt != '%' || (fmt[1] != 'n')))) goto LAB_00409256;
    bVar8 = *fmt;
  } while( true );
}


/* ==== _hextodec @ 00409340 ==== */

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


/* ==== _inc @ 00409380 ==== */

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


/* ==== _un_inc @ 004093b0 ==== */

void __cdecl _un_inc(int chr,void *stream)

{
  if (chr != -1) {
    ungetc(chr,stream);
  }
  return;
}


/* ==== _whiteout @ 004093d0 ==== */

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


/* ==== _dosmaperr @ 00409420 ==== */

void __cdecl _dosmaperr(ulong oserrno)

{
  ulong *puVar1;
  int iVar2;
  
  _doserrno = oserrno;
  iVar2 = 0;
  puVar1 = &DAT_004104b8;
  do {
    if (oserrno == *puVar1) {
      errno = *(undefined4 *)(iVar2 * 8 + 0x4104bc);
      return;
    }
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + 1;
  } while (puVar1 < &_timezone);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    errno = 0xd;
    return;
  }
  if ((oserrno < 0xbc) || (errno = 8, 0xca < oserrno)) {
    errno = 0x16;
  }
  return;
}


/* ==== _write @ 00409490 ==== */

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


/* ==== _openfile @ 004096b0 ==== */

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
      uVar7 = DAT_00413b9c | 1;
      goto LAB_004096ed;
    }
    if (cVar1 != 'w') {
      return;
    }
    oflag = 0x301;
  }
  uVar7 = DAT_00413b9c | 2;
LAB_004096ed:
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
      goto LAB_0040979e;
    case 'D':
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_0040979e;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x10;
        goto LAB_0040979e;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x20;
        goto LAB_0040979e;
      }
      break;
    case 'T':
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_0040979e;
      }
      break;
    case 'b':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x8000;
        goto LAB_0040979e;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_0040979e;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_0040979e;
      }
      break;
    case 't':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x4000;
        goto LAB_0040979e;
      }
    }
    bVar2 = false;
LAB_0040979e:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}


/* ==== _getstream @ 00409880 ==== */

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


/* ==== __loctotime_t @ 00409910 ==== */

long __cdecl __loctotime_t(int yr,int mo,int dy,int hr,int mn,int sc,int dstflag)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_24 [8];
  int local_1c;
  int local_14;
  uint local_10;
  int local_8;
  
  uVar2 = yr - 0x76c;
  if (((int)uVar2 < 0x46) || (0x8a < (int)uVar2)) {
    return -1;
  }
  iVar3 = *(int *)(&DAT_004127e4 + mo * 4) + dy;
  if (((uVar2 & 3) == 0) && (2 < mo)) {
    iVar3 = iVar3 + 1;
  }
  __tzset();
  local_1c = hr;
  local_14 = mo + -1;
  iVar1 = sc + (mn + (hr + ((yr + -0x76d >> 2) + uVar2 * 0x16d + iVar3) * 0x18) * 0x3c) * 0x3c +
          0x7c558180 + _timezone;
  if (dstflag != 1) {
    if (dstflag != -1) {
      return iVar1;
    }
    if (_daylight == 0) {
      return iVar1;
    }
    local_10 = uVar2;
    local_8 = iVar3;
    iVar3 = _isindst(local_24);
    if (iVar3 == 0) {
      return iVar1;
    }
  }
  return iVar1 + _dstbias;
}


/* ==== _isatty @ 00409a00 ==== */

int __cdecl _isatty(int fh)

{
  if (_nhandle <= (uint)fh) {
    return 0;
  }
  return *(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 0x40;
}


/* ==== __tzset @ 00409a30 ==== */

void __tzset(void)

{
  if (DAT_00413b58 == 0) {
    _tzset();
    DAT_00413b58 = DAT_00413b58 + 1;
  }
  return;
}


/* ==== _tzset @ 00409a50 ==== */

void _tzset(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined3 extraout_var;
  DWORD DVar5;
  int iVar6;
  byte *extraout_EAX;
  long lVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  bool bVar12;
  byte *pbVar4;
  
  DAT_00413aa0 = 0;
  DAT_004106c8 = 0xffffffff;
  DAT_004106b8 = 0xffffffff;
  cVar3 = getenv("TZ");
  pbVar4 = (byte *)CONCAT31(extraout_var,cVar3);
  if (pbVar4 == (byte *)0x0) {
    DVar5 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_00413aa8);
    if (DVar5 != 0xffffffff) {
      DAT_00413aa0 = 1;
      _timezone = DAT_00413aa8 * 0x3c;
      if (DAT_00413aee != 0) {
        _timezone = _timezone + DAT_00413afc * 0x3c;
      }
      if ((DAT_00413b42 == 0) || (DAT_00413b50 == 0)) {
        _daylight = 0;
        _dstbias = 0;
      }
      else {
        _daylight = 1;
        _dstbias = (DAT_00413b50 - DAT_00413afc) * 0x3c;
      }
      FUN_0040c230(PTR_DAT_004106b0,(LPCWSTR)&DAT_00413aac,0x40);
      FUN_0040c230(PTR_DAT_004106b4,(LPCWSTR)&DAT_00413b00,0x40);
      PTR_DAT_004106b4[0x3f] = 0;
      PTR_DAT_004106b0[0x3f] = 0;
      return;
    }
  }
  else if (*pbVar4 != 0) {
    pbVar10 = pbVar4;
    pbVar11 = DAT_00413b54;
    if (DAT_00413b54 != (byte *)0x0) {
      do {
        bVar1 = *pbVar10;
        bVar12 = bVar1 < *pbVar11;
        if (bVar1 != *pbVar11) {
LAB_00409b93:
          iVar6 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
          goto LAB_00409b98;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar10[1];
        bVar12 = bVar1 < pbVar11[1];
        if (bVar1 != pbVar11[1]) goto LAB_00409b93;
        pbVar10 = pbVar10 + 2;
        pbVar11 = pbVar11 + 2;
      } while (bVar1 != 0);
      iVar6 = 0;
LAB_00409b98:
      if (iVar6 == 0) {
        return;
      }
    }
    free(DAT_00413b54);
    uVar8 = 0xffffffff;
    pbVar10 = pbVar4;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      bVar1 = *pbVar10;
      pbVar10 = pbVar10 + 1;
    } while (bVar1 != 0);
    malloc(~uVar8);
    DAT_00413b54 = extraout_EAX;
    if (extraout_EAX != (byte *)0x0) {
      uVar8 = 0xffffffff;
      pbVar10 = pbVar4;
      do {
        pbVar11 = pbVar10;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pbVar11 = pbVar10 + 1;
        bVar1 = *pbVar10;
        pbVar10 = pbVar11;
      } while (bVar1 != 0);
      uVar8 = ~uVar8;
      pbVar10 = pbVar11 + -uVar8;
      pbVar11 = extraout_EAX;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pbVar11 = *(undefined4 *)pbVar10;
        pbVar10 = pbVar10 + 4;
        pbVar11 = pbVar11 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pbVar11 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        pbVar11 = pbVar11 + 1;
      }
      strncpy(PTR_DAT_004106b0,(char *)pbVar4,3);
      pbVar10 = pbVar4 + 3;
      PTR_DAT_004106b0[3] = 0;
      bVar1 = *pbVar10;
      if (bVar1 == 0x2d) {
        pbVar10 = pbVar4 + 4;
      }
      lVar7 = atol((char *)pbVar10);
      _timezone = lVar7 * 0xe10;
      for (; (bVar2 = *pbVar10, bVar2 == 0x2b || (('/' < (char)bVar2 && ((char)bVar2 < ':'))));
          pbVar10 = pbVar10 + 1) {
      }
      if (*pbVar10 == 0x3a) {
        pbVar10 = pbVar10 + 1;
        lVar7 = atol((char *)pbVar10);
        _timezone = _timezone + lVar7 * 0x3c;
        bVar2 = *pbVar10;
        while (('/' < (char)bVar2 && ((char)bVar2 < ':'))) {
          pbVar4 = pbVar10 + 1;
          pbVar10 = pbVar10 + 1;
          bVar2 = *pbVar4;
        }
        if (*pbVar10 == 0x3a) {
          pbVar10 = pbVar10 + 1;
          lVar7 = atol((char *)pbVar10);
          _timezone = _timezone + lVar7;
          bVar2 = *pbVar10;
          while (('/' < (char)bVar2 && ((char)bVar2 < ':'))) {
            pbVar4 = pbVar10 + 1;
            pbVar10 = pbVar10 + 1;
            bVar2 = *pbVar4;
          }
        }
      }
      if (bVar1 == 0x2d) {
        _timezone = -_timezone;
      }
      _daylight = (int)(char)*pbVar10;
      if (_daylight != 0) {
        strncpy(PTR_DAT_004106b4,(char *)pbVar10,3);
        PTR_DAT_004106b4[3] = 0;
        return;
      }
      *PTR_DAT_004106b4 = 0;
    }
  }
  return;
}


/* ==== _isindst @ 00409d00 ==== */

int __cdecl _isindst(void *tb)

{
  uint uVar1;
  uint uVar2;
  uint hour;
  uint date;
  int iVar3;
  int iVar4;
  uint month;
  uint week;
  uint uVar5;
  uint msec;
  
  if (_daylight == 0) {
    return 0;
  }
  iVar4 = *(int *)((int)tb + 0x14);
  if ((iVar4 == DAT_004106b8) && (iVar4 == DAT_004106c8)) goto LAB_00409ed4;
  if (DAT_00413aa0 == 0) {
    cvtdate(1,1,iVar4,4,1,0,0,2,0,0,0);
    iVar4 = *(int *)((int)tb + 0x14);
    msec = 0;
    uVar2 = 0;
    uVar5 = 0;
    hour = 2;
    uVar1 = 0;
    week = 5;
    month = 10;
LAB_00409ec8:
    date = 0;
    iVar3 = 1;
  }
  else {
    if (DAT_00413b40 != 0) {
      uVar5 = (uint)DAT_00413b44._2_2_;
      uVar2 = 0;
      uVar1 = 0;
    }
    else {
      uVar2 = DAT_00413b44 & 0xffff;
      uVar5 = 0;
      uVar1 = (uint)DAT_00413b44._2_2_;
    }
    cvtdate(1,(uint)(DAT_00413b40 == 0),iVar4,(uint)DAT_00413b42,uVar1,uVar2,uVar5,
            DAT_00413b48 & 0xffff,DAT_00413b48 >> 0x10,DAT_00413b4c & 0xffff,DAT_00413b4c >> 0x10);
    if (DAT_00413aec == 0) {
      msec = (uint)DAT_00413af8._2_2_;
      uVar2 = DAT_00413af8 & 0xffff;
      uVar5 = (uint)DAT_00413af4._2_2_;
      hour = DAT_00413af4 & 0xffff;
      uVar1 = DAT_00413af0 & 0xffff;
      week = (uint)DAT_00413af0._2_2_;
      month = (uint)DAT_00413aee;
      iVar4 = *(int *)((int)tb + 0x14);
      goto LAB_00409ec8;
    }
    msec = (uint)DAT_00413af8._2_2_;
    uVar2 = DAT_00413af8 & 0xffff;
    uVar5 = (uint)DAT_00413af4._2_2_;
    date = (uint)DAT_00413af0._2_2_;
    hour = DAT_00413af4 & 0xffff;
    iVar4 = *(int *)((int)tb + 0x14);
    month = (uint)DAT_00413aee;
    uVar1 = 0;
    week = 0;
    iVar3 = 0;
  }
  cvtdate(0,iVar3,iVar4,month,week,uVar1,date,hour,uVar5,uVar2,msec);
LAB_00409ed4:
  iVar4 = *(int *)((int)tb + 0x1c);
  if (DAT_004106bc < DAT_004106cc) {
    if ((iVar4 < DAT_004106bc) || (DAT_004106cc < iVar4)) {
      return 0;
    }
    if ((DAT_004106bc < iVar4) && (iVar4 < DAT_004106cc)) {
      return 1;
    }
  }
  else {
    if ((iVar4 < DAT_004106cc) || (DAT_004106bc < iVar4)) {
      return 1;
    }
    if ((DAT_004106cc < iVar4) && (iVar4 < DAT_004106bc)) {
      return 0;
    }
  }
  iVar3 = (*(int *)tb + (*(int *)((int)tb + 4) + *(int *)((int)tb + 8) * 0x3c) * 0x3c) * 1000;
  if (iVar4 != DAT_004106bc) {
    return (uint)(iVar3 < DAT_004106d0);
  }
  return (uint)(DAT_004106c0 <= iVar3);
}


/* ==== cvtdate @ 00409f70 ==== */

void __cdecl
cvtdate(int trantype,int datetype,int year,int month,int week,int dayofweek,int date,int hour,
       int min,int sec,int msec)

{
  int iVar1;
  int iVar2;
  
  if (datetype == 1) {
    if ((year & 3U) == 0) {
      iVar1 = *(int *)(&DAT_004127ac + month * 4);
    }
    else {
      iVar1 = *(int *)(&DAT_004127e4 + month * 4);
    }
    iVar2 = ((year + -1 >> 2) + -0x63db + year * 0x16d + iVar1 + 1) % 7;
    if (iVar2 < dayofweek) {
      iVar1 = iVar1 + -6 + (week * 7 - iVar2) + dayofweek;
    }
    else {
      iVar1 = iVar1 + 1 + (week * 7 - iVar2) + dayofweek;
    }
    if (week == 5) {
      if ((year & 3U) == 0) {
        iVar2 = *(int *)(&DAT_004127b0 + month * 4);
      }
      else {
        iVar2 = (&DAT_004127e8)[month];
      }
      if (iVar2 < iVar1) {
        iVar1 = iVar1 + -7;
      }
    }
  }
  else {
    if ((year & 3U) == 0) {
      iVar1 = *(int *)(&DAT_004127ac + month * 4);
    }
    else {
      iVar1 = *(int *)(&DAT_004127e4 + month * 4);
    }
    iVar1 = iVar1 + date;
  }
  if (trantype == 1) {
    DAT_004106bc = iVar1;
    DAT_004106b8 = year;
    DAT_004106c0 = msec + (sec + (min + hour * 0x3c) * 0x3c) * 1000;
    return;
  }
  DAT_004106cc = iVar1;
  DAT_004106d0 = msec + (sec + (min + hour * 0x3c) * 0x3c + _dstbias) * 1000;
  if (DAT_004106d0 < 0) {
    DAT_004106c8 = year;
    DAT_004106d0 = DAT_004106d0 + 86399999;
    return;
  }
  if (86399999 < DAT_004106d0) {
    DAT_004106d0 = DAT_004106d0 + -86399999;
  }
  DAT_004106c8 = year;
  return;
}


/* ==== gmtime @ 0040a110 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl gmtime(long *timer)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  
  bVar1 = false;
  iVar5 = *timer;
  if (-1 < iVar5) {
    iVar3 = iVar5 % 0x7861f80;
    iVar5 = (iVar5 / 0x7861f80) * 4;
    _DAT_00413b74 = iVar5 + 0x46;
    iVar4 = iVar3;
    if (0x1e1337f < iVar3) {
      iVar4 = iVar3 + -0x1e13380;
      _DAT_00413b74 = iVar5 + 0x47;
      if (0x1e1337f < iVar4) {
        iVar4 = iVar3 + -0x3c26700;
        _DAT_00413b74 = iVar5 + 0x48;
        if (iVar4 < 0x1e28500) {
          bVar1 = true;
        }
        else {
          _DAT_00413b74 = iVar5 + 0x49;
          iVar4 = iVar3 + -0x5a4ec00;
        }
      }
    }
    puVar6 = (undefined4 *)&DAT_004127b0;
    _DAT_00413b7c = iVar4 / 0x15180;
    if (!bVar1) {
      puVar6 = &DAT_004127e8;
    }
    iVar3 = 1;
    iVar5 = puVar6[1];
    puVar2 = puVar6;
    while (iVar5 < _DAT_00413b7c) {
      iVar3 = iVar3 + 1;
      iVar5 = puVar2[2];
      puVar2 = puVar2 + 1;
    }
    _DAT_00413b70 = iVar3 + -1;
    _DAT_00413b6c = _DAT_00413b7c - puVar6[iVar3 + -1];
    _DAT_00413b80 = 0;
    _DAT_00413b78 = (*timer / 0x15180 + 4) % 7;
    _DAT_00413b68 = (iVar4 % 0x15180) / 0xe10;
    iVar5 = (iVar4 % 0x15180) % 0xe10;
    _DAT_00413b64 = iVar5 / 0x3c;
    _DAT_00413b60 = iVar5 % 0x3c;
    return;
  }
  return;
}


/* ==== _heap_init @ 0040a270 ==== */

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


/* ==== __sbh_new_region @ 0040a2b0 ==== */

void __sbh_new_region(void)

{
  bool bVar1;
  undefined4 *lpAddress;
  LPVOID pvVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **lpMem;
  undefined4 *puVar5;
  
  if (DAT_004106e8 == -1) {
    lpMem = &PTR_LOOP_004106d8;
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
      if (lpMem == &PTR_LOOP_004106d8) {
        if (PTR_LOOP_004106d8 == (undefined *)0x0) {
          PTR_LOOP_004106d8 = (undefined *)&PTR_LOOP_004106d8;
        }
        if (PTR_LOOP_004106dc == (undefined *)0x0) {
          PTR_LOOP_004106dc = (undefined *)&PTR_LOOP_004106d8;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_004106d8;
        lpMem[1] = PTR_LOOP_004106dc;
        PTR_LOOP_004106dc = (undefined *)lpMem;
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
  if (lpMem != &PTR_LOOP_004106d8) {
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== __sbh_release_region @ 0040a420 ==== */

void __cdecl __sbh_release_region(void *preg)

{
  VirtualFree(*(LPVOID *)((int)preg + 0x10),0,0x8000);
  if (PTR_LOOP_004126f8 == preg) {
    PTR_LOOP_004126f8 = *(undefined **)((int)preg + 4);
  }
  if (preg != &PTR_LOOP_004106d8) {
    **(undefined4 **)((int)preg + 4) = *(undefined4 *)preg;
    *(undefined4 *)(*(int *)preg + 4) = *(undefined4 *)((int)preg + 4);
    HeapFree(_crtheap,0,preg);
    return;
  }
  DAT_004106e8 = 0xffffffff;
  return;
}


/* ==== __sbh_decommit_pages @ 0040a480 ==== */

void __cdecl __sbh_decommit_pages(int count)

{
  BOOL BVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *preg;
  undefined *puVar5;
  
  preg = PTR_LOOP_004106dc;
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
            DAT_00413b84 = DAT_00413b84 + -1;
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
    if ((puVar5 == PTR_LOOP_004106dc) || (preg = puVar5, count < 1)) {
      return;
    }
  } while( true );
}


/* ==== __sbh_find_block @ 0040a550 ==== */

void __cdecl __sbh_find_block(void *pblock,void *ppreg,void *pppage)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_004106d8;
  while ((pblock <= ppuVar1[4] || (ppuVar1[5] <= pblock))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_004106d8) {
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


/* ==== __sbh_free_block @ 0040a5b0 ==== */

void __cdecl __sbh_free_block(void *preg,void *ppage,void *pmap)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (int)ppage - *(int *)((int)preg + 0x10) >> 0xc;
  piVar1 = (int *)((int)preg + iVar2 * 8 + 0x18);
  *piVar1 = *(int *)((int)preg + iVar2 * 8 + 0x18) + (uint)*(byte *)pmap;
  *(undefined1 *)pmap = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_00413b84 = DAT_00413b84 + 1, DAT_00413b84 == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}


/* ==== __sbh_alloc_block @ 0040a610 ==== */

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
  
  piVar11 = (int *)PTR_LOOP_004126f8;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      pvVar8 = (void *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX != 0) {
            PTR_LOOP_004126f8 = (undefined *)piVar11;
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
            PTR_LOOP_004126f8 = (undefined *)piVar11;
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
  } while (piVar11 != (int *)PTR_LOOP_004126f8);
  ppuVar7 = &PTR_LOOP_004106d8;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_004106d8) {
      __sbh_new_region();
      if (extraout_EAX_01 == (undefined *)0x0) {
        return;
      }
      piVar11 = *(int **)(extraout_EAX_01 + 0x10);
      *(char *)(piVar11 + 2) = (char)para_req;
      PTR_LOOP_004126f8 = extraout_EAX_01;
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
  PTR_LOOP_004126f8 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)para_req;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -para_req;
  piVar11[1] = piVar11[1] - para_req;
  *piVar11 = (int)piVar11 + para_req + 8;
  return;
}


/* ==== __sbh_alloc_block_from_page @ 0040a850 ==== */

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
            goto LAB_0040a99f;
          }
          *(byte **)ppage = pbVar6 + para_req;
          *(uint *)((int)ppage + 4) = uVar5 - para_req;
          goto LAB_0040a9a6;
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
LAB_0040a99f:
            *(undefined4 *)((int)ppage + 4) = 0;
          }
LAB_0040a9a6:
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


/* ==== __sbh_resize_block @ 0040a9d0 ==== */

int __cdecl __sbh_resize_block(void *preg,void *ppage,void *pmap,uint new_para_sz)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  
  iVar5 = 0;
  piVar3 = (int *)((int)preg + ((int)ppage - *(int *)((int)preg + 0x10) >> 0xc) * 8 + 0x18);
  uVar6 = (uint)*(byte *)pmap;
  if (uVar6 <= new_para_sz) {
    if ((uVar6 < new_para_sz) &&
       (pcVar1 = (char *)(new_para_sz + (int)pmap), pcVar1 <= (char *)((int)ppage + 0xf8U))) {
      for (pcVar7 = (char *)(uVar6 + (int)pmap); (pcVar7 < pcVar1 && (*pcVar7 == '\0'));
          pcVar7 = pcVar7 + 1) {
      }
      if (pcVar7 == pcVar1) {
        *(char *)pmap = (char)new_para_sz;
        if ((pmap <= *(char **)ppage) && (*(char **)ppage < pcVar1)) {
          if (pcVar1 < (char *)((int)ppage + 0xf8U)) {
            *(char **)ppage = pcVar1;
            iVar5 = 0;
            cVar4 = *pcVar1;
            while (cVar4 == '\0') {
              iVar2 = iVar5 + 1;
              iVar5 = iVar5 + 1;
              cVar4 = pcVar1[iVar2];
            }
            *(int *)((int)ppage + 4) = iVar5;
          }
          else {
            *(undefined4 *)((int)ppage + 4) = 0;
            *(int *)ppage = (int)ppage + 8;
          }
        }
        *piVar3 = *piVar3 + (uVar6 - new_para_sz);
        iVar5 = 1;
      }
    }
    return iVar5;
  }
  *(char *)pmap = (char)new_para_sz;
  piVar3[1] = 0xf1;
  *piVar3 = *piVar3 + (uVar6 - new_para_sz);
  return 1;
}


/* ==== _callnewh @ 0040aaa0 ==== */

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


/* ==== FUN_0040aac0 @ 0040aac0 ==== */

void FUN_0040aac0(void)

{
  return;
}


/* ==== _setenvp @ 0040ab30 ==== */

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


/* ==== __crtGetEnvironmentStringsA @ 0040ac20 ==== */

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
  if (DAT_00413b94 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr == (LPWCH)0x0) {
      pCVar8 = GetEnvironmentStrings();
      if (pCVar8 == (LPCH)0x0) {
        return;
      }
      DAT_00413b94 = 2;
    }
    else {
      DAT_00413b94 = 1;
    }
  }
  if (DAT_00413b94 == 1) {
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
  else if ((DAT_00413b94 == 2) &&
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


/* ==== FUN_0040ae45 @ 0040ae45 ==== */

void FUN_0040ae45(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* ==== _FF_MSGBANNER @ 0040ae60 ==== */

void _FF_MSGBANNER(void)

{
  if ((DAT_00413830 == 1) || ((DAT_00413830 == 0 && (DAT_00410304 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_00413b98 != (code *)0x0) {
      (*DAT_00413b98)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}


/* ==== _NMSG_WRITE @ 0040aea0 ==== */

void __cdecl _NMSG_WRITE(int rterrnum)

{
  char cVar1;
  undefined **ppuVar2;
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
  
  ppuVar2 = (undefined **)&DAT_00412700;
  iVar8 = 0;
  do {
    if ((undefined *)rterrnum == *ppuVar2) break;
    ppuVar2 = ppuVar2 + 2;
    iVar8 = iVar8 + 1;
  } while (ppuVar2 < &_cfltcvt_tab);
  if (rterrnum == (&DAT_00412700)[iVar8 * 2]) {
    if ((DAT_00413830 == 1) || ((DAT_00413830 == 0 && (DAT_00410304 == 1)))) {
      if ((__pioinfo == 0) || (hFile = *(HANDLE *)(__pioinfo + 0x10), hFile == (HANDLE)0xffffffff))
      {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar7 = *(char **)(iVar8 * 8 + 0x412704);
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
      pcVar7 = *(char **)(iVar8 * 8 + 0x412704);
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


/* ==== FUN_0040b080 @ 0040b080 ==== */

char * __cdecl FUN_0040b080(byte *param_1,byte *param_2)

{
  byte *pbVar1;
  byte bVar2;
  char *pcVar3;
  byte *pbVar4;
  
  if (DAT_00413a50 == 0) {
    pcVar3 = _strpbrk((char *)param_1,(char *)param_2);
    return pcVar3;
  }
  bVar2 = *param_1;
  while (bVar2 != 0) {
    bVar2 = *param_2;
    pbVar4 = param_2;
    while (bVar2 != 0) {
      bVar2 = *pbVar4;
      if ((*(byte *)((int)&DAT_00413848 + bVar2 + 1) & 4) == 0) {
        if (bVar2 == *param_1) break;
      }
      else {
        if (((bVar2 == *param_1) && (pbVar4[1] == param_1[1])) || (pbVar4[1] == 0)) break;
        pbVar4 = pbVar4 + 1;
      }
      pbVar1 = pbVar4 + 1;
      pbVar4 = pbVar4 + 1;
      bVar2 = *pbVar1;
    }
    if ((*pbVar4 != 0) ||
       (((*(byte *)((int)&DAT_00413848 + *param_1 + 1) & 4) != 0 &&
        (pbVar4 = param_1 + 1, param_1 = param_1 + 1, *pbVar4 == 0)))) break;
    pbVar4 = param_1 + 1;
    param_1 = param_1 + 1;
    bVar2 = *pbVar4;
  }
  return (char *)(-(uint)(*param_1 != 0) & (uint)param_1);
}


/* ==== FUN_0040b120 @ 0040b120 ==== */

byte * __cdecl FUN_0040b120(byte *param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined3 extraout_var;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  if (DAT_00413a50 == 0) {
    cVar3 = strncpy((char *)param_1,(char *)param_2,param_3);
    return (byte *)CONCAT31(extraout_var,cVar3);
  }
  uVar5 = 0;
  pbVar7 = param_1;
  pbVar6 = param_1;
  if (param_3 != 0) {
    do {
      bVar1 = *param_2;
      uVar5 = param_3 - 1;
      bVar2 = *(byte *)((int)&DAT_00413848 + bVar1 + 1);
      *pbVar6 = bVar1;
      if ((bVar2 & 4) == 0) {
        pbVar7 = pbVar6 + 1;
        param_2 = param_2 + 1;
        if (bVar1 == 0) goto LAB_0040b193;
      }
      else {
        pbVar7 = pbVar6 + 1;
        if (uVar5 == 0) {
          *pbVar6 = 0;
          goto LAB_0040b193;
        }
        bVar1 = param_2[1];
        uVar5 = param_3 - 2;
        *pbVar7 = bVar1;
        pbVar7 = pbVar6 + 2;
        param_2 = param_2 + 2;
        if (bVar1 == 0) {
          *pbVar6 = 0;
          goto LAB_0040b193;
        }
      }
      param_3 = uVar5;
      pbVar6 = pbVar7;
    } while (uVar5 != 0);
    uVar5 = 0;
  }
LAB_0040b193:
  if (uVar5 != 0) {
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      pbVar7[0] = 0;
      pbVar7[1] = 0;
      pbVar7[2] = 0;
      pbVar7[3] = 0;
      pbVar7 = pbVar7 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pbVar7 = 0;
      pbVar7 = pbVar7 + 1;
    }
  }
  return param_1;
}


/* ==== _strdup @ 0040b1c0 ==== */

char __cdecl _strdup(char *s)

{
  char cVar1;
  char *extraout_EAX;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (s != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar4 = s;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    malloc(~uVar2);
    if (extraout_EAX != (char *)0x0) {
      uVar2 = 0xffffffff;
      do {
        pcVar4 = s;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar4 = s + 1;
        cVar1 = *s;
        s = pcVar4;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      pcVar4 = pcVar4 + -uVar2;
      pcVar5 = extraout_EAX;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      return (char)extraout_EAX;
    }
  }
  return '\0';
}


/* ==== FUN_0040b210 @ 0040b210 ==== */

int __cdecl FUN_0040b210(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  ushort uVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  if (DAT_00413a50 != 0) {
    while( true ) {
      bVar1 = *param_1;
      uVar4 = (ushort)bVar1;
      pbVar6 = param_1 + 1;
      if ((*(byte *)((int)&DAT_00413848 + bVar1 + 1) & 4) != 0) {
        bVar2 = *pbVar6;
        if (bVar2 == 0) {
          uVar4 = 0;
        }
        else {
          pbVar6 = param_1 + 2;
          uVar4 = CONCAT11(bVar1,bVar2);
        }
      }
      uVar3 = (uint)*param_2;
      pbVar5 = param_2 + 1;
      if ((*(byte *)((int)&DAT_00413848 + uVar3 + 1) & 4) != 0) {
        bVar1 = *pbVar5;
        if (bVar1 == 0) {
          uVar3 = 0;
        }
        else {
          pbVar5 = param_2 + 2;
          uVar3 = (uint)CONCAT11(*param_2,bVar1);
        }
      }
      if ((ushort)uVar3 != uVar4) break;
      param_2 = pbVar5;
      param_1 = pbVar6;
      if (uVar4 == 0) {
        return 0;
      }
    }
    return (-(uint)((ushort)uVar3 < uVar4) & 2) - 1;
  }
  while( true ) {
    bVar1 = *param_1;
    bVar7 = bVar1 < *param_2;
    if (bVar1 != *param_2) break;
    if (bVar1 == 0) {
      return 0;
    }
    bVar1 = param_1[1];
    bVar7 = bVar1 < param_2[1];
    if (bVar1 != param_2[1]) break;
    param_1 = param_1 + 2;
    param_2 = param_2 + 2;
    if (bVar1 == 0) {
      return 0;
    }
  }
  return (1 - (uint)bVar7) - (uint)(bVar7 != 0);
}


/* ==== FUN_0040b2e0 @ 0040b2e0 ==== */

byte * __cdecl FUN_0040b2e0(byte *param_1,byte *param_2)

{
  byte *pbVar1;
  
  if (param_2 <= param_1) {
    return (byte *)0x0;
  }
  if (DAT_00413a50 != 0) {
    if ((*(byte *)((int)&DAT_00413848 + param_2[-1] + 1) & 4) == 0) {
      pbVar1 = param_2 + -2;
      while ((param_1 <= pbVar1 && ((*(byte *)((int)&DAT_00413848 + *pbVar1 + 1) & 4) != 0))) {
        pbVar1 = pbVar1 + -1;
      }
      return param_2 + (-1 - ((int)param_2 - (int)pbVar1 & 1U));
    }
    return param_2 + -2;
  }
  return param_2 + -1;
}


/* ==== FUN_0040b350 @ 0040b350 ==== */

int __cdecl FUN_0040b350(byte *param_1,byte *param_2)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  byte *pbVar4;
  byte *src;
  byte *pbVar5;
  
  src = param_2;
  if (DAT_00413a50 == 0) {
    iVar3 = __strcmpi((char *)param_1,(char *)param_2);
    return iVar3;
  }
  while( true ) {
    uVar1 = (ushort)*param_1;
    pbVar4 = param_1 + 1;
    if ((*(byte *)((int)&DAT_00413848 + uVar1 + 1) & 4) == 0) {
      if ((*(byte *)((int)&DAT_00413848 + uVar1 + 1) & 0x10) == 0x10) {
        uVar1 = (ushort)(byte)(&DAT_00413950)[uVar1];
      }
    }
    else if (*pbVar4 == 0) {
      uVar1 = 0;
    }
    else {
      iVar3 = __crtLCMapStringA(DAT_00413a54,0x200,(char *)param_1,2,(char *)&param_2,2,DAT_00413a50
                                ,1);
      if (iVar3 == 1) {
        uVar1 = (ushort)param_2 & 0xff;
        pbVar4 = param_1 + 2;
      }
      else {
        if (iVar3 != 2) {
          return 0x7fffffff;
        }
        uVar1 = (ushort)param_2 * 0x100 + ((ushort)((uint)param_2 >> 8) & 0xff);
        pbVar4 = param_1 + 2;
      }
    }
    uVar2 = (ushort)*src;
    pbVar5 = src + 1;
    if ((*(byte *)((int)&DAT_00413848 + uVar2 + 1) & 4) == 0) {
      if ((*(byte *)((int)&DAT_00413848 + uVar2 + 1) & 0x10) == 0x10) {
        uVar2 = (ushort)(byte)(&DAT_00413950)[uVar2];
      }
    }
    else if (*pbVar5 == 0) {
      uVar2 = 0;
    }
    else {
      iVar3 = __crtLCMapStringA(DAT_00413a54,0x200,(char *)src,2,(char *)&param_2,2,DAT_00413a50,1);
      if (iVar3 == 1) {
        uVar2 = (ushort)param_2 & 0xff;
        pbVar5 = src + 2;
      }
      else {
        if (iVar3 != 2) {
          return 0x7fffffff;
        }
        uVar2 = (ushort)param_2 * 0x100 + ((ushort)((uint)param_2 >> 8) & 0xff);
        pbVar5 = src + 2;
      }
    }
    if (uVar2 != uVar1) break;
    param_1 = pbVar4;
    src = pbVar5;
    if (uVar1 == 0) {
      return 0;
    }
  }
  return (-(uint)(uVar2 < uVar1) & 2) - 1;
}


/* ==== FUN_0040b530 @ 0040b530 ==== */

undefined4 * __cdecl FUN_0040b530(undefined4 *param_1,undefined4 *param_2,uint param_3)

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
          goto switchD_0040b6e7_caseD_2;
        case 3:
          goto switchD_0040b6e7_caseD_3;
        }
        goto switchD_0040b6e7_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_0040b6e7_caseD_0;
      case 1:
        goto switchD_0040b6e7_caseD_1;
      case 2:
        goto switchD_0040b6e7_caseD_2;
      case 3:
        goto switchD_0040b6e7_caseD_3;
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
              goto switchD_0040b6e7_caseD_2;
            case 3:
              goto switchD_0040b6e7_caseD_3;
            }
            goto switchD_0040b6e7_caseD_1;
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
              goto switchD_0040b6e7_caseD_2;
            case 3:
              goto switchD_0040b6e7_caseD_3;
            }
            goto switchD_0040b6e7_caseD_1;
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
              goto switchD_0040b6e7_caseD_2;
            case 3:
              goto switchD_0040b6e7_caseD_3;
            }
            goto switchD_0040b6e7_caseD_1;
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
switchD_0040b6e7_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return param_1;
    case 2:
switchD_0040b6e7_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return param_1;
    case 3:
switchD_0040b6e7_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return param_1;
    }
switchD_0040b6e7_caseD_0:
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
        goto switchD_0040b565_caseD_2;
      case 3:
        goto switchD_0040b565_caseD_3;
      }
      goto switchD_0040b565_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_0040b565_caseD_0;
    case 1:
      goto switchD_0040b565_caseD_1;
    case 2:
      goto switchD_0040b565_caseD_2;
    case 3:
      goto switchD_0040b565_caseD_3;
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
            goto switchD_0040b565_caseD_2;
          case 3:
            goto switchD_0040b565_caseD_3;
          }
          goto switchD_0040b565_caseD_1;
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
            goto switchD_0040b565_caseD_2;
          case 3:
            goto switchD_0040b565_caseD_3;
          }
          goto switchD_0040b565_caseD_1;
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
            goto switchD_0040b565_caseD_2;
          case 3:
            goto switchD_0040b565_caseD_3;
          }
          goto switchD_0040b565_caseD_1;
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
switchD_0040b565_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_0040b565_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_0040b565_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_0040b565_caseD_0:
  return param_1;
}


/* ==== wctomb @ 0040b870 ==== */

int __cdecl wctomb(char *s,ushort wc)

{
  char *lpMultiByteStr;
  int iVar1;
  
  lpMultiByteStr = s;
  if (s == (char *)0x0) {
    return 0;
  }
  if (DAT_00413a78 == 0) {
    if (wc < 0x100) {
      *s = (char)wc;
      return 1;
    }
  }
  else {
    s = (char *)0x0;
    iVar1 = WideCharToMultiByte(DAT_00413a88,0x220,(LPCWSTR)&wc,1,lpMultiByteStr,__mb_cur_max,
                                (LPCSTR)0x0,(LPBOOL)&s);
    if ((iVar1 != 0) && (s == (char *)0x0)) {
      return iVar1;
    }
  }
  errno = 0x2a;
  return -1;
}


/* ==== __aulldiv @ 0040b8f0 ==== */

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


/* ==== __aullrem @ 0040b960 ==== */

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


/* ==== _alloc_osfhnd @ 0040b9e0 ==== */

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
    if (0x413cbf < (int)piVar3) {
      return -1;
    }
  } while( true );
}


/* ==== _set_osfhnd @ 0040baa0 ==== */

int __cdecl _set_osfhnd(int fh,long value)

{
  int iVar1;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (*(int *)((&__pioinfo)[fh >> 5] + iVar1) == -1) {
      if (DAT_00410304 == 1) {
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


/* ==== _free_osfhnd @ 0040bb50 ==== */

int __cdecl _free_osfhnd(int fh)

{
  int iVar1;
  DWORD nStdHandle;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar1) & 1) != 0) &&
       (*(int *)((&__pioinfo)[fh >> 5] + iVar1) != -1)) {
      if (DAT_00410304 == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_0040bbba;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0040bbba:
      *(undefined4 *)((&__pioinfo)[fh >> 5] + iVar1) = 0xffffffff;
      return 0;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _get_osfhandle @ 0040bbf0 ==== */

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


/* ==== mbtowc @ 0040bc40 ==== */

int __cdecl mbtowc(ushort *pwc,char *s,uint n)

{
  byte bVar1;
  int iVar2;
  
  if ((s != (char *)0x0) && (n != 0)) {
    bVar1 = *s;
    if (bVar1 != 0) {
      if (DAT_00413a78 == 0) {
        if (pwc == (ushort *)0x0) {
          return 1;
        }
        *pwc = (ushort)bVar1;
        return 1;
      }
      if ((_pctype[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(DAT_00413a88,9,s,1,(LPWSTR)pwc,(uint)(pwc != (ushort *)0x0));
        if (iVar2 != 0) {
          return 1;
        }
        errno = 0x2a;
        return -1;
      }
      if (((1 < (int)__mb_cur_max) && ((int)__mb_cur_max <= (int)n)) &&
         (iVar2 = MultiByteToWideChar(DAT_00413a88,9,s,__mb_cur_max,(LPWSTR)pwc,
                                      (uint)(pwc != (ushort *)0x0)), iVar2 != 0)) {
        return __mb_cur_max;
      }
      if (n < __mb_cur_max) {
        errno = 0x2a;
        return -1;
      }
      if (s[1] != '\0') {
        return __mb_cur_max;
      }
      errno = 0x2a;
      return -1;
    }
    if (pwc != (ushort *)0x0) {
      *pwc = 0;
      return 0;
    }
  }
  return 0;
}


/* ==== isspace @ 0040bd40 ==== */

int __cdecl isspace(int c)

{
  int iVar1;
  
  if (1 < __mb_cur_max) {
    iVar1 = _isctype(c,8);
    return iVar1;
  }
  return (byte)_pctype[c * 2] & 8;
}


/* ==== __allmul @ 0040bd70 ==== */

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


/* ==== __allshl @ 0040bdb0 ==== */

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


/* ==== _sopen @ 0040bdd0 ==== */

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
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_00413bac != 0x8000)))) {
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
    goto switchD_0040be68_caseD_11;
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
      goto LAB_0040befb;
    }
    if (uVar1 != 0) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_0040bed6:
    dwCreationDisposition = 3;
    goto LAB_0040befb;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      dwCreationDisposition = 2;
      goto LAB_0040befb;
    }
    if (uVar1 != 0x200) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_0040bef6:
    dwCreationDisposition = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_0040be68_caseD_11:
          _doserrno = 0;
          errno = 0x16;
          return -1;
        }
        goto LAB_0040bed6;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_0040bef6;
      if (uVar1 != 0x700) {
        errno = 0x16;
        _doserrno = 0;
        return -1;
      }
    }
    dwCreationDisposition = 1;
  }
LAB_0040befb:
  dwFlagsAndAttributes = 0x80;
  if (((oflag & 0x100U) != 0) && (((byte)pmode & ~(byte)DAT_004137b8 & 0x80) == 0)) {
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


/* ==== atol @ 0040c190 ==== */

long __cdecl atol(char *s)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint c;
  int iVar4;
  byte *pbVar5;
  
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[(uint)(byte)*s * 2] & 8;
    }
    else {
      uVar2 = _isctype((uint)(byte)*s,8);
    }
    if (uVar2 == 0) break;
    s = s + 1;
  }
  uVar2 = (uint)(byte)*s;
  pbVar5 = (byte *)(s + 1);
  if ((uVar2 == 0x2d) || (c = uVar2, uVar2 == 0x2b)) {
    c = (uint)*pbVar5;
    pbVar5 = (byte *)(s + 2);
  }
  iVar4 = 0;
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar3 = (byte)_pctype[c * 2] & 4;
    }
    else {
      uVar3 = _isctype(c,4);
    }
    if (uVar3 == 0) break;
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    iVar4 = (c - 0x30) + iVar4 * 10;
    c = (uint)bVar1;
  }
  if (uVar2 == 0x2d) {
    iVar4 = -iVar4;
  }
  return iVar4;
}


/* ==== FUN_0040c230 @ 0040c230 ==== */

uint __cdecl FUN_0040c230(LPSTR param_1,LPCWSTR param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  DWORD DVar5;
  int iVar6;
  LPCWSTR lpWideCharStr;
  BOOL local_4;
  
  uVar4 = param_3;
  lpWideCharStr = param_2;
  uVar2 = 0;
  local_4 = 0;
  if ((param_1 != (LPSTR)0x0) && (param_3 == 0)) {
    return uVar2;
  }
  if (param_1 == (LPSTR)0x0) {
    if (DAT_00413a78 == 0) {
      uVar4 = FUN_0040c4f0(param_2);
      return uVar4;
    }
    iVar3 = WideCharToMultiByte(DAT_00413a88,0x220,param_2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,&local_4);
    if ((iVar3 != 0) && (local_4 == 0)) {
      return iVar3 - 1;
    }
  }
  else if (DAT_00413a78 == 0) {
    if (param_3 == 0) {
      return 0;
    }
    while ((ushort)*param_2 < 0x100) {
      param_1[uVar2] = (CHAR)*param_2;
      if (*param_2 == L'\0') {
        return uVar2;
      }
      uVar2 = uVar2 + 1;
      param_2 = param_2 + 1;
      if (param_3 <= uVar2) {
        return uVar2;
      }
    }
  }
  else if (__mb_cur_max == 1) {
    iVar3 = 0;
    if (param_3 != 0) {
      iVar3 = FUN_0040c420(param_2,param_3);
    }
    uVar4 = WideCharToMultiByte(DAT_00413a88,0x220,lpWideCharStr,iVar3,param_1,iVar3,(LPCSTR)0x0,
                                &local_4);
    if ((uVar4 != 0) && (local_4 == 0)) {
      if (param_1[uVar4 - 1] == '\0') {
        return uVar4 - 1;
      }
      return uVar4;
    }
  }
  else {
    iVar3 = WideCharToMultiByte(DAT_00413a88,0x220,param_2,-1,param_1,param_3,(LPCSTR)0x0,&local_4);
    if (iVar3 == 0) {
      if ((local_4 == 0) && (DVar5 = GetLastError(), DVar5 == 0x7a)) {
        uVar2 = 0;
        if (uVar4 != 0) {
          do {
            iVar3 = WideCharToMultiByte(DAT_00413a88,0,lpWideCharStr,1,(LPSTR)&param_2,__mb_cur_max,
                                        (LPCSTR)0x0,&local_4);
            if (iVar3 == 0) {
              errno = 0x2a;
              return 0xffffffff;
            }
            if (local_4 != 0) {
              errno = 0x2a;
              return 0xffffffff;
            }
            if (uVar4 < iVar3 + uVar2) {
              return uVar2;
            }
            iVar6 = 0;
            if (0 < iVar3) {
              do {
                cVar1 = *(char *)((int)&param_2 + iVar6);
                param_1[uVar2] = cVar1;
                if (cVar1 == '\0') {
                  return uVar2;
                }
                iVar6 = iVar6 + 1;
                uVar2 = uVar2 + 1;
              } while (iVar6 < iVar3);
            }
            lpWideCharStr = lpWideCharStr + 1;
          } while (uVar2 < uVar4);
        }
        return uVar2;
      }
    }
    else if (local_4 == 0) {
      return iVar3 - 1;
    }
  }
  errno = 0x2a;
  return 0xffffffff;
}


/* ==== FUN_0040c420 @ 0040c420 ==== */

int __cdecl FUN_0040c420(short *param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = param_1;
  iVar2 = param_2;
  if (param_2 != 0) {
    do {
      if (*psVar1 == 0) break;
      psVar1 = psVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if ((iVar2 != 0) && (*psVar1 == 0)) {
      return ((int)psVar1 - (int)param_1 >> 1) + 1;
    }
  }
  return param_2;
}


/* ==== getenv @ 0040c460 ==== */

char __cdecl getenv(char *name)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint n;
  uint uVar4;
  char *a;
  int *piVar5;
  char *pcVar6;
  
  if (((_environ != (int *)0x0) ||
      (((_wenviron == 0 || (iVar2 = __wtomb_environ(), iVar2 == 0)) && (_environ != (int *)0x0))))
     && (name != (char *)0x0)) {
    uVar3 = 0xffffffff;
    a = (char *)*_environ;
    pcVar6 = name;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    n = ~uVar3 - 1;
    piVar5 = _environ;
    if (a != (char *)0x0) {
      do {
        uVar4 = 0xffffffff;
        pcVar6 = a;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        if (((n < ~uVar4 - 1) && (a[n] == '=')) && (iVar2 = _strnicoll(a,name,n), iVar2 == 0)) {
          return (char)~uVar3 + (char)*piVar5;
        }
        a = (char *)piVar5[1];
        piVar5 = piVar5 + 1;
        if (a == (char *)0x0) {
          return '\0';
        }
      } while( true );
    }
  }
  return '\0';
}


/* ==== FUN_0040c4f0 @ 0040c4f0 ==== */

int __cdecl FUN_0040c4f0(short *param_1)

{
  short sVar1;
  short *psVar2;
  
  sVar1 = *param_1;
  psVar2 = param_1;
  while (psVar2 = psVar2 + 1, sVar1 != 0) {
    sVar1 = *psVar2;
  }
  return ((int)psVar2 - (int)param_1 >> 1) + -1;
}


/* ==== __crtMessageBoxA @ 0040c510 ==== */

int __cdecl __crtMessageBoxA(char *text,char *caption,uint type)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_00413ba0 != (FARPROC)0x0) {
LAB_0040c560:
    if (DAT_00413ba4 != (FARPROC)0x0) {
      iVar1 = (*DAT_00413ba4)();
    }
    if ((iVar1 != 0) && (DAT_00413ba8 != (FARPROC)0x0)) {
      iVar1 = (*DAT_00413ba8)(iVar1);
    }
    iVar1 = (*DAT_00413ba0)(iVar1,text,caption,type);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_00413ba0 = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_00413ba0 != (FARPROC)0x0) {
      DAT_00413ba4 = GetProcAddress(hModule,"GetActiveWindow");
      DAT_00413ba8 = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_0040c560;
    }
  }
  return 0;
}


/* ==== _strpbrk @ 0040c5a0 ==== */

/* Library Function - Single Match
    _strpbrk
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strpbrk(char *_Str,char *_Control)

{
  byte bVar1;
  byte *pbVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *_Control;
    if (bVar1 == 0) break;
    _Control = _Control + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  do {
    pbVar2 = (byte *)_Str;
    bVar1 = *pbVar2;
    if (bVar1 == 0) {
      return (char *)0x0;
    }
    _Str = (char *)(pbVar2 + 1);
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return (char *)pbVar2;
}


/* ==== __strcmpi @ 0040c5e0 ==== */

/* Library Function - Single Match
    __strcmpi
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl __strcmpi(char *_Str1,char *_Str2)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  int c;
  int iVar7;
  
  if (DAT_00413a78 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_0040c62e;
        bVar5 = *_Str2;
        _Str2 = _Str2 + 1;
        bVar4 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_0040c62e:
    iVar7 = (int)cVar6;
  }
  else {
    c = 0;
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') {
          return iVar7;
        }
        cVar6 = *_Str2;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),cVar6);
        _Str2 = _Str2 + 1;
        cVar1 = *_Str1;
        c = CONCAT31((int3)((uint)c >> 8),cVar1);
        _Str1 = _Str1 + 1;
      } while (cVar6 == cVar1);
      c = tolower(c);
      iVar7 = tolower(iVar7);
    } while ((byte)c == (byte)iVar7);
    uVar2 = (uint)((byte)c < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
  }
  return iVar7;
}


/* ==== _fptrap @ 0040c670 ==== */

void _fptrap(void)

{
  _amsg_exit(2);
  return;
}


/* ==== _chsize @ 0040c680 ==== */

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
  
  FUN_0040c940();
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
      iVar4 = FUN_0040c8c0(in_stack_00001008,0x8000);
      while( true ) {
        cnt = 0x1000;
        if ((int)uVar6 < 0x1000) {
          cnt = uVar6;
        }
        iVar2 = _write(in_stack_00001008,&fh,cnt);
        if (iVar2 == -1) break;
        uVar6 = uVar6 - iVar2;
        if ((int)uVar6 < 1) {
LAB_0040c761:
          FUN_0040c8c0(in_stack_00001008,iVar4);
          _lseek(in_stack_00001008,pos,0);
          return iVar5;
        }
      }
      if (_doserrno == 5) {
        errno = 0xd;
      }
      iVar5 = -1;
      goto LAB_0040c761;
    }
  }
  else {
    errno = 9;
  }
  return -1;
}


/* ==== _strnicoll @ 0040c800 ==== */

int __cdecl _strnicoll(char *a,char *b,uint n)

{
  int iVar1;
  
  if (n == 0) {
    return 0;
  }
  iVar1 = __crtCompareStringA(DAT_00413a54,1,a,n,b,n,DAT_00413a50);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}


/* ==== __wtomb_environ @ 0040c840 ==== */

int __wtomb_environ(void)

{
  LPCWSTR lpWideCharStr;
  uint size;
  char *lpMultiByteStr;
  int iVar1;
  int *piVar2;
  
  lpWideCharStr = (LPCWSTR)*_wenviron;
  piVar2 = _wenviron;
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return 0;
  }
  while (((size = WideCharToMultiByte(1,0,lpWideCharStr,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0),
          size != 0 && (malloc(size), lpMultiByteStr != (char *)0x0)) &&
         (iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*piVar2,-1,lpMultiByteStr,size,(LPCSTR)0x0,
                                      (LPBOOL)0x0), iVar1 != 0))) {
    __crtsetenv(lpMultiByteStr,0);
    lpWideCharStr = (LPCWSTR)piVar2[1];
    piVar2 = piVar2 + 1;
    if (lpWideCharStr == (LPCWSTR)0x0) {
      return 0;
    }
  }
  return -1;
}


/* ==== FUN_0040c8c0 @ 0040c8c0 ==== */

int __cdecl FUN_0040c8c0(uint param_1,int param_2)

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


/* ==== FUN_0040c940 @ 0040c940 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_0040c940(void)

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


/* ==== __crtCompareStringA @ 0040c970 ==== */

int __cdecl __crtCompareStringA(ulong lcid,ulong flags,char *s1,int n1,char *s2,int n2,int codepage)

{
  int iVar1;
  BOOL BVar2;
  BYTE *pBVar3;
  int cchWideChar;
  PCNZWCH lpWideCharStr;
  LPWSTR lpWideCharStr_00;
  int iVar4;
  int local_18;
  _cpinfo local_14;
  
  if (DAT_00413bb4 == 0) {
    iVar1 = CompareStringW(0,0,L"",1,L"",1);
    if (iVar1 == 0) {
      iVar1 = CompareStringA(0,0,"",1,"",1);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_00413bb4 = 2;
    }
    else {
      DAT_00413bb4 = 1;
    }
  }
  iVar1 = n1;
  if (0 < n1) {
    iVar1 = __ansicp((int)s1,n1);
  }
  if (0 < n2) {
    n2 = __ansicp((int)s2,n2);
  }
  if (DAT_00413bb4 == 2) {
    iVar1 = CompareStringA(lcid,flags,s1,iVar1,s2,n2);
    return iVar1;
  }
  local_18 = DAT_00413bb4;
  if (DAT_00413bb4 == 1) {
    local_18 = 0;
    n1 = 0;
    if (codepage == 0) {
      codepage = DAT_00413a88;
    }
    if ((iVar1 == 0) || (n2 == 0)) {
      if (iVar1 == n2) {
        return 2;
      }
      if (1 < n2) {
        return 1;
      }
      if (1 < iVar1) {
        return 3;
      }
      BVar2 = GetCPInfo(codepage,&local_14);
      if (BVar2 == 0) {
        return 0;
      }
      if (0 < iVar1) {
        if (local_14.MaxCharSize < 2) {
          return 3;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 3;
          }
          if ((*pBVar3 <= (byte)*s1) && ((byte)*s1 <= pBVar3[1])) break;
          local_14.LeadByte[0] = pBVar3[2];
          pBVar3 = pBVar3 + 2;
        }
        return 2;
      }
      if (0 < n2) {
        if (local_14.MaxCharSize < 2) {
          return 1;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 1;
          }
          if ((*pBVar3 <= (byte)*s2) && ((byte)*s2 <= pBVar3[1])) break;
          local_14.LeadByte[0] = pBVar3[2];
          pBVar3 = pBVar3 + 2;
        }
        return 2;
      }
    }
    cchWideChar = MultiByteToWideChar(codepage,9,s1,iVar1,(LPWSTR)0x0,0);
    if (cchWideChar == 0) {
      return 0;
    }
    malloc(cchWideChar * 2);
    if (lpWideCharStr == (PCNZWCH)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(codepage,1,s1,iVar1,lpWideCharStr,cchWideChar);
    if ((((iVar1 != 0) && (iVar1 = MultiByteToWideChar(codepage,9,s2,n2,(LPWSTR)0x0,0), iVar1 != 0))
        && (malloc(iVar1 * 2), n1 = (int)lpWideCharStr_00, lpWideCharStr_00 != (LPWSTR)0x0)) &&
       (iVar4 = MultiByteToWideChar(codepage,1,s2,n2,lpWideCharStr_00,iVar1), iVar4 != 0)) {
      local_18 = CompareStringW(lcid,flags,lpWideCharStr,cchWideChar,lpWideCharStr_00,iVar1);
    }
    free(lpWideCharStr);
    free((void *)n1);
  }
  return local_18;
}


/* ==== __crtsetenv @ 0040cc40 ==== */

int __cdecl __crtsetenv(char *option,int primary)

{
  char **ppcVar1;
  char **p;
  char cVar2;
  byte *pbVar3;
  undefined3 extraout_var;
  int iVar4;
  char **extraout_EAX;
  undefined4 *extraout_EAX_00;
  int len;
  char **extraout_EAX_01;
  LPCSTR lpName;
  char **extraout_EAX_02;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  bool bVar9;
  
  if (option == (char *)0x0) {
    return -1;
  }
  pbVar3 = FUN_0040d0e0((byte *)option,0x3d);
  if (pbVar3 == (byte *)0x0) {
    return -1;
  }
  if ((byte *)option == pbVar3) {
    return -1;
  }
  bVar9 = pbVar3[1] == 0;
  if (_environ == __initenv) {
    cVar2 = copy_environ(_environ);
    _environ = (char **)CONCAT31(extraout_var,cVar2);
  }
  if (_environ == (char **)0x0) {
    if ((primary == 0) || (_wenviron == (undefined4 *)0x0)) {
      if (bVar9) {
        return 0;
      }
      malloc(4);
      if (extraout_EAX == (char **)0x0) {
        _environ = extraout_EAX;
        return -1;
      }
      _environ = extraout_EAX;
      *extraout_EAX = (char *)0x0;
      if (_wenviron == (undefined4 *)0x0) {
        malloc(4);
        if (extraout_EAX_00 == (undefined4 *)0x0) {
          _wenviron = extraout_EAX_00;
          return -1;
        }
        _wenviron = extraout_EAX_00;
        *extraout_EAX_00 = 0;
      }
    }
    else {
      iVar4 = __wtomb_environ();
      if (iVar4 != 0) {
        return -1;
      }
    }
  }
  p = _environ;
  len = (int)pbVar3 - (int)option;
  iVar4 = findenv(option,len);
  if ((iVar4 < 0) || (*p == (char *)0x0)) {
    if (bVar9) {
      return 0;
    }
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    realloc(p,iVar4 * 4 + 8);
    if (extraout_EAX_02 == (char **)0x0) {
      return -1;
    }
    extraout_EAX_02[iVar4] = option;
    extraout_EAX_02[iVar4 + 1] = (char *)0x0;
    _environ = extraout_EAX_02;
  }
  else if (bVar9) {
    free(p[iVar4]);
    pcVar7 = p[iVar4];
    ppcVar1 = p + iVar4;
    while (pcVar7 != (char *)0x0) {
      *ppcVar1 = ppcVar1[1];
      iVar4 = iVar4 + 1;
      pcVar7 = ppcVar1[1];
      ppcVar1 = ppcVar1 + 1;
    }
    realloc(p,iVar4 * 4);
    if (extraout_EAX_01 != (char **)0x0) {
      _environ = extraout_EAX_01;
    }
  }
  else {
    p[iVar4] = option;
  }
  if (primary != 0) {
    uVar5 = 0xffffffff;
    pcVar7 = option;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar2 != '\0');
    malloc(~uVar5 + 1);
    if (lpName != (LPCSTR)0x0) {
      uVar5 = 0xffffffff;
      do {
        pcVar7 = option;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar7 = option + 1;
        cVar2 = *option;
        option = pcVar7;
      } while (cVar2 != '\0');
      uVar5 = ~uVar5;
      pcVar7 = pcVar7 + -uVar5;
      pcVar8 = lpName;
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
      lpName[len] = '\0';
      SetEnvironmentVariableA(lpName,(LPCSTR)(~-(uint)bVar9 & (uint)(lpName + len + 1)));
      free(lpName);
      return 0;
    }
  }
  return 0;
}


/* ==== findenv @ 0040ce50 ==== */

int __cdecl findenv(char *name,int len)

{
  char *b;
  int iVar1;
  int *piVar2;
  
  b = (char *)*_environ;
  piVar2 = _environ;
  if (b == (char *)0x0) {
    return 0;
  }
  while ((iVar1 = _strnicoll(name,b,len), iVar1 != 0 ||
         ((*(char *)(*piVar2 + len) != '=' && (*(char *)(*piVar2 + len) != '\0'))))) {
    b = (char *)piVar2[1];
    piVar2 = piVar2 + 1;
    if (b == (char *)0x0) {
      return -((int)piVar2 - (int)_environ >> 2);
    }
  }
  return (int)piVar2 - (int)_environ >> 2;
}


/* ==== copy_environ @ 0040ced0 ==== */

char __cdecl copy_environ(char **oldenviron)

{
  char *pcVar1;
  char cVar2;
  char **ppcVar3;
  undefined4 *extraout_EAX;
  undefined3 extraout_var;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = 0;
  if (oldenviron != (char **)0x0) {
    pcVar1 = *oldenviron;
    ppcVar3 = oldenviron;
    while (pcVar1 != (char *)0x0) {
      ppcVar3 = ppcVar3 + 1;
      iVar4 = iVar4 + 1;
      pcVar1 = *ppcVar3;
    }
    malloc(iVar4 * 4 + 4);
    if (extraout_EAX == (undefined4 *)0x0) {
      _amsg_exit(9);
    }
    pcVar1 = *oldenviron;
    puVar5 = extraout_EAX;
    while (pcVar1 != (char *)0x0) {
      oldenviron = oldenviron + 1;
      cVar2 = _strdup(pcVar1);
      *puVar5 = CONCAT31(extraout_var,cVar2);
      puVar5 = puVar5 + 1;
      pcVar1 = *oldenviron;
    }
    *puVar5 = 0;
    return (char)extraout_EAX;
  }
  return '\0';
}


/* ==== realloc @ 0040cf40 ==== */

void __cdecl realloc(void *p,uint size)

{
  byte *pmap;
  int iVar1;
  undefined4 *extraout_EAX;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  void *local_8;
  void *local_4;
  
  if (p == (void *)0x0) {
    malloc(size);
    return;
  }
  if (size == 0) {
    free(p);
    return;
  }
  if (size < 0xffffffe1) {
    if (size == 0) {
      size = 0x10;
    }
    else {
      size = size + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar4 = (undefined4 *)0x0;
    if (size < 0xffffffe1) {
      __sbh_find_block(p,&local_4,&local_8);
      if (pmap == (byte *)0x0) {
        puVar4 = HeapReAlloc(_crtheap,0,p,size);
        goto LAB_0040d0aa;
      }
      if (size < __sbh_threshold) {
        iVar1 = __sbh_resize_block(local_4,local_8,pmap,size >> 4);
        puVar4 = p;
        if (iVar1 != 0) goto LAB_0040d03f;
        __sbh_alloc_block(size >> 4);
        if (extraout_EAX != (undefined4 *)0x0) {
          uVar3 = (uint)*pmap << 4;
          if (size <= (uint)*pmap << 4) {
            uVar3 = size;
          }
          puVar5 = extraout_EAX;
          for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
            puVar5 = (undefined4 *)((int)puVar5 + 1);
          }
          __sbh_free_block(local_4,local_8,pmap);
          puVar4 = extraout_EAX;
          goto LAB_0040d03f;
        }
      }
      else {
LAB_0040d03f:
        if (puVar4 != (undefined4 *)0x0) {
          return;
        }
      }
      puVar4 = HeapAlloc(_crtheap,0,size);
      if (puVar4 != (undefined4 *)0x0) {
        uVar3 = (uint)*pmap << 4;
        if (size <= (uint)*pmap << 4) {
          uVar3 = size;
        }
        puVar5 = p;
        puVar6 = puVar4;
        for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        __sbh_free_block(local_4,local_8,pmap);
        goto LAB_0040d0aa;
      }
    }
    else {
LAB_0040d0aa:
      if (puVar4 != (undefined4 *)0x0) {
        return;
      }
    }
    if (_newmode == 0) {
      return;
    }
    iVar1 = _callnewh(size);
    if (iVar1 == 0) {
      return;
    }
  } while( true );
}


/* ==== FUN_0040d0e0 @ 0040d0e0 ==== */

byte * __cdecl FUN_0040d0e0(byte *param_1,uint param_2)

{
  char cVar1;
  undefined3 extraout_var;
  uint uVar2;
  byte *pbVar3;
  
  if (DAT_00413a50 == 0) {
    cVar1 = strchr((char *)param_1,param_2);
    return (byte *)CONCAT31(extraout_var,cVar1);
  }
  uVar2 = (uint)(ushort)*param_1;
  if (*param_1 == 0) {
LAB_0040d177:
    return (byte *)((param_2 != uVar2) - 1 & (uint)param_1);
  }
  do {
    if ((*(byte *)((int)&DAT_00413848 + uVar2 + 1) & 4) == 0) {
      pbVar3 = param_1;
      if (param_2 == uVar2) goto LAB_0040d177;
    }
    else {
      pbVar3 = param_1 + 1;
      if (param_1[1] == 0) {
        return (byte *)0x0;
      }
      if (param_2 == (uVar2 << 8 | (uint)param_1[1])) {
        return param_1;
      }
    }
    uVar2 = (uint)(ushort)pbVar3[1];
    param_1 = pbVar3 + 1;
    if (pbVar3[1] == 0) {
      return (byte *)((param_2 != 0) - 1 & (uint)param_1);
    }
  } while( true );
}


/* ==== RtlUnwind @ 0040d190 ==== */

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x0040d190. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


/* ==== FUN_0040d1a0 @ 0040d1a0 ==== */

undefined4 __cdecl FUN_0040d1a0(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


/* ==== FUN_0040d1b0 @ 0040d1b0 ==== */

uint __cdecl FUN_0040d1b0(byte param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  
  pbVar2 = param_2;
  if (param_2[1] == 0x3a) {
    pbVar2 = param_2 + 2;
  }
  bVar1 = *pbVar2;
  if ((((bVar1 == 0x5c) || (bVar1 == 0x2f)) && (pbVar2[1] == 0)) ||
     (((param_1 & 0x10) != 0 || (uVar4 = 0x8000, bVar1 == 0)))) {
    uVar4 = 0x4040;
  }
  uVar4 = uVar4 | (uint)(~param_1 & 1 | 2) << 7;
  pbVar2 = (byte *)FUN_0040d750(param_2,0x2e);
  if (pbVar2 != (byte *)0x0) {
    iVar3 = FUN_0040b350(pbVar2,&DAT_0040e530);
    if (iVar3 != 0) {
      iVar3 = FUN_0040b350(pbVar2,&DAT_0040e528);
      if (iVar3 != 0) {
        iVar3 = FUN_0040b350(pbVar2,&DAT_0040e520);
        if (iVar3 != 0) {
          iVar3 = FUN_0040b350(pbVar2,&DAT_0040e518);
          if (iVar3 != 0) goto LAB_0040d25a;
        }
      }
    }
    uVar4 = uVar4 | 0x40;
  }
LAB_0040d25a:
  return (uVar4 & 0x1c0) >> 6 | uVar4 | uVar4 >> 3 & 0x38;
}


/* ==== FUN_0040d280 @ 0040d280 ==== */

undefined4 __cdecl FUN_0040d280(byte *param_1,int *param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  HANDLE hFindFile;
  LPSTR lpRootPathName;
  UINT UVar4;
  long lVar5;
  BOOL BVar6;
  DWORD oserrno;
  int iVar7;
  LPSTR pCVar8;
  _SYSTEMTIME local_260;
  int local_250;
  _FILETIME local_24c;
  _WIN32_FIND_DATAA local_244;
  char local_104 [260];
  
  pcVar2 = FUN_0040b080(param_1,&DAT_0040e53c);
  if (pcVar2 != (char *)0x0) {
    errno = 2;
    _doserrno = 2;
    return 0xffffffff;
  }
  if (param_1[1] == 0x3a) {
    if ((*param_1 != 0) && (param_1[2] == 0)) {
      errno = 2;
      _doserrno = 2;
      return 0xffffffff;
    }
    uVar3 = FUN_0040d8f0((int)(char)*param_1);
    local_250 = uVar3 - 0x60;
  }
  else {
    local_250 = FUN_0040d8a0();
  }
  hFindFile = FindFirstFileA((LPCSTR)param_1,&local_244);
  if (hFindFile != (HANDLE)0xffffffff) {
    BVar6 = FileTimeToLocalFileTime(&local_244.ftLastWriteTime,&local_24c);
    if ((BVar6 == 0) || (BVar6 = FileTimeToSystemTime(&local_24c,&local_260), BVar6 == 0)) {
LAB_0040d5c6:
      oserrno = GetLastError();
      _dosmaperr(oserrno);
      FindClose(hFindFile);
      return 0xffffffff;
    }
    lVar5 = __loctotime_t((uint)local_260.wYear,(uint)local_260.wMonth,(uint)local_260.wDay,
                          (uint)local_260.wHour,(uint)local_260.wMinute,(uint)local_260.wSecond,-1);
    param_2[7] = lVar5;
    if ((local_244.ftLastAccessTime.dwLowDateTime != 0) ||
       (local_244.ftLastAccessTime.dwHighDateTime != 0)) {
      BVar6 = FileTimeToLocalFileTime(&local_244.ftLastAccessTime,&local_24c);
      if ((BVar6 == 0) || (BVar6 = FileTimeToSystemTime(&local_24c,&local_260), BVar6 == 0))
      goto LAB_0040d5c6;
      lVar5 = __loctotime_t((uint)local_260.wYear,(uint)local_260.wMonth,(uint)local_260.wDay,
                            (uint)local_260.wHour,(uint)local_260.wMinute,(uint)local_260.wSecond,-1
                           );
    }
    param_2[6] = lVar5;
    if ((local_244.ftCreationTime.dwLowDateTime == 0) &&
       (local_244.ftCreationTime.dwHighDateTime == 0)) {
      param_2[8] = param_2[7];
    }
    else {
      BVar6 = FileTimeToLocalFileTime(&local_244.ftCreationTime,&local_24c);
      if ((BVar6 == 0) || (BVar6 = FileTimeToSystemTime(&local_24c,&local_260), BVar6 == 0))
      goto LAB_0040d5c6;
      lVar5 = __loctotime_t((uint)local_260.wYear,(uint)local_260.wMonth,(uint)local_260.wDay,
                            (uint)local_260.wHour,(uint)local_260.wMinute,(uint)local_260.wSecond,-1
                           );
      param_2[8] = lVar5;
    }
    FindClose(hFindFile);
LAB_0040d584:
    uVar3 = FUN_0040d1b0((byte)local_244.dwFileAttributes,param_1);
    *(short *)((int)param_2 + 6) = (short)uVar3;
    *(undefined2 *)(param_2 + 2) = 1;
    *param_2 = local_250 + -1;
    param_2[4] = local_250 + -1;
    param_2[5] = local_244.nFileSizeLow;
    *(undefined2 *)(param_2 + 1) = 0;
    *(undefined2 *)(param_2 + 3) = 0;
    *(undefined2 *)((int)param_2 + 10) = 0;
    return 0;
  }
  pcVar2 = FUN_0040b080(param_1,&DAT_0040e538);
  if ((pcVar2 != (char *)0x0) &&
     (lpRootPathName = FUN_0040d7d0(local_104,(LPCSTR)param_1,(LPSTR)0x104),
     lpRootPathName != (LPSTR)0x0)) {
    iVar7 = -1;
    pCVar8 = lpRootPathName;
    do {
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      cVar1 = *pCVar8;
      pCVar8 = pCVar8 + 1;
    } while (cVar1 != '\0');
    if ((iVar7 != -5) && (iVar7 = FUN_0040d5f0(lpRootPathName), iVar7 == 0)) {
      errno = 2;
      _doserrno = 2;
      return 0xffffffff;
    }
    UVar4 = GetDriveTypeA(lpRootPathName);
    if (1 < UVar4) {
      local_244.dwFileAttributes = 0x10;
      local_244.nFileSizeHigh = 0;
      local_244.nFileSizeLow = 0;
      local_244.cFileName[0] = '\0';
      lVar5 = __loctotime_t(0x7bc,1,1,0,0,0,-1);
      param_2[7] = lVar5;
      param_2[6] = lVar5;
      param_2[8] = lVar5;
      goto LAB_0040d584;
    }
  }
  errno = 2;
  _doserrno = 2;
  return 0xffffffff;
}


/* ==== FUN_0040d5f0 @ 0040d5f0 ==== */

undefined4 __cdecl FUN_0040d5f0(char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar3 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  if (((4 < ~uVar2 - 1) && ((*param_1 == '\\' || (*param_1 == '/')))) &&
     ((param_1[1] == '\\' || (param_1[1] == '/')))) {
    pcVar3 = param_1 + 3;
    cVar1 = param_1[3];
    while (((cVar1 != '\0' && (cVar1 != '\\')) && (cVar1 != '/'))) {
      pcVar4 = pcVar3 + 1;
      pcVar3 = pcVar3 + 1;
      cVar1 = *pcVar4;
    }
    if ((*pcVar3 != '\0') && (pcVar4 = pcVar3 + 1, pcVar3[1] != '\0')) {
      cVar1 = *pcVar4;
      while (((cVar1 != '\0' && (cVar1 != '\\')) && (cVar1 != '/'))) {
        pcVar3 = pcVar4 + 1;
        pcVar4 = pcVar4 + 1;
        cVar1 = *pcVar3;
      }
      if ((*pcVar4 == '\0') || (pcVar4[1] == '\0')) {
        return 1;
      }
    }
  }
  return 0;
}


/* ==== FUN_0040d670 @ 0040d670 ==== */

byte * __cdecl FUN_0040d670(byte *param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  
  iVar6 = 0;
  uVar4 = GetCurrentProcessId();
  bVar2 = *param_1;
  pbVar7 = param_1;
  while (bVar2 != 0) {
    pbVar1 = pbVar7 + 1;
    pbVar7 = pbVar7 + 1;
    bVar2 = *pbVar1;
  }
  while ((pbVar7 = pbVar7 + -1, param_1 <= pbVar7 &&
         (iVar5 = FUN_0040d9e0(param_1,pbVar7), iVar5 == 0))) {
    if (*pbVar7 != 0x58) {
      return (byte *)0x0;
    }
    if (4 < iVar6) break;
    iVar6 = iVar6 + 1;
    *pbVar7 = (char)((ulonglong)uVar4 % 10) + 0x30;
    uVar4 = uVar4 / 10;
  }
  uVar3 = errno;
  if ((*pbVar7 == 0x58) && (4 < iVar6)) {
    *pbVar7 = 0x61;
    uVar3 = errno;
    iVar6 = 0x62;
    errno = 0;
    while( true ) {
      iVar5 = FUN_0040d990((LPCSTR)param_1,0);
      if ((iVar5 != 0) && (errno != 0xd)) {
        errno = uVar3;
        return param_1;
      }
      errno = 0;
      if (iVar6 == 0x7b) break;
      *pbVar7 = (byte)iVar6;
      iVar6 = iVar6 + 1;
    }
  }
  errno = uVar3;
  return (byte *)0x0;
}


/* ==== FUN_0040d750 @ 0040d750 ==== */

void __cdecl FUN_0040d750(byte *param_1,uint param_2)

{
  ushort uVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  
  pbVar2 = (byte *)0x0;
  if (DAT_00413a50 == 0) {
    _strrchr((char *)param_1,param_2);
    return;
  }
  do {
    bVar4 = *param_1;
    if ((*(byte *)((int)&DAT_00413848 + bVar4 + 1) & 4) == 0) {
      pbVar5 = param_1;
      bVar3 = bVar4;
      if (param_2 == bVar4) {
LAB_0040d7bf:
        pbVar2 = param_1;
        pbVar5 = pbVar2;
        bVar4 = bVar3;
      }
    }
    else {
      bVar3 = param_1[1];
      pbVar5 = param_1 + 1;
      if (bVar3 == 0) {
        param_1 = pbVar5;
        bVar4 = bVar3;
        if (pbVar2 == (byte *)0x0) goto LAB_0040d7bf;
      }
      else {
        uVar1 = CONCAT11(bVar4,bVar3);
        bVar4 = bVar3;
        if (param_2 == uVar1) {
          pbVar2 = param_1;
        }
      }
    }
    param_1 = pbVar5 + 1;
    if (bVar4 == 0) {
      return;
    }
  } while( true );
}


/* ==== FUN_0040d7d0 @ 0040d7d0 ==== */

LPSTR __cdecl FUN_0040d7d0(char *param_1,LPCSTR param_2,LPSTR param_3)

{
  LPSTR extraout_EAX;
  LPSTR pCVar1;
  DWORD oserrno;
  LPSTR pCVar2;
  LPSTR nBufferLength;
  
  if ((param_2 == (LPCSTR)0x0) || (*param_2 == '\0')) {
    pCVar2 = (LPSTR)FUN_0040da40(param_1,(uint)param_3);
    return pCVar2;
  }
  pCVar2 = param_1;
  nBufferLength = param_3;
  if (param_1 == (char *)0x0) {
    malloc(0x104);
    if (extraout_EAX == (LPSTR)0x0) {
      errno = 0xc;
      return (LPSTR)0x0;
    }
    pCVar2 = extraout_EAX;
    nBufferLength = (LPSTR)0x104;
  }
  pCVar1 = (LPSTR)GetFullPathNameA(param_2,(DWORD)nBufferLength,pCVar2,&param_3);
  if (pCVar1 < nBufferLength) {
    if (pCVar1 != (LPSTR)0x0) {
      return pCVar2;
    }
    if (param_1 == (char *)0x0) {
      free(pCVar2);
    }
    oserrno = GetLastError();
    _dosmaperr(oserrno);
    return (LPSTR)0x0;
  }
  if (param_1 == (char *)0x0) {
    free(pCVar2);
  }
  errno = 0x22;
  return (LPSTR)0x0;
}


/* ==== FUN_0040d8a0 @ 0040d8a0 ==== */

int FUN_0040d8a0(void)

{
  DWORD DVar1;
  int iVar2;
  uint local_104 [65];
  
  iVar2 = 0;
  DVar1 = GetCurrentDirectoryA(0x104,(LPSTR)local_104);
  if ((DVar1 != 0) && ((char)(local_104[0] >> 8) == ':')) {
    iVar2 = toupper(local_104[0] & 0xff);
    iVar2 = iVar2 + -0x40;
  }
  return iVar2;
}


/* ==== FUN_0040d8f0 @ 0040d8f0 ==== */

uint __cdecl FUN_0040d8f0(uint param_1)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  uint local_8 [2];
  
  uVar1 = param_1;
  if (param_1 < 0x100) {
    if ((*(byte *)((int)&DAT_00413848 + param_1 + 1) & 0x10) == 0x10) {
      return (uint)(byte)(&DAT_00413950)[param_1];
    }
  }
  else {
    bVar2 = (byte)(param_1 >> 8);
    param_1 = CONCAT31(CONCAT21(param_1._2_2_,(char)param_1),bVar2);
    if ((*(byte *)((int)&DAT_00413848 + bVar2 + 1) & 4) != 0) {
      iVar3 = __crtLCMapStringA(DAT_00413a54,0x100,(char *)&param_1,2,(char *)local_8,2,DAT_00413a50
                                ,1);
      if (iVar3 != 0) {
        return (local_8[0] & 0xff) * 0x100 + (local_8[0] >> 8 & 0xff);
      }
    }
  }
  return uVar1;
}


/* ==== FUN_0040d990 @ 0040d990 ==== */

undefined4 __cdecl FUN_0040d990(LPCSTR param_1,byte param_2)

{
  DWORD DVar1;
  
  DVar1 = GetFileAttributesA(param_1);
  if (DVar1 == 0xffffffff) {
    DVar1 = GetLastError();
    _dosmaperr(DVar1);
    return 0xffffffff;
  }
  if (((DVar1 & 1) != 0) && ((param_2 & 2) != 0)) {
    errno = 0xd;
    _doserrno = 5;
    return 0xffffffff;
  }
  return 0;
}


/* ==== FUN_0040d9e0 @ 0040d9e0 ==== */

undefined4 __cdecl FUN_0040d9e0(byte *param_1,byte *param_2)

{
  if ((DAT_00413a50 != 0) && (param_1 <= param_2)) {
    while (*param_1 != 0) {
      if ((*(byte *)((int)&DAT_00413848 + *param_1 + 1) & 4) != 0) {
        param_1 = param_1 + 1;
        if (param_1 == param_2) {
          return 0xffffffff;
        }
        if (*param_1 == 0) {
          return 0;
        }
      }
      param_1 = param_1 + 1;
      if (param_2 < param_1) {
        return 0;
      }
    }
  }
  return 0;
}


/* ==== GetCurrentProcessId @ 0040da30 ==== */

DWORD GetCurrentProcessId(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040da30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetCurrentProcessId();
  return DVar1;
}


/* ==== FUN_0040da40 @ 0040da40 ==== */

void __cdecl FUN_0040da40(char *param_1,uint param_2)

{
  FUN_0040da60(0,param_1,param_2);
  return;
}


/* ==== FUN_0040da60 @ 0040da60 ==== */

char * __cdecl FUN_0040da60(uint param_1,char *param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  DWORD DVar3;
  uint uVar4;
  char *extraout_EAX;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char local_10c [4];
  LPSTR local_108;
  CHAR local_104 [260];
  
  if (param_1 == 0) {
    DVar3 = GetCurrentDirectoryA(0x104,local_104);
  }
  else {
    iVar2 = FUN_0040db90(param_1);
    if (iVar2 == 0) {
      _doserrno = 0xf;
      errno = 0xd;
      return (char *)0x0;
    }
    local_10c[0] = (char)param_1 + '@';
    local_10c[1] = 0x3a;
    local_10c[2] = 0x2e;
    local_10c[3] = 0;
    DVar3 = GetFullPathNameA(local_10c,0x104,local_104,&local_108);
  }
  if ((DVar3 == 0) || (uVar4 = DVar3 + 1, 0x104 < uVar4)) {
    return (char *)0x0;
  }
  if (param_2 == (char *)0x0) {
    if ((int)uVar4 <= (int)param_3) {
      uVar4 = param_3;
    }
    malloc(uVar4);
    param_2 = extraout_EAX;
    if (extraout_EAX == (char *)0x0) {
      errno = 0xc;
      return (char *)0x0;
    }
  }
  else if ((int)param_3 < (int)uVar4) {
    errno = 0x22;
    return (char *)0x0;
  }
  uVar4 = 0xffffffff;
  pcVar6 = local_104;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  pcVar7 = param_2;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  return param_2;
}


/* ==== FUN_0040db90 @ 0040db90 ==== */

undefined4 __cdecl FUN_0040db90(uint param_1)

{
  char cVar1;
  UINT UVar2;
  
  if (param_1 == 0) {
    return 1;
  }
  cVar1 = (char)param_1;
  param_1 = (uint)CONCAT12(0x5c,CONCAT11(0x3a,cVar1 + '@'));
  UVar2 = GetDriveTypeA((LPCSTR)&param_1);
  if ((UVar2 != 0) && (UVar2 != 1)) {
    return 1;
  }
  return 0;
}


