#ifndef ARRAY_SIZE
#define ARRAY_SIZE

#include <bsd/stdlib.h>

struct ArrayAndSize {
    int* array;
    size_t capacity;
    size_t size;
};

ArrayAndSize* ArrayAndSizeCtor();

void ArrayAndSizeDump(ArrayAndSize* array_size);

void ArrayAndSizeDtor(ArrayAndSize* array_size);

#endif //ARRAY_SIZE