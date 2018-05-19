/**
 * SudokuSolver function implementation.
 * 
 * 
 * 2018-05-19
 * John Y
 */


#include "SudokuSolver.hpp"

#include <map>
#include <vector>


void findChoices(Sudoku &game, int row, int col, 
	std::vector<int> &possibleChoices)
{
	if (game.getCell(row, col) != Sudoku::EMPTY_VALUE) 
	{
		return;
	}
	std::map<int, bool> possibilities;
	for (int i = Sudoku::MIN_VALUE; i <= Sudoku::MAX_VALUE; i++)
	{
		possibilities.insert(std::make_pair(i, true));
	}
	for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
	{
		if (game.getCell(i, col) != Sudoku::EMPTY_VALUE)
		{
			possibilities[game.getCell(i, col)] = false;
		}
		if (game.getCell(row, i) != Sudoku::EMPTY_VALUE)
		{
			possibilities[game.getCell(row, i)] = false;
		}
	}
	int box = row / Sudoku::NUM_BOXES * Sudoku::BOX_DIMENSION + 
		col / Sudoku::NUM_BOXES;
	int startingRow = (box / Sudoku::BOX_DIMENSION) * Sudoku::BOX_DIMENSION;
	int startingCol = (box % Sudoku::BOX_DIMENSION) * Sudoku::BOX_DIMENSION;
	for (int row = startingRow; row < startingRow + Sudoku::BOX_DIMENSION; row++)
	{
		for (int col = startingCol; col < startingCol + Sudoku::BOX_DIMENSION;
			col++)
		{
			if (game.getCell(row, col) != Sudoku::EMPTY_VALUE)
			{
				possibilities[game.getCell(row, col)] = false;
			}
		}
	}
	for (std::map<int, bool>::iterator it = possibilities.begin();
	 it != possibilities.end(); it++)
	{
		if (it->second)
		{
			possibleChoices.push_back(it->first);
		}
	}
}


bool solve(Sudoku &game)
{
	if (game.isSolved())
	{
		return true;
	}
	const int NOT_FOUND = -1;
	int emptyCellRow = NOT_FOUND;
	int emptyCellCol = NOT_FOUND;
	for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
	{
		for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
		{
			if (game.getCell(row, col) == Sudoku::EMPTY_VALUE)
			{
				emptyCellRow = row;
				emptyCellCol = col;
				break;
			}
		}
	}
	if (emptyCellRow == NOT_FOUND || emptyCellCol == NOT_FOUND)
	{
		return false;
	}
	std::vector<int> possibleChoices = {};
	findChoices(game, emptyCellRow, emptyCellCol, possibleChoices);
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