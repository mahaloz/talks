// Function: ngx_http_auth_basic_user

undefined8 ngx_http_auth_basic_user(long param_1)

{
  long lVar1;
  bool bVar2;
  ulong local_40;
  ulong local_38;
  char *local_30;
  ulong local_28;
  long local_20;
  long local_18;
  undefined8 local_10;
  
  if ((*(long *)(param_1 + 0x1a8) == 0) && (*(long *)(param_1 + 0x1b0) != 0)) {
    local_10 = 0xfffffffffffffffb;
  }
  else if (*(long *)(param_1 + 0x160) == 0) {
    *(char **)(param_1 + 0x1b0) = "";
    local_10 = 0xfffffffffffffffb;
  }
  else {
    local_38 = *(ulong *)(*(long *)(param_1 + 0x160) + 0x18);
    local_30 = *(char **)(*(long *)(param_1 + 0x160) + 0x20);
    local_18 = param_1;
    if ((local_38 < 6) || (lVar1 = ngx_strncasecmp(local_30,"Basic ",6), lVar1 != 0)) {
      *(char **)(local_18 + 0x1b0) = "";
      local_10 = 0xfffffffffffffffb;
    }
    else {
      local_38 = local_38 - 6;
      local_30 = (char *)((long)local_30 + 6);
      while( true ) {
        bVar2 = false;
        if (local_38 != 0) {
          bVar2 = *local_30 == ' ';
        }
        if (!bVar2) break;
        local_38 = local_38 - 1;
        local_30 = local_30 + 1;
      }
      if (local_38 == 0) {
        *(char **)(local_18 + 0x1b0) = "";
        local_10 = 0xfffffffffffffffb;
      }
      else {
        local_28 = 0x10;
        local_20 = ngx_pnalloc(*(undefined8 *)(local_18 + 0x70),0x11);
        if (local_20 == 0) {
          local_10 = 0xffffffffffffffff;
        }
        else {
          lVar1 = ngx_decode_base64(&local_28,&local_38);
          if (lVar1 == 0) {
            *(undefined1 *)(local_20 + local_28) = 0;
            for (local_40 = 0; (local_40 < local_28 && (*(char *)(local_20 + local_40) != ':'));
                local_40 = local_40 + 1) {
            }
            if ((local_40 == 0) || (local_40 == local_28)) {
              *(char **)(local_18 + 0x1b0) = "";
              local_10 = 0xfffffffffffffffb;
            }
            else {
              *(ulong *)(local_18 + 0x1a8) = local_40;
              *(long *)(local_18 + 0x1b0) = local_20;
              *(ulong *)(local_18 + 0x1b8) = (local_28 - local_40) + -1;
              *(ulong *)(local_18 + 0x1c0) = local_20 + local_40 + 1;
              local_10 = 0;
            }
          }
          else {
            *(char **)(local_18 + 0x1b0) = "";
            local_10 = 0xfffffffffffffffb;
          }
        }
      }
    }
  }
  return local_10;
}



