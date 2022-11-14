/*
Main driver of Sudoku game
*/
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "game.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    int seed;                    // random seed
    int gamesize = 9;            // default size of game
    int nobs = 10;               // default number of prefilled spaces
    int sim = 0;                 // number of simulation runs (if running speed tests)
    bool verbose = false;        // print each simulation result for speed tests
    string method = "backtrace"; // choose solving method

    // Handle command line args
    for (int i = 1; i < argc; ++i)
    {
        if ((string(argv[i]) == "--seed") ||
            (string(argv[i]) == "-s"))
        {

            if (i + 1 < argc)
            {
                istringstream ss(argv[++i]);
                if (!(ss >> seed))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else
            {
                cerr << "--seed option requires one argument."
                     << endl;
                return 1;
            }
        }

        if ((string(argv[i]) == "--gamesize") ||
            (string(argv[i]) == "-g"))
        {

            if (i + 1 < argc)
            {
                istringstream ss(argv[++i]);
                if (!(ss >> gamesize))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else
            {
                cerr << "--gamesize option requires one argument."
                     << endl;
                return 1;
            }
        }

        if ((string(argv[i]) == "--nobs") ||
            (string(argv[i]) == "-n"))
        {

            if (i + 1 < argc)
            {
                istringstream ss(argv[++i]);
                if (!(ss >> nobs))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else
            {
                cerr << "--nobs option requires one argument."
                     << endl;
                return 1;
            }
        }

        if ((string(argv[i]) == "--Unittest") ||
            (string(argv[i]) == "-u"))
        {

            if (i + 1 < argc)
            {
                istringstream ss(argv[++i]);
                if (!(ss >> sim))
                    cerr << "Invalid number " << argv[i++] << endl;
            }
            else
            {
                cerr << "--Unittest option requires one argument."
                     << endl;
                return 1;
            }
        }

        if ((string(argv[i]) == "--Verbose") ||
            (string(argv[i]) == "-v"))
        {
            verbose = true;
        }

        if ((string(argv[i]) == "--RP") ||
            (string(argv[i]) == "-rp"))
        {
            method = "RP";
        }
    }

    srand(seed); // set random seed

    // Welcome message
    cout << "===========================================" << endl;
    cout << "============ Welcome to Sudoku! ===========" << endl;
    cout << "===========================================" << endl;

    playGame(gamesize, nobs);

    return 0;
}
