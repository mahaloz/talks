// Function: ngx_http_script_regex_end_code
typedef struct struct_7 {
    struct struct_0 *field_0;
    struct struct_8 *field_8;
    char padding_10[8];
    unsigned long long field_18;
    struct struct_9 *field_20;
    char padding_28[16];
    unsigned long long field_38;
    char field_40;
    char padding_41[7];
    unsigned long long field_48;
    struct struct_5 *field_50;
} struct_7;

typedef struct struct_12 {
    char padding_0[8];
    char field_8;
} struct_12;

typedef struct struct_17 {
    char padding_0[32];
    struct struct_13 *field_20;
    char padding_28[488];
    char field_210;
    char padding_211[167];
    struct struct_15 *field_2b8;
    char padding_2c0[232];
    unsigned long long field_3a8;
    struct struct_16 *field_3b0;
    unsigned long long field_3b8;
    unsigned long long field_3c0;
} struct_17;

typedef struct struct_15 {
    unsigned long long field_0;
    unsigned long long field_8;
    char padding_10[8];
    unsigned long long field_18;
    struct struct_16 *field_20;
    char padding_28[8];
    unsigned long long field_30;
} struct_15;

typedef struct struct_0 {
    char padding_0[8];
    char field_8;
} struct_0;

typedef struct struct_8 {
    char field_0;
} struct_8;

typedef struct struct_9 {
    char field_0;
} struct_9;

typedef struct struct_5 {
    char padding_0[32];
    struct struct_1 *field_20;
    char padding_28[488];
    char field_210;
    char padding_211[167];
    struct struct_3 *field_2b8;
    char padding_2c0[232];
    unsigned long long field_3a8;
    struct struct_6 *field_3b0;
    char field_3b8;
    char padding_3b9[7];
    void* field_3c0;
} struct_5;

typedef struct struct_13 {
    char padding_0[96];
    struct struct_14 *field_60;
} struct_13;

typedef struct struct_16 {
    char field_0;
} struct_16;

typedef struct struct_1 {
    char padding_0[96];
    struct struct_2 *field_60;
} struct_1;

typedef struct struct_3 {
    unsigned long long field_0;
    unsigned long long field_8;
    char padding_10[8];
    unsigned long long field_18;
    struct struct_4 *field_20;
    char padding_28[8];
    unsigned long long field_30;
} struct_3;

typedef struct struct_6 {
    char field_0;
} struct_6;

typedef struct struct_14 {
    unsigned long long field_0;
} struct_14;

typedef struct struct_2 {
    unsigned long long field_0;
} struct_2;

typedef struct struct_4 {
    char field_0;
} struct_4;

extern struct_12 ngx_http_script_exit_code;

