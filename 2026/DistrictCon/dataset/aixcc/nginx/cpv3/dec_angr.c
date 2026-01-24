// Function: ngx_http_trace_handler
typedef struct struct_0 {
    char padding_0[112];
    unsigned long long field_70;
    char padding_78[16];
    unsigned long long field_88;
    unsigned long long field_90;
    struct struct_0 *field_98;
    char padding_a0[480];
    unsigned long long field_280;
    char padding_288[144];
    unsigned long long field_318;
    unsigned long long field_320;
    char padding_328[32];
    unsigned long long field_348;
    char padding_350[72];
    char field_398;
    char padding_399[7];
    void* field_3a0;
    char padding_3a8[304];
    unsigned int field_4d8;
} struct_0;

typedef struct struct_1 {
    char padding_0[8];
    struct struct_2 *field_8;
    char padding_10[64];
    unsigned short field_50;
} struct_1;

typedef struct struct_2 {
    char field_0;
} struct_2;

extern unsigned long long g_59ed48;
extern unsigned long long g_59ed50;

unsigned long long ngx_http_trace_handler(struct_0 *p)
{
    char *ptr6;  // rax
    char *v17;  // rdx
    unsigned long long v18;  // rsi
    char *ptr4;  // rax
    char *ptr5;  // rax
    char *addr;  // rax
    unsigned long long v22;  // r8
    unsigned long long v23;  // r9
    unsigned long long v24;  // rdx
    unsigned long long v25;  // rcx
    char *v0;  // [bp-0x88]
    char *v1;  // [bp-0x80]
    char *v2;  // [bp-0x78]
    unsigned long v3;  // [bp-0x70]
    unsigned long v4;  // [bp-0x68]
    unsigned long v5;  // [bp-0x60]
    unsigned long long v6;  // [bp-0x58]
    unsigned long v7;  // [bp-0x50]
    unsigned long long count;  // [bp-0x48]
    struct_1 *v9;  // [bp-0x40]
    unsigned long long result;  // [bp-0x38]
    struct_1 *ptr;  // [bp-0x30]
    unsigned long v12;  // [bp-0x28]
    struct_0 *cur;  // [bp-0x20]
    unsigned long long v14;  // [bp-0x10]

    ptr = ngx_create_temp_buf(p->field_70, 200);
    if (!ptr)
    {
        v14 = 500;
        return v14;
    }
    v2 = &ptr->field_8->field_0;
    memcpy(ptr->field_8, p->field_3a0, *((long long *)&p->field_398));
    ptr->field_8 = &v2[*((long long *)&p->field_398)];
    ptr6 = ptr->field_8;
    v17 = ptr6 + 1;
    ptr->field_8 = v17;
    *(ptr6) = 10;
    v7 = *((long long *)&p->field_398) + 1;
    cur = &p->field_88;
    v12 = *((long long *)&cur->padding_0[0]);
    v6 = 0;
    while (true)
    {
        if (v6 >= *((long long *)&cur->padding_0[8]))
        {
            if (!*((long long *)&cur->padding_0[16]))
                break;
            cur = *((long long *)&cur->padding_0[16]);
            v12 = *((long long *)&cur->padding_0[0]);
            v6 = 0;
        }
        v5 = *((long long *)(v12 + v6 * 56 + 8)) + *((long long *)(v12 + v6 * 56 + 24)) + 3;
        v7 += v5;
        v0 = &ptr->field_8->field_0;
        memcpy(ptr->field_8, *((long long *)(v12 + v6 * 56 + 16)), *((long long *)(v12 + v6 * 56 + 8)));
        ptr->field_8 = &v0[*((long long *)(v12 + v6 * 56 + 8))];
        ptr4 = ptr->field_8;
        ptr->field_8 = ptr4 + 1;
        *(ptr4) = 58;
        ptr5 = ptr->field_8;
        ptr->field_8 = ptr5 + 1;
        *(ptr5) = 32;
        v1 = &ptr->field_8->field_0;
        memcpy(ptr->field_8, *((long long *)(v12 + v6 * 56 + 32)), *((long long *)(v12 + v6 * 56 + 24)));
        ptr->field_8 = &v1[*((long long *)(v12 + v6 * 56 + 24))];
        addr = ptr->field_8;
        v17 = addr + 1;
        ptr->field_8 = v17;
        *(addr) = 10;
        v6 += 1;
    }
    ptr->field_50 = ptr->field_50 & 65407 | 128;
    v3 = g_59ed48;
    v4 = g_59ed50;
    p->field_280 = 200;
    p->field_318 = v3;
    p->field_320 = v4;
    p->field_348 = v7;
    count = ngx_http_send_header(p, v18, v17, v7, v22, v23);
    if (count != -1 && count <= 0 && !((char)(p->field_4d8 >> 14) & 1))
    {
        v9 = ptr;
        result = 0;
        count = ngx_http_output_filter(p, &v9);
        ngx_http_close_request(p, count, v24, v25, v22, v23);
        v14 = -4;
        return v14;
    }
    v14 = count;
    return v14;
}


