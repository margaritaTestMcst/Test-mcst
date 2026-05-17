#include "matrix_multiply/matrix_multiply.h"
#include "sigint_handlers/handlers.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
    if(argc != 2 || !choose_handler_mode(argv[1])){
        fprintf(stderr, "<program> <sigaction/signal> expected\n");
        return 0;
    }

    int (*A)[MATRIX_SIZE] = calloc(MATRIX_SIZE, sizeof(*A));
    if(!A) return 0;

    int (*B)[MATRIX_SIZE] = calloc(MATRIX_SIZE, sizeof(*B));
    if(!B){
        free(A);
        return 0;
    }

    int (*C)[MATRIX_SIZE] = calloc(MATRIX_SIZE, sizeof(*C));
    if(!C){
        free(A);
        free(B);
        return 0;
    }

    fill_matr(A, B, C);
    matrix_multiply(A, B, C);

    free(A);
    free(B);
    free(C);
}