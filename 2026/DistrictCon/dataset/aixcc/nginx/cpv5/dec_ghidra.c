// Function: ngx_get_con_his

long ngx_get_con_his(long param_1,ulong param_2)

{
  ulong local_30;
  long local_28;
  long local_10;
  
  local_30 = 0;
  local_10 = param_1;
  if (((param_1 != 0) && (param_2 != 1)) && (local_28 = param_1, param_2 != 0)) {
    for (; local_30 <= param_2; local_30 = local_30 + 1) {
      local_28 = *(long *)(local_28 + 0x10);
    }
    local_10 = local_28;
  }
  return local_10;
}



// Function: ngx_http_get_last_ip_variable

undefined8 ngx_http_get_last_ip_variable(long param_1,uint *param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)
           ngx_get_con_his(*(undefined8 *)(param_1 + 0x10),*(undefined8 *)(param_1 + 8));
  *(undefined8 *)(param_2 + 2) = puVar1[1];
  *param_2 = *param_2 & 0xf0000000 | (uint)*puVar1 & 0xfffffff;
  return 0;
}



