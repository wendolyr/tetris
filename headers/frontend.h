/**
 * @file frontend.h
 * @brief Headers for all frontend functions
 */

#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "defines.h"
#include "types.h"

/**
 * @brief Turns on all ncurses settings
 */
void createWindow();

/**
 * @brief Prints frames for window and field
 */
void printFrames();

/**
 * @brief Prints used buttons in the game
 */
void printControlTips();

/**
 * @brief Prints some tetromino in main menu and pause menu
 */
void printLogo();

/**
 * @brief Prints screen depends of finite state
 * @param tetris - game params and field
 * @param tetromino - tetromino params
 * @param state - finite state
 */
void gameDisplay(GameInfo_t *tetris, Tetromino_t *tetromino, int state);

/**
 * @brief Prints main menu screen
 * @param pause_screen - type of printing screen
 */
void printMainMenu(int pause_screen);

/**
 * @brief Prints pause menu screen
 * @param pause_screen - type of printing screen
 */
void printPauseMenu(int pause_screen);

/**
 * @brief Prints game over screen
 * @param tetris - game params
 */
void printGameOverScreen(GameInfo_t *tetris);

/**
 * @brief Clears game field and next tetromino preview when pause
 */
void clearGameInfo();

/**
 * @brief Prints game field on the screen
 * @param game - game info and field filling
 */
void printField(GameInfo_t *game);

/**
 * @brief Prints tetromino on the screen
 * @param tetris - game field info
 * @param tetromino - tetromino position
 */
void printTetromino(GameInfo_t *tetris, Tetromino_t *tetromino);

/**
 * @brief Checks shifted position of ghost tetromino
 * @param tetris - game field info
 * @param tetromino - tetromino position
 * @param i - row of tetromino matrix
 * @param j - column of tetromino matrix
 * @param k - shifted tetromino position
 */
void checkGhostPlace(GameInfo_t *tetris, Tetromino_t *tetromino, int i, int j,
                     int k, int *flag);

#endif