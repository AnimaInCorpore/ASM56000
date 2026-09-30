/* error: 11 functions from DSPLNK */

/* ==== FUN_00408b90 @ 00408b90 ==== */

undefined4 __cdecl FUN_00408b90(undefined4 param_1)

{
  return param_1;
}


/* ==== FUN_00408ba1 @ 00408ba1 ==== */

float10 __cdecl FUN_00408ba1(undefined4 param_1,undefined4 param_2)

{
  return (float10)(double)CONCAT44(param_1,param_2);
}


/* ==== FUN_00408bba @ 00408bba ==== */

void __cdecl
FUN_00408bba(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_3 = param_2;
  *param_4 = param_1;
  return;
}


/* ==== FUN_004098b0 @ 004098b0 ==== */

void FUN_004098b0(void)

{
  undefined4 in_stack_00000004;
  undefined4 local_8;
  
  if (DAT_00461dbc == (undefined4 *)0x0) {
    fprintf(DAT_00461f34,s______FATAL______s_00455a6c,in_stack_00000004);
  }
  else {
    if ((DAT_00461dbc[2] == 0) || (*(int *)DAT_00461dbc[2] == 0)) {
      local_8 = *DAT_00461dbc;
    }
    else {
      local_8 = *(undefined4 *)DAT_00461dbc[2];
    }
    fprintf(DAT_00461f34,s_______File__s__Module__s_004559e4,*DAT_00461dbc,local_8);
    if (DAT_00461318 == 0) {
      if (-1 < DAT_00457c00) {
        if ((DAT_00461ddc == (undefined4 *)0x0) || (**(int **)*DAT_00461ddc == 0)) {
          fprintf(DAT_00461f34,s___Section__d__Symbol__ld_00455a28,DAT_00457c00,DAT_00461e7c);
        }
        else {
          fprintf(DAT_00461f34,s___Section__s__Symbol__ld_00455a0c,**(undefined4 **)*DAT_00461ddc,
                  DAT_00461e7c);
        }
        if (DAT_00461314 != 0) {
          fprintf(DAT_00461f34,s___Source_line__ld_00455a44,DAT_00461314);
        }
      }
    }
    else {
      fprintf(DAT_00461f34,s___Line__ld_00455a00,DAT_00461318);
    }
    fprintf(DAT_00461f34,s____FATAL______s_00455a58,in_stack_00000004);
  }
  if (DAT_00461d64 != (char *)0x0) {
    remove(DAT_00461d64);
  }
  exit(-1);
  return;
}


/* ==== FUN_00409a25 @ 00409a25 ==== */

void FUN_00409a25(void)

{
  undefined4 in_stack_00000004;
  undefined4 local_8;
  
  if (DAT_004611f0 == '\0') {
    if (DAT_00461dbc == (undefined4 *)0x0) {
      if (DAT_00461b40 == '\0') {
        fprintf(DAT_00461f34,s______ERROR______s_00455b38,in_stack_00000004);
      }
      else {
        fprintf(DAT_00461f34,s______ERROR______s___s_00455b20,in_stack_00000004,&DAT_00461b40);
      }
    }
    else {
      if ((DAT_00461dbc[2] == 0) || (*(int *)DAT_00461dbc[2] == 0)) {
        local_8 = *DAT_00461dbc;
      }
      else {
        local_8 = *(undefined4 *)DAT_00461dbc[2];
      }
      fprintf(DAT_00461f34,s_______File__s__Module__s_00455a80,*DAT_00461dbc,local_8);
      if (DAT_00461318 == 0) {
        if (-1 < DAT_00457c00) {
          if ((DAT_00461ddc == (undefined4 *)0x0) || (**(int **)*DAT_00461ddc == 0)) {
            fprintf(DAT_00461f34,s___Section__d__Symbol__ld_00455ac4,DAT_00457c00,DAT_00461e7c);
          }
          else {
            fprintf(DAT_00461f34,s___Section__s__Symbol__ld_00455aa8,**(undefined4 **)*DAT_00461ddc,
                    DAT_00461e7c);
          }
          if (DAT_00461314 != 0) {
            fprintf(DAT_00461f34,s___Source_line__ld_00455ae0,DAT_00461314);
          }
        }
      }
      else {
        fprintf(DAT_00461f34,s___Line__ld_00455a9c,DAT_00461318);
      }
      if (DAT_00461b40 == '\0') {
        fprintf(DAT_00461f34,s____ERROR______s_00455b0c,in_stack_00000004);
      }
      else {
        fprintf(DAT_00461f34,s____ERROR______s___s_00455af4,in_stack_00000004,&DAT_00461b40);
      }
    }
    DAT_004612ec = DAT_004612ec + 1;
  }
  else {
    DAT_004612f4 = DAT_004612f4 + 1;
  }
  return;
}


