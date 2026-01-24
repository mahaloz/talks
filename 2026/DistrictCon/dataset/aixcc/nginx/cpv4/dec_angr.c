// Function: ngx_http_set_browser_cookie
typedef struct struct_1 {
    char padding_0[112];
    unsigned long long field_70;
    char padding_78[296];
    struct struct_0 *field_1a0;
    char padding_1a8[96];
    unsigned short field_208;
    char padding_20a[318];
    unsigned long long field_348;
    char padding_350[16];
    unsigned long long field_360;
} struct_1;

typedef struct struct_0 {
    char padding_0[32];
    unsigned long long field_20;
} struct_0;

unsigned long long ngx_http_set_browser_cookie(struct_1 *a0)
{
    unsigned long long v3;  // r9
    unsigned long long v4;  // rax
    unsigned long long v5;  // r8
    unsigned long long v6;  // r9
    unsigned long long v7;  // rax
    unsigned long long ptr[7];  // [bp-0x20]
    unsigned long long v1;  // [bp-0x10]

    if (!((char)(a0->field_208 >> 10) & 1) && !((char)(a0->field_208 >> 5) & 1) && !((char)(a0->field_208 >> 9) & 1))
    {
        v1 = 0;
        return v1;
    }
    ptr[0] = ngx_list_push(&a0->padding_20a[6]);
    if (!ptr)
    {
        v1 = -1;
        return v1;
    }
    ptr[0] = 1;
    ptr[6] = 0;
    ptr[1] = 14;
    ptr[2] = "Browser-Cookie";
    ptr[4] = ngx_pnalloc(a0->field_70, 43);
    if (!ptr[4])
    {
        ptr[0] = 0;
        v1 = -1;
        return v1;
    }
    if (((char)(a0->field_208 >> 10) & 1) && a0->field_1a0)
    {
        v4 = ngx_sprintf(ptr[4], "\"%xT-%xO\":%s", a0->field_360, a0->field_348, a0->field_1a0->field_20, v3);
        ptr[3] = v4 - ptr[4];
    }
    else
    {
        v7 = ngx_sprintf(ptr[4], "\"%xT-%xO\"", a0->field_360, a0->field_348, v5, v6);
        ptr[3] = v7 - ptr[4];
    }
    v1 = 0;
    return v1;
}


