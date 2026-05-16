#include "algo_src.h"
#include <assert.h>


SubsequenceInfo create_subseq_info(size_t start, size_t len, int sum){
    SubsequenceInfo info = {};
    info.start = start;
    info.len = len;
    info.sum = sum;
    return info;
}

static void fill_subseq_info(size_t start, size_t len, int sum, SubsequenceInfo* info){
    info->start = start;
    info->len = len;
    info->sum = sum;
}

void find_max_sum_subseq(ArrayAndSize* array, SubsequenceInfo* curr_sum, SubsequenceInfo* best_sum){
    assert(array);

    for(size_t i = 1; i < array->size - 1; i++){
        if(array->array[i] > array->array[i - 1]){
            curr_sum->sum += array->array[i];
            (curr_sum->len)++;
            continue;
        }

        if((curr_sum->sum == best_sum->sum && curr_sum->len > best_sum->len) || curr_sum->sum > best_sum->sum){
            fill_subseq_info(curr_sum->start, curr_sum->len, curr_sum->sum, best_sum);
        }

        fill_subseq_info(i, 1,  array->array[i], curr_sum);
    }

    if((curr_sum->sum == best_sum->sum && curr_sum->len > best_sum->len) || curr_sum->sum > best_sum->sum){
        fill_subseq_info(curr_sum->start, curr_sum->len, curr_sum->sum, best_sum);
    }
}

void dump_max_sum_subseq(ArrayAndSize* array, SubsequenceInfo info){
    for(size_t i = info.start; i < info.len + info.start; i++){
        printf("%d ", array->array[i]);
    }
    printf("\n");
}