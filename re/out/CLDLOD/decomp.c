/* ==== main @ 00401000 ==== */

int __cdecl main(int argc,char **argv,char **envp)

{
  void *extraout_EAX;
  int extraout_EAX_00;
  
  signal(2,FUN_0040108a);
  if (argc != 2) {
    fprintf(&DAT_0040c1a0,s_Version_6_3_usage__cldlod_cldfil_0040bb90);
    exit(-1);
  }
  fopen(argv[1],&DAT_0040bbc0);
  DAT_0040edb0 = extraout_EAX;
  if (extraout_EAX == (void *)0x0) {
    FUN_00402314(s_cannot_open_input_file__s_0040bbc4,argv[1]);
  }
  FUN_00401099();
  fclose(DAT_0040edb0);
  exit(0);
  return extraout_EAX_00;
}


/* ==== FUN_0040108a @ 0040108a ==== */

void FUN_0040108a(void)

{
  exit(1);
  return;
}


/* ==== FUN_00401099 @ 00401099 ==== */

void FUN_00401099(void)

{
  FUN_004012c1();
  if ((DAT_0040f1f0 != 0) && (DAT_0040f1e8 != 0)) {
    FUN_004014d4();
    FUN_004010ff();
    FUN_00401609();
  }
  FUN_00401792();
  if ((DAT_0040f1f0 != 0) && (DAT_0040f1e8 != 0)) {
    FUN_00401e6a();
  }
  FUN_004022b4((int *)&DAT_0040c180,s__END__01__X_0040bbe0,DAT_0040f19c,DAT_0040f134);
  return;
}


/* ==== FUN_004010ff @ 004010ff ==== */

void FUN_004010ff(void)

{
  int iVar1;
  uint uVar2;
  size_t sVar3;
  char *va0;
  char *local_3c;
  int local_34;
  int local_2c;
  int local_28 [2];
  int local_20;
  int local_18;
  int local_14;
  int local_10;
  int local_8;
  
  local_2c = 0;
  local_8 = -0x2c5;
  iVar1 = fseek(DAT_0040edb0,DAT_0040f1f0,0);
  if (iVar1 != 0) {
    FUN_00402314(s_cannot_seek_to_symbol_table_0040bbf0);
  }
  for (; local_2c < DAT_0040f1e8; local_2c = local_2c + 1) {
    uVar2 = FUN_00402204((char *)local_28,0x20,1,DAT_0040edb0);
    if (uVar2 != 1) {
      FUN_00402314(s_cannot_read_symbol_table_entry___0040bc0c,local_2c);
    }
    if (local_28[0] != 0) {
      FUN_0040223e((undefined1 *)local_28,4,2);
    }
    iVar1 = _strcmp((char *)local_28,&DAT_0040bc30);
    if ((((iVar1 == 0) && (local_18 == -1)) && (local_10 == 0)) && (local_14 == 0)) {
      local_8 = local_20;
      break;
    }
  }
  FUN_004022b4((int *)&DAT_0040c180,s__START_0040bc38);
  if ((local_8 < 0) || (DAT_0040f1a0 == 0)) {
    FUN_004022b4((int *)&DAT_0040c180,&DAT_0040bc50);
  }
  else {
    local_3c = DAT_0040f1ec;
    local_34 = 4;
    do {
      if (local_34 == local_8) break;
      sVar3 = _strlen(local_3c);
      local_34 = local_34 + 1 + sVar3;
      local_3c = local_3c + sVar3 + 1;
    } while (local_3c < DAT_0040f1ec + DAT_0040f1a0);
    va0 = _strchr(local_3c,0x3b);
    if (va0 == (char *)0x0) {
      FUN_004022b4((int *)&DAT_0040c180,&DAT_0040bc40,local_3c);
    }
    else {
      *va0 = '\0';
      FUN_004022b4((int *)&DAT_0040c180,&DAT_0040bc48,local_3c);
      *va0 = ';';
      FUN_004022b4((int *)&DAT_0040c180,&DAT_0040bc4c,va0);
    }
  }
  return;
}


/* ==== FUN_004012c1 @ 004012c1 ==== */

void FUN_004012c1(void)

{
  uint uVar1;
  
  uVar1 = FUN_00402204((char *)&DAT_0040f180,0x1c,1,DAT_0040edb0);
  if (uVar1 != 1) {
    FUN_00402314(s_cannot_read_file_header_0040bc54);
  }
  DAT_0040f104 = DAT_0040f184;
  DAT_0040f1e8 = DAT_0040f190;
  DAT_0040f1f0 = DAT_0040f18c;
  DAT_0040f15c = (uint)((DAT_0040f198 & 1) != 0);
  if (DAT_0040f180 == 0x2c5) {
    DAT_0040f160 = 6;
    DAT_0040f19c = 4;
  }
  else if (DAT_0040f180 == 0x2c6) {
    DAT_0040f19c = 8;
    DAT_0040f160 = 8;
  }
  else if (DAT_0040f180 == 0x2c7) {
    DAT_0040f19c = 4;
    DAT_0040f160 = 4;
  }
  else if (DAT_0040f180 == 0x2c8) {
    DAT_0040f19c = 6;
    DAT_0040f160 = 6;
  }
  else if (DAT_0040f180 == 0x2ca) {
    DAT_0040f160 = 6;
    DAT_0040f19c = 4;
  }
  else if (DAT_0040f180 == 0x2c9) {
    DAT_0040f19c = 4;
    DAT_0040f160 = 4;
  }
  else if (DAT_0040f180 == 0x2cb) {
    DAT_0040f160 = 4;
    DAT_0040f19c = 8;
  }
  else if (DAT_0040f180 == 0x2cc) {
    DAT_0040f160 = 4;
    DAT_0040f19c = 8;
  }
  else {
    FUN_00402314(s_Header_has_a_bad_magic_number_0040bc6c);
  }
  if (DAT_0040f194 != 0) {
    if (DAT_0040f15c == 0) {
      uVar1 = FUN_00402204(&DAT_0040f1c0,DAT_0040f194,1,DAT_0040edb0);
      if (uVar1 != 1) {
        FUN_00402314(s_cannot_read_linker_file_header_0040bcb0);
      }
    }
    else {
      uVar1 = FUN_00402204(&DAT_0040f120,DAT_0040f194,1,DAT_0040edb0);
      if (uVar1 != 1) {
        FUN_00402314(s_cannot_read_optional_file_header_0040bc8c);
      }
    }
  }
  DAT_0040f1f4 = DAT_0040f194 + 0x1c;
  return;
}


/* ==== FUN_004014d4 @ 004014d4 ==== */

void FUN_004014d4(void)

{
  int iVar1;
  uint uVar2;
  char *extraout_EAX;
  int offset;
  
  offset = DAT_0040f1f0 + DAT_0040f1e8 * 0x20;
  iVar1 = fseek(DAT_0040edb0,offset,0);
  if (iVar1 != 0) {
    FUN_00402314(s_cannot_seek_to_string_table_leng_0040bcd0);
  }
  uVar2 = FUN_00402204((char *)&DAT_0040f1a0,4,1,DAT_0040edb0);
  if ((uVar2 != 1) && ((DAT_0040edb0[3] & 0x10U) == 0)) {
    FUN_00402314(s_cannot_read_string_table_length_0040bcf4);
  }
  if ((DAT_0040edb0[3] & 0x10U) == 0) {
    if (DAT_0040f1a0 != 0) {
      DAT_0040f1a0 = DAT_0040f1a0 - 4;
      malloc(DAT_0040f1a0);
      DAT_0040f1ec = extraout_EAX;
      if (extraout_EAX == (char *)0x0) {
        FUN_00402314(s_cannot_allocate_string_table_0040bd14);
      }
      iVar1 = fseek(DAT_0040edb0,offset + 4,0);
      if (iVar1 != 0) {
        FUN_00402314(s_cannot_seek_to_string_table_0040bd34);
      }
      uVar2 = FUN_00402b70(DAT_0040f1ec,DAT_0040f1a0,1,DAT_0040edb0);
      if (uVar2 != 1) {
        FUN_00402314(s_cannot_read_string_table_0040bd50);
      }
    }
  }
  else {
    DAT_0040f1a0 = 0;
  }
  return;
}


/* ==== FUN_00401609 @ 00401609 ==== */

void FUN_00401609(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int *extraout_EAX;
  int *local_54;
  char local_50 [32];
  int local_30;
  int local_2c;
  int local_28;
  int local_24 [2];
  int local_1c;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar3 = fseek(DAT_0040edb0,DAT_0040f1f0,0);
  if (iVar3 != 0) {
    FUN_00402314(s_cannot_seek_to_symbol_table_0040bd6c);
  }
  local_28 = 0;
  while (local_28 < DAT_0040f1e8) {
    uVar4 = FUN_00402204((char *)local_24,0x20,1,DAT_0040edb0);
    if (uVar4 != 1) {
      FUN_00402314(s_cannot_read_symbol_table_entry___0040bd88,local_28);
    }
    if (local_24[0] != 0) {
      FUN_0040223e((undefined1 *)local_24,4,2);
    }
    iVar3 = _strcmp((char *)local_24,&DAT_0040bdac);
    piVar1 = DAT_0040edb8;
    piVar2 = local_54;
    if ((((iVar3 == 0) && (local_14 != -1)) && (local_c == 0)) && (local_10 == 0)) {
      malloc(0xc);
      if (extraout_EAX == (int *)0x0) {
        FUN_00402314(s_cannot_allocate_comment_record_0040bdb4);
      }
      *extraout_EAX = local_14;
      extraout_EAX[1] = local_1c;
      extraout_EAX[2] = 0;
      piVar1 = extraout_EAX;
      piVar2 = extraout_EAX;
      if (DAT_0040edb8 != (int *)0x0) {
        local_54[2] = (int)extraout_EAX;
        piVar1 = DAT_0040edb8;
        piVar2 = extraout_EAX;
      }
    }
    local_54 = piVar2;
    DAT_0040edb8 = piVar1;
    local_30 = local_28;
    for (local_2c = 0; local_28 = local_28 + 1, local_2c < local_8; local_2c = local_2c + 1) {
      uVar4 = FUN_00402204(local_50,0x20,1,DAT_0040edb0);
      if (uVar4 != 1) {
        FUN_00402314(s_cannot_read_auxiliary_entry__d_f_0040bdd4,local_2c,local_30);
      }
    }
  }
  DAT_0040edbc = DAT_0040edb8;
  return;
}


