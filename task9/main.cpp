#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Array/array_and_size.h"
#include "Algo_src/algo_src.h"


int main(){
    ArrayAndSize* array = ArrayAndSizeCtor();
    if(!array) return 0;

    SubsequenceInfo curr_sum = create_subseq_info(0, 1, array->array[0]);
    SubsequenceInfo best_sum = create_subseq_info(0, 1, array->array[0]);
    find_max_sum_subseq(array, &curr_sum, &best_sum);
    dump_max_sum_subseq(array, best_sum);

    ArrayAndSizeDtor(array);
}