/**
 * @file backend.h
 * @brief Header file for all backend functions
 */

#ifndef BACKEND_H
#define BACKEND_H

#ifdef __linux__
#define _POSIX_C_SOURCE 199309L
#endif

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "defines.h"
#include "matrix.h"
#include "types.h"

/*

FSM functions

*/

/**
 * @brief sets one of the form tetromino
 * @param color - generated color
 * @param type - generated type of tetromino
 * @param shape - tetromino shape matrix
 */
void settingTetromino(int color, int type, int **shape);

/**
 * @brief generates and spawns tetrominoes
 * @param game - pointer to struct that contains tetromino struct
 */
void spawningTetromino(Singleton_t *game);

/**
 * @brief moves current tetromino one pixel down
 * @param game - pointer to all information about the game
 * @return 0 if can move down and 1 otherwise
 */
int movingDown(Singleton_t *game);

/**
 * @brief moves current tetromino one pixel left
 * @param game - pointer to all information about the game
 */
void movingLeft(Singleton_t *game);

/**
 * @brief moves current tetromino one pixel right
 * @param game - pointer to all information about the game
 */
void movingRight(Singleton_t *game);

/**
 * @brief rotate current tetromino
 * @param game - pointer to all information about the game
 */
void rotatingTetromino(Singleton_t *game);

/**
 * @brief checks possibility to rotate tetromino near edges
 * @param game - pointer to all information about the game
 * @param permission - pointer to variable that tracks the total possibility
 */
void rotatingNearEdges(Singleton_t *game, int *permission);

/**
 * @brief checks for collision current tetromino with field
 * @param game - pointer to all information about the game
 * @param permission - pointer to variable that tracks the total possibility
 * @return 0 if there are no collision and 1 otherwise
 */
int collisionCheck(Singleton_t *game, int *permission);

/**
 * @brief attaches tetriminoes to the field when can't move down
 * @param game - pointer to all information about the game
 * @return 0 if can attach tetromino and 1 if can't
 */
int attachingTetromino(Singleton_t *game);

/**
 * @brief checks if there are any filled lines after attaching tetromino
 * @param game - pointer to all information about the game
 */
void checkingFieldRows(Singleton_t *game);

/**
 * @brief destroys filled line on the field
 * @param tetris - pointer to current field info
 * @param row - line that needs to be destroyed
 */
void destroyRow(GameInfo_t *tetris, int row);

/**
 * @brief scoring if there are any destroyed lines
 * @param game - pointer to all information about the game
 * @param destroyed_rows - amount of destroyed lines
 */
void scoring(Singleton_t *game, int destroyed_rows);

/*

MAIN MENU INTERACTION

*/

/**
 * @brief buttons press processing in main menu
 * @param game - pointer to all information about the game
 * @param action - current player pressed button
 */
void mainMenuInteraction(Singleton_t *game, UserAction_t action);

/**
 * @brief buttons press processing in game over menu
 * @param game - pointer to all information about the game
 * @param action - current player pressed button
 */
void gameOverInteraction(Singleton_t *game, UserAction_t action);

/**
 * @brief button press processing in pause menu
 * @param game - pointer to all information about the game
 * @param action - current player pressed button
 */
void pauseInteraction(Singleton_t *game, UserAction_t action);

/*

OTHER BACKEND FUNCTIONS

*/

/**
 * @brief user input processing
 * @param action - current player pressed button
 * @param hold - holding button (true only when pressing down)
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief update information about game
 * @return struct that contains current params of the game
 */
GameInfo_t updateCurrentState();

/**
 * @brief update information about tetromino
 * @return struct that contains current information about tetromino
 */
Tetromino_t updateTetrominoState();

/**
 * @brief update information about game finite state
 * @return current state of FSM
 */
Fsm_t updateFsmState();

/**
 * @brief gets access to struct Singleton_t
 * @return pointer to Singleton_t struct
 */
Singleton_t *getState();

/**
 * allocates memory for GameInfo_t struct
 * @return ST_OK if memory allocated successfully and ST_ERROR otherwise
 */
int createGameInfo(GameInfo_t **tetris);

/**
 * allocates memory for Tetromino_t struct
 * @return ST_OK if memory allocated successfully and ST_ERROR otherwise
 */
int createTetromino(Tetromino_t **tetromino);

/**
 * @brief clear the field and reset all stats
 */
void prepareForNewGame();

/**
 * @brief frees all allocated memory
 */
void removeGame();

/**
 * @brief get high score from the file or set 0 if there is no such file
 * @param tetris - current game info
 */
void getHighScore(GameInfo_t *tetris);

/**
 * @brief save current score to the file if it's greater than the record
 * @param tetris - current game info
 */
void saveHighScore(GameInfo_t *tetris);

/**
 * @brief set timer depends of current speed
 */
int timer();

#endif