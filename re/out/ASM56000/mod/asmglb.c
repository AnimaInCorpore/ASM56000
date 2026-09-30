/* asmglb: 18 functions from ASM56000 */

/* ==== FUN_00401000 @ 00401000 ==== */

double __cdecl FUN_00401000(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = atan((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_00401015 @ 00401015 ==== */

double __cdecl FUN_00401015(uint param_1,uint param_2)

{
  undefined4 unaff_EBP;
  double dVar1;
  
  dVar1 = fabs((double)CONCAT44(param_2,param_1),unaff_EBP);
  return dVar1;
}


/* ==== FUN_0040102a @ 0040102a ==== */

double __cdecl FUN_0040102a(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = acos((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_0040103f @ 0040103f ==== */

double __cdecl FUN_0040103f(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = asin((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_00401054 @ 00401054 ==== */

double __cdecl FUN_00401054(uint param_1,uint param_2)

{
  undefined4 unaff_EBP;
  double dVar1;
  
  dVar1 = ceil((double)CONCAT44(param_2,param_1),unaff_EBP);
  return dVar1;
}


/* ==== FUN_00401069 @ 00401069 ==== */

double FUN_00401069(void)

{
  undefined4 unaff_EBP;
  double dVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  dVar1 = cosh((double)CONCAT44(in_stack_00000008,in_stack_00000004),unaff_EBP);
  return dVar1;
}


/* ==== FUN_0040107e @ 0040107e ==== */

double __cdecl FUN_0040107e(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = cos((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_00401093 @ 00401093 ==== */

double __cdecl FUN_00401093(uint param_1,uint param_2)

{
  undefined4 unaff_EBP;
  double dVar1;
  
  dVar1 = floor((double)CONCAT44(param_2,param_1),unaff_EBP);
  return dVar1;
}


/* ==== FUN_004010a8 @ 004010a8 ==== */

double __cdecl FUN_004010a8(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = log10((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_004010bd @ 004010bd ==== */

double __cdecl FUN_004010bd(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = log((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_004010d2 @ 004010d2 ==== */

double __cdecl FUN_004010d2(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = sin((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_004010e7 @ 004010e7 ==== */

double __cdecl FUN_004010e7(uint param_1,int param_2)

{
  undefined4 unaff_EBP;
  double dVar1;
  
  dVar1 = sinh((double)CONCAT44(param_2,param_1),unaff_EBP);
  return dVar1;
}


/* ==== FUN_004010fc @ 004010fc ==== */

double __cdecl FUN_004010fc(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = sqrt((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_00401111 @ 00401111 ==== */

double __cdecl FUN_00401111(undefined4 param_1)

{
  double dVar1;
  undefined4 in_stack_00000008;
  
  dVar1 = tan((double)CONCAT44(in_stack_00000008,param_1),param_1);
  return dVar1;
}


/* ==== FUN_00401126 @ 00401126 ==== */

double FUN_00401126(void)

{
  undefined4 unaff_EBP;
  double dVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  dVar1 = tanh((double)CONCAT44(in_stack_00000008,in_stack_00000004),unaff_EBP);
  return dVar1;
}


/* ==== FUN_0040113b @ 0040113b ==== */

double __cdecl FUN_0040113b(uint param_1,int param_2)

{
  undefined4 unaff_EBP;
  double dVar1;
  
  dVar1 = exp((double)CONCAT44(param_2,param_1),unaff_EBP);
  return dVar1;
}


/* ==== FUN_00401150 @ 00401150 ==== */

double __cdecl FUN_00401150(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  double dVar1;
  undefined4 in_stack_00000010;
  
  dVar1 = pow((double)CONCAT44(param_2,param_1),(double)CONCAT44(in_stack_00000010,param_3),param_3,
              param_2);
  return dVar1;
}


/* ==== FUN_0040116d @ 0040116d ==== */

double __cdecl FUN_0040116d(uint param_1,int param_2,uint param_3,int param_4)

{
  undefined4 unaff_EBP;
  double dVar1;
  undefined4 unaff_retaddr;
  
  dVar1 = atan2((double)CONCAT44(param_2,param_1),(double)CONCAT44(param_4,param_3),unaff_EBP,
                unaff_retaddr);
  return dVar1;
}


