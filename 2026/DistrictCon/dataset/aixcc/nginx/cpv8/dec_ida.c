// Function: ngx_mail_pop3_user
ngx_int_t  ngx_mail_pop3_user(ngx_mail_session_t *s, ngx_connection_t *c)
{
  ngx_str_t *arg; // [rsp+0h] [rbp-20h]

  if ( s->args.nelts != 1 )
    return 20;
  arg = (ngx_str_t *)s->args.elts;
  s->login.len = arg->len;
  s->login.data = (u_char *)ngx_pnalloc(c->pool, 0x64u);
  if ( !s->login.data )
    return -1;
  memcpy(s->login.data, arg->data, s->login.len);
  if ( (c->log->log_level & 0x200) != 0 )
    ngx_log_error_core(8u, c->log, 0, "pop3 login: \"%V\"", &s->login);
  s->mail_state = 1;
  return 0;
}


