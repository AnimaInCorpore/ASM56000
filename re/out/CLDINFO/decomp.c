/* ==== main @ 00401000 ==== */

int __cdecl main(int argc,char **argv,char **envp)

{
  int *extraout_EAX;
  int extraout_EAX_00;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int *local_c;
  undefined4 local_8;
  
  local_c = (int *)0x0;
  if (argc != 2) {
    fprintf(&DAT_00407230,s_Version_6_3_usage__cldinfo_file_00407030);
    exit(-1);
  }
  fopen(argv[1],&DAT_00407054);
  local_c = extraout_EAX;
  if (extraout_EAX == (int *)0x0) {
    FUN_00401830(s_cldinfo_00407058);
    exit(-2);
  }
  FUN_00401121(local_c,&local_14,&local_1c,&local_10,&local_8,&local_24,&local_20,&local_18);
  fclose(local_c);
  fprintf(&DAT_00407210,s_filename___s_00407060,argv[1]);
  if (DAT_00409b38 == 0) {
    fprintf(&DAT_00407210,s_xsize___ld__ysize___ld__psize____004070bc,local_14,local_1c,local_10,
            local_24,local_20,local_18,local_8);
  }
  else {
    fprintf(&DAT_00407210,s_xsize___ld__ysize___ld__psize____00407070,local_14,local_1c,local_10,
            local_24,local_20,local_18);
  }
  exit(0);
  return extraout_EAX_00;
}


/* ==== FUN_00401121 @ 00401121 ==== */

void __cdecl
FUN_00401121(int *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
            undefined4 *param_5,undefined4 *param_6,undefined4 *param_7,undefined4 *param_8)

{
  FUN_00401186(param_1);
  *param_2 = DAT_00409b40;
  *param_4 = DAT_00409b3c;
  *param_3 = DAT_00409b44;
  *param_6 = DAT_00409b4c;
  *param_7 = DAT_00409b50;
  *param_8 = DAT_00409b54;
  if (DAT_00409b38 == 0) {
    *param_5 = DAT_00409b48;
  }
  return;
}


/* ==== FUN_00401186 @ 00401186 ==== */

void __cdecl FUN_00401186(int *param_1)

{
  int iVar1;
  uint uVar2;
  char *extraout_EAX;
  char local_9c [12];
  int local_90;
  uint local_8c;
  uint local_84;
  long local_80;
  uint local_6c;
  uint local_68;
  int local_64;
  int local_54;
  uint local_4c;
  int local_48;
  int local_44;
  char local_40 [20];
  undefined4 local_2c;
  
  FUN_0040169b(param_1,&local_68);
  if (local_54 == 0x3c) {
    FUN_00401733(param_1,local_40,0x3c);
  }
  else {
    DAT_00409b38 = 1;
  }
  local_48 = 0;
  do {
    if (local_64 <= local_48) {
      if (DAT_00409b38 == 0) {
        DAT_00409b48 = local_2c;
      }
      if (DAT_00409b34 != (char *)0x0) {
        free(DAT_00409b34);
        DAT_00409b30 = 0;
        DAT_00409b34 = (char *)0x0;
      }
      return;
    }
    iVar1 = fseek(param_1,local_54 + 0x1c + local_48 * 0x34,0);
    if (iVar1 != 0) {
      FUN_00401830(s_read_section_contents_1_00407118);
      exit(-5);
    }
    uVar2 = FUN_00401ca0(local_9c,0x34,1,param_1);
    if (uVar2 != 1) {
      FUN_00401830(s_read_section_contents_2_00407130);
      exit(-5);
    }
    FUN_00401626((int)local_9c,0x34);
    FUN_00401626((int)local_9c,8);
    iVar1 = _strncmp(local_9c,s__text_00407148,8);
    if ((iVar1 != 0) && (iVar1 = _strncmp(local_9c,s__data_00407150,8), iVar1 != 0)) {
      if ((int)DAT_00409b30 < (int)local_84) {
        if (DAT_00409b34 != (char *)0x0) {
          free(DAT_00409b34);
        }
        malloc(local_84 << 2);
        DAT_00409b34 = extraout_EAX;
        if (extraout_EAX == (char *)0x0) {
          FUN_00401830(s_malloc_error_00407158);
          exit(-5);
        }
        DAT_00409b30 = local_84;
      }
      iVar1 = fseek(param_1,local_80,0);
      if (iVar1 != 0) {
        FUN_00401830(s_read_section_contents_3_00407168);
        exit(-5);
      }
      if ((local_84 != 0) &&
         (uVar2 = FUN_00401ca0(DAT_00409b34,local_84 << 2,1,param_1), uVar2 != 1)) {
        FUN_00401830(s_read_section_contents_4_00407180);
        exit(-5);
      }
      FUN_00401626((int)DAT_00409b34,local_84 << 2);
      local_44 = local_90;
      if (local_90 < 0x10) {
        if (local_90 < 0xb) {
          if ((4 < local_90) && (local_90 < 0xb)) {
            local_44 = 3;
          }
        }
        else {
LAB_00401411:
          local_44 = 0;
        }
      }
      else if (local_90 < 0x1a) {
        if (local_90 < 0x15) {
          if ((0xf < local_90) && (local_90 < 0x15)) {
            local_44 = 1;
          }
        }
        else {
          local_44 = 2;
        }
      }
      else {
        if (local_90 == 0x11e) goto LAB_00401411;
        if ((0x11f < local_90) && (local_90 < 0x122)) {
          local_44 = 0x11f;
        }
      }
      if ((local_6c & 0x400) == 0) {
        local_4c = local_84;
        if (local_44 == 3) {
          local_4c = local_84 >> 1;
          DAT_00409b40 = DAT_00409b40 + local_4c;
          DAT_00409b44 = DAT_00409b44 + local_4c;
        }
        else if (local_44 == 2) {
          DAT_00409b44 = DAT_00409b44 + local_84;
        }
        else if (local_44 == 0) {
          DAT_00409b3c = DAT_00409b3c + local_84;
        }
        else if (local_44 == 1) {
          DAT_00409b40 = DAT_00409b40 + local_84;
        }
        else if (local_44 == 0x11d) {
          DAT_00409b50 = DAT_00409b50 + local_84;
        }
        else if ((local_44 < 0x1c) || (0x11c < local_44)) {
          if (local_44 == 0x11f) {
            DAT_00409b54 = DAT_00409b54 + local_84;
          }
        }
        else {
          DAT_00409b4c = DAT_00409b4c + local_84;
        }
      }
      else {
        local_4c = local_8c;
        if (local_44 == 3) {
          DAT_00409b40 = DAT_00409b40 + local_8c;
          DAT_00409b44 = DAT_00409b44 + local_8c;
        }
        else if (local_44 == 2) {
          DAT_00409b44 = DAT_00409b44 + local_8c;
        }
        else if (local_44 == 0) {
          DAT_00409b3c = DAT_00409b3c + local_8c;
        }
        else if (local_44 == 1) {
          DAT_00409b40 = DAT_00409b40 + local_8c;
        }
        else if (local_44 == 0x11d) {
          DAT_00409b50 = DAT_00409b50 + local_8c;
        }
        else if ((local_44 < 0x1c) || (0x11c < local_44)) {
          if (local_44 == 0x11f) {
            DAT_00409b54 = DAT_00409b54 + local_8c;
          }
        }
        else {
          DAT_00409b4c = DAT_00409b4c + local_8c;
        }
      }
    }
    local_48 = local_48 + 1;
  } while( true );
}


