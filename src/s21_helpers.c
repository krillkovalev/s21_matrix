#include "s21_matrix.h"

int s21_is_empty(matrix_t *A) {
  int status = 0;
  if (A == NULL || A->matrix == NULL || A->columns <= 0 || A->rows <= 0) {
    status = 1;
  }
  return status;
}

void s21_init_matrix(double number, matrix_t *A) {
  for (int x = 0; x < A->rows; x += 1) {
    for (int y = 0; y < A->columns; number += 1.0, y += 1)
      A->matrix[x][y] = number;
  }
}