#ifndef ARRAY_SIZE
#define ARRAY_SIZE

#include <bsd/stdlib.h>

typedef struct ArrayAndSize {
    int* array;
    size_t capacity;
    size_t size;
} ArrayAndSize;

ArrayAndSize* ArrayAndSizeCtor();

void ArrayAndSizeDump(ArrayAndSize* array_size);

void ArrayAndSizeDtor(ArrayAndSize* array_size);

#endif //ARRAY_SIZE