/**
 * Sudoku class and constants.
 * 
 * 
 * 2018-05-15
 * John Y
 */
#include <iostream>

extern const int DIMENSION;
extern const int MIN_VALUE;
extern const int MAX_VALUE;
extern const int EMPTY_VALUE;


class sudoku
{
private:
	int puzzle[DIMENSION][DIMENSION];
	int solution[DIMENSION][DIMENSION];

public:
	/**
	 * @brief      { Prints the status of the game to console. }
	 */
	void print();


	/**
	 * @brief      { Returns a string representing the status of the game. }
	 *
	 * @return     { The string representing the status of the game. }
	 */
	std::string getString();


	/**
	 * @brief      { Determines if the sudoku puzzle is solved. }
	 *
	 * @return     { True if solved, False otherwise. }
	 */
	bool isSolved();


	/**
	 * @brief      { Fills the cell with at row and col with the value. }
	 *
	 * @param[in]  row    The row position of the cell
	 * @param[in]  col    The column position of the cell
	 * @param[in]  value  The value
	 *
	 * @return     { True if the value can be place at the cell, false 
	 *               otherwise. }
	 */
	bool fillCell(int row, int col, int value);


	/**
	 * @brief      { Erase the value in the cell at row and col }
	 *
	 * @param[in]  row   The row position of the cell
	 * @param[in]  col   The column position of the cell
	 *
	 * @return     { True if the cell can be erased, false otherwise. }
	 */
	bool eraseCell(int row, int col);
}