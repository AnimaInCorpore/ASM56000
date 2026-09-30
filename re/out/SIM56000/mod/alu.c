/* ==== insn_validate @ 00430850 ==== */

int __cdecl insn_validate(ulong opw,ulong devflags)

{
  int iVar1;
  
  iVar1 = opclass_lookup(opw,devflags);
  iVar1 = (*(code *)(&insn_valid_handlers)[iVar1])(opw);
  if (iVar1 == 2) {
    return 2;
  }
  return (uint)(iVar1 == 0);
}


/* ==== alu_op_h430880 @ 00430880 ==== */

void alu_op_h430880(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x48c) = 0;
  *(undefined4 *)(alu_core + 0x494) = 0;
  if ((*(byte *)(alu_core + 0x470) & 0x80) == 0) {
    *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
    *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
    *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
    *(undefined4 *)(alu_core + 0x490) = 0;
  }
  else {
    *(uint *)(alu_core + 0x474) = ~*(uint *)(alu_core + 0x468) & 0xffffff;
    *(uint *)(alu_core + 0x478) = ~*(uint *)(alu_core + 0x46c) & 0xffffff;
    *(uint *)(alu_core + 0x47c) = ~*(uint *)(alu_core + 0x470) & 0xff;
    *(undefined4 *)(alu_core + 0x490) = 1;
  }
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x490) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x48c) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x494) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_ovf_add @ 004309c0 ==== */

void alu_ovf_add(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(alu_core + 0x47c) & 0x80;
  if ((((uVar1 == 0) && ((*(byte *)(alu_core + 0x494) & 0x80) == 0)) &&
      ((*(byte *)(alu_core + 0x488) & 0x80) != 0)) ||
     (((uVar1 != 0 && ((*(byte *)(alu_core + 0x494) & 0x80) != 0)) &&
      ((*(byte *)(alu_core + 0x488) & 0x80) == 0)))) {
    alu_ccr = alu_ccr | 2;
  }
  return;
}


/* ==== alu_norm_sum @ 00430a10 ==== */

void alu_norm_sum(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(alu_core + 0x480);
  if (0xffffff < (int)uVar1) {
    *(uint *)(alu_core + 0x480) = uVar1 & 0xffffff;
    *(int *)(alu_core + 0x484) =
         *(int *)(alu_core + 0x484) + ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0xffffffU)) >> 0x18);
  }
  uVar1 = *(uint *)(alu_core + 0x484);
  if (0xffffff < (int)uVar1) {
    *(uint *)(alu_core + 0x484) = uVar1 & 0xffffff;
    *(int *)(alu_core + 0x488) =
         *(int *)(alu_core + 0x488) + ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0xffffffU)) >> 0x18);
  }
  return;
}


/* ==== alu_op_h430a90 @ 00430a90 ==== */

void alu_op_h430a90(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x460) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x45c) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x464) + *(int *)(alu_core + 0x47c);
  if ((alu_ccr & 1) != 0) {
    *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + 1;
  }
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_sub();
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_ovf_sub @ 00430b90 ==== */

void alu_ovf_sub(void)

{
  if ((*(byte *)(alu_core + 0x488) & 0x80) == 0) {
    if ((*(byte *)(alu_core + 0x494) & 0x80) == 0) {
      if ((*(byte *)(alu_core + 0x47c) & 0x80) == 0) {
        return;
      }
      alu_ccr = alu_ccr | 1;
      return;
    }
  }
  else {
    if ((*(byte *)(alu_core + 0x494) & 0x80) == 0) {
      return;
    }
    if ((*(byte *)(alu_core + 0x47c) & 0x80) == 0) {
      return;
    }
  }
  alu_ccr = alu_ccr | 1;
  return;
}


/* ==== alu_add56 @ 00430be0 ==== */

void alu_add56(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x460) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x45c) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x464) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_sub();
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h430cd0 @ 00430cd0 ==== */

void alu_op_h430cd0(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  alu_ccr = alu_ccr & 0xffffffc0;
  *(int *)(alu_core + 0x474) = *(int *)(alu_core + 0x468) << 1;
  *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x46c) << 1;
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) << 1;
  alu_norm_res();
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  uVar1 = *(uint *)(alu_core + 0x47c) & 0x180;
  if ((uVar1 == 0x100) || (uVar1 == 0x80)) {
    alu_ccr = alu_ccr | 2;
  }
  *(uint *)(alu_core + 0x47c) = *(uint *)(alu_core + 0x47c) & 0xff;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x460) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x45c) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x464) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ovf_sub();
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_norm_res @ 00430e00 ==== */

void alu_norm_res(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(alu_core + 0x474);
  if (0xffffff < (int)uVar1) {
    *(uint *)(alu_core + 0x474) = uVar1 & 0xffffff;
    *(int *)(alu_core + 0x478) =
         *(int *)(alu_core + 0x478) + ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0xffffffU)) >> 0x18);
  }
  uVar1 = *(uint *)(alu_core + 0x478);
  if (0xffffff < (int)uVar1) {
    *(uint *)(alu_core + 0x478) = uVar1 & 0xffffff;
    *(int *)(alu_core + 0x47c) =
         *(int *)(alu_core + 0x47c) + ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0xffffffU)) >> 0x18);
  }
  return;
}


/* ==== alu_op_h430e80 @ 00430e80 ==== */

void alu_op_h430e80(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) / 2;
  if ((*(byte *)(alu_core + 0x470) & 0x80) != 0) {
    *(uint *)(alu_core + 0x47c) = *(uint *)(alu_core + 0x47c) | 0x80;
  }
  uVar1 = *(uint *)(alu_core + 0x46c);
  if (((byte)*(undefined4 *)(alu_core + 0x470) & 1) == 1) {
    uVar1 = uVar1 | 0x1000000;
  }
  *(int *)(alu_core + 0x478) = (int)uVar1 / 2;
  uVar1 = *(uint *)(alu_core + 0x468);
  if (((byte)*(undefined4 *)(alu_core + 0x46c) & 1) == 1) {
    uVar1 = uVar1 | 0x1000000;
  }
  *(int *)(alu_core + 0x474) = (int)uVar1 / 2;
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x490) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x48c) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x494) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_sub();
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h430fc0 @ 00430fc0 ==== */

void alu_op_h430fc0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x45c) & *(uint *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff1;
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if ((*(uint *)(alu_core + 0x484) & 0x800000) != 0) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431090 @ 00431090 ==== */

void alu_op_h431090(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(int *)(alu_core + 0x474) = *(int *)(alu_core + 0x468) << 1;
  *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x46c) << 1;
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) << 1;
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  if ((*(uint *)(alu_core + 0x47c) & 0x100) != 0) {
    alu_ccr = alu_ccr | 1;
  }
  uVar1 = *(uint *)(alu_core + 0x47c) & 0x180;
  if ((uVar1 == 0x100) || (uVar1 == 0x80)) {
    alu_ccr = alu_ccr | 2;
  }
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h431170 @ 00431170 ==== */

void alu_op_h431170(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) / 2;
  if ((*(byte *)(alu_core + 0x470) & 0x80) != 0) {
    *(uint *)(alu_core + 0x47c) = *(uint *)(alu_core + 0x47c) | 0x80;
  }
  uVar1 = *(uint *)(alu_core + 0x46c);
  if (((byte)*(undefined4 *)(alu_core + 0x470) & 1) == 1) {
    uVar1 = uVar1 | 0x1000000;
  }
  *(int *)(alu_core + 0x478) = (int)uVar1 / 2;
  uVar1 = *(uint *)(alu_core + 0x468);
  if (((byte)*(undefined4 *)(alu_core + 0x46c) & 1) == 1) {
    uVar1 = uVar1 | 0x1000000;
  }
  *(int *)(alu_core + 0x474) = (int)uVar1 / 2;
  alu_ccr = alu_ccr & 0xffffffc0;
  if ((*(byte *)(alu_core + 0x468) & 1) != 0) {
    alu_ccr = alu_ccr | 1;
  }
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h431270 @ 00431270 ==== */

