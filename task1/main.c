#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Array/array_and_size.h"
#include "Threads/threads.h"

bool ParseCmdlineArg(char* arg, long* value);

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Incorrect data format: expected <program name> <num of threads>\n");
        return 0;
    }

    ArrayAndSize* array = ArrayAndSizeCtor();
    if(!array) return 0;

    long threads_wanted = 0;
    ParseCmdlineArg(argv[2], &threads_wanted);

    int threads = ChooseNumOfThreads(array, threads_wanted);

}

bool ParseCmdlineArg(char* arg, long* value){
    assert(arg);
    assert(value);
    char* endptr = NULL;

    long x = strtol(arg, &endptr, 10);

    if(endptr==arg){
        fprintf(stderr, "Error: not a number\n");
        return false;
    }

    if(*endptr != '\0'){
        fprintf(stderr, "Error: invalid characters after number\n");
        return false;
    }

    return true;

}