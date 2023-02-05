//
// Created by Oznak Banshee on 2/5/23.
//
#include "check.h"
#include "s21_matrix.h"

// CREATION

START_TEST(s21_create_matrix1) {
    matrix_t result = {0};
    ck_assert_int_eq(s21_create_matrix(3, 3, &result), 0);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_create_matrix2) {
    matrix_t result = {0};
    ck_assert_int_eq(s21_create_matrix(3, 0, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_create_matrix3) {
    matrix_t result = {0};
    ck_assert_int_eq(s21_create_matrix(0, 3, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&result);
}
END_TEST

Suite *s21_create_matrix_test(void) {
    Suite *s = suite_create("\033[46m-=s21_create_matrix=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_create_matrix1);
    tcase_add_test(tc, s21_create_matrix2);
    tcase_add_test(tc, s21_create_matrix3);
    suite_add_tcase(s, tc);
    return s;
}

// COMPARING

START_TEST(s21_eq_matrix1) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    A.matrix[0][0] = 1.345678;
    A.matrix[0][1] = 1.345678;
    A.matrix[1][0] = 1.345678;
    A.matrix[1][1] = 1.345678;

    B.matrix[0][0] = 1.345678;
    B.matrix[0][1] = 1.345678;
    B.matrix[1][0] = 1.345678;
    B.matrix[1][1] = 1.345678;
    ck_assert_int_eq(s21_eq_matrix(&A,&B), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix2) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    A.matrix[0][0] = 1.345678;
    A.matrix[0][1] = 1.345678;
    A.matrix[1][0] = 1.345678;
    A.matrix[1][1] = 1.345678;

    B.matrix[0][0] = 1.345678;
    B.matrix[0][1] = 1.345678;
    B.matrix[1][0] = 1.345678;
    B.matrix[1][1] = 1.345677;
    ck_assert_int_eq(s21_eq_matrix(&A,&B), FAILURE);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix3) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 3, &B);
    A.matrix[0][0] = 0;
    A.matrix[0][1] = 0;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 0;

    B.matrix[0][0] = 0;
    B.matrix[0][1] = 0;
    B.matrix[0][2] = 0;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 0;
    B.matrix[1][2] = 0;
    ck_assert_int_eq(s21_eq_matrix(&A,&B), FAILURE);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix4) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 0, &A);
    s21_create_matrix(2, 0, &B);
    ck_assert_int_eq(s21_eq_matrix(&A,&B), FAILURE);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

Suite *s21_eq_matrix_test(void) {
    Suite *s = suite_create("\033[46m-=s21_eq_matrix_test=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_eq_matrix1);
    tcase_add_test(tc, s21_eq_matrix2);
    tcase_add_test(tc, s21_eq_matrix3);
    tcase_add_test(tc, s21_eq_matrix4);
    suite_add_tcase(s, tc);
    return s;
}

// SUM MATRIX

START_TEST(s21_sum_matrix1) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(0, 0, &A);
    s21_create_matrix(0, 0, &B);
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix2) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 1, &B);
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), WRONG_OPERATION);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix3) {
    matrix_t A = {0}, B = {0}, C = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;

    B.matrix[0][0] = 4;
    B.matrix[0][1] = 3;
    B.matrix[1][0] = 2;
    B.matrix[1][1] = 1;

    C.matrix[0][0] = 5;
    C.matrix[0][1] = 5;
    C.matrix[1][0] = 5;
    C.matrix[1][1] = 5;
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
    ck_assert_int_eq(s21_eq_matrix(&result,&C), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix4) {
    matrix_t A = {0}, B = {0}, C = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);
    A.matrix[0][0] = DBL_MAX;
    A.matrix[0][1] = DBL_MAX;
    A.matrix[1][0] = DBL_MAX;
    A.matrix[1][1] = DBL_MAX;

    B.matrix[0][0] = DBL_MAX;
    B.matrix[0][1] = DBL_MAX;
    B.matrix[1][0] = DBL_MAX;
    B.matrix[1][1] = DBL_MAX;
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), WRONG_OPERATION);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST

Suite *s21_sum_matrix_test(void) {
    Suite *s = suite_create("\033[46m-=s21_sum_matrix_test=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_sum_matrix1);
    tcase_add_test(tc, s21_sum_matrix2);
    tcase_add_test(tc, s21_sum_matrix3);
    tcase_add_test(tc, s21_sum_matrix4);
    suite_add_tcase(s, tc);
    return s;
}

// SUB MATRIX

START_TEST(s21_sub_matrix1) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(0, 0, &A);
    s21_create_matrix(0, 0, &B);
    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix2) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 1, &B);
    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), WRONG_OPERATION);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix3) {
    matrix_t A = {0}, B = {0}, C = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;

    B.matrix[0][0] = 4;
    B.matrix[0][1] = 3;
    B.matrix[1][0] = 2;
    B.matrix[1][1] = 1;

    C.matrix[0][0] = -3;
    C.matrix[0][1] = -1;
    C.matrix[1][0] = 1;
    C.matrix[1][1] = 3;
    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
    ck_assert_int_eq(s21_eq_matrix(&result,&C), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix4) {
    matrix_t A = {0}, B = {0}, C = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);
    A.matrix[0][0] = -DBL_MAX;
    A.matrix[0][1] = -DBL_MAX;
    A.matrix[1][0] = -DBL_MAX;
    A.matrix[1][1] = -DBL_MAX;

    B.matrix[0][0] = DBL_MAX;
    B.matrix[0][1] = DBL_MAX;
    B.matrix[1][0] = DBL_MAX;
    B.matrix[1][1] = DBL_MAX;
    ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), WRONG_OPERATION);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST

