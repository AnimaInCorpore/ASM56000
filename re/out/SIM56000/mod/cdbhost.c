/* ==== host_write @ 0047a900 ==== */

long __cdecl host_write(int hfd,char *buf,ulong n)

{
  void *stream;
  int iVar1;
  uint uVar2;
  
  if ((hfd < 0) || (*(int *)(cur_sim + 0x4088) <= hfd)) {
    return -1;
  }
  iVar1 = *(int *)(*(int *)(cur_sim + 0x4080) + hfd * 0x10);
  if ((iVar1 != 1) && (iVar1 != 2)) {
    iVar1 = _write(iVar1,buf,n);
    return iVar1;
  }
  if (*(int *)(cur_sim + 0x408c + iVar1 * 4) != 0) {
    stream = *(void **)(cur_sim + 0x4098 + iVar1 * 4);
    if (stream != (void *)0x0) {
      uVar2 = fwrite(buf,1,n,stream);
      fflush(*(void **)(cur_sim + iVar1 * 4 + 0x4098));
      return uVar2;
    }
  }
  return n;
}


/* ==== host_read @ 0047a9a0 ==== */

long __cdecl host_read(int hfd,char *buf,ulong n)

{
  uint uVar1;
  int iVar2;
  
  if ((hfd < 0) || (*(int *)(cur_sim + 0x4088) <= hfd)) {
    return -1;
  }
  iVar2 = *(int *)(*(int *)(cur_sim + 0x4080) + hfd * 0x10);
  if (iVar2 != 0) {
    iVar2 = _read(iVar2,buf,n);
    return iVar2;
  }
  if ((*(int *)(cur_sim + 0x408c) != 0) && (*(void **)(cur_sim + 0x4098) != (void *)0x0)) {
    uVar1 = fread(buf,1,n,*(void **)(cur_sim + 0x4098));
    return uVar1;
  }
  return n;
}


/* ==== host_close @ 0047aa10 ==== */

int __cdecl host_close(int hfd)

{
  int iVar1;
  
  if ((((-1 < hfd) && (2 < hfd)) && (-1 < hfd)) && (hfd < *(int *)(cur_sim + 0x4088))) {
    iVar1 = hfd * 0x10;
    dsp_free(*(void **)(*(int *)(cur_sim + 0x4080) + 4 + iVar1));
    *(undefined4 *)(*(int *)(cur_sim + 0x4080) + 4 + iVar1) = 0;
    if (hfd < *(int *)(cur_sim + 0x4084)) {
      *(int *)(cur_sim + 0x4084) = hfd;
    }
    iVar1 = _close(*(int *)(*(int *)(cur_sim + 0x4080) + iVar1));
    return iVar1;
  }
  return -1;
}


/* ==== host_open @ 0047aa90 ==== */

int __cdecl host_open(char *path,ulong oflag,ulong pmode)

