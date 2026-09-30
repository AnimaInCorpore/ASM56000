/* ==== avl_new @ 0046a700 ==== */

void __cdecl avl_new(int cmp_type)

{
  undefined4 *extraout_EAX;
  undefined4 *puVar1;
  
  if (*(int *)(prof_ctx + 0x3500) == 1) {
    prof_malloc(0xc);
    extraout_EAX[1] = 0;
    *extraout_EAX = 0;
    extraout_EAX[2] = cmp_type;
    return;
  }
  puVar1 = (undefined4 *)pool_alloc(prof_ctx + 0x34e8,0xc);
  puVar1[1] = 0;
  *puVar1 = 0;
  puVar1[2] = cmp_type;
  return;
}


/* ==== avl_free @ 0046a750 ==== */

void __cdecl avl_free(void *tree,int free_mode)

{
  if (tree != (void *)0x0) {
    avl_cur_tree = tree;
    avl_free_nodes(*(void **)tree,free_mode);
    dsp_free(tree);
  }
  return;
}


/* ==== avl_free_nodes @ 0046a780 ==== */

void __cdecl avl_free_nodes(void *node,int free_mode)

{
  if (node != (void *)0x0) {
    avl_free_nodes(*(void **)((int)node + 4),free_mode);
    avl_free_nodes(*(void **)((int)node + 0xc),free_mode);
    if (free_mode == 1) {
      dsp_free(*(void **)((int)node + 8));
    }
    if (free_mode != 0) {
      dsp_free(node);
    }
  }
  return;
}


/* ==== avl_insert @ 0046a7d0 ==== */

void __cdecl avl_insert(void *tree,void *item,int replace)

{
  undefined4 extraout_EAX;
  
  if (tree != (void *)0x0) {
    avl_cur_tree = tree;
    avl_insert_node(*(void **)tree,item,replace);
    *(undefined4 *)tree = extraout_EAX;
  }
  return;
}


/* ==== avl_insert_node @ 0046a800 ==== */

void __cdecl avl_insert_node(void *node,void *item,int replace)

{
  undefined4 uVar1;
  void *n1;
  void *n1_00;
  void *extraout_EAX;
  void *node_00;
  
  if ((node == (void *)0x0) || (item == (void *)0x0)) {
    uVar1 = 3;
  }
  else {
    uVar1 = (*(code *)(&avl_cmp_tab)[*(int *)(avl_cur_tree + 8)])
                      (*(undefined4 *)((int)node + 8),item);
  }
  switch(uVar1) {
  case 0:
    goto switchD_0046a83d_caseD_0;
  case 1:
    if (replace == 0) {
      return;
    }
switchD_0046a83d_caseD_0:
    avl_insert_node(*(void **)((int)node + 4),item,replace);
    *(void **)((int)node + 4) = n1;
    avl_rebalance(node,n1,*(void **)((int)n1 + 4),*(void **)((int)n1 + 8),*(void **)((int)n1 + 0xc),
                  *(void **)((int)node + 8),*(void **)((int)node + 0xc));
    return;
  case 2:
    avl_insert_node(*(void **)((int)node + 0xc),item,replace);
    *(void **)((int)node + 0xc) = n1_00;
    avl_rebalance(node,n1_00,*(void **)((int)node + 4),*(void **)((int)node + 8),
                  *(void **)((int)n1_00 + 4),*(void **)((int)n1_00 + 8),*(void **)((int)n1_00 + 0xc)
                 );
    return;
  case 3:
    node_00 = avl_spare_node;
    if (avl_spare_node == (void *)0x0) {
      if (*(int *)(prof_ctx + 0x3500) == 1) {
        prof_malloc(0x10);
        node_00 = extraout_EAX;
      }
      else {
        node_00 = (void *)pool_alloc(prof_ctx + 0x34e8,0x10);
      }
    }
    avl_spare_node = (void *)0x0;
    *(int *)(avl_cur_tree + 4) = *(int *)(avl_cur_tree + 4) + 1;
    avl_set_node(node_00,(void *)0x0,item,(void *)0x0);
    return;
  default:
    return;
  }
}


/* ==== avl_set_node @ 0046a930 ==== */

void __cdecl avl_set_node(void *node,void *left,void *item,void *right)

