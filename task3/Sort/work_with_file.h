//! @file
#ifndef WORK_WITH_FILE_H
#define WORK_WITH_FILE_H
#include <sys/stat.h>
#include "structures_consts.h"

//! @brief Reads a file and puts it's content into array
//!
//! The function reads all file's content into a buffer,
//!     created by using ^calloc function,
//!     replaces newline characters with null terminators,
//!     and calls function to count amount of strings
//!
//! ^Creates a buffer with 1 extra byte compared to the file size for safety
//!
//! @return file_in_array structure containing:
//!     - all_strings_in_file: pointer to buffer with file content (strings separated by '\0')
//!     - amount_str: number of lines in the file
//!
//! @note Allocated memory must be freed by the caller
//! @warning Function uses assert for pointer name_of_file
//! @warning Function checks file status using fstat to get file size in bytes.
//!          If fstat fails, error message is printed to stderr and program exit with EXIT_FAILURE
file_in_array read_file_to_string_array(const char *name_of_file);

//! @brief Validates stat() operation and if success put information to all_info_about_file
//!
//! This function checks the correctness of the stat() system call execution.
//! If successful, it populates the provided stat structure to all_info_about_file.
//! On failure, it outputs detailed error information to stderr.
bool incorr_work_with_stat(const char *name_of_file, struct stat *all_info_about_file);

//! Counts the number of substrings separated by a specified delimiter character
//!
//! @param [in] array_to_search Pointer to the null-terminated character array to find amount of strings
//! @param [in] ch Delimiter character used to separate substrings
//!
//! @return Number of substrings found (always at least 1, since even an empty string
//!         or string without delimiters counts as one substring)
//!
//! @warning The function modifies the input array in place by replacing delimiters
//!          with null characters ('\0'). Make sure to work on a copy if the original
//!          data needs to be preserved.
int count_strings_by_symbols(char *array_to_search, char ch);

//! Writes sorted Onegin lines to a file in append mode
//!
//! Appends sorted string array to the specified file using "a+" mode.
//!
//! The function iterates through each string pointer in the array,
//! accessing every element-string and writing its content to the file.
//!
//! The function preserves existing null terminators in strings and
//! adds newline characters at the end of each line.
//!
//! @note Skips empty strings (starting with '\0' or '\n')
//! @note Adds an extra newline at the end for separation
//!
//! @warning Function uses assert for all pointers
void put_sorted_text_to_file(const char *name_of_file, ptr_array_and_size_of_strings *arr, const size_t *amount_str);


#endif // WORK_WITH_FILE_H