/* ==== FUN_00401792 @ 00401792 ==== */

void FUN_00401792(void)

{
  int iVar1;
  uint uVar2;
  int local_3c [13];
  int local_8;
  
  for (local_8 = 0; local_8 < DAT_0040f104; local_8 = local_8 + 1) {
    iVar1 = fseek(DAT_0040edb0,DAT_0040f1f4,0);
    if (iVar1 != 0) {
      FUN_00402314(s_cannot_seek_to_section_headers_0040be08);
    }
    uVar2 = FUN_00402204((char *)local_3c,0x34,1,DAT_0040edb0);
    if (uVar2 != 1) {
      FUN_00402314(s_cannot_read_section_headers_0040be28);
    }
    if (local_3c[0] != 0) {
      FUN_0040223e((undefined1 *)local_3c,4,2);
    }
    DAT_0040f1f4 = DAT_0040f1f4 + 0x34;
    FUN_00401853(local_8 + 1);
    FUN_00401948(local_3c);
  }
  return;
}


/* ==== FUN_00401853 @ 00401853 ==== */

void __cdecl FUN_00401853(int param_1)

{
  while ((DAT_0040edbc != (int *)0x0 && (*DAT_0040edbc <= param_1))) {
    if (0 < *DAT_0040edbc) {
      FUN_004022b4((int *)&DAT_0040c180,s__COMMENT_0040be44);
      if (((uint)DAT_0040edbc[1] < 4) || (DAT_0040f1a0 < DAT_0040edbc[1])) {
        FUN_00402314(s_invalid_string_table_offset_for_c_0040be50);
      }
      FUN_004022b4((int *)&DAT_0040c180,&DAT_0040be78,DAT_0040f1ec + -4 + DAT_0040edbc[1]);
      DAT_0040edbc = (int *)DAT_0040edbc[2];
    }
  }
  return;
}


/* ==== FUN_004018f6 @ 004018f6 ==== */

int * __cdecl FUN_004018f6(int *param_1)

{
  int *local_8;
  
  if (*param_1 == 0) {
    if (((uint)param_1[1] < 4) || (DAT_0040f1a0 < param_1[1])) {
      FUN_00402314(s_invalid_string_table_offset_for_s_0040be7c);
    }
    local_8 = (int *)(DAT_0040f1ec + -4 + param_1[1]);
  }
  else {
    local_8 = param_1;
  }
  return local_8;
}


/* ==== FUN_00401948 @ 00401948 ==== */

void __cdecl FUN_00401948(int *param_1)

{
  int va2;
  undefined4 va1;
  int *va0;
  char *extraout_EAX;
  int iVar1;
  uint uVar2;
  int local_24;
  char *local_20;
  char *local_14;
  uint local_10;
  char local_c [8];
  
  if (param_1[7] == 0) {
    return;
  }
  if (param_1[6] == 0) {
    return;
  }
  local_24 = param_1[3];
  va2 = param_1[2];
  va0 = FUN_004018f6(param_1);
  if (local_24 < 0x11e) {
    if (local_24 == 0x11d) {
      local_20 = &DAT_0040bf18;
      goto LAB_00401b6a;
    }
    switch(local_24) {
    case 0:
      local_20 = &DAT_0040beb0;
      break;
    case 1:
      local_20 = &DAT_0040bee0;
      break;
    case 2:
      local_20 = &DAT_0040bec8;
      break;
    case 3:
      local_20 = &DAT_0040bef8;
      break;
    default:
      goto switchD_004019b2_caseD_4;
    case 5:
      local_20 = &DAT_0040befc;
      break;
    case 6:
      local_20 = &DAT_0040bf00;
      break;
    case 7:
      local_20 = &DAT_0040bf04;
      break;
    case 8:
      local_20 = &DAT_0040bf08;
      break;
    case 9:
      local_20 = &DAT_0040bf0c;
      break;
    case 10:
      local_20 = &DAT_0040bf10;
      break;
    case 0xb:
      local_20 = &DAT_0040beb4;
      break;
    case 0xc:
      local_20 = &DAT_0040beb8;
      break;
    case 0xd:
      local_20 = &DAT_0040bebc;
      break;
    case 0xe:
      local_20 = &DAT_0040bec0;
      break;
    case 0xf:
      local_20 = &DAT_0040bec4;
      break;
    case 0x10:
      local_20 = &DAT_0040bee4;
      break;
    case 0x11:
      local_20 = &DAT_0040bee8;
      break;
    case 0x12:
      local_20 = &DAT_0040beec;
      break;
    case 0x13:
      local_20 = &DAT_0040bef0;
      break;
    case 0x14:
      local_20 = &DAT_0040bef4;
      break;
    case 0x15:
      local_20 = &DAT_0040becc;
      break;
    case 0x16:
      local_20 = &DAT_0040bed0;
      break;
    case 0x17:
      local_20 = &DAT_0040bed4;
      break;
    case 0x18:
      local_20 = &DAT_0040bed8;
      break;
    case 0x19:
      local_20 = &DAT_0040bedc;
      break;
    case 0x1c:
      local_20 = &DAT_0040bf14;
    }
  }
  else {
switchD_004019b2_caseD_4:
    if ((((DAT_0040f180 == 0x2ca) && (local_24 == 0x1e)) && ((param_1[0xc] & 0x800U) != 0)) &&
       ((param_1[0xc] & 0x4000U) == 0)) {
      local_24 = 0x1d;
    }
    if ((local_24 < 0x1d) || (0x11c < local_24)) {
      local_20 = s_<ERROR>_0040bf20;
    }
    else {
      sprintf(local_c,&DAT_0040bf1c,local_24 + -0x1d);
      local_20 = local_c;
    }
  }
LAB_00401b6a:
  malloc(param_1[6] << 2);
  if (extraout_EAX == (char *)0x0) {
    FUN_00402314(s_cannot_allocate_raw_data_for_sec_0040bf28,va0);
  }
  iVar1 = fseek(DAT_0040edb0,param_1[7],0);
  if (iVar1 != 0) {
    FUN_00402314(s_cannot_seek_to_raw_data_in_secti_0040bf50,va0);
  }
  uVar2 = FUN_00402204(extraout_EAX,param_1[6],4,DAT_0040edb0);
  if (uVar2 != 4) {
    FUN_00402314(s_cannot_read_raw_data_in_section___0040bf78,va0);
  }
  if ((param_1[0xc] & 0x400U) == 0) {
    FUN_004022b4((int *)&DAT_0040c180,s__DATA__s__01__X_0040c008,local_20,DAT_0040f19c,va2);
    local_10 = 0;
    local_14 = extraout_EAX;
    while ((int)local_10 < param_1[6]) {
      if (*local_20 == 'L') {
        FUN_004022b4((int *)&DAT_0040c180,s__01__lX__01__lX_0040c01c,DAT_0040f160,
                     *(undefined4 *)(local_14 + 4),DAT_0040f160,*(undefined4 *)local_14);
        local_14 = local_14 + 8;
        local_10 = local_10 + 2;
      }
      else {
        va1 = *(undefined4 *)local_14;
        local_14 = local_14 + 4;
        FUN_004022b4((int *)&DAT_0040c180,s__01__lX_0040c030,DAT_0040f160,va1);
        local_10 = local_10 + 1;
      }
      uVar2 = (int)local_10 >> 0x1f;
      if ((((local_10 ^ uVar2) - uVar2 & 7 ^ uVar2) == uVar2) && ((int)local_10 < param_1[6])) {
        FUN_004022b4((int *)&DAT_0040c180,&DAT_0040c03c);
      }
    }
    FUN_004022b4((int *)&DAT_0040c180,&DAT_0040c040);
  }
  else if (*local_20 == 'L') {
    FUN_004022b4((int *)&DAT_0040c180,s__BLOCKDATA_Y__01__X__01__X__01___0040bf9c,DAT_0040f19c,va2,
                 DAT_0040f19c,param_1[4],DAT_0040f160,*(undefined4 *)extraout_EAX);
    FUN_004022b4((int *)&DAT_0040c180,s__BLOCKDATA_X__01__X__01__X__01___0040bfc0,DAT_0040f19c,va2,
                 DAT_0040f19c,param_1[4],DAT_0040f160,*(undefined4 *)(extraout_EAX + 4));
  }
  else {
    FUN_004022b4((int *)&DAT_0040c180,s__BLOCKDATA__s__01__X__01__X__01__0040bfe4,local_20,
                 DAT_0040f19c,va2,DAT_0040f19c,param_1[4],DAT_0040f160,*(undefined4 *)extraout_EAX);
  }
  return;
}


/* ==== FUN_00401e6a @ 00401e6a ==== */

void FUN_00401e6a(void)

{
  int iVar1;
  uint uVar2;
  char local_50 [32];
  int local_30;
  int local_2c;
  int local_28;
  int local_24 [7];
  int local_8;
  
  iVar1 = fseek(DAT_0040edb0,DAT_0040f1f0,0);
  if (iVar1 != 0) {
    FUN_00402314(s_cannot_seek_to_symbol_table_0040c044);
  }
  local_28 = 0;
  while (local_28 < DAT_0040f1e8) {
    uVar2 = FUN_00402204((char *)local_24,0x20,1,DAT_0040edb0);
    if (uVar2 != 1) {
      FUN_00402314(s_cannot_read_symbol_table_entry___0040c060,local_28);
    }
    FUN_00401f54(local_24);
    local_30 = local_28;
    for (local_2c = 0; local_28 = local_28 + 1, local_2c < local_8; local_2c = local_2c + 1) {
      uVar2 = FUN_00402204(local_50,0x20,1,DAT_0040edb0);
      if (uVar2 != 1) {
        FUN_00402314(s_cannot_read_auxiliary_entry__d_f_0040c084,local_2c,local_30);
      }
    }
  }
  return;
}


/* ==== FUN_00401f54 @ 00401f54 ==== */

void __cdecl FUN_00401f54(int *param_1)