/* ==== FUN_00401626 @ 00401626 ==== */

void __cdecl FUN_00401626(int param_1,uint param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  uint local_8;
  
  for (local_8 = 0; local_8 < param_2 >> 2; local_8 = local_8 + 1) {
    puVar1 = (undefined1 *)(param_1 + local_8 * 4);
    uVar2 = *puVar1;
    uVar3 = puVar1[1];
    *puVar1 = puVar1[3];
    puVar1[1] = puVar1[2];
    puVar1[2] = uVar3;
    puVar1[3] = uVar2;
  }
  return;
}


/* ==== FUN_0040169b @ 0040169b ==== */

uint __cdecl FUN_0040169b(int *param_1,uint *param_2)

{
  uint uVar1;
  
  fseek(param_1,0,0);
  uVar1 = FUN_00401ca0((char *)param_2,0x1c,1,param_1);
  if (uVar1 != 1) {
    FUN_00401830(s_read_file_hdr_00407198);
    exit(-2);
  }
  FUN_00401626((int)param_2,0x1c);
  if ((*param_2 < 0x2c5) || (0x2cc < *param_2)) {
    fprintf(&DAT_00407230,s_read_file_hdr___failure_004071a8);
    exit(-2);
    uVar1 = 0;
  }
  else {
    uVar1 = param_2[4];
  }
  return uVar1;
}


/* ==== FUN_00401733 @ 00401733 ==== */

undefined4 __cdecl FUN_00401733(int *param_1,char *param_2,uint param_3)

{
  uint uVar1;
  
  fseek(param_1,0x1c,0);
  if (param_3 != 0x3c) {
    fprintf(&DAT_00407230,s_read_aout_hdr___failure_004071c4);
    exit(-3);
  }
  uVar1 = FUN_00401ca0(param_2,param_3,1,param_1);
  if (uVar1 != 1) {
    FUN_00401830(s_read_aout_hdr_004071e0);
    exit(-3);
  }
  FUN_00401626((int)param_2,param_3);
  return 0;
}


/* ==== fclose @ 004017b0 ==== */

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


/* ==== FUN_00401830 @ 00401830 ==== */

void __cdecl FUN_00401830(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    uVar3 = 0xffffffff;
    pcVar4 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    _write(2,param_1,~uVar3 - 1);
    _write(2,&DAT_00406004,2);
  }
  if ((errno < 0) || (iVar2 = errno, DAT_00407528 <= errno)) {
    iVar2 = DAT_00407528;
  }
  uVar3 = 0xffffffff;
  pcVar4 = (&PTR_s_No_error_00407478)[iVar2];
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  _write(2,(&PTR_s_No_error_00407478)[iVar2],~uVar3 - 1);
  _write(2,&DAT_00406000,1);
  return;
}


/* ==== _fsopen @ 004018b0 ==== */

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


/* ==== fopen @ 004018e0 ==== */

void __cdecl fopen(char *name,char *mode)

{
  _fsopen(name,mode,0x40);
  return;
}


/* ==== _cinit @ 00401900 ==== */

void _cinit(void)

{
  if (_FPinit != (code *)0x0) {
    (*_FPinit)();
  }
  _initterm(&DAT_00407008,&DAT_00407010);
  _initterm(&DAT_00407000,&DAT_00407004);
  return;
}


/* ==== exit @ 00401930 ==== */

void __cdecl exit(int status)

{
  doexit(status,0,0);
  return;
}


/* ==== __exit @ 00401950 ==== */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __exit(int _Code)

{
  doexit(_Code,1,0);
  return;
}


/* ==== doexit @ 00401970 ==== */

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
    _initterm(&DAT_00407014,&DAT_0040701c);
  }
  _initterm(&DAT_00407020,&DAT_00407024);
  if (retcaller == 0) {
    _C_Exit_Done = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(code);
  }
  return;
}


/* ==== _initterm @ 00401a20 ==== */

void __cdecl _initterm(void *begin,void *end)

{
  for (; begin < end; begin = (void *)((int)begin + 4)) {
    if (*(code **)begin != (code *)0x0) {
      (**(code **)begin)();
    }
  }
  return;
}


/* ==== fprintf @ 00401a40 ==== */

int __cdecl fprintf(void *stream,char *fmt,...)

{
  int flag;
  int iVar1;
  
  flag = _stbuf(stream);
  iVar1 = _output(stream,fmt,&stack0x0000000c);
  _ftbuf(flag,stream);
  return iVar1;
}


/* ==== malloc @ 00401b60 ==== */

void __cdecl malloc(uint size)

{
  _nh_malloc(size,_newmode);
  return;
}


/* ==== _nh_malloc @ 00401b80 ==== */

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


/* ==== _heap_alloc @ 00401bd0 ==== */

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


/* ==== free @ 00401c10 ==== */

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


/* ==== _strncmp @ 00401c60 ==== */

