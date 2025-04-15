#include "../../headers/frontend.h"

void createWindow() {
  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(6, COLOR_BLACK, COLOR_CYAN);
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
  init_pair(8, COLOR_BLACK, COLOR_BLACK);

  printFrames();
  printControlTips();
}

void gameDisplay(GameInfo_t *tetris, Tetromino_t *tetromino, int state) {
  if (state == MainMenu) {
    printMainMenu(tetris->pause);

  } else if (state == Moving || state == Spawn || state == Attaching) {
    printField(tetris);
    printTetromino(tetris, tetromino);

  } else if (state == PauseMenu) {
    printPauseMenu(tetris->pause);

  } else if (state == GameOver) {
    printGameOverScreen(tetris);
  }

  refresh();
}

void printFrames() {
  for (int x = 1; x < WINDOW_WIDTH - 1; x++) {
    mvaddch(0, x, ACS_HLINE);
    mvaddch(WINDOW_HEIGHT - 1, x, ACS_HLINE);
  }

  for (int y = 1; y < WINDOW_HEIGHT - 1; y++) {
    mvaddch(y, 0, ACS_VLINE);
    mvaddch(y, WINDOW_WIDTH - 1, ACS_VLINE);
  }
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(WINDOW_HEIGHT - 1, 0, ACS_LLCORNER);
  mvaddch(WINDOW_HEIGHT - 1, WINDOW_WIDTH - 1, ACS_LRCORNER);
  mvaddch(0, WINDOW_WIDTH - 1, ACS_URCORNER);

  for (int x = FIELD_LEFT; x < FIELD_WIDTH * CELL_WIDTH + FIELD_LEFT; x++) {
    mvaddch(FIELD_TOP - 1, x, ACS_HLINE);
    mvaddch(FIELD_HEIGHT + FIELD_TOP, x, ACS_HLINE);
  }

  for (int y = FIELD_TOP; y < FIELD_HEIGHT + FIELD_TOP; y++) {
    mvaddch(y, FIELD_LEFT - 1, ACS_VLINE);
    mvaddch(y, FIELD_WIDTH * CELL_WIDTH + FIELD_LEFT, ACS_VLINE);
  }

  mvaddch(FIELD_TOP - 1, FIELD_LEFT - 1, ACS_ULCORNER);
  mvaddch(FIELD_HEIGHT + FIELD_TOP, FIELD_LEFT - 1, ACS_LLCORNER);
  mvaddch(FIELD_HEIGHT + FIELD_TOP, FIELD_WIDTH * CELL_WIDTH + FIELD_LEFT,
          ACS_LRCORNER);
  mvaddch(FIELD_TOP - 1, FIELD_WIDTH * CELL_WIDTH + FIELD_LEFT, ACS_URCORNER);

  refresh();
}

void printControlTips() {
  attron(A_BOLD);
  mvprintw(FIELD_BOTTOM - 6, WINDOW_WIDTH + 2, "  Control  buttons");
  attroff(A_BOLD);
  mvprintw(FIELD_BOTTOM - 4, WINDOW_WIDTH + 2, "< Enter >   - choose");
  mvprintw(FIELD_BOTTOM - 3, WINDOW_WIDTH + 2, "< Arrow >   - move");
  mvprintw(FIELD_BOTTOM - 2, WINDOW_WIDTH + 2, "< Space >   - rotate");
  mvprintw(FIELD_BOTTOM - 1, WINDOW_WIDTH + 2, "  < P >     - pause");
  mvprintw(FIELD_BOTTOM, WINDOW_WIDTH + 2, " < Esc >    - exit");
}

void printMainMenu(int pause_screen) {
  attron(A_BOLD);
  mvprintw(3, 7, "GAME: TETRIS");
  attroff(A_BOLD);
  mvprintw(FIELD_TOP, FIELD_RIGHT + 3, "Record");
  mvprintw(FIELD_TOP + 1, FIELD_RIGHT + 3, "%10d", 0);
  mvprintw(FIELD_TOP + 3, FIELD_RIGHT + 3, "Score");
  mvprintw(FIELD_TOP + 4, FIELD_RIGHT + 3, "%10d", 0);
  mvprintw(FIELD_TOP + 6, FIELD_RIGHT + 3, "Level");
  mvprintw(FIELD_TOP + 7, FIELD_RIGHT + 3, "%10d", 0);
  mvprintw(FIELD_TOP + 9, FIELD_RIGHT + 3, "Next");

  printLogo();

  if (pause_screen == 1) {
    mvprintw(11, 10, " Exit ");
    attron(COLOR_PAIR(7));
    mvprintw(9, 10, " Play ");
    attroff(COLOR_PAIR(7));
  } else {
    mvprintw(9, 10, " Play ");
    attron(COLOR_PAIR(7));
    mvprintw(11, 10, " Exit ");
    attroff(COLOR_PAIR(7));
  }

  refresh();
}

void printLogo() {
  attron(COLOR_PAIR(3));
  mvprintw(15, 10, "  ");
  mvprintw(16, 10, "    ");
  mvprintw(17, 10, "  ");

  attroff(COLOR_PAIR(3));

  attron(COLOR_PAIR(5));
  mvprintw(20, 4, "    ");
  mvprintw(21, 4, "    ");
  attroff(COLOR_PAIR(5));

  attron(COLOR_PAIR(6));
  mvprintw(19, 20, "  ");
  mvprintw(20, 20, "  ");
  mvprintw(21, 18, "    ");
  attroff(COLOR_PAIR(6));
}

