/**
 * Sudoku constants, class and function prototypes.
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


	/**
	 * @brief      Determines if all the rows in the game are valid.
	 *
	 * @return     True if all rows are valid, False otherwise.
	 */
	bool has_valid_rows();


	/**
	 * @brief      Determines if all the columns in the game are valid.
	 *
	 * @return     True if all columns are valid, False otherwise.
	 */
	bool has_valid_cols();


	/**
	 * @brief      Determines if all the boxes in the game are valid.
	 *
	 * @return     True if all boxes are valid, False otherwise.
	 */
	bool has_valid_boxes();


	/**
	 * @brief      Determines if all cells in the game are valid.
	 *
	 * @return     True if all cells are valid, False otherwise.
	 */
	bool is_valid();


public:
	/**
	 * @brief      Prints the status of the game to console.
	 */
	void print();


	/**
	 * @brief      Returns a string representing the status of the game.
	 *
	 * @return     The string representing the status of the game.
	 */
	std::string getString();


	/**
	 * @brief      Determines if the sudoku puzzle is solved.
	 *
	 * @return     True if solved, False otherwise.
	 */
	bool isSolved();


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
	void reset_solution();
}