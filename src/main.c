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
    Matrix *m = matrix_create();
    matrix_print(m);
    // printf("       |");
    // test_column_heads(m);
    // printf("\n");
    // test_line_heads(m);
    return 0;
}
