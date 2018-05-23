# Sudoku Solver

A Sudoku solver employing backtracking search, constraint programming, and Minimum Remaining Value (MRV) heuristic. Written in C++11.

## Getting started

Sudoku game implementation can be found at:

```
src/main/cpp/Sudoku.cpp
```

Sudoku solver implementation can be found at:

```
src/main/cpp/SudokuSolver.cpp
```

A file containing 10,000 25 numbers sudoku can be found at:

```
src/test/resources/puzzles.txt
```

## Running the tests

A test driver that finds the total and average CPU time to solve 10,000 puzzles can be found at:

```
src/main/test/cpp/SudokuSolverTest.cpp
```

Compile using clang++:

```
clang++ SudokuSolverTest.cpp ../../main/cpp/Sudoku.cpp ../../main/cpp/UI.cpp ../../main/cpp/SudokuSolver.cpp -std=c++11
```

## Built With

* [Sublime](https://www.sublimetext.com/) - The text editor
* [clang++](https://clang.llvm.org/) - C++ compiler
* [Doxygen](https://www.stack.nl/~dimitri/doxygen/) - Used to generate documentation from source code

## Authors

* **John Y** - [Dniwrallets](https://github.com/dniwrallets)

## Acknowledgments

* [Printable Sudoku Puzzles](http://www.printable-sudoku-puzzles.com/wfiles/) - Sudoku puzzles for testing