/* ==== FUN_00409bfd @ 00409bfd ==== */

void FUN_00409bfd(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 local_8;
  
  if (DAT_004611f0 == '\0') {
    if (DAT_00461dbc == (undefined4 *)0x0) {
      fprintf(DAT_00461f34,s______ERROR______s___s_00455bd8,in_stack_00000004,in_stack_00000008);
    }
    else {
      if ((DAT_00461dbc[2] == 0) || (*(int *)DAT_00461dbc[2] == 0)) {
        local_8 = *DAT_00461dbc;
      }
      else {
        local_8 = *(undefined4 *)DAT_00461dbc[2];
      }
      fprintf(DAT_00461f34,s_______File__s__Module__s_00455b4c,*DAT_00461dbc,local_8);
      if (DAT_00461318 == 0) {
        if (-1 < DAT_00457c00) {
          if ((DAT_00461ddc == (undefined4 *)0x0) || (**(int **)*DAT_00461ddc == 0)) {
            fprintf(DAT_00461f34,s___Section__d__Symbol__ld_00455b90,DAT_00457c00,DAT_00461e7c);
          }
          else {
            fprintf(DAT_00461f34,s___Section__s__Symbol__ld_00455b74,**(undefined4 **)*DAT_00461ddc,
                    DAT_00461e7c);
          }
          if (DAT_00461314 != 0) {
            fprintf(DAT_00461f34,s___Source_line__ld_00455bac,DAT_00461314);
          }
        }
      }
      else {
        fprintf(DAT_00461f34,s___Line__ld_00455b68,DAT_00461318);
      }
      fprintf(DAT_00461f34,s____ERROR______s___s_00455bc0,in_stack_00000004,in_stack_00000008);
    }
    DAT_004612ec = DAT_004612ec + 1;
  }
  else {
    DAT_004612f4 = DAT_004612f4 + 1;
  }
  return;
}


/* ==== FUN_00409d88 @ 00409d88 ==== */

void FUN_00409d88(void)

