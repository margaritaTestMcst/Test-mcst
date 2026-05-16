#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Array/array_and_size.h"

int main(){
    ArrayAndSize* array = ArrayAndSizeCtor();
    if(!array) return 0;

    if(array->size == 0){
        ArrayAndSizeDtor(array);
        return 0;
    } 

    size_t cur_start = 0;
    size_t cur_len = 1;
    int cur_sum = array->array[0];

    size_t best_start = 0;
    size_t best_len = 1;
    int best_sum = array->array[0];

    for(size_t i = 1; i < array->size - 1; i++){
        if(array->array[i] > array->array[i - 1]){
            cur_sum += array->array[i];
            cur_len++;
            continue;
        }

        if((cur_sum == best_sum && cur_len > best_len) || cur_sum > best_sum){
            best_sum = cur_sum;
            best_start = cur_start;
            best_len = cur_len;
        }

        cur_start = i;
        cur_len = 1;
        cur_sum = array->array[i];
    }

    if((cur_sum == best_sum && cur_len > best_len) || cur_sum > best_sum){
        best_sum = cur_sum;
        best_start = cur_start;
        best_len = cur_len;
    }

    for(size_t i = best_start; i < best_len + best_start; i++){
        printf("%d ", array->array[i]);
    }
    printf("\n");

    ArrayAndSizeDtor(array);
}