/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  sVar3 = _MaxCount;
  pcVar6 = _Str1;
  if (_MaxCount != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = _MaxCount - sVar3;
    do {
      pcVar6 = _Str2;
      pcVar7 = _Str1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = _Str1 + 1;
      pcVar6 = _Str2 + 1;
      cVar2 = *_Str1;
      cVar1 = *_Str2;
      _Str2 = pcVar6;
      _Str1 = pcVar7;
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


/* ==== FUN_00401ca0 @ 00401ca0 ==== */

uint __cdecl FUN_00401ca0(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *stream;
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  char *pcVar9;
  
  stream = param_4;
  piVar5 = (int *)(param_3 * param_2);
  if (piVar5 == (int *)0x0) {
    return 0;
  }
  piVar6 = piVar5;
  if ((param_4[3] & 0x10cU) == 0) {
    param_4 = (int *)0x1000;
    piVar8 = (int *)0x1000;
  }
  else {
    piVar8 = (int *)param_4[6];
    param_4 = piVar8;
  }
  do {
    if (((stream[3] & 0x10cU) == 0) || (piVar1 = (int *)stream[1], piVar1 == (int *)0x0)) {
      if (piVar6 < piVar8) {
        iVar3 = _filbuf(stream);
        if (iVar3 == -1) {
          return (uint)((int)piVar5 - (int)piVar6) / param_2;
        }
        *param_1 = (char)iVar3;
        piVar8 = (int *)stream[6];
        param_1 = param_1 + 1;
        iVar3 = -1;
        param_4 = piVar8;
      }
      else {
        piVar1 = piVar6;
        if (piVar8 != (int *)0x0) {
          piVar1 = (int *)((int)piVar6 - (uint)piVar6 % (uint)piVar8);
        }
        iVar2 = _read(stream[4],param_1,(uint)piVar1);
        if (iVar2 == 0) {
          stream[3] = stream[3] | 0x10;
          return (uint)((int)piVar5 - (int)piVar6) / param_2;
        }
        if (iVar2 == -1) {
          stream[3] = stream[3] | 0x20;
          return (uint)((int)piVar5 - (int)piVar6) / param_2;
        }
        iVar3 = -iVar2;
        param_1 = param_1 + iVar2;
      }
    }
    else {
      if (piVar6 < piVar1) {
        piVar1 = piVar6;
      }
      iVar3 = -(int)piVar1;
      pcVar7 = (char *)*stream;
      pcVar9 = param_1;
      for (uVar4 = (uint)piVar1 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = (uint)piVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      param_1 = param_1 + (int)piVar1;
      stream[1] = stream[1] - (int)piVar1;
      *stream = *stream + (int)piVar1;
      piVar8 = param_4;
    }
    piVar6 = (int *)((int)piVar6 + iVar3);
    if (piVar6 == (int *)0x0) {
      return param_3;
    }
  } while( true );
}


/* ==== fseek @ 00401de0 ==== */

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


/* ==== entry @ 00401e80 ==== */

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
  puStack_c = &DAT_00406008;
  puStack_10 = &LAB_00404d38;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  DVar1 = GetVersion();
  _DAT_00409b70 = DVar1 >> 8 & 0xff;
  _DAT_00409b6c = DVar1 & 0xff;
  _DAT_00409b68 = _DAT_00409b6c * 0x100 + _DAT_00409b70;
  _DAT_00409b64 = DVar1 >> 0x10;
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
  ___initenv = _environ;
  iVar2 = main(__argc,__argv,_environ);
  exit(iVar2);
  *unaff_FS_OFFSET = local_14;
  return;
}


/* ==== _amsg_exit @ 00401fa0 ==== */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _amsg_exit(int rterrnum)

{
  if (DAT_00409bb0 != 2) {
    _FF_MSGBANNER();
  }
  _NMSG_WRITE(rterrnum);
  (*(code *)PTR___exit_00407470)(0xff);
  return;
}


/* ==== _close @ 00401fd0 ==== */

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
      if (lVar2 == lVar1) goto LAB_00402057;
    }
    hObject = (HANDLE)_get_osfhandle(fh);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      oserrno = GetLastError();
      goto LAB_00402059;
    }
  }
LAB_00402057:
  oserrno = 0;
LAB_00402059:
  _free_osfhnd(fh);
  *(undefined1 *)((&__pioinfo)[fh >> 5] + 4 + iVar4) = 0;
  if (oserrno == 0) {
    return 0;
  }
  _dosmaperr(oserrno);
  return -1;
}


/* ==== _freebuf @ 004020b0 ==== */

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


/* ==== _flush @ 00402140 ==== */

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


/* ==== _write @ 00402240 ==== */

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


/* ==== _openfile @ 00402460 ==== */

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
      uVar7 = DAT_00409e04 | 1;
      goto LAB_0040249d;
    }
    if (cVar1 != 'w') {
      return;
    }
    oflag = 0x301;
  }
  uVar7 = DAT_00409e04 | 2;
LAB_0040249d:
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
      goto LAB_0040254e;
    case 'D':
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_0040254e;
      }
      break;
    case 'R':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x10;
        goto LAB_0040254e;
      }
      break;
    case 'S':
      if (!bVar4) {
        bVar4 = true;
        oflag = oflag | 0x20;
        goto LAB_0040254e;
      }
      break;
    case 'T':
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_0040254e;
      }
      break;
    case 'b':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x8000;
        goto LAB_0040254e;
      }
      break;
    case 'c':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 | 0x4000;
        goto LAB_0040254e;
      }
      break;
    case 'n':
      if (!bVar3) {
        bVar3 = true;
        uVar7 = uVar7 & 0xffffbfff;
        goto LAB_0040254e;
      }
      break;
    case 't':
      if ((oflag & 0xc000) == 0) {
        oflag = oflag | 0x4000;
        goto LAB_0040254e;
      }
    }
    bVar2 = false;
LAB_0040254e:
    pcVar6 = pcVar6 + 1;
    cVar1 = *pcVar6;
  } while( true );
}


/* ==== _getstream @ 00402630 ==== */

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


/* ==== _stbuf @ 004026c0 ==== */

