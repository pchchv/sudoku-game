/*
Implement Board class to hold state of sudoku game
*/
#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>

// Holds the state of the game
class Board
{
    int N;
    int **grid;
    bool **immutable;
    bool **infeasible;

public:
    // Implemented as matrix with single array
    Board(int _N) : N(_N)
    {
        // Matrix for value tracking
        grid = new int *[N];
        for (int i = 0; i < N; i++)
        {
            grid[i] = new int[N];
        }
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                grid[i][j] = 0;

        // Matrix for tracking the immutable
        immutable = new bool *[N];
        for (int i = 0; i < N; i++)
        {
            immutable[i] = new bool[N];
        }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                immutable[i][j] = true;

        // Matrix for tracking the values of inappropriate — problem cells,
        // which will be highlighted in red during the gameplay
        infeasible = new bool *[N];
        for (int i = 0; i < N; i++)
        {
            infeasible[i] = new bool[N];
        }

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                infeasible[i][j] = false;
    }

    // Destructor for the board
    ~Board()
    {
        for (int i = 0; i < N; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;

        for (int i = 0; i < N; i++)
        {
            delete[] immutable[i];
        }
        delete[] immutable;

        for (int i = 0; i < N; i++)
        {
            delete[] infeasible[i];
        }
        delete[] infeasible;
    }

    void printSudoku();     // Print the sudoku to the screen
    bool checkSudoku();     // Check if sudoku is complete
    void clearSudoku();     // Clear mutables from sudoku
    bool inBounds(int val); // Check if value can exist in sudoku
    bool feasibleUser(int row, int col, int val);

    // Operator overload to assign value to cell
    int &operator()(int x, int y)
    {
        assert(x < N && y < N);
        return grid[x][y];
    }

    // Operator overload to assign value to cell
    void assignValue(int x, int y, int val)
    {
        (*this)(x, y) = val;
    }

    // Toggle cell mutability
    void assignImmutable(int x, int y, bool val)
    {
        immutable[x][y] = val;
    }

    // Checks if the cell is immutable
    bool checkImmutable(int x, int y)
    {
        return immutable[x][y];
    }

    // Tracks the cells that are causing the infeasibility
    bool isProblem(int x, int y)
    {
        return infeasible[x][y];
    }

    // Get size of game (9 for 9x9 game)
    int getSize()
    {
        return N;
    }

    // Debug function
    void setFromArray(int a[4][4])
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                grid[i][j] = a[i][j];
    }
};

bool feasible(Board &b, int row, int col, int val);
bool solve(Board &b, int row, int col);
int *genPerm(int N);
Board generatePuzzle(int n, int nobs);
