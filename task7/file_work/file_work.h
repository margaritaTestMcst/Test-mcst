#ifndef FILE_WORK_H
#define FILE_WORK_H

#define PART_SIZE 1024

void copy_to_process_file(int src_file, const char* dst);

void put_result_so_stdout(const char* str, const char* src);

#endif //FILE_WORK_H