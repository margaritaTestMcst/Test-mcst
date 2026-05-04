#include <stdio.h>
#include <pthread.h>

#include "Array/array_and_size.h"

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Incorrect data format: expected <program name> <num of threads>\n");
        return 0;
    }

    ArrayAndSize* array = ArrayAndSizeCtor();
    if(!array) return 0;

}