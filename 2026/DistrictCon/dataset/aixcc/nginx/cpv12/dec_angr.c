// Function: ngx_sendfile_r
typedef struct struct_0 {
    char padding_0[16];
    unsigned long long field_10;
    char padding_18[40];
    struct struct_1 *field_40;
} struct_0;

typedef struct struct_2 {
    char padding_0[48];
    struct struct_3 *field_30;
    char padding_38[40];
    unsigned long long field_60;
    unsigned long long field_68;
} struct_2;

typedef struct struct_1 {
    unsigned int field_0;
} struct_1;

typedef struct struct_3 {
    unsigned long long field_0;
} struct_3;

unsigned long long ngx_sendfile_r(struct_2 *a0, struct_0 *ptr, unsigned long long a2)
{
    unsigned long long v9;  // rcx
    unsigned long long v10;  // r8
    unsigned long long v11;  // r9
    unsigned int i;  // [bp-0xd8]
    unsigned int v1;  // [bp-0xd4]
    unsigned long long v2;  // [bp-0xd0]
    char *v3;  // [bp-0xc8]
    char *v4;  // [bp-0xc0]
    char v5;  // [bp-0xb8]
    unsigned long v6;  // [bp-0x88]
    unsigned long long v7;  // [bp-0x10]

    if ((int)fstat64(ptr->field_40->field_0, &v5))
    {
        v7 = -1;
        return v7;
    }
    v4 = ngx_palloc(a0->field_68, v6);
    if (!v4)
    {
        v7 = -1;
        return v7;
    }
    else if (read(ptr->field_40->field_0, v4, v6) == -1)
    {
        v7 = -1;
        return v7;
    }
    else
    {
        lseek64(ptr->field_40->field_0, 0, 0);
        v3 = ngx_alloc(100, a0->field_60);
        if (!v3)
        {
            v7 = -1;
            return v7;
        }
        v1 = ptr->field_10 + a2 - 1;
        for (i = 0; v1 >= ptr->field_10; i += 1)
        {
            v3[i] = v4[v1];
            v1 -= 1;
        }
        v2 = a0->field_30(a0, v3, a2);
        ngx_pfree(a0->field_68, v4, a2, v9, v10, v11);
        free(v3);
        v7 = v2;
        return v7;
    }
}


