#ifndef MERGE
#define MERGE

#include "../Array/array_and_size.h"
#include <pthread.h>

typedef struct MergeThreadTask{
    int* arr;
    int* tmp;

    long left;
    long middle;
    long right;
} MergeThreadTask;


void ParallelMergeAllParts(ArrayAndSize *array_size, int *temp, long *bounds, long parts_count);

#endif //MERGE