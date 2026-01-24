// Function: ngx_http_set_browser_cookie
ngx_int_t  ngx_http_set_browser_cookie(ngx_http_request_t *r)
{
  ngx_table_elt_t *browser_cookie; // [rsp+8h] [rbp-18h]

  if ( ((*((_WORD *)&r->headers_in + 196) >> 10) & 1) == 0
    && ((*((_WORD *)&r->headers_in + 196) >> 5) & 1) == 0
    && ((*((_WORD *)&r->headers_in + 196) >> 9) & 1) == 0 )
  {
    return 0;
  }
  browser_cookie = (ngx_table_elt_t *)ngx_list_push(&r->headers_out.headers);
  if ( !browser_cookie )
    return -1;
  browser_cookie->hash = 1;
  browser_cookie->next = 0;
  browser_cookie->key.len = 14;
  browser_cookie->key.data = (u_char *)"Browser-Cookie";
  browser_cookie->value.data = (u_char *)ngx_pnalloc(r->pool, 0x2Bu);
  if ( browser_cookie->value.data )
  {
    if ( ((*((_WORD *)&r->headers_in + 196) >> 10) & 1) != 0 && r->headers_in.cookie )
      browser_cookie->value.len = ngx_sprintf(
                                    browser_cookie->value.data,
                                    "\"%xT-%xO\":%s",
                                    r->headers_out.last_modified_time,
                                    r->headers_out.content_length_n,
                                    (const char *)r->headers_in.cookie->value.data)
                                - browser_cookie->value.data;
    else
      browser_cookie->value.len = ngx_sprintf(
                                    browser_cookie->value.data,
                                    "\"%xT-%xO\"",
                                    r->headers_out.last_modified_time,
                                    r->headers_out.content_length_n)
                                - browser_cookie->value.data;
    return 0;
  }
  else
  {
    browser_cookie->hash = 0;
    return -1;
  }
}