void alu_op_h431270(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(1);
    return;
  }
  alu_mpy();
  return;
}


/* ==== alu_op_h431290 @ 00431290 ==== */

void alu_op_h431290(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(1);
    return;
  }
  alu_mac();
  return;
}


/* ==== alu_op_h4312b0 @ 004312b0 ==== */

void alu_op_h4312b0(void)

{
  if (*(int *)(alu_core + 0x1bc) != 1) {
    *(undefined4 *)(alu_core + 0x480) = 0;
    *(undefined4 *)(alu_core + 0x484) = 0;
    *(undefined4 *)(alu_core + 0x488) = 0;
    alu_ccr = alu_ccr & 0xffffffc1;
    alu_set_ccr();
    alu_store_ext();
    return;
  }
  return;
}


/* ==== alu_op_h431300 @ 00431300 ==== */

void alu_op_h431300(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(uint *)(alu_core + 0x480) =
       (~*(uint *)(alu_core + 0x460) & 0xffffff) + 1 + *(int *)(alu_core + 0x474);
  *(uint *)(alu_core + 0x484) =
       (~*(uint *)(alu_core + 0x45c) & 0xffffff) + *(int *)(alu_core + 0x478);
  *(uint *)(alu_core + 0x488) = (~*(uint *)(alu_core + 0x464) & 0xff) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_c();
  alu_ovf_d();
  alu_set_ccr();
  return;
}


/* ==== alu_ovf_c @ 00431400 ==== */

void alu_ovf_c(void)

{
  if ((*(byte *)(alu_core + 0x488) & 0x80) == 0) {
    if (((*(byte *)(alu_core + 0x494) & 0x80) != 0) && ((*(byte *)(alu_core + 0x47c) & 0x80) == 0))
    {
      alu_ccr = alu_ccr | 1;
      return;
    }
  }
  else if (((*(byte *)(alu_core + 0x494) & 0x80) != 0) ||
          ((*(byte *)(alu_core + 0x47c) & 0x80) == 0)) {
    alu_ccr = alu_ccr | 1;
  }
  return;
}


/* ==== alu_ovf_d @ 00431450 ==== */

void alu_ovf_d(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(alu_core + 0x47c) & 0x80;
  if ((((uVar1 != 0) && ((*(byte *)(alu_core + 0x494) & 0x80) == 0)) &&
      ((*(byte *)(alu_core + 0x488) & 0x80) == 0)) ||
     (((uVar1 == 0 && ((*(byte *)(alu_core + 0x494) & 0x80) != 0)) &&
      ((*(byte *)(alu_core + 0x488) & 0x80) != 0)))) {
    alu_ccr = alu_ccr | 2;
  }
  return;
}


/* ==== alu_op_h4314a0 @ 004314a0 ==== */

void alu_op_h4314a0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  if ((*(byte *)(alu_core + 0x464) & 0x80) == 0) {
    *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
    *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
    *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  }
  else {
    *(uint *)(alu_core + 0x490) = (~*(uint *)(alu_core + 0x460) & 0xffffff) + 1;
    *(uint *)(alu_core + 0x48c) = ~*(uint *)(alu_core + 0x45c) & 0xffffff;
    *(uint *)(alu_core + 0x494) = ~*(uint *)(alu_core + 0x464) & 0xff;
    alu_norm_abs();
  }
  if ((*(byte *)(alu_core + 0x470) & 0x80) == 0) {
    *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
    *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
    *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  }
  else {
    *(uint *)(alu_core + 0x474) = (~*(uint *)(alu_core + 0x468) & 0xffffff) + 1;
    *(uint *)(alu_core + 0x478) = ~*(uint *)(alu_core + 0x46c) & 0xffffff;
    *(uint *)(alu_core + 0x47c) = ~*(uint *)(alu_core + 0x470) & 0xff;
    alu_norm_res();
  }
  *(uint *)(alu_core + 0x480) =
       (~*(uint *)(alu_core + 0x490) & 0xffffff) + 1 + *(int *)(alu_core + 0x474);
  *(uint *)(alu_core + 0x484) =
       (~*(uint *)(alu_core + 0x48c) & 0xffffff) + *(int *)(alu_core + 0x478);
  *(uint *)(alu_core + 0x488) = *(int *)(alu_core + 0x47c) + (~*(uint *)(alu_core + 0x494) & 0x1ff);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_c();
  if ((((*(char *)(alu_core + 0x488) == -0x80) && (*(int *)(alu_core + 0x484) == 0)) &&
      (*(int *)(alu_core + 0x480) == 0)) && (*(int *)(alu_core + 0x47c) != 0)) {
    alu_ccr = alu_ccr | 2;
  }
  alu_set_ccr();
  return;
}


/* ==== alu_norm_abs @ 00431680 ==== */

void alu_norm_abs(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(alu_core + 0x490);
  if (0xffffff < (int)uVar1) {
    *(uint *)(alu_core + 0x490) = uVar1 & 0xffffff;
    *(int *)(alu_core + 0x48c) =
         *(int *)(alu_core + 0x48c) + ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0xffffffU)) >> 0x18);
  }
  uVar1 = *(uint *)(alu_core + 0x48c);
  if (0xffffff < (int)uVar1) {
    *(uint *)(alu_core + 0x48c) = uVar1 & 0xffffff;
    *(int *)(alu_core + 0x494) =
         *(int *)(alu_core + 0x494) + ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0xffffffU)) >> 0x18);
  }
  return;
}


/* ==== alu_op_h431700 @ 00431700 ==== */

void alu_op_h431700(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(uint *)(alu_core + 0x474) = (alu_ccr & 1) + *(int *)(alu_core + 0x468) * 2;
  *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x46c) << 1;
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) << 1;
  alu_norm_res();
  alu_ccr = alu_ccr & 0xfffffffc;
  uVar1 = *(uint *)(alu_core + 0x47c) & 0x180;
  if ((uVar1 != 0) && (uVar1 != 0x180)) {
    alu_ccr = alu_ccr | 0x42;
  }
  *(uint *)(alu_core + 0x47c) = *(uint *)(alu_core + 0x47c) & 0xff;
  uVar1 = *(uint *)(alu_core + 0x45c);
  if ((*(byte *)(alu_core + 0x470) & 0x80) != 0) {
    uVar1 = ~uVar1;
  }
  if ((uVar1 >> 0x17 & 1) == 0) {
    *(uint *)(alu_core + 0x490) = (~*(uint *)(alu_core + 0x460) & 0xffffff) + 1;
    *(uint *)(alu_core + 0x48c) = ~*(uint *)(alu_core + 0x45c) & 0xffffff;
    uVar1 = ~*(uint *)(alu_core + 0x464) & 0xff;
  }
  else {
    *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
    *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
    uVar1 = *(uint *)(alu_core + 0x464);
  }
  *(uint *)(alu_core + 0x494) = uVar1;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x490) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x48c) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x494) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  if ((*(byte *)(alu_core + 0x488) & 0x80) == 0) {
    alu_ccr = alu_ccr | 1;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h4318a0 @ 004318a0 ==== */

void alu_op_h4318a0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x460) = 1;
  *(undefined4 *)(alu_core + 0x45c) = 0;
  *(undefined4 *)(alu_core + 0x464) = 0;
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(uint *)(alu_core + 0x480) = (~*(uint *)(alu_core + 0x460) & 0xffffff) + 1;
  *(uint *)(alu_core + 0x484) = ~*(uint *)(alu_core + 0x45c) & 0xffffff;
  *(uint *)(alu_core + 0x488) = ~*(uint *)(alu_core + 0x464) & 0xff;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_c();
  alu_ovf_d();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h4318e0 @ 004318e0 ==== */

