#ifndef ALGO_SRC
#define ALGO_SRC

#include <bsd/stdlib.h>
#include "../Array/array_and_size.h"

struct SubsequenceInfo {
    size_t start;
    size_t len;
    int sum;
};

SubsequenceInfo create_subseq_info(size_t start, size_t len, int sum);

void find_max_sum_subseq(ArrayAndSize* array, SubsequenceInfo* curr_sum, SubsequenceInfo* best_sum);

void dump_max_sum_subseq(ArrayAndSize* array, SubsequenceInfo info);

#endif //ALGO_SRC