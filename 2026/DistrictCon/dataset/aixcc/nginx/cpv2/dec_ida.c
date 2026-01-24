// Function: ngx_http_auth_basic_user
ngx_int_t  ngx_http_auth_basic_user(ngx_http_request_t *r)
{
  bool v2; // [rsp+7h] [rbp-39h]
  ngx_uint_t len; // [rsp+8h] [rbp-38h]
  ngx_str_t encoded; // [rsp+10h] [rbp-30h] BYREF
  ngx_str_t auth; // [rsp+20h] [rbp-20h] BYREF
  ngx_http_request_t *ra; // [rsp+30h] [rbp-10h]

  ra = r;
  if ( !r->headers_in.user.len && ra->headers_in.user.data )
    return -5;
  if ( ra->headers_in.authorization )
  {
    encoded = ra->headers_in.authorization->value;
    if ( encoded.len < 6 || ngx_strncasecmp(encoded.data, (u_char *)"Basic ", 6u) )
    {
      ra->headers_in.user.data = (u_char *)"";
      return -5;
    }
    else
    {
      encoded.len -= 6LL;
      for ( encoded.data += 6; ; ++encoded.data )
      {
        v2 = 0;
        if ( encoded.len )
          v2 = *encoded.data == 32;
        if ( !v2 )
          break;
        --encoded.len;
      }
      if ( encoded.len )
      {
        auth.len = 16;
        auth.data = (u_char *)ngx_pnalloc(ra->pool, 0x11u);
        if ( auth.data )
        {
          if ( ngx_decode_base64(&auth, &encoded) )
          {
            ra->headers_in.user.data = (u_char *)"";
            return -5;
          }
          else
          {
            auth.data[auth.len] = 0;
            for ( len = 0; len < auth.len && auth.data[len] != 58; ++len )
              ;
            if ( len && len != auth.len )
            {
              ra->headers_in.user.len = len;
              ra->headers_in.user.data = auth.data;
              ra->headers_in.passwd.len = auth.len - len - 1;
              ra->headers_in.passwd.data = &auth.data[len + 1];
              return 0;
            }
            else
            {
              ra->headers_in.user.data = (u_char *)"";
              return -5;
            }
          }
        }
        else
        {
          return -1;
        }
      }
      else
      {
        ra->headers_in.user.data = (u_char *)"";
        return -5;
      }
    }
  }
  else
  {
    ra->headers_in.user.data = (u_char *)"";
    return -5;
  }
}


