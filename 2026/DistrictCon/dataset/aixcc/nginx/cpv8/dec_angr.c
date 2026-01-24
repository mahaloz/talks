// Function: ngx_mail_pop3_user
typedef struct struct_1 {
    char padding_0[80];
    unsigned long long field_50;
    char padding_58[8];
    char field_60;
    char padding_61[7];
    void* field_68;
    char padding_70[176];
    struct struct_0 *field_120;
    unsigned long long field_128;
} struct_1;

typedef struct struct_0 {
    unsigned long long field_0;
    void* field_8;
} struct_0;

typedef struct struct_2 {
    char padding_0[96];
    struct struct_3 *field_60;
    unsigned long long field_68;
} struct_2;

typedef struct struct_3 {
    unsigned long long field_0;
} struct_3;

unsigned long long ngx_mail_pop3_user(struct_1 *ptr, struct_2 *a1)
{
    unsigned long long v3;  // r9
    struct_0 *v0;  // [bp-0x28]
    unsigned long long v1;  // [bp-0x10]

    if (ptr->field_128 != 1)
    {
        v1 = 20;
        return v1;
    }
    v0 = ptr->field_120;
    *((unsigned long long *)&ptr->field_60) = v0->field_0;
    ptr->field_68 = ngx_pnalloc(a1->field_68, 100);
    if (!ptr->field_68)
    {
        v1 = -1;
        return v1;
    }
    memcpy(ptr->field_68, v0->field_8, *((long long *)&ptr->field_60));
    if (((unsigned short)a1->field_60->field_0 & 0x200))
        ngx_log_error_core(8, a1->field_60, 0, "pop3 login: \"%V\"", &ptr->field_60, v3);
    ptr->field_50 = 1;
    v1 = 0;
    return v1;
}


