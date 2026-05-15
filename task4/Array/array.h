#ifndef ARRAY_SIZE
#define ARRAY_SIZE

#include <bsd/stdlib.h>
#include <stdbool.h>

typedef struct ArrayAndSize {
    void* array;
    size_t size_of_elem;
    size_t capacity;
    size_t size;
} ArrayAndSize;

ArrayAndSize* ArrayAndSizeCtor(size_t size_of_elem);

bool ArrayAndSizeInsert(ArrayAndSize* array_size, const void* elem);

void ArrayAndSizeDtor(ArrayAndSize* array_size);

#endif //ARRAY_SIZE