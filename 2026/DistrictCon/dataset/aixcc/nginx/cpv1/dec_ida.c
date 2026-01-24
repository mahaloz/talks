// Function: ngx_http_validate_from
ngx_int_t  ngx_http_validate_from(ngx_str_t *from, ngx_pool_t *pool, ngx_uint_t alloc)
{
  u_char *v3; // rax
  u_char *v4; // rax
  u_char *v5; // rax
  u_char *v6; // rax
  u_char *v7; // rax
  int state; // [rsp+Ch] [rbp-44h]
  size_t i; // [rsp+10h] [rbp-40h]
  u_char ch_0; // [rsp+1Fh] [rbp-31h]
  u_char *u; // [rsp+20h] [rbp-30h]
  u_char *ua; // [rsp+20h] [rbp-30h]
  u_char *f; // [rsp+28h] [rbp-28h]

  f = from->data;
  state = 0;
  if ( alloc )
  {
    u = (u_char *)ngx_palloc(pool, from->len);
    if ( !u )
      return -1;
  }
  else
  {
    u = from->data;
  }
  i = 0;
  while ( 2 )
  {
    if ( i < from->len )
    {
      ch_0 = f[i];
      switch ( state )
      {
        case 0:
          if ( ((*__ctype_b_loc())[ch_0] & 8) != 0 || ch_0 == 45 || ch_0 == 95 )
          {
            state = 1;
          }
          else
          {
            if ( ch_0 != 46 )
              return -5;
            state = 2;
          }
          v3 = u++;
          *v3 = ch_0;
          goto LABEL_46;
        case 1:
          if ( ch_0 == 64 )
          {
            state = 3;
          }
          else if ( ch_0 == 46 )
          {
            state = 2;
          }
          else if ( ((*__ctype_b_loc())[ch_0] & 8) == 0 && ch_0 != 45 && ch_0 != 95 && ch_0 != 43 )
          {
            return -5;
          }
          v5 = u++;
          *v5 = ch_0;
          goto LABEL_46;
        case 2:
          if ( ((*__ctype_b_loc())[ch_0] & 8) != 0 || ch_0 == 45 || ch_0 == 95 )
          {
            v4 = u++;
            *v4 = ch_0;
            state = 1;
          }
          else
          {
            if ( ch_0 != 46 )
              return -5;
            state = 2;
            for ( ua = u - 2; *ua != 46; --ua )
              ;
            u = ua + 1;
          }
LABEL_46:
          ++i;
          continue;
        case 3:
          if ( ch_0 == 46 )
          {
            state = 4;
          }
          else if ( ((*__ctype_b_loc())[ch_0] & 8) == 0 && ch_0 != 45 )
          {
            return -5;
          }
          v6 = u++;
          *v6 = ch_0;
          goto LABEL_46;
        case 4:
          if ( ((*__ctype_b_loc())[ch_0] & 0x400) == 0 )
            return -5;
          v7 = u++;
          *v7 = ch_0;
          goto LABEL_46;
      }
    }
    break;
  }
  if ( state != 4 )
    return -5;
  *u = 0;
  if ( alloc )
    from->data = u;
  return 0;
}


