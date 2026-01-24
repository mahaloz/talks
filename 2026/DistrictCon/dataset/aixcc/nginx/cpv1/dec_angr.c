// Function: ngx_http_validate_from
typedef struct struct_0 {
    unsigned long long field_0;
    void* field_8;
} struct_0;


unsigned long long ngx_http_validate_from(struct_0 *ptr, unsigned long long a1, unsigned long long a2)
{
    unsigned long long *v7;  // rax
    unsigned long long *v8;  // rax
    unsigned long long *v9;  // rax
    unsigned long long *v10;  // rax
    unsigned long long *v11;  // rax
    unsigned int v0;  // [bp-0x4c]
    unsigned long long v1;  // [bp-0x48]
    char v2;  // [bp-0x39]
    void* cur;  // [bp-0x38]
    void* v4;  // [bp-0x30]
    unsigned long long v5;  // [bp-0x10]

    v4 = ptr->field_8;
    v0 = 0;
    if (a2)
    {
        cur = ngx_palloc(a1, ptr->field_0);
        if (!cur)
        {
            v5 = -1;
            return v5;
        }
    }
    else
    {
        cur = ptr->field_8;
    }
    v1 = 0;
LABEL_4a3b47:
    if (v1 < ptr->field_0)
    {
        v2 = *((char *)v4 + v1);
        switch (v0)
        {
        case 0:
            v7 = __ctype_b_loc();
            if (!((char)*((short *)(*(v7) + v2 * 2)) & 8))
            {
                switch (v2)
                {
                case 45: case 95:
                    v0 = 1;
LABEL_4a3bfb:
                    cur += 1;
                    *((char *)cur) = v2;
                    break;
                case 46:
                    v0 = 2;
LABEL_4a3bfb:
                    cur += 1;
                    *((char *)cur) = v2;
LABEL_4a3e47:
                    break;
                default:
                    v5 = -5;
                    return v5;
                }
            }
            else
            {
                v0 = 1;
                goto LABEL_4a3bfb;
            }
        case 1:
            switch (v2)
            {
            case 64:
                v0 = 3;
                cur += 1;
                *((char *)cur) = v2;
                goto LABEL_4a3e47;
            case 46:
                v0 = 2;
                break;
            default:
                v9 = __ctype_b_loc();
                if (!((char)*((short *)(*(v9) + v2 * 2)) & 8) && v2 != 45 && v2 != 95 && v2 != 43)
                {
                    v5 = -5;
                    return v5;
                }
                break;
            }
            cur += 1;
            *((char *)cur) = v2;
LABEL_4a3e47:
            break;
        case 2:
            v8 = __ctype_b_loc();
            if (!((char)*((short *)(*(v8) + v2 * 2)) & 8))
            {
                switch (v2)
                {
                case 45: case 95:
                    cur += 1;
                    *((char *)cur) = v2;
                    v0 = 1;
LABEL_4a3cd6:
                    break;
                case 46:
                    v0 = 2;
                    for (cur -= 2; *((char *)cur) != 46; cur -= 1);
                    cur += 1;
LABEL_4a3cd6:
LABEL_4a3e47:
                    break;
                default:
                    v5 = -5;
                    return v5;
                }
            }
            else
            {
                cur += 1;
                *((char *)cur) = v2;
                v0 = 1;
                goto LABEL_4a3cd6;
            }
        case 3:
            if (v2 == 46)
            {
                v0 = 4;
            }
            else
            {
                v10 = __ctype_b_loc();
                if (!((char)*((short *)(*(v10) + v2 * 2)) & 8) && v2 != 45)
                {
                    v5 = -5;
                    return v5;
                }
            }
            cur += 1;
            *((char *)cur) = v2;
LABEL_4a3e47:
            break;
        case 4:
            v11 = __ctype_b_loc();
            if (!(*((short *)(*(v11) + v2 * 2)) & 0x400))
            {
                v5 = -5;
                return v5;
            }
            cur += 1;
            *((char *)cur) = v2;
LABEL_4a3e47:
            v1 += 1;
            goto LABEL_4a3b47;
        default:
            v5 = -5;
            return v5;
        }
    }
    else if (v0 == 4)
    {
        *((char *)cur) = 0;
        if (a2)
            ptr->field_8 = cur;
        v5 = 0;
        return v5;
    }
    else
    {
        v5 = -5;
        return v5;
    }
}


