#include "test.h"

START_TEST(createMatrixTest) {
  int code = ST_OK;
  int **matrix = createMatrix(TETR_HEIGHT, TETR_WIDTH, &code);

  ck_assert_int_eq(code, 0);
  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      ck_assert_int_eq(matrix[i][j], 0);
    }
  }

  free(matrix);
}
END_TEST

START_TEST(turnRightMatrixTest) {
  int code = 0;
  int **matrix = createMatrix(TETR_HEIGHT, TETR_WIDTH, &code);
  int counter = 1;
  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      matrix[i][j] = counter++;
    }
  }
  code = turnRightMatrix(TETR_HEIGHT, TETR_WIDTH, matrix);
  ck_assert_int_eq(code, ST_OK);

  for (int j = 0; j < TETR_WIDTH; j++) {
    for (int i = TETR_HEIGHT - 1; i >= 0; i--) {
      counter--;
      ck_assert_int_eq(matrix[i][j], counter);
    }
  }
  free(matrix);

  code = turnRightMatrix(3, 3, NULL);
  ck_assert_int_eq(code, ST_ERROR);
}
END_TEST

START_TEST(turnLeftMatrixTest) {
  int code = 0;
  int **matrix = createMatrix(TETR_HEIGHT, TETR_WIDTH, &code);
  int counter = 1;
  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      matrix[i][j] = counter++;
    }
  }
  code = turnLeftMatrix(TETR_HEIGHT, TETR_WIDTH, matrix);
  ck_assert_int_eq(code, ST_OK);

  for (int j = TETR_WIDTH - 1; j >= 0; j--) {
    for (int i = 0; i < TETR_HEIGHT; i++) {
      counter--;
      ck_assert_int_eq(matrix[i][j], counter);
    }
  }
  free(matrix);

  code = turnLeftMatrix(3, 3, NULL);
  ck_assert_int_eq(code, ST_ERROR);
}
END_TEST

Suite *matrixTests() {
  Suite *s = suite_create("matrixTests");
  TCase *tc_core = tcase_create("matrixTests");

  tcase_add_test(tc_core, createMatrixTest);
  tcase_add_test(tc_core, turnRightMatrixTest);
  tcase_add_test(tc_core, turnLeftMatrixTest);

  suite_add_tcase(s, tc_core);

  return s;
}