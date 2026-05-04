#ifndef THREADS
#define THREADS

#include <bsd/stdlib.h>
#include "../Array/array_and_size.h"

long ChooseNumOfThreads(ArrayAndSize* array_size, long threads);

#endif //THREADS