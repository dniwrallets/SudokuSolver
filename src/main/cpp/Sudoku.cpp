/**
 * Sudoku class implementation
 * 
 * 
 * 2018-05-17
 * John Y
 */


#include "Sudoku.hpp"


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
	return false;
}


int Sudoku::getCell(int row, int col)
{
	return 0;
}


bool Sudoku::fillCell(int row, int col, int value)
{
	return false;
}


bool Sudoku::eraseCell(int row, int col)
{
	return false;
}


void Sudoku::reset_solution()
{

}


bool Sudoku::has_valid_rows()
{
	return false;
}


bool Sudoku::has_valid_cols()
{
	return false;
}


bool Sudoku::has_valid_boxes()
{
	return false;
}


bool Sudoku::is_valid()
{
	return false;
}