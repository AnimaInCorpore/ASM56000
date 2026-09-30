/* map: 36 functions from DSPLNK */

/* ==== FUN_0041d7d0 @ 0041d7d0 ==== */

void FUN_0041d7d0(void)

{
  if (DAT_0046129c == 0) {
    FUN_0041d8d1(s_No_sections_found_00458e6c);
  }
  else {
    FUN_0041e110();
    FUN_0041ee64();
  }
  if (DAT_004612dc == 0) {
    if ((DAT_00457b64 != '\0') || (DAT_00457b68 != '\0')) {
      if (DAT_00457b90 == '\0') {
        FUN_0041db64(1);
      }
      FUN_0041d8d1(s_No_symbols_found_00458e80);
    }
  }
  else {
    if (((DAT_00457b64 != '\0') || (DAT_00457b68 != '\0')) && (DAT_00457b90 == '\0')) {
      FUN_0041db64(1);
    }
    FUN_0041f797();
    FUN_004200d0();
  }
  if ((DAT_00461208 != '\0') && (DAT_0046129c != 0)) {
    if (DAT_00457b90 == '\0') {
      FUN_0041db64(1);
    }
    FUN_004207e9();
  }
  if ((DAT_00461248 == '\0') && (DAT_004612e0 != DAT_004612e4)) {
    if (DAT_00457b90 == '\0') {
      FUN_0041db64(1);
    }
    FUN_00421b2a();
  }
  return;
}


/* ==== FUN_0041d8d1 @ 0041d8d1 ==== */

void __cdecl FUN_0041d8d1(char *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint local_c;
  
  iVar2 = DAT_00457bc0;
  DAT_00457bc0 = iVar2;
  if (DAT_00457b90 != '\0') {
    DAT_00457b90 = '\0';
    FUN_0041dcc0();
    DAT_00457bc0 = iVar2;
  }
  for (; iVar2 = DAT_00457bc0, *param_1 != '\0'; param_1 = param_1 + 1) {
    iVar3 = DAT_00457bbc + 1;
    bVar1 = DAT_00457bc4 < DAT_00457bbc;
    DAT_00457bbc = iVar3;
    if ((bVar1) && (*param_1 != '\n')) {
      FUN_0041da05();
    }
    DAT_00457bc0 = iVar2 + 1;
    if (*param_1 == '\n') {
      FUN_0041da05();
    }
    else {
      DAT_00461f3c[1] = DAT_00461f3c[1] + -1;
      if (DAT_00461f3c[1] < 0) {
        local_c = _flsbuf((int)*param_1,DAT_00461f3c);
      }
      else {
        *(char *)*DAT_00461f3c = *param_1;
        local_c = (uint)*(byte *)*DAT_00461f3c;
        *DAT_00461f3c = *DAT_00461f3c + 1;
      }
      if (local_c == 0xffffffff) {
        thunk_FUN_004098b0(s_Cannot_write_string_to_map_file_00458e94);
      }
    }
  }
  return;
}


/* ==== FUN_0041da05 @ 0041da05 ==== */

void FUN_0041da05(void)

{
  int local_8;
  
  if (DAT_00457bcc < DAT_00457bd0) {
    DAT_00461f3c[1] = DAT_00461f3c[1] + -1;
    if (DAT_00461f3c[1] < 0) {
      local_8 = _flsbuf(10,DAT_00461f3c);
    }
    else {
      *(undefined1 *)*DAT_00461f3c = 10;
      local_8 = 10;
      *DAT_00461f3c = *DAT_00461f3c + 1;
    }
    if (local_8 == -1) {
      thunk_FUN_004098b0(s_Cannot_write_new_line_to_map_fil_00458eb4);
    }
    DAT_00457bcc = DAT_00457bcc + 1;
    DAT_00457bbc = 1;
    DAT_00457bc0 = 1;
  }
  else {
    FUN_0041db64(1);
  }
  FUN_0041dac4();
  return;
}


/* ==== FUN_0041dac4 @ 0041dac4 ==== */

void FUN_0041dac4(void)

{
  int local_8;
  
  for (; DAT_00457bbc < DAT_00457bc8; DAT_00457bbc = DAT_00457bbc + 1) {
    DAT_00461f3c[1] = DAT_00461f3c[1] + -1;
    if (DAT_00461f3c[1] < 0) {
      local_8 = _flsbuf(0x20,DAT_00461f3c);
    }
    else {
      *(undefined1 *)*DAT_00461f3c = 0x20;
      local_8 = 0x20;
      *DAT_00461f3c = *DAT_00461f3c + 1;
    }
    if (local_8 == -1) {
      thunk_FUN_004098b0(s_Cannot_write_left_margin_to_map_f_00458ed8);
    }
  }
  return;
}


/* ==== FUN_0041db64 @ 0041db64 ==== */

void __cdecl FUN_0041db64(int param_1)

{
  int iVar1;
  int local_8;
  
  if (DAT_00461240 == '\0') {
    for (; DAT_00457bcc <= DAT_00457bd4; DAT_00457bcc = DAT_00457bcc + 1) {
      DAT_00461f3c[1] = DAT_00461f3c[1] + -1;
      if (DAT_00461f3c[1] < 0) {
        iVar1 = _flsbuf(10,DAT_00461f3c);
      }
      else {
        *(undefined1 *)*DAT_00461f3c = 10;
        iVar1 = 10;
        *DAT_00461f3c = *DAT_00461f3c + 1;
      }
      if (iVar1 == -1) {
        thunk_FUN_004098b0(s_Cannot_write_new_page_to_map_fil_00458f24);
      }
    }
  }
  else {
    DAT_00461f3c[1] = DAT_00461f3c[1] + -1;
    if (DAT_00461f3c[1] < 0) {
      local_8 = _flsbuf(0xc,DAT_00461f3c);
    }
    else {
      *(undefined1 *)*DAT_00461f3c = 0xc;
      local_8 = 0xc;
      *DAT_00461f3c = *DAT_00461f3c + 1;
    }
    if (local_8 == -1) {
      thunk_FUN_004098b0(s_Cannot_write_form_feed_to_map_fi_00458f00);
    }
  }
  if (param_1 != 0) {
    DAT_00457bbc = 1;
    DAT_00457bc0 = 1;
    DAT_00457bcc = 1;
    DAT_00461310 = DAT_00461310 + 1;
    FUN_0041dcc0();
  }
  return;
}


/* ==== FUN_0041dcc0 @ 0041dcc0 ==== */

void FUN_0041dcc0(void)

{
  int local_8;
  
  for (DAT_00457bcc = 1; DAT_00457bcc <= DAT_00457bdc; DAT_00457bcc = DAT_00457bcc + 1) {
    DAT_00461f3c[1] = DAT_00461f3c[1] + -1;
    if (DAT_00461f3c[1] < 0) {
      local_8 = _flsbuf(10,DAT_00461f3c);
    }
    else {
      *(undefined1 *)*DAT_00461f3c = 10;
      local_8 = 10;
      *DAT_00461f3c = *DAT_00461f3c + 1;
    }
    if (local_8 == -1) {
      thunk_FUN_004098b0(s_Cannot_write_page_header_to_map_f_00458f48);
    }
  }
  if (DAT_00457bd8 != 0) {
    FUN_0041dd75();
  }
  return;
}


/* ==== FUN_0041dd75 @ 0041dd75 ==== */

void FUN_0041dd75(void)

{
  char *local_24;
  char *local_20;
  char *local_1c;
  char *local_18;
  char local_14 [16];
  
  FUN_0041dac4();
  FUN_0041d8d1(&DAT_00458f70);
  FUN_0041d8d1(s_Linker_00457ed8);
  FUN_0041d8d1(s_Version_00458f78);
  if (DAT_00461260 == '\0') {
    local_18 = s_6_3_7_00457ee0;
  }
  else {
    local_18 = &DAT_00458f84;
  }
  FUN_0041dea5(local_18);
  FUN_0041d8d1(&DAT_00458f8c);
  if (DAT_00461260 == '\0') {
    local_1c = &DAT_00461d48;
  }
  else {
    local_1c = s_00_00_00_00458f90;
  }
  FUN_0041dea5(local_1c);
  FUN_0041d8d1(&DAT_00458f9c);
  if (DAT_00461260 == '\0') {
    local_20 = &DAT_00461d58;
  }
  else {
    local_20 = s_00_00_00_00458fa0;
  }
  FUN_0041dea5(local_20);
  FUN_0041d8d1(&DAT_00458fac);
  if (DAT_00461260 == '\0') {
    local_24 = &DAT_00461730;
  }
  else {
    local_24 = thunk_FUN_0042e468(&DAT_00461730);
  }
  FUN_0041dea5(local_24);
  sprintf(local_14,s_Page__d_00458fb0,DAT_00461310);
  FUN_0041dea5(local_14);
  FUN_0041da05();
  FUN_0041da05();
  return;
}


/* ==== FUN_0041dea5 @ 0041dea5 ==== */

void __cdecl FUN_0041dea5(char *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = strlen(param_1);
  uVar1 = DAT_00457bc0;
  if (((int)uVar2 <= (DAT_00457bc4 - DAT_00457bc8) + 1) &&
     (DAT_00457bc4 < (int)(uVar2 + DAT_00457bbc))) {
    FUN_0041da05();
  }
  DAT_00457bc0 = uVar1;
  FUN_0041d8d1(param_1);
  return;
}


/* ==== FUN_0041df05 @ 0041df05 ==== */

void FUN_0041df05(void)

