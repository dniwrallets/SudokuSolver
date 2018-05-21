/**
 * Sudoku constants, class and function prototypes.
 * 
 * 
 * 2018-05-19
 * John Y
 */


#pragma once

#include <string>


class Sudoku
{
public:
	static const int GRID_DIMENSION;
	static const int BOX_DIMENSION;
	static const int NUM_BOXES;
	static const int MIN_VALUE;
	static const int MAX_VALUE;
	static const int EMPTY_VALUE;


	/**
	 * @brief      Constructs the object from console input.
	 */
	Sudoku();


	/**
	 * @brief      Constructs the object from an 2D array representing the 
	 *             puzzle
	 *
	 * @param      puzzle  2D array representing the puzzle
	 */
	Sudoku(int **puzzle);


	/**
	 * @brief      Destroys the object.
	 */
	~Sudoku();


	/**
	 * @brief      Returns a 2D array representing the puzzle.
	 *
	 * @return     2D array representing the puzzle.
	 */
	int **getPuzzle();


	/**
	 * @brief      Returns a 2D array representing the puzzle.
	 *
	 * @return     2D array representing the solution.
	 */
	int **getSolution();


	/**
	 * @brief      Determines if the sudoku puzzle is solved.
	 *
	 * @return     True if solved, False otherwise.
	 */
	bool isSolved();


	/**
	 * @brief      Returns the number of empty cells.
	 *
	 * @return     The number of empty cells.
	 */
	int getNumberOfEmptyCells();


	/**
	 * @brief      Gets the cell at row and col.
	 *
	 * @param[in]  row   The row position of the cell
	 * @param[in]  col   The column position of the cell
	 *
	 * @return     The value in the cell.
	 */
	int getCell(int row, int col);


	/**
	 * @brief      Fills the cell with at row and col with the value.
	 *
	 * @param[in]  row    The row position of the cell
	 * @param[in]  col    The column position of the cell
	 * @param[in]  value  The value
	 *
	 * @return     True if the value can be place at the cell, false 
	 *             otherwise.
	 */
	bool fillCell(int row, int col, int value);


	/**
	 * @brief      Erase the value in the cell at row and col.
	 *
	 * @param[in]  row   The row position of the cell
	 * @param[in]  col   The column position of the cell
	 *
	 * @return     True if the cell can be erased, false otherwise.
	 */
	bool eraseCell(int row, int col);


	/**
	 * @brief      Clear all cells in solution.
	 */
	void resetSolution();


private:
	int **puzzle;
	int **solution;
	int numberOfEmptyCells;


	/**
	 * @brief      Determines a row is valid.
	 *
	 * @param[in]  row   The row index
	 *
	 * @return     True if the row is valid, False otherwise.
	 */
	bool isValidRow(int row);


	/**
	 * @brief      Determines if a column is valid.
	 *
	 * @param[in]  col   The column index
	 *
	 * @return     True if the column is valid, False otherwise.
	 */
	bool isValidCol(int col);


	/**
	 * @brief      Determines if a boxe in the game is valid.
	 *
	 * @param[in]  box   The box index
	 *
	 * @return     True if the boxe is valid, False otherwise.
	 */
	bool isValidBox(int box);


	/**
	 * @brief      Determines if all cells in the game are valid.
	 *
	 * @return     True if all cells are valid, False otherwise.
	 */
	bool isValid();
};