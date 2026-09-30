/* ==== entry @ 00483400 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  int extraout_EAX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_00493c78;
  puStack_10 = &LAB_00486c08;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  DVar1 = GetVersion();
  _DAT_0050531c = DVar1 >> 8 & 0xff;
  _DAT_00505318 = DVar1 & 0xff;
  _DAT_00505314 = _DAT_00505318 * 0x100 + _DAT_0050531c;
  DAT_00505310 = DVar1 >> 0x10;
  iVar2 = _heap_init();
  if (iVar2 == 0) {
    _amsg_exit(0x1c);
  }
  local_8 = 0;
  _ioinit();
  __initmbctable();
  _acmdln = GetCommandLineA();
  __crtGetEnvironmentStringsA();
  _aenvptr = extraout_EAX;
  if ((extraout_EAX == 0) || (_acmdln == (LPSTR)0x0)) {
    exit(-1);
  }
  _setargv();
  _setenvp();
  _cinit();
  __initenv = _environ;
  iVar2 = main(__argc,__argv,_environ);
  exit(iVar2);
  *unaff_FS_OFFSET = local_14;
  return;
}


/* ==== _amsg_exit @ 00483520 ==== */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _amsg_exit(int rterrnum)

{
  if (DAT_005052c4 != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
  (*(code *)PTR___exit_004d7c4c)(0xff);
  return;
}


/* ==== abort @ 00483550 ==== */

void abort(void)

{
  _NMSG_WRITE(10);
  raise(0x16);
                    /* WARNING: Subroutine does not return */
  __exit(3);
}


/* ==== sprintf @ 00483570 ==== */

int __cdecl sprintf(char *buf,char *fmt,...)

{
  int iVar1;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 local_14;
  
  local_18 = buf;
  local_20 = buf;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = _output(&local_20,fmt,&stack0x0000000c);
  local_1c = local_1c + -1;
  if (-1 < local_1c) {
    *local_20 = '\0';
    return iVar1;
  }
  _flsbuf(0,&local_20);
  return iVar1;
}


/* ==== strchr @ 004835f0 ==== */

/* Library Function - Single Match
    _strchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strchr(char *s,int c)

{
  char cVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  while (((uint)s & 3) != 0) {
    uVar2 = *(uint *)s;
    if ((char)uVar2 == (char)c) {
      return (char)s;
    }
    s = (char *)((int)s + 1);
    if ((char)uVar2 == '\0') {
      return '\0';
    }
  }
  while( true ) {
    while( true ) {
      uVar2 = *(uint *)s;
      uVar5 = uVar2 ^ CONCAT22(CONCAT11((char)c,(char)c),CONCAT11((char)c,(char)c));
      uVar4 = uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff;
      puVar6 = (uint *)((int)s + 4);
      if (((uVar5 ^ 0xffffffff ^ uVar5 + 0x7efefeff) & 0x81010100) != 0) break;
      s = (char *)puVar6;
      if ((uVar4 & 0x81010100) != 0) {
        if ((uVar4 & 0x1010100) != 0) {
          return '\0';
        }
        if ((uVar2 + 0x7efefeff & 0x80000000) == 0) {
          return '\0';
        }
      }
    }
    uVar2 = *(uint *)s;
    cVar1 = (char)s;
    if ((char)uVar2 == (char)c) {
      return cVar1;
    }
    if ((char)uVar2 == '\0') {
      return '\0';
    }
    cVar3 = (char)(uVar2 >> 8);
    if (cVar3 == (char)c) {
      return cVar1 + '\x01';
    }
    if (cVar3 == '\0') {
      return '\0';
    }
    cVar3 = (char)(uVar2 >> 0x10);
    if (cVar3 == (char)c) {
      return cVar1 + '\x02';
    }
    if (cVar3 == '\0') break;
    cVar3 = (char)(uVar2 >> 0x18);
    if (cVar3 == (char)c) {
      return cVar1 + '\x03';
    }
    s = (char *)puVar6;
    if (cVar3 == '\0') {
      return '\0';
    }
  }
  return '\0';
}


/* ==== __fpmath @ 004836b0 ==== */

/* Library Function - Single Match
    __fpmath
   
   Library: Visual Studio 1998 Release */

void __cdecl __fpmath(int param_1)

{
  _cfltcvt_init();
  _adjust_fdiv = _ms_p5_mp_test_fdiv();
  __setdefaultprecision();
  return;
}


/* ==== _cfltcvt_init @ 004836e0 ==== */

void _cfltcvt_init(void)

{
  PTR__fptrap_004d846c = _cropzeros;
  _cfltcvt_tab = _cfltcvt;
  PTR__fptrap_004d8470 = _fassign;
  PTR__fptrap_004d8474 = _forcdecpt;
  PTR__fptrap_004d8478 = _positive;
  PTR__fptrap_004d847c = _cfltcvt;
  return;
}


/* ==== tolower @ 00483720 ==== */

int __cdecl tolower(int c)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int unaff_EBX;
  uint local_8 [2];
  
  iVar1 = c;
  if (DAT_005055d0 == 0) {
    if ((0x40 < c) && (c < 0x5b)) {
      return c + 0x20;
    }
  }
  else {
    if (c < 0x100) {
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[c * 2] & 1;
      }
      else {
        uVar2 = _isctype(c,1);
      }
      if (uVar2 == 0) {
        return iVar1;
      }
    }
    iVar3 = c;
    if ((_pctype[(iVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      c._0_2_ = (ushort)(byte)iVar1;
      iVar3 = 1;
    }
    else {
      c._0_2_ = CONCAT11((byte)iVar1,(char)((uint)iVar1 >> 8));
      c._3_1_ = SUB41(iVar3,3);
      c._0_3_ = (uint3)(ushort)c;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_005055d0,0x100,(char *)&c,iVar3,(char *)local_8,3,0,unaff_EBX);
    if (iVar3 == 0) {
      return iVar1;
    }
    if (iVar3 == 1) {
      return local_8[0] & 0xff;
    }
    c = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return c;
}


/* ==== _isctype @ 00483820 ==== */

int __cdecl _isctype(int c,int mask)

{
  int iVar1;
  BOOL BVar2;
  uint local_4;
  
  iVar1 = c;
  if (c + 1U < 0x101) {
    return (uint)*(ushort *)(_pctype + c * 2) & mask;
  }
  if ((_pctype[(c >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
    c._0_2_ = (ushort)(byte)c;
    iVar1 = 1;
  }
  else {
    c._0_2_ = CONCAT11((byte)c,(char)((uint)c >> 8));
    c._3_1_ = SUB41(iVar1,3);
    c._0_3_ = (uint3)(ushort)c;
    iVar1 = 2;
  }
  BVar2 = FUN_004882f0(1,(LPCSTR)&c,iVar1,(LPWORD)&local_4,0,0);
  if (BVar2 == 0) {
    return 0;
  }
  return local_4 & 0xffff & mask;
}


/* ==== strncmp @ 004838c0 ==== */

/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl strncmp(char *a,char *b,uint n)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  uVar3 = n;
  pcVar6 = a;
  if (n != 0) {
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = n - uVar3;
    do {
      pcVar6 = b;
      pcVar7 = a;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = a + 1;
      pcVar6 = b + 1;
      cVar2 = *a;
      cVar1 = *b;
      b = pcVar6;
      a = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}


/* ==== fclose @ 00483900 ==== */

int __cdecl fclose(void *stream)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  if ((*(uint *)((int)stream + 0xc) & 0x40) != 0) {
    *(undefined4 *)((int)stream + 0xc) = 0;
    return -1;
  }
  if ((*(uint *)((int)stream + 0xc) & 0x83) != 0) {
    iVar2 = _flush(stream);
    _freebuf(stream);
    iVar1 = _close(*(int *)((int)stream + 0x10));
    if (iVar1 < 0) {
      *(undefined4 *)((int)stream + 0xc) = 0;
      return -1;
    }
    if (*(void **)((int)stream + 0x1c) != (void *)0x0) {
      free(*(void **)((int)stream + 0x1c));
      *(undefined4 *)((int)stream + 0x1c) = 0;
    }
  }
  *(undefined4 *)((int)stream + 0xc) = 0;
  return iVar2;
}


/* ==== sscanf @ 00483980 ==== */

int __cdecl sscanf(char *buf,char *fmt,...)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 local_14;
  
  uVar3 = 0xffffffff;
  local_18 = buf;
  local_20 = buf;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *buf;
    buf = buf + 1;
  } while (cVar1 != '\0');
  local_1c = ~uVar3 - 1;
  local_14 = 0x49;
  iVar2 = _input(&local_20,fmt,&stack0x0000000c);
  return iVar2;
}


/* ==== fscanf @ 004839d0 ==== */

int __cdecl fscanf(void *stream,char *fmt,...)

{
  int iVar1;
  
  iVar1 = _input(stream,fmt,&stack0x0000000c);
  return iVar1;
}


/* ==== _fsopen @ 004839f0 ==== */

void __cdecl _fsopen(char *name,char *mode,int shflag)

{
  void *stream;
  
  _getstream();
  if (stream == (void *)0x0) {
    return;
  }
  _openfile(name,mode,shflag,stream);
  return;
}


/* ==== fopen @ 00483a20 ==== */

void __cdecl fopen(char *name,char *mode)

{
  _fsopen(name,mode,0x40);
  return;
}


/* ==== fflush @ 00483a40 ==== */

int __cdecl fflush(void *stream)

{
  int iVar1;
  
  if (stream == (void *)0x0) {
    iVar1 = flsall(0);
    return iVar1;
  }
  iVar1 = _flush(stream);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(uint *)((int)stream + 0xc) & 0x4000) != 0) {
    iVar1 = _commit(*(int *)((int)stream + 0x10));
    return -(uint)(iVar1 != 0);
  }
  return 0;
}


/* ==== _flush @ 00483a90 ==== */

int __cdecl _flush(void *stream)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint cnt;
  
  iVar3 = 0;
  if ((((byte)*(uint *)((int)stream + 0xc) & 3) == 2) &&
     ((*(uint *)((int)stream + 0xc) & 0x108) != 0)) {
    cnt = *(int *)stream - (int)*(void **)((int)stream + 8);
    if (0 < (int)cnt) {
      uVar2 = _write(*(int *)((int)stream + 0x10),*(void **)((int)stream + 8),cnt);
      uVar1 = *(uint *)((int)stream + 0xc);
      if (uVar2 == cnt) {
        if ((uVar1 & 0x80) != 0) {
          *(undefined4 *)((int)stream + 4) = 0;
          *(uint *)((int)stream + 0xc) = uVar1 & 0xfffffffd;
          *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
          return 0;
        }
      }
      else {
        iVar3 = -1;
        *(uint *)((int)stream + 0xc) = uVar1 | 0x20;
      }
    }
  }
  *(undefined4 *)((int)stream + 4) = 0;
  *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
  return iVar3;
}


/* ==== _flushall @ 00483b00 ==== */

int _flushall(void)

{
  int iVar1;
  
  iVar1 = flsall(1);
  return iVar1;
}


/* ==== flsall @ 00483b10 ==== */

int __cdecl flsall(int flushflag)

{
  void *stream;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = 0;
  if (0 < _nstream) {
    do {
      stream = *(void **)(__piob + iVar3 * 4);
      if ((stream != (void *)0x0) && ((*(uint *)((int)stream + 0xc) & 0x83) != 0)) {
        if (flushflag == 1) {
          iVar1 = fflush(stream);
          if (iVar1 != -1) {
            iVar2 = iVar2 + 1;
          }
        }
        else if ((flushflag == 0) && ((*(uint *)((int)stream + 0xc) & 2) != 0)) {
          iVar1 = fflush(stream);
          if (iVar1 == -1) {
            iVar4 = -1;
          }
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < _nstream);
  }
  if (flushflag != 1) {
    iVar2 = iVar4;
  }
  return iVar2;
}


/* ==== fseek @ 00483b90 ==== */

int __cdecl fseek(void *stream,long offset,int origin)

{
  uint uVar1;
  long lVar2;
  
  if (((*(uint *)((int)stream + 0xc) & 0x83) != 0) &&
     (((origin == 0 || (origin == 1)) || (origin == 2)))) {
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffffef;
    if (origin == 1) {
      lVar2 = ftell(stream);
      offset = offset + lVar2;
      origin = 0;
    }
    _flush(stream);
    uVar1 = *(uint *)((int)stream + 0xc);
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        *(undefined4 *)((int)stream + 0x18) = 0x200;
      }
    }
    else {
      *(uint *)((int)stream + 0xc) = uVar1 & 0xfffffffc;
    }
    lVar2 = _lseek(*(int *)((int)stream + 0x10),offset,origin);
    return (lVar2 != -1) - 1;
  }
  errno = 0x16;
  return -1;
}


/* ==== rewind @ 00483c30 ==== */

void __cdecl rewind(void *stream)

{
  uint fh;
  undefined *puVar1;
  
  fh = *(uint *)((int)stream + 0x10);
  _flush(stream);
  *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffffcf;
  if (fh == 0xffffffff) {
    puVar1 = &__badioinfo;
  }
  else {
    puVar1 = (undefined *)((&__pioinfo)[(int)fh >> 5] + (fh & 0x1f) * 8);
  }
  puVar1[4] = puVar1[4] & 0xfd;
  if ((*(uint *)((int)stream + 0xc) & 0x80) != 0) {
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xfffffffc;
  }
  _lseek(fh,0,0);
  return;
}


/* ==== ftell @ 00483c90 ==== */

long __cdecl ftell(void *stream)

{
  uint fh;
  uint uVar1;
  char *pcVar2;
  int iVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  int local_8;
  int local_4;
  
  fh = *(uint *)((int)stream + 0x10);
  if (*(int *)((int)stream + 4) < 0) {
    *(undefined4 *)((int)stream + 4) = 0;
  }
  local_4 = _lseek(fh,0,1);
  if (local_4 < 0) {
    return -1;
  }
  uVar1 = *(uint *)((int)stream + 0xc);
  if ((uVar1 & 0x108) == 0) {
    return local_4 - *(int *)((int)stream + 4);
  }
  pcVar7 = *(char **)stream;
  pcVar2 = *(char **)((int)stream + 8);
  local_8 = (int)pcVar7 - (int)pcVar2;
  iVar3 = (int)fh >> 5;
  if ((uVar1 & 3) == 0) {
    if ((uVar1 & 0x80) == 0) {
      errno = 0x16;
      return -1;
    }
  }
  else {
    pcVar5 = pcVar2;
    if ((*(byte *)((&__pioinfo)[iVar3] + 4 + (fh & 0x1f) * 8) & 0x80) != 0) {
      for (; pcVar5 < pcVar7; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          local_8 = local_8 + 1;
        }
      }
    }
  }
  if (local_4 == 0) {
    return local_8;
  }
  if ((*(byte *)((int)stream + 0xc) & 1) == 0) goto LAB_00483e05;
  if (*(int *)((int)stream + 4) == 0) {
    return local_4;
  }
  pcVar7 = pcVar7 + (*(int *)((int)stream + 4) - (int)pcVar2);
  iVar6 = (fh & 0x1f) * 8;
  if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 0x80) != 0) {
    lVar4 = _lseek(fh,0,2);
    if (lVar4 == local_4) {
      pcVar5 = *(char **)((int)stream + 8);
      pcVar2 = pcVar5 + (int)pcVar7;
      for (; pcVar5 < pcVar2; pcVar5 = pcVar5 + 1) {
        if (*pcVar5 == '\n') {
          pcVar7 = pcVar7 + 1;
        }
      }
      if ((*(uint *)((int)stream + 0xc) & 0x2000) != 0) {
LAB_00483dfc:
        pcVar7 = pcVar7 + 1;
      }
    }
    else {
      _lseek(fh,local_4,0);
      if (((pcVar7 < (char *)0x201) && ((*(uint *)((int)stream + 0xc) & 8) != 0)) &&
         ((*(uint *)((int)stream + 0xc) & 0x400) == 0)) {
        pcVar7 = (char *)0x200;
      }
      else {
        pcVar7 = *(char **)((int)stream + 0x18);
      }
      if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 4) != 0) goto LAB_00483dfc;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_00483e05:
  return local_4 + local_8;
}


/* ==== strrchr @ 00483e40 ==== */

/* Library Function - Single Match
    _strrchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strrchr(char *s,int c)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = s;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = s + 1;
    cVar1 = *s;
    s = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while ((char)c != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != (char)c) {
    pcVar3 = (char *)0x0;
  }
  return (char)pcVar3;
}


/* ==== tmpnam @ 00483e70 ==== */

char __cdecl tmpnam(char *s)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (DAT_005052d0 == '\0') {
    init_namebuf(0);
  }
  else {
    iVar2 = genfname(&DAT_005052d0);
    if (iVar2 != 0) {
      return '\0';
    }
  }
  iVar2 = _access(&DAT_005052d0,0);
  while (iVar2 == 0) {
    iVar2 = genfname(&DAT_005052d0);
    if (iVar2 != 0) {
      return '\0';
    }
    iVar2 = _access(&DAT_005052d0,0);
  }
  if (s == (char *)0x0) {
    return -0x30;
  }
  uVar3 = 0xffffffff;
  pcVar5 = &DAT_005052d0;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  pcVar6 = s;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  return (char)s;
}


/* ==== init_namebuf @ 00483f10 ==== */

void __cdecl init_namebuf(int flag)

{
  char cVar1;
  char *pcVar2;
  DWORD val;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  
  pcVar5 = &DAT_005052d0;
  if (flag != 0) {
    pcVar5 = &DAT_005052e0;
  }
  *(undefined2 *)pcVar5 = DAT_004c5cd4;
  pcVar2 = pcVar5 + 1;
  if ((*pcVar5 != '\\') && (*pcVar5 != '/')) {
    *pcVar2 = '\\';
    pcVar2 = pcVar5 + 2;
  }
  if (flag == 0) {
    *pcVar2 = 's';
  }
  else {
    *pcVar2 = 't';
  }
  pcVar2 = pcVar2 + 1;
  iVar7 = 0x20;
  val = GetCurrentProcessId();
  _ultoa(val,pcVar2,iVar7);
  uVar3 = 0xffffffff;
  pcVar2 = &DAT_004c7e34;
  do {
    pcVar6 = pcVar2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar7 = -1;
  do {
    pcVar2 = pcVar5;
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    pcVar2 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar2;
  } while (cVar1 != '\0');
  pcVar5 = pcVar6 + -uVar3;
  pcVar2 = pcVar2 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar2 = pcVar2 + 1;
  }
  return;
}


/* ==== genfname @ 00483f90 ==== */

int __cdecl genfname(char *fname)

{
  uchar uVar1;
  char cVar2;
  undefined3 extraout_var;
  ulong uVar3;
  undefined3 extraout_var_00;
  uint uVar4;
  uint uVar5;
  char *nptr;
  char *pcVar6;
  char *pcVar7;
  
  uVar1 = _mbsrchr((uchar *)fname,0x2e);
  nptr = (char *)(CONCAT31(extraout_var,uVar1) + 1);
  uVar3 = strtoul(nptr,(char **)0x0,0x20);
  if (0x7ffe < uVar3 + 1) {
    return -1;
  }
  cVar2 = _ultoa(uVar3 + 1,(char *)&fname,0x20);
  uVar4 = 0xffffffff;
  pcVar6 = (char *)CONCAT31(extraout_var_00,cVar2);
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar2 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar2 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)nptr = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    nptr = nptr + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *nptr = *pcVar6;
    pcVar6 = pcVar6 + 1;
    nptr = nptr + 1;
  }
  return 0;
}


/* ==== fprintf @ 00484000 ==== */

int __cdecl fprintf(void *stream,char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(stream);
  iVar1 = _output(stream,fmt,&stack0x0000000c);
  _ftbuf(flag,stream);
  return iVar1;
}


/* ==== free @ 00484040 ==== */

void __cdecl free(void *p)

{
  void *lpMem;
  void *pmap;
  void *local_4;
  
  lpMem = p;
  if (p != (void *)0x0) {
    __sbh_find_block(p,&local_4,&p);
    if (pmap != (void *)0x0) {
      __sbh_free_block(local_4,p,pmap);
      return;
    }
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== strncat @ 00484090 ==== */

/* Library Function - Single Match
    _strncat
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strncat(char *dst,char *src,uint n)

{
  byte bVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  cVar3 = (char)dst;
  if (n == 0) {
    return cVar3;
  }
  do {
    if (((uint)dst & 3) == 0) goto LAB_004840ba;
    uVar5 = *(uint *)dst;
    dst = (char *)((int)dst + 1);
  } while ((byte)uVar5 != 0);
  goto LAB_004840eb;
  while( true ) {
    if ((uVar5 & 0xff0000) == 0) {
      puVar6 = (uint *)((int)puVar6 + 2);
      goto LAB_004840fb;
    }
    if ((uVar5 & 0xff000000) == 0) break;
LAB_004840ba:
    do {
      puVar6 = (uint *)dst;
      dst = (char *)(puVar6 + 1);
    } while (((*puVar6 ^ 0xffffffff ^ *puVar6 + 0x7efefeff) & 0x81010100) == 0);
    uVar5 = *puVar6;
    if ((char)uVar5 == '\0') goto LAB_004840fb;
    if ((char)(uVar5 >> 8) == '\0') {
      puVar6 = (uint *)((int)puVar6 + 1);
      goto LAB_004840fb;
    }
  }
LAB_004840eb:
  puVar6 = (uint *)((int)dst + -1);
LAB_004840fb:
  if (((uint)src & 3) == 0) {
    uVar4 = n >> 2;
  }
  else {
    do {
      bVar1 = (byte)*(uint *)src;
      uVar5 = (uint)bVar1;
      src = (char *)((int)src + 1);
      if (bVar1 == 0) goto LAB_0048414a;
      *(byte *)puVar6 = bVar1;
      puVar6 = (uint *)((int)puVar6 + 1);
      n = n - 1;
      if (n == 0) goto LAB_00484140;
    } while (((uint)src & 3) != 0);
    uVar4 = n >> 2;
  }
  do {
    if (uVar4 == 0) {
      for (uVar5 = n & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        uVar4 = *(uint *)src;
        src = (char *)((int)src + 1);
        *(byte *)puVar6 = (byte)uVar4;
        puVar6 = (uint *)((int)puVar6 + 1);
        if ((byte)uVar4 == 0) {
          return cVar3;
        }
      }
LAB_00484140:
      *(byte *)puVar6 = 0;
      return cVar3;
    }
    uVar2 = *(uint *)src;
    uVar5 = *(uint *)src;
    src = (char *)((int)src + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar5 == '\0') {
LAB_0048414a:
        *(byte *)puVar6 = (byte)uVar5;
        return cVar3;
      }
      if ((char)(uVar5 >> 8) == '\0') {
        *(short *)puVar6 = (short)uVar5;
        return cVar3;
      }
      if ((uVar5 & 0xff0000) == 0) {
        *(short *)puVar6 = (short)uVar5;
        *(byte *)((int)puVar6 + 2) = 0;
        return cVar3;
      }
      if ((uVar5 & 0xff000000) == 0) {
        *puVar6 = uVar5;
        return cVar3;
      }
    }
    *puVar6 = uVar5;
    puVar6 = puVar6 + 1;
    uVar4 = uVar4 - 1;
  } while( true );
}


/* ==== strncpy @ 004841c0 ==== */

/* Library Function - Single Match
    _strncpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strncpy(char *dst,char *src,uint n)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  
  cVar3 = (char)dst;
  if (n == 0) {
    return cVar3;
  }
  if (((uint)src & 3) != 0) {
    while( true ) {
      uVar5 = *(uint *)src;
      src = (char *)((int)src + 1);
      *dst = (char)uVar5;
      dst = (char *)((int)dst + 1);
      n = n - 1;
      if (n == 0) {
        return cVar3;
      }
      if ((char)uVar5 == '\0') break;
      if (((uint)src & 3) == 0) {
        uVar5 = n >> 2;
        goto joined_r0x004841fe;
      }
    }
    do {
      if (((uint)dst & 3) == 0) {
        uVar5 = n >> 2;
        cVar4 = '\0';
        if (uVar5 == 0) goto LAB_0048423b;
        goto LAB_004842a9;
      }
      *dst = '\0';
      dst = (char *)((int)dst + 1);
      n = n - 1;
    } while (n != 0);
    return cVar3;
  }
  uVar5 = n >> 2;
  if (uVar5 != 0) {
    do {
      uVar1 = *(uint *)src;
      uVar2 = *(uint *)src;
      src = (char *)((int)src + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *(uint *)dst = 0;
joined_r0x004842a5:
          while( true ) {
            uVar5 = uVar5 - 1;
            dst = (char *)((int)dst + 4);
            if (uVar5 == 0) break;
LAB_004842a9:
            *(uint *)dst = 0;
          }
          cVar4 = '\0';
          n = n & 3;
          if (n != 0) goto LAB_0048423b;
          return cVar3;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *(uint *)dst = uVar2 & 0xff;
          goto joined_r0x004842a5;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *(uint *)dst = uVar2 & 0xffff;
          goto joined_r0x004842a5;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *(uint *)dst = uVar2;
          goto joined_r0x004842a5;
        }
      }
      *(uint *)dst = uVar2;
      dst = (char *)((int)dst + 4);
      uVar5 = uVar5 - 1;
joined_r0x004841fe:
    } while (uVar5 != 0);
    n = n & 3;
    if (n == 0) {
      return cVar3;
    }
  }
  do {
    cVar4 = (char)*(uint *)src;
    src = (char *)((int)src + 1);
    *dst = cVar4;
    dst = (char *)((int)dst + 1);
    if (cVar4 == '\0') {
      while (n = n - 1, n != 0) {
LAB_0048423b:
        *dst = cVar4;
        dst = (char *)((int)dst + 1);
      }
      return cVar3;
    }
    n = n - 1;
  } while (n != 0);
  return cVar3;
}


/* ==== fgetc @ 004842c0 ==== */

int __cdecl fgetc(void *stream)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)stream + 4) + -1;
  *(int *)((int)stream + 4) = iVar2;
  if (-1 < iVar2) {
    bVar1 = **(byte **)stream;
    *(byte **)stream = *(byte **)stream + 1;
    return (uint)bVar1;
  }
  iVar2 = _filbuf(stream);
  return iVar2;
}


/* ==== signal @ 004842f0 ==== */

void __cdecl signal(int sig,void *func)

{
  int *piVar1;
  undefined *extraout_EAX;
  undefined *puVar2;
  BOOL BVar3;
  
  if ((func == (void *)0x4) || (func == (void *)0x3)) {
    errno = 0x16;
    return;
  }
  if (sig != 2) {
    if (((sig != 0x15) && (sig != 0x16)) && (sig != 0xf)) {
      if (((sig != 8) && (sig != 4)) && (sig != 0xb)) {
        errno = 0x16;
        return;
      }
      siglookup(sig);
      if (extraout_EAX == (undefined *)0x0) {
        errno = 0x16;
        return;
      }
      puVar2 = extraout_EAX;
      if (*(int *)(extraout_EAX + 4) != sig) {
        return;
      }
      do {
        *(void **)(puVar2 + 8) = func;
        if (&_XcptActTab + _XcptActTabCount * 0xc <= puVar2 + 0xc) {
          return;
        }
        piVar1 = (int *)(puVar2 + 0x10);
        puVar2 = puVar2 + 0xc;
      } while (*piVar1 == sig);
      return;
    }
    if ((sig != 2) && (sig != 0x15)) goto LAB_004843a4;
  }
  if (DAT_00505300 == 0) {
    BVar3 = SetConsoleCtrlHandler((PHANDLER_ROUTINE)&LAB_00484460,1);
    if (BVar3 != 1) {
      _doserrno = GetLastError();
      errno = 0x16;
      return;
    }
    DAT_00505300 = 1;
  }
LAB_004843a4:
  switch(sig) {
  case 2:
    DAT_005052f0 = func;
    return;
  default:
    return;
  case 0xf:
    DAT_005052fc = func;
    return;
  case 0x15:
    DAT_005052f4 = func;
    return;
  case 0x16:
    DAT_005052f8 = func;
    return;
  }
}


/* ==== raise @ 004844b0 ==== */

int __cdecl raise(int sig)

{
  int iVar1;
  int iVar2;
  int extraout_EAX;
  int iVar3;
  code *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar2 = sig;
  switch(sig) {
  case 2:
    puVar6 = &DAT_005052f0;
    pcVar4 = DAT_005052f0;
    break;
  default:
    return -1;
  case 4:
  case 8:
  case 0xb:
    siglookup(sig);
    puVar6 = (undefined4 *)(extraout_EAX + 8);
    pcVar4 = (code *)*puVar6;
    break;
  case 0xf:
    puVar6 = &DAT_005052fc;
    pcVar4 = DAT_005052fc;
    break;
  case 0x15:
    puVar6 = &DAT_005052f4;
    pcVar4 = DAT_005052f4;
    break;
  case 0x16:
    puVar6 = &DAT_005052f8;
    pcVar4 = DAT_005052f8;
  }
  iVar1 = DAT_00505370;
  iVar3 = DAT_004d82b4;
  if (pcVar4 == (code *)0x1) {
    return 0;
  }
  if (pcVar4 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (((sig == 8) || (sig == 0xb)) || (iVar5 = sig, sig == 4)) {
    DAT_00505370 = 0;
    iVar5 = iVar1;
    if (sig == 8) {
      DAT_004d82b4 = 0x8c;
      sig = iVar3;
      goto LAB_0048456f;
    }
  }
  else {
LAB_0048456f:
    if (iVar2 == 8) {
      if (DAT_004d82a8 < DAT_004d82ac + DAT_004d82a8) {
        iVar3 = (DAT_004d82ac + DAT_004d82a8) - DAT_004d82a8;
        puVar6 = (undefined4 *)(DAT_004d82a8 * 0xc + 0x4d8238);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      goto LAB_004845a6;
    }
  }
  *puVar6 = 0;
LAB_004845a6:
  if (iVar2 == 8) {
    (*pcVar4)(8,DAT_004d82b4);
  }
  else {
    (*pcVar4)(iVar2);
    if ((iVar2 != 0xb) && (iVar2 != 4)) {
      return 0;
    }
  }
  if (iVar2 == 8) {
    DAT_004d82b4 = sig;
  }
  DAT_00505370 = iVar5;
  return 0;
}


/* ==== siglookup @ 00484630 ==== */

void __cdecl siglookup(int sig)

{
  int *piVar1;
  undefined *puVar2;
  
  if (DAT_004d8234 != sig) {
    puVar2 = &_XcptActTab;
    do {
      if (&_XcptActTab + _XcptActTabCount * 0xc <= puVar2 + 0xc) {
        return;
      }
      piVar1 = (int *)(puVar2 + 0x10);
      puVar2 = puVar2 + 0xc;
    } while (*piVar1 != sig);
  }
  return;
}


/* ==== _cinit @ 00484680 ==== */

void _cinit(void)

{
  if (_FPinit != (undefined *)0x0) {
    (*(code *)_FPinit)();
  }
  _initterm(&DAT_00495008,&DAT_00495010);
  _initterm(&DAT_00495000,&DAT_00495004);
  return;
}


/* ==== exit @ 004846b0 ==== */

void __cdecl exit(int status)

{
  doexit(status,0,0);
  return;
}


/* ==== __exit @ 004846d0 ==== */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __exit(int _Code)

{
  doexit(_Code,1,0);
  return;
}


/* ==== doexit @ 004846f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl doexit(int code,int quick,int retcaller)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  undefined4 *puVar2;
  UINT uExitCode;
  
  if (_C_Exit_Done == 1) {
    uExitCode = code;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  __C_Termination_Done = 1;
  _exitflag = (undefined1)retcaller;
  if (quick == 0) {
    if ((__onexitbegin != (undefined4 *)0x0) &&
       (puVar2 = (undefined4 *)(__onexitend + -4), puVar1 = __onexitbegin, __onexitbegin <= puVar2))
    {
      do {
        if ((code *)*puVar2 != (code *)0x0) {
          (*(code *)*puVar2)();
          puVar1 = __onexitbegin;
        }
        puVar2 = puVar2 + -1;
      } while (puVar1 <= puVar2);
    }
    _initterm(&DAT_00495014,&DAT_00495024);
  }
  _initterm(&DAT_00495028,&DAT_0049502c);
  if (retcaller == 0) {
    _C_Exit_Done = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(code);
  }
  return;
}


/* ==== _initterm @ 004847a0 ==== */

void __cdecl _initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != (code *)0x0) {
      (**(code **)begin)();
    }
  }
  return;
}


/* ==== _setjmp3 @ 004847c0 ==== */

/* Library Function - Single Match
    __setjmp3
   
   Library: Visual Studio */

int __cdecl _setjmp3(void *env,int count,...)

{
  int iVar1;
  uint uVar2;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 *puVar3;
  undefined4 unaff_EDI;
  undefined4 *puVar4;
  int *unaff_FS_OFFSET;
  undefined4 unaff_retaddr;
  int in_stack_0000000c;
  undefined4 in_stack_00000010;
  
  *(undefined4 *)env = unaff_EBP;
  *(undefined4 *)((int)env + 4) = unaff_EBX;
  *(undefined4 *)((int)env + 8) = unaff_EDI;
  *(undefined4 *)((int)env + 0xc) = unaff_ESI;
  *(BADSPACEBASE **)((int)env + 0x10) = register0x00000010;
  *(undefined4 *)((int)env + 0x14) = unaff_retaddr;
  *(undefined4 *)((int)env + 0x20) = 0x56433230;
  *(undefined4 *)((int)env + 0x24) = 0;
  iVar1 = *unaff_FS_OFFSET;
  *(int *)((int)env + 0x18) = iVar1;
  if (iVar1 == -1) {
    *(undefined4 *)((int)env + 0x1c) = 0xffffffff;
  }
  else if ((count == 0) ||
          (*(int *)((int)env + 0x24) = in_stack_0000000c, iVar1 = in_stack_0000000c, count == 1)) {
    *(undefined4 *)((int)env + 0x1c) = *(undefined4 *)(iVar1 + 0xc);
  }
  else {
    *(undefined4 *)((int)env + 0x1c) = in_stack_00000010;
    uVar2 = count - 2;
    if (uVar2 != 0) {
      puVar3 = (undefined4 *)&stack0x00000014;
      puVar4 = (undefined4 *)((int)env + 0x28);
      if (6 < uVar2) {
        uVar2 = 6;
      }
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
    }
  }
  return 0;
}


/* ==== time @ 00484840 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long __cdecl time(long *timer)

{
  DWORD DVar1;
  long lVar2;
  _SYSTEMTIME local_cc;
  _SYSTEMTIME local_bc;
  _TIME_ZONE_INFORMATION local_ac;
  
  GetLocalTime(&local_bc);
  GetSystemTime(&local_cc);
  if (local_cc.wMinute == DAT_00505362) {
    if (local_cc.wHour == DAT_00505360) {
      if (local_cc.wDay == DAT_0050535e) {
        if (local_cc.wMonth == DAT_0050535a) {
          if (local_cc.wYear == DAT_00505358) goto LAB_0048490f;
        }
      }
    }
  }
  DVar1 = GetTimeZoneInformation(&local_ac);
  if (DVar1 == 0xffffffff) {
    DAT_00505350 = -1;
  }
  else if (((DVar1 == 2) && (local_ac.DaylightDate.wMonth != 0)) && (local_ac.DaylightBias != 0)) {
    DAT_00505350 = 1;
  }
  else {
    DAT_00505350 = 0;
  }
  DAT_00505358 = local_cc.wYear;
  DAT_0050535a = local_cc.wMonth;
  _DAT_0050535c = local_cc.wDayOfWeek;
  DAT_0050535e = local_cc.wDay;
  DAT_00505360 = local_cc.wHour;
  DAT_00505362 = local_cc.wMinute;
  _DAT_00505364 = local_cc.wSecond;
  DAT_00505364_2 = local_cc.wMilliseconds;
LAB_0048490f:
  lVar2 = __loctotime_t((uint)local_bc.wYear,(uint)local_bc.wMonth,(uint)local_bc.wDay,
                        (uint)local_bc.wHour,(uint)local_bc.wMinute,(uint)local_bc.wSecond,
                        DAT_00505350);
  if (timer != (long *)0x0) {
    *timer = lVar2;
  }
  return lVar2;
}


/* ==== fread @ 00484970 ==== */

uint __cdecl fread(void *buffer,uint size,uint count,void *stream)

{
  void *stream_00;
  void *pvVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  void *pvVar5;
  void *pvVar6;
  undefined4 *puVar7;
  void *pvVar8;
  undefined4 *puVar9;
  
  stream_00 = stream;
  pvVar5 = (void *)(count * size);
  if (pvVar5 == (void *)0x0) {
    return 0;
  }
  pvVar6 = pvVar5;
  if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
    stream = (void *)0x1000;
    pvVar8 = (void *)0x1000;
  }
  else {
    pvVar8 = *(void **)((int)stream + 0x18);
    stream = pvVar8;
  }
  do {
    if (((*(uint *)((int)stream_00 + 0xc) & 0x10c) == 0) ||
       (pvVar1 = *(void **)((int)stream_00 + 4), pvVar1 == (void *)0x0)) {
      if (pvVar6 < pvVar8) {
        iVar3 = _filbuf(stream_00);
        if (iVar3 == -1) {
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        *(char *)buffer = (char)iVar3;
        pvVar8 = *(void **)((int)stream_00 + 0x18);
        buffer = (void *)((int)buffer + 1);
        iVar3 = -1;
        stream = pvVar8;
      }
      else {
        pvVar1 = pvVar6;
        if (pvVar8 != (void *)0x0) {
          pvVar1 = (void *)((int)pvVar6 - (uint)pvVar6 % (uint)pvVar8);
        }
        iVar2 = _read(*(int *)((int)stream_00 + 0x10),buffer,(uint)pvVar1);
        if (iVar2 == 0) {
          *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x10;
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        if (iVar2 == -1) {
          *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x20;
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        iVar3 = -iVar2;
        buffer = (void *)((int)buffer + iVar2);
      }
    }
    else {
      if (pvVar6 < pvVar1) {
        pvVar1 = pvVar6;
      }
      iVar3 = -(int)pvVar1;
      puVar7 = *(undefined4 **)stream_00;
      puVar9 = buffer;
      for (uVar4 = (uint)pvVar1 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar9 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar9 = puVar9 + 1;
      }
      for (uVar4 = (uint)pvVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
      buffer = (void *)((int)buffer + (int)pvVar1);
      *(int *)((int)stream_00 + 4) = *(int *)((int)stream_00 + 4) - (int)pvVar1;
      *(int *)stream_00 = *(int *)stream_00 + (int)pvVar1;
      pvVar8 = stream;
    }
    pvVar6 = (void *)((int)pvVar6 + iVar3);
    if (pvVar6 == (void *)0x0) {
      return count;
    }
  } while( true );
}


/* ==== qsort @ 00484ab0 ==== */

void __cdecl qsort(void *base,uint num,uint width,void *compare)

{
  uint uVar1;
  int iVar2;
  char *p;
  char *q;
  char *local_100;
  int *local_fc;
  undefined4 *local_f8;
  int local_f4;
  int local_f0 [30];
  undefined4 local_78 [30];
  
  if ((num < 2) || (width == 0)) {
    return;
  }
  local_100 = (char *)((num - 1) * width + (int)base);
  local_fc = local_f0;
  local_f8 = local_78;
  local_f4 = 0;
LAB_00484b04:
  uVar1 = (uint)((int)local_100 - (int)base) / width + 1;
  if (8 < uVar1) {
    swap((char *)((int)base + (uVar1 >> 1) * width),base,width);
    q = local_100 + width;
    p = base;
LAB_00484b7e:
    p = p + width;
    if (p <= local_100) goto code_r0x00484b88;
    goto LAB_00484b98;
  }
  shortsort(base,local_100,width,compare);
  goto LAB_00484b25;
code_r0x00484b88:
  iVar2 = (*compare)(p,base);
  if (iVar2 < 1) goto LAB_00484b7e;
LAB_00484b98:
  do {
    q = q + -width;
    if (q <= base) break;
    iVar2 = (*compare)(q,base);
  } while (-1 < iVar2);
  if (p <= q) {
    swap(p,q,width);
    goto LAB_00484b7e;
  }
  swap(base,q,width);
  if ((int)(q + (-1 - (int)base)) < (int)local_100 - (int)p) {
    if (p < local_100) {
      *local_f8 = p;
      *local_fc = (int)local_100;
      local_f4 = local_f4 + 1;
      local_f8 = local_f8 + 1;
      local_fc = local_fc + 1;
    }
    if ((char *)((int)base + width) < q) {
      local_100 = q + -width;
      goto LAB_00484b04;
    }
  }
  else {
    if ((char *)((int)base + width) < q) {
      *local_f8 = base;
      *local_fc = (int)q - width;
      local_f4 = local_f4 + 1;
      local_f8 = local_f8 + 1;
      local_fc = local_fc + 1;
    }
    base = p;
    if (p < local_100) goto LAB_00484b04;
  }
LAB_00484b25:
  local_f4 = local_f4 + -1;
  local_f8 = local_f8 + -1;
  local_fc = local_fc + -1;
  if (local_f4 < 0) {
    return;
  }
  local_100 = (char *)*local_fc;
  base = (char *)*local_f8;
  goto LAB_00484b04;
}


/* ==== shortsort @ 00484c60 ==== */

void __cdecl shortsort(char *lo,char *hi,uint width,void *comp)

{
  char *pcVar1;
  char *p;
  int iVar2;
  
  for (; p = lo, pcVar1 = lo, lo < hi; hi = hi + -width) {
    while (pcVar1 = pcVar1 + width, pcVar1 <= hi) {
      iVar2 = (*comp)(pcVar1,p);
      if (0 < iVar2) {
        p = pcVar1;
      }
    }
    swap(p,hi,width);
  }
  return;
}


/* ==== swap @ 00484cc0 ==== */

void __cdecl swap(char *p,char *q,uint width)

{
  char cVar1;
  
  if (p != q) {
    for (; width != 0; width = width - 1) {
      cVar1 = *p;
      *p = *q;
      p = p + 1;
      *q = cVar1;
      q = q + 1;
    }
  }
  return;
}


/* ==== _filbuf @ 00484cf0 ==== */

int __cdecl _filbuf(void *stream)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar2 = *(uint *)((int)stream + 0xc);
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) != 0) {
      *(uint *)((int)stream + 0xc) = uVar2 | 0x20;
      return -1;
    }
    *(uint *)((int)stream + 0xc) = uVar2 | 1;
    if ((uVar2 & 0x10c) == 0) {
      _getbuf(stream);
    }
    else {
      *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    }
    iVar3 = _read(*(int *)((int)stream + 0x10),*(void **)((int)stream + 8),
                  *(uint *)((int)stream + 0x18));
    *(int *)((int)stream + 4) = iVar3;
    if ((iVar3 != 0) && (iVar3 != -1)) {
      if ((*(uint *)((int)stream + 0xc) & 0x82) == 0) {
        uVar2 = *(uint *)((int)stream + 0x10);
        if (uVar2 == 0xffffffff) {
          puVar4 = &__badioinfo;
        }
        else {
          puVar4 = (undefined *)((&__pioinfo)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 8);
        }
        if ((puVar4[4] & 0x82) == 0x82) {
          *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 0x2000;
        }
      }
      if (((*(int *)((int)stream + 0x18) == 0x200) && ((*(uint *)((int)stream + 0xc) & 8) != 0)) &&
         ((*(uint *)((int)stream + 0xc) & 0x400) == 0)) {
        *(undefined4 *)((int)stream + 0x18) = 0x1000;
      }
      *(int *)((int)stream + 4) = iVar3 + -1;
      bVar1 = **(byte **)stream;
      *(byte **)stream = *(byte **)stream + 1;
      return (uint)bVar1;
    }
    *(undefined4 *)((int)stream + 4) = 0;
    *(uint *)((int)stream + 0xc) =
         *(uint *)((int)stream + 0xc) | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
  }
  return -1;
}


/* ==== malloc @ 00484de0 ==== */

void __cdecl malloc(uint size)

{
  _nh_malloc(size,_newmode);
  return;
}


/* ==== _nh_malloc @ 00484e00 ==== */

void __cdecl _nh_malloc(uint size,int nhFlag)

{
  int extraout_EAX;
  int iVar1;
  
  if (size < 0xffffffe1) {
    if (size == 0) {
      size = 1;
    }
    do {
      if (size < 0xffffffe1) {
        _heap_alloc(size);
        iVar1 = extraout_EAX;
      }
      else {
        iVar1 = 0;
      }
    } while (((iVar1 == 0) && (nhFlag != 0)) && (iVar1 = _callnewh(size), iVar1 != 0));
  }
  return;
}


/* ==== _heap_alloc @ 00484e50 ==== */

void __cdecl _heap_alloc(uint size)

{
  int extraout_EAX;
  uint dwBytes;
  
  dwBytes = size + 0xf & 0xfffffff0;
  if ((dwBytes <= __sbh_threshold) && (__sbh_alloc_block(size + 0xf >> 4), extraout_EAX != 0)) {
    return;
  }
  HeapAlloc(_crtheap,0,dwBytes);
  return;
}


/* ==== strtol @ 00484e90 ==== */

long __cdecl strtol(char *s,char **endptr,int base)

{
  ulong uVar1;
  
  uVar1 = strtoxl(s,endptr,base,0);
  return uVar1;
}


/* ==== strtoxl @ 00484eb0 ==== */

ulong __cdecl strtoxl(char *nptr,char **endptr,int ibase,int flags)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  uint local_c;
  byte *local_8;
  uint local_4;
  
  local_4 = 0;
  bVar5 = *nptr;
  pbVar1 = (byte *)nptr;
  while( true ) {
    local_c = (uint)bVar5;
    local_8 = pbVar1 + 1;
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[local_c * 2] & 8;
    }
    else {
      uVar2 = _isctype(local_c,8);
    }
    if (uVar2 == 0) break;
    bVar5 = *local_8;
    pbVar1 = local_8;
  }
  if (bVar5 == 0x2d) {
    flags = flags | 2;
  }
  else if (bVar5 != 0x2b) goto LAB_00484f3b;
  bVar5 = *local_8;
  local_8 = pbVar1 + 2;
  local_c = (uint)bVar5;
LAB_00484f3b:
  if (((ibase < 0) || (ibase == 1)) || (0x24 < ibase)) {
    if (endptr != (char **)0x0) {
      *endptr = nptr;
    }
    return 0;
  }
  if (ibase == 0) {
    if (bVar5 == 0x30) {
      if ((*local_8 == 0x78) || (ibase = 8, *local_8 == 0x58)) {
        ibase = 0x10;
      }
    }
    else {
      ibase = 10;
    }
  }
  if (((ibase == 0x10) && (bVar5 == 0x30)) && ((*local_8 == 0x78 || (*local_8 == 0x58)))) {
    bVar5 = local_8[1];
    local_c = (uint)bVar5;
    local_8 = local_8 + 2;
  }
  uVar2 = (uint)(0xffffffff / (ulonglong)(uint)ibase);
  do {
    if (__mb_cur_max < 2) {
      uVar3 = (byte)_pctype[local_c * 2] & 4;
    }
    else {
      uVar3 = _isctype(local_c,4);
    }
    if (uVar3 == 0) {
      if (__mb_cur_max < 2) {
        uVar3 = *(ushort *)(_pctype + local_c * 2) & 0x103;
      }
      else {
        uVar3 = _isctype(local_c,0x103);
      }
      if (uVar3 == 0) {
LAB_00485074:
        local_8 = local_8 + -1;
        if ((flags & 8U) == 0) {
          if (endptr != (char **)0x0) {
            local_8 = (byte *)nptr;
          }
          local_4 = 0;
        }
        else if (((flags & 4U) != 0) ||
                (((flags & 1U) == 0 &&
                 ((((flags & 2U) != 0 && (0x80000000 < local_4)) ||
                  (((flags & 2U) == 0 && (0x7fffffff < local_4)))))))) {
          errno = 0x22;
          if ((flags & 1U) == 0) {
            local_4 = ((flags & 2U) != 0) + 0x7fffffff;
          }
          else {
            local_4 = 0xffffffff;
          }
        }
        if (endptr != (char **)0x0) {
          *endptr = (char *)local_8;
        }
        if ((flags & 2U) != 0) {
          local_4 = -local_4;
        }
        return local_4;
      }
      iVar4 = toupper((int)(char)bVar5);
      uVar3 = iVar4 - 0x37;
    }
    else {
      uVar3 = (int)(char)bVar5 - 0x30;
    }
    if ((uint)ibase <= uVar3) goto LAB_00485074;
    if ((local_4 < uVar2) ||
       ((local_4 == uVar2 && (uVar3 <= (uint)(0xffffffff % (ulonglong)(uint)ibase))))) {
      local_4 = local_4 * ibase + uVar3;
      flags = flags | 8;
    }
    else {
      flags = flags | 0xc;
    }
    bVar5 = *local_8;
    local_8 = local_8 + 1;
    local_c = (uint)bVar5;
  } while( true );
}


/* ==== strtoul @ 00485140 ==== */

ulong __cdecl strtoul(char *nptr,char **endptr,int base)

{
  ulong uVar1;
  
  uVar1 = strtoxl(nptr,endptr,base,1);
  return uVar1;
}


/* ==== FUN_00485160 @ 00485160 ==== */

LPSTR __cdecl FUN_00485160(int param_1)

{
  char cVar1;
  undefined3 extraout_var;
  int iVar2;
  LPSTR pCVar3;
  byte *local_10;
  undefined *local_c;
  int local_8;
  undefined4 local_4;
  
  cVar1 = getenv("COMSPEC");
  local_10 = (byte *)CONCAT31(extraout_var,cVar1);
  if (param_1 == 0) {
    if (local_10 != (byte *)0x0) {
      iVar2 = _access((char *)local_10,0);
      return (LPSTR)(uint)(iVar2 == 0);
    }
    return (LPSTR)0x0;
  }
  local_c = &DAT_00493c90;
  local_8 = param_1;
  local_4 = 0;
  if (local_10 != (byte *)0x0) {
    pCVar3 = FUN_0048ada0(0,local_10,&local_10,(undefined4 *)0x0);
    if (pCVar3 != (LPSTR)0xffffffff) {
      return pCVar3;
    }
    if ((errno != 2) && (errno != 0xd)) {
      return (LPSTR)0xffffffff;
    }
  }
  local_10 = (byte *)0x493c84;
  if ((DAT_00505310 & 0x8000) == 0) {
    local_10 = (byte *)s_cmd_exe_004c8c70;
  }
  pCVar3 = FUN_0048abb0(0,local_10,&local_10,(undefined4 *)0x0);
  return pCVar3;
}


/* ==== getenv @ 00485210 ==== */

char __cdecl getenv(char *name)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint n;
  uint uVar4;
  char *a;
  int *piVar5;
  char *pcVar6;
  
  if (((_environ != (int *)0x0) ||
      (((_wenviron == 0 || (iVar2 = __wtomb_environ(), iVar2 == 0)) && (_environ != (int *)0x0))))
     && (name != (char *)0x0)) {
    uVar3 = 0xffffffff;
    a = (char *)*_environ;
    pcVar6 = name;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    n = ~uVar3 - 1;
    piVar5 = _environ;
    if (a != (char *)0x0) {
      do {
        uVar4 = 0xffffffff;
        pcVar6 = a;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        if (((n < ~uVar4 - 1) && (a[n] == '=')) && (iVar2 = _strnicoll(a,name,n), iVar2 == 0)) {
          return (char)~uVar3 + (char)*piVar5;
        }
        a = (char *)piVar5[1];
        piVar5 = piVar5 + 1;
        if (a == (char *)0x0) {
          return '\0';
        }
      } while( true );
    }
  }
  return '\0';
}


/* ==== printf @ 004852a0 ==== */

int __cdecl printf(char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(&DAT_004d7fc0);
  iVar1 = _output(&DAT_004d7fc0,fmt,&stack0x00000008);
  _ftbuf(flag,&DAT_004d7fc0);
  return iVar1;
}


/* ==== fputs @ 004852e0 ==== */

int __cdecl fputs(char *s,void *stream)

{
  char cVar1;
  int flag;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar3 = 0xffffffff;
  pcVar4 = s;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  flag = _stbuf(stream);
  uVar2 = fwrite(s,1,~uVar3 - 1,stream);
  _ftbuf(flag,stream);
  return -(uint)(uVar2 != ~uVar3 - 1);
}


/* ==== strtod @ 00485370 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double __cdecl strtod(char *s,char **endptr)

{
  byte bVar1;
  double dVar2;
  uint uVar3;
  uint *extraout_EAX;
  byte *flt;
  int unaff_EDI;
  byte *pbVar4;
  
  flt = (byte *)s;
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar3 = (byte)_pctype[(uint)*flt * 2] & 8;
    }
    else {
      uVar3 = _isctype((uint)*flt,8);
    }
    if (uVar3 == 0) break;
    flt = flt + 1;
  }
  uVar3 = 0xffffffff;
  pbVar4 = flt;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
  } while (bVar1 != 0);
  _fltin2(flt,(char *)(~uVar3 - 1),0,0,unaff_EDI);
  if (endptr != (char **)0x0) {
    *endptr = (char *)(flt + extraout_EAX[1]);
  }
  uVar3 = *extraout_EAX;
  if ((uVar3 & 0x240) == 0) {
    if ((uVar3 & 0x81) == 0) {
      if ((uVar3 & 0x100) == 0) {
        return *(double *)(extraout_EAX + 4);
      }
      dVar2 = 0.0;
    }
    else {
      dVar2 = __HUGE;
      if (*flt == 0x2d) {
        errno = 0x22;
        return -__HUGE;
      }
    }
    errno = 0x22;
    return dVar2;
  }
  if (endptr == (char **)0x0) {
    return 0.0;
  }
  *endptr = s;
  return 0.0;
}


/* ==== fgets @ 00485430 ==== */

char __cdecl fgets(char *buf,int n,void *stream)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  if (n < 1) {
    return '\0';
  }
  iVar3 = n + -1;
  pcVar4 = buf;
  if (iVar3 != 0) {
    while( true ) {
      iVar1 = *(int *)((int)stream + 4) + -1;
      *(int *)((int)stream + 4) = iVar1;
      if (iVar1 < 0) {
        uVar2 = _filbuf(stream);
      }
      else {
        uVar2 = (uint)**(byte **)stream;
        *(byte **)stream = *(byte **)stream + 1;
      }
      if (uVar2 == 0xffffffff) break;
      *pcVar4 = (char)uVar2;
      pcVar4 = pcVar4 + 1;
      if ((char)uVar2 == '\n') goto LAB_00485496;
      iVar3 = iVar3 + -1;
      if (iVar3 == 0) {
        *pcVar4 = '\0';
        return (char)buf;
      }
    }
    if (pcVar4 == buf) {
      return '\0';
    }
  }
LAB_00485496:
  *pcVar4 = '\0';
  return (char)buf;
}


/* ==== strpbrk @ 004854b0 ==== */

/* Library Function - Single Match
    _strpbrk
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strpbrk(char *s,char *set)

{
  byte bVar1;
  byte *pbVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *set;
    if (bVar1 == 0) break;
    set = set + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  do {
    bVar1 = *s;
    pbVar2 = (byte *)(uint)bVar1;
    if (bVar1 == 0) break;
    pbVar2 = (byte *)s;
    s = s + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return (char)pbVar2;
}


/* ==== toupper @ 004854f0 ==== */

int __cdecl toupper(int c)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int unaff_EBX;
  uint local_8 [2];
  
  iVar1 = c;
  if (DAT_005055d0 == 0) {
    if ((0x60 < c) && (c < 0x7b)) {
      return c + -0x20;
    }
  }
  else {
    if (c < 0x100) {
      if (__mb_cur_max < 2) {
        uVar2 = (byte)_pctype[c * 2] & 2;
      }
      else {
        uVar2 = _isctype(c,2);
      }
      if (uVar2 == 0) {
        return iVar1;
      }
    }
    iVar3 = c;
    if ((_pctype[(iVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      c._0_2_ = (ushort)(byte)iVar1;
      iVar3 = 1;
    }
    else {
      c._0_2_ = CONCAT11((byte)iVar1,(char)((uint)iVar1 >> 8));
      c._3_1_ = SUB41(iVar3,3);
      c._0_3_ = (uint3)(ushort)c;
      iVar3 = 2;
    }
    iVar3 = __crtLCMapStringA(DAT_005055d0,0x200,(char *)&c,iVar3,(char *)local_8,3,0,unaff_EBX);
    if (iVar3 == 0) {
      return iVar1;
    }
    if (iVar3 == 1) {
      return local_8[0] & 0xff;
    }
    c = (local_8[0] >> 8 & 0xff) << 8 | local_8[0] & 0xff;
  }
  return c;
}


/* ==== realloc @ 004855f0 ==== */

void __cdecl realloc(void *p,uint size)

{
  byte *pmap;
  int iVar1;
  undefined4 *extraout_EAX;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  void *local_8;
  void *local_4;
  
  if (p == (void *)0x0) {
    malloc(size);
    return;
  }
  if (size == 0) {
    free(p);
    return;
  }
  if (size < 0xffffffe1) {
    if (size == 0) {
      size = 0x10;
    }
    else {
      size = size + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar4 = (undefined4 *)0x0;
    if (size < 0xffffffe1) {
      __sbh_find_block(p,&local_4,&local_8);
      if (pmap == (byte *)0x0) {
        puVar4 = HeapReAlloc(_crtheap,0,p,size);
        goto LAB_0048575a;
      }
      if (size < __sbh_threshold) {
        iVar1 = __sbh_resize_block(local_4,local_8,pmap,size >> 4);
        puVar4 = p;
        if (iVar1 != 0) goto LAB_004856ef;
        __sbh_alloc_block(size >> 4);
        if (extraout_EAX != (undefined4 *)0x0) {
          uVar3 = (uint)*pmap << 4;
          if (size <= (uint)*pmap << 4) {
            uVar3 = size;
          }
          puVar5 = extraout_EAX;
          for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
            puVar5 = (undefined4 *)((int)puVar5 + 1);
          }
          __sbh_free_block(local_4,local_8,pmap);
          puVar4 = extraout_EAX;
          goto LAB_004856ef;
        }
      }
      else {
LAB_004856ef:
        if (puVar4 != (undefined4 *)0x0) {
          return;
        }
      }
      puVar4 = HeapAlloc(_crtheap,0,size);
      if (puVar4 != (undefined4 *)0x0) {
        uVar3 = (uint)*pmap << 4;
        if (size <= (uint)*pmap << 4) {
          uVar3 = size;
        }
        puVar5 = p;
        puVar6 = puVar4;
        for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        __sbh_free_block(local_4,local_8,pmap);
        goto LAB_0048575a;
      }
    }
    else {
LAB_0048575a:
      if (puVar4 != (undefined4 *)0x0) {
        return;
      }
    }
    if (_newmode == 0) {
      return;
    }
    iVar1 = _callnewh(size);
    if (iVar1 == 0) {
      return;
    }
  } while( true );
}


/* ==== fwrite @ 00485790 ==== */

uint __cdecl fwrite(void *buf,uint size,uint n,void *stream)

{
  void *stream_00;
  void *pvVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  void *pvVar5;
  void *pvVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  stream_00 = stream;
  pvVar5 = (void *)(n * size);
  if (pvVar5 == (void *)0x0) {
    return 0;
  }
  pvVar6 = pvVar5;
  if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
    stream = (void *)0x1000;
  }
  else {
    stream = *(void **)((int)stream + 0x18);
  }
  do {
    uVar4 = *(uint *)((int)stream_00 + 0xc) & 0x108;
    if ((uVar4 == 0) || (pvVar1 = *(void **)((int)stream_00 + 4), pvVar1 == (void *)0x0)) {
      if (pvVar6 < stream) {
        iVar2 = _flsbuf((int)*(char *)buf,stream_00);
        if (iVar2 == -1) goto LAB_004858c4;
        stream = *(void **)((int)stream_00 + 0x18);
        buf = (void *)((int)buf + 1);
        pvVar6 = (void *)((int)pvVar6 - 1);
        if ((int)stream < 1) {
          stream = (void *)0x1;
        }
      }
      else {
        if ((uVar4 != 0) && (iVar2 = _flush(stream_00), iVar2 != 0)) {
LAB_004858c4:
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        pvVar1 = pvVar6;
        if (stream != (void *)0x0) {
          pvVar1 = (void *)((int)pvVar6 - (uint)pvVar6 % (uint)stream);
        }
        pvVar3 = (void *)_write(*(int *)((int)stream_00 + 0x10),buf,(uint)pvVar1);
        if (pvVar3 == (void *)0xffffffff) {
LAB_004858a9:
          *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x20;
          return (uint)((int)pvVar5 - (int)pvVar6) / size;
        }
        pvVar6 = (void *)((int)pvVar6 - (int)pvVar3);
        buf = (void *)((int)buf + (int)pvVar3);
        if (pvVar3 < pvVar1) goto LAB_004858a9;
      }
    }
    else {
      if (pvVar6 < pvVar1) {
        pvVar1 = pvVar6;
      }
      pvVar6 = (void *)((int)pvVar6 - (int)pvVar1);
      puVar7 = buf;
      puVar8 = *(undefined4 **)stream_00;
      for (uVar4 = (uint)pvVar1 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      for (uVar4 = (uint)pvVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      buf = (void *)((int)buf + (int)pvVar1);
      *(int *)((int)stream_00 + 4) = *(int *)((int)stream_00 + 4) - (int)pvVar1;
      *(int *)stream_00 = *(int *)stream_00 + (int)pvVar1;
    }
    if (pvVar6 == (void *)0x0) {
      return n;
    }
  } while( true );
}


/* ==== fmod @ 004858e0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

double fmod(double x,double y)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  float10 fVar1;
  
  __fload(x._0_4_,x._4_4_);
  __fload(y._0_4_,y._4_4_);
  __trandisp2(extraout_ECX,extraout_EDX);
  fVar1 = (float10)FUN_0048b22e();
  return (double)fVar1;
}


/* ==== _CIfmod @ 004858ea ==== */

double __fastcall _CIfmod(void)

{
  undefined4 in_ECX;
  float10 fVar1;
  
  fVar1 = (float10)__cintrindisp2(in_ECX,0x4d7f50);
  return (double)fVar1;
}


/* ==== _ftol @ 00485914 ==== */

/* Library Function - Single Match
    __ftol
   
   Library: Visual Studio */

longlong _ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}


/* ==== rename @ 00485a20 ==== */

int __cdecl rename(char *oldname,char *newname)

{
  BOOL BVar1;
  ulong oserrno;
  
  BVar1 = MoveFileA(oldname,newname);
  if (BVar1 == 0) {
    oserrno = GetLastError();
  }
  else {
    oserrno = 0;
  }
  if (oserrno != 0) {
    _dosmaperr(oserrno);
    return -1;
  }
  return 0;
}


/* ==== strtok @ 00485a60 ==== */

char __cdecl strtok(char *s,char *delim)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  byte local_20 [32];
  
  pbVar4 = local_20;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    pbVar4[0] = 0;
    pbVar4[1] = 0;
    pbVar4[2] = 0;
    pbVar4[3] = 0;
    pbVar4 = pbVar4 + 4;
  }
  do {
    bVar1 = *delim;
    delim = delim + 1;
    local_20[bVar1 >> 3] = local_20[bVar1 >> 3] | '\x01' << (bVar1 & 7);
  } while (bVar1 != 0);
  if (s == (char *)0x0) {
    s = (char *)_nexttoken;
  }
  bVar1 = *s;
  bVar2 = local_20[bVar1 >> 3] & (byte)(1 << (bVar1 & 7));
  while ((bVar2 != 0 && (bVar1 != 0))) {
    bVar1 = s[1];
    s = s + 1;
    bVar2 = local_20[bVar1 >> 3] & (byte)(1 << (bVar1 & 7));
  }
  bVar1 = *s;
  _nexttoken = (byte *)s;
  do {
    if (bVar1 == 0) {
LAB_00485b27:
      return -((byte *)s != _nexttoken) & (byte)s;
    }
    if ((local_20[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0) {
      *_nexttoken = 0;
      _nexttoken = _nexttoken + 1;
      goto LAB_00485b27;
    }
    bVar1 = _nexttoken[1];
    _nexttoken = _nexttoken + 1;
  } while( true );
}


/* ==== strcmp @ 00485b40 ==== */

/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl strcmp(char *a,char *b)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  
  if (((uint)a & 3) != 0) {
    if (((uint)a & 1) != 0) {
      bVar4 = *a;
      a = a + 1;
      bVar5 = bVar4 < (byte)*b;
      if (bVar4 != *b) goto LAB_00485b84;
      b = b + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)a & 2) == 0) goto LAB_00485b50;
    }
    uVar1 = *(undefined2 *)a;
    a = a + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*b;
    if (bVar4 != *b) goto LAB_00485b84;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)b[1];
    if (bVar4 != b[1]) goto LAB_00485b84;
    if (bVar4 == 0) {
      return 0;
    }
    b = b + 2;
  }
LAB_00485b50:
  while( true ) {
    uVar2 = *(undefined4 *)a;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*b;
    if (bVar4 != *b) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 8);
    bVar5 = bVar4 < (byte)b[1];
    if (bVar4 != b[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 0x10);
    bVar5 = bVar4 < (byte)b[2];
    if (bVar4 != b[2]) break;
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < (byte)b[3];
    if (bVar3 != b[3]) break;
    b = b + 4;
    a = a + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_00485b84:
  return (uint)bVar5 * -2 + 1;
}


/* ==== strlen @ 00485bd0 ==== */

/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

uint __cdecl strlen(char *s)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)s;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_00485bf0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00485c23:
  return (uint)((int)puVar2 + (-1 - (int)s));
LAB_00485bf0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)s;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (uint)((int)puVar3 + (1 - (int)s));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (uint)((int)puVar3 + (2 - (int)s));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_00485c23;
}


/* ==== atol @ 00485c50 ==== */

long __cdecl atol(char *s)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint c;
  int iVar4;
  byte *pbVar5;
  
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[(uint)(byte)*s * 2] & 8;
    }
    else {
      uVar2 = _isctype((uint)(byte)*s,8);
    }
    if (uVar2 == 0) break;
    s = s + 1;
  }
  uVar2 = (uint)(byte)*s;
  pbVar5 = (byte *)(s + 1);
  if ((uVar2 == 0x2d) || (c = uVar2, uVar2 == 0x2b)) {
    c = (uint)*pbVar5;
    pbVar5 = (byte *)(s + 2);
  }
  iVar4 = 0;
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar3 = (byte)_pctype[c * 2] & 4;
    }
    else {
      uVar3 = _isctype(c,4);
    }
    if (uVar3 == 0) break;
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    iVar4 = (c - 0x30) + iVar4 * 10;
    c = (uint)bVar1;
  }
  if (uVar2 == 0x2d) {
    iVar4 = -iVar4;
  }
  return iVar4;
}


/* ==== atoi @ 00485cf0 ==== */

int __cdecl atoi(char *s)

{
  long lVar1;
  
  lVar1 = atol(s);
  return lVar1;
}


/* ==== longjmp @ 00485d00 ==== */

/* WARNING: Unable to track spacebase fully for stack */
/* Library Function - Single Match
    _longjmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl longjmp(void *env,int value)

{
  PVOID pvVar1;
  int iVar2;
  int *unaff_FS_OFFSET;
  
  pvVar1 = *(PVOID *)((int)env + 0x18);
  if (pvVar1 != (PVOID)*unaff_FS_OFFSET) {
    __global_unwind2(pvVar1);
  }
  if (pvVar1 != (PVOID)0x0) {
    iVar2 = FUN_0048c4f0();
    if ((iVar2 == 0) || (*(int *)((int)env + 0x20) != 0x56433230)) {
      __local_unwind2((int)pvVar1,*(int *)((int)env + 0x1c));
    }
    else if (*(code **)((int)env + 0x24) != (code *)0x0) {
      (**(code **)((int)env + 0x24))(env);
    }
  }
  FUN_00486be6();
                    /* WARNING: Could not recover jumptable at 0x00485d75. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)((int)env + 0x14))();
  return;
}


/* ==== vsprintf @ 00485d80 ==== */

int __cdecl vsprintf(char *buf,char *fmt,void *args)

{
  int iVar1;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 local_14;
  
  local_18 = buf;
  local_20 = buf;
  local_14 = 0x42;
  local_1c = 0x7fffffff;
  iVar1 = _output(&local_20,fmt,args);
  local_1c = local_1c + -1;
  if (-1 < local_1c) {
    *local_20 = '\0';
    return iVar1;
  }
  _flsbuf(0,&local_20);
  return iVar1;
}


/* ==== ctime @ 00485df0 ==== */

char __cdecl ctime(long *timer)

{
  char cVar1;
  void *tm;
  
  localtime(timer);
  if (tm != (void *)0x0) {
    cVar1 = asctime(tm);
    return cVar1;
  }
  return '\0';
}


/* ==== srand @ 00485e10 ==== */

void __cdecl srand(uint seed)

{
  holdrand = seed;
  return;
}


/* ==== rand @ 00485e20 ==== */

int rand(void)

{
  holdrand = holdrand * 0x343fd + 0x269ec3;
  return holdrand >> 0x10 & 0x7fff;
}


/* ==== fputc @ 00485e50 ==== */

int __cdecl fputc(int c,void *stream)

{
  int iVar1;
  
  iVar1 = *(int *)((int)stream + 4) + -1;
  *(int *)((int)stream + 4) = iVar1;
  if (-1 < iVar1) {
    **(undefined1 **)stream = (char)c;
    *(int *)stream = *(int *)stream + 1;
    return c & 0xff;
  }
  iVar1 = _flsbuf(c,stream);
  return iVar1;
}


/* ==== strstr @ 00485e80 ==== */

/* Library Function - Single Match
    _strstr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char __cdecl strstr(char *s,char *sub)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  uint *puVar10;
  char *pcVar11;
  
  cVar3 = *sub;
  if (cVar3 == '\0') {
    return (char)s;
  }
  if (sub[1] == '\0') {
    while (((uint)s & 3) != 0) {
      uVar5 = *(uint *)s;
      if ((char)uVar5 == cVar3) {
        return (char)s;
      }
      s = (char *)((int)s + 1);
      if ((char)uVar5 == '\0') {
        return '\0';
      }
    }
    while( true ) {
      while( true ) {
        uVar5 = *(uint *)s;
        uVar8 = uVar5 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar7 = uVar5 ^ 0xffffffff ^ uVar5 + 0x7efefeff;
        puVar10 = (uint *)((int)s + 4);
        if (((uVar8 ^ 0xffffffff ^ uVar8 + 0x7efefeff) & 0x81010100) != 0) break;
        s = (char *)puVar10;
        if ((uVar7 & 0x81010100) != 0) {
          if ((uVar7 & 0x1010100) != 0) {
            return '\0';
          }
          if ((uVar5 + 0x7efefeff & 0x80000000) == 0) {
            return '\0';
          }
        }
      }
      uVar5 = *(uint *)s;
      cVar4 = (char)s;
      if ((char)uVar5 == cVar3) {
        return cVar4;
      }
      if ((char)uVar5 == '\0') {
        return '\0';
      }
      cVar6 = (char)(uVar5 >> 8);
      if (cVar6 == cVar3) {
        return cVar4 + '\x01';
      }
      if (cVar6 == '\0') {
        return '\0';
      }
      cVar6 = (char)(uVar5 >> 0x10);
      if (cVar6 == cVar3) {
        return cVar4 + '\x02';
      }
      if (cVar6 == '\0') break;
      cVar6 = (char)(uVar5 >> 0x18);
      if (cVar6 == cVar3) {
        return cVar4 + '\x03';
      }
      s = (char *)puVar10;
      if (cVar6 == '\0') {
        return '\0';
      }
    }
    return '\0';
  }
  do {
    cVar4 = *s;
    do {
      while (s = s + 1, cVar4 != cVar3) {
        if (cVar4 == '\0') {
          return '\0';
        }
        cVar4 = *s;
      }
      cVar4 = *s;
      pcVar11 = s + 1;
      pcVar9 = sub;
    } while (cVar4 != sub[1]);
    do {
      if (pcVar9[2] == '\0') {
LAB_00485ef3:
        return (char)s + -1;
      }
      if (*pcVar11 != pcVar9[2]) break;
      pcVar1 = pcVar9 + 3;
      if (*pcVar1 == '\0') goto LAB_00485ef3;
      pcVar2 = pcVar11 + 1;
      pcVar9 = pcVar9 + 2;
      pcVar11 = pcVar11 + 2;
    } while (*pcVar1 == *pcVar2);
  } while( true );
}


/* ==== atof @ 00485f00 ==== */

double __cdecl atof(char *s)

{
  byte bVar1;
  uint uVar2;
  int extraout_EAX;
  int unaff_EDI;
  byte *pbVar3;
  
  while( true ) {
    if (__mb_cur_max < 2) {
      uVar2 = (byte)_pctype[(uint)(byte)*s * 2] & 8;
    }
    else {
      uVar2 = _isctype((uint)(byte)*s,8);
    }
    if (uVar2 == 0) break;
    s = s + 1;
  }
  uVar2 = 0xffffffff;
  pbVar3 = (byte *)s;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0);
  _fltin2(s,(char *)(~uVar2 - 1),0,0,unaff_EDI);
  return *(double *)(extraout_EAX + 0x10);
}


/* ==== _XcptFilter @ 00485f60 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _XcptFilter(ulong xcptnum,void *pxcptptrs)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  undefined4 *puVar6;
  int iVar7;
  
  piVar4 = (int *)func_0x004860a0(xcptnum);
  uVar3 = DAT_00505370;
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    LVar5 = UnhandledExceptionFilter(pxcptptrs);
    return LVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 != (code *)0x1) {
    DAT_00505370 = pxcptptrs;
    if (piVar4[1] == 8) {
      if (DAT_004d82a8 < DAT_004d82ac + DAT_004d82a8) {
        iVar7 = (DAT_004d82ac + DAT_004d82a8) - DAT_004d82a8;
        puVar6 = (undefined4 *)(DAT_004d82a8 * 0xc + 0x4d8238);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar2 = DAT_004d82b4;
      iVar7 = *piVar4;
      if (iVar7 == -0x3fffff72) {
        DAT_004d82b4 = 0x83;
      }
      else if (iVar7 == -0x3fffff70) {
        DAT_004d82b4 = 0x81;
      }
      else if (iVar7 == -0x3fffff6f) {
        DAT_004d82b4 = 0x84;
      }
      else if (iVar7 == -0x3fffff6d) {
        DAT_004d82b4 = 0x85;
      }
      else if (iVar7 == -0x3fffff73) {
        DAT_004d82b4 = 0x82;
      }
      else if (iVar7 == -0x3fffff71) {
        DAT_004d82b4 = 0x86;
      }
      else if (iVar7 == -0x3fffff6e) {
        DAT_004d82b4 = 0x8a;
      }
      (*pcVar1)(8,DAT_004d82b4);
      DAT_004d82b4 = uVar2;
      DAT_00505370 = (void *)uVar3;
      return -1;
    }
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    DAT_00505370 = (void *)uVar3;
    return -1;
  }
  return -1;
}


/* ==== _setenvp @ 004860f0 ==== */

void _setenvp(void)

{
  char cVar1;
  char cVar2;
  int *extraout_EAX;
  int extraout_EAX_00;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  int *piVar9;
  char *pcVar10;
  int *local_4;
  
  iVar7 = 0;
  cVar2 = *_aenvptr;
  pcVar6 = _aenvptr;
  while (cVar2 != '\0') {
    if (cVar2 != '=') {
      iVar7 = iVar7 + 1;
    }
    uVar3 = 0xffffffff;
    pcVar8 = pcVar6;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar2 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar2 != '\0');
    pcVar8 = pcVar6 + ~uVar3;
    pcVar6 = pcVar6 + ~uVar3;
    cVar2 = *pcVar8;
  }
  malloc(iVar7 * 4 + 4);
  _environ = extraout_EAX;
  if (extraout_EAX == (int *)0x0) {
    _amsg_exit(9);
  }
  cVar2 = *_aenvptr;
  piVar9 = extraout_EAX;
  local_4 = extraout_EAX;
  pcVar6 = _aenvptr;
  do {
    if (cVar2 == '\0') {
      free(_aenvptr);
      _aenvptr = (char *)0x0;
      *piVar9 = 0;
      return;
    }
    uVar3 = 0xffffffff;
    pcVar8 = pcVar6;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    if (cVar2 != '=') {
      malloc(uVar3);
      *piVar9 = extraout_EAX_00;
      if (extraout_EAX_00 == 0) {
        _amsg_exit(9);
      }
      uVar4 = 0xffffffff;
      pcVar8 = pcVar6;
      do {
        pcVar10 = pcVar8;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar10 = pcVar8 + 1;
        cVar2 = *pcVar8;
        pcVar8 = pcVar10;
      } while (cVar2 != '\0');
      uVar4 = ~uVar4;
      pcVar8 = pcVar10 + -uVar4;
      pcVar10 = (char *)*local_4;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar10 = pcVar10 + 4;
      }
      piVar9 = local_4 + 1;
      for (uVar4 = uVar4 & 3; local_4 = piVar9, uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar10 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      }
    }
    cVar2 = pcVar6[uVar3];
    pcVar6 = pcVar6 + uVar3;
  } while( true );
}


/* ==== _setargv @ 004861e0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _setargv(void)

{
  char **argv;
  char *cmdstart;
  int local_8;
  int local_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_00505378,0x104);
  _DAT_0050533c = &DAT_00505378;
  cmdstart = _acmdln;
  if (*_acmdln == '\0') {
    cmdstart = &DAT_00505378;
  }
  parse_cmdline(cmdstart,(char **)0x0,(char *)0x0,&local_8,&local_4);
  malloc(local_4 + local_8 * 4);
  if (argv == (char **)0x0) {
    _amsg_exit(8);
  }
  parse_cmdline(cmdstart,argv,(char *)(argv + local_8),&local_8,&local_4);
  __argv = argv;
  __argc = local_8 + -1;
  return;
}


/* ==== parse_cmdline @ 00486280 ==== */

void __cdecl parse_cmdline(char *cmdstart,char **argv,char *args,int *numargs,int *numchars)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  byte *pbVar7;
  uint uVar8;
  
  piVar6 = numchars;
  *numchars = 0;
  *numargs = 1;
  if (argv != (char **)0x0) {
    *argv = args;
    argv = argv + 1;
  }
  if (*cmdstart == '\"') {
    bVar2 = cmdstart[1];
    while ((pbVar7 = (byte *)(cmdstart + 1), bVar2 != 0x22 && (bVar2 != 0))) {
      if (((*(byte *)((int)&DAT_00505488 + bVar2 + 1) & 4) != 0) &&
         (*numchars = *numchars + 1, (byte *)args != (byte *)0x0)) {
        *args = *pbVar7;
        args = args + 1;
        pbVar7 = (byte *)(cmdstart + 2);
      }
      *numchars = *numchars + 1;
      if ((byte *)args != (byte *)0x0) {
        *args = *pbVar7;
        args = args + 1;
      }
      cmdstart = (char *)pbVar7;
      bVar2 = pbVar7[1];
    }
    *numchars = *numchars + 1;
    if ((byte *)args != (byte *)0x0) {
      *args = 0;
      args = args + 1;
    }
    if (*pbVar7 == 0x22) {
      pbVar7 = (byte *)(cmdstart + 2);
    }
  }
  else {
    do {
      *piVar6 = *piVar6 + 1;
      if ((byte *)args != (byte *)0x0) {
        *args = *cmdstart;
        args = args + 1;
      }
      bVar2 = *cmdstart;
      pbVar7 = (byte *)(cmdstart + 1);
      numchars = (int *)(uint)bVar2;
      if ((*(byte *)((int)numchars + 0x505489) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if ((byte *)args != (byte *)0x0) {
          *args = *pbVar7;
          args = args + 1;
        }
        pbVar7 = (byte *)(cmdstart + 2);
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_00486359;
      cmdstart = (char *)pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_00486359:
      pbVar7 = pbVar7 + -1;
    }
    else if ((byte *)args != (byte *)0x0) {
      args[-1] = 0;
    }
  }
  bVar4 = false;
  bVar5 = false;
  while (*pbVar7 != 0) {
    for (; (*pbVar7 == 0x20 || (*pbVar7 == 9)); pbVar7 = pbVar7 + 1) {
    }
    if (*pbVar7 == 0) break;
    if (argv != (char **)0x0) {
      *argv = args;
      argv = argv + 1;
    }
    *numargs = *numargs + 1;
    while( true ) {
      uVar8 = 0;
      bVar3 = true;
      bVar2 = *pbVar7;
      while (bVar2 == 0x5c) {
        pbVar1 = pbVar7 + 1;
        pbVar7 = pbVar7 + 1;
        uVar8 = uVar8 + 1;
        bVar2 = *pbVar1;
      }
      if (*pbVar7 == 0x22) {
        if ((uVar8 & 1) == 0) {
          if ((bVar4) && (pbVar7[1] == 0x22)) {
            pbVar7 = pbVar7 + 1;
          }
          else {
            bVar3 = false;
          }
          bVar4 = !bVar5;
          bVar5 = bVar4;
        }
        uVar8 = uVar8 >> 1;
      }
      for (; uVar8 != 0; uVar8 = uVar8 - 1) {
        if ((byte *)args != (byte *)0x0) {
          *args = 0x5c;
          args = args + 1;
        }
        *piVar6 = *piVar6 + 1;
      }
      bVar2 = *pbVar7;
      if ((bVar2 == 0) || ((!bVar4 && ((bVar2 == 0x20 || (bVar2 == 9)))))) break;
      if (bVar3) {
        if ((byte *)args == (byte *)0x0) {
          if ((*(byte *)((int)&DAT_00505488 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_00486455;
        }
        if ((*(byte *)((int)&DAT_00505488 + bVar2 + 1) & 4) != 0) {
          *args = bVar2;
          args = args + 1;
          pbVar7 = pbVar7 + 1;
          *piVar6 = *piVar6 + 1;
        }
        *args = *pbVar7;
        args = args + 1;
        *piVar6 = *piVar6 + 1;
        pbVar7 = pbVar7 + 1;
      }
      else {
LAB_00486455:
        pbVar7 = pbVar7 + 1;
      }
    }
    if ((byte *)args != (byte *)0x0) {
      *args = 0;
      args = args + 1;
    }
    *piVar6 = *piVar6 + 1;
  }
  if (argv != (char **)0x0) {
    *argv = (char *)0x0;
  }
  *numargs = *numargs + 1;
  return;
}


/* ==== __crtGetEnvironmentStringsA @ 00486490 ==== */

void __crtGetEnvironmentStringsA(void)

{
  char cVar1;
  WCHAR WVar2;
  WCHAR *pWVar3;
  int iVar5;
  uint uVar6;
  LPSTR lpMultiByteStr;
  LPCH pCVar7;
  CHAR *extraout_EAX;
  LPCH pCVar8;
  LPWCH lpWideCharStr;
  LPCH pCVar9;
  CHAR *pCVar10;
  WCHAR *pWVar4;
  
  lpWideCharStr = (LPWCH)0x0;
  pCVar8 = (LPCH)0x0;
  if (DAT_00505480 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr == (LPWCH)0x0) {
      pCVar8 = GetEnvironmentStrings();
      if (pCVar8 == (LPCH)0x0) {
        return;
      }
      DAT_00505480 = 2;
    }
    else {
      DAT_00505480 = 1;
    }
  }
  if (DAT_00505480 == 1) {
    if ((lpWideCharStr != (LPWCH)0x0) ||
       (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr != (LPWCH)0x0)) {
      WVar2 = *lpWideCharStr;
      pWVar3 = lpWideCharStr;
      while (WVar2 != L'\0') {
        do {
          pWVar4 = pWVar3;
          pWVar3 = pWVar4 + 1;
        } while (*pWVar3 != L'\0');
        pWVar3 = pWVar4 + 2;
        WVar2 = *pWVar3;
      }
      iVar5 = ((int)pWVar3 - (int)lpWideCharStr >> 1) + 1;
      uVar6 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      if ((uVar6 != 0) && (malloc(uVar6), lpMultiByteStr != (LPSTR)0x0)) {
        iVar5 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,lpMultiByteStr,uVar6,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        if (iVar5 == 0) {
          free(lpMultiByteStr);
        }
        FreeEnvironmentStringsW(lpWideCharStr);
        return;
      }
      FreeEnvironmentStringsW(lpWideCharStr);
      return;
    }
  }
  else if ((DAT_00505480 == 2) &&
          ((pCVar8 != (LPCH)0x0 || (pCVar8 = GetEnvironmentStrings(), pCVar8 != (LPCH)0x0)))) {
    cVar1 = *pCVar8;
    pCVar7 = pCVar8;
    while (cVar1 != '\0') {
      do {
        pCVar9 = pCVar7;
        pCVar7 = pCVar9 + 1;
      } while (pCVar9[1] != '\0');
      pCVar7 = pCVar9 + 2;
      cVar1 = pCVar9[2];
    }
    pCVar7 = pCVar7 + (1 - (int)pCVar8);
    malloc((uint)pCVar7);
    if (extraout_EAX != (CHAR *)0x0) {
      pCVar9 = pCVar8;
      pCVar10 = extraout_EAX;
      for (uVar6 = (uint)pCVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pCVar10 = *(undefined4 *)pCVar9;
        pCVar9 = pCVar9 + 4;
        pCVar10 = pCVar10 + 4;
      }
      for (uVar6 = (uint)pCVar7 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pCVar10 = *pCVar9;
        pCVar9 = pCVar9 + 1;
        pCVar10 = pCVar10 + 1;
      }
      FreeEnvironmentStringsA(pCVar8);
      return;
    }
    FreeEnvironmentStringsA(pCVar8);
    return;
  }
  return;
}


/* ==== _setmbcp @ 004865f0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl _setmbcp(int codepage)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  UINT CodePage;
  UINT *pUVar5;
  BOOL BVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  BYTE *pBVar11;
  byte *pbVar12;
  byte *pbVar13;
  undefined4 *puVar14;
  _cpinfo local_14;
  
  CodePage = FUN_004867e0(codepage);
  if (CodePage == DAT_0050558c) {
    return 0;
  }
  if (CodePage == 0) {
    FUN_00486890();
    return 0;
  }
  iVar10 = 0;
  pUVar5 = &DAT_004d82c0;
  do {
    if (*pUVar5 == CodePage) {
      puVar14 = &DAT_00505488;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined1 *)puVar14 = 0;
      uVar7 = 0;
      iVar10 = iVar10 * 0x30;
      pbVar12 = (byte *)(iVar10 + 0x4d82d0);
      do {
        bVar3 = *pbVar12;
        for (pbVar13 = pbVar12; (bVar3 != 0 && (bVar3 = pbVar13[1], bVar3 != 0));
            pbVar13 = pbVar13 + 2) {
          uVar8 = (uint)*pbVar13;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_004d82b8)[uVar7];
            do {
              pbVar2 = (byte *)((int)&DAT_00505488 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          bVar3 = pbVar13[2];
        }
        uVar7 = uVar7 + 1;
        pbVar12 = pbVar12 + 8;
      } while (uVar7 < 4);
      DAT_0050558c = CodePage;
      DAT_00505590 = FUN_00486830(CodePage);
      _DAT_00505598 = *(undefined4 *)(iVar10 + 0x4d82c4);
      _DAT_0050559c = *(undefined4 *)(iVar10 + 0x4d82c8);
      _DAT_005055a0 = *(undefined4 *)(iVar10 + 0x4d82cc);
      return 0;
    }
    pUVar5 = pUVar5 + 0xc;
    iVar10 = iVar10 + 1;
  } while (pUVar5 < &__badioinfo);
  BVar6 = GetCPInfo(CodePage,&local_14);
  if (BVar6 != 1) {
    if (DAT_005055a4 == 0) {
      return -1;
    }
    FUN_00486890();
    return 0;
  }
  puVar14 = &DAT_00505488;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined1 *)puVar14 = 0;
  if (local_14.MaxCharSize < 2) {
    DAT_0050558c = 0;
    DAT_00505590 = 0;
  }
  else {
    if (local_14.LeadByte[0] != '\0') {
      pBVar11 = local_14.LeadByte + 1;
      do {
        bVar3 = *pBVar11;
        if (bVar3 == 0) break;
        for (uVar7 = (uint)pBVar11[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
          *(byte *)((int)&DAT_00505488 + uVar7 + 1) = *(byte *)((int)&DAT_00505488 + uVar7 + 1) | 4;
        }
        pBVar1 = pBVar11 + 1;
        pBVar11 = pBVar11 + 2;
      } while (*pBVar1 != 0);
    }
    uVar7 = 1;
    do {
      *(byte *)((int)&DAT_00505488 + uVar7 + 1) = *(byte *)((int)&DAT_00505488 + uVar7 + 1) | 8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0xff);
    DAT_0050558c = CodePage;
    DAT_00505590 = FUN_00486830(CodePage);
  }
  _DAT_00505598 = 0;
  _DAT_0050559c = 0;
  _DAT_005055a0 = 0;
  return 0;
}


/* ==== FUN_004867e0 @ 004867e0 ==== */

int __cdecl FUN_004867e0(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_005055a4 = 1;
                    /* WARNING: Could not recover jumptable at 0x004867fd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_005055a4 = 1;
                    /* WARNING: Could not recover jumptable at 0x00486812. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_005055e0;
  }
  DAT_005055a4 = (uint)bVar2;
  return param_1;
}


/* ==== FUN_00486830 @ 00486830 ==== */

undefined4 __cdecl FUN_00486830(undefined4 param_1)

{
  switch(param_1) {
  case 0x3a4:
    return 0x411;
  default:
    return 0;
  case 0x3a8:
    return 0x804;
  case 0x3b5:
    return 0x412;
  case 0x3b6:
    return 0x404;
  }
}


/* ==== FUN_00486890 @ 00486890 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00486890(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00505488;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_0050558c = 0;
  DAT_00505590 = 0;
  _DAT_00505598 = 0;
  _DAT_0050559c = 0;
  _DAT_005055a0 = 0;
  return;
}


/* ==== __initmbctable @ 004868c0 ==== */

int __initmbctable(void)

{
  int iVar1;
  
  iVar1 = _setmbcp(-3);
  return iVar1;
}


/* ==== _ioinit @ 004868d0 ==== */

void _ioinit(void)

{
  byte bVar1;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar2;
  DWORD DVar3;
  HANDLE hFile;
  int iVar4;
  byte *pbVar5;
  int *piVar6;
  uint uVar7;
  UINT *pUVar8;
  UINT local_48;
  _STARTUPINFOA local_44;
  
  malloc(0x100);
  if (extraout_EAX == (undefined4 *)0x0) {
    _amsg_exit(0x1b);
  }
  _nhandle = 0x20;
  puVar2 = extraout_EAX;
  __pioinfo = extraout_EAX;
  if (extraout_EAX < extraout_EAX + 0x40) {
    do {
      *(undefined1 *)(puVar2 + 1) = 0;
      *puVar2 = 0xffffffff;
      *(undefined1 *)((int)puVar2 + 5) = 10;
      puVar2 = puVar2 + 2;
    } while (puVar2 < __pioinfo + 0x40);
  }
  GetStartupInfoA(&local_44);
  if ((local_44.cbReserved2 != 0) && ((UINT *)local_44.lpReserved2 != (UINT *)0x0)) {
    local_48 = *(UINT *)local_44.lpReserved2;
    pUVar8 = (UINT *)((int)local_44.lpReserved2 + 4);
    pbVar5 = (byte *)((int)pUVar8 + local_48);
    if (0x7ff < (int)local_48) {
      local_48 = 0x800;
    }
    if ((int)_nhandle < (int)local_48) {
      piVar6 = &DAT_00505b84;
      do {
        malloc(0x100);
        if (extraout_EAX_00 == (undefined4 *)0x0) {
          local_48 = _nhandle;
          break;
        }
        *piVar6 = (int)extraout_EAX_00;
        _nhandle = _nhandle + 0x20;
        puVar2 = extraout_EAX_00;
        if (extraout_EAX_00 < extraout_EAX_00 + 0x40) {
          do {
            *(undefined1 *)(puVar2 + 1) = 0;
            *puVar2 = 0xffffffff;
            *(undefined1 *)((int)puVar2 + 5) = 10;
            puVar2 = puVar2 + 2;
          } while (puVar2 < (undefined4 *)(*piVar6 + 0x100));
        }
        piVar6 = piVar6 + 1;
      } while ((int)_nhandle < (int)local_48);
    }
    uVar7 = 0;
    if (0 < (int)local_48) {
      do {
        if (((*(HANDLE *)pbVar5 != (HANDLE)0xffffffff) && ((*pUVar8 & 1) != 0)) &&
           (((*pUVar8 & 8) != 0 || (DVar3 = GetFileType(*(HANDLE *)pbVar5), DVar3 != 0)))) {
          iVar4 = (int)(&__pioinfo)[(int)uVar7 >> 5];
          *(undefined4 *)(iVar4 + (uVar7 & 0x1f) * 8) = *(undefined4 *)pbVar5;
          *(byte *)(iVar4 + (uVar7 & 0x1f) * 8 + 4) = (byte)*pUVar8;
        }
        uVar7 = uVar7 + 1;
        pUVar8 = (UINT *)((int)pUVar8 + 1);
        pbVar5 = pbVar5 + 4;
      } while ((int)uVar7 < (int)local_48);
    }
  }
  iVar4 = 0;
  do {
    puVar2 = __pioinfo + iVar4 * 2;
    if (__pioinfo[iVar4 * 2] == -1) {
      *(undefined1 *)(puVar2 + 1) = 0x81;
      if (iVar4 == 0) {
        DVar3 = 0xfffffff6;
      }
      else {
        DVar3 = 0xfffffff5 - (iVar4 != 1);
      }
      hFile = GetStdHandle(DVar3);
      if ((hFile == (HANDLE)0xffffffff) || (DVar3 = GetFileType(hFile), DVar3 == 0)) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_00486aab;
      }
      *puVar2 = hFile;
      if ((DVar3 & 0xff) == 2) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_00486aab;
      }
      if ((DVar3 & 0xff) == 3) {
        bVar1 = *(byte *)(puVar2 + 1) | 8;
        goto LAB_00486aab;
      }
    }
    else {
      bVar1 = *(byte *)(puVar2 + 1) | 0x80;
LAB_00486aab:
      *(byte *)(puVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(_nhandle);
      return;
    }
  } while( true );
}


/* ==== _heap_init @ 00486ad0 ==== */

int _heap_init(void)

{
  int extraout_EAX;
  
  _crtheap = HeapCreate(1,0x1000,0);
  if (_crtheap == (HANDLE)0x0) {
    return 0;
  }
  __sbh_new_region();
  if (extraout_EAX == 0) {
    HeapDestroy(_crtheap);
    return 0;
  }
  return 1;
}


/* ==== __global_unwind2 @ 00486b10 ==== */

/* Library Function - Single Match
    __global_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x486b28,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


/* ==== __local_unwind2 @ 00486b52 ==== */

/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_00486b30;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_00486be6();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}


/* ==== FUN_00486be6 @ 00486be6 ==== */

void FUN_00486be6(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_004d83c4 = *(undefined4 *)(unaff_EBP + 8);
  DAT_004d83c0 = in_EAX;
  DAT_004d83c8 = unaff_EBP;
  return;
}


/* ==== FUN_00486cc5 @ 00486cc5 ==== */

void FUN_00486cc5(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* ==== _FF_MSGBANNER @ 00486ce0 ==== */

void _FF_MSGBANNER(void)

{
  if ((DAT_005052c4 == 1) || ((DAT_005052c4 == 0 && (DAT_004d7c50 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_005055a8 != (code *)0x0) {
      (*DAT_005055a8)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}


/* ==== _NMSG_WRITE @ 00486d20 ==== */

void __cdecl _NMSG_WRITE(int rterrnum)

{
  char cVar1;
  undefined **ppuVar2;
  DWORD DVar3;
  HANDLE hFile;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  CHAR *pCVar10;
  char *pcVar11;
  DWORD local_1a8;
  char local_1a4 [100];
  char acStack_140 [60];
  CHAR local_104 [260];
  
  ppuVar2 = (undefined **)&DAT_004d83d0;
  iVar8 = 0;
  do {
    if ((undefined *)rterrnum == *ppuVar2) break;
    ppuVar2 = ppuVar2 + 2;
    iVar8 = iVar8 + 1;
  } while (ppuVar2 < &PTR_DAT_004d8460);
  if (rterrnum == (&DAT_004d83d0)[iVar8 * 2]) {
    if ((DAT_005052c4 == 1) || ((DAT_005052c4 == 0 && (DAT_004d7c50 == 1)))) {
      if ((__pioinfo == 0) || (hFile = *(HANDLE *)(__pioinfo + 0x10), hFile == (HANDLE)0xffffffff))
      {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar7 = *(char **)(iVar8 * 8 + 0x4d83d4);
      uVar5 = 0xffffffff;
      pcVar9 = pcVar7;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      WriteFile(hFile,pcVar7,~uVar5 - 1,&local_1a8,(LPOVERLAPPED)0x0);
    }
    else if (rterrnum != 0xfc) {
      DVar3 = GetModuleFileNameA((HMODULE)0x0,local_104,0x104);
      if (DVar3 == 0) {
        pcVar7 = "<program name unknown>";
        pCVar10 = local_104;
        for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
          *(undefined4 *)pCVar10 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pCVar10 = pCVar10 + 4;
        }
        *(undefined2 *)pCVar10 = *(undefined2 *)pcVar7;
        pCVar10[2] = pcVar7[2];
      }
      uVar5 = 0xffffffff;
      pcVar7 = local_104;
      pcVar9 = local_104;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      if (0x3c < ~uVar5) {
        uVar5 = 0xffffffff;
        pcVar7 = local_104;
        do {
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        pcVar7 = acStack_140 + ~uVar5;
        strncpy(pcVar7,&DAT_004d55dc,3);
      }
      pcVar9 = "Runtime Error!\n\nProgram: ";
      pcVar11 = local_1a4;
      for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      *(undefined2 *)pcVar11 = *(undefined2 *)pcVar9;
      uVar5 = 0xffffffff;
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar4 = -1;
      pcVar7 = local_1a4;
      do {
        pcVar11 = pcVar7;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar11 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar11;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = pcVar11 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar7 = "\n\n";
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar4 = -1;
      pcVar7 = local_1a4;
      do {
        pcVar11 = pcVar7;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar11 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar11;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = pcVar11 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar7 = *(char **)(iVar8 * 8 + 0x4d83d4);
      do {
        pcVar9 = pcVar7;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar8 = -1;
      pcVar7 = local_1a4;
      do {
        pcVar11 = pcVar7;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar11 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar11;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar5;
      pcVar9 = pcVar11 + -1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      __crtMessageBoxA(local_1a4,"Microsoft Visual C++ Runtime Library",0x12010);
      return;
    }
  }
  return;
}


/* ==== _flsbuf @ 00486f00 ==== */

int __cdecl _flsbuf(int c,void *stream)

{
  uint fh;
  void *buf;
  void *stream_00;
  int iVar1;
  undefined *puVar2;
  uint uVar3;
  uint uVar4;
  
  stream_00 = stream;
  uVar4 = *(uint *)((int)stream + 0xc);
  fh = *(uint *)((int)stream + 0x10);
  if (((uVar4 & 0x82) == 0) || ((uVar4 & 0x40) != 0)) {
LAB_00487020:
    *(uint *)((int)stream + 0xc) = uVar4 | 0x20;
    return -1;
  }
  uVar3 = 0;
  if ((uVar4 & 1) != 0) {
    *(undefined4 *)((int)stream + 4) = 0;
    if ((uVar4 & 0x10) == 0) goto LAB_00487020;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(uint *)((int)stream + 0xc) = uVar4 & 0xfffffffe;
  }
  uVar4 = *(uint *)((int)stream + 0xc);
  *(undefined4 *)((int)stream + 4) = 0;
  *(uint *)((int)stream + 0xc) = uVar4 & 0xffffffef | 2;
  if ((uVar4 & 0x10c) == 0) {
    if ((stream == &DAT_004d7fc0) || (stream == &DAT_004d7fe0)) {
      iVar1 = _isatty(fh);
      if (iVar1 != 0) goto LAB_00486f73;
    }
    _getbuf(stream_00);
  }
LAB_00486f73:
  if ((*(uint *)((int)stream_00 + 0xc) & 0x108) == 0) {
    uVar4 = 1;
    uVar3 = _write(fh,&c,1);
  }
  else {
    buf = *(void **)((int)stream_00 + 8);
    uVar4 = *(int *)stream_00 - (int)buf;
    *(int *)stream_00 = (int)buf + 1;
    *(int *)((int)stream_00 + 4) = *(int *)((int)stream_00 + 0x18) + -1;
    if ((int)uVar4 < 1) {
      if (fh == 0xffffffff) {
        puVar2 = &__badioinfo;
      }
      else {
        puVar2 = (undefined *)((&__pioinfo)[(int)fh >> 5] + (fh & 0x1f) * 8);
      }
      if ((puVar2[4] & 0x20) != 0) {
        _lseek(fh,0,2);
      }
      **(undefined1 **)((int)stream_00 + 8) = (undefined1)c;
    }
    else {
      uVar3 = _write(fh,buf,uVar4);
      **(undefined1 **)((int)stream_00 + 8) = (undefined1)c;
    }
  }
  if (uVar3 != uVar4) {
    *(uint *)((int)stream_00 + 0xc) = *(uint *)((int)stream_00 + 0xc) | 0x20;
    return -1;
  }
  return c & 0xff;
}


/* ==== _output @ 00487030 ==== */

int __cdecl _output(void *stream,char *fmt,void *argptr)

{
  ushort uVar1;
  uint uVar2;
  short *psVar3;
  int *piVar4;
  ushort *puVar5;
  int iVar6;
  char cVar7;
  uint unaff_EBX;
  undefined1 *puVar8;
  undefined1 *len;
  char *pcVar9;
  int iVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  longlong lVar13;
  uint uVar14;
  uint local_24c;
  ushort *local_248;
  int local_244;
  int local_240;
  char local_23a;
  char local_239;
  int local_238;
  int local_234;
  int local_230;
  uint local_22c;
  int local_228;
  int local_224;
  int local_220;
  uint local_21c;
  undefined4 local_218;
  char local_214 [4];
  undefined4 local_210;
  undefined4 local_20c;
  uint local_204;
  undefined1 local_200 [511];
  undefined1 uStack_1;
  
  local_220 = 0;
  len = (undefined1 *)0x0;
  local_240 = 0;
  cVar7 = *fmt;
  local_21c = CONCAT31(local_21c._1_3_,cVar7);
  pcVar9 = fmt;
  do {
    if ((cVar7 == '\0') || (fmt = pcVar9 + 1, local_240 < 0)) {
      return local_240;
    }
    if ((cVar7 < ' ') || ('x' < cVar7)) {
      uVar2 = 0;
    }
    else {
      uVar2 = (byte)"Runtime Error!\n\nProgram: "[cVar7 + 0x14] & 0xf;
    }
    local_220 = (int)(char)(&DAT_004942c8)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_004870ad_caseD_0:
      local_230 = 0;
      if ((_pctype[(local_21c & 0xff) * 2 + 1] & 0x80) != 0) {
        write_char((int)cVar7,stream,&local_240);
        cVar7 = *fmt;
        fmt = pcVar9 + 2;
      }
      write_char((int)cVar7,stream,&local_240);
      break;
    case 1:
      local_218 = 0;
      local_228 = 0;
      local_234 = 0;
      local_238 = 0;
      local_24c = 0;
      local_244 = -1;
      local_230 = 0;
      break;
    case 2:
      switch(cVar7) {
      case ' ':
        local_24c = local_24c | 2;
        break;
      case '#':
        local_24c = local_24c | 0x80;
        break;
      case '+':
        local_24c = local_24c | 1;
        break;
      case '-':
        local_24c = local_24c | 4;
        break;
      case '0':
        local_24c = local_24c | 8;
      }
      break;
    case 3:
      if (cVar7 == '*') {
        local_234 = get_int_arg(&argptr);
        if (local_234 < 0) {
          local_24c = local_24c | 4;
          local_234 = -local_234;
        }
      }
      else {
        local_234 = cVar7 + -0x30 + local_234 * 10;
      }
      break;
    case 4:
      local_244 = 0;
      break;
    case 5:
      if (cVar7 == '*') {
        local_244 = get_int_arg(&argptr);
        if (local_244 < 0) {
          local_244 = -1;
        }
      }
      else {
        local_244 = cVar7 + -0x30 + local_244 * 10;
      }
      break;
    case 6:
      switch(cVar7) {
      case 'I':
        if ((*fmt != '6') || (pcVar9[2] != '4')) {
          local_220 = 0;
          goto switchD_004870ad_caseD_0;
        }
        fmt = pcVar9 + 3;
        local_24c = local_24c | 0x8000;
        break;
      case 'h':
        local_24c = local_24c | 0x20;
        break;
      case 'l':
        local_24c = local_24c | 0x10;
        break;
      case 'w':
        local_24c = local_24c | 0x800;
      }
      break;
    case 7:
      switch(cVar7) {
      case 'C':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 'c':
        if ((local_24c & 0x810) == 0) {
          iVar10 = get_int_arg(&argptr);
          local_200[0] = (char)iVar10;
          len = (undefined1 *)0x1;
        }
        else {
          uVar1 = get_short_arg(&argptr);
          len = (undefined1 *)wctomb(local_200,uVar1);
          if ((int)len < 0) {
            local_248 = (ushort *)local_200;
            local_228 = 1;
            break;
          }
        }
        local_248 = (ushort *)local_200;
        break;
      case 'E':
      case 'G':
        local_218 = 1;
        cVar7 = cVar7 + ' ';
      case 'e':
      case 'f':
      case 'g':
        local_248 = (ushort *)local_200;
        if (local_244 < 0) {
          local_244 = 6;
        }
        else if ((local_244 == 0) && (cVar7 == 'g')) {
          local_244 = 1;
        }
        local_210 = *(undefined4 *)argptr;
        local_20c = *(undefined4 *)((int)argptr + 4);
        argptr = (undefined4 *)((int)argptr + 8);
        (*(code *)_cfltcvt_tab)(&local_210,local_200,(int)cVar7,local_244,local_218);
        if (((unaff_EBX & 0x80) != 0) && (local_244 == 0)) {
          (*(code *)PTR__fptrap_004d8474)(&local_204);
        }
        if ((cVar7 == 'g') && ((unaff_EBX & 0x80) == 0)) {
          (*(code *)PTR__fptrap_004d846c)(local_200);
        }
        uVar2 = local_24c | 0x40;
        if (local_200[0] == '-') {
          local_248 = (ushort *)(local_200 + 1);
          uVar2 = local_24c | 0x140;
        }
        local_24c = uVar2;
        uVar2 = 0xffffffff;
        puVar5 = local_248;
        do {
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          uVar1 = *puVar5;
          puVar5 = (ushort *)((int)puVar5 + 1);
        } while ((char)uVar1 != '\0');
        len = (undefined1 *)(~uVar2 - 1);
        break;
      case 'S':
        if ((local_24c & 0x830) == 0) {
          local_24c = local_24c | 0x800;
        }
      case 's':
        iVar10 = 0x7fffffff;
        if (local_244 != -1) {
          iVar10 = local_244;
        }
        local_248 = (ushort *)get_int_arg(&argptr);
        if ((local_24c & 0x810) == 0) {
          puVar5 = local_248;
          if (local_248 == (ushort *)0x0) {
            puVar5 = (ushort *)PTR_DAT_004d8460;
            local_248 = (ushort *)PTR_DAT_004d8460;
          }
          for (; (iVar10 != 0 && (iVar10 = iVar10 + -1, (char)*puVar5 != '\0'));
              puVar5 = (ushort *)((int)puVar5 + 1)) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_004d8464;
          }
          local_230 = 1;
          for (puVar5 = local_248; (iVar10 != 0 && (iVar10 = iVar10 + -1, *puVar5 != 0));
              puVar5 = puVar5 + 1) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_004872c1_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg(&argptr);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_004d8460;
          pcVar9 = PTR_DAT_004d8460;
          do {
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            cVar7 = *pcVar9;
            pcVar9 = pcVar9 + 1;
          } while (cVar7 != '\0');
          len = (undefined1 *)(~uVar2 - 1);
        }
        else if ((local_24c & 0x800) == 0) {
          len = (undefined1 *)(int)*psVar3;
          local_230 = 0;
        }
        else {
          local_230 = 1;
          len = (undefined1 *)((uint)(int)*psVar3 >> 1);
        }
        break;
      case 'd':
      case 'i':
        local_22c = 10;
        local_24c = local_24c | 0x40;
        goto LAB_004875f7;
      case 'n':
        piVar4 = (int *)get_int_arg(&argptr);
        if ((local_24c & 0x20) == 0) {
          local_228 = 1;
          *piVar4 = local_240;
        }
        else {
          local_228 = 1;
          *(undefined2 *)piVar4 = (undefined2)local_240;
        }
        break;
      case 'o':
        local_22c = 8;
        if ((local_24c & 0x80) != 0) {
          local_24c = local_24c | 0x200;
        }
        goto LAB_004875f7;
      case 'p':
        local_244 = 8;
switchD_004872c1_caseD_58:
        local_224 = 7;
LAB_004875b2:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_004875f7;
      case 'u':
        local_22c = 10;
LAB_004875f7:
        if ((local_24c & 0x8000) == 0) {
          if ((local_24c & 0x20) == 0) {
            if ((local_24c & 0x40) == 0) {
              uVar2 = get_int_arg(&argptr);
              uVar11 = (ulonglong)uVar2;
            }
            else {
              iVar10 = get_int_arg(&argptr);
              uVar11 = (ulonglong)iVar10;
            }
          }
          else if ((local_24c & 0x40) == 0) {
            uVar2 = get_int_arg(&argptr);
            uVar11 = (ulonglong)uVar2 & 0xffffffff0000ffff;
          }
          else {
            iVar10 = get_int_arg(&argptr);
            uVar11 = (ulonglong)(int)(short)iVar10;
          }
        }
        else {
          uVar11 = get_int64_arg(&argptr);
        }
        iVar10 = (int)(uVar11 >> 0x20);
        if ((((local_24c & 0x40) != 0) && (iVar10 == 0 || (longlong)uVar11 < 0)) &&
           ((longlong)uVar11 < 0)) {
          local_24c = local_24c | 0x100;
          uVar11 = CONCAT44(-(iVar10 + (uint)((int)uVar11 != 0)),-(int)uVar11);
        }
        iVar10 = (int)(uVar11 >> 0x20);
        if ((local_24c & 0x8000) == 0) {
          iVar10 = 0;
        }
        lVar13 = CONCAT44(iVar10,(int)uVar11);
        if (local_244 < 0) {
          local_244 = 1;
        }
        else {
          local_24c = local_24c & 0xfffffff7;
        }
        local_248 = (ushort *)register0x00000010;
        if ((int)uVar11 == 0 && iVar10 == 0) {
          local_238 = 0;
        }
        while( true ) {
          uVar2 = local_22c;
          puVar5 = (ushort *)((int)local_248 + -1);
          iVar10 = local_244 + -1;
          if ((local_244 < 1) && (lVar13 == 0)) break;
          local_204 = (int)local_22c >> 0x1f;
          uVar14 = (uint)((ulonglong)lVar13 >> 0x20);
          uVar12 = __aullrem((uint)lVar13,uVar14,local_22c,local_204);
          iVar6 = (int)uVar12 + 0x30;
          lVar13 = __aulldiv((uint)lVar13,uVar14,uVar2,local_204);
          if (0x39 < iVar6) {
            iVar6 = iVar6 + local_224;
          }
          *(char *)puVar5 = (char)iVar6;
          local_244 = iVar10;
          local_248 = puVar5;
        }
        len = &uStack_1 + -(int)puVar5;
        local_244 = iVar10;
        if (((local_24c & 0x200) != 0) && (((char)*local_248 != '0' || (len == (undefined1 *)0x0))))
        {
          len = &stack0x00000000 + -(int)puVar5;
          *(char *)puVar5 = '0';
          local_248 = puVar5;
        }
        break;
      case 'x':
        local_224 = 0x27;
        goto LAB_004875b2;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_0048778f;
              local_23a = ' ';
            }
            else {
              local_23a = '+';
            }
          }
          else {
            local_23a = '-';
          }
          local_238 = 1;
        }
LAB_0048778f:
        iVar10 = (local_234 - local_238) - (int)len;
        if ((local_24c & 0xc) == 0) {
          write_multi_char(0x20,iVar10,stream,&local_240);
        }
        write_string(&local_23a,local_238,stream,&local_240);
        if (((local_24c & 8) != 0) && ((local_24c & 4) == 0)) {
          write_multi_char(0x30,iVar10,stream,&local_240);
        }
        if ((local_230 == 0) || (puVar5 = local_248, puVar8 = len, (int)len < 1)) {
          write_string((char *)local_248,(int)len,stream,&local_240);
        }
        else {
          do {
            puVar8 = puVar8 + -1;
            iVar6 = wctomb(local_214,*puVar5);
            if (iVar6 < 1) break;
            write_string(local_214,iVar6,stream,&local_240);
            puVar5 = puVar5 + 1;
          } while (puVar8 != (undefined1 *)0x0);
        }
        if ((local_24c & 4) != 0) {
          write_multi_char(0x20,iVar10,stream,&local_240);
        }
      }
    }
    cVar7 = *fmt;
    local_21c = CONCAT31(local_21c._1_3_,cVar7);
    pcVar9 = fmt;
  } while( true );
}


/* ==== write_char @ 004879c0 ==== */

void __cdecl write_char(int ch,void *stream,int *pnumwritten)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)((int)stream + 4) + -1;
  *(int *)((int)stream + 4) = iVar1;
  if (iVar1 < 0) {
    uVar2 = _flsbuf(ch,stream);
  }
  else {
    **(undefined1 **)stream = (char)ch;
    uVar2 = ch & 0xff;
    *(int *)stream = *(int *)stream + 1;
  }
  if (uVar2 == 0xffffffff) {
    *pnumwritten = -1;
    return;
  }
  *pnumwritten = *pnumwritten + 1;
  return;
}


/* ==== write_multi_char @ 00487a10 ==== */

void __cdecl write_multi_char(int ch,int num,void *stream,int *pnumwritten)

{
  do {
    if (num < 1) {
      return;
    }
    num = num + -1;
    write_char(ch,stream,pnumwritten);
  } while (*pnumwritten != -1);
  return;
}


/* ==== write_string @ 00487a50 ==== */

void __cdecl write_string(char *string,int len,void *stream,int *pnumwritten)

{
  char cVar1;
  
  do {
    if (len < 1) {
      return;
    }
    len = len + -1;
    cVar1 = *string;
    string = string + 1;
    write_char((int)cVar1,stream,pnumwritten);
  } while (*pnumwritten != -1);
  return;
}


/* ==== get_int_arg @ 00487a90 ==== */

int __cdecl get_int_arg(void *pargptr)

{
  int *piVar1;
  
  piVar1 = *(int **)pargptr;
  *(int **)pargptr = piVar1 + 1;
  return *piVar1;
}


/* ==== get_int64_arg @ 00487ab0 ==== */

longlong __cdecl get_int64_arg(void *pargptr)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)pargptr;
  *(longlong **)pargptr = plVar1 + 1;
  return *plVar1;
}


/* ==== get_short_arg @ 00487ad0 ==== */

short __cdecl get_short_arg(void *pargptr)

{
  short *psVar1;
  
  psVar1 = *(short **)pargptr;
  *(short **)pargptr = psVar1 + 2;
  return *psVar1;
}


/* ==== __setdefaultprecision @ 00487af0 ==== */

/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 1998 Release */

void __setdefaultprecision(void)

{
  FUN_0048cb10((void *)0x10000,0x30000);
  return;
}


/* ==== _ms_p5_test_fdiv @ 00487b10 ==== */

/* WARNING: Removing unreachable block (ram,0x00487b51) */

int _ms_p5_test_fdiv(void)

{
  return 0;
}


/* ==== _ms_p5_mp_test_fdiv @ 00487b60 ==== */

int _ms_p5_mp_test_fdiv(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  
  hModule = GetModuleHandleA("KERNEL32");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent");
    if (pFVar1 != (FARPROC)0x0) {
      iVar2 = (*pFVar1)(0);
      return iVar2;
    }
  }
  iVar2 = _ms_p5_test_fdiv();
  return iVar2;
}


/* ==== _forcdecpt @ 00487b90 ==== */

void __cdecl _forcdecpt(char *buffer)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = tolower((int)*buffer);
  if (iVar3 != 0x65) {
    do {
      buffer = buffer + 1;
      if (__mb_cur_max < 2) {
        uVar4 = (byte)_pctype[*buffer * 2] & 4;
      }
      else {
        uVar4 = _isctype((int)*buffer,4);
      }
    } while (uVar4 != 0);
  }
  cVar2 = *buffer;
  *buffer = __decimal_point;
  do {
    buffer = buffer + 1;
    cVar1 = *buffer;
    *buffer = cVar2;
    cVar2 = cVar1;
  } while (*buffer != '\0');
  return;
}


/* ==== _cropzeros @ 00487bf0 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _cropzeros(char *buf)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  cVar1 = *buf;
  while ((cVar1 != '\0' && (cVar1 != __decimal_point))) {
    pcVar2 = buf + 1;
    buf = buf + 1;
    cVar1 = *pcVar2;
  }
  pcVar2 = buf + 1;
  if (*buf != '\0') {
    cVar1 = *pcVar2;
    while (((cVar1 != '\0' && (cVar1 != 'e')) && (cVar1 != 'E'))) {
      pcVar3 = pcVar2 + 1;
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar3;
    }
    cVar1 = pcVar2[-1];
    pcVar3 = pcVar2;
    while (pcVar4 = pcVar3 + -1, cVar1 == '0') {
      cVar1 = pcVar3[-2];
      pcVar3 = pcVar4;
    }
    if (*pcVar4 == __decimal_point) {
      pcVar4 = pcVar3 + -2;
    }
    cVar1 = *pcVar2;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
    while (cVar1 != '\0') {
      pcVar2 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar4 = pcVar4 + 1;
      *pcVar4 = cVar1;
    }
  }
  return;
}


/* ==== _positive @ 00487c60 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _positive(double *arg)

{
  if (0.0 <= *arg) {
    return 1;
  }
  return 0;
}


/* ==== _fassign @ 00487c80 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _fassign(int flag,char *argument,char *number)

{
  uint uStack_8;
  undefined4 uStack_4;
  
  if (flag != 0) {
    FUN_0048d100(&uStack_8,(byte *)number);
    *(uint *)argument = uStack_8;
    *(undefined4 *)(argument + 4) = uStack_4;
    return;
  }
  FUN_0048d140((uint *)&number,(byte *)number);
  *(char **)argument = number;
  return;
}


/* ==== _cftoe @ 00487ce0 ==== */

char __cdecl _cftoe(double *pvalue,char *buf,int ndec,int caps)

{
  int *pflt;
  char *pcVar1;
  int iVar2;
  char *unaff_ESI;
  char *pcVar3;
  void *unaff_EDI;
  int *piVar4;
  
  piVar4 = DAT_005055ac;
  if (DAT_005055b0 == '\0') {
    _fltout2(*pvalue,unaff_EDI,unaff_ESI);
    _fptostr(buf + (uint)(*pflt == 0x2d) + (uint)(0 < ndec),ndec + 1,pflt);
    piVar4 = pflt;
  }
  else {
    _shift(buf + (*DAT_005055ac == 0x2d),(uint)(0 < ndec));
  }
  pcVar1 = buf;
  if (*piVar4 == 0x2d) {
    *buf = '-';
    pcVar1 = buf + 1;
  }
  if (0 < ndec) {
    *pcVar1 = pcVar1[1];
    pcVar1 = pcVar1 + 1;
    *pcVar1 = __decimal_point;
  }
  pcVar3 = pcVar1 + ndec + (uint)(DAT_005055b0 == '\0');
  builtin_strncpy(pcVar1 + ndec + (uint)(DAT_005055b0 == '\0'),"e+000",6);
  if (caps != 0) {
    *pcVar3 = 'E';
  }
  if (*(char *)piVar4[3] != '0') {
    iVar2 = piVar4[1] + -1;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
      pcVar3[1] = '-';
    }
    if (99 < iVar2) {
      pcVar3[2] = pcVar3[2] +
                  (((char)(iVar2 / 100) + (char)(iVar2 >> 0x1f)) -
                  (char)((longlong)iVar2 * 0x51eb851f >> 0x3f));
      iVar2 = iVar2 % 100;
    }
    if (9 < iVar2) {
      pcVar3[3] = pcVar3[3] +
                  (((char)(iVar2 / 10) + (char)(iVar2 >> 0x1f)) -
                  (char)((longlong)iVar2 * 0x66666667 >> 0x3f));
      iVar2 = iVar2 % 10;
    }
    pcVar3[4] = pcVar3[4] + (char)iVar2;
  }
  return (char)buf;
}


/* ==== _cftof @ 00487e20 ==== */

char __cdecl _cftof(double *pvalue,char *buf,int ndec)

{
  int iVar1;
  int *pflt;
  uint uVar2;
  char *unaff_ESI;
  int *piVar3;
  void *unaff_EDI;
  char *pcVar4;
  
  piVar3 = DAT_005055ac;
  if (DAT_005055b0 == '\0') {
    _fltout2(*pvalue,unaff_EDI,unaff_ESI);
    _fptostr(buf + (*pflt == 0x2d),pflt[1] + ndec,pflt);
    piVar3 = pflt;
  }
  else if (DAT_005055b4 == ndec) {
    iVar1 = DAT_005055b4 + (uint)(*DAT_005055ac == 0x2d);
    buf[iVar1] = '0';
    (buf + iVar1)[1] = '\0';
  }
  pcVar4 = buf;
  if (*piVar3 == 0x2d) {
    *buf = '-';
    pcVar4 = buf + 1;
  }
  if (piVar3[1] < 1) {
    _shift(pcVar4,1);
    *pcVar4 = '0';
    pcVar4 = pcVar4 + 1;
  }
  else {
    pcVar4 = pcVar4 + piVar3[1];
  }
  if (0 < ndec) {
    _shift(pcVar4,1);
    *pcVar4 = __decimal_point;
    iVar1 = piVar3[1];
    if (iVar1 < 0) {
      if ((DAT_005055b0 != '\0') || (-iVar1 <= ndec)) {
        ndec = -iVar1;
      }
      _shift(pcVar4 + 1,ndec);
      uVar2 = (uint)ndec >> 2;
      pcVar4 = pcVar4 + 1;
      while (uVar2 != 0) {
        uVar2 = uVar2 - 1;
        builtin_strncpy(pcVar4,"0000",4);
        pcVar4 = pcVar4 + 4;
      }
      for (uVar2 = ndec & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar4 = '0';
        pcVar4 = pcVar4 + 1;
      }
    }
  }
  return (char)buf;
}


/* ==== _cftog @ 00487f20 ==== */

char __cdecl _cftog(double *pvalue,char *buf,int ndec,int caps)

{
  char cVar1;
  int *pflt;
  char *buf_00;
  char *unaff_ESI;
  void *unaff_EDI;
  
  _fltout2(*pvalue,unaff_EDI,unaff_ESI);
  DAT_005055b4 = pflt[1] + -1;
  buf_00 = buf + (*pflt == 0x2d);
  DAT_005055ac = pflt;
  _fptostr(buf_00,ndec,pflt);
  DAT_005055b8 = DAT_005055b4 < DAT_005055ac[1] + -1;
  DAT_005055b4 = DAT_005055ac[1] + -1;
  if ((-5 < DAT_005055b4) && (DAT_005055b4 < ndec)) {
    if ((bool)DAT_005055b8) {
      cVar1 = *buf_00;
      while (cVar1 != '\0') {
        cVar1 = buf_00[1];
        buf_00 = buf_00 + 1;
      }
      buf_00[-1] = '\0';
    }
    cVar1 = FUN_00488000(pvalue,buf,ndec);
    return cVar1;
  }
  cVar1 = FUN_00487fd0(pvalue,buf,ndec,caps);
  return cVar1;
}


/* ==== FUN_00487fd0 @ 00487fd0 ==== */

void __cdecl FUN_00487fd0(double *param_1,undefined1 *param_2,int param_3,int param_4)

{
  DAT_005055b0 = 1;
  _cftoe(param_1,param_2,param_3,param_4);
  DAT_005055b0 = 0;
  return;
}


/* ==== FUN_00488000 @ 00488000 ==== */

void __cdecl FUN_00488000(double *param_1,char *param_2,uint param_3)

{
  DAT_005055b0 = 1;
  _cftof(param_1,param_2,param_3);
  DAT_005055b0 = 0;
  return;
}


/* ==== _cfltcvt @ 00488030 ==== */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _cfltcvt(double *arg,char *buffer,int format,int precision,int caps)

{
  if ((format != 0x65) && (format != 0x45)) {
    if (format == 0x66) {
      _cftof(arg,buffer,precision);
      return;
    }
    _cftog(arg,buffer,precision,caps);
    return;
  }
  _cftoe(arg,buffer,precision,caps);
  return;
}


/* ==== _shift @ 004880a0 ==== */

void __cdecl _shift(char *s,int dist)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if (dist != 0) {
    uVar2 = 0xffffffff;
    pcVar3 = s;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    memmove(s + dist,s,~uVar2);
  }
  return;
}


/* ==== __crtLCMapStringA @ 004880d0 ==== */

int __cdecl
__crtLCMapStringA(ulong lcid,ulong flags,char *src,int cchsrc,char *dst,int cchdst,int codepage,
                 int berror)

{
  int iVar1;
  int iVar2;
  LPCWSTR lpWideCharStr;
  LPCWSTR lpDestStr;
  
  if (DAT_005055c0 == 0) {
    iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_005055c0 = 1;
    }
    else {
      DAT_005055c0 = 2;
    }
  }
  iVar1 = cchsrc;
  if (0 < cchsrc) {
    iVar1 = __ansicp((int)src);
  }
  if (DAT_005055c0 == 2) {
    iVar1 = LCMapStringA(lcid,flags,src,iVar1,dst,cchdst);
    return iVar1;
  }
  if (DAT_005055c0 != 1) {
    return DAT_005055c0;
  }
  cchsrc = 0;
  if (codepage == 0) {
    codepage = DAT_005055e0;
  }
  iVar2 = MultiByteToWideChar(codepage,9,src,iVar1,(LPWSTR)0x0,0);
  if (iVar2 == 0) {
    return 0;
  }
  malloc(iVar2 * 2);
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return 0;
  }
  iVar1 = MultiByteToWideChar(codepage,1,src,iVar1,lpWideCharStr,iVar2);
  if ((iVar1 != 0) &&
     (iVar1 = LCMapStringW(lcid,flags,lpWideCharStr,iVar2,(LPWSTR)0x0,0), iVar1 != 0)) {
    if ((flags & 0x400) == 0) {
      malloc(iVar1 * 2);
      cchsrc = (int)lpDestStr;
      if ((lpDestStr == (LPCWSTR)0x0) ||
         (iVar2 = LCMapStringW(lcid,flags,lpWideCharStr,iVar2,lpDestStr,iVar1), iVar2 == 0))
      goto LAB_004882cf;
      if (cchdst == 0) {
        iVar1 = WideCharToMultiByte(codepage,0x220,lpDestStr,iVar1,(LPSTR)0x0,0,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        iVar2 = iVar1;
      }
      else {
        iVar1 = WideCharToMultiByte(codepage,0x220,lpDestStr,iVar1,dst,cchdst,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        iVar2 = iVar1;
      }
    }
    else {
      if (cchdst == 0) goto LAB_00488234;
      if (cchdst < iVar1) goto LAB_004882cf;
      iVar2 = LCMapStringW(lcid,flags,lpWideCharStr,iVar2,(LPWSTR)dst,cchdst);
    }
    if (iVar2 != 0) {
LAB_00488234:
      free(lpWideCharStr);
      free((void *)cchsrc);
      return iVar1;
    }
  }
LAB_004882cf:
  free(lpWideCharStr);
  free((void *)cchsrc);
  return 0;
}


/* ==== FUN_004882f0 @ 004882f0 ==== */

BOOL __cdecl
FUN_004882f0(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6)

{
  BOOL BVar1;
  uint size;
  LPCWSTR lpWideCharStr;
  int cchSrc;
  LPCWSTR p;
  WORD local_2;
  
  p = (LPCWSTR)0x0;
  if (DAT_005055e8 == 0) {
    BVar1 = GetStringTypeA(0,1,"",1,&local_2);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeW(1,L"",1,&local_2);
      if (BVar1 == 0) {
        return 0;
      }
      DAT_005055e8 = 1;
    }
    else {
      DAT_005055e8 = 2;
    }
  }
  if (DAT_005055e8 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_005055d0;
    }
    BVar1 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
    return BVar1;
  }
  param_6 = DAT_005055e8;
  if (DAT_005055e8 == 1) {
    param_6 = 0;
    if (param_5 == 0) {
      param_5 = DAT_005055e0;
    }
    size = MultiByteToWideChar(param_5,9,param_2,param_3,(LPWSTR)0x0,0);
    if (size != 0) {
      calloc(2,size);
      p = lpWideCharStr;
      if (lpWideCharStr != (LPCWSTR)0x0) {
        cchSrc = MultiByteToWideChar(param_5,1,param_2,param_3,lpWideCharStr,size);
        if (cchSrc != 0) {
          BVar1 = GetStringTypeW(param_1,lpWideCharStr,cchSrc,param_4);
          free(lpWideCharStr);
          return BVar1;
        }
      }
    }
    free(p);
  }
  return param_6;
}


/* ==== _close @ 00488420 ==== */

int __cdecl _close(int fh)

{
  long lVar1;
  long lVar2;
  HANDLE hObject;
  BOOL BVar3;
  DWORD oserrno;
  int iVar4;
  
  if (_nhandle <= (uint)fh) {
    errno = 9;
    _doserrno = 0;
    return -1;
  }
  iVar4 = (fh & 0x1fU) * 8;
  if ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar4) & 1) == 0) {
    errno = 9;
    _doserrno = 0;
    return -1;
  }
  lVar1 = _get_osfhandle(fh);
  if (lVar1 != -1) {
    if ((fh == 1) || (fh == 2)) {
      lVar1 = _get_osfhandle(2);
      lVar2 = _get_osfhandle(1);
      if (lVar2 == lVar1) goto LAB_004884a7;
    }
    hObject = (HANDLE)_get_osfhandle(fh);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      oserrno = GetLastError();
      goto LAB_004884a9;
    }
  }
LAB_004884a7:
  oserrno = 0;
LAB_004884a9:
  _free_osfhnd(fh);
  *(undefined1 *)((&__pioinfo)[fh >> 5] + 4 + iVar4) = 0;
  if (oserrno == 0) {
    return 0;
  }
  _dosmaperr(oserrno);
  return -1;
}


/* ==== _freebuf @ 00488500 ==== */

void __cdecl _freebuf(void *stream)

{
  if (((*(uint *)((int)stream + 0xc) & 0x83) != 0) && ((*(uint *)((int)stream + 0xc) & 8) != 0)) {
    free(*(void **)((int)stream + 8));
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xfffffbf7;
    *(undefined4 *)stream = 0;
    *(undefined4 *)((int)stream + 8) = 0;
    *(undefined4 *)((int)stream + 4) = 0;
  }
  return;
}


/* ==== _input @ 00488540 ==== */

int __cdecl _input(void *stream,char *fmt,void *arglist)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  ushort *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *chr;
  byte bVar8;
  byte *pbVar9;
  int iVar10;
  char *pcVar11;
  ushort *puVar12;
  char *pcVar13;
  ushort *puVar14;
  bool bVar15;
  longlong lVar16;
  void *stream_00;
  char local_1cd;
  int local_1cc;
  char local_1c7;
  char local_1c6;
  char local_1c5;
  int local_1c4;
  char local_1c0;
  char local_1bf;
  char local_1be;
  byte local_1bd;
  uint local_1bc;
  ushort *local_1b8;
  uint local_1b4;
  int local_1b0;
  int local_1ac;
  int local_1a8;
  int local_1a4;
  byte local_19e;
  undefined1 local_19d;
  undefined8 local_19c;
  undefined4 local_194;
  ushort local_18e;
  undefined4 *local_18c;
  int local_188;
  undefined4 local_184;
  byte local_180 [11];
  undefined1 local_175;
  char local_160;
  char local_15f [351];
  
  local_1bf = '\0';
  local_1cc = 0;
  local_1ac = 0;
  bVar8 = *fmt;
  chr = local_18c;
  do {
    if (bVar8 == 0) {
LAB_00489196:
      if ((chr == (undefined4 *)0xffffffff) && ((local_1ac == 0 && (local_1bf == '\0')))) {
        local_1ac = -1;
      }
      return local_1ac;
    }
    iVar10 = 0;
    if ((int)__mb_cur_max < 2) {
      uVar5 = (byte)_pctype[(uint)bVar8 * 2] & 8;
    }
    else {
      uVar5 = _isctype((uint)bVar8,8);
    }
    if (uVar5 != 0) {
      local_1cc = local_1cc + -1;
      stream_00 = stream;
      iVar6 = _whiteout(&local_1cc,stream);
      _un_inc(iVar6,stream_00);
      fmt = fmt + 1;
      iVar6 = isspace((uint)(byte)*fmt);
      while (iVar6 != 0) {
        fmt = fmt + 1;
        iVar6 = isspace((uint)(byte)*fmt);
      }
    }
    if (*fmt != '%') {
      local_1cc = local_1cc + 1;
      chr = (undefined4 *)_inc(stream);
      if ((undefined4 *)(uint)(byte)*fmt != chr) goto LAB_0048917d;
      pbVar9 = (byte *)(fmt + 1);
      if ((_pctype[((uint)chr & 0xff) * 2 + 1] & 0x80) != 0) {
        local_1cc = local_1cc + 1;
        uVar5 = _inc(stream);
        if ((byte)fmt[1] != uVar5) {
          local_1cc = local_1cc + -1;
          _un_inc(uVar5,stream);
          goto LAB_0048917d;
        }
        local_1cc = local_1cc + -1;
        pbVar9 = (byte *)(fmt + 2);
      }
      goto LAB_00489143;
    }
    local_1a4 = 0;
    local_1b4 = local_1b4 & 0xffffff00;
    local_1a8 = 0;
    local_1b0 = 0;
    local_1c4 = 0;
    local_1bd = 0;
    local_1be = '\0';
    local_1c5 = '\0';
    local_1cd = '\0';
    local_1c0 = '\0';
    local_1c7 = '\0';
    local_1c6 = '\x01';
    local_188 = 0;
    do {
      pbVar9 = (byte *)(fmt + 1);
      uVar5 = (uint)*pbVar9;
      if ((int)__mb_cur_max < 2) {
        uVar7 = (byte)_pctype[uVar5 * 2] & 4;
      }
      else {
        uVar7 = _isctype(uVar5,4);
      }
      if (uVar7 == 0) {
        switch(uVar5) {
        case 0x2a:
          local_1c5 = local_1c5 + '\x01';
          break;
        default:
switchD_004886c0_caseD_2b:
          local_1cd = local_1cd + '\x01';
          break;
        case 0x46:
        case 0x4e:
          break;
        case 0x49:
          if ((fmt[2] != '6') || (fmt[3] != '4')) goto switchD_004886c0_caseD_2b;
          iVar10 = iVar10 + 1;
          local_19c = 0;
          pbVar9 = (byte *)(fmt + 3);
          break;
        case 0x4c:
          local_1c6 = local_1c6 + '\x01';
          break;
        case 0x68:
          local_1c6 = local_1c6 + -1;
          local_1c7 = local_1c7 + -1;
          break;
        case 0x6c:
          local_1c6 = local_1c6 + '\x01';
        case 0x77:
          local_1c7 = local_1c7 + '\x01';
        }
      }
      else {
        local_1b0 = local_1b0 + 1;
        local_1c4 = (uVar5 - 0x30) + local_1c4 * 10;
      }
      fmt = (char *)pbVar9;
    } while (local_1cd == '\0');
    puVar3 = arglist;
    if (local_1c5 == '\0') {
      local_1b8 = *(ushort **)arglist;
      puVar3 = (undefined4 *)((int)arglist + 4);
      local_18c = arglist;
    }
    arglist = puVar3;
    bVar15 = false;
    if ((local_1c7 == '\0') && ((*fmt == 'S' || (local_1c7 = -1, *fmt == 'C')))) {
      local_1c7 = '\x01';
    }
    local_1bc = (byte)*fmt | 0x20;
    local_188 = iVar10;
    if (local_1bc != 0x6e) {
      if ((local_1bc == 99) || (local_1bc == 0x7b)) {
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
      }
      else {
        chr = (undefined4 *)_whiteout(&local_1cc,stream);
      }
    }
    puVar12 = local_1b8;
    uVar5 = local_1bc;
    if ((local_1b0 != 0) && (local_1c4 == 0)) {
LAB_0048917d:
      local_1cc = local_1cc + -1;
      _un_inc((int)chr,stream);
      goto LAB_00489196;
    }
    switch(local_1bc) {
    case 99:
      if (local_1b0 == 0) {
        local_1b0 = 1;
        local_1c4 = local_1c4 + 1;
      }
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar11 = &DAT_004d8488;
      goto LAB_0048883e;
    case 100:
    case 0x6f:
    case 0x75:
      goto switchD_004887d8_caseD_64;
    case 0x65:
    case 0x66:
    case 0x67:
      pcVar11 = &local_160;
      if (chr == (undefined4 *)0x2d) {
        local_160 = '-';
        pcVar11 = local_15f;
LAB_00488e83:
        local_1c4 = local_1c4 + -1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00488e83;
      iVar10 = local_1a8;
      if ((local_1b0 == 0) || (0x15d < local_1c4)) {
        local_1c4 = 0x15d;
      }
      while( true ) {
        if ((int)__mb_cur_max < 2) {
          uVar5 = (byte)_pctype[(int)chr * 2] & 4;
        }
        else {
          uVar5 = _isctype((int)chr,4);
        }
        if ((uVar5 == 0) ||
           (iVar6 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar6, bVar15)) break;
        *pcVar11 = (char)chr;
        pcVar11 = pcVar11 + 1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        iVar10 = iVar10 + 1;
      }
      if ((__decimal_point == (char)chr) &&
         (iVar6 = local_1c4 + -1, bVar15 = local_1c4 != 0, local_1c4 = iVar6, bVar15)) {
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        *pcVar11 = __decimal_point;
        while( true ) {
          pcVar11 = pcVar11 + 1;
          if ((int)__mb_cur_max < 2) {
            uVar5 = (byte)_pctype[(int)chr * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)chr,4);
          }
          if ((uVar5 == 0) ||
             (iVar6 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar6, bVar15)) break;
          *pcVar11 = (char)chr;
          iVar10 = iVar10 + 1;
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      pcVar13 = pcVar11;
      if ((iVar10 != 0) &&
         (((chr == (undefined4 *)0x65 || (chr == (undefined4 *)0x45)) &&
          (iVar6 = local_1c4 + -1, bVar15 = local_1c4 != 0, local_1c4 = iVar6, bVar15)))) {
        *pcVar11 = 'e';
        pcVar13 = pcVar11 + 1;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        if (chr == (undefined4 *)0x2d) {
          *pcVar13 = '-';
          pcVar13 = pcVar11 + 2;
LAB_00488fde:
          iVar6 = local_1c4 + -1;
          if (local_1c4 != 0) goto LAB_00488ff3;
        }
        else if (chr == (undefined4 *)0x2b) goto LAB_00488fde;
        while( true ) {
          if ((int)__mb_cur_max < 2) {
            uVar5 = (byte)_pctype[(int)chr * 2] & 4;
          }
          else {
            uVar5 = _isctype((int)chr,4);
          }
          if ((uVar5 == 0) ||
             (iVar6 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar6, bVar15)) break;
          iVar10 = iVar10 + 1;
          *pcVar13 = (char)chr;
          pcVar13 = pcVar13 + 1;
LAB_00488ff3:
          local_1c4 = iVar6;
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      local_1cc = local_1cc + -1;
      _un_inc((int)chr,stream);
      if (iVar10 == 0) goto LAB_00489196;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        *pcVar13 = '\0';
        (*(code *)PTR__fptrap_004d8470)(local_1c6 + -1,local_1b8,&local_160);
      }
      break;
    default:
      if ((undefined4 *)(uint)(byte)*fmt != chr) goto LAB_0048917d;
      local_1bf = local_1bf + -1;
      if (local_1c5 == '\0') {
        arglist = local_18c;
      }
      break;
    case 0x69:
      local_1bc = 100;
    case 0x78:
      uVar5 = local_1bc;
      if (chr == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_00488a92:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar15 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00488a92;
      if (chr == (undefined4 *)0x30) {
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        if (((char)chr == 'x') || ((char)chr == 'X')) {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
          uVar5 = 0x78;
          local_1bc = 0x78;
        }
        else {
          local_1a8 = 1;
          if (uVar5 == 0x78) {
            local_1cc = local_1cc + -1;
            _un_inc((int)chr,stream);
            chr = (undefined4 *)0x30;
          }
          else {
            uVar5 = 0x6f;
            local_1bc = 0x6f;
          }
        }
      }
      goto LAB_00488b74;
    case 0x6e:
      iVar6 = local_1cc;
      if (local_1c5 != '\0') break;
      goto LAB_00488e35;
    case 0x70:
      local_1c6 = '\x01';
switchD_004887d8_caseD_64:
      if (chr == (undefined4 *)0x2d) {
        local_1be = '\x01';
LAB_00488b4a:
        local_1c4 = local_1c4 + -1;
        if ((local_1c4 == 0) && (local_1b0 != 0)) {
          bVar15 = true;
        }
        else {
          local_1cc = local_1cc + 1;
          chr = (undefined4 *)_inc(stream);
        }
      }
      else if (chr == (undefined4 *)0x2b) goto LAB_00488b4a;
LAB_00488b74:
      iVar6 = local_1a4;
      lVar16 = local_19c;
      if (iVar10 == 0) {
        while (!bVar15) {
          if ((uVar5 == 0x78) || (uVar5 == 0x70)) {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 0x80;
            }
            else {
              uVar7 = _isctype((int)chr,0x80);
            }
            if (uVar7 != 0) {
              iVar6 = iVar6 << 4;
              chr = (undefined4 *)_hextodec((int)chr);
              goto LAB_00488d6a;
            }
LAB_00488d66:
            bVar15 = true;
          }
          else {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 4;
            }
            else {
              uVar7 = _isctype((int)chr,4);
            }
            if (uVar7 == 0) goto LAB_00488d66;
            if (uVar5 == 0x6f) {
              if (0x37 < (int)chr) goto LAB_00488d66;
              iVar6 = iVar6 << 3;
            }
            else {
              iVar6 = iVar6 * 10;
            }
          }
LAB_00488d6a:
          if (bVar15) {
            local_1cc = local_1cc + -1;
            _un_inc((int)chr,stream);
          }
          else {
            local_1a8 = local_1a8 + 1;
            iVar6 = iVar6 + -0x30 + (int)chr;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 + -1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              chr = (undefined4 *)_inc(stream);
            }
            else {
              bVar15 = true;
            }
          }
        }
        local_1a4 = iVar6;
        if (local_1be != '\0') {
          local_1a4 = -iVar6;
        }
      }
      else {
        while( true ) {
          uVar5 = (uint)lVar16;
          iVar10 = (int)((ulonglong)lVar16 >> 0x20);
          if (bVar15) break;
          if (local_1bc == 0x78) {
            if ((int)__mb_cur_max < 2) {
              uVar5 = (byte)_pctype[(int)chr * 2] & 0x80;
            }
            else {
              uVar5 = _isctype((int)chr,0x80);
            }
            if (uVar5 != 0) {
              lVar16 = __allshl(4,iVar10);
              chr = (undefined4 *)_hextodec((int)chr);
              goto LAB_00488c41;
            }
LAB_00488c3d:
            bVar15 = true;
          }
          else {
            if ((int)__mb_cur_max < 2) {
              uVar7 = (byte)_pctype[(int)chr * 2] & 4;
            }
            else {
              uVar7 = _isctype((int)chr,4);
            }
            if (uVar7 == 0) goto LAB_00488c3d;
            if (local_1bc == 0x6f) {
              if (0x37 < (int)chr) goto LAB_00488c3d;
              lVar16 = __allshl(3,iVar10);
            }
            else {
              lVar16 = __allmul(uVar5,iVar10,10,0);
            }
          }
LAB_00488c41:
          if (bVar15) {
            local_1cc = local_1cc + -1;
            _un_inc((int)chr,stream);
          }
          else {
            puVar3 = chr + -0xc;
            local_1a8 = local_1a8 + 1;
            if ((local_1b0 == 0) || (local_1c4 = local_1c4 + -1, local_1c4 != 0)) {
              local_1cc = local_1cc + 1;
              chr = (undefined4 *)_inc(stream);
              lVar16 = lVar16 + (int)puVar3;
            }
            else {
              bVar15 = true;
              lVar16 = lVar16 + (int)puVar3;
            }
          }
        }
        local_19c = lVar16;
        if (local_1be != '\0') {
          local_19c = CONCAT44(-(iVar10 + (uint)(uVar5 != 0)),-uVar5);
        }
      }
      iVar10 = local_1a8;
      if (local_1bc == 0x46) {
        iVar10 = 0;
      }
      if (iVar10 == 0) goto LAB_00489196;
      if (local_1c5 == '\0') {
        local_1ac = local_1ac + 1;
        iVar6 = local_1a4;
        iVar10 = local_188;
LAB_00488e35:
        if (iVar10 == 0) {
          if (local_1c6 == '\0') {
            *local_1b8 = (ushort)iVar6;
          }
          else {
            *(int *)local_1b8 = iVar6;
          }
        }
        else {
          *(undefined4 *)local_1b8 = (undefined4)local_19c;
          *(undefined4 *)(local_1b8 + 2) = local_19c._4_4_;
        }
      }
      break;
    case 0x73:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pcVar11 = s_____004d8480;
LAB_0048883e:
      local_1bd = 0xff;
      pbVar9 = (byte *)fmt;
LAB_00488843:
      fmt = (char *)pbVar9;
      pbVar9 = local_180;
      for (iVar10 = 8; iVar10 != 0; iVar10 = iVar10 + -1) {
        pbVar9[0] = 0;
        pbVar9[1] = 0;
        pbVar9[2] = 0;
        pbVar9[3] = 0;
        pbVar9 = pbVar9 + 4;
      }
      if ((local_1bc == 0x7b) && (*pcVar11 == 0x5d)) {
        local_1b4 = CONCAT31(local_1b4._1_3_,0x5d);
        pcVar11 = pcVar11 + 1;
        local_175 = 0x20;
      }
      bVar8 = *pcVar11;
      uVar5 = local_1b4;
      while (bVar8 != 0x5d) {
        pbVar9 = (byte *)(pcVar11 + 1);
        uVar7 = (uint)local_184 >> 8;
        local_184 = CONCAT31((int3)uVar7,bVar8);
        local_1b4._1_3_ = (undefined3)(uVar5 >> 8);
        if (((bVar8 == 0x2d) &&
            (local_1b4._0_1_ = (byte)uVar5, bVar2 = (byte)local_1b4, (byte)local_1b4 != 0)) &&
           (bVar1 = *pbVar9, bVar1 != 0x5d)) {
          pbVar9 = (byte *)(pcVar11 + 2);
          uVar7 = (uint)local_194 >> 8;
          bVar8 = (byte)local_1b4;
          if (bVar1 <= (byte)local_1b4) {
            local_1b4 = CONCAT31(local_1b4._1_3_,bVar1);
            bVar8 = bVar1;
            uVar5 = local_1b4;
            bVar1 = bVar2;
          }
          local_1b4 = uVar5;
          local_194 = CONCAT31((int3)uVar7,bVar1);
          if (bVar8 <= bVar1) {
            uVar5 = local_1b4 & 0xff;
            iVar10 = (bVar1 - uVar5) + 1;
            do {
              uVar7 = uVar5 >> 3;
              bVar8 = (byte)uVar5;
              uVar5 = uVar5 + 1;
              iVar10 = iVar10 + -1;
              local_180[uVar7] = local_180[uVar7] | '\x01' << (bVar8 & 7);
            } while (iVar10 != 0);
          }
          local_1b4 = local_1b4 & 0xffffff00;
        }
        else {
          local_1b4 = CONCAT31(local_1b4._1_3_,bVar8);
          local_180[bVar8 >> 3] = local_180[bVar8 >> 3] | '\x01' << (bVar8 & 7);
        }
        pcVar11 = (char *)pbVar9;
        uVar5 = local_1b4;
        bVar8 = *pbVar9;
      }
      if (*pcVar11 == 0) goto LAB_00489196;
      if (local_1bc == 0x7b) {
        fmt = pcVar11;
      }
      local_1cc = local_1cc + -1;
      local_1b4 = uVar5;
      _un_inc((int)chr,stream);
      puVar14 = puVar12;
      while( true ) {
        if ((local_1b0 != 0) &&
           (iVar10 = local_1c4 + -1, bVar15 = local_1c4 == 0, local_1c4 = iVar10, puVar4 = puVar14,
           bVar15)) goto LAB_00488a2c;
        local_1cc = local_1cc + 1;
        chr = (undefined4 *)_inc(stream);
        if ((chr == (undefined4 *)0xffffffff) ||
           (bVar8 = (byte)chr,
           ((int)(char)(local_180[(int)chr >> 3] ^ local_1bd) & 1 << (bVar8 & 7)) == 0)) break;
        if (local_1c5 == '\0') {
          if (local_1c0 == '\0') {
            *(byte *)puVar14 = bVar8;
            puVar14 = (ushort *)((int)puVar14 + 1);
          }
          else {
            local_19e = bVar8;
            if ((_pctype[((uint)chr & 0xff) * 2 + 1] & 0x80) != 0) {
              local_1cc = local_1cc + 1;
              iVar10 = _inc(stream);
              local_19d = (undefined1)iVar10;
            }
            mbtowc(&local_18e,(char *)&local_19e,__mb_cur_max);
            *puVar14 = local_18e;
            puVar14 = puVar14 + 1;
          }
        }
        else {
          puVar12 = (ushort *)((int)puVar12 + 1);
        }
      }
      local_1cc = local_1cc + -1;
      local_1b8 = puVar14;
      _un_inc((int)chr,stream);
      puVar4 = local_1b8;
LAB_00488a2c:
      local_1b8 = puVar4;
      if (puVar12 == puVar14) goto LAB_00489196;
      if ((local_1c5 == '\0') && (local_1ac = local_1ac + 1, local_1bc != 99)) {
        if (local_1c0 == '\0') {
          *(byte *)local_1b8 = 0;
        }
        else {
          *local_1b8 = 0;
        }
      }
      break;
    case 0x7b:
      if ('\0' < local_1c7) {
        local_1c0 = '\x01';
      }
      pbVar9 = (byte *)(fmt + 1);
      pcVar11 = (char *)pbVar9;
      if (*pbVar9 == 0x5e) {
        pcVar11 = fmt + 2;
        fmt = (char *)pbVar9;
        goto LAB_0048883e;
      }
      goto LAB_00488843;
    }
    local_1bf = local_1bf + '\x01';
    pbVar9 = (byte *)(fmt + 1);
LAB_00489143:
    fmt = (char *)pbVar9;
    if ((chr == (undefined4 *)0xffffffff) && ((*fmt != '%' || (fmt[1] != 'n')))) goto LAB_00489196;
    bVar8 = *fmt;
  } while( true );
}


/* ==== _hextodec @ 00489280 ==== */

int __cdecl _hextodec(int chr)

{
  uint uVar1;
  
  if (__mb_cur_max < 2) {
    uVar1 = (byte)_pctype[chr * 2] & 4;
  }
  else {
    uVar1 = _isctype(chr,4);
  }
  if (uVar1 == 0) {
    chr = (chr & 0xffffffdfU) - 7;
  }
  return chr;
}


/* ==== _inc @ 004892c0 ==== */

int __cdecl _inc(void *stream)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)((int)stream + 4) + -1;
  *(int *)((int)stream + 4) = iVar2;
  if (-1 < iVar2) {
    bVar1 = **(byte **)stream;
    *(byte **)stream = *(byte **)stream + 1;
    return (uint)bVar1;
  }
  iVar2 = _filbuf(stream);
  return iVar2;
}


/* ==== _un_inc @ 004892f0 ==== */

void __cdecl _un_inc(int chr,void *stream)

{
  if (chr != -1) {
    ungetc(chr,stream);
  }
  return;
}


/* ==== _whiteout @ 00489310 ==== */

int __cdecl _whiteout(int *counter,void *stream)

{
  int c;
  int iVar1;
  
  *counter = *counter + 1;
  c = _inc(stream);
  iVar1 = isspace(c);
  while (iVar1 != 0) {
    *counter = *counter + 1;
    c = _inc(stream);
    iVar1 = isspace(c);
  }
  return c;
}


/* ==== _openfile @ 00489360 ==== */

void __cdecl _openfile(char *name,char *mode,int shflag,void *stream)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint oflag;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  
  cVar1 = *mode;
  bVar3 = false;
  bVar4 = false;
  if (cVar1 == 'a') {
    oflag = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      oflag = 0;
      uVar7 = DAT_005055ec | 1;
      goto LAB_0048939d;
    }
    if (cVar1 != 'w') {
      return;
    }
    oflag = 0x301;
  }
  uVar7 = DAT_005055ec | 2;
LAB_0048939d:
  pcVar6 = mode + 1;
  bVar2 = true;
  cVar1 = *pcVar6;
  do {
    if ((cVar1 == '\0') || (!bVar2)) {
      iVar5 = _sopen(name,oflag,shflag,0x1a4);
      if (-1 < iVar5) {
        _cflush = _cflush + 1;
        *(uint *)((int)stream + 0xc) = uVar7;
        *(undefined4 *)((int)stream + 4) = 0;
        *(undefined4 *)stream = 0;
        *(undefined4 *)((int)stream + 8) = 0;
        *(undefined4 *)((int)stream + 0x1c) = 0;
        *(int *)((int)stream + 0x10) = iVar5;
        return;
      }
      return;
    }
    switch(cVar1) {
    case '+':
      if ((oflag & 2) != 0) break;
      oflag = oflag & 0xfffffffe | 2;
      uVar7 = uVar7 & 0xfffffffc | 0x80;
      goto LAB_0048944e;
    case 'D':
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_0048944e;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x10;
        goto LAB_0048944e;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x20;
        goto LAB_0048944e;
      }
      break;
    case 'T':
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_0048944e;
      }
      break;
    case 'b':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x8000;
        goto LAB_0048944e;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_0048944e;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_0048944e;
      }
      break;
    case 't':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x4000;
        goto LAB_0048944e;
      }
    }
    bVar2 = false;
LAB_0048944e:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}


/* ==== _getstream @ 00489530 ==== */

void _getstream(void)

{
  int extraout_EAX;
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)0x0;
  iVar1 = 0;
  piVar2 = __piob;
  if (0 < _nstream) {
    do {
      if (*piVar2 == 0) {
        malloc(0x20);
        __piob[iVar1] = extraout_EAX;
        if ((undefined4 *)__piob[iVar1] != (undefined4 *)0x0) {
          puVar3 = (undefined4 *)__piob[iVar1];
        }
        break;
      }
      if ((*(byte *)(*piVar2 + 0xc) & 0x83) == 0) {
        puVar3 = (undefined4 *)__piob[iVar1];
        break;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < _nstream);
  }
  if (puVar3 != (undefined4 *)0x0) {
    puVar3[1] = 0;
    puVar3[3] = 0;
    puVar3[2] = 0;
    *puVar3 = 0;
    puVar3[7] = 0;
    puVar3[4] = 0xffffffff;
  }
  return;
}


/* ==== _commit @ 004895c0 ==== */

int __cdecl _commit(int fh)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD DVar2;
  
  DVar2 = _doserrno;
  if (((uint)fh < _nhandle) && ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 1) != 0))
  {
    hFile = (HANDLE)_get_osfhandle(fh);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
    }
    else {
      DVar2 = 0;
    }
    if (DVar2 == 0) {
      return 0;
    }
  }
  _doserrno = DVar2;
  errno = 9;
  return -1;
}


/* ==== _write @ 00489620 ==== */

int __cdecl _write(int fh,void *buf,uint cnt)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  char *pcVar4;
  BOOL BVar5;
  int iVar6;
  char *pcVar7;
  DWORD local_41c;
  ulong local_414;
  DWORD local_410;
  int local_40c;
  int *local_408;
  char local_404 [1028];
  
  if ((uint)fh < _nhandle) {
    piVar1 = &__pioinfo + (fh >> 5);
    iVar6 = (fh & 0x1fU) * 8;
    bVar2 = *(byte *)(iVar6 + 4 + (&__pioinfo)[fh >> 5]);
    if ((bVar2 & 1) != 0) {
      local_41c = 0;
      local_40c = 0;
      if (cnt == 0) {
        return 0;
      }
      local_408 = piVar1;
      if ((bVar2 & 0x20) != 0) {
        _lseek(fh,0,2);
      }
      if ((*(byte *)((undefined4 *)(*piVar1 + iVar6) + 1) & 0x80) == 0) {
        BVar5 = WriteFile(*(HANDLE *)(*piVar1 + iVar6),buf,cnt,&local_410,(LPOVERLAPPED)0x0);
        if (BVar5 == 0) {
          local_414 = GetLastError();
        }
        else {
          local_41c = local_410;
          local_414 = 0;
        }
      }
      else {
        local_414 = 0;
        pcVar7 = buf;
        if (cnt != 0) {
          do {
            pcVar4 = local_404;
            do {
              if (cnt <= (uint)((int)pcVar7 - (int)buf)) break;
              cVar3 = *pcVar7;
              pcVar7 = pcVar7 + 1;
              if (cVar3 == '\n') {
                *pcVar4 = '\r';
                local_40c = local_40c + 1;
                pcVar4 = pcVar4 + 1;
              }
              *pcVar4 = cVar3;
              pcVar4 = pcVar4 + 1;
            } while ((int)pcVar4 - (int)local_404 < 0x400);
            BVar5 = WriteFile(*(HANDLE *)(iVar6 + *local_408),local_404,(int)pcVar4 - (int)local_404
                              ,&local_410,(LPOVERLAPPED)0x0);
            if (BVar5 == 0) {
              local_414 = GetLastError();
              break;
            }
            local_41c = local_41c + local_410;
            if (((int)local_410 < (int)pcVar4 - (int)local_404) ||
               (cnt <= (uint)((int)pcVar7 - (int)buf))) break;
          } while( true );
        }
      }
      if (local_41c != 0) {
        return local_41c - local_40c;
      }
      if (local_414 == 0) {
        if (((*(byte *)(iVar6 + 4 + *local_408) & 0x40) != 0) && (*(char *)buf == '\x1a')) {
          return 0;
        }
        errno = 0x1c;
        _doserrno = 0;
        return -1;
      }
      if (local_414 == 5) {
        _doserrno = local_414;
        errno = 9;
        return -1;
      }
      _dosmaperr(local_414);
      return -1;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _lseek @ 00489840 ==== */

long __cdecl _lseek(int fh,long pos,int mthd)

{
  HANDLE hFile;
  DWORD DVar1;
  ulong oserrno;
  int iVar2;
  
  if ((uint)fh < _nhandle) {
    iVar2 = (fh & 0x1fU) * 8;
    if ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar2) & 1) != 0) {
      hFile = (HANDLE)_get_osfhandle(fh);
      if (hFile == (HANDLE)0xffffffff) {
        errno = 9;
        return -1;
      }
      DVar1 = SetFilePointer(hFile,pos,(PLONG)0x0,mthd);
      if (DVar1 == 0xffffffff) {
        oserrno = GetLastError();
      }
      else {
        oserrno = 0;
      }
      if (oserrno != 0) {
        _dosmaperr(oserrno);
        return -1;
      }
      *(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar2) =
           *(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar2) & 0xfd;
      return DVar1;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _access @ 00489900 ==== */

int __cdecl _access(char *path,int mode)

{
  DWORD DVar1;
  
  DVar1 = GetFileAttributesA(path);
  if (DVar1 == 0xffffffff) {
    DVar1 = GetLastError();
    _dosmaperr(DVar1);
    return -1;
  }
  if (((DVar1 & 1) != 0) && ((mode & 2U) != 0)) {
    errno = 0xd;
    _doserrno = 5;
    return -1;
  }
  return 0;
}


/* ==== _strdup @ 00489950 ==== */

char __cdecl _strdup(char *s)

{
  char cVar1;
  char *extraout_EAX;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (s != (char *)0x0) {
    uVar2 = 0xffffffff;
    pcVar4 = s;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    malloc(~uVar2);
    if (extraout_EAX != (char *)0x0) {
      uVar2 = 0xffffffff;
      do {
        pcVar4 = s;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar4 = s + 1;
        cVar1 = *s;
        s = pcVar4;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      pcVar4 = pcVar4 + -uVar2;
      pcVar5 = extraout_EAX;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      return (char)extraout_EAX;
    }
  }
  return '\0';
}


/* ==== _open @ 004899a0 ==== */

int __cdecl _open(char *path,int oflag,...)

{
  int iVar1;
  int in_stack_0000000c;
  
  iVar1 = _sopen(path,oflag,0x40,in_stack_0000000c);
  return iVar1;
}


/* ==== _sopen @ 004899c0 ==== */

int __cdecl _sopen(char *path,int oflag,int shflag,int pmode)

{
  uint uVar1;
  HANDLE hFile;
  long lVar2;
  int iVar3;
  DWORD DVar4;
  DWORD dwCreationDisposition;
  DWORD dwFlagsAndAttributes;
  int iVar5;
  bool bVar6;
  byte local_11;
  uint local_10;
  _SECURITY_ATTRIBUTES local_c;
  
  bVar6 = (oflag & 0x80U) == 0;
  local_c.nLength = 0xc;
  local_c.lpSecurityDescriptor = (LPVOID)0x0;
  if (bVar6) {
    local_11 = 0;
  }
  else {
    local_11 = 0x10;
  }
  local_c.bInheritHandle = (BOOL)bVar6;
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_00505698 != 0x8000)))) {
    local_11 = local_11 | 0x80;
  }
  uVar1 = oflag & 3;
  if (uVar1 == 0) {
    local_10 = 0x80000000;
  }
  else if (uVar1 == 1) {
    local_10 = 0x40000000;
  }
  else {
    if (uVar1 != 2) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
    local_10 = 0xc0000000;
  }
  switch(shflag) {
  case 0x10:
    DVar4 = 0;
    break;
  default:
    goto switchD_00489a58_caseD_11;
  case 0x20:
    DVar4 = 1;
    break;
  case 0x30:
    DVar4 = 2;
    break;
  case 0x40:
    DVar4 = 3;
  }
  uVar1 = oflag & 0x700;
  if (uVar1 < 0x101) {
    if (uVar1 == 0x100) {
      dwCreationDisposition = 4;
      goto LAB_00489aeb;
    }
    if (uVar1 != 0) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00489ac6:
    dwCreationDisposition = 3;
    goto LAB_00489aeb;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      dwCreationDisposition = 2;
      goto LAB_00489aeb;
    }
    if (uVar1 != 0x200) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00489ae6:
    dwCreationDisposition = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_00489a58_caseD_11:
          _doserrno = 0;
          errno = 0x16;
          return -1;
        }
        goto LAB_00489ac6;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_00489ae6;
      if (uVar1 != 0x700) {
        errno = 0x16;
        _doserrno = 0;
        return -1;
      }
    }
    dwCreationDisposition = 1;
  }
LAB_00489aeb:
  dwFlagsAndAttributes = 0x80;
  if (((oflag & 0x100U) != 0) && (((byte)pmode & ~(byte)DAT_0050530c & 0x80) == 0)) {
    dwFlagsAndAttributes = 1;
  }
  if ((oflag & 0x40U) != 0) {
    dwFlagsAndAttributes = dwFlagsAndAttributes | 0x4000000;
    local_10 = local_10 | 0x10000;
  }
  if ((oflag & 0x1000U) != 0) {
    dwFlagsAndAttributes = dwFlagsAndAttributes | 0x100;
  }
  if ((oflag & 0x20U) == 0) {
    if ((oflag & 0x10U) != 0) {
      dwFlagsAndAttributes = dwFlagsAndAttributes | 0x10000000;
    }
  }
  else {
    dwFlagsAndAttributes = dwFlagsAndAttributes | 0x8000000;
  }
  uVar1 = _alloc_osfhnd();
  if (uVar1 == 0xffffffff) {
    errno = 0x18;
    _doserrno = 0;
    return -1;
  }
  hFile = CreateFileA(path,local_10,DVar4,&local_c,dwCreationDisposition,dwFlagsAndAttributes,
                      (HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    DVar4 = GetLastError();
    _dosmaperr(DVar4);
    return -1;
  }
  DVar4 = GetFileType(hFile);
  if (DVar4 != 0) {
    if (DVar4 == 2) {
      local_11 = local_11 | 0x40;
    }
    else if (DVar4 == 3) {
      local_11 = local_11 | 8;
    }
    _set_osfhnd(uVar1,(long)hFile);
    iVar5 = (uVar1 & 0x1f) * 8;
    *(byte *)(iVar5 + 4 + (&__pioinfo)[(int)uVar1 >> 5]) = local_11 | 1;
    if ((((local_11 & 0x48) == 0) && ((local_11 & 0x80) != 0)) && ((oflag & 2U) != 0)) {
      lVar2 = _lseek(uVar1,-1,2);
      if (lVar2 == -1) {
        if (_doserrno != 0x83) {
          _close(uVar1);
          return -1;
        }
      }
      else {
        shflag = shflag & 0xffffff00;
        iVar3 = _read(uVar1,&shflag,1);
        if (((iVar3 == 0) && ((char)shflag == '\x1a')) &&
           (iVar3 = _chsize(uVar1,lVar2), iVar3 == -1)) {
          _close(uVar1);
          return -1;
        }
        lVar2 = _lseek(uVar1,0,0);
        if (lVar2 == -1) {
          _close(uVar1);
          return -1;
        }
      }
    }
    if (((local_11 & 0x48) == 0) && ((oflag & 8U) != 0)) {
      *(byte *)(iVar5 + 4 + (&__pioinfo)[(int)uVar1 >> 5]) =
           *(byte *)(iVar5 + 4 + (&__pioinfo)[(int)uVar1 >> 5]) | 0x20;
    }
    return uVar1;
  }
  CloseHandle(hFile);
  DVar4 = GetLastError();
  _dosmaperr(DVar4);
  return -1;
}


/* ==== xtoa @ 00489d80 ==== */

void __cdecl xtoa(ulong val,char *buf,uint radix,int is_neg)

{
  ulonglong uVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  
  pcVar2 = buf;
  if (is_neg != 0) {
    *buf = '-';
    buf = buf + 1;
    val = -val;
    pcVar2 = buf;
  }
  do {
    pcVar4 = pcVar2;
    uVar1 = (ulonglong)val;
    val = val / radix;
    cVar3 = (char)(uVar1 % (ulonglong)radix);
    if ((uint)(uVar1 % (ulonglong)radix) < 10) {
      cVar3 = cVar3 + '0';
    }
    else {
      cVar3 = cVar3 + 'W';
    }
    *pcVar4 = cVar3;
    pcVar2 = pcVar4 + 1;
  } while (val != 0);
  pcVar4[1] = '\0';
  do {
    cVar3 = *pcVar4;
    *pcVar4 = *buf;
    *buf = cVar3;
    pcVar4 = pcVar4 + -1;
    buf = buf + 1;
  } while (buf < pcVar4);
  return;
}


/* ==== _ultoa @ 00489df0 ==== */

char __cdecl _ultoa(ulong val,char *buf,int radix)

{
  xtoa(val,buf,radix,0);
  return (char)buf;
}


/* ==== GetCurrentProcessId @ 00489e10 ==== */

DWORD GetCurrentProcessId(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00489e10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetCurrentProcessId();
  return DVar1;
}


/* ==== _mbsrchr @ 00489e20 ==== */

uchar __cdecl _mbsrchr(uchar *s,uint c)

{
  ushort uVar1;
  uchar uVar2;
  byte *pbVar3;
  byte bVar4;
  byte bVar5;
  byte *pbVar6;
  
  pbVar3 = (byte *)0x0;
  if (DAT_0050558c == 0) {
    uVar2 = strrchr((char *)s,c);
    return uVar2;
  }
  do {
    bVar5 = *s;
    if ((*(byte *)((int)&DAT_00505488 + bVar5 + 1) & 4) == 0) {
      pbVar6 = s;
      bVar4 = bVar5;
      if (c == bVar5) {
LAB_00489e8f:
        pbVar3 = s;
        pbVar6 = pbVar3;
        bVar5 = bVar4;
      }
    }
    else {
      bVar4 = s[1];
      pbVar6 = s + 1;
      if (bVar4 == 0) {
        s = pbVar6;
        bVar5 = bVar4;
        if (pbVar3 == (byte *)0x0) goto LAB_00489e8f;
      }
      else {
        uVar1 = CONCAT11(bVar5,bVar4);
        bVar5 = bVar4;
        if (c == uVar1) {
          pbVar3 = s;
        }
      }
    }
    s = pbVar6 + 1;
    if (bVar5 == 0) {
      return (uchar)pbVar3;
    }
  } while( true );
}


/* ==== _stbuf @ 00489ef0 ==== */

int __cdecl _stbuf(void *stream)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = _isatty(*(int *)((int)stream + 0x10));
  if (iVar2 != 0) {
    if (stream == &DAT_004d7fc0) {
      iVar2 = 0;
    }
    else {
      if (stream != &DAT_004d7fe0) {
        return 0;
      }
      iVar2 = 1;
    }
    _cflush = _cflush + 1;
    if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
      if ((&DAT_005055f8)[iVar2] == 0) {
        malloc(0x1000);
        (&DAT_005055f8)[iVar2] = extraout_EAX;
        if (extraout_EAX == 0) {
          return 0;
        }
      }
      uVar1 = (&DAT_005055f8)[iVar2];
      *(undefined4 *)((int)stream + 0x18) = 0x1000;
      *(undefined4 *)((int)stream + 8) = uVar1;
      *(undefined4 *)stream = uVar1;
      *(undefined4 *)((int)stream + 4) = 0x1000;
      *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 0x1102;
      return 1;
    }
  }
  return 0;
}


/* ==== _ftbuf @ 00489f90 ==== */

void __cdecl _ftbuf(int flag,void *stream)

{
  if (flag == 0) {
    if ((*(uint *)((int)stream + 0xc) & 0x1000) != 0) {
      _flush(stream);
    }
  }
  else if ((*(uint *)((int)stream + 0xc) & 0x1000) != 0) {
    _flush(stream);
    *(undefined4 *)((int)stream + 0x18) = 0;
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffeeff;
    *(undefined4 *)stream = 0;
    *(undefined4 *)((int)stream + 8) = 0;
    return;
  }
  return;
}


/* ==== __sbh_new_region @ 00489ff0 ==== */

void __sbh_new_region(void)

{
  bool bVar1;
  undefined4 *lpAddress;
  LPVOID pvVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **lpMem;
  undefined4 *puVar5;
  
  if (DAT_004d84a8 == -1) {
    lpMem = &PTR_LOOP_004d8498;
  }
  else {
    lpMem = HeapAlloc(_crtheap,0,0x2020);
    if (lpMem == (undefined **)0x0) {
      return;
    }
  }
  lpAddress = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (lpAddress != (undefined4 *)0x0) {
    pvVar2 = VirtualAlloc(lpAddress,0x10000,0x1000,4);
    if (pvVar2 != (LPVOID)0x0) {
      if (lpMem == &PTR_LOOP_004d8498) {
        if (PTR_LOOP_004d8498 == (undefined *)0x0) {
          PTR_LOOP_004d8498 = (undefined *)&PTR_LOOP_004d8498;
        }
        if (PTR_LOOP_004d849c == (undefined *)0x0) {
          PTR_LOOP_004d849c = (undefined *)&PTR_LOOP_004d8498;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_004d8498;
        lpMem[1] = PTR_LOOP_004d849c;
        PTR_LOOP_004d849c = (undefined *)lpMem;
        *(undefined ***)lpMem[1] = lpMem;
      }
      lpMem[5] = (undefined *)(lpAddress + 0x100000);
      lpMem[4] = (undefined *)lpAddress;
      lpMem[2] = (undefined *)(lpMem + 6);
      lpMem[3] = (undefined *)(lpMem + 0x26);
      iVar3 = 0;
      ppuVar4 = lpMem + 6;
      do {
        bVar1 = 0xf < iVar3;
        iVar3 = iVar3 + 1;
        *ppuVar4 = (undefined *)((bVar1 - 1 & 0xf1) - 1);
        ppuVar4[1] = (undefined *)0xf1;
        ppuVar4 = ppuVar4 + 2;
      } while (iVar3 < 0x400);
      puVar5 = lpAddress;
      for (iVar3 = 0x4000; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      if (lpAddress < lpMem[4] + 0x10000) {
        do {
          lpAddress[1] = 0xf0;
          *lpAddress = lpAddress + 2;
          *(undefined1 *)(lpAddress + 0x3e) = 0xff;
          lpAddress = lpAddress + 0x400;
        } while (lpAddress < lpMem[4] + 0x10000);
      }
      return;
    }
    VirtualFree(lpAddress,0,0x8000);
  }
  if (lpMem != &PTR_LOOP_004d8498) {
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== __sbh_release_region @ 0048a160 ==== */

void __cdecl __sbh_release_region(void *preg)

{
  VirtualFree(*(LPVOID *)((int)preg + 0x10),0,0x8000);
  if (PTR_LOOP_004da4b8 == preg) {
    PTR_LOOP_004da4b8 = *(undefined **)((int)preg + 4);
  }
  if (preg != &PTR_LOOP_004d8498) {
    **(undefined4 **)((int)preg + 4) = *(undefined4 *)preg;
    *(undefined4 *)(*(int *)preg + 4) = *(undefined4 *)((int)preg + 4);
    HeapFree(_crtheap,0,preg);
    return;
  }
  DAT_004d84a8 = 0xffffffff;
  return;
}


/* ==== __sbh_decommit_pages @ 0048a1c0 ==== */

void __cdecl __sbh_decommit_pages(int count)

{
  BOOL BVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *preg;
  undefined *puVar5;
  
  preg = PTR_LOOP_004d849c;
  do {
    puVar5 = preg;
    if (*(int *)(preg + 0x10) != -1) {
      iVar4 = 0;
      piVar2 = (int *)(preg + 0x2010);
      iVar3 = 0x3ff000;
      do {
        if (*piVar2 == 0xf0) {
          BVar1 = VirtualFree((LPVOID)(*(int *)(preg + 0x10) + iVar3),0x1000,0x4000);
          if (BVar1 != 0) {
            *piVar2 = -1;
            DAT_00505600 = DAT_00505600 + -1;
            if ((*(int **)(preg + 0xc) == (int *)0x0) || (piVar2 < *(int **)(preg + 0xc))) {
              *(int **)(preg + 0xc) = piVar2;
            }
            iVar4 = iVar4 + 1;
            count = count + -1;
            if (count == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        piVar2 = piVar2 + -2;
      } while (-1 < iVar3);
      puVar5 = *(undefined **)(preg + 4);
      if ((iVar4 != 0) && (*(int *)(preg + 0x18) == -1)) {
        iVar3 = 1;
        piVar2 = (int *)(preg + 0x20);
        do {
          if (*piVar2 != -1) break;
          iVar3 = iVar3 + 1;
          piVar2 = piVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          __sbh_release_region(preg);
        }
      }
    }
    if ((puVar5 == PTR_LOOP_004d849c) || (preg = puVar5, count < 1)) {
      return;
    }
  } while( true );
}


/* ==== __sbh_find_block @ 0048a290 ==== */

void __cdecl __sbh_find_block(void *pblock,void *ppreg,void *pppage)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_004d8498;
  while ((pblock <= ppuVar1[4] || (ppuVar1[5] <= pblock))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_004d8498) {
      return;
    }
  }
  if (((uint)pblock & 0xf) != 0) {
    return;
  }
  if (((uint)pblock & 0xfff) < 0x100) {
    return;
  }
  *(undefined ***)ppreg = ppuVar1;
  *(uint *)pppage = (uint)pblock & 0xfffff000;
  return;
}


/* ==== __sbh_free_block @ 0048a2f0 ==== */

void __cdecl __sbh_free_block(void *preg,void *ppage,void *pmap)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (int)ppage - *(int *)((int)preg + 0x10) >> 0xc;
  piVar1 = (int *)((int)preg + iVar2 * 8 + 0x18);
  *piVar1 = *(int *)((int)preg + iVar2 * 8 + 0x18) + (uint)*(byte *)pmap;
  *(undefined1 *)pmap = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_00505600 = DAT_00505600 + 1, DAT_00505600 == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}


/* ==== __sbh_alloc_block @ 0048a350 ==== */

void __cdecl __sbh_alloc_block(uint para_req)

{
  undefined **ppuVar1;
  uint *puVar2;
  undefined **ppuVar3;
  undefined *puVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  int *piVar5;
  undefined *extraout_EAX_01;
  undefined **ppuVar6;
  undefined **ppuVar7;
  void *pvVar8;
  int iVar9;
  uint *puVar10;
  int *piVar11;
  bool bVar12;
  
  piVar11 = (int *)PTR_LOOP_004da4b8;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      pvVar8 = (void *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX != 0) {
            PTR_LOOP_004da4b8 = (undefined *)piVar11;
            *puVar10 = *puVar10 - para_req;
            piVar11[2] = (int)puVar10;
            return;
          }
          puVar10[1] = para_req;
        }
        pvVar8 = (void *)((int)pvVar8 + 0x1000);
      }
      puVar2 = (uint *)piVar11[2];
      pvVar8 = (void *)piVar11[4];
      for (puVar10 = (uint *)(piVar11 + 6); puVar10 < puVar2; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX_00 != 0) {
            PTR_LOOP_004da4b8 = (undefined *)piVar11;
            *puVar10 = *puVar10 - para_req;
            piVar11[2] = (int)puVar10;
            return;
          }
          puVar10[1] = para_req;
        }
        pvVar8 = (void *)((int)pvVar8 + 0x1000);
      }
    }
    piVar11 = (int *)*piVar11;
  } while (piVar11 != (int *)PTR_LOOP_004da4b8);
  ppuVar7 = &PTR_LOOP_004d8498;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_004d8498) {
      __sbh_new_region();
      if (extraout_EAX_01 == (undefined *)0x0) {
        return;
      }
      piVar11 = *(int **)(extraout_EAX_01 + 0x10);
      *(char *)(piVar11 + 2) = (char)para_req;
      PTR_LOOP_004da4b8 = extraout_EAX_01;
      *piVar11 = (int)piVar11 + para_req + 8;
      piVar11[1] = 0xf0 - para_req;
      *(uint *)(extraout_EAX_01 + 0x18) = *(int *)(extraout_EAX_01 + 0x18) - (para_req & 0xff);
      return;
    }
  }
  ppuVar3 = (undefined **)ppuVar7[3];
  puVar4 = *ppuVar3;
  piVar11 = (int *)(ppuVar7[4] + ((int)ppuVar3 + (-0x18 - (int)ppuVar7) >> 3) * 0x1000);
  ppuVar6 = ppuVar3;
  for (iVar9 = 0; (puVar4 == (undefined *)0xffffffff && (iVar9 < 0x10)); iVar9 = iVar9 + 1) {
    puVar4 = ppuVar6[2];
    ppuVar6 = ppuVar6 + 2;
  }
  piVar5 = VirtualAlloc(piVar11,iVar9 << 0xc,0x1000,4);
  if (piVar5 != piVar11) {
    return;
  }
  ppuVar6 = ppuVar3;
  if (0 < iVar9) {
    piVar5 = piVar11 + 1;
    do {
      *piVar5 = 0xf0;
      piVar5[-1] = (int)(piVar5 + 1);
      *(undefined1 *)(piVar5 + 0x3d) = 0xff;
      *ppuVar6 = (undefined *)0xf0;
      ppuVar6[1] = (undefined *)0xf1;
      piVar5 = piVar5 + 0x400;
      ppuVar6 = ppuVar6 + 2;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  ppuVar1 = ppuVar7 + 0x806;
  bVar12 = false;
  if (ppuVar6 < ppuVar1) {
    do {
      if (*ppuVar6 == (undefined *)0xffffffff) break;
      ppuVar6 = ppuVar6 + 2;
    } while (ppuVar6 < ppuVar1);
    bVar12 = ppuVar6 < ppuVar1;
  }
  PTR_LOOP_004da4b8 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)para_req;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -para_req;
  piVar11[1] = piVar11[1] - para_req;
  *piVar11 = (int)piVar11 + para_req + 8;
  return;
}


/* ==== __sbh_alloc_block_from_page @ 0048a590 ==== */

void __cdecl __sbh_alloc_block_from_page(void *ppage,uint free_para_count,uint para_req)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = *(byte **)ppage;
  if (para_req <= *(uint *)((int)ppage + 4)) {
    *pbVar2 = (byte)para_req;
    if (pbVar2 + para_req < (byte *)((int)ppage + 0xf8U)) {
      *(uint *)ppage = *(int *)ppage + para_req;
      *(uint *)((int)ppage + 4) = *(int *)((int)ppage + 4) - para_req;
    }
    else {
      *(undefined4 *)((int)ppage + 4) = 0;
      *(int *)ppage = (int)ppage + 8;
    }
    return;
  }
  pbVar6 = pbVar2;
  if (pbVar2[*(uint *)((int)ppage + 4)] != 0) {
    pbVar6 = pbVar2 + *(uint *)((int)ppage + 4);
  }
  if (pbVar6 + para_req < (byte *)((int)ppage + 0xf8U)) {
    do {
      if (*pbVar6 == 0) {
        pbVar3 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar3 = pbVar3 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar3;
        }
        if (para_req <= uVar5) {
          if ((byte *)((int)ppage + 0xf8U) <= pbVar6 + para_req) {
            *(int *)ppage = (int)ppage + 8;
            goto LAB_0048a6df;
          }
          *(byte **)ppage = pbVar6 + para_req;
          *(uint *)((int)ppage + 4) = uVar5 - para_req;
          goto LAB_0048a6e6;
        }
        if (pbVar6 == pbVar2) {
          *(uint *)((int)ppage + 4) = uVar5;
        }
        else {
          free_para_count = free_para_count - uVar5;
          if (free_para_count < para_req) {
            return;
          }
        }
      }
      else {
        pbVar3 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar3;
    } while (pbVar3 + para_req < (byte *)((int)ppage + 0xf8U));
  }
  pbVar3 = (byte *)((int)ppage + 8);
  pbVar6 = pbVar3;
  if (pbVar3 < pbVar2) {
    while (pbVar6 + para_req < (byte *)((int)ppage + 0xf8U)) {
      if (*pbVar6 == 0) {
        pbVar4 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = pbVar6[1];
        while (bVar1 == 0) {
          pbVar4 = pbVar4 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar4;
        }
        if (para_req <= uVar5) {
          if (pbVar6 + para_req < (byte *)((int)ppage + 0xf8U)) {
            *(byte **)ppage = pbVar6 + para_req;
            *(uint *)((int)ppage + 4) = uVar5 - para_req;
          }
          else {
            *(byte **)ppage = pbVar3;
LAB_0048a6df:
            *(undefined4 *)((int)ppage + 4) = 0;
          }
LAB_0048a6e6:
          *pbVar6 = (byte)para_req;
          return;
        }
        free_para_count = free_para_count - uVar5;
        if (free_para_count < para_req) {
          return;
        }
      }
      else {
        pbVar4 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar4;
      if (pbVar2 <= pbVar4) {
        return;
      }
    }
  }
  return;
}


/* ==== __sbh_resize_block @ 0048a710 ==== */

int __cdecl __sbh_resize_block(void *preg,void *ppage,void *pmap,uint new_para_sz)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  
  iVar5 = 0;
  piVar3 = (int *)((int)preg + ((int)ppage - *(int *)((int)preg + 0x10) >> 0xc) * 8 + 0x18);
  uVar6 = (uint)*(byte *)pmap;
  if (uVar6 <= new_para_sz) {
    if ((uVar6 < new_para_sz) &&
       (pcVar1 = (char *)(new_para_sz + (int)pmap), pcVar1 <= (char *)((int)ppage + 0xf8U))) {
      for (pcVar7 = (char *)(uVar6 + (int)pmap); (pcVar7 < pcVar1 && (*pcVar7 == '\0'));
          pcVar7 = pcVar7 + 1) {
      }
      if (pcVar7 == pcVar1) {
        *(char *)pmap = (char)new_para_sz;
        if ((pmap <= *(char **)ppage) && (*(char **)ppage < pcVar1)) {
          if (pcVar1 < (char *)((int)ppage + 0xf8U)) {
            *(char **)ppage = pcVar1;
            iVar5 = 0;
            cVar4 = *pcVar1;
            while (cVar4 == '\0') {
              iVar2 = iVar5 + 1;
              iVar5 = iVar5 + 1;
              cVar4 = pcVar1[iVar2];
            }
            *(int *)((int)ppage + 4) = iVar5;
          }
          else {
            *(undefined4 *)((int)ppage + 4) = 0;
            *(int *)ppage = (int)ppage + 8;
          }
        }
        *piVar3 = *piVar3 + (uVar6 - new_para_sz);
        iVar5 = 1;
      }
    }
    return iVar5;
  }
  *(char *)pmap = (char)new_para_sz;
  piVar3[1] = 0xf1;
  *piVar3 = *piVar3 + (uVar6 - new_para_sz);
  return 1;
}


/* ==== __loctotime_t @ 0048a7e0 ==== */

long __cdecl __loctotime_t(int yr,int mo,int dy,int hr,int mn,int sc,int dstflag)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_24 [8];
  int local_1c;
  int local_14;
  uint local_10;
  int local_8;
  
  uVar2 = yr - 0x76c;
  if (((int)uVar2 < 0x46) || (0x8a < (int)uVar2)) {
    return -1;
  }
  iVar3 = *(int *)(&DAT_004da8fc + mo * 4) + dy;
  if (((uVar2 & 3) == 0) && (2 < mo)) {
    iVar3 = iVar3 + 1;
  }
  __tzset();
  local_1c = hr;
  local_14 = mo + -1;
  iVar1 = sc + (mn + (hr + ((yr + -0x76d >> 2) + uVar2 * 0x16d + iVar3) * 0x18) * 0x3c) * 0x3c +
          0x7c558180 + _timezone;
  if (dstflag != 1) {
    if (dstflag != -1) {
      return iVar1;
    }
    if (_daylight == 0) {
      return iVar1;
    }
    local_10 = uVar2;
    local_8 = iVar3;
    iVar3 = _isindst(local_24);
    if (iVar3 == 0) {
      return iVar1;
    }
  }
  return iVar1 + _dstbias;
}


/* ==== _read @ 0048a8d0 ==== */

int __cdecl _read(int fh,void *buf,uint cnt)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  LPVOID lpBuffer;
  BOOL BVar4;
  DWORD DVar5;
  uint nNumberOfBytesToRead;
  int iVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  DWORD local_c;
  int *local_8;
  char *local_4;
  
  if ((uint)fh < _nhandle) {
    iVar6 = (fh & 0x1fU) * 8;
    piVar1 = &__pioinfo + (fh >> 5);
    local_c = iVar6 + (&__pioinfo)[fh >> 5];
    bVar3 = *(byte *)(local_c + 4);
    if ((bVar3 & 1) != 0) {
      iVar7 = 0;
      if ((cnt == 0) || ((bVar3 & 2) != 0)) {
        return 0;
      }
      lpBuffer = buf;
      nNumberOfBytesToRead = cnt;
      if (((bVar3 & 0x48) != 0) && (*(char *)(local_c + 5) != '\n')) {
        *(char *)buf = *(char *)(local_c + 5);
        lpBuffer = (LPVOID)((int)buf + 1);
        iVar7 = 1;
        nNumberOfBytesToRead = cnt - 1;
        *(undefined1 *)(iVar6 + 5 + *piVar1) = 10;
      }
      local_8 = piVar1;
      BVar4 = ReadFile(*(HANDLE *)(iVar6 + *piVar1),lpBuffer,nNumberOfBytesToRead,&local_c,
                       (LPOVERLAPPED)0x0);
      if (BVar4 == 0) {
        DVar5 = GetLastError();
        if (DVar5 == 5) {
          _doserrno = DVar5;
          errno = 9;
          return -1;
        }
        if (DVar5 == 0x6d) {
          return 0;
        }
        _dosmaperr(DVar5);
        return -1;
      }
      iVar7 = iVar7 + local_c;
      bVar3 = *(byte *)(iVar6 + 4 + *piVar1);
      if ((bVar3 & 0x80) != 0) {
        if ((local_c == 0) || (*(char *)buf != '\n')) {
          bVar3 = bVar3 & 0xfb;
        }
        else {
          bVar3 = bVar3 | 4;
        }
        *(byte *)(iVar6 + 4 + *piVar1) = bVar3;
        local_4 = (char *)(iVar7 + (int)buf);
        pcVar8 = buf;
        pcVar9 = buf;
        if (buf < local_4) {
          while (cVar2 = *pcVar9, cVar2 != '\x1a') {
            if (cVar2 == '\r') {
              if (pcVar9 < local_4 + -1) {
                if (pcVar9[1] == '\n') {
                  pcVar9 = pcVar9 + 2;
                  *pcVar8 = '\n';
                  goto LAB_0048aab8;
                }
                *pcVar8 = '\r';
                pcVar8 = pcVar8 + 1;
                pcVar9 = pcVar9 + 1;
              }
              else {
                DVar5 = 0;
                pcVar9 = pcVar9 + 1;
                BVar4 = ReadFile(*(HANDLE *)(iVar6 + *local_8),&cnt,1,&local_c,(LPOVERLAPPED)0x0);
                if (BVar4 == 0) {
                  DVar5 = GetLastError();
                }
                if ((DVar5 == 0) && (local_c != 0)) {
                  if ((*(byte *)(iVar6 + 4 + *local_8) & 0x48) == 0) {
                    if ((pcVar8 == buf) && ((char)cnt == '\n')) {
                      *pcVar8 = '\n';
                      goto LAB_0048aab8;
                    }
                    _lseek(fh,-1,1);
                    if ((char)cnt != '\n') goto LAB_0048aab5;
                  }
                  else {
                    if ((char)cnt == '\n') {
                      *pcVar8 = '\n';
                      goto LAB_0048aab8;
                    }
                    *pcVar8 = '\r';
                    pcVar8 = pcVar8 + 1;
                    *(char *)(iVar6 + 5 + *local_8) = (char)cnt;
                  }
                }
                else {
LAB_0048aab5:
                  *pcVar8 = '\r';
LAB_0048aab8:
                  pcVar8 = pcVar8 + 1;
                }
              }
            }
            else {
              *pcVar8 = cVar2;
              pcVar8 = pcVar8 + 1;
              pcVar9 = pcVar9 + 1;
            }
            if (local_4 <= pcVar9) {
              return (int)pcVar8 - (int)buf;
            }
          }
          bVar3 = *(byte *)(iVar6 + 4 + *local_8);
          if ((bVar3 & 0x40) == 0) {
            *(byte *)(iVar6 + 4 + *local_8) = bVar3 | 2;
          }
        }
        iVar7 = (int)pcVar8 - (int)buf;
      }
      return iVar7;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _getbuf @ 0048ab30 ==== */

void __cdecl _getbuf(void *stream)

{
  int extraout_EAX;
  
  _cflush = _cflush + 1;
  malloc(0x1000);
  *(int *)((int)stream + 8) = extraout_EAX;
  if (extraout_EAX != 0) {
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 8;
    *(undefined4 *)((int)stream + 0x18) = 0x1000;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(undefined4 *)((int)stream + 4) = 0;
    return;
  }
  *(undefined4 *)((int)stream + 0x18) = 2;
  *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) | 4;
  *(int *)((int)stream + 8) = (int)stream + 0x14;
  *(int *)stream = (int)stream + 0x14;
  *(undefined4 *)((int)stream + 4) = 0;
  return;
}


/* ==== _callnewh @ 0048ab90 ==== */

int __cdecl _callnewh(uint size)

{
  int iVar1;
  
  if (_pnhNewHandler != (code *)0x0) {
    iVar1 = (*_pnhNewHandler)(size);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}


/* ==== FUN_0048abb0 @ 0048abb0 ==== */

LPSTR __cdecl FUN_0048abb0(int param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4)

{
  byte bVar1;
  char cVar2;
  uchar uVar3;
  LPSTR pCVar4;
  byte *pbVar5;
  undefined3 extraout_var;
  byte *s;
  char *pcVar6;
  undefined3 extraout_var_00;
  byte *pbVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  byte *p;
  char *pcVar11;
  char *pcVar12;
  byte *pbVar13;
  
  p = (byte *)0x0;
  pCVar4 = FUN_0048ada0(param_1,param_2,param_3,param_4);
  if (((pCVar4 == (LPSTR)0xffffffff) && (errno == 2)) &&
     (pbVar5 = FUN_0048e3f0(param_2,0x2f), pbVar5 == (byte *)0x0)) {
    cVar2 = getenv("PATH");
    if ((char *)CONCAT31(extraout_var,cVar2) != (char *)0x0) {
      malloc(0x104);
      if (s == (byte *)0x0) {
        return (LPSTR)0xffffffff;
      }
      pcVar6 = (char *)FUN_0048e350((char *)CONCAT31(extraout_var,cVar2),(char *)s,0x103);
      while ((p = s, pcVar6 != (char *)0x0 && (*s != 0))) {
        uVar8 = 0xffffffff;
        pbVar5 = s;
        do {
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar5 + 1;
        } while (bVar1 != 0);
        if (s[~uVar8 - 2] == 0x5c) {
          uVar3 = _mbsrchr(s,0x5c);
          if (s + (~uVar8 - 2) != (byte *)CONCAT31(extraout_var_00,uVar3)) {
LAB_0048ac7d:
            uVar8 = 0xffffffff;
            pcVar11 = (char *)&DAT_004c5cd4;
            do {
              pcVar12 = pcVar11;
              if (uVar8 == 0) break;
              uVar8 = uVar8 - 1;
              pcVar12 = pcVar11 + 1;
              cVar2 = *pcVar11;
              pcVar11 = pcVar12;
            } while (cVar2 != '\0');
            uVar8 = ~uVar8;
            iVar9 = -1;
            pbVar5 = s;
            do {
              pbVar7 = pbVar5;
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              pbVar7 = pbVar5 + 1;
              bVar1 = *pbVar5;
              pbVar5 = pbVar7;
            } while (bVar1 != 0);
            pbVar5 = (byte *)(pcVar12 + -uVar8);
            pbVar7 = pbVar7 + -1;
            for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *(undefined4 *)pbVar7 = *(undefined4 *)pbVar5;
              pbVar5 = pbVar5 + 4;
              pbVar7 = pbVar7 + 4;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pbVar7 = *pbVar5;
              pbVar5 = pbVar5 + 1;
              pbVar7 = pbVar7 + 1;
            }
          }
        }
        else if (s[~uVar8 - 2] != 0x2f) goto LAB_0048ac7d;
        uVar8 = 0xffffffff;
        pbVar5 = s;
        do {
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar5 + 1;
        } while (bVar1 != 0);
        uVar10 = 0xffffffff;
        pbVar5 = param_2;
        do {
          if (uVar10 == 0) break;
          uVar10 = uVar10 - 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar5 + 1;
        } while (bVar1 != 0);
        if (0x103 < ~uVar8 + (~uVar10 - 2)) break;
        uVar8 = 0xffffffff;
        pbVar5 = param_2;
        do {
          pbVar7 = pbVar5;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pbVar7 = pbVar5 + 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar7;
        } while (bVar1 != 0);
        uVar8 = ~uVar8;
        iVar9 = -1;
        pbVar5 = s;
        do {
          pbVar13 = pbVar5;
          if (iVar9 == 0) break;
          iVar9 = iVar9 + -1;
          pbVar13 = pbVar5 + 1;
          bVar1 = *pbVar5;
          pbVar5 = pbVar13;
        } while (bVar1 != 0);
        pbVar5 = pbVar7 + -uVar8;
        pbVar7 = pbVar13 + -1;
        for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pbVar7 = *(undefined4 *)pbVar5;
          pbVar5 = pbVar5 + 4;
          pbVar7 = pbVar7 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pbVar7 = *pbVar5;
          pbVar5 = pbVar5 + 1;
          pbVar7 = pbVar7 + 1;
        }
        pCVar4 = FUN_0048ada0(param_1,s,param_3,param_4);
        if (pCVar4 != (LPSTR)0xffffffff) break;
        if (errno != 2) {
          pbVar5 = FUN_0048e3f0(s,0x5c);
          if ((s != pbVar5) && (pbVar5 = FUN_0048e3f0(s,0x2f), s != pbVar5)) break;
          pbVar5 = s + 1;
          pbVar7 = FUN_0048e3f0(pbVar5,0x5c);
          if ((pbVar5 != pbVar7) && (pbVar7 = FUN_0048e3f0(pbVar5,0x2f), pbVar5 != pbVar7)) break;
        }
        pcVar6 = (char *)FUN_0048e350(pcVar6,(char *)s,0x103);
      }
    }
  }
  if (p != (byte *)0x0) {
    free(p);
  }
  return pCVar4;
}


/* ==== FUN_0048ada0 @ 0048ada0 ==== */

LPSTR __cdecl FUN_0048ada0(int param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4)

{
  byte bVar1;
  char cVar2;
  uchar uVar3;
  undefined3 extraout_var;
  byte *pbVar4;
  byte *pbVar5;
  byte *extraout_EAX;
  undefined3 extraout_var_01;
  byte *path;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined **ppuVar10;
  byte *pbVar11;
  char *pcVar12;
  char *pcVar13;
  byte *local_c;
  LPSTR local_8;
  undefined3 extraout_var_00;
  
  local_c = param_2;
  uVar3 = _mbsrchr(param_2,0x5c);
  pbVar5 = (byte *)CONCAT31(extraout_var,uVar3);
  uVar3 = _mbsrchr(param_2,0x2f);
  pbVar4 = (byte *)CONCAT31(extraout_var_00,uVar3);
  if (pbVar4 == (byte *)0x0) {
    if ((pbVar5 == (byte *)0x0) && (pbVar5 = FUN_0048e3f0(param_2,0x3a), pbVar5 == (byte *)0x0)) {
      uVar6 = 0xffffffff;
      pbVar5 = param_2;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        bVar1 = *pbVar5;
        pbVar5 = pbVar5 + 1;
      } while (bVar1 != 0);
      malloc(~uVar6 + 2);
      if (extraout_EAX == (byte *)0x0) {
        return (LPSTR)0xffffffff;
      }
      extraout_EAX[0] = 0x2e;
      extraout_EAX[1] = 0x5c;
      extraout_EAX[2] = 0;
      uVar6 = 0xffffffff;
      pbVar5 = param_2;
      do {
        pbVar4 = pbVar5;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pbVar4 = pbVar5 + 1;
        bVar1 = *pbVar5;
        pbVar5 = pbVar4;
      } while (bVar1 != 0);
      uVar6 = ~uVar6;
      iVar7 = -1;
      pbVar5 = extraout_EAX;
      do {
        pbVar11 = pbVar5;
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pbVar11 = pbVar5 + 1;
        bVar1 = *pbVar5;
        pbVar5 = pbVar11;
      } while (bVar1 != 0);
      pbVar5 = pbVar4 + -uVar6;
      pbVar4 = pbVar11 + -1;
      for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pbVar4 = *(undefined4 *)pbVar5;
        pbVar5 = pbVar5 + 4;
        pbVar4 = pbVar4 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar4 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        pbVar4 = pbVar4 + 1;
      }
      pbVar5 = extraout_EAX + 2;
      local_c = extraout_EAX;
    }
  }
  else if ((pbVar5 == (byte *)0x0) || (pbVar5 < pbVar4)) {
    pbVar5 = pbVar4;
  }
  local_8 = (LPSTR)0xffffffff;
  uVar3 = _mbsrchr(pbVar5,0x2e);
  if (CONCAT31(extraout_var_01,uVar3) == 0) {
    uVar6 = 0xffffffff;
    pbVar5 = local_c;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      bVar1 = *pbVar5;
      pbVar5 = pbVar5 + 1;
    } while (bVar1 != 0);
    malloc(~uVar6 + 4);
    if (path == (byte *)0x0) {
      return (LPSTR)0xffffffff;
    }
    uVar6 = 0xffffffff;
    pbVar5 = local_c;
    do {
      pbVar4 = pbVar5;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pbVar4 = pbVar5 + 1;
      bVar1 = *pbVar5;
      pbVar5 = pbVar4;
    } while (bVar1 != 0);
    uVar6 = ~uVar6;
    pbVar5 = pbVar4 + -uVar6;
    pbVar4 = path;
    for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pbVar4 = *(undefined4 *)pbVar5;
      pbVar5 = pbVar5 + 4;
      pbVar4 = pbVar4 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar4 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      pbVar4 = pbVar4 + 1;
    }
    uVar6 = 0xffffffff;
    pbVar5 = local_c;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      bVar1 = *pbVar5;
      pbVar5 = pbVar5 + 1;
    } while (bVar1 != 0);
    ppuVar10 = &PTR_DAT_004da4cc;
    do {
      uVar8 = 0xffffffff;
      pcVar12 = *ppuVar10;
      do {
        pcVar13 = pcVar12;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pcVar13 = pcVar12 + 1;
        cVar2 = *pcVar12;
        pcVar12 = pcVar13;
      } while (cVar2 != '\0');
      uVar8 = ~uVar8;
      pbVar5 = (byte *)(pcVar13 + -uVar8);
      pbVar4 = path + (~uVar6 - 1);
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pbVar4 = *(undefined4 *)pbVar5;
        pbVar5 = pbVar5 + 4;
        pbVar4 = pbVar4 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pbVar4 = *pbVar5;
        pbVar5 = pbVar5 + 1;
        pbVar4 = pbVar4 + 1;
      }
      iVar7 = _access((char *)path,0);
      if (iVar7 != -1) {
        local_8 = FUN_0048afa0(param_1,(LPCSTR)path,param_3,param_4);
        break;
      }
      ppuVar10 = ppuVar10 + -1;
    } while (0x4da4bf < (int)ppuVar10);
    free(path);
  }
  else {
    iVar7 = _access((char *)local_c,0);
    if (iVar7 != -1) {
      local_8 = FUN_0048afa0(param_1,(LPCSTR)local_c,param_3,param_4);
    }
  }
  if (local_c != param_2) {
    free(local_c);
  }
  return local_8;
}


/* ==== FUN_0048afa0 @ 0048afa0 ==== */

LPSTR __cdecl FUN_0048afa0(int param_1,LPCSTR param_2,undefined4 *param_3,undefined4 *param_4)

{
  LPCSTR pCVar1;
  int iVar2;
  LPSTR pCVar3;
  
  pCVar1 = param_2;
  iVar2 = FUN_0048e720(&param_2,param_3,param_4,(int *)&param_2,(int *)&param_4);
  if (iVar2 == -1) {
    return (LPSTR)0xffffffff;
  }
  pCVar3 = FUN_0048e4a0(param_1,pCVar1,param_2,param_4);
  free(param_2);
  free(param_4);
  return pCVar3;
}


/* ==== _strnicoll @ 0048b010 ==== */

int __cdecl _strnicoll(char *a,char *b,uint n)

{
  int iVar1;
  
  if (n == 0) {
    return 0;
  }
  iVar1 = __crtCompareStringA(DAT_00505590,1,a,n,b,n,DAT_0050558c);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}


/* ==== __wtomb_environ @ 0048b050 ==== */

int __wtomb_environ(void)

{
  LPCWSTR lpWideCharStr;
  uint size;
  char *lpMultiByteStr;
  int iVar1;
  int *piVar2;
  
  lpWideCharStr = (LPCWSTR)*_wenviron;
  piVar2 = _wenviron;
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return 0;
  }
  while (((size = WideCharToMultiByte(1,0,lpWideCharStr,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0),
          size != 0 && (malloc(size), lpMultiByteStr != (char *)0x0)) &&
         (iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*piVar2,-1,lpMultiByteStr,size,(LPCSTR)0x0,
                                      (LPBOOL)0x0), iVar1 != 0))) {
    __crtsetenv(lpMultiByteStr,0);
    lpWideCharStr = (LPCWSTR)piVar2[1];
    piVar2 = piVar2 + 1;
    if (lpWideCharStr == (LPCWSTR)0x0) {
      return 0;
    }
  }
  return -1;
}


/* ==== _fltin2 @ 0048b0d0 ==== */

void __cdecl _fltin2(void *flt,char *str,int len_ignore,int scale,int decpt)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined1 local_c [12];
  
  pvVar1 = flt;
  uVar4 = 0;
  uVar2 = __strgtold12(local_c,&flt,flt,0,0,0,0);
  if ((uVar2 & 4) == 0) {
    iVar3 = _ld12tod(local_c,(double *)&local_14);
    if (((uVar2 & 2) != 0) || (iVar3 == 1)) {
      uVar4 = 0x80;
    }
    if (((uVar2 & 1) != 0) || (iVar3 == 2)) {
      uVar4 = uVar4 | 0x100;
    }
  }
  else {
    uVar4 = 0x200;
    local_14 = 0;
    uStack_10 = 0;
  }
  *(uint *)PTR_DAT_004da4d8 = uVar4;
  *(int *)(PTR_DAT_004da4d8 + 4) = (int)flt - (int)pvVar1;
  *(ulonglong *)(PTR_DAT_004da4d8 + 0x10) = CONCAT44(uStack_10,local_14);
  return;
}


/* ==== __cintrindisp2 @ 0048b180 ==== */

/* Library Function - Single Match
    __cintrindisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __cintrindisp2(undefined4 param_1,int param_2)

{
  __trandisp2(param_1,param_2);
  DAT_00505638 = 1;
  FUN_0048b235();
  return;
}


/* ==== __cintrindisp1 @ 0048b1be ==== */

/* Library Function - Single Match
    __cintrindisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __cintrindisp1(undefined4 param_1,int param_2)

{
  __trandisp1(param_1,param_2);
  DAT_00505638 = 1;
  FUN_0048b235();
  return;
}


/* ==== __ctrandisp2 @ 0048b1f4 ==== */

/* Library Function - Single Match
    __ctrandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cdecl __ctrandisp2(uint param_1,int param_2,uint param_3,int param_4)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2(extraout_ECX,extraout_EDX);
  FUN_0048b22e();
  return;
}


/* ==== FUN_0048b22e @ 0048b22e ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048b22e(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  DAT_00505638 = '\0';
  if (DAT_005052c8 != 0) {
    DAT_00505638 = 0;
    return;
  }
  _DAT_00505630 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        DAT_00505638 = 0;
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_0048b303;
    }
    if (((ulonglong)_DAT_00505630 & 0x7ff0000000000000) == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_0048b303;
    }
    if ((DAT_00505636 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_0048b303;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    DAT_00505638 = 0;
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    DAT_00505638 = 0;
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_0048b303:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_00505638 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_0048f770((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
               (ushort *)(unaff_EBP + -0xa4));
  return;
}


/* ==== FUN_0048b235 @ 0048b235 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048b235(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  if (DAT_005052c8 != 0) {
    return;
  }
  _DAT_00505630 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_0048b303;
    }
    if (((ulonglong)_DAT_00505630 & 0x7ff0000000000000) == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_0048b303;
    }
    if ((DAT_00505636 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_0048b303;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_0048b303:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_00505638 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_0048f770((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),(int *)(unaff_EBP + -0x8e),
               (ushort *)(unaff_EBP + -0xa4));
  return;
}


/* ==== __ctrandisp1 @ 0048b365 ==== */

/* Library Function - Single Match
    __ctrandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cdecl __ctrandisp1(uint param_1,int param_2)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  
  __fload(param_1,param_2);
  __trandisp1(extraout_ECX,extraout_EDX);
  FUN_0048b22e();
  return;
}


/* ==== __fload @ 0048b391 ==== */

/* Library Function - Single Match
    __fload
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

float10 __cdecl __fload(uint param_1,int param_2)

{
  float10 fVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    fVar1 = (float10)CONCAT28(param_2._2_2_ | 0x7fff,
                              CONCAT44(param_2 << 0xb | param_1 >> 0x15,param_1));
  }
  else {
    fVar1 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  return fVar1;
}


/* ==== __trandisp1 @ 0048b3d0 ==== */

/* Library Function - Single Match
    __trandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __trandisp1(undefined4 param_1,int param_2)

{
  float10 fVar1;
  byte bVar2;
  undefined2 uVar3;
  int unaff_EBP;
  float10 in_ST0;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar3 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar3 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar3;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  bVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0048b435. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_2 + (char)(&DAT_004da4fd)[(byte)((bVar2 & 7) << 1 | (char)bVar2 < '\0')] + 0x10
              ))();
  return;
}


/* ==== __trandisp2 @ 0048b437 ==== */

/* Library Function - Single Match
    __trandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __fastcall __trandisp2(undefined4 param_1,int param_2)

{
  float10 fVar1;
  char cVar2;
  byte bVar3;
  undefined2 uVar4;
  int unaff_EBP;
  float10 in_ST0;
  float10 in_ST1;
  
  if (*(char *)(param_2 + 0xe) == '\x05') {
    uVar4 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar4 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar4;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = param_2;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST1) << 8 | (ushort)(in_ST1 < fVar1) << 9 | (ushort)(in_ST1 != fVar1) << 10 |
       (ushort)(in_ST1 == fVar1) << 0xe;
  bVar3 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
  cVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0048b4c1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_2 + (char)((&DAT_004da4fd)[(byte)(cVar2 << 1 | cVar2 < '\0') & 0xf] |
                               (&DAT_004da4fd)[(byte)((bVar3 & 7) << 1 | (char)bVar3 < '\0')] << 2)
              + 0x10))();
  return;
}


/* ==== FUN_0048bda6 @ 0048bda6 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl FUN_0048bda6(undefined4 param_1,uint param_2,ushort param_3)

{
  undefined4 in_EAX;
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 in_stack_0000001c;
  undefined2 in_stack_00000020;
  undefined2 in_stack_00000022;
  ushort in_stack_00000024;
  
  if ((((((CONCAT22(param_3,param_2._2_2_) ^ 0x700) & 0x700) == 0) &&
       ((&DAT_004da52c)[(param_2._2_2_ & 0x7800) >> 0xb] != '\0')) && ((param_3 & 0x7fff) != 0x7fff)
      ) && ((((in_stack_00000024 & 0x7fff) != 0 && ((in_stack_00000024 & 0x7fff) != 0x7fff)) &&
            (((CONCAT22(in_stack_00000022,in_stack_00000020) & 0x7fffffff) == 0 &&
             ((param_2 & 0x7fffffff) == 0)))))) {
    if ((ushort)((param_3 & 0x7fff) + 0x3f) < (in_stack_00000024 & 0x7fff)) {
      iVar1 = ((in_stack_00000024 & 0x7fff) - (param_3 & 0x7fff) & 0x3f | 0x20) + 1;
      fVar3 = ABS((float10)CONCAT28(in_stack_00000024 & 0x7fff | param_3 & 0x8000,
                                    CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))));
      fVar2 = ABS((float10)CONCAT28(in_stack_00000024,
                                    CONCAT26(in_stack_00000022,
                                             CONCAT24(in_stack_00000020,in_stack_0000001c))));
      do {
        if (fVar3 <= fVar2) {
          fVar2 = fVar2 - fVar3;
        }
        fVar3 = fVar3 * (float10)_DAT_004da55c;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    else {
      while (-1 < (int)((in_stack_00000024 & 0x7fff) - ((param_3 & 0x7fff) + 10))) {
        fVar2 = (float10)CONCAT28(in_stack_00000024,
                                  CONCAT26(in_stack_00000022,
                                           CONCAT24(in_stack_00000020,in_stack_0000001c)));
        fVar3 = (float10)CONCAT28((in_stack_00000024 & 0x7fff) -
                                  ((in_stack_00000024 & 0x7fff) - param_3 & 7 | 4) |
                                  param_3 & 0x8000,
                                  CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)));
        fVar2 = fVar2 - (float10)(unkint10)(fVar2 / fVar3) * fVar3;
        in_stack_0000001c = SUB104(fVar2,0);
        in_stack_00000020 = (undefined2)((unkuint10)fVar2 >> 0x20);
        in_stack_00000022 = (undefined2)((unkuint10)fVar2 >> 0x30);
        in_stack_00000024 = (ushort)((unkuint10)fVar2 >> 0x40);
      }
    }
  }
  return in_EAX;
}


/* ==== _adj_fprem @ 0048bfac ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _adj_fprem(void)

{
  uint va7;
  undefined2 in_FPUControlWord;
  float10 in_ST0;
  float10 fVar1;
  float10 in_ST1;
  int va0;
  uint va1;
  ushort uVar2;
  undefined4 in_stack_ffffffd8;
  undefined4 in_stack_ffffffdc;
  undefined2 in_stack_ffffffe0;
  undefined2 in_stack_ffffffe2;
  undefined4 va3;
  undefined4 va4;
  ushort uVar3;
  undefined2 in_stack_ffffffee;
  undefined4 in_stack_fffffff0;
  uint va6;
  undefined4 in_stack_fffffff4;
  undefined4 in_stack_fffffff8;
  undefined2 uVar4;
  
  va3 = SUB104(in_ST0,0);
  va4 = (undefined4)((unkuint10)in_ST0 >> 0x20);
  uVar3 = (ushort)((unkuint10)in_ST0 >> 0x40);
  va0 = SUB104(in_ST1,0);
  va1 = (uint)((unkuint10)in_ST1 >> 0x20);
  uVar2 = (ushort)((unkuint10)in_ST1 >> 0x40);
  if (((uint)((unkuint10)in_ST1 >> 0x30) & 0x7fff0000) != 0) {
    FUN_0048bda6(va0,va1,uVar2,in_stack_ffffffd8,in_stack_ffffffdc,
                 CONCAT22(in_stack_ffffffe2,in_stack_ffffffe0),va3,va4,
                 CONCAT22(in_stack_ffffffee,uVar3),in_stack_fffffff0,in_stack_fffffff4,
                 in_stack_fffffff8);
    return;
  }
  if (va0 != 0 || va1 != 0) {
    uVar4 = (undefined2)((uint)in_stack_fffffff0 >> 0x10);
    va6 = CONCAT22(uVar4,in_FPUControlWord);
    va7 = va6 | 0x33f;
    if ((uVar3 & 0x7fff) < 0x7fbf) {
      fVar1 = in_ST0 * (float10)_DAT_004da544;
      va3 = SUB104(fVar1,0);
      va4 = (undefined4)((unkuint10)fVar1 >> 0x20);
      uVar3 = (ushort)((unkuint10)fVar1 >> 0x40);
    }
    else {
      va6 = CONCAT22(uVar4,(short)va7);
      va7 = va6 | 0x300;
    }
    fVar1 = in_ST1 * (float10)_DAT_004da544;
    FUN_0048bda6(SUB104(fVar1,0),(uint)((unkuint10)fVar1 >> 0x20),(ushort)((unkuint10)fVar1 >> 0x40)
                 ,va0,va1,CONCAT22(in_stack_ffffffe2,uVar2),va3,va4,
                 CONCAT22(in_stack_ffffffee,uVar3),va6,va7,in_stack_fffffff8);
    return;
  }
  return;
}


/* ==== calloc @ 0048c330 ==== */

void __cdecl calloc(uint num,uint size)

{
  undefined4 *extraout_EAX;
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint dwBytes;
  undefined4 *puVar4;
  
  dwBytes = size * num;
  if (dwBytes < 0xffffffe1) {
    if (dwBytes == 0) {
      dwBytes = 0x10;
    }
    else {
      dwBytes = dwBytes + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar3 = (undefined4 *)0x0;
    if (dwBytes < 0xffffffe1) {
      if (__sbh_threshold < dwBytes) {
LAB_0048c390:
        if (puVar3 != (undefined4 *)0x0) {
          return;
        }
      }
      else {
        __sbh_alloc_block(dwBytes >> 4);
        if (extraout_EAX != (undefined4 *)0x0) {
          puVar4 = extraout_EAX;
          for (uVar2 = dwBytes >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          for (uVar2 = dwBytes & 3; puVar3 = extraout_EAX, uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar4 = 0;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
          goto LAB_0048c390;
        }
      }
      puVar3 = HeapAlloc(_crtheap,8,dwBytes);
    }
    if ((puVar3 != (undefined4 *)0x0) || (_newmode == 0)) {
      return;
    }
    iVar1 = _callnewh(dwBytes);
    if (iVar1 == 0) {
      return;
    }
  } while( true );
}


/* ==== _dosmaperr @ 0048c440 ==== */

void __cdecl _dosmaperr(ulong oserrno)

{
  ulong *puVar1;
  int iVar2;
  
  _doserrno = oserrno;
  iVar2 = 0;
  puVar1 = &DAT_004da670;
  do {
    if (oserrno == *puVar1) {
      errno = *(undefined4 *)(iVar2 * 8 + 0x4da674);
      return;
    }
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + 1;
  } while (puVar1 < &DAT_004da7d8);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    errno = 0xd;
    return;
  }
  if ((oserrno < 0xbc) || (errno = 8, 0xca < oserrno)) {
    errno = 0x16;
  }
  return;
}


/* ==== __allmul @ 0048c4b0 ==== */

/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio */

longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}


/* ==== FUN_0048c4f0 @ 0048c4f0 ==== */

void FUN_0048c4f0(void)

{
  undefined4 uVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [16];
  
  uVar1 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = local_14;
  *unaff_FS_OFFSET = uVar1;
  return;
}


/* ==== asctime @ 0048c560 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char __cdecl asctime(void *tm)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  
  iVar1 = *(int *)((int)tm + 0x18) * 3;
  DAT_00505643 = 0x20;
  DAT_00505647 = 0x20;
  iVar2 = *(int *)((int)tm + 0x10) * 3;
  _DAT_00505644 = *(undefined2 *)("JanFebMarAprMayJunJulAugSepOctNovDec" + iVar2);
  _DAT_00505640 = *(undefined2 *)("SunMonTueWedThuFriSat" + iVar1);
  DAT_00505646 = "JanFebMarAprMayJunJulAugSepOctNovDec"[iVar2 + 2];
  DAT_00505642 = "SunMonTueWedThuFriSat"[iVar1 + 2];
  cVar3 = store_dt(&DAT_00505648,*(int *)((int)tm + 0xc));
  *(undefined1 *)CONCAT31(extraout_var,cVar3) = 0x20;
  cVar3 = store_dt((undefined1 *)CONCAT31(extraout_var,cVar3) + 1,*(int *)((int)tm + 8));
  *(undefined1 *)CONCAT31(extraout_var_00,cVar3) = 0x3a;
  cVar3 = store_dt((undefined1 *)CONCAT31(extraout_var_00,cVar3) + 1,*(int *)((int)tm + 4));
  *(undefined1 *)CONCAT31(extraout_var_01,cVar3) = 0x3a;
  cVar3 = store_dt((undefined1 *)CONCAT31(extraout_var_01,cVar3) + 1,*(int *)tm);
  *(undefined1 *)CONCAT31(extraout_var_02,cVar3) = 0x20;
  cVar3 = store_dt((undefined1 *)CONCAT31(extraout_var_02,cVar3) + 1,
                   *(int *)((int)tm + 0x14) / 100 + 0x13);
  cVar3 = store_dt((char *)CONCAT31(extraout_var_03,cVar3),*(int *)((int)tm + 0x14) % 100);
  *(undefined1 *)CONCAT31(extraout_var_04,cVar3) = 10;
  ((undefined1 *)CONCAT31(extraout_var_04,cVar3))[1] = 0;
  return '@';
}


/* ==== store_dt @ 0048c650 ==== */

char __cdecl store_dt(char *p,int val)

{
  *p = (((char)(val / 10) + (char)(val >> 0x1f)) - (char)((longlong)val * 0x66666667 >> 0x3f)) + '0'
  ;
  p[1] = (char)(val % 10) + '0';
  return (char)p + '\x02';
}


/* ==== localtime @ 0048c690 ==== */

void __cdecl localtime(long *timer)

{
  long *timer_00;
  void *tb;
  int iVar1;
  int extraout_EAX;
  int *tb_00;
  int iVar2;
  
  timer_00 = timer;
  if (*timer < 0) {
    return;
  }
  __tzset();
  iVar1 = *timer_00;
  if ((iVar1 < 0x3f481) || (0x7ffc0b7e < iVar1)) {
    gmtime(timer_00);
    iVar2 = _isindst(tb_00);
    iVar1 = *tb_00;
    if (iVar2 != 0) {
      iVar1 = iVar1 - _dstbias;
    }
    timer = (long *)(iVar1 - _timezone);
    iVar1 = (int)timer % 0x3c;
    *tb_00 = iVar1;
    if (iVar1 < 0) {
      *tb_00 = iVar1 + 0x3c;
      timer = timer + -0xf;
    }
    timer = (long *)((int)timer / 0x3c + tb_00[1]);
    iVar1 = (int)timer % 0x3c;
    tb_00[1] = iVar1;
    if (iVar1 < 0) {
      tb_00[1] = iVar1 + 0x3c;
      timer = timer + -0xf;
    }
    timer = (long *)((int)timer / 0x3c + tb_00[2]);
    iVar1 = (int)timer % 0x18;
    tb_00[2] = iVar1;
    if (iVar1 < 0) {
      tb_00[2] = iVar1 + 0x18;
      timer = timer + -6;
    }
    iVar1 = (int)timer / 0x18;
    if (0 < iVar1) {
      tb_00[6] = (iVar1 + tb_00[6]) % 7;
      tb_00[3] = tb_00[3] + iVar1;
      tb_00[7] = tb_00[7] + iVar1;
      return;
    }
    if (iVar1 < 0) {
      tb_00[6] = (iVar1 + 7 + tb_00[6]) % 7;
      iVar2 = tb_00[3] + iVar1;
      tb_00[3] = iVar2;
      if (iVar2 < 1) {
        tb_00[7] = 0x16c;
        tb_00[3] = iVar2 + 0x1f;
        tb_00[4] = 0xb;
        tb_00[5] = tb_00[5] + -1;
        return;
      }
      tb_00[7] = tb_00[7] + iVar1;
    }
  }
  else {
    timer = (long *)(iVar1 - _timezone);
    gmtime((long *)&timer);
    if (_daylight != 0) {
      iVar1 = _isindst(tb);
      if (iVar1 != 0) {
        timer = (long *)((int)timer - _dstbias);
        gmtime((long *)&timer);
        *(undefined4 *)(extraout_EAX + 0x20) = 1;
        return;
      }
    }
  }
  return;
}


/* ==== FUN_0048c880 @ 0048c880 ==== */

int __cdecl FUN_0048c880(short *param_1)

{
  short sVar1;
  short *psVar2;
  
  sVar1 = *param_1;
  psVar2 = param_1;
  while (psVar2 = psVar2 + 1, sVar1 != 0) {
    sVar1 = *psVar2;
  }
  return ((int)psVar2 - (int)param_1 >> 1) + -1;
}


/* ==== __crtMessageBoxA @ 0048c8a0 ==== */

int __cdecl __crtMessageBoxA(char *text,char *caption,uint type)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_0050565c != (FARPROC)0x0) {
LAB_0048c8f0:
    if (DAT_00505660 != (FARPROC)0x0) {
      iVar1 = (*DAT_00505660)();
    }
    if ((iVar1 != 0) && (DAT_00505664 != (FARPROC)0x0)) {
      iVar1 = (*DAT_00505664)(iVar1);
    }
    iVar1 = (*DAT_0050565c)(iVar1,text,caption,type);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_0050565c = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_0050565c != (FARPROC)0x0) {
      DAT_00505660 = GetProcAddress(hModule,"GetActiveWindow");
      DAT_00505664 = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_0048c8f0;
    }
  }
  return 0;
}


/* ==== _isatty @ 0048c930 ==== */

int __cdecl _isatty(int fh)

{
  if (_nhandle <= (uint)fh) {
    return 0;
  }
  return *(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 0x40;
}


/* ==== wctomb @ 0048c960 ==== */

int __cdecl wctomb(char *s,ushort wc)

{
  char *lpMultiByteStr;
  int iVar1;
  
  lpMultiByteStr = s;
  if (s == (char *)0x0) {
    return 0;
  }
  if (DAT_005055d0 == 0) {
    if (wc < 0x100) {
      *s = (char)wc;
      return 1;
    }
  }
  else {
    s = (char *)0x0;
    iVar1 = WideCharToMultiByte(DAT_005055e0,0x220,(LPCWSTR)&wc,1,lpMultiByteStr,__mb_cur_max,
                                (LPCSTR)0x0,(LPBOOL)&s);
    if ((iVar1 != 0) && (s == (char *)0x0)) {
      return iVar1;
    }
  }
  errno = 0x2a;
  return -1;
}


/* ==== __aulldiv @ 0048c9e0 ==== */

/* Library Function - Single Match
    __aulldiv
   
   Library: Visual Studio */

undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}


/* ==== __aullrem @ 0048ca50 ==== */

/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio */

undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = param_1;
  uVar9 = param_4;
  uVar10 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar10 >> 1;
      uVar4 = (uint)(CONCAT14((uVar10 & 1) != 0,uVar4) >> 1);
      uVar9 = uVar5;
      uVar10 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}


/* ==== FUN_0048cad0 @ 0048cad0 ==== */

uint __thiscall FUN_0048cad0(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_0048cb30(local_8);
  uVar1 = param_2 & param_1 | ~param_2 & uVar1;
  FUN_0048cbd0(uVar1);
  return uVar1;
}


/* ==== FUN_0048cb10 @ 0048cb10 ==== */

void __cdecl FUN_0048cb10(void *param_1,uint param_2)

{
  FUN_0048cad0(param_1,(uint)param_1,param_2 & 0xfff7ffff);
  return;
}


/* ==== FUN_0048cb30 @ 0048cb30 ==== */

uint __cdecl FUN_0048cb30(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 < 0x401) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
  }
  else if (uVar2 == 0x800) {
    uVar1 = uVar1 | 0x200;
  }
  else if (uVar2 == 0xc00) {
    uVar1 = uVar1 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}


/* ==== FUN_0048cbd0 @ 0048cbd0 ==== */

void FUN_0048cbd0(void)

{
  return;
}


/* ==== FUN_0048cc60 @ 0048cc60 ==== */

undefined4 __cdecl FUN_0048cc60(int param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if ((*(uint *)(param_1 + iVar3 * 4) &
      ~(-1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f))) != 0) {
    return 0;
  }
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    piVar2 = (int *)(param_1 + iVar3 * 4);
    do {
      if (*piVar2 != 0) {
        return 0;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 3);
    return 1;
  }
  return 1;
}


/* ==== FUN_0048ccd0 @ 0048ccd0 ==== */

void __cdecl FUN_0048ccd0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  bVar1 = (byte)(param_2 >> 0x1f);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  iVar2 = FUN_0048f9f0(*(uint *)(param_1 + iVar3 * 4),
                       1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) &
                            0x1f),(uint *)(param_1 + iVar3 * 4));
  iVar3 = iVar3 + -1;
  if (-1 < iVar3) {
    puVar4 = (uint *)(param_1 + iVar3 * 4);
    do {
      if (iVar2 == 0) {
        return;
      }
      iVar2 = FUN_0048f9f0(*puVar4,1,puVar4);
      iVar3 = iVar3 + -1;
      puVar4 = puVar4 + -1;
    } while (-1 < iVar3);
  }
  return;
}


/* ==== FUN_0048cd40 @ 0048cd40 ==== */

undefined4 __cdecl FUN_0048cd40(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_4;
  
  local_4 = 0;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  if (((*(uint *)(param_1 + iVar3 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_0048cc60(param_1,param_2 + 1), iVar1 == 0)) {
    local_4 = FUN_0048ccd0(param_1,param_2 + -1);
  }
  *(uint *)(param_1 + iVar3 * 4) = *(uint *)(param_1 + iVar3 * 4) & -1 << (bVar2 & 0x1f);
  iVar3 = iVar3 + 1;
  if (iVar3 < 3) {
    puVar4 = (undefined4 *)(param_1 + iVar3 * 4);
    for (iVar1 = 3 - iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
  }
  return local_4;
}


/* ==== FUN_0048cde0 @ 0048cde0 ==== */

void __cdecl FUN_0048cde0(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 - (int)param_2;
  iVar2 = 3;
  do {
    *(undefined4 *)((int)param_2 + iVar1) = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* ==== FUN_0048ce00 @ 0048ce00 ==== */

void __cdecl FUN_0048ce00(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


/* ==== FUN_0048ce10 @ 0048ce10 ==== */

undefined4 __cdecl FUN_0048ce10(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*param_1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 1;
  } while (iVar1 < 3);
  return 1;
}


/* ==== FUN_0048ce30 @ 0048ce30 ==== */

void __cdecl FUN_0048ce30(uint *param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  
  iVar1 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  uVar5 = 0;
  bVar2 = (((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2;
  param_2 = 3;
  puVar6 = param_1;
  do {
    uVar4 = *puVar6 >> (bVar2 & 0x1f) | uVar5;
    uVar5 = (~(-1 << (bVar2 & 0x1f)) & *puVar6) << (0x20 - bVar2 & 0x1f);
    *puVar6 = uVar4;
    param_2 = param_2 + -1;
    puVar6 = puVar6 + 1;
  } while (param_2 != 0);
  iVar7 = 2;
  iVar3 = 8;
  do {
    if (iVar7 < iVar1) {
      *(undefined4 *)((int)param_1 + iVar3) = 0;
    }
    else {
      *(undefined4 *)((int)param_1 + iVar3) = *(undefined4 *)((int)param_1 + iVar3 + iVar1 * -4);
    }
    iVar7 = iVar7 + -1;
    iVar3 = iVar3 + -4;
  } while (-1 < iVar3);
  return;
}


/* ==== FUN_0048cef0 @ 0048cef0 ==== */

undefined4 __cdecl FUN_0048cef0(ushort *param_1,uint *param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint local_18;
  uint local_14;
  int local_10;
  undefined4 local_c [3];
  
  uVar1 = param_1[5];
  local_14 = *(uint *)(param_1 + 1);
  local_18 = *(uint *)(param_1 + 3);
  uVar4 = uVar1 & 0x7fff;
  iVar5 = uVar4 - 0x3fff;
  local_10 = (uint)*param_1 << 0x10;
  if (iVar5 == -0x3fff) {
    iVar5 = 0;
    iVar2 = FUN_0048ce10((int *)&local_18);
    if (iVar2 == 0) {
      FUN_0048ce00(&local_18);
      uVar3 = 2;
      goto LAB_0048d071;
    }
  }
  else {
    FUN_0048cde0((int)local_c,&local_18);
    iVar2 = FUN_0048cd40((int)&local_18,param_3[2]);
    if (iVar2 != 0) {
      iVar5 = uVar4 - 0x3ffe;
    }
    iVar2 = param_3[1];
    if (iVar5 < iVar2 - param_3[2]) {
      FUN_0048ce00(&local_18);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_0048d071;
    }
    if (iVar5 <= iVar2) {
      FUN_0048cde0((int)&local_18,local_c);
      FUN_0048ce30(&local_18,iVar2 - iVar5);
      FUN_0048cd40((int)&local_18,param_3[2]);
      FUN_0048ce30(&local_18,param_3[3] + 1);
      iVar5 = 0;
      uVar3 = 2;
      goto LAB_0048d071;
    }
    if (*param_3 <= iVar5) {
      FUN_0048ce00(&local_18);
      local_18 = local_18 | 0x80000000;
      FUN_0048ce30(&local_18,param_3[3]);
      iVar5 = param_3[5] + *param_3;
      uVar3 = 1;
      goto LAB_0048d071;
    }
    iVar5 = param_3[5] + iVar5;
    local_18 = local_18 & 0x7fffffff;
    FUN_0048ce30(&local_18,param_3[3]);
  }
  uVar3 = 0;
LAB_0048d071:
  local_18 = iVar5 << (0x1fU - (char)param_3[3] & 0x1f) |
             -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 | local_18;
  if (param_3[4] == 0x40) {
    param_2[1] = local_18;
    *param_2 = local_14;
    return uVar3;
  }
  if (param_3[4] == 0x20) {
    *param_2 = local_18;
  }
  return uVar3;
}


/* ==== _ld12tod @ 0048d0c0 ==== */

int __cdecl _ld12tod(void *pld12,double *d)

{
  int iVar1;
  
  iVar1 = FUN_0048cef0(pld12,(uint *)d,(int *)&DAT_004da7e0);
  return iVar1;
}


/* ==== FUN_0048d0e0 @ 0048d0e0 ==== */

void __cdecl FUN_0048d0e0(ushort *param_1,uint *param_2)

{
  FUN_0048cef0(param_1,param_2,(int *)&DAT_004da7f8);
  return;
}


/* ==== FUN_0048d100 @ 0048d100 ==== */

void __cdecl FUN_0048d100(uint *param_1,byte *param_2)

{
  undefined1 local_c [12];
  
  __strgtold12(local_c,(char **)&param_2,(char *)param_2,0,0,0,0);
  _ld12tod(local_c,(double *)param_1);
  return;
}


/* ==== FUN_0048d140 @ 0048d140 ==== */

void __cdecl FUN_0048d140(uint *param_1,byte *param_2)

{
  ushort local_c [6];
  
  __strgtold12(local_c,(char **)&param_2,(char *)param_2,0,0,0,0);
  FUN_0048d0e0(local_c,param_1);
  return;
}


/* ==== _fptostr @ 0048d180 ==== */

void __cdecl _fptostr(char *buf,int digits,void *pflt)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  
  pcVar5 = *(char **)((int)pflt + 0xc);
  pcVar7 = buf + 1;
  *buf = '0';
  pcVar1 = pcVar7;
  iVar6 = digits;
  if (0 < digits) {
    do {
      cVar2 = *pcVar5;
      if (cVar2 == '\0') {
        cVar2 = '0';
      }
      else {
        pcVar5 = pcVar5 + 1;
      }
      *pcVar1 = cVar2;
      pcVar1 = pcVar1 + 1;
      iVar6 = iVar6 + -1;
      digits = digits + -1;
    } while (digits != 0);
  }
  *pcVar1 = '\0';
  if ((-1 < iVar6) && ('4' < *pcVar5)) {
    cVar2 = pcVar1[-1];
    while (pcVar5 = pcVar1 + -1, cVar2 == '9') {
      *pcVar5 = '0';
      cVar2 = pcVar1[-2];
      pcVar1 = pcVar5;
    }
    *pcVar5 = *pcVar5 + '\x01';
  }
  if (*buf == '1') {
    *(int *)((int)pflt + 4) = *(int *)((int)pflt + 4) + 1;
    return;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = pcVar7;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar5;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3;
  pcVar7 = pcVar5 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)buf = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    buf = buf + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *buf = *pcVar7;
    pcVar7 = pcVar7 + 1;
    buf = buf + 1;
  }
  return;
}


/* ==== _fltout2 @ 0048d220 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _fltout2(double x,void *flt,char *resultstr)

{
  undefined4 in_stack_ffffffe4;
  undefined2 uVar1;
  uint local_c;
  uint local_8;
  undefined2 local_4;
  
  uVar1 = (undefined2)((uint)in_stack_ffffffe4 >> 0x10);
  FUN_0048d2a0(&local_c,(uint *)&x);
  _DAT_00505690 = FUN_0048fbf0(local_c,local_8,CONCAT22(uVar1,local_4),0x11,0,&DAT_00505668);
  _DAT_00505688 = (int)DAT_0050566a;
  _DAT_0050568c = (int)DAT_00505668;
  _DAT_00505694 = &DAT_0050566c;
  return;
}


/* ==== FUN_0048d2a0 @ 0048d2a0 ==== */

void __cdecl FUN_0048d2a0(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  
  uVar4 = 0x80000000;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  if (uVar3 == 0) {
    uVar4 = 0;
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    iVar6 = 0x3c01;
  }
  else if (uVar3 == 0x7ff) {
    iVar6 = 0x7fff;
  }
  else {
    iVar6 = uVar3 + 0x3c00;
  }
  uVar5 = (ushort)iVar6;
  uVar3 = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | uVar4;
  param_1[1] = uVar3;
  *param_1 = uVar2 << 0xb;
  for (; uVar4 == 0; uVar4 = uVar4 & 0x80000000) {
    uVar4 = uVar3 * 2;
    uVar3 = *param_1 >> 0x1f | uVar4;
    iVar6 = iVar6 + 0xffff;
    uVar5 = (ushort)iVar6;
    param_1[1] = uVar3;
    *param_1 = *param_1 * 2;
  }
  *(ushort *)(param_1 + 2) = uVar5 | uVar1 & 0x8000;
  return;
}


/* ==== memmove @ 0048d360 ==== */

void __cdecl memmove(void *dst,void *src,uint n)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((src < dst) && (dst < (void *)(n + (int)src))) {
    puVar3 = (undefined4 *)((n - 4) + (int)src);
    puVar4 = (undefined4 *)((n - 4) + (int)dst);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = n >> 2;
      uVar2 = n & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return;
        case 2:
          goto switchD_0048d517_caseD_2;
        case 3:
          goto switchD_0048d517_caseD_3;
        }
        goto switchD_0048d517_caseD_1;
      }
    }
    else {
      switch(n) {
      case 0:
        goto switchD_0048d517_caseD_0;
      case 1:
        goto switchD_0048d517_caseD_1;
      case 2:
        goto switchD_0048d517_caseD_2;
      case 3:
        goto switchD_0048d517_caseD_3;
      default:
        uVar1 = n - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return;
            case 2:
              goto switchD_0048d517_caseD_2;
            case 3:
              goto switchD_0048d517_caseD_3;
            }
            goto switchD_0048d517_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return;
            case 2:
              goto switchD_0048d517_caseD_2;
            case 3:
              goto switchD_0048d517_caseD_3;
            }
            goto switchD_0048d517_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return;
            case 2:
              goto switchD_0048d517_caseD_2;
            case 3:
              goto switchD_0048d517_caseD_3;
            }
            goto switchD_0048d517_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_0048d517_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return;
    case 2:
switchD_0048d517_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return;
    case 3:
switchD_0048d517_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return;
    }
switchD_0048d517_caseD_0:
    return;
  }
  if (((uint)dst & 3) == 0) {
    uVar1 = n >> 2;
    uVar2 = n & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined4 *)dst = *(undefined4 *)src;
        src = (undefined4 *)((int)src + 4);
        dst = (undefined4 *)((int)dst + 4);
      }
      switch(uVar2) {
      case 0:
        return;
      case 2:
        goto switchD_0048d395_caseD_2;
      case 3:
        goto switchD_0048d395_caseD_3;
      }
      goto switchD_0048d395_caseD_1;
    }
  }
  else {
    switch(n) {
    case 0:
      goto switchD_0048d395_caseD_0;
    case 1:
      goto switchD_0048d395_caseD_1;
    case 2:
      goto switchD_0048d395_caseD_2;
    case 3:
      goto switchD_0048d395_caseD_3;
    default:
      uVar1 = (n - 4) + ((uint)dst & 3);
      switch((uint)dst & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
        src = (void *)((int)src + 3);
        dst = (void *)((int)dst + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined4 *)dst = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            dst = (undefined4 *)((int)dst + 4);
          }
          switch(uVar2) {
          case 0:
            return;
          case 2:
            goto switchD_0048d395_caseD_2;
          case 3:
            goto switchD_0048d395_caseD_3;
          }
          goto switchD_0048d395_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        src = (void *)((int)src + 2);
        dst = (void *)((int)dst + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined4 *)dst = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            dst = (undefined4 *)((int)dst + 4);
          }
          switch(uVar2) {
          case 0:
            return;
          case 2:
            goto switchD_0048d395_caseD_2;
          case 3:
            goto switchD_0048d395_caseD_3;
          }
          goto switchD_0048d395_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        src = (void *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        dst = (void *)((int)dst + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *(undefined4 *)dst = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            dst = (undefined4 *)((int)dst + 4);
          }
          switch(uVar2) {
          case 0:
            return;
          case 2:
            goto switchD_0048d395_caseD_2;
          case 3:
            goto switchD_0048d395_caseD_3;
          }
          goto switchD_0048d395_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    *(undefined4 *)((int)dst + (uVar1 - 7) * 4) = *(undefined4 *)((int)src + (uVar1 - 7) * 4);
  case 6:
    *(undefined4 *)((int)dst + (uVar1 - 6) * 4) = *(undefined4 *)((int)src + (uVar1 - 6) * 4);
  case 5:
    *(undefined4 *)((int)dst + (uVar1 - 5) * 4) = *(undefined4 *)((int)src + (uVar1 - 5) * 4);
  case 4:
    *(undefined4 *)((int)dst + (uVar1 - 4) * 4) = *(undefined4 *)((int)src + (uVar1 - 4) * 4);
  case 3:
    *(undefined4 *)((int)dst + (uVar1 - 3) * 4) = *(undefined4 *)((int)src + (uVar1 - 3) * 4);
  case 2:
    *(undefined4 *)((int)dst + (uVar1 - 2) * 4) = *(undefined4 *)((int)src + (uVar1 - 2) * 4);
  case 1:
    *(undefined4 *)((int)dst + (uVar1 - 1) * 4) = *(undefined4 *)((int)src + (uVar1 - 1) * 4);
    src = (void *)((int)src + uVar1 * 4);
    dst = (void *)((int)dst + uVar1 * 4);
  }
  switch(uVar2) {
  case 1:
switchD_0048d395_caseD_1:
    *(undefined1 *)dst = *(undefined1 *)src;
    return;
  case 2:
switchD_0048d395_caseD_2:
    *(undefined1 *)dst = *(undefined1 *)src;
    *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
    return;
  case 3:
switchD_0048d395_caseD_3:
    *(undefined1 *)dst = *(undefined1 *)src;
    *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
    *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
    return;
  }
switchD_0048d395_caseD_0:
  return;
}


/* ==== _fptrap @ 0048d6a0 ==== */

void _fptrap(void)

{
  _amsg_exit(2);
  return;
}


/* ==== _alloc_osfhnd @ 0048d6b0 ==== */

int _alloc_osfhnd(void)

{
  undefined4 *puVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = -1;
  iVar5 = 0;
  iVar6 = 0;
  piVar3 = &__pioinfo;
  do {
    puVar2 = (undefined4 *)*piVar3;
    if (puVar2 == (undefined4 *)0x0) {
      malloc(0x100);
      if (extraout_EAX != (undefined4 *)0x0) {
        _nhandle = _nhandle + 0x20;
        (&__pioinfo)[iVar5] = extraout_EAX;
        puVar2 = extraout_EAX;
        if (extraout_EAX < extraout_EAX + 0x40) {
          do {
            *(undefined1 *)(puVar2 + 1) = 0;
            *puVar2 = 0xffffffff;
            *(undefined1 *)((int)puVar2 + 5) = 10;
            puVar2 = puVar2 + 2;
          } while (puVar2 < (undefined4 *)((&__pioinfo)[iVar5] + 0x100));
        }
        iVar4 = iVar5 << 5;
      }
      return iVar4;
    }
    puVar1 = puVar2 + 0x40;
    for (; puVar2 < puVar1; puVar2 = puVar2 + 2) {
      if ((*(byte *)(puVar2 + 1) & 1) == 0) {
        *puVar2 = 0xffffffff;
        iVar4 = ((int)puVar2 - *piVar3 >> 3) + iVar6;
        break;
      }
    }
    if (iVar4 != -1) {
      return iVar4;
    }
    piVar3 = piVar3 + 1;
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + 0x20;
    if (0x505c7f < (int)piVar3) {
      return -1;
    }
  } while( true );
}


/* ==== _set_osfhnd @ 0048d770 ==== */

int __cdecl _set_osfhnd(int fh,long value)

{
  int iVar1;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (*(int *)((&__pioinfo)[fh >> 5] + iVar1) == -1) {
      if (DAT_004d7c50 == 1) {
        if (fh == 0) {
          SetStdHandle(0xfffffff6,(HANDLE)value);
        }
        else {
          if (fh == 1) {
            SetStdHandle(0xfffffff5,(HANDLE)value);
            *(long *)(__pioinfo + 8) = value;
            return 0;
          }
          if (fh == 2) {
            SetStdHandle(0xfffffff4,(HANDLE)value);
            *(long *)(__pioinfo + 0x10) = value;
            return 0;
          }
        }
      }
      *(long *)((&__pioinfo)[fh >> 5] + iVar1) = value;
      return 0;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _free_osfhnd @ 0048d820 ==== */

int __cdecl _free_osfhnd(int fh)

{
  int iVar1;
  DWORD nStdHandle;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar1) & 1) != 0) &&
       (*(int *)((&__pioinfo)[fh >> 5] + iVar1) != -1)) {
      if (DAT_004d7c50 == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_0048d88a;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0048d88a:
      *(undefined4 *)((&__pioinfo)[fh >> 5] + iVar1) = 0xffffffff;
      return 0;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _get_osfhandle @ 0048d8c0 ==== */

long __cdecl _get_osfhandle(int fh)

{
  if (((uint)fh < _nhandle) && ((*(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 1) != 0))
  {
    return *(long *)((&__pioinfo)[fh >> 5] + (fh & 0x1fU) * 8);
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== mbtowc @ 0048d910 ==== */

int __cdecl mbtowc(ushort *pwc,char *s,uint n)

{
  byte bVar1;
  int iVar2;
  
  if ((s != (char *)0x0) && (n != 0)) {
    bVar1 = *s;
    if (bVar1 != 0) {
      if (DAT_005055d0 == 0) {
        if (pwc == (ushort *)0x0) {
          return 1;
        }
        *pwc = (ushort)bVar1;
        return 1;
      }
      if ((_pctype[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(DAT_005055e0,9,s,1,(LPWSTR)pwc,(uint)(pwc != (ushort *)0x0));
        if (iVar2 != 0) {
          return 1;
        }
        errno = 0x2a;
        return -1;
      }
      if (((1 < (int)__mb_cur_max) && ((int)__mb_cur_max <= (int)n)) &&
         (iVar2 = MultiByteToWideChar(DAT_005055e0,9,s,__mb_cur_max,(LPWSTR)pwc,
                                      (uint)(pwc != (ushort *)0x0)), iVar2 != 0)) {
        return __mb_cur_max;
      }
      if (n < __mb_cur_max) {
        errno = 0x2a;
        return -1;
      }
      if (s[1] != '\0') {
        return __mb_cur_max;
      }
      errno = 0x2a;
      return -1;
    }
    if (pwc != (ushort *)0x0) {
      *pwc = 0;
      return 0;
    }
  }
  return 0;
}


/* ==== isspace @ 0048da10 ==== */

int __cdecl isspace(int c)

{
  int iVar1;
  
  if (1 < __mb_cur_max) {
    iVar1 = _isctype(c,8);
    return iVar1;
  }
  return (byte)_pctype[c * 2] & 8;
}


/* ==== __allshl @ 0048da40 ==== */

/* Library Function - Single Match
    __allshl
   
   Library: Visual Studio */

longlong __fastcall __allshl(byte param_1,int param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 << (param_1 & 0x1f) | in_EAX >> 0x20 - (param_1 & 0x1f),
                    in_EAX << (param_1 & 0x1f));
  }
  return (ulonglong)(in_EAX << (param_1 & 0x1f)) << 0x20;
}


/* ==== ungetc @ 0048da60 ==== */

int __cdecl ungetc(int c,void *stream)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  
  if ((c != -1) &&
     ((uVar1 = *(uint *)((int)stream + 0xc), (uVar1 & 1) != 0 ||
      (((uVar1 & 0x80) != 0 && ((uVar1 & 2) == 0)))))) {
    if (*(int *)((int)stream + 8) == 0) {
      _getbuf(stream);
    }
    if (*(int *)stream == *(int *)((int)stream + 8)) {
      if (*(int *)((int)stream + 4) != 0) {
        return -1;
      }
      *(int *)stream = *(int *)stream + 1;
    }
    if ((*(byte *)((int)stream + 0xc) & 0x40) == 0) {
      iVar2 = *(int *)stream;
      *(char **)stream = (char *)(iVar2 + -1);
      *(char *)(iVar2 + -1) = (char)c;
    }
    else {
      iVar2 = *(int *)stream;
      pcVar3 = (char *)(iVar2 + -1);
      *(char **)stream = pcVar3;
      if (*pcVar3 != (char)c) {
        *(int *)stream = iVar2;
        return -1;
      }
    }
    *(int *)((int)stream + 4) = *(int *)((int)stream + 4) + 1;
    *(uint *)((int)stream + 0xc) = *(uint *)((int)stream + 0xc) & 0xffffffef | 1;
    return c & 0xff;
  }
  return -1;
}


/* ==== _chsize @ 0048daf0 ==== */

int _chsize(int fh,long size)

{
  long pos;
  long lVar1;
  uint cnt;
  int iVar2;
  HANDLE hFile;
  BOOL BVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint in_stack_00001008;
  int in_stack_0000100c;
  
  FUN_00490000();
  iVar5 = 0;
  if ((in_stack_00001008 < _nhandle) &&
     ((*(byte *)((&__pioinfo)[(int)in_stack_00001008 >> 5] + 4 + (in_stack_00001008 & 0x1f) * 8) & 1
      ) != 0)) {
    pos = _lseek(in_stack_00001008,0,1);
    if ((pos != -1) && (lVar1 = _lseek(in_stack_00001008,0,2), lVar1 != -1)) {
      uVar6 = in_stack_0000100c - lVar1;
      if ((int)uVar6 < 1) {
        if ((int)uVar6 < 0) {
          _lseek(in_stack_00001008,in_stack_0000100c,0);
          hFile = (HANDLE)_get_osfhandle(in_stack_00001008);
          BVar3 = SetEndOfFile(hFile);
          iVar5 = (BVar3 != 0) - 1;
          if (iVar5 == -1) {
            errno = 0xd;
            _doserrno = GetLastError();
          }
        }
        _lseek(in_stack_00001008,pos,0);
        return iVar5;
      }
      puVar7 = (undefined4 *)register0x00000010;
      for (iVar4 = 0x400; puVar7 = puVar7 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = 0;
      }
      iVar4 = FUN_0048ff80(in_stack_00001008,0x8000);
      while( true ) {
        cnt = 0x1000;
        if ((int)uVar6 < 0x1000) {
          cnt = uVar6;
        }
        iVar2 = _write(in_stack_00001008,&fh,cnt);
        if (iVar2 == -1) break;
        uVar6 = uVar6 - iVar2;
        if ((int)uVar6 < 1) {
LAB_0048dbd1:
          FUN_0048ff80(in_stack_00001008,iVar4);
          _lseek(in_stack_00001008,pos,0);
          return iVar5;
        }
      }
      if (_doserrno == 5) {
        errno = 0xd;
      }
      iVar5 = -1;
      goto LAB_0048dbd1;
    }
  }
  else {
    errno = 9;
  }
  return -1;
}


/* ==== __tzset @ 0048dc70 ==== */

void __tzset(void)

{
  if (DAT_00505758 == 0) {
    _tzset();
    DAT_00505758 = DAT_00505758 + 1;
  }
  return;
}


/* ==== _tzset @ 0048dc90 ==== */

void _tzset(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined3 extraout_var;
  DWORD DVar5;
  int iVar6;
  byte *extraout_EAX;
  long lVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  bool bVar12;
  byte *pbVar4;
  
  DAT_005056a0 = 0;
  DAT_004da8b8 = 0xffffffff;
  DAT_004da8a8 = 0xffffffff;
  cVar3 = getenv("TZ");
  pbVar4 = (byte *)CONCAT31(extraout_var,cVar3);
  if (pbVar4 == (byte *)0x0) {
    DVar5 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_005056a8);
    if (DVar5 != 0xffffffff) {
      DAT_005056a0 = 1;
      _timezone = DAT_005056a8 * 0x3c;
      if (DAT_005056ee != 0) {
        _timezone = _timezone + DAT_005056fc * 0x3c;
      }
      if ((DAT_00505742 == 0) || (DAT_00505750 == 0)) {
        _daylight = 0;
        _dstbias = 0;
      }
      else {
        _daylight = 1;
        _dstbias = (DAT_00505750 - DAT_005056fc) * 0x3c;
      }
      FUN_00490030(PTR_DAT_004da8a0,(LPCWSTR)&DAT_005056ac,0x40);
      FUN_00490030(PTR_DAT_004da8a4,(LPCWSTR)&DAT_00505700,0x40);
      PTR_DAT_004da8a4[0x3f] = 0;
      PTR_DAT_004da8a0[0x3f] = 0;
      return;
    }
  }
  else if (*pbVar4 != 0) {
    pbVar10 = pbVar4;
    pbVar11 = DAT_00505754;
    if (DAT_00505754 != (byte *)0x0) {
      do {
        bVar1 = *pbVar10;
        bVar12 = bVar1 < *pbVar11;
        if (bVar1 != *pbVar11) {
LAB_0048ddd3:
          iVar6 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
          goto LAB_0048ddd8;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar10[1];
        bVar12 = bVar1 < pbVar11[1];
        if (bVar1 != pbVar11[1]) goto LAB_0048ddd3;
        pbVar10 = pbVar10 + 2;
        pbVar11 = pbVar11 + 2;
      } while (bVar1 != 0);
      iVar6 = 0;
LAB_0048ddd8:
      if (iVar6 == 0) {
        return;
      }
    }
    free(DAT_00505754);
    uVar8 = 0xffffffff;
    pbVar10 = pbVar4;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      bVar1 = *pbVar10;
      pbVar10 = pbVar10 + 1;
    } while (bVar1 != 0);
    malloc(~uVar8);
    DAT_00505754 = extraout_EAX;
    if (extraout_EAX != (byte *)0x0) {
      uVar8 = 0xffffffff;
      pbVar10 = pbVar4;
      do {
        pbVar11 = pbVar10;
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        pbVar11 = pbVar10 + 1;
        bVar1 = *pbVar10;
        pbVar10 = pbVar11;
      } while (bVar1 != 0);
      uVar8 = ~uVar8;
      pbVar10 = pbVar11 + -uVar8;
      pbVar11 = extraout_EAX;
      for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pbVar11 = *(undefined4 *)pbVar10;
        pbVar10 = pbVar10 + 4;
        pbVar11 = pbVar11 + 4;
      }
      for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pbVar11 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        pbVar11 = pbVar11 + 1;
      }
      strncpy(PTR_DAT_004da8a0,(char *)pbVar4,3);
      pbVar10 = pbVar4 + 3;
      PTR_DAT_004da8a0[3] = 0;
      bVar1 = *pbVar10;
      if (bVar1 == 0x2d) {
        pbVar10 = pbVar4 + 4;
      }
      lVar7 = atol((char *)pbVar10);
      _timezone = lVar7 * 0xe10;
      for (; (bVar2 = *pbVar10, bVar2 == 0x2b || (('/' < (char)bVar2 && ((char)bVar2 < ':'))));
          pbVar10 = pbVar10 + 1) {
      }
      if (*pbVar10 == 0x3a) {
        pbVar10 = pbVar10 + 1;
        lVar7 = atol((char *)pbVar10);
        _timezone = _timezone + lVar7 * 0x3c;
        bVar2 = *pbVar10;
        while (('/' < (char)bVar2 && ((char)bVar2 < ':'))) {
          pbVar4 = pbVar10 + 1;
          pbVar10 = pbVar10 + 1;
          bVar2 = *pbVar4;
        }
        if (*pbVar10 == 0x3a) {
          pbVar10 = pbVar10 + 1;
          lVar7 = atol((char *)pbVar10);
          _timezone = _timezone + lVar7;
          bVar2 = *pbVar10;
          while (('/' < (char)bVar2 && ((char)bVar2 < ':'))) {
            pbVar4 = pbVar10 + 1;
            pbVar10 = pbVar10 + 1;
            bVar2 = *pbVar4;
          }
        }
      }
      if (bVar1 == 0x2d) {
        _timezone = -_timezone;
      }
      _daylight = (int)(char)*pbVar10;
      if (_daylight != 0) {
        strncpy(PTR_DAT_004da8a4,(char *)pbVar10,3);
        PTR_DAT_004da8a4[3] = 0;
        return;
      }
      *PTR_DAT_004da8a4 = 0;
    }
  }
  return;
}


/* ==== _isindst @ 0048df40 ==== */

int __cdecl _isindst(void *tb)

{
  uint uVar1;
  uint uVar2;
  uint hour;
  uint date;
  int iVar3;
  int iVar4;
  uint month;
  uint week;
  uint uVar5;
  uint msec;
  
  if (_daylight == 0) {
    return 0;
  }
  iVar4 = *(int *)((int)tb + 0x14);
  if ((iVar4 == DAT_004da8a8) && (iVar4 == DAT_004da8b8)) goto LAB_0048e114;
  if (DAT_005056a0 == 0) {
    cvtdate(1,1,iVar4,4,1,0,0,2,0,0,0);
    iVar4 = *(int *)((int)tb + 0x14);
    msec = 0;
    uVar2 = 0;
    uVar5 = 0;
    hour = 2;
    uVar1 = 0;
    week = 5;
    month = 10;
LAB_0048e108:
    date = 0;
    iVar3 = 1;
  }
  else {
    if (DAT_00505740 != 0) {
      uVar5 = (uint)DAT_00505744._2_2_;
      uVar2 = 0;
      uVar1 = 0;
    }
    else {
      uVar2 = DAT_00505744 & 0xffff;
      uVar5 = 0;
      uVar1 = (uint)DAT_00505744._2_2_;
    }
    cvtdate(1,(uint)(DAT_00505740 == 0),iVar4,(uint)DAT_00505742,uVar1,uVar2,uVar5,
            DAT_00505748 & 0xffff,DAT_00505748 >> 0x10,DAT_0050574c & 0xffff,DAT_0050574c >> 0x10);
    if (DAT_005056ec == 0) {
      msec = (uint)DAT_005056f8._2_2_;
      uVar2 = DAT_005056f8 & 0xffff;
      uVar5 = (uint)DAT_005056f4._2_2_;
      hour = DAT_005056f4 & 0xffff;
      uVar1 = DAT_005056f0 & 0xffff;
      week = (uint)DAT_005056f0._2_2_;
      month = (uint)DAT_005056ee;
      iVar4 = *(int *)((int)tb + 0x14);
      goto LAB_0048e108;
    }
    msec = (uint)DAT_005056f8._2_2_;
    uVar2 = DAT_005056f8 & 0xffff;
    uVar5 = (uint)DAT_005056f4._2_2_;
    date = (uint)DAT_005056f0._2_2_;
    hour = DAT_005056f4 & 0xffff;
    iVar4 = *(int *)((int)tb + 0x14);
    month = (uint)DAT_005056ee;
    uVar1 = 0;
    week = 0;
    iVar3 = 0;
  }
  cvtdate(0,iVar3,iVar4,month,week,uVar1,date,hour,uVar5,uVar2,msec);
LAB_0048e114:
  iVar4 = *(int *)((int)tb + 0x1c);
  if (DAT_004da8ac < DAT_004da8bc) {
    if ((iVar4 < DAT_004da8ac) || (DAT_004da8bc < iVar4)) {
      return 0;
    }
    if ((DAT_004da8ac < iVar4) && (iVar4 < DAT_004da8bc)) {
      return 1;
    }
  }
  else {
    if ((iVar4 < DAT_004da8bc) || (DAT_004da8ac < iVar4)) {
      return 1;
    }
    if ((DAT_004da8bc < iVar4) && (iVar4 < DAT_004da8ac)) {
      return 0;
    }
  }
  iVar3 = (*(int *)tb + (*(int *)((int)tb + 4) + *(int *)((int)tb + 8) * 0x3c) * 0x3c) * 1000;
  if (iVar4 != DAT_004da8ac) {
    return (uint)(iVar3 < DAT_004da8c0);
  }
  return (uint)(DAT_004da8b0 <= iVar3);
}


/* ==== cvtdate @ 0048e1b0 ==== */

void __cdecl
cvtdate(int trantype,int datetype,int year,int month,int week,int dayofweek,int date,int hour,
       int min,int sec,int msec)

{
  int iVar1;
  int iVar2;
  
  if (datetype == 1) {
    if ((year & 3U) == 0) {
      iVar1 = *(int *)(&DAT_004da8c4 + month * 4);
    }
    else {
      iVar1 = *(int *)(&DAT_004da8fc + month * 4);
    }
    iVar2 = ((year + -1 >> 2) + -0x63db + year * 0x16d + iVar1 + 1) % 7;
    if (iVar2 < dayofweek) {
      iVar1 = iVar1 + -6 + (week * 7 - iVar2) + dayofweek;
    }
    else {
      iVar1 = iVar1 + 1 + (week * 7 - iVar2) + dayofweek;
    }
    if (week == 5) {
      if ((year & 3U) == 0) {
        iVar2 = *(int *)(&DAT_004da8c8 + month * 4);
      }
      else {
        iVar2 = (&DAT_004da900)[month];
      }
      if (iVar2 < iVar1) {
        iVar1 = iVar1 + -7;
      }
    }
  }
  else {
    if ((year & 3U) == 0) {
      iVar1 = *(int *)(&DAT_004da8c4 + month * 4);
    }
    else {
      iVar1 = *(int *)(&DAT_004da8fc + month * 4);
    }
    iVar1 = iVar1 + date;
  }
  if (trantype == 1) {
    DAT_004da8ac = iVar1;
    DAT_004da8a8 = year;
    DAT_004da8b0 = msec + (sec + (min + hour * 0x3c) * 0x3c) * 1000;
    return;
  }
  DAT_004da8bc = iVar1;
  DAT_004da8c0 = msec + (sec + (min + hour * 0x3c) * 0x3c + _dstbias) * 1000;
  if (DAT_004da8c0 < 0) {
    DAT_004da8b8 = year;
    DAT_004da8c0 = DAT_004da8c0 + 86399999;
    return;
  }
  if (86399999 < DAT_004da8c0) {
    DAT_004da8c0 = DAT_004da8c0 + -86399999;
  }
  DAT_004da8b8 = year;
  return;
}


/* ==== FUN_0048e350 @ 0048e350 ==== */

uint __cdecl FUN_0048e350(char *param_1,char *param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  
  cVar2 = *param_1;
  while (cVar2 == ';') {
    pcVar3 = param_1 + 1;
    param_1 = param_1 + 1;
    cVar2 = *pcVar3;
  }
  iVar4 = param_3 + -1;
  pcVar3 = param_1;
  if (iVar4 != 0) {
    cVar2 = *param_1;
    while ((cVar2 != '\0' && (cVar2 != ';'))) {
      if (cVar2 == '\"') {
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
        cVar2 = *pcVar1;
        while ((cVar2 != '\0' && (cVar2 != '\"'))) {
          *param_2 = cVar2;
          param_2 = param_2 + 1;
          pcVar3 = pcVar3 + 1;
          iVar4 = iVar4 + -1;
          if (iVar4 == 0) goto LAB_0048e3b1;
          cVar2 = *pcVar3;
        }
        if (*pcVar3 != '\0') {
          pcVar3 = pcVar3 + 1;
        }
      }
      else {
        *param_2 = cVar2;
        param_2 = param_2 + 1;
        pcVar3 = pcVar3 + 1;
        iVar4 = iVar4 + -1;
        if (iVar4 == 0) {
LAB_0048e3b1:
          *param_2 = '\0';
          return 0;
        }
      }
      cVar2 = *pcVar3;
    }
    if (*pcVar3 == ';') {
      do {
        pcVar1 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar1 == ';');
      *param_2 = '\0';
      return -(uint)(param_1 != pcVar3) & (uint)pcVar3;
    }
  }
  *param_2 = '\0';
  return -(uint)(param_1 != pcVar3) & (uint)pcVar3;
}


/* ==== FUN_0048e3f0 @ 0048e3f0 ==== */

byte * __cdecl FUN_0048e3f0(byte *param_1,uint param_2)

{
  char cVar1;
  undefined3 extraout_var;
  uint uVar2;
  byte *pbVar3;
  
  if (DAT_0050558c == 0) {
    cVar1 = strchr((char *)param_1,param_2);
    return (byte *)CONCAT31(extraout_var,cVar1);
  }
  uVar2 = (uint)(ushort)*param_1;
  if (*param_1 == 0) {
LAB_0048e487:
    return (byte *)((param_2 != uVar2) - 1 & (uint)param_1);
  }
  do {
    if ((*(byte *)((int)&DAT_00505488 + uVar2 + 1) & 4) == 0) {
      pbVar3 = param_1;
      if (param_2 == uVar2) goto LAB_0048e487;
    }
    else {
      pbVar3 = param_1 + 1;
      if (param_1[1] == 0) {
        return (byte *)0x0;
      }
      if (param_2 == (uVar2 << 8 | (uint)param_1[1])) {
        return param_1;
      }
    }
    uVar2 = (uint)(ushort)pbVar3[1];
    param_1 = pbVar3 + 1;
    if (pbVar3[1] == 0) {
      return (byte *)((param_2 != 0) - 1 & (uint)param_1);
    }
  } while( true );
}


/* ==== FUN_0048e4a0 @ 0048e4a0 ==== */

LPSTR __cdecl FUN_0048e4a0(int param_1,LPCSTR param_2,LPSTR param_3,LPVOID param_4)

{
  undefined4 *puVar1;
  char cVar2;
  byte bVar3;
  bool bVar4;
  uint uVar5;
  LPSTR lpCommandLine;
  char *pcVar6;
  char *pcVar7;
  uint *extraout_EAX;
  uint uVar8;
  DWORD DVar9;
  BOOL BVar10;
  int iVar11;
  undefined4 *puVar12;
  _STARTUPINFOA *p_Var13;
  uint *puVar14;
  _PROCESS_INFORMATION local_54;
  _STARTUPINFOA local_44;
  
  lpCommandLine = param_3;
  bVar4 = false;
  switch(param_1) {
  case 0:
  case 1:
  case 2:
  case 3:
    goto switchD_0048e4be_caseD_0;
  case 4:
    bVar4 = true;
switchD_0048e4be_caseD_0:
    cVar2 = *param_3;
    pcVar7 = param_3;
    break;
  default:
    _doserrno = 0;
    errno = 0x16;
    return (LPSTR)0xffffffff;
  }
  while (cVar2 != '\0') {
    do {
      pcVar6 = pcVar7;
      pcVar7 = pcVar6 + 1;
    } while (pcVar6[1] != '\0');
    if (pcVar6[2] != '\0') {
      *pcVar7 = ' ';
      pcVar7 = pcVar6 + 2;
    }
    cVar2 = *pcVar7;
  }
  p_Var13 = &local_44;
  for (iVar11 = 0x11; iVar11 != 0; iVar11 = iVar11 + -1) {
    p_Var13->cb = 0;
    p_Var13 = (_STARTUPINFOA *)&p_Var13->lpReserved;
  }
  local_44.cb = 0x44;
  uVar8 = _nhandle;
  do {
    uVar5 = uVar8;
    if (uVar5 == 0) break;
    uVar8 = uVar5 - 1;
  } while (*(char *)((&__pioinfo)[(int)uVar8 >> 5] + 4 + (uVar8 & 0x1f) * 8) == '\0');
  local_44.cbReserved2 = (short)uVar5 * 5 + 4;
  calloc((uint)local_44.cbReserved2,1);
  local_44.lpReserved2._0_2_ = SUB42(extraout_EAX,0);
  local_44.lpReserved2._2_2_ = (undefined2)((uint)extraout_EAX >> 0x10);
  *extraout_EAX = uVar5;
  uVar8 = 0;
  puVar14 = extraout_EAX + 1;
  puVar12 = (undefined4 *)(uVar5 + 4 + (int)extraout_EAX);
  if (0 < (int)uVar5) {
    do {
      puVar1 = (undefined4 *)((&__pioinfo)[(int)uVar8 >> 5] + (uVar8 & 0x1f) * 8);
      bVar3 = *(byte *)(puVar1 + 1);
      if ((bVar3 & 0x10) == 0) {
        *(byte *)puVar14 = bVar3;
        *puVar12 = *puVar1;
      }
      else {
        *(undefined1 *)puVar14 = 0;
        *puVar12 = 0xffffffff;
      }
      uVar8 = uVar8 + 1;
      puVar14 = (uint *)((int)puVar14 + 1);
      puVar12 = puVar12 + 1;
    } while ((int)uVar8 < (int)uVar5);
  }
  if (bVar4) {
    puVar14 = extraout_EAX + 1;
    iVar11 = 0;
    puVar12 = (undefined4 *)(uVar5 + 4 + (int)extraout_EAX);
    while( true ) {
      uVar8 = uVar5;
      if (2 < (int)uVar5) {
        uVar8 = 3;
      }
      if ((int)uVar8 <= iVar11) break;
      *(undefined1 *)puVar14 = 0;
      iVar11 = iVar11 + 1;
      *puVar12 = 0xffffffff;
      puVar14 = (uint *)((int)puVar14 + 1);
      puVar12 = puVar12 + 1;
    }
    DVar9 = 8;
  }
  else {
    DVar9 = 0;
  }
  errno = 0;
  _doserrno = 0;
  BVar10 = CreateProcessA(param_2,lpCommandLine,(LPSECURITY_ATTRIBUTES)0x0,
                          (LPSECURITY_ATTRIBUTES)0x0,1,DVar9,param_4,(LPCSTR)0x0,&local_44,&local_54
                         );
  DVar9 = GetLastError();
  free((void *)CONCAT22(local_44.lpReserved2._2_2_,local_44.lpReserved2._0_2_));
  if (BVar10 == 0) {
    _dosmaperr(DVar9);
    return (LPSTR)0xffffffff;
  }
  if (param_1 == 2) {
                    /* WARNING: Subroutine does not return */
    __exit(0);
  }
  if (param_1 == 0) {
    WaitForSingleObject(local_54.hProcess,0xffffffff);
    GetExitCodeProcess(local_54.hProcess,(LPDWORD)&param_3);
    CloseHandle(local_54.hProcess);
    CloseHandle(local_54.hThread);
    return param_3;
  }
  if (param_1 == 4) {
    CloseHandle(local_54.hProcess);
    param_3 = (LPSTR)0x0;
    CloseHandle(local_54.hThread);
    return param_3;
  }
  param_3 = local_54.hProcess;
  CloseHandle(local_54.hThread);
  return param_3;
}


/* ==== FUN_0048e720 @ 0048e720 ==== */

undefined4 __thiscall
FUN_0048e720(void *this,undefined4 *param_1,undefined4 *param_2,int *param_3,int *param_4)

{
  char cVar1;
  int extraout_EAX;
  char *extraout_EAX_00;
  int extraout_EAX_01;
  uint uVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int *piVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  int *local_4;
  
  uVar6 = 2;
  pcVar4 = (char *)*param_1;
  puVar3 = param_1;
  while (pcVar4 != (char *)0x0) {
    uVar2 = 0xffffffff;
    puVar3 = puVar3 + 1;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    uVar6 = uVar6 + ~uVar2;
    pcVar4 = (char *)*puVar3;
  }
  malloc(uVar6);
  *param_3 = extraout_EAX;
  if (extraout_EAX == 0) {
    *param_4 = 0;
    errno = 0xc;
    _doserrno = 8;
    return 0xffffffff;
  }
  if (param_2 != (undefined4 *)0x0) {
    uVar6 = 2;
    pcVar4 = (char *)*param_2;
    puVar3 = param_2;
    while (pcVar4 != (char *)0x0) {
      uVar2 = 0xffffffff;
      puVar3 = puVar3 + 1;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      uVar6 = uVar6 + ~uVar2;
      pcVar4 = (char *)*puVar3;
    }
  }
  if (param_2 == (undefined4 *)0x0) {
    *param_4 = 0;
    piVar5 = param_4;
    local_4 = this;
  }
  else {
    if (_aenvptr == (char *)0x0) {
      __crtGetEnvironmentStringsA();
      _aenvptr = extraout_EAX_00;
      if (extraout_EAX_00 == (char *)0x0) {
        return 0xffffffff;
      }
    }
    local_4 = (int *)0x0;
    if (*_aenvptr != '\0') {
      cVar1 = *_aenvptr;
      pcVar4 = _aenvptr;
      do {
        if (cVar1 == '=') break;
        uVar2 = 0xffffffff;
        do {
          if (uVar2 == 0) break;
          uVar2 = uVar2 - 1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
        local_4 = (int *)((int)local_4 + ~uVar2);
        pcVar4 = (char *)((int)local_4 + (int)_aenvptr);
        cVar1 = *pcVar4;
      } while (cVar1 != '\0');
    }
    cVar1 = *(char *)((int)local_4 + (int)_aenvptr);
    piVar5 = local_4;
    while ((((cVar1 == '=' && (_aenvptr[(int)piVar5 + 1] != '\0')) &&
            (_aenvptr[(int)piVar5 + 2] == ':')) && (_aenvptr[(int)piVar5 + 3] == '='))) {
      uVar2 = 0xffffffff;
      pcVar4 = (char *)((int)(piVar5 + 1) + (int)_aenvptr);
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      piVar5 = (int *)((int)piVar5 + ~uVar2 + 4);
      cVar1 = *(char *)((int)piVar5 + (int)_aenvptr);
    }
    malloc((int)piVar5 + (uVar6 - (int)local_4));
    *param_4 = extraout_EAX_01;
    if (extraout_EAX_01 == 0) {
      free((void *)*param_3);
      *param_3 = 0;
      errno = 0xc;
      _doserrno = 8;
      return 0xffffffff;
    }
  }
  pcVar4 = (char *)*param_3;
  if ((char *)*param_1 == (char *)0x0) {
    pcVar4 = pcVar4 + 1;
  }
  else {
    uVar6 = 0xffffffff;
    pcVar7 = (char *)*param_1;
    do {
      pcVar8 = pcVar7;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar7 = pcVar8 + -uVar6;
    pcVar8 = pcVar4;
    for (uVar2 = uVar6 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    pcVar7 = (char *)*param_1;
    param_1 = param_1 + 1;
    uVar6 = 0xffffffff;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    pcVar4 = pcVar4 + ~uVar6;
  }
  pcVar7 = (char *)*param_1;
  while (pcVar7 != (char *)0x0) {
    uVar6 = 0xffffffff;
    do {
      pcVar8 = pcVar7;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar7 = pcVar8 + -uVar6;
    pcVar8 = pcVar4;
    for (uVar2 = uVar6 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    uVar6 = 0xffffffff;
    pcVar7 = (char *)*param_1;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    pcVar4[~uVar6 - 1] = ' ';
    pcVar4 = pcVar4 + (~uVar6 - 1) + 1;
    pcVar7 = (char *)param_1[1];
    param_1 = param_1 + 1;
  }
  pcVar4[-1] = '\0';
  *pcVar4 = '\0';
  pcVar4 = (char *)*param_4;
  if (param_2 != (undefined4 *)0x0) {
    pcVar7 = _aenvptr + (int)local_4;
    pcVar8 = pcVar4;
    for (uVar6 = (uint)((int)piVar5 - (int)local_4) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar6 = (int)piVar5 - (int)local_4 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    pcVar4 = pcVar4 + ((int)piVar5 - (int)local_4);
    pcVar7 = (char *)*param_2;
    while (pcVar7 != (char *)0x0) {
      uVar6 = 0xffffffff;
      do {
        pcVar8 = pcVar7;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      pcVar7 = pcVar8 + -uVar6;
      pcVar8 = pcVar4;
      for (uVar2 = uVar6 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      uVar6 = 0xffffffff;
      pcVar7 = (char *)*param_2;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      pcVar4 = pcVar4 + ~uVar6;
      pcVar7 = (char *)param_2[1];
      param_2 = param_2 + 1;
    }
  }
  if (pcVar4 != (char *)0x0) {
    if (pcVar4 == (char *)*param_4) {
      *pcVar4 = '\0';
      pcVar4 = pcVar4 + 1;
    }
    *pcVar4 = '\0';
  }
  free(_aenvptr);
  _aenvptr = (char *)0x0;
  return 0;
}


/* ==== __crtCompareStringA @ 0048e9e0 ==== */

int __cdecl __crtCompareStringA(ulong lcid,ulong flags,char *s1,int n1,char *s2,int n2,int codepage)

{
  int iVar1;
  BOOL BVar2;
  BYTE *pBVar3;
  int cchWideChar;
  PCNZWCH lpWideCharStr;
  LPWSTR lpWideCharStr_00;
  int iVar4;
  int local_18;
  _cpinfo local_14;
  
  if (DAT_00505760 == 0) {
    iVar1 = CompareStringA(0,0,"",1,"",1);
    if (iVar1 == 0) {
      iVar1 = CompareStringW(0,0,L"",1,L"",1);
      if (iVar1 == 0) {
        return 0;
      }
      DAT_00505760 = 1;
    }
    else {
      DAT_00505760 = 2;
    }
  }
  iVar1 = n1;
  if (0 < n1) {
    iVar1 = __ansicp((int)s1,n1);
  }
  if (0 < n2) {
    n2 = __ansicp((int)s2,n2);
  }
  if (DAT_00505760 == 2) {
    iVar1 = CompareStringA(lcid,flags,s1,iVar1,s2,n2);
    return iVar1;
  }
  local_18 = DAT_00505760;
  if (DAT_00505760 == 1) {
    local_18 = 0;
    n1 = 0;
    if (codepage == 0) {
      codepage = DAT_005055e0;
    }
    if ((iVar1 == 0) || (n2 == 0)) {
      if (iVar1 == n2) {
        return 2;
      }
      if (1 < n2) {
        return 1;
      }
      if (1 < iVar1) {
        return 3;
      }
      BVar2 = GetCPInfo(codepage,&local_14);
      if (BVar2 == 0) {
        return 0;
      }
      if (0 < iVar1) {
        if (local_14.MaxCharSize < 2) {
          return 3;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 3;
          }
          if ((*pBVar3 <= (byte)*s1) && ((byte)*s1 <= pBVar3[1])) break;
          local_14.LeadByte[0] = pBVar3[2];
          pBVar3 = pBVar3 + 2;
        }
        return 2;
      }
      if (0 < n2) {
        if (local_14.MaxCharSize < 2) {
          return 1;
        }
        pBVar3 = local_14.LeadByte;
        while( true ) {
          if ((local_14.LeadByte[0] == 0) || (pBVar3[1] == 0)) {
            return 1;
          }
          if ((*pBVar3 <= (byte)*s2) && ((byte)*s2 <= pBVar3[1])) break;
          local_14.LeadByte[0] = pBVar3[2];
          pBVar3 = pBVar3 + 2;
        }
        return 2;
      }
    }
    cchWideChar = MultiByteToWideChar(codepage,9,s1,iVar1,(LPWSTR)0x0,0);
    if (cchWideChar == 0) {
      return 0;
    }
    malloc(cchWideChar * 2);
    if (lpWideCharStr == (PCNZWCH)0x0) {
      return 0;
    }
    iVar1 = MultiByteToWideChar(codepage,1,s1,iVar1,lpWideCharStr,cchWideChar);
    if ((((iVar1 != 0) && (iVar1 = MultiByteToWideChar(codepage,9,s2,n2,(LPWSTR)0x0,0), iVar1 != 0))
        && (malloc(iVar1 * 2), n1 = (int)lpWideCharStr_00, lpWideCharStr_00 != (LPWSTR)0x0)) &&
       (iVar4 = MultiByteToWideChar(codepage,1,s2,n2,lpWideCharStr_00,iVar1), iVar4 != 0)) {
      local_18 = CompareStringW(lcid,flags,lpWideCharStr,cchWideChar,lpWideCharStr_00,iVar1);
    }
    free(lpWideCharStr);
    free((void *)n1);
  }
  return local_18;
}


/* ==== __ansicp @ 0048ecb0 ==== */

int __cdecl __ansicp(int lcid)

{
  char *pcVar1;
  int iVar2;
  int in_stack_00000008;
  
  iVar2 = in_stack_00000008;
  for (pcVar1 = (char *)lcid; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0'));
      pcVar1 = pcVar1 + 1) {
  }
  if (*pcVar1 != '\0') {
    return in_stack_00000008;
  }
  return (int)pcVar1 - lcid;
}


/* ==== __crtsetenv @ 0048ece0 ==== */

int __cdecl __crtsetenv(char *option,int primary)

{
  char **ppcVar1;
  char **p;
  char cVar2;
  byte *pbVar3;
  undefined3 extraout_var;
  int iVar4;
  char **extraout_EAX;
  undefined4 *extraout_EAX_00;
  int len;
  char **extraout_EAX_01;
  LPCSTR lpName;
  char **extraout_EAX_02;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  bool bVar9;
  
  if (option == (char *)0x0) {
    return -1;
  }
  pbVar3 = FUN_0048e3f0((byte *)option,0x3d);
  if (pbVar3 == (byte *)0x0) {
    return -1;
  }
  if ((byte *)option == pbVar3) {
    return -1;
  }
  bVar9 = pbVar3[1] == 0;
  if (_environ == __initenv) {
    cVar2 = copy_environ(_environ);
    _environ = (char **)CONCAT31(extraout_var,cVar2);
  }
  if (_environ == (char **)0x0) {
    if ((primary == 0) || (_wenviron == (undefined4 *)0x0)) {
      if (bVar9) {
        return 0;
      }
      malloc(4);
      if (extraout_EAX == (char **)0x0) {
        _environ = extraout_EAX;
        return -1;
      }
      _environ = extraout_EAX;
      *extraout_EAX = (char *)0x0;
      if (_wenviron == (undefined4 *)0x0) {
        malloc(4);
        if (extraout_EAX_00 == (undefined4 *)0x0) {
          _wenviron = extraout_EAX_00;
          return -1;
        }
        _wenviron = extraout_EAX_00;
        *extraout_EAX_00 = 0;
      }
    }
    else {
      iVar4 = __wtomb_environ();
      if (iVar4 != 0) {
        return -1;
      }
    }
  }
  p = _environ;
  len = (int)pbVar3 - (int)option;
  iVar4 = findenv(option,len);
  if ((iVar4 < 0) || (*p == (char *)0x0)) {
    if (bVar9) {
      return 0;
    }
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    realloc(p,iVar4 * 4 + 8);
    if (extraout_EAX_02 == (char **)0x0) {
      return -1;
    }
    extraout_EAX_02[iVar4] = option;
    extraout_EAX_02[iVar4 + 1] = (char *)0x0;
    _environ = extraout_EAX_02;
  }
  else if (bVar9) {
    free(p[iVar4]);
    pcVar7 = p[iVar4];
    ppcVar1 = p + iVar4;
    while (pcVar7 != (char *)0x0) {
      *ppcVar1 = ppcVar1[1];
      iVar4 = iVar4 + 1;
      pcVar7 = ppcVar1[1];
      ppcVar1 = ppcVar1 + 1;
    }
    realloc(p,iVar4 * 4);
    if (extraout_EAX_01 != (char **)0x0) {
      _environ = extraout_EAX_01;
    }
  }
  else {
    p[iVar4] = option;
  }
  if (primary != 0) {
    uVar5 = 0xffffffff;
    pcVar7 = option;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar2 != '\0');
    malloc(~uVar5 + 1);
    if (lpName != (LPCSTR)0x0) {
      uVar5 = 0xffffffff;
      do {
        pcVar7 = option;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar7 = option + 1;
        cVar2 = *option;
        option = pcVar7;
      } while (cVar2 != '\0');
      uVar5 = ~uVar5;
      pcVar7 = pcVar7 + -uVar5;
      pcVar8 = lpName;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar8 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      }
      lpName[len] = '\0';
      SetEnvironmentVariableA(lpName,(LPCSTR)(~-(uint)bVar9 & (uint)(lpName + len + 1)));
      free(lpName);
      return 0;
    }
  }
  return 0;
}


/* ==== findenv @ 0048eef0 ==== */

int __cdecl findenv(char *name,int len)

{
  char *b;
  int iVar1;
  int *piVar2;
  
  b = (char *)*_environ;
  piVar2 = _environ;
  if (b == (char *)0x0) {
    return 0;
  }
  while ((iVar1 = _strnicoll(name,b,len), iVar1 != 0 ||
         ((*(char *)(*piVar2 + len) != '=' && (*(char *)(*piVar2 + len) != '\0'))))) {
    b = (char *)piVar2[1];
    piVar2 = piVar2 + 1;
    if (b == (char *)0x0) {
      return -((int)piVar2 - (int)_environ >> 2);
    }
  }
  return (int)piVar2 - (int)_environ >> 2;
}


/* ==== copy_environ @ 0048ef70 ==== */

char __cdecl copy_environ(char **oldenviron)

{
  char *pcVar1;
  char cVar2;
  char **ppcVar3;
  undefined4 *extraout_EAX;
  undefined3 extraout_var;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = 0;
  if (oldenviron != (char **)0x0) {
    pcVar1 = *oldenviron;
    ppcVar3 = oldenviron;
    while (pcVar1 != (char *)0x0) {
      ppcVar3 = ppcVar3 + 1;
      iVar4 = iVar4 + 1;
      pcVar1 = *ppcVar3;
    }
    malloc(iVar4 * 4 + 4);
    if (extraout_EAX == (undefined4 *)0x0) {
      _amsg_exit(9);
    }
    pcVar1 = *oldenviron;
    puVar5 = extraout_EAX;
    while (pcVar1 != (char *)0x0) {
      oldenviron = oldenviron + 1;
      cVar2 = _strdup(pcVar1);
      *puVar5 = CONCAT31(extraout_var,cVar2);
      puVar5 = puVar5 + 1;
      pcVar1 = *oldenviron;
    }
    *puVar5 = 0;
    return (char)extraout_EAX;
  }
  return '\0';
}


/* ==== __strgtold12 @ 0048efe0 ==== */

uint __cdecl
__strgtold12(void *pld12,char **p_end_ptr,char *str,int mult12,int scale,int decpt,int implicit_E)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint uVar13;
  char *pcVar14;
  byte *pbVar15;
  int local_60;
  char *local_5c;
  uint local_54;
  byte *local_50;
  int local_4c;
  int local_48;
  uint local_30;
  ushort local_2c;
  undefined2 uStack_2a;
  undefined2 uStack_28;
  char *local_26;
  ushort local_22;
  char local_1c [23];
  char local_5;
  
  local_5c = local_1c;
  iVar8 = 0;
  uVar13 = 0;
  uVar7 = 0;
  local_4c = 1;
  local_54 = 0;
  bVar2 = false;
  bVar4 = false;
  bVar3 = false;
  bVar5 = false;
  bVar6 = false;
  local_48 = 0;
  local_60 = 0;
  local_30 = 0;
  local_50 = (byte *)str;
  for (pbVar11 = (byte *)str;
      (((bVar10 = *pbVar11, bVar10 == 0x20 || (bVar10 == 9)) || (bVar10 == 10)) ||
      (pbVar15 = (byte *)str, bVar10 == 0xd)); pbVar11 = pbVar11 + 1) {
  }
  do {
    bVar10 = *pbVar11;
    pbVar12 = pbVar11 + 1;
    str = (char *)CONCAT31(str._1_3_,bVar10);
    switch(iVar8) {
    case 0:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_0048f4b2;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 5;
      }
      else if (bVar10 == 0x2b) {
        iVar8 = 2;
        uVar7 = 0;
      }
      else if (bVar10 == 0x2d) {
        iVar8 = 2;
        uVar7 = 0x8000;
      }
      else {
        if (bVar10 != 0x30) goto switchD_0048f2a2_caseD_2c;
        iVar8 = 1;
      }
      break;
    case 1:
      bVar2 = true;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_0048f4b2;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 4;
      }
      else {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_0048f2a2_caseD_2b;
        default:
          goto switchD_0048f2a2_caseD_2c;
        case 0x30:
switchD_0048f116_caseD_30:
          iVar8 = 1;
          break;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_0048f2a2_caseD_44;
        }
      }
      break;
    case 2:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 3;
        goto LAB_0048f4b2;
      }
      if (bVar10 == __decimal_point) {
        iVar8 = 5;
      }
      else {
        if (bVar10 == 0x30) goto switchD_0048f116_caseD_30;
        iVar8 = 10;
        pbVar12 = pbVar15;
      }
      break;
    case 3:
      while( true ) {
        bVar2 = true;
        if (__mb_cur_max < 2) {
          uVar9 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)str & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *local_5c = bVar10 - 0x30;
          bVar10 = *pbVar12;
          local_5c = local_5c + 1;
          str = (char *)CONCAT31(str._1_3_,bVar10);
          pbVar12 = pbVar12 + 1;
        }
        else {
          bVar10 = *pbVar12;
          local_60 = local_60 + 1;
          str = (char *)CONCAT31(str._1_3_,bVar10);
          pbVar12 = pbVar12 + 1;
        }
      }
      local_54 = uVar13;
      if (bVar10 != __decimal_point) {
        switch(bVar10) {
        case 0x2b:
        case 0x2d:
          goto switchD_0048f2a2_caseD_2b;
        case 0x44:
        case 0x45:
        case 100:
        case 0x65:
          goto switchD_0048f2a2_caseD_44;
        }
switchD_0048f2a2_caseD_2c:
        iVar8 = 10;
        goto LAB_0048f4b2;
      }
      iVar8 = 4;
      break;
    case 4:
      bVar4 = true;
      if (uVar13 == 0) {
        while (bVar10 == 0x30) {
          bVar10 = *pbVar12;
          local_60 = local_60 + -1;
          pbVar12 = pbVar12 + 1;
          str._1_3_ = (undefined3)((uint)str >> 8);
          str = (char *)CONCAT31(str._1_3_,bVar10);
        }
      }
      while( true ) {
        bVar2 = true;
        if (__mb_cur_max < 2) {
          uVar9 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar9 = _isctype((uint)str & 0xff,4);
        }
        if (uVar9 == 0) break;
        if (uVar13 < 0x19) {
          uVar13 = uVar13 + 1;
          *local_5c = bVar10 - 0x30;
          local_5c = local_5c + 1;
          local_60 = local_60 + -1;
        }
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      local_54 = uVar13;
      switch(bVar10) {
      case 0x2b:
      case 0x2d:
switchD_0048f2a2_caseD_2b:
        bVar2 = true;
        pbVar12 = pbVar12 + -1;
        iVar8 = 0xb;
        break;
      default:
        goto switchD_0048f2a2_caseD_2c;
      case 0x44:
      case 0x45:
      case 100:
      case 0x65:
switchD_0048f2a2_caseD_44:
        bVar2 = true;
        iVar8 = 6;
      }
      break;
    case 5:
      bVar4 = true;
      if (__mb_cur_max < 2) {
        uVar9 = (byte)_pctype[(uint)bVar10 * 2] & 4;
      }
      else {
        uVar9 = _isctype((uint)bVar10,4);
      }
      if (uVar9 == 0) {
        iVar8 = 10;
        pbVar12 = pbVar15;
      }
      else {
        iVar8 = 4;
        pbVar12 = pbVar11;
      }
      break;
    case 6:
      pbVar11 = pbVar11 + -1;
      pbVar15 = pbVar11;
      local_50 = pbVar11;
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_0048f4b2;
      }
      if (bVar10 == 0x2b) {
LAB_0048f4a6:
        iVar8 = 7;
        pbVar15 = pbVar11;
        local_50 = pbVar11;
      }
      else {
        if (bVar10 != 0x2d) goto LAB_0048f396;
LAB_0048f497:
        iVar8 = 7;
        local_4c = -1;
        pbVar15 = pbVar11;
        local_50 = pbVar11;
      }
      break;
    case 7:
      if (('0' < (char)bVar10) && ((char)bVar10 < ':')) {
        iVar8 = 9;
        goto LAB_0048f4b2;
      }
LAB_0048f396:
      if (bVar10 == 0x30) {
        iVar8 = 8;
      }
      else {
        iVar8 = 10;
        pbVar12 = pbVar15;
      }
      break;
    case 8:
      bVar3 = true;
      while (bVar10 == 0x30) {
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
      }
      if (((char)bVar10 < '1') || ('9' < (char)bVar10)) goto switchD_0048f2a2_caseD_2c;
      iVar8 = 9;
LAB_0048f4b2:
      pbVar12 = pbVar12 + -1;
      break;
    case 9:
      bVar3 = true;
      local_48 = 0;
      while( true ) {
        if (__mb_cur_max < 2) {
          uVar13 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)str & 0xff,4);
        }
        if (uVar13 == 0) goto LAB_0048f41a;
        local_48 = (char)bVar10 + -0x30 + local_48 * 10;
        if (0x1450 < local_48) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      local_48 = 0x1451;
LAB_0048f41a:
      while( true ) {
        if (__mb_cur_max < 2) {
          uVar13 = (byte)_pctype[((uint)str & 0xff) * 2] & 4;
        }
        else {
          uVar13 = _isctype((uint)str & 0xff,4);
        }
        if (uVar13 == 0) break;
        bVar10 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        str = (char *)CONCAT31(str._1_3_,bVar10);
      }
      iVar8 = 10;
      pbVar12 = pbVar12 + -1;
      uVar13 = local_54;
      pbVar15 = local_50;
      break;
    case 0xb:
      if (implicit_E == 0) goto switchD_0048f2a2_caseD_2c;
      if (bVar10 == 0x2b) goto LAB_0048f4a6;
      if (bVar10 == 0x2d) goto LAB_0048f497;
      iVar8 = 10;
      pbVar12 = pbVar11;
      pbVar15 = pbVar11;
      local_50 = pbVar11;
    }
    pbVar11 = pbVar12;
  } while (iVar8 != 10);
  *p_end_ptr = (char *)pbVar12;
  if (bVar2) {
    if (0x18 < uVar13) {
      if ('\x04' < local_5) {
        local_5 = local_5 + '\x01';
      }
      local_5c = local_5c + -1;
      local_60 = local_60 + 1;
      uVar13 = 0x18;
    }
    if (uVar13 == 0) {
      local_2c = 0;
      local_22 = 0;
      str = (char *)0x0;
      pcVar14 = (char *)0x0;
      goto LAB_0048f584;
    }
    cVar1 = local_5c[-1];
    while (cVar1 == '\0') {
      uVar13 = uVar13 - 1;
      local_60 = local_60 + 1;
      cVar1 = local_5c[-2];
      local_5c = local_5c + -1;
    }
    FUN_0048faf0(local_1c,uVar13,(uint *)&local_2c);
    if (local_4c < 0) {
      local_48 = -local_48;
    }
    uVar13 = local_48 + local_60;
    if (!bVar3) {
      uVar13 = uVar13 + scale;
    }
    if (!bVar4) {
      uVar13 = uVar13 - decpt;
    }
    if ((int)uVar13 < 0x1451) {
      if (-0x1451 < (int)uVar13) {
        FUN_00490520((int *)&local_2c,uVar13,mult12);
        pcVar14 = (char *)CONCAT22(uStack_28,uStack_2a);
        str = local_26;
        goto LAB_0048f584;
      }
      bVar6 = true;
    }
    else {
      bVar5 = true;
    }
  }
  local_2c = (ushort)str;
  pcVar14 = str;
  local_22 = local_2c;
LAB_0048f584:
  if (bVar2) {
    if (bVar5) {
      pcVar14 = (char *)0x0;
      local_22 = 0x7fff;
      str = (char *)0x80000000;
      local_2c = 0;
      local_30 = 2;
    }
    else if (bVar6) {
      local_2c = 0;
      local_22 = 0;
      str = (char *)0x0;
      pcVar14 = (char *)0x0;
      local_30 = 1;
    }
  }
  else {
    local_2c = 0;
    local_22 = 0;
    str = (char *)0x0;
    pcVar14 = (char *)0x0;
    local_30 = 4;
  }
  *(ushort *)pld12 = local_2c;
  *(char **)((int)pld12 + 2) = pcVar14;
  *(char **)((int)pld12 + 6) = str;
  *(ushort *)((int)pld12 + 10) = local_22 | uVar7;
  return local_30;
}


/* ==== FUN_0048f770 @ 0048f770 ==== */

void __cdecl FUN_0048f770(uint param_1,int *param_2,ushort *param_3)

{
  int iVar1;
  uint flags;
  undefined1 local_58 [40];
  int local_30;
  int local_2c;
  uint local_20;
  
  param_3 = (ushort *)(uint)*param_3;
  switch(*param_2) {
  case 1:
  case 5:
    flags = 8;
    break;
  case 2:
    flags = 4;
    break;
  case 3:
    flags = 0x11;
    break;
  case 4:
    flags = 0x12;
    break;
  default:
    goto switchD_0048f78f_caseD_6;
  case 7:
    *param_2 = 1;
    goto switchD_0048f78f_caseD_6;
  case 8:
    flags = 0x10;
  }
  iVar1 = _handle_exc(flags,(double *)(param_2 + 6),(uint)param_3);
  if (iVar1 == 0) {
    if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
      local_30 = param_2[4];
      local_20 = local_20 & 0xffffffe3 | 3;
      local_2c = param_2[5];
    }
    else {
      local_20 = local_20 & 0xfffffffe;
    }
    _raise_exc(local_58,(ulong *)&param_3,flags,param_1,(double *)(param_2 + 2),
               (double *)(param_2 + 6));
  }
switchD_0048f78f_caseD_6:
  _ctrlfp((uint)param_3,0xffff);
  iVar1 = 0;
  if ((*param_2 != 8) && (DAT_004daa18 == 0)) {
    iVar1 = FUN_00490c50(param_2);
  }
  if (iVar1 == 0) {
    FUN_00490c20(*param_2);
  }
  return;
}


/* ==== gmtime @ 0048f890 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl gmtime(long *timer)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  
  bVar1 = false;
  iVar5 = *timer;
  if (-1 < iVar5) {
    iVar3 = iVar5 % 0x7861f80;
    iVar5 = (iVar5 / 0x7861f80) * 4;
    _DAT_0050577c = iVar5 + 0x46;
    iVar4 = iVar3;
    if (0x1e1337f < iVar3) {
      iVar4 = iVar3 + -0x1e13380;
      _DAT_0050577c = iVar5 + 0x47;
      if (0x1e1337f < iVar4) {
        iVar4 = iVar3 + -0x3c26700;
        _DAT_0050577c = iVar5 + 0x48;
        if (iVar4 < 0x1e28500) {
          bVar1 = true;
        }
        else {
          _DAT_0050577c = iVar5 + 0x49;
          iVar4 = iVar3 + -0x5a4ec00;
        }
      }
    }
    puVar6 = (undefined4 *)&DAT_004da8c8;
    _DAT_00505784 = iVar4 / 0x15180;
    if (!bVar1) {
      puVar6 = &DAT_004da900;
    }
    iVar3 = 1;
    iVar5 = puVar6[1];
    puVar2 = puVar6;
    while (iVar5 < _DAT_00505784) {
      iVar3 = iVar3 + 1;
      iVar5 = puVar2[2];
      puVar2 = puVar2 + 1;
    }
    _DAT_00505778 = iVar3 + -1;
    _DAT_00505774 = _DAT_00505784 - puVar6[iVar3 + -1];
    _DAT_00505788 = 0;
    _DAT_00505780 = (*timer / 0x15180 + 4) % 7;
    _DAT_00505770 = (iVar4 % 0x15180) / 0xe10;
    iVar5 = (iVar4 % 0x15180) % 0xe10;
    _DAT_0050576c = iVar5 / 0x3c;
    _DAT_00505768 = iVar5 % 0x3c;
    return;
  }
  return;
}


/* ==== FUN_0048f9f0 @ 0048f9f0 ==== */

undefined4 __cdecl FUN_0048f9f0(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = param_2 + param_1;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    uVar2 = 1;
  }
  *param_3 = uVar1;
  return uVar2;
}


/* ==== FUN_0048fa20 @ 0048fa20 ==== */

void __cdecl FUN_0048fa20(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = FUN_0048f9f0(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_0048f9f0(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = FUN_0048f9f0(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  FUN_0048f9f0(param_1[2],param_2[2],param_1 + 2);
  return;
}


/* ==== FUN_0048fa90 @ 0048fa90 ==== */

void __cdecl FUN_0048fa90(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = uVar1 * 2;
  param_1[1] = uVar2 * 2 | uVar1 >> 0x1f;
  param_1[2] = param_1[2] << 1 | uVar2 >> 0x1f;
  return;
}


/* ==== FUN_0048fac0 @ 0048fac0 ==== */

void __cdecl FUN_0048fac0(uint *param_1)

{
  uint uVar1;
  
  uVar1 = param_1[1];
  param_1[1] = uVar1 >> 1 | param_1[2] << 0x1f;
  param_1[2] = param_1[2] >> 1;
  *param_1 = *param_1 >> 1 | uVar1 << 0x1f;
  return;
}


/* ==== FUN_0048faf0 @ 0048faf0 ==== */

void __cdecl FUN_0048faf0(char *param_1,int param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  short sVar3;
  uint local_c;
  uint local_8;
  uint local_4;
  
  puVar2 = param_3;
  sVar3 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  if (param_2 != 0) {
    param_3 = (uint *)param_2;
    do {
      local_c = *puVar2;
      local_8 = puVar2[1];
      local_4 = puVar2[2];
      FUN_0048fa90(puVar2);
      FUN_0048fa90(puVar2);
      FUN_0048fa20(puVar2,&local_c);
      FUN_0048fa90(puVar2);
      local_c = (uint)*param_1;
      local_8 = 0;
      local_4 = 0;
      FUN_0048fa20(puVar2,&local_c);
      param_1 = param_1 + 1;
      param_3 = (uint *)((int)param_3 + -1);
    } while (param_3 != (uint *)0x0);
  }
  uVar1 = puVar2[2];
  while (uVar1 == 0) {
    sVar3 = sVar3 + -0x10;
    puVar2[2] = puVar2[1] >> 0x10;
    uVar1 = puVar2[2];
    puVar2[1] = *puVar2 >> 0x10 | puVar2[1] << 0x10;
    *puVar2 = *puVar2 << 0x10;
  }
  uVar1 = puVar2[2];
  while ((uVar1 & 0x8000) == 0) {
    FUN_0048fa90(puVar2);
    sVar3 = sVar3 + -1;
    uVar1 = puVar2[2];
  }
  *(short *)((int)puVar2 + 10) = sVar3;
  return;
}


/* ==== FUN_0048fbf0 @ 0048fbf0 ==== */

undefined4 __cdecl
FUN_0048fbf0(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  ushort uVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  short *psVar8;
  int iVar9;
  short sVar10;
  int iVar11;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  undefined2 local_10;
  undefined4 uStack_e;
  undefined4 uStack_a;
  undefined1 local_6;
  char cStack_5;
  
  psVar1 = param_6;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xcc;
  local_15 = 0xcc;
  local_14 = 0xcc;
  local_13 = 0xcc;
  uVar5 = param_3 & 0x7fff;
  local_12 = 0xfb;
  local_11 = 0x3f;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar5 == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
LAB_0048fdff:
    *(undefined1 *)(psVar1 + 1) = 0x20;
    *(undefined1 *)((int)psVar1 + 3) = 1;
    *(undefined1 *)(psVar1 + 2) = 0x30;
    *(undefined1 *)((int)psVar1 + 5) = 0;
    return 1;
  }
  if ((short)uVar5 == 0x7fff) {
    *param_6 = 1;
    if (((param_2 != 0x80000000) || (param_1 != 0)) && ((param_2 & 0x40000000) == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e53;
      param_6[4] = 0x4e41;
      *(undefined1 *)((int)param_6 + 3) = 6;
      *(undefined1 *)(param_6 + 5) = 0;
      return 0;
    }
    if ((((param_3 & 0x8000) != 0) && (param_2 == 0xc0000000)) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x44;
      return 0;
    }
    if ((param_2 == 0x80000000) && (param_1 == 0)) {
      param_6[2] = 0x2331;
      param_6[3] = 0x4e49;
      *(undefined1 *)((int)param_6 + 3) = 5;
      param_6[4] = 0x46;
      return 0;
    }
    param_6[2] = 0x2331;
    param_6[3] = 0x4e51;
    param_6[4] = 0x4e41;
    *(undefined1 *)((int)param_6 + 3) = 6;
    *(undefined1 *)(param_6 + 5) = 0;
    return 0;
  }
  local_6 = (undefined1)uVar5;
  cStack_5 = (char)(uVar5 >> 8);
  local_10 = 0;
  sVar10 = (short)(((uVar5 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar5 * 0x4d10 >>
                  0x10);
  uStack_a = param_2;
  uStack_e = param_1;
  FUN_00490520((int *)&local_10,-(int)sVar10,1);
  if (0x3ffe < CONCAT11(cStack_5,local_6)) {
    sVar10 = sVar10 + 1;
    FUN_00490260((int *)&local_10,(int *)&local_1c);
  }
  *psVar1 = sVar10;
  iVar9 = param_4;
  if (((param_5 & 1) != 0) && (iVar9 = param_4 + sVar10, param_4 + sVar10 < 1)) {
    *psVar1 = 0;
    goto LAB_0048fdff;
  }
  if (0x15 < iVar9) {
    iVar9 = 0x15;
  }
  uVar2 = CONCAT11(cStack_5,local_6);
  local_6 = 0;
  cStack_5 = '\0';
  iVar6 = 8;
  iVar11 = uVar2 - 0x3ffe;
  do {
    FUN_0048fa90((uint *)&local_10);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if (iVar11 < 0) {
    for (uVar5 = -iVar11 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
      FUN_0048fac0((uint *)&local_10);
    }
  }
  psVar1 = psVar1 + 2;
  iVar9 = iVar9 + 1;
  psVar7 = psVar1;
  uVar5 = uStack_e;
  uVar3 = uStack_a;
  if (0 < iVar9) {
    do {
      uStack_a._2_2_ = (undefined2)(uVar3 >> 0x10);
      uStack_a._0_2_ = (undefined2)uVar3;
      uStack_e._2_2_ = (undefined2)(uVar5 >> 0x10);
      uStack_e._0_2_ = (undefined2)uVar5;
      param_1 = CONCAT22((undefined2)uStack_e,local_10);
      param_2 = CONCAT22((undefined2)uStack_a,uStack_e._2_2_);
      param_3 = CONCAT13(cStack_5,CONCAT12(local_6,uStack_a._2_2_));
      uStack_e = uVar5;
      uStack_a = uVar3;
      FUN_0048fa90((uint *)&local_10);
      FUN_0048fa90((uint *)&local_10);
      FUN_0048fa20((uint *)&local_10,&param_1);
      FUN_0048fa90((uint *)&local_10);
      cVar4 = cStack_5 + '0';
      cStack_5 = '\0';
      *(char *)psVar7 = cVar4;
      psVar7 = (short *)((int)psVar7 + 1);
      iVar9 = iVar9 + -1;
      uVar5 = uStack_e;
      uVar3 = uStack_a;
    } while (iVar9 != 0);
  }
  psVar8 = psVar7 + -1;
  if (*(char *)((int)psVar7 + -1) < '5') {
    if (psVar1 <= psVar8) {
      do {
        if ((char)*psVar8 != '0') break;
        psVar8 = (short *)((int)psVar8 + -1);
      } while (psVar1 <= psVar8);
      if (psVar1 <= psVar8) goto LAB_0048ff56;
    }
    *(char *)psVar1 = '0';
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)((int)param_6 + 5) = 0;
    return 1;
  }
  if (psVar1 <= psVar8) {
    do {
      if ((char)*psVar8 != '9') break;
      *(char *)psVar8 = '0';
      psVar8 = (short *)((int)psVar8 + -1);
    } while (psVar1 <= psVar8);
    if (psVar1 <= psVar8) {
      *(char *)psVar8 = (char)*psVar8 + '\x01';
      goto LAB_0048ff56;
    }
  }
  psVar8 = (short *)((int)psVar8 + 1);
  *param_6 = *param_6 + 1;
  *(char *)psVar8 = *(char *)psVar8 + '\x01';
LAB_0048ff56:
  cVar4 = ((char)psVar8 - (char)param_6) + -3;
  *(char *)((int)param_6 + 3) = cVar4;
  *(undefined1 *)((int)param_6 + cVar4 + 4) = 0;
  return 1;
}


/* ==== FUN_0048ff80 @ 0048ff80 ==== */

int __cdecl FUN_0048ff80(uint param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  if (param_1 < _nhandle) {
    bVar1 = *(byte *)((&__pioinfo)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8);
    if ((bVar1 & 1) != 0) {
      if (param_2 == 0x8000) {
        bVar2 = bVar1 & 0x7f;
      }
      else {
        if (param_2 != 0x4000) {
          errno = 0x16;
          return -1;
        }
        bVar2 = bVar1 | 0x80;
      }
      *(byte *)((&__pioinfo)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) = bVar2;
      return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
    }
  }
  errno = 9;
  return -1;
}


/* ==== FUN_00490000 @ 00490000 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_00490000(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}


/* ==== FUN_00490030 @ 00490030 ==== */

uint __cdecl FUN_00490030(LPSTR param_1,LPCWSTR param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  DWORD DVar5;
  int iVar6;
  LPCWSTR lpWideCharStr;
  BOOL local_4;
  
  uVar4 = param_3;
  lpWideCharStr = param_2;
  uVar2 = 0;
  local_4 = 0;
  if ((param_1 != (LPSTR)0x0) && (param_3 == 0)) {
    return uVar2;
  }
  if (param_1 == (LPSTR)0x0) {
    if (DAT_005055d0 == 0) {
      uVar4 = FUN_0048c880(param_2);
      return uVar4;
    }
    iVar3 = WideCharToMultiByte(DAT_005055e0,0x220,param_2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,&local_4);
    if ((iVar3 != 0) && (local_4 == 0)) {
      return iVar3 - 1;
    }
  }
  else if (DAT_005055d0 == 0) {
    if (param_3 == 0) {
      return 0;
    }
    while ((ushort)*param_2 < 0x100) {
      param_1[uVar2] = (CHAR)*param_2;
      if (*param_2 == L'\0') {
        return uVar2;
      }
      uVar2 = uVar2 + 1;
      param_2 = param_2 + 1;
      if (param_3 <= uVar2) {
        return uVar2;
      }
    }
  }
  else if (__mb_cur_max == 1) {
    iVar3 = 0;
    if (param_3 != 0) {
      iVar3 = FUN_00490220(param_2,param_3);
    }
    uVar4 = WideCharToMultiByte(DAT_005055e0,0x220,lpWideCharStr,iVar3,param_1,iVar3,(LPCSTR)0x0,
                                &local_4);
    if ((uVar4 != 0) && (local_4 == 0)) {
      if (param_1[uVar4 - 1] == '\0') {
        return uVar4 - 1;
      }
      return uVar4;
    }
  }
  else {
    iVar3 = WideCharToMultiByte(DAT_005055e0,0x220,param_2,-1,param_1,param_3,(LPCSTR)0x0,&local_4);
    if (iVar3 == 0) {
      if ((local_4 == 0) && (DVar5 = GetLastError(), DVar5 == 0x7a)) {
        uVar2 = 0;
        if (uVar4 != 0) {
          do {
            iVar3 = WideCharToMultiByte(DAT_005055e0,0,lpWideCharStr,1,(LPSTR)&param_2,__mb_cur_max,
                                        (LPCSTR)0x0,&local_4);
            if (iVar3 == 0) {
              errno = 0x2a;
              return 0xffffffff;
            }
            if (local_4 != 0) {
              errno = 0x2a;
              return 0xffffffff;
            }
            if (uVar4 < iVar3 + uVar2) {
              return uVar2;
            }
            iVar6 = 0;
            if (0 < iVar3) {
              do {
                cVar1 = *(char *)((int)&param_2 + iVar6);
                param_1[uVar2] = cVar1;
                if (cVar1 == '\0') {
                  return uVar2;
                }
                iVar6 = iVar6 + 1;
                uVar2 = uVar2 + 1;
              } while (iVar6 < iVar3);
            }
            lpWideCharStr = lpWideCharStr + 1;
          } while (uVar2 < uVar4);
        }
        return uVar2;
      }
    }
    else if (local_4 == 0) {
      return iVar3 - 1;
    }
  }
  errno = 0x2a;
  return 0xffffffff;
}


/* ==== FUN_00490220 @ 00490220 ==== */

int __cdecl FUN_00490220(short *param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = param_1;
  iVar2 = param_2;
  if (param_2 != 0) {
    do {
      if (*psVar1 == 0) break;
      psVar1 = psVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if ((iVar2 != 0) && (*psVar1 == 0)) {
      return ((int)psVar1 - (int)param_1 >> 1) + 1;
    }
  }
  return param_2;
}


/* ==== FUN_00490260 @ 00490260 ==== */

void __cdecl FUN_00490260(int *param_1,int *param_2)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort uVar6;
  ushort *puVar7;
  ushort *puVar8;
  short *local_20;
  int local_18;
  int local_14;
  int local_10;
  byte local_c;
  undefined1 uStack_b;
  undefined2 uStack_a;
  short local_8;
  undefined2 uStack_6;
  undefined2 local_4;
  ushort uStack_2;
  
  local_14 = 0;
  local_c = 0;
  uStack_b = 0;
  uStack_a = 0;
  local_8 = 0;
  uStack_6 = 0;
  uVar3 = *(ushort *)((int)param_2 + 10) & 0x7fff;
  uVar1 = *(ushort *)((int)param_1 + 10) & 0x7fff;
  uVar6 = (*(ushort *)((int)param_2 + 10) ^ *(ushort *)((int)param_1 + 10)) & 0x8000;
  uVar4 = uVar3 + uVar1;
  local_4 = 0;
  uStack_2 = 0;
  if (((0x7ffe < uVar1) || (0x7ffe < uVar3)) || (0xbffd < uVar4)) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  if (uVar4 < 0x3fc0) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  if (((uVar1 == 0) && (uVar4 = uVar4 + 1, (param_1[2] & 0x7fffffffU) == 0)) &&
     ((param_1[1] == 0 && (*param_1 == 0)))) {
    *(undefined2 *)((int)param_1 + 10) = 0;
    return;
  }
  if (((uVar3 == 0) && (uVar4 = uVar4 + 1, (param_2[2] & 0x7fffffffU) == 0)) &&
     ((param_2[1] == 0 && (*param_2 == 0)))) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  local_20 = &local_8;
  local_18 = 0;
  iVar5 = 5;
  do {
    if (0 < iVar5) {
      puVar8 = (ushort *)(param_2 + 2);
      puVar7 = (ushort *)(local_18 * 2 + (int)param_1);
      local_10 = iVar5;
      do {
        iVar2 = FUN_0048f9f0(*(uint *)(local_20 + -2),(uint)*puVar8 * (uint)*puVar7,
                             (uint *)(local_20 + -2));
        if (iVar2 != 0) {
          *local_20 = *local_20 + 1;
        }
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + -1;
        local_10 = local_10 + -1;
      } while (local_10 != 0);
    }
    local_20 = local_20 + 1;
    local_18 = local_18 + 1;
    iVar5 = iVar5 + -1;
  } while (0 < iVar5);
  uVar4 = uVar4 + 0xc002;
  while ((0 < (short)uVar4 && ((uStack_2 & 0x8000) == 0))) {
    FUN_0048fa90((uint *)&local_c);
    uVar4 = uVar4 - 1;
  }
  if ((short)uVar4 < 1) {
    uVar4 = uVar4 - 1;
    if ((short)uVar4 < 0) {
      iVar5 = -(int)(short)uVar4;
      uVar4 = uVar4 + (short)iVar5;
      do {
        if ((local_c & 1) != 0) {
          local_14 = local_14 + 1;
        }
        FUN_0048fac0((uint *)&local_c);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (local_14 != 0) {
      local_c = local_c | 1;
    }
  }
  if ((0x8000 < CONCAT11(uStack_b,local_c)) ||
     (iVar2 = CONCAT22(local_4,uStack_6), iVar5 = CONCAT22(local_8,uStack_a),
     (CONCAT22(uStack_a,CONCAT11(uStack_b,local_c)) & 0x1ffff) == 0x18000)) {
    if (CONCAT22(local_8,uStack_a) == -1) {
      iVar5 = 0;
      if (CONCAT22(local_4,uStack_6) == -1) {
        if (uStack_2 == 0xffff) {
          uStack_2 = 0x8000;
          uVar4 = uVar4 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
        else {
          uStack_2 = uStack_2 + 1;
          iVar2 = 0;
          iVar5 = 0;
        }
      }
      else {
        iVar2 = CONCAT22(local_4,uStack_6) + 1;
      }
    }
    else {
      iVar5 = CONCAT22(local_8,uStack_a) + 1;
      iVar2 = CONCAT22(local_4,uStack_6);
    }
  }
  local_8 = (short)((uint)iVar5 >> 0x10);
  uStack_a = (undefined2)iVar5;
  local_4 = (undefined2)((uint)iVar2 >> 0x10);
  uStack_6 = (undefined2)iVar2;
  if (0x7ffe < uVar4) {
    param_1[1] = 0;
    *param_1 = 0;
    param_1[2] = (-(uint)(uVar6 != 0) & 0x80000000) + 0x7fff8000;
    return;
  }
  *(undefined2 *)param_1 = uStack_a;
  *(uint *)((int)param_1 + 2) = CONCAT22(uStack_6,local_8);
  *(uint *)((int)param_1 + 6) = CONCAT22(uStack_2,local_4);
  *(ushort *)((int)param_1 + 10) = uVar4 | uVar6;
  return;
}


/* ==== FUN_00490520 @ 00490520 ==== */

void __cdecl FUN_00490520(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined2 local_c;
  undefined4 uStack_a;
  undefined2 uStack_6;
  int local_4;
  
  iVar3 = 0x4da9e0;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      iVar3 = 0x4dab40;
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      iVar3 = iVar3 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        piVar2 = (int *)(iVar3 + uVar1 * 0xc);
        if (0x7fff < *(ushort *)(iVar3 + uVar1 * 0xc)) {
          local_c = (undefined2)*piVar2;
          uStack_a._0_2_ = (undefined2)((uint)*piVar2 >> 0x10);
          uStack_a._2_2_ = (undefined2)piVar2[1];
          uStack_6 = (undefined2)((uint)piVar2[1] >> 0x10);
          local_4 = piVar2[2];
          uStack_a = CONCAT22(uStack_a._2_2_,(undefined2)uStack_a) + -1;
          piVar2 = (int *)&local_c;
        }
        FUN_00490260(param_1,piVar2);
      }
    }
  }
  return;
}


/* ==== _raise_exc @ 004905b0 ==== */

void __cdecl _raise_exc(void *prec,ulong *pcw,int flags,int opcode,double *parg1,double *presult)

{
  ulong *puVar1;
  double *pdVar2;
  uint uVar3;
  void *dwExceptionCode;
  
  puVar1 = pcw;
  *(undefined4 *)((int)prec + 4) = 0;
  *(undefined4 *)((int)prec + 8) = 0;
  *(undefined4 *)((int)prec + 0xc) = 0;
  dwExceptionCode = prec;
  if ((flags & 0x10U) != 0) {
    *(uint *)((int)prec + 4) = *(uint *)((int)prec + 4) | 1;
    dwExceptionCode = (void *)0xc000008f;
  }
  if ((flags & 2U) != 0) {
    dwExceptionCode = (void *)0xc0000093;
    *(uint *)((int)prec + 4) = *(uint *)((int)prec + 4) | 2;
  }
  if ((flags & 1U) != 0) {
    dwExceptionCode = (void *)0xc0000091;
    *(uint *)((int)prec + 4) = *(uint *)((int)prec + 4) | 4;
  }
  if ((flags & 4U) != 0) {
    dwExceptionCode = (void *)0xc000008e;
    *(uint *)((int)prec + 4) = *(uint *)((int)prec + 4) | 8;
  }
  if ((flags & 8U) != 0) {
    dwExceptionCode = (void *)0xc0000090;
    *(uint *)((int)prec + 4) = *(uint *)((int)prec + 4) | 0x10;
  }
  *(ulong *)((int)prec + 8) = (~*pcw & 1) << 4 | *(uint *)((int)prec + 8) & 0xffffffef;
  *(ulong *)((int)prec + 8) = (~*pcw & 4) << 1 | *(uint *)((int)prec + 8) & 0xfffffff7;
  *(ulong *)((int)prec + 8) = ~*pcw >> 1 & 4 | *(uint *)((int)prec + 8) & 0xfffffffb;
  *(ulong *)((int)prec + 8) = ~*pcw >> 3 & 2 | *(uint *)((int)prec + 8) & 0xfffffffd;
  *(ulong *)((int)prec + 8) = ~*pcw >> 5 & 1 | *(uint *)((int)prec + 8) & 0xfffffffe;
  uVar3 = FUN_00490c60();
  pdVar2 = presult;
  if ((uVar3 & 1) != 0) {
    *(uint *)((int)prec + 0xc) = *(uint *)((int)prec + 0xc) | 0x10;
  }
  if ((uVar3 & 4) != 0) {
    *(uint *)((int)prec + 0xc) = *(uint *)((int)prec + 0xc) | 8;
  }
  if ((uVar3 & 8) != 0) {
    *(uint *)((int)prec + 0xc) = *(uint *)((int)prec + 0xc) | 4;
  }
  if ((uVar3 & 0x10) != 0) {
    *(uint *)((int)prec + 0xc) = *(uint *)((int)prec + 0xc) | 2;
  }
  if ((uVar3 & 0x20) != 0) {
    *(uint *)((int)prec + 0xc) = *(uint *)((int)prec + 0xc) | 1;
  }
  uVar3 = *puVar1 & 0xc00;
  if (uVar3 < 0x401) {
    if (uVar3 == 0x400) {
      *(uint *)prec = *(uint *)prec & 0xfffffffd | 1;
    }
    else if (uVar3 == 0) {
      *(uint *)prec = *(uint *)prec & 0xfffffffc;
    }
  }
  else if (uVar3 == 0x800) {
    *(uint *)prec = *(uint *)prec & 0xfffffffe | 2;
  }
  else if (uVar3 == 0xc00) {
    *(uint *)prec = *(uint *)prec | 3;
  }
  uVar3 = *puVar1 & 0x300;
  if (uVar3 == 0) {
    *(uint *)prec = *(uint *)prec & 0xffffffeb | 8;
  }
  else if (uVar3 == 0x200) {
    *(uint *)prec = *(uint *)prec & 0xffffffe7 | 4;
  }
  else if (uVar3 == 0x300) {
    *(uint *)prec = *(uint *)prec & 0xffffffe3;
  }
  *(uint *)prec = *(uint *)prec & 0xfffe001f | (opcode & 0xfffU) << 5;
  *(uint *)((int)prec + 0x20) = *(uint *)((int)prec + 0x20) | 1;
  *(uint *)((int)prec + 0x20) = *(uint *)((int)prec + 0x20) & 0xffffffe3 | 2;
  *(undefined4 *)((int)prec + 0x10) = *(undefined4 *)parg1;
  *(undefined4 *)((int)prec + 0x14) = *(undefined4 *)((int)parg1 + 4);
  *(uint *)((int)prec + 0x50) = *(uint *)((int)prec + 0x50) | 1;
  *(uint *)((int)prec + 0x50) = *(uint *)((int)prec + 0x50) & 0xffffffe3 | 2;
  *(undefined4 *)((int)prec + 0x40) = *(undefined4 *)presult;
  *(undefined4 *)((int)prec + 0x44) = *(undefined4 *)((int)presult + 4);
  FUN_00490c70();
  RaiseException((DWORD)dwExceptionCode,0,1,(ULONG_PTR *)&prec);
  if ((*(byte *)((int)prec + 8) & 0x10) != 0) {
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  if ((*(byte *)((int)prec + 8) & 8) != 0) {
    *puVar1 = *puVar1 & 0xfffffffb;
  }
  if ((*(byte *)((int)prec + 8) & 4) != 0) {
    *puVar1 = *puVar1 & 0xfffffff7;
  }
  if ((*(byte *)((int)prec + 8) & 2) != 0) {
    *puVar1 = *puVar1 & 0xffffffef;
  }
  if ((*(byte *)((int)prec + 8) & 1) != 0) {
    *puVar1 = *puVar1 & 0xffffffdf;
  }
  switch(*(uint *)prec & 3) {
  case 0:
    uVar3 = *puVar1 & 0xfffff3ff;
    break;
  case 1:
    *puVar1 = *puVar1 & 0xfffff7ff | 0x400;
    goto switchD_0049084b_default;
  case 2:
    uVar3 = *puVar1 & 0xfffffbff | 0x800;
    break;
  case 3:
    uVar3 = *puVar1 | 0xc00;
    break;
  default:
    goto switchD_0049084b_default;
  }
  *puVar1 = uVar3;
switchD_0049084b_default:
  uVar3 = *(uint *)prec >> 2 & 7;
  if (uVar3 == 0) {
    *puVar1 = *puVar1 & 0xfffff3ff | 0x300;
  }
  else {
    if (uVar3 == 1) {
      *puVar1 = *puVar1 & 0xfffff3ff | 0x200;
      *(undefined4 *)pdVar2 = *(undefined4 *)((int)prec + 0x40);
      *(undefined4 *)((int)pdVar2 + 4) = *(undefined4 *)((int)prec + 0x44);
      return;
    }
    if (uVar3 == 2) {
      *puVar1 = *puVar1 & 0xfffff3ff;
      *(undefined4 *)pdVar2 = *(undefined4 *)((int)prec + 0x40);
      *(undefined4 *)((int)pdVar2 + 4) = *(undefined4 *)((int)prec + 0x44);
      return;
    }
  }
  *(undefined4 *)pdVar2 = *(undefined4 *)((int)prec + 0x40);
  *(undefined4 *)((int)pdVar2 + 4) = *(undefined4 *)((int)prec + 0x44);
  return;
}


/* ==== _handle_exc @ 004908f0 ==== */

int __cdecl _handle_exc(uint flags,double *presult,uint cw)

{
  ulonglong uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  float10 fVar7;
  uint local_14;
  undefined8 local_10;
  
  uVar5 = flags & 0x1f;
  if (((flags & 8) == 0) || ((cw & 1) == 0)) {
    if (((flags & 4) == 0) || ((cw & 4) == 0)) {
      if (((flags & 1) == 0) || ((cw & 8) == 0)) {
        if (((flags & 2) != 0) && ((cw & 0x10) != 0)) {
          bVar6 = (flags & 0x10) != 0;
          local_10 = *presult;
          if (local_10 == 0.0) {
            bVar6 = true;
          }
          else {
            fVar7 = FUN_00490d60(*(uint *)presult,*(uint *)((int)presult + 4),(int *)&local_14);
            iVar4 = local_14 - 0x600;
            if (iVar4 < -0x432) {
              bVar6 = true;
              *(undefined4 *)presult = 0;
              local_10 = 0.0;
              *(undefined4 *)((int)presult + 4) = 0;
            }
            else {
              local_10 = (double)(ulonglong)
                                 (SUB87((double)fVar7,0) & 0xfffffffffffff | 0x10000000000000);
              if (iVar4 < -0x3fd) {
                iVar4 = -0x3fd - iVar4;
                do {
                  if ((((ulonglong)local_10 & 1) != 0) && (!bVar6)) {
                    bVar6 = true;
                  }
                  uVar5 = (uint)local_10 >> 1;
                  uVar1 = (ulonglong)local_10 & 0x100000000;
                  local_10._0_4_ = uVar5;
                  if (uVar1 != 0) {
                    local_10._0_4_ = uVar5 | 0x80000000;
                  }
                  iVar4 = iVar4 + -1;
                  local_10 = (double)CONCAT44(local_10._4_4_ >> 1,(uint)local_10);
                } while (iVar4 != 0);
              }
              if ((double)fVar7 < 0.0) {
                local_10 = -local_10;
              }
              *(uint *)presult = (uint)local_10;
              *(uint *)((int)presult + 4) = local_10._4_4_;
            }
          }
          if (bVar6) {
            FUN_00490cc0(0x10);
          }
          uVar5 = local_14 & 0xfffffffd;
          local_14 = uVar5;
        }
      }
      else {
        FUN_00490cc0();
        uVar3 = DAT_004dad14;
        uVar2 = DAT_004dad04;
        uVar5 = cw & 0xc00;
        if (uVar5 < 0x401) {
          if (uVar5 == 0x400) {
            if (*presult <= 0.0) {
              local_10 = -(double)CONCAT44(DAT_004dad04,DAT_004dad00);
              *presult = local_10;
              uVar5 = flags & 0x1e;
            }
            else {
              *(undefined4 *)presult = DAT_004dad10;
              *(undefined4 *)((int)presult + 4) = uVar3;
              uVar5 = flags & 0x1e;
            }
            goto LAB_00490bfb;
          }
          if (uVar5 == 0) {
            if (*presult <= 0.0) {
              local_10 = -(double)CONCAT44(DAT_004dad04,DAT_004dad00);
              *presult = local_10;
              uVar5 = flags & 0x1e;
            }
            else {
              *(undefined4 *)presult = DAT_004dad00;
              *(undefined4 *)((int)presult + 4) = uVar2;
              uVar5 = flags & 0x1e;
            }
            goto LAB_00490bfb;
          }
        }
        else if (uVar5 == 0x800) {
          if (0.0 < *presult) {
            *(undefined4 *)presult = DAT_004dad00;
            *(undefined4 *)((int)presult + 4) = uVar2;
            uVar5 = flags & 0x1e;
            goto LAB_00490bfb;
          }
          local_10 = -(double)CONCAT44(DAT_004dad14,DAT_004dad10);
          *presult = local_10;
        }
        else if (uVar5 == 0xc00) {
          if (*presult <= 0.0) {
            local_10 = -(double)CONCAT44(DAT_004dad14,DAT_004dad10);
            *presult = local_10;
            uVar5 = flags & 0x1e;
          }
          else {
            *(undefined4 *)presult = DAT_004dad10;
            *(undefined4 *)((int)presult + 4) = uVar3;
            uVar5 = flags & 0x1e;
          }
          goto LAB_00490bfb;
        }
        uVar5 = flags & 0x1e;
      }
    }
    else {
      FUN_00490cc0();
      uVar5 = flags & 0x1b;
    }
  }
  else {
    FUN_00490cc0();
    uVar5 = flags & 0x17;
  }
LAB_00490bfb:
  if (((flags & 0x10) != 0) && ((cw & 0x20) != 0)) {
    FUN_00490cc0(0x20);
    uVar5 = uVar5 & 0xffffffef;
  }
  return (uint)(uVar5 == 0);
}


/* ==== FUN_00490c20 @ 00490c20 ==== */

void __cdecl FUN_00490c20(int param_1)

{
  if (param_1 == 1) {
    errno = 0x21;
  }
  else if ((1 < param_1) && (param_1 < 4)) {
    errno = 0x22;
    return;
  }
  return;
}


/* ==== FUN_00490c50 @ 00490c50 ==== */

undefined4 FUN_00490c50(void)

{
  return 0;
}


/* ==== FUN_00490c60 @ 00490c60 ==== */

int FUN_00490c60(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}


/* ==== FUN_00490c70 @ 00490c70 ==== */

int FUN_00490c70(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}


/* ==== _ctrlfp @ 00490c90 ==== */

uint _ctrlfp(uint newctrl,uint mask)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}


/* ==== FUN_00490cc0 @ 00490cc0 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00490cc0(void)

{
  return;
}


/* ==== FUN_00490d20 @ 00490d20 ==== */

float10 __cdecl FUN_00490d20(undefined4 param_1,undefined4 param_2,short param_3)

{
  undefined2 uStack_4;
  
  uStack_4 = (undefined2)param_2;
  return (float10)(double)CONCAT26(param_2._2_2_ & 0x800f | (param_3 + 0x3fe) * 0x10,
                                   CONCAT24(uStack_4,param_1));
}


/* ==== FUN_00490d60 @ 00490d60 ==== */

float10 __cdecl FUN_00490d60(uint param_1,uint param_2,int *param_3)

{
  ushort uVar1;
  double dVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  
  if ((double)CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((undefined2)param_2,param_1)))
      == 0.0) {
    *param_3 = 0;
    return (float10)0.0;
  }
  if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    dVar2 = (double)CONCAT17(param_2._3_1_,
                             CONCAT16(param_2._2_1_,CONCAT24((undefined2)param_2,param_1)));
    iVar5 = -0x3fd;
    uVar4 = param_2;
    uVar3 = param_2;
    while ((uVar3 & 0x100000) == 0) {
      uVar3 = uVar4 << 1;
      param_2._0_2_ = (undefined2)uVar3;
      param_2._2_1_ = (undefined1)(uVar3 >> 0x10);
      param_2._3_1_ = (byte)(uVar3 >> 0x18);
      uVar4 = uVar3;
      if ((param_1 & 0x80000000) != 0) {
        uVar4 = uVar3 | 1;
        param_2._0_2_ = (undefined2)uVar4;
      }
      param_1 = param_1 << 1;
      iVar5 = iVar5 + -1;
    }
    uVar1 = CONCAT11(param_2._3_1_,param_2._2_1_) & 0xffef;
    param_2._2_1_ = (undefined1)uVar1;
    param_2._3_1_ = (byte)(uVar1 >> 8);
    if (dVar2 < 0.0) {
      param_2._3_1_ = param_2._3_1_ | 0x80;
    }
    fVar6 = FUN_00490d20(param_1,CONCAT13(param_2._3_1_,CONCAT12(param_2._2_1_,(undefined2)param_2))
                         ,0);
    *param_3 = iVar5;
    return (float10)(double)fVar6;
  }
  fVar6 = FUN_00490d20(param_1,param_2,0);
  *param_3 = ((param_2 >> 0x10 & 0x7ff0) >> 4) - 0x3fe;
  return (float10)(double)fVar6;
}


/* ==== RtlUnwind @ 00490e60 ==== */

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x00490e60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


/* ==== _getch @ 00490e70 ==== */

int _getch(void)

{
  uint uVar1;
  int iVar2;
  byte *extraout_EAX;
  DWORD local_1c;
  DWORD local_18;
  _INPUT_RECORD local_14;
  
  if (DAT_004db068 != 0xffffffff) {
    uVar1 = DAT_004db068 & 0xff;
    DAT_004db068 = 0xffffffff;
    return uVar1;
  }
  if (DAT_004db070 == (HANDLE)0xffffffff) {
    return -1;
  }
  if (DAT_004db070 == (HANDLE)0xfffffffe) {
    __initconin();
  }
  GetConsoleMode(DAT_004db070,&local_18);
  SetConsoleMode(DAT_004db070,0);
  iVar2 = ReadConsoleInputA(DAT_004db070,&local_14,1,&local_1c);
  do {
    if ((iVar2 == 0) || (local_1c == 0)) {
      uVar1 = 0xffffffff;
LAB_00490f49:
      SetConsoleMode(DAT_004db070,local_18);
      return uVar1;
    }
    if ((local_14.EventType == 1) && (local_14.Event.KeyEvent.bKeyDown != 0)) {
      uVar1 = local_14.Event._10_4_ & 0xff;
      if (uVar1 != 0) goto LAB_00490f49;
      _getextendedkeycode(&local_14.Event);
      if (extraout_EAX != (byte *)0x0) {
        uVar1 = (uint)*extraout_EAX;
        DAT_004db068 = (uint)extraout_EAX[1];
        goto LAB_00490f49;
      }
    }
    iVar2 = ReadConsoleInputA(DAT_004db070,&local_14,1,&local_1c);
  } while( true );
}


/* ==== _getextendedkeycode @ 00490f80 ==== */

void __cdecl _getextendedkeycode(void *pKE)

{
  uint uVar1;
  short *psVar2;
  
  uVar1 = *(uint *)((int)pKE + 0xc);
  if ((uVar1 & 0x100) == 0) {
    return;
  }
  psVar2 = &DAT_004dad28;
  while (*psVar2 != *(short *)((int)pKE + 8)) {
    psVar2 = psVar2 + 5;
    if ((short *)0x4dad9f < psVar2) {
      return;
    }
  }
  if ((uVar1 & 3) != 0) {
    return;
  }
  if ((uVar1 & 0xc) != 0) {
    return;
  }
  if ((uVar1 & 0x10) != 0) {
    return;
  }
  return;
}


/* ==== __strcmpi @ 00491060 ==== */

/* Library Function - Single Match
    __strcmpi
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl __strcmpi(char *_Str1,char *_Str2)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  int c;
  int iVar7;
  
  if (DAT_005055d0 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_004910ae;
        bVar5 = *_Str2;
        _Str2 = _Str2 + 1;
        bVar4 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_004910ae:
    iVar7 = (int)cVar6;
  }
  else {
    c = 0;
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') {
          return iVar7;
        }
        cVar6 = *_Str2;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),cVar6);
        _Str2 = _Str2 + 1;
        cVar1 = *_Str1;
        c = CONCAT31((int3)((uint)c >> 8),cVar1);
        _Str1 = _Str1 + 1;
      } while (cVar6 == cVar1);
      c = tolower(c);
      iVar7 = tolower(iVar7);
    } while ((byte)c == (byte)iVar7);
    uVar2 = (uint)((byte)c < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
  }
  return iVar7;
}


/* ==== remove @ 004915b0 ==== */

int __cdecl remove(char *path)

{
  BOOL BVar1;
  ulong oserrno;
  
  BVar1 = DeleteFileA(path);
  if (BVar1 == 0) {
    oserrno = GetLastError();
  }
  else {
    oserrno = 0;
  }
  if (oserrno != 0) {
    _dosmaperr(oserrno);
    return -1;
  }
  return 0;
}


/* ==== _unlink @ 004915e0 ==== */

int __cdecl _unlink(char *path)

{
  int iVar1;
  
  iVar1 = remove(path);
  return iVar1;
}


/* ==== _fstat @ 004915f0 ==== */

int __cdecl _fstat(int fh,void *buf)

{
  void *pvVar1;
  DWORD DVar2;
  uint uVar3;
  BOOL BVar4;
  long lVar5;
  int iVar6;
  _FILETIME local_4c;
  _SYSTEMTIME local_44;
  _BY_HANDLE_FILE_INFORMATION local_34;
  
  if ((uint)fh < _nhandle) {
    iVar6 = (fh & 0x1fU) * 8;
    if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[fh >> 5]) & 1) != 0) {
      DVar2 = GetFileType(*(HANDLE *)(iVar6 + (&__pioinfo)[fh >> 5]));
      pvVar1 = buf;
      uVar3 = DVar2 & 0xffff7fff;
      if (uVar3 == 1) {
        *(undefined2 *)((int)buf + 6) = 0;
        *(undefined2 *)((int)buf + 0xc) = 0;
        *(undefined2 *)((int)buf + 10) = 0;
        *(undefined2 *)((int)buf + 4) = 0;
        *(undefined2 *)((int)buf + 8) = 1;
        BVar4 = GetFileInformationByHandle(*(HANDLE *)(iVar6 + (&__pioinfo)[fh >> 5]),&local_34);
        if (BVar4 != 0) {
          if (((byte)local_34.dwFileAttributes & 1) == 0) {
            *(ushort *)((int)pvVar1 + 6) = *(ushort *)((int)pvVar1 + 6) | 0x1b6;
          }
          else {
            *(ushort *)((int)pvVar1 + 6) = *(ushort *)((int)pvVar1 + 6) | 0x124;
          }
          BVar4 = FileTimeToLocalFileTime(&local_34.ftLastWriteTime,&local_4c);
          if ((BVar4 != 0) && (BVar4 = FileTimeToSystemTime(&local_4c,&local_44), BVar4 != 0)) {
            lVar5 = __loctotime_t((uint)local_44.wYear,(uint)local_44.wMonth,(uint)local_44.wDay,
                                  (uint)local_44.wHour,(uint)local_44.wMinute,(uint)local_44.wSecond
                                  ,-1);
            *(long *)((int)pvVar1 + 0x1c) = lVar5;
            if ((local_34.ftLastAccessTime.dwLowDateTime != 0) ||
               (local_34.ftLastAccessTime.dwHighDateTime != 0)) {
              BVar4 = FileTimeToLocalFileTime(&local_34.ftLastAccessTime,&local_4c);
              if (BVar4 == 0) {
                return -1;
              }
              BVar4 = FileTimeToSystemTime(&local_4c,&local_44);
              if (BVar4 == 0) {
                return -1;
              }
              lVar5 = __loctotime_t((uint)local_44.wYear,(uint)local_44.wMonth,(uint)local_44.wDay,
                                    (uint)local_44.wHour,(uint)local_44.wMinute,
                                    (uint)local_44.wSecond,-1);
            }
            *(long *)((int)pvVar1 + 0x18) = lVar5;
            if ((local_34.ftCreationTime.dwLowDateTime == 0) &&
               (local_34.ftCreationTime.dwHighDateTime == 0)) {
              *(byte *)((int)pvVar1 + 7) = *(byte *)((int)pvVar1 + 7) | 0x80;
              *(undefined4 *)((int)pvVar1 + 0x20) = *(undefined4 *)((int)pvVar1 + 0x1c);
              *(DWORD *)((int)pvVar1 + 0x14) = local_34.nFileSizeLow;
              *(undefined4 *)pvVar1 = 0;
              *(undefined4 *)((int)pvVar1 + 0x10) = 0;
              return 0;
            }
            BVar4 = FileTimeToLocalFileTime(&local_34.ftCreationTime,&local_4c);
            if ((BVar4 != 0) && (BVar4 = FileTimeToSystemTime(&local_4c,&local_44), BVar4 != 0)) {
              lVar5 = __loctotime_t((uint)local_44.wYear,(uint)local_44.wMonth,(uint)local_44.wDay,
                                    (uint)local_44.wHour,(uint)local_44.wMinute,
                                    (uint)local_44.wSecond,-1);
              *(byte *)((int)pvVar1 + 7) = *(byte *)((int)pvVar1 + 7) | 0x80;
              *(long *)((int)pvVar1 + 0x20) = lVar5;
              *(DWORD *)((int)pvVar1 + 0x14) = local_34.nFileSizeLow;
              *(undefined4 *)pvVar1 = 0;
              *(undefined4 *)((int)pvVar1 + 0x10) = 0;
              return 0;
            }
          }
          return -1;
        }
LAB_00491743:
        DVar2 = GetLastError();
        _dosmaperr(DVar2);
        return -1;
      }
      if (uVar3 == 2) {
        *(undefined2 *)((int)buf + 6) = 0x2000;
      }
      else {
        if (uVar3 != 3) {
          if (uVar3 == 0) {
            errno = 9;
            return -1;
          }
          goto LAB_00491743;
        }
        *(undefined2 *)((int)buf + 6) = 0x1000;
      }
      *(int *)buf = fh;
      *(int *)((int)buf + 0x10) = fh;
      *(undefined2 *)((int)buf + 8) = 1;
      *(undefined2 *)((int)buf + 4) = 0;
      *(undefined2 *)((int)buf + 0xc) = 0;
      *(undefined2 *)((int)buf + 10) = 0;
      *(undefined4 *)((int)buf + 0x20) = 0;
      *(undefined4 *)((int)buf + 0x1c) = 0;
      *(undefined4 *)((int)buf + 0x18) = 0;
      if (uVar3 == 2) {
        *(undefined4 *)((int)buf + 0x14) = 0;
        return 0;
      }
      BVar4 = PeekNamedPipe(*(HANDLE *)(iVar6 + (&__pioinfo)[fh >> 5]),(LPVOID)0x0,0,(LPDWORD)0x0,
                            (LPDWORD)&buf,(LPDWORD)0x0);
      if (BVar4 != 0) {
        *(void **)((int)pvVar1 + 0x14) = buf;
        return 0;
      }
      *(undefined4 *)((int)pvVar1 + 0x14) = 0;
      return 0;
    }
  }
  errno = 9;
  return -1;
}


/* ==== __initconin @ 00491970 ==== */

void __initconin(void)

{
  DAT_004db070 = CreateFileA("CONIN$",0xc0000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
  return;
}


