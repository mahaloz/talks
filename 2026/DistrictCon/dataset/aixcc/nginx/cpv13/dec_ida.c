// Function: ngx_mail_pop3_pass
ngx_int_t  ngx_mail_pop3_pass(ngx_mail_session_t *s, ngx_connection_t *c)
{
  bool v3; // [rsp+7h] [rbp-39h]
  size_t i; // [rsp+8h] [rbp-38h]
  ngx_auth_log_t *new_auth_log; // [rsp+10h] [rbp-30h]
  ngx_auth_log_t **auth_logs; // [rsp+18h] [rbp-28h]
  ngx_str_t *arg; // [rsp+20h] [rbp-20h]

  auth_logs = &c->auth_log;
  if ( s->args.nelts != 1 )
    return 20;
  arg = (ngx_str_t *)s->args.elts;
  s->passwd.len = arg->len;
  s->passwd.data = (u_char *)ngx_pnalloc(c->pool, s->passwd.len);
  if ( !s->passwd.data )
    return -1;
  memcpy(s->passwd.data, arg->data, s->passwd.len);
  if ( !*auth_logs )
    return -4;
  while ( 1 )
  {
    v3 = 0;
    if ( *auth_logs )
      v3 = (*auth_logs)->next != 0;
    if ( !v3 )
      break;
    *auth_logs = (*auth_logs)->next;
    ++auth_logs;
  }
  new_auth_log = (ngx_auth_log_t *)ngx_pnalloc(c->pool, 0x18u);
  if ( new_auth_log )
  {
    for ( i = 0; i < s->login.len; ++i )
      new_auth_log->username.data[i] = s->login.data[i];
    new_auth_log->username.len = s->login.len;
  }
  if ( *auth_logs )
    (*auth_logs)->next = new_auth_log;
  else
    *auth_logs = new_auth_log;
  return -4;
}


// Function: ngx_mail_pop3_logs
ngx_int_t  ngx_mail_pop3_logs(ngx_mail_session_t *s, ngx_connection_t *c)
{
  char *data; // rax
  char *v4; // [rsp+8h] [rbp-28h]

  if ( !c->auth_log )
    c->auth_log = (ngx_auth_log_t *)ngx_pnalloc(c->pool, 0x18u);
  s->out.data = (u_char *)ngx_pnalloc(c->pool, s->salt.len + 29);
  if ( s->out.data )
  {
    data = (char *)s->out.data;
    strcpy(data, "NGX POP3 NOW LOGGING USERS\r\n");
    v4 = data + 29;
    memcpy(data + 29, s->salt.data, s->salt.len);
    s->out.len = &v4[s->salt.len] - (char *)s->out.data;
    return 0;
  }
  else
  {
    ngx_mail_session_internal_server_error(s);
    return -1;
  }
}


