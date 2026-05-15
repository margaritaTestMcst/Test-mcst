#include "array.h"
#include <stdio.h>
#include <assert.h>


static bool RecallocArr(ArrayAndSize* array_size);

ArrayAndSize* ArrayAndSizeCtor(){
    ArrayAndSize* array_size = (ArrayAndSize*)canary_calloc(1, sizeof(ArrayAndSize));
    if(!array_size){
        fprintf(stderr, "Error: can't alloc ArrayAndSize struct\n");
        return NULL;
    }

    char** array = (char**)canary_calloc(sizeof(char*), 10);
    if(!array){
        fprintf(stderr, "Error: can't alloc char** array in ArrayAndSize struct\n");
        canary_free(array_size, sizeof(ArrayAndSize));
        return NULL;
    }

    array_size->array = array;
    array_size->capacity = 10;

    return array_size;
}


bool ArrayAndSizeInsert(ArrayAndSize* array_size, char* str){
    assert(array_size);
    assert(canary_verify(array_size->array, sizeof(char*) * array_size->capacity) == NO_MISTAKE_CANARY);

    if(array_size->capacity == array_size->size){
        bool could_realloc = RecallocArr(array_size);
        if(!could_realloc) return false;
    }

    assert(array_size->capacity != array_size->size);

    array_size->array[array_size->size] = str;
    array_size->size++;

    assert(canary_verify(array_size->array, sizeof(char*) * array_size->capacity) == NO_MISTAKE_CANARY);

    return true;
}

static bool RecallocArr(ArrayAndSize* array_size){
    assert(array_size);

    char** array = (char**)canary_recalloc(array_size->array, array_size->capacity, array_size->capacity*2,  sizeof(char*));
    if(!array){
        fprintf(stderr, "Error: can't realloc int* array in ArrayAndSize struct\n");
        return false;
    }

    array_size->array = array;
    array_size->capacity*= 2;

    return true;
}

void ArrayAndSizeDtor(ArrayAndSize* array_size){
    if(!array_size) return;
    if(array_size->array) canary_free(array_size->array, sizeof(char*) * array_size->capacity);
    canary_free(array_size, sizeof(ArrayAndSize));
}