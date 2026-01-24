// Function: ngx_mail_pop3_pass
typedef struct struct_1 {
    char padding_0[88];
    struct struct_0 *field_58;
    char padding_60[8];
    unsigned long long field_68;
} struct_1;

typedef struct struct_3 {
    char padding_0[96];
    unsigned long long field_60;
    unsigned long long field_68;
    char field_70;
    char padding_71[7];
    void* field_78;
    char padding_80[160];
    struct struct_2 *field_120;
    unsigned long long field_128;
} struct_3;

typedef struct struct_2 {
    unsigned long long field_0;
    void* field_8;
} struct_2;

typedef struct struct_0 {
    unsigned long long field_0;
    unsigned long long field_8;
    struct struct_0 *field_10;
} struct_0;

typedef struct struct_4 {
    unsigned long long field_0;
    unsigned long long field_8;
    struct struct_4 *field_10;
} struct_4;

unsigned long long ngx_mail_pop3_pass(struct_3 *ptr, struct_1 *a1)
{
    char v0;  // [bp-0x41]
    unsigned long long i;  // [bp-0x40]
    struct_4 *p;  // [bp-0x38]
    struct_1 *cur;  // [bp-0x30]
    struct_2 *v4;  // [bp-0x28]
    unsigned long long v5;  // [bp-0x10]

    cur = &a1->field_58;
    if (ptr->field_128 != 1)
    {
        v5 = 20;
        return v5;
    }
    v4 = ptr->field_120;
    *((unsigned long long *)&ptr->field_70) = v4->field_0;
    ptr->field_78 = ngx_pnalloc(a1->field_68, *((long long *)&ptr->field_70));
    if (!ptr->field_78)
    {
        v5 = -1;
        return v5;
    }
    memcpy(ptr->field_78, v4->field_8, *((long long *)&ptr->field_70));
    if (!*((long long *)&cur->padding_0[0]))
    {
        v5 = -4;
        return v5;
    }
    while (true)
    {
        v0 = 0;
        if (*((long long *)&cur->padding_0[0]))
            v0 = *((long long *)(*((long long *)&cur->padding_0[0]) + 16));
        if (!(v0 & 1))
            break;
        *((long long *)&cur->padding_0[0]) = *((long long *)(*((long long *)&cur->padding_0[0]) + 16));
        cur = &cur->padding_0[8];
    }
    p = ngx_pnalloc(a1->field_68, 24);
    if (p)
    {
        for (i = 0; i < ptr->field_60; i += 1)
        {
            *((char *)(p->field_8 + i)) = *((char *)(ptr->field_68 + i));
        }
        p->field_0 = ptr->field_60;
    }
    if (*((long long *)&cur->padding_0[0]))
        *((struct_4 **)(*((long long *)&cur->padding_0[0]) + 16)) = p;
    else
        *((struct_4 **)&cur->padding_0[0]) = p;
    v5 = -4;
    return v5;
}


// Function: ngx_mail_pop3_logs
typedef struct struct_1 {
    char padding_0[16];
    unsigned long long field_10;
    struct struct_0 *field_18;
    char padding_20[96];
    char field_80;
    char padding_81[7];
    void* field_88;
} struct_1;

typedef struct struct_2 {
    unsigned long long field_0;
    unsigned long long field_8;
    unsigned long long field_10;
    unsigned int field_18;
    char field_1c;
} struct_2;

typedef struct struct_0 {
    unsigned long long field_0;
    unsigned long long field_8;
    unsigned long long field_10;
    unsigned int field_18;
    char field_1c;
} struct_0;

extern unsigned long long g_5b4528;
extern unsigned long long g_5b4530;
extern unsigned int g_5b4538;
extern char g_5b453c;
extern unsigned long long pop3_logging;

unsigned long long ngx_mail_pop3_logs(struct_1 *p, unsigned long long *addr)
{
    struct_2 *v4;  // rax
    unsigned long long v5;  // rdx
    unsigned long long v6;  // r8
    unsigned long long v7;  // r9
    struct_0 *ptr;  // rax
    unsigned long v0;  // [bp-0x30]
    unsigned long v1;  // [bp-0x28], Other Possible Types: unsigned long long
    unsigned long long v2;  // [bp-0x10]

    if (!addr[11])
        addr[11] = ngx_pnalloc(addr[13], 24);
    v4 = ngx_pnalloc(addr[13], *((long long *)&p->field_80) + 29);
    p->field_18 = v4;
    if (p->field_18)
    {
        ptr = p->field_18;
        ptr->field_0 = pop3_logging;
        ptr->field_8 = g_5b4528;
        ptr->field_10 = g_5b4530;
        ptr->field_18 = g_5b4538;
        ptr->field_1c = g_5b453c;
        v1 = ptr + 1;
        v0 = v1;
        memcpy(v1, p->field_88, *((long long *)&p->field_80));
        v1 = v0 + *((long long *)&p->field_80);
        p->field_10 = v1 - (char *)p->field_18;
        v2 = 0;
        return v2;
    }
    ngx_mail_session_internal_server_error(p, addr, v5, v4, v6, v7);
    v2 = -1;
    return v2;
}