void alu_op_h4318e0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x460) = 1;
  *(undefined4 *)(alu_core + 0x45c) = 0;
  *(undefined4 *)(alu_core + 0x464) = 0;
  alu_add56();
  return;
}


/* ==== alu_op_h431920 @ 00431920 ==== */

void alu_op_h431920(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x45c) ^ *(uint *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff1;
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if ((*(uint *)(alu_core + 0x484) & 0x800000) != 0) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h4319f0 @ 004319f0 ==== */

void alu_op_h4319f0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x46c) << 1;
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x478) & 0xffffff;
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff0;
  if (0x7fffff < *(int *)(alu_core + 0x46c)) {
    alu_ccr = alu_ccr | 1;
  }
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if (0x7fffff < *(int *)(alu_core + 0x484)) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431ac0 @ 00431ac0 ==== */

void alu_op_h431ac0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x46c) / 2;
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff0;
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if ((*(byte *)(alu_core + 0x46c) & 1) != 0) {
    alu_ccr = alu_ccr | 1;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431b80 @ 00431b80 ==== */

void alu_op_h431b80(void)

{
  alu_flag = 0;
  return;
}


/* ==== alu_op_h431b90 @ 00431b90 ==== */

void alu_op_h431b90(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(uint *)(alu_core + 0x474) = ~*(uint *)(alu_core + 0x468) & 0xffffff;
  *(uint *)(alu_core + 0x478) = ~*(uint *)(alu_core + 0x46c) & 0xffffff;
  *(uint *)(alu_core + 0x47c) = ~*(uint *)(alu_core + 0x470) & 0xff;
  *(undefined4 *)(alu_core + 0x494) = 0;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x474) + 1;
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc1;
  if (((*(byte *)(alu_core + 0x470) & 0x80) != 0) && ((*(byte *)(alu_core + 0x488) & 0x80) != 0)) {
    alu_ccr = alu_ccr | 2;
  }
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h431c70 @ 00431c70 ==== */

void alu_op_h431c70(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(uint *)(alu_core + 0x484) = ~*(uint *)(alu_core + 0x478) & 0xffffff;
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff1;
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if (0x7fffff < *(int *)(alu_core + 0x484)) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431d40 @ 00431d40 ==== */

void alu_op_h431d40(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x45c) | *(uint *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff1;
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if (0x7fffff < *(int *)(alu_core + 0x484)) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431e10 @ 00431e10 ==== */

void alu_op_h431e10(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(uint *)(alu_core + 0x484) = (alu_ccr & 1) + *(int *)(alu_core + 0x478) * 2 & 0xffffff;
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff0;
  if (0x7fffff < *(int *)(alu_core + 0x478)) {
    alu_ccr = alu_ccr | 1;
  }
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if (0x7fffff < *(int *)(alu_core + 0x484)) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431ef0 @ 00431ef0 ==== */

void alu_op_h431ef0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(uint *)(alu_core + 0x484) = *(int *)(alu_core + 0x478) / 2 | ((int)(char)alu_ccr & 1U) << 0x17;
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xfffffff0;
  if ((*(byte *)(alu_core + 0x478) & 1) != 0) {
    alu_ccr = alu_ccr | 1;
  }
  if (*(int *)(alu_core + 0x484) == 0) {
    alu_ccr = alu_ccr | 4;
  }
  if (0x7fffff < *(int *)(alu_core + 0x484)) {
    alu_ccr = alu_ccr | 8;
  }
  alu_store_ext();
  return;
}


/* ==== alu_op_h431fe0 @ 00431fe0 ==== */

void alu_op_h431fe0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(uint *)(alu_core + 0x480) = ((~*(uint *)(alu_core + 0x460) & 0xffffff) - (alu_ccr & 1)) + 1;
  *(uint *)(alu_core + 0x484) = ~*(uint *)(alu_core + 0x45c) & 0xffffff;
  *(uint *)(alu_core + 0x488) = ~*(uint *)(alu_core + 0x464) & 0xff;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_c();
  alu_ovf_d();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h432120 @ 00432120 ==== */

void alu_op_h432120(void)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  int iVar11;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(1);
    return;
  }
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(0);
    return;
  }
  bVar3 = false;
  bVar4 = false;
  iVar11 = 0;
  bVar10 = false;
  if ((*(uint *)(cur_dtype + 8) < 4) || ((alu_ccr & 0x4000) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    iVar1 = *(int *)(alu_core + 0x1c0);
    if (iVar1 == 0x2c) {
      bVar3 = true;
    }
    else if (iVar1 == 0x2b) {
      bVar10 = (*(uint *)(alu_core + 0x45c) & 0x800000) != 0;
      if ((*(uint *)(alu_core + 0xb8) & 0x800000) != 0) {
        bVar4 = true;
      }
    }
    else if ((iVar1 == 0x2f) && (bVar3 = true, (*(uint *)(alu_core + 0xb8) & 0x800000) != 0)) {
      iVar11 = 1;
    }
  }
  if (bVar3) {
    *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x46c);
    *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x470);
    if ((*(byte *)(alu_core + 0x470) & 0x80) == 0) {
      *(undefined4 *)(alu_core + 0x47c) = 0;
      *(uint *)(alu_core + 0x478) = *(uint *)(alu_core + 0x478) & 0xff;
    }
    else {
      *(undefined4 *)(alu_core + 0x47c) = 0xff;
      *(uint *)(alu_core + 0x478) = *(uint *)(alu_core + 0x478) | 0xffff00;
    }
  }
  else {
    *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
    *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
    *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  }
  if (bVar10) {
    *(uint *)(alu_core + 0x45c) = *(uint *)(alu_core + 0x45c) & 0x7fffff;
    *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x478) + *(int *)(alu_core + 0x460);
    if ((*(uint *)(alu_core + 0x460) & 0x800000) != 0) {
      *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x47c) + 0xff;
    }
  }
  uVar5 = *(uint *)(alu_core + 0x45c);
  if (0x7fffff < (int)uVar5) {
    uVar5 = (~uVar5 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x48c) = uVar5;
  uVar5 = *(uint *)(alu_core + 0x460);
  if (0x7fffff < (int)uVar5) {
    uVar5 = (~uVar5 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x490) = uVar5;
  uVar5 = *(uint *)(alu_core + 0x48c);
  iVar1 = *(int *)(alu_core + 0x490);
  uVar6 = (int)uVar5 >> 0x1f;
  uVar8 = (uVar5 & 0x3f) * iVar1;
  uVar7 = ((int)(uVar5 + (uVar6 & 0x3ffff)) >> 0x12 & 0x7fU) * iVar1;
  uVar9 = ((int)(uVar5 + (uVar6 & 0xfff)) >> 0xc & 0x3fU) * iVar1;
  uVar6 = ((int)(uVar5 + (uVar6 & 0x3f)) >> 6 & 0x3fU) * iVar1;
  uVar5 = (((uVar9 & 0xfff) + (uVar7 & 0x3f) * 0x40) * 0x40 + (uVar6 & 0x3ffff)) * 0x40 +
          (uVar8 & 0xffffff);
  uVar6 = ((int)(uVar9 + ((int)uVar9 >> 0x1f & 0xfffU)) >> 0xc) +
          ((int)(uVar8 + ((int)uVar8 >> 0x1f & 0xffffffU)) >> 0x18) +
          ((int)(uVar7 + ((int)uVar7 >> 0x1f & 0x3fU)) >> 6) +
          ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0x3ffffU)) >> 0x12);
  if (0xffffff < uVar5) {
    uVar6 = uVar6 + ((int)uVar5 >> 0x18);
    uVar5 = uVar5 & 0xffffff;
  }
  uVar7 = *(uint *)(alu_core + 0x460);
  uVar8 = uVar7;
  if ((*(uint *)(alu_core + 0x45c) & 0x800000) == 0) {
    uVar8 = ~uVar7;
  }
  uVar8 = uVar8 >> 0x17 & 1;
  if (*(int *)(alu_core + 0x1cc) == 0) {
    uVar8 = (uint)(uVar8 == 0);
  }
  if ((uVar7 == 0) || (*(uint *)(alu_core + 0x45c) == 0)) {
    uVar8 = 1;
  }
  if (uVar8 == 1) {
    *(uint *)(alu_core + 0x480) = uVar5 * 2;
    *(uint *)(alu_core + 0x484) = uVar6 * 2;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0;
    *(undefined4 *)(alu_core + 0x494) = 0;
  }
  else {
    *(uint *)(alu_core + 0x480) = (~uVar5 & 0xffffff) * 2 + 2;
    *(uint *)(alu_core + 0x484) = (~uVar6 & 0xffffff) << 1;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0xff;
    *(undefined4 *)(alu_core + 0x494) = 0xff;
  }
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  if (bVar4) {
    if (bVar10) {
      *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + 1;
    }
    *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x45c) * 2;
    alu_norm_sum();
  }
  if (iVar11 != 0) {
    if ((*(uint *)(alu_core + 0x460) & 0x800000) != 0) {
      *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + 0x1fffffe;
      *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + 0x1fe;
    }
    *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x460) * 2;
    alu_norm_sum();
  }
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h432140 @ 00432140 ==== */