{
  int *piVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 va2;
  uint va3;
  undefined4 local_44;
  uint local_40;
  int local_2c;
  undefined4 local_24;
  int local_18;
  uint local_8;
  
  if ((((DAT_00461248 == '\0') && (DAT_0046122c == '\0')) && (DAT_00461238 != '\0')) &&
     (DAT_0046129c != 0)) {
    if (DAT_00461f20 != (undefined *)0x0) {
      thunk_FUN_0042e1ce(DAT_00461f20);
    }
    iVar4 = FUN_0041f5d6();
    FUN_0042164c(iVar4,DAT_0046129c);
    DAT_00461f20 = (undefined *)0x0;
    bVar3 = true;
    local_8 = 0;
    local_40 = 0;
    local_2c = 4;
    local_24 = 0;
    for (local_18 = 0; local_18 < DAT_0046129c; local_18 = local_18 + 1) {
      piVar1 = *(int **)(iVar4 + local_18 * 4);
      if (*(int *)(*piVar1 + 8) != local_2c) {
        local_2c = *(int *)(*piVar1 + 8);
        local_24 = *(undefined4 *)(*piVar1 + 0x10);
        bVar3 = true;
        local_40 = 0;
      }
      va3 = piVar1[4];
      uVar2 = piVar1[5];
      if (va3 < uVar2) {
        uVar6 = piVar1[2] & 0x4000;
        if (((piVar1[2] & 0x2000U) == 0) && (uVar6 == 0)) {
          local_44 = **(undefined4 **)*piVar1;
        }
        else {
          local_44 = *(undefined4 *)**(undefined4 **)piVar1[0x10];
        }
        if (((!bVar3) && (va3 <= local_8)) &&
           ((uVar6 == 0 && ((local_40 == 0 && ((piVar1[2] & 0x2000U) == 0)))))) {
          va2 = local_24;
          iVar5 = thunk_FUN_0042f22f(local_2c);
          sprintf(&DAT_00461528,s_Overlap_of_section___s__at_addre_00458fbc,local_44,
                  (int)s_XYLPEDU_00457ff0[iVar5],va2,va3);
          thunk_FUN_00409d88(&DAT_00461528);
        }
        bVar3 = false;
        local_40 = uVar6;
        local_8 = uVar2 - 1;
      }
    }
  }
  return;
}


/* ==== FUN_0041e110 @ 0041e110 ==== */

void FUN_0041e110(void)

