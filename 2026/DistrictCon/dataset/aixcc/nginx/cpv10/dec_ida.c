// Function: ngx_http_process_prefer
ngx_int_t  ngx_http_process_prefer(ngx_http_request_t *r, ngx_table_elt_t *h, ngx_uint_t offset)
{
  ngx_table_elt_t *p; // [rsp+18h] [rbp-28h]

  if ( r->headers_in.prefer )
  {
    if ( r->connection->log->log_level >= 7 )
      ngx_log_error_core(
        7u,
        r->connection->log,
        0,
        "client sent duplicate host header: \"%V: %V\", previous value: \"%V: %V\"",
        &h->key,
        &h->value,
        &r->headers_in.prefer->key,
        &r->headers_in.prefer->value);
    free(r->headers_in.prefer);
    return 0;
  }
  else
  {
    p = (ngx_table_elt_t *)ngx_alloc(0x38u, r->connection->log);
    if ( p )
    {
      p->hash = h->hash;
      p->key = h->key;
      p->value = h->value;
      r->headers_in.prefer = p;
      return 0;
    }
    else
    {
      ngx_http_finalize_request(r, 400);
      return -1;
    }
  }
}


