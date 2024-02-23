#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = 0;
  if (rows > 0 && columns > 0 && result != NULL) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (s21_is_empty(A) == 1 || s21_is_empty(B) == 1) {
    status = FAILURE;
  } else {
    if (A->rows != B->rows || A->columns != B->columns) {
      status = FAILURE;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
            status = FAILURE;
            break;
          }
        }
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;
  if (s21_is_empty(A) == 0 || s21_is_empty(B) == 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      status = CALCULATION_ERROR;
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;
  if (s21_is_empty(A) == 0 || s21_is_empty(B) == 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      status = CALCULATION_ERROR;
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = 0;
  if (s21_is_empty(A) == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;
  if (s21_is_empty(A) == 0)
    if (A->columns != B->rows) {
      status = CALCULATION_ERROR;
    } else {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++)
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = 0;
  if (s21_is_empty(A) == 0) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      if (s21_create_matrix(A->rows, A->columns, result) == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor = {0};
            double determinant = 0.0;
            s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
            s21_make_minor(i, j, A, &minor);
            s21_determinant(&minor, &determinant);
            result->matrix[i][j] = determinant * pow(-1, i + j);
            s21_remove_matrix(&minor);
          }
        }
      }
    } else {
      status = CALCULATION_ERROR;
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

void s21_make_minor(int rows, int columns, matrix_t *A, matrix_t *result) {
  int minor_rows = 0, minor_columns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == rows) continue;
    minor_columns = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == columns)
        continue;
      else {
        result->matrix[minor_rows][minor_columns] = A->matrix[i][j];
      }
      minor_columns++;
    }
    minor_rows++;
  }
}

double s21_get_determinant(matrix_t *A) {
  double result = 0.0;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_make_minor(0, i, A, &tmp);
      if (i % 2) {
        result -= A->matrix[0][i] * s21_get_determinant(&tmp);

      } else {
        result += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = 0;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns)
      *result = s21_get_determinant(A);
    else
      status = CALCULATION_ERROR;
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = 1;
  if (s21_is_empty(A) == 0) {
    if (A->rows == A->columns) {
      double det = 0.0;
      s21_determinant(A, &det);
      if (det != 0) {
        matrix_t compl_tmp = {0};
        if (s21_calc_complements(A, &compl_tmp) == 0) {
          matrix_t transpose_tmp = {0};
          if (s21_transpose(&compl_tmp, &transpose_tmp) == 0) {
            s21_mult_number(&transpose_tmp, 1.0 / det, result);
            s21_remove_matrix(&transpose_tmp);
          }
        }
        s21_remove_matrix(&compl_tmp);
      } else {
        status = CALCULATION_ERROR;
      }
    } else {
      status = CALCULATION_ERROR;
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}