{
  int *piVar1;
  uint va0;
  int iVar2;
  bool bVar3;
  bool bVar4;
  undefined4 uVar5;
  uint uVar6;
  longlong lVar7;
  char *local_a4;
  uint local_70;
  int local_68;
  int local_60;
  uint local_5c;
  double local_54;
  int local_48;
  int local_3c;
  int local_34;
  uint local_28;
  int local_24;
  uint local_20;
  int local_1c;
  int local_18;
  uint local_c;
  
  local_20 = DAT_00461f74;
  if ((DAT_0046129c != 0) && (DAT_00457b5c != '\0')) {
    if (DAT_00461f20 == 0) {
      local_18 = FUN_0041f5d6();
      DAT_00461f20 = local_18;
      FUN_0041ebb8(local_18,DAT_0046129c);
    }
    else {
      local_18 = DAT_00461f20;
    }
    FUN_0041d8d1(s_Section_Link_Map_by_Address_00458fec);
    FUN_0041da05();
    local_3c = 4;
    local_34 = 0;
    bVar4 = true;
    bVar3 = false;
    if ((((DAT_00461f44 == 1) || (DAT_00461f44 == 3)) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)
       ) {
      local_60 = 0x22;
    }
    else {
      local_60 = 0x1e;
    }
    local_1c = local_60;
    local_28 = 0;
    local_5c = 0;
    local_c = 0;
    local_54 = 0.0;
    for (local_24 = 0; local_24 < DAT_0046129c; local_24 = local_24 + 1) {
      piVar1 = *(int **)(local_18 + local_24 * 4);
      if ((((piVar1[2] & 0x2000U) == 0) || (DAT_00457b4c != '\0')) &&
         (((piVar1[2] & 0x4000U) == 0 || (DAT_00457b58 != '\0')))) {
        va0 = piVar1[4];
        uVar6 = piVar1[5];
        if (uVar6 != va0) {
          if ((*(int *)(*piVar1 + 8) != local_3c) || (*(int *)(*piVar1 + 0x10) != local_34)) {
            if ((local_3c == 0x1c) || (local_3c == 0x11d)) {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            if ((((DAT_00461f44 == 1) || (DAT_00461f44 == 3)) || (DAT_00461f44 == 4)) ||
               ((DAT_00461f44 == 5 || (bVar3)))) {
              local_68 = 0x22;
            }
            else {
              local_68 = 0x1e;
            }
            local_1c = local_68;
            if (((DAT_00457b6c != '\0') && (local_3c != 4)) &&
               ((local_28 < local_20 && (local_54 < 1.0)))) {
              if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
                sprintf(&DAT_00461528,s__08lX__08lX__10lu_UNUSED_00459020,local_28,local_20,
                        (local_20 - local_28) + 1);
              }
              else if ((((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)) ||
                      (bVar3)) {
                sprintf(&DAT_00461528,s__06lX__06lX__8lu_UNUSED_00459040,local_28,local_20,
                        (local_20 - local_28) + 1);
              }
              else {
                sprintf(&DAT_00461528,s__04lX__04lX__5lu_UNUSED_00459060,local_28,local_20,
                        (local_20 - local_28) + 1);
              }
              FUN_0041d8d1(&DAT_00461528);
              FUN_0041da05();
              DAT_00461528 = 0;
            }
            local_3c = *(int *)(*piVar1 + 8);
            local_34 = *(int *)(*piVar1 + 0x10);
            if ((local_3c == 0x1c) || (local_3c == 0x11d)) {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            if (((DAT_00457b78 == '\0') || (local_3c == 0x1c)) ||
               ((local_3c == 0x11d || ((DAT_00461f44 == 4 && (local_3c == 0)))))) {
              local_70 = DAT_00461f78;
            }
            else {
              local_70 = DAT_00461f74;
            }
            local_20 = local_70;
            bVar4 = true;
            local_c = 0;
            local_28 = 0;
            local_54 = 0.0;
            local_5c = 0;
            FUN_0041da05();
            FUN_0041da05();
            uVar5 = thunk_FUN_0042f22f(local_3c);
            switch(uVar5) {
            case 1:
              FUN_0041d8d1(&DAT_00459084);
              break;
            case 2:
              FUN_0041d8d1(&DAT_00459088);
              break;
            case 3:
              FUN_0041d8d1(&DAT_0045908c);
              break;
            case 4:
              FUN_0041d8d1(&DAT_00459090);
              break;
            case 5:
              FUN_0041d8d1(&DAT_00459094);
              break;
            case 6:
              FUN_0041d8d1(&DAT_00459098);
              break;
            case 7:
              FUN_0041d8d1(&DAT_0045909c);
            }
            FUN_0041d8d1(s_Memory___004590a0);
            sprintf(&DAT_00461528,&DAT_004590ac,local_34);
            FUN_0041d8d1(&DAT_00461528);
            if (local_34 == 0) {
              FUN_0041d8d1(s___default_004590b0);
            }
            else if (local_34 == 1) {
              FUN_0041d8d1(s___low_004590bc);
            }
            else if (local_34 == 2) {
              FUN_0041d8d1(s___high_004590c4);
            }
            FUN_0041d8d1(&DAT_004590cc);
            FUN_0041da05();
            FUN_0041da05();
            if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
              FUN_0041d8d1(s_Start_End_Length_Section_004590d0);
            }
            else if ((((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)) ||
                    (bVar3)) {
              FUN_0041d8d1(s_Start_End_Length_Section_004590fc);
            }
            else {
              FUN_0041d8d1(s_Start_End_Length_Section_00459124);
            }
            FUN_0041da05();
          }
          if (va0 < uVar6) {
            local_48 = uVar6 - va0;
          }
          else {
            local_54 = ((double)local_20 + (double)(uVar6 + 1)) - (double)va0;
            lVar7 = _ftol();
            local_48 = (int)lVar7;
          }
          if ((DAT_00457b6c != '\0') && (local_28 < va0)) {
            if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
              sprintf(&DAT_00461528,s__08lX__08lX__10lu_UNUSED_00459148,local_28,va0 - 1,
                      va0 - local_28);
            }
            else if (((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) ||
                    ((DAT_00461f44 == 5 || (bVar3)))) {
              sprintf(&DAT_00461528,s__06lX__06lX__8lu_UNUSED_00459168,local_28,va0 - 1,
                      va0 - local_28);
            }
            else {
              sprintf(&DAT_00461528,s__04lX__04lX__5lu_UNUSED_00459188,local_28,va0 - 1,
                      va0 - local_28);
            }
            FUN_0041d8d1(&DAT_00461528);
            FUN_0041da05();
            DAT_00461528 = 0;
            if (local_28 < va0 + local_48) {
              local_28 = va0 + local_48;
            }
          }
          iVar2 = piVar1[5];
          uVar6 = piVar1[2] & 0x4000;
          if (local_28 < va0 + local_48) {
            local_28 = va0 + local_48;
          }
          if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
            sprintf(&DAT_00461528,s__08lX__08lX__10lu_004591ac,va0,piVar1[5] - 1U & local_20,
                    local_48);
          }
          else if ((((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)) || (bVar3))
          {
            sprintf(&DAT_00461528,s__06lX__06lX__8lu_004591c8,va0,piVar1[5] - 1U & local_20,local_48
                   );
          }
          else {
            sprintf(&DAT_00461528,s__04lX__04lX__5lu_004591e4,va0,piVar1[5] - 1U & local_20,local_48
                   );
          }
          FUN_0041d8d1(&DAT_00461528);
          if (((piVar1[2] & 0x2000U) == 0) && (uVar6 == 0)) {
            local_a4 = (char *)**(undefined4 **)*piVar1;
          }
          else {
            local_a4 = *(char **)**(undefined4 **)piVar1[0x10];
          }
          strncpy(&DAT_00461528,local_a4,0x10);
          DAT_00461538 = 0;
          FUN_0041d8d1(&DAT_00461528);
          if ((piVar1[2] & 0x1000U) == 0) {
            FUN_0041eb80(local_1c + 0x10);
            FUN_0041d8d1(&DAT_00459204);
          }
          if ((piVar1[2] & 0x2000U) != 0) {
            FUN_0041eb80(local_1c + 0x10);
            if ((piVar1[3] & 0x400U) == 0) {
              if ((piVar1[3] & 0x800U) == 0) {
                FUN_0041d8d1(&DAT_00459210);
              }
              else {
                FUN_0041d8d1(&DAT_0045920c);
              }
            }
            else {
              FUN_0041d8d1(&DAT_00459208);
            }
            if ((piVar1[2] & 0x20000U) != 0) {
              FUN_0041d8d1(&DAT_00459214);
            }
          }
          if (uVar6 != 0) {
            FUN_0041eb80(local_1c + 0x10);
            FUN_0041d8d1(&DAT_00459218);
          }
          if (((DAT_00461248 == '\0') && (!bVar4)) &&
             ((va0 <= local_c &&
              ((((DAT_0046122c == '\0' && (uVar6 == 0)) && (local_5c == 0)) &&
               ((piVar1[2] & 0x2000U) == 0)))))) {
            FUN_0041eb80(local_1c + 0x10);
            FUN_0041d8d1(s__Overlap__0045921c);
          }
          bVar4 = false;
          FUN_0041da05();
          local_5c = uVar6;
          local_c = iVar2 - 1;
        }
      }
    }
    if (((DAT_00457b6c != '\0') && (local_3c != 4)) && ((local_28 < local_20 && (local_54 < 1.0))))
    {
      if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
        sprintf(&DAT_00461528,s__08lX__08lX__10lu_UNUSED_00459228,local_28,local_20,
                (local_20 - local_28) + 1);
      }
      else if ((((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)) || (bVar3)) {
        sprintf(&DAT_00461528,s__06lX__06lX__8lu_UNUSED_00459248,local_28,local_20,
                (local_20 - local_28) + 1);
      }
      else {
        sprintf(&DAT_00461528,s__04lX__04lX__5lu_UNUSED_00459268,local_28,local_20,
                (local_20 - local_28) + 1);
      }
      FUN_0041d8d1(&DAT_00461528);
      FUN_0041da05();
      DAT_00461528 = 0;
    }
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
  }
  return;
}


/* ==== FUN_0041eb80 @ 0041eb80 ==== */

void __cdecl FUN_0041eb80(int param_1)

{
  if (DAT_00457bc0 < param_1) {
    while (DAT_00457bc0 < param_1) {
      FUN_0041d8d1(&DAT_00459290);
    }
  }
  else {
    FUN_0041d8d1(&DAT_0045928c);
  }
  return;
}


/* ==== FUN_0041ebb8 @ 0041ebb8 ==== */

void __cdecl FUN_0041ebb8(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_0041ebe0;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_0041ebe0 @ 0041ebe0 ==== */

int __cdecl FUN_0041ebe0(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = FUN_00421f79(*(int *)(*param_1 + 8),*(int *)(*param_2 + 8));
  if (iVar3 == 0) {
    if (*(uint *)(*param_1 + 0x10) < *(uint *)(*param_2 + 0x10)) {
      iVar3 = -1;
    }
    else if (*(uint *)(*param_2 + 0x10) < *(uint *)(*param_1 + 0x10)) {
      iVar3 = 1;
    }
    else if ((uint)param_1[4] < (uint)param_2[4]) {
      iVar3 = -1;
    }
    else if ((uint)param_2[4] < (uint)param_1[4]) {
      iVar3 = 1;
    }
    else if ((uint)param_2[5] < (uint)param_1[5]) {
      iVar3 = -1;
    }
    else if ((uint)param_1[5] < (uint)param_2[5]) {
      iVar3 = 1;
    }
    else {
      iVar3 = strcmp((char *)**(undefined4 **)*param_1,(char *)**(undefined4 **)*param_2);
      if (iVar3 == 0) {
        uVar1 = param_1[2];
        uVar2 = param_2[2];
        if (((uVar1 & 0x1000) == 0) || ((uVar2 & 0x1000) != 0)) {
          if (((uVar1 & 0x1000) == 0) && ((uVar2 & 0x1000) != 0)) {
            iVar3 = 1;
          }
          else {
            iVar3 = uVar1 - uVar2;
          }
        }
        else {
          iVar3 = -1;
        }
      }
    }
  }
  return iVar3;
}


/* ==== FUN_0041ed36 @ 0041ed36 ==== */

void __cdecl FUN_0041ed36(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_0041ed5e;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_0041ed5e @ 0041ed5e ==== */

undefined4 __cdecl FUN_0041ed5e(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10);
  uVar3 = *(int *)(param_2 + 0x14) - *(int *)(param_2 + 0x10);
  if (uVar2 < uVar3) {
    uVar1 = 1;
  }
  else if (uVar3 < uVar2) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* ==== FUN_0041eda4 @ 0041eda4 ==== */

void __cdecl FUN_0041eda4(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_0041edcc;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_0041edcc @ 0041edcc ==== */

int __cdecl FUN_0041edcc(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)*param_1 + 4) - *(int *)(*(int *)*param_2 + 4);
  if (iVar1 == 0) {
    iVar1 = param_1[1] - param_2[1];
  }
  return iVar1;
}


/* ==== FUN_0041ee04 @ 0041ee04 ==== */

void __cdecl FUN_0041ee04(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_0041ee2c;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_0041ee2c @ 0041ee2c ==== */

int __cdecl FUN_0041ee2c(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x14) - *(int *)(param_2 + 0x14);
  if (iVar1 == 0) {
    iVar1 = FUN_004221bc(*(int *)(param_1 + 0xc),*(int *)(param_2 + 0xc));
  }
  return iVar1;
}


/* ==== FUN_0041ee64 @ 0041ee64 ==== */

void FUN_0041ee64(void)

{
  char *b;
  int *piVar1;
  uint va0;
  uint uVar2;
  int iVar3;
  undefined4 va0_00;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  longlong lVar10;
  uint local_58;
  int local_48;
  int local_44;
  int local_2c;
  int local_28;
  
  if ((DAT_0046129c != 0) && (DAT_00457b60 != '\0')) {
    if (DAT_00461f20 == 0) {
      DAT_00461f20 = FUN_0041f5d6();
    }
    iVar7 = DAT_00461f20;
    FUN_0041f45b(DAT_00461f20,DAT_0046129c);
    FUN_0041d8d1(s_Section_Link_Map_by_Name_00459294);
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041d8d1(s_Section_Memory_Start_End_Length_004592c8);
    FUN_0041da05();
    for (local_28 = 0; local_28 < DAT_0046129c; local_28 = local_28 + local_2c) {
      strncpy(&DAT_00461528,(char *)**(undefined4 **)**(undefined4 **)(iVar7 + local_28 * 4),0x10);
      DAT_00461538 = 0;
      FUN_0041d8d1(&DAT_00461528);
      bVar4 = true;
      bVar6 = true;
      bVar5 = false;
      b = (char *)**(undefined4 **)**(undefined4 **)(iVar7 + local_28 * 4);
      local_2c = local_28;
      do {
        local_2c = local_2c + 1;
        if (*(int *)(iVar7 + local_2c * 4) == 0) break;
      } while ((char *)**(undefined4 **)**(undefined4 **)(iVar7 + local_2c * 4) == b);
      local_2c = local_2c - local_28;
      if (1 < local_2c) {
        FUN_0041ebb8(iVar7 + local_28 * 4,local_2c);
      }
      for (local_48 = 0; local_48 < local_2c; local_48 = local_48 + 1) {
        piVar1 = *(int **)(iVar7 + (local_28 + local_48) * 4);
        if ((((piVar1[2] & 0x2000U) == 0) || (DAT_00457b4c != '\0')) &&
           (((piVar1[2] & 0x4000U) == 0 || (DAT_00457b58 != '\0')))) {
          va0 = piVar1[4];
          uVar2 = piVar1[5];
          if (uVar2 != va0) {
            iVar3 = *(int *)(*piVar1 + 8);
            va0_00 = *(undefined4 *)(*piVar1 + 0x10);
            if ((((DAT_00457b78 == '\0') || (iVar3 == 0x1c)) || (iVar3 == 0x11d)) ||
               ((DAT_00461f44 == 4 && (iVar3 == 0)))) {
              local_58 = DAT_00461f78;
            }
            else {
              local_58 = DAT_00461f74;
            }
            if (va0 < uVar2) {
              local_44 = uVar2 - va0;
            }
            else {
              lVar10 = _ftol();
              local_44 = (int)lVar10;
            }
            local_58 = piVar1[5] - 1U & local_58;
            bVar6 = false;
            if (((piVar1[2] & 0x6000U) != 0) &&
               ((**(char **)**(undefined4 **)piVar1[0x10] != *b ||
                (iVar8 = strcmp(*(char **)**(undefined4 **)piVar1[0x10],b), iVar8 != 0)))) {
              if ((bVar4) && (bVar4 = false, !bVar5)) {
                FUN_0041da05();
              }
              FUN_0041eb80(3);
              strncpy(&DAT_00461528,*(char **)**(undefined4 **)piVar1[0x10],0xe);
              DAT_00461536 = 0;
              FUN_0041d8d1(&DAT_00461528);
            }
            bVar5 = true;
            FUN_0041eb80(0x12);
            if ((piVar1[2] & 0x2000U) == 0) {
              if ((piVar1[2] & 0x4000U) == 0) {
                if ((piVar1[2] & 0x1000U) == 0) {
                  FUN_0041d8d1(&DAT_00459320);
                }
              }
              else {
                FUN_0041d8d1(&DAT_0045931c);
              }
            }
            else {
              if ((piVar1[3] & 0x400U) == 0) {
                if ((piVar1[3] & 0x800U) == 0) {
                  FUN_0041d8d1(&DAT_00459314);
                }
                else {
                  FUN_0041d8d1(&DAT_00459310);
                }
              }
              else {
                FUN_0041d8d1(&DAT_0045930c);
              }
              if ((piVar1[2] & 0x20000U) != 0) {
                FUN_0041d8d1(&DAT_00459318);
              }
            }
            FUN_0041eb80(0x18);
            uVar9 = thunk_FUN_0042f22f(iVar3);
            switch(uVar9) {
            case 1:
              FUN_0041d8d1(&DAT_00459324);
              break;
            case 2:
              FUN_0041d8d1(&DAT_00459328);
              break;
            case 3:
              FUN_0041d8d1(&DAT_0045932c);
              break;
            case 4:
              FUN_0041d8d1(&DAT_00459330);
              break;
            case 5:
              FUN_0041d8d1(&DAT_00459334);
              break;
            case 6:
              FUN_0041d8d1(&DAT_00459338);
              break;
            case 7:
              FUN_0041d8d1(&DAT_0045933c);
            }
            sprintf(&DAT_00461528,s___ld__00459340,va0_00);
            FUN_0041d8d1(&DAT_00461528);
            FUN_0041eb80(0x25);
            if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
              sprintf(&DAT_00461528,s__08lX__08lX__10lu_00459348,va0,local_58,local_44);
            }
            else if ((((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)) ||
                    ((iVar3 == 0x1c || (iVar3 == 0x11d)))) {
              sprintf(&DAT_00461528,s__06lX__06lX__8lu_0045935c,va0,local_58,local_44);
            }
            else {
              sprintf(&DAT_00461528,s__04lX__04lX__5lu_00459378,va0,local_58,local_44);
            }
            FUN_0041d8d1(&DAT_00461528);
            FUN_0041da05();
          }
        }
      }
      if (bVar6) {
        FUN_0041eb80(0x18);
        FUN_0041d8d1(&DAT_00459398);
        FUN_0041da05();
      }
    }
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
  }
  return;
}


/* ==== FUN_0041f45b @ 0041f45b ==== */

void __cdecl FUN_0041f45b(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_0041f483;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_0041f483 @ 0041f483 ==== */

int __cdecl FUN_0041f483(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = strcmp((char *)**(undefined4 **)*param_1,(char *)**(undefined4 **)*param_2);
  if ((iVar3 == 0) &&
     (iVar3 = FUN_00421f79(*(int *)(*param_1 + 8),*(int *)(*param_2 + 8)), iVar3 == 0)) {
    if (*(uint *)(*param_1 + 0x10) < *(uint *)(*param_2 + 0x10)) {
      iVar3 = -1;
    }
    else if (*(uint *)(*param_2 + 0x10) < *(uint *)(*param_1 + 0x10)) {
      iVar3 = 1;
    }
    else if ((uint)param_1[4] < (uint)param_2[4]) {
      iVar3 = -1;
    }
    else if ((uint)param_2[4] < (uint)param_1[4]) {
      iVar3 = 1;
    }
    else if ((uint)param_2[5] < (uint)param_1[5]) {
      iVar3 = -1;
    }
    else if ((uint)param_1[5] < (uint)param_2[5]) {
      iVar3 = 1;
    }
    else {
      uVar1 = param_1[2];
      uVar2 = param_2[2];
      if (((uVar1 & 0x1000) == 0) || ((uVar2 & 0x1000) != 0)) {
        if (((uVar1 & 0x1000) == 0) && ((uVar2 & 0x1000) != 0)) {
          iVar3 = 1;
        }
        else {
          iVar3 = uVar1 - uVar2;
        }
      }
      else {
        iVar3 = -1;
      }
    }
  }
  return iVar3;
}


/* ==== FUN_0041f5d6 @ 0041f5d6 ==== */

int FUN_0041f5d6(void)

{
  int iVar1;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  if (DAT_0046129c == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = DAT_00461f20;
    if (DAT_00461f20 == 0) {
      iVar1 = thunk_FUN_0042e170(DAT_0046129c * 4 + 4);
      local_14 = 0;
      DAT_00461f20 = iVar1;
      for (local_18 = 0; local_18 < 0x7d3; local_18 = local_18 + 1) {
        for (local_c = *(int *)(&DAT_00463f48 + local_18 * 4); local_c != 0;
            local_c = *(int *)(local_c + 0x10)) {
          for (local_20 = *(int *)(local_c + 8); local_20 != 0; local_20 = *(int *)(local_20 + 0x74)
              ) {
            for (local_8 = *(int *)(local_20 + 0x18); local_8 != 0;
                local_8 = *(int *)(local_8 + 0x44)) {
              *(int *)(iVar1 + local_14 * 4) = local_8;
              local_14 = local_14 + 1;
              *(undefined4 *)(local_8 + 0x3c) = 0;
            }
            for (local_1c = *(int *)(local_20 + 0x1c); local_1c != 0;
                local_1c = *(int *)(local_1c + 0x44)) {
              *(int *)(iVar1 + local_14 * 4) = local_1c;
              local_14 = local_14 + 1;
              *(undefined4 *)(local_1c + 0x3c) = 0;
            }
            for (local_1c = *(int *)(local_20 + 0x20); local_1c != 0;
                local_1c = *(int *)(local_1c + 0x44)) {
              *(int *)(iVar1 + local_14 * 4) = local_1c;
              local_14 = local_14 + 1;
              *(undefined4 *)(local_1c + 0x3c) = 0;
            }
            for (local_1c = *(int *)(local_20 + 0x24); local_1c != 0;
                local_1c = *(int *)(local_1c + 0x44)) {
              *(int *)(iVar1 + local_14 * 4) = local_1c;
              local_14 = local_14 + 1;
              *(undefined4 *)(local_1c + 0x3c) = 0;
            }
          }
        }
      }
      *(undefined4 *)(iVar1 + local_14 * 4) = 0;
    }
  }
  return iVar1;
}


/* ==== FUN_0041f797 @ 0041f797 ==== */

void FUN_0041f797(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  uint uVar5;
  uint local_54;
  uint local_50;
  char *local_4c;
  char *local_48;
  int local_34;
  int local_30;
  int local_1c;
  int local_18;
  
  if ((DAT_004612dc != 0) && (DAT_00457b64 != '\0')) {
    if (DAT_00461f1c == 0) {
      local_18 = thunk_FUN_0042e170(DAT_004612dc << 2);
      local_1c = 0;
      DAT_00461f1c = local_18;
      for (local_30 = 0; local_30 < 0x7d3; local_30 = local_30 + 1) {
        for (local_34 = *(int *)(&DAT_00461ff8 + local_30 * 4); local_34 != 0;
            local_34 = *(int *)(local_34 + 0x60)) {
          *(int *)(local_18 + local_1c * 4) = local_34;
          local_1c = local_1c + 1;
        }
      }
    }
    else {
      local_18 = DAT_00461f1c;
    }
    FUN_0041fecc(local_18,DAT_004612dc);
    FUN_0041d8d1(s_Symbol_Listing_by_Name_004593a0);
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041d8d1(s_Name_Type_Value_Section_Attribut_004593d4);
    FUN_0041da05();
    bVar4 = true;
    for (local_1c = 0; local_1c < DAT_004612dc; local_1c = local_1c + 1) {
      puVar1 = *(undefined4 **)(local_18 + local_1c * 4);
      uVar2 = puVar1[10];
      if ((uVar2 & 0x20000) != 0) {
        puVar1[0xc] = 4;
        puVar1[0xb] = 4;
        puVar1[0xd] = 0;
        puVar1[0xe] = 0;
      }
      if ((((puVar1[0x12] != 0) || ((uVar2 & 0x20000) != 0)) &&
          ((iVar3 = puVar1[0xb], DAT_00457b50 != '\0' || (iVar3 != 4)))) &&
         ((DAT_00457b54 != '\0' || ((uVar2 & 0xc0) != 0)))) {
        bVar4 = false;
        uVar5 = strlen((char *)*puVar1);
        if ((uVar5 < 0x11) || (DAT_004611e0 != 1)) {
          strncpy(&DAT_00461528,(char *)*puVar1,0x10);
          DAT_00461538 = 0;
          FUN_0041d8d1(&DAT_00461528);
        }
        else {
          uVar5 = strlen((char *)*puVar1);
          if (uVar5 < 0x200) {
            if ((int)DAT_004611e4 < 1) {
              strcpy(&DAT_00461528,(char *)*puVar1);
            }
            else {
              strncpy(&DAT_00461528,(char *)*puVar1,DAT_004611e4);
            }
          }
          else {
            strncpy(&DAT_00461528,(char *)*puVar1,0x1ff);
            DAT_00461727 = 0;
          }
          FUN_0041d8d1(&DAT_00461528);
          FUN_0041da05();
        }
        FUN_0041feae(0x12);
        if ((uVar2 & 0x200) == 0) {
          if ((uVar2 & 0x100) == 0) {
            FUN_0041d8d1(&DAT_00459424);
          }
          else {
            FUN_0041d8d1(&DAT_00459420);
          }
        }
        else {
          FUN_0041d8d1(&DAT_0045941c);
        }
        FUN_0041eb80(0x18);
        if (iVar3 < 0x1d) {
          if (iVar3 == 0x1c) {
            FUN_0041d8d1(&DAT_00459438);
          }
          else {
            switch(iVar3) {
            case 0:
              FUN_0041d8d1(&DAT_00459434);
              break;
            case 1:
              FUN_0041d8d1(&DAT_00459428);
              break;
            case 2:
              FUN_0041d8d1(&DAT_0045942c);
              break;
            case 3:
              FUN_0041d8d1(&DAT_00459430);
              break;
            default:
switchD_0041faaf_default:
              FUN_0041d8d1(&DAT_00459444);
            }
          }
        }
        else if (iVar3 == 0x11d) {
          FUN_0041d8d1(&DAT_0045943c);
        }
        else {
          if (iVar3 != 0x11f) goto switchD_0041faaf_default;
          FUN_0041d8d1(&DAT_00459440);
        }
        if (iVar3 == 4) {
          local_48 = DAT_00461fb8;
        }
        else {
          if (((DAT_00457b78 == '\0') || (iVar3 == 0x1c)) || (iVar3 == 0x11d)) {
            local_4c = s__08lX_00457c10;
          }
          else {
            local_4c = DAT_00461fbc;
          }
          local_48 = local_4c;
        }
        if (iVar3 == 4) {
          local_50 = DAT_00461f6c;
        }
        else {
          if (((DAT_00457b78 == '\0') || (iVar3 == 0x1c)) || (iVar3 == 0x11d)) {
            local_54 = DAT_00461f78;
          }
          else {
            local_54 = DAT_00461f74;
          }
          local_50 = local_54;
        }
        if ((uVar2 & 0x200) == 0) {
          if ((uVar2 & 0x100) != 0) {
            if ((uVar2 & 0x800) == 0) {
              sprintf(&DAT_00461528,local_48,puVar1[4] & local_50);
            }
            else if (((DAT_00461f44 == 4) || (DAT_00461f44 == 6)) && (iVar3 == 0)) {
              sprintf(&DAT_00461528,local_48,
                      (puVar1[3] << ((byte)DAT_00461f58 & 0x1f) | puVar1[4]) & DAT_00461f78);
            }
            else if ((DAT_00461f44 == 7) && ((iVar3 == 0 || (iVar3 == 4)))) {
              sprintf(&DAT_00461528,local_48,
                      (puVar1[3] << ((byte)DAT_00461f58 & 0x1f) | puVar1[4]) & 0xfffffff);
            }
            else {
              sprintf(&DAT_00461528,local_48,puVar1[3] & local_50);
              uVar5 = strlen(&DAT_00461528);
              sprintf(&DAT_00461528 + uVar5,local_48,puVar1[4] & local_50);
            }
          }
        }
        else {
          thunk_FUN_004302d1((uint *)&DAT_00461528,(uint *)s____6E_00459448,puVar1[2],puVar1[3]);
        }
        FUN_0041d8d1(&DAT_00461528);
        FUN_0041eb80(0x2c);
        if ((uVar2 & 0x20000) == 0) {
          strncpy(&DAT_00461528,*(char **)**(undefined4 **)puVar1[0x12],0x10);
        }
        else {
          DAT_00461528 = 0;
        }
        DAT_00461538 = 0;
        FUN_0041d8d1(&DAT_00461528);
        if ((uVar2 & 0x1000) == 0) {
          FUN_0041eb80(0x3e);
          FUN_0041d8d1(&DAT_00459454);
        }
        else {
          FUN_0041eb80(0x3e);
          FUN_0041d8d1(&DAT_00459450);
        }
        if ((uVar2 & 0x20) == 0) {
          if ((uVar2 & 0x80) == 0) {
            if ((uVar2 & 0x40) != 0) {
              FUN_0041eb80(0x3e);
              FUN_0041d8d1(s_GLOBAL_00459468);
            }
          }
          else {
            FUN_0041eb80(0x3e);
            FUN_0041d8d1(s_EXTERN_00459460);
          }
        }
        else {
          FUN_0041eb80(0x3e);
          FUN_0041d8d1(s_LOCAL_00459458);
        }
        if ((uVar2 & 0x2000) != 0) {
          FUN_0041eb80(0x3e);
          FUN_0041d8d1(s_BUFFER_00459470);
        }
        if ((uVar2 & 0x4000) != 0) {
          FUN_0041eb80(0x3e);
          FUN_0041d8d1(s_OVERLAY_00459478);
        }
        FUN_0041da05();
      }
    }
    if (bVar4) {
      FUN_0041da05();
      FUN_0041d8d1(s_No_symbols_00459480);
    }
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
  }
  return;
}


/* ==== FUN_0041feae @ 0041feae ==== */

void __cdecl FUN_0041feae(int param_1)

{
  while (DAT_00457bc0 < param_1) {
    FUN_0041d8d1(&DAT_00459490);
  }
  return;
}


/* ==== FUN_0041fecc @ 0041fecc ==== */

void __cdecl FUN_0041fecc(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_0041fef4;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_0041fef4 @ 0041fef4 ==== */

int __cdecl FUN_0041fef4(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  float10 fVar2;
  double local_20;
  double local_c;
  
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  if (iVar1 == 0) {
    if ((param_1[0x12] == 0) && (param_2[0x12] == 0)) {
      iVar1 = 0;
    }
    else {
      if ((param_1[0x12] != 0) || (param_2[0x12] != 0)) {
        if (param_2[0x12] == 0) {
          return 1;
        }
        if (param_1[0x12] == 0) {
          return -1;
        }
        if (param_1[0x12] != param_2[0x12]) {
          return *(int *)(**(int **)param_1[0x12] + 4) - *(int *)(**(int **)param_2[0x12] + 4);
        }
      }
      if ((param_1[10] & 0x200) == 0) {
        if ((param_1[10] & 0x800) == 0) {
          if (param_1[0xb] == 4) {
            fVar2 = thunk_FUN_0040848c(param_1[4]);
            local_20 = (double)fVar2;
          }
          else {
            fVar2 = thunk_FUN_004084f1(0,param_1[4]);
            local_20 = (double)fVar2;
          }
        }
        else {
          fVar2 = thunk_FUN_004084f1(param_1[3],param_1[4]);
          local_20 = (double)fVar2;
        }
      }
      else {
        local_20 = *(double *)(param_1 + 2);
      }
      if ((param_2[10] & 0x200) == 0) {
        if ((param_2[10] & 0x800) == 0) {
          if (param_2[0xb] == 4) {
            fVar2 = thunk_FUN_0040848c(param_2[4]);
            local_c = (double)fVar2;
          }
          else {
            fVar2 = thunk_FUN_004084f1(0,param_2[4]);
            local_c = (double)fVar2;
          }
        }
        else {
          fVar2 = thunk_FUN_004084f1(param_2[3],param_2[4]);
          local_c = (double)fVar2;
        }
      }
      else {
        local_c = *(double *)(param_2 + 2);
      }
      if (0.0 <= local_20 - local_c) {
        if (local_20 - local_c <= 0.0) {
          iVar1 = 0;
        }
        else {
          iVar1 = 1;
        }
      }
      else {
        iVar1 = -1;
      }
    }
  }
  return iVar1;
}


/* ==== FUN_004200d0 @ 004200d0 ==== */

void FUN_004200d0(void)

{
  undefined4 *puVar1;
  int iVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  int local_60;
  uint local_5c;
  uint local_58;
  char *local_54;
  char *local_50;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  
  if ((DAT_004612dc != 0) && (DAT_00457b68 != '\0')) {
    if (DAT_00461f1c == 0) {
      local_20 = thunk_FUN_0042e170(DAT_004612dc << 2);
      local_24 = 0;
      DAT_00461f1c = local_20;
      for (local_38 = 0; local_38 < 0x7d3; local_38 = local_38 + 1) {
        for (local_3c = *(int *)(&DAT_00461ff8 + local_38 * 4); local_3c != 0;
            local_3c = *(int *)(local_3c + 0x60)) {
          *(int *)(local_20 + local_24 * 4) = local_3c;
          local_24 = local_24 + 1;
        }
      }
    }
    else {
      local_20 = DAT_00461f1c;
    }
    FUN_0042062b(local_20,DAT_004612dc);
    FUN_0041d8d1(s_Symbol_Listing_by_Value_00459494);
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
    uVar4 = strlen(s_Value_Name_004594c8);
    do {
      FUN_0041d8d1(s_Value_Name_004594c8);
      if (DAT_004611e0 == 1) break;
    } while ((int)(DAT_00457bbc + uVar4) < DAT_00457bc4);
    FUN_0041da05();
    local_38 = 0;
    bVar3 = true;
    for (local_24 = 0; local_24 < DAT_004612dc; local_24 = local_24 + 1) {
      puVar1 = *(undefined4 **)(local_20 + local_24 * 4);
      uVar5 = puVar1[10];
      if ((uVar5 & 0x20000) != 0) {
        puVar1[0xc] = 4;
        puVar1[0xb] = 4;
        puVar1[0xd] = 0;
        puVar1[0xe] = 0;
      }
      if ((((puVar1[0x12] != 0) || ((uVar5 & 0x20000) != 0)) &&
          ((iVar2 = puVar1[0xb], DAT_00457b50 != '\0' || (iVar2 != 4)))) &&
         ((DAT_00457b54 != '\0' || ((uVar5 & 0xc0) != 0)))) {
        bVar3 = false;
        if (iVar2 == 4) {
          local_50 = DAT_00461fb8;
        }
        else {
          if (((DAT_00457b78 == '\0') || (iVar2 == 0x1c)) || (iVar2 == 0x11d)) {
            local_54 = s__08lX_00457c10;
          }
          else {
            local_54 = DAT_00461fbc;
          }
          local_50 = local_54;
        }
        if (iVar2 == 4) {
          local_58 = DAT_00461f6c;
        }
        else {
          if (((DAT_00457b78 == '\0') || (iVar2 == 0x1c)) || (iVar2 == 0x11d)) {
            local_5c = DAT_00461f78;
          }
          else {
            local_5c = DAT_00461f74;
          }
          local_58 = local_5c;
        }
        if ((uVar5 & 0x200) == 0) {
          if ((uVar5 & 0x100) != 0) {
            if ((uVar5 & 0x800) == 0) {
              sprintf(&DAT_00461528,local_50,puVar1[4] & local_58);
            }
            else if (((DAT_00461f44 == 4) || (DAT_00461f44 == 6)) && (iVar2 == 0)) {
              sprintf(&DAT_00461528,local_50,
                      (puVar1[3] << ((byte)DAT_00461f58 & 0x1f) | puVar1[4]) & DAT_00461f78);
            }
            else if ((DAT_00461f44 == 7) && ((iVar2 == 0 || (iVar2 == 4)))) {
              sprintf(&DAT_00461528,local_50,
                      (puVar1[3] << ((byte)DAT_00461f58 & 0x1f) | puVar1[4]) & 0xfffffff);
            }
            else {
              sprintf(&DAT_00461528,local_50,puVar1[3] & local_58);
              uVar5 = strlen(&DAT_00461528);
              sprintf(&DAT_00461528 + uVar5,local_50,puVar1[4] & local_58);
            }
          }
        }
        else {
          thunk_FUN_004302d1((uint *)&DAT_00461528,(uint *)s____6E_004594f0,puVar1[2],puVar1[3]);
        }
        FUN_0041d8d1(&DAT_00461528);
        FUN_0041eb80(local_38 + 0x13);
        if (DAT_004611e0 == 1) {
          uVar5 = strlen((char *)*puVar1);
          if (uVar5 < 0x200) {
            if ((int)DAT_004611e4 < 1) {
              strcpy(&DAT_00461528,(char *)*puVar1);
            }
            else {
              strncpy(&DAT_00461528,(char *)*puVar1,DAT_004611e4);
            }
          }
          else {
            strncpy(&DAT_00461528,(char *)*puVar1,0x1ff);
            DAT_00461727 = 0;
          }
          FUN_0041d8d1(&DAT_00461528);
          FUN_0041da05();
        }
        else {
          strncpy(&DAT_00461528,(char *)*puVar1,0x10);
          DAT_00461538 = 0;
          FUN_0041d8d1(&DAT_00461528);
          uVar5 = strlen(&DAT_00461528);
          if ((int)uVar5 < 0x11) {
            local_60 = 0x12 - uVar5;
          }
          else {
            local_60 = 2;
          }
          if ((int)(DAT_00457bbc + local_60 + uVar4) < DAT_00457bc4) {
            local_38 = local_38 + uVar4;
            FUN_0041eb80(local_38 + 1);
          }
          else {
            local_38 = 0;
            FUN_0041da05();
          }
        }
      }
    }
    if (bVar3) {
      FUN_0041da05();
      FUN_0041d8d1(s_No_symbols_004594f8);
    }
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
  }
  return;
}


/* ==== FUN_0042062b @ 0042062b ==== */

void __cdecl FUN_0042062b(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_00420653;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_00420653 @ 00420653 ==== */

int __cdecl FUN_00420653(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  float10 fVar2;
  double local_20;
  double local_c;
  
  if (((param_1[0x12] != 0) || ((param_1[10] & 0x20000) != 0)) &&
     ((param_2[0x12] != 0 || ((param_2[10] & 0x20000) != 0)))) {
    if ((param_1[10] & 0x200) == 0) {
      if ((param_1[10] & 0x800) == 0) {
        if (param_1[0xb] == 4) {
          fVar2 = thunk_FUN_0040848c(param_1[4]);
          local_20 = (double)fVar2;
        }
        else {
          fVar2 = thunk_FUN_004084f1(0,param_1[4]);
          local_20 = (double)fVar2;
        }
      }
      else {
        fVar2 = thunk_FUN_004084f1(param_1[3],param_1[4]);
        local_20 = (double)fVar2;
      }
    }
    else {
      local_20 = *(double *)(param_1 + 2);
    }
    if ((param_2[10] & 0x200) == 0) {
      if ((param_2[10] & 0x800) == 0) {
        if (param_2[0xb] == 4) {
          fVar2 = thunk_FUN_0040848c(param_2[4]);
          local_c = (double)fVar2;
        }
        else {
          fVar2 = thunk_FUN_004084f1(0,param_2[4]);
          local_c = (double)fVar2;
        }
      }
      else {
        fVar2 = thunk_FUN_004084f1(param_2[3],param_2[4]);
        local_c = (double)fVar2;
      }
    }
    else {
      local_c = *(double *)(param_2 + 2);
    }
    if (local_20 - local_c < 0.0) {
      return -1;
    }
    if (0.0 < local_20 - local_c) {
      return 1;
    }
  }
  iVar1 = strcmp((char *)*param_1,(char *)*param_2);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  return iVar1;
}


/* ==== FUN_004207e9 @ 004207e9 ==== */

void FUN_004207e9(void)

{
  int *piVar1;
  uint va0;
  undefined4 *puVar2;
  int *piVar3;
  byte bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  longlong lVar14;
  uint local_dc;
  char *local_d8;
  char *local_d4;
  char *local_cc;
  uint local_c8;
  uint local_98;
  uint local_84;
  double local_78;
  int local_6c;
  int local_5c;
  uint local_44;
  int local_40;
  uint local_38;
  int *local_30;
  uint local_2c;
  uint local_18;
  
  if ((DAT_0046129c != 0) && (DAT_00461208 != '\0')) {
    if (DAT_00461f20 == 0) {
      DAT_00461f20 = FUN_0041f5d6();
    }
    iVar8 = DAT_00461f20;
    FUN_0042164c(DAT_00461f20,DAT_0046129c);
    if (DAT_00461f1c != (undefined *)0x0) {
      thunk_FUN_0042e1ce(DAT_00461f1c);
      DAT_00461f1c = (undefined *)0x0;
    }
    if (DAT_00457b70 != '\0') {
      FUN_0042154d();
    }
    FUN_0041d8d1(s_Global_Link_Map_by_Memory_Space_00459508);
    FUN_0041da05();
    local_5c = 4;
    bVar6 = true;
    bVar5 = false;
    if ((((DAT_00461f44 == 1) || (DAT_00461f44 == 3)) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)
       ) {
      bVar4 = 1;
    }
    else {
      bVar4 = 0;
    }
    iVar11 = (-(uint)bVar4 & 3) + 0x2b;
    iVar13 = (-(uint)bVar4 & 6) + 0x46;
    local_44 = 0;
    local_84 = 0;
    local_18 = 0;
    local_38 = DAT_00461f74;
    local_78 = 0.0;
    for (local_40 = 0; local_40 < DAT_0046129c; local_40 = local_40 + 1) {
      piVar1 = *(int **)(iVar8 + local_40 * 4);
      if ((((piVar1[2] & 0x2000U) == 0) || (DAT_00457b4c != '\0')) &&
         (((piVar1[2] & 0x4000U) == 0 || (DAT_00457b58 != '\0')))) {
        va0 = piVar1[4];
        uVar12 = piVar1[5];
        if ((uVar12 != va0) || ((DAT_00457b70 != '\0' && (piVar1[0xf] != 0)))) {
          if (*(int *)(*piVar1 + 8) != local_5c) {
            if ((local_5c == 0x1c) || (local_5c == 0x11d)) {
              bVar5 = true;
            }
            else {
              bVar5 = false;
            }
            if ((((DAT_00457b6c != '\0') && (local_5c != 4)) && (local_44 < local_38)) &&
               (local_78 < 1.0)) {
              if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
                sprintf(&DAT_00461528,s__08lX__08lX_UNUSED_00459540,local_44,local_38);
              }
              if (((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || ((DAT_00461f44 == 5 || (bVar5))))
              {
                sprintf(&DAT_00461528,s__06lX__06lX_UNUSED_00459558,local_44,local_38);
              }
              else {
                sprintf(&DAT_00461528,s__04lX__04lX_UNUSED_00459574,local_44,local_38);
              }
              FUN_0041d8d1(&DAT_00461528);
              FUN_0041da05();
              DAT_00461528 = 0;
            }
            local_5c = *(int *)(*piVar1 + 8);
            if ((local_5c == 0x1c) || (local_5c == 0x11d)) {
              bVar5 = true;
            }
            else {
              bVar5 = false;
            }
            if ((((DAT_00457b78 == '\0') || (local_5c == 0x1c)) || (local_5c == 0x11d)) ||
               ((DAT_00461f44 == 4 && (local_5c == 0)))) {
              local_98 = DAT_00461f78;
            }
            else {
              local_98 = DAT_00461f74;
            }
            local_38 = local_98;
            bVar6 = true;
            local_18 = 0;
            local_44 = 0;
            local_78 = 0.0;
            local_84 = 0;
            FUN_0041da05();
            FUN_0041da05();
            uVar10 = thunk_FUN_0042f22f(local_5c);
            switch(uVar10) {
            case 1:
              FUN_0041d8d1(&DAT_00459590);
              break;
            case 2:
              FUN_0041d8d1(&DAT_00459594);
              break;
            case 3:
              FUN_0041d8d1(&DAT_00459598);
              break;
            case 4:
              FUN_0041d8d1(&DAT_0045959c);
              break;
            case 5:
              FUN_0041d8d1(&DAT_004595a0);
              break;
            case 6:
              FUN_0041d8d1(&DAT_004595a4);
              break;
            case 7:
              FUN_0041d8d1(&DAT_004595a8);
            }
            FUN_0041d8d1(s_Memory_004595ac);
            FUN_0041da05();
            FUN_0041da05();
            if (((DAT_00461f44 == 1) || (DAT_00461f44 == 3)) ||
               ((DAT_00461f44 == 4 || ((DAT_00461f44 == 5 || (bVar5)))))) {
              FUN_0041d8d1(s_Start_End_Section_Counter_Symbol_004595b4);
            }
            else {
              FUN_0041d8d1(s_Start_End_Section_Counter_Symbol_004595fc);
            }
            FUN_0041da05();
          }
          uVar9 = local_18;
          if (uVar12 == va0) {
            local_6c = 0;
          }
          else if (va0 < uVar12) {
            local_6c = uVar12 - va0;
          }
          else {
            local_78 = ((double)local_38 + (double)(uVar12 + 1)) - (double)va0;
            lVar14 = _ftol();
            local_6c = (int)lVar14;
          }
          if ((DAT_00457b6c != '\0') && (local_44 < va0)) {
            if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
              sprintf(&DAT_00461528,s__08lX__08lX_UNUSED_00459644,local_44,va0 - 1);
            }
            else if ((((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || (DAT_00461f44 == 5)) ||
                    (bVar5)) {
              sprintf(&DAT_00461528,s__06lX__06lX_UNUSED_0045965c,local_44,va0 - 1);
            }
            else {
              sprintf(&DAT_00461528,s__04lX__04lX_UNUSED_00459678,local_44,va0 - 1);
            }
            FUN_0041d8d1(&DAT_00461528);
            FUN_0041da05();
            DAT_00461528 = 0;
            if (local_44 < va0 + local_6c) {
              local_44 = va0 + local_6c;
            }
          }
          if (local_6c == 0) {
            local_c8 = piVar1[5];
          }
          else {
            local_c8 = piVar1[5] - 1;
          }
          local_18 = local_c8;
          uVar12 = piVar1[2] & 0x4000;
          if (local_44 < va0 + local_6c) {
            local_44 = va0 + local_6c;
          }
          if (local_6c == 0) {
            FUN_0041eb80((-(uint)bVar4 & 3) + 0x12);
          }
          else {
            if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
              sprintf(&DAT_00461528,s__08lX__08lX_00459694,va0,local_c8 & local_38);
            }
            if (((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || ((DAT_00461f44 == 5 || (bVar5)))) {
              sprintf(&DAT_00461528,s__06lX__06lX_004596a4,va0,local_c8 & local_38);
            }
            else {
              sprintf(&DAT_00461528,s__04lX__04lX_004596b8,va0,local_c8 & local_38);
            }
            FUN_0041d8d1(&DAT_00461528);
          }
          if (((piVar1[2] & 0x2000U) == 0) && (uVar12 == 0)) {
            local_cc = (char *)**(undefined4 **)*piVar1;
          }
          else {
            local_cc = *(char **)**(undefined4 **)piVar1[0x10];
          }
          strncpy(&DAT_00461528,local_cc,0x10);
          DAT_00461538 = 0;
          FUN_0041d8d1(&DAT_00461528);
          FUN_0041eb80((-(uint)bVar4 & 3) + 0x23);
          sprintf(&DAT_00461528,s___6ld_004596cc,*(undefined4 *)(*piVar1 + 0x10));
          FUN_0041d8d1(&DAT_00461528);
          FUN_0041eb80(iVar11);
          if ((((piVar1[2] & 0x1000U) == 0) || ((piVar1[2] & 0x2000U) != 0)) || (uVar12 != 0)) {
            FUN_0041d8d1(&DAT_004596d4);
          }
          if ((piVar1[2] & 0x1000U) == 0) {
            FUN_0041eb80(iVar11);
            FUN_0041d8d1(&DAT_004596d8);
          }
          if ((piVar1[2] & 0x2000U) != 0) {
            FUN_0041eb80(iVar11);
            if ((piVar1[3] & 0x400U) == 0) {
              if ((piVar1[3] & 0x800U) == 0) {
                FUN_0041d8d1(&DAT_004596e4);
              }
              else {
                FUN_0041d8d1(&DAT_004596e0);
              }
            }
            else {
              FUN_0041d8d1(&DAT_004596dc);
            }
            if ((piVar1[2] & 0x20000U) != 0) {
              FUN_0041d8d1(&DAT_004596e8);
            }
          }
          if (uVar12 != 0) {
            FUN_0041eb80(iVar11);
            FUN_0041d8d1(&DAT_004596ec);
          }
          if ((((piVar1[2] & 0x1000U) == 0) || ((piVar1[2] & 0x2000U) != 0)) || (uVar12 != 0)) {
            FUN_0041eb80(iVar11);
            FUN_0041d8d1(&DAT_004596f0);
          }
          if (((DAT_00461248 == '\0') && (!bVar6)) &&
             (((va0 <= uVar9 && (((local_6c != 0 && (DAT_0046122c == '\0')) && (uVar12 == 0)))) &&
              ((local_84 == 0 && ((piVar1[2] & 0x2000U) == 0)))))) {
            FUN_0041eb80(iVar13);
            FUN_0041d8d1(s__Section_Overlap__004596f4);
          }
          bVar6 = false;
          FUN_0041da05();
          local_84 = uVar12;
          if (DAT_00457b70 != '\0') {
            bVar7 = true;
            local_2c = 0;
            local_30 = (int *)piVar1[0xf];
            while (local_30 != (int *)0x0) {
              puVar2 = (undefined4 *)*local_30;
              FUN_0041eb80(iVar11);
              strncpy(&DAT_00461528,(char *)*puVar2,0x10);
              DAT_00461538 = 0;
              FUN_0041d8d1(&DAT_00461528);
              FUN_0041eb80((-(uint)bVar4 & 3) + 0x3d);
              uVar10 = thunk_FUN_0042f22f(local_5c);
              switch(uVar10) {
              case 1:
                FUN_0041d8d1(&DAT_00459708);
                break;
              case 2:
                FUN_0041d8d1(&DAT_0045970c);
                break;
              case 3:
                FUN_0041d8d1(&DAT_00459710);
                break;
              case 4:
                FUN_0041d8d1(&DAT_00459714);
                break;
              case 5:
                FUN_0041d8d1(&DAT_00459718);
                break;
              case 6:
                FUN_0041d8d1(&DAT_0045971c);
                break;
              case 7:
                FUN_0041d8d1(&DAT_00459720);
              }
              if (local_5c == 4) {
                local_d4 = DAT_00461fb4;
              }
              else {
                if (((DAT_00457b78 == '\0') || (local_5c == 0x1c)) || (local_5c == 0x11d)) {
                  local_d8 = s__08lX_00457c10;
                }
                else {
                  local_d8 = DAT_00461fbc;
                }
                local_d4 = local_d8;
              }
              if (local_5c == 4) {
                local_dc = DAT_00461f6c;
              }
              else {
                local_dc = local_38;
              }
              if ((DAT_00461f44 == 4) && (local_5c == 0)) {
                sprintf(&DAT_00461528,local_d4,
                        (puVar2[3] << ((byte)DAT_00461f58 & 0x1f) | puVar2[4]) & local_dc);
              }
              else {
                sprintf(&DAT_00461528,local_d4,puVar2[4] & local_dc);
              }
              FUN_0041d8d1(&DAT_00461528);
              if (bVar7) {
                bVar7 = false;
              }
              else if ((uint)puVar2[4] <= local_2c) {
                FUN_0041eb80(iVar13);
                FUN_0041d8d1(s__Symbol_Overlap__00459724);
              }
              local_2c = puVar2[4];
              FUN_0041da05();
              piVar3 = (int *)local_30[1];
              thunk_FUN_0042e1ce((undefined *)local_30);
              local_30 = piVar3;
            }
            piVar1[0xf] = 0;
          }
        }
      }
    }
    if ((((DAT_00457b6c != '\0') && (local_5c != 4)) && (local_44 < local_38)) && (local_78 < 1.0))
    {
      if ((DAT_00461f44 == 1) || (DAT_00461f44 == 6)) {
        sprintf(&DAT_00461528,s__08lX__08lX_UNUSED_00459738,local_44,local_38);
      }
      else if (((DAT_00461f44 == 3) || (DAT_00461f44 == 4)) || ((DAT_00461f44 == 5 || (bVar5)))) {
        sprintf(&DAT_00461528,s__06lX__06lX_UNUSED_00459750,local_44,local_38);
      }
      else {
        sprintf(&DAT_00461528,s__04lX__04lX_UNUSED_0045976c,local_44,local_38);
      }
      FUN_0041d8d1(&DAT_00461528);
      FUN_0041da05();
      DAT_00461528 = 0;
    }
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
  }
  return;
}


/* ==== FUN_0042154d @ 0042154d ==== */

void FUN_0042154d(void)

{
  int iVar1;
  int *piVar2;
  int local_1c;
  int local_18;
  int *local_14;
  int *local_c;
  
  if (DAT_004612dc != 0) {
    for (local_18 = 0; local_18 < 0x7d3; local_18 = local_18 + 1) {
      for (local_1c = *(int *)(&DAT_00461ff8 + local_18 * 4); local_1c != 0;
          local_1c = *(int *)(local_1c + 0x60)) {
        if (*(int *)(local_1c + 0x2c) != 4) {
          iVar1 = *(int *)(local_1c + 0x48);
          local_c = *(int **)(iVar1 + 0x3c);
          local_14 = (int *)0x0;
          for (; (local_c != (int *)0x0 &&
                 (*(uint *)(*local_c + 0x10) <= *(uint *)(local_1c + 0x10)));
              local_c = (int *)local_c[1]) {
            local_14 = local_c;
          }
          piVar2 = (int *)thunk_FUN_0042e170(8);
          *piVar2 = local_1c;
          if (local_14 == (int *)0x0) {
            piVar2[1] = *(int *)(iVar1 + 0x3c);
            *(int **)(iVar1 + 0x3c) = piVar2;
          }
          else {
            piVar2[1] = local_14[1];
            local_14[1] = (int)piVar2;
          }
        }
      }
    }
  }
  return;
}


/* ==== FUN_0042164c @ 0042164c ==== */

void __cdecl FUN_0042164c(undefined4 param_1,int param_2)

{
  DAT_00461f18 = param_1;
  DAT_00461dc8 = FUN_00421674;
  thunk_FUN_0042e25d(0,param_2 + -1);
  return;
}


/* ==== FUN_00421674 @ 00421674 ==== */

int __cdecl FUN_00421674(int *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = FUN_00421f79(*(int *)(*param_1 + 8),*(int *)(*param_2 + 8));
  if (iVar3 == 0) {
    if ((uint)param_1[4] < (uint)param_2[4]) {
      iVar3 = -1;
    }
    else if ((uint)param_2[4] < (uint)param_1[4]) {
      iVar3 = 1;
    }
    else if ((uint)param_2[5] < (uint)param_1[5]) {
      iVar3 = -1;
    }
    else if ((uint)param_1[5] < (uint)param_2[5]) {
      iVar3 = 1;
    }
    else {
      iVar3 = strcmp((char *)**(undefined4 **)*param_1,(char *)**(undefined4 **)*param_2);
      if (iVar3 == 0) {
        uVar1 = param_1[2];
        uVar2 = param_2[2];
        if (((uVar1 & 0x1000) == 0) || ((uVar2 & 0x1000) != 0)) {
          if (((uVar1 & 0x1000) == 0) && ((uVar2 & 0x1000) != 0)) {
            iVar3 = 1;
          }
          else {
            iVar3 = uVar1 - uVar2;
          }
        }
        else {
          iVar3 = -1;
        }
      }
    }
  }
  return iVar3;
}


/* ==== FUN_00421791 @ 00421791 ==== */

void FUN_00421791(void)

{
  undefined4 *puVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  undefined *puVar5;
  int iVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  char *local_40;
  char *local_3c;
  char *local_38;
  char *local_28;
  char *local_24;
  int local_20;
  int local_1c;
  char *local_18;
  char *local_14;
  int local_c;
  char *pcVar7;
  
  if (DAT_004612e0 != DAT_004612e4) {
    if (DAT_00461f24 != (undefined *)0x0) {
      thunk_FUN_0042e1ce(DAT_00461f24);
    }
    puVar5 = (undefined *)thunk_FUN_0042e170(DAT_004612e0 << 2);
    local_1c = 0;
    DAT_00461f24 = puVar5;
    for (local_20 = 0; local_20 < 0x7d3; local_20 = local_20 + 1) {
      for (local_c = *(int *)(&DAT_00465e98 + local_20 * 4); local_c != 0;
          local_c = *(int *)(local_c + 0x18)) {
        *(int *)(puVar5 + local_1c * 4) = local_c;
        local_1c = local_1c + 1;
      }
    }
    FUN_00421ec7(puVar5,DAT_004612e0);
    fprintf(DAT_00461f34,s_Unresolved_Externals__00459788);
    local_24 = &DAT_0046131c;
    local_18 = &DAT_0046131c;
    bVar3 = true;
    bVar2 = true;
    for (local_1c = 0; local_1c < DAT_004612e0; local_1c = local_1c + 1) {
      puVar1 = *(undefined4 **)(puVar5 + local_1c * 4);
      if ((puVar1[1] & 0x100) == 0) {
        if ((*local_18 != *(char *)*puVar1) ||
           (iVar6 = strcmp(local_18,(char *)*puVar1), iVar6 != 0)) {
          if (bVar2) {
            bVar2 = false;
          }
          else {
            fprintf(DAT_00461f34,&DAT_004597a4);
          }
          local_18 = (char *)*puVar1;
          fprintf(DAT_00461f34,&DAT_004597a8,local_18);
          bVar3 = true;
        }
        if (puVar1[2] == 0) {
          local_14 = s_command_line_004597b0;
          local_28 = s_command_line_004597b0;
        }
        else {
          if (DAT_00461260 == '\0') {
            local_38 = *(char **)puVar1[2];
          }
          else {
            local_38 = thunk_FUN_0042e468(*(char **)puVar1[2]);
          }
          local_28 = local_38;
          if (*(int *)puVar1[3] == 0) {
            local_3c = *(char **)puVar1[2];
          }
          else {
            local_3c = *(char **)puVar1[3];
          }
          if (DAT_00461260 == '\0') {
            local_40 = local_3c;
          }
          else {
            local_40 = thunk_FUN_0042e468(local_3c);
          }
          local_14 = local_40;
          if (DAT_00461260 != '\0') {
            cVar4 = strrchr(local_38,0x2e);
            pcVar7 = (char *)CONCAT31(extraout_var,cVar4);
            if (((pcVar7 != (char *)0x0) && (*pcVar7 == DAT_004597c0)) &&
               (iVar6 = strcmp(pcVar7,&DAT_004597c8), iVar6 == 0)) {
              strcpy(pcVar7,&DAT_00457fd8);
            }
            cVar4 = strrchr(local_40,0x2e);
            pcVar7 = (char *)CONCAT31(extraout_var_00,cVar4);
            if (((pcVar7 != (char *)0x0) && (*pcVar7 == DAT_004597d0)) &&
               (iVar6 = strcmp(pcVar7,&DAT_004597d8), iVar6 == 0)) {
              strcpy(pcVar7,&DAT_00457fd8);
            }
          }
        }
        if (((bVar3) || (*local_24 != *local_14)) || (iVar6 = strcmp(local_24,local_14), iVar6 != 0)
           ) {
          local_24 = local_14;
          if (bVar3) {
            bVar3 = false;
            fprintf(DAT_00461f34,&DAT_004597e4,local_28);
          }
          else {
            fprintf(DAT_00461f34,&DAT_004597e0,local_28);
          }
          if ((puVar1[2] != 0) && ((*(uint *)(puVar1[2] + 4) & 2) != 0)) {
            fprintf(DAT_00461f34,&DAT_004597e8,local_14);
          }
        }
      }
    }
    fprintf(DAT_00461f34,&DAT_004597f0);
  }
  return;
}


/* ==== FUN_00421b2a @ 00421b2a ==== */

void FUN_00421b2a(void)

{
  undefined4 *puVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  undefined *puVar5;
  int iVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  char *local_40;
  char *local_3c;
  char *local_38;
  char *local_28;
  char *local_24;
  int local_20;
  int local_1c;
  char *local_18;
  char *local_14;
  int local_c;
  char *pcVar7;
  
  if (DAT_004612e0 != DAT_004612e4) {
    if (DAT_00461f24 != (undefined *)0x0) {
      thunk_FUN_0042e1ce(DAT_00461f24);
    }
    puVar5 = (undefined *)thunk_FUN_0042e170(DAT_004612e0 << 2);
    local_1c = 0;
    DAT_00461f24 = puVar5;
    for (local_20 = 0; local_20 < 0x7d3; local_20 = local_20 + 1) {
      for (local_c = *(int *)(&DAT_00465e98 + local_20 * 4); local_c != 0;
          local_c = *(int *)(local_c + 0x18)) {
        *(int *)(puVar5 + local_1c * 4) = local_c;
        local_1c = local_1c + 1;
      }
    }
    FUN_00421ec7(puVar5,DAT_004612e0);
    FUN_0041d8d1(s_Unresolved_Externals__004597f4);
    FUN_0041da05();
    FUN_0041da05();
    local_24 = &DAT_0046131c;
    local_18 = &DAT_0046131c;
    bVar3 = true;
    bVar2 = true;
    for (local_1c = 0; local_1c < DAT_004612e0; local_1c = local_1c + 1) {
      puVar1 = *(undefined4 **)(puVar5 + local_1c * 4);
      if ((puVar1[1] & 0x100) == 0) {
        if ((*local_18 != *(char *)*puVar1) ||
           (iVar6 = strcmp(local_18,(char *)*puVar1), iVar6 != 0)) {
          if (bVar2) {
            bVar2 = false;
          }
          else {
            FUN_0041d8d1(&DAT_0045980c);
            FUN_0041da05();
          }
          local_18 = (char *)*puVar1;
          FUN_0041d8d1(local_18);
          FUN_0041d8d1(&DAT_00459810);
          bVar3 = true;
        }
        if (puVar1[2] == 0) {
          local_14 = s_command_line_00459814;
          local_28 = s_command_line_00459814;
        }
        else {
          if (DAT_00461260 == '\0') {
            local_38 = *(char **)puVar1[2];
          }
          else {
            local_38 = thunk_FUN_0042e468(*(char **)puVar1[2]);
          }
          local_28 = local_38;
          if (*(int *)puVar1[3] == 0) {
            local_3c = *(char **)puVar1[2];
          }
          else {
            local_3c = *(char **)puVar1[3];
          }
          if (DAT_00461260 == '\0') {
            local_40 = local_3c;
          }
          else {
            local_40 = thunk_FUN_0042e468(local_3c);
          }
          local_14 = local_40;
          if (DAT_00461260 != '\0') {
            cVar4 = strrchr(local_38,0x2e);
            pcVar7 = (char *)CONCAT31(extraout_var,cVar4);
            if (((pcVar7 != (char *)0x0) && (*pcVar7 == DAT_00459824)) &&
               (iVar6 = strcmp(pcVar7,&DAT_0045982c), iVar6 == 0)) {
              strcpy(pcVar7,&DAT_00457fd8);
            }
            cVar4 = strrchr(local_40,0x2e);
            pcVar7 = (char *)CONCAT31(extraout_var_00,cVar4);
            if (((pcVar7 != (char *)0x0) && (*pcVar7 == DAT_00459834)) &&
               (iVar6 = strcmp(pcVar7,&DAT_0045983c), iVar6 == 0)) {
              strcpy(pcVar7,&DAT_00457fd8);
            }
          }
        }
        if (((bVar3) || (*local_24 != *local_14)) || (iVar6 = strcmp(local_24,local_14), iVar6 != 0)
           ) {
          local_24 = local_14;
          if (bVar3) {
            bVar3 = false;
          }
          else {
            FUN_0041d8d1(&DAT_00459844);
          }
          FUN_0041d8d1(local_28);
          if ((puVar1[2] != 0) && ((*(uint *)(puVar1[2] + 4) & 2) != 0)) {
            FUN_0041d8d1(&DAT_00459848);
            FUN_0041d8d1(local_14);
            FUN_0041d8d1(&DAT_0045984c);
          }
        }
      }
    }
    FUN_0041d8d1(&DAT_00459850);
    FUN_0041da05();
    FUN_0041da05();
    FUN_0041da05();
  }
  return;
}


