/*
Implement unit testing functions
*/

#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "game.hpp"
#include "test.hpp"
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

void unitTest(int size, int nobs, int ntimes, bool verbose)
{

    int total = 0;

    // Generate sudoku and solve ntimes
    for (int i = 0; i < ntimes; ++i)
    {
        Board board = generateSudoku(size, nobs);

        auto t = measure<std::chrono::nanoseconds>::execution(solve, board, 0, 0);

        // Print output if verbose
        if (verbose)
            cout << "Backtrace solved in " << t << " ns." << endl;

        total += t;
    }

    cout << "Average time for Backtrace: " << total / ntimes << endl;
}