Suite *s21_sub_matrix_test(void) {
    Suite *s = suite_create("\033[46m-=s21_sub_matrix_test=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_sub_matrix1);
    tcase_add_test(tc, s21_sub_matrix2);
    tcase_add_test(tc, s21_sub_matrix3);
    tcase_add_test(tc, s21_sub_matrix4);
    suite_add_tcase(s, tc);
    return s;
}

// MULT MATRIX & MATRIX

START_TEST(s21_mult_matrix1) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(0, 1, &A);
    s21_create_matrix(0, 1, &B);
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix2) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 5, &A);
    s21_create_matrix(3, 1, &B);
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), WRONG_OPERATION);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix3) {
    matrix_t A = {0}, B = {0}, C = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &C);
    A.matrix[0][0] = DBL_MAX;
    A.matrix[0][1] = DBL_MAX;
    A.matrix[1][0] = DBL_MAX;
    A.matrix[1][1] = DBL_MAX;

    B.matrix[0][0] = DBL_MAX;
    B.matrix[0][1] = DBL_MAX;
    B.matrix[1][0] = DBL_MAX;
    B.matrix[1][1] = DBL_MAX;

    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), WRONG_OPERATION);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix4) {
    matrix_t A = {0}, B = {0}, C = {0}, result = {0};
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &C);
    A.matrix[0][0] = 2.34;
    A.matrix[0][1] = 1.23;
    A.matrix[0][2] = 2.3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 2.5;
    A.matrix[1][2] = 1;
    A.matrix[2][0] = 0;
    A.matrix[2][1] = 10;
    A.matrix[2][2] = 4;

    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 4;
    B.matrix[1][1] = 5;
    B.matrix[1][2] = 6;
    B.matrix[2][0] = 7;
    B.matrix[2][1] = 8;
    B.matrix[2][2] = 9;

    C.matrix[0][0] = 23.36;
    C.matrix[0][1] = 29.23;
    C.matrix[0][2] = 35.1;
    C.matrix[1][0] = 17;
    C.matrix[1][1] = 20.5;
    C.matrix[1][2] = 24;
    C.matrix[2][0] = 68;
    C.matrix[2][1] = 82;
    C.matrix[2][2] = 96;

    ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
    ck_assert_int_eq(s21_eq_matrix(&C, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    s21_remove_matrix(&result);
}
END_TEST

Suite *s21_mult_matrix_test(void) {
    Suite *s = suite_create("\033[46m-=s21_mult_matrix_test=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_mult_matrix1);
    tcase_add_test(tc, s21_mult_matrix2);
    tcase_add_test(tc, s21_mult_matrix3);
    tcase_add_test(tc, s21_mult_matrix4);
    suite_add_tcase(s, tc);
    return s;
}

// TRANSPOSE

START_TEST(s21_transpose1) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(0, 0, &A);
    ck_assert_int_eq(s21_transpose(&A, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose2) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;

    B.matrix[0][0] = 1;
    B.matrix[0][1] = 3;
    B.matrix[1][0] = 2;
    B.matrix[1][1] = 4;
    ck_assert_int_eq(s21_transpose(&A, &result), OK);
    ck_assert_int_eq(s21_eq_matrix(&B, &result), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

Suite *s21_transpose_test(void) {
    Suite *s = suite_create("\033[46m-=s21_transpose_test=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_transpose1);
    tcase_add_test(tc, s21_transpose2);
    suite_add_tcase(s, tc);
    return s;
}

// CALC_COMPLEMENTS

START_TEST(s21_calc_complements_test1) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(0, 0, &A);
    ck_assert_int_eq(s21_calc_complements(&A, &result), INCORRECT_MATRIX);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test2) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(3, 1, &A);
    ck_assert_int_eq(s21_calc_complements(&A, &result), WRONG_OPERATION);
    s21_remove_matrix(&result);
}
END_TEST

Suite *s21_calc_complements_test(void) {
    Suite *s = suite_create("\033[46m-=s21_transpose_test=-\033[0m");
    TCase *tc = tcase_create("matrix_tc");
    tcase_add_test(tc, s21_calc_complements_test1);
    tcase_add_test(tc, s21_calc_complements_test2);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    int failed = 0;
    Suite *s21_matrix_test[] = {s21_create_matrix_test(),
                                s21_eq_matrix_test(),
                                s21_sum_matrix_test(),
                                s21_sub_matrix_test(),
                                s21_mult_matrix_test(),
                                s21_transpose_test(),
                                s21_calc_complements_test(),
                                NULL};

    for (int i = 0; s21_matrix_test[i] != NULL; i++) {  // (&& failed == 0)
        SRunner *sr = srunner_create(s21_matrix_test[i]);

        srunner_set_fork_status(sr, CK_NOFORK);
        srunner_run_all(sr, CK_NORMAL);

        failed += srunner_ntests_failed(sr);
        srunner_free(sr);
    }
    printf("========= FAILED: %d =========\n", failed);

    return failed == 0 ? 0 : 1;
}