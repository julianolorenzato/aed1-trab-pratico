#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Função auxiliar para percorrer a matriz (não foi pedida, mas foi criada pra reusar o código)
Matrix *get_cell(Matrix *origin, int line, int column)
{
    Matrix *curr = origin;

    // Vai ate a linha especifica;
    for (int i = 0; i < line; i++)
    {
        curr = curr->below;
    }

    // Vai ate a coluna especifica;
    for (int i = 0; i < column; i++)
    {
        curr = curr->right;
    }

    return curr;
}

Matrix *matrix_create(void)
{
    int lines, columns;
    scanf("%d %d", &lines, &columns);

    // Célula origem da matriz.
    Matrix *origin = (Matrix *)malloc(sizeof(Matrix));

    // Para cada linha, cria uma nova célula de cabeça (com campos line e column iguais a -1),
    // que é colocada abaixo da celula anterior (partindo da origem).
    Matrix *curr = origin;
    for (int i = 0; i < lines; i++)
    {
        Matrix *new_cell = (Matrix *)malloc(sizeof(Matrix));
        new_cell->line = -1;
        new_cell->column = -1;

        curr->below = new_cell;
        curr = new_cell;
        new_cell->right = new_cell;
    }

    // Finaliza conectando a última célula de cabeça das linhas à celula origem (criando um ciclo).
    curr->below = origin;

    // Para cada coluna, cria uma nova célula de cabeça (com campos line e column iguais a -1),
    // que é colocada à direita da celula anterior (partindo da origem).
    curr = origin;
    for (int i = 0; i < columns; i++)
    {
        Matrix *new_cell = (Matrix *)malloc(sizeof(Matrix));
        new_cell->line = -1;
        new_cell->column = -1;

        curr->right = new_cell;
        curr = new_cell;
        new_cell->below = new_cell;
    }

    // Finaliza conectando a última célula de cabeça das colunas à celula origem (criando um ciclo).
    curr->right = origin;

    while (1)
    {
        Matrix *cell = (Matrix *)malloc(sizeof(Matrix));
        scanf("%d %d %f", &cell->line, &cell->line, &cell->info);

        if (cell->line == 0)
        {
            free(cell);
            break;
        }

        Matrix *curr_line = origin;
        for (int i = 0; i < cell->line; i++)
        {
            curr_line = curr_line->below;
        }

        // Muda a posição de curr_line para a direita enquanto o próximo não é uma cabeça ou o próximo é uma coluna maior que o alvo.
        while ((curr_line->right->column != -1 && curr_line->right->line != -1) || curr_line->right->column > cell->column)
        {
            curr_line = curr_line->right;
        }

        Matrix *curr_col = origin;
        for (int i = 0; i < cell->column; i++)
        {
            curr_col = curr_col->right;
        }

        // Muda a posição de curr_col para baixo enquanto o próximo não é uma cabeça ou o próximo é uma linha maior que o alvo.
        while ((curr_col->below->column != -1 && curr_col->below->line != -1) || curr_col->below->line > cell->line)
        {
            curr_col = curr_col->below;
        }
        
        Matrix *temp = curr_line->right;
        curr_line->right = cell;
        cell->right = temp;

        temp = curr_col->below;
        curr_col->below = cell;
        cell->below = temp;
    }
}