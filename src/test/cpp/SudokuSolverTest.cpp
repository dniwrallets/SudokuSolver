/**
 * SudokuSolver test driver
 * 
 * 
 * 2018-05-20
 * John Y
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <time.h>

#include "../../main/cpp/Sudoku.hpp"
#include "../../main/cpp/SudokuSolver.hpp"
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
	
	int puzzleA1d[] =
	{
		6,0,0,0,0,8,9,4,0,
		9,0,0,0,0,6,1,0,0,
		0,7,0,0,4,0,0,0,0,
		2,0,0,6,1,0,0,0,0,
		0,0,0,0,0,0,2,0,0,
		0,8,9,0,0,2,0,0,0,
		0,0,0,0,6,0,0,0,5,
		0,0,0,0,0,0,0,3,0,
		8,0,0,0,0,1,6,0,0
	};
	int puzzleB1d[] =
	{
		0,0,2,8,0,0,0,0,0,
		0,3,0,0,6,0,0,0,7,
		1,0,0,0,0,0,0,4,0,
		6,0,0,0,9,0,0,0,0,
		0,5,0,6,0,0,0,0,9,
		0,0,0,0,5,7,0,6,0,
		0,0,0,3,0,0,1,0,0,
		0,7,0,0,0,6,0,0,8,
		4,0,0,0,0,0,0,2,0
	};
	int puzzleC1d[] =
	{
		0,2,0,3,0,0,0,0,0,
		4,0,0,0,5,0,0,0,0,
		0,0,6,0,0,1,7,0,0,
		5,0,0,2,0,0,0,1,0,
		0,3,0,0,0,0,0,4,0,
		0,0,1,0,0,6,8,0,0,
		0,0,9,0,0,0,0,7,0,
		0,0,0,1,0,0,9,0,0,
		0,0,0,0,0,9,0,6,8,
	};
	int puzzleD1d[] =
	{
		9,8,0,7,0,0,0,0,0,
		7,0,0,0,0,0,6,0,0,
		0,0,6,0,5,0,0,0,0,
		0,4,0,0,0,5,0,3,0,
		0,0,7,9,0,0,5,0,0,
		5,0,0,0,2,0,0,0,1,
		0,0,8,5,0,0,9,0,0,
		0,0,0,0,1,0,0,0,0,
		0,0,0,0,0,3,0,2,4
	};
	int puzzleE1d[] = 
	{
		5,0,0,0,0,6,0,2,9,
		0,6,0,0,0,0,0,0,7,
		0,0,1,0,9,4,0,0,0,
		7,0,0,1,0,0,9,0,2,
		0,2,0,0,0,0,0,4,0,
		4,0,0,0,0,0,6,0,0,
		0,0,0,0,2,0,0,0,8,
		0,0,0,0,0,1,3,0,0,
		8,3,0,0,0,5,0,0,0
	};
	int puzzleF2d[] =
	{
		4,1,0,9,0,6,0,0,0,
		0,0,0,0,0,0,0,7,0,
		0,0,5,0,4,0,0,0,0,
		6,0,0,0,0,0,5,9,0,
		0,0,0,0,5,0,0,0,1,
		8,0,4,0,0,3,0,0,0,
		0,0,0,3,0,0,0,0,2,
		9,0,8,0,0,0,0,0,0,
		0,3,0,0,0,0,6,0,0
	};
	int puzzleG1d[] =
	{
		0,0,0,0,0,0,0,0,8,
		0,0,0,0,4,0,7,0,6,
		0,0,7,0,0,8,0,9,0,
		0,0,1,0,0,6,0,0,9,
		0,5,0,0,0,0,0,0,0,
		3,0,0,2,0,0,0,1,0,
		0,0,6,0,0,1,9,0,0,
		2,0,0,0,3,0,0,0,0,
		0,4,0,5,0,0,0,7,0
	};
	int puzzleH1d[] =
	{
		0,2,0,3,0,0,0,0,0,
		4,0,0,0,5,0,0,0,0,
		0,0,6,0,0,1,7,0,0,
		5,0,0,2,0,0,0,1,0,
		0,3,0,0,0,0,0,4,0,
		0,0,1,0,0,6,8,0,0,
		0,0,9,0,0,0,0,7,0,
		0,0,0,1,0,0,9,0,0,
		0,0,0,0,0,9,0,6,8
	};
	int puzzleI1d[] =
	{
		0,0,0,1,0,0,5,3,0,
		5,0,0,0,9,0,0,0,2,
		0,8,0,0,6,0,0,4,0,
		0,0,4,5,0,0,0,0,0,
		2,0,0,0,0,0,0,0,7,
		0,0,0,0,0,6,8,0,0,
		0,3,0,0,2,0,0,6,0,
		8,0,0,0,5,0,0,0,3,
		0,7,5,0,0,4,0,0,0
	};
	int puzzleJ1d[] =
	{
		0,0,0,0,0,1,0,0,0,
		0,0,7,9,0,0,0,0,5,
		0,9,3,0,5,0,8,0,0,
		7,0,0,0,0,0,0,8,0,
		5,0,6,0,7,0,1,0,3,
		0,1,0,0,0,0,0,0,2,
		0,0,5,0,3,0,4,7,0,
		8,0,0,0,0,2,3,0,0,
		0,0,0,4,0,0,0,0,0
	};
	int puzzleM1d[] = 
	{
		8,0,0,0,0,0,0,0,0,
		0,0,3,6,0,0,0,0,0,
		0,7,0,0,9,0,2,0,0,
		0,5,0,0,0,7,0,0,0,
		0,0,0,0,4,5,7,0,0,
		0,0,0,1,0,0,0,3,0,
		0,0,1,0,0,0,0,6,8,
		0,0,8,5,0,0,0,1,0,
		0,9,0,0,0,0,4,0,0
	};
	int puzzleN1d[] =
	{
		1,0,0,0,0,7,0,9,0,
		0,3,0,0,2,0,0,0,8,
		0,0,9,6,0,0,5,0,0,
		0,0,5,3,0,0,9,0,0,
		0,1,0,0,8,0,0,0,2,
		6,0,0,0,0,4,0,0,0,
		3,0,0,0,0,0,0,1,0,
		0,4,1,0,0,0,0,0,7,
		0,0,7,0,0,0,3,0,0
	};
	int puzzleO1d[] =
	{
		0,0,0,0,7,0,4,2,6,
		0,1,0,0,0,8,0,0,3,
		0,0,0,4,9,0,0,0,0,
		0,4,0,0,0,0,2,0,8,
		3,0,0,0,0,0,0,0,5,
		2,0,6,0,0,0,0,7,0,
		0,0,0,0,1,4,0,0,0,
		1,0,0,7,0,0,0,8,0,
		9,2,5,0,6,0,0,0,0
	};

	std::cout << "Building Puzzle...";

	int **puzzle = new int*[Sudoku::GRID_DIMENSION];
	for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
	{
		puzzle[i] = new int[Sudoku::GRID_DIMENSION];
	}

	std::vector<Sudoku*> puzzles;

	convertPuzzleDimension(puzzleA1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));
	
	convertPuzzleDimension(puzzleB1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleC1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleD1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleE1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleM1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleN1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleH1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleI1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleJ1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleM1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleN1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	convertPuzzleDimension(puzzleO1d, puzzle);
	puzzles.push_back(new Sudoku(puzzle));

	for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
	{
		delete[] puzzle[i];
	}
	delete[] puzzle;

	std::cout << "Done" << std::endl <<std::endl;

	clock_t totalTime = 0;
	for (int i = 0; i < puzzles.size(); i++)
	{
		std::cout << "Running test " << i << ":"<< std::endl;
		clock_t testTime = 0;
		for (int j = 0; j < 3; j++)
		{
			puzzles.at(i)->resetSolution();
			bool isSolved;
			clock_t start = clock();
			isSolved = solveSudoku(*puzzles.at(i));
			clock_t stop = clock();
			assert(isSolved);
			std::cout << "\t Trial: " << j << ", time: " 
				<< (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC << "ms"
				<< std::endl;
			testTime += (stop - start);
			totalTime += testTime;
		}
		std::cout << "Test " << i << " complete, average time:" 
			<< (double)(testTime / 3.0) * 1000.0 / CLOCKS_PER_SEC 
			<< " ms" << std::endl << std::endl;
	}
	
	std::cout << "Test complete, total time: " 
		<< (double)(totalTime / 3.0) * 1000.0 / CLOCKS_PER_SEC << "ms" 
		<< std:: endl;
	std::cout << "Freeing memory..." << std::endl;

	for (int i = 0; i < puzzles.size(); i++)
	{
		delete puzzles.at(i);
	}

	return 0;
}