/**
 * SudokuSolver function implementation.
 * 
 * 
 * 2018-05-20
 * John Y
 */


#include "SudokuSolver.hpp"

#include <vector>
#include <map>
#include <cassert>


static const int EMPTY_CELLS_THRESHOLD = Sudoku:: GRID_DIMENSION * 
	Sudoku::GRID_DIMENSION * 1 / 16;


/**
 * @brief      Select the first empty cell from the game by checking from left
 *             to right, up to down.
 *
 * @param      game          The Sudoku game
 * @param      emptyCellRow  Reference variable for the row position
 * @param      emptyCellCol  Reference variable for the column position
 *
 * @return     true if a cell is found, false otherwise.
 */
static bool selectEmptyCellByPosition(Sudoku &game, int &emptyCellRow, 
	int &emptyCellCol)
{
	const int NOT_FOUND = -1;
	int currentNumberOfChoices = NOT_FOUND;
	int currentBestRow = NOT_FOUND;
	int currentBestCol = NOT_FOUND;
	for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
	{
		for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
		{
			if (game.getCell(row, col) == Sudoku::EMPTY_VALUE)
			{
				emptyCellRow = row;
				emptyCellCol = col;
				return true;
			}
		}
	}
	return false;
}


/**
 * @brief      Select the empty cell with lowest number of possible choices 
 *             from the game by checking from left, to right, up to down.
 *
 * @param      game          The Sudoku game
 * @param      emptyCellRow  Reference variable for the row position
 * @param      emptyCellCol  Reference variable for the column position
 *
 * @return     true if a cell is found, false otherwise.
 */
static bool selectEmptyCellByChoices(Sudoku &game, int &emptyCellRow, 
	int &emptyCellCol)
{
	const int NOT_FOUND = -1;
	int currentNumberOfChoices = NOT_FOUND;
	int currentBestRow = NOT_FOUND;
	int currentBestCol = NOT_FOUND;

	for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
	{
		for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
		{
			if (game.getCell(row, col) == Sudoku::EMPTY_VALUE)
			{
				std::vector<int> choices;
				findChoices(game, row, col, choices);
				if (choices.size() > 0 && (currentNumberOfChoices == NOT_FOUND ||
					choices.size() < currentNumberOfChoices))
				{
					currentNumberOfChoices = choices.size();
					currentBestRow = row;
					currentBestCol = col;
				}
			}
			if (currentNumberOfChoices == 1)
			{
				break;
			}
		}
	}
	if (currentNumberOfChoices == NOT_FOUND)
	{
		return false;
	}
	emptyCellRow = currentBestRow;
	emptyCellCol = currentBestCol;
	return true;
}


/**
 * @brief      Select an empty cell from the game.
 *
 * @param      game          The Sudoku game
 * @param      emptyCellRow  Reference variable for the row position
 * @param      emptyCellCol  Reference variable for the column position
 *
 * @return     true if a cell is found, false otherwise.
 */
static bool selectEmptyCell(Sudoku &game, int &emptyCellRow, int &emptyCellCol)
{
	if (game.getNumberOfEmptyCells() <= EMPTY_CELLS_THRESHOLD)
	{
		return selectEmptyCellByChoices(game, emptyCellRow, emptyCellCol);
	}
	return selectEmptyCellByPosition(game, emptyCellRow, emptyCellCol);
}


void findChoices(Sudoku &game, int row, int col, 
	std::vector<int> &possibleChoices)
{
	assert(row >= 0 && row < Sudoku::GRID_DIMENSION);
	assert(col >= 0 && col < Sudoku::GRID_DIMENSION);

	if (game.getCell(row, col) != Sudoku::EMPTY_VALUE) 
	{
		return;
	}
	bool possibilityTable[] = 
	{
		true, true, true, true, true, 
		true, true, true, true
	};

	for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
	{
		if (game.getCell(i, col) != Sudoku::EMPTY_VALUE)
		{
			possibilityTable[game.getCell(i, col) - 1] = false;
		}
		if (game.getCell(row, i) != Sudoku::EMPTY_VALUE)
		{
			possibilityTable[game.getCell(row, i) - 1] = false;
		}
	}
	int box = row / Sudoku::BOX_DIMENSION * Sudoku::BOX_DIMENSION + 
		col / Sudoku::BOX_DIMENSION;
	int startingRow = (box / Sudoku::BOX_DIMENSION) * Sudoku::BOX_DIMENSION;
	int startingCol = (box % Sudoku::BOX_DIMENSION) * Sudoku::BOX_DIMENSION;
	for (int row = startingRow; row < startingRow + Sudoku::BOX_DIMENSION; 
		row++)
	{
		for (int col = startingCol; col < startingCol + Sudoku::BOX_DIMENSION;
			col++)
		{
			if (game.getCell(row, col) != Sudoku::EMPTY_VALUE)
			{
				possibilityTable[game.getCell(row, col) - 1] = false;
			}
		}
	}
	for (int i = 0; i < Sudoku::MAX_VALUE; i++)
	{
		if (possibilityTable[i])
		{
			possibleChoices.push_back(i + 1);
		}
	}
}


/**
 * @brief      Solves the Sudoku game via backtracking algorithm.
 *
 * @param      game             The Sudoku game
 * @param      occurrenceTable  An array with 9 elements where the content at 
 *             index i corresponds to the  number of occurrence of the value
 *             i + 1 in the game
 *             
 * @return     True if solved, false if no solution exists.
 */
bool solveSudoku(Sudoku &game, int occurrenceTable[])
{
	if (game.isSolved())
	{
		return true;
	}
	int emptyCellRow;
	int emptyCellCol;
	if (!selectEmptyCell(game, emptyCellRow, emptyCellCol))
	{
		return false;
	}
	std::vector<int> possibleChoices;
	findChoices(game, emptyCellRow, emptyCellCol, possibleChoices);
	std::map<int, int> candidateChoices;
	for (int i = 0; i < possibleChoices.size(); i++)
	{
		candidateChoices[occurrenceTable[possibleChoices.at(i) - 1]] = 
			possibleChoices.at(i);
	}
	for (std::map<int, int>::iterator i = candidateChoices.begin(); 
		i != candidateChoices.end(); i++)
	{
		game.fillCell(emptyCellRow, emptyCellCol, i->second);
		occurrenceTable[i->second - 1]--;
		if (solveSudoku(game, occurrenceTable))
		{
			return true;
		}
		occurrenceTable[i->second - 1]++;
		game.eraseCell(emptyCellRow, emptyCellCol);
	}
	return false;
}


/**
 * @brief      Updates the occurrenceTable according to game.
 *
 * @param      game             The Sudoku game
 * @param      occurrenceTable  An array with 9 elements where the content at 
 *             index i corresponds to the  number of occurrence of the value
 *             i + 1 in the game
 */
void updateOccurrenceTable(Sudoku &game, int occurrenceTable[])
{
	for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
	{
		for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
		{
			if (game.getCell(row, col) != Sudoku::EMPTY_VALUE)
			{
				occurrenceTable[game.getCell(row, col) - 1]++;
			}
		}
	}
}


bool solveSudoku(Sudoku &game)
{
	int occurrenceTable[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	updateOccurrenceTable(game, occurrenceTable);
	return solveSudoku(game, occurrenceTable);
}

















