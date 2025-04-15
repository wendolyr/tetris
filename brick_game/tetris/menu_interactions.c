#include "../../headers/backend.h"

void mainMenuInteraction(Singleton_t *game, UserAction_t action) {
  if (game->tetris->pause == PAUSE_ONE) {
    if (action == Down)
      game->tetris->pause = PAUSE_TWO;
    else if (action == Start) {
      game->state = Spawn;
      game->tetris->pause = NO_PAUSE;
    }
  } else if (game->tetris->pause == PAUSE_TWO) {
    if (action == Up)
      game->tetris->pause = PAUSE_ONE;
    else if (action == Start)
      game->state = Exit;
  }
}

void gameOverInteraction(Singleton_t *game, UserAction_t action) {
  if (action == Terminate) game->state = Exit;

  if (game->tetris->pause == PAUSE_ONE) {
    if (action == Start) {
      saveHighScore(game->tetris);
      prepareForNewGame();
    } else if (action == Down)
      game->tetris->pause = PAUSE_TWO;

  } else if (game->tetris->pause == PAUSE_TWO) {
    if (action == Start) {
      saveHighScore(game->tetris);
      game->state = Exit;
    } else if (action == Up)
      game->tetris->pause = PAUSE_ONE;
  }
}

void pauseInteraction(Singleton_t *game, UserAction_t action) {
  if (action == Pause) {
    game->state = Moving;
    game->tetris->pause = NO_PAUSE;
  }

  if (game->tetris->pause == PAUSE_ONE) {
    if (action == Start) {
      game->state = Moving;
      game->tetris->pause = NO_PAUSE;
    } else if (action == Down)
      game->tetris->pause = PAUSE_TWO;
  } else if (game->tetris->pause == PAUSE_TWO) {
    if (action == Start) {
      saveHighScore(game->tetris);
      game->state = Exit;
    } else if (action == Up)
      game->tetris->pause = PAUSE_ONE;
  }
}