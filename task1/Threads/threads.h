#ifndef THREADS
#define THREADS

#include <bsd/stdlib.h>
#include "../Array/array_and_size.h"

typedef struct ThreadTask{
    int* array;
    size_t left;
    size_t right;
} ThreadTask;

long ChooseNumOfThreads(ArrayAndSize* array_size, long threads);

#endif //THREADS