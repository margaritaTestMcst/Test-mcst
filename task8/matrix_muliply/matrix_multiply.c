#include "matrix_multiply.h"
#include "../sigint_handlers/handlers.h"
#include <unistd.h>

void init_matr(int (*A)[MATRIX_SIZE], int (*B)[MATRIX_SIZE], int (*C)[MATRIX_SIZE]){
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            A[i][j] = 100;
            B[i][j] = 100;
        }
    }
}

void matrix_multiply(int (*A)[MATRIX_SIZE], int (*B)[MATRIX_SIZE], int (*C)[MATRIX_SIZE]){
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            for(int k = 0; k < MATRIX_SIZE; k++){
                update_idx(i, j, k);

                C[i][j] += A[i][k] * B[k][j];

                usleep(500000);
            }
        }
    }
}