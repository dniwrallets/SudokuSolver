/**
 * SudokuSolver function declaration.
 * 
 * 
 * 2018-05-19
 * John Y
 */


#pragma once

#include "Sudoku.hpp"


/**
 * @brief      Finds all possible valid values that can be filled into the cell
 *             at row, col in game. Add all the values into possibleChoices.
 *
 * @param      game             The Sudoku game
 * @param[in]  row              The row position
 * @param[in]  col              The col column position
 * @param      possibleChoices  A vector pointer that contains all possible 
 *             choices.
 */
void findChoices(Sudoku &game, int row, int col, 
	std::vector<int> &possibleChoices);


/**
 * @brief      Solves the Sudoku game via backtracking algorithm.
 *
 * @param      game  The Sudoku game
 *
 * @return     True if solved, false if no solution exists.
 */
bool solveSudoku(Sudoku &game);