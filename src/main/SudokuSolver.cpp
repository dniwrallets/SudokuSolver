/**
 * SudokuSolver function implementation.
 * 
 * 
 * 2018-05-17
 * John Y
 */


#include "SudokuSolver.hpp"


/**
 * @brief      Finds all possible valid values that can be filled into the cell
 *             at row, col in game. Add all the values into possible_choices.
 *
 * @param      game             The Sudoku game
 * @param[in]  row              The row position
 * @param[in]  col              The col column position
 * @param      possibleChoices  A vector pointer that contains all possible 
 *             choices
 */
void find_possible_choices(Sudoku &game, int row, int col, 
	std::vector<int> &possibleChoices)
{
	if (game.getCell(row, col) != EMPTY_VALUE) 
	{
		return;
	}
	std::map<int, bool> possibilities;
	for (int i = MIN_VALUE; i <= MAX_VALUE; i++)
	{
		possibilities.insert(std::make_pair(i, true));
	}
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		if (game.getCell(i, col) != EMPTY_VALUE)
		{
			possibilities[game.getCell(i, col)] = false;
		}
		if (game.getCell(row, i) != EMPTY_VALUE)
		{
			possibilities[game.getCell(row, i)] = false;
		}
	}
	int box = row / NUM_BOXES * BOX_DIM + col / NUM_BOXES;
	int starting_row = (box / BOX_DIM) * BOX_DIM;
	int starting_col = (box % BOX_DIM) * BOX_DIM;
	for (int row = starting_row; row < starting_row + BOX_DIM; row++)
	{
		for (int col = starting_col; col < starting_col + BOX_DIM; col++)
		{
			if (game.getCell(row, col) != EMPTY_VALUE)
			{
				possibilities[game.getCell(row, col)] = false;
			}
		}
	}
	for (std::map<int, bool>::iterator it = possibilities.begin();
	 it != possibilities.end(); it++)
	{
		if (it.second)
		{
			possibleChoices.add(it.first);
		}
	}
}


bool solve(Sudoku &game)
{
	if (game.isSolved)
	{
		return true;
	}
	const int NOT_FOUND = -1;
	int emptyCellRow = NOT_FOUND;
	int emptyCellCol = NOT_FOUND;
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			if (game.getCell(row, col) == EMPTY_VALUE)
			{
				emptyCellRow = row;
				emptyCellCol = col;
				break;
			}
		}
	}
	if (emptyCellRow = NOT_FOUND || emptyCellCol == NOT_FOUND)
	{
		return false;
	}
	std::vector<int> possibleChoices = {};
	find_possible_choices(&game, emptyCellRow, emptyCellCol, &possibleChoices);
	for (int i = 0; i < possibleChoices.size(); i++) 
	{
		game.fillCell(emptyCellRow, emptyCellCol, possibleChoices.at(i));
		if (solve(game))
		{
			return true;
		}
		game.eraseCell(emptyCellRow, emptyCellCol);
	}
	return false;
}