{
  int iVar1;
  int iVar2;
  
  if (node != (void *)0x0) {
    *(void **)((int)node + 8) = item;
    *(void **)((int)node + 4) = left;
    *(void **)((int)node + 0xc) = right;
    if (left == (void *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)left;
    }
    if (right == (void *)0x0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)right;
    }
    if (iVar1 < iVar2) {
      if (left != (void *)0x0) {
        *(int *)node = *(int *)left + 1;
        return;
      }
    }
    else if (right != (void *)0x0) {
      *(int *)node = *(int *)right + 1;
      return;
    }
    *(undefined4 *)node = 1;
  }
  return;
}


/* ==== avl_rebalance @ 0046a990 ==== */

void __cdecl avl_rebalance(void *n0,void *n1,void *l,void *d1,void *m,void *d2,void *r)

{
  void *item;
  void *left;
  void *right;
  int iVar1;
  void *right_00;
  void *left_00;
  int iVar2;
  
  if (m == (void *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)m;
  }
  if (l == (void *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)l;
  }
  if (iVar1 < iVar2) {
    if (m == (void *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)m;
    }
    if (r == (void *)0x0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)r;
    }
    if (iVar1 < iVar2) {
      avl_set_node(n1,l,d1,*(void **)((int)m + 4));
      item = *(void **)((int)m + 8);
      avl_set_node(m,*(void **)((int)m + 0xc),d2,r);
      avl_set_node(n0,left,item,right);
      return;
    }
  }
  if (l == (void *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)l;
  }
  if (r == (void *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)r;
  }
  if (iVar1 <= iVar2) {
    avl_set_node(n1,m,d2,r);
    avl_set_node(n0,l,d1,right_00);
    return;
  }
  avl_set_node(n1,l,d1,m);
  avl_set_node(n0,left_00,d2,r);
  return;
}


/* ==== avl_delete @ 0046aa90 ==== */

void __cdecl avl_delete(void *tree,void *key,int free_mode,int repeat)

{
  undefined4 extraout_EAX;
  
  if (tree != (void *)0x0) {
    avl_cur_tree = tree;
    do {
      avl_removed = (void *)0x0;
      avl_delete_node(*(void **)tree,key);
      *(undefined4 *)tree = extraout_EAX;
      if (((free_mode != 0) || (avl_removed != (void *)0x0)) && (avl_removed != (void *)0x0)) {
        if (free_mode == 1) {
          dsp_free(*(void **)((int)avl_removed + 8));
        }
        if (free_mode != 0) {
          dsp_free(avl_removed);
        }
      }
    } while (repeat == 1);
  }
  return;
}


/* ==== avl_delete_node @ 0046ab20 ==== */

void __cdecl avl_delete_node(void *node,void *key)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  void *left;
  void *right;
  void *item;
  void *pvVar4;
  
  if ((node == (void *)0x0) || (key == (void *)0x0)) {
    iVar3 = 3;
  }
  else {
    iVar3 = (*(code *)(&avl_cmp_tab)[*(int *)(avl_cur_tree + 8)])
                      (*(undefined4 *)((int)node + 8),key);
  }
  if (iVar3 == 0) {
LAB_0046ab87:
    pvVar4 = *(void **)((int)node + 0xc);
    item = *(void **)((int)node + 8);
    avl_delete_node(*(void **)((int)node + 4),key);
    avl_set_node(node,left,item,pvVar4);
    pvVar4 = *(void **)((int)node + 0xc);
    if (pvVar4 != (void *)0x0) {
      avl_rebalance(node,pvVar4,*(void **)((int)node + 4),*(void **)((int)node + 8),
                    *(void **)((int)pvVar4 + 4),*(void **)((int)pvVar4 + 8),
                    *(void **)((int)pvVar4 + 0xc));
      return;
    }
  }
  else {
    if (iVar3 == 1) {
      iVar3 = *(int *)((int)node + 4);
      if (iVar3 != 0) {
        for (iVar2 = *(int *)(iVar3 + 0xc); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xc)) {
          iVar3 = iVar2;
        }
        uVar1 = *(undefined4 *)((int)node + 8);
        *(undefined4 *)((int)node + 8) = *(undefined4 *)(iVar3 + 8);
        *(undefined4 *)(iVar3 + 8) = uVar1;
        goto LAB_0046ab87;
      }
      iVar3 = *(int *)((int)node + 0xc);
      if (iVar3 == 0) {
        *(int *)(avl_cur_tree + 4) = *(int *)(avl_cur_tree + 4) + -1;
        avl_removed = node;
        return;
      }
      for (iVar2 = *(int *)(iVar3 + 4); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
        iVar3 = iVar2;
      }
      uVar1 = *(undefined4 *)((int)node + 8);
      *(undefined4 *)((int)node + 8) = *(undefined4 *)(iVar3 + 8);
      *(undefined4 *)(iVar3 + 8) = uVar1;
    }
    else if (iVar3 != 2) {
      return;
    }
    avl_delete_node(*(void **)((int)node + 0xc),key);
    avl_set_node(node,*(void **)((int)node + 4),*(void **)((int)node + 8),right);
    pvVar4 = *(void **)((int)node + 4);
    if (pvVar4 != (void *)0x0) {
      avl_rebalance(node,pvVar4,*(void **)((int)pvVar4 + 4),*(void **)((int)pvVar4 + 8),
                    *(void **)((int)pvVar4 + 0xc),*(void **)((int)node + 8),
                    *(void **)((int)node + 0xc));
      return;
    }
  }
  return;
}