{
  uint uVar1;
  int iVar2;
  int *local_10;
  char local_c;
  
  local_c = 'I';
  if (*param_1 == 0) {
    if (((uint)param_1[1] < 4) || (DAT_0040f1a0 < param_1[1])) {
      FUN_00402314(s_invalid_string_table_offset_for_s_0040c0b8,param_1 + DAT_0040f1f0 * -8);
    }
    local_10 = (int *)(DAT_0040f1ec + -4 + param_1[1]);
  }
  else {
    FUN_0040223e((undefined1 *)param_1,4,2);
    local_10 = param_1;
  }
  uVar1 = DAT_0040b034;
  if ((char)*local_10 != '.') {
    if ((param_1[5] & 0x30U) != 0x20) {
      switch(param_1[6]) {
      default:
        if ((5 < (param_1[5] & 0x1000fU)) && ((param_1[5] & 0x1000fU) < 8)) {
          local_c = 'F';
        }
        break;
      case -1:
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 100:
      case 0x65:
      case 0x66:
      case 0x67:
      case 0x68:
      case 0x69:
      case 0x6a:
      }
    }
    iVar2 = _strcmp((char *)local_10,s_etext_0040c0f4);
    if (((((iVar2 != 0) || (param_1[4] != -1)) || (param_1[5] != 0)) ||
        (uVar1 = DAT_0040b034, param_1[6] != 2)) &&
       (((iVar2 = _strcmp((char *)local_10,&DAT_0040c0fc), uVar1 = DAT_0040b034, iVar2 != 0 ||
         (param_1[4] != -1)) || ((param_1[5] != 0 || (param_1[6] != 2)))))) {
      if ((param_1[4] < 1) && ((param_1[5] & 0x30U) != 0x10)) {
        DAT_0040b034 = 4;
      }
      else {
        DAT_0040b034 = param_1[3];
      }
      if (DAT_0040b034 < 0x11d) {
        if (uVar1 != DAT_0040b034) {
          FUN_004022b4((int *)&DAT_0040c180,s__SYMBOL__s_0040c100,(&PTR_DAT_0040b038)[DAT_0040b034])
          ;
        }
        FUN_004022b4((int *)&DAT_0040c180,s___19s__c_0040c10c,local_10,(int)local_c);
        if (local_c == 'F') {
          FUN_004022b4((int *)&DAT_0040c180,s____6E_0040c118,param_1[2],param_1[3]);
          uVar1 = DAT_0040b034;
        }
        else {
          FUN_004022b4((int *)&DAT_0040c180,s__01__lX_0040c120,DAT_0040f160,param_1[2]);
          uVar1 = DAT_0040b034;
        }
      }
    }
  }
  DAT_0040b034 = uVar1;
  return;
}


/* ==== FUN_00402204 @ 00402204 ==== */

uint __cdecl FUN_00402204(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  uVar1 = FUN_00402b70(param_1,param_2,param_3,param_4);
  FUN_0040223e(param_1,param_2,param_3);
  return uVar1;
}


/* ==== FUN_0040223e @ 0040223e ==== */

void __cdecl FUN_0040223e(undefined1 *param_1,int param_2,int param_3)

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


/* ==== FUN_004022b4 @ 004022b4 ==== */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl FUN_004022b4(int *param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00402e40(param_1,param_2,(undefined4 *)&stack0x0000000c);
  if (iVar1 < 0) {
    FUN_00402314(s_cannot_write_to_output_file_0040c12c);
  }
  return;
}


/* ==== FUN_00402314 @ 00402314 ==== */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void __cdecl FUN_00402314(char *param_1)

{
  int iVar1;
  
  iVar1 = errno;
  fprintf(&DAT_0040c1a0,s_cldlod__0040c148);
  FUN_00402e40((int *)&DAT_0040c1a0,param_1,(undefined4 *)&stack0x00000008);
  fprintf(&DAT_0040c1a0,&DAT_0040c154);
  if (iVar1 != 0) {
    errno = iVar1;
    FUN_00402e80(s_cldlod_0040c158);
  }
  exit(1);
  return;
}


/* ==== fclose @ 004023b0 ==== */

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


/* ==== _fsopen @ 00402430 ==== */

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


/* ==== fopen @ 00402460 ==== */

void __cdecl fopen(char *name,char *mode)

{
  _fsopen(name,mode,0x40);
  return;
}


/* ==== _cinit @ 00402480 ==== */

void _cinit(void)

{
  if (_FPinit != (undefined *)0x0) {
    (*(code *)_FPinit)();
  }
  _initterm(&DAT_0040b008,&DAT_0040b010);
  _initterm(&DAT_0040b000,&DAT_0040b004);
  return;
}


/* ==== exit @ 004024b0 ==== */

void __cdecl exit(int status)

{
  doexit(status,0,0);
  return;
}


/* ==== __exit @ 004024d0 ==== */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __exit(int _Code)

{
  doexit(_Code,1,0);
  return;
}


/* ==== doexit @ 004024f0 ==== */

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
    _initterm(&DAT_0040b014,&DAT_0040b01c);
  }
  _initterm(&DAT_0040b020,&DAT_0040b024);
  if (retcaller == 0) {
    _C_Exit_Done = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(code);
  }
  return;
}


/* ==== _initterm @ 004025a0 ==== */

void __cdecl _initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != (code *)0x0) {
      (**(code **)begin)();
    }
  }
  return;
}


/* ==== fprintf @ 004025c0 ==== */

int __cdecl fprintf(void *stream,char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(stream);
  iVar1 = _output(stream,fmt,&stack0x0000000c);
  _ftbuf(flag,stream);
  return iVar1;
}


/* ==== signal @ 004026e0 ==== */

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
    if ((sig != 2) && (sig != 0x15)) goto LAB_00402794;
  }
  if (DAT_0040ee20 == 0) {
    BVar3 = SetConsoleCtrlHandler((PHANDLER_ROUTINE)&LAB_00402850,1);
    if (BVar3 != 1) {
      _doserrno = GetLastError();
      errno = 0x16;
      return;
    }
    DAT_0040ee20 = 1;
  }
LAB_00402794:
  switch(sig) {
  case 2:
    DAT_0040ee10 = func;
    return;
  default:
    return;
  case 0xf:
    DAT_0040ee1c = func;
    return;
  case 0x15:
    DAT_0040ee14 = func;
    return;
  case 0x16:
    DAT_0040ee18 = func;
    return;
  }
}


/* ==== siglookup @ 004028a0 ==== */

void __cdecl siglookup(int sig)

{
  int *piVar1;
  undefined4 *puVar2;
  
  if (DAT_0040c414 != sig) {
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


/* ==== _strchr @ 00402900 ==== */

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


/* ==== _strlen @ 004029c0 ==== */

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
    if (((uint)puVar2 & 3) == 0) goto LAB_004029e0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00402a13:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_004029e0:
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
  goto LAB_00402a13;
}


/* ==== _strcmp @ 00402a40 ==== */

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
      if (bVar4 != *_Str2) goto LAB_00402a84;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_00402a50;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_00402a84;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_00402a84;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_00402a50:
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
LAB_00402a84:
  return (uint)bVar5 * -2 + 1;
}


/* ==== fseek @ 00402ad0 ==== */

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


/* ==== FUN_00402b70 @ 00402b70 ==== */

uint __cdecl FUN_00402b70(char *param_1,uint param_2,uint param_3,int *param_4)

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


/* ==== malloc @ 00402cb0 ==== */

void __cdecl malloc(uint size)

{
  _nh_malloc(size,_newmode);
  return;
}


/* ==== _nh_malloc @ 00402cd0 ==== */

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


/* ==== _heap_alloc @ 00402d20 ==== */

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


/* ==== sprintf @ 00402d60 ==== */

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


/* ==== __fpmath @ 00402dd0 ==== */

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


/* ==== _cfltcvt_init @ 00402e00 ==== */

void _cfltcvt_init(void)

{
  PTR__fptrap_0040e4cc = _cropzeros;
  _cfltcvt_tab = _cfltcvt;
  PTR__fptrap_0040e4d0 = _fassign;
  PTR__fptrap_0040e4d4 = _forcdecpt;
  PTR__fptrap_0040e4d8 = _positive;
  PTR__fptrap_0040e4dc = _cfltcvt;
  return;
}


/* ==== FUN_00402e40 @ 00402e40 ==== */

int __cdecl FUN_00402e40(int *param_1,char *param_2,undefined4 *param_3)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(param_1);
  iVar1 = _output(param_1,param_2,param_3);
  _ftbuf(flag,param_1);
  return iVar1;
}


/* ==== FUN_00402e80 @ 00402e80 ==== */

void __cdecl FUN_00402e80(char *param_1)

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
    _write(2,&DAT_0040a004,2);
  }
  if ((errno < 0) || (iVar2 = errno, DAT_0040e590 <= errno)) {
    iVar2 = DAT_0040e590;
  }
  uVar3 = 0xffffffff;
  pcVar4 = (&PTR_s_No_error_0040e4e0)[iVar2];
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  _write(2,(&PTR_s_No_error_0040e4e0)[iVar2],~uVar3 - 1);
  _write(2,&DAT_0040a000,1);
  return;
}


/* ==== entry @ 00402f00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  undefined uVar1;
  DWORD DVar2;
  int iVar3;
  int extraout_EAX;
  undefined3 extraout_var;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0040a008;
  puStack_10 = &LAB_00406518;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  DVar2 = GetVersion();
  _DAT_0040edd8 = DVar2 >> 8 & 0xff;
  _DAT_0040edd4 = DVar2 & 0xff;
  _DAT_0040edd0 = _DAT_0040edd4 * 0x100 + _DAT_0040edd8;
  _DAT_0040edcc = DVar2 >> 0x10;
  iVar3 = _heap_init();
  if (iVar3 == 0) {
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
  uVar1 = main(__argc,__argv,_environ);
  exit(CONCAT31(extraout_var,uVar1));
  *unaff_FS_OFFSET = local_14;
  return;
}


/* ==== _amsg_exit @ 00403020 ==== */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _amsg_exit(int rterrnum)

{
  if (DAT_0040ee34 != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
  (*(code *)PTR___exit_0040c3f4)(0xff);
  return;
}


/* ==== free @ 00403050 ==== */

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


/* ==== _close @ 004030a0 ==== */

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
      if (lVar2 == lVar1) goto LAB_00403127;
    }
    hObject = (HANDLE)_get_osfhandle(fh);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      oserrno = GetLastError();
      goto LAB_00403129;
    }
  }
LAB_00403127:
  oserrno = 0;
LAB_00403129:
  _free_osfhnd(fh);
  *(undefined1 *)((&__pioinfo)[fh >> 5] + 4 + iVar4) = 0;
  if (oserrno == 0) {
    return 0;
  }
  _dosmaperr(oserrno);
  return -1;
}


