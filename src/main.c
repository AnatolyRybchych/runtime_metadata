#include <stdio.h>
#include <metadata.h>

void print_struct_fields(matadata_struct_t symbol, int tabs){
    if(metdata_get_struct_fields_count(symbol) == 0) return;
    for(int i = 0; i < metdata_get_struct_fields_count(symbol); i++){
        for(int j = 0; j < tabs; j++) printf("    ");
        struct_field_t curr = metdata_get_struct_fields(symbol)[i];
        
        printf(
            "%s %s\n", 
            metadata_get_symbol_name(curr.type),
            curr.name
        );
        print_struct_fields(curr.type, tabs + 1); 
    }
}

int main(int argc, char const *argv[]){
    matadata_primitive_t int_primitive = metadata_decl_primitive("int", sizeof(int));
    matadata_primitive_t float_primitive = metadata_decl_primitive("float", sizeof(float));

    matadata_struct_t point_struct = metadata_decl_struct("point", int_primitive, "x", int_primitive, "y", FIELDS_END); 
    matadata_struct_t size_struct = metadata_decl_struct("size", int_primitive, "width", int_primitive, "height", FIELDS_END); 
    matadata_struct_t rect_struct = metadata_decl_struct("rect", point_struct, "pos", size_struct, "size", FIELDS_END); 

    for(int i = 0 ; i < metadata_get_symbols_count(); i++){
        matadata_symbol_t symbol = metadata_get_symbols()[i];
        printf(
            "%s %s, size:%i\n", 
            metdata_get_symbol_type_string(metadata_get_symbol_type(symbol)), 
            metadata_get_symbol_name(symbol),
            metadata_sizeof(symbol)
        );
        print_struct_fields(symbol, 1);
    }

    return 0;
}
