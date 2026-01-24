// Function: ngx_black_list_insert
void  ngx_black_list_insert(ngx_black_list_t **black_list, u_char *insert_ip, size_t size, ngx_log_t *log)
{
  bool v4; // [rsp+Fh] [rbp-41h]
  size_t i; // [rsp+10h] [rbp-40h]
  u_char *new_str; // [rsp+18h] [rbp-38h]
  ngx_black_list_t *new_black_list; // [rsp+20h] [rbp-30h]
  ngx_black_list_t *reader; // [rsp+28h] [rbp-28h]

  new_str = (u_char *)ngx_alloc(size, log);
  for ( i = 0; i < size; ++i )
    new_str[i] = insert_ip[i];
  new_black_list = (ngx_black_list_t *)ngx_alloc(0x18u, log);
  new_black_list->IP = (ngx_str_t *)ngx_alloc(0x10u, log);
  new_black_list->IP->data = new_str;
  new_black_list->IP->len = size;
  new_black_list->next = 0;
  reader = *black_list;
  if ( *black_list )
  {
    while ( 1 )
    {
      v4 = 0;
      if ( reader )
        v4 = reader->next != 0;
      if ( !v4 )
        break;
      if ( !strcmp((const char *)insert_ip, (const char *)reader->IP->data) )
      {
        memset(new_black_list->IP->data, 0, new_black_list->IP->len);
        free(new_black_list->IP->data);
        new_black_list->IP->data = 0;
        memset(new_black_list->IP, 0, sizeof(ngx_str_t));
        free(new_black_list->IP);
        new_black_list->IP = 0;
        memset(new_black_list, 0, sizeof(ngx_black_list_t));
        free(new_black_list);
        return;
      }
      reader = reader->next;
    }
    reader->next = new_black_list;
    new_black_list->prev = reader;
  }
  else
  {
    *black_list = new_black_list;
  }
}


// Function: ngx_black_list_remove
ngx_int_t  ngx_black_list_remove(ngx_black_list_t **black_list, u_char *remove_ip)
{
  bool v3; // [rsp+Fh] [rbp-21h]
  ngx_black_list_t *reader; // [rsp+10h] [rbp-20h]

  reader = *black_list;
  if ( !*black_list || strcmp((const char *)remove_ip, (const char *)reader->IP->data) )
  {
    for ( reader = reader->next; ; reader = reader->next )
    {
      v3 = 0;
      if ( reader )
        v3 = reader->next != 0;
      if ( !v3 )
        return -1;
      if ( !strcmp((const char *)remove_ip, (const char *)reader->IP->data) )
        break;
    }
    if ( reader->prev )
      reader->prev->next = reader->next;
    if ( reader->next )
      reader->next->prev = reader->prev;
  }
  memset(reader->IP->data, 0, reader->IP->len);
  free(reader->IP->data);
  reader->IP->data = 0;
  memset(reader->IP, 0, sizeof(ngx_str_t));
  free(reader->IP);
  reader->IP = 0;
  memset(reader, 0, sizeof(ngx_black_list_t));
  free(reader);
  return 0;
}


// Function: ngx_is_ip_banned
ngx_int_t  ngx_is_ip_banned(ngx_cycle_t *cycle, ngx_connection_t *connection)
{
  ngx_black_list_t *black_list; // [rsp+8h] [rbp-28h]
  ngx_black_list_t *reader; // [rsp+10h] [rbp-20h]

  if ( cycle )
    black_list = cycle->black_list;
  else
    black_list = 0;
  for ( reader = black_list; reader; reader = reader->next )
  {
    if ( !strcmp((const char *)connection->addr_text.data, (const char *)reader->IP->data) )
    {
      ngx_close_connection(connection);
      return -1;
    }
  }
  return 0;
}


