#include "test.h"

START_TEST(mainMenuInteractionTest) {
  Singleton_t *game = getState();
  game->state = MainMenu;
  game->tetris->pause = PAUSE_ONE;
  mainMenuInteraction(game, Down);
  ck_assert_int_eq(game->tetris->pause, PAUSE_TWO);

  mainMenuInteraction(game, Up);
  ck_assert_int_eq(game->tetris->pause, PAUSE_ONE);

  mainMenuInteraction(game, Start);
  ck_assert_int_eq(game->tetris->pause, NO_PAUSE);
  ck_assert_int_eq(game->state, Spawn);

  game->state = MainMenu;
  game->tetris->pause = PAUSE_TWO;
  mainMenuInteraction(game, Start);
  ck_assert_int_eq(game->state, Exit);
}
END_TEST

START_TEST(pauseInteractionTest) {
  Singleton_t *game = getState();

  game->state = PauseMenu;
  game->tetris->pause = 1;

  pauseInteraction(game, Down);
  ck_assert_int_eq(game->tetris->pause, PAUSE_TWO);

  pauseInteraction(game, Up);
  ck_assert_int_eq(game->tetris->pause, PAUSE_ONE);

  pauseInteraction(game, Start);
  ck_assert_int_eq(game->state, Moving);
  ck_assert_int_eq(game->tetris->pause, 0);

  game->state = PauseMenu;
  game->tetris->pause = PAUSE_TWO;
  pauseInteraction(game, Start);
  ck_assert_int_eq(game->state, Exit);

  game->state = PauseMenu;
  pauseInteraction(game, Pause);
  ck_assert_int_eq(game->state, Moving);
}
END_TEST

START_TEST(gameOverInteractionTest) {
  Singleton_t *game = getState();
  game->state = GameOver;
  game->tetris->pause = 1;

  gameOverInteraction(game, Down);
  ck_assert_int_eq(game->tetris->pause, PAUSE_TWO);
  ck_assert_int_eq(game->state, GameOver);

  gameOverInteraction(game, Up);
  ck_assert_int_eq(game->tetris->pause, PAUSE_ONE);
  ck_assert_int_eq(game->state, GameOver);

  gameOverInteraction(game, Start);
  ck_assert_int_eq(game->state, Spawn);
  ck_assert_int_eq(game->tetris->pause, NO_PAUSE);

  game->state = GameOver;
  game->tetris->pause = PAUSE_TWO;
  gameOverInteraction(game, Start);
  ck_assert_int_eq(game->state, Exit);
}
END_TEST

Suite *menuInteractionTests() {
  Suite *s = suite_create("menuInteractionTest");
  TCase *tc_core = tcase_create("menuInteractionTest");

  tcase_add_test(tc_core, mainMenuInteractionTest);
  tcase_add_test(tc_core, pauseInteractionTest);
  tcase_add_test(tc_core, gameOverInteractionTest);

  suite_add_tcase(s, tc_core);

  return s;
}