void alu_op_h432140(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(1);
    return;
  }
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(0);
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  uVar2 = *(uint *)(alu_core + 0x45c);
  if (0x7fffff < (int)uVar2) {
    uVar2 = (~uVar2 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x48c) = uVar2;
  uVar2 = *(uint *)(alu_core + 0x460);
  if (0x7fffff < (int)uVar2) {
    uVar2 = (~uVar2 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x490) = uVar2;
  uVar2 = *(uint *)(alu_core + 0x48c);
  iVar1 = *(int *)(alu_core + 0x490);
  uVar3 = (int)uVar2 >> 0x1f;
  uVar5 = (uVar2 & 0x3f) * iVar1;
  uVar4 = ((int)(uVar2 + (uVar3 & 0x3ffff)) >> 0x12 & 0x7fU) * iVar1;
  uVar6 = ((int)(uVar2 + (uVar3 & 0xfff)) >> 0xc & 0x3fU) * iVar1;
  uVar3 = ((int)(uVar2 + (uVar3 & 0x3f)) >> 6 & 0x3fU) * iVar1;
  uVar2 = (((uVar6 & 0xfff) + (uVar4 & 0x3f) * 0x40) * 0x40 + (uVar3 & 0x3ffff)) * 0x40 +
          (uVar5 & 0xffffff);
  uVar3 = ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0xfffU)) >> 0xc) +
          ((int)(uVar5 + ((int)uVar5 >> 0x1f & 0xffffffU)) >> 0x18) +
          ((int)(uVar4 + ((int)uVar4 >> 0x1f & 0x3fU)) >> 6) +
          ((int)(uVar3 + ((int)uVar3 >> 0x1f & 0x3ffffU)) >> 0x12);
  if (0xffffff < uVar2) {
    uVar3 = uVar3 + ((int)uVar2 >> 0x18);
    uVar2 = uVar2 & 0xffffff;
  }
  uVar4 = *(uint *)(alu_core + 0x460);
  uVar5 = uVar4;
  if ((*(uint *)(alu_core + 0x45c) & 0x800000) == 0) {
    uVar5 = ~uVar4;
  }
  uVar5 = uVar5 >> 0x17 & 1;
  if (*(int *)(alu_core + 0x1cc) == 0) {
    uVar5 = (uint)(uVar5 == 0);
  }
  if ((uVar4 == 0) || (*(int *)(alu_core + 0x45c) == 0)) {
    uVar5 = 1;
  }
  if (uVar5 == 1) {
    *(uint *)(alu_core + 0x480) = uVar2 * 2;
    *(uint *)(alu_core + 0x484) = uVar3 * 2;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0;
    *(undefined4 *)(alu_core + 0x494) = 0;
  }
  else {
    *(uint *)(alu_core + 0x480) = (~uVar2 & 0xffffff) * 2 + 2;
    *(uint *)(alu_core + 0x484) = (~uVar3 & 0xffffff) << 1;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0xff;
    *(undefined4 *)(alu_core + 0x494) = 0xff;
  }
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_ovf_add();
  alu_round();
  if ((((*(byte *)(alu_core + 0x47c) & 0x80) == 0) && ((*(byte *)(alu_core + 0x494) & 0x80) == 0))
     && ((*(byte *)(alu_core + 0x488) & 0x80) != 0)) {
    alu_ccr = alu_ccr | 2;
  }
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h432290 @ 00432290 ==== */

void alu_op_h432290(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  alu_ccr = alu_ccr & 0xffffffc0;
  *(int *)(alu_core + 0x474) = *(int *)(alu_core + 0x468) << 1;
  *(int *)(alu_core + 0x478) = *(int *)(alu_core + 0x46c) << 1;
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) << 1;
  alu_norm_res();
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  uVar1 = *(uint *)(alu_core + 0x47c) & 0x180;
  if ((uVar1 == 0x100) || (uVar1 == 0x80)) {
    alu_ccr = alu_ccr | 2;
  }
  *(uint *)(alu_core + 0x47c) = *(uint *)(alu_core + 0x47c) & 0xff;
  *(uint *)(alu_core + 0x480) = (~*(uint *)(alu_core + 0x460) & 0xffffff) + 1;
  *(uint *)(alu_core + 0x484) = ~*(uint *)(alu_core + 0x45c) & 0xffffff;
  *(uint *)(alu_core + 0x488) = ~*(uint *)(alu_core + 0x464) & 0xff;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ovf_c();
  alu_ovf_d();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h432410 @ 00432410 ==== */

void alu_op_h432410(void)

{
  uint uVar1;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    return;
  }
  *(int *)(alu_core + 0x47c) = *(int *)(alu_core + 0x470) / 2;
  if ((*(byte *)(alu_core + 0x470) & 0x80) != 0) {
    *(uint *)(alu_core + 0x47c) = *(uint *)(alu_core + 0x47c) | 0x80;
  }
  uVar1 = *(uint *)(alu_core + 0x46c);
  if ((*(byte *)(alu_core + 0x470) & 1) != 0) {
    uVar1 = uVar1 | 0x1000000;
  }
  *(int *)(alu_core + 0x478) = (int)uVar1 / 2;
  uVar1 = *(uint *)(alu_core + 0x468);
  if ((*(byte *)(alu_core + 0x46c) & 1) != 0) {
    uVar1 = uVar1 | 0x1000000;
  }
  *(int *)(alu_core + 0x474) = (int)uVar1 / 2;
  *(undefined4 *)(alu_core + 0x490) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x48c) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x494) = *(undefined4 *)(alu_core + 0x464);
  *(uint *)(alu_core + 0x480) = (~*(uint *)(alu_core + 0x460) & 0xffffff) + 1;
  *(uint *)(alu_core + 0x484) = ~*(uint *)(alu_core + 0x45c) & 0xffffff;
  *(uint *)(alu_core + 0x488) = ~*(uint *)(alu_core + 0x464) & 0xff;
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + *(int *)(alu_core + 0x474);
  *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x478);
  *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + *(int *)(alu_core + 0x47c);
  alu_norm_sum();
  alu_ccr = alu_ccr & 0xffffffc0;
  alu_ovf_c();
  alu_ovf_d();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h432590 @ 00432590 ==== */

