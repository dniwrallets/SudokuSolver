/**
 * SudokuSolver Test driver that times the solver's performance across 5000 
 *   puzzles
 * 
 * 
 * 2018-05-22
 * John Y
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include <time.h>

#include "../../main/cpp/Sudoku.hpp"
#include "../../main/cpp/SudokuSolver.hpp"


const std::string FILE_PATH = "../resources/puzzles.txt";
const int TRAILS_PER_TEST = 2;


/**
 * @brief      Loads the sudoku repository at FILE_PATH
 *
 * @param      puzzles  The vector reference pointer containing the puzzles
 *
 * @return     True if read is successful, false otherwise.
 */
bool loadRepository(std::vector<Sudoku *> &puzzles)
{
	std::string puzzle;
	std::ifstream puzzleRepository(FILE_PATH);
	if (!puzzleRepository.is_open())
	{
		std::cout << "Unable to open file at: " << FILE_PATH << 
			". Exiting now..." << std::endl;
		return false;
	}
	std::cout << "Sudoku repository opened successfully, loading puzzles..."
		<< std::endl;
	while (std::getline(puzzleRepository, puzzle))
	{
		puzzles.push_back(new Sudoku(puzzle));
	}
	std::cout << "Done, " << puzzles.size() << " puzzle(s) loaded." << std::endl;
	return true;
}


int main(int argc, char const *argv[])
{
	std::vector<Sudoku*> puzzles;
	if (!loadRepository(puzzles))
	{
		return EXIT_FAILURE;
	}

	clock_t totalTime = 0;
	for (int test = 0; test < puzzles.size(); test++)
	{
		clock_t trial = 0;
		for (int trail = 0; trail < TRAILS_PER_TEST; trail++)
		{
			puzzles.at(test)->resetSolution();
			bool isSolved;
			clock_t start = clock();
			isSolved = solveSudoku(*puzzles.at(test));
			clock_t stop = clock();
			assert(isSolved);
			trial += (stop - start);
			totalTime += trial;
		}
	}

	std::cout << std::endl << "Test complete, total CPU time: " 
		<< (double)(totalTime) / CLOCKS_PER_SEC / TRAILS_PER_TEST << "s"
		<< std:: endl;
	std::cout << "Average CPU time per puzzle: " 
		<< (double)(totalTime) * 1000.0 / CLOCKS_PER_SEC / TRAILS_PER_TEST /
			puzzles.size()
		<< "ms" << std::endl;
	std::cout << "Freeing memory..." << std::endl;

	for (int test = 0; test < puzzles.size(); test++)
	{
		delete puzzles.at(test);
	}
	return 0;
}

