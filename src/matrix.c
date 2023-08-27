#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Funções de utilidade
int count_lines(Matrix *m);
int count_columns(Matrix *m);
void insert_headers(Matrix *origin, int lines, int columns);
void insert_cell(Matrix *origin, int line, int column, float info);
Matrix *getprev_col(Matrix *origin, int x, int y);
Matrix *getprev_line(Matrix *origin, int x, int y);

Matrix *matrix_create(void)
{
    int lines, columns;
    scanf("%d %d", &lines, &columns);

    // Célula origem da matriz.
    Matrix *origin = (Matrix *)malloc(sizeof(Matrix));

    insert_headers(origin, lines, columns);

    while (1)
    {
        int new_cell_line, new_cell_column;
        float new_cell_info;

        scanf("%d", &new_cell_line);
        if (new_cell_line == 0)
            break;

        scanf(" %d %f", &new_cell_column, &new_cell_info);
        if (new_cell_info == 0)
            continue;

        insert_cell(origin, new_cell_line, new_cell_column, new_cell_info);
    }

    return origin;
}

void matrix_destroy(Matrix *m)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return;
    }

    int lines = count_lines(m);
    int columns = count_columns(m);

    // Libera as células de dentro da matriz
    Matrix *line_head = m;
    for (int i = 0; i < lines; i++)
    {
        line_head = line_head->below;

        Matrix *iterator = line_head->right;
        while (iterator != line_head)
        {
            Matrix *temp = iterator;
            iterator = iterator->right;
            free(temp);
        }
    }

    // Libera as cabeças de linhas
    Matrix *curr = m->below;
    for (int i = 0; i < lines; i++)
    {
        Matrix *temp = curr;
        curr = curr->below;
        free(temp);
    }

    // Libera as cabeças de colunas
    curr = m->right;
    for (int i = 0; i < columns; i++)
    {
        Matrix *temp = curr;
        curr = curr->right;
        free(temp);
    }

    // Libera a célula origem
    free(m);
}

void matrix_print(Matrix *m)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return;
    }

    int lines = count_lines(m);
    int columns = count_columns(m);

    printf("%d %d\n", lines, columns);

    // Percorre as cabeças das linhas
    Matrix *line_head = m;
    for (int i = 0; i < lines; i++)
    {
        line_head = line_head->below;

        // Percorre todas as celulas não zeradas de cada linha
        Matrix *iterator = line_head->right;
        while (iterator != line_head)
        {
            printf("%d %d %.1f\n", iterator->line, iterator->column, iterator->info);
            iterator = iterator->right;
        }
    }

    printf("0\n");
}

Matrix *matrix_add(Matrix *m, Matrix *n)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return NULL;
    }

    if (n == NULL)
    {
        printf("Matriz n nao pode ser nula\n");
        return NULL;
    }

    int lines_m = count_lines(m);
    int columns_m = count_columns(m);

    int lines_n = count_lines(n);
    int columns_n = count_columns(n);

    if (lines_m != lines_n || columns_m != columns_n)
    {
        printf("As matrizes devem ter as mesmas dimensoes\n");
        return NULL;
    }

    Matrix *res = (Matrix *)malloc(sizeof(Matrix));

    insert_headers(res, lines_m, columns_m);

    Matrix *line_head_m = m;
    Matrix *line_head_n = n;
    for (int i = 1; i <= lines_m; i++)
    {
        line_head_m = line_head_m->below;
        line_head_n = line_head_n->below;

        Matrix *iterator_m = line_head_m;
        Matrix *iterator_n = line_head_n;
        for (int j = 1; j <= columns_m; j++)
        {
            float info = 0;

            if (iterator_m->right->column == j)
            {
                info += iterator_m->right->info;
                iterator_m = iterator_m->right;
            }

            if (iterator_n->right->column == j)
            {
                info += iterator_n->right->info;
                iterator_n = iterator_n->right;
            }

            if (info != 0)
            {
                insert_cell(res, i, j, info);
            }
        }
    }

    return res;
}

Matrix *matrix_multiply(Matrix *m, Matrix *n)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return NULL;
    }

    if (n == NULL)
    {
        printf("Matriz n nao pode ser nula\n");
        return NULL;
    }

    int lines_m = count_lines(m);
    int columns_m = count_columns(m);

    int lines_n = count_lines(n);
    int columns_n = count_columns(n);

    if (columns_m != lines_n)
    {
        printf("O numero de colunas da primeira matriz deve ser igual ao numero de linhas da segunda matriz\n");
        return NULL;
    }

    Matrix *res = (Matrix *)malloc(sizeof(Matrix));

    insert_headers(res, lines_m, columns_n);

    // Percorre todas as linhas da matriz resultante
    for (int line = 1; line <= lines_m; line++)
    {
        printf("LINHA: %d\n", line);
        // Percorre todas as colunas da matriz resultante
        for (int col = 1; col <= columns_n; col++)
        {
            float res_info = 0;

            // Para cada celula da matriz resultante soma os produtos das linhas da matriz m com as colunas da matriz n
            for (int k = 1; k <= columns_m /* poderia ser lines_n aqui pois é igual */; k++)
            {
                float elem1 = matrix_getelem(m, line, k);
                float elem2 = matrix_getelem(n, k, col);

                res_info += elem1 * elem2;
            }

            if (res_info != 0)
            {
                insert_cell(res, line, col, res_info);
            }
        }
    }

    return res;
}