int __cdecl _stbuf(void *stream)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EAX;
  
  iVar2 = _isatty(*(int *)((int)stream + 0x10));
  if (iVar2 != 0) {
    if (stream == &DAT_00407210) {
      iVar2 = 0;
    }
    else {
      if (stream != &DAT_00407230) {
        return 0;
      }
      iVar2 = 1;
    }
    _cflush = _cflush + 1;
    if ((*(uint *)((int)stream + 0xc) & 0x10c) == 0) {
      if ((&DAT_00409bb8)[iVar2] == 0) {
        malloc(0x1000);
        (&DAT_00409bb8)[iVar2] = extraout_EAX;
        if (extraout_EAX == 0) {
          return 0;
        }
      }
      uVar1 = (&DAT_00409bb8)[iVar2];
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


/* ==== _ftbuf @ 00402760 ==== */

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


/* ==== _output @ 004027c0 ==== */

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
      uVar2 = (byte)"Operation not permitted"[cVar7 + 8] & 0xf;
    }
    local_220 = (int)(char)(&DAT_00406350)[uVar2 * 8 + local_220] >> 4;
    switch(local_220) {
    case 0:
switchD_0040283d_caseD_0:
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
          goto switchD_0040283d_caseD_0;
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
          (*(code *)PTR__fptrap_00409904)(&local_204);
        }
        if ((cVar7 == 'g') && ((unaff_EBX & 0x80) == 0)) {
          (*(code *)PTR__fptrap_004098fc)(local_200);
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
            puVar5 = (ushort *)PTR_DAT_0040752c;
            local_248 = (ushort *)PTR_DAT_0040752c;
          }
          for (; (iVar10 != 0 && (iVar10 = iVar10 + -1, (char)*puVar5 != '\0'));
              puVar5 = (ushort *)((int)puVar5 + 1)) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248);
        }
        else {
          if (local_248 == (ushort *)0x0) {
            local_248 = (ushort *)PTR_DAT_00407530;
          }
          local_230 = 1;
          for (puVar5 = local_248; (iVar10 != 0 && (iVar10 = iVar10 + -1, *puVar5 != 0));
              puVar5 = puVar5 + 1) {
          }
          len = (undefined1 *)((int)puVar5 - (int)local_248 >> 1);
        }
        break;
      case 'X':
        goto switchD_00402a51_caseD_58;
      case 'Z':
        psVar3 = (short *)get_int_arg(&argptr);
        if ((psVar3 == (short *)0x0) ||
           (local_248 = *(ushort **)(psVar3 + 2), local_248 == (ushort *)0x0)) {
          uVar2 = 0xffffffff;
          local_248 = (ushort *)PTR_DAT_0040752c;
          pcVar9 = PTR_DAT_0040752c;
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
        goto LAB_00402d87;
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
        goto LAB_00402d87;
      case 'p':
        local_244 = 8;
switchD_00402a51_caseD_58:
        local_224 = 7;
LAB_00402d42:
        local_22c = 0x10;
        if ((local_24c & 0x80) != 0) {
          local_23a = '0';
          local_239 = (char)local_224 + 'Q';
          local_238 = 2;
        }
        goto LAB_00402d87;
      case 'u':
        local_22c = 10;
LAB_00402d87:
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
        goto LAB_00402d42;
      }
      if (local_228 == 0) {
        if ((local_24c & 0x40) != 0) {
          if ((local_24c & 0x100) == 0) {
            if ((local_24c & 1) == 0) {
              if ((local_24c & 2) == 0) goto LAB_00402f1f;
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
LAB_00402f1f:
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


/* ==== write_char @ 00403150 ==== */

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


/* ==== write_multi_char @ 004031a0 ==== */

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


/* ==== write_string @ 004031e0 ==== */

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


/* ==== get_int_arg @ 00403220 ==== */

int __cdecl get_int_arg(void *pargptr)

{
  int *piVar1;
  
  piVar1 = *(int **)pargptr;
  *(int **)pargptr = piVar1 + 1;
  return *piVar1;
}


/* ==== get_int64_arg @ 00403240 ==== */

longlong __cdecl get_int64_arg(void *pargptr)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)pargptr;
  *(longlong **)pargptr = plVar1 + 1;
  return *plVar1;
}


/* ==== get_short_arg @ 00403260 ==== */

short __cdecl get_short_arg(void *pargptr)

{
  short *psVar1;
  
  psVar1 = *(short **)pargptr;
  *(short **)pargptr = psVar1 + 2;
  return *psVar1;
}


/* ==== _ioinit @ 00403280 ==== */

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
      piVar6 = &DAT_00409e44;
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
        goto LAB_0040345b;
      }
      *puVar2 = hFile;
      if ((DVar3 & 0xff) == 2) {
        bVar1 = *(byte *)(puVar2 + 1) | 0x40;
        goto LAB_0040345b;
      }
      if ((DVar3 & 0xff) == 3) {
        bVar1 = *(byte *)(puVar2 + 1) | 8;
        goto LAB_0040345b;
      }
    }
    else {
      bVar1 = *(byte *)(puVar2 + 1) | 0x80;
LAB_0040345b:
      *(byte *)(puVar2 + 1) = bVar1;
    }
    iVar4 = iVar4 + 1;
    if (2 < iVar4) {
      SetHandleCount(_nhandle);
      return;
    }
  } while( true );
}


/* ==== calloc @ 00403480 ==== */

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
LAB_004034e0:
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
          goto LAB_004034e0;
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


/* ==== _callnewh @ 00403590 ==== */

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


/* ==== _heap_init @ 004035b0 ==== */

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


/* ==== __sbh_new_region @ 004035f0 ==== */

void __sbh_new_region(void)