/* ==== _freebuf @ 00403180 ==== */

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


/* ==== _flush @ 00403210 ==== */

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


/* ==== _openfile @ 00403310 ==== */

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
      uVar7 = DAT_0040f094 | 1;
      goto LAB_0040334d;
    }
    if (cVar1 != 'w') {
      return;
    }
    oflag = 0x301;
  }
  uVar7 = DAT_0040f094 | 2;
LAB_0040334d:
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
      goto LAB_004033fe;
    case 'D':
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_004033fe;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x10;
        goto LAB_004033fe;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x20;
        goto LAB_004033fe;
      }
      break;
    case 'T':
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_004033fe;
      }
      break;
    case 'b':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x8000;
        goto LAB_004033fe;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_004033fe;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_004033fe;
      }
      break;
    case 't':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x4000;
        goto LAB_004033fe;
      }
    }
    bVar2 = false;
LAB_004033fe:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}


/* ==== _getstream @ 004034e0 ==== */

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


/* ==== _stbuf @ 00403570 ==== */

int __cdecl _stbuf(void *stream)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = _isatty(*(int *)((int)stream + 0x10));
  if (iVar2 != 0) {
    if (stream == &DAT_0040c180) {
      iVar2 = 0;
    }
    else {
      if (stream != &DAT_0040c1a0) {
        return 0;
      }
      iVar2 = 1;
    }
    _cflush = _cflush + 1;
    if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
      if ((&DAT_0040ee38)[iVar2] == 0) {
        malloc(0x1000);
        (&DAT_0040ee38)[iVar2] = extraout_EAX;
        if (extraout_EAX == 0) {
          return 0;
        }
      }
      uVar1 = (&DAT_0040ee38)[iVar2];
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


/* ==== _ftbuf @ 00403610 ==== */

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


/* ==== _output @ 00403670 ==== */

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
      uVar2 = *(byte *)(cVar7 + 0x409ff8) & 0xf;
    }
    local_220 = (int)(char)(&DAT_0040a018)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_004036ed_caseD_0:
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
          goto switchD_004036ed_caseD_0;
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
          (*(code *)PTR__fptrap_0040e4d4)(&local_204);
        }
        if ((cVar7 == 'g') && ((unaff_EBX & 0x80) == 0)) {
          (*(code *)PTR__fptrap_0040e4cc)(local_200);
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
            puVar5 = (ushort *)PTR_DAT_0040c3fc;
            local_248 = (ushort *)PTR_DAT_0040c3fc;
          }
          for (; (iVar10 != 0 && (iVar10 = iVar10 + -1, (char)*puVar5 != '\0'));
              puVar5 = (ushort *)((int)puVar5 + 1)) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_0040c400;
          }
          local_230 = 1;
          for (puVar5 = local_248; (iVar10 != 0 && (iVar10 = iVar10 + -1, *puVar5 != 0));
              puVar5 = puVar5 + 1) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_00403901_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg(&argptr);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_0040c3fc;
          pcVar9 = PTR_DAT_0040c3fc;
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
        goto LAB_00403c37;
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
        goto LAB_00403c37;
      case 'p':
        local_244 = 8;
switchD_00403901_caseD_58:
        local_224 = 7;
LAB_00403bf2:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_00403c37;
      case 'u':
        local_22c = 10;
LAB_00403c37:
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
        goto LAB_00403bf2;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_00403dcf;
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
LAB_00403dcf:
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


/* ==== write_char @ 00404000 ==== */

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


/* ==== write_multi_char @ 00404050 ==== */

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


/* ==== write_string @ 00404090 ==== */

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


/* ==== get_int_arg @ 004040d0 ==== */

int __cdecl get_int_arg(void *pargptr)

{
  int *piVar1;
  
  piVar1 = *(int **)pargptr;
  *(int **)pargptr = piVar1 + 1;
  return *piVar1;
}


/* ==== get_int64_arg @ 004040f0 ==== */

longlong __cdecl get_int64_arg(void *pargptr)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)pargptr;
  *(longlong **)pargptr = plVar1 + 1;
  return *plVar1;
}


/* ==== get_short_arg @ 00404110 ==== */

short __cdecl get_short_arg(void *pargptr)

{
  short *psVar1;
  
  psVar1 = *(short **)pargptr;
  *(short **)pargptr = psVar1 + 2;
  return *psVar1;
}


/* ==== _ioinit @ 00404130 ==== */

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
      piVar6 = &DAT_0040f204;
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
        goto LAB_0040430b;
      }
      *puVar2 = hFile;
      if ((DVar3 & 0xff) == 2) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_0040430b;
      }
      if ((DVar3 & 0xff) == 3) {
        bVar1 = *(byte *)(puVar2 + 1) | 8;
        goto LAB_0040430b;
      }
    }
    else {
      bVar1 = *(byte *)(puVar2 + 1) | 0x80;
LAB_0040430b:
      *(byte *)(puVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(_nhandle);
      return;
    }
  } while( true );
}


/* ==== calloc @ 00404330 ==== */

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
LAB_00404390:
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
          goto LAB_00404390;
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


/* ==== _XcptFilter @ 00404440 ==== */

int __cdecl _XcptFilter(ulong xcptnum,void *pxcptptrs)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  undefined4 *puVar6;
  int iVar7;
  
  piVar4 = FUN_00404580(xcptnum);
  uVar3 = DAT_0040ee40;
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    LVar5 = UnhandledExceptionFilter(pxcptptrs);
    return LVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 != (code *)0x1) {
    DAT_0040ee40 = pxcptptrs;
    if (piVar4[1] == 8) {
      if (DAT_0040c488 < DAT_0040c48c + DAT_0040c488) {
        iVar7 = (DAT_0040c48c + DAT_0040c488) - DAT_0040c488;
        puVar6 = (undefined4 *)(DAT_0040c488 * 0xc + 0x40c418);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar2 = DAT_0040c494;
      iVar7 = *piVar4;
      if (iVar7 == -0x3fffff72) {
        DAT_0040c494 = 0x83;
      }
      else if (iVar7 == -0x3fffff70) {
        DAT_0040c494 = 0x81;
      }
      else if (iVar7 == -0x3fffff6f) {
        DAT_0040c494 = 0x84;
      }
      else if (iVar7 == -0x3fffff6d) {
        DAT_0040c494 = 0x85;
      }
      else if (iVar7 == -0x3fffff73) {
        DAT_0040c494 = 0x82;
      }
      else if (iVar7 == -0x3fffff71) {
        DAT_0040c494 = 0x86;
      }
      else if (iVar7 == -0x3fffff6e) {
        DAT_0040c494 = 0x8a;
      }
      (*pcVar1)(8,DAT_0040c494);
      DAT_0040c494 = uVar2;
      DAT_0040ee40 = (void *)uVar3;
      return -1;
    }
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    DAT_0040ee40 = (void *)uVar3;
    return -1;
  }
  return -1;
}


/* ==== FUN_00404580 @ 00404580 ==== */

int * __cdecl FUN_00404580(int param_1)

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


/* ==== _lseek @ 004045d0 ==== */

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


/* ==== ftell @ 00404690 ==== */

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
  if ((*(byte *)((int)stream + 0xc) & 1) == 0) goto LAB_00404805;
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
LAB_004047fc:
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
      if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 4) != 0) goto LAB_004047fc;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_00404805:
  return local_4 + local_8;
}


/* ==== _filbuf @ 00404840 ==== */

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


