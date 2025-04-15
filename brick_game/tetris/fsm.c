#include "../../headers/backend.h"

void settingTetromino(int color, int type, int **shape) {
  int tetromino_types[7][TETR_HEIGHT][TETR_WIDTH] = {
      {{0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0},
       {color, color, color, color, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0},
       {0, color, 0, 0, 0},
       {0, color, color, color, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0},
       {0, color, color, 0, 0},
       {0, 0, color, color, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0},
       {0, color, color, 0, 0},
       {0, color, color, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0},
       {0, 0, color, color, 0},
       {0, color, color, 0, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0},
       {0, 0, color, 0, 0},
       {0, color, color, color, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}},
      {{0, 0, 0, 0, 0},
       {0, 0, 0, color, 0},
       {0, color, color, color, 0},
       {0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0}}};

  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      shape[i][j] = tetromino_types[type - 1][i][j];
    }
  }
}

void spawningTetromino(Singleton_t *game) {
  int possibility = 1;
  static int new_game = 1;
  static int prev_form = 0;
  if (!new_game) {
    for (int i = 0; i < TETR_HEIGHT; i++) {
      for (int j = 0; j < TETR_WIDTH; j++) {
        game->tetromino->shape[i][j] = game->tetris->next[i][j];
      }
    }
    game->tetromino->index = prev_form;
  }

#ifdef __APPLE__
  for (int i = 0; i < 10; i++) {
    rand();
  }
#endif

  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      game->tetris->next[i][j] = 0;
    }
  }

  int form = 1 + rand() % 7;
  prev_form = form;
  int color = 1 + rand() % 7;
  settingTetromino(color, form, game->tetris->next);

  if (new_game) {
    new_game = 0;
    spawningTetromino(game);
  }

  game->tetromino->x = TETR_SPAWN_X;
  game->tetromino->y = TETR_SPAWN_Y;
  game->tetromino->rotation_stage = 0;

  if (collisionCheck(game, &possibility)) {
    game->state = GameOver;
    game->tetris->pause = 1;
    new_game = 1;
  } else
    game->state = Moving;
}

int movingDown(Singleton_t *game) {
  int permission = 1;

  if (game->tetromino->y < FIELD_BOTTOM - 2)
    game->tetromino->y += 1;
  else if (game->tetromino->y == FIELD_BOTTOM - 2) {
    for (int i = 0; i < TETR_WIDTH; i++) {
      if (game->tetromino->shape[4][i] != 0) permission = 0;
    }
    if (permission) game->tetromino->y += 1;
  } else if (game->tetromino->y == FIELD_BOTTOM - 1) {
    for (int i = 0; i < TETR_WIDTH; i++) {
      if (game->tetromino->shape[3][i] != 0) permission = 0;
    }
    if (permission) game->tetromino->y += 1;
  } else {
    permission = 0;
  }

  if (collisionCheck(game, &permission)) {
    game->tetromino->y -= 1;
  }

  if (permission == 0) game->state = Attaching;

  return permission;
}

void movingLeft(Singleton_t *game) {
  int permission = 1;

  if (game->tetromino->x > FIELD_LEFT + 4)
    game->tetromino->x -= 2;

  else if (game->tetromino->x == FIELD_LEFT + 4) {
    for (int i = 0; i < TETR_HEIGHT; i++) {
      if (game->tetromino->shape[i][0] != 0) permission = 0;
    }
    if (permission) game->tetromino->x -= 2;

  } else if (game->tetromino->x == FIELD_LEFT + 2) {
    for (int i = 0; i < TETR_HEIGHT; i++) {
      if (game->tetromino->shape[i][1] != 0) permission = 0;
    }

    if (permission) game->tetromino->x -= 2;
  }

  if (collisionCheck(game, &permission)) {
    game->tetromino->x += 2;
  }
}

void movingRight(Singleton_t *game) {
  int permission = 1;

  if (game->tetromino->x < FIELD_RIGHT - 5)
    game->tetromino->x += 2;

  else if (game->tetromino->x == FIELD_RIGHT - 5) {
    for (int i = 0; i < TETR_HEIGHT; i++) {
      if (game->tetromino->shape[i][4] != 0) permission = 0;
    }
    if (permission) game->tetromino->x += 2;

  } else if (game->tetromino->x == FIELD_RIGHT - 3) {
    for (int i = 0; i < TETR_HEIGHT; i++) {
      if (game->tetromino->shape[i][3] != 0) permission = 0;
    }
    if (permission) game->tetromino->x += 2;
  }

  if (collisionCheck(game, &permission)) {
    game->tetromino->x -= 2;
  }
}

void rotatingTetromino(Singleton_t *game) {
  if (game->tetromino->index == 2 || game->tetromino->index == 6 ||
      game->tetromino->index == 7) {
    turnLeftMatrix(TETR_HEIGHT, TETR_WIDTH, game->tetromino->shape);
    int permission = 1;
    rotatingNearEdges(game, &permission);
    if (permission == 1) {
      collisionCheck(game, &permission);
    }

    if (permission == 0)
      turnRightMatrix(TETR_HEIGHT, TETR_WIDTH, game->tetromino->shape);
    else
      game->tetromino->rotation_stage =
          (game->tetromino->rotation_stage + 1) % 4;

  } else if (game->tetromino->index == 1 || game->tetromino->index == 3 ||
             game->tetromino->index == 5) {
    int permission = 1;
    if (game->tetromino->rotation_stage == 0) {
      turnLeftMatrix(TETR_HEIGHT, TETR_WIDTH, game->tetromino->shape);
      rotatingNearEdges(game, &permission);
      if (permission == 1) {
        collisionCheck(game, &permission);
      }

      if (permission == 0)
        turnRightMatrix(TETR_HEIGHT, TETR_WIDTH, game->tetromino->shape);
    } else {
      turnRightMatrix(TETR_HEIGHT, TETR_WIDTH, game->tetromino->shape);
      rotatingNearEdges(game, &permission);
      if (permission == 1) {
        collisionCheck(game, &permission);
      }

      if (permission == 0)
        turnLeftMatrix(TETR_HEIGHT, TETR_WIDTH, game->tetromino->shape);
    }
    if (permission)
      game->tetromino->rotation_stage =
          (game->tetromino->rotation_stage + 1) % 2;
  }
}

