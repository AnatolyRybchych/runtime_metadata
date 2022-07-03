#include "metadata_symbol.h"
#include "metadata.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void metadata_add_symbol_ptr(struct __matadata_symbol_t *symbol);

matadata_primitive_t metadata_decl_primitive(const char *name, unsigned int size_bytes){
    char *_name = malloc(strlen(name) + 1);
    strcpy(_name, name);

    struct metadata_primitive_data_t *_data = malloc(sizeof(metadata_primitive_data_t));
    *_data = (struct metadata_primitive_data_t){
        .size = size_bytes,
    };

    struct __matadata_symbol_t *primitive = malloc(sizeof(struct __matadata_symbol_t));
    *primitive = (struct __matadata_symbol_t){
        .type = METADATA_TYPE_PRIMITIVE,
        .name = _name,
        .data = _data,
    };
    metadata_add_symbol_ptr(primitive);
    return primitive;
}

matadata_struct_t metadata_decl_struct(const char *name, matadata_symbol_t field1, const char *name1, ...){
    int size = 0;
    int fields_count = 0;
    struct __struct_field_t*fields = NULL;

    const void * const *arg = (const void * const *)&field1;
    while (*arg){
        matadata_symbol_t field = (matadata_symbol_t)*arg++;
        if(field->type == METADATA_TYPE_PRIMITIVE){
            size += ((metadata_primitive_data_t*)(field->data))->size;
        }
        else if(field->type == METADATA_TYPE_STRUCT){
            size += ((metadata_struct_data_t*)(field->data))->size;
        }
        else{
            fprintf(stderr, "struct %s declaration failed, field %s has incompatible type", name, field->name);
            exit(-1);
        }

        char *field_name = (char*)*arg++;
        if(field_name == NULL){
            fprintf(stderr, "struct %s declaration failed, field should have name", name);
            exit(-1);
        }

        char *_name = malloc(strlen(field_name) + 1);
        strcpy(_name, field_name);

        fields = realloc(fields, sizeof(struct_field_t) * (fields_count + 1));
        fields[fields_count].name = _name;
        fields[fields_count].type = field;
        fields_count ++;
    }
    
    char *_name = malloc(strlen(name) + 1);
    strcpy(_name, name);

    struct metadata_struct_data_t *_data = malloc(sizeof(metadata_struct_data_t));
    *_data = (struct metadata_struct_data_t){
        .size = size,
        .fields_count = fields_count,
        .fields = fields,
    };

    struct __matadata_symbol_t *primitive = malloc(sizeof(struct __matadata_symbol_t));
    *primitive = (struct __matadata_symbol_t){
        .type = METADATA_TYPE_STRUCT,
        .name = _name,
        .data = _data,
    };
    metadata_add_symbol_ptr(primitive);
    return primitive;
}