{
  char cVar1;
  undefined4 extraout_EAX;
  int iVar2;
  char *extraout_EAX_00;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar2 = *(int *)(cur_sim + 0x4084);
  if (iVar2 < *(int *)(cur_sim + 0x4088)) {
    do {
      if (*(int *)(*(int *)(cur_sim + 0x4080) + 4 + iVar2 * 0x10) == 0) break;
      *(int *)(cur_sim + 0x4084) = iVar2 + 1;
      iVar2 = *(int *)(cur_sim + 0x4084);
    } while (iVar2 < *(int *)(cur_sim + 0x4088));
  }
  if (*(int *)(cur_sim + 0x4084) == *(int *)(cur_sim + 0x4088)) {
    *(int *)(cur_sim + 0x4088) = *(int *)(cur_sim + 0x4088) + 1;
    dsp_realloc(*(void **)(cur_sim + 0x4080),*(int *)(cur_sim + 0x4088) << 4);
    *(undefined4 *)(cur_sim + 0x4080) = extraout_EAX;
  }
  piVar5 = (int *)(*(int *)(cur_sim + 0x4084) * 0x10 + *(int *)(cur_sim + 0x4080));
  iVar2 = _open(path,oflag,pmode);
  *piVar5 = iVar2;
  if (iVar2 == -1) {
    return -1;
  }
  uVar3 = 0xffffffff;
  pcVar6 = path;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  dsp_alloc(~uVar3,0);
  piVar5[1] = (int)extraout_EAX_00;
  if (extraout_EAX_00 == (char *)0x0) {
    _close(*piVar5);
    return -1;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar6 = path;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = path + 1;
    cVar1 = *path;
    path = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar6 = pcVar6 + -uVar3;
  pcVar7 = extraout_EAX_00;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  piVar5[3] = pmode;
  piVar5[2] = oflag;
  return *(int *)(cur_sim + 0x4084);
}


/* ==== host_lseek @ 0047abc0 ==== */

long __cdecl host_lseek(int hfd,long off,int whence)

{
  long lVar1;
  
  if ((-1 < hfd) && (hfd < *(int *)(cur_sim + 0x4088))) {
    lVar1 = _lseek(*(int *)(*(int *)(cur_sim + 0x4080) + hfd * 0x10),off,whence);
    return lVar1;
  }
  return -1;
}


/* ==== host_io_init @ 0047ac00 ==== */

void host_io_init(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  char *name;
  int iVar4;
  
  *(undefined4 *)(cur_sim + 0x4070) = 0;
  *(undefined4 *)(cur_sim + 0x4078) = 0;
  iVar1 = *(int *)(cur_dtype + 4);
  bVar3 = iVar1 == 0x2c9;
  if (bVar3) {
    iVar2 = cdb_lookup_scoped(s_putchar_004d4ed0,0xd2);
    iVar4 = 0xd2;
    name = s__ARTREAD_004d4ec4;
  }
  else {
    if (iVar1 == 0x2cb) {
      iVar2 = src_find_line((uchar *)s_F__send_004d4ebc);
      iVar4 = src_find_line((uchar *)s_F__receive_004d4eb0);
      goto LAB_0047acef;
    }
    iVar2 = cdb_lookup_scoped(s___send_004d4ea8,2);
    iVar4 = 2;
    name = s___receive_004d4e9c;
  }
  iVar4 = cdb_lookup_scoped(name,iVar4);
LAB_0047acef:
  if (iVar2 == -1) {
    *(undefined4 *)(cur_sim + 0x404c) = 0;
    *(undefined4 *)(cur_sim + 0x4070) = 0;
  }
  else {
    *(undefined4 *)(cur_sim + 0x4070) =
         *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar2 * 0x20);
  }
  if (iVar4 == -1) {
    *(undefined4 *)(cur_sim + 0x404c) = 0;
    *(undefined4 *)(cur_sim + 0x4078) = 0;
  }
  else {
    *(undefined4 *)(cur_sim + 0x4078) =
         *(undefined4 *)(*(int *)(cur_sim + 0x3fe0) + 8 + iVar4 * 0x20);
    if (bVar3) {
      *(int *)(cur_sim + 0x4078) = *(int *)(cur_sim + 0x4078) + 3;
    }
  }
  if ((iVar1 == 0x2c5) || (iVar1 == 0x2c8)) {
    host_io_mode_var = 3;
  }
  else {
    if (((iVar1 == 0x2c7) || (iVar1 == 0x2ca)) || (bVar3)) {
      host_io_mode_var = 2;
      return;
    }
    if (iVar1 == 0x2c6) {
      host_io_mode_var = 4;
      return;
    }
    if (iVar1 == 0x2cb) {
      host_io_mode_var = 1;
      return;
    }
  }
  return;
}


/* ==== host_io_mode @ 0047ade0 ==== */

int host_io_mode(void)

{
  return host_io_mode_var;
}


/* ==== host_io_service @ 0047adf0 ==== */

int host_io_service(void)

