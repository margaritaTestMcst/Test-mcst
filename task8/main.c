#include "matrix_multiply/matrix_multiply.h"
#include "sigint_handlers/handlers.h"
#include <stdio.h>


int main(int argc, char* argv[]){
    if(argc != 2 || !choose_handler_mode(argv[1])){
        fprintf(stderr, "<program> <sigaction/signal> expected");
        return 0;
    }

    int A[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int B[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int C[MATRIX_SIZE][MATRIX_SIZE] = {0};
    fill_matr(A, B, C);
    matrix_multiply(A, B, C);
}