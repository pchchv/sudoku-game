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
