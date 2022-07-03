#ifndef __RUNTIME_METADATA_H_
#define __RUNTIME_METADATA_H_
#include <metadata.h>
#include "metadata_symbol.h"

struct __metadata_t{
    int symbols_count;
    matadata_symbol_t *symbols;
};

void metadata_add_symbol_ptr(struct __matadata_symbol_t *symbol);

#endif //__RUNTIME_METADATA_H_