// Function: ngx_mail_smtp_noop
ngx_int_t  ngx_mail_smtp_noop(ngx_mail_session_t *s, ngx_connection_t *c)
{
  if ( s->args.nelts <= 0xA )
  {
    s->out.len = 14;
    s->out.data = (u_char *)smtp_noop;
    return 0;
  }
  else
  {
    s->out.len = 28;
    s->out.data = (u_char *)smtp_invalid_argument;
    ngx_mail_close_connection(c);
    return -1;
  }
}