{
  ulong *result;
  undefined4 *reply;
  undefined4 *buf;
  ulong *state;
  int iVar1;
  int iVar2;
  int *fd_wordmode;
  int iVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  int iVar7;
  uint uVar8;
  uint local_8 [2];
  
  iVar2 = cur_sim;
  iVar1 = *(int *)(cur_dtype + 4);
  local_8[0] = (uint)(iVar1 == 0x2c9);
  result = (ulong *)(cur_sim + 0x43f8);
  reply = (undefined4 *)(cur_sim + 0x4050);
  buf = (undefined4 *)(cur_sim + 0x4060);
  state = (ulong *)(cur_sim + 0x43f4);
  fd_wordmode = (int *)(cur_sim + 0x43a4);
  if ((*(int *)(cur_sim + 0x4070) == 0) || (*(int *)(cur_sim + 0x4070) != *(int *)(cur_dev + 0x1c)))
  {
    if (*(int *)(cur_sim + 0x4078) == 0) {
      return 0;
    }
    if (*(int *)(cur_sim + 0x4078) != *(int *)(cur_dev + 0x1c)) {
      return 0;
    }
    if (local_8[0] != 0) {
      host_read(0,&host_io_char,1);
      local_8[0] = (uint)host_io_char;
      dev_call_slot1(*(int *)(cur_dev + 4),1,0xf001,(long)local_8);
      return 1;
    }
    iVar3 = cdb_default_space();
    if (iVar3 == 3) {
      iVar3 = 2;
    }
    iVar4 = host_io_get_ret_arg();
    uVar5 = 0;
    if (*(int *)(iVar2 + 0x4054) != 0) {
      do {
        if (iVar1 != 0x2cb) {
          iVar7 = dev_call_slot1(*(int *)(cur_dev + 4),iVar3,iVar4,
                                 *(int *)(iVar2 + 0x405c) + uVar5 * 4);
joined_r0x0047b096:
          iVar4 = iVar4 + 1;
          if (iVar7 == 0) {
LAB_0047b0a2:
            sim_error(s_Error_writing_memory_004d4ed8);
            return -1;
          }
        }
        else {
          if (*state != 0) {
            iVar7 = dev_call_slot13(0,iVar3,iVar4,*(int *)(iVar2 + 0x405c) + uVar5 * 4);
            goto joined_r0x0047b096;
          }
          lVar6 = dev_call_slot14(0,iVar3,iVar4,*(int *)(iVar2 + 0x405c) + uVar5 * 4);
          if (lVar6 == 0) goto LAB_0047b0a2;
          iVar4 = iVar4 + 2;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(uint *)(iVar2 + 0x4054));
    }
    *reply = 0;
  }
  else {
    iVar3 = cdb_default_space();
    if (iVar3 == 3) {
      iVar3 = 2;
    }
    iVar4 = host_io_get_ret_arg();
    uVar5 = host_io_get_ret_arg2();
    *(uint *)(iVar2 + 0x4064) = uVar5;
    if (*(uint *)(iVar2 + 0x4068) < uVar5) {
      hio_buf_resize(buf,uVar5);
    }
    uVar8 = 0;
    if (uVar5 != 0) {
      do {
        if (iVar1 != 0x2cb) {
          iVar7 = dev_mem_read(*(int *)(cur_dev + 4),iVar3,iVar4,
                               *(int *)(iVar2 + 0x406c) + uVar8 * 4);
joined_r0x0047af4a:
          iVar4 = iVar4 + 1;
          if (iVar7 == 0) {
LAB_0047b0ea:
            sim_error(s_Error_reading_memory_004c7abc);
            return -1;
          }
        }
        else {
          if (*state != 0) {
            iVar7 = dev_call_slot10(0,iVar3,iVar4,*(int *)(iVar2 + 0x406c) + uVar8 * 4);
            goto joined_r0x0047af4a;
          }
          lVar6 = dev_call_slot11(*(int *)(cur_dev + 4),iVar3,iVar4,
                                  *(int *)(iVar2 + 0x406c) + uVar8 * 4);
          if (lVar6 == 0) goto LAB_0047b0ea;
          iVar4 = iVar4 + 2;
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar5);
    }
    *buf = 1;
    if (local_8[0] != 0) {
      host_io_char = (char)iVar4;
      host_write(1,&host_io_char,1);
      return 1;
    }
  }
  hio_step(reply,buf,fd_wordmode,state,result);
  return 1;
}


/* ==== host_io_get_ret_arg @ 0047b110 ==== */

int host_io_get_ret_arg(void)

{
  long lVar1;
  int iVar2;
  char *name;
  long local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c [3];
  
  iVar2 = *(int *)(cur_dtype + 4);
  if (iVar2 == 0x2c5) {
    name = &DAT_004b2930;
  }
  else {
    if (iVar2 != 0x2c7) {
      if ((iVar2 == 0x2c8) || (iVar2 == 0x2ca)) {
        periph_find_reg(*(int *)(cur_dev + 4),&DAT_004a8a6c,&local_18,&local_14);
        lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_14,(long)&local_1c);
        if (lVar1 == 0) {
          sim_error(s_Error_reading_register_004c6178);
          return 0;
        }
        return local_1c;
      }
      if (iVar2 == 0x2cb) {
        periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2948,&local_18,&local_1c);
        lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_1c,(long)local_c);
        if (lVar1 == 0) {
          sim_error(s_Error_reading_register_004c6178);
          return 0;
        }
        return local_c[0];
      }
      if (iVar2 != 0x2c6) {
        if (iVar2 != 0x2c9) {
          return 0;
        }
        periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b2910,&local_18,&local_14);
        lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_14,(long)&local_1c);
        if (lVar1 == 0) {
          sim_error(s_Error_reading_register_004c6178);
          return 0;
        }
        return local_1c;
      }
      periph_find_reg(*(int *)(cur_dev + 4),&DAT_004d3098,&local_1c,&local_18);
      lVar1 = periph_call(*(int *)(cur_dev + 4),local_1c,local_18,(long)&local_14);
      if (lVar1 == 0) {
        sim_error(s_Error_reading_register_004c6178);
        return 0;
      }
      return local_14;
    }
    name = &DAT_004b2940;
  }
  iVar2 = cdb_default_space();
  if (iVar2 == 3) {
    iVar2 = 2;
  }
  periph_find_reg(*(int *)(cur_dev + 4),name,&local_18,&local_14);
  lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_14,(long)&local_1c);
  if (lVar1 != 0) {
    local_1c = local_1c + -1;
    lVar1 = dev_mem_read(*(int *)(cur_dev + 4),iVar2,local_1c,(long)&local_10);
    if (lVar1 == 0) {
      sim_error(s_Error_reading_memory_004c7abc);
      return 0;
    }
    return local_10;
  }
  sim_error(s_Error_reading_register_004c6178);
  return 0;
}


