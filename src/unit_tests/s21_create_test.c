#include "../s21_test_matrix.h"

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_2) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_3) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_4) {
  matrix_t a;
  int result = 0;
  result = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(result, 1);
  result = s21_create_matrix(3, 3, &a);
  ck_assert_int_eq(result, 0);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(0, 3, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(0, 0, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(3, 0, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(-1, 5, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(5, -1, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
  result = s21_create_matrix(-1, -1, &a);
  ck_assert_int_eq(result, 1);
  if (result == 0) {
    s21_remove_matrix(&a);
  }
}
END_TEST

START_TEST(create_5) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_6) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_7) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_8) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 4, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_9) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(10, 15, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_10) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_11) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_12) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_13) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(-1, 1, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc = tcase_create("case_create_matrix");

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, create_4);
  tcase_add_test(tc, create_5);
  tcase_add_test(tc, create_6);
  tcase_add_test(tc, create_7);
  tcase_add_test(tc, create_8);
  tcase_add_test(tc, create_9);
  tcase_add_test(tc, create_10);
  tcase_add_test(tc, create_11);
  tcase_add_test(tc, create_12);
  tcase_add_test(tc, create_13);

  suite_add_tcase(s, tc);
  return s;
}