void rotatingNearEdges(Singleton_t *game, int *permission) {
  if ((game->tetromino->x == FIELD_LEFT + 2) ||
      (game->tetromino->x == FIELD_RIGHT - 3)) {
    for (int i = 0; i < TETR_HEIGHT && game->tetromino->x == FIELD_LEFT + 2;
         i++) {
      if (game->tetromino->shape[i][0] != 0) *permission = 0;
    }

    for (int i = 0; i < TETR_HEIGHT && game->tetromino->x == FIELD_RIGHT - 3;
         i++) {
      if (game->tetromino->shape[i][TETR_WIDTH - 1] != 0) *permission = 0;
    }

  } else if ((game->tetromino->x == FIELD_LEFT) ||
             (game->tetromino->x == FIELD_RIGHT - 1)) {
    for (int i = 0; i < TETR_HEIGHT && game->tetromino->x == FIELD_LEFT; i++) {
      if (game->tetromino->shape[i][1] != 0) *permission = 0;
    }

    for (int i = 0; i < TETR_HEIGHT && game->tetromino->x == FIELD_RIGHT - 1;
         i++) {
      if (game->tetromino->shape[i][TETR_WIDTH - 2] != 0) *permission = 0;
    }
  }

  if ((game->tetromino->y == FIELD_BOTTOM - 1)) {
    for (int i = 0; i < TETR_WIDTH; i++) {
      if (game->tetromino->shape[TETR_HEIGHT - 1][i] != 0) *permission = 0;
    }
  } else if (game->tetromino->y == FIELD_BOTTOM) {
    for (int i = 0; i < TETR_WIDTH; i++) {
      if (game->tetromino->shape[TETR_HEIGHT - 2][i] != 0) *permission = 0;
    }
  }
}

int collisionCheck(Singleton_t *game, int *permission) {
  int check = 0;

  for (int i = 0; i < TETR_HEIGHT && *permission == 1; i++) {
    for (int j = 0; j < TETR_WIDTH && *permission == 1; j++) {
      if (game->tetromino->shape[i][j] != 0) {
        int x_corrected = 0;
        int y_corrected = 0;

        if (game->tetromino->y != TETR_SPAWN_Y) {
          x_corrected =
              (game->tetromino->x - 2 * CELL_WIDTH - FIELD_LEFT) / CELL_WIDTH +
              j;
          y_corrected = game->tetromino->y - 2 + i - FIELD_TOP;

        } else {
          x_corrected =
              (game->tetromino->x - 2 * CELL_WIDTH - FIELD_LEFT) / CELL_WIDTH +
              j;
          y_corrected = game->tetromino->y - FIELD_TOP;
        }

        *permission =
            game->tetris->field[y_corrected][x_corrected] != 0 ? 0 : 1;

        if (*permission == 0) check = 1;
      }
    }
  }

  return check;
}

int attachingTetromino(Singleton_t *game) {
  int permission = 1;
  for (int i = 0; i < TETR_HEIGHT && permission; i++) {
    for (int j = 0; j < TETR_WIDTH && permission; j++) {
      if (game->tetromino->shape[i][j] != 0) {
        int x_corrected =
            (game->tetromino->x - 2 * CELL_WIDTH - FIELD_LEFT) / CELL_WIDTH + j;
        int y_corrected = game->tetromino->y - 2 + i - FIELD_TOP;
        if (y_corrected >= 0)
          game->tetris->field[y_corrected][x_corrected] =
              game->tetromino->shape[i][j];
        else
          permission = 0;
      }
    }
  }

  if (permission) {
    checkingFieldRows(game);
    game->state = Spawn;
  } else {
    game->state = GameOver;
    game->tetris->pause = 1;
  }

  return permission;
}

void checkingFieldRows(Singleton_t *game) {
  int destroyed_rows = 0;
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    int counter = 0;
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (game->tetris->field[i][j] != 0) {
        counter++;
      }
    }
    if (counter == FIELD_WIDTH) {
      destroyRow(game->tetris, i);
      i++;
      destroyed_rows++;
    }
  }

  if (destroyed_rows != 0) {
    scoring(game, destroyed_rows);
  }
}

void destroyRow(GameInfo_t *tetris, int row) {
  for (int i = row; i >= 0; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (i != 0)
        tetris->field[i][j] = tetris->field[i - 1][j];
      else
        tetris->field[i][j] = 0;
    }
  }
}

void scoring(Singleton_t *game, int destroyed_rows) {
  if (destroyed_rows == 1) {
    game->tetris->score += SCORE_ONE;
  } else if (destroyed_rows == 2) {
    game->tetris->score += SCORE_TWO;
  } else if (destroyed_rows == 3) {
    game->tetris->score += SCORE_THREE;
  } else if (destroyed_rows == 4) {
    game->tetris->score += SCORE_FOUR;
  }

  if (game->tetris->level < MAX_LEVEL) {
    game->tetris->level = 1 + game->tetris->score / LEVELUP_SCORE;
    if (game->tetris->level > MAX_LEVEL) game->tetris->level = MAX_LEVEL;
    game->tetris->speed = game->tetris->level;
  }
}