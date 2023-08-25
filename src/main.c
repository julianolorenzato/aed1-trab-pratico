#include "matrix.h"
#include <stdio.h>

// int main()
// {
//     // Matrix *A = matrix_create();
//     // matrix_print(A);
//     // Matrix *B = matrix_create();
//     // matrix_print(B);
//     // Matrix *C = matrix_add(A, B);
//     // matrix_print(C);
//     // matrix_destroy(C);
//     // matrix_destroy(A);
//     // matrix_destroy(B);

//     Matrix *A = matrix_create();
//     matrix_print(A);
//     Matrix *B = matrix_create();
//     matrix_print(B);

//     Matrix *C = matrix_multiply(A, B);
//     matrix_print(C);

//     matrix_destroy(A);
//     matrix_destroy(B);
//     matrix_destroy(C);
//     return 0;
// }

int main()
{
    Matrix *A, *B;
    A = matrix_create();
    B = matrix_create();
    Matrix *C = matrix_multiply(A, B);
    matrix_print(C);
    matrix_destroy(A);
    matrix_destroy(B);
    matrix_destroy(C);

    return 0;
}
