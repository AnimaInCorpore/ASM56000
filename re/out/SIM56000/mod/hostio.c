/* ==== hio_buf_clear @ 0045e5a0 ==== */

void __cdecl hio_buf_clear(void *buf)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)((int)buf + 8);
  if ((((buf != (void *)0x0) && (*(int *)((int)buf + 0xc) != 0)) && (iVar1 != 0)) &&
     (iVar2 = 0, 0 < iVar1)) {
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)((int)buf + 0xc) + -4 + iVar2 * 4) = 0;
    } while (iVar2 < iVar1);
  }
  return;
}


/* ==== hio_buf_alloc @ 0045e5d0 ==== */

void __cdecl hio_buf_alloc(void *buf,ulong n)

{
  undefined4 extraout_EAX;
  uint uVar1;
  
  if (n == 0) {
    *(undefined4 *)((int)buf + 0xc) = 0;
    return;
  }
  cdb_malloc(n * 4);
  *(undefined4 *)((int)buf + 0xc) = extraout_EAX;
  uVar1 = 0;
  *(ulong *)((int)buf + 8) = n;
  if (n != 0) {
    do {
      uVar1 = uVar1 + 1;
      *(undefined4 *)(*(int *)((int)buf + 0xc) + -4 + uVar1 * 4) = 0;
    } while (uVar1 < n);
  }
  return;
}


/* ==== hio_buf_resize @ 0045e620 ==== */

void __cdecl hio_buf_resize(void *buf,ulong n)

{
  int extraout_EAX;
  uint uVar1;
  
  cdb_realloc(*(void **)((int)buf + 0xc),n * 4);
  *(int *)((int)buf + 0xc) = extraout_EAX;
  if (extraout_EAX == 0) {
    fprintf(&DAT_004d7fe0,s_memory_exhausted__004d2c28);
    exit(-1);
  }
  uVar1 = 0;
  *(ulong *)((int)buf + 8) = n;
  if (n != 0) {
    do {
      uVar1 = uVar1 + 1;
      *(undefined4 *)(*(int *)((int)buf + 0xc) + -4 + uVar1 * 4) = 0;
    } while (uVar1 < n);
  }
  return;
}


/* ==== hio_buf_free @ 0045e680 ==== */

void __cdecl hio_buf_free(void *buf)

{
  cdb_free(*(void **)((int)buf + 0xc));
  return;
}


/* ==== hio_step @ 0045e6a0 ==== */

void __cdecl hio_step(void *reply,void *request,int *fd_wordmode,ulong *state,ulong *result)

