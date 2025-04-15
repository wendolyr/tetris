#include "../../headers/backend.h"

void userInput(UserAction_t action, bool hold) {
  Singleton_t *game = getState();

  if (action == Terminate) {
    saveHighScore(game->tetris);
    game->state = Exit;
  }

  else if (game->state == MainMenu) {
    mainMenuInteraction(game, action);

  } else if (game->state == Spawn)
    spawningTetromino(game);

  else if (game->state == Moving) {
    if (action == Left)
      movingLeft(game);
    else if (action == Right)
      movingRight(game);
    else if (action == Down && hold == false)
      movingDown(game);
    else if (action == Down && hold == true) {
      int code = 1;
      while (code == 1) {
        code = movingDown(game);
      }
    } else if (action == Action) {
      rotatingTetromino(game);
    } else if (action == Pause) {
      game->state = PauseMenu;
      game->tetris->pause = PAUSE_ONE;
    }

  } else if (game->state == Attaching)
    attachingTetromino(game);

  else if (game->state == PauseMenu) {
    pauseInteraction(game, action);
  }

  else if (game->state == GameOver) {
    gameOverInteraction(game, action);
  }
}

GameInfo_t updateCurrentState() {
  GameInfo_t tetris = {0};
  Singleton_t *game = getState();
  if (game != NULL) {
    if (game->state == Exit) {
      removeGame();
      tetris.field = NULL;
      tetris.next = NULL;
    } else {
      tetris = *game->tetris;
    }
  }

  return tetris;
}

Tetromino_t updateTetrominoState() {
  Tetromino_t tetromino = {0};
  Singleton_t *game = getState();
  if (game != NULL) {
    if (game->state != Exit && game->tetromino != NULL) {
      tetromino = *game->tetromino;
    }
  }

  return tetromino;
}

Fsm_t updateFsmState() {
  Fsm_t state = 0;
  Singleton_t *game = getState();

  if (game->state != Exit) {
    state = game->state;
  }

  return state;
}

Singleton_t *getState() {
  static Singleton_t *game = NULL;
  static int game_started = 0;
  if (game == NULL && !game_started) {
    game_started = 1;
    game = malloc(sizeof(Singleton_t));
    if (game != NULL) {
      int code = createGameInfo(&game->tetris);
      if (code == ST_OK) {
        code = createTetromino(&game->tetromino);
        if (code == ST_ERROR) {
          free(game->tetris->field);
          free(game->tetris->next);
          free(game->tetris);
        }
      }

      if (code == ST_ERROR) {
        free(game);
        game = NULL;
      } else if (code == ST_OK)
        game->state = MainMenu;
    }
  }

  return game;
}

int createGameInfo(GameInfo_t **tetris) {
  int code = ST_OK;
  *tetris = malloc(sizeof(GameInfo_t));

  if (*tetris != NULL) {
    (*tetris)->field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH, &code);
    if ((*tetris)->field != NULL) {
      (*tetris)->next = createMatrix(TETR_HEIGHT, TETR_WIDTH, &code);
      if ((*tetris)->next == NULL) free((*tetris)->field);
    }
  } else
    code = ST_ERROR;

  if (code == ST_OK) {
    (*tetris)->score = 0;
    getHighScore((*tetris));
    (*tetris)->level = 1;
    (*tetris)->speed = 1;
    (*tetris)->pause = 1;
  } else
    free(*tetris);

  return code;
}

int createTetromino(Tetromino_t **tetromino) {
  int code = 0;
  *tetromino = malloc(sizeof(Tetromino_t));
  if (*tetromino != NULL) {
    (*tetromino)->shape = createMatrix(TETR_HEIGHT, TETR_WIDTH, &code);
  } else
    code = ST_ERROR;

  if (code == ST_OK) {
    (*tetromino)->index = 0;
    (*tetromino)->rotation_stage = 0;
    (*tetromino)->x = 0;
    (*tetromino)->y = 0;
  } else
    free(*tetromino);

  return code;
}

void prepareForNewGame() {
  Singleton_t *game = getState();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      game->tetris->field[i][j] = 0;
    }
  }
  game->tetris->score = 0;
  getHighScore(game->tetris);
  game->tetris->level = 1;
  game->tetris->speed = 1;
  game->tetris->pause = NO_PAUSE;
  game->state = Spawn;
}

void removeGame() {
  Singleton_t *game = getState();
  if (game != NULL) {
    if (game->tetris != NULL) {
      free(game->tetris->field);
      free(game->tetris->next);
      free(game->tetris);
      game->tetris = NULL;
    }

    if (game->tetromino != NULL) {
      free(game->tetromino->shape);
      free(game->tetromino);
      game->tetromino = NULL;
    }
    free(game);
    game = NULL;
  }
}

void getHighScore(GameInfo_t *tetris) {
  FILE *file = fopen(HIGH_SCORE_DIR, "r");
  if (file == NULL) {
    tetris->high_score = 0;
  } else {
    int temp = 0;
    fscanf(file, "%d", &temp);
    tetris->high_score = temp;

    fclose(file);
  }
}

void saveHighScore(GameInfo_t *tetris) {
  if (tetris->score > tetris->high_score) {
    tetris->high_score = tetris->score;
    FILE *file = fopen(HIGH_SCORE_DIR, "w");
    if (file != NULL) {
      fprintf(file, "%d", tetris->high_score);
      fclose(file);
    }
  }
}

int timer() {
  static struct timespec start = {0, 0};
  static double time_failing = 0.0;
  static int initialized = 0;
  int alarm = 0;
  Singleton_t *game = getState();
  struct timespec end;
  clock_gettime(CLOCK_MONOTONIC, &end);

  if (!initialized) {
    start = end;
    initialized = 1;
  } else if (game->state == Moving) {
    double elapsed_time = (end.tv_sec - start.tv_sec) +
                          (double)(end.tv_nsec - start.tv_nsec) / 1e9;

    time_failing += elapsed_time;
    double waiting_time = 1 - 0.08 * game->tetris->speed;
    if (time_failing > waiting_time) {
      alarm = 1;
      time_failing -= waiting_time;
    }
  } else if (game->state == Spawn) {
    time_failing = 0.0;
  }
  start = end;

  return alarm;
}