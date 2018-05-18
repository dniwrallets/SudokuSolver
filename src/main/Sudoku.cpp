/**
 * Sudoku class implementation
 * 
 * 
 * 2018-05-17
 * John Y
 */


#include "Sudoku.hpp"

#include <map>


const int GRID_DIMENSION = 9;
const int BOX_DIMENSION = 3;
const int NUM_BOXES = 9;
const int MIN_VALUE = 1;
const int MAX_VALUE = 9;
const int EMPTY_VALUE = 0;


Sudoku::Sudoku()
{
	puzzle = new int*[GRID_DIMENSION];
	solution = new int*[GRID_DIMENSION];
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		puzzle[i] = new int[GRID_DIMENSION];
		solution[i] = new int[GRID_DIMENSION];
	}
}


Sudoku::Sudoku(std::string fileName)
{

}


void Sudoku::print()
{

}


std::string Sudoku::getString()
{
	return nullptr;
}


bool Sudoku::isSolved()
{
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			if (getCell(row, col) == EMPTY_VALUE)
			{
				return false;
			}
		}
	}
	return true;
}


int Sudoku::getCell(int row, int col)
{
	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return puzzle[row][col];
	}
	return solution[row][col];
}


bool Sudoku::fillCell(int row, int col, int value)
{
	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return false;
	}
	solution[row][col] = value;
}


bool Sudoku::eraseCell(int row, int col)
{
	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return false;
	}
	solution[row][col] = EMPTY_VALUE;
}


void Sudoku::reset_solution()
{
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			solution[row][col] = EMPTY_VALUE;
		}
	}
}


bool Sudoku::has_valid_rows()
{
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		std::map<int, bool> possibilities;
		for (int i = MIN_VALUE; i <= MAX_VALUE; i++)
		{
			possibilities.insert(std::make_pair(i, false));
		}
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			if (getCell(row, col) != EMPTY_VALUE)
			{
				if (possibilities.find(getCell(row, col))->second)
				{
					return false;
				}
				possibilities[getCell(row, col)] = true;
			}
		}
	}
	return true;
}


bool Sudoku::has_valid_cols()
{
	for (int col = 0; col < GRID_DIMENSION; col++)
	{
		std::map<int, bool> possibilities;
		for (int i = MIN_VALUE; i <= MAX_VALUE; i++)
		{
			possibilities.insert(std::make_pair(i, false));
		}
		for (int row = 0; row < GRID_DIMENSION; row++)
		{
			if (getCell(row, col) != EMPTY_VALUE)
			{
				if (possibilities.find(getCell(row, col))->second)
				{
					return false;
				}
				possibilities[getCell(row, col)] = true;
			}
		}
	}
	return true;
}


bool Sudoku::has_valid_boxes()
{
	for (int box = 0; box < NUM_BOXES; box++)
	{
		int starting_row = (box / BOX_DIMENSION) * BOX_DIMENSION;
		int starting_col = (box % BOX_DIMENSION) * BOX_DIMENSION;
		std::map<int, bool> possibilities;
		for (int i = MIN_VALUE; i <= MAX_VALUE; i++)
		{
			possibilities.insert(std::make_pair(i, false));
		}
		for (int row = starting_row; row < starting_row + BOX_DIMENSION; row++)
		{
			for (int col = starting_col; col < starting_col + BOX_DIMENSION; 
				col++)
			{
				if (getCell(row, col) != EMPTY_VALUE)
				{
					if (possibilities.find(getCell(row, col))->second)
					{
						return false;
					}
					possibilities[getCell(row, col)] = true;
				}
			}
		}
	}
	return true;
}


bool Sudoku::is_valid()
{
	return has_valid_row() && has_valid_cols() && has_valid_boxes();
}






















