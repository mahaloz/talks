// Function: ngx_http_set_browser_cookie

undefined8 ngx_http_set_browser_cookie(long param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 local_10;
  
  if ((((*(ushort *)(param_1 + 0x208) >> 10 & 1) == 0) &&
      ((*(ushort *)(param_1 + 0x208) >> 5 & 1) == 0)) &&
     ((*(ushort *)(param_1 + 0x208) >> 9 & 1) == 0)) {
    local_10 = 0;
  }
  else {
    puVar1 = (undefined8 *)ngx_list_push(param_1 + 0x210);
    if (puVar1 == (undefined8 *)0x0) {
      local_10 = 0xffffffffffffffff;
    }
    else {
      *puVar1 = 1;
      puVar1[6] = 0;
      puVar1[1] = 0xe;
      puVar1[2] = "Browser-Cookie";
      uVar2 = ngx_pnalloc(*(undefined8 *)(param_1 + 0x70),0x2b);
      puVar1[4] = uVar2;
      if (puVar1[4] == 0) {
        *puVar1 = 0;
        local_10 = 0xffffffffffffffff;
      }
      else {
        if (((*(ushort *)(param_1 + 0x208) >> 10 & 1) == 0) || (*(long *)(param_1 + 0x1a0) == 0)) {
          lVar3 = ngx_sprintf(puVar1[4],"\"%xT-%xO\"",*(undefined8 *)(param_1 + 0x360),
                              *(undefined8 *)(param_1 + 0x348));
          puVar1[3] = lVar3 - puVar1[4];
        }
        else {
          lVar3 = ngx_sprintf(puVar1[4],"\"%xT-%xO\":%s",*(undefined8 *)(param_1 + 0x360),
                              *(undefined8 *)(param_1 + 0x348),
                              *(undefined8 *)(*(long *)(param_1 + 0x1a0) + 0x20));
          puVar1[3] = lVar3 - puVar1[4];
        }
        local_10 = 0;
      }
    }
  }
  return local_10;
}



