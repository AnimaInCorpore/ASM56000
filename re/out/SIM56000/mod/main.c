/* ==== main @ 00401000 ==== */

int main(int argc,char **argv,char **envp)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  char local_100 [256];
  
  sim_init_tables();
  dev_create(0,s_56001_00495030);
  gui_mode = 0;
  out_text(banner_ptr,1);
  iVar2 = max_devices;
  if (1 < argc) {
    cmd_execute(0,argv[1]);
    iVar2 = max_devices;
  }
LAB_00401060:
  if (((*(int *)(dev_state_tab + cur_dev_index * 4) == 0) ||
      (iVar3 = cur_dev_index, *(int *)(*(int *)(dev_state_tab + cur_dev_index * 4) + 0x40) != 0)) &&
     (iVar3 = 0, piVar1 = (int *)dev_state_tab, 0 < iVar2)) {
    do {
      if ((*piVar1 != 0) && (*(int *)(*piVar1 + 0x40) == 0)) {
        cur_dev_index = iVar3;
        run_dev_index = iVar3;
        scrollback_end(iVar3);
        iVar2 = max_devices;
        break;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar3 < iVar2);
  }
  if (iVar3 < iVar2) goto code_r0x004010b6;
  goto LAB_00401100;
code_r0x004010b6:
  if ((macro_active == 0) || (macro_read_line(iVar3,local_100), macro_active == 0)) {
    cmd_read_line(iVar3,local_100);
  }
  cmd_execute(iVar3,local_100);
  iVar2 = max_devices;
  if (max_devices <= iVar3) {
LAB_00401100:
    iVar3 = 0;
    if (0 < iVar2) {
      do {
        if ((*(int *)(dev_tab + iVar3 * 4) != 0) &&
           ((*(byte *)(*(int *)(dev_tab + iVar3 * 4) + 0x44) & 0x20) == 0)) {
          dev_housekeeping(iVar3);
          iVar2 = max_devices;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar2);
    }
  }
  goto LAB_00401060;
}


