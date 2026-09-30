/* ==== mem_reg_read @ 0042c4c0 ==== */

int __cdecl mem_reg_read(int id,ulong addr,ulong *out)

{
  uint uVar1;
  ulong addr_00;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ulong *pval;
  int iVar5;
  uint *puVar6;
  int iVar7;
  int local_20;
  ulong local_18 [6];
  
  if ((id < 0x1d) || (0x11c < id)) {
    if (id == 0x11d) {
      uVar2 = 0xffffff;
    }
    else {
      uVar2 = (-(uint)(id != 0x1c) & 0xff810000) + 0x7fffff;
    }
    uVar2 = addr & uVar2;
    *out = 0;
    switch(id) {
    case 3:
      uVar4 = mem_reg_read(2,uVar2,out);
      uVar2 = mem_reg_read(1,uVar2,out + 1);
      return uVar4 & uVar2;
    case 4:
      id = 0;
    case 0:
    case 1:
    case 2:
      id = mem_region_of(id,uVar2);
      break;
    case 9:
      uVar4 = mem_reg_read(0x17,uVar2,out);
      uVar2 = mem_reg_read(0x12,uVar2,out + 1);
      return uVar4 & uVar2;
    case 10:
      uVar4 = mem_reg_read(0x18,uVar2,out);
      uVar2 = mem_reg_read(0x13,uVar2,out + 1);
      return uVar4 & uVar2;
    }
    iVar5 = memmap_find(id,uVar2);
    iVar7 = *(int *)(cur_dtype + 0x20) + iVar5 * 0x2c;
    if (id < 0x13) {
      if ((id == 0x12) || (id == 0xd)) goto LAB_0042c769;
    }
    else if (id < 0x18) {
      if (id == 0x17) {
LAB_0042c769:
        if ((*(uint *)(cur_dtype + 8) & 0x3618) != 0) {
          *out = 5;
          return 1;
        }
        *out = *(ulong *)(*(int *)(cur_dev + 0x18) + 0x4a0);
        iVar7 = mdisk_read(*(int *)(cur_dev + 4),id,uVar2,out,0);
        return iVar7;
      }
      if ((id == 0x13) && ((*(uint *)(iVar7 + 0x18) & 0x10000) != 0)) {
        dev_spaces_call_8(uVar2,(long *)out,0);
        return 1;
      }
    }
    else {
      if (id == 0x1c) {
        iVar7 = mdisk_read(*(int *)(cur_dev + 4),0x1c,uVar2,out,0);
        return iVar7;
      }
      if (id == 0x11d) goto LAB_0042c769;
    }
    if ((*(uint *)(iVar7 + 0xc) <= uVar2) && (uVar2 <= *(uint *)(iVar7 + 0x10))) {
      *out = *(ulong *)(*(int *)(iVar5 * 0x10 + *(int *)(cur_dev + 0xc) + 8) +
                       (uVar2 - *(uint *)(iVar7 + 0xc)) * 4);
      return 1;
    }
    return 0;
  }
  uVar2 = id - 0x1d;
  uVar4 = uVar2 & 1;
  if ((uVar2 & 0x80) == 0) {
    iVar7 = *(int *)(&DAT_004c2930 + (uVar2 & 7) * 4);
  }
  else {
    iVar7 = *(int *)(&DAT_004c2950 + (uVar2 & 3) * 4);
  }
  if ((uVar2 & 0x40) == 0) {
    local_20 = 1;
    addr = addr & *(uint *)(&DAT_004c2970 + (uVar2 & 0x3f) * 4);
    if (7 < (uVar2 & 0x3f)) goto LAB_0042c558;
  }
  else {
    addr = addr & *(uint *)(&DAT_004c2960 + ((int)uVar2 >> 3 & 3U) * 4);
  }
  local_20 = iVar7;
LAB_0042c558:
  iVar5 = 0;
  if (0 < iVar7) {
    pval = local_18;
    do {
      addr_00 = reg_field_pack(id,addr,iVar5);
      mdisk_read(*(int *)(cur_dev + 4),0x1c,addr_00,pval,0);
      iVar5 = iVar5 + 1;
      pval = pval + 1;
    } while (iVar5 < iVar7);
  }
  uVar3 = 0;
  if (-1 < iVar7 + -1) {
    puVar6 = local_18 + iVar7 + -1;
    do {
      uVar1 = *puVar6;
      puVar6 = puVar6 + -1;
      uVar3 = uVar3 << (-(uVar4 != 0) & 4U) + 4 | (-(uint)(uVar4 != 0) & 0xf0) + 0xf & uVar1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  if ((uVar4 != 0) && ((uVar2 & 0x80) != 0)) {
    uVar3 = uVar3 >> 4;
  }
  *out = uVar3;
  return local_20;
}


/* ==== reg_field_pack @ 0042c7f0 ==== */

ulong __cdecl reg_field_pack(int id,ulong val,int idx)

{
  uint uVar1;
  uint3 uVar2;
  uint uVar3;
  
  uVar3 = id - 0x1d;
  uVar1 = idx + val;
  if ((uVar3 & 0x40) != 0) {
    uVar3 = (int)uVar3 >> 3 & 3;
    return uVar1 << (3U - (char)uVar3 & 0x1f) & 0xfffff800 |
           *(uint *)(&DAT_004c2a70 + uVar3 * 4) & uVar1;
  }
  uVar2 = (uint3)(val >> 8);
  if ((uVar3 & 0x80) != 0) {
    switch(id) {
    case 0xa7:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      goto LAB_0042ca30;
    case 0xa8:
      goto switchD_0042c850_caseD_a8;
    case 0xa9:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      goto LAB_0042ca4d;
    case 0xaa:
      goto switchD_0042c850_caseD_aa;
    default:
      goto switchD_0042c850_caseD_ab;
    case 0xaf:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      goto LAB_0042cb43;
    case 0xb0:
      goto switchD_0042c850_caseD_b0;
    case 0xb1:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      goto LAB_0042cb7b;
    case 0xb2:
      goto switchD_0042c850_caseD_b2;
    case 0xb7:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      if ((uVar3 & DAT_004c2a80) != 0) {
        return val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0xffff8000) + 0x10000;
      }
      break;
    case 0xb8:
      if ((val & 1) != 0) {
        return val >> 1 | (-(uint)(idx != 0) & 0xffff8000) + 0x10000;
      }
      return val >> 1 | (-(uint)(idx != 0) & 0xfffe0000) + 0x40000;
    case 0xb9:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      if ((uVar3 & DAT_004c2a84) == 0) {
        return (uint)((uVar3 & DAT_004c2a80) != 0) | val * 2 |
               (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0xfffe0000) + 0x40000;
      }
      uVar1 = (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0xffff8000) + 0x10000;
      goto LAB_0042cdb7;
    case 0xba:
      uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
      if ((uVar3 & DAT_004c2a80) != 0) {
        return val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0xffff8000) + 0x10000;
      }
      break;
    case 0xbf:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      goto LAB_0042cef9;
    case 0xc0:
      return -(uint)(idx != 0) & 0x800 | val & 0xff | (uint)uVar2 << 0xc;
    case 0xc1:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      goto LAB_0042ce59;
    case 0xc2:
      goto switchD_0042c850_caseD_c2;
    case 199:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      goto LAB_0042d023;
    case 200:
      goto switchD_0042c850_caseD_c8;
    case 0xc9:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      goto LAB_0042cf80;
    case 0xca:
      goto switchD_0042c850_caseD_ca;
    case 0xcf:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      goto LAB_0042d14f;
    case 0xd0:
      goto switchD_0042c850_caseD_d0;
    case 0xd1:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      goto LAB_0042d0ac;
    case 0xd2:
      goto switchD_0042c850_caseD_d2;
    case 0xd7:
      uVar3 = *(uint *)(&DAT_004c28e4 + idx * 4);
      goto LAB_0042d27c;
    case 0xd8:
      goto switchD_0042c850_caseD_d8;
    case 0xd9:
      uVar3 = *(uint *)(&DAT_004c28f4 + idx * 4);
      goto LAB_0042d1c3;
    case 0xda:
      goto switchD_0042c850_caseD_da;
    }
    return val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0xfffe0000) + 0x40000;
  }
  switch(id) {
  case 0x1e:
  case 0x26:
  case 0x56:
    goto switchD_0042ca1a_caseD_1e;
  default:
    goto switchD_0042c850_caseD_ab;
  case 0x25:
  case 0x28:
switchD_0042c850_caseD_a8:
    return val * 2 | idx;
  case 0x27:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
LAB_0042ca30:
    uVar1 = -(uint)((uVar3 & DAT_004c2a80) != 0) & 2;
LAB_0042cbfd:
    return uVar1 | (uVar3 & DAT_004c2a84) != 0 | val << 2;
  case 0x29:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
LAB_0042ca4d:
    return (uint)((uVar3 & DAT_004c2a88) != 0) | -(uint)((uVar3 & DAT_004c2a84) != 0) & 2 |
           -(uint)((uVar3 & DAT_004c2a80) != 0) & 4 | val << 3;
  case 0x2a:
switchD_0042c850_caseD_aa:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
LAB_0042cadc:
    return -(uint)((uVar3 & DAT_004c2a80) != 0) & 2 | (uint)((uVar3 & DAT_004c2a84) != 0) | val * 4;
  case 0x2b:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4);
    return -(uint)((uVar3 & DAT_004c2a80) != 0) & 4 | -(uint)((uVar3 & DAT_004c2a84) != 0) & 2 |
           (uint)((uVar3 & DAT_004c2a88) != 0) | val << 3;
  case 0x2c:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
    goto LAB_0042cadc;
  case 0x2d:
  case 0x30:
switchD_0042c850_caseD_b0:
    return (-(uint)(idx != 0) & 0x20000) + 0x20000 | val;
  case 0x2e:
    return val >> 1 | (-(uint)((val & 1) != 0) & 0x20000) + 0x20000;
  case 0x2f:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
LAB_0042cb43:
    return (uint)((uVar3 & DAT_004c2a80) != 0) |
           (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0x20000) + 0x20000 | val * 2;
  case 0x31:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
LAB_0042cb7b:
    return (uint)((uVar3 & DAT_004c2a84) != 0) |
           (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0x20000) + 0x20000 |
           -(uint)((uVar3 & DAT_004c2a80) != 0) & 2 | val << 2;
  case 0x32:
switchD_0042c850_caseD_b2:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
LAB_0042cc1a:
    return (uint)((uVar3 & DAT_004c2a80) != 0) |
           (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0x20000) + 0x20000 | val * 2;
  case 0x33:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4);
    uVar1 = -(uint)((uVar3 & DAT_004c2a80) != 0) & 2 |
            (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0x20000) + 0x20000;
    goto LAB_0042cbfd;
  case 0x34:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
    goto LAB_0042cc1a;
  case 0x35:
    if ((val & 1) != 0) {
      return val >> 1 | (-(uint)(idx != 0) & 0x8000) + 0x68000;
    }
    goto LAB_0042cd00;
  case 0x36:
    if ((val & 1) != 0) {
      return val >> 2 | (-(uint)((val & 2) != 0) & 0x8000) + 0x68000;
    }
    return val >> 2 | (-(uint)((val & 2) != 0) & 0x20000) + 0x38000;
  case 0x37:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
    if ((uVar3 & DAT_004c2a80) != 0) {
      return val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0x8000) + 0x68000;
    }
    break;
  case 0x38:
    if ((val & 1) != 0) {
      return val >> 1 | (-(uint)(idx != 0) & 0x8000) + 0x68000;
    }
LAB_0042cd00:
    return val >> 1 | (-(uint)(idx != 0) & 0x20000) + 0x38000;
  case 0x39:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
    if ((uVar3 & DAT_004c2a84) != 0) {
      uVar1 = (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0x8000) + 0x68000;
      goto LAB_0042cdb7;
    }
    goto LAB_0042cda5;
  case 0x3a:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
    if ((uVar3 & DAT_004c2a80) != 0) {
      return val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0x8000) + 0x68000;
    }
    break;
  case 0x3b:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4);
    if ((uVar3 & DAT_004c2a84) != 0) {
      uVar1 = (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0x8000) + 0x68000;
      goto LAB_0042cdb7;
    }
LAB_0042cda5:
    uVar1 = (-(uint)((uVar3 & DAT_004c2a88) != 0) & 0x20000) + 0x38000;
LAB_0042cdb7:
    return (uint)((uVar3 & DAT_004c2a80) != 0) | val * 2 | uVar1;
  case 0x3c:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
    if ((uVar3 & DAT_004c2a80) != 0) {
      return val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0x8000) + 0x68000;
    }
    break;
  case 0x3d:
  case 0x40:
    return -(uint)(idx != 0) & 0x800 | val & 0xff | (uint)uVar2 << 0xc;
  case 0x3e:
    return val & 0xff | (uint)uVar2 << 0xb;
  case 0x3f:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
    goto LAB_0042cef9;
  case 0x41:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
LAB_0042ce59:
    uVar3 = -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x2000 |
            -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x1000 |
            -(uint)((uVar3 & DAT_004c2a88) != 0) & 0x800;
LAB_0042cedd:
    return uVar3 | val & 0xff | (uint)uVar2 << 0xe;
  case 0x42:
switchD_0042c850_caseD_c2:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
    goto LAB_0042cef9;
  case 0x43:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a80;
    uVar3 = -(uint)((*(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a84) != 0) & 0x1000 |
            -(uint)(uVar3 != 0) & 0x2000 | -(uint)(uVar3 != 0) & 0x800;
    goto LAB_0042cedd;
  case 0x44:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
LAB_0042cef9:
    return -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x1000 |
           -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x800 | val & 0xff | (uint)uVar2 << 0xd;
  case 0x45:
  case 0x48:
switchD_0042c850_caseD_c8:
    return -(uint)(idx != 0) & 0x800 | (val & 0xfffffe00) << 3 | val & 0x1ff;
  case 0x46:
    return (val & 0xfffffe00) << 2 | val & 0x1ff;
  case 0x47:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
    goto LAB_0042d023;
  case 0x49:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
LAB_0042cf80:
    uVar3 = -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x2000 |
            -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x1000 |
            -(uint)((uVar3 & DAT_004c2a88) != 0) & 0x800;
LAB_0042d004:
    return uVar3 | (val & 0xfffffe00) << 5 | val & 0x1ff;
  case 0x4a:
switchD_0042c850_caseD_ca:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
    goto LAB_0042d023;
  case 0x4b:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a80;
    uVar3 = -(uint)((*(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a84) != 0) & 0x1000 |
            -(uint)(uVar3 != 0) & 0x2000 | -(uint)(uVar3 != 0) & 0x800;
    goto LAB_0042d004;
  case 0x4c:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
LAB_0042d023:
    return -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x1000 |
           -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x800 | (val & 0xfffffe00) << 4 | val & 0x1ff;
  case 0x4d:
  case 0x50:
switchD_0042c850_caseD_d0:
    return -(uint)(idx != 0) & 0x800 | (val & 0xfffffc00) << 2 | val & 0x3ff;
  case 0x4e:
    return (val & 0xfffffc00) << 1 | val & 0x3ff;
  case 0x4f:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
    goto LAB_0042d14f;
  case 0x51:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
LAB_0042d0ac:
    uVar3 = -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x2000 |
            -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x1000 |
            -(uint)((uVar3 & DAT_004c2a88) != 0) & 0x800;
LAB_0042d130:
    return uVar3 | (val & 0xfffffc00) << 4 | val & 0x3ff;
  case 0x52:
switchD_0042c850_caseD_d2:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
    goto LAB_0042d14f;
  case 0x53:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a80;
    uVar3 = -(uint)((*(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a84) != 0) & 0x1000 |
            -(uint)(uVar3 != 0) & 0x2000 | -(uint)(uVar3 != 0) & 0x800;
    goto LAB_0042d130;
  case 0x54:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
LAB_0042d14f:
    return -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x1000 |
           -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x800 | (val & 0xfffffc00) << 3 | val & 0x3ff;
  case 0x55:
  case 0x58:
switchD_0042c850_caseD_d8:
    return -(uint)(idx != 0) & 0x800 | (val & 0xfffff800) << 1 | val & 0x7ff;
  case 0x57:
    uVar3 = *(uint *)(&DAT_004c28e0 + idx * 4);
    goto LAB_0042d27c;
  case 0x59:
    uVar3 = *(uint *)(&DAT_004c28f0 + idx * 4);
LAB_0042d1c3:
    return -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x2000 |
           -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x1000 |
           -(uint)((uVar3 & DAT_004c2a88) != 0) & 0x800 | (val & 0xfffff800) << 3 | val & 0x7ff;
  case 0x5a:
switchD_0042c850_caseD_da:
    uVar3 = *(uint *)(&DAT_004c2908 + idx * 4);
    goto LAB_0042d27c;
  case 0x5b:
    uVar3 = *(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a80;
    return -(uint)((*(uint *)(&DAT_004c2918 + idx * 4) & DAT_004c2a84) != 0) & 0x1000 |
           -(uint)(uVar3 != 0) & 0x2000 | -(uint)(uVar3 != 0) & 0x800 | (val & 0xfffff800) << 3 |
           val & 0x7ff;
  case 0x5c:
    uVar3 = *(uint *)(&DAT_004c2928 + idx * 4);
LAB_0042d27c:
    uVar1 = -(uint)((uVar3 & DAT_004c2a80) != 0) & 0x1000 |
            -(uint)((uVar3 & DAT_004c2a84) != 0) & 0x800 | (val & 0xfffff800) << 2 | val & 0x7ff;
switchD_0042c850_caseD_ab:
    return uVar1;
  }
  val = val | (-(uint)((uVar3 & DAT_004c2a84) != 0) & 0x20000) + 0x38000;
switchD_0042ca1a_caseD_1e:
  return val;
}


/* ==== mem_write_n @ 0042d460 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int mem_write_n(int id,long a2,long a3,ulong addr,ulong count,ulong val)

{
  uint uVar1;
  int iVar2;
  
  if ((id < 0x1d) || (0x24 < id)) {
    iVar2 = 1;
  }
  else {
    iVar2 = *(int *)(&DAT_004c2a1c + id * 4);
  }
  uVar1 = 0;
  if (a3 != 0) {
    do {
      mem_reg_write(id,a2,addr);
      uVar1 = uVar1 + iVar2;
      a2 = a2 + iVar2;
    } while (uVar1 < (uint)a3);
  }
  return iVar2;
}


/* ==== mem_region_of @ 0042d4c0 ==== */

int __cdecl mem_region_of(int space,ulong addr)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint local_8;
  uint local_4;
  
  uVar1 = *(uint *)(cur_dtype + 8);
  uVar2 = *(uint *)(**(int **)(cur_dev + 8) + 0x1b0);
  uVar6 = uVar2 & 3;
  uVar5 = uVar2 & 4;
  if ((uVar1 & 0x3400) == 0) {
    if ((uVar1 & 0x210) != 0) {
      local_4 = 0;
      local_8 = 0;
      if ((uVar1 & 0x10) != 0) {
        local_8 = 0xf00;
        local_4 = 0x600;
      }
      if ((uVar1 & 0x200) != 0) {
        local_8 = 0x1900;
        local_4 = 0x500;
      }
      switch(space) {
      case 0:
      case 4:
        if (uVar5 == 0) {
          return (-(uint)(addr < local_8) & 2) + 0xd;
        }
        if ((0x3ff < addr) && (addr < local_4)) {
          return 0xd;
        }
        iVar4 = memmap_find(0xe,addr);
        if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0xc + iVar4 * 0x2c) <= addr) &&
           (addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + iVar4 * 0x2c + 0x10))) {
          return 0xe;
        }
        iVar4 = memmap_find(0xf,addr);
        if (addr < *(uint *)(*(int *)(cur_dtype + 0x20) + 0xc + iVar4 * 0x2c)) {
          return 0xd;
        }
        if (*(uint *)(*(int *)(cur_dtype + 0x20) + iVar4 * 0x2c + 0x10) < addr) {
          return 0xd;
        }
        return 0xf;
      case 1:
        uVar5 = 1;
        break;
      case 2:
        if (((uVar5 == 0) || (addr < 0x400)) || (0x7ff < addr)) {
          iVar4 = memmap_find(0x18,addr);
          if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0xc + iVar4 * 0x2c) <= addr) &&
             (addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + iVar4 * 0x2c + 0x10))) {
            return 0x18;
          }
          iVar4 = memmap_find(0x19,addr);
          if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0xc + iVar4 * 0x2c) <= addr) &&
             (addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + iVar4 * 0x2c + 0x10))) {
            return 0x19;
          }
        }
        goto LAB_0042da24;
      case 3:
        break;
      default:
        goto switchD_0042d507_default;
      }
    }
