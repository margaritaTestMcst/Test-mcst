#include "threads.h"
#include "../Merge/merge.h"
#include <assert.h>
#include <pthread.h>

long ChooseNumOfThreads(ArrayAndSize* array_size, long threads){
    assert(array_size);

    if(threads <= 1 || array_size->size < 2){
        return 1;
    }

    if(threads > 16){
        return 16; //на моем процессоре 16 ядер, и желательно не допускать, чтобы потоков было сильно больше, чем ядер
    }

    long size_div_two = array_size->size / 2;
    if(threads > size_div_two){
        return size_div_two; // нужно чтобы базово в самом минимальном подмассиве было 2 элемента
    }

    return threads;
}

// Sorting small arrays =====================================================================================================

static void* ThreadSortFunc(void* arg);

static int CompareInts(const void* a, const void* b);

void FirstVersionParallelSort(ArrayAndSize* array_size, long threads){
    assert(array_size);
    assert(array_size->array);

    pthread_t* thread_id = (pthread_t*)calloc(sizeof(pthread_t), threads);
    if(!thread_id){
        fprintf(stderr, "Error: can't allocate pthread_t* thread_id\n");
        return;
    }

    ThreadTask* tasks = (ThreadTask*)calloc(sizeof(ThreadTask), threads);
    if(!tasks){
        fprintf(stderr, "Error: can't allocate  ThreadTask* tasks\n");
        free(thread_id);
        return;
    }

    long *end_parts = calloc(threads + 1, sizeof(long));
    if(!end_parts){
        fprintf(stderr, "Error: can't allocate size_t *end_parts\n");
        free(tasks);
        free(thread_id);
        return;
    }

    for(long i = 0; i <= threads; i++) {
        end_parts[i] = i * (long)array_size->size / threads;
    }

    for(int i = 0; i < threads; i++){
        tasks[i].array = array_size->array;
        tasks[i].left = end_parts[i];
        tasks[i].right = end_parts[i + 1];

        pthread_create(&thread_id[i], NULL, ThreadSortFunc, &tasks[i]);
    }

    for(int i = 0; i < threads; i++){
        pthread_join(thread_id[i], NULL);
    }

    free(tasks);
    free(thread_id);

    int* tmp = (int*)calloc(sizeof(int), array_size->size);
    if(!tmp){
        fprintf(stderr, "Error: can't allocate int* tmp\n");
        free(end_parts);
        return;
    }

    ParallelMergeAllParts(array_size, tmp, end_parts, threads);

    free(tmp);
    free(end_parts);
}

static int CompareInts(const void* a, const void* b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static void* ThreadSortFunc(void* arg){
    ThreadTask* task = (ThreadTask*)arg;

    qsort(task->array + task->left, (size_t)(task->right - task->left), sizeof(int), CompareInts);

    return NULL;
}