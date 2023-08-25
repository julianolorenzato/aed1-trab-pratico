#include "matrix.h"
#include <stdio.h>

// Função de debug (apagar antes de enviar)
void test_column_heads(Matrix *origin)
{
    Matrix *curr = origin;
    while (curr->right != origin)
    {
        curr = curr->right;
        printf(" %d %d |", curr->line, curr->column);
    }
}

// Função de debug (apagar antes de enviar)
void test_line_heads(Matrix *origin)
{
    Matrix *curr = origin;
    while (curr->below != origin)
    {
        curr = curr->below;
        printf(" %d %d |\n", curr->line, curr->column);
    }
}

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
    Matrix *m;
    m = matrix_create();
    matrix_setelem(m, 1, 2, 1);
    matrix_setelem(m, 2, 2, 2);
    matrix_setelem(m, 3, 2, 3);
    matrix_setelem(m, 1, 1, 4);
    matrix_setelem(m, 3, 1, 5);
    matrix_setelem(m, 3, 1, 6);
    matrix_setelem(m, 3, 1, 0);
    matrix_print(m);

    return 0;
}
