// Function: ngx_black_list_insert
typedef struct struct_1 {
    struct struct_0 *field_0;
    struct struct_1 *field_8;
    struct struct_1 *field_10;
} struct_1;

typedef struct struct_3 {
    struct struct_2 *field_0;
    struct struct_3 *field_8;
    struct struct_3 *field_10;
} struct_3;

typedef struct struct_0 {
    char field_0;
    char padding_1[7];
    void* field_8;
} struct_0;

typedef struct struct_2 {
    unsigned long long field_0;
    char *field_8;
} struct_2;

void ngx_black_list_insert(struct_3 **p, char *a1, unsigned long long a2)
{
    unsigned long long v6;  // rcx
    char v0;  // [bp-0x49]
    unsigned long long i;  // [bp-0x48]
    unsigned long long v2;  // [bp-0x40]
    struct_1 *ptr;  // [bp-0x38], Other Possible Types: unsigned long long
    struct_3 *cur;  // [bp-0x30]

    v2 = ngx_alloc(a2, v6);
    for (i = 0; i < a2; i += 1)
    {
        *((char *)(v2 + i)) = a1[i];
    }
    ptr = ngx_alloc(24, v6);
    ptr->field_0 = ngx_alloc(16, v6);
    ptr->field_0->field_8 = v2;
    *((unsigned long long *)&ptr->field_0->field_0) = a2;
    ptr->field_8 = NULL;
    cur = *(p);
    if (!cur)
    {
        *(p) = ptr;
        return;
    }
    while (true)
    {
        v0 = 0;
        if (cur)
            v0 = cur->field_8;
        if (!(v0 & 1))
        {
            cur->field_8 = ptr;
            ptr->field_10 = cur;
            return;
        }
        if (!strcmp(a1, cur->field_0->field_8))
        {
            memset(ptr->field_0->field_8, 0, *((long long *)&ptr->field_0->field_0));
            free(ptr->field_0->field_8);
            ptr->field_0->field_8 = NULL;
            memset(ptr->field_0, 0, 16);
            free(ptr->field_0);
            ptr->field_0 = NULL;
            memset(ptr, 0, 24);
            free(ptr);
            ptr = 0;
            return;
        }
        cur = cur->field_8;
    }
}


// Function: ngx_black_list_remove
typedef struct struct_4 {
    struct struct_0 *field_0;
    struct struct_3 *field_8;
} struct_4;

typedef struct struct_0 {
    char field_0;
    char padding_1[7];
    void* field_8;
} struct_0;

typedef struct struct_3 {
    struct struct_1 *field_0;
    struct struct_3 *field_8;
    struct struct_2 *field_10;
} struct_3;

typedef struct struct_6 {
    struct struct_7 *field_0;
    struct struct_6 *field_8;
    struct struct_5 *field_10;
} struct_6;

typedef struct struct_2 {
    char padding_0[8];
    struct struct_3 *field_8;
} struct_2;

typedef struct struct_1 {
    char field_0;
    char padding_1[7];
    void* field_8;
} struct_1;

typedef struct struct_7 {
    unsigned long long field_0;
    unsigned long long field_8;
} struct_7;

typedef struct struct_5 {
    char padding_0[8];
    struct struct_6 *field_8;
} struct_5;

unsigned long long ngx_black_list_remove(struct_4 **p, char *a1)
{
    char v0;  // [bp-0x29]
    struct_3 *cur;  // [bp-0x28], Other Possible Types: struct_4 *, unsigned long long
    unsigned long long v2;  // [bp-0x10]

    cur = *(p);
    if (cur && !strcmp(a1, cur->field_0->field_8))
    {
        memset(cur->field_0->field_8, 0, *((long long *)&cur->field_0->field_0));
        free(cur->field_0->field_8);
        cur->field_0->field_8 = NULL;
        memset(cur->field_0, 0, 16);
        free(cur->field_0);
        cur->field_0 = NULL;
        memset(cur, 0, 24);
        free(cur);
        cur = 0;
        v2 = 0;
        return v2;
    }
    cur = cur->field_8;
    while (true)
    {
        v0 = 0;
        if (cur)
            v0 = cur->field_8;
        if (!(v0 & 1))
        {
            v2 = -1;
            return v2;
        }
        if (!strcmp(a1, cur->field_0->field_8))
            break;
        cur = cur->field_8;
    }
    if (cur->field_10)
        cur->field_10->field_8 = cur->field_8;
    if (cur->field_8)
        cur->field_8->field_10 = cur->field_10;
    memset(cur->field_0->field_8, 0, *((long long *)&cur->field_0->field_0));
    free(cur->field_0->field_8);
    cur->field_0->field_8 = NULL;
    memset(cur->field_0, 0, 16);
    free(cur->field_0);
    cur->field_0 = NULL;
    memset(cur, 0, 24);
    free(cur);
    cur = 0;
    v2 = 0;
    return v2;
}


// Function: ngx_is_ip_banned
typedef struct struct_2 {
    char padding_0[672];
    struct struct_1 *field_2a0;
} struct_2;

typedef struct struct_4 {
    struct struct_3 *field_0;
    struct struct_4 *field_8;
} struct_4;

typedef struct struct_5 {
    char padding_0[144];
    char *field_90;
} struct_5;

typedef struct struct_1 {
    struct struct_0 *field_0;
    struct struct_1 *field_8;
} struct_1;

typedef struct struct_3 {
    char padding_0[8];
    char *field_8;
} struct_3;

typedef struct struct_0 {
    char padding_0[8];
    unsigned long long field_8;
} struct_0;

unsigned long long ngx_is_ip_banned(struct_2 *a0, struct_5 *a1)
{
    unsigned long long v4;  // rdx
    unsigned long long v5;  // rcx
    unsigned long long v6;  // r8
    unsigned long long v7;  // r9
    struct_4 *v0;  // [bp-0x30]
    struct_4 *cur;  // [bp-0x28]
    unsigned long long v2;  // [bp-0x10]

    v0 = (!a0 ? NULL : a0->field_2a0);
    for (cur = v0; cur; cur = cur->field_8)
    {
        if (!strcmp(a1->field_90, cur->field_0->field_8))
        {
            ngx_close_connection(a1, a1, v4, v5, v6, v7);
            v2 = -1;
            return v2;
        }
    }
    v2 = 0;
    return v2;
}


