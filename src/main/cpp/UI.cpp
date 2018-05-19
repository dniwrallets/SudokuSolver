/**
 * Sudoku solver user interface function implementations.
 * 
 * 
 * 2018-05-19
 * John Y
 */


#include "UI.hpp"

#include <iostream>
#include <string>


static const std::string RED = "\033[31;1m";
static const std::string GREEN = "\033[32m";
static const std::string YELLOW = "\033[33m";
static const std::string BLUE = "\033[34m";
static const std::string RESET = "\033[0m";
static const std::string WHITE = "\033[37m";

static const std::string LEFT_INDENT = "    ";
static const std::string HORIZONTAL_BOARDER = LEFT_INDENT + WHITE + "+-------+-------+-------+\n" + RESET;
static const std::string VERTICAL_BOARDER = WHITE + "|" + RESET;
static const std::string BLANK_CELL = WHITE + "." + RESET;


void printSudoku(Sudoku &game)
{
	int **puzzle = game.getPuzzle();
	int **solution = game.getSolution();
	for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
	{
		if (row % Sudoku::BOX_DIMENSION == 0)
		{
			std::cout << HORIZONTAL_BOARDER;
		}
		for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
		{
			if (col == 0)
			{
				std::cout << LEFT_INDENT << VERTICAL_BOARDER;
			}
			else if (col % Sudoku::BOX_DIMENSION == 0)
			{
				std::cout << " " << VERTICAL_BOARDER;
			}
			if (puzzle[row][col] == Sudoku::EMPTY_VALUE)
			{
				if (solution[row][col] == Sudoku::EMPTY_VALUE)
				{
					std::cout << " " << BLANK_CELL;
				}
				else
				{
					std::cout << " " << RED << solution[row][col] << RESET;
				}
			}
			else
			{
				std::cout << " " << GREEN << puzzle[row][col] << RESET;
			}
		}
		std::cout << " " << VERTICAL_BOARDER << std::endl;
	}
	std::cout << HORIZONTAL_BOARDER;
}