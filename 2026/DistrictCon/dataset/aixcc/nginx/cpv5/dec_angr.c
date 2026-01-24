// Function: ngx_get_con_his
typedef struct struct_0 {
    char padding_0[16];
    struct struct_0 *field_10;
} struct_0;

struct_0 * ngx_get_con_his(struct_0 *a0, unsigned long long a1)
{
    unsigned long long i;  // [bp-0x30]
    struct_0 *cur;  // [bp-0x28]
    struct_0 *v2;  // [bp-0x10]

    cur = a0;
    if (cur && a1 != 1 && a1)
    {
        for (i = 0; i <= a1; i += 1)
        {
            cur = cur->field_10;
        }
        v2 = cur;
        return v2;
    }
    v2 = cur;
    return v2;
}


// Function: ngx_http_get_last_ip_variable
typedef struct struct_0 {
    char padding_0[8];
    unsigned long long field_8;
    void* field_10;
} struct_0;

typedef struct struct_1 {
    unsigned int field_0;
    char padding_4[4];
    unsigned long long field_8;
} struct_1;

unsigned long long ngx_http_get_last_ip_variable(struct_0 *a0, struct_1 *ptr, unsigned long long a2)
{
    unsigned long long index[2];  // [bp-0x28]
    unsigned long long v1;  // [bp-0x20]

    v1 = a2;
    index[0] = ngx_get_con_his(a0->field_10, a0->field_8);
    ptr->field_8 = index[1];
    ptr->field_0 = ptr->field_0 & 0xf0000000 | (unsigned int)index[0] & 268435455;
    return 0;
}


