/**
 * @file defines.h
 * @brief Header for all defines
 */

#ifndef DEFINES_H
#define DEFINES_H

/*

SIZES

*/

/**
 * @brief total window height
 */
#define WINDOW_HEIGHT 24

/**
 * @brief total window width
 */
#define WINDOW_WIDTH 37

/**
 * @brief height of the game field
 */
#define FIELD_HEIGHT 20

/**
 * @brief width of the game field
 */
#define FIELD_WIDTH 10

/**
 * @brief width of one cell
 */
#define CELL_WIDTH 2

/**
 * @brief total tetromino height
 */
#define TETR_HEIGHT 5

/**
 * @brief total tetromino width
 */
#define TETR_WIDTH 5

/*

COORDINATES

*/

/**
 * @brief y coordinate of the first line of the field
 */
#define FIELD_TOP 2

/**
 * @brief y coordinate of the last line of the field
 */
#define FIELD_BOTTOM 21

/**
 * @brief x coordinate of the first column of the field
 */
#define FIELD_LEFT 3

/**
 * @brief x coordinate of the last column of the field
 */
#define FIELD_RIGHT 22

/**
 * @brief start x coordinate of the tetromino center
 */
#define TETR_SPAWN_X 13

/**
 * @brief start y coordinate of the tetromino center
 */
#define TETR_SPAWN_Y 2

/*

ACTION BUTTONS

*/

/**
 * @brief button to rotate tetromino
 */
#define KEY_SPACE ' '

/**
 * @brief button to pause
 */
#define KEY_PAUSE_2 'p'

/**
 * @brief CAPSLOCKed button to pause
 */
#define KEY_PAUSE_1 'P'

/**
 * @brief menu button to select an action
 */
#define KEY_START '\n'

/**
 * @brief button to exit the game
 */
#define KEY_ESC 27

/**
 * @brief action when the button is not pressed
 */
#define NO_ACTION 10

/*

PAUSE STATES

*/

/**
 * @brief no menu state
 */
#define NO_PAUSE 0

/**
 * @brief menu state with the first highlight action
 */
#define PAUSE_ONE 1

/**
 * @brief menu state with the second highlight action
 */
#define PAUSE_TWO 2

/*

LEVEL AND SCORE

*/

/**
 * @brief max level of the game
 */
#define MAX_LEVEL 10

/**
 * @brief required points to level up
 */
#define LEVELUP_SCORE 600

/**
 * @brief points for one destroyed row
 */
#define SCORE_ONE 100

/**
 * @brief points for two destroyed rows
 */
#define SCORE_TWO 300

/**
 * @brief points for three destroyed rows
 */
#define SCORE_THREE 700

/**
 * @brief points for four destroyed rows
 */
#define SCORE_FOUR 1500

/**
 * @brief directory for storing the game record
 */
#define HIGH_SCORE_DIR "build/.high_score.txt"

#endif