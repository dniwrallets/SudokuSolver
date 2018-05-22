/**
 * SudokuSolver function implementation.
 * 
 * 
 * 2018-05-22
 * John Y
 */


#include "SudokuSolver.hpp"

#include <map>
#include <vector>


class SudokuOccurrenceData
{
public:
	/**
	 * @brief      Constructs the object.
	 *
	 * @param      game  The Sudoku game
	 */
	SudokuOccurrenceData(Sudoku &game)
	{
		valueOccurrenceTable = 
			new int[Sudoku::MAX_VALUE - Sudoku::MIN_VALUE + 1];
		rowOccurrenceTable = new int[Sudoku::GRID_DIMENSION];
		colOccurrenceTable = new int[Sudoku::GRID_DIMENSION];
		boxOccurrenceTable = new int[Sudoku::NUM_BOXES];
		for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
		{
			valueOccurrenceTable[i] = 0;
			rowOccurrenceTable[i] = 0;
			colOccurrenceTable[i] = 0;
			boxOccurrenceTable[i] = 0;
		}
		for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
		{
			for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
			{
				if (game.getCell(row, col) != Sudoku::EMPTY_VALUE)
				{
					valueOccurrenceTable[game.getCell(row, col) - 1]++;
					int box = row / Sudoku::BOX_DIMENSION * 
						Sudoku::BOX_DIMENSION + col / Sudoku::BOX_DIMENSION;
					rowOccurrenceTable[row]++;
					colOccurrenceTable[col]++;
					boxOccurrenceTable[box]++;
				}
			}
		}
	}


	/**
	 * @brief      Destroys the object.
	 */
	~SudokuOccurrenceData()
	{
		delete[] valueOccurrenceTable;
		delete[] rowOccurrenceTable;
		delete[] colOccurrenceTable;
		delete[] boxOccurrenceTable;
	}


	/**
	 * @brief      Get the number of occurrences of a value 
	 *
	 * @param[in]  value  The value
	 *
	 * @return     The number of times the value appears.
	 */
	int getValueOccurrence(int value)
	{
		return valueOccurrenceTable[value - 1];
	}


	/**
	 * @brief      Get the total number of fill cells that effects possible 
	 *             value
	 *
	 * @param[in]  row   The row position
	 * @param[in]  col   The column position
	 *
	 * @return     The number of constraints.
	 */
	int getNumberOfFilledCells(int row, int col)
	{
		int box = row / Sudoku::BOX_DIMENSION * Sudoku::BOX_DIMENSION + 
			col / Sudoku::BOX_DIMENSION;
		return rowOccurrenceTable[row] + colOccurrenceTable[col] +
			boxOccurrenceTable[box];
	}


	/**
	 * @brief      Adds a new occurrence.
	 *
	 * @param[in]  row    The row position
	 * @param[in]  col    The column position
	 * @param[in]  value  The value
	 */
	void addOccurrence(int row, int col, int value)
	{
		int box = row / Sudoku::BOX_DIMENSION * Sudoku::BOX_DIMENSION + 
			col / Sudoku::BOX_DIMENSION;
		valueOccurrenceTable[value - 1]++;
		rowOccurrenceTable[row]++;
		colOccurrenceTable[col]++;
		boxOccurrenceTable[box]++;
	}


	/**
	 * @brief      Removes an occurrence.
	 *
	 * @param[in]  row    The row position
	 * @param[in]  col    The column position
	 * @param[in]  value  The value
	 */
	void removeOccurrence(int row, int col, int value)
	{

		int box = row / Sudoku::BOX_DIMENSION * Sudoku::BOX_DIMENSION + 
			col / Sudoku::BOX_DIMENSION;
		valueOccurrenceTable[value - 1]--;
		rowOccurrenceTable[row]--;
		colOccurrenceTable[col]--;
		boxOccurrenceTable[box]--;
	}


private:
	int *valueOccurrenceTable;
	int *rowOccurrenceTable;
	int *colOccurrenceTable;
	int *boxOccurrenceTable;
};


