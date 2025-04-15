#include "headers/tetris.h"

int main() {
  createWindow();
  launch_game();
  endwin();

  return 0;
}

void launch_game() {
  srand(time(NULL));
  GameInfo_t tetris = {0};
  do {
    tetris = updateCurrentState();
    if (tetris.field != NULL) {
      Tetromino_t tetromino = updateTetrominoState();
      int fsm_state = updateFsmState();
      gameDisplay(&tetris, &tetromino, fsm_state);
      playerInput(fsm_state);
    }

  } while (tetris.field != NULL);
}

void playerInput(int state) {
  UserAction_t action = NO_ACTION;
  bool hold = false;

  if (timer() && state == Moving) {
    action = Down;
  } else {
    int button = getch();
    timeout(1);
    switch (button) {
      case KEY_PAUSE_1:
        action = Pause;
        break;
      case KEY_PAUSE_2:
        action = Pause;
        break;
      case KEY_ESC:
        action = Terminate;
        break;
      case KEY_LEFT:
        action = Left;
        break;
      case KEY_RIGHT:
        action = Right;
        break;
      case KEY_UP:
        action = Up;
        break;
      case KEY_DOWN:
        action = Down;
        hold = true;
        break;
      case KEY_SPACE:
        action = Action;
        break;
      case KEY_START:
        action = Start;
        break;
    }
  }

  userInput(action, hold);
}
