#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "assert_without_ndebug.h"
#include "structures_consts.h"
#include "swap_func.h"

ptr_array_and_size_of_strings *create_ptr_array(file_in_array *arr)
{
    MY_ASSERT_WTHOUT_NDEBUG(arr != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(arr->all_strings_in_file != NULL);

    ptr_array_and_size_of_strings *arr_with_ptr_sz =
        calloc(arr->amount_str, sizeof(ptr_array_and_size_of_strings));

    MY_ASSERT_WTHOUT_NDEBUG(arr_with_ptr_sz != NULL);

    char *search_ptr = arr->all_strings_in_file;

    for (size_t num_of_elem = 0; num_of_elem < arr->amount_str; num_of_elem++)
    {
        size_t len = strlen(search_ptr) + 1;

        arr_with_ptr_sz[num_of_elem].ptr = search_ptr;
        arr_with_ptr_sz[num_of_elem].str_size = len;

        search_ptr += len;
    }

    return arr_with_ptr_sz;
}

char my_tolower(char ch)
{
    return ('A' <= ch && ch <= 'Z') ? ch + ('a' - 'A') : ch;
}

bool my_isalpha(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

int compare_strings_from_beginning(const char *str1, const char *str2)
{
    MY_ASSERT_WTHOUT_NDEBUG(str1 != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(str2 != NULL);

    int idx1 = 0;

    int idx2 = 0;

    char char1 = '\0';
    char char2 = '\0';

    while (str1[idx1] != '\0' && str2[idx2] != '\0')
    {
        char1 = my_tolower(str1[idx1]);
        char2 = my_tolower(str2[idx2]);

        if (char1 != char2)
            return char1 - char2;

        idx1++;
        idx2++;
    }

    return my_tolower(str1[idx1]) - my_tolower(str2[idx2]);
}

int compare_strings_from_end(const char *str1, const char *str2)
{
    return -compare_strings_from_beginning(str1, str2);
}

int compare_plain(const char *str1, const char *str2)
{
    return strcmp(str1, str2);
}

int compare_rplain(const char *str1, const char *str2)
{
    return -strcmp(str1, str2);
}

void sort_array_set_by_ptr2arr(ptr_array_and_size_of_strings *arr, const size_t *strings, int (*how_to_compare)(const char *, const char *))
{
    MY_ASSERT_WTHOUT_NDEBUG(arr != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(strings != NULL);

    int left = 0, right = *strings - 1;
    bool is_elem_to_sort = 1;

    while (left < right && is_elem_to_sort)
    {
        is_elem_to_sort = 0;

        for (int string = left; string < right; string++)
        {
            if (how_to_compare((const char *)arr[string].ptr,
                               (const char *)arr[string + 1].ptr) > 0)
            {
                swap_structures(&arr[string], &arr[string + 1]);
                is_elem_to_sort = 1;
            }
        }
        right--;

        for (int string = right; string > left; string--)
        {
            if (how_to_compare((const char *)arr[string - 1].ptr,
                               (const char *)arr[string].ptr) > 0)
            {
                swap_structures(&arr[string - 1], &arr[string]);
                is_elem_to_sort = 1;
            }
        }
        left++;
    }
}

void free_memory(ptr_array_and_size_of_strings *arr, file_in_array *array_for_size)
{
    MY_ASSERT_WTHOUT_NDEBUG(arr != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(array_for_size != NULL);

    free(arr);
    free(array_for_size->all_strings_in_file);
}