{
  bool bVar1;
  undefined4 *lpAddress;
  LPVOID pvVar2;
  int iVar3;
  undefined **ppuVar4;
  undefined **lpMem;
  undefined4 *puVar5;
  
  if (DAT_00407558 == -1) {
    lpMem = &PTR_LOOP_00407548;
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
      if (lpMem == &PTR_LOOP_00407548) {
        if (PTR_LOOP_00407548 == (undefined *)0x0) {
          PTR_LOOP_00407548 = (undefined *)&PTR_LOOP_00407548;
        }
        if (PTR_LOOP_0040754c == (undefined *)0x0) {
          PTR_LOOP_0040754c = (undefined *)&PTR_LOOP_00407548;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_00407548;
        lpMem[1] = PTR_LOOP_0040754c;
        PTR_LOOP_0040754c = (undefined *)lpMem;
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
  if (lpMem != &PTR_LOOP_00407548) {
    HeapFree(_crtheap,0,lpMem);
  }
  return;
}


/* ==== __sbh_release_region @ 00403760 ==== */

void __cdecl __sbh_release_region(void *preg)

{
  VirtualFree(*(LPVOID *)((int)preg + 0x10),0,0x8000);
  if (PTR_LOOP_00409568 == preg) {
    PTR_LOOP_00409568 = *(undefined **)((int)preg + 4);
  }
  if (preg != &PTR_LOOP_00407548) {
    **(undefined4 **)((int)preg + 4) = *(undefined4 *)preg;
    *(undefined4 *)(*(int *)preg + 4) = *(undefined4 *)((int)preg + 4);
    HeapFree(_crtheap,0,preg);
    return;
  }
  DAT_00407558 = 0xffffffff;
  return;
}


/* ==== __sbh_decommit_pages @ 004037c0 ==== */

void __cdecl __sbh_decommit_pages(int count)

{
  BOOL BVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *preg;
  undefined *puVar5;
  
  preg = PTR_LOOP_0040754c;
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
            DAT_00409bc8 = DAT_00409bc8 + -1;
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
    if ((puVar5 == PTR_LOOP_0040754c) || (preg = puVar5, count < 1)) {
      return;
    }
  } while( true );
}


/* ==== __sbh_find_block @ 00403890 ==== */

void __cdecl __sbh_find_block(void *pblock,void *ppreg,void *pppage)

{
  undefined **ppuVar1;
  
  ppuVar1 = &PTR_LOOP_00407548;
  while ((pblock <= ppuVar1[4] || (ppuVar1[5] <= pblock))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_00407548) {
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


/* ==== __sbh_free_block @ 004038f0 ==== */

void __cdecl __sbh_free_block(void *preg,void *ppage,void *pmap)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (int)ppage - *(int *)((int)preg + 0x10) >> 0xc;
  piVar1 = (int *)((int)preg + iVar2 * 8 + 0x18);
  *piVar1 = *(int *)((int)preg + iVar2 * 8 + 0x18) + (uint)*(byte *)pmap;
  *(undefined1 *)pmap = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_00409bc8 = DAT_00409bc8 + 1, DAT_00409bc8 == 0x20)) {
    __sbh_decommit_pages(0x10);
  }
  return;
}


/* ==== __sbh_alloc_block @ 00403950 ==== */

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
  
  piVar11 = (int *)PTR_LOOP_00409568;
  do {
    if (piVar11[4] != -1) {
      puVar10 = (uint *)piVar11[2];
      pvVar8 = (void *)(((int)puVar10 + (-0x18 - (int)piVar11) >> 3) * 0x1000 + piVar11[4]);
      for (; puVar10 < piVar11 + 0x806; puVar10 = puVar10 + 2) {
        if (((int)para_req <= (int)*puVar10) && (para_req < puVar10[1])) {
          __sbh_alloc_block_from_page(pvVar8,*puVar10,para_req);
          if (extraout_EAX != 0) {
            PTR_LOOP_00409568 = (undefined *)piVar11;
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
            PTR_LOOP_00409568 = (undefined *)piVar11;
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
  } while (piVar11 != (int *)PTR_LOOP_00409568);
  ppuVar7 = &PTR_LOOP_00407548;
  while ((ppuVar7[4] == (undefined *)0xffffffff || (ppuVar7[3] == (undefined *)0x0))) {
    ppuVar7 = (undefined **)*ppuVar7;
    if (ppuVar7 == &PTR_LOOP_00407548) {
      __sbh_new_region();
      if (extraout_EAX_01 == (undefined *)0x0) {
        return;
      }
      piVar11 = *(int **)(extraout_EAX_01 + 0x10);
      *(char *)(piVar11 + 2) = (char)para_req;
      PTR_LOOP_00409568 = extraout_EAX_01;
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
  PTR_LOOP_00409568 = (undefined *)ppuVar7;
  ppuVar7[3] = (undefined *)(-(uint)bVar12 & (uint)ppuVar6);
  *(char *)(piVar11 + 2) = (char)para_req;
  ppuVar7[2] = (undefined *)ppuVar3;
  *ppuVar3 = *ppuVar3 + -para_req;
  piVar11[1] = piVar11[1] - para_req;
  *piVar11 = (int)piVar11 + para_req + 8;
  return;
}


/* ==== __sbh_alloc_block_from_page @ 00403b90 ==== */

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
            goto LAB_00403cdf;
          }
          *(byte **)ppage = pbVar6 + para_req;
          *(uint *)((int)ppage + 4) = uVar5 - para_req;
          goto LAB_00403ce6;
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
LAB_00403cdf:
            *(undefined4 *)((int)ppage + 4) = 0;
          }
LAB_00403ce6:
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


/* ==== _filbuf @ 00403d10 ==== */

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


/* ==== _read @ 00403e00 ==== */

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
                  goto LAB_00403fe8;
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
                      goto LAB_00403fe8;
                    }
                    _lseek(fh,-1,1);
                    if ((char)cnt != '\n') goto LAB_00403fe5;
                  }
                  else {
                    if ((char)cnt == '\n') {
                      *pcVar8 = '\n';
                      goto LAB_00403fe8;
                    }
                    *pcVar8 = '\r';
                    pcVar8 = pcVar8 + 1;
                    *(char *)(iVar6 + 5 + *local_8) = (char)cnt;
                  }
                }
                else {
LAB_00403fe5:
                  *pcVar8 = '\r';
LAB_00403fe8:
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


/* ==== _lseek @ 00404060 ==== */

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


/* ==== ftell @ 00404120 ==== */

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
  if ((*(byte *)((int)stream + 0xc) & 1) == 0) goto LAB_00404295;
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
LAB_0040428c:
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
      if ((*(byte *)(iVar6 + 4 + (&__pioinfo)[iVar3]) & 4) != 0) goto LAB_0040428c;
    }
  }
  local_4 = local_4 - (int)pcVar7;
LAB_00404295:
  return local_4 + local_8;
}


/* ==== _XcptFilter @ 004042d0 ==== */

