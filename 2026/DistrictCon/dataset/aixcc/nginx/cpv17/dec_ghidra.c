// Function: ngx_mail_smtp_noop

undefined8 ngx_mail_smtp_noop(long param_1,undefined8 param_2)

{
  undefined8 local_10;
  
  if (*(ulong *)(param_1 + 0x128) < 0xb) {
    *(undefined8 *)(param_1 + 0x10) = 0xe;
    *(undefined1 **)(param_1 + 0x18) = smtp_noop;
    local_10 = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0x10) = 0x1c;
    *(char **)(param_1 + 0x18) = smtp_invalid_argument;
    ngx_mail_close_connection(param_2);
    local_10 = 0xffffffffffffffff;
  }
  return local_10;
}



