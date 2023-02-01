#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define INCORRECT_MATRIX 1
#define WRONG_OPERATION 2

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int main() {
    printf("Hello, World!\n");
    return 0;
}

// https://learnc.info/c/fast_array_allocation.html

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int res = OK;
    result->rows = rows;
    result->columns = columns;
    if (rows > 0 && columns > 0) {
        result->matrix = (double**) malloc(rows*sizeof(double *) + rows*columns*sizeof(double));
        result->matrix[0] = (double *)(result->matrix + rows);
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
        free(A->matrix);
        A->matrix = NULL;
    }
}