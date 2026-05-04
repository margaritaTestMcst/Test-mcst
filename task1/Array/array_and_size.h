#ifndef ARRAY_SIZE
#define ARRAY_SIZE

#include <bsd/stdlib.h>

typedef struct ArrayAndSize {
    int* array;
    size_t capacity;
} ArrayAndSize;

ArrayAndSize* ArrayAndSizeCtor();

void ArrayAndSizeDtor(ArrayAndSize* array_size);

#endif //ARRAY_SIZE