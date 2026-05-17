#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "assert_without_ndebug.h"
#include "structures_consts.h"

int count_strings_by_symbols(char *array_to_search, char ch)
{
    MY_ASSERT_WTHOUT_NDEBUG(array_to_search != NULL);

    int count_str = 1;

    while ((array_to_search = strchr(array_to_search, ch)) != NULL)
    {
        count_str++;
        *(array_to_search) = '\0';
        array_to_search++;
    }

    return count_str;
}

bool incorr_work_with_stat(const char *name_of_file, struct stat *all_info_about_file)
{
    MY_ASSERT_WTHOUT_NDEBUG(name_of_file != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(all_info_about_file != NULL);

    if (stat(name_of_file, all_info_about_file) == -1)
    {
        perror("Stat error");
        fprintf(stderr, "Error code: %d\n", errno);
        return true;
    }
    return false;
}

file_in_array read_file_to_string_array(const char *name_of_file)
{
    MY_ASSERT_WTHOUT_NDEBUG(name_of_file != NULL);
    file_in_array fptr_in_array = {};
    FILE *fptr = fopen(name_of_file, "r");
    MY_ASSERT_WTHOUT_NDEBUG(fptr != NULL);

    struct stat file_info = {};
    fptr_in_array.is_stat_err = incorr_work_with_stat(name_of_file, &(file_info));
    if (fptr_in_array.is_stat_err)
    {
        return fptr_in_array;
    }

    char *all_strings_in_file = (char *)calloc(file_info.st_size + 1, sizeof(char));
    MY_ASSERT_WTHOUT_NDEBUG(all_strings_in_file != NULL);

    MY_ASSERT_WTHOUT_NDEBUG(fread(all_strings_in_file, sizeof(char), file_info.st_size, fptr) == file_info.st_size);

    char *search_ptr = all_strings_in_file;

    int nmb_of_str = count_strings_by_symbols(search_ptr, '\n');

    fptr_in_array.amount_str = nmb_of_str;
    fptr_in_array.all_strings_in_file = all_strings_in_file;

    fclose(fptr);
    return fptr_in_array;
}

void put_sorted_text_to_file(const char *name_of_file, ptr_array_and_size_of_strings *arr, const size_t *amount_str)
{
    MY_ASSERT_WTHOUT_NDEBUG(arr != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(name_of_file != NULL);
    MY_ASSERT_WTHOUT_NDEBUG(amount_str != NULL);

    FILE *fptr = fopen(name_of_file, "a+");
    MY_ASSERT_WTHOUT_NDEBUG(fptr != NULL);

    for (int string = 0; string < *amount_str; string++)
    {
        if (arr[string].ptr[0] != '\0' && arr[string].ptr[0] != '\n')
        {
            fputs(arr[string].ptr, fptr);
            fputs("\n", fptr);
        }
    }
    fclose(fptr);
}
