/**
 * @file tetris.h
 * @brief Header file for entry point for the game
 */

#ifndef TETRIS_H
#define TETRIS_H

#include "backend.h"
#include "frontend.h"

/**
 * @brief Game loop function
 */
void launch_game();

/**
 * @brief Player input processing
 */
void playerInput(int state);

#endif