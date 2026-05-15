#include "array.h"
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


static bool RecallocArr(ArrayAndSize* array_size);

ArrayAndSize* ArrayAndSizeCtor(size_t size_of_elem){
    assert(size_of_elem > 0 && size_of_elem <= 0.8 * SIZE_MAX);

    ArrayAndSize* array_size = (ArrayAndSize*)calloc(1, sizeof(ArrayAndSize));
    if(!array_size){
        fprintf(stderr, "Error: can't alloc ArrayAndSize struct\n");
        return NULL;
    }

    void* array = calloc(10, size_of_elem);
    if(!array){
        fprintf(stderr, "Error: can't alloc char** array in ArrayAndSize struct\n");
        free(array_size);
        return NULL;
    }

    array_size->array = array;
    array_size->capacity = 10;

    return array_size;
}


bool ArrayAndSizeInsert(ArrayAndSize* array_size, const void* elem){
    assert(array_size);

    if(array_size->capacity == array_size->size){
        bool could_realloc = RecallocArr(array_size);
        if(!could_realloc) return false;
    }

    assert(array_size->capacity != array_size->size);

    memcpy(array_size->array + array_size->size * array_size->size_of_elem, elem, array_size->size_of_elem);
    array_size->size++;

    return true;
}

static bool RecallocArr(ArrayAndSize* array_size){
    assert(array_size);

    void* array = recallocarray(array_size->array, array_size->capacity, array_size->capacity*2, array_size->size_of_elem);
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
    if(array_size->array) free(array_size->array);
    free(array_size);
}