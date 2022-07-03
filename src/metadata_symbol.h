#ifndef __METADATA_SYMBOL_H_
#define __METADATA_SYMBOL_H_
#include "metadata.h"

struct __matadata_symbol_t{
    metadata_symbol_type type;
    char *name;
    void *data;
};

typedef struct metadata_primitive_data_t{
    int size;
} metadata_primitive_data_t;

typedef struct metadata_struct_data_t{
    int size;
    int fields_count;
    struct_field_t *fields;
} metadata_struct_data_t;

#endif //__METADATA_SYMBOL_H_