switchD_0042d507_caseD_3:
    switch(space) {
    case 0:
    case 4:
      if ((((((uVar1 & 0x100) != 0) && ((uVar6 == 3 || (uVar6 == 2)))) || (uVar6 == 1)) ||
          ((3 < uVar1 && ((uVar2 & 0x10) != 0)))) &&
         ((iVar4 = memmap_find(0xf,addr), iVar4 != 0 &&
          (iVar4 = memmap_find(0xf,addr),
          addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10 + iVar4 * 0x2c))))) {
        return 0xf;
      }
      if ((uVar6 != 3) &&
         (iVar4 = memmap_find(0xe,addr),
         addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10 + iVar4 * 0x2c))) {
        return 0xe;
      }
      return 0xd;
    case 1:
      iVar4 = memmap_find(0x13,addr);
      if ((*(uint *)(*(int *)(cur_dtype + 0x20) + 0xc + iVar4 * 0x2c) <= addr) &&
         (addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + iVar4 * 0x2c + 0x10))) {
        return 0x13;
      }
      if ((uVar5 != 0) &&
         (iVar4 = memmap_find(0x14,addr),
         addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10 + iVar4 * 0x2c))) {
        return 0x14;
      }
      return 0x12;
    case 2:
      if (((uVar2 & 8) == 0) || (uVar1 < 4)) {
        iVar4 = memmap_find(0x18,addr);
        if (addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10 + iVar4 * 0x2c)) {
          return 0x18;
        }
        if ((uVar5 != 0) &&
           (iVar4 = memmap_find(0x19,addr),
           addr <= *(uint *)(*(int *)(cur_dtype + 0x20) + 0x10 + iVar4 * 0x2c))) {
          return 0x19;
        }
      }
      break;
    default:
      goto switchD_0042d507_default;
    }
  }
  else {
    switch(space) {
    case 0:
    case 4:
      iVar3 = memmap_find(0xe,addr);
      iVar4 = *(int *)(cur_dtype + 0x20) + iVar3 * 0x2c;
      if (((*(uint *)(iVar4 + 0xc) <= addr) && (addr <= *(uint *)(iVar4 + 0x10))) &&
         (*(int *)(*(int *)(cur_dev + 0xc) + 0xc + iVar3 * 0x10) == 0)) {
        return 0xe;
      }
      iVar3 = memmap_find(0xf,addr);
      iVar4 = *(int *)(cur_dtype + 0x20) + iVar3 * 0x2c;
      if (((*(uint *)(iVar4 + 0xc) <= addr) && (addr <= *(uint *)(iVar4 + 0x10))) &&
         (*(int *)(*(int *)(cur_dev + 0xc) + 0xc + iVar3 * 0x10) == 0)) {
        return 0xf;
      }
      return 0xd;
    case 1:
      iVar3 = memmap_find(0x13,addr);
      iVar4 = *(int *)(cur_dtype + 0x20) + iVar3 * 0x2c;
      if (((*(uint *)(iVar4 + 0xc) <= addr) && (addr <= *(uint *)(iVar4 + 0x10))) &&
         (*(int *)(*(int *)(cur_dev + 0xc) + 0xc + iVar3 * 0x10) == 0)) {
        return 0x13;
      }
      iVar3 = memmap_find(0x14,addr);
      iVar4 = *(int *)(cur_dtype + 0x20) + iVar3 * 0x2c;
      if (((*(uint *)(iVar4 + 0xc) <= addr) && (addr <= *(uint *)(iVar4 + 0x10))) &&
         (*(int *)(*(int *)(cur_dev + 0xc) + 0xc + iVar3 * 0x10) == 0)) {
        return 0x14;
      }
      return 0x12;
    case 2:
      iVar3 = memmap_find(0x18,addr);
      iVar4 = *(int *)(cur_dtype + 0x20) + iVar3 * 0x2c;
      if (((*(uint *)(iVar4 + 0xc) <= addr) && (addr <= *(uint *)(iVar4 + 0x10))) &&
         (*(int *)(*(int *)(cur_dev + 0xc) + 0xc + iVar3 * 0x10) == 0)) {
        return 0x18;
      }
      iVar3 = memmap_find(0x19,addr);
      iVar4 = *(int *)(cur_dtype + 0x20) + iVar3 * 0x2c;
      if (((*(uint *)(iVar4 + 0xc) <= addr) && (addr <= *(uint *)(iVar4 + 0x10))) &&
         (*(int *)(*(int *)(cur_dev + 0xc) + 0xc + iVar3 * 0x10) == 0)) {
        return 0x19;
      }
      break;
    case 3:
      goto switchD_0042d507_caseD_3;
    default:
      goto switchD_0042d507_default;
    }
  }
LAB_0042da24:
  space = 0x17;
switchD_0042d507_default:
  return space;
}


/* ==== mem_reg_write @ 0042da70 ==== */

int __cdecl mem_reg_write(int id,ulong addr,ulong val)