/* ==== _read @ 00404930 ==== */

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
                  goto LAB_00404b18;
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
                      goto LAB_00404b18;
                    }
                    _lseek(fh,-1,1);
                    if ((char)cnt != '\n') goto LAB_00404b15;
                  }
                  else {
                    if ((char)cnt == '\n') {
                      *pcVar8 = '\n';
                      goto LAB_00404b18;
                    }
                    *pcVar8 = '\r';
                    pcVar8 = pcVar8 + 1;
                    *(char *)(iVar6 + 5 + *local_8) = (char)cnt;
                  }
                }
                else {
LAB_00404b15:
                  *pcVar8 = '\r';
LAB_00404b18:
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


/* ==== _callnewh @ 00404b90 ==== */

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


/* ==== _heap_init @ 00404bb0 ==== */

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


/* ==== __sbh_new_region @ 00404bf0 ==== */

void __sbh_new_region(void)

{
  bool bVar1;
  undefined4 *lpAddress;
  LPVOID pvVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **lpMem;
  undefined4 *puVar5;
  
  if (DAT_0040c4b0 == -1) {
    lpMem = &PTR_LOOP_0040c4a0;
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
      if (lpMem == &PTR_LOOP_0040c4a0) {
        if (PTR_LOOP_0040c4a0 == (undefined *)0x0) {
          PTR_LOOP_0040c4a0 = (undefined *)&PTR_LOOP_0040c4a0;
        }
        if (PTR_LOOP_0040c4a4 == (undefined *)0x0) {
          PTR_LOOP_0040c4a4 = (undefined *)&PTR_LOOP_0040c4a0;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_0040c4a0;
        lpMem[1] = PTR_LOOP_0040c4a4;
        PTR_LOOP_0040c4a4 = (undefined *)lpMem;
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
  if (lpMem != &PTR_LOOP_0040c4a0) {
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== __sbh_release_region @ 00404d60 ==== */

void __cdecl __sbh_release_region(void *preg)

{
  VirtualFree(*(LPVOID *)((int)preg + 0x10),0,0x8000);
  if (PTR_LOOP_0040e4c0 == preg) {
    PTR_LOOP_0040e4c0 = *(undefined **)((int)preg + 4);
  }
  if (preg != &PTR_LOOP_0040c4a0) {
    **(undefined4 **)((int)preg + 4) = *(undefined4 *)preg;
    *(undefined4 *)(*(int *)preg + 4) = *(undefined4 *)((int)preg + 4);
    HeapFree(_crtheap,0,preg);
    return;
  }
  DAT_0040c4b0 = 0xffffffff;
  return;
}


/* ==== __sbh_decommit_pages @ 00404dc0 ==== */

void __cdecl __sbh_decommit_pages(int count)

{
  BOOL BVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *preg;
  undefined *puVar5;
  
  preg = PTR_LOOP_0040c4a4;
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
            DAT_0040ee4c = DAT_0040ee4c + -1;
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
    if ((puVar5 == PTR_LOOP_0040c4a4) || (preg = puVar5, count < 1)) {
      return;
    }
  } while( true );
}


/* ==== __sbh_find_block @ 00404e90 ==== */

void __cdecl __sbh_find_block(void *pblock,void *ppreg,void *pppage)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_0040c4a0;
  while ((pblock <= ppuVar1[4] || (ppuVar1[5] <= pblock))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_0040c4a0) {
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


/* ==== __sbh_free_block @ 00404ef0 ==== */

void __cdecl __sbh_free_block(void *preg,void *ppage,void *pmap)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (int)ppage - *(int *)((int)preg + 0x10) >> 0xc;
  piVar1 = (int *)((int)preg + iVar2 * 8 + 0x18);
  *piVar1 = *(int *)((int)preg + iVar2 * 8 + 0x18) + (uint)*(byte *)pmap;
  *(undefined1 *)pmap = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_0040ee4c = DAT_0040ee4c + 1, DAT_0040ee4c == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}


/* ==== __sbh_alloc_block @ 00404f50 ==== */

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
  
  piVar11 = (int *)PTR_LOOP_0040e4c0;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      pvVar8 = (void *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX != 0) {
            PTR_LOOP_0040e4c0 = (undefined *)piVar11;
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
            PTR_LOOP_0040e4c0 = (undefined *)piVar11;
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
  } while (piVar11 != (int *)PTR_LOOP_0040e4c0);
  ppuVar7 = &PTR_LOOP_0040c4a0;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_0040c4a0) {
      __sbh_new_region();
      if (extraout_EAX_01 == (undefined *)0x0) {
        return;
      }
      piVar11 = *(int **)(extraout_EAX_01 + 0x10);
      *(char *)(piVar11 + 2) = (char)para_req;
      PTR_LOOP_0040e4c0 = extraout_EAX_01;
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
  PTR_LOOP_0040e4c0 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)para_req;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -para_req;
  piVar11[1] = piVar11[1] - para_req;
  *piVar11 = (int)piVar11 + para_req + 8;
  return;
}


/* ==== __sbh_alloc_block_from_page @ 00405190 ==== */

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
            goto LAB_004052df;
          }
          *(byte **)ppage = pbVar6 + para_req;
          *(uint *)((int)ppage + 4) = uVar5 - para_req;
          goto LAB_004052e6;
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
LAB_004052df:
            *(undefined4 *)((int)ppage + 4) = 0;
          }
LAB_004052e6:
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


/* ==== _flsbuf @ 00405310 ==== */

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
LAB_00405430:
    *(uint *)((int)stream + 0xc) = uVar4 | 0x20;
    return -1;
  }
  uVar3 = 0;
  if ((uVar4 & 1) != 0) {
    *(undefined4 *)((int)stream + 4) = 0;
    if ((uVar4 & 0x10) == 0) goto LAB_00405430;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(uint *)((int)stream + 0xc) = uVar4 & 0xfffffffe;
  }
  uVar4 = *(uint *)((int)stream + 0xc);
  *(undefined4 *)((int)stream + 4) = 0;
  *(uint *)((int)stream + 0xc) = uVar4 & 0xffffffef | 2;
  if ((uVar4 & 0x10c) == 0) {
    if ((stream == &DAT_0040c180) || (stream == &DAT_0040c1a0)) {
      iVar1 = _isatty(fh);
      if (iVar1 != 0) goto LAB_00405383;
    }
    _getbuf(stream_00);
  }
LAB_00405383:
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


/* ==== __setdefaultprecision @ 00405440 ==== */

/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 1998 Release */

void __setdefaultprecision(void)

{
  FUN_00407140((void *)0x10000,0x30000);
  return;
}


/* ==== _ms_p5_test_fdiv @ 00405460 ==== */

/* WARNING: Removing unreachable block (ram,0x004054a1) */

int _ms_p5_test_fdiv(void)

{
  return 0;
}


/* ==== _ms_p5_mp_test_fdiv @ 004054b0 ==== */

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


/* ==== _forcdecpt @ 004054e0 ==== */

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


/* ==== _cropzeros @ 00405540 ==== */

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


/* ==== _positive @ 004055b0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _positive(double *arg)

{
  if (0.0 <= *arg) {
    return 1;
  }
  return 0;
}


/* ==== _fassign @ 004055d0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _fassign(int flag,char *argument,char *number)

{
  uint uStack_8;
  undefined4 uStack_4;
  
  if (flag != 0) {
    FUN_004078d0(&uStack_8,(byte *)number);
    *(uint *)argument = uStack_8;
    *(undefined4 *)(argument + 4) = uStack_4;
    return;
  }
  FUN_00407910((uint *)&number,(byte *)number);
  *(char **)argument = number;
  return;
}


/* ==== _cftoe @ 00405630 ==== */

char __cdecl _cftoe(double *pvalue,char *buf,int ndec,int caps)

