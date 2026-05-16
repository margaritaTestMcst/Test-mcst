#ifndef MATRIX_MULIPLY_H
#define MATRIX_MULIPLY_H

const int MATRIX_SIZE = 100;

void init_matr(int (*A)[MATRIX_SIZE], int (*B)[MATRIX_SIZE], int (*C)[MATRIX_SIZE]);
void matrix_multiply(int (*A)[MATRIX_SIZE], int (*B)[MATRIX_SIZE], int (*C)[MATRIX_SIZE]);

#endif //MATRIX_MULIPLY_H