/* ==== host_io_get_ret_arg2 @ 0047b400 ==== */

int host_io_get_ret_arg2(void)

{
  long lVar1;
  int iVar2;
  char *name;
  long local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c [3];
  
  iVar2 = *(int *)(cur_dtype + 4);
  if (iVar2 == 0x2c5) {
    name = &DAT_004b2930;
  }
  else {
    if (iVar2 != 0x2c7) {
      if (iVar2 == 0x2c6) {
        periph_find_reg(*(int *)(cur_dev + 4),&DAT_004d3080,&local_18,&local_1c);
        lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_1c,(long)&local_14);
        if (lVar1 == 0) {
          sim_error(s_Error_reading_register_004c6178);
          return 0;
        }
        return local_14;
      }
      if ((iVar2 == 0x2c8) || (iVar2 == 0x2ca)) {
        periph_find_reg(*(int *)(cur_dev + 4),&DAT_004b29a8,&local_18,&local_14);
        lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_14,(long)&local_1c);
        if (lVar1 == 0) {
          sim_error(s_Error_reading_register_004c6178);
          return 0;
        }
        return local_1c;
      }
      if (iVar2 != 0x2cb) {
        return 0;
      }
      periph_find_reg(*(int *)(cur_dev + 4),&DAT_004d3080,&local_18,&local_14);
      lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_14,(long)local_c);
      if (lVar1 == 0) {
        sim_error(s_Error_reading_register_004c6178);
        return 0;
      }
      return local_c[0];
    }
    name = &DAT_004b2940;
  }
  iVar2 = cdb_default_space();
  if (iVar2 == 3) {
    iVar2 = 2;
  }
  periph_find_reg(*(int *)(cur_dev + 4),name,&local_18,&local_14);
  lVar1 = periph_call(*(int *)(cur_dev + 4),local_18,local_14,(long)&local_1c);
  if (lVar1 != 0) {
    local_1c = local_1c + -2;
    lVar1 = dev_mem_read(*(int *)(cur_dev + 4),iVar2,local_1c,(long)&local_10);
    if (lVar1 == 0) {
      sim_error(s_Error_reading_memory_004c7abc);
      return 0;
    }
    return local_10;
  }
  sim_error(s_Error_reading_register_004c6178);
  return 0;
}