{
  ulong addr_00;
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  ulong uVar4;
  int iVar5;
  uint val_00;
  ulong *puVar6;
  int iVar7;
  uint local_18 [6];
  
  iVar7 = id;
  val_00 = *(uint *)val & 0xffffff;
  if ((id < 0x1d) || (0x11c < id)) {
    if (id == 0x11d) {
      uVar1 = 0xffffff;
    }
    else {
      uVar1 = (-(uint)(id != 0x1c) & 0xff810000) + 0x7fffff;
    }
    uVar1 = addr & uVar1;
    switch(id) {
    case 3:
      mem_reg_write(2,uVar1,val);
      mem_reg_write(1,uVar1,val + 4);
      return 1;
    case 4:
      id = 0;
    case 0:
    case 1:
    case 2:
      id = mem_region_of(id,uVar1);
      break;
    case 9:
      mem_reg_write(0x17,uVar1,val);
      mem_reg_write(0x12,uVar1,val + 4);
      return 1;
    case 10:
      mem_reg_write(0x18,uVar1,val);
      mem_reg_write(0x13,uVar1,val + 4);
      return 1;
    }
    iVar5 = memmap_find(id,uVar1);
    iVar7 = *(int *)(cur_dtype + 0x20) + iVar5 * 0x2c;
    if (id < 0x13) {
      if ((id != 0x12) && (id != 0xd)) {
LAB_0042dcdf:
        if ((((*(uint *)(iVar7 + 0x18) & 0x800000) == 0) && (*(uint *)(iVar7 + 0xc) <= uVar1)) &&
           (uVar1 <= *(uint *)(iVar7 + 0x10))) {
          *(uint *)(*(int *)(*(int *)(cur_dev + 0xc) + iVar5 * 0x10 + 8) +
                   (uVar1 - *(uint *)(iVar7 + 0xc)) * 4) = val_00;
          return 1;
        }
        return 1;
      }
    }
    else if (id < 0x18) {
      if (id != 0x17) {
        if ((id == 0x13) && ((*(uint *)(iVar7 + 0x18) & 0x10000) != 0)) {
          dev_spaces_call_c(uVar1,*(long *)val,0);
          return 1;
        }
        goto LAB_0042dcdf;
      }
    }
    else {
      if (id == 0x1c) {
        iVar7 = *(int *)(cur_dev + 4);
        id = 0x1c;
        goto override_prt_42dd2e_d659ec56;
      }
      if (id != 0x11d) goto LAB_0042dcdf;
    }
    if ((*(uint *)(cur_dtype + 8) & 0x3618) != 0) {
      return 1;
    }
    iVar7 = *(int *)(cur_dev + 4);
override_prt_42dd2e_d659ec56:
    mdisk_write(iVar7,id,uVar1,val_00,0);
    return 1;
  }
  uVar1 = id - 0x1d;
  uVar2 = uVar1 & 1;
  if ((uVar1 & 0x80) == 0) {
    uVar4 = *(ulong *)(&DAT_004c2930 + (uVar1 & 7) * 4);
  }
  else {
    uVar4 = *(ulong *)(&DAT_004c2950 + (uVar1 & 3) * 4);
  }
  if ((uVar1 & 0x40) == 0) {
    val = 1;
    addr = addr & *(uint *)(&DAT_004c2970 + (uVar1 & 0x3f) * 4);
    if (7 < (uVar1 & 0x3f)) goto LAB_0042db03;
  }
  else {
    addr = addr & *(uint *)(&DAT_004c2960 + ((int)uVar1 >> 3 & 3U) * 4);
  }
  val = uVar4;
LAB_0042db03:
  if ((uVar2 != 0) && ((uVar1 & 0x80) != 0)) {
    val_00 = val_00 << 4;
  }
  if (0 < (int)uVar4) {
    puVar3 = local_18;
    id = uVar4;
    do {
      *puVar3 = (-(uint)(uVar2 != 0) & 0xf0) + 0xf & val_00;
      val_00 = val_00 >> (-(uVar2 != 0) & 4U) + 4;
      id = id + -1;
      puVar3 = puVar3 + 1;
    } while (id != 0);
  }
  iVar5 = 0;
  if (0 < (int)uVar4) {
    puVar6 = local_18;
    do {
      addr_00 = reg_field_pack(iVar7,addr,iVar5);
      mdisk_write(*(int *)(cur_dev + 4),0x1c,addr_00,*puVar6,0);
      iVar5 = iVar5 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar5 < (int)uVar4);
  }
  return val;
}


/* ==== omr_remap_56009 @ 0042dd70 ==== */