{
  undefined4 in_stack_00000004;
  undefined4 local_8;
  
  if (DAT_004611f0 == '\0') {
    if (DAT_00461dbc == (undefined4 *)0x0) {
      if (DAT_00461b40 == '\0') {
        fprintf(DAT_00461f34,s______WARNING______s_00455cac,in_stack_00000004);
      }
      else {
        fprintf(DAT_00461f34,s______WARNING______s___s_00455c90,in_stack_00000004,&DAT_00461b40);
      }
    }
    else {
      if ((DAT_00461dbc[2] == 0) || (*(int *)DAT_00461dbc[2] == 0)) {
        local_8 = *DAT_00461dbc;
      }
      else {
        local_8 = *(undefined4 *)DAT_00461dbc[2];
      }
      fprintf(DAT_00461f34,s_______File__s__Module__s_00455bf0,*DAT_00461dbc,local_8);
      if (DAT_00461318 == 0) {
        if (-1 < DAT_00457c00) {
          if ((DAT_00461ddc == (undefined4 *)0x0) || (**(int **)*DAT_00461ddc == 0)) {
            fprintf(DAT_00461f34,s___Section__d__Symbol__ld_00455c34,DAT_00457c00,DAT_00461e7c);
          }
          else {
            fprintf(DAT_00461f34,s___Section__s__Symbol__ld_00455c18,**(undefined4 **)*DAT_00461ddc,
                    DAT_00461e7c);
          }
          if (DAT_00461314 != 0) {
            fprintf(DAT_00461f34,s___Source_line__ld_00455c50,DAT_00461314);
          }
        }
      }
      else {
        fprintf(DAT_00461f34,s___Line__ld_00455c0c,DAT_00461318);
      }
      if (DAT_00461b40 == '\0') {
        fprintf(DAT_00461f34,s____WARNING______s_00455c7c,in_stack_00000004);
      }
      else {
        fprintf(DAT_00461f34,s____WARNING______s___s_00455c64,in_stack_00000004,&DAT_00461b40);
      }
    }
    DAT_004612f0 = DAT_004612f0 + 1;
  }
  return;
}


/* ==== FUN_00409f4d @ 00409f4d ==== */

void FUN_00409f4d(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 local_8;
  
  if (DAT_004611f0 == '\0') {
    if (DAT_00461dbc == (undefined4 *)0x0) {
      fprintf(DAT_00461f34,s______WARNING______s___s_00455d50,in_stack_00000004,in_stack_00000008);
    }
    else {
      if ((DAT_00461dbc[2] == 0) || (*(int *)DAT_00461dbc[2] == 0)) {
        local_8 = *DAT_00461dbc;
      }
      else {
        local_8 = *(undefined4 *)DAT_00461dbc[2];
      }
      fprintf(DAT_00461f34,s_______File__s__Module__s_00455cc4,*DAT_00461dbc,local_8);
      if (DAT_00461318 == 0) {
        if (-1 < DAT_00457c00) {
          if ((DAT_00461ddc == (undefined4 *)0x0) || (**(int **)*DAT_00461ddc == 0)) {
            fprintf(DAT_00461f34,s___Section__d__Symbol__ld_00455d08,DAT_00457c00,DAT_00461e7c);
          }
          else {
            fprintf(DAT_00461f34,s___Section__s__Symbol__ld_00455cec,**(undefined4 **)*DAT_00461ddc,
                    DAT_00461e7c);
          }
          if (DAT_00461314 != 0) {
            fprintf(DAT_00461f34,s___Source_line__ld_00455d24,DAT_00461314);
          }
        }
      }
      else {
        fprintf(DAT_00461f34,s___Line__ld_00455ce0,DAT_00461318);
      }
      fprintf(DAT_00461f34,s____WARNING______s___s_00455d38,in_stack_00000004,in_stack_00000008);
    }
    DAT_004612f0 = DAT_004612f0 + 1;
  }
  return;
}


/* ==== FUN_0040a0ca @ 0040a0ca ==== */

void FUN_0040a0ca(void)

{
  undefined4 in_stack_00000004;
  
  fprintf(&DAT_0045d650,s__s___s_00455d6c,PTR_s_dsplnk_00457ed0,in_stack_00000004);
  exit(-1);
  return;
}


/* ==== FUN_0040a0f6 @ 0040a0f6 ==== */

void FUN_0040a0f6(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  fprintf(&DAT_0045d650,s__s___s___s_00455d74,PTR_s_dsplnk_00457ed0,in_stack_00000004,
          in_stack_00000008);
  exit(-1);
  return;
}


/* ==== FUN_0040a126 @ 0040a126 ==== */

void FUN_0040a126(void)

{
  undefined4 in_stack_00000004;
  
  fprintf(&DAT_0045d650,s__s___s_00455d80,PTR_s_dsplnk_00457ed0,in_stack_00000004);
  return;
}