{
  int *pflt;
  char *pcVar1;
  int iVar2;
  char *unaff_ESI;
  char *pcVar3;
  void *unaff_EDI;
  int *piVar4;
  
  piVar4 = DAT_0040ee50;
  if (DAT_0040ee54 == '\0') {
    _fltout2(*pvalue,unaff_EDI,unaff_ESI);
    _fptostr(buf + (uint)(*pflt == 0x2d) + (uint)(0 < ndec),ndec + 1,pflt);
    piVar4 = pflt;
  }
  else {
    _shift(buf + (*DAT_0040ee50 == 0x2d),(uint)(0 < ndec));
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
  pcVar3 = pcVar1 + ndec + (uint)(DAT_0040ee54 == '\0');
  builtin_strncpy(pcVar1 + ndec + (uint)(DAT_0040ee54 == '\0'),"e+000",6);
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


/* ==== _cftof @ 00405770 ==== */

char __cdecl _cftof(double *pvalue,char *buf,int ndec)

{
  int iVar1;
  int *pflt;
  uint uVar2;
  char *unaff_ESI;
  int *piVar3;
  void *unaff_EDI;
  char *pcVar4;
  
  piVar3 = DAT_0040ee50;
  if (DAT_0040ee54 == '\0') {
    _fltout2(*pvalue,unaff_EDI,unaff_ESI);
    _fptostr(buf + (*pflt == 0x2d),pflt[1] + ndec,pflt);
    piVar3 = pflt;
  }
  else if (DAT_0040ee58 == ndec) {
    iVar1 = DAT_0040ee58 + (uint)(*DAT_0040ee50 == 0x2d);
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
      if ((DAT_0040ee54 != '\0') || (-iVar1 <= ndec)) {
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


/* ==== _cftog @ 00405870 ==== */

char __cdecl _cftog(double *pvalue,char *buf,int ndec,int caps)

{
  char cVar1;
  int *pflt;
  char *buf_00;
  char *unaff_ESI;
  void *unaff_EDI;
  
  _fltout2(*pvalue,unaff_EDI,unaff_ESI);
  DAT_0040ee58 = pflt[1] + -1;
  buf_00 = buf + (*pflt == 0x2d);
  DAT_0040ee50 = pflt;
  _fptostr(buf_00,ndec,pflt);
  DAT_0040ee5c = DAT_0040ee58 < DAT_0040ee50[1] + -1;
  DAT_0040ee58 = DAT_0040ee50[1] + -1;
  if ((-5 < DAT_0040ee58) && (DAT_0040ee58 < ndec)) {
    if ((bool)DAT_0040ee5c) {
      cVar1 = *buf_00;
      while (cVar1 != '\0') {
        cVar1 = buf_00[1];
        buf_00 = buf_00 + 1;
      }
      buf_00[-1] = '\0';
    }
    cVar1 = FUN_00405950(pvalue,buf,ndec);
    return cVar1;
  }
  cVar1 = FUN_00405920(pvalue,buf,ndec,caps);
  return cVar1;
}


/* ==== FUN_00405920 @ 00405920 ==== */

void __cdecl FUN_00405920(double *param_1,undefined1 *param_2,int param_3,int param_4)

{
  DAT_0040ee54 = 1;
  _cftoe(param_1,param_2,param_3,param_4);
  DAT_0040ee54 = 0;
  return;
}


/* ==== FUN_00405950 @ 00405950 ==== */

void __cdecl FUN_00405950(double *param_1,char *param_2,uint param_3)

{
  DAT_0040ee54 = 1;
  _cftof(param_1,param_2,param_3);
  DAT_0040ee54 = 0;
  return;
}


/* ==== _cfltcvt @ 00405980 ==== */

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


/* ==== _shift @ 004059f0 ==== */

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


/* ==== _write @ 00405a20 ==== */

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


/* ==== _setenvp @ 00405c40 ==== */

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


/* ==== _setargv @ 00405d30 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _setargv(void)

{
  char **argv;
  char *cmdstart;
  int local_8;
  int local_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_0040ee60,0x104);
  _DAT_0040edf8 = &DAT_0040ee60;
  cmdstart = _acmdln;
  if (*_acmdln == '\0') {
    cmdstart = &DAT_0040ee60;
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


/* ==== parse_cmdline @ 00405dd0 ==== */

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
      if (((*(byte *)((int)&DAT_0040ef70 + bVar2 + 1) & 4) != 0) &&
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
      if ((*(byte *)((int)numchars + 0x40ef71) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if ((byte *)args != (byte *)0x0) {
          *args = *pbVar7;
          args = args + 1;
        }
        pbVar7 = (byte *)(cmdstart + 2);
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_00405ea9;
      cmdstart = (char *)pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_00405ea9:
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
          if ((*(byte *)((int)&DAT_0040ef70 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_00405fa5;
        }
        if ((*(byte *)((int)&DAT_0040ef70 + bVar2 + 1) & 4) != 0) {
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
LAB_00405fa5:
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


/* ==== __crtGetEnvironmentStringsA @ 00405fe0 ==== */

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
  if (DAT_0040ef68 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr == (LPWCH)0x0) {
      pCVar8 = GetEnvironmentStrings();
      if (pCVar8 == (LPCH)0x0) {
        return;
      }
      DAT_0040ef68 = 2;
    }
    else {
      DAT_0040ef68 = 1;
    }
  }
  if (DAT_0040ef68 == 1) {
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
  else if ((DAT_0040ef68 == 2) &&
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


/* ==== _setmbcp @ 00406140 ==== */

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
  
  CodePage = FUN_00406330(codepage);
  if (CodePage == DAT_0040f074) {
    return 0;
  }
  if (CodePage == 0) {
    FUN_004063e0();
    return 0;
  }
  iVar10 = 0;
  pUVar5 = &DAT_0040e5a0;
  do {
    if (*pUVar5 == CodePage) {
      puVar14 = &DAT_0040ef70;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined1 *)puVar14 = 0;
      uVar7 = 0;
      iVar10 = iVar10 * 0x30;
      pbVar12 = (byte *)(iVar10 + 0x40e5b0);
      do {
        bVar3 = *pbVar12;
        for (pbVar13 = pbVar12; (bVar3 != 0 && (bVar3 = pbVar13[1], bVar3 != 0));
            pbVar13 = pbVar13 + 2) {
          uVar8 = (uint)*pbVar13;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_0040e598)[uVar7];
            do {
              pbVar2 = (byte *)((int)&DAT_0040ef70 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          bVar3 = pbVar13[2];
        }
        uVar7 = uVar7 + 1;
        pbVar12 = pbVar12 + 8;
      } while (uVar7 < 4);
      DAT_0040f074 = CodePage;
      _DAT_0040f078 = FUN_00406380(CodePage);
      _DAT_0040f080 = *(undefined4 *)(iVar10 + 0x40e5a4);
      _DAT_0040f084 = *(undefined4 *)(iVar10 + 0x40e5a8);
      _DAT_0040f088 = *(undefined4 *)(iVar10 + 0x40e5ac);
      return 0;
    }
    pUVar5 = pUVar5 + 0xc;
    iVar10 = iVar10 + 1;
  } while (pUVar5 < &DAT_0040e690);
  BVar6 = GetCPInfo(CodePage,&local_14);
  if (BVar6 != 1) {
    if (DAT_0040f08c == 0) {
      return -1;
    }
    FUN_004063e0();
    return 0;
  }
  puVar14 = &DAT_0040ef70;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined1 *)puVar14 = 0;
  if (local_14.MaxCharSize < 2) {
    DAT_0040f074 = 0;
    _DAT_0040f078 = 0;
  }
  else {
    if (local_14.LeadByte[0] != '\0') {
      pBVar11 = local_14.LeadByte + 1;
      do {
        bVar3 = *pBVar11;
        if (bVar3 == 0) break;
        for (uVar7 = (uint)pBVar11[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
          *(byte *)((int)&DAT_0040ef70 + uVar7 + 1) = *(byte *)((int)&DAT_0040ef70 + uVar7 + 1) | 4;
        }
        pBVar1 = pBVar11 + 1;
        pBVar11 = pBVar11 + 2;
      } while (*pBVar1 != 0);
    }
    uVar7 = 1;
    do {
      *(byte *)((int)&DAT_0040ef70 + uVar7 + 1) = *(byte *)((int)&DAT_0040ef70 + uVar7 + 1) | 8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0xff);
    DAT_0040f074 = CodePage;
    _DAT_0040f078 = FUN_00406380(CodePage);
  }
  _DAT_0040f080 = 0;
  _DAT_0040f084 = 0;
  _DAT_0040f088 = 0;
  return 0;
}


/* ==== FUN_00406330 @ 00406330 ==== */

int __cdecl FUN_00406330(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_0040f08c = 1;
                    /* WARNING: Could not recover jumptable at 0x0040634d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_0040f08c = 1;
                    /* WARNING: Could not recover jumptable at 0x00406362. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_0040f0e0;
  }
  DAT_0040f08c = (uint)bVar2;
  return param_1;
}


/* ==== FUN_00406380 @ 00406380 ==== */

undefined4 __cdecl FUN_00406380(undefined4 param_1)

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


/* ==== FUN_004063e0 @ 004063e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004063e0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_0040ef70;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_0040f074 = 0;
  _DAT_0040f078 = 0;
  _DAT_0040f080 = 0;
  _DAT_0040f084 = 0;
  _DAT_0040f088 = 0;
  return;
}


/* ==== __initmbctable @ 00406410 ==== */

int __initmbctable(void)

{
  int iVar1;
  
  iVar1 = _setmbcp(-3);
  return iVar1;
}


/* ==== __global_unwind2 @ 00406420 ==== */

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x406438,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


/* ==== __local_unwind2 @ 00406462 ==== */

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
  puStack_18 = &LAB_00406440;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_004064f6();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}


/* ==== FUN_004064f6 @ 004064f6 ==== */

void FUN_004064f6(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_0040e698 = *(undefined4 *)(unaff_EBP + 8);
  DAT_0040e694 = in_EAX;
  DAT_0040e69c = unaff_EBP;
  return;
}


/* ==== FUN_004065d5 @ 004065d5 ==== */

void FUN_004065d5(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* ==== _FF_MSGBANNER @ 004065f0 ==== */

void _FF_MSGBANNER(void)

{
  if ((DAT_0040ee34 == 1) || ((DAT_0040ee34 == 0 && (DAT_0040c3f8 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_0040f090 != (code *)0x0) {
      (*DAT_0040f090)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}


/* ==== _NMSG_WRITE @ 00406630 ==== */

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
  
  piVar2 = &DAT_0040e6a0;
  iVar8 = 0;
  do {
    if (rterrnum == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar8 = iVar8 + 1;
  } while (piVar2 < &DAT_0040e730);
  if (rterrnum == (&DAT_0040e6a0)[iVar8 * 2]) {
    if ((DAT_0040ee34 == 1) || ((DAT_0040ee34 == 0 && (DAT_0040c3f8 == 1)))) {
      if ((__pioinfo == 0) || (hFile = *(HANDLE *)(__pioinfo + 0x10), hFile == (HANDLE)0xffffffff))
      {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar7 = *(char **)(iVar8 * 8 + 0x40e6a4);
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
      pcVar7 = *(char **)(iVar8 * 8 + 0x40e6a4);
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


/* ==== _dosmaperr @ 00406810 ==== */

void __cdecl _dosmaperr(ulong oserrno)

{
  undefined **ppuVar1;
  int iVar2;
  
  _doserrno = oserrno;
  iVar2 = 0;
  ppuVar1 = (undefined **)&DAT_0040e730;
  do {
    if ((undefined *)oserrno == *ppuVar1) {
      errno = *(undefined4 *)(iVar2 * 8 + 0x40e734);
      return;
    }
    ppuVar1 = ppuVar1 + 2;
    iVar2 = iVar2 + 1;
  } while (ppuVar1 < &_pctype);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    errno = 0xd;
    return;
  }
  if ((oserrno < 0xbc) || (errno = 8, 0xca < oserrno)) {
    errno = 0x16;
  }
  return;
}


/* ==== _alloc_osfhnd @ 00406880 ==== */

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
    if (0x40f2ff < (int)piVar3) {
      return -1;
    }
  } while( true );
}


/* ==== _set_osfhnd @ 00406940 ==== */

int __cdecl _set_osfhnd(int fh,long value)

{
  int iVar1;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (*(int *)((&__pioinfo)[fh >> 5] + iVar1) == -1) {
      if (DAT_0040c3f8 == 1) {
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


/* ==== _free_osfhnd @ 004069f0 ==== */

int __cdecl _free_osfhnd(int fh)

{
  int iVar1;
  DWORD nStdHandle;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar1) & 1) != 0) &&
       (*(int *)((&__pioinfo)[fh >> 5] + iVar1) != -1)) {
      if (DAT_0040c3f8 == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_00406a5a;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_00406a5a:
      *(undefined4 *)((&__pioinfo)[fh >> 5] + iVar1) = 0xffffffff;
      return 0;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _get_osfhandle @ 00406a90 ==== */

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


/* ==== _sopen @ 00406b40 ==== */

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
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_0040f0f0 != 0x8000)))) {
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
    goto switchD_00406bd8_caseD_11;
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
      goto LAB_00406c6b;
    }
    if (uVar1 != 0) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00406c46:
    dwCreationDisposition = 3;
    goto LAB_00406c6b;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      dwCreationDisposition = 2;
      goto LAB_00406c6b;
    }
    if (uVar1 != 0x200) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00406c66:
    dwCreationDisposition = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_00406bd8_caseD_11:
          _doserrno = 0;
          errno = 0x16;
          return -1;
        }
        goto LAB_00406c46;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_00406c66;
      if (uVar1 != 0x700) {
        errno = 0x16;
        _doserrno = 0;
        return -1;
      }
    }
    dwCreationDisposition = 1;
  }
LAB_00406c6b:
  dwFlagsAndAttributes = 0x80;
  if (((oflag & 0x100U) != 0) && (((byte)pmode & ~(byte)DAT_0040edc8 & 0x80) == 0)) {
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


/* ==== _isatty @ 00406f00 ==== */

int __cdecl _isatty(int fh)

{
  if (_nhandle <= (uint)fh) {
    return 0;
  }
  return *(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 0x40;
}


/* ==== wctomb @ 00406f30 ==== */

int __cdecl wctomb(char *s,ushort wc)

{
  char *lpMultiByteStr;
  int iVar1;
  
  lpMultiByteStr = s;
  if (s == (char *)0x0) {
    return 0;
  }
  if (DAT_0040f0d0 == 0) {
    if (wc < 0x100) {
      *s = (char)wc;
      return 1;
    }
  }
  else {
    s = (char *)0x0;
    iVar1 = WideCharToMultiByte(DAT_0040f0e0,0x220,(LPCWSTR)&wc,1,lpMultiByteStr,__mb_cur_max,
                                (LPCSTR)0x0,(LPBOOL)&s);
    if ((iVar1 != 0) && (s == (char *)0x0)) {
      return iVar1;
    }
  }
  errno = 0x2a;
  return -1;
}


/* ==== __aulldiv @ 00406fb0 ==== */

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


/* ==== __aullrem @ 00407020 ==== */

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


/* ==== _getbuf @ 004070a0 ==== */

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


/* ==== FUN_00407100 @ 00407100 ==== */

uint __thiscall FUN_00407100(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_00407160(local_8);
  uVar1 = param_2 & param_1 | ~param_2 & uVar1;
  FUN_00407200(uVar1);
  return uVar1;
}


/* ==== FUN_00407140 @ 00407140 ==== */

void __cdecl FUN_00407140(void *param_1,uint param_2)

{
  FUN_00407100(param_1,(uint)param_1,param_2 & 0xfff7ffff);
  return;
}


/* ==== FUN_00407160 @ 00407160 ==== */

uint __cdecl FUN_00407160(uint param_1)

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


/* ==== FUN_00407200 @ 00407200 ==== */

void FUN_00407200(void)

{
  return;
}


/* ==== _isctype @ 00407290 ==== */

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
  BVar2 = FUN_00408190(1,(LPCSTR)&c,iVar1,(LPWORD)&local_4,0,0);
  if (BVar2 == 0) {
    return 0;
  }
  return local_4 & 0xffff & mask;
}


/* ==== tolower @ 00407330 ==== */

int __cdecl tolower(int c)

{
  int iVar1;
  uint uVar2;
  LPCWSTR pWVar3;
  int iVar4;
  uint local_8 [2];
  
  iVar1 = c;
  if (DAT_0040f0d0 == 0) {
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
    iVar4 = FUN_004082c0(DAT_0040f0d0,0x100,(char *)&c,pWVar3,(LPWSTR)local_8,3,0);
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


/* ==== FUN_00407430 @ 00407430 ==== */

undefined4 __cdecl FUN_00407430(int param_1,int param_2)

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


/* ==== FUN_004074a0 @ 004074a0 ==== */

void __cdecl FUN_004074a0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = FUN_00408510(*(uint *)(param_1 + iVar3 * 4),
                       1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) &
                            0x1f),(uint *)(param_1 + iVar3 * 4));
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (uint *)(param_1 + iVar3 * 4);
    do {
      if (iVar2 == 0) {
        return;
      }
      iVar2 = FUN_00408510(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return;
}


/* ==== FUN_00407510 @ 00407510 ==== */

undefined4 __cdecl FUN_00407510(int param_1,int param_2)

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
     (iVar1 = FUN_00407430(param_1,param_2 + 1), iVar1 == 0)) {
    local_4 = FUN_004074a0(param_1,param_2 + -1);
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


/* ==== FUN_004075b0 @ 004075b0 ==== */

void __cdecl FUN_004075b0(int param_1,undefined4 *param_2)

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


/* ==== FUN_004075d0 @ 004075d0 ==== */

void __cdecl FUN_004075d0(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


/* ==== FUN_004075e0 @ 004075e0 ==== */

undefined4 __cdecl FUN_004075e0(int *param_1)

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


/* ==== FUN_00407600 @ 00407600 ==== */

void __cdecl FUN_00407600(uint *param_1,int param_2)

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


/* ==== FUN_004076c0 @ 004076c0 ==== */

undefined4 __cdecl FUN_004076c0(ushort *param_1,uint *param_2,int *param_3)

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
    iVar2 = FUN_004075e0((int *)&local_18);
    if (iVar2 == 0) {
      FUN_004075d0(&local_18);
      uVar3 = 2;
      goto LAB_00407841;
    }
  }
  else {
    FUN_004075b0((int)local_c,&local_18);
    iVar2 = FUN_00407510((int)&local_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_004075d0(&local_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_00407841;
    }
    if (iVar5 <= iVar2) {
      FUN_004075b0((int)&local_18,local_c);
      FUN_00407600(&local_18,iVar2 - iVar5);
      FUN_00407510((int)&local_18,param_3[2]);
      FUN_00407600(&local_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_00407841;
    }
    if (*param_3 <= iVar5) {
      FUN_004075d0(&local_18);
      local_18 = local_18 | 0x80000000;
      FUN_00407600(&local_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_00407841;
    }
    iVar5 = param_3[5] + iVar5;
    local_18 = local_18 & 0x7fffffff;
    FUN_00407600(&local_18,param_3[3]);
  }
  uVar3 = 0;
LAB_00407841:
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


/* ==== FUN_00407890 @ 00407890 ==== */

void __cdecl FUN_00407890(ushort *param_1,uint *param_2)

{
  FUN_004076c0(param_1,param_2,(int *)&DAT_0040eac0);
  return;
}


/* ==== FUN_004078b0 @ 004078b0 ==== */

void __cdecl FUN_004078b0(ushort *param_1,uint *param_2)

{
  FUN_004076c0(param_1,param_2,(int *)&DAT_0040ead8);
  return;
}


/* ==== FUN_004078d0 @ 004078d0 ==== */

void __cdecl FUN_004078d0(uint *param_1,byte *param_2)

{
  ushort local_c [6];
  
  __strgtold12(local_c,(char **)&param_2,(char *)param_2,0,0,0,0);
  FUN_00407890(local_c,param_1);
  return;
}


/* ==== FUN_00407910 @ 00407910 ==== */

void __cdecl FUN_00407910(uint *param_1,byte *param_2)

{
  ushort local_c [6];
  
  __strgtold12(local_c,(char **)&param_2,(char *)param_2,0,0,0,0);
  FUN_004078b0(local_c,param_1);
  return;
}


/* ==== _fptostr @ 00407950 ==== */

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


/* ==== _fltout2 @ 004079f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _fltout2(double x,void *flt,char *resultstr)

{
  undefined4 in_stack_ffffffe4;
  undefined2 uVar1;
  uint local_c;
  uint local_8;
  undefined2 local_4;
  
  uVar1 = (undefined2)((uint)in_stack_ffffffe4 >> 0x10);
  FUN_00407a70(&local_c,(uint *)&x);
  _DAT_0040f0c0 = FUN_00408ea0(local_c,local_8,CONCAT22(uVar1,local_4),0x11,0,&DAT_0040f098);
  _DAT_0040f0b8 = (int)DAT_0040f09a;
  _DAT_0040f0bc = (int)DAT_0040f098;
  _DAT_0040f0c4 = &DAT_0040f09c;
  return;
}


/* ==== FUN_00407a70 @ 00407a70 ==== */

void __cdecl FUN_00407a70(uint *param_1,uint *param_2)

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


/* ==== memmove @ 00407b30 ==== */

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
          goto switchD_00407ce7_caseD_2;
        case 3:
          goto switchD_00407ce7_caseD_3;
        }
        goto switchD_00407ce7_caseD_1;
      }
    }
    else {
      switch(n) {
      case 0:
        goto switchD_00407ce7_caseD_0;
      case 1:
        goto switchD_00407ce7_caseD_1;
      case 2:
        goto switchD_00407ce7_caseD_2;
      case 3:
        goto switchD_00407ce7_caseD_3;
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
              goto switchD_00407ce7_caseD_2;
            case 3:
              goto switchD_00407ce7_caseD_3;
            }
            goto switchD_00407ce7_caseD_1;
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
              goto switchD_00407ce7_caseD_2;
            case 3:
              goto switchD_00407ce7_caseD_3;
            }
            goto switchD_00407ce7_caseD_1;
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
              goto switchD_00407ce7_caseD_2;
            case 3:
              goto switchD_00407ce7_caseD_3;
            }
            goto switchD_00407ce7_caseD_1;
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
switchD_00407ce7_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return;
    case 2:
switchD_00407ce7_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return;
    case 3:
switchD_00407ce7_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return;
    }
switchD_00407ce7_caseD_0:
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
        goto switchD_00407b65_caseD_2;
      case 3:
        goto switchD_00407b65_caseD_3;
      }
      goto switchD_00407b65_caseD_1;
    }
  }
  else {
    switch(n) {
    case 0:
      goto switchD_00407b65_caseD_0;
    case 1:
      goto switchD_00407b65_caseD_1;
    case 2:
      goto switchD_00407b65_caseD_2;
    case 3:
      goto switchD_00407b65_caseD_3;
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
            goto switchD_00407b65_caseD_2;
          case 3:
            goto switchD_00407b65_caseD_3;
          }
          goto switchD_00407b65_caseD_1;
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
            goto switchD_00407b65_caseD_2;
          case 3:
            goto switchD_00407b65_caseD_3;
          }
          goto switchD_00407b65_caseD_1;
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
            goto switchD_00407b65_caseD_2;
          case 3:
            goto switchD_00407b65_caseD_3;
          }
          goto switchD_00407b65_caseD_1;
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
switchD_00407b65_caseD_1:
    *(undefined1 *)dst = *(undefined1 *)src;
    return;
  case 2:
switchD_00407b65_caseD_2:
    *(undefined1 *)dst = *(undefined1 *)src;
    *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
    return;
  case 3:
switchD_00407b65_caseD_3:
    *(undefined1 *)dst = *(undefined1 *)src;
    *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
    *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
    return;
  }
switchD_00407b65_caseD_0:
  return;
}


/* ==== _fptrap @ 00407e70 ==== */

void _fptrap(void)

{
  _amsg_exit(2);
  return;
}


/* ==== __crtMessageBoxA @ 00407e80 ==== */

int __cdecl __crtMessageBoxA(char *text,char *caption,uint type)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_0040f0e4 != (FARPROC)0x0) {
LAB_00407ed0:
    if (DAT_0040f0e8 != (FARPROC)0x0) {
      iVar1 = (*DAT_0040f0e8)();
    }
    if ((iVar1 != 0) && (DAT_0040f0ec != (FARPROC)0x0)) {
      iVar1 = (*DAT_0040f0ec)(iVar1);
    }
    iVar1 = (*DAT_0040f0e4)(iVar1,text,caption,type);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_0040f0e4 = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_0040f0e4 != (FARPROC)0x0) {
      DAT_0040f0e8 = GetProcAddress(hModule,"GetActiveWindow");
      DAT_0040f0ec = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_00407ed0;
    }
  }
  return 0;
}


/* ==== strncpy @ 00407f10 ==== */

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
        goto joined_r0x00407f4e;
      }
    }
    do {
      if (((uint)dst & 3) == 0) {
        uVar5 = n >> 2;
        cVar4 = '\0';
        if (uVar5 == 0) goto LAB_00407f8b;
        goto LAB_00407ff9;
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
joined_r0x00407ff5:
          while( true ) {
            uVar5 = uVar5 - 1;
            dst = (char *)((int)dst + 4);
            if (uVar5 == 0) break;
LAB_00407ff9:
            *(uint *)dst = 0;
          }
          cVar4 = '\0';
          n = n & 3;
          if (n != 0) goto LAB_00407f8b;
          return cVar3;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *(uint *)dst = uVar2 & 0xff;
          goto joined_r0x00407ff5;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *(uint *)dst = uVar2 & 0xffff;
          goto joined_r0x00407ff5;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *(uint *)dst = uVar2;
          goto joined_r0x00407ff5;
        }
      }
      *(uint *)dst = uVar2;
      dst = (char *)((int)dst + 4);
      uVar5 = uVar5 - 1;
