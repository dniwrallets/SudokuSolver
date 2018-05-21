/**
 * Sudoku class test driver
 * 
 * 
 * 2018-05-20
 * John Y
 */


#include <iostream>
#include <assert.h>

#include "../../main/cpp/Sudoku.hpp"
#include "../../main/cpp/UI.hpp"


void convertPuzzleDimension(int *p1d, int **p2d)
{
	for (int i = 0; i < Sudoku::GRID_DIMENSION * Sudoku::GRID_DIMENSION; i++)
	{
		p2d[i/Sudoku::GRID_DIMENSION][i % Sudoku::GRID_DIMENSION] = p1d[i];
	}
}


int main(int argc, char const *argv[])
{
	int puzzle1d[81] = {0,0,4,0,0,6,0,0,2,
                        0,3,0,0,5,0,0,7,0,
                        2,0,0,9,0,0,3,0,0,
                        9,0,0,4,0,0,7,0,0,
                        0,4,0,0,8,0,0,3,0,
                        0,0,1,0,0,5,0,0,8,
                        0,0,9,0,0,3,0,0,7,
                        0,7,0,0,2,0,0,6,0,
                        1,0,0,6,0,0,8,0,0};
	int **puzzle = new int*[Sudoku::GRID_DIMENSION];
	for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
	{
		puzzle[i] = new int[Sudoku::GRID_DIMENSION];
	}
	convertPuzzleDimension(puzzle1d, puzzle);

	std::cout << "Building Puzzle:" << std::endl;
	Sudoku s(puzzle);
	std::cout << "Done" << std::endl;
	printSudoku(s);

	assert(s.getNumberOfEmptyCells() == 54);

	s.fillCell(0, 0, 5);
	s.fillCell(0, 1, 9);
	s.fillCell(0, 3, 7);
	s.fillCell(0, 4, 3);
	s.fillCell(0, 6, 1);
	s.fillCell(0, 7, 8);


	s.fillCell(1, 0, 8);
	s.fillCell(1, 2, 6);
	s.fillCell(1, 3, 2);
	s.fillCell(1, 5, 1);
	s.fillCell(1, 6, 9);
	s.fillCell(1, 8, 4);

	s.fillCell(2, 1, 1);

	printSudoku(s);

	assert(s.getNumberOfEmptyCells() == 41);

	assert(!s.fillCell(2, 2, 1));
	assert(!s.fillCell(2, 2, 2));
	assert(!s.fillCell(2, 2, 3));
	assert(!s.fillCell(2, 2, 4));
	assert(!s.fillCell(2, 2, 5));
	assert(!s.fillCell(2, 2, 6));
	assert(!s.fillCell(2, 2, 8));
	assert(!s.fillCell(2, 2, 9));
	assert(s.fillCell(2, 2, 7));

	s.fillCell(2, 4, 4);
	s.fillCell(3, 4, 6);
	s.fillCell(6, 4, 1);
	s.fillCell(8, 4, 7);

	assert(!s.fillCell(5, 4, 1));
	assert(!s.fillCell(5, 4, 2));
	assert(!s.fillCell(5, 4, 3));
	assert(!s.fillCell(5, 4, 4));
	assert(!s.fillCell(5, 4, 5));
	assert(!s.fillCell(5, 4, 6));
	assert(!s.fillCell(5, 4, 7));
	assert(!s.fillCell(5, 4, 8));
	assert(s.fillCell(5, 4, 9));

	s.fillCell(2, 7, 5);
	s.fillCell(2, 8, 6);

	assert(!s.fillCell(2, 5, 1));
	assert(!s.fillCell(2, 5, 2));
	assert(!s.fillCell(2, 5, 3));
	assert(!s.fillCell(2, 5, 4));
	assert(!s.fillCell(2, 5, 5));
	assert(!s.fillCell(2, 5, 6));
	assert(!s.fillCell(2, 5, 7));
	assert(!s.fillCell(2, 5, 9));

	assert(s.fillCell(2, 5, 8));

	printSudoku(s);
	assert(s.getNumberOfEmptyCells() == 32);

	s.resetSolution();
	assert(s.getNumberOfEmptyCells() == 54);
	return 0;
}