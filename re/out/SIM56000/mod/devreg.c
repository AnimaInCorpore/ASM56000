/* ==== device_install @ 0041c140 ==== */

int __cdecl device_install(char *name,char *key)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  undefined **ppuVar12;
  bool bVar13;
  int local_4;
  
  if (name == (char *)0x0) {
    return -1;
  }
  local_4 = 0;
  puVar11 = (undefined4 *)chiptype_tab;
  if (0 < num_chiptypes) {
    do {
      if ((undefined4 *)*puVar11 == (undefined4 *)0x0) break;
      pbVar3 = *(byte **)*puVar11;
      pbVar10 = (byte *)name;
      do {
        bVar2 = *pbVar3;
        bVar13 = bVar2 < *pbVar10;
        if (bVar2 != *pbVar10) {
LAB_0041c195:
          iVar4 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
          goto LAB_0041c19a;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar3[1];
        bVar13 = bVar2 < pbVar10[1];
        if (bVar2 != pbVar10[1]) goto LAB_0041c195;
        pbVar3 = pbVar3 + 2;
        pbVar10 = pbVar10 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_0041c19a:
      if (iVar4 == 0) {
        return local_4;
      }
      local_4 = local_4 + 1;
      puVar11 = puVar11 + 1;
    } while (local_4 < num_chiptypes);
  }
  if (local_4 == num_chiptypes) {
    return -1;
  }
  iVar4 = 0;
  ppuVar12 = &keyed_dev_table;
  do {
    pbVar3 = *(byte **)*ppuVar12;
    pbVar10 = (byte *)name;
    do {
      bVar2 = *pbVar3;
      bVar13 = bVar2 < *pbVar10;
      if (bVar2 != *pbVar10) {
LAB_0041c1f1:
        iVar5 = (1 - (uint)bVar13) - (uint)(bVar13 != 0);
        goto LAB_0041c1f6;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar3[1];
      bVar13 = bVar2 < pbVar10[1];
      if (bVar2 != pbVar10[1]) goto LAB_0041c1f1;
      pbVar3 = pbVar3 + 2;
      pbVar10 = pbVar10 + 2;
    } while (bVar2 != 0);
    iVar5 = 0;
LAB_0041c1f6:
    if (iVar5 == 0) {
      pcVar6 = device_keygen(name);
      iVar5 = 0;
      bVar13 = true;
      pcVar7 = key;
      break;
    }
    ppuVar12 = ppuVar12 + 4;
    iVar4 = iVar4 + 1;
    if ((undefined **)0x4bf77f < ppuVar12) {
      return -1;
    }
  } while( true );
  while( true ) {
    iVar5 = iVar5 + 1;
    pcVar7 = pcVar7 + 1;
    if (8 < iVar5) break;
    if (*pcVar7 != pcVar7[(int)pcVar6 - (int)key]) {
      bVar13 = false;
      break;
    }
  }
  if (!bVar13) {
    return -1;
  }
  *(undefined **)(chiptype_tab + local_4 * 4) = (&keyed_dev_table)[iVar4 * 4];
  uVar8 = 0xffffffff;
  do {
    pcVar7 = key;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar7 = key + 1;
    cVar1 = *key;
    key = pcVar7;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  pcVar7 = pcVar7 + -uVar8;
  pcVar6 = s__004bf764 + iVar4 * 0x10;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar6 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *(char **)(*(int *)(chiptype_tab + local_4 * 4) + 0x4dc) = s__004bf764 + iVar4 * 0x10;
  *(undefined **)(itype_tab + local_4 * 4) = (&keyed_dev_aux)[iVar4];
  return local_4;
}


/* ==== device_keygen @ 0041c2c0 ==== */

char * __cdecl device_keygen(char *name)

{
  char cVar1;
  uint uVar2;
  uint extraout_EAX;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int c;
  char *pcVar6;
  uint uVar7;
  
  uVar3 = 0xffffffff;
  DAT_004dbdd0 = 0;
  pcVar6 = name;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  keygen_seed = 0x12d715;
  uVar5 = 0;
  uVar7 = 0;
  if (~uVar3 != 1) {
    uVar4 = 0;
    do {
      c = (int)name[uVar7];
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[c * 2] & 1;
      }
      else {
        uVar2 = _isctype(c,1);
      }
      if (uVar2 != 0) {
        c = tolower(c);
      }
      keygen_seed = keygen_seed + (c << (sbyte)((ulonglong)uVar4 % 0x17));
      keygen_step();
      uVar5 = uVar5 ^ extraout_EAX;
      uVar7 = uVar7 + 1;
      uVar4 = uVar4 + 5;
    } while (uVar7 < ~uVar3 - 1);
  }
  uVar5 = uVar5 >> 8;
  uVar3 = 0;
  do {
    do {
      keygen_step();
      keygen_step();
      uVar7 = (uVar5 ^ extraout_EAX_01 >> 8 ^ extraout_EAX_00 >> 8) & 0x7f;
      if (__mb_cur_max < 2) {
        uVar4 = *(ushort *)(_pctype + uVar7 * 2) & 0x107;
      }
      else {
        uVar4 = _isctype(uVar7,0x107);
      }
    } while (uVar4 == 0);
    if (__mb_cur_max < 2) {
      uVar4 = (byte)_pctype[uVar7 * 2] & 1;
    }
    else {
      uVar4 = _isctype(uVar7,1);
    }
    if (uVar4 != 0) {
      uVar7 = tolower(uVar7);
    }
    (&keygen_out)[uVar3] = (char)uVar7;
    uVar5 = uVar5 >> 1;
    uVar3 = uVar3 + 1;
  } while (uVar3 < 8);
  return &keygen_out;
}


/* ==== keygen_step @ 0041c400 ==== */

void keygen_step(void)

{
  ulong uVar1;
  
  uVar1 = keygen_mulmod(keygen_seed,keygen_mult);
  keygen_seed = (uVar1 + 1) % keygen_mod;
  return;
}


/* ==== keygen_mulmod @ 0041c430 ==== */

ulong __cdecl keygen_mulmod(ulong a,ulong b)

{
  return ((((a / keygen_base) * (b % keygen_base) + (b / keygen_base) * (a % keygen_base)) %
          keygen_base) * keygen_base + (b % keygen_base) * (a % keygen_base)) % keygen_mod;
}


/* ==== igrp_method_41c490 @ 0041c490 ==== */

/* WARNING: Type propagation algorithm not settling */

void igrp_method_41c490(int param_1,int param_2,ulong param_3,ulong param_4,ulong *param_5)

{
  int iVar1;
  ulong uVar2;
  ulong uStack_d4;
  uint uStack_d0;
  ulong uStack_cc;
  int iStack_c8;
  ulong auStack_c4 [47];
  uint uStack_8;
  uint uStack_4;
  
  iStack_c8 = cur_sim + 0x188;
  if (profiler_hook != (undefined *)0x0) {
    if (*(int *)(cur_sim + 0x48c) == 0) {
      if (DAT_004bf854 < 0) {
        periph_find_reg(0,&DAT_004b2924,&DAT_004bf850,&DAT_004bf854);
      }
      periph_call(param_1,DAT_004bf850,DAT_004bf854,(long)&uStack_d4);
      if (DAT_004bf85c < 0) {
        periph_find_reg(0,&DAT_004b2950,&DAT_004bf858,&DAT_004bf85c);
      }
      periph_call(param_1,DAT_004bf858,DAT_004bf85c,(long)&uStack_cc);
    }
    else {
      uStack_d4 = *(ulong *)(cur_sim + 0x480);
      uStack_cc = *(ulong *)(cur_sim + 0x484);
    }
    *param_5 = param_3;
    param_5[0x23] = uStack_d4;
    param_5[0x24] = uStack_cc;
    dev_mem_read(param_1,param_2,param_3,(long)&uStack_8);
    dev_mem_read(param_1,param_2,param_3 + 1,(long)&uStack_4);
    iVar1 = memmap_find(param_2,param_3);
    uStack_d0 = *(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar1 * 0x2c);
    iVar1 = memmap_find(0,0);
    if (((uStack_d0 & 0x10000000) != 0) &&
       ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0x24 + iVar1 * 0x2c) & 0x4000000) != 0)) {
      uStack_d0 = uStack_8 & 0xffff | (uStack_4 & 0xff) << 0x10;
      dev_mem_read(param_1,param_2,param_3 + 2,(long)&uStack_8);
      dev_mem_read(param_1,param_2,param_3 + 3,(long)&uStack_4);
      uStack_4 = uStack_8 & 0xffff | (uStack_4 & 3) << 0x10;
      uStack_8 = uStack_d0;
    }
    iVar1 = decode_insn(auStack_c4 + 1,uStack_d4,uStack_cc,auStack_c4);
    if ((iVar1 == 0) && (param_3 == param_4)) {
      auStack_c4[1] = 0xffffffff;
    }
    insn_stat_classify(param_5,auStack_c4 + 1);
    insn_stat_operands(param_5,auStack_c4 + 1);
    uVar2 = eval_cc(uStack_d4,param_5[0x22]);
    param_5[0x3a] = uVar2;
    uVar2 = param_5[4];
    if ((((((uVar2 == 0x2d) || (uVar2 == 0x2f)) || (uVar2 == 0x2e)) ||
         ((uVar2 == 0x30 || (uVar2 == 0x11)))) ||
        ((uVar2 == 0x12 || ((uVar2 == 0x13 || (uVar2 == 0x15)))))) &&
       (param_4 == ((param_5[3] & 4) != 0) + 1 + param_3)) {
      param_5[0x3a] = 0;
    }
    if (uVar2 == 0x23) {
      *(undefined4 *)(iStack_c8 + 0x2a0) = 1;
    }
  }
  return;
}


