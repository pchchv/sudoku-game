/*
Main driver of Sudoku game
*/
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

int main()
{
    int seed;                    // random seed
    int gamesize = 9;            // default size of game
    int nobs = 10;               // default number of prefilled spaces
    int sim = 0;                 // number of simulation runs (if running speed tests)
    bool verbose = false;        // print each simulation result for speed tests
    string method = "backtrace"; // choose solving method
}
