#ifndef ARRAY_SIZE
#define ARRAY_SIZE

#include <bsd/stdlib.h>
#include <stdbool.h>
#include "../my_canary_std_func/my_canary_std_func.h"

typedef struct ArrayAndSize {
    char** array;
    size_t capacity;
    size_t size;
} ArrayAndSize;

ArrayAndSize* ArrayAndSizeCtor();

bool ArrayAndSizeInsert(ArrayAndSize* array_size, char* str);

void ArrayAndSizeDtor(ArrayAndSize* array_size);

#endif //ARRAY_SIZE