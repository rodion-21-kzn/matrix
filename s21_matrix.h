//
// Created by Oznak Banshee on 2/4/23.
//

#ifndef MATRIX_S21_MATRIX_H
#define MATRIX_S21_MATRIX_H

#define OK 0
#define INCORRECT_MATRIX 1
#define WRONG_OPERATION 2

#define SUCCESS 1
#define FAILURE 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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

#endif //MATRIX_S21_MATRIX_H
