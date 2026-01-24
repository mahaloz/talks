// Function: ngx_http_trace_handler

long ngx_http_trace_handler(long param_1)

{
  void *pvVar1;
  undefined1 *puVar2;
  undefined *puVar3;
  long lVar4;
  undefined8 uVar5;
  ulong local_58;
  long local_50;
  long local_40 [3];
  long local_28;
  long *local_20;
  long local_18;
  
  local_18 = param_1;
  local_40[2] = ngx_create_temp_buf(*(undefined8 *)(param_1 + 0x70),200);
  if (local_40[2] == 0) {
    return 500;
  }
  pvVar1 = *(void **)(local_40[2] + 8);
  memcpy(pvVar1,*(void **)(local_18 + 0x3a0),*(size_t *)(local_18 + 0x398));
  *(long *)(local_40[2] + 8) = (long)pvVar1 + *(long *)(local_18 + 0x398);
  puVar2 = *(undefined1 **)(local_40[2] + 8);
  *(undefined1 **)(local_40[2] + 8) = puVar2 + 1;
  *puVar2 = 10;
  local_50 = *(long *)(local_18 + 0x398) + 1;
  local_20 = (long *)(local_18 + 0x88);
  local_28 = *local_20;
  local_58 = 0;
  do {
    if ((ulong)local_20[1] <= local_58) {
      if (local_20[2] == 0) {
        *(ushort *)(local_40[2] + 0x50) = *(ushort *)(local_40[2] + 0x50) & 0xff7f | 0x80;
        puVar3 = PTR_s_message_http_0029ed50;
        uVar5 = DAT_0029ed48;
        *(undefined8 *)(local_18 + 0x280) = 200;
        *(undefined8 *)(local_18 + 0x318) = uVar5;
        *(undefined **)(local_18 + 800) = puVar3;
        *(long *)(local_18 + 0x348) = local_50;
        lVar4 = ngx_http_send_header(local_18);
        if (lVar4 == -1) {
          return -1;
        }
        if (0 < lVar4) {
          return lVar4;
        }
        if ((*(uint *)(local_18 + 0x4d8) >> 0xe & 1) != 0) {
          return lVar4;
        }
        local_40[0] = local_40[2];
        local_40[1] = 0;
        uVar5 = ngx_http_output_filter(local_18,local_40);
        ngx_http_close_request(local_18,uVar5);
        return -4;
      }
      local_20 = (long *)local_20[2];
      local_28 = *local_20;
      local_58 = 0;
    }
    local_50 = *(long *)(local_28 + local_58 * 0x38 + 8) +
               *(long *)(local_28 + local_58 * 0x38 + 0x18) + 3 + local_50;
    pvVar1 = *(void **)(local_40[2] + 8);
    memcpy(pvVar1,*(void **)(local_28 + local_58 * 0x38 + 0x10),
           *(size_t *)(local_28 + local_58 * 0x38 + 8));
    *(long *)(local_40[2] + 8) = (long)pvVar1 + *(long *)(local_28 + local_58 * 0x38 + 8);
    puVar2 = *(undefined1 **)(local_40[2] + 8);
    *(undefined1 **)(local_40[2] + 8) = puVar2 + 1;
    *puVar2 = 0x3a;
    puVar2 = *(undefined1 **)(local_40[2] + 8);
    *(undefined1 **)(local_40[2] + 8) = puVar2 + 1;
    *puVar2 = 0x20;
    pvVar1 = *(void **)(local_40[2] + 8);
    memcpy(pvVar1,*(void **)(local_28 + local_58 * 0x38 + 0x20),
           *(size_t *)(local_28 + local_58 * 0x38 + 0x18));
    *(long *)(local_40[2] + 8) = (long)pvVar1 + *(long *)(local_28 + local_58 * 0x38 + 0x18);
    puVar2 = *(undefined1 **)(local_40[2] + 8);
    *(undefined1 **)(local_40[2] + 8) = puVar2 + 1;
    *puVar2 = 10;
    local_58 = local_58 + 1;
  } while( true );
}



