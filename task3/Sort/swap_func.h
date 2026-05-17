//! @file
#ifndef SWAP_FUNC_H
#define SWAP_FUNC_H
#include "structures_consts.h"
#include <stdlib.h>

//! @warning Function uses assert for all pointers
void swap_structures(ptr_array_and_size_of_strings *struct1, ptr_array_and_size_of_strings *struct2);

#endif // SWAP_FUNC_H