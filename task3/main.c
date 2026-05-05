#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Sort/structures_consts.h"
#include "Sort/work_with_file.h"
#include "Sort/functions_for_sort.h"

int choose_comparator(const char* cmp_mode);

int main(int argc, const char *const *const argv)
{
    if(argc != 4){
        fprintf(stderr, "Incorrect data format: expected <program name> <input_file><output_file><type>\n");
        return 0;
    }

    file_in_array info = read_file_to_string_array(argv[1]);
    if (!info.is_stat_err)
    {
        ptr_array_and_size_of_strings *array = create_ptr_array(&info);

        int sorting_mode = choose_comparator(argv[3]);
        if(sorting_mode == INT_MAX){
            fprintf(stderr, "Incorrect comparator, avaliable: plain, rplain, lex, rlex\n");
            free_memory(array, &info);
            return 0;
        }

        sort_array_set_by_ptr2arr(array, &(info.amount_str), comparators[sorting_mode]);
        put_sorted_text_to_file(argv[2], array, &(info.amount_str));

        free_memory(array, &info);
    }

    return 0;
}

int choose_comparator(const char* cmp_mode){
    if(!cmp_mode) return INT_MAX;

    if(!strcmp(cmp_mode, "plain"))  return CMP_PLAIN;
    if(!strcmp(cmp_mode, "rplain")) return CMP_RPLAIN;
    if(!strcmp(cmp_mode, "lex"))    return CMP_LEX;
    if(!strcmp(cmp_mode, "rlex"))   return CMP_RLEX;

    return INT_MAX;
}