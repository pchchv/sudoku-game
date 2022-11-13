/*
File to implement game play
*/

#include <iostream>
#include <regex>
#include <sstream>
#include "game.hpp"
#include "solver.hpp"
using namespace std;

void playGame(int size, int nobs);

// Play again
void playAgainPrompt(int size, int nobs)
{
    string user_response;

    do
    {
        cout << "Would you like to play again? y/n" << endl;
        getline(cin, user_response);
    } while ((user_response != "y") && (user_response != "n"));

    if (user_response == "y")
    {
        playGame(size, nobs);
    }
    else
    {
        return;
    }
}

void playGame(int size, int nobs)
{
    string user_entry;
    bool solverSucces = false;
    Board board = generateSudoku(size, nobs);
    regex rgx("[0-9]{1,}");
    smatch match;
    int user_input[3];

    // Repeat until sudoku is solved
    do
    {
        board.printSudoku();      // print sudoku
        getline(cin, user_entry); // get user input

        // Check for user commands
        if (user_entry == "Solve" || user_entry == "solve")
        {
            solverSucces = solve(board, 0, 0);
            board.printSudoku();
            break;
        }

        if (user_entry == "Clear" || user_entry == "clear")
        {
            board.clearSudoku();
            continue;
        }

        // Assuming no special command, parses user input
        int count = 0;
        for (sregex_iterator i = sregex_iterator(user_entry.begin(), user_entry.end(), rgx);
             i != sregex_iterator();
             ++i)
        {
            smatch m = *i;
            user_input[count] = stoi(m.str());
            ++count;
        }

        // If parse values are out of range — throw error and continue
        bool invalid = false;
        for (int i = 0; i < 3; i++)
        {
            if (!board.inBounds(user_input[i]))
            {
                invalid = true;
            }
        }

        if (invalid)
        {
            cout << "Values entered must be between 1 and " << board.getSize() << endl;
            continue;
        }

        // Assign board value if feasible move
        if (board.feasibleUser((user_input[0] - 1), (user_input[1] - 1), user_input[2]) == true)
        {
            if (board.checkImmutable((user_input[0] - 1), (user_input[1] - 1)) == false)
            {
                board.assignValue((user_input[0] - 1), (user_input[1] - 1), user_input[2]);
            }
            else
            {
                cout << "You can't change that value!" << endl;
            }
        }
        else
        {
            cout << "Not feasible!" << endl;
        }

        // Reset inputs to 0, will cause invalid message if unchanged on next round
        for (int i = 0; i < 3; i++)
        {
            user_input[i] = 0;
        }

    } while (!board.checkSudoku());

    string user_response;

    if (solverSucces)
    {
        cout << "The sudoku is solved!" << endl;
        playAgainPrompt(size, nobs);
    }
    else
    {
        cout << "Could not solve sudoku based on pre-filled values" << endl;

        do
        {

            cout << "Would you like to clear and try to solve? y/n" << endl;
            getline(cin, user_response);

        } while ((user_response != "y") && (user_response != "n"));

        if (user_response == "y")
        {
            board.clearSudoku();
            solve(board, 0, 0);
            board.printSudoku();
            playAgainPrompt(size, nobs);
        }
    }
}
