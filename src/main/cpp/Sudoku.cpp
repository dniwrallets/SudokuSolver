/**
 * Sudoku class implementation
 * 
 * 
 * 2018-05-21
 * John Y
 */


#include "Sudoku.hpp"

#include <cassert>

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
	numberOfEmptyCells = 0;
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		puzzle[row] = new int[GRID_DIMENSION];
		solution[row] = new int[GRID_DIMENSION];
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			puzzle[row][col] = p[row][col];
			if (puzzle[row][col] == EMPTY_VALUE)
			{
				numberOfEmptyCells++;
			}
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
	return numberOfEmptyCells == 0;
}


int Sudoku::getNumberOfEmptyCells()
{
	return numberOfEmptyCells;
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
	assert(row >= 0 && row < GRID_DIMENSION);
	assert(col >= 0 && col < GRID_DIMENSION);

	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return puzzle[row][col];
	}
	return solution[row][col];
}


bool Sudoku::fillCell(int row, int col, int value)
{
	assert(row >= 0 && row < GRID_DIMENSION);
	assert(col >= 0 && col < GRID_DIMENSION);
	assert(value >= MIN_VALUE && value <= MAX_VALUE);

	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return false;
	}
	int previousValue = getCell(row, col);
	solution[row][col] = value;
	if (isValidRow(row) && isValidCol(col) && 
		isValidBox(row / BOX_DIMENSION * BOX_DIMENSION + 
		col / BOX_DIMENSION))
	{
		numberOfEmptyCells--;
		return true;
	}
	solution[row][col] = previousValue;
	return false;
}


bool Sudoku::eraseCell(int row, int col)
{
	assert(row >= 0 && row < GRID_DIMENSION);
	assert(col >= 0 && col < GRID_DIMENSION);

	if (puzzle[row][col] != EMPTY_VALUE)
	{
		return false;
	}
	numberOfEmptyCells++;
	solution[row][col] = EMPTY_VALUE;
	return true;
}


void Sudoku::resetSolution()
{
	numberOfEmptyCells = 0;
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		for (int col = 0; col < GRID_DIMENSION; col++)
		{
			solution[row][col] = EMPTY_VALUE;
			if (puzzle[row][col] == EMPTY_VALUE)
			{
				numberOfEmptyCells++;
			}
		}
	}
}


bool Sudoku::isValidRow(int row)
{
	assert(row >= 0 && row < GRID_DIMENSION);

	bool choiceTable[] = 
	{
		false, false, false, false, false, 
		false, false, false, false
	};
	for (int col = 0; col < GRID_DIMENSION; col++)
	{
		if (getCell(row, col) != EMPTY_VALUE)
		{
			if (choiceTable[getCell(row, col) - 1])
			{
				return false;
			}
			choiceTable[getCell(row, col) - 1] = true;
		}
	}
	return true;
}


bool Sudoku::isValidCol(int col)
{
	assert(col >= 0 && col < GRID_DIMENSION);

	bool choiceTable[] = 
	{
		false, false, false, false, false, 
		false, false, false, false
	};
	for (int row = 0; row < GRID_DIMENSION; row++)
	{
		if (getCell(row, col) != EMPTY_VALUE)
		{
			if (choiceTable[getCell(row, col) - 1])
			{
				return false;
			}
			choiceTable[getCell(row, col) - 1] = true;
		}
	}
	return true;
}


bool Sudoku::isValidBox(int box)
{
	assert(box >= 0 && box < NUM_BOXES);

	bool choiceTable[] = 
	{
		false, false, false, false, false, 
		false, false, false, false
	};
	int starting_row = (box / BOX_DIMENSION) * BOX_DIMENSION;
	int starting_col = (box % BOX_DIMENSION) * BOX_DIMENSION;
	for (int row = starting_row; row < starting_row + BOX_DIMENSION; row++)
	{
		for (int col = starting_col; col < starting_col + BOX_DIMENSION; 
			col++)
		{
			if (getCell(row, col) != EMPTY_VALUE)
			{
				if (choiceTable[getCell(row, col) - 1])
				{
					return false;
				}
				choiceTable[getCell(row, col) - 1] = true;
			}
		}
	}
	return true;
}


bool Sudoku::isValid()
{
	for (int i = 0; i < GRID_DIMENSION; i++)
	{
		if (!isValidRow(i) || !isValidRow(i) || !isValidBox(i))
		{
			return false;
		}
	}
	return true;
}