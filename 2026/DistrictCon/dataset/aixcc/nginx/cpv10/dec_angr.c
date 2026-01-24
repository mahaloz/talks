// Function: ngx_http_process_prefer
typedef struct struct_2 {
    char padding_0[32];
    struct struct_0 *field_20;
    char padding_28[200];
    struct struct_3 *field_f0;
} struct_2;

typedef struct struct_0 {
    char padding_0[96];
    struct struct_1 *field_60;
} struct_0;

typedef struct struct_3 {
    unsigned long long field_0;
    unsigned long long field_8;
    unsigned long long field_10;
    unsigned long long field_18;
    unsigned long long field_20;
} struct_3;

typedef struct struct_1 {
    unsigned long long field_0;
} struct_1;

unsigned long long ngx_http_process_prefer(struct_2 *p, unsigned long long *index, unsigned long long a2)
{
    unsigned long long v6;  // rcx
    unsigned long long v7;  // r8
    unsigned long long v8;  // r9
    unsigned long v0;  // [bp-0x48]
    unsigned long v1;  // [bp-0x40]
    unsigned long long ptr[5];  // [bp-0x30]
    unsigned long long v3;  // [bp-0x28]
    unsigned long long v4;  // [bp-0x10]

    v3 = a2;
    if (p->field_f0)
    {
        if (p->field_20->field_60->field_0 >= 7)
        {
            v0 = &p->field_f0->field_8;
            v1 = &p->field_f0->field_18;
            ngx_log_error_core(7, p->field_20->field_60, 0, "client sent duplicate host header: \"%V: %V\", previous value: \"%V: %V\"", index + 1, index + 3);
        }
        free(p->field_f0);
        v4 = 0;
        return v4;
    }
    else
    {
        ptr[0] = ngx_alloc(56, p->field_20->field_60);
        if (ptr)
        {
            ptr[0] = *(index);
            ptr[1] = index[1];
            ptr[2] = index[2];
            ptr[3] = index[3];
            ptr[4] = index[4];
            p->field_f0 = ptr;
            v4 = 0;
            return v4;
        }
        ngx_http_finalize_request(p, 400, a2, v6, v7, v8);
        v4 = -1;
        return v4;
    }
}


