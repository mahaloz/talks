// Function: ngx_sendfile_r
ssize_t  ngx_sendfile_r(ngx_connection_t *c, ngx_buf_t *file, size_t size)
{
  int j; // [rsp+0h] [rbp-D0h]
  int i; // [rsp+4h] [rbp-CCh]
  ssize_t n; // [rsp+8h] [rbp-C8h]
  u_char *rev; // [rsp+10h] [rbp-C0h]
  u_char *buf; // [rsp+18h] [rbp-B8h]
  stat sb; // [rsp+20h] [rbp-B0h] BYREF
  size_t sizea; // [rsp+B0h] [rbp-20h]
  ngx_buf_t *filea; // [rsp+B8h] [rbp-18h]
  ngx_connection_t *ca; // [rsp+C0h] [rbp-10h]

  ca = c;
  filea = file;
  sizea = size;
  if ( (unsigned int)fstat64(file->file->fd, (struct stat64 *)&sb) )
    return -1;
  buf = (u_char *)ngx_palloc(ca->pool, sb.st_size);
  if ( !buf )
    return -1;
  if ( read(filea->file->fd, buf, sb.st_size) == -1 )
    return -1;
  lseek64(filea->file->fd, 0, 0);
  rev = (u_char *)ngx_alloc(0x64u, ca->log);
  if ( !rev )
    return -1;
  i = sizea + LODWORD(filea->file_pos) - 1;
  j = 0;
  while ( i >= filea->file_pos )
    rev[j++] = buf[i--];
  n = ca->send(ca, rev, sizea);
  ngx_pfree(ca->pool, buf);
  free(rev);
  return n;
}


