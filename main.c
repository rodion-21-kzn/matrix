#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define WRONG_OPERATION 2

#define SUCCESS 1
#define FAILURE 0


typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_correct_matrix(matrix_t *matrix);

void s21_input_matrix(matrix_t *matrix);

void s21_print_matrix(matrix_t *matrix);


int main() {
    int rows = 2;
    int columns = 2;
    matrix_t matrix1;
    matrix_t matrix2;
    s21_create_matrix (rows, columns, &matrix1);
    s21_create_matrix (rows, columns, &matrix2);
    s21_input_matrix (&matrix1);
    s21_input_matrix (&matrix2);
    s21_print_matrix (&matrix1);
    s21_print_matrix (&matrix2);
    int x = s21_eq_matrix(&matrix1,&matrix2);
    printf("%d",x);
    s21_remove_matrix (&matrix1);
    s21_remove_matrix (&matrix2);
    return 0;
}

// https://learnc.info/c/fast_array_allocation.html
// проверку на выделение памяти

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int res = OK;
    result->rows = rows;
    result->columns = columns;
    if (rows > 0 && columns > 0) {
        result->matrix = (double **) malloc (rows * sizeof (double *) + rows * columns * sizeof (double));
        result->matrix[0] = (double *) (result->matrix + rows);
        for (int i = 1; i < rows; i++) {
            result->matrix[i] = result->matrix[0] + i * columns;
        }
    } else {
        result->matrix = NULL;
        res = INCORRECT_MATRIX;
    }
    return res;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        free (A->matrix);
        A->matrix = NULL;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = SUCCESS;
    if (s21_correct_matrix (A) == INCORRECT_MATRIX || s21_correct_matrix (B) == INCORRECT_MATRIX) {
        res = FAILURE;
    } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
        res = FAILURE;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int k = 0; k < A->columns; k++) {
                if (fabs (A->matrix[i][k] - B->matrix[i][k]) >= FLT_EPSILON) {
                    res = FAILURE;
                }
            }
        }
    }
    return res;
}

void s21_input_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int k = 0; k < matrix->columns; k++) {
            double test = 0;
            scanf ("%lf", &test);
            matrix->matrix[i][k] = test;
        }
    }
}

void s21_print_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int k = 0; k < matrix->columns; k++) {
            printf ("%20lf", matrix->matrix[i][k]);
        }
        printf ("\n");
    }
}

int s21_correct_matrix(matrix_t *matrix) {
    int res = OK;
    if (matrix == NULL || matrix->columns <= 0 || matrix->rows <= 0 || matrix->matrix == NULL) {
        res = INCORRECT_MATRIX;
    }
    return res;
}