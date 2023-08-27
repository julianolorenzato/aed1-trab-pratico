struct matrix
{
    struct matrix *right;
    struct matrix *below;
    int line;
    int column;
    float info;
};

typedef struct matrix Matrix;

Matrix *matrix_create(void);
void matrix_destroy(Matrix *m);
void matrix_print(Matrix *m);
Matrix *matrix_add(Matrix *m, Matrix *n);
Matrix *matrix_multiply(Matrix *m, Matrix *n);
Matrix *matrix_transpose(Matrix *m);
float matrix_getelem(Matrix *m, int x, int y);
void matrix_setelem(Matrix *m, int x, int y, float elem);

// Funções de utilidade
int count_lines(Matrix *m);
int count_columns(Matrix *m);
void insert_headers(Matrix *origin, int lines, int columns);
void insert_cell(Matrix *origin, int line, int column, float info);
Matrix *getprev_col(Matrix *origin, int x, int y);
Matrix *getprev_line(Matrix *origin, int x, int y);