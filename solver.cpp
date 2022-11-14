/*
Implementation of backtracking algorithm and other game-play mechanics
*/

#include "solver.hpp"
#include <iostream>
#include <cassert>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Prints the board
void Board::printSudoku()
{
    int blockSize = (int)sqrt(N);
    int extra_space = N / 10;

    for (int i = 0; i < N; i++)
    {
        cout << "+---";
        for (int j = 0; j < extra_space; j++)
            cout << "-";
    }

    cout << "+" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| ";
        for (int j = 0; j < N; j++)
        {

            if ((*this)(i, j) == 0)
            {
                cout << ".";
                for (int k = 0; k < extra_space; k++)
                    cout << " ";
            }
            else
            {
                if (!isProblem(i, j))
                {
                    cout << (*this)(i, j);
                }
                else
                {
                    cout << "\033[31m" << (*this)(i, j) << "\033[39m";
                }

                int numDigits = (*this)(i, j) / 10;
                while (numDigits < extra_space)
                {
                    cout << " ";
                    numDigits++;
                }
            }

            if ((j + 1) % blockSize == 0)
            {
                cout << " | ";
            }
            else
            {
                cout << "   ";
            }
        }

        cout << endl;
        if ((i + 1) % blockSize == 0)
        {
            for (int j = 0; j < N; j++)
            {
                cout << "+---";

                for (int k = 0; k < extra_space; k++)
                    cout << "-";
            }

            cout << "+" << endl;
        }
    }
}

// Checks if the sudoku is complete
bool Board::checkSudoku()
{
    int val = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            val = (*this)(i, j);
            (*this)(i, j) = 0;
            if (!feasible(*this, i, j, val))
            {
                (*this)(i, j) = val;
                return false;
            }
            (*this)(i, j) = val;
        }
    return true;
}

// All cells that are not immutable are empty,
// immutable cells are filled with randomly generated data
void Board::clearSudoku()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!checkImmutable(i, j))
                (*this)(i, j) = 0;
}

// Checks if the value is in the sudoku size range
bool Board::inBounds(int val)
{
    if ((val > 0) && (val <= N))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks the feasibility of the board
// Not useful for solvers because it cannot return once the problem is solved
// Needs to cycle through the entire board to update the problem cells to return red to the user
bool Board::feasibleUser(int row, int col, int val)
{
    int blockSize = (int)sqrt(N);

    if (row >= N)
    {
        std::cout << "You can't play off the game board!" << endl;
        return false;
    }

    if (col >= N)
    {
        std::cout << "You can't play off the game board!" << endl;
        return false;
    }

    bool isfeasible = true;

    for (int i = 0; i < N; i++)
    {
        if ((*this)(row, i) == val)
        {
            infeasible[row][i] = true;
            isfeasible = false;
        }
        else
        {
            infeasible[row][i] = false;
        }
    }

    for (int i = 0; i < N; i++)
    {
        if ((*this)(i, col) == val)
        {
            infeasible[i][col] = true;
            isfeasible = false;
        }
        else
        {
            infeasible[i][col] = false;
        }
    }

    int blockRow = blockSize * (row / blockSize);
    int blockCol = blockSize * (col / blockSize);

    // Checks if used yet in block
    for (int i = 0; i < blockSize; i++)
    {
        for (int j = 0; j < blockSize; j++)
        {
            if ((*this)(blockRow + i, blockCol + j) == val)
            {
                infeasible[blockRow + i][blockCol + j] = true;
                isfeasible = false;
            }
            else
            {
                infeasible[blockRow + i][blockCol + j] = false;
            }
        }
    }
    return isfeasible;
}

// Helper function for solve
// Checks to see if candidate is feasible
bool feasible(Board &board, int row, int col, int val)
{
    int N = board.getSize();
    assert(row < N);
    assert(col < N);
    int blockSize = (int)sqrt(N);

    // Check if used yet in row
    for (int j = 0; j < N; j++)
        if (board(row, j) == val)
            return false;

    // Check if used yet in col
    for (int i = 0; i < N; i++)
        if (board(i, col) == val)
            return false;

    // Coordinates of upper-left hand corner of block that (row,col) occupies
    int blockRow = blockSize * (row / blockSize);
    int blockCol = blockSize * (col / blockSize);

    // Check if used yet in block
    for (int i = 0; i < blockSize; i++)
        for (int j = 0; j < blockSize; j++)
            if (board(blockRow + i, blockCol + j) == val)
                return false;

    return true;
}

// Backtracking algorithm
bool solve(Board &board, int row, int col)
{
    // N: size of the board; note N must be a perfect square!
    int N = board.getSize();
    assert(N == pow(sqrt(N), 2));

    // Check to see if we are at end of board
    if (row == N)
        return true;

    // Skip over values that have been filled in
    if (board(row, col) != 0)
    {
        if (col == (N - 1))
        {
            if (solve(board, row + 1, 0))
                return true;
        }
        else
        {
            if (solve(board, row, col + 1))
                return true;
        }
        return false;
    }

    // Try different values
    for (int val = 1; val <= N; val++)
    {
        if (feasible(board, row, col, val))
        {
            board(row, col) = val;
            if (col == (N - 1))
            {
                if (solve(board, row + 1, 0))
                    return true;
            }
            else
            {
                if (solve(board, row, col + 1))
                    return true;
            }
        }
    }

    // Backtrack if no value is found that works
    board(row, col) = 0;
    return false;
}

// Generates a board for the solution
// Only N possible boards are generated
// TODO: Expand to get more
Board generateSudoku(int N, int nobs)
{
    // Generate permutation of 1...n
    // Fill diagonal of board with this permutation
    // Solve board
    // Randomly remove enough entries to only leave nobs observed
    assert(nobs <= N * N);
    Board board(N);

    int *perm = genPerm(N); // permuted 1...N

    // Fill diag of board with perm
    for (int i = 0; i < N; i++)
        board(i, i) = perm[i];
    delete[] perm;

    // Solve board
    bool isSolved = solve(board, 0, 0);
    assert(isSolved);

    // Remove N*N - nobs entries
    perm = genPerm(N * N);
    int x, y;
    for (int i = 0; i < (N * N - nobs); i++)
    {
        x = (perm[i] - 1) / N;
        y = (perm[i] - 1) % N;
        board(x, y) = 0;
        board.assignImmutable(x, y, false);
    }

    delete[] perm;
    return board;
}

int *genPerm(int N)
{
    // Initialize array [1,...,N]
    int *x = new int[N];
    for (int i = 0; i < N; i++)
        x[i] = i + 1;

    // Generate random permutation of [1,...,N]
    int rindex;
    int temp;
    for (int i = (N - 1); i > 0; i--)
    {
        rindex = rand() % (i + 1);
        temp = x[i];
        x[i] = x[rindex];
        x[rindex] = temp;
    }

    return x;
}