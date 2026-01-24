// Function: ngx_init_cycle
ngx_cycle_t * ngx_init_cycle(ngx_cycle_t *old_cycle)
{
  int *v1; // rax
  size_t v2; // rax
  u_char *v3; // rax
  ngx_host_specs_t *v4; // rax
  ngx_str_t *v5; // rax
  u_char *v6; // rax
  u_char *v7; // rax
  ngx_str_t *v8; // rax
  u_char *v9; // rax
  u_char *v10; // rax
  ngx_str_t *v11; // rax
  u_char *v12; // rax
  u_char *v13; // rax
  ngx_fd_t v14; // eax
  int *v15; // rax
  int *v16; // rax
  int *v17; // rax
  int *v18; // rax
  int *v19; // rax
  int *v20; // rax
  int *v21; // rax
  ngx_log_t *v23; // [rsp+10h] [rbp-2B0h]
  ngx_log_t *v24; // [rsp+18h] [rbp-2A8h]
  ngx_log_t *v25; // [rsp+20h] [rbp-2A0h]
  ngx_log_t *v26; // [rsp+28h] [rbp-298h]
  ngx_log_t *v27; // [rsp+30h] [rbp-290h]
  ngx_log_t *v28; // [rsp+38h] [rbp-288h]
  ngx_log_t *v29; // [rsp+40h] [rbp-280h]
  ngx_log_t *v30; // [rsp+48h] [rbp-278h]
  ngx_uint_t nelts; // [rsp+50h] [rbp-270h]
  ngx_uint_t v32; // [rsp+58h] [rbp-268h]
  u_char *name; // [rsp+60h] [rbp-260h]
  char *temp_char; // [rsp+68h] [rbp-258h]
  char *temp_chara; // [rsp+68h] [rbp-258h]
  char *temp_charb; // [rsp+68h] [rbp-258h]
  char *temp_charc; // [rsp+68h] [rbp-258h]
  char *temp_chard; // [rsp+68h] [rbp-258h]
  char *temp_chare; // [rsp+68h] [rbp-258h]
  char line[64]; // [rsp+70h] [rbp-250h] BYREF
  char hostname[256]; // [rsp+B0h] [rbp-210h] BYREF
  ngx_core_module_t *module; // [rsp+1B0h] [rbp-110h]
  ngx_core_conf_t *old_ccf; // [rsp+1B8h] [rbp-108h]
  ngx_core_conf_t *ccf; // [rsp+1C0h] [rbp-100h]
  ngx_listening_t *nls; // [rsp+1C8h] [rbp-F8h]
  ngx_listening_t *ls; // [rsp+1D0h] [rbp-F0h]
  ngx_open_file_t *file; // [rsp+1D8h] [rbp-E8h]
  ngx_list_part_t *opart; // [rsp+1E0h] [rbp-E0h]
  ngx_list_part_t *part; // [rsp+1E8h] [rbp-D8h]
  ngx_shm_zone_t *oshm_zone; // [rsp+1F0h] [rbp-D0h]
  ngx_shm_zone_t *shm_zone; // [rsp+1F8h] [rbp-C8h]
  ngx_cycle_t **old; // [rsp+200h] [rbp-C0h]
  ngx_cycle_t *cycle; // [rsp+208h] [rbp-B8h]
  ngx_pool_t *pool; // [rsp+210h] [rbp-B0h]
  ngx_conf_t_1 conf; // [rsp+218h] [rbp-A8h] BYREF
  ngx_time_t *tp; // [rsp+278h] [rbp-48h]
  ngx_log_t *log; // [rsp+280h] [rbp-40h]
  ngx_uint_t n; // [rsp+288h] [rbp-38h]
  ngx_uint_t i; // [rsp+290h] [rbp-30h]
  char **senv; // [rsp+298h] [rbp-28h]
  void *rv; // [rsp+2A0h] [rbp-20h]
  FILE *fp; // [rsp+2A8h] [rbp-18h]
  ngx_cycle_t *old_cyclea; // [rsp+2B0h] [rbp-10h]

  old_cyclea = old_cycle;
  ngx_timezone_update();
  tp = (ngx_time_t *)ngx_cached_time;
  *(_QWORD *)ngx_cached_time = 0;
  ngx_time_update();
  log = old_cyclea->log;
  pool = ngx_create_pool(0x4000u, log);
  if ( !pool )
    return 0;
  pool->log = log;
  cycle = (ngx_cycle_t *)ngx_pcalloc(pool, 0x2A8u);
  memset(cycle, 0, sizeof(ngx_cycle_t));
  if ( !cycle )
    goto LABEL_38;
  cycle->pool = pool;
  cycle->log = log;
  cycle->old_cycle = old_cyclea;
  cycle->conf_prefix.len = old_cyclea->conf_prefix.len;
  cycle->conf_prefix.data = ngx_pstrdup(pool, &old_cyclea->conf_prefix);
  if ( !cycle->conf_prefix.data )
    goto LABEL_38;
  cycle->prefix.len = old_cyclea->prefix.len;
  cycle->prefix.data = ngx_pstrdup(pool, &old_cyclea->prefix);
  if ( !cycle->prefix.data )
    goto LABEL_38;
  cycle->error_log.len = old_cyclea->error_log.len;
  cycle->error_log.data = (u_char *)ngx_pnalloc(pool, old_cyclea->error_log.len + 1);
  if ( !cycle->error_log.data )
    goto LABEL_38;
  ngx_cpystrn(cycle->error_log.data, old_cyclea->error_log.data, old_cyclea->error_log.len + 1);
  cycle->conf_file.len = old_cyclea->conf_file.len;
  cycle->conf_file.data = (u_char *)ngx_pnalloc(pool, old_cyclea->conf_file.len + 1);
  if ( !cycle->conf_file.data )
    goto LABEL_38;
  ngx_cpystrn(cycle->conf_file.data, old_cyclea->conf_file.data, old_cyclea->conf_file.len + 1);
  cycle->conf_param.len = old_cyclea->conf_param.len;
  cycle->conf_param.data = ngx_pstrdup(pool, &old_cyclea->conf_param);
  if ( !cycle->conf_param.data )
    goto LABEL_38;
  v32 = old_cyclea->paths.nelts ? old_cyclea->paths.nelts : 10LL;
  n = v32;
  if ( ngx_array_init_2(&cycle->paths, pool, v32, 8u) )
    goto LABEL_38;
  memset(cycle->paths.elts, 0, 8 * n);
  if ( ngx_array_init_2(&cycle->config_dump, pool, 1u, 0x18u) )
    goto LABEL_38;
  cycle->config_dump_sentinel.color = 0;
  cycle->config_dump_rbtree.root = &cycle->config_dump_sentinel;
  cycle->config_dump_rbtree.sentinel = &cycle->config_dump_sentinel;
  cycle->config_dump_rbtree.insert = (ngx_rbtree_insert_pt)ngx_str_rbtree_insert_value;
  if ( old_cyclea->open_files.part.nelts )
  {
    n = old_cyclea->open_files.part.nelts;
    for ( part = old_cyclea->open_files.part.next; part; part = part->next )
      n += part->nelts;
  }
  else
  {
    n = 20;
  }
  if ( ngx_list_init_0(&cycle->open_files, pool, n, 0x28u) )
    goto LABEL_38;
  if ( old_cyclea->shared_memory.part.nelts )
  {
    n = old_cyclea->shared_memory.part.nelts;
    for ( part = old_cyclea->shared_memory.part.next; part; part = part->next )
      n += part->nelts;
  }
  else
  {
    n = 1;
  }
  if ( ngx_list_init_0(&cycle->shared_memory, pool, n, 0x58u)
    || (!old_cyclea->listening.nelts ? (nelts = 10) : (nelts = old_cyclea->listening.nelts),
        (n = nelts, ngx_array_init_2(&cycle->listening, pool, nelts, 0x128u))
     || (memset(cycle->listening.elts, 0, 296 * n),
         cycle->reusable_connections_queue.prev = &cycle->reusable_connections_queue,
         cycle->reusable_connections_queue.next = &cycle->reusable_connections_queue,
         (cycle->conf_ctx = (void ****)ngx_pcalloc(pool, 8 * ngx_max_module)) == 0)) )
  {
LABEL_38:
    ngx_destroy_pool(pool);
    return 0;
  }
  if ( gethostname(hostname, 0x100u) == -1 )
  {
    if ( log->log_level )
    {
      v30 = log;
      v1 = __errno_location();
      ngx_log_error_core(1u, v30, *v1, "gethostname() failed");
    }
    goto LABEL_57;
  }
  hostname[255] = 0;
  v2 = strlen(hostname);
  cycle->hostname.len = v2;
  v3 = (u_char *)ngx_pnalloc(pool, cycle->hostname.len);
  cycle->hostname.data = v3;
  if ( !cycle->hostname.data )
    goto LABEL_57;
  ngx_strlow(cycle->hostname.data, (u_char *)hostname, cycle->hostname.len);
  if ( ngx_cycle_modules(cycle) )
    goto LABEL_57;
  for ( i = 0; cycle->modules[i]; ++i )
  {
    if ( cycle->modules[i]->type == 1163022147 )
    {
      module = (ngx_core_module_t *)cycle->modules[i]->ctx;
      if ( module->create_conf )
      {
        rv = module->create_conf(cycle);
        if ( !rv )
          goto LABEL_57;
        cycle->conf_ctx[cycle->modules[i]->index] = (void ***)rv;
      }
    }
  }
  senv = environ;
  memset(&conf, 0, sizeof(conf));
  conf.args = ngx_array_create(pool, 0xAu, 0x10u);
  if ( !conf.args )
    goto LABEL_57;
  conf.temp_pool = ngx_create_pool(0x4000u, log);
  if ( !conf.temp_pool )
    goto LABEL_57;
  conf.ctx = cycle->conf_ctx;
  conf.cycle = cycle;
  conf.pool = pool;
  conf.log = log;
  conf.module_type = 1163022147;
  conf.cmd_type = 0x1000000;
  if ( ngx_conf_param(&conf) || ngx_conf_parse(&conf, &cycle->conf_file) )
  {
LABEL_69:
    environ = senv;
    ngx_destroy_cycle_pools(&conf);
    return 0;
  }
  if ( ngx_test_config && !ngx_quiet_mode )
    ngx_log_stderr(0, "the configuration file %s syntax is ok", (const char *)cycle->conf_file.data);
  for ( i = 0; cycle->modules[i]; ++i )
  {
    if ( cycle->modules[i]->type == 1163022147 )
    {
      module = (ngx_core_module_t *)cycle->modules[i]->ctx;
      if ( module->init_conf )
      {
        if ( module->init_conf(cycle, cycle->conf_ctx[cycle->modules[i]->index]) == (char *)-1LL )
          goto LABEL_69;
      }
    }
  }
  if ( ngx_process == 2 )
    return cycle;
  v4 = (ngx_host_specs_t *)ngx_alloc(0x18u, log);
  cycle->host_specs = v4;
  if ( !cycle->host_specs || (v5 = (ngx_str_t *)ngx_alloc(0x10u, log), (cycle->host_specs->host_cpu = v5) == 0) )
  {
LABEL_57:
    ngx_destroy_pool(pool);
    return 0;
  }
  cycle->host_specs->host_cpu->data = (u_char *)"Unknown CPU\n";
  memset(line, 0, sizeof(line));
  fp = fopen64("/proc/cpuinfo", "r");
  if ( fp )
  {
    while ( fgets(line, 64, fp) )
    {
      if ( !strncmp(line, "model name", 0xAu) )
      {
        temp_char = strchr(line, 58);
        if ( temp_char )
        {
          temp_chara = temp_char + 2;
          v6 = (u_char *)ngx_alloc(0x40u, log);
          cycle->host_specs->host_cpu->data = v6;
          if ( cycle->host_specs->host_cpu->data )
          {
            memset(cycle->host_specs->host_cpu->data, 0, 0x40u);
            v7 = ngx_sprintf(cycle->host_specs->host_cpu->data, "%s", temp_chara);
            cycle->host_specs->host_cpu->len = v7 - cycle->host_specs->host_cpu->data;
          }
          break;
        }
      }
    }
  }
  fclose(fp);
  v8 = (ngx_str_t *)ngx_alloc(0x10u, log);
  cycle->host_specs->host_mem = v8;
  if ( !cycle->host_specs->host_mem )
    goto LABEL_83;
  cycle->host_specs->host_mem->data = (u_char *)"Unknown RAM\n";
  memset(line, 0, sizeof(line));
  fp = fopen64("/proc/meminfo", "r");
  if ( fp )
  {
    while ( fgets(line, 64, fp) )
    {
      if ( !strncmp(line, "MemTotal:", 9u) )
      {
        temp_charb = strchr(line, 58);
        if ( temp_charb )
        {
          temp_charc = temp_charb + 8;
          v9 = (u_char *)ngx_alloc(0x40u, log);
          cycle->host_specs->host_mem->data = v9;
          if ( cycle->host_specs->host_mem->data )
          {
            memset(cycle->host_specs->host_mem->data, 0, 0x40u);
            v10 = ngx_sprintf(cycle->host_specs->host_mem->data, "%s", temp_charc);
            cycle->host_specs->host_mem->len = v10 - cycle->host_specs->host_mem->data;
          }
          break;
        }
      }
    }
  }
  fclose(fp);
  v11 = (ngx_str_t *)ngx_alloc(0x10u, log);
  cycle->host_specs->host_os = v11;
  if ( !cycle->host_specs->host_os )
  {
LABEL_83:
    ngx_destroy_pool(pool);
    return 0;
  }
  cycle->host_specs->host_os->data = (u_char *)"Unknown OS\n";
  memset(line, 0, sizeof(line));
  fp = fopen64("/etc/os-release", "r");
  if ( fp )
  {
    while ( fgets(line, 64, fp) )
    {
      if ( !strncmp(line, "PRETTY_NAME", 0xBu) )
      {
        temp_chard = strchr(line, 61);
        if ( temp_chard )
        {
          temp_chare = temp_chard + 1;
          v12 = (u_char *)ngx_alloc(0x40u, log);
          cycle->host_specs->host_os->data = v12;
          if ( cycle->host_specs->host_os->data )
          {
            memset(cycle->host_specs->host_os->data, 0, 0x40u);
            v13 = ngx_sprintf(cycle->host_specs->host_os->data, "%s", temp_chare);
            cycle->host_specs->host_os->len = v13 - cycle->host_specs->host_os->data;
          }
          break;
        }
      }
    }
  }
  fclose(fp);
  ccf = (ngx_core_conf_t *)cycle->conf_ctx[qword_19FFC0];
  if ( !ccf->remote_admin )
    free(cycle->host_specs);
  if ( ngx_test_config )
  {
    if ( ngx_create_pidfile(&ccf->pid, log) )
      goto failed;
  }
  else if ( old_cyclea->conf_ctx )
  {
    old_ccf = (ngx_core_conf_t *)old_cyclea->conf_ctx[qword_19FFC0];
    if ( ccf->pid.len != old_ccf->pid.len || strcmp((const char *)ccf->pid.data, (const char *)old_ccf->pid.data) )
    {
      if ( ngx_create_pidfile(&ccf->pid, log) )
        goto failed;
      ngx_delete_pidfile(old_cyclea);
    }
  }
  if ( ngx_test_lockfile(cycle->lock_file.data, log)
    || ngx_create_paths(cycle, ccf->user)
    || ngx_log_open_default(cycle) )
  {
    goto failed;
  }
  part = &cycle->open_files.part;
  file = (ngx_open_file_t *)cycle->open_files.part.elts;
  for ( i = 0; ; ++i )
  {
    if ( i < part->nelts )
      goto LABEL_116;
    if ( !part->next )
      break;
    part = part->next;
    file = (ngx_open_file_t *)part->elts;
    i = 0;
LABEL_116:
    if ( file[i].name.len )
    {
      v14 = open64((const char *)file[i].name.data, 1089, 420);
      file[i].fd = v14;
      if ( (log->log_level & 0x10) != 0 )
        ngx_log_error_core(8u, log, 0, "log: %p %d \"%s\"", &file[i], file[i].fd, (const char *)file[i].name.data);
      if ( file[i].fd == -1 )
      {
        if ( log->log_level )
        {
          v29 = log;
          v15 = __errno_location();
          ngx_log_error_core(1u, v29, *v15, "open() \"%s\" failed", (const char *)file[i].name.data);
        }
        goto failed;
      }
      if ( (unsigned int)fcntl64((unsigned int)file[i].fd, 2, 1) == -1 )
      {
        if ( log->log_level )
        {
          v28 = log;
          v16 = __errno_location();
          ngx_log_error_core(1u, v28, *v16, "fcntl(FD_CLOEXEC) \"%s\" failed", (const char *)file[i].name.data);
        }
        goto failed;
      }
    }
  }
  cycle->log = &cycle->new_log;
  pool->log = &cycle->new_log;
  part = &cycle->shared_memory.part;
  shm_zone = (ngx_shm_zone_t *)cycle->shared_memory.part.elts;
  for ( i = 0; ; ++i )
  {
    if ( i < part->nelts )
      goto LABEL_132;
    if ( !part->next )
      break;
    part = part->next;
    shm_zone = (ngx_shm_zone_t *)part->elts;
    i = 0;
LABEL_132:
    if ( !shm_zone[i].shm.size )
    {
      if ( log->log_level )
        ngx_log_error_core(1u, log, 0, "zero size shared memory zone \"%V\"", &shm_zone[i].shm.name);
      goto failed;
    }
    shm_zone[i].shm.log = cycle->log;
    opart = &old_cyclea->shared_memory.part;
    oshm_zone = (ngx_shm_zone_t *)old_cyclea->shared_memory.part.elts;
    for ( n = 0; ; ++n )
    {
      if ( n >= opart->nelts )
      {
        if ( !opart->next )
          goto LABEL_149;
        opart = opart->next;
        oshm_zone = (ngx_shm_zone_t *)opart->elts;
        n = 0;
      }
      if ( shm_zone[i].shm.name.len == oshm_zone[n].shm.name.len
        && !strncmp(
              (const char *)shm_zone[i].shm.name.data,
              (const char *)oshm_zone[n].shm.name.data,
              shm_zone[i].shm.name.len) )
      {
        break;
      }
    }
    if ( shm_zone[i].tag == oshm_zone[n].tag && shm_zone[i].shm.size == oshm_zone[n].shm.size && !shm_zone[i].noreuse )
    {
      shm_zone[i].shm.addr = oshm_zone[n].shm.addr;
      if ( shm_zone[i].init(&shm_zone[i], oshm_zone[n].data) )
        goto failed;
    }
    else
    {
LABEL_149:
      if ( ngx_shm_alloc(&shm_zone[i].shm)
        || ngx_init_zone_pool(cycle, &shm_zone[i])
        || shm_zone[i].init(&shm_zone[i], 0) )
      {
        goto failed;
      }
    }
  }
  if ( old_cyclea->listening.nelts )
  {
    ls = (ngx_listening_t *)old_cyclea->listening.elts;
    for ( i = 0; i < old_cyclea->listening.nelts; ++i )
      *((_DWORD *)&ls[i] + 72) &= ~2u;
    nls = (ngx_listening_t *)cycle->listening.elts;
    for ( n = 0; n < cycle->listening.nelts; ++n )
    {
      for ( i = 0; i < old_cyclea->listening.nelts; ++i )
      {
        if ( ((*((_DWORD *)&ls[i] + 72) >> 2) & 1) == 0
          && ((*((_DWORD *)&ls[i] + 72) >> 1) & 1) == 0
          && ls[i].type == nls[n].type
          && !ngx_cmp_sockaddr(nls[n].sockaddr, nls[n].socklen, ls[i].sockaddr, ls[i].socklen, 1u) )
        {
          nls[n].fd = ls[i].fd;
          *((_DWORD *)&nls[n] + 72) = (16 * ((*((_DWORD *)&ls[i] + 72) & 0x10) != 0))
                                    | *((_DWORD *)&nls[n] + 72) & 0xFFFFFFEF;
          nls[n].previous = &ls[i];
          *((_DWORD *)&ls[i] + 72) = *((_DWORD *)&ls[i] + 72) & 0xFFFFFFFD | 2;
          if ( ls[i].backlog != nls[n].backlog )
            *((_DWORD *)&nls[n] + 72) = *((_DWORD *)&nls[n] + 72) & 0xFFFFFFBF | 0x40;
          if ( (*((_DWORD *)&ls[i] + 72) & 0x10000) == 0 || (*((_DWORD *)&nls[n] + 72) & 0x10000) != 0 )
          {
            if ( (HIWORD(*((_DWORD *)&ls[i] + 72)) & 1) != (HIWORD(*((_DWORD *)&nls[n] + 72)) & 1) )
              *((_DWORD *)&nls[n] + 72) = *((_DWORD *)&nls[n] + 72) & 0xFFFBFFFF | 0x40000;
          }
          else
          {
            *((_DWORD *)&nls[n] + 72) = *((_DWORD *)&nls[n] + 72) & 0xFFFDFFFF | 0x20000;
          }
          if ( ((*((_DWORD *)&nls[n] + 72) >> 12) & 1) != 0 && ((*((_DWORD *)&ls[i] + 72) >> 12) & 1) == 0 )
            *((_DWORD *)&nls[n] + 72) = *((_DWORD *)&nls[n] + 72) & 0xFFFFDFFF | 0x2000;
          break;
        }
      }
      if ( nls[n].fd == -1 )
      {
        *((_DWORD *)&nls[n] + 72) = *((_DWORD *)&nls[n] + 72) & 0xFFFFFFFE | 1;
        if ( (*((_DWORD *)&nls[n] + 72) & 0x10000) != 0 )
          *((_DWORD *)&nls[n] + 72) = *((_DWORD *)&nls[n] + 72) & 0xFFFBFFFF | 0x40000;
      }
    }
  }
  else
  {
    ls = (ngx_listening_t *)cycle->listening.elts;
    for ( i = 0; i < cycle->listening.nelts; ++i )
    {
      *((_DWORD *)&ls[i] + 72) = *((_DWORD *)&ls[i] + 72) & 0xFFFFFFFE | 1;
      if ( (*((_DWORD *)&ls[i] + 72) & 0x10000) != 0 )
        *((_DWORD *)&ls[i] + 72) = *((_DWORD *)&ls[i] + 72) & 0xFFFBFFFF | 0x40000;
    }
  }
  if ( ngx_open_listening_sockets(cycle) )
  {
failed:
    if ( old_cyclea->conf_ctx )
    {
      old_ccf = (ngx_core_conf_t *)old_cyclea->conf_ctx[qword_19FFC0];
      if ( old_ccf->environment )
        environ = old_ccf->environment;
    }
    part = &cycle->open_files.part;
    file = (ngx_open_file_t *)cycle->open_files.part.elts;
    for ( i = 0; ; ++i )
    {
      if ( i >= part->nelts )
      {
        if ( !part->next )
        {
          part = &cycle->shared_memory.part;
          shm_zone = (ngx_shm_zone_t *)cycle->shared_memory.part.elts;
          for ( i = 0; ; ++i )
          {
            if ( i >= part->nelts )
            {
              if ( !part->next )
              {
                if ( !ngx_test_config )
                {
                  ls = (ngx_listening_t *)cycle->listening.elts;
                  for ( i = 0; i < cycle->listening.nelts; ++i )
                  {
                    if ( ls[i].fd != -1
                      && (*((_DWORD *)&ls[i] + 72) & 1) != 0
                      && close(ls[i].fd) == -1
                      && log->log_level )
                    {
                      v23 = log;
                      v21 = __errno_location();
                      ngx_log_error_core(1u, v23, *v21, "close() socket %V failed", &ls[i].addr_text);
                    }
                  }
                }
                ngx_destroy_cycle_pools(&conf);
                return 0;
              }
              part = part->next;
              shm_zone = (ngx_shm_zone_t *)part->elts;
              i = 0;
            }
            if ( shm_zone[i].shm.addr )
            {
              opart = &old_cyclea->shared_memory.part;
              oshm_zone = (ngx_shm_zone_t *)old_cyclea->shared_memory.part.elts;
              for ( n = 0; ; ++n )
              {
                if ( n >= opart->nelts )
                {
                  if ( !opart->next )
                    goto LABEL_283;
                  opart = opart->next;
                  oshm_zone = (ngx_shm_zone_t *)opart->elts;
                  n = 0;
                }
                if ( shm_zone[i].shm.name.len == oshm_zone[n].shm.name.len
                  && !strncmp(
                        (const char *)shm_zone[i].shm.name.data,
                        (const char *)oshm_zone[n].shm.name.data,
                        shm_zone[i].shm.name.len) )
                {
                  break;
                }
              }
              if ( shm_zone[i].tag != oshm_zone[n].tag
                || shm_zone[i].shm.size != oshm_zone[n].shm.size
                || shm_zone[i].noreuse )
              {
LABEL_283:
                ngx_shm_free(&shm_zone[i].shm);
                continue;
              }
            }
          }
        }
        part = part->next;
        file = (ngx_open_file_t *)part->elts;
        i = 0;
      }
      if ( file[i].fd != -1 && file[i].fd != 2 && close(file[i].fd) == -1 && log->log_level )
      {
        v24 = log;
        v20 = __errno_location();
        ngx_log_error_core(1u, v24, *v20, "close() \"%s\" failed", (const char *)file[i].name.data);
      }
    }
  }
  if ( !ngx_test_config )
    ngx_configure_listening_sockets(cycle);
  if ( !ngx_use_stderr )
    ngx_log_redirect_stderr(cycle);
  pool->log = cycle->log;
  if ( ngx_init_modules(cycle) )
    exit(1);
  opart = &old_cyclea->shared_memory.part;
  oshm_zone = (ngx_shm_zone_t *)old_cyclea->shared_memory.part.elts;
  for ( i = 0; i < opart->nelts; ++i )
  {
LABEL_198:
    part = &cycle->shared_memory.part;
    shm_zone = (ngx_shm_zone_t *)cycle->shared_memory.part.elts;
    for ( n = 0; ; ++n )
    {
      if ( n >= part->nelts )
      {
        if ( !part->next )
          goto LABEL_209;
        part = part->next;
        shm_zone = (ngx_shm_zone_t *)part->elts;
        n = 0;
      }
      if ( oshm_zone[i].shm.name.len == shm_zone[n].shm.name.len
        && !strncmp(
              (const char *)oshm_zone[i].shm.name.data,
              (const char *)shm_zone[n].shm.name.data,
              oshm_zone[i].shm.name.len) )
      {
        break;
      }
    }
    if ( oshm_zone[i].tag != shm_zone[n].tag || oshm_zone[i].shm.size != shm_zone[n].shm.size || oshm_zone[i].noreuse )
    {
LABEL_209:
      ngx_shm_free(&oshm_zone[i].shm);
      continue;
    }
  }
  if ( opart->next )
  {
    opart = opart->next;
    oshm_zone = (ngx_shm_zone_t *)opart->elts;
    i = 0;
    goto LABEL_198;
  }
  ls = (ngx_listening_t *)old_cyclea->listening.elts;
  for ( i = 0; i < old_cyclea->listening.nelts; ++i )
  {
    if ( ((*((_DWORD *)&ls[i] + 72) >> 1) & 1) == 0 && ls[i].fd != -1 )
    {
      if ( close(ls[i].fd) == -1 && log->log_level )
      {
        v27 = log;
        v17 = __errno_location();
        ngx_log_error_core(1u, v27, *v17, "close() socket listening socket on %V failed", &ls[i].addr_text);
      }
      if ( ls[i].sockaddr->sa_family == 1 )
      {
        name = ls[i].addr_text.data + 5;
        if ( cycle->log->log_level >= 5 )
          ngx_log_error_core(5u, cycle->log, 0, "deleting socket %s", (const char *)name);
        if ( unlink((const char *)name) == -1 && cycle->log->log_level )
        {
          v26 = cycle->log;
          v18 = __errno_location();
          ngx_log_error_core(1u, v26, *v18, "unlink() %s failed", (const char *)name);
        }
      }
    }
  }
  part = &old_cyclea->open_files.part;
  file = (ngx_open_file_t *)old_cyclea->open_files.part.elts;
  for ( i = 0; i < part->nelts; ++i )
  {
LABEL_230:
    if ( file[i].fd != -1 && file[i].fd != 2 && close(file[i].fd) == -1 && log->log_level )
    {
      v25 = log;
      v19 = __errno_location();
      ngx_log_error_core(1u, v25, *v19, "close() \"%s\" failed", (const char *)file[i].name.data);
    }
  }
  if ( part->next )
  {
    part = part->next;
    file = (ngx_open_file_t *)part->elts;
    i = 0;
    goto LABEL_230;
  }
  ngx_destroy_pool(conf.temp_pool);
  if ( ngx_process != 1 && old_cyclea->conf_ctx )
  {
    if ( !ngx_temp_pool )
    {
      ngx_temp_pool = ngx_create_pool(0x80u, cycle->log);
      if ( !ngx_temp_pool )
      {
        if ( cycle->log->log_level )
          ngx_log_error_core(1u, cycle->log, 0, "could not create ngx_temp_pool");
        exit(1);
      }
      n = 10;
      if ( ngx_array_init_2(&ngx_old_cycles, ngx_temp_pool, 0xAu, 8u) )
        exit(1);
      memset(ngx_old_cycles.elts, 0, 8 * n);
      qword_1BA8B0 = (long)ngx_clean_old_cycles;
      qword_1BA8C0 = (long)cycle->log;
      qword_1BA890 = (long)&dumb;
      dword_1BA918 = -1;
    }
    ngx_temp_pool->log = cycle->log;
    old = (ngx_cycle_t **)ngx_array_push(&ngx_old_cycles);
    if ( !old )
      exit(1);
    *old = old_cyclea;
    if ( (((unsigned int)dword_1BA8A8 >> 9) & 1) == 0 )
    {
      ngx_event_add_timer(&ngx_cleaner_event, 0x7530u);
      dword_1BA8A8 = dword_1BA8A8 & 0xFFFFFDFF | 0x200;
    }
    return cycle;
  }
  else
  {
    ngx_destroy_pool(old_cyclea->pool);
    cycle->old_cycle = 0;
    return cycle;
  }
}


