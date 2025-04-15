#include "test.h"

START_TEST(userInputTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  userInput(Terminate, false);
  ck_assert_int_eq(game->state, Exit);

  game->state = MainMenu;
  game->tetris->pause = PAUSE_ONE;
  userInput(Start, false);
  ck_assert_int_eq(game->state, Spawn);
  ck_assert_int_eq(game->tetris->pause, NO_PAUSE);

  userInput(Up, false);
  ck_assert_int_eq(game->state, Moving);

  userInput(Left, false);
  ck_assert_int_eq(game->state, Moving);

  userInput(Right, false);
  ck_assert_int_eq(game->state, Moving);

  userInput(Pause, false);
  ck_assert_int_eq(game->state, PauseMenu);
  ck_assert_int_eq(game->tetris->pause, PAUSE_ONE);

  userInput(Pause, false);
  ck_assert_int_eq(game->state, Moving);

  userInput(Action, false);
  ck_assert_int_eq(game->state, Moving);

  userInput(Down, true);
  ck_assert_int_eq(game->state, Attaching);

  userInput(Up, false);
  ck_assert_int_eq(game->state, Spawn);

  userInput(Up, false);
  ck_assert_int_eq(game->state, Moving);

  userInput(Down, false);
  ck_assert_int_eq(game->state, Moving);

  game->state = GameOver;
  game->tetris->pause = PAUSE_ONE;
  userInput(Down, false);
  ck_assert_int_eq(game->tetris->pause, PAUSE_TWO);
}
END_TEST

START_TEST(updateTetrominoStateTest) {
  Singleton_t *game = getState();
  game->tetromino->x = 10;
  game->tetromino->y = 4;

  ck_assert_int_eq(updateTetrominoState().x, 10);
  ck_assert_int_eq(updateTetrominoState().y, 4);
}
END_TEST

START_TEST(updateFsmStateTest) {
  Singleton_t *game = getState();
  game->state = PauseMenu;

  ck_assert_int_eq(updateFsmState(), PauseMenu);
}
END_TEST

START_TEST(timerTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  spawningTetromino(game);
  int counter_one = 0;
  int counter_two = 0;
  timer();
  while (!timer()) {
    counter_one++;
  }
  game->tetris->speed = 10;
  while (!timer()) {
    counter_two++;
  }

  ck_assert_int_eq(counter_one > counter_two, 1);
}
END_TEST

START_TEST(prepareForNewGameTest) {
  Singleton_t *game = getState();
  prepareForNewGame();
  ck_assert_int_eq(game->state, Spawn);
  ck_assert_int_eq(game->tetris->level, 1);
  ck_assert_int_eq(game->tetris->speed, 1);
  ck_assert_int_eq(game->tetris->score, 0);
  ck_assert_int_eq(game->tetris->pause, 0);
}
END_TEST

START_TEST(updateCurrentStateTest) {
  Singleton_t *game = getState();
  game->tetris->level = 10;
  game->tetris->score = 500;
  ck_assert_int_eq(updateCurrentState().level, 10);
  ck_assert_int_eq(updateCurrentState().score, 500);

  game->state = Exit;
  ck_assert_ptr_eq(updateCurrentState().field, NULL);
}
END_TEST

Suite *backendTests() {
  Suite *s = suite_create("backendTests");
  TCase *tc_core = tcase_create("backendTests");

  tcase_add_test(tc_core, userInputTest);
  tcase_add_test(tc_core, updateTetrominoStateTest);
  tcase_add_test(tc_core, updateFsmStateTest);
  tcase_add_test(tc_core, timerTest);
  tcase_add_test(tc_core, prepareForNewGameTest);
  tcase_add_test(tc_core, updateCurrentStateTest);

  suite_add_tcase(s, tc_core);

  return s;
}