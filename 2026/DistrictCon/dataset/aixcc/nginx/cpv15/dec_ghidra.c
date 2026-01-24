// Function: ngx_http_userid_get_uid

undefined4 * ngx_http_userid_get_uid(long param_1,long param_2)

{
  undefined4 *puVar1;
  long lVar2;
  long lVar3;
  undefined1 local_40 [8];
  undefined4 *local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  long local_18;
  undefined4 *local_10;
  
  local_10 = *(undefined4 **)(*(long *)(param_1 + 0x28) + ngx_http_userid_filter_module * 8);
  if (local_10 == (undefined4 *)0x0) {
    local_20 = param_2;
    local_18 = param_1;
    puVar1 = (undefined4 *)ngx_pcalloc(*(undefined8 *)(param_1 + 0x70),0x38);
    if (puVar1 == (undefined4 *)0x0) {
      local_10 = (undefined4 *)0x0;
    }
    else {
      *(undefined4 **)(*(long *)(local_18 + 0x28) + ngx_http_userid_filter_module * 8) = puVar1;
      lVar2 = ngx_http_parse_multi_header_lines
                        (local_18,*(undefined8 *)(local_18 + 0x1a0),local_20 + 0x18,puVar1 + 8);
      local_10 = puVar1;
      if (lVar2 != 0) {
        if ((**(ulong **)(*(long *)(local_18 + 0x20) + 0x60) & 0x100) != 0) {
          ngx_log_error_core(8,*(undefined8 *)(*(long *)(local_18 + 0x20) + 0x60),0,
                             "uid cookie: \"%V\"",puVar1 + 8);
        }
        if (*(ulong *)(puVar1 + 8) < 0x16) {
          if (3 < **(ulong **)(*(long *)(local_18 + 0x20) + 0x60)) {
            ngx_log_error_core(4,*(undefined8 *)(*(long *)(local_18 + 0x20) + 0x60),0,
                               "client sent too short userid cookie \"%V\"",lVar2 + 0x18);
          }
        }
        else {
          local_30 = *(undefined8 *)(puVar1 + 8);
          local_28 = *(undefined8 *)(puVar1 + 10);
          local_38 = puVar1;
          lVar3 = ngx_decode_base64(local_40,&local_30);
          if (lVar3 == -1) {
            if (3 < **(ulong **)(*(long *)(local_18 + 0x20) + 0x60)) {
              ngx_log_error_core(4,*(undefined8 *)(*(long *)(local_18 + 0x20) + 0x60),0,
                                 "client sent invalid userid cookie \"%V\"",lVar2 + 0x18);
            }
          }
          else if ((**(ulong **)(*(long *)(local_18 + 0x20) + 0x60) & 0x100) != 0) {
            ngx_log_error_core(8,*(undefined8 *)(*(long *)(local_18 + 0x20) + 0x60),0,
                               "uid: %08XD%08XD%08XD%08XD",*puVar1,puVar1[1],puVar1[2],puVar1[3]);
          }
        }
      }
    }
  }
  return local_10;
}