/* ==== avl_find @ 0046ac60 ==== */

void __cdecl avl_find(void *tree,void *key,int mode)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (tree == (void *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)tree;
  }
  iVar2 = 0;
  avl_cur_tree = tree;
  if (iVar3 != 0) {
    if (iVar3 == 0) goto LAB_0046aca6;
    do {
      if (key == (void *)0x0) {
LAB_0046aca6:
        iVar1 = 3;
      }
      else {
        iVar1 = (*(code *)(&avl_cmp_tab)[*(int *)((int)avl_cur_tree + 8)])
                          (*(undefined4 *)(iVar3 + 8),key);
      }
      if (iVar1 == 1) {
        return;
      }
      if (iVar1 != mode) {
        iVar2 = iVar3;
      }
      if (iVar1 == 0) {
        iVar3 = *(int *)(iVar3 + 4);
      }
      else {
        iVar3 = *(int *)(iVar3 + 0xc);
      }
    } while (iVar3 != 0);
  }
  if ((mode != 1) && (iVar2 != 0)) {
    return;
  }
  return;
}


/* ==== avl_walk @ 0046acf0 ==== */

void __cdecl avl_walk(void *tree,void *fn,int order,int bracket)

{
  if (tree != (void *)0x0) {
    if ((bracket == 1) || (bracket == 3)) {
      (*fn)(0);
    }
    avl_walk_node(*(void **)tree,fn,order);
    if ((bracket == 2) || (bracket == 3)) {
      (*fn)(0);
    }
  }
  return;
}


/* ==== avl_walk_node @ 0046ad40 ==== */

void __cdecl avl_walk_node(void *node,void *fn,int order)

