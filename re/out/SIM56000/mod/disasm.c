/* ==== disassemble @ 00423b10 ==== */

int __cdecl disassemble(ulong *insn,char *text,long a3,long a4,void *info)

{
  char cVar1;
  int iVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  int *piStack_e8;
  int iStack_e4;
  char *pcStack_e0;
  char local_dc [100];
  int local_78 [30];
  
  dis_reset();
  local_dc[0] = '\0';
  iVar6 = 1;
  iVar2 = opclass_lookup(*insn,dis_cpu_level);
  iStack_e4 = (*(code *)(&dis_fmt_handlers)[iVar2])(*insn,local_78);
  if (0 < iStack_e4) {
    piStack_e8 = local_78;
    do {
      iVar2 = *piStack_e8;
      if (iVar2 != 0) {
        if (iVar2 == -2) {
          pcVar7 = &dis_hex_ea;
        }
        else {
          if (iVar2 != -3) {
            if (iVar2 == -4) {
              uVar3 = insn[1];
            }
            else {
              if (iVar2 != -5) {
                pcVar7 = (&dis_token_strings)[iVar2];
                goto LAB_00423c3a;
              }
              uVar3 = insn[1] + 1 & 0xffff;
            }
            fmt_hex24(uVar3,&dis_hex_c);
            uVar4 = 0xffffffff;
            pcVar7 = &DAT_004c16e8;
            do {
              pcVar9 = pcVar7;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar9 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar9;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            iVar2 = -1;
            pcVar7 = local_dc;
            do {
              pcVar8 = pcVar7;
              if (iVar2 == 0) break;
              iVar2 = iVar2 + -1;
              pcVar8 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar8;
            } while (cVar1 != '\0');
            pcVar7 = pcVar9 + -uVar4;
            pcVar9 = pcVar8 + -1;
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
              pcVar7 = pcVar7 + 4;
              pcVar9 = pcVar9 + 4;
            }
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar9 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              pcVar9 = pcVar9 + 1;
            }
            uVar4 = 0xffffffff;
            pcVar7 = &dis_hex_c;
            do {
              pcVar9 = pcVar7;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar9 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar9;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            iVar2 = -1;
            pcVar7 = local_dc;
            do {
              pcVar8 = pcVar7;
              if (iVar2 == 0) break;
              iVar2 = iVar2 + -1;
              pcVar8 = pcVar7 + 1;
              cVar1 = *pcVar7;
              pcVar7 = pcVar8;
            } while (cVar1 != '\0');
            pcVar7 = pcVar9 + -uVar4;
            pcVar9 = pcVar8 + -1;
            for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
              pcVar7 = pcVar7 + 4;
              pcVar9 = pcVar9 + 4;
            }
            iVar6 = 2;
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *pcVar9 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              pcVar9 = pcVar9 + 1;
            }
            goto LAB_00423c5f;
          }
          pcVar7 = &dis_hex_b;
        }
LAB_00423c3a:
        uVar4 = 0xffffffff;
        do {
          pcVar9 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar2 = -1;
        pcVar7 = local_dc;
        do {
          pcVar8 = pcVar7;
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        pcVar7 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        }
      }
LAB_00423c5f:
      piStack_e8 = piStack_e8 + 1;
      iStack_e4 = iStack_e4 + -1;
    } while (iStack_e4 != 0);
  }
  uVar3 = str_find_token(local_dc,&DAT_004c16b4,&pcStack_e0);
  if (uVar3 != 0) {
    uVar4 = 0xffffffff;
    pcVar7 = &DAT_004c16e4;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    local_dc[0] = '\0';
    iVar2 = -1;
    pcVar7 = local_dc;
    do {
      pcVar8 = pcVar7;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    uVar3 = *insn;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    fmt_hex24(uVar3,&dis_hex_c);
    uVar4 = 0xffffffff;
    pcVar7 = &DAT_004c16e8;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar2 = -1;
    pcVar7 = local_dc;
    do {
      pcVar8 = pcVar7;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar7 = &dis_hex_c;
    do {
      pcVar9 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    iVar2 = -1;
    pcVar7 = local_dc;
    do {
      pcVar8 = pcVar7;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    pcVar7 = pcVar9 + -uVar4;
    pcVar9 = pcVar8 + -1;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    iVar6 = 0;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_dc;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)text = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    text = text + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *text = *pcVar7;
    pcVar7 = pcVar7 + 1;
    text = text + 1;
  }
  if (info != (void *)0x0) {
    *(int *)((int)info + 0x74) = iVar6;
    dis_move_addrs(info,insn[1]);
  }
  return iVar6;
}


/* ==== dis_move_addrs @ 00423d90 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dis_move_addrs(void *info,ulong pc)

{
  *(uint *)((int)info + 0x78) = _dis_effect_flags;
  if ((_dis_effect_flags & 2) != 0) {
    dis_ea_addr(info,pc,dis_sel_b,dis_val_b,(ulong *)((int)info + 0x80));
  }
  if ((_dis_effect_flags & 4) != 0) {
    dis_ea_addr(info,pc,dis_sel_c,DAT_004dbebc,(ulong *)((int)info + 0x84));
  }
  if ((_dis_effect_flags & 1) != 0) {
    dis_ea_addr(info,pc,dis_sel_a,DAT_004dbec0,(ulong *)((int)info + 0x7c));
  }
  if ((_dis_effect_flags & 8) != 0) {
    dis_ea_addr(info,pc,dis_sel_b,dis_val_b,(ulong *)((int)info + 0x80));
  }
  if ((_dis_effect_flags & 0x20) != 0) {
    dis_ea_addr(info,pc,dis_sel_d,DAT_004dbec4,(ulong *)((int)info + 0x84));
  }
  if ((_dis_effect_flags & 0x10) != 0) {
    dis_ea_addr(info,pc,dis_sel_e,DAT_004dbec8,(ulong *)((int)info + 0x80));
  }
  return;
}


/* ==== dis_ea_addr @ 00423e90 ==== */

void __cdecl dis_ea_addr(void *info,ulong pc,ulong sel,ulong defval,ulong *out)

{
  ulong rn;
  ulong mn;
  uint uVar1;
  ulong nn;
  
  uVar1 = sel & 7;
  rn = *(ulong *)((int)info + uVar1 * 4 + 0x14);
  nn = *(ulong *)((int)info + uVar1 * 4 + 0x34);
  mn = *(ulong *)((int)info + uVar1 * 4 + 0x54);
  *out = defval;
  if (sel != 0x100) {
    if (sel == 0x2000) {
      *out = pc;
      return;
    }
    if (sel == 0x4000) {
      *out = pc + 1;
      return;
    }
    if ((sel & 0x8000) == 0) {
      if ((sel & 0x10000) != 0) {
        uVar1 = sel >> 3 & 3;
        if (uVar1 != 1) {
          nn = 1;
        }
        if ((uVar1 != 0) && (uVar1 != 2)) {
          dis_agu_addr(rn,nn,mn,0,out);
          return;
        }
        dis_agu_addr(rn,nn,mn,1,out);
      }
    }
    else {
      uVar1 = sel & 0x3c;
      if ((uVar1 == 0x30) || (uVar1 == 0x34)) {
        *out = pc;
        return;
      }
      uVar1 = uVar1 >> 3;
      if (uVar1 < 5) {
        *out = rn;
        return;
      }
      if (uVar1 == 5) {
        dis_agu_addr(rn,nn,mn,0,out);
        return;
      }
      if (uVar1 == 7) {
        dis_agu_addr(rn,1,mn,1,out);
        return;
      }
    }
  }
  return;
}


/* ==== dis_agu_addr @ 00423f90 ==== */

void __cdecl dis_agu_addr(ulong rn,ulong nn,ulong mn,int negate,ulong *out)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong v;
  uint uVar5;
  bool bVar6;
  
  iVar1 = negate;
  v = nn;
  if (negate != 0) {
    v = nn ^ 0xffff;
  }
  if (((mn & 0xc000) == 0x8000) && (3 < dis_cpu_level)) {
    bVar6 = true;
  }
  else {
    bVar6 = false;
  }
  if (((mn & 0x8000) != 0) && (!bVar6)) {
    *out = v + negate + rn & 0xffff;
    return;
  }
  if (mn == 0) {
    bitrev16(rn,&rn);
    bitrev16(v,&nn);
    bitrev16(nn + rn + iVar1,out);
    return;
  }
  uVar3 = 0x4000;
  uVar2 = mn & 0x4000;
  while (uVar2 == 0) {
    uVar3 = uVar3 >> 1;
    uVar2 = mn & uVar3;
  }
  uVar2 = v + negate + rn & 0xffff;
  if (!bVar6) {
    uVar3 = uVar3 * 2 - 1;
    bVar6 = (uVar3 & v) + negate + (uVar3 & rn) <= uVar3;
    uVar5 = v >> 0xf & 1;
    if (uVar5 == 0) {
      mn = mn ^ 0xffff;
    }
    uVar4 = uVar2 + uVar5 + mn & 0xffff;
    if (uVar5 == 0) {
      if (uVar3 < (uVar3 & mn) + (uVar3 & uVar2) || !bVar6) {
        uVar2 = uVar4;
      }
      *out = uVar2;
      return;
    }
    if (bVar6) {
      uVar2 = uVar4;
    }
    *out = uVar2;
    return;
  }
  *out = uVar2 & mn & 0x7fff | ~(mn & 0x7fff) & rn;
  return;
}


