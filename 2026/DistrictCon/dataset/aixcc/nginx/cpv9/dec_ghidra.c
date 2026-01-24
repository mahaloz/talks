// Function: ngx_black_list_insert

void ngx_black_list_insert(long *param_1,char *param_2,ulong param_3,undefined8 param_4)

{
  int iVar1;
  long lVar2;
  long *__s;
  long lVar3;
  bool bVar4;
  ulong local_48;
  long *local_30;
  
  lVar2 = ngx_alloc(param_3,param_4);
  for (local_48 = 0; local_48 < param_3; local_48 = local_48 + 1) {
    *(char *)(lVar2 + local_48) = param_2[local_48];
  }
  __s = (long *)ngx_alloc(0x18,param_4);
  lVar3 = ngx_alloc(0x10,param_4);
  *__s = lVar3;
  *(long *)(*__s + 8) = lVar2;
  *(ulong *)*__s = param_3;
  __s[1] = 0;
  local_30 = (long *)*param_1;
  if (local_30 == (long *)0x0) {
    *param_1 = (long)__s;
  }
  else {
    while( true ) {
      bVar4 = false;
      if (local_30 != (long *)0x0) {
        bVar4 = local_30[1] != 0;
      }
      if (!bVar4) {
        local_30[1] = (long)__s;
        __s[2] = (long)local_30;
        return;
      }
      iVar1 = strcmp(param_2,*(char **)(*local_30 + 8));
      if (iVar1 == 0) break;
      local_30 = (long *)local_30[1];
    }
    memset(*(void **)(*__s + 8),0,*(size_t *)*__s);
    free(*(void **)(*__s + 8));
    *(undefined8 *)(*__s + 8) = 0;
    memset((void *)*__s,0,0x10);
    free((void *)*__s);
    *__s = 0;
    memset(__s,0,0x18);
    free(__s);
  }
  return;
}



// Function: ngx_black_list_remove

undefined8 ngx_black_list_remove(undefined8 *param_1,char *param_2)

{
  long *__s;
  int iVar1;
  bool bVar2;
  long *local_28;
  
  __s = (long *)*param_1;
  if ((__s != (long *)0x0) && (iVar1 = strcmp(param_2,*(char **)(*__s + 8)), iVar1 == 0)) {
    memset(*(void **)(*__s + 8),0,*(size_t *)*__s);
    free(*(void **)(*__s + 8));
    *(undefined8 *)(*__s + 8) = 0;
    memset((void *)*__s,0,0x10);
    free((void *)*__s);
    *__s = 0;
    memset(__s,0,0x18);
    free(__s);
    return 0;
  }
  local_28 = (long *)__s[1];
  while( true ) {
    bVar2 = false;
    if (local_28 != (long *)0x0) {
      bVar2 = local_28[1] != 0;
    }
    if (!bVar2) break;
    iVar1 = strcmp(param_2,*(char **)(*local_28 + 8));
    if (iVar1 == 0) {
      if (local_28[2] != 0) {
        *(long *)(local_28[2] + 8) = local_28[1];
      }
      if (local_28[1] != 0) {
        *(long *)(local_28[1] + 0x10) = local_28[2];
      }
      memset(*(void **)(*local_28 + 8),0,*(size_t *)*local_28);
      free(*(void **)(*local_28 + 8));
      *(undefined8 *)(*local_28 + 8) = 0;
      memset((void *)*local_28,0,0x10);
      free((void *)*local_28);
      *local_28 = 0;
      memset(local_28,0,0x18);
      free(local_28);
      return 0;
    }
    local_28 = (long *)local_28[1];
  }
  return 0xffffffffffffffff;
}



// Function: ngx_is_ip_banned

undefined8 ngx_is_ip_banned(long param_1,long param_2)

{
  int iVar1;
  long *local_30;
  long *local_28;
  
  if (param_1 == 0) {
    local_30 = (long *)0x0;
  }
  else {
    local_30 = *(long **)(param_1 + 0x2a0);
  }
  local_28 = local_30;
  while( true ) {
    if (local_28 == (long *)0x0) {
      return 0;
    }
    iVar1 = strcmp(*(char **)(param_2 + 0x90),*(char **)(*local_28 + 8));
    if (iVar1 == 0) break;
    local_28 = (long *)local_28[1];
  }
  ngx_close_connection(param_2);
  return 0xffffffffffffffff;
}