/**
 * @brief      Select an empty cell from the game.
 *
 * @param      game          The Sudoku game
 * @param      emptyCellRow  Reference variable for the row position
 * @param      emptyCellCol  Reference variable for the column position
 *
 * @return     true if a cell is found, false otherwise.
 */
static bool selectEmptyCell(Sudoku &game, SudokuOccurrenceData &occurrenceData,
	int &emptyCellRow, int &emptyCellCol)
{
	const int NOT_FOUND = -1;
	int currentNumberOfConstraints = NOT_FOUND;
	int currentBestRow = NOT_FOUND;
	int currentBestCol = NOT_FOUND;
	for (int row = 0; row < Sudoku::GRID_DIMENSION; row++)
	{
		for (int col = 0; col < Sudoku::GRID_DIMENSION; col++)
		{
			if (game.getCell(row, col) == Sudoku::EMPTY_VALUE)
			{
				int numberOfConstraints = 
					occurrenceData.getNumberOfFilledCells(row, col);
				if (currentNumberOfConstraints == NOT_FOUND ||
					numberOfConstraints > currentNumberOfConstraints)
				{
					currentNumberOfConstraints = numberOfConstraints;
					currentBestRow = row;
					currentBestCol = col;
				}
			}
		}
	}
	if (currentNumberOfConstraints == NOT_FOUND)
	{
		return false;
	}
	emptyCellRow = currentBestRow;
	emptyCellCol = currentBestCol;
	return true;
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
	bool choiceTable[] = 
	{
		true, true, true, true, true, 
		true, true, true, true
	};
	for (int i = 0; i < Sudoku::GRID_DIMENSION; i++)
	{
		if (game.getCell(i, col) != Sudoku::EMPTY_VALUE)
		{
			choiceTable[game.getCell(i, col) - 1] = false;
		}
		if (game.getCell(row, i) != Sudoku::EMPTY_VALUE)
		{
			choiceTable[game.getCell(row, i) - 1] = false;
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
				choiceTable[game.getCell(row, col) - 1] = false;
			}
		}
	}
	for (int i = 0; i < Sudoku::MAX_VALUE; i++)
	{
		if (choiceTable[i])
		{
			possibleChoices.push_back(i + 1);
		}
	}
}


/**
 * @brief      Solves the Sudoku game via backtracking algorithm.
 *
 * @param      game            The Sudoku game
 * @param      occurrenceData  The SudokuOccurrenceData object that keeps track
 *                             of number of occupied cells in a row/col, or the
 *                             number of occurrence of a value
 *
 * @return     True if solved, false if no solution exists.
 */
bool solveSudoku(Sudoku &game, SudokuOccurrenceData &occurrenceData)
{
	if (game.isSolved())
	{
		return true;
	}
	int emptyCellRow;
	int emptyCellCol;
	if (!selectEmptyCell(game, occurrenceData, emptyCellRow, emptyCellCol))
	{
		return false;
	}
	std::vector<int> possibleChoices;
	findChoices(game, emptyCellRow, emptyCellCol, possibleChoices);
	std::multimap<int, int> candidateChoices;
	for (int i = 0; i < possibleChoices.size(); i++)
	{
		candidateChoices.insert(std::pair<int,int>
			(
				occurrenceData.getValueOccurrence(possibleChoices.at(i)),
				possibleChoices.at(i)
			));
	}
	for (std::map<int, int>::iterator i = candidateChoices.begin(); 
		i != candidateChoices.end(); i++)
	{
		game.fillCell(emptyCellRow, emptyCellCol, i->second);
		occurrenceData.addOccurrence(emptyCellRow, emptyCellCol, i->second);
		if (solveSudoku(game, occurrenceData))
		{
			return true;
		}
		game.eraseCell(emptyCellRow, emptyCellCol);
		occurrenceData.removeOccurrence(emptyCellRow, emptyCellCol, i->second);
	}
	return false;
}


bool solveSudoku(Sudoku &game)
{
	SudokuOccurrenceData occurrenceData(game);
	return solveSudoku(game, occurrenceData);
}
