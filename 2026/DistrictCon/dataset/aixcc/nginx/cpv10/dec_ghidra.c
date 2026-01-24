// Function: ngx_http_process_prefer

undefined8 ngx_http_process_prefer(long param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 local_10;
  
  if (*(long *)(param_1 + 0xf0) == 0) {
    puVar1 = (undefined8 *)ngx_alloc(0x38,*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x60));
    if (puVar1 == (undefined8 *)0x0) {
      ngx_http_finalize_request(param_1,400);
      local_10 = 0xffffffffffffffff;
    }
    else {
      *puVar1 = *param_2;
      puVar1[1] = param_2[1];
      puVar1[2] = param_2[2];
      puVar1[3] = param_2[3];
      puVar1[4] = param_2[4];
      *(undefined8 **)(param_1 + 0xf0) = puVar1;
      local_10 = 0;
    }
  }
  else {
    if (6 < **(ulong **)(*(long *)(param_1 + 0x20) + 0x60)) {
      ngx_log_error_core(7,*(undefined8 *)(*(long *)(param_1 + 0x20) + 0x60),0,
                         "client sent duplicate host header: \"%V: %V\", previous value: \"%V: %V\""
                         ,param_2 + 1,param_2 + 3,*(long *)(param_1 + 0xf0) + 8,
                         *(long *)(param_1 + 0xf0) + 0x18);
    }
    free(*(void **)(param_1 + 0xf0));
    local_10 = 0;
  }
  return local_10;
}