void alu_op_h432590(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_ops();
    alu_flag = 0;
    return;
  }
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x460);
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x45c);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x464);
  alu_store_ext();
  alu_flag = 0;
  return;
}


/* ==== hid_4325c1 @ 004325c1 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void hid_4325c1(void)

{
  int in_EAX;
  int in_ECX;
  int unaff_retaddr;
  
  *(char *)(in_ECX + 0x48490) = *(char *)(in_ECX + 0x48490) + (char)in_ECX;
  *(char *)((int)&alu_core + in_ECX) =
       *(char *)((int)&alu_core + in_ECX) + (char)((uint)in_EAX >> 8);
  *(undefined4 *)(in_EAX + 0x488) = *(undefined4 *)(in_EAX + 0x464);
  *(undefined4 *)(unaff_retaddr + -4) = 0x4325e1;
  alu_store_ext();
  alu_flag = 0;
  return;
}


/* ==== alu_mpy @ 00432d50 ==== */

void alu_mpy(void)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(0);
    return;
  }
  if ((*(uint *)(cur_dtype + 8) < 4) || ((alu_ccr & 0x4000) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (((bVar2) && (*(int *)(alu_core + 0x1c0) == 0x2e)) &&
     ((*(uint *)(alu_core + 0x460) & 0x800000) != 0)) {
    bVar2 = true;
    *(uint *)(alu_core + 0x460) = *(uint *)(alu_core + 0x460) & 0x7fffff;
  }
  else {
    bVar2 = false;
  }
  *(undefined4 *)(alu_core + 0x474) = 0;
  *(undefined4 *)(alu_core + 0x478) = 0;
  *(undefined4 *)(alu_core + 0x47c) = 0;
  uVar3 = *(uint *)(alu_core + 0x45c);
  if (0x7fffff < (int)uVar3) {
    uVar3 = (~uVar3 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x48c) = uVar3;
  uVar3 = *(uint *)(alu_core + 0x460);
  if (0x7fffff < (int)uVar3) {
    uVar3 = (~uVar3 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x490) = uVar3;
  uVar3 = *(uint *)(alu_core + 0x48c);
  iVar1 = *(int *)(alu_core + 0x490);
  uVar4 = (int)uVar3 >> 0x1f;
  uVar6 = (uVar3 & 0x3f) * iVar1;
  uVar5 = ((int)(uVar3 + (uVar4 & 0x3ffff)) >> 0x12 & 0x7fU) * iVar1;
  uVar7 = ((int)(uVar3 + (uVar4 & 0xfff)) >> 0xc & 0x3fU) * iVar1;
  uVar4 = ((int)(uVar3 + (uVar4 & 0x3f)) >> 6 & 0x3fU) * iVar1;
  uVar3 = (((uVar7 & 0xfff) + (uVar5 & 0x3f) * 0x40) * 0x40 + (uVar4 & 0x3ffff)) * 0x40 +
          (uVar6 & 0xffffff);
  uVar4 = ((int)(uVar7 + ((int)uVar7 >> 0x1f & 0xfffU)) >> 0xc) +
          ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0xffffffU)) >> 0x18) +
          ((int)(uVar4 + ((int)uVar4 >> 0x1f & 0x3ffffU)) >> 0x12) +
          ((int)(uVar5 + ((int)uVar5 >> 0x1f & 0x3fU)) >> 6);
  if (0xffffff < uVar3) {
    uVar4 = uVar4 + ((int)uVar3 >> 0x18);
    uVar3 = uVar3 & 0xffffff;
  }
  uVar5 = *(uint *)(alu_core + 0x460);
  uVar6 = uVar5;
  if ((*(uint *)(alu_core + 0x45c) & 0x800000) == 0) {
    uVar6 = ~uVar5;
  }
  uVar6 = uVar6 >> 0x17 & 1;
  if (*(int *)(alu_core + 0x1cc) == 0) {
    uVar6 = (uint)(uVar6 == 0);
  }
  if ((uVar5 == 0) || (*(uint *)(alu_core + 0x45c) == 0)) {
    uVar6 = 1;
  }
  if (uVar6 == 1) {
    *(uint *)(alu_core + 0x480) = uVar3 * 2;
    *(uint *)(alu_core + 0x484) = uVar4 * 2;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0;
  }
  else {
    *(uint *)(alu_core + 0x480) = (~uVar3 & 0xffffff) * 2 + 2;
    *(uint *)(alu_core + 0x484) = (~uVar4 & 0xffffff) << 1;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0xff;
  }
  if (bVar2) {
    *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + *(int *)(alu_core + 0x45c);
    if ((*(uint *)(alu_core + 0x45c) & 0x800000) != 0) {
      *(int *)(alu_core + 0x488) = *(int *)(alu_core + 0x488) + 0xff;
    }
    alu_norm_sum();
  }
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_mac @ 00433020 ==== */

void alu_mac(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_src(0);
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = 0;
  *(undefined4 *)(alu_core + 0x478) = 0;
  *(undefined4 *)(alu_core + 0x47c) = 0;
  uVar2 = *(uint *)(alu_core + 0x45c);
  if (0x7fffff < (int)uVar2) {
    uVar2 = (~uVar2 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x48c) = uVar2;
  uVar2 = *(uint *)(alu_core + 0x460);
  if (0x7fffff < (int)uVar2) {
    uVar2 = (~uVar2 & 0xffffff) + 1;
  }
  *(uint *)(alu_core + 0x490) = uVar2;
  uVar2 = *(uint *)(alu_core + 0x48c);
  iVar1 = *(int *)(alu_core + 0x490);
  uVar3 = (int)uVar2 >> 0x1f;
  uVar5 = (uVar2 & 0x3f) * iVar1;
  uVar4 = ((int)(uVar2 + (uVar3 & 0x3ffff)) >> 0x12 & 0x7fU) * iVar1;
  uVar6 = ((int)(uVar2 + (uVar3 & 0xfff)) >> 0xc & 0x3fU) * iVar1;
  uVar3 = ((int)(uVar2 + (uVar3 & 0x3f)) >> 6 & 0x3fU) * iVar1;
  uVar2 = (((uVar6 & 0xfff) + (uVar4 & 0x3f) * 0x40) * 0x40 + (uVar3 & 0x3ffff)) * 0x40 +
          (uVar5 & 0xffffff);
  uVar3 = ((int)(uVar6 + ((int)uVar6 >> 0x1f & 0xfffU)) >> 0xc) +
          ((int)(uVar5 + ((int)uVar5 >> 0x1f & 0xffffffU)) >> 0x18) +
          ((int)(uVar3 + ((int)uVar3 >> 0x1f & 0x3ffffU)) >> 0x12) +
          ((int)(uVar4 + ((int)uVar4 >> 0x1f & 0x3fU)) >> 6);
  if (0xffffff < uVar2) {
    uVar3 = uVar3 + ((int)uVar2 >> 0x18);
    uVar2 = uVar2 & 0xffffff;
  }
  uVar4 = *(uint *)(alu_core + 0x460);
  uVar5 = uVar4;
  if ((*(uint *)(alu_core + 0x45c) & 0x800000) == 0) {
    uVar5 = ~uVar4;
  }
  uVar5 = uVar5 >> 0x17 & 1;
  if (*(int *)(alu_core + 0x1cc) == 0) {
    uVar5 = (uint)(uVar5 == 0);
  }
  if ((uVar4 == 0) || (*(uint *)(alu_core + 0x45c) == 0)) {
    uVar5 = 1;
  }
  if (uVar5 == 1) {
    *(uint *)(alu_core + 0x480) = uVar2 * 2;
    *(uint *)(alu_core + 0x484) = uVar3 * 2;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0;
  }
  else {
    *(uint *)(alu_core + 0x480) = (~uVar2 & 0xffffff) * 2 + 2;
    *(uint *)(alu_core + 0x484) = (~uVar3 & 0xffffff) << 1;
    alu_norm_sum();
    *(undefined4 *)(alu_core + 0x488) = 0xff;
  }
  alu_round();
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_round @ 00433250 ==== */

void alu_round(void)

{
  alu_norm_sum();
  if ((alu_ccr & 0xc00) == 0x400) {
    alu_norm_sum();
    *(int *)(alu_core + 0x484) = *(int *)(alu_core + 0x484) + 1;
    alu_norm_sum();
    if ((*(int *)(alu_core + 0x480) == 0) && ((*(uint *)(alu_core + 0x484) & 1) == 0)) {
      *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x484) & 0xfffffc;
    }
    *(undefined4 *)(alu_core + 0x480) = 0;
    *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x484) & 0xfffffe;
    return;
  }
  if ((alu_ccr & 0xc00) != 0x800) {
    *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + 0x800000;
    alu_norm_sum();
    if (*(int *)(alu_core + 0x480) == 0) {
      *(uint *)(alu_core + 0x484) = *(uint *)(alu_core + 0x484) & 0xfffffe;
    }
    *(undefined4 *)(alu_core + 0x480) = 0;
    return;
  }
  *(int *)(alu_core + 0x480) = *(int *)(alu_core + 0x480) + 0x400000;
  alu_norm_sum();
  if ((*(uint *)(alu_core + 0x480) & 0x7fffff) == 0) {
    *(undefined4 *)(alu_core + 0x480) = 0;
  }
  *(uint *)(alu_core + 0x480) = *(uint *)(alu_core + 0x480) & 0x800000;
  return;
}


/* ==== alu_shift1 @ 00433360 ==== */

void __cdecl alu_shift1(void *core)

{
  uint uVar1;
  int src;
  uint uVar2;
  
  alu_core = core;
  alu_ccr = *(uint *)((int)core + 0x9c);
  uVar2 = (int)*(uint *)((int)core + 0x184) >> 8 & 7;
  src = (3 < uVar2) + 0x4d;
  *(uint *)((int)core + 0x1c8) = (*(uint *)((int)core + 0x184) & 8 | 0x960) >> 3;
  uVar1 = alu_ccr;
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_load_acc();
  if ((uVar1 & 0x20) == 0) {
    if (((uVar1 & 0x10) == 0) || ((uVar1 & 4) != 0)) {
      *(undefined4 *)((int)alu_core + 0x474) = *(undefined4 *)((int)alu_core + 0x468);
      *(undefined4 *)((int)alu_core + 0x478) = *(undefined4 *)((int)alu_core + 0x46c);
      *(undefined4 *)((int)alu_core + 0x47c) = *(undefined4 *)((int)alu_core + 0x470);
    }
    else {
      *(int *)((int)alu_core + 0x474) = *(int *)((int)alu_core + 0x468) << 1;
      *(int *)((int)alu_core + 0x478) = *(int *)((int)alu_core + 0x46c) << 1;
      *(int *)((int)alu_core + 0x47c) = *(int *)((int)alu_core + 0x470) << 1;
      alu_norm_res();
      *(uint *)((int)alu_core + src * 4) = *(int *)((int)alu_core + src * 4) - 1U & 0xffff;
      core_copy_reg(uVar2 + 0x1e,src);
      uVar1 = *(uint *)((int)alu_core + 0x47c) & 0x180;
      if ((uVar1 == 0x100) || (uVar1 == 0x80)) {
        alu_ccr = alu_ccr | 2;
      }
    }
  }
  else {
    *(int *)((int)alu_core + 0x47c) = *(int *)((int)alu_core + 0x470) / 2;
    if ((*(byte *)((int)alu_core + 0x470) & 0x80) != 0) {
      *(uint *)((int)alu_core + 0x47c) = *(uint *)((int)alu_core + 0x47c) | 0x80;
    }
    uVar1 = *(uint *)((int)alu_core + 0x46c);
    if (((byte)*(undefined4 *)((int)alu_core + 0x470) & 1) == 1) {
      uVar1 = uVar1 | 0x1000000;
    }
    *(int *)((int)alu_core + 0x478) = (int)uVar1 / 2;
    uVar1 = *(uint *)((int)alu_core + 0x468);
    if (((byte)*(undefined4 *)((int)alu_core + 0x46c) & 1) == 1) {
      uVar1 = uVar1 | 0x1000000;
    }
    *(int *)((int)alu_core + 0x474) = (int)uVar1 / 2;
    *(uint *)((int)alu_core + src * 4) = *(int *)((int)alu_core + src * 4) + 1U & 0xffff;
    core_copy_reg(uVar2 + 0x1e,src);
  }
  *(uint *)((int)alu_core + 0x47c) = *(uint *)((int)alu_core + 0x47c) & 0xff;
  *(undefined4 *)((int)alu_core + 0x480) = *(undefined4 *)((int)alu_core + 0x474);
  *(undefined4 *)((int)alu_core + 0x484) = *(undefined4 *)((int)alu_core + 0x478);
  *(undefined4 *)((int)alu_core + 0x488) = *(undefined4 *)((int)alu_core + 0x47c);
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_op_h4335a0 @ 004335a0 ==== */

void alu_op_h4335a0(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x490) = 0;
  *(undefined4 *)(alu_core + 0x48c) = 0;
  *(undefined4 *)(alu_core + 0x494) = 0;
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_set_ccr();
  return;
}


/* ==== alu_op_h433650 @ 00433650 ==== */

void alu_op_h433650(void)

{
  if (*(int *)(alu_core + 0x1bc) == 1) {
    alu_load_acc();
    return;
  }
  *(undefined4 *)(alu_core + 0x474) = *(undefined4 *)(alu_core + 0x468);
  *(undefined4 *)(alu_core + 0x478) = *(undefined4 *)(alu_core + 0x46c);
  *(undefined4 *)(alu_core + 0x47c) = *(undefined4 *)(alu_core + 0x470);
  *(undefined4 *)(alu_core + 0x494) = 0;
  *(undefined4 *)(alu_core + 0x480) = *(undefined4 *)(alu_core + 0x474);
  *(undefined4 *)(alu_core + 0x484) = *(undefined4 *)(alu_core + 0x478);
  *(undefined4 *)(alu_core + 0x488) = *(undefined4 *)(alu_core + 0x47c);
  alu_round();
  alu_ccr = alu_ccr & 0xffffffc1;
  alu_ovf_add();
  alu_set_ccr();
  alu_store_ext();
  return;
}


/* ==== alu_store_ext @ 00433700 ==== */

void alu_store_ext(void)

{
  int iVar1;
  
  *(uint *)(alu_core + 0x488) = *(uint *)(alu_core + 0x488) & 0xff;
  iVar1 = *(int *)(alu_core + 0x1c8);
  if (iVar1 == 300) {
    core_copy_reg_quiet(1,0x120);
    core_copy_reg_quiet(2,0x121);
    core_copy_reg(3,0x122);
    return;
  }
  if (iVar1 == 2) {
    core_copy_reg(2,0x121);
    return;
  }
  if (iVar1 == 0x12d) {
    core_copy_reg_quiet(5,0x120);
    core_copy_reg_quiet(6,0x121);
    core_copy_reg(7,0x122);
    return;
  }
  if (iVar1 == 6) {
    core_copy_reg(6,0x121);
  }
  return;
}


/* ==== alu_load_src @ 004337c0 ==== */

void __cdecl alu_load_src(int mode)

{
  ulong src;
  
  if ((*(int *)(alu_core + 0x1c8) == 300) || (*(int *)(alu_core + 0x1c8) == 2)) {
    core_read_copy(1,0x11a);
    core_read_copy(2,0x11b);
    src = 3;
  }
  else {
    core_read_copy(5,0x11a);
    core_read_copy(6,0x11b);
    src = 7;
  }
  core_read_copy(src,0x11c);
  if (mode == 0) {
    core_read_copy(*(ulong *)(alu_core + 0x1c0),0x117);
  }
  else {
    *(undefined4 *)(alu_core + 0x45c) =
         *(undefined4 *)(&DAT_004c4e50 + (*(int *)(alu_core + 0x1c0) >> 8 & 0x1fU) * 4);
  }
  core_read_copy(*(ulong *)(alu_core + 0x1c4),0x118);
  return;
}


/* ==== alu_set_ccr @ 00433890 ==== */

void alu_set_ccr(void)

{
  uint uVar1;
  uint uVar2;
  
  if (((*(int *)(alu_core + 0x480) == 0) && (*(int *)(alu_core + 0x484) == 0)) &&
     (*(char *)(alu_core + 0x488) == '\0')) {
    alu_ccr = alu_ccr | 4;
  }
  uVar2 = *(uint *)(alu_core + 0x488);
  if ((uVar2 & 0x80) != 0) {
    alu_ccr = alu_ccr | 8;
  }
  if ((alu_ccr & 2) != 0) {
    alu_ccr = alu_ccr | 0x40;
  }
  if ((alu_ccr & 0xc00) == 0x400) {
    if ((*(uint *)(alu_core + 0x484) & 0x800000) == 0x800000) {
      if (((byte)uVar2 & 1) == 1) {
LAB_00433978:
        alu_ccr = alu_ccr | 0x10;
      }
    }
    else if ((uVar2 & 1) == 0) goto LAB_00433978;
    uVar2 = uVar2 & 0xff;
    if (uVar2 == 0xff) goto LAB_0043398e;
  }
  else {
    uVar1 = *(uint *)(alu_core + 0x484);
    if ((alu_ccr & 0xc00) == 0x800) {
      if (((uVar1 & 0x600000) == 0x600000) || ((uVar1 & 0x600000) == 0)) {
        alu_ccr = alu_ccr | 0x10;
      }
      uVar2 = (uVar2 & 0xff) + (uVar1 & 0xc00000);
      if (uVar2 == 0xc000ff) goto LAB_0043398e;
    }
    else {
      if (((uVar1 & 0xc00000) == 0xc00000) || ((uVar1 & 0xc00000) == 0)) {
        alu_ccr = alu_ccr | 0x10;
      }
      uVar2 = (uVar2 & 0xff) + (uVar1 & 0x800000);
      if (uVar2 == 0x8000ff) goto LAB_0043398e;
    }
  }
  if (uVar2 != 0) {
    alu_ccr = alu_ccr | 0x20;
  }
LAB_0043398e:
  *(uint *)(alu_core + 0x9c) = alu_ccr;
  core_touch_reg(0x27);
  return;
}


/* ==== alu_load_acc @ 004339b0 ==== */

void alu_load_acc(void)

{
  if ((*(int *)(alu_core + 0x1c8) != 300) && (*(int *)(alu_core + 0x1c8) != 2)) {
    core_read_copy(5,0x11a);
    core_read_copy(6,0x11b);
    core_read_copy(7,0x11c);
    return;
  }
  core_read_copy(1,0x11a);
  core_read_copy(2,0x11b);
  core_read_copy(3,0x11c);
  return;
}


/* ==== alu_load_ops @ 00433a30 ==== */

void alu_load_ops(void)

{
  int iVar1;
  ulong uVar2;
  
  if ((*(int *)(alu_core + 0x1c8) == 300) || (*(int *)(alu_core + 0x1c8) == 2)) {
    core_read_copy(1,0x11a);
    core_read_copy(2,0x11b);
    uVar2 = 3;
  }
  else {
    core_read_copy(5,0x11a);
    core_read_copy(6,0x11b);
    uVar2 = 7;
  }
  core_read_copy(uVar2,0x11c);
  *(undefined4 *)(alu_core + 0x464) = 0;
  iVar1 = *(int *)(alu_core + 0x1c0);
  if (iVar1 < 7) {
    if (iVar1 != 6) {
      if (iVar1 != 2) {
        return;
      }
LAB_00433b85:
      core_read_copy(2,0x117);
      core_read_copy(1,0x118);
      core_read_copy(3,0x119);
      return;
    }
  }
  else {
    if (iVar1 < 0x12d) {
      if (iVar1 == 300) goto LAB_00433b85;
      switch(iVar1) {
      case 0x2b:
        uVar2 = 0x2b;
        break;
      case 0x2c:
        core_read_copy(0x2c,0x117);
        *(undefined4 *)(alu_core + 0x460) = 0;
        sign_ext_word(0x117,0x119);
        return;
      default:
        goto switchD_00433ae9_caseD_2d;
      case 0x2e:
        core_read_copy(0x2e,0x117);
        *(undefined4 *)(alu_core + 0x460) = 0;
        sign_ext_word(0x117,0x119);
        return;
      case 0x2f:
        uVar2 = 0x2f;
      }
      core_read_copy(uVar2,0x117);
      *(undefined4 *)(alu_core + 0x460) = 0;
      sign_ext_word(0x117,0x119);
      return;
    }
    if (iVar1 != 0x12d) {
      if (iVar1 == 0x130) {
        core_read_copy(0x2c,0x117);
        uVar2 = 0x2b;
      }
      else {
        if (iVar1 != 0x131) {
          return;
        }
        core_read_copy(0x2f,0x117);
        uVar2 = 0x2e;
      }
      core_read_copy(uVar2,0x118);
      sign_ext_word(0x117,0x119);
      return;
    }
  }
  core_read_copy(6,0x117);
  core_read_copy(5,0x118);
  core_read_copy(7,0x119);
switchD_00433ae9_caseD_2d:
  return;
}


/* ==== sign_ext_word @ 00433c50 ==== */

void __cdecl sign_ext_word(int src,int dst)

{
  if (0x7fffff < *(int *)(alu_core + src * 4)) {
    *(undefined4 *)(alu_core + dst * 4) = 0xff;
    return;
  }
  *(undefined4 *)(alu_core + dst * 4) = 0;
  return;
}


/* ==== alu_execute @ 00433c80 ==== */

void __cdecl alu_execute(void *core)

{
  alu_core = core;
  alu_ccr = *(undefined4 *)((int)core + 0x9c);
  alu_flag = 1;
  (**(code **)(&alu_handlers + *(int *)((int)core + 0x1b8) * 4))();
  if ((*(int *)((int)alu_core + 0x1bc) != 1) && (alu_flag != 0)) {
    *(undefined4 *)((int)alu_core + 0x9c) = alu_ccr;
    core_touch_reg(0x27);
  }
  return;
}


/* ==== alu_decode @ 00433ce0 ==== */

void __cdecl alu_decode(ulong opw,long *out)

{
  ulong uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  ulong uVar9;
  
  uVar1 = opw;
  uVar2 = opw & 0xff;
  uVar7 = opw & 8;
  uVar4 = (int)uVar2 >> 4 & 7;
  if ((opw & 0x80) == 0) {
    uVar8 = opw & 0xfffffe;
    if ((*(uint *)(cur_dtype + 8) < 4) || ((uVar8 != 8 && (uVar8 != 10)))) {
      if ((uVar2 == 4) || ((uVar2 == 8 || (iVar3 = (opw & 7) + uVar4 * 8, uVar2 == 0xc)))) {
        iVar3 = 0x40;
      }
      uVar6 = *(uint *)(&DAT_004c5068 + uVar2 * 4);
      uVar9 = *(ulong *)(&DAT_004c4f50 + iVar3 * 4);
      if ((&DAT_004c5268)[iVar3] == '\0') {
        uVar4 = 0xfffffffe;
        uVar2 = 0;
        lVar5 = -2;
        opw = uVar9;
      }
      else if (uVar7 == 0) {
        lVar5 = -2;
        uVar4 = (-(uint)(*(int *)(&DAT_004c52b0 + (opw & 0x7f) * 4) != 0) & 0xfffffed6) + 300;
        uVar2 = 0;
        opw = uVar9;
      }
      else {
        lVar5 = -2;
        uVar4 = (-(uint)(*(int *)(&DAT_004c52b0 + (opw & 0x7f) * 4) != 0) & 0xfffffed9) + 0x12d;
        uVar2 = 0;
        opw = uVar9;
      }
    }
    else {
      lVar5 = -2;
      uVar4 = opw & 1 | 300;
      uVar2 = 0;
      uVar6 = uVar4;
      opw = (uVar8 != 8) + 0x22;
    }
  }
  else {
    uVar2 = ((int)(char)~(byte)(opw & 7) & 4U) >> 2;
    if ((opw & 0xff00c0) == 0x100c0) {
      uVar6 = opw;
      opw = *(ulong *)(&DAT_004c54f0 + (opw & 3) * 4);
    }
    else {
      uVar6 = *(uint *)(&DAT_004c54b0 + uVar4 * 4);
      opw = *(ulong *)(&DAT_004c5058 + (opw & 3) * 4);
    }
    lVar5 = *(long *)(&DAT_004c54d0 + uVar4 * 4);
    uVar4 = (uVar7 != 0) + 300;
  }
  uVar9 = 0xc;
  if ((uVar1 & 0xffc0c0) != 0x18040) {
    uVar9 = opw;
  }
  *out = uVar9;
  out[1] = 1;
  out[2] = uVar6;
  out[3] = lVar5;
  out[4] = uVar4;
  out[5] = uVar2;
  return;
}


/* ==== periph_reset @ 00433e80 ==== */

void periph_reset(void)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar8 = 0;
  *(undefined4 *)(cur_dev + 0x44) = 0;
  *(undefined4 *)(cur_sim + 0x24) = 0;
  iVar6 = *(int *)(cur_dtype + 0x1c);
  if (0 < iVar6) {
    puVar4 = (undefined4 *)(*(int *)(cur_sim + 4) + 0x14);
    do {
      puVar4[0x23] = 0;
      *puVar4 = 0;
      puVar4 = puVar4 + 0x4b;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  iVar6 = *(int *)(cur_dtype + 0x14);
  if (0 < iVar6) {
    iVar7 = 0;
    do {
      iVar2 = *(int *)(cur_sim + 8);
      iVar5 = 0;
      iVar3 = *(int *)(*(int *)(*(int *)(cur_dtype + 0x18) + 0x2c + iVar7) + 0x28);
      if (0 < iVar3) {
        do {
          pbVar1 = (byte *)(*(int *)(iVar2 + iVar8 * 8 + 4) + 2 + iVar5 * 4);
          *pbVar1 = *pbVar1 & 0xf0;
          iVar5 = iVar5 + 1;
        } while (iVar5 < iVar3);
      }
      iVar8 = iVar8 + 1;
      iVar7 = iVar7 + 0x48;
    } while (iVar8 < iVar6);
  }
  return;
}


/* ==== periph_call @ 00433f10 ==== */

long __cdecl periph_call(int devidx,int periph,long a,long b)

{
  cur_dev = *(int **)(dev_tab + devidx * 4);
  cur_dtype = *(int *)(chiptype_tab + *cur_dev * 4);
  (*(code *)**(undefined4 **)(*(int *)(cur_dtype + 0x18) + 0x2c + periph * 0x48))(periph,a,b);
  return 1;
}


/* ==== periph_find_reg @ 00433f60 ==== */

long __cdecl periph_find_reg(int devidx,char *name,int *periph,int *reg)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int local_10;
  int local_8;
  
  cur_dev = *(int **)(dev_tab + devidx * 4);
  iVar9 = 0;
  local_10 = 0;
  iVar5 = *(int *)(chiptype_tab + *cur_dev * 4);
  iVar3 = *(int *)(iVar5 + 0x14);
  cur_dtype = iVar5;
  if (0 < iVar3) {
    do {
      iVar10 = *(int *)(*(int *)(iVar5 + 0x18) + 0x2c + iVar9);
      if (**(char **)(*(int *)(iVar5 + 0x18) + iVar9 + 0x30) == '\0') {
        iVar4 = *(int *)(iVar10 + 0x28);
        puVar7 = *(undefined4 **)(iVar10 + 0x2c);
        iVar10 = 0;
        if (0 < iVar4) {
          do {
            iVar5 = str_icmp((char *)*puVar7,name);
            if (iVar5 == 0) {
              *periph = local_10;
              *reg = iVar10;
              return 1;
            }
            iVar10 = iVar10 + 1;
            puVar7 = puVar7 + 7;
            iVar5 = cur_dtype;
          } while (iVar10 < iVar4);
        }
      }
      iVar9 = iVar9 + 0x48;
      local_10 = local_10 + 1;
    } while (local_10 < iVar3);
  }
  uVar6 = 0xffffffff;
  pcVar11 = name;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar1 != '\0');
  iVar9 = ~uVar6 - 2;
  cVar1 = name[iVar9];
  iVar3 = *(int *)(iVar5 + 0x14);
  local_10 = 0;
  if (iVar3 < 1) {
    return 0;
  }
  local_8 = 0;
  do {
    iVar10 = local_8 + *(int *)(iVar5 + 0x18);
    if (cVar1 == **(char **)(iVar10 + 0x30)) {
      iVar10 = *(int *)(iVar10 + 0x2c);
      iVar8 = 0;
      iVar4 = *(int *)(iVar10 + 0x28);
      puVar7 = *(undefined4 **)(iVar10 + 0x2c);
      if (0 < iVar4) {
        do {
          uVar6 = 0xffffffff;
          pcVar11 = (char *)*puVar7;
          do {
            if (uVar6 == 0) break;
            uVar6 = uVar6 - 1;
            cVar2 = *pcVar11;
            pcVar11 = pcVar11 + 1;
          } while (cVar2 != '\0');
          if ((~uVar6 - 1 == iVar9) && (iVar5 = str_nicmp((char *)*puVar7,name,iVar9), iVar5 == 0))
          {
            *periph = local_10;
            *reg = iVar8;
            return 1;
          }
          iVar8 = iVar8 + 1;
          puVar7 = puVar7 + 7;
          iVar5 = cur_dtype;
        } while (iVar8 < iVar4);
      }
    }
    local_10 = local_10 + 1;
    local_8 = local_8 + 0x48;
    if (iVar3 <= local_10) {
      return 0;
    }
  } while( true );
}


