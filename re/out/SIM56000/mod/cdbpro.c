/* ==== scan_saved_regs_56800 @ 0046e1a0 ==== */

char __cdecl scan_saved_regs_56800(ulong func_addr,int frame_base)

{
  char cVar1;
  int dev;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  char *extraout_EAX;
  ulong uVar6;
  uint uVar7;
  uint uVar8;
  uint b;
  char *pcVar9;
  int iVar10;
  char *pcVar11;
  int local_c;
  char *local_8;
  
  dev = *(int *)(cur_dev + 4);
  iVar10 = 0;
  local_c = 0;
  local_8 = (char *)0x0;
  iVar3 = cdb_func_of_pc(func_addr);
  iVar4 = cdb_func_bf_sym(iVar3);
  if ((iVar3 == -1) || (iVar4 == -1)) {
    return '\0';
  }
  uVar2 = *(uint *)(iVar4 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
  b = *(uint *)(iVar3 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
joined_r0x0046e203:
  uVar7 = b;
  pcVar9 = local_8;
  if (uVar2 <= uVar7) {
    for (; pcVar9 != (char *)0x0; pcVar9 = *(char **)(pcVar9 + 0x10)) {
      *(int *)(pcVar9 + 8) = *(int *)(pcVar9 + 8) + (frame_base - iVar10);
    }
    return (char)local_8;
  }
  b = uVar7 + 1;
  lVar5 = dev_mem_read(dev,0,uVar7,(long)&func_addr);
  if (lVar5 != 0) {
    iVar3 = opcode_tab_search(&DAT_00492928,0xd,func_addr);
    if (iVar3 != -1) {
      cdb_malloc(0x14);
      *(int *)(extraout_EAX + 8) = iVar10;
      *(undefined4 *)(extraout_EAX + 0xc) = *(undefined4 *)(&DAT_0049292c + iVar3 * 0xc);
      uVar7 = 0xffffffff;
      pcVar9 = (&PTR_DAT_00492930)[iVar3 * 3];
      do {
        pcVar11 = pcVar9;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      pcVar9 = pcVar11 + -uVar7;
      pcVar11 = extraout_EAX;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar11 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar11 = pcVar11 + 1;
      }
      extraout_EAX[0x10] = '\0';
      extraout_EAX[0x11] = '\0';
      extraout_EAX[0x12] = '\0';
      extraout_EAX[0x13] = '\0';
      if (local_8 != (char *)0x0) {
        *(char **)(extraout_EAX + 0x10) = local_8;
      }
      iVar10 = local_c + 1;
      local_c = iVar10;
      local_8 = extraout_EAX;
      goto joined_r0x0046e203;
    }
    if (func_addr != 0x3fdc) {
      if (((func_addr & 0xfc1f) == 0x3806) || (func_addr == 0x1e6)) {
        iVar10 = iVar10 + 1;
        local_c = iVar10;
      }
      goto joined_r0x0046e203;
    }
    lVar5 = dev_mem_read(dev,0,b,(long)&func_addr);
    if (lVar5 != 0) {
      uVar6 = func_addr;
      if ((func_addr & 0x8000) != 0) {
        uVar6 = func_addr | 0xffff0000;
      }
      lVar5 = dev_mem_read(dev,0,uVar7 + 2,(long)&func_addr);
      if (lVar5 == 0) goto LAB_0046e385;
      b = uVar7 + 3;
      if (func_addr != 0) goto joined_r0x0046e203;
      lVar5 = dev_mem_read(dev,0,uVar7 + 3,(long)&func_addr);
      if (lVar5 != 0) {
        b = uVar7 + 4;
        if (func_addr == 0x3611) {
          iVar10 = iVar10 + uVar6;
          local_c = iVar10;
        }
        goto joined_r0x0046e203;
      }
    }
  }
LAB_0046e385:
  cdb_c_error(s_error_reading_from_program_memor_004d406c);
  return '\0';
}


/* ==== scan_saved_regs_56000 @ 0046e3a0 ==== */

char __cdecl scan_saved_regs_56000(ulong func_addr,int frame_base)

{
  char cVar1;
  int dev;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  char *extraout_EAX;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  int iVar10;
  char *pcVar11;
  int local_c;
  char *local_8;
  
  dev = *(int *)(cur_dev + 4);
  iVar10 = 0;
  local_c = 0;
  local_8 = (char *)0x0;
  iVar3 = cdb_func_of_pc(func_addr);
  iVar4 = cdb_func_bf_sym(iVar3);
  if ((iVar3 == -1) || (iVar4 == -1)) {
    return '\0';
  }
  uVar2 = *(uint *)(iVar4 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
  uVar6 = *(uint *)(iVar3 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
joined_r0x0046e403:
  do {
    pcVar9 = local_8;
    if (uVar2 <= uVar6) {
joined_r0x0046e57c:
      for (; pcVar9 != (char *)0x0; pcVar9 = *(char **)(pcVar9 + 0x10)) {
        *(int *)(pcVar9 + 8) = *(int *)(pcVar9 + 8) + (frame_base - iVar10);
      }
      return (char)local_8;
    }
    uVar8 = uVar6 + 1;
    lVar5 = dev_mem_read(dev,0,uVar6,(long)&func_addr);
    if (lVar5 == 0) goto LAB_0046e5a9;
    iVar3 = opcode_tab_search(&DAT_004929c8,0x24,func_addr);
    if (iVar3 != -1) {
      cdb_malloc(0x14);
      *(int *)(extraout_EAX + 8) = iVar10;
      *(undefined4 *)(extraout_EAX + 0xc) = *(undefined4 *)(&DAT_004929cc + iVar3 * 0xc);
      uVar6 = 0xffffffff;
      pcVar9 = (&PTR_DAT_004929d0)[iVar3 * 3];
      do {
        pcVar11 = pcVar9;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar9 = pcVar11 + -uVar6;
      pcVar11 = extraout_EAX;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar11 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar11 = pcVar11 + 1;
      }
      extraout_EAX[0x10] = '\0';
      extraout_EAX[0x11] = '\0';
      extraout_EAX[0x12] = '\0';
      extraout_EAX[0x13] = '\0';
      if (local_8 != (char *)0x0) {
        *(char **)(extraout_EAX + 0x10) = local_8;
      }
      iVar10 = local_c + 1;
      uVar6 = uVar8;
      local_c = iVar10;
      local_8 = extraout_EAX;
      goto joined_r0x0046e403;
    }
    if ((func_addr & 0xff00ff) == 0x3e0000) {
      if (func_addr == 0x76f400) goto LAB_0046e4f8;
      uVar7 = uVar8;
      uVar8 = func_addr >> 8 & 0xff;
LAB_0046e520:
      lVar5 = dev_mem_read(dev,0,uVar7,(long)&func_addr);
      if (lVar5 != 0) {
        if (func_addr != 0x22d000) goto joined_r0x0046e57c;
        uVar6 = uVar7 + 2;
        lVar5 = dev_mem_read(dev,0,uVar7 + 1,(long)&func_addr);
        if (lVar5 != 0) {
          if (func_addr == 0x204e00) {
            iVar10 = iVar10 + uVar8;
            local_c = iVar10;
          }
          goto joined_r0x0046e403;
        }
      }
LAB_0046e5a9:
      cdb_c_error(s_error_reading_from_program_memor_004d406c);
      return '\0';
    }
    if (func_addr == 0x76f400) {
LAB_0046e4f8:
      uVar7 = uVar6 + 2;
      lVar5 = dev_mem_read(dev,0,uVar8,(long)&func_addr);
      uVar8 = func_addr;
      if (lVar5 == 0) goto LAB_0046e5a9;
      goto LAB_0046e520;
    }
    if ((((func_addr & 0xc0ffff) == 0x405e00) || ((func_addr & 0xf4ffff) == 0x405e00)) ||
       (uVar6 = uVar8, (func_addr & 0xffff3f) == 0x55e3c)) {
      iVar10 = iVar10 + 1;
      uVar6 = uVar8;
      local_c = iVar10;
    }
  } while( true );
}


/* ==== scan_saved_regs_96000 @ 0046e5c0 ==== */

char __cdecl scan_saved_regs_96000(ulong func_addr,int frame_base)

{
  char cVar1;
  int dev;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  char *extraout_EAX;
  char *extraout_EAX_00;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  char *pcVar10;
  char *pcVar11;
  int local_10;
  char *local_c;
  
  dev = *(int *)(cur_dev + 4);
  iVar8 = 0;
  local_10 = 0;
  local_c = (char *)0x0;
  iVar3 = cdb_func_of_pc(func_addr);
  iVar4 = cdb_func_bf_sym(iVar3);
  if ((iVar3 == -1) || (iVar4 == -1)) {
    return '\0';
  }
  uVar2 = *(uint *)(iVar4 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
  uVar6 = *(uint *)(iVar3 * 0x20 + 8 + *(int *)(cur_sim + 0x3fe0));
joined_r0x0046e627:
  pcVar10 = local_c;
  if (uVar2 <= uVar6) {
joined_r0x0046e7c9:
    for (; pcVar10 != (char *)0x0; pcVar10 = *(char **)(pcVar10 + 0x10)) {
      *(int *)(pcVar10 + 8) = *(int *)(pcVar10 + 8) + (frame_base - iVar8);
    }
    return (char)local_c;
  }
  uVar9 = uVar6 + 1;
  lVar5 = dev_mem_read(dev,0,uVar6,(long)&func_addr);
  if (lVar5 != 0) {
    iVar3 = opcode_tab_search(&DAT_00492b78,0x15c,func_addr);
    if (iVar3 != -1) {
      cdb_malloc(0x14);
      uVar6 = 0xffffffff;
      *(int *)(extraout_EAX + 8) = iVar8;
      iVar8 = iVar3 * 0xc;
      *(undefined4 *)(extraout_EAX + 0xc) = *(undefined4 *)(&DAT_00492b7c + iVar8);
      pcVar10 = (&PTR_DAT_00492b80)[iVar3 * 3];
      do {
        pcVar11 = pcVar10;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar11 = pcVar10 + 1;
        cVar1 = *pcVar10;
        pcVar10 = pcVar11;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar10 = pcVar11 + -uVar6;
      pcVar11 = extraout_EAX;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar11 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        pcVar11 = pcVar11 + 1;
      }
      extraout_EAX[0x10] = '\0';
      extraout_EAX[0x11] = '\0';
      extraout_EAX[0x12] = '\0';
      extraout_EAX[0x13] = '\0';
      if (local_c != (char *)0x0) {
        *(char **)(extraout_EAX + 0x10) = local_c;
      }
      local_c = extraout_EAX;
      if (*(ulong *)(&DAT_00492b84 + iVar8) == func_addr) {
        cdb_malloc(0x14);
        *(int *)(extraout_EAX_00 + 8) = local_10;
        *(undefined4 *)(extraout_EAX_00 + 0xc) = *(undefined4 *)(&DAT_00492b88 + iVar8);
        uVar6 = 0xffffffff;
        pcVar10 = (&PTR_DAT_00492b8c)[iVar3 * 3];
        do {
          pcVar11 = pcVar10;
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          pcVar11 = pcVar10 + 1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar11;
        } while (cVar1 != '\0');
        uVar6 = ~uVar6;
        pcVar10 = pcVar11 + -uVar6;
        pcVar11 = extraout_EAX_00;
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
          pcVar10 = pcVar10 + 4;
          pcVar11 = pcVar11 + 4;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *pcVar11 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          pcVar11 = pcVar11 + 1;
        }
        *(char **)(extraout_EAX_00 + 0x10) = extraout_EAX;
        local_c = extraout_EAX_00;
      }
      iVar8 = local_10 + 1;
      uVar6 = uVar9;
      local_10 = iVar8;
      goto joined_r0x0046e627;
    }
    if ((func_addr & 0xff80007f) != 0x800036) {
      if (((func_addr & 0xe00ffff8) == 0x2007a000) ||
         (uVar6 = uVar9, (func_addr & 0xfffff6ff) == 0x137a07c)) {
        iVar8 = iVar8 + 1;
        uVar6 = uVar9;
        local_10 = iVar8;
      }
      goto joined_r0x0046e627;
    }
    uVar7 = func_addr >> 7;
    lVar5 = dev_mem_read(dev,0,uVar9,(long)&func_addr);
    if (lVar5 != 0) {
      if (func_addr != 0xaea2000) goto joined_r0x0046e7c9;
      uVar9 = uVar6 + 3;
      lVar5 = dev_mem_read(dev,0,uVar6 + 2,(long)&func_addr);
      if (lVar5 == 0) goto LAB_0046e7f6;
      uVar6 = uVar9;
      if (func_addr == 0x15b3a000) {
        iVar8 = iVar8 + (uVar7 & 0xffff);
        local_10 = iVar8;
      }
      goto joined_r0x0046e627;
    }
  }
LAB_0046e7f6:
  cdb_c_error(s_error_reading_from_program_memor_004d406c);
  return '\0';
}


/* ==== opcode_tab_search @ 0046e810 ==== */

int __cdecl opcode_tab_search(void *tab,int count,ulong key)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = count + -1;
  iVar3 = 0;
  if (iVar4 < 0) {
    return -1;
  }
  do {
    iVar2 = (iVar4 + iVar3) / 2;
    uVar1 = *(uint *)((int)tab + iVar2 * 0xc);
    if (key < uVar1) {
      iVar4 = iVar2 + -1;
    }
    else {
      if (key <= uVar1) {
        if (*(ulong *)((int)tab + iVar2 * 0xc + -0xc) != key) {
          return iVar2;
        }
        return iVar2 + -1;
      }
      iVar3 = iVar2 + 1;
    }
  } while (iVar3 <= iVar4);
  return -1;
}