{
  undefined4 *puVar1;
  uint *puVar2;
  char cVar3;
  char *buf;
  ulong uVar4;
  char *buf_00;
  int iVar5;
  undefined3 extraout_var;
  char *buf_01;
  long lVar6;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined3 extraout_var_00;
  
  switch(*state) {
  case 0:
    if (*(int *)request == 0) {
      return;
    }
    puVar1 = *(undefined4 **)((int)request + 0xc);
    switch(*puVar1) {
    case 0:
      *(undefined4 *)request = 0;
      *result = puVar1[1];
      uVar8 = *(uint *)(*(int *)((int)request + 0xc) + 8);
      if (*(uint *)((int)request + 8) < uVar8) {
        hio_buf_resize(request,uVar8);
      }
      *state = 1;
      return;
    case 1:
      *(undefined4 *)request = 0;
      iVar7 = host_close(puVar1[1]);
      **(int **)((int)reply + 0xc) = iVar7;
      iVar7 = hio_errno_map(errno);
      *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
      *(undefined4 *)((int)reply + 4) = 2;
      *(undefined4 *)reply = 1;
      return;
    case 2:
      *(undefined4 *)request = 0;
      if ((uint)puVar1[1] < 0x15) {
        if (fd_wordmode[puVar1[1]] == 0) {
          iVar7 = host_io_mode();
          cdb_malloc(iVar7 * *(int *)(*(int *)((int)request + 0xc) + 8));
          iVar7 = *(int *)((int)request + 0xc);
          iVar5 = host_io_mode();
          lVar6 = host_read(*(int *)(iVar7 + 4),buf_00,iVar5 * *(int *)(iVar7 + 8));
          iVar7 = host_io_mode();
          *result = lVar6 / iVar7;
          uVar4 = hio_errno_map(errno);
          result[1] = uVar4;
          cdb_free(*(void **)((int)reply + 0xc));
          uVar4 = hio_unpack_words(buf_00,*(int *)(*(int *)((int)request + 0xc) + 8));
          *(ulong *)((int)reply + 0xc) = uVar4;
          cdb_free(buf_00);
          *(undefined4 *)((int)reply + 8) = *(undefined4 *)(*(int *)((int)request + 0xc) + 8);
        }
        else {
          cdb_malloc(puVar1[2]);
          uVar4 = host_read(*(int *)(*(int *)((int)request + 0xc) + 4),buf,
                            *(ulong *)(*(int *)((int)request + 0xc) + 8));
          *result = uVar4;
          uVar4 = hio_errno_map(errno);
          result[1] = uVar4;
          cdb_free(*(void **)((int)reply + 0xc));
          uVar4 = hio_bytes_to_words(buf,*(int *)(*(int *)((int)request + 0xc) + 8));
          *(ulong *)((int)reply + 0xc) = uVar4;
          cdb_free(buf);
          *(undefined4 *)((int)reply + 8) = *(undefined4 *)(*(int *)((int)request + 0xc) + 8);
        }
        *(ulong *)((int)reply + 4) = *result;
        *(undefined4 *)reply = 1;
        *state = 2;
        return;
      }
      break;
    case 3:
      *(undefined4 *)request = 0;
      *result = puVar1[1];
      uVar8 = *(uint *)(*(int *)((int)request + 0xc) + 8);
      result[1] = uVar8;
      if (*(uint *)((int)request + 8) < uVar8) {
        hio_buf_resize(request,uVar8);
      }
      *state = 3;
      return;
    case 4:
      *(undefined4 *)request = 0;
      uVar8 = (uint)((puVar1[3] & 1) != 0);
      if ((puVar1[3] & 2) != 0) {
        uVar8 = uVar8 | 2;
      }
      if (*(code **)(cur_dtype + 0x4e8) == (code *)0x0) {
        uVar9 = *(uint *)(cur_dtype + 0xc);
      }
      else {
        uVar9 = (**(code **)(cur_dtype + 0x4e8))();
      }
      if ((uVar9 & 0x10000000) != 0) {
        uVar9 = *(uint *)(*(int *)((int)request + 0xc) + 8);
        if ((uVar9 & 0x8000) != 0) {
          *(uint *)(*(int *)((int)request + 0xc) + 8) = uVar9 | 0xffff0000;
        }
      }
      uVar9 = *(uint *)(*(int *)((int)request + 0xc) + 4);
      if (uVar9 < 0x15) {
        if (fd_wordmode[uVar9] == 0) {
          iVar7 = *(int *)((int)request + 0xc);
          iVar5 = host_io_mode();
          lVar6 = host_lseek(*(int *)(iVar7 + 4),iVar5 * *(int *)(iVar7 + 8),uVar8);
          **(long **)((int)reply + 0xc) = lVar6;
          puVar2 = *(uint **)((int)reply + 0xc);
          if (*puVar2 != 0) {
            uVar8 = host_io_mode();
            *puVar2 = *puVar2 / uVar8;
          }
        }
        else {
          lVar6 = host_lseek(uVar9,*(long *)(*(int *)((int)request + 0xc) + 8),uVar8);
          **(long **)((int)reply + 0xc) = lVar6;
        }
        iVar7 = hio_errno_map(errno);
        *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
        *(undefined4 *)((int)reply + 4) = 2;
        *(undefined4 *)reply = 1;
        return;
      }
      break;
    case 5:
      *(undefined4 *)request = 0;
      if (*(uint *)((int)request + 8) < (uint)puVar1[1]) {
        hio_buf_resize(request,puVar1[1]);
      }
      *state = 4;
      return;
    case 6:
      *(undefined4 *)request = 0;
      if (*(uint *)((int)request + 8) < (uint)puVar1[1]) {
        hio_buf_resize(request,puVar1[1]);
      }
      *state = 5;
      return;
    case 7:
      *(undefined4 *)request = 0;
      *result = puVar1[1];
      uVar8 = *(uint *)(*(int *)((int)request + 0xc) + 8);
      if (*(uint *)((int)request + 8) < uVar8) {
        hio_buf_resize(request,uVar8);
      }
      *state = 7;
      return;
    default:
      goto switchD_0045e6b4_default;
    }
    goto LAB_0045ed81;
  case 1:
    if (*(int *)request != 0) {
      cVar3 = hio_words_to_bytes(*(void **)((int)request + 0xc),*(ulong *)((int)request + 4));
      *(undefined4 *)request = 0;
      uVar8 = *result;
      uVar9 = (uint)((uVar8 & 1) != 0);
      if ((uVar8 & 2) != 0) {
        uVar9 = uVar9 | 2;
      }
      if ((uVar8 & 4) != 0) {
        uVar9 = uVar9 | 8;
      }
      if ((uVar8 & 0x10) != 0) {
        uVar9 = uVar9 | 0x200;
      }
      if ((uVar8 & 8) != 0) {
        uVar9 = uVar9 | 0x100;
      }
      if ((uVar8 & 0x20) == 0) {
        uVar4 = uVar9 | 0x4000;
      }
      else {
        uVar4 = uVar9 | 0x8000;
      }
      iVar7 = host_open((char *)CONCAT31(extraout_var,cVar3),uVar4,0x1b6);
      if (-1 < iVar7) {
        if ((*result & 0x20) == 0) {
          fd_wordmode[iVar7] = 1;
        }
        else {
          fd_wordmode[iVar7] = 0;
        }
      }
      cdb_free((char *)CONCAT31(extraout_var,cVar3));
      **(int **)((int)reply + 0xc) = iVar7;
      iVar7 = hio_errno_map(errno);
      *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
      *(undefined4 *)((int)reply + 4) = 2;
      *(undefined4 *)reply = 1;
      *state = 0;
      return;
    }
    break;
  case 2:
    if (*(int *)reply == 0) {
      **(ulong **)((int)reply + 0xc) = *result;
      *(ulong *)(*(int *)((int)reply + 0xc) + 4) = result[1];
      *(undefined4 *)((int)reply + 4) = 2;
      *(undefined4 *)reply = 1;
      *state = 0;
      return;
    }
    break;
  case 3:
    if (*(int *)request != 0) {
      *(undefined4 *)request = 0;
      if (fd_wordmode[*result] == 0) {
        cVar3 = hio_pack_words(*(ulong **)((int)request + 0xc),result[1]);
        buf_01 = (char *)CONCAT31(extraout_var_01,cVar3);
        iVar7 = host_io_mode();
        lVar6 = host_write(*result,buf_01,iVar7 * result[1]);
        iVar7 = host_io_mode();
        **(int **)((int)reply + 0xc) = lVar6 / iVar7;
      }
      else {
        cVar3 = hio_words_to_bytes(*(ulong **)((int)request + 0xc),result[1]);
        buf_01 = (char *)CONCAT31(extraout_var_00,cVar3);
        lVar6 = host_write(*result,buf_01,result[1]);
        **(long **)((int)reply + 0xc) = lVar6;
      }
      cdb_free(buf_01);
      iVar7 = hio_errno_map(errno);
      *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
      *(undefined4 *)((int)reply + 4) = 2;
      *(undefined4 *)reply = 1;
      *state = 0;
      return;
    }
    break;
  case 4:
    if (*(int *)request != 0) {
      cVar3 = hio_words_to_bytes(*(void **)((int)request + 0xc),*(ulong *)((int)request + 4));
      *(undefined4 *)request = 0;
      iVar7 = _unlink((char *)CONCAT31(extraout_var_02,cVar3));
      **(int **)((int)reply + 0xc) = iVar7;
      iVar7 = hio_errno_map(errno);
      *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
      *(undefined4 *)((int)reply + 4) = 2;
      *(undefined4 *)reply = 1;
      cdb_free((char *)CONCAT31(extraout_var_02,cVar3));
      *state = 0;
      return;
    }
    break;
  case 5:
    if (*(int *)request != 0) {
      *(undefined4 *)request = 0;
      cVar3 = hio_words_to_bytes(*(void **)((int)request + 0xc),*(ulong *)((int)request + 4));
      *result = CONCAT31(extraout_var_03,cVar3);
      *state = 6;
      return;
    }
    break;
  case 6:
    if (*(int *)request != 0) {
      cVar3 = hio_words_to_bytes(*(void **)((int)request + 0xc),*(ulong *)((int)request + 4));
      *(undefined4 *)request = 0;
      iVar7 = rename((char *)*result,(char *)CONCAT31(extraout_var_04,cVar3));
      **(int **)((int)reply + 0xc) = iVar7;
      iVar7 = hio_errno_map(errno);
      *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
      *(undefined4 *)((int)reply + 4) = 2;
      *(undefined4 *)reply = 1;
      cdb_free((void *)*result);
      cdb_free((char *)CONCAT31(extraout_var_04,cVar3));
      *state = 0;
      return;
    }
    break;
  case 7:
    if (*(int *)request == 0) {
      return;
    }
    uVar9 = 0;
    cVar3 = hio_words_to_bytes(*(void **)((int)request + 0xc),*(ulong *)((int)request + 4));
    uVar8 = *result;
    if ((uVar8 & 8) != 0) {
      uVar9 = 4;
    }
    if ((uVar8 & 4) != 0) {
      uVar9 = uVar9 | 2;
    }
    if ((uVar8 & 2) != 0) {
      uVar9 = 6;
    }
    *(undefined4 *)request = 0;
    iVar7 = _access((char *)CONCAT31(extraout_var_05,cVar3),uVar9);
    **(int **)((int)reply + 0xc) = iVar7;
    iVar7 = hio_errno_map(errno);
    *(int *)(*(int *)((int)reply + 0xc) + 4) = iVar7;
    *(undefined4 *)((int)reply + 4) = 2;
    *(undefined4 *)reply = 1;
    cdb_free((char *)CONCAT31(extraout_var_05,cVar3));
LAB_0045ed81:
    *state = 0;
  }
switchD_0045e6b4_default:
  return;
}