joined_r0x00407f4e:
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
LAB_00407f8b:
        *dst = cVar4;
        dst = (char *)((int)dst + 1);
      }
      return cVar3;
    }
    n = n - 1;
  } while (n != 0);
  return cVar3;
}


/* ==== _chsize @ 00408010 ==== */

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
  
  FUN_004092b0();
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
      iVar4 = FUN_00409230(in_stack_00001008,0x8000);
      while( true ) {
        cnt = 0x1000;
        if ((int)uVar6 < 0x1000) {
          cnt = uVar6;
        }
        iVar2 = _write(in_stack_00001008,&fh,cnt);
        if (iVar2 == -1) break;
        uVar6 = uVar6 - iVar2;
        if ((int)uVar6 < 1) {
LAB_004080f1:
          FUN_00409230(in_stack_00001008,iVar4);
          _lseek(in_stack_00001008,pos,0);
          return iVar5;
        }
      }
      if (_doserrno == 5) {
        errno = 0xd;
      }
      iVar5 = -1;
      goto LAB_004080f1;
    }
  }
  else {
    errno = 9;
  }
  return -1;
}


/* ==== FUN_00408190 @ 00408190 ==== */

BOOL __cdecl
FUN_00408190(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6)

{
  BOOL BVar1;
  uint size;
  LPCWSTR lpWideCharStr;
  int cchSrc;
  LPCWSTR p;
  WORD local_2;
  
  p = (LPCWSTR)0x0;
  if (DAT_0040f0f8 == 0) {
    BVar1 = GetStringTypeA(0,1,"",1,&local_2);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeW(1,L"",1,&local_2);
      if (BVar1 == 0) {
        return 0;
      }
      DAT_0040f0f8 = 1;
    }
    else {
      DAT_0040f0f8 = 2;
    }
  }
  if (DAT_0040f0f8 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_0040f0d0;
    }
    BVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return BVar1;
  }
  param_6 = DAT_0040f0f8;
  if (DAT_0040f0f8 == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = DAT_0040f0e0;
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


/* ==== FUN_004082c0 @ 004082c0 ==== */

int __cdecl
FUN_004082c0(LCID param_1,uint param_2,char *param_3,LPCWSTR param_4,LPWSTR param_5,int param_6,
            UINT param_7)

{
  int iVar1;
  LPCWSTR cbMultiByte;
  LPCWSTR lpWideCharStr;
  int iVar2;
  LPCWSTR lpDestStr;
  
  if (DAT_0040f100 == 0) {
    iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_0040f100 = 1;
    }
    else {
      DAT_0040f100 = 2;
    }
  }
  cbMultiByte = param_4;
  if (0 < (int)param_4) {
    cbMultiByte = (LPCWSTR)__ansicp((int)param_3);
  }
  if (DAT_0040f100 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,(int)cbMultiByte,(LPSTR)param_5,param_6);
    return iVar1;
  }
  if (DAT_0040f100 != 1) {
    return DAT_0040f100;
  }
  param_4 = (LPCWSTR)0x0;
  if (param_7 == 0) {
    param_7 = DAT_0040f0e0;
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
      goto LAB_004084bf;
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
      if (param_6 == 0) goto LAB_00408424;
      if (param_6 < iVar2) goto LAB_004084bf;
      iVar1 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,param_5,param_6);
    }
    if (iVar1 != 0) {
LAB_00408424:
      free(lpWideCharStr);
      free(param_4);
      return iVar2;
    }
  }
