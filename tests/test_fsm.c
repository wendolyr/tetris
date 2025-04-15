#include "test.h"

START_TEST(checkingFieldRowsTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  for (int j = 0; j < FIELD_WIDTH; j++) {
    game->tetris->field[FIELD_HEIGHT - 1][j] = 1;
  }

  checkingFieldRows(game);
  ck_assert_int_eq(game->tetris->score, SCORE_ONE);

  prepareForNewGame();
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      game->tetris->field[FIELD_HEIGHT - 1 - i][j] = 1;
    }
  }
  checkingFieldRows(game);
  ck_assert_int_eq(game->tetris->score, SCORE_TWO);

  prepareForNewGame();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      game->tetris->field[FIELD_HEIGHT - 1 - i][j] = 1;
    }
  }
  checkingFieldRows(game);
  ck_assert_int_eq(game->tetris->score, SCORE_THREE);

  prepareForNewGame();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      game->tetris->field[FIELD_HEIGHT - 1 - i][j] = 1;
    }
  }
  checkingFieldRows(game);
  ck_assert_int_eq(game->tetris->score, SCORE_FOUR);
}
END_TEST

START_TEST(spawningTetrominoTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  spawningTetromino(game);
  ck_assert_int_eq(game->tetromino->y, TETR_SPAWN_Y);
  ck_assert_int_eq(game->tetromino->x, TETR_SPAWN_X);
  ck_assert_int_eq(game->state, Moving);
  prepareForNewGame();

  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      game->tetris->field[i][j] = 1;
    }
  }

  spawningTetromino(game);
  ck_assert_int_eq(game->state, GameOver);
  ck_assert_int_eq(game->tetris->pause, PAUSE_ONE);
}
END_TEST

START_TEST(movingDownTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  spawningTetromino(game);
  movingDown(game);
  ck_assert_int_eq(game->tetromino->y, TETR_SPAWN_Y + 1);
  ck_assert_int_eq(game->tetromino->x, TETR_SPAWN_X);

  game->tetromino->y = FIELD_BOTTOM - 1;
  movingDown(game);
  ck_assert_int_eq(game->tetromino->y, FIELD_BOTTOM);

  movingDown(game);
  ck_assert_int_eq(game->state, Attaching);
}
END_TEST

START_TEST(movingLeftTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  spawningTetromino(game);
  movingLeft(game);
  ck_assert_int_eq(game->tetromino->y, TETR_SPAWN_Y);
  ck_assert_int_eq(game->tetromino->x, TETR_SPAWN_X - CELL_WIDTH);

  prepareForNewGame();
  settingTetromino(1, 2, game->tetromino->shape);
  game->tetromino->x = FIELD_LEFT + 4;
  game->tetromino->y = TETR_SPAWN_Y;
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 2;

  movingLeft(game);
  ck_assert_int_eq(game->tetromino->x, FIELD_LEFT + 2);

  movingLeft(game);
  ck_assert_int_eq(game->tetromino->x, FIELD_LEFT + 2);

  while (game->tetromino->rotation_stage != 3) rotatingTetromino(game);
  movingLeft(game);
  ck_assert_int_eq(game->tetromino->x, FIELD_LEFT);
}
END_TEST

START_TEST(movingRightTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  spawningTetromino(game);
  movingRight(game);
  ck_assert_int_eq(game->tetromino->y, TETR_SPAWN_Y);
  ck_assert_int_eq(game->tetromino->x, TETR_SPAWN_X + CELL_WIDTH);

  prepareForNewGame();
  settingTetromino(1, 2, game->tetromino->shape);
  game->tetromino->x = FIELD_RIGHT - 5;
  game->tetromino->y = TETR_SPAWN_Y;
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 2;

  movingRight(game);
  ck_assert_int_eq(game->tetromino->x, FIELD_RIGHT - 3);

  movingRight(game);
  ck_assert_int_eq(game->tetromino->x, FIELD_RIGHT - 3);

  rotatingTetromino(game);
  movingRight(game);
  ck_assert_int_eq(game->tetromino->x, FIELD_RIGHT - 1);
}
END_TEST

START_TEST(rotatingTetrominoTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  settingTetromino(1, 2, game->tetromino->shape);
  game->tetromino->rotation_stage = 0;
  game->tetromino->x = TETR_SPAWN_X;
  game->tetromino->y = TETR_SPAWN_Y;
  game->tetromino->index = 2;

  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 1);

  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 2);

  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 3);

  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 0);

  settingTetromino(1, 3, game->tetromino->shape);
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 3;

  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 1);

  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 0);
}
END_TEST

START_TEST(rotatingNearEdgesTest) {
  Singleton_t *game = getState();

  settingTetromino(1, 2, game->tetromino->shape);
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 2;
  rotatingTetromino(game);
  game->tetromino->x = FIELD_RIGHT - 1;
  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 1);

  game->tetromino->x = TETR_SPAWN_X;
  while (game->tetromino->rotation_stage != 3) rotatingTetromino(game);
  game->tetromino->x = FIELD_LEFT;
  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 3);

  settingTetromino(1, 1, game->tetromino->shape);
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 1;
  game->tetromino->x = TETR_SPAWN_X;
  game->tetromino->y = FIELD_BOTTOM - 1;
  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 0);

  game->tetromino->y = FIELD_BOTTOM;
  rotatingTetromino(game);
  ck_assert_int_eq(game->tetromino->rotation_stage, 0);
}
END_TEST

START_TEST(attachingTetrominoTest) {
  Singleton_t *game = getState();

  prepareForNewGame();
  settingTetromino(1, 2, game->tetromino->shape);
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 2;
  game->tetromino->x = TETR_SPAWN_X;
  game->tetromino->y = TETR_SPAWN_Y;
  game->state = Moving;
  movingDown(game);
  movingDown(game);
  attachingTetromino(game);
  ck_assert_int_eq(game->state, Spawn);

  settingTetromino(1, 2, game->tetromino->shape);
  game->tetromino->rotation_stage = 0;
  game->tetromino->index = 2;
  game->tetromino->x = TETR_SPAWN_X;
  game->tetromino->y = TETR_SPAWN_Y;
  game->state = Moving;

  movingDown(game);
  ck_assert_int_eq(game->state, Attaching);

  attachingTetromino(game);
  ck_assert_int_eq(game->state, GameOver);
}
END_TEST

Suite *fsmTests() {
  Suite *s = suite_create("fsmTests");
  TCase *tc_core = tcase_create("fsmTests");

  tcase_add_test(tc_core, checkingFieldRowsTest);
  tcase_add_test(tc_core, spawningTetrominoTest);
  tcase_add_test(tc_core, movingDownTest);
  tcase_add_test(tc_core, movingLeftTest);
  tcase_add_test(tc_core, movingRightTest);
  tcase_add_test(tc_core, rotatingTetrominoTest);
  tcase_add_test(tc_core, rotatingNearEdgesTest);
  tcase_add_test(tc_core, attachingTetrominoTest);

  suite_add_tcase(s, tc_core);

  return s;
}