void __cdecl omr_remap_56009(ulong omr)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = memmap_find(0xe,0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = (uint)((omr & 0x13) != 0);
  iVar1 = memmap_find(0xe,0x200);
  iVar2 = memmap_find(0x13,0xf00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  uVar3 = (uint)((omr & 8) == 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = uVar3;
  uVar4 = (uint)((omr & 8) != 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = uVar4;
  iVar1 = memmap_find(0xe,0x500);
  iVar2 = memmap_find(0x18,0xe00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = uVar3;
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = uVar4;
  iVar1 = memmap_find(0xe,0x800);
  iVar2 = memmap_find(0x13,0xc00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = (uint)((omr & 4) == 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = (uint)((omr & 4) != 0);
  return;
}


/* ==== omr_remap_56011 @ 0042dec0 ==== */

void __cdecl omr_remap_56011(ulong omr)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = memmap_find(0xe,0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = (uint)((omr & 0x13) != 0);
  iVar1 = memmap_find(0xe,0x200);
  iVar2 = memmap_find(0x13,0xd00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  uVar3 = (uint)((omr & 8) == 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = uVar3;
  uVar4 = (uint)((omr & 8) != 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = uVar4;
  iVar1 = memmap_find(0xe,0x500);
  iVar2 = memmap_find(0x18,0xe00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = uVar3;
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = uVar4;
  iVar1 = memmap_find(0xe,0x800);
  iVar2 = memmap_find(0x13,0xa00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = (uint)((omr & 4) == 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = (uint)((omr & 4) != 0);
  return;
}


/* ==== omr_remap_56012 @ 0042e010 ==== */

void __cdecl omr_remap_56012(ulong omr)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = memmap_find(0xe,0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = (uint)((omr & 0x13) != 0);
  iVar1 = memmap_find(0xe,0x100);
  iVar2 = memmap_find(0x13,0xd00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  uVar3 = (uint)((omr & 8) == 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = uVar3;
  uVar4 = (uint)((omr & 8) != 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = uVar4;
  iVar1 = memmap_find(0xe,0x400);
  iVar2 = memmap_find(0x18,0xe00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = uVar3;
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = uVar4;
  iVar1 = memmap_find(0xe,0x700);
  iVar2 = memmap_find(0x13,0xa00);
  *(undefined4 *)(*(int *)(cur_dev + 0xc) + 8 + iVar1 * 0x10) =
       *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(cur_dev + 0xc));
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar1 * 0x10) = (uint)((omr & 4) == 0);
  *(uint *)(*(int *)(cur_dev + 0xc) + 0xc + iVar2 * 0x10) = (uint)((omr & 4) != 0);
  return;
}


/* ==== reg_write_check @ 0042e160 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int reg_write_check(int id,long a2,ulong val)

{
  uint uVar1;
  ulong addr;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  ulong *pval;
  uint uVar8;
  int in_stack_00000010;
  ulong uStack_28;
  uint auStack_24 [3];
  ulong auStack_18 [6];
  
  iVar7 = id;
  if ((id < 0x1d) || (0x11c < id)) {
    if (in_stack_00000010 == 0) {
      iVar7 = mem_reg_read(id,a2,(ulong *)val);
      return iVar7;
    }
    uVar4 = 3;
    uVar2 = 0;
    iVar7 = 2;
    do {
      uVar8 = mem_reg_read(id,iVar7 + a2,auStack_24);
      uVar4 = uVar4 & uVar8;
      uVar2 = uVar2 << 8 | auStack_24[0] & 0xff;
      iVar7 = iVar7 + -1;
    } while (-1 < iVar7);
    iVar7 = 0;
    if (uVar4 != 0) {
      iVar7 = 3;
    }
    *(uint *)val = uVar2;
    return iVar7;
  }
  uVar4 = id - 0x1d;
  uVar2 = uVar4 & 1;
  if ((uVar4 & 0x80) == 0) {
    iVar3 = *(int *)(&DAT_004c2930 + (uVar4 & 7) * 4);
  }
  else {
    iVar3 = *(int *)(&DAT_004c2950 + (uVar4 & 3) * 4);
  }
  if ((uVar4 & 0x40) == 0) {
    in_stack_00000010 = 1;
    a2 = a2 & *(uint *)(&DAT_004c2970 + (uVar4 & 0x3f) * 4);
    if (7 < (uVar4 & 0x3f)) goto LAB_0042e1f4;
  }
  else {
    a2 = a2 & *(uint *)(&DAT_004c2960 + ((int)uVar4 >> 3 & 3U) * 4);
  }
  in_stack_00000010 = iVar3;
LAB_0042e1f4:
  iVar5 = 0;
  if (0 < iVar3) {
    pval = auStack_18;
    do {
      addr = reg_field_pack(id,a2,iVar5);
      mdisk_read(*(int *)(cur_dev + 4),0x1c,addr,pval,0);
      iVar5 = iVar5 + 1;
      pval = pval + 1;
    } while (iVar5 < iVar3);
  }
  uVar8 = 0;
  iVar5 = (-(uint)(uVar2 != 0) & 4) + 4;
  id = 0;
  if (-1 < iVar3 + -1) {
    puVar6 = auStack_18 + iVar3 + -1;
    id = iVar5 * iVar3;
    do {
      uVar1 = *puVar6;
      puVar6 = puVar6 + -1;
      uVar8 = uVar8 << (sbyte)iVar5 | (-(uint)(uVar2 != 0) & 0xf0) + 0xf & uVar1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  iVar3 = in_stack_00000010;
  iVar5 = id;
  if ((uVar2 != 0) && ((uVar4 & 0x80) != 0)) {
    uVar8 = uVar8 >> 4;
    iVar5 = id + -4;
    id = iVar5;
  }
  while (iVar5 < 0x18) {
    a2 = in_stack_00000010 + a2;
    mem_reg_read(iVar7,a2,&uStack_28);
    uVar8 = uVar8 | uStack_28 << ((byte)iVar5 & 0x1f);
    iVar3 = iVar3 + in_stack_00000010;
    iVar5 = iVar5 + id;
  }
  *(uint *)val = uVar8 & 0xffffff;
  return iVar3;
}


/* ==== reg_read_check @ 0042e370 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int reg_read_check(int id,long a2,ulong val)

{
  long lVar1;
  ulong addr;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  ulong *puVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  int in_stack_00000010;
  uint uStack_2c;
  uint uStack_28;
  uint uStack_24;
  uint auStack_20 [8];
  
  lVar1 = a2;
  uStack_2c = *(uint *)val & 0xffffff;
  if ((0x1c < id) && (id < 0x11d)) {
    uVar5 = id - 0x1d;
    uStack_28 = uVar5 & 1;
    uStack_24 = uVar5 & 0x80;
    if (uStack_24 == 0) {
      iVar3 = *(int *)(&DAT_004c2930 + (uVar5 & 7) * 4);
    }
    else {
      iVar3 = *(int *)(&DAT_004c2950 + (uVar5 & 3) * 4);
    }
    if ((uVar5 & 0x40) == 0) {
      a2 = 1;
      uVar9 = *(uint *)(&DAT_004c2970 + (uVar5 & 0x3f) * 4);
      if ((uVar5 & 0x3f) < 8) {
        a2 = iVar3;
      }
    }
    else {
      uVar9 = *(uint *)(&DAT_004c2960 + ((int)uVar5 >> 3 & 3U) * 4);
      a2 = iVar3;
    }
    uVar9 = lVar1 & uVar9;
    iVar4 = (-(uint)(uStack_28 != 0) & 4) + 4;
    uVar5 = uStack_2c;
    if ((uStack_28 != 0) && (uStack_24 != 0)) {
      uVar5 = uStack_2c << 4;
    }
    iVar7 = 0;
    if (0 < iVar3) {
      iVar7 = iVar4 * iVar3;
      puVar8 = auStack_20 + 2;
      in_stack_00000010 = iVar3;
      do {
        *puVar8 = (-(uint)(uStack_28 != 0) & 0xf0) + 0xf & uVar5;
        uVar5 = uVar5 >> (sbyte)iVar4;
        in_stack_00000010 = in_stack_00000010 + -1;
        puVar8 = puVar8 + 1;
      } while (in_stack_00000010 != 0);
    }
    iVar4 = 0;
    if (0 < iVar3) {
      puVar6 = auStack_20 + 2;
      do {
        addr = reg_field_pack(id,uVar9,iVar4);
        mdisk_write(*(int *)(cur_dev + 4),0x1c,addr,*puVar6);
        iVar4 = iVar4 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar4 < iVar3);
    }
    iVar3 = a2;
    iVar4 = iVar7;
    if ((uStack_28 != 0) && (uStack_24 != 0)) {
      iVar7 = iVar7 + -4;
      iVar4 = iVar7;
    }
    while (iVar7 < 0x18) {
      uVar9 = uVar9 + a2;
      uStack_2c = uStack_2c >> ((byte)iVar4 & 0x1f);
      mem_reg_write(id,uVar9,(ulong)&uStack_2c);
      iVar7 = iVar7 + iVar4;
      iVar3 = iVar3 + a2;
    }
    return iVar3;
  }
  if (in_stack_00000010 == 0) {
    iVar3 = mem_reg_write(id,a2,(ulong)&uStack_2c);
  }
  else {
    auStack_20[0] = *(uint *)val & 0xff;
    auStack_20[1] = 0;
    uVar5 = mem_reg_write(id,a2,(ulong)auStack_20);
    auStack_20[0] = uStack_2c >> 8 & 0xff;
    uVar9 = mem_reg_write(id,a2 + 1,(ulong)auStack_20);
    auStack_20[0] = uStack_2c >> 0x10 & 0xff;
    uVar2 = mem_reg_write(id,a2 + 2,(ulong)auStack_20);
    iVar3 = 0;
    if ((uVar5 & uVar9 & uVar2) != 0) {
      return 3;
    }
  }
  return iVar3;
}


/* ==== insn_exec_h42e5c0 @ 0042e5c0 ==== */

undefined4 insn_exec_h42e5c0(void)

{
  return 1;
}


/* ==== insn_exec_h42e5d0 @ 0042e5d0 ==== */

int insn_exec_h42e5d0(uint param_1)

{
  if ((param_1 & 0x400000) != 0) {
    return (-(uint)((param_1 & 0x8000) != 0) & 0xffffffe8) + 0x37;
  }
  return (-(uint)((param_1 & 0x8000) != 0) & 0xffffffe8) + 0x38;
}


/* ==== insn_exec_h42e600 @ 0042e600 ==== */

int insn_exec_h42e600(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 != 0) {
    return 0x23;
  }
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      if (param_3 != 0) {
        return 0;
      }
      return ((param_1 & 0x400) != 0) + 2;
    }
    if (uVar1 != 7) {
      uVar1 = param_1 >> 0x13 & 1;
      if ((param_1 & 0x8000) != 0) {
        return 0x25 - (uint)(uVar1 != 0);
      }
      return 0x3e - (uint)(uVar1 != 0);
    }
  }
  return 2;
}


/* ==== insn_exec_h42e670 @ 0042e670 ==== */

uint insn_exec_h42e670(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 != 0) {
    return 0x23;
  }
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      if (param_3 != 0) {
        return 0;
      }
      return (uint)(byte)(((byte)(param_1 >> 8) & 4 | 8) >> 2);
    }
    if (uVar1 != 7) {
      uVar1 = param_1 >> 0x13 & 1;
      if ((param_1 & 0x8000) != 0) {
        return (-(uint)(uVar1 != 0) & 0xffffffeb) + 0x25;
      }
      return (-(uint)(uVar1 != 0) & 0xffffffd3) + 0x3e;
    }
  }
  return 2;
}


/* ==== insn_exec_h42e6e0 @ 0042e6e0 ==== */

uint insn_exec_h42e6e0(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 != 0) {
    return 0x23;
  }
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      if (param_3 != 0) {
        return 0;
      }
      return (uint)(byte)(((byte)(param_1 >> 8) & 4 | 8) >> 2);
    }
    if (uVar1 != 7) {
      uVar1 = param_1 >> 0x10 & 3;
      if ((param_1 & 0x8000) != 0) {
        uVar1 = uVar1 | 8;
      }
      if ((param_1 & 0x80000) != 0) {
        uVar1 = uVar1 | 4;
      }
      return *(uint *)(&DAT_004c3670 + uVar1 * 4);
    }
  }
  return 2;
}


/* ==== insn_exec_h42e750 @ 0042e750 ==== */

int insn_exec_h42e750(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0x13 & 1;
  if ((param_1 & 0x8000) != 0) {
    return 0x25 - (uint)(uVar1 != 0);
  }
  return 0x3e - (uint)(uVar1 != 0);
}


/* ==== insn_exec_h42e780 @ 0042e780 ==== */

int insn_exec_h42e780(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0x13 & 1;
  if ((param_1 & 0x8000) != 0) {
    return (-(uint)(uVar1 != 0) & 0xffffffeb) + 0x25;
  }
  return (-(uint)(uVar1 != 0) & 0xffffffd3) + 0x3e;
}


/* ==== insn_exec_h42e7b0 @ 0042e7b0 ==== */

undefined4 insn_exec_h42e7b0(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 0x10 & 3;
  if ((param_1 & 0x8000) != 0) {
    uVar1 = (uint)(byte)((byte)uVar1 | 8);
  }
  if ((param_1 & 0x80000) != 0) {
    uVar1 = uVar1 | 4;
  }
  return *(undefined4 *)(&DAT_004c36b0 + uVar1 * 4);
}


/* ==== insn_exec_h42e7e0 @ 0042e7e0 ==== */

undefined4 insn_exec_h42e7e0(void)

{
  return 0x27;
}


/* ==== insn_exec_h42e7f0 @ 0042e7f0 ==== */

char insn_exec_h42e7f0(undefined4 param_1)

{
  return (((byte)((uint)param_1 >> 0x10) & 7) < 6) + '&';
}


/* ==== insn_exec_h42e810 @ 0042e810 ==== */

undefined4 insn_exec_h42e810(void)

{
  return 0x26;
}


/* ==== insn_exec_h42e820 @ 0042e820 ==== */

undefined4 insn_exec_h42e820(void)

{
  return 0x3f;
}


/* ==== insn_exec_h42e830 @ 0042e830 ==== */

int insn_exec_h42e830(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 != 0) {
    return 0x3a;
  }
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      if (param_3 != 0) {
        return 0;
      }
      return ((param_1 & 0x400) != 0) + 2;
    }
    if (uVar1 != 7) {
      return 0x3c - (uint)((param_1 & 0x8000) != 0);
    }
  }
  return 2;
}


/* ==== insn_exec_h42e890 @ 0042e890 ==== */

int insn_exec_h42e890(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 != 0) {
    return 0x21;
  }
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      if (param_3 != 0) {
        return 0;
      }
      return ((param_1 & 0x400) != 0) + 2;
    }
    if (uVar1 != 7) {
      return (-(uint)((param_1 & 0x8000) != 0) & 0xffffffe9) + 0x39;
    }
  }
  return 2;
}


