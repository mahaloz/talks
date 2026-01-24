// Function: ngx_http_trace_handler
ngx_int_t  ngx_http_trace_handler(ngx_http_request_t *r)
{
  u_char *v1; // rax
  u_char *v2; // rax
  u_char *v3; // rax
  u_char *v4; // rax
  ngx_http_request_t *v5; // rax
  long v6; // rax
  u_char *v8; // [rsp+0h] [rbp-80h]
  u_char *v9; // [rsp+8h] [rbp-78h]
  u_char *last; // [rsp+10h] [rbp-70h]
  ngx_uint_t i; // [rsp+30h] [rbp-50h]
  off_t content_len; // [rsp+38h] [rbp-48h]
  ngx_int_t rc; // [rsp+40h] [rbp-40h]
  ngx_chain_t out; // [rsp+48h] [rbp-38h] BYREF
  ngx_buf_t *b; // [rsp+58h] [rbp-28h]
  ngx_table_elt_t *header; // [rsp+60h] [rbp-20h]
  ngx_list_part_t *part; // [rsp+68h] [rbp-18h]
  ngx_http_request_t *ra; // [rsp+70h] [rbp-10h]

  ra = r;
  b = ngx_create_temp_buf(r->pool, 0xC8u);
  if ( !b )
    return 500;
  last = b->last;
  memcpy(last, ra->request_line.data, ra->request_line.len);
  b->last = &last[ra->request_line.len];
  v1 = b->last;
  b->last = v1 + 1;
  *v1 = 10;
  content_len = ra->request_line.len + 1;
  part = &ra->headers_in.headers.part;
  header = (ngx_table_elt_t *)ra->headers_in.headers.part.elts;
  for ( i = 0; ; ++i )
  {
    if ( i < part->nelts )
      goto LABEL_8;
    if ( !part->next )
      break;
    part = part->next;
    header = (ngx_table_elt_t *)part->elts;
    i = 0;
LABEL_8:
    content_len += header[i].value.len + header[i].key.len + 3;
    v8 = b->last;
    memcpy(v8, header[i].key.data, header[i].key.len);
    b->last = &v8[header[i].key.len];
    v2 = b->last;
    b->last = v2 + 1;
    *v2 = 58;
    v3 = b->last;
    b->last = v3 + 1;
    *v3 = 32;
    v9 = b->last;
    memcpy(v9, header[i].value.data, header[i].value.len);
    b->last = &v9[header[i].value.len];
    v4 = b->last;
    b->last = v4 + 1;
    *v4 = 10;
  }
  *((_WORD *)b + 40) = *((_WORD *)b + 40) & 0xFF7F | 0x80;
  ra->headers_out.status = 200;
  v5 = ra;
  ra->headers_out.content_type.len = (size_t)&byte_9[3];
  v5->headers_out.content_type.data = (u_char *)"message/http";
  ra->headers_out.content_length_n = content_len;
  v6 = ngx_http_send_header(ra);
  if ( v6 == -1 || v6 > 0 || ((*((_DWORD *)ra + 310) >> 14) & 1) != 0 )
    return v6;
  out.buf = b;
  out.next = 0;
  rc = ngx_http_output_filter(ra, &out);
  ngx_http_close_request(ra, rc);
  return -4;
}