Matrix *matrix_transpose(Matrix *m)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return NULL;
    }

    int col = count_lines(m);
    int lines = count_columns(m);

    Matrix *line_head, *iterator, *transposta = malloc(sizeof(Matrix));
    insert_headers(transposta, lines, col);

    line_head = m;
    for (int i = 0; i < lines; i++)
    {
        line_head = line_head->below;

        // Percorre todas as celulas não zeradas de cada linha
        iterator = line_head->right;
        while (iterator != line_head)
        {
            matrix_setelem(transposta, iterator->column, iterator->line, iterator->info);
            iterator = iterator->right;
        }
    }
    return transposta;
}

float matrix_getelem(Matrix *m, int x, int y)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return 0;
    }

    for (int i = 0; i < x; i++)
    {
        m = m->below;
    }

    while ((m->right->column != -1 && m->right->line != -1) || m->right->column > x)
    {
        m = m->right;
        if (m->column == y)
        {
            return m->info;
        }
    }

    return 0.0;
}

void matrix_setelem(Matrix *m, int line, int column, float elem)
{
    if (m == NULL)
    {
        printf("Matriz m nao pode ser nula\n");
        return;
    }

    Matrix *aux, *prev_col, *prev_line;
    aux = m;

    for (int i = 0; i < line; i++)
    {
        aux = aux->below;
    }

    while ((aux->right->column != -1 && aux->right->line != -1) || aux->right->column > line)
    {
        aux = aux->right;
        if (aux->column == column)
        {
            break;
        }
    }

    if (aux->column == column && aux->line == line)
    {
        // Se encontrar a célula e o valor a ser colocado for 0 a célula será destruída
        if (elem == 0)
        {
            prev_col = getprev_col(m, line, column);
            prev_line = getprev_line(m, line, column);
            aux = prev_line->right;

            prev_col->below = aux->below;
            prev_line->right = aux->right;

            free(aux);
        }
        else
        {
            aux->info = elem;
        }
        return;
    }

    if (elem != 0)
    {
        insert_cell(m, line, column, elem);
    }
}

// ------------------------- Funções de utilidade -------------------------

int count_lines(Matrix *m)
{
    int lines = 0;

    Matrix *curr = m;
    while (curr->below != m)
    {
        curr = curr->below;
        lines++;
    }

    return lines;
}

int count_columns(Matrix *m)
{
    int columns = 0;

    Matrix *curr = m;
    while (curr->right != m)
    {
        curr = curr->right;
        columns++;
    }

    return columns;
}

void insert_headers(Matrix *origin, int lines, int columns)
{
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
}

// Deve ser usada em uma matrix com headers já inseridos
void insert_cell(Matrix *origin, int line, int column, float info)
{
    Matrix *cell = (Matrix *)malloc(sizeof(Matrix));
    cell->line = line;
    cell->column = column;
    cell->info = info;

    Matrix *curr_line = getprev_line(origin, line, column);

    Matrix *curr_col = getprev_col(origin, line, column);

    // Adiciona a nova celula no meio da linha
    Matrix *temp = curr_line->right;
    curr_line->right = cell;
    cell->right = temp;

    // Adiciona a nova célula no meio da coluna.
    temp = curr_col->below;
    curr_col->below = cell;
    cell->below = temp;
}

Matrix *getprev_col(Matrix *origin, int line, int column)
{
    // Muda a posição de curr_col para a direita até chegar na coluna específica.
    Matrix *curr_col = origin;
    for (int i = 0; i < column; i++)
    {
        curr_col = curr_col->right;
    }
    // Muda a posição de curr_col para baixo enquanto o próximo não é uma cabeça ou o próximo é uma linha maior que o alvo.
    while ((curr_col->below->column != -1 && curr_col->below->line != -1) || curr_col->below->line >= line)
    {
        if (curr_col->below->line == line && curr_col->below->column == column)
        {
            break;
        }
        curr_col = curr_col->below;
    }
    return curr_col;
}

// Retorna a celula anterior na linha em relação a posição especificada
Matrix *getprev_line(Matrix *origin, int line, int column)
{
    // Muda a posição de curr_line para baixo até chegar na linha especifica.
    Matrix *curr_line = origin;
    for (int i = 0; i < line; i++)
    {
        curr_line = curr_line->below;
    }

    // Muda a posição de curr_line para a direita enquanto o próximo não é uma cabeça ou o próximo é uma coluna maior que o alvo.
    while ((curr_line->right->column != -1 && curr_line->right->line != -1) || curr_line->right->column >= column)
    {
        if (curr_line->right->line == line && curr_line->right->column == column)
        {
            break;
        }
        curr_line = curr_line->right;
    }
    return curr_line;
}
