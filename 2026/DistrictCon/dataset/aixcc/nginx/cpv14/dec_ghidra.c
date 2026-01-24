// Function: ngx_http_script_regex_end_code

void ngx_http_script_regex_end_code(long *param_1)

{
  long lVar1;
  long lVar2;
  undefined1 *puVar3;
  void *pvVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  void *local_20;
  void *local_18;
  long *local_10;
  
  lVar1 = *param_1;
  lVar2 = param_1[10];
  *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0xfb;
  local_10 = param_1;
  if ((**(ulong **)(*(long *)(lVar2 + 0x20) + 0x60) & 0x100) != 0) {
    ngx_log_error_core(8,*(undefined8 *)(*(long *)(lVar2 + 0x20) + 0x60),0,"http script regex end");
  }
  if ((*(byte *)(lVar1 + 8) >> 3 & 1) == 0) {
    if (local_10[7] == 0) {
      local_10[3] = local_10[1] - local_10[4];
      if (2000 < (ulong)local_10[3]) {
        if (3 < **(ulong **)(*(long *)(lVar2 + 0x20) + 0x60)) {
          ngx_log_error_core(4,*(undefined8 *)(*(long *)(lVar2 + 0x20) + 0x60),0,
                             "the rewritten URI is too long");
        }
        *local_10 = (long)&ngx_http_script_exit_code;
        local_10[9] = 500;
      }
      if ((*(byte *)(lVar1 + 8) >> 2 & 1) == 0) {
        *(undefined8 *)(lVar2 + 0x3b8) = 0;
      }
    }
    else {
      local_10[3] = local_10[7] - local_10[4];
      if (((*(byte *)(lVar1 + 8) >> 2 & 1) != 0) && (*(long *)(lVar2 + 0x3b8) != 0)) {
        puVar3 = (undefined1 *)local_10[1];
        local_10[1] = (long)(puVar3 + 1);
        *puVar3 = 0x26;
        pvVar4 = (void *)local_10[1];
        memcpy(pvVar4,*(void **)(lVar2 + 0x3c0),*(size_t *)(lVar2 + 0x3b8));
        local_10[1] = (long)pvVar4 + *(long *)(lVar2 + 0x3b8);
      }
      *(long *)(lVar2 + 0x3b8) = local_10[1] - local_10[7];
      *(long *)(lVar2 + 0x3c0) = local_10[7];
      local_10[7] = 0;
    }
    if ((((*(byte *)(local_10 + 8) >> 4 & 1) != 0) ||
        ((**(ulong **)(*(long *)(lVar2 + 0x20) + 0x60) & 0x100) != 0)) &&
       (5 < **(ulong **)(*(long *)(lVar2 + 0x20) + 0x60))) {
      ngx_log_error_core(6,*(undefined8 *)(*(long *)(lVar2 + 0x20) + 0x60),0,
                         "rewritten data: \"%V\", args: \"%V\"",local_10 + 3,lVar2 + 0x3b8);
    }
    if ((*(byte *)(lVar1 + 8) & 1) != 0) {
      *(long *)(lVar2 + 0x3a8) = local_10[3];
      *(long *)(lVar2 + 0x3b0) = local_10[4];
      if (*(long *)(lVar2 + 0x3a8) == 0) {
        if (3 < **(ulong **)(*(long *)(lVar2 + 0x20) + 0x60)) {
          ngx_log_error_core(4,*(undefined8 *)(*(long *)(lVar2 + 0x20) + 0x60),0,
                             "the rewritten URI has a zero length");
        }
        *local_10 = (long)&ngx_http_script_exit_code;
        local_10[9] = 500;
        return;
      }
      ngx_http_set_exten(lVar2);
    }
    *local_10 = *local_10 + 0x10;
  }
  else {
    local_18 = (void *)local_10[4];
    local_20 = (void *)local_10[4];
    ngx_unescape_uri(&local_18,&local_20,local_10[1] - local_10[4],2);
    pvVar4 = local_18;
    if (local_20 < (void *)local_10[1]) {
      memmove(local_18,local_20,local_10[1] - (long)local_20);
      local_18 = (void *)((long)pvVar4 + (local_10[1] - (long)local_20));
    }
    local_10[1] = (long)local_18;
    if (((*(byte *)(lVar1 + 8) >> 2 & 1) != 0) && (*(long *)(lVar2 + 0x3b8) != 0)) {
      uVar5 = 0x3f;
      if ((*(byte *)(lVar1 + 8) >> 1 & 1) != 0) {
        uVar5 = 0x26;
      }
      puVar3 = (undefined1 *)local_10[1];
      local_10[1] = (long)(puVar3 + 1);
      *puVar3 = uVar5;
      pvVar4 = (void *)local_10[1];
      memcpy(pvVar4,*(void **)(lVar2 + 0x3c0),*(size_t *)(lVar2 + 0x3b8));
      local_10[1] = (long)pvVar4 + *(long *)(lVar2 + 0x3b8);
    }
    local_10[3] = local_10[1] - local_10[4];
    if ((((*(byte *)(local_10 + 8) >> 4 & 1) != 0) ||
        ((**(ulong **)(*(long *)(lVar2 + 0x20) + 0x60) & 0x100) != 0)) &&
       (5 < **(ulong **)(*(long *)(lVar2 + 0x20) + 0x60))) {
      ngx_log_error_core(6,*(undefined8 *)(*(long *)(lVar2 + 0x20) + 0x60),0,
                         "rewritten redirect: \"%V\"",local_10 + 3);
    }
    if (*(long *)(lVar2 + 0x2b8) != 0) {
      **(undefined8 **)(lVar2 + 0x2b8) = 0;
      *(undefined8 *)(lVar2 + 0x2b8) = 0;
    }
    uVar6 = ngx_list_push(lVar2 + 0x210);
    *(undefined8 *)(lVar2 + 0x2b8) = uVar6;
    if (*(long *)(lVar2 + 0x2b8) == 0) {
      *local_10 = (long)&ngx_http_script_exit_code;
      local_10[9] = 500;
    }
    else {
      **(undefined8 **)(lVar2 + 0x2b8) = 1;
      *(undefined8 *)(*(long *)(lVar2 + 0x2b8) + 0x30) = 0;
      *(undefined8 *)(*(long *)(lVar2 + 0x2b8) + 8) = 8;
      *(char **)(*(long *)(lVar2 + 0x2b8) + 0x10) = "Location";
      lVar1 = *(long *)(lVar2 + 0x2b8);
      *(long *)(lVar1 + 0x18) = local_10[3];
      *(long *)(lVar1 + 0x20) = local_10[4];
      *local_10 = *local_10 + 0x10;
    }
  }
  return;
}



