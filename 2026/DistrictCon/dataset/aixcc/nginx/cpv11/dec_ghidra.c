// Function: ngx_init_cycle

long * ngx_init_cycle(long *param_1)

{
  ulong *puVar1;
  int iVar2;
  long lVar3;
  int *piVar4;
  size_t sVar5;
  undefined8 uVar6;
  char *pcVar7;
  ulong local_278;
  long local_270;
  char local_258 [64];
  char local_218 [255];
  undefined1 local_119;
  long local_118;
  long local_110;
  long local_108;
  long local_100;
  long local_f8;
  long local_f0;
  long *local_e8;
  long *local_e0;
  long local_d8;
  long local_d0;
  undefined8 *local_c8;
  long *local_c0;
  long local_b8;
  undefined1 local_b0 [8];
  long local_a8;
  long *local_a0;
  long local_98;
  long local_90;
  ulong *local_80;
  long local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 *local_50;
  ulong *local_48;
  ulong local_40;
  ulong local_38;
  undefined8 local_30;
  long local_28;
  FILE *local_20;
  long *local_18;
  
  local_18 = param_1;
  ngx_timezone_update();
  local_50 = ngx_cached_time;
  *ngx_cached_time = 0;
  ngx_time_update();
  local_48 = (ulong *)local_18[2];
  local_b8 = ngx_create_pool(0x4000,local_48);
  if (local_b8 == 0) {
    return (long *)0x0;
  }
  *(ulong **)(local_b8 + 0x48) = local_48;
  local_c0 = (long *)ngx_pcalloc(local_b8);
  memset(local_c0,0,0x2a8);
  if (local_c0 == (long *)0x0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  local_c0[1] = local_b8;
  local_c0[2] = (long)local_48;
  local_c0[0x43] = (long)local_18;
  local_c0[0x4a] = local_18[0x4a];
  lVar3 = ngx_pstrdup(local_b8,local_18 + 0x4a);
  local_c0[0x4b] = lVar3;
  if (local_c0[0x4b] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  local_c0[0x4c] = local_18[0x4c];
  lVar3 = ngx_pstrdup(local_b8,local_18 + 0x4c);
  local_c0[0x4d] = lVar3;
  if (local_c0[0x4d] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  local_c0[0x4e] = local_18[0x4e];
  lVar3 = ngx_pnalloc(local_b8,local_18[0x4e] + 1);
  local_c0[0x4f] = lVar3;
  if (local_c0[0x4f] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  ngx_cpystrn(local_c0[0x4f],local_18[0x4f],local_18[0x4e] + 1);
  local_c0[0x46] = local_18[0x46];
  lVar3 = ngx_pnalloc(local_b8,local_18[0x46] + 1);
  local_c0[0x47] = lVar3;
  if (local_c0[0x47] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  ngx_cpystrn(local_c0[0x47],local_18[0x47],local_18[0x46] + 1);
  local_c0[0x48] = local_18[0x48];
  lVar3 = ngx_pstrdup(local_b8,local_18 + 0x48);
  local_c0[0x49] = lVar3;
  if (local_c0[0x49] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  if (local_18[0x1f] == 0) {
    local_270 = 10;
  }
  else {
    local_270 = local_18[0x1f];
  }
  local_40 = local_270;
  lVar3 = ngx_array_init(local_c0 + 0x1e,local_b8,local_270,8);
  if (lVar3 != 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  memset((void *)local_c0[0x1e],0,local_40 << 3);
  lVar3 = ngx_array_init(local_c0 + 0x23,local_b8,1,0x18);
  if (lVar3 != 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  *(undefined1 *)(local_c0 + 0x2f) = 0;
  local_c0[0x28] = (long)(local_c0 + 0x2b);
  local_c0[0x29] = (long)(local_c0 + 0x2b);
  local_c0[0x2a] = (long)ngx_str_rbtree_insert_value;
  if (local_18[0x32] == 0) {
    local_40 = 0x14;
  }
  else {
    local_40 = local_18[0x32];
    for (local_e0 = (long *)local_18[0x33]; local_e0 != (long *)0x0;
        local_e0 = *(long **)((long)local_e0 + 0x10)) {
      local_40 = *(long *)((long)local_e0 + 8) + local_40;
    }
  }
  lVar3 = ngx_list_init(local_c0 + 0x30,local_b8,local_40,0x28);
  if (lVar3 != 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  if (local_18[0x39] == 0) {
    local_40 = 1;
  }
  else {
    local_40 = local_18[0x39];
    for (local_e0 = (long *)local_18[0x3a]; local_e0 != (long *)0x0;
        local_e0 = *(long **)((long)local_e0 + 0x10)) {
      local_40 = *(long *)((long)local_e0 + 8) + local_40;
    }
  }
  lVar3 = ngx_list_init(local_c0 + 0x37,local_b8,local_40,0x58);
  if (lVar3 != 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  if (local_18[0x1a] == 0) {
    local_278 = 10;
  }
  else {
    local_278 = local_18[0x1a];
  }
  local_40 = local_278;
  lVar3 = ngx_array_init(local_c0 + 0x19,local_b8,local_278,0x128);
  if (lVar3 != 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  memset((void *)local_c0[0x19],0,local_40 * 0x128);
  local_c0[0x15] = (long)(local_c0 + 0x15);
  local_c0[0x16] = (long)(local_c0 + 0x15);
  lVar3 = ngx_pcalloc(local_b8,ngx_max_module << 3);
  *local_c0 = lVar3;
  if (*local_c0 == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  iVar2 = gethostname(local_218,0x100);
  puVar1 = local_48;
  if (iVar2 == -1) {
    if (*local_48 != 0) {
      piVar4 = __errno_location();
      ngx_log_error_core(1,puVar1,*piVar4,"gethostname() failed");
    }
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  local_119 = 0;
  sVar5 = strlen(local_218);
  local_c0[0x52] = sVar5;
  lVar3 = ngx_pnalloc(local_b8,local_c0[0x52]);
  local_c0[0x53] = lVar3;
  if (local_c0[0x53] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  ngx_strlow(local_c0[0x53],local_218,local_c0[0x52]);
  lVar3 = ngx_cycle_modules(local_c0);
  if (lVar3 != 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  for (local_38 = 0; *(long *)(local_c0[0x12] + local_38 * 8) != 0; local_38 = local_38 + 1) {
    if ((*(long *)(*(long *)(local_c0[0x12] + local_38 * 8) + 0x48) == 0x45524f43) &&
       (local_118 = *(long *)(*(long *)(local_c0[0x12] + local_38 * 8) + 0x38),
       *(long *)(local_118 + 0x10) != 0)) {
      local_28 = (**(code **)(local_118 + 0x10))(local_c0);
      if (local_28 == 0) {
        ngx_destroy_pool(local_b8);
        return (long *)0x0;
      }
      *(long *)(*local_c0 + *(long *)(*(long *)(local_c0[0x12] + local_38 * 8) + 8) * 8) = local_28;
    }
  }
  local_30 = *(undefined8 *)PTR_environ_0029efa8;
  memset(local_b0,0,0x60);
  local_a8 = ngx_array_create(local_b8,10,0x10);
  if (local_a8 == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  local_90 = ngx_create_pool(0x4000,local_48);
  if (local_90 == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  local_78 = *local_c0;
  local_a0 = local_c0;
  local_98 = local_b8;
  local_80 = local_48;
  local_70 = 0x45524f43;
  local_68 = 0x1000000;
  lVar3 = ngx_conf_param(local_b0);
  if (lVar3 != 0) {
    *(undefined8 *)PTR_environ_0029efa8 = local_30;
    ngx_destroy_cycle_pools(local_b0);
    return (long *)0x0;
  }
  lVar3 = ngx_conf_parse(local_b0,local_c0 + 0x46);
  if (lVar3 != 0) {
    *(undefined8 *)PTR_environ_0029efa8 = local_30;
    ngx_destroy_cycle_pools(local_b0);
    return (long *)0x0;
  }
  if ((ngx_test_config != 0) && (ngx_quiet_mode == 0)) {
    ngx_log_stderr(0,"the configuration file %s syntax is ok",local_c0[0x47]);
  }
  for (local_38 = 0; *(long *)(local_c0[0x12] + local_38 * 8) != 0; local_38 = local_38 + 1) {
    if (((*(long *)(*(long *)(local_c0[0x12] + local_38 * 8) + 0x48) == 0x45524f43) &&
        (local_118 = *(long *)(*(long *)(local_c0[0x12] + local_38 * 8) + 0x38),
        *(long *)(local_118 + 0x18) != 0)) &&
       (lVar3 = (**(code **)(local_118 + 0x18))
                          (local_c0,*(undefined8 *)
                                     (*local_c0 +
                                     *(long *)(*(long *)(local_c0[0x12] + local_38 * 8) + 8) * 8)),
       lVar3 == -1)) {
      *(undefined8 *)PTR_environ_0029efa8 = local_30;
      ngx_destroy_cycle_pools(local_b0);
      return (long *)0x0;
    }
  }
  if (ngx_process == 2) {
    return local_c0;
  }
  lVar3 = ngx_alloc(0x18,local_48);
  local_c0[0x11] = lVar3;
  if (local_c0[0x11] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  uVar6 = ngx_alloc(0x10);
  *(undefined8 *)local_c0[0x11] = uVar6;
  if (*(long *)local_c0[0x11] == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  *(char **)(*(long *)local_c0[0x11] + 8) = "Unknown CPU\n";
  memset(local_258,0,0x40);
  local_20 = fopen64("/proc/cpuinfo","r");
  if (local_20 != (FILE *)0x0) {
    do {
      pcVar7 = fgets(local_258,0x40,local_20);
      if (pcVar7 == (char *)0x0) goto LAB_00149064;
      iVar2 = strncmp(local_258,"model name",10);
    } while ((iVar2 != 0) || (pcVar7 = strchr(local_258,0x3a), pcVar7 == (char *)0x0));
    uVar6 = ngx_alloc(0x40);
    *(undefined8 *)(*(long *)local_c0[0x11] + 8) = uVar6;
    if (*(long *)(*(long *)local_c0[0x11] + 8) != 0) {
      memset(*(void **)(*(long *)local_c0[0x11] + 8),0,0x40);
      lVar3 = ngx_sprintf(*(undefined8 *)(*(long *)local_c0[0x11] + 8),"%s",pcVar7 + 2);
      **(long **)local_c0[0x11] = lVar3 - *(long *)(*(long *)local_c0[0x11] + 8);
    }
  }
LAB_00149064:
  fclose(local_20);
  uVar6 = ngx_alloc(0x10);
  *(undefined8 *)(local_c0[0x11] + 8) = uVar6;
  if (*(long *)(local_c0[0x11] + 8) == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  *(char **)(*(long *)(local_c0[0x11] + 8) + 8) = "Unknown RAM\n";
  memset(local_258,0,0x40);
  local_20 = fopen64("/proc/meminfo","r");
  if (local_20 != (FILE *)0x0) {
    do {
      pcVar7 = fgets(local_258,0x40,local_20);
      if (pcVar7 == (char *)0x0) goto LAB_00149272;
      iVar2 = strncmp(local_258,"MemTotal:",9);
    } while ((iVar2 != 0) || (pcVar7 = strchr(local_258,0x3a), pcVar7 == (char *)0x0));
    uVar6 = ngx_alloc(0x40);
    *(undefined8 *)(*(long *)(local_c0[0x11] + 8) + 8) = uVar6;
    if (*(long *)(*(long *)(local_c0[0x11] + 8) + 8) != 0) {
      memset(*(void **)(*(long *)(local_c0[0x11] + 8) + 8),0,0x40);
      lVar3 = ngx_sprintf(*(undefined8 *)(*(long *)(local_c0[0x11] + 8) + 8),"%s",pcVar7 + 8);
      **(long **)(local_c0[0x11] + 8) = lVar3 - *(long *)(*(long *)(local_c0[0x11] + 8) + 8);
    }
  }
LAB_00149272:
  fclose(local_20);
  uVar6 = ngx_alloc(0x10);
  *(undefined8 *)(local_c0[0x11] + 0x10) = uVar6;
  if (*(long *)(local_c0[0x11] + 0x10) == 0) {
    ngx_destroy_pool(local_b8);
    return (long *)0x0;
  }
  *(char **)(*(long *)(local_c0[0x11] + 0x10) + 8) = "Unknown OS\n";
  memset(local_258,0,0x40);
  local_20 = fopen64("/etc/os-release","r");
  if (local_20 != (FILE *)0x0) {
    do {
      pcVar7 = fgets(local_258,0x40,local_20);
      if (pcVar7 == (char *)0x0) goto LAB_0014947a;
      iVar2 = strncmp(local_258,"PRETTY_NAME",0xb);
    } while ((iVar2 != 0) || (pcVar7 = strchr(local_258,0x3d), pcVar7 == (char *)0x0));
    uVar6 = ngx_alloc(0x40);
    *(undefined8 *)(*(long *)(local_c0[0x11] + 0x10) + 8) = uVar6;
    if (*(long *)(*(long *)(local_c0[0x11] + 0x10) + 8) != 0) {
      memset(*(void **)(*(long *)(local_c0[0x11] + 0x10) + 8),0,0x40);
      lVar3 = ngx_sprintf(*(undefined8 *)(*(long *)(local_c0[0x11] + 0x10) + 8),"%s",pcVar7 + 1);
      **(long **)(local_c0[0x11] + 0x10) = lVar3 - *(long *)(*(long *)(local_c0[0x11] + 0x10) + 8);
    }
  }
LAB_0014947a:
  fclose(local_20);
  local_108 = *(long *)(*local_c0 + ngx_core_module._8_8_ * 8);
  if (*(long *)(local_108 + 0x10) == 0) {
    free((void *)local_c0[0x11]);
  }
  if (ngx_test_config == 0) {
    if ((*local_18 != 0) &&
       ((local_110 = *(long *)(*local_18 + ngx_core_module._8_8_ * 8),
        *(long *)(local_108 + 0xa0) != *(long *)(local_110 + 0xa0) ||
        (iVar2 = strcmp(*(char **)(local_108 + 0xa8),*(char **)(local_110 + 0xa8)), iVar2 != 0)))) {
      lVar3 = ngx_create_pidfile(local_108 + 0xa0,local_48);
      if (lVar3 != 0) goto LAB_0014a9e0;
      ngx_delete_pidfile(local_18);
    }
  }
  else {
    lVar3 = ngx_create_pidfile(local_108 + 0xa0,local_48);
    if (lVar3 != 0) goto LAB_0014a9e0;
  }
  lVar3 = ngx_test_lockfile(local_c0[0x51],local_48);
  if (((lVar3 == 0) &&
      (lVar3 = ngx_create_paths(local_c0,*(undefined4 *)(local_108 + 0x78)), lVar3 == 0)) &&
     (lVar3 = ngx_log_open_default(local_c0), lVar3 == 0)) {
    local_e0 = local_c0 + 0x31;
    local_f0 = *local_e0;
    local_38 = 0;
    do {
      if ((ulong)local_e0[1] <= local_38) {
        if (local_e0[2] == 0) {
          local_c0[2] = (long)(local_c0 + 3);
          *(long **)(local_b8 + 0x48) = local_c0 + 3;
          local_e0 = local_c0 + 0x38;
          local_d0 = *local_e0;
          local_38 = 0;
          goto LAB_001498b5;
        }
        local_e0 = (long *)local_e0[2];
        local_f0 = *local_e0;
        local_38 = 0;
      }
      if (*(long *)(local_f0 + local_38 * 0x28 + 8) != 0) {
        iVar2 = open64(*(char **)(local_f0 + local_38 * 0x28 + 0x10),0x441,0x1a4);
        *(int *)(local_f0 + local_38 * 0x28) = iVar2;
        if ((*local_48 & 0x10) != 0) {
          ngx_log_error_core(8,local_48,0,"log: %p %d \"%s\"",local_f0 + local_38 * 0x28,
                             *(undefined4 *)(local_f0 + local_38 * 0x28),
                             *(undefined8 *)(local_f0 + local_38 * 0x28 + 0x10));
        }
        puVar1 = local_48;
        if (*(int *)(local_f0 + local_38 * 0x28) == -1) {
          if (*local_48 != 0) {
            piVar4 = __errno_location();
            ngx_log_error_core(1,puVar1,*piVar4,"open() \"%s\" failed",
                               *(undefined8 *)(local_f0 + local_38 * 0x28 + 0x10));
          }
          break;
        }
        iVar2 = fcntl64(*(undefined4 *)(local_f0 + local_38 * 0x28),2,1);
        puVar1 = local_48;
        if (iVar2 == -1) goto code_r0x001497f0;
      }
      local_38 = local_38 + 1;
    } while( true );
  }
LAB_0014a9e0:
  if ((*local_18 != 0) &&
     (local_110 = *(long *)(*local_18 + ngx_core_module._8_8_ * 8), *(long *)(local_110 + 0xe8) != 0
     )) {
    *(undefined8 *)PTR_environ_0029efa8 = *(undefined8 *)(local_110 + 0xe8);
  }
  local_e0 = local_c0 + 0x31;
  local_f0 = *local_e0;
  local_38 = 0;
  do {
    if ((ulong)local_e0[1] <= local_38) {
      if (local_e0[2] == 0) {
        local_e0 = local_c0 + 0x38;
        local_d0 = *local_e0;
        local_38 = 0;
        do {
          if ((ulong)local_e0[1] <= local_38) {
            if (local_e0[2] == 0) {
              if (ngx_test_config == 0) {
                local_f8 = local_c0[0x19];
                for (local_38 = 0; local_38 < (ulong)local_c0[0x1a]; local_38 = local_38 + 1) {
                  if ((((*(int *)(local_f8 + local_38 * 0x128) != -1) &&
                       ((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) & 1) != 0)) &&
                      (iVar2 = close(*(int *)(local_f8 + local_38 * 0x128)), puVar1 = local_48,
                      iVar2 == -1)) && (*local_48 != 0)) {
                    piVar4 = __errno_location();
                    ngx_log_error_core(1,puVar1,*piVar4,"close() socket %V failed",
                                       local_f8 + local_38 * 0x128 + 0x20);
                  }
                }
                ngx_destroy_cycle_pools(local_b0);
              }
              else {
                ngx_destroy_cycle_pools(local_b0);
              }
              return (long *)0x0;
            }
            local_e0 = (long *)local_e0[2];
            local_d0 = *local_e0;
            local_38 = 0;
          }
          if (*(long *)(local_d0 + local_38 * 0x58 + 8) != 0) {
            local_e8 = local_18 + 0x38;
            local_d8 = *local_e8;
            local_40 = 0;
            while( true ) {
              if ((ulong)local_e8[1] <= local_40) {
                if (local_e8[2] == 0) goto LAB_0014adb7;
                local_e8 = (long *)local_e8[2];
                local_d8 = *local_e8;
                local_40 = 0;
              }
              if ((*(long *)(local_d0 + local_38 * 0x58 + 0x18) ==
                   *(long *)(local_d8 + local_40 * 0x58 + 0x18)) &&
                 (iVar2 = strncmp(*(char **)(local_d0 + local_38 * 0x58 + 0x20),
                                  *(char **)(local_d8 + local_40 * 0x58 + 0x20),
                                  *(size_t *)(local_d0 + local_38 * 0x58 + 0x18)), iVar2 == 0))
              break;
              local_40 = local_40 + 1;
            }
            if ((*(long *)(local_d0 + local_38 * 0x58 + 0x40) !=
                 *(long *)(local_d8 + local_40 * 0x58 + 0x40)) ||
               ((*(long *)(local_d0 + local_38 * 0x58 + 0x10) !=
                 *(long *)(local_d8 + local_40 * 0x58 + 0x10) ||
                (*(long *)(local_d0 + local_38 * 0x58 + 0x50) != 0)))) {
LAB_0014adb7:
              ngx_shm_free(local_d0 + local_38 * 0x58 + 8);
            }
          }
          local_38 = local_38 + 1;
        } while( true );
      }
      local_e0 = (long *)local_e0[2];
      local_f0 = *local_e0;
      local_38 = 0;
    }
    if ((((*(int *)(local_f0 + local_38 * 0x28) != -1) &&
         (*(int *)(local_f0 + local_38 * 0x28) != 2)) &&
        (iVar2 = close(*(int *)(local_f0 + local_38 * 0x28)), puVar1 = local_48, iVar2 == -1)) &&
       (*local_48 != 0)) {
      piVar4 = __errno_location();
      ngx_log_error_core(1,puVar1,*piVar4,"close() \"%s\" failed",
                         *(undefined8 *)(local_f0 + local_38 * 0x28 + 0x10));
    }
    local_38 = local_38 + 1;
  } while( true );
LAB_001498b5:
  if ((ulong)local_e0[1] <= local_38) {
    if (local_e0[2] == 0) {
      if (local_18[0x1a] == 0) {
        local_f8 = local_c0[0x19];
        for (local_38 = 0; local_38 < (ulong)local_c0[0x1a]; local_38 = local_38 + 1) {
          lVar3 = local_f8 + local_38 * 0x128;
          *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffffffe | 1;
          if ((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 0x10 & 1) != 0) {
            lVar3 = local_f8 + local_38 * 0x128;
            *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffbffff | 0x40000;
          }
        }
      }
      else {
        local_f8 = local_18[0x19];
        for (local_38 = 0; local_38 < (ulong)local_18[0x1a]; local_38 = local_38 + 1) {
          lVar3 = local_f8 + local_38 * 0x128;
          *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffffffd;
        }
        local_100 = local_c0[0x19];
        for (local_40 = 0; local_40 < (ulong)local_c0[0x1a]; local_40 = local_40 + 1) {
          for (local_38 = 0; local_38 < (ulong)local_18[0x1a]; local_38 = local_38 + 1) {
            if ((((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 2 & 1) == 0) &&
                ((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 1 & 1) == 0)) &&
               ((*(int *)(local_f8 + local_38 * 0x128 + 0x30) ==
                 *(int *)(local_100 + local_40 * 0x128 + 0x30) &&
                (lVar3 = ngx_cmp_sockaddr(*(undefined8 *)(local_100 + local_40 * 0x128 + 8),
                                          *(undefined4 *)(local_100 + local_40 * 0x128 + 0x10),
                                          *(undefined8 *)(local_f8 + local_38 * 0x128 + 8),
                                          *(undefined4 *)(local_f8 + local_38 * 0x128 + 0x10),1),
                lVar3 == 0)))) {
              *(undefined4 *)(local_100 + local_40 * 0x128) =
                   *(undefined4 *)(local_f8 + local_38 * 0x128);
              lVar3 = local_100 + local_40 * 0x128;
              *(uint *)(lVar3 + 0x120) =
                   *(uint *)(lVar3 + 0x120) & 0xffffffef |
                   (*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 4 & 1) << 4;
              *(ulong *)(local_100 + local_40 * 0x128 + 200) = local_f8 + local_38 * 0x128;
              lVar3 = local_f8 + local_38 * 0x128;
              *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffffffd | 2;
              if (*(int *)(local_f8 + local_38 * 0x128 + 0x34) !=
                  *(int *)(local_100 + local_40 * 0x128 + 0x34)) {
                lVar3 = local_100 + local_40 * 0x128;
                *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xffffffbf | 0x40;
              }
              if (((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 0x10 & 1) == 0) ||
                 ((*(uint *)(local_100 + local_40 * 0x128 + 0x120) >> 0x10 & 1) != 0)) {
                if ((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 0x10 & 1) !=
                    (*(uint *)(local_100 + local_40 * 0x128 + 0x120) >> 0x10 & 1)) {
                  lVar3 = local_100 + local_40 * 0x128;
                  *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffbffff | 0x40000;
                }
              }
              else {
                lVar3 = local_100 + local_40 * 0x128;
                *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffdffff | 0x20000;
              }
              if (((*(uint *)(local_100 + local_40 * 0x128 + 0x120) >> 0xc & 1) != 0) &&
                 ((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 0xc & 1) == 0)) {
                lVar3 = local_100 + local_40 * 0x128;
                *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xffffdfff | 0x2000;
              }
              break;
            }
          }
          if ((*(int *)(local_100 + local_40 * 0x128) == -1) &&
             (lVar3 = local_100 + local_40 * 0x128,
             *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffffffe | 1,
             (*(uint *)(local_100 + local_40 * 0x128 + 0x120) >> 0x10 & 1) != 0)) {
            lVar3 = local_100 + local_40 * 0x128;
            *(uint *)(lVar3 + 0x120) = *(uint *)(lVar3 + 0x120) & 0xfffbffff | 0x40000;
          }
        }
      }
      lVar3 = ngx_open_listening_sockets(local_c0);
      if (lVar3 == 0) {
        if (ngx_test_config == 0) {
          ngx_configure_listening_sockets(local_c0);
        }
        if (ngx_use_stderr == 0) {
          ngx_log_redirect_stderr(local_c0);
        }
        *(long *)(local_b8 + 0x48) = local_c0[2];
        lVar3 = ngx_init_modules(local_c0);
        if (lVar3 != 0) {
                    /* WARNING: Subroutine does not return */
          exit(1);
        }
        local_e8 = local_18 + 0x38;
        local_d8 = *local_e8;
        local_38 = 0;
        do {
          if ((ulong)local_e8[1] <= local_38) {
            if (local_e8[2] == 0) {
              local_f8 = local_18[0x19];
              for (local_38 = 0; local_38 < (ulong)local_18[0x1a]; local_38 = local_38 + 1) {
                if (((*(uint *)(local_f8 + local_38 * 0x128 + 0x120) >> 1 & 1) == 0) &&
                   (*(int *)(local_f8 + local_38 * 0x128) != -1)) {
                  iVar2 = close(*(int *)(local_f8 + local_38 * 0x128));
                  puVar1 = local_48;
                  if ((iVar2 == -1) && (*local_48 != 0)) {
                    piVar4 = __errno_location();
                    ngx_log_error_core(1,puVar1,*piVar4,
                                       "close() socket listening socket on %V failed",
                                       local_f8 + local_38 * 0x128 + 0x20);
                  }
                  if (**(short **)(local_f8 + local_38 * 0x128 + 8) == 1) {
                    pcVar7 = (char *)(*(long *)(local_f8 + local_38 * 0x128 + 0x28) + 5);
                    if (4 < *(ulong *)local_c0[2]) {
                      ngx_log_error_core(5,local_c0[2],0,"deleting socket %s",pcVar7);
                    }
                    iVar2 = unlink(pcVar7);
                    if ((iVar2 == -1) && (*(long *)local_c0[2] != 0)) {
                      lVar3 = local_c0[2];
                      piVar4 = __errno_location();
                      ngx_log_error_core(1,lVar3,*piVar4,"unlink() %s failed",pcVar7);
                    }
                  }
                }
              }
              local_e0 = local_18 + 0x31;
              local_f0 = *local_e0;
              local_38 = 0;
              do {
                if ((ulong)local_e0[1] <= local_38) {
                  if (local_e0[2] == 0) {
                    ngx_destroy_pool(local_90);
                    if ((ngx_process == 1) || (*local_18 == 0)) {
                      ngx_destroy_pool(local_18[1]);
                      local_c0[0x43] = 0;
                      return local_c0;
                    }
                    if (ngx_temp_pool == 0) {
                      ngx_temp_pool = ngx_create_pool(0x80,local_c0[2]);
                      if (ngx_temp_pool == 0) {
                        if (*(long *)local_c0[2] != 0) {
                          ngx_log_error_core(1,local_c0[2],0,"could not create ngx_temp_pool");
                        }
                    /* WARNING: Subroutine does not return */
                        exit(1);
                      }
                      local_40 = 10;
                      lVar3 = ngx_array_init(&ngx_old_cycles,ngx_temp_pool,10,8);
                      if (lVar3 != 0) {
                    /* WARNING: Subroutine does not return */
                        exit(1);
                      }
                      memset(ngx_old_cycles,0,local_40 << 3);
                      ngx_cleaner_event._48_8_ = ngx_clean_old_cycles;
                      ngx_cleaner_event._64_8_ = local_c0[2];
                      ngx_cleaner_event._16_8_ = dumb;
                      dumb._24_4_ = 0xffffffff;
                    }
                    *(long *)(ngx_temp_pool + 0x48) = local_c0[2];
                    local_c8 = (undefined8 *)ngx_array_push(&ngx_old_cycles);
                    if (local_c8 == (undefined8 *)0x0) {
                    /* WARNING: Subroutine does not return */
                      exit(1);
                    }
                    *local_c8 = local_18;
                    if (((uint)ngx_cleaner_event._40_4_ >> 9 & 1) == 0) {
                      ngx_event_add_timer(ngx_cleaner_event,30000);
                      ngx_cleaner_event._40_4_ = ngx_cleaner_event._40_4_ & 0xfffffdff | 0x200;
                    }
                    return local_c0;
                  }
                  local_e0 = (long *)local_e0[2];
                  local_f0 = *local_e0;
                  local_38 = 0;
                }
                if ((((*(int *)(local_f0 + local_38 * 0x28) != -1) &&
                     (*(int *)(local_f0 + local_38 * 0x28) != 2)) &&
                    (iVar2 = close(*(int *)(local_f0 + local_38 * 0x28)), puVar1 = local_48,
                    iVar2 == -1)) && (*local_48 != 0)) {
                  piVar4 = __errno_location();
                  ngx_log_error_core(1,puVar1,*piVar4,"close() \"%s\" failed",
                                     *(undefined8 *)(local_f0 + local_38 * 0x28 + 0x10));
                }
                local_38 = local_38 + 1;
              } while( true );
            }
            local_e8 = (long *)local_e8[2];
            local_d8 = *local_e8;
            local_38 = 0;
          }
          local_e0 = local_c0 + 0x38;
          local_d0 = *local_e0;
          local_40 = 0;
          while( true ) {
            if ((ulong)local_e0[1] <= local_40) {
              if (local_e0[2] == 0) goto LAB_0014a48c;
              local_e0 = (long *)local_e0[2];
              local_d0 = *local_e0;
              local_40 = 0;
            }
            if ((*(long *)(local_d8 + local_38 * 0x58 + 0x18) ==
                 *(long *)(local_d0 + local_40 * 0x58 + 0x18)) &&
               (iVar2 = strncmp(*(char **)(local_d8 + local_38 * 0x58 + 0x20),
                                *(char **)(local_d0 + local_40 * 0x58 + 0x20),
                                *(size_t *)(local_d8 + local_38 * 0x58 + 0x18)), iVar2 == 0)) break;
            local_40 = local_40 + 1;
          }
          if ((*(long *)(local_d8 + local_38 * 0x58 + 0x40) !=
               *(long *)(local_d0 + local_40 * 0x58 + 0x40)) ||
             ((*(long *)(local_d8 + local_38 * 0x58 + 0x10) !=
               *(long *)(local_d0 + local_40 * 0x58 + 0x10) ||
              (*(long *)(local_d8 + local_38 * 0x58 + 0x50) != 0)))) {
LAB_0014a48c:
            ngx_shm_free(local_d8 + local_38 * 0x58 + 8);
          }
          local_38 = local_38 + 1;
        } while( true );
      }
      goto LAB_0014a9e0;
    }
    local_e0 = (long *)local_e0[2];
    local_d0 = *local_e0;
    local_38 = 0;
  }
  if (*(long *)(local_d0 + local_38 * 0x58 + 0x10) == 0) {
    if (*local_48 != 0) {
      ngx_log_error_core(1,local_48,0,"zero size shared memory zone \"%V\"",
                         local_d0 + local_38 * 0x58 + 0x18);
    }
    goto LAB_0014a9e0;
  }
  *(long *)(local_d0 + local_38 * 0x58 + 0x28) = local_c0[2];
  local_e8 = local_18 + 0x38;
  local_d8 = *local_e8;
  local_40 = 0;
  while( true ) {
    if ((ulong)local_e8[1] <= local_40) {
      if (local_e8[2] == 0) goto LAB_00149b81;
      local_e8 = (long *)local_e8[2];
      local_d8 = *local_e8;
      local_40 = 0;
    }
    if ((*(long *)(local_d0 + local_38 * 0x58 + 0x18) ==
         *(long *)(local_d8 + local_40 * 0x58 + 0x18)) &&
       (iVar2 = strncmp(*(char **)(local_d0 + local_38 * 0x58 + 0x20),
                        *(char **)(local_d8 + local_40 * 0x58 + 0x20),
                        *(size_t *)(local_d0 + local_38 * 0x58 + 0x18)), iVar2 == 0)) break;
    local_40 = local_40 + 1;
  }
  if ((*(long *)(local_d0 + local_38 * 0x58 + 0x40) == *(long *)(local_d8 + local_40 * 0x58 + 0x40))
     && ((*(long *)(local_d0 + local_38 * 0x58 + 0x10) ==
          *(long *)(local_d8 + local_40 * 0x58 + 0x10) &&
         (*(long *)(local_d0 + local_38 * 0x58 + 0x50) == 0)))) {
    *(undefined8 *)(local_d0 + local_38 * 0x58 + 8) =
         *(undefined8 *)(local_d8 + local_40 * 0x58 + 8);
    lVar3 = (**(code **)(local_d0 + local_38 * 0x58 + 0x38))
                      (local_d0 + local_38 * 0x58,*(undefined8 *)(local_d8 + local_40 * 0x58));
  }
  else {
LAB_00149b81:
    lVar3 = ngx_shm_alloc(local_d0 + local_38 * 0x58 + 8);
    if ((lVar3 != 0) ||
       (lVar3 = ngx_init_zone_pool(local_c0,local_d0 + local_38 * 0x58), lVar3 != 0))
    goto LAB_0014a9e0;
    lVar3 = (**(code **)(local_d0 + local_38 * 0x58 + 0x38))(local_d0 + local_38 * 0x58,0);
  }
  if (lVar3 != 0) goto LAB_0014a9e0;
  local_38 = local_38 + 1;
  goto LAB_001498b5;
code_r0x001497f0:
  if (*local_48 != 0) {
    piVar4 = __errno_location();
    ngx_log_error_core(1,puVar1,*piVar4,"fcntl(FD_CLOEXEC) \"%s\" failed",
                       *(undefined8 *)(local_f0 + local_38 * 0x28 + 0x10));
  }
  goto LAB_0014a9e0;
}