{
  bool bVar1;
  void *pvVar2;
  
  if (node != (void *)0x0) {
    if (((order == 2) || (order == 0)) || (order == 4)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((order == 2) || (order == 3)) {
      (*fn)(*(undefined4 *)((int)node + 8));
    }
    if (bVar1) {
      pvVar2 = *(void **)((int)node + 4);
    }
    else {
      pvVar2 = *(void **)((int)node + 0xc);
    }
    avl_walk_node(pvVar2,fn,order);
    if ((order == 0) || (order == 1)) {
      (*fn)(*(undefined4 *)((int)node + 8));
    }
    if (bVar1) {
      pvVar2 = *(void **)((int)node + 0xc);
    }
    else {
      pvVar2 = *(void **)((int)node + 4);
    }
    avl_walk_node(pvVar2,fn,order);
    if ((order == 4) || (order == 5)) {
      (*fn)(*(undefined4 *)((int)node + 8));
    }
  }
  return;
}


/* ==== avl_copy_sorted @ 0046ade0 ==== */

void __cdecl avl_copy_sorted(void *tree,int cmp_type,int resort)

{
  int iVar1;
  char cVar2;
  char cVar3;
  void *tree_00;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  void *item_00;
  undefined4 local_c;
  undefined4 local_8;
  int local_4;
  void *item;
  
  if (resort == 1) {
    local_8 = 0;
    local_c = 0;
    iVar1 = *(int *)tree;
    local_4 = cmp_type;
    while (iVar1 != 0) {
      avl_delete(tree,*(void **)(iVar1 + 8),0,0);
      avl_spare_node = avl_removed;
      avl_insert(&local_c,item_00,1);
      iVar1 = *(int *)tree;
    }
    *(undefined4 *)tree = local_c;
    *(undefined4 *)((int)tree + 4) = local_8;
    *(int *)((int)tree + 8) = local_4;
    return;
  }
  avl_new(cmp_type);
  cVar2 = avl_iter(tree,(char *)0x0,(void *)0x0);
  cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
  item = (void *)CONCAT31(extraout_var_00,cVar3);
  while (item != (void *)0x0) {
    avl_insert(tree_00,item,1);
    cVar3 = avl_iter((void *)0x0,(char *)CONCAT31(extraout_var,cVar2),(void *)0x0);
    item = (void *)CONCAT31(extraout_var_01,cVar3);
  }
  return;
}


/* ==== avl_iter @ 0046aec0 ==== */

char __cdecl avl_iter(void *tree,char *iter,void *key)

{
  char cVar1;
  char *extraout_EAX;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  if (tree == (void *)0x0) {
    if (iter == (char *)0x0) {
      return '\0';
    }
    avl_cur_tree = *(void **)(iter + 0x104);
    pcVar3 = *(char **)(iter + 0x100);
    if (iter <= pcVar3) {
      do {
        iVar5 = *(int *)(pcVar3 + 4);
        if (iVar5 == 0) {
          *(char **)(iter + 0x100) = pcVar3 + -8;
        }
        else {
          *pcVar3 = *pcVar3 + '\x01';
          pcVar3 = *(char **)(iter + 0x100);
          cVar1 = *pcVar3;
          if (cVar1 == '\x01') {
            *(char **)(iter + 0x100) = pcVar3 + 8;
            pcVar3[8] = '\0';
            *(undefined4 *)(*(int *)(iter + 0x100) + 4) = *(undefined4 *)(iVar5 + 4);
          }
          else {
            if (cVar1 == '\x02') {
              iVar4 = *(int *)(iter + 0x100);
              *(undefined1 **)(iter + 0x100) = (undefined1 *)(iVar4 + 8);
              *(undefined1 *)(iVar4 + 8) = 0;
              *(undefined4 *)(*(int *)(iter + 0x100) + 4) = *(undefined4 *)(iVar5 + 0xc);
              if ((iVar5 == 0) || (*(int *)(iter + 0x108) == 0)) {
                iVar4 = 3;
              }
              else {
                iVar4 = (*(code *)(&avl_cmp_tab)[*(int *)((int)avl_cur_tree + 8)])
                                  (*(undefined4 *)(iVar5 + 8),*(int *)(iter + 0x108));
              }
              if (iVar4 != 0) {
                return (char)*(undefined4 *)(iVar5 + 8);
              }
              break;
            }
            if (cVar1 == '\x03') {
              *(char **)(iter + 0x100) = pcVar3 + -8;
            }
          }
        }
        pcVar3 = *(char **)(iter + 0x100);
        if (pcVar3 < iter) {
          dsp_free(iter);
          return '\0';
        }
      } while( true );
    }
  }
  else {
    iVar5 = 0;
    if (*(int *)tree == 0) {
      return '\0';
    }
    prof_malloc(0x10c);
    iVar4 = *(int *)tree;
    avl_cur_tree = tree;
    *(char **)(extraout_EAX + 0x100) = extraout_EAX;
    if (iVar4 != 0) {
      if (iVar4 == 0) goto LAB_0046af22;
      do {
        if (iter == (char *)0x0) {
LAB_0046af22:
          iVar2 = 3;
        }
        else {
          iVar2 = (*(code *)(&avl_cmp_tab)[*(int *)((int)avl_cur_tree + 8)])
                            (*(undefined4 *)(iVar4 + 8),iter);
        }
        *(int *)(*(int *)(extraout_EAX + 0x100) + 4) = iVar4;
        **(char **)(extraout_EAX + 0x100) = (iVar2 == 2) + '\x01';
        if ((iVar2 == 2) || (iVar5 = *(int *)(extraout_EAX + 0x100), iVar2 == 2)) {
          iVar4 = *(int *)(iVar4 + 0xc);
        }
        else {
          iVar4 = *(int *)(iVar4 + 4);
        }
        *(int *)(extraout_EAX + 0x100) = *(int *)(extraout_EAX + 0x100) + 8;
      } while (iVar4 != 0);
    }
    iter = extraout_EAX;
    if (iVar5 != 0) {
      *(int *)(extraout_EAX + 0x100) = iVar5;
      *(void **)(extraout_EAX + 0x108) = key;
      *(void **)(extraout_EAX + 0x104) = tree;
      return (char)extraout_EAX;
    }
  }
  dsp_free(iter);
  return '\0';
}