/* ==== hio_errno_map @ 0045edd0 ==== */

int __cdecl hio_errno_map(int host_errno)

{
  switch(host_errno) {
  case 2:
    return 6;
  default:
    return -1;
  case 9:
    return 8;
  case 0xc:
    return 3;
  case 0xd:
    return 7;
  case 0x16:
    return 9;
  case 0x1d:
    return 10;
  case 0x21:
    return 1;
  case 0x22:
    return 2;
  }
}


/* ==== hio_words_to_bytes @ 0045ee70 ==== */

char __cdecl hio_words_to_bytes(void *words,ulong n)

{
  undefined1 uVar1;
  int extraout_EAX;
  int iVar2;
  
  cdb_malloc(n);
  iVar2 = 0;
  if (0 < (int)n) {
    do {
      uVar1 = *(undefined1 *)words;
      words = (void *)((int)words + 4);
      *(undefined1 *)(iVar2 + extraout_EAX) = uVar1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)n);
  }
  return (char)extraout_EAX;
}


/* ==== hio_pack_words @ 0045eea0 ==== */

char __cdecl hio_pack_words(ulong *words,int n)

{
  int iVar1;
  int extraout_EAX;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  
  iVar1 = host_io_mode();
  cdb_malloc(iVar1 * n);
  iVar1 = host_io_mode();
  if (0 < n) {
    do {
      iVar2 = host_io_mode();
      if (0 < iVar2) {
        iVar4 = iVar2 * 8;
        puVar3 = (undefined1 *)((iVar1 - iVar2) + extraout_EAX);
        do {
          iVar4 = iVar4 + -8;
          iVar2 = iVar2 + -1;
          *puVar3 = (char)(*words >> ((byte)iVar4 & 0x1f));
          puVar3 = puVar3 + 1;
        } while (iVar2 != 0);
      }
      words = words + 1;
      iVar2 = host_io_mode();
      iVar1 = iVar1 + iVar2;
      n = n + -1;
    } while (n != 0);
  }
  return (char)extraout_EAX;
}


