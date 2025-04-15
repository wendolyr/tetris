/**
 * @file test._h
 * @brief Header for all tests of backend functions
 */

#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "../headers/backend.h"

/**
 * @brief FSM functions tests
 */
Suite *fsmTests();

/**
 * @brief matrix functions tests
 */
Suite *matrixTests();

/**
 * @brief menu interaction functions tests
 */
Suite *menuInteractionTests();

/**
 * @brief others backend functions tests
 */
Suite *backendTests();

#endif