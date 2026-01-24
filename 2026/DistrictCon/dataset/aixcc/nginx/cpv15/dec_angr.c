// Function: ngx_http_userid_get_uid
typedef struct struct_2 {
    char padding_0[32];
    struct struct_0 *field_20;
    unsigned long long field_28;
    char padding_30[64];
    unsigned long long field_70;
    char padding_78[296];
    unsigned long long field_1a0;
} struct_2;

typedef struct struct_0 {
    char padding_0[96];
    struct struct_1 *field_60;
} struct_0;

typedef struct struct_1 {
    unsigned long long field_0;
} struct_1;

extern unsigned long long idx;

void* ngx_http_userid_get_uid(struct_2 *index, unsigned long long a1)
{
    unsigned long long v10;  // r9
    void* ptr;  // rax
    unsigned int v0;  // [bp-0x68]
    unsigned int v1;  // [bp-0x60]
    void* p;  // [bp-0x50]
    unsigned long long v3;  // [bp-0x48]
    unsigned int v4[2];  // [bp-0x40]
    void* v5;  // [bp-0x38]
    unsigned long v6;  // [bp-0x30]
    unsigned long v7;  // [bp-0x28]
    void* v8;  // [bp-0x10]

    p = *((long long *)(index->field_28 + idx * 8));
    if (p)
    {
        v8 = p;
        return v8;
    }
    if (!p)
    {
        p = ngx_pcalloc(index->field_70, 56);
        if (!p)
        {
            v8 = NULL;
            return v8;
        }
        *((void* *)(index->field_28 + idx * 8)) = p;
    }
    v3 = ngx_http_parse_multi_header_lines(index, index->field_1a0, a1 + 24);
    if (!v3)
    {
        v8 = p;
        return v8;
    }
    if (((unsigned short)index->field_20->field_60->field_0 & 0x100))
        ngx_log_error_core(8, index->field_20->field_60, 0, "uid cookie: \"%V\"", p + 32, v10);
    if ((long long)p[32] < 22)
    {
        if (index->field_20->field_60->field_0 >= 4)
            ngx_log_error_core(4, index->field_20->field_60, 0, "client sent too short userid cookie \"%V\"", v3 + 24, v10);
        v8 = p;
        return v8;
    }
    else
    {
        ptr = p;
        v6 = (long long)ptr[32];
        v7 = (long long)ptr[40];
        v5 = p;
        if (ngx_decode_base64(&v4, &v6) == -1)
        {
            if (index->field_20->field_60->field_0 >= 4)
                ngx_log_error_core(4, index->field_20->field_60, 0, "client sent invalid userid cookie \"%V\"", v3 + 24, v10);
            v8 = p;
            return v8;
        }
        else
        {
            if (((unsigned short)index->field_20->field_60->field_0 & 0x100))
            {
                v0 = (int)p[8];
                v1 = (int)p[12];
                ngx_log_error_core(8, index->field_20->field_60, 0, "uid: %08XD%08XD%08XD%08XD", *((int *)p), (int)p[4]);
            }
            v8 = p;
            return v8;
        }
    }
}


