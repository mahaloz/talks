// Function: ngx_http_script_regex_end_code
void  ngx_http_script_regex_end_code(ngx_http_script_engine_t *e)
{
  char v1; // al
  u_char v2; // cl
  u_char *pos; // rax
  u_char *v4; // rax
  u_char *v5; // [rsp+0h] [rbp-40h]
  u_char *v6; // [rsp+8h] [rbp-38h]
  u_char *v7; // [rsp+10h] [rbp-30h]
  u_char *code; // [rsp+18h] [rbp-28h]
  ngx_http_request_t *r; // [rsp+20h] [rbp-20h]
  u_char *src; // [rsp+28h] [rbp-18h] BYREF
  u_char *dst; // [rsp+30h] [rbp-10h] BYREF
  ngx_http_script_engine_t *ea; // [rsp+38h] [rbp-8h]

  ea = e;
  code = e->ip;
  r = e->request;
  *((_BYTE *)e + 64) &= ~4u;
  if ( (r->connection->log->log_level & 0x100) != 0 )
    ngx_log_error_core(8u, r->connection->log, 0, "http script regex end");
  if ( (code[8] & 8) != 0 )
  {
    dst = ea->buf.data;
    src = ea->buf.data;
    ngx_unescape_uri(&dst, &src, ea->pos - ea->buf.data, 2u);
    if ( src < ea->pos )
    {
      v7 = dst;
      memmove(dst, src, ea->pos - src);
      dst = &v7[ea->pos - src];
    }
    ea->pos = dst;
    if ( (code[8] & 4) != 0 && r->args.len )
    {
      v1 = 63;
      if ( (code[8] & 2) != 0 )
        v1 = 38;
      v2 = v1;
      pos = ea->pos;
      ea->pos = pos + 1;
      *pos = v2;
      v6 = ea->pos;
      memcpy(v6, r->args.data, r->args.len);
      ea->pos = &v6[r->args.len];
    }
    ea->buf.len = ea->pos - ea->buf.data;
    if ( ((*((_BYTE *)ea + 64) & 0x10) != 0 || (r->connection->log->log_level & 0x100) != 0)
      && r->connection->log->log_level >= 6 )
    {
      ngx_log_error_core(6u, r->connection->log, 0, "rewritten redirect: \"%V\"", &ea->buf);
    }
    if ( r->headers_out.location )
    {
      r->headers_out.location->hash = 0;
      r->headers_out.location = 0;
    }
    r->headers_out.location = (ngx_table_elt_t *)ngx_list_push(&r->headers_out.headers);
    if ( r->headers_out.location )
    {
      r->headers_out.location->hash = 1;
      r->headers_out.location->next = 0;
      r->headers_out.location->key.len = 8;
      r->headers_out.location->key.data = (u_char *)"Location";
      r->headers_out.location->value = ea->buf;
      ea->ip += 16;
    }
    else
    {
      ea->ip = (u_char *)&ngx_http_script_exit_code;
      ea->status = 500;
    }
    return;
  }
  if ( ea->args )
  {
    ea->buf.len = ea->args - ea->buf.data;
    if ( (code[8] & 4) != 0 && r->args.len )
    {
      v4 = ea->pos;
      ea->pos = v4 + 1;
      *v4 = 38;
      v5 = ea->pos;
      memcpy(v5, r->args.data, r->args.len);
      ea->pos = &v5[r->args.len];
    }
    r->args.len = ea->pos - ea->args;
    r->args.data = ea->args;
    ea->args = 0;
  }
  else
  {
    ea->buf.len = ea->pos - ea->buf.data;
    if ( ea->buf.len > 0x7D0 )
    {
      if ( r->connection->log->log_level >= 4 )
        ngx_log_error_core(4u, r->connection->log, 0, "the rewritten URI is too long");
      ea->ip = (u_char *)&ngx_http_script_exit_code;
      ea->status = 500;
    }
    if ( (code[8] & 4) == 0 )
      r->args.len = 0;
  }
  if ( ((*((_BYTE *)ea + 64) & 0x10) != 0 || (r->connection->log->log_level & 0x100) != 0)
    && r->connection->log->log_level >= 6 )
  {
    ngx_log_error_core(6u, r->connection->log, 0, "rewritten data: \"%V\", args: \"%V\"", &ea->buf, &r->args);
  }
  if ( (code[8] & 1) == 0 )
  {
LABEL_41:
    ea->ip += 16;
    return;
  }
  r->uri = ea->buf;
  if ( r->uri.len )
  {
    ngx_http_set_exten(r);
    goto LABEL_41;
  }
  if ( r->connection->log->log_level >= 4 )
    ngx_log_error_core(4u, r->connection->log, 0, "the rewritten URI has a zero length");
  ea->ip = (u_char *)&ngx_http_script_exit_code;
  ea->status = 500;
}


