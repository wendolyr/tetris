/**
 * @file matrix.h
 * @brief Header file for all matrix function
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

/**
 * @brief Codes for matrix functions results
 */
typedef enum { ST_OK = 0, ST_ERROR = 1 } status_code;

/**
 * @brief Allocate memory for matrix and fills with zero values
 * @param rows - number of rows
 * @param columns - number of columns
 * @param code - pointer to status code
 * @return ST_OK if memory allocated successfully and ST_ERROR if didn't
 */
int **createMatrix(int rows, int columns, int *code);

/**
 * @brief Turn matrix counterclockwise
 * @param rows - number of rows
 * @param columns - number of columns
 * @param result - resulting turned matrix
 * @return ST_OK if there are no errors inside the function and ST_ERROR
 * otherwise
 * @warning Works only with square matrix, otherwise may be segfault
 */
int turnLeftMatrix(int rows, int columns, int **result);

/**
 * @brief Turn matrix clockwise
 * @param rows - number of rows
 * @param columns - number of columns
 * @param result - resulting turned matrix
 * @return ST_OK if there are no errors inside the function and ST_ERROR
 * otherwise
 * @warning Works only with square matrix, otherwise may be segfault
 */
int turnRightMatrix(int rows, int columns, int **result);

#endif