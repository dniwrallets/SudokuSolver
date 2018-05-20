/**
 * Sudoku class implementation
 * 
 * 
 * 2018-05-19
 * John Y
 */


#include "Sudoku.hpp"

#include <map>


const int Sudoku::GRID_DIMENSION = 9;
const int Sudoku::BOX_DIMENSION = 3;
const int Sudoku::NUM_BOXES = 9;
const int Sudoku::MIN_VALUE = 1;
const int Sudoku::MAX_VALUE = 9;
const int Sudoku::EMPTY_VALUE = 0;


Sudoku::Sudoku()
{
}


Sudoku::Sudoku(int** p)
{
	puzzle = new int*[GRID_DIMENSION];
	solution = new int*[GRID_DIMENSION];
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		puzzle[i] = new int[GRID_DIMENSION];
		solution[i] = new int[GRID_DIMENSION];
	}
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			puzzle[row][col] = p[row][col];
		}
	}
	resetSolution();
}


Sudoku::~Sudoku()
{
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		delete[] puzzle[i];
		delete[] solution[i];
	}
	delete[] puzzle;
	delete[] solution;
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


int **Sudoku::getPuzzle()
{
	int **p = new int*[GRID_DIMENSION];
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		p[i] = new int[GRID_DIMENSION];
	}
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			p[row][col] = puzzle[row][col];
		}
	}
	return p;
}


int **Sudoku::getSolution()
{
	int **s = new int*[GRID_DIMENSION];
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		s[i] = new int[GRID_DIMENSION];
	}
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			s[row][col] = solution[row][col];
		}
	}
	return s;
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
	int previousValue = getCell(row, col);
	solution[row][col] = value;
	if (isValid())
	{
		return true;
	}
	solution[row][col] = previousValue;
	return false;
}


bool Sudoku::eraseCell(int row, int col)
{
	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return false;
	}
	solution[row][col] = EMPTY_VALUE;
	return true;
}


void Sudoku::resetSolution()
{
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			solution[row][col] = EMPTY_VALUE;
		}
	}
}


bool Sudoku::hasValidRows()
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


bool Sudoku::hasValidCols()
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


bool Sudoku::hasValidBoxes()
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


bool Sudoku::isValid()
{
	return hasValidRows() && hasValidCols() && hasValidBoxes();
}