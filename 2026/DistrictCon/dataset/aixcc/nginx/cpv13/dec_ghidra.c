// Function: ngx_mail_pop3_pass

undefined8 ngx_mail_pop3_pass(long param_1,long param_2)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  bool bVar3;
  ulong local_40;
  long *local_30;
  undefined8 local_10;
  
  local_30 = (long *)(param_2 + 0x58);
  if (*(long *)(param_1 + 0x128) == 1) {
    puVar2 = *(undefined8 **)(param_1 + 0x120);
    *(undefined8 *)(param_1 + 0x70) = *puVar2;
    uVar1 = ngx_pnalloc(*(undefined8 *)(param_2 + 0x68),*(undefined8 *)(param_1 + 0x70));
    *(undefined8 *)(param_1 + 0x78) = uVar1;
    if (*(long *)(param_1 + 0x78) == 0) {
      local_10 = 0xffffffffffffffff;
    }
    else {
      memcpy(*(void **)(param_1 + 0x78),(void *)puVar2[1],*(size_t *)(param_1 + 0x70));
      if (*local_30 == 0) {
        local_10 = 0xfffffffffffffffc;
      }
      else {
        while( true ) {
          bVar3 = false;
          if (*local_30 != 0) {
            bVar3 = *(long *)(*local_30 + 0x10) != 0;
          }
          if (!bVar3) break;
          *local_30 = *(long *)(*local_30 + 0x10);
          local_30 = local_30 + 1;
        }
        puVar2 = (undefined8 *)ngx_pnalloc(*(undefined8 *)(param_2 + 0x68),0x18);
        if (puVar2 != (undefined8 *)0x0) {
          for (local_40 = 0; local_40 < *(ulong *)(param_1 + 0x60); local_40 = local_40 + 1) {
            *(undefined1 *)(puVar2[1] + local_40) =
                 *(undefined1 *)(*(long *)(param_1 + 0x68) + local_40);
          }
          *puVar2 = *(undefined8 *)(param_1 + 0x60);
        }
        if (*local_30 == 0) {
          *local_30 = (long)puVar2;
        }
        else {
          *(undefined8 **)(*local_30 + 0x10) = puVar2;
        }
        local_10 = 0xfffffffffffffffc;
      }
    }
  }
  else {
    local_10 = 0x14;
  }
  return local_10;
}



// Function: ngx_mail_pop3_logs

undefined8 ngx_mail_pop3_logs(long param_1,long param_2)

{
  char *pcVar1;
  undefined8 uVar2;
  undefined8 local_10;
  
  if (*(long *)(param_2 + 0x58) == 0) {
    uVar2 = ngx_pnalloc(*(undefined8 *)(param_2 + 0x68),0x18);
    *(undefined8 *)(param_2 + 0x58) = uVar2;
  }
  uVar2 = ngx_pnalloc(*(undefined8 *)(param_2 + 0x68),*(long *)(param_1 + 0x80) + 0x1d);
  *(undefined8 *)(param_1 + 0x18) = uVar2;
  if (*(long *)(param_1 + 0x18) == 0) {
    ngx_mail_session_internal_server_error(param_1);
    local_10 = 0xffffffffffffffff;
  }
  else {
    pcVar1 = *(char **)(param_1 + 0x18);
    *(undefined8 *)pcVar1 = pop3_logging._0_8_;
    *(undefined8 *)(pcVar1 + 8) = pop3_logging._8_8_;
    *(undefined8 *)(pcVar1 + 0x10) = pop3_logging._16_8_;
    *(undefined4 *)(pcVar1 + 0x18) = pop3_logging._24_4_;
    pcVar1[0x1c] = pop3_logging[0x1c];
    memcpy(pcVar1 + 0x1d,*(void **)(param_1 + 0x88),*(size_t *)(param_1 + 0x80));
    *(char **)(param_1 + 0x10) =
         pcVar1 + 0x1d + (*(long *)(param_1 + 0x80) - *(long *)(param_1 + 0x18));
    local_10 = 0;
  }
  return local_10;
}



