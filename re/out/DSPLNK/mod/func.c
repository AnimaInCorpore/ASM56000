/* func: 13 functions from DSPLNK */

/* ==== FUN_004128e0 @ 004128e0 ==== */

uint * __cdecl FUN_004128e0(uint *param_1)

{
  char cVar1;
  uint local_1c;
  uint local_18;
  uint local_14;
  char local_c [8];
  int iVar2;
  
  local_14 = 0;
  while( true ) {
    if (__mb_cur_max < 2) {
      local_18 = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 0x107;
    }
    else {
      local_18 = _isctype((int)*DAT_00461d68,0x107);
    }
    if (((local_18 == 0) && (*DAT_00461d68 != '_')) || (6 < local_14)) break;
    if (__mb_cur_max < 2) {
      local_1c = *(ushort *)(_pctype + *DAT_00461d68 * 2) & 1;
    }
    else {
      local_1c = _isctype((int)*DAT_00461d68,1);
    }
    if (local_1c == 0) {
      cVar1 = *DAT_00461d68;
    }
    else {
      iVar2 = tolower((int)*DAT_00461d68);
      cVar1 = (char)iVar2;
    }
    local_c[local_14] = cVar1;
    local_14 = local_14 + 1;
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
  }
  local_c[local_14] = '\0';
  if (*DAT_00461d68 == '(') {
    *DAT_00461d6c = *DAT_00461d68;
    DAT_00461d6c = DAT_00461d6c + 1;
    DAT_00461d68 = DAT_00461d68 + 1;
    iVar2 = thunk_FUN_0042e1df(local_c,0x458278,DAT_00458320,0xc,FUN_00412ce0);
    if (iVar2 == 0) {
      thunk_FUN_00409bfd(s_Invalid_function_name_00456570,local_c);
      thunk_FUN_0040ca80((undefined *)param_1);
      param_1 = (uint *)0x0;
    }
    else {
      switch(*(undefined1 *)(iVar2 + 4)) {
      case 1:
        param_1 = FUN_00412d95((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 2:
        param_1 = (uint *)FUN_004133da((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 3:
        param_1 = (uint *)FUN_004136d0((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 4:
        param_1 = FUN_00413290((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 5:
        param_1 = FUN_00413acf((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 6:
      case 7:
        thunk_FUN_004098b0(s_Branch_optimization_sequence_fai_00456588);
        break;
      case 8:
      case 9:
        param_1 = FUN_00412f0d(param_1,(int)*(char *)(iVar2 + 4));
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 10:
        param_1 = FUN_004130a7((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 0xb:
        param_1 = (uint *)FUN_004133aa((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 0xc:
        param_1 = (uint *)FUN_00413832((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 0xd:
        param_1 = (uint *)FUN_00412d06((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      case 0xe:
        param_1 = (uint *)FUN_00412d46((undefined *)param_1);
        if (param_1 == (uint *)0x0) {
          return (uint *)0x0;
        }
        break;
      default:
        thunk_FUN_004098b0(s_Invalid_function_type_004565b0);
      }
      if (*DAT_00461d68 == ')') {
        *DAT_00461d6c = *DAT_00461d68;
        DAT_00461d6c = DAT_00461d6c + 1;
        DAT_00461d68 = DAT_00461d68 + 1;
      }
      else {
        thunk_FUN_0040ca80((undefined *)param_1);
        thunk_FUN_00409a25(s_Extra_characters_in_function_arg_004565c8);
        param_1 = (uint *)0x0;
      }
    }
  }
  else {
    thunk_FUN_0040ca80((undefined *)param_1);
    thunk_FUN_00409a25(s_Missing_____for_function_00456554);
    param_1 = (uint *)0x0;
  }
  return param_1;
}


/* ==== FUN_00412ce0 @ 00412ce0 ==== */

void __cdecl FUN_00412ce0(char *param_1,undefined4 *param_2)

{
  uint n;
  
  n = strlen((char *)*param_2);
  strncmp(param_1,(char *)*param_2,n);
  return;
}


/* ==== FUN_00412d06 @ 00412d06 ==== */

int __cdecl FUN_00412d06(undefined *param_1)

{
  int *piVar1;
  
  thunk_FUN_0040ca80(param_1);
  piVar1 = thunk_FUN_0040a772();
  if (piVar1 == (int *)0x0) {
    thunk_FUN_0040ca80((undefined *)0x0);
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[2] = piVar1[2] << 1;
  }
  return (int)piVar1;
}


/* ==== FUN_00412d46 @ 00412d46 ==== */

int __cdecl FUN_00412d46(undefined *param_1)

{
  int *piVar1;
  
  thunk_FUN_0040ca80(param_1);
  piVar1 = thunk_FUN_0040a772();
  if (piVar1 == (int *)0x0) {
    thunk_FUN_0040ca80((undefined *)0x0);
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[2] = piVar1[2] << 1;
    piVar1[2] = piVar1[2] + 1;
  }
  return (int)piVar1;
}


/* ==== FUN_00412d95 @ 00412d95 ==== */

undefined4 * __cdecl FUN_00412d95(undefined *param_1)

{
  uint uVar1;
  int *piVar2;
  uint local_8;
  
  local_8 = 0;
  thunk_FUN_0040ca80(param_1);
  piVar2 = thunk_FUN_0040a772();
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2[1] = 0;
    *piVar2 = 0;
    uVar1 = piVar2[2];
    if (((((uVar1 & 0xf000) == 0) || ((uVar1 & 0xf) == 0)) &&
        (((uVar1 & 0xf000) == 0 || ((uVar1 & 0xf0) == 0)))) &&
       (((uVar1 & 0xf00) == 0 || ((uVar1 & 0xf) == 0)))) {
      if (((uVar1 & 0xf00) == 0) || ((uVar1 & 0xf0) == 0)) {
        if ((uVar1 & 0xff00) == 0) {
          if ((uVar1 & 0xff) == 0) {
            thunk_FUN_00409d88(s_Empty_bit_mask_field_00456638);
          }
          else {
            local_8 = uVar1 | 0x2000;
          }
        }
        else {
          local_8 = uVar1 >> 8 | 0x8000;
        }
      }
      else {
        local_8 = uVar1 >> 4 | 0x4000;
      }
      piVar2[1] = 0;
      *piVar2 = 0;
      piVar2[2] = local_8;
      piVar2[4] = 0x100;
      piVar2[8] = 4;
      piVar2[7] = 4;
      piVar2[9] = 0;
      piVar2[10] = 0;
      piVar2[5] = DAT_00461f60;
    }
    else {
      thunk_FUN_00409a25(s_Bit_mask_cannot_span_more_than_e_0045660c);
      thunk_FUN_0040ca80((undefined *)piVar2);
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}


/* ==== FUN_00412f0d @ 00412f0d ==== */

undefined4 * __cdecl FUN_00412f0d(undefined4 *param_1,int param_2)

{
  uint uVar1;
  uint local_8;
  
  thunk_FUN_0040ca80((undefined *)param_1);
  param_1 = thunk_FUN_0040a772();
  if (param_1 == (int *)0x0) {
    thunk_FUN_0040ca80((undefined *)0x0);
    param_1 = (undefined4 *)0x0;
  }
  else if ((param_1[6] & 0x1000) == 0) {
    if (param_1[4] == 0x100) {
      uVar1 = param_1[2];
      while (*DAT_00461d68 == ',') {
        DAT_00461d68 = DAT_00461d68 + 1;
        thunk_FUN_0040ca80((undefined *)param_1);
        param_1 = thunk_FUN_0040a772();
        if (param_1 == (int *)0x0) {
          thunk_FUN_0040ca80((undefined *)0x0);
          return (undefined4 *)0x0;
        }
        if (param_1[4] == 0x100) {
          local_8 = param_1[2];
        }
        else {
          local_8 = 0;
        }
        if (param_2 == 9) {
          if (local_8 < uVar1) {
            uVar1 = local_8;
          }
        }
        else if (uVar1 < local_8) {
          uVar1 = local_8;
        }
      }
      param_1[1] = 0;
      *param_1 = 0;
      param_1[2] = uVar1;
      param_1[4] = 0x100;
      param_1[5] = DAT_00461f60;
      param_1[6] = param_1[6] & 0xffffefff;
      param_1[8] = 4;
      param_1[7] = 4;
      param_1[9] = 0;
      param_1[10] = 0;
    }
    else {
      thunk_FUN_0040ca80((undefined *)param_1);
      thunk_FUN_00409a25(s_Expression_result_must_be_intege_00456670);
      param_1 = (undefined4 *)0x0;
    }
  }
  else {
    thunk_FUN_00409a25(s_Relative_expression_not_allowed_00456650);
    thunk_FUN_0040ca80((undefined *)param_1);
    param_1 = (undefined4 *)0x0;
  }
  return param_1;
}


/* ==== FUN_004130a7 @ 004130a7 ==== */

undefined4 * __cdecl FUN_004130a7(undefined *param_1)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  
  thunk_FUN_0040ca80(param_1);
  piVar2 = thunk_FUN_0040a772();
  if (piVar2 == (int *)0x0) {
    thunk_FUN_0040ca80((undefined *)0x0);
    piVar2 = (int *)0x0;
  }
  else if ((piVar2[6] & 0x1000U) == 0) {
    if (piVar2[4] == 0x100) {
      uVar3 = piVar2[2];
      thunk_FUN_0040ca80((undefined *)piVar2);
      cVar1 = *DAT_00461d68;
      DAT_00461d68 = DAT_00461d68 + 1;
      if (cVar1 == ',') {
        piVar2 = thunk_FUN_0040a772();
        if (piVar2 == (int *)0x0) {
          thunk_FUN_0040ca80((undefined *)0x0);
          piVar2 = (int *)0x0;
        }
        else if ((piVar2[6] & 0x1000U) == 0) {
          if (piVar2[4] == 0x100) {
            piVar2[1] = 0;
            *piVar2 = 0;
            if (piVar2[2] != 0) {
              uVar3 = thunk_FUN_00430ac9(uVar3,piVar2[2],0xffffffff);
            }
            piVar2[2] = uVar3;
            piVar2[4] = 0x100;
            piVar2[5] = DAT_00461f60;
            piVar2[6] = piVar2[6] & 0xffffefff;
            piVar2[8] = 4;
            piVar2[7] = 4;
            piVar2[9] = 0;
            piVar2[10] = 0;
          }
          else {
            thunk_FUN_0040ca80((undefined *)piVar2);
            thunk_FUN_00409a25(s_Expression_result_must_be_intege_00456718);
            piVar2 = (int *)0x0;
          }
        }
        else {
          thunk_FUN_00409a25(s_Relative_expression_not_allowed_004566f8);
          thunk_FUN_0040ca80((undefined *)piVar2);
          piVar2 = (int *)0x0;
        }
      }
      else {
        thunk_FUN_00409a25(s_Syntax_error___expected_comma_004566d8);
        piVar2 = (int *)0x0;
      }
    }
    else {
      thunk_FUN_0040ca80((undefined *)piVar2);
      thunk_FUN_00409a25(s_Expression_result_must_be_intege_004566b4);
      piVar2 = (int *)0x0;
    }
  }
  else {
    thunk_FUN_00409a25(s_Relative_expression_not_allowed_00456694);
    thunk_FUN_0040ca80((undefined *)piVar2);
    piVar2 = (int *)0x0;
  }
  return piVar2;
}


/* ==== FUN_00413290 @ 00413290 ==== */

undefined4 * __cdecl FUN_00413290(undefined *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint local_8;
  
  local_8 = 0;
  thunk_FUN_0040ca80(param_1);
  piVar1 = thunk_FUN_0040a772();
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[1] = 0;
    *piVar1 = 0;
    uVar3 = piVar1[2] & 0xff00;
    uVar2 = piVar1[2] & 0xff;
    if ((uVar3 == 0) || (uVar2 == 0)) {
      if (uVar3 == 0) {
        if (uVar2 == 0) {
          thunk_FUN_00409d88(s_Empty_bit_mask_field_00456768);
        }
        else {
          local_8 = uVar2 << 8;
        }
      }
      else {
        local_8 = uVar3 | 0x80;
      }
      piVar1[1] = 0;
      *piVar1 = 0;
      piVar1[2] = local_8;
      piVar1[4] = 0x100;
      piVar1[8] = 4;
      piVar1[7] = 4;
      piVar1[9] = 0;
      piVar1[10] = 0;
      piVar1[5] = DAT_00461f60;
    }
    else {
      thunk_FUN_00409a25(s_Bit_mask_cannot_span_more_than_e_0045673c);
      thunk_FUN_0040ca80((undefined *)piVar1);
      piVar1 = (int *)0x0;
    }
  }
  return piVar1;
}


/* ==== FUN_004133aa @ 004133aa ==== */

int __cdecl FUN_004133aa(undefined *param_1)

{
  int *piVar1;
  
  thunk_FUN_0040ca80(param_1);
  piVar1 = thunk_FUN_0040a571();
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[4] = 0x4000000;
  }
  return (int)piVar1;
}


/* ==== FUN_004133da @ 004133da ==== */

undefined * __cdecl FUN_004133da(undefined *param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  thunk_FUN_0040ca80(param_1);
  piVar2 = thunk_FUN_0040a571();
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else if (piVar2[4] == 0x100) {
    cVar1 = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    if (cVar1 == ',') {
      iVar3 = thunk_FUN_0040a4ae();
      piVar2[8] = iVar3;
      if (piVar2[8] == -1) {
        thunk_FUN_0040ca80((undefined *)piVar2);
        piVar2 = (int *)0x0;
      }
      else {
        iVar3 = thunk_FUN_0042fc54(piVar2[8]);
        piVar2[7] = iVar3;
        cVar1 = *DAT_00461d68;
        DAT_00461d68 = DAT_00461d68 + 1;
        if (cVar1 == ',') {
          iVar3 = thunk_FUN_0040a4ae();
          piVar2[9] = iVar3;
          if (piVar2[9] == -1) {
            thunk_FUN_0040ca80((undefined *)piVar2);
            piVar2 = (int *)0x0;
          }
          else {
            cVar1 = *DAT_00461d68;
            DAT_00461d68 = DAT_00461d68 + 1;
            if (cVar1 == ',') {
              iVar3 = thunk_FUN_0040a4ae();
              piVar2[0xb] = iVar3;
              if (piVar2[0xb] == -1) {
                thunk_FUN_0040ca80((undefined *)piVar2);
                piVar2 = (int *)0x0;
              }
              else {
                cVar1 = *DAT_00461d68;
                DAT_00461d68 = DAT_00461d68 + 1;
                if (cVar1 == ',') {
                  iVar3 = thunk_FUN_0040a4ae();
                  piVar2[0xc] = iVar3;
                  if (piVar2[0xc] == -1) {
                    thunk_FUN_0040ca80((undefined *)piVar2);
                    piVar2 = (int *)0x0;
                  }
                  else {
                    cVar1 = *DAT_00461d68;
                    DAT_00461d68 = DAT_00461d68 + 1;
                    if (cVar1 == ',') {
                      iVar3 = thunk_FUN_0040a4ae();
                      piVar2[0xd] = iVar3;
                      if (piVar2[0xd] == -1) {
                        thunk_FUN_0040ca80((undefined *)piVar2);
                        piVar2 = (int *)0x0;
                      }
                      else {
                        cVar1 = *DAT_00461d68;
                        DAT_00461d68 = DAT_00461d68 + 1;
                        if (cVar1 == ',') {
                          iVar3 = thunk_FUN_0040a4ae();
                          piVar2[0xe] = iVar3;
                          if (piVar2[0xe] == -1) {
                            thunk_FUN_0040ca80((undefined *)piVar2);
                            piVar2 = (int *)0x0;
                          }
                          else if (*DAT_00461d68 == ',') {
                            DAT_00461d68 = DAT_00461d68 + 1;
                            iVar3 = thunk_FUN_0040a4ae();
                            piVar2[0x10] = iVar3;
                            if (piVar2[0x10] == -1) {
                              thunk_FUN_0040ca80((undefined *)piVar2);
                              piVar2 = (int *)0x0;
                            }
                          }
                        }
                        else {
                          thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456844);
                          thunk_FUN_0040ca80((undefined *)piVar2);
                          piVar2 = (int *)0x0;
                        }
                      }
                    }
                    else {
                      thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456824);
                      thunk_FUN_0040ca80((undefined *)piVar2);
                      piVar2 = (int *)0x0;
                    }
                  }
                }
                else {
                  thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456804);
                  thunk_FUN_0040ca80((undefined *)piVar2);
                  piVar2 = (int *)0x0;
                }
              }
            }
            else {
              thunk_FUN_00409a25(s_Syntax_error___expected_comma_004567e4);
              thunk_FUN_0040ca80((undefined *)piVar2);
              piVar2 = (int *)0x0;
            }
          }
        }
        else {
          thunk_FUN_00409a25(s_Syntax_error___expected_comma_004567c4);
          thunk_FUN_0040ca80((undefined *)piVar2);
          piVar2 = (int *)0x0;
        }
      }
    }
    else {
      thunk_FUN_00409a25(s_Syntax_error___expected_comma_004567a4);
      thunk_FUN_0040ca80((undefined *)piVar2);
      piVar2 = (int *)0x0;
    }
  }
  else {
    thunk_FUN_0040ca80((undefined *)piVar2);
    thunk_FUN_00409a25(s_Expression_result_must_be_intege_00456780);
    piVar2 = (int *)0x0;
  }
  return (undefined *)piVar2;
}


/* ==== FUN_004136d0 @ 004136d0 ==== */

int __cdecl FUN_004136d0(undefined *param_1)

{
  uint uVar1;
  char cVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined3 extraout_var;
  uint uVar5;
  
  thunk_FUN_0040ca80(param_1);
  piVar3 = thunk_FUN_0040a370();
  if (piVar3 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    cVar2 = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    if (cVar2 == ',') {
      uVar5 = piVar3[2];
      thunk_FUN_0040ca80((undefined *)piVar3);
      puVar4 = thunk_FUN_0040a3e6();
      if (puVar4 == (undefined4 *)0x0) {
        piVar3 = (int *)0x0;
      }
      else {
        cVar2 = *DAT_00461d68;
        DAT_00461d68 = DAT_00461d68 + 1;
        if (cVar2 == ',') {
          uVar1 = puVar4[2];
          thunk_FUN_0040ca80((undefined *)puVar4);
          if (uVar1 <= uVar5) {
            cVar2 = strchr(DAT_00461d68,0x2c);
            DAT_00461d68 = (char *)CONCAT31(extraout_var,cVar2);
            if (DAT_00461d68 == (char *)0x0) {
              thunk_FUN_00409a25(s_Syntax_error___expected_comma_004568a4);
              thunk_FUN_0040ca80((undefined *)puVar4);
              return 0;
            }
            DAT_00461d68 = (char *)((int)DAT_00461d68 + 1);
          }
          piVar3 = thunk_FUN_0040a370();
          if (piVar3 == (int *)0x0) {
            piVar3 = (int *)0x0;
          }
          else if (uVar5 < uVar1) {
            *DAT_00461d68 = ')';
            DAT_00461d68[1] = '\0';
          }
        }
        else {
          thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456884);
          thunk_FUN_0040ca80((undefined *)puVar4);
          piVar3 = (int *)0x0;
        }
      }
    }
    else {
      thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456864);
      thunk_FUN_0040ca80((undefined *)piVar3);
      piVar3 = (int *)0x0;
    }
  }
  return (int)piVar3;
}


/* ==== FUN_00413832 @ 00413832 ==== */

undefined * __cdecl FUN_00413832(undefined *param_1)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  int *piVar4;
  undefined3 extraout_var;
  undefined4 *puVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  
  thunk_FUN_0040ca80(param_1);
  piVar4 = thunk_FUN_0040a370();
  if (piVar4 == (int *)0x0) {
    piVar4 = (int *)0x0;
  }
  else {
    cVar3 = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    if (cVar3 == ',') {
      uVar1 = piVar4[2];
      thunk_FUN_0040ca80((undefined *)piVar4);
      piVar4 = thunk_FUN_0040a370();
      if (piVar4 == (int *)0x0) {
        piVar4 = (int *)0x0;
      }
      else {
        cVar3 = *DAT_00461d68;
        DAT_00461d68 = DAT_00461d68 + 1;
        if (cVar3 == ',') {
          uVar2 = piVar4[2];
          thunk_FUN_0040ca80((undefined *)piVar4);
          if (uVar1 < uVar2) {
            piVar4 = thunk_FUN_0040a370();
            if (piVar4 == (int *)0x0) {
              piVar4 = (int *)0x0;
            }
            else {
              cVar3 = strrchr(DAT_00461d68,0x2c);
              DAT_00461d68 = (char *)CONCAT31(extraout_var,cVar3);
              if (DAT_00461d68 == (char *)0x0) {
                thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456904);
                thunk_FUN_0040ca80((undefined *)piVar4);
                piVar4 = (int *)0x0;
              }
              else {
                DAT_00461d68 = DAT_00461d68 + 1;
                puVar5 = thunk_FUN_0040a3e6();
                if (puVar5 == (undefined4 *)0x0) {
                  piVar4 = (int *)0x0;
                }
                else if (*DAT_00461d68 == ')') {
                  thunk_FUN_0040ca80((undefined *)puVar5);
                }
                else {
                  thunk_FUN_00409a25(s_Syntax_error___expected_terminat_00456924);
                  thunk_FUN_0040ca80((undefined *)puVar5);
                  piVar4 = (int *)0x0;
                }
              }
            }
          }
          else {
            cVar3 = strchr(DAT_00461d68,0x2c);
            DAT_00461d68 = (char *)CONCAT31(extraout_var_00,cVar3);
            if (DAT_00461d68 == (char *)0x0) {
              thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456954);
              thunk_FUN_0040ca80((undefined *)piVar4);
              piVar4 = (int *)0x0;
            }
            else {
              DAT_00461d68 = DAT_00461d68 + 1;
              piVar4 = thunk_FUN_0040a370();
              if (piVar4 == (int *)0x0) {
                piVar4 = (int *)0x0;
              }
              else {
                cVar3 = strchr(DAT_00461d68,0x2c);
                DAT_00461d68 = (char *)CONCAT31(extraout_var_01,cVar3);
                if (DAT_00461d68 == (char *)0x0) {
                  thunk_FUN_00409a25(s_Syntax_error___expected_comma_00456974);
                  thunk_FUN_0040ca80((undefined *)piVar4);
                  piVar4 = (int *)0x0;
                }
                else {
                  DAT_00461d68 = DAT_00461d68 + 1;
                  puVar5 = thunk_FUN_0040a3e6();
                  if (puVar5 == (undefined4 *)0x0) {
                    piVar4 = (int *)0x0;
                  }
                  else if (*DAT_00461d68 == ')') {
                    thunk_FUN_0040ca80((undefined *)puVar5);
                  }
                  else {
                    thunk_FUN_00409a25(s_Syntax_error___expected_terminat_00456994);
                    thunk_FUN_0040ca80((undefined *)puVar5);
                    piVar4 = (int *)0x0;
                  }
                }
              }
            }
          }
        }
        else {
          thunk_FUN_00409a25(s_Syntax_error___expected_comma_004568e4);
          thunk_FUN_0040ca80((undefined *)piVar4);
          piVar4 = (int *)0x0;
        }
      }
    }
    else {
      thunk_FUN_00409a25(s_Syntax_error___expected_comma_004568c4);
      thunk_FUN_0040ca80((undefined *)piVar4);
      piVar4 = (int *)0x0;
    }
  }
  return (undefined *)piVar4;
}


/* ==== FUN_00413acf @ 00413acf ==== */

uint * __cdecl FUN_00413acf(undefined *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  uint *puVar3;
  uint local_8;
  
  thunk_FUN_0040ca80(param_1);
  puVar2 = thunk_FUN_0040a3e6();
  if (puVar2 == (undefined4 *)0x0) {
    puVar3 = (uint *)0x0;
  }
  else {
    cVar1 = *DAT_00461d68;
    DAT_00461d68 = DAT_00461d68 + 1;
    if (cVar1 == ',') {
      DAT_00457b9c = puVar2[2];
      thunk_FUN_0040ca80((undefined *)puVar2);
      puVar3 = (uint *)thunk_FUN_0040a571();
      if (puVar3 == (uint *)0x0) {
        puVar3 = (uint *)0x0;
      }
      else {
        if (puVar3[4] == 0x100) {
          if (((puVar3[5] == DAT_00461f64) || (puVar3[1] == DAT_00461f6c)) || (puVar3[7] == 4)) {
            local_8 = thunk_FUN_00407988((int)puVar3);
          }
          else {
            local_8 = puVar3[2];
          }
        }
        else {
          thunk_FUN_00408616(*puVar3,puVar3[1],DAT_00461f60,puVar3);
          local_8 = puVar3[2];
        }
        if ((DAT_00457b9c == 2) && (((int)local_8 < -0x8000 || (0x7fff < (int)local_8)))) {
          thunk_FUN_00409a25(s_Byte_addressable_value_too_large_004569e4);
          thunk_FUN_0040ca80((undefined *)puVar3);
          puVar3 = (uint *)0x0;
        }
        else {
          puVar3[1] = 0;
          puVar3[2] = local_8;
        }
      }
    }
    else {
      thunk_FUN_00409a25(s_Syntax_error___expected_comma_004569c4);
      thunk_FUN_0040ca80((undefined *)puVar2);
      puVar3 = (uint *)0x0;
    }
  }
  return puVar3;
}


