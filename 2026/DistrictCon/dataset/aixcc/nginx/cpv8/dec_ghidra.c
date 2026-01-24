// Function: ngx_mail_pop3_user

undefined8 ngx_mail_pop3_user(long param_1,long param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 local_10;
  
  if (*(long *)(param_1 + 0x128) == 1) {
    puVar1 = *(undefined8 **)(param_1 + 0x120);
    *(undefined8 *)(param_1 + 0x60) = *puVar1;
    uVar2 = ngx_pnalloc(*(undefined8 *)(param_2 + 0x68),100);
    *(undefined8 *)(param_1 + 0x68) = uVar2;
    if (*(long *)(param_1 + 0x68) == 0) {
      local_10 = 0xffffffffffffffff;
    }
    else {
      memcpy(*(void **)(param_1 + 0x68),(void *)puVar1[1],*(size_t *)(param_1 + 0x60));
      if ((**(ulong **)(param_2 + 0x60) & 0x200) != 0) {
        ngx_log_error_core(8,*(undefined8 *)(param_2 + 0x60),0,"pop3 login: \"%V\"",param_1 + 0x60);
      }
      *(undefined8 *)(param_1 + 0x50) = 1;
      local_10 = 0;
    }
  }
  else {
    local_10 = 0x14;
  }
  return local_10;
}