/* ==== hio_bytes_to_words @ 0045ef20 ==== */

ulong __cdecl hio_bytes_to_words(char *bytes,int n)

{
  byte *pbVar1;
  uint *extraout_EAX;
  int iVar2;
  uint *puVar3;
  
  cdb_malloc(n * 4);
  iVar2 = 0;
  puVar3 = extraout_EAX;
  if (0 < n) {
    do {
      pbVar1 = (byte *)(bytes + iVar2);
      iVar2 = iVar2 + 1;
      *puVar3 = (uint)*pbVar1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < n);
  }
  return (ulong)extraout_EAX;
}


/* ==== hio_unpack_words @ 0045ef60 ==== */

ulong __cdecl hio_unpack_words(char *bytes,int n)

{
  uint uVar1;
  uint *extraout_EAX;
  int iVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  
  cdb_malloc(n * 4);
  iVar3 = 0;
  puVar4 = extraout_EAX;
  if (0 < n) {
    do {
      *puVar4 = 0;
      iVar5 = 0;
      iVar2 = host_io_mode();
      if (0 < iVar2) {
        do {
          uVar1 = *puVar4;
          *puVar4 = uVar1 << 8;
          iVar2 = iVar5 + iVar3;
          iVar5 = iVar5 + 1;
          *puVar4 = (uint)(byte)bytes[iVar2] | uVar1 << 8;
          iVar2 = host_io_mode();
        } while (iVar5 < iVar2);
      }
      puVar4 = puVar4 + 1;
      iVar2 = host_io_mode();
      iVar3 = iVar3 + iVar2;
      n = n + -1;
    } while (n != 0);
  }
  return (ulong)extraout_EAX;
}