LAB_004084bf:
  free(lpWideCharStr);
  free(param_4);
  return 0;
}


/* ==== __ansicp @ 004084e0 ==== */

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


/* ==== FUN_00408510 @ 00408510 ==== */

undefined4 __cdecl FUN_00408510(uint param_1,uint param_2,uint *param_3)

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


/* ==== FUN_00408540 @ 00408540 ==== */

void __cdecl FUN_00408540(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00408510(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_00408510(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = FUN_00408510(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  FUN_00408510(param_1[2],param_2[2],param_1 + 2);
  return;
}


/* ==== FUN_004085b0 @ 004085b0 ==== */

void __cdecl FUN_004085b0(uint *param_1)

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


/* ==== FUN_004085e0 @ 004085e0 ==== */

void __cdecl FUN_004085e0(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}


/* ==== FUN_00408610 @ 00408610 ==== */

void __cdecl FUN_00408610(char *param_1,int param_2,uint *param_3)

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
      FUN_004085b0(puVar2);
      FUN_004085b0(puVar2);
      FUN_00408540(puVar2,&local_c);
      FUN_004085b0(puVar2);
      local_c = (uint)*param_1;
      local_8 = 0;
      local_4 = 0;
      FUN_00408540(puVar2,&local_c);
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
    FUN_004085b0(puVar2);
    sVar3 = sVar3 + -1;
    uVar1 = puVar2[2];
  }
  *(short *)((int)puVar2 + 10) = sVar3;
  return;
}


/* ==== __strgtold12 @ 00408710 ==== */

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
        goto LAB_00408be2;
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
        if (bVar10 != 0x30) goto switchD_004089d2_caseD_2c;
        iVar8 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_00408be2;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 4;
      }
      else {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_004089d2_caseD_2b;
        default:
          goto switchD_004089d2_caseD_2c;
        case 0x30:
switchD_00408846_caseD_30:
          iVar8 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_004089d2_caseD_44;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_00408be2;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 5;
      }
      else {
        if (bVar10 == 0x30) goto switchD_00408846_caseD_30;
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
          goto switchD_004089d2_caseD_2b;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_004089d2_caseD_44;
        }
switchD_004089d2_caseD_2c:
        iVar8 = 10;
        goto LAB_00408be2;
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
switchD_004089d2_caseD_2b:
        bVar2 = true;
        pbVar12 = pbVar12 + -1;
        iVar8 = 0xb;
        break;
      default:
        goto switchD_004089d2_caseD_2c;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
switchD_004089d2_caseD_44:
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
        goto LAB_00408be2;
      }
      if (bVar10 == 0x2b) {
LAB_00408bd6:
        iVar8 = 7;
        pbVar15 = pbVar11;
        local_50 = pbVar11;
      }
      else {
        if (bVar10 != 0x2d) goto LAB_00408ac6;
LAB_00408bc7:
        iVar8 = 7;
        local_4c = -1;
        pbVar15 = pbVar11;
        local_50 = pbVar11;
      }
      break;
    case 7:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_00408be2;
      }
LAB_00408ac6:
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
      if (((char)bVar10 < '1') || ('9' < (char)bVar10)) goto switchD_004089d2_caseD_2c;
      iVar8 = 9;
LAB_00408be2:
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
        if (uVar13 == 0) goto LAB_00408b4a;
        local_48 = (char)bVar10 + -0x30 + local_48 * 10;
        if (0x1450 < local_48) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      local_48 = 0x1451;
LAB_00408b4a:
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
      if (implicit_E == 0) goto switchD_004089d2_caseD_2c;
      if (bVar10 == 0x2b) goto LAB_00408bd6;
      if (bVar10 == 0x2d) goto LAB_00408bc7;
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
      goto LAB_00408cb4;
    }
    cVar1 = local_5c[-1];
    while (cVar1 == '\0') {
      uVar13 = uVar13 - 1;
      local_60 = local_60 + 1;
      cVar1 = local_5c[-2];
      local_5c = local_5c + -1;
    }
    FUN_00408610(local_1c,uVar13,(uint *)&local_2c);
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
        FUN_004095a0((int *)&local_2c,uVar13,mult12);
        pcVar14 = (char *)CONCAT22(uStack_28,uStack_2a);
        str = local_26;
        goto LAB_00408cb4;
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
LAB_00408cb4:
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


/* ==== FUN_00408ea0 @ 00408ea0 ==== */

undefined4 __cdecl
FUN_00408ea0(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

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
LAB_004090af:
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
  FUN_004095a0((int *)&local_10,-(int)sVar10,1);
  if (0x3ffe < CONCAT11(cStack_5,local_6)) {
    sVar10 = sVar10 + 1;
    FUN_004092e0((int *)&local_10,(int *)&local_1c);
  }
  *psVar1 = sVar10;
  iVar9 = param_4;
  if (((param_5 & 1) != 0) && (iVar9 = param_4 + sVar10, param_4 + sVar10 < 1)) {
    *psVar1 = 0;
    goto LAB_004090af;
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
    FUN_004085b0((uint *)&local_10);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if (iVar11 < 0) {
    for (uVar5 = -iVar11 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
      FUN_004085e0((uint *)&local_10);
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
      FUN_004085b0((uint *)&local_10);
      FUN_004085b0((uint *)&local_10);
      FUN_00408540((uint *)&local_10,&param_1);
      FUN_004085b0((uint *)&local_10);
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
      if (psVar1 <= psVar8) goto LAB_00409206;
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
      goto LAB_00409206;
    }
  }
  psVar8 = (short *)((int)psVar8 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar8 = *(char *)psVar8 + '\x01';
LAB_00409206:
  cVar4 = ((char)psVar8 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar4;
  *(undefined1 *)((int)param_6 + cVar4 + 4) = 0;
  return 1;
}


/* ==== FUN_00409230 @ 00409230 ==== */

int __cdecl FUN_00409230(uint param_1,int param_2)

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


/* ==== FUN_004092b0 @ 004092b0 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_004092b0(void)

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


/* ==== FUN_004092e0 @ 004092e0 ==== */

void __cdecl FUN_004092e0(int *param_1,int *param_2)

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
        iVar2 = FUN_00408510(*(uint *)(local_20 + -2),(uint)*puVar8 * (uint)*puVar7,
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
    FUN_004085b0((uint *)&local_c);
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
        FUN_004085e0((uint *)&local_c);
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


/* ==== FUN_004095a0 @ 004095a0 ==== */

void __cdecl FUN_004095a0(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined2 local_c;
  undefined4 uStack_a;
  undefined2 uStack_6;
  int local_4;
  
  iVar3 = 0x40ea90;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = 0x40ebf0;
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
        FUN_004092e0(param_1,piVar2);
      }
    }
  }
  return;
}


/* ==== RtlUnwind @ 00409630 ==== */

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x00409630. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