void printField(GameInfo_t *game) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (game->field[i][j] == 0) {
        mvprintw(FIELD_TOP + i, FIELD_LEFT + j * CELL_WIDTH, "  ");
      } else {
        attron(COLOR_PAIR(game->field[i][j]));
        mvprintw(FIELD_TOP + i, FIELD_LEFT + j * CELL_WIDTH, "  ");
        attroff(COLOR_PAIR(game->field[i][j]));
      }
    }
  }

  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      attron(COLOR_PAIR(game->next[i][j]));
      mvprintw(FIELD_TOP + 10 + i, FIELD_RIGHT + 3 + j * CELL_WIDTH, "  ");
      attroff(COLOR_PAIR(game->next[i][j]));
    }
  }

  mvprintw(FIELD_TOP + 1, FIELD_RIGHT + 3, "%10d", game->high_score);
  mvprintw(FIELD_TOP + 4, FIELD_RIGHT + 3, "%10d", game->score);
  mvprintw(FIELD_TOP + 7, FIELD_RIGHT + 3, "%10d", game->level);
}

void printTetromino(GameInfo_t *tetris, Tetromino_t *tetromino) {
  int ghost_shift = 0;
  int flag = 0;

  for (int k = 1; k < FIELD_HEIGHT && !flag; k++) {
    for (int i = 0; i < TETR_HEIGHT && !flag; i++) {
      for (int j = 0; j < TETR_WIDTH && !flag; j++) {
        checkGhostPlace(tetris, tetromino, i, j, k, &flag);
      }
    }
    if (flag == 0) ghost_shift++;
  }

  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      if (tetromino->shape[i][j] != 0 && ghost_shift != 0) {
        mvprintw(tetromino->y - 2 + i + ghost_shift,
                 tetromino->x - 2 * CELL_WIDTH + j * CELL_WIDTH, "[]");
      }
    }
  }

  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      if (tetromino->shape[i][j] != 0 && (tetromino->y - 2 + i) != 1) {
        attron(COLOR_PAIR(tetromino->shape[i][j]));
        mvprintw(tetromino->y - 2 + i,
                 tetromino->x - 2 * CELL_WIDTH + j * CELL_WIDTH, "  ");
        attroff(COLOR_PAIR(tetromino->shape[i][j]));
      }
    }
  }
}

void checkGhostPlace(GameInfo_t *tetris, Tetromino_t *tetromino, int i, int j,
                     int k, int *flag) {
  if (tetromino->shape[i][j] != 0) {
    int x_cor = (tetromino->x - 2 * CELL_WIDTH - FIELD_LEFT) / CELL_WIDTH + j;
    int y_cor = tetromino->y - 2 + i - FIELD_TOP + k;
    if (y_cor >= FIELD_HEIGHT)
      *flag = 1;
    else if (y_cor >= 0 && tetris->field[y_cor][x_cor] != 0)
      *flag = 1;
  }
}

void printPauseMenu(int pause_screen) {
  clearGameInfo();

  attron(A_BOLD);
  mvprintw(3, 8, "PAUSE MENU");
  attroff(A_BOLD);

  printLogo();

  if (pause_screen == 1) {
    attron(COLOR_PAIR(7));
    mvprintw(9, 8, " Continue ");
    attroff(COLOR_PAIR(7));
    mvprintw(11, 10, " Exit ");
  } else {
    mvprintw(9, 8, " Continue ");
    attron(COLOR_PAIR(7));
    mvprintw(11, 10, " Exit ");
    attroff(COLOR_PAIR(7));
  }
}

void printGameOverScreen(GameInfo_t *tetris) {
  clearGameInfo();

  attron(A_BOLD);
  mvprintw(3, 9, "GAME OVER");
  mvprintw(12, 8, "Last record");
  attroff(A_BOLD);

  if (tetris->score > tetris->high_score) {
    mvprintw(4, 9, "Congrats!");
    mvprintw(5, 8, "New record!");
  }

  attron(A_UNDERLINE);
  mvprintw(7, 5, "level %10d", tetris->level);
  mvprintw(8, 5, "score %10d", tetris->score);
  mvprintw(13, 5, "score %10d", tetris->high_score);
  attroff(A_UNDERLINE);

  if (tetris->pause == 1) {
    attron(COLOR_PAIR(7));
    mvprintw(16, 8, " New game ");
    attroff(COLOR_PAIR(7));
    mvprintw(18, 10, " Exit ");
  } else {
    mvprintw(16, 8, " New game ");
    attron(COLOR_PAIR(7));
    mvprintw(18, 10, " Exit ");
    attroff(COLOR_PAIR(7));
  }
}

void clearGameInfo() {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      mvprintw(FIELD_TOP + i, FIELD_LEFT + j * CELL_WIDTH, "  ");
    }
  }

  for (int i = 0; i < TETR_HEIGHT; i++) {
    for (int j = 0; j < TETR_WIDTH; j++) {
      mvprintw(FIELD_TOP + 10 + i, FIELD_RIGHT + 3 + j * CELL_WIDTH, "  ");
    }
  }
}