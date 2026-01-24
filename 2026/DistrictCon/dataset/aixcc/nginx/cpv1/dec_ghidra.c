// Function: ngx_http_validate_from

undefined8 ngx_http_validate_from(ulong *param_1,undefined8 param_2,long param_3)

{
  byte bVar1;
  ulong uVar2;
  ushort **ppuVar3;
  int local_4c;
  ulong local_48;
  byte *local_38;
  undefined8 local_10;
  
  uVar2 = param_1[1];
  local_4c = 0;
  if (param_3 == 0) {
    local_38 = (byte *)param_1[1];
  }
  else {
    local_38 = (byte *)ngx_palloc(param_2,*param_1);
    if (local_38 == (byte *)0x0) {
      return 0xffffffffffffffff;
    }
  }
  local_48 = 0;
  do {
    if (*param_1 <= local_48) {
      if (local_4c == 4) {
        *local_38 = 0;
        if (param_3 != 0) {
          param_1[1] = (ulong)local_38;
        }
        local_10 = 0;
      }
      else {
        local_10 = 0xfffffffffffffffb;
      }
      return local_10;
    }
    bVar1 = *(byte *)(uVar2 + local_48);
    switch(local_4c) {
    case 0:
      ppuVar3 = __ctype_b_loc();
      if (((((*ppuVar3)[(int)(uint)bVar1] & 8) == 0) && (bVar1 != 0x2d)) && (bVar1 != 0x5f)) {
        if (bVar1 != 0x2e) {
          return 0xfffffffffffffffb;
        }
        local_4c = 2;
      }
      else {
        local_4c = 1;
      }
      *local_38 = bVar1;
      local_38 = local_38 + 1;
      break;
    case 1:
      if (bVar1 == 0x40) {
        local_4c = 3;
      }
      else if (bVar1 == 0x2e) {
        local_4c = 2;
      }
      else {
        ppuVar3 = __ctype_b_loc();
        if (((((*ppuVar3)[(int)(uint)bVar1] & 8) == 0) && (bVar1 != 0x2d)) &&
           ((bVar1 != 0x5f && (bVar1 != 0x2b)))) {
          return 0xfffffffffffffffb;
        }
      }
      *local_38 = bVar1;
      local_38 = local_38 + 1;
      break;
    case 2:
      ppuVar3 = __ctype_b_loc();
      if (((((*ppuVar3)[(int)(uint)bVar1] & 8) == 0) && (bVar1 != 0x2d)) && (bVar1 != 0x5f)) {
        if (bVar1 != 0x2e) {
          return 0xfffffffffffffffb;
        }
        local_4c = 2;
        for (local_38 = local_38 + -2; *local_38 != 0x2e; local_38 = local_38 + -1) {
        }
      }
      else {
        *local_38 = bVar1;
        local_4c = 1;
      }
      local_38 = local_38 + 1;
      break;
    case 3:
      if (bVar1 == 0x2e) {
        local_4c = 4;
      }
      else {
        ppuVar3 = __ctype_b_loc();
        if ((((*ppuVar3)[(int)(uint)bVar1] & 8) == 0) && (bVar1 != 0x2d)) {
          return 0xfffffffffffffffb;
        }
      }
      *local_38 = bVar1;
      local_38 = local_38 + 1;
      break;
    case 4:
      ppuVar3 = __ctype_b_loc();
      if (((*ppuVar3)[(int)(uint)bVar1] & 0x400) == 0) {
        return 0xfffffffffffffffb;
      }
      *local_38 = bVar1;
      local_38 = local_38 + 1;
      break;
    default:
      return 0xfffffffffffffffb;
    }
    local_48 = local_48 + 1;
  } while( true );
}



