#include <stdlib.h>
#include "assert_without_ndebug.h"
#include "structures_consts.h"

void swap_structures(ptr_array_and_size_of_strings *struct1, ptr_array_and_size_of_strings *struct2)
{
    MY_ASSERT_WTHOUT_NDEBUG(struct1 != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(struct2 != NULL);

    ptr_array_and_size_of_strings temp = *struct1;
    *struct1 = *struct2;
    *struct2 = temp;
}