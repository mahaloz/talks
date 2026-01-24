// Function: ngx_sendfile_r

undefined8 ngx_sendfile_r(long param_1,long param_2,undefined8 param_3)

{
  int iVar1;
  void *__buf;
  ssize_t sVar2;
  void *__ptr;
  undefined8 uVar3;
  int local_d8;
  int local_d4;
  stat64 local_b8;
  undefined8 local_28;
  long local_20;
  long local_18;
  undefined8 local_10;
  
  local_28 = param_3;
  local_20 = param_2;
  local_18 = param_1;
  iVar1 = fstat64(**(int **)(param_2 + 0x40),&local_b8);
  if (iVar1 == 0) {
    __buf = (void *)ngx_palloc(*(undefined8 *)(local_18 + 0x68),local_b8.st_size);
    if (__buf == (void *)0x0) {
      local_10 = 0xffffffffffffffff;
    }
    else {
      sVar2 = read(**(int **)(local_20 + 0x40),__buf,local_b8.st_size);
      if (sVar2 == -1) {
        local_10 = 0xffffffffffffffff;
      }
      else {
        lseek64(**(int **)(local_20 + 0x40),0,0);
        __ptr = (void *)ngx_alloc(100,*(undefined8 *)(local_18 + 0x60));
        if (__ptr == (void *)0x0) {
          local_10 = 0xffffffffffffffff;
        }
        else {
          local_d4 = (int)*(undefined8 *)(local_20 + 0x10) + (int)local_28;
          local_d8 = 0;
          while (local_d4 = local_d4 + -1, *(long *)(local_20 + 0x10) <= (long)local_d4) {
            *(undefined1 *)((long)__ptr + (long)local_d8) =
                 *(undefined1 *)((long)__buf + (long)local_d4);
            local_d8 = local_d8 + 1;
          }
          uVar3 = (**(code **)(local_18 + 0x30))(local_18,__ptr,local_28);
          ngx_pfree(*(undefined8 *)(local_18 + 0x68),__buf);
          free(__ptr);
          local_10 = uVar3;
        }
      }
    }
  }
  else {
    local_10 = 0xffffffffffffffff;
  }
  return local_10;
}



