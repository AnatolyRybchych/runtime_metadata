#include "metadata.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

static struct __metadata_t value = {
    .symbols_count = 0,
    .symbols = NULL,
};

metadata_t metadata(void){
    return &value;
}

int metadata_get_symbols_count(void){
    return value.symbols_count;
}

const matadata_symbol_t *metadata_get_symbols(void){
    return value.symbols;
}

const char *metadata_get_symbol_name(const matadata_symbol_t symbol){
    return symbol->name;
}

metadata_symbol_type metadata_get_symbol_type(const matadata_symbol_t symbol){
    return symbol->type;
}

bool metadata_is_symbol_can_be_struct_field(const matadata_symbol_t symbol){
    return symbol->type == METADATA_TYPE_PRIMITIVE || symbol->type == METADATA_TYPE_STRUCT;
}

const char *metdata_get_symbol_type_string(metadata_symbol_type type){
    switch (type)
    {
        case METADATA_TYPE_PRIMITIVE: return "primitive";
        case METADATA_TYPE_STRUCT: return "struct";
        case METADATA_TYPE_FUNCTION: return "function";
        case METADATA_TYPE_OBJECT: return "object";
        case METADATA_TYPE_METHOD: return "method";
        default: return "undefined";
    }
}

int metadata_sizeof(const matadata_symbol_t symbol){
    if(symbol->type == METADATA_TYPE_PRIMITIVE){
        return ((metadata_primitive_data_t*)symbol->data)->size;
    }
    else if(symbol->type == METADATA_TYPE_STRUCT){
        return ((metadata_struct_data_t*)symbol->data)->size;
    }
    else{
        printf("symbol %s has incompatible type %s\n", symbol->name, metdata_get_symbol_type_string(symbol->type));
        exit(-1);
    }
}

int metdata_get_struct_fields_count(const matadata_struct_t symbol){
    if(symbol->type == METADATA_TYPE_STRUCT)
        return ((metadata_struct_data_t*)symbol->data)->fields_count;
    else{
        return 0;
    }
}

const struct_field_t *metdata_get_struct_fields(const matadata_struct_t symbol){
    if(symbol->type == METADATA_TYPE_STRUCT)
        return ((metadata_struct_data_t*)symbol->data)->fields;
    else{
        return NULL;
    }
}

matadata_symbol_t metdata_get_symbol(const char *name){
    matadata_symbol_t *symbol = value.symbols;
    matadata_symbol_t *symbols_end = value.symbols + value.symbols_count;

    while (symbol != symbols_end){
        if(!strcmp((*symbol)->name, name)) return *symbol;
        symbol++;
    }
    return UNDEFINED_SYMBOL;
}

void metadata_add_symbol_ptr(struct __matadata_symbol_t *symbol){
    if(metdata_get_symbol(symbol->name) != UNDEFINED_SYMBOL){
        fprintf(stderr, "symbol %s is already defined\n", symbol->name);
        exit(-1);
    }
    value.symbols = realloc(value.symbols, (++value.symbols_count) * sizeof(matadata_symbol_t));
    value.symbols[value.symbols_count - 1] = symbol;
}
