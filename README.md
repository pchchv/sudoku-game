# Sudoku written in **C++**

## *Running the game:*

### A compilation of the game with a makefile is required

### After compiling, type ```./sudoku``` to start

### The default is to run a 9x9 interactive game

## Command line flags:

### `-s` `--seed` Specifies a random grain for playback

### `-g` `--gamesize` Specifies an integer value to specify the size of the game, i.e. 9 for a 9x9 game, 16 for a 16x16 game, etc.

### `-n` `--nobs` Specifies the number of prefilled values to include

### `-u` `--unittest` Runs a single speed test

### `-v` `--verbose` Outputs detailed information after each unit test. Has no effect if the game is played in interactive mode

#

## *Game Usage:*

### To fill a cell, enter the column number, row number and the value you want to enter (based on 1). Separate with spaces, commas, or any other separators. For example: ```3 6 1``` or ```5,8,2```

### Enter solve at any time for automatic sudoku solving

### If you hit an impossible configuration, you will be asked to clear the board first

### Once decided, you will be asked if you want to play again