int __cdecl _XcptFilter(ulong xcptnum,void *pxcptptrs)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  LONG LVar5;
  undefined4 *puVar6;
  int iVar7;
  
  piVar4 = FUN_00404410(xcptnum);
  uVar3 = DAT_00409bcc;
  if ((piVar4 == (int *)0x0) || (pcVar1 = (code *)piVar4[2], pcVar1 == (code *)0x0)) {
    LVar5 = UnhandledExceptionFilter(pxcptptrs);
    return LVar5;
  }
  if (pcVar1 == (code *)0x5) {
    piVar4[2] = 0;
    return 1;
  }
  if (pcVar1 != (code *)0x1) {
    DAT_00409bcc = pxcptptrs;
    if (piVar4[1] == 8) {
      if (DAT_004095e8 < DAT_004095ec + DAT_004095e8) {
        iVar7 = (DAT_004095ec + DAT_004095e8) - DAT_004095e8;
        puVar6 = (undefined4 *)(DAT_004095e8 * 0xc + 0x409578);
        do {
          *puVar6 = 0;
          puVar6 = puVar6 + 3;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
      uVar2 = DAT_004095f4;
      iVar7 = *piVar4;
      if (iVar7 == -0x3fffff72) {
        DAT_004095f4 = 0x83;
      }
      else if (iVar7 == -0x3fffff70) {
        DAT_004095f4 = 0x81;
      }
      else if (iVar7 == -0x3fffff6f) {
        DAT_004095f4 = 0x84;
      }
      else if (iVar7 == -0x3fffff6d) {
        DAT_004095f4 = 0x85;
      }
      else if (iVar7 == -0x3fffff73) {
        DAT_004095f4 = 0x82;
      }
      else if (iVar7 == -0x3fffff71) {
        DAT_004095f4 = 0x86;
      }
      else if (iVar7 == -0x3fffff6e) {
        DAT_004095f4 = 0x8a;
      }
      (*pcVar1)(8,DAT_004095f4);
      DAT_004095f4 = uVar2;
      DAT_00409bcc = (void *)uVar3;
      return -1;
    }
    piVar4[2] = 0;
    (*pcVar1)(piVar4[1]);
    DAT_00409bcc = (void *)uVar3;
    return -1;
  }
  return -1;
}


/* ==== FUN_00404410 @ 00404410 ==== */

int * __cdecl FUN_00404410(int param_1)

{
  int *piVar1;
  
  piVar1 = &DAT_00409570;
  if (DAT_00409570 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (&DAT_00409570 + DAT_004095f0 * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((&DAT_00409570 + DAT_004095f0 * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}


/* ==== _setenvp @ 00404460 ==== */

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


/* ==== _setargv @ 00404550 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void _setargv(void)

{
  char **argv;
  char *cmdstart;
  int local_8;
  int local_4;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_00409bd0,0x104);
  _DAT_00409b90 = &DAT_00409bd0;
  cmdstart = _acmdln;
  if (*_acmdln == '\0') {
    cmdstart = &DAT_00409bd0;
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


/* ==== parse_cmdline @ 004045f0 ==== */

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
      if (((*(byte *)((int)&DAT_00409ce0 + bVar2 + 1) & 4) != 0) &&
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
      if ((*(byte *)((int)numchars + 0x409ce1) & 4) != 0) {
        *piVar6 = *piVar6 + 1;
        if ((byte *)args != (byte *)0x0) {
          *args = *pbVar7;
          args = args + 1;
        }
        pbVar7 = (byte *)(cmdstart + 2);
      }
      if (bVar2 == 0x20) break;
      if (bVar2 == 0) goto LAB_004046c9;
      cmdstart = (char *)pbVar7;
    } while (bVar2 != 9);
    if (bVar2 == 0) {
LAB_004046c9:
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
          if ((*(byte *)((int)&DAT_00409ce0 + bVar2 + 1) & 4) != 0) {
            pbVar7 = pbVar7 + 1;
            *piVar6 = *piVar6 + 1;
          }
          *piVar6 = *piVar6 + 1;
          goto LAB_004047c5;
        }
        if ((*(byte *)((int)&DAT_00409ce0 + bVar2 + 1) & 4) != 0) {
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
LAB_004047c5:
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


/* ==== __crtGetEnvironmentStringsA @ 00404800 ==== */

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
  if (DAT_00409cd8 == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr == (LPWCH)0x0) {
      pCVar8 = GetEnvironmentStrings();
      if (pCVar8 == (LPCH)0x0) {
        return;
      }
      DAT_00409cd8 = 2;
    }
    else {
      DAT_00409cd8 = 1;
    }
  }
  if (DAT_00409cd8 == 1) {
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
  else if ((DAT_00409cd8 == 2) &&
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


/* ==== _setmbcp @ 00404960 ==== */

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
  
  CodePage = FUN_00404b50(codepage);
  if (CodePage == DAT_00409de4) {
    return 0;
  }
  if (CodePage == 0) {
    FUN_00404c00();
    return 0;
  }
  iVar10 = 0;
  pUVar5 = &DAT_00409600;
  do {
    if (*pUVar5 == CodePage) {
      puVar14 = &DAT_00409ce0;
      for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      *(undefined1 *)puVar14 = 0;
      uVar7 = 0;
      iVar10 = iVar10 * 0x30;
      pbVar12 = (byte *)(iVar10 + 0x409610);
      do {
        bVar3 = *pbVar12;
        for (pbVar13 = pbVar12; (bVar3 != 0 && (bVar3 = pbVar13[1], bVar3 != 0));
            pbVar13 = pbVar13 + 2) {
          uVar8 = (uint)*pbVar13;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_004095f8)[uVar7];
            do {
              pbVar2 = (byte *)((int)&DAT_00409ce0 + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          bVar3 = pbVar13[2];
        }
        uVar7 = uVar7 + 1;
        pbVar12 = pbVar12 + 8;
      } while (uVar7 < 4);
      DAT_00409de4 = CodePage;
      _DAT_00409de8 = FUN_00404ba0(CodePage);
      _DAT_00409df0 = *(undefined4 *)(iVar10 + 0x409604);
      _DAT_00409df4 = *(undefined4 *)(iVar10 + 0x409608);
      _DAT_00409df8 = *(undefined4 *)(iVar10 + 0x40960c);
      return 0;
    }
    pUVar5 = pUVar5 + 0xc;
    iVar10 = iVar10 + 1;
  } while (pUVar5 < &DAT_004096f0);
  BVar6 = GetCPInfo(CodePage,&local_14);
  if (BVar6 != 1) {
    if (DAT_00409dfc == 0) {
      return -1;
    }
    FUN_00404c00();
    return 0;
  }
  puVar14 = &DAT_00409ce0;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined1 *)puVar14 = 0;
  if (local_14.MaxCharSize < 2) {
    DAT_00409de4 = 0;
    _DAT_00409de8 = 0;
  }
  else {
    if (local_14.LeadByte[0] != '\0') {
      pBVar11 = local_14.LeadByte + 1;
      do {
        bVar3 = *pBVar11;
        if (bVar3 == 0) break;
        for (uVar7 = (uint)pBVar11[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
          *(byte *)((int)&DAT_00409ce0 + uVar7 + 1) = *(byte *)((int)&DAT_00409ce0 + uVar7 + 1) | 4;
        }
        pBVar1 = pBVar11 + 1;
        pBVar11 = pBVar11 + 2;
      } while (*pBVar1 != 0);
    }
    uVar7 = 1;
    do {
      *(byte *)((int)&DAT_00409ce0 + uVar7 + 1) = *(byte *)((int)&DAT_00409ce0 + uVar7 + 1) | 8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0xff);
    DAT_00409de4 = CodePage;
    _DAT_00409de8 = FUN_00404ba0(CodePage);
  }
  _DAT_00409df0 = 0;
  _DAT_00409df4 = 0;
  _DAT_00409df8 = 0;
  return 0;
}


/* ==== FUN_00404b50 @ 00404b50 ==== */

int __cdecl FUN_00404b50(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_00409dfc = 1;
                    /* WARNING: Could not recover jumptable at 0x00404b6d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_00409dfc = 1;
                    /* WARNING: Could not recover jumptable at 0x00404b82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_00409e20;
  }
  DAT_00409dfc = (uint)bVar2;
  return param_1;
}


/* ==== FUN_00404ba0 @ 00404ba0 ==== */

undefined4 __cdecl FUN_00404ba0(undefined4 param_1)

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


/* ==== FUN_00404c00 @ 00404c00 ==== */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404c00(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00409ce0;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_00409de4 = 0;
  _DAT_00409de8 = 0;
  _DAT_00409df0 = 0;
  _DAT_00409df4 = 0;
  _DAT_00409df8 = 0;
  return;
}


/* ==== __initmbctable @ 00404c30 ==== */

int __initmbctable(void)

{
  int iVar1;
  
  iVar1 = _setmbcp(-3);
  return iVar1;
}


/* ==== __global_unwind2 @ 00404c40 ==== */

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x404c58,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


/* ==== __local_unwind2 @ 00404c82 ==== */

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
  puStack_18 = &LAB_00404c60;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_00404d16();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}


/* ==== FUN_00404d16 @ 00404d16 ==== */

void FUN_00404d16(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_004096f8 = *(undefined4 *)(unaff_EBP + 8);
  DAT_004096f4 = in_EAX;
  DAT_004096fc = unaff_EBP;
  return;
}


/* ==== FUN_00404df5 @ 00404df5 ==== */

void FUN_00404df5(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}


/* ==== _FF_MSGBANNER @ 00404e10 ==== */

void _FF_MSGBANNER(void)

{
  if ((DAT_00409bb0 == 1) || ((DAT_00409bb0 == 0 && (DAT_00407474 == 1)))) {
    _NMSG_WRITE(0xfc);
    if (DAT_00409e00 != (code *)0x0) {
      (*DAT_00409e00)();
    }
    _NMSG_WRITE(0xff);
  }
  return;
}


/* ==== _NMSG_WRITE @ 00404e50 ==== */

void __cdecl _NMSG_WRITE(int rterrnum)

{
  char cVar1;
  int *piVar2;
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
  
  piVar2 = &DAT_00409700;
  iVar8 = 0;
  do {
    if (rterrnum == *piVar2) break;
    piVar2 = piVar2 + 2;
    iVar8 = iVar8 + 1;
  } while (piVar2 < &DAT_00409790);
  if (rterrnum == (&DAT_00409700)[iVar8 * 2]) {
    if ((DAT_00409bb0 == 1) || ((DAT_00409bb0 == 0 && (DAT_00407474 == 1)))) {
      if ((__pioinfo == 0) || (hFile = *(HANDLE *)(__pioinfo + 0x10), hFile == (HANDLE)0xffffffff))
      {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar7 = *(char **)(iVar8 * 8 + 0x409704);
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
        strncpy(pcVar7,"...",3);
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
      pcVar7 = *(char **)(iVar8 * 8 + 0x409704);
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


/* ==== _dosmaperr @ 00405030 ==== */

void __cdecl _dosmaperr(ulong oserrno)

{
  undefined **ppuVar1;
  int iVar2;
  
  _doserrno = oserrno;
  iVar2 = 0;
  ppuVar1 = (undefined **)&DAT_00409790;
  do {
    if ((undefined *)oserrno == *ppuVar1) {
      errno = *(undefined4 *)(iVar2 * 8 + 0x409794);
      return;
    }
    ppuVar1 = ppuVar1 + 2;
    iVar2 = iVar2 + 1;
  } while (ppuVar1 < &_cfltcvt_tab);
  if ((0x12 < oserrno) && (oserrno < 0x25)) {
    errno = 0xd;
    return;
  }
  if ((oserrno < 0xbc) || (errno = 8, 0xca < oserrno)) {
    errno = 0x16;
  }
  return;
}


/* ==== _alloc_osfhnd @ 004050a0 ==== */

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
    if (0x409f3f < (int)piVar3) {
      return -1;
    }
  } while( true );
}


/* ==== _set_osfhnd @ 00405160 ==== */

int __cdecl _set_osfhnd(int fh,long value)

{
  int iVar1;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (*(int *)((&__pioinfo)[fh >> 5] + iVar1) == -1) {
      if (DAT_00407474 == 1) {
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


/* ==== _free_osfhnd @ 00405210 ==== */

int __cdecl _free_osfhnd(int fh)

{
  int iVar1;
  DWORD nStdHandle;
  
  if ((uint)fh < _nhandle) {
    iVar1 = (fh & 0x1fU) * 8;
    if (((*(byte *)((&__pioinfo)[fh >> 5] + 4 + iVar1) & 1) != 0) &&
       (*(int *)((&__pioinfo)[fh >> 5] + iVar1) != -1)) {
      if (DAT_00407474 == 1) {
        if (fh == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (fh == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (fh != 2) goto LAB_0040527a;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0040527a:
      *(undefined4 *)((&__pioinfo)[fh >> 5] + iVar1) = 0xffffffff;
      return 0;
    }
  }
  errno = 9;
  _doserrno = 0;
  return -1;
}


/* ==== _get_osfhandle @ 004052b0 ==== */

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


/* ==== _sopen @ 00405360 ==== */

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
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_00409e30 != 0x8000)))) {
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
    goto switchD_004053f8_caseD_11;
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
      goto LAB_0040548b;
    }
    if (uVar1 != 0) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00405466:
    dwCreationDisposition = 3;
    goto LAB_0040548b;
  }
  if (uVar1 < 0x301) {
    if (uVar1 == 0x300) {
      dwCreationDisposition = 2;
      goto LAB_0040548b;
    }
    if (uVar1 != 0x200) {
      errno = 0x16;
      _doserrno = 0;
      return -1;
    }
LAB_00405486:
    dwCreationDisposition = 5;
  }
  else {
    if (uVar1 < 0x501) {
      if (uVar1 != 0x500) {
        if (uVar1 != 0x400) {
switchD_004053f8_caseD_11:
          _doserrno = 0;
          errno = 0x16;
          return -1;
        }
        goto LAB_00405466;
      }
    }
    else {
      if (uVar1 == 0x600) goto LAB_00405486;
      if (uVar1 != 0x700) {
        errno = 0x16;
        _doserrno = 0;
        return -1;
      }
    }
    dwCreationDisposition = 1;
  }
LAB_0040548b:
  dwFlagsAndAttributes = 0x80;
  if (((oflag & 0x100U) != 0) && (((byte)pmode & ~(byte)DAT_00409b60 & 0x80) == 0)) {
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


/* ==== _isatty @ 00405720 ==== */

int __cdecl _isatty(int fh)

{
  if (_nhandle <= (uint)fh) {
    return 0;
  }
  return *(byte *)((&__pioinfo)[fh >> 5] + 4 + (fh & 0x1fU) * 8) & 0x40;
}


/* ==== wctomb @ 00405750 ==== */

int __cdecl wctomb(char *s,ushort wc)

{
  char *lpMultiByteStr;
  int iVar1;
  
  lpMultiByteStr = s;
  if (s == (char *)0x0) {
    return 0;
  }
  if (DAT_00409e10 == 0) {
    if (wc < 0x100) {
      *s = (char)wc;
      return 1;
    }
  }
  else {
    s = (char *)0x0;
    iVar1 = WideCharToMultiByte(DAT_00409e20,0x220,(LPCWSTR)&wc,1,lpMultiByteStr,__mb_cur_max,
                                (LPCSTR)0x0,(LPBOOL)&s);
    if ((iVar1 != 0) && (s == (char *)0x0)) {
      return iVar1;
    }
  }
  errno = 0x2a;
  return -1;
}


/* ==== __aulldiv @ 004057d0 ==== */

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


/* ==== __aullrem @ 00405840 ==== */

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


/* ==== _flsbuf @ 004058c0 ==== */

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
LAB_004059e0:
    *(uint *)((int)stream + 0xc) = uVar4 | 0x20;
    return -1;
  }
  uVar3 = 0;
  if ((uVar4 & 1) != 0) {
    *(undefined4 *)((int)stream + 4) = 0;
    if ((uVar4 & 0x10) == 0) goto LAB_004059e0;
    *(undefined4 *)stream = *(undefined4 *)((int)stream + 8);
    *(uint *)((int)stream + 0xc) = uVar4 & 0xfffffffe;
  }
  uVar4 = *(uint *)((int)stream + 0xc);
  *(undefined4 *)((int)stream + 4) = 0;
  *(uint *)((int)stream + 0xc) = uVar4 & 0xffffffef | 2;
  if ((uVar4 & 0x10c) == 0) {
    if ((stream == &DAT_00407210) || (stream == &DAT_00407230)) {
      iVar1 = _isatty(fh);
      if (iVar1 != 0) goto LAB_00405933;
    }
    _getbuf(stream_00);
  }
LAB_00405933:
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


/* ==== _getbuf @ 004059f0 ==== */

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


/* ==== __crtMessageBoxA @ 00405a50 ==== */

int __cdecl __crtMessageBoxA(char *text,char *caption,uint type)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_00409e24 != (FARPROC)0x0) {
LAB_00405aa0:
    if (DAT_00409e28 != (FARPROC)0x0) {
      iVar1 = (*DAT_00409e28)();
    }
    if ((iVar1 != 0) && (DAT_00409e2c != (FARPROC)0x0)) {
      iVar1 = (*DAT_00409e2c)(iVar1);
    }
    iVar1 = (*DAT_00409e24)(iVar1,text,caption,type);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_00409e24 = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_00409e24 != (FARPROC)0x0) {
      DAT_00409e28 = GetProcAddress(hModule,"GetActiveWindow");
      DAT_00409e2c = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_00405aa0;
    }
  }
  return 0;
}


/* ==== strncpy @ 00405ae0 ==== */

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
        goto joined_r0x00405b1e;
      }
    }
    do {
      if (((uint)dst & 3) == 0) {
        uVar5 = n >> 2;
        cVar4 = '\0';
        if (uVar5 == 0) goto LAB_00405b5b;
        goto LAB_00405bc9;
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
joined_r0x00405bc5:
          while( true ) {
            uVar5 = uVar5 - 1;
            dst = (char *)((int)dst + 4);
            if (uVar5 == 0) break;
LAB_00405bc9:
            *(uint *)dst = 0;
          }
          cVar4 = '\0';
          n = n & 3;
          if (n != 0) goto LAB_00405b5b;
          return cVar3;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *(uint *)dst = uVar2 & 0xff;
          goto joined_r0x00405bc5;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *(uint *)dst = uVar2 & 0xffff;
          goto joined_r0x00405bc5;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *(uint *)dst = uVar2;
          goto joined_r0x00405bc5;
        }
      }
      *(uint *)dst = uVar2;
      dst = (char *)((int)dst + 4);
      uVar5 = uVar5 - 1;
joined_r0x00405b1e:
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
LAB_00405b5b:
        *dst = cVar4;
        dst = (char *)((int)dst + 1);
      }
      return cVar3;
    }
    n = n - 1;
  } while (n != 0);
  return cVar3;
}


/* ==== _chsize @ 00405be0 ==== */

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
  
  FUN_00405df0();
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
      iVar4 = FUN_00405d70(in_stack_00001008,0x8000);
      while( true ) {
        cnt = 0x1000;
        if ((int)uVar6 < 0x1000) {
          cnt = uVar6;
        }
        iVar2 = _write(in_stack_00001008,&fh,cnt);
        if (iVar2 == -1) break;
        uVar6 = uVar6 - iVar2;
        if ((int)uVar6 < 1) {
LAB_00405cc1:
          FUN_00405d70(in_stack_00001008,iVar4);
          _lseek(in_stack_00001008,pos,0);
          return iVar5;
        }
      }
      if (_doserrno == 5) {
        errno = 0xd;
      }
      iVar5 = -1;
      goto LAB_00405cc1;
    }
  }
  else {
    errno = 9;
  }
  return -1;
}


/* ==== _fptrap @ 00405d60 ==== */

void _fptrap(void)

{
  _amsg_exit(2);
  return;
}


/* ==== FUN_00405d70 @ 00405d70 ==== */

int __cdecl FUN_00405d70(uint param_1,int param_2)

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


/* ==== FUN_00405df0 @ 00405df0 ==== */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_00405df0(void)

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


/* ==== RtlUnwind @ 00405e20 ==== */

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x00405e20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


