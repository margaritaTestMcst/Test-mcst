#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "file_work/file_work.h"

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Usage: <program> <file_path>\n");
        return 1;
    }

    int read_fp = open(argv[1], O_RDONLY);
    if(read_fp == -1){
        fprintf(stderr, "Can't open file for reading\n");
        return 0;
    }

    pid_t child_pid = fork();
    if(child_pid == -1){
        fprintf(stderr, "Can't create child process\n");
        return 0;
    }

    if(child_pid == 0){
        copy_to_process_file(read_fp, "child_copy");
        close(read_fp);
        exit(0);
    }
    else{
        copy_to_process_file(read_fp, "parent_copy");
        close(read_fp);

        int status = 0;
        waitpid(child_pid, &status, 0); 

        put_result_so_stdout("Parent", "parent_copy");
        put_result_so_stdout("Child", "child_copy");
    }
    
}