/* ==== insn_exec_h42e8f0 @ 0042e8f0 ==== */

byte insn_exec_h42e8f0(byte param_1,undefined4 param_2,int param_3)

{
  if (param_3 != 0) {
    return 0;
  }
  return (~param_1 & 0x40 | 0xb0) >> 4;
}


/* ==== insn_exec_h42e910 @ 0042e910 ==== */

byte insn_exec_h42e910(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  if (param_3 != 0) {
    return 0;
  }
  uVar1 = param_1 >> 0xb & 7;
  if ((uVar1 != 5) && (uVar1 != 7)) {
    return (~(byte)param_1 & 0x40 | 0xb0) >> 4;
  }
  return 2;
}


/* ==== insn_exec_h42e950 @ 0042e950 ==== */

int insn_exec_h42e950(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 != 0) {
    return (-(uint)((param_1 & 0x40) != 0) & 0xfffffffc) + 0xc;
  }
  return (-(uint)((param_1 & 0x40) != 0) & 0xfffffffc) + 0xd;
}


/* ==== insn_exec_h42e980 @ 0042e980 ==== */

int insn_exec_h42e980(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1 & 0x40;
  if (param_4 != 0) {
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xc;
  }
  uVar2 = param_1 >> 0xb & 7;
  if ((param_3 != 0) && (uVar2 == 6)) {
    return 0;
  }
  if (uVar2 == 4) {
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xe;
  }
  if (uVar2 < 4) {
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xd;
  }
  return 2;
}


/* ==== insn_exec_h42e9e0 @ 0042e9e0 ==== */

uint insn_exec_h42e9e0(uint param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = param_1 >> 0x10 & 1;
  uVar2 = param_1 & 0x40;
  uVar4 = param_1 & 0x8000;
  uVar3 = param_1 >> 0xb & 7;
  if (param_4 == 2) {
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xc;
  }
  if (param_4 == 0) {
    switch(uVar3) {
    case 4:
      goto switchD_0042ea67_caseD_4;
    case 5:
    case 7:
      return 2;
    case 6:
      if (param_3 == 0) {
        return (uint)(byte)(((byte)(param_1 >> 8) & 4 | 8) >> 2);
      }
      return 0;
    default:
      if (uVar4 == 0) {
        return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xd;
      }
      return (-(uint)(uVar2 != 0) & 0xfffffffc) + 0xd;
    }
  }
  if (uVar3 != 6) {
    if (uVar4 == 0) {
      return (-(uint)(uVar2 != 0) & 0xfffffffc) + 0xc;
    }
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xc;
  }
  if (param_2 < 4) {
    return 5;
  }
  return 0x55 - (uVar1 != 0);
switchD_0042ea67_caseD_4:
  if (uVar4 == 0) {
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xe;
  }
  return (-(uint)(uVar2 != 0) & 0xfffffffc) + 0xe;
}


