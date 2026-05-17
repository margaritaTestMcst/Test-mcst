#include "file_work.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void copy_to_process_file(int src_file, const char* dst){
    int dst_fp = open(dst, O_WRONLY);
    if(dst_fp == -1){
        fprintf(stderr, "Can't open file for write\n");
        return;
    }

    char* tmp_buf = (char*)calloc(PART_SIZE, sizeof(char));
    off_t offset = 0;
    int symb_read = pread(src_file, tmp_buf, PART_SIZE, offset);

    while(symb_read){
        write(dst_fp, tmp_buf, symb_read);

        offset+=symb_read;
        symb_read = pread(src_file, tmp_buf, PART_SIZE, offset);
    }

    free(tmp_buf);
    close(dst_fp);

}

void put_result_so_stdout(const char* str, const char* src){
    int src_file = open(src, O_RDONLY);
    if(src_file == -1){
        fprintf(stderr, "Can't open file for read\n");
        return;
    }

    printf("%s:\n", str);
    char* tmp_buf = (char*)calloc(PART_SIZE, sizeof(char));
    int symb_read = read(src_file, tmp_buf, PART_SIZE);

    while(symb_read){
        write(STDOUT_FILENO, tmp_buf, symb_read);

        symb_read = read(src_file, tmp_buf, PART_SIZE);
    }

    free(tmp_buf);
    close(src_file);

}