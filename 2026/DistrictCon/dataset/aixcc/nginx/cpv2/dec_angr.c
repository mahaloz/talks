// Function: ngx_http_auth_basic_user
typedef struct struct_3 {
    char padding_0[112];
    unsigned long long field_70;
    char padding_78[232];
    struct struct_1 *field_160;
    char padding_168[64];
    unsigned long long field_1a8;
    struct struct_2 *field_1b0;
    unsigned long long field_1b8;
    unsigned long long field_1c0;
} struct_3;

typedef struct struct_2 {
    char padding_0[16];
    char field_10;
} struct_2;

typedef struct struct_1 {
    char padding_0[24];
    unsigned long long field_18;
    struct struct_0 *field_20;
} struct_1;

typedef struct struct_0 {
    char padding_0[6];
    char field_6;
} struct_0;

typedef struct struct_4 {
    char padding_0[16];
    char field_10;
} struct_4;

extern struct_2 g_571ac9;

unsigned long long ngx_http_auth_basic_user(struct_3 *ptr)
{
    char v0;  // [bp-0x41]
    unsigned long result;  // [bp-0x40]
    unsigned long v2;  // [bp-0x38], Other Possible Types: unsigned long long
    struct_0 *cur;  // [bp-0x30], Other Possible Types: unsigned long
    unsigned long v4;  // [bp-0x28]
    struct_4 *v5;  // [bp-0x20]
    unsigned long long v6;  // [bp-0x10]

    if (!ptr->field_1a8 && ptr->field_1b0)
    {
        v6 = -5;
        return v6;
    }
    if (!ptr->field_160)
    {
        ptr->field_1b0 = &g_571ac9.padding_0[0];
        v6 = -5;
        return v6;
    }
    v2 = ptr->field_160->field_18;
    cur = ptr->field_160->field_20;
    if (v2 >= 6 && !ngx_strncasecmp(cur, "Basic ", 6))
    {
        v2 -= 6;
        cur = &cur->field_6;
        while (true)
        {
            v0 = 0;
            if (v2)
                v0 = *((char *)cur) == 32;
            if (!(v0 & 1))
                break;
            v2 -= 1;
            cur += 1;
        }
        if (!v2)
        {
            ptr->field_1b0 = &g_571ac9.padding_0[0];
            v6 = -5;
            return v6;
        }
        v4 = 16;
        v5 = ngx_pnalloc(ptr->field_70, v4 + 1);
        if (!v5)
        {
            v6 = -1;
            return v6;
        }
        else if (ngx_decode_base64(&v4, &v2))
        {
            ptr->field_1b0 = &g_571ac9.padding_0[0];
            v6 = -5;
            return v6;
        }
        else
        {
            v5->padding_0[v4] = 0;
            for (result = 0; result < v4 && v5->padding_0[result] != 58; result += 1);
            if (result && result != v4)
            {
                ptr->field_1a8 = result;
                ptr->field_1b0 = v5;
                ptr->field_1b8 = v4 - result - 1;
                ptr->field_1c0 = &v5->padding_0[1 + result];
                v6 = 0;
                return v6;
            }
            ptr->field_1b0 = &g_571ac9.padding_0[0];
            v6 = -5;
            return v6;
        }
    }
    ptr->field_1b0 = &g_571ac9.padding_0[0];
    v6 = -5;
    return v6;
}


