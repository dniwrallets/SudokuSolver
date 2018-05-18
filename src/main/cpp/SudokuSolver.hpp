/**
 * SudokuSolver function declaration.
 * 
 * 
 * 2018-05-17
 * John Y
 */


#pragma once

#include "Sudoku.hpp"


/**
 * @brief      Solves the Sudoku game via backtracking algorithm.
 *
 * @param      game  The Sudoku game
 *
 * @return     True if solved, false if no solution exists.
 */
bool solve(Sudoku &game);