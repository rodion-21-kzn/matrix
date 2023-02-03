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

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

void s21_fill_minor(matrix_t *A, matrix_t *minors, int delete_row, int delete_column);

double s21_count_determinant_2x(matrix_t *minors);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);


int main() {
    int rows = 3;
    int columns = 3;
    double determ = 0;
    matrix_t temp;
    matrix_t matrix3;
    s21_create_matrix (rows, columns, &temp);
    s21_input_matrix(&temp);
    s21_inverse_matrix(&temp,&matrix3);
    s21_print_matrix(&matrix3);
    return 0;
}

// https://learnc.info/c/fast_array_allocation.html

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
        res = INCORRECT_MATRIX;
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

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (result->matrix == NULL) s21_create_matrix(A->rows,A->columns,result);
    if (s21_correct_matrix (A) == INCORRECT_MATRIX || s21_correct_matrix (B) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
        res = WRONG_OPERATION;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int k = 0; k < A->columns; k++) {
                result->matrix[i][k] = A->matrix[i][k] + B->matrix[i][k];
            }
        }
    }
    return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (result->matrix == NULL) s21_create_matrix(A->rows,A->columns,result);
    if (s21_correct_matrix (A) == INCORRECT_MATRIX || s21_correct_matrix (B) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
        res = WRONG_OPERATION;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int k = 0; k < A->columns; k++) {
                result->matrix[i][k] = A->matrix[i][k] - B->matrix[i][k];
            }
        }
    }
    return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int res = OK;
    if (result->matrix == NULL) s21_create_matrix(A->rows,A->columns,result);
    if (s21_correct_matrix (A) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int k = 0; k < A->columns; k++) {
                result->matrix[i][k] = A->matrix[i][k] * number;
            }
        }
    }
    return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = OK;
    if (s21_correct_matrix (A) == INCORRECT_MATRIX || s21_correct_matrix (B) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else if (A->columns != B->rows) {
        res = WRONG_OPERATION;
    } else {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                for (int k = 0; k < B->rows; k++ ) {
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int res = OK;
    if (s21_correct_matrix (A) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    }
    return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int res = OK;
    if (s21_correct_matrix (A) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                matrix_t minors;
                double determinant = 0;
                double complement = 0;
                s21_create_matrix(A->rows-1, A->columns-1, &minors);
                s21_fill_minor(A, &minors, i, j);
                s21_determinant(&minors, &determinant);
                complement = determinant * pow(-1,i+j);
                result->matrix[i][j] = complement;
                s21_remove_matrix(&minors);
            }
        }
    }
    return res;
}

int s21_determinant(matrix_t *A, double *result) {
    int res = OK;
    *result = 0;
    if (s21_correct_matrix (A) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else if (A->rows == 1) {
        *result = A->matrix[0][0];
    } else if (A->rows == 2) {
        *result = s21_count_determinant_2x(A);
    } else {
        for (int i = 0; i < A->columns; i++) {
            matrix_t minors;
            double determinant = 0;
            s21_create_matrix(A->rows-1, A->columns-1, &minors);
            s21_fill_minor(A, &minors, 0, i);
            s21_determinant(&minors,&determinant);
            *result = *result + (A->matrix[0][i] * determinant * pow(-1,i));
            s21_remove_matrix(&minors);
        }
    }
    return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int res = OK;
    double determinant = 0;
    s21_determinant(A,&determinant);
    if (s21_correct_matrix (A) == INCORRECT_MATRIX) {
        res = INCORRECT_MATRIX;
    } else if (determinant == 0) {
        res = WRONG_OPERATION;
    } else {
        matrix_t inverse;
        s21_create_matrix(A->rows, A->columns, &inverse);
        s21_calc_complements(A,result);
        s21_transpose(result, &inverse);
        s21_mult_number(&inverse, 1/determinant, result);
        s21_remove_matrix(&inverse);
    }
}


// support function

double s21_count_determinant_2x(matrix_t *minors) {
    double main_diag = 1;
    double secondary_diag = 1;
    double minor = 0;
    for (int i = 0; i < minors->columns && i < minors->rows; i++) {
        main_diag *= minors->matrix[i][i];
    }
    for (int i = 0, j = minors->columns - 1; i < minors->rows && j >= 0; i++, j--) {
        secondary_diag *= minors->matrix[i][j];
    }
    minor = main_diag - secondary_diag;
    return minor;
}

void s21_fill_minor(matrix_t *A, matrix_t *minors, int delete_row, int delete_column) {
    int minor_row = 0;
    int minor_column = 0;
    for (int i = 0; i < A->rows; i++ ) {
        for (int j = 0; j < A->columns; j++) {
            if (i != delete_row && j != delete_column) {
                minors->matrix[minor_row][minor_column] = A->matrix[i][j];
                if (minor_column + 1 >= minors->columns) {
                    minor_row++;
                    minor_column = 0;
                } else {
                    minor_column++;
                }
            }
        }
    }
}

void s21_input_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int k = 0; k < matrix->columns; k++) {
            double test = 0;
            scanf("%lf", &test);
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