#include "matrix.h"
#include <stdio.h>

// Função de debug (apagar antes de enviar)
void test_column_heads(Matrix *origin) {
    Matrix *curr = origin;
    while (curr->right != origin)
    {
        curr = curr->right;
        printf(" %d %d |", curr->line, curr->column);
    }
    
}

// Função de debug (apagar antes de enviar)
void test_line_heads(Matrix *origin) {
    Matrix *curr = origin;
    while (curr->below != origin)
    {
        curr = curr->below;
        printf(" %d %d |\n", curr->line, curr->column);
    }
    
}

int main()
{
    Matrix *A = matrix_create();
    matrix_print(A);
    Matrix *B = matrix_create();
    matrix_print(B);
    Matrix *C = matrix_add(A, B);
    matrix_print(C);
    matrix_destroy(C);
    matrix_destroy(A);
    matrix_destroy(B);
    return 0;
}
