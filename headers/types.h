/**
 * @file types.h
 * @brief Header file for all used objects and data types
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Describes the possible actions of the  player when pressing the
 * buttons
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Describes the possible states of finite state machine
 */
typedef enum {
  MainMenu,
  Spawn,
  Moving,
  PauseMenu,
  Attaching,
  GameOver,
  Exit,
} Fsm_t;

/**
 * @brief Describes the information about game field
 * @details field - pointer at the game field matrix HEIGHT*WIDTH
 * @details next - pointer at the next tetromino that will be spawned
 * @details score - player score
 * @details high_score - local game record
 * @details level - current game level from 1 to 10
 * @details speed - current game speed
 * @details pause - pause state for menu interaction
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Describes the information about tetromino
 * @details shape - pointer at the tetromino TETR_HEIGHT*TETR_WIDTH
 * @details index - type of tetromino from 1 to 7
 * @details rotation_stage - current stage of rotation
 * @details y - tetromino center y coordinate
 * @details x - tetromino center x coordinate
 */
typedef struct {
  int **shape;
  int index;
  int rotation_stage;
  int y;
  int x;
} Tetromino_t;

/**
 * @brief Describes the all information about the game
 * @details tetris - information about game field
 * @details tetromino - information about current tetromino
 * @details state - current state of the game
 */
typedef struct {
  GameInfo_t *tetris;
  Tetromino_t *tetromino;
  Fsm_t state;
} Singleton_t;

#endif