/* ==== insn_exec_h42eaf0 @ 0042eaf0 ==== */

int insn_exec_h42eaf0(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_1 & 0x8000;
  uVar1 = param_1 >> 0x10 & 1;
  if (param_4 != 0) {
    if (uVar2 == 0) {
      return 6;
    }
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xc;
  }
  switch(param_1 >> 0xb & 7) {
  case 4:
    break;
  case 5:
  case 7:
    return 2;
  case 6:
    return (-(uint)(param_3 != 0) & 0xfffffffe) + 2;
  default:
    if (uVar2 == 0) {
      return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xd;
    }
    return 7;
  }
  if (uVar2 == 0) {
    return (-(uint)(uVar1 != 0) & 0xfffffffc) + 0xe;
  }
  return 0x48;
}


/* ==== insn_exec_h42eb90 @ 0042eb90 ==== */

int insn_exec_h42eb90(uint param_1,uint param_2,undefined4 param_3,int param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  
  if ((param_2 < 4) || ((param_1 & 0x3000) != 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  uVar3 = param_1 & 0x8000;
  uVar2 = param_1 >> 0x10 & 1;
  if (param_4 != 0) {
    if (uVar3 != 0) {
      return (-(uint)(uVar2 != 0) & 0xfffffffc) + 0xc;
    }
    return 0x28;
  }
  if (!bVar1) {
    if (uVar3 != 0) {
      return 0x40;
    }
    return (-(uint)(uVar2 != 0) & 0xfffffffc) + 0xd;
  }
  if (uVar3 != 0) {
    return 0x4d - (uint)(uVar2 != 0);
  }
  return 0x4f - (uint)(uVar2 != 0);
}


/* ==== insn_exec_h42ec20 @ 0042ec20 ==== */

int insn_exec_h42ec20(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x8000;
  if (param_4 == 0) {
    switch(param_1 >> 0xb & 7) {
    case 4:
      return 0x49 - (uint)(uVar1 != 0);
    case 5:
    case 7:
      return 2;
    case 6:
      return (-(uint)(param_3 != 0) & 0xfffffffe) + 2;
    default:
      return (-(uint)(uVar1 != 0) & 0xffffffc4) + 0x43;
    }
  }
  return (-(uint)(uVar1 != 0) & 0x23) + 6;
}


/* ==== insn_exec_h42ec90 @ 0042ec90 ==== */

int insn_exec_h42ec90(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 != 0) {
    return (-(uint)((param_1 & 0x8000) != 0) & 0x23) + 6;
  }
  return (-(uint)((param_1 & 0x8000) != 0) & 0xffffffc4) + 0x43;
}


/* ==== insn_exec_h42ecc0 @ 0042ecc0 ==== */

int insn_exec_h42ecc0(undefined4 param_1,undefined4 param_2,int param_3)

{
  return (-(uint)(param_3 != 0) & 0xffffffe4) + 0x1c;
}


/* ==== insn_exec_h42ecd0 @ 0042ecd0 ==== */

int insn_exec_h42ecd0(undefined4 param_1,undefined4 param_2,int param_3)

{
  return (-(uint)(param_3 != 0) & 0xffffffbf) + 0x41;
}


/* ==== insn_exec_h42ece0 @ 0042ece0 ==== */

int insn_exec_h42ece0(uint param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  if (param_3 != 0) {
    return 0;
  }
  uVar1 = param_1 >> 0xb & 7;
  if ((uVar1 != 5) && (uVar1 != 7)) {
    return 0x1e - (uint)((param_1 & 0x40) != 0);
  }
  return 2;
}


/* ==== insn_exec_h42ed20 @ 0042ed20 ==== */

int insn_exec_h42ed20(uint param_1,undefined4 param_2,int param_3)

{
  if (param_3 != 0) {
    return 0;
  }
  return 0x1e - (uint)((param_1 & 0x40) != 0);
}


/* ==== insn_exec_h42ed40 @ 0042ed40 ==== */

uint insn_exec_h42ed40(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  uint uVar1;
  
  if (param_4 != 0) {
    return 0x2a;
  }
  uVar1 = param_1 >> 0xb & 7;
  if (uVar1 != 5) {
    if (uVar1 == 6) {
      if (param_3 != 0) {
        return 0;
      }
      return (uint)(byte)(((byte)(param_1 >> 8) & 4 | 8) >> 2);
    }
    if (uVar1 != 7) {
      if ((param_1 & 0x8000) != 0) {
        return 0x2d - ((param_1 & 0x40) != 0);
      }
      return 0x45 - ((param_1 & 0x40) != 0);
    }
  }
  return 2;
}


/* ==== insn_exec_h42eda0 @ 0042eda0 ==== */

int insn_exec_h42eda0(uint param_1)

{
  if ((param_1 & 0x8000) != 0) {
    return 0x2d - (uint)((param_1 & 0x40) != 0);
  }
  return 0x45 - (uint)((param_1 & 0x40) != 0);
}


/* ==== insn_exec_h42edc0 @ 0042edc0 ==== */

uint insn_exec_h42edc0(uint param_1)

{
  return (~param_1 & 0x8000 | 0x84000) >> 0xd;
}


/* ==== insn_exec_h42ede0 @ 0042ede0 ==== */

char insn_exec_h42ede0(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 == 1) {
    return (-((param_1 & 0x400) != 0) & 0x14U) + 0x36;
  }
  return '\x03';
}


/* ==== insn_exec_h42ee10 @ 0042ee10 ==== */

undefined4 insn_exec_h42ee10(void)

{
  return 0x47;
}


/* ==== insn_exec_h42ee20 @ 0042ee20 ==== */

int insn_exec_h42ee20(byte param_1)

{
  return 0x1b - (uint)((param_1 & 3) != 2);
}


/* ==== insn_exec_h42ee40 @ 0042ee40 ==== */

int insn_exec_h42ee40(uint param_1)

{
  if (((param_1 & 0x2000) != 0) && ((param_1 & 0x800) != 0)) {
    return 2;
  }
  if ((param_1 & 0x8000) != 0) {
    return 0x51 - (uint)((param_1 & 0x10000) != 0);
  }
  return 0x53 - (uint)((param_1 & 0x10000) != 0);
}


/* ==== insn_exec_h42ee80 @ 0042ee80 ==== */

int insn_exec_h42ee80(undefined4 param_1,undefined4 param_2,int param_3)

{
  return (-(uint)(param_3 != 0) & 0xffffffb5) + 0x4b;
}


/* ==== insn_exec_h42ee90 @ 0042ee90 ==== */

int insn_exec_h42ee90(uint param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if ((param_1 & 0xfc0e0) == 0xbc060) {
    return 0x4b;
  }
  return (-(uint)(param_4 != 0) & 0xffffffe8) + 0x40;
}


