#ifndef THREADS
#define THREADS

#include <bsd/stdlib.h>
#include "../Array/array_and_size.h"

typedef struct ThreadTask{
    int* array;
    long left;
    long right;
} ThreadTask;

long ChooseNumOfThreads(ArrayAndSize* array_size, long threads);

void FirstVersionParallelSort(ArrayAndSize* array_size, long threads);

#endif //THREADS