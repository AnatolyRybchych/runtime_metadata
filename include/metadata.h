#ifndef __METADATA_H_
#define __METADATA_H_

#include <stdbool.h>

#define FIELDS_END (matadata_symbol_t)0
#define UNDEFINED_SYMBOL (matadata_symbol_t)0

typedef const struct __metadata_t* metadata_t;
typedef const struct __struct_field_t struct_field_t;
typedef const struct __matadata_symbol_t* matadata_symbol_t;
typedef const struct __matadata_symbol_t* matadata_struct_t;
typedef const struct __matadata_symbol_t* matadata_primitive_t;

typedef int metadata_symbol_type;
enum metadata_symbol_type{
    METADATA_TYPE_FUNCTION,
    METADATA_TYPE_STRUCT,
    METADATA_TYPE_PRIMITIVE,
    METADATA_TYPE_OBJECT,
    METADATA_TYPE_METHOD,
};

metadata_t metadata(void);
int metadata_get_symbols_count(void);
const matadata_symbol_t *metadata_get_symbols(void);
const char *metadata_get_symbol_name(const matadata_symbol_t symbol);
metadata_symbol_type metadata_get_symbol_type(const matadata_symbol_t symbol);
bool metadata_is_symbol_can_be_struct_field(const matadata_symbol_t symbol);
const char *metdata_get_symbol_type_string(metadata_symbol_type type);
int metadata_sizeof(const matadata_symbol_t symbol);
int metdata_get_struct_fields_count(const matadata_struct_t symbol);
const struct_field_t *metdata_get_struct_fields(const matadata_struct_t symbol);
matadata_symbol_t metdata_get_symbol(const char *name);

matadata_primitive_t metadata_decl_primitive(const char *name, unsigned int size_bytes);
matadata_struct_t metadata_decl_struct(const char *name, matadata_symbol_t field1, const char *name1, ...);

struct __struct_field_t{
    matadata_symbol_t type;
    char *name;
};

#endif
