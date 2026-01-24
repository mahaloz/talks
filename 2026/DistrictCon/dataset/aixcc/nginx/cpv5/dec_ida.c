// Function: ngx_get_con_his
ngx_con_his_t * ngx_get_con_his(ngx_con_his_t *con_his_list, size_t number)
{
  size_t counter; // [rsp+0h] [rbp-28h]
  ngx_con_his_t *target; // [rsp+8h] [rbp-20h]

  target = con_his_list;
  counter = 0;
  if ( !con_his_list || number <= 1 )
    return con_his_list;
  while ( counter <= number )
  {
    target = target->next;
    ++counter;
  }
  return target;
}


// Function: ngx_http_get_last_ip_variable
ngx_int_t  ngx_http_get_last_ip_variable(ngx_http_request_t *r, ngx_http_variable_value_t *v, uintptr_t data)
{
  ngx_con_his_t *con_his; // rax

  con_his = ngx_get_con_his(r->connection_history, r->request_counter);
  v->data = con_his->addr_text.data;
  *(_DWORD *)v = con_his->addr_text.len & 0xFFFFFFF | *(_DWORD *)v & 0xF0000000;
  return 0;
}