struct_7 * ngx_http_script_regex_end_code(struct_7 *ptr, unsigned long a1, unsigned long a2, unsigned long a3, unsigned long long a4, unsigned long long a5)
{
    char v8;  // al
    char *ptr4;  // rax
    struct_15 *addr;  // rax
    struct_7 *idx4;  // rcx
    char *ptr3;  // rax
    struct_7 *pos;  // rcx
    char *v0;  // [bp-0x48]
    char *v1;  // [bp-0x40]
    char *v2;  // [bp-0x38]
    struct_12 *v3;  // [bp-0x30]
    struct_17 *p;  // [bp-0x28]
    char *v5;  // [bp-0x20]
    char *v6;  // [bp-0x18]

    v3 = ptr->field_0;
    p = ptr->field_50;
    ptr->field_40 = ptr->field_40 & 251;
    if (((unsigned short)p->field_20->field_60->field_0 & 0x100))
        ngx_log_error_core(8, p->field_20->field_60, 0, "http script regex end", a4, a5);
    if ((v3->field_8 >> 3 & 1))
    {
        v6 = &ptr->field_20->field_0;
        v5 = &ptr->field_20->field_0;
        ngx_unescape_uri(&v6, &v5, ptr->field_8 - ptr->field_20);
        if (v5 < ptr->field_8)
        {
            v2 = v6;
            memmove(v6, v5, ptr->field_8 - v5);
            v6 = v2 + ptr->field_8 - v5;
        }
        ptr->field_8 = v6;
        if ((v3->field_8 >> 2 & 1) && p->field_3b8)
        {
            v8 = ((v3->field_8 >> 1 & 1) ? 38 : 63);
            ptr4 = ptr->field_8;
            ptr->field_8 = ptr4 + 1;
            *(ptr4) = v8;
            v1 = &ptr->field_8->field_0;
            memcpy(ptr->field_8, p->field_3c0, p->field_3b8);
            ptr->field_8 = &v1[p->field_3b8];
        }
        ptr->field_18 = ptr->field_8 - ptr->field_20;
        if (((ptr->field_40 >> 4 & 1) || ((unsigned short)p->field_20->field_60->field_0 & 0x100)) && p->field_20->field_60->field_0 >= 6)
            ngx_log_error_core(6, p->field_20->field_60, 0, "rewritten redirect: \"%V\"", &ptr->field_18, a5);
        if (p->field_2b8)
        {
            p->field_2b8->field_0 = 0;
            p->field_2b8 = NULL;
        }
        p->field_2b8 = ngx_list_push(&p->field_210);
        if (p->field_2b8)
        {
            p->field_2b8->field_0 = 1;
            p->field_2b8->field_30 = 0;
            p->field_2b8->field_8 = 8;
            *((char **)&p->field_2b8->padding_10[0]) = "Location";
            addr = p->field_2b8;
            idx4 = ptr;
            addr->field_18 = idx4->field_18;
            addr->field_20 = idx4->field_20;
            ptr->field_0 = &ptr->field_0[1].padding_0[7];
            return ptr;
        }
        ptr->field_0 = &ngx_http_script_exit_code.padding_0[0];
        ptr->field_48 = 500;
        return ptr;
    }
    else
    {
        if (ptr->field_38)
        {
            ptr->field_18 = ptr->field_38 - (char *)ptr->field_20;
            if ((v3->field_8 >> 2 & 1) && p->field_3b8)
            {
                ptr3 = ptr->field_8;
                ptr->field_8 = ptr3 + 1;
                *(ptr3) = 38;
                v0 = &ptr->field_8->field_0;
                memcpy(ptr->field_8, p->field_3c0, p->field_3b8);
                ptr->field_8 = &v0[p->field_3b8];
            }
            p->field_3b8 = &ptr->field_8[-1 * ptr->field_38];
            p->field_3c0 = ptr->field_38;
            ptr->field_38 = 0;
        }
        else
        {
            ptr->field_18 = ptr->field_8 - ptr->field_20;
            if (ptr->field_18 > 2000)
            {
                if (p->field_20->field_60->field_0 >= 4)
                    ngx_log_error_core(4, p->field_20->field_60, 0, "the rewritten URI is too long", a4, a5);
                ptr->field_0 = &ngx_http_script_exit_code.padding_0[0];
                ptr->field_48 = 500;
            }
            if (!(v3->field_8 >> 2 & 1))
                p->field_3b8 = 0;
        }
        if ((ptr->field_40 >> 4 & 1) || ((unsigned short)p->field_20->field_60->field_0 & 0x100))
        {
            if (p->field_20->field_60->field_0 >= 6)
                ngx_log_error_core(6, p->field_20->field_60, 0, "rewritten data: \"%V\", args: \"%V\"", &ptr->field_18, &p->field_3b8);
        }
        if ((v3->field_8 & 1))
        {
            pos = ptr;
            p->field_3a8 = pos->field_18;
            p->field_3b0 = pos->field_20;
            if (!p->field_3a8)
            {
                if (p->field_20->field_60->field_0 >= 4)
                    ngx_log_error_core(4, p->field_20->field_60, 0, "the rewritten URI has a zero length", a4, a5);
                ptr->field_0 = &ngx_http_script_exit_code.padding_0[0];
                ptr->field_48 = 500;
                return ptr;
            }
            ngx_http_set_exten(p);
        }
        ptr->field_0 = &ptr->field_0[1].padding_0[7];
        return ptr;
    }
}


