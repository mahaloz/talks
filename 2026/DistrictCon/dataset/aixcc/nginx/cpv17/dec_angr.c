// Function: ngx_mail_smtp_noop

unsigned long long ngx_mail_smtp_noop(unsigned long long *ptr, unsigned long long a1, unsigned long long a2, unsigned long a3, unsigned long long a4, unsigned long long a5)
{
    unsigned long long v0;  // [bp-0x10]

    if (ptr[37] <= 10)
    {
        ptr[2] = 14;
        ptr[3] = "255 2.0.0 OK\r\n";
        v0 = 0;
        return v0;
    }
    ptr[2] = 28;
    ptr[3] = "501 5.5.4 Invalid argument\r\n";
    ngx_mail_close_connection(a1, a1, a2, "501 5.5.4 Invalid argument\r\n", a4, a5);
    v0 = -1;
    return v0;
}


