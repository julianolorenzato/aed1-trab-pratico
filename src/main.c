#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define MATRIX_SIZE 700
#define NON_ZEROED_PERCENT 2

// TESTE 1
// int main(void)
// {
//     /* Inicializacao da aplicacao ... */
//     time_t begin = time(NULL);
//     Matrix *A = matrix_create();
//     matrix_print(A);
//     Matrix *B = matrix_create();
//     matrix_print(B);
//     Matrix *C = matrix_add(A, B);
//     matrix_print(C);
//     matrix_destroy(C);
//     C = matrix_multiply(A, B);
//     matrix_print(C);
//     matrix_destroy(C);
//     C = matrix_transpose(A);
//     matrix_print(C);
//     matrix_destroy(C);
//     matrix_destroy(A);
//     matrix_destroy(B);

//     time_t end = time(NULL);

//     printf("tempo de execução: %d\n", begin - end);

//     return 0;
// }

// TESTE 2
Matrix *giant_matrix_create(unsigned int m)
{
    // Célula origem da matriz.
    Matrix *origin = (Matrix *)malloc(sizeof(Matrix));

    insert_headers(origin, m, m);

    float new_cell_info;
    srand((unsigned)time(NULL));

    for (unsigned int i = 1; i <= m; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
        {
            new_cell_info = (float)(rand() % 100);

            if (new_cell_info > NON_ZEROED_PERCENT)
            {
                new_cell_info = 0;
            }

            if (new_cell_info == 0)
                continue;

            insert_cell(origin, i, j, new_cell_info);
        }
    }

    return origin;
}

float **giant_matrix_create_normal(unsigned int size)
{
    srand((unsigned)time(NULL));

    float **matrix = malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(float));
        for (int j = 0; j < size; j++)
        {
            float v = (float)(rand() % 100);

            if (v > NON_ZEROED_PERCENT)
                matrix[i][j] = 0;
            else
                matrix[i][j] = v;
        }
    }

    return matrix;
}

float **matrix_multiply_normal(float **matrix1, float **matrix2, int size)
{
    float **result = malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
    {
        printf("LINHA: %d\n", i);
        result[i] = (float *)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < size; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

void matrix_destroy_normal(float **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

int main(void)
{
    // /* Inicializacao da aplicacao ... */
    printf("proccess id: %d\n", getpid());

    time_t begin = time(NULL);
    float **A = giant_matrix_create_normal(MATRIX_SIZE);
    float **B = giant_matrix_create_normal(MATRIX_SIZE);
    float **C = matrix_multiply_normal(A, B, MATRIX_SIZE);
    matrix_destroy_normal(A, MATRIX_SIZE);
    matrix_destroy_normal(B, MATRIX_SIZE);
    matrix_destroy_normal(C, MATRIX_SIZE);

    // time_t begin = time(NULL);
    // Matrix *A = giant_matrix_create(MATRIX_SIZE);
    // Matrix *B = giant_matrix_create(MATRIX_SIZE);
    // Matrix *C = matrix_multiply(A, B);
    // matrix_destroy(A);
    // matrix_destroy(B);
    // matrix_destroy(C);

    time_t end = time(NULL);

    printf("tempo de execução: %d\n", end - begin);

    return 0;
}