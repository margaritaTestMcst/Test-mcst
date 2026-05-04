#include "array_and_size.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

static bool RecallocInts(ArrayAndSize* array_size);

ArrayAndSize* ArrayAndSizeCtor(){
    ArrayAndSize* array_size = (ArrayAndSize*)calloc(1, sizeof(ArrayAndSize));
    if(!array_size){
        fprintf(stderr, "Error: can't alloc ArrayAndSize struct\n");
        return NULL;
    }

    int* ints = (int*)calloc(sizeof(int), 10);
    if(!ints){
        fprintf(stderr, "Error: can't alloc int* array in ArrayAndSize struct\n");
        free(array_size);
        return NULL;
    }

    array_size->array = ints;
    array_size->capacity = 10;

    size_t count = 0;
    int temp = 0;

    while(true){
        if(scanf("%d", &temp)!=1){
            break;
        }
        if(count + 1 == array_size->capacity){
            if(!RecallocInts(array_size)){
                free(array_size->array);
                free(array_size);
                return NULL;
            }
        }
        array_size->array[count] = temp;
        count++;
    }
    array_size->size = count;
    return array_size;
}


static bool RecallocInts(ArrayAndSize* array_size){
    assert(array_size);

    int* ints = (int*)recallocarray(array_size->array, array_size->capacity, array_size->capacity*2,  sizeof(int));
    if(!ints){
        fprintf(stderr, "Error: can't realloc int* array in ArrayAndSize struct\n");
        return false;
    }

    array_size->array = ints;
    array_size->capacity*= 2;

    return true;
}

void ArrayAndSizeDump(ArrayAndSize* array_size){
    assert(array_size);
    for(size_t i = 0; i < array_size->size; i++){
        printf("%d ", array_size->array[i]);
    }
}

void ArrayAndSizeDtor(ArrayAndSize* array_size){
    if(!array_size) return;
    if(array_size->array) free(array_size->array);
    free(array_size);
}