#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "read_program.h"

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
// Creating buffer for reading program info from disk

char* read_stdin_to_string_array(){
    char* buffer = NULL;
    size_t capacity = 0;

    ssize_t len = getline(&buffer, &capacity, stdin);

    if(len == -1){
        free(buffer);
        return NULL;
    }

    return buffer;
}

void buffer_free(char* buffer){
    if(buffer){
        memset(buffer, 0, strlen(buffer));
        free(buffer);
    }
}
