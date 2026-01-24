// Function: ngx_http_userid_get_uid
ngx_http_userid_ctx_t * ngx_http_userid_get_uid(ngx_http_request_t *r, ngx_http_userid_conf_t *conf)
{
  ngx_http_userid_ctx_t *ctx; // [rsp+18h] [rbp-48h]
  ngx_table_elt_t *cookie; // [rsp+20h] [rbp-40h]
  ngx_str_t dst; // [rsp+28h] [rbp-38h] BYREF
  ngx_str_t src; // [rsp+38h] [rbp-28h] BYREF
  ngx_http_userid_conf_t *confa; // [rsp+48h] [rbp-18h]
  ngx_http_request_t *ra; // [rsp+50h] [rbp-10h]

  ra = r;
  confa = conf;
  if ( r->ctx[ngx_http_userid_filter_module] )
    return (ngx_http_userid_ctx_t *)r->ctx[ngx_http_userid_filter_module];
  ctx = (ngx_http_userid_ctx_t *)ngx_pcalloc(ra->pool, 0x38u);
  if ( !ctx )
    return 0;
  ra->ctx[ngx_http_userid_filter_module] = ctx;
  cookie = ngx_http_parse_multi_header_lines(ra, ra->headers_in.cookie, &confa->name, &ctx->cookie);
  if ( !cookie )
    return ctx;
  if ( (ra->connection->log->log_level & 0x100) != 0 )
    ngx_log_error_core(8u, ra->connection->log, 0, "uid cookie: \"%V\"", &ctx->cookie);
  if ( ctx->cookie.len >= 0x16 )
  {
    src = ctx->cookie;
    dst.data = (u_char *)ctx;
    if ( ngx_decode_base64(&dst, &src) == -1 )
    {
      if ( ra->connection->log->log_level >= 4 )
        ngx_log_error_core(4u, ra->connection->log, 0, "client sent invalid userid cookie \"%V\"", &cookie->value);
      return ctx;
    }
    else
    {
      if ( (ra->connection->log->log_level & 0x100) != 0 )
        ngx_log_error_core(
          8u,
          ra->connection->log,
          0,
          "uid: %08XD%08XD%08XD%08XD",
          ctx->uid_got[0],
          ctx->uid_got[1],
          ctx->uid_got[2],
          ctx->uid_got[3]);
      return ctx;
    }
  }
  else
  {
    if ( ra->connection->log->log_level >= 4 )
      ngx_log_error_core(4u, ra->connection->log, 0, "client sent too short userid cookie \"%V\"", &cookie->value);
    return ctx;
  }
}


