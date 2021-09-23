# UCP
C Project to understand basic C concepts such as file I/O, data structures and storing data dynamically.

Files in Project:
DeclarationOfOriginality.pdf
file_io.c
file_io.h
game_functions.c
game_functions.h
linked_list.c
linked_list.h
main.c
main.h
makefile
settings.txt
UCP Assignment Report.docx
readme.txt

How to compile:
Type 'make' into the command line to compile 3 versions of the TicTacToe
program, the default 'TicTacToe', 'TicTacToeEditor' and 'TicTacToeSecret'.

Test Files:
Tested using the settings.txt file as import.

Functionality:
- Reads the file containing the settings desired for the game of TicTacToe
- Creates a linked list which saves the settings, game number, and what happened
  on each turn of the game
- Prints Menu for User to select from
- Allows user to view the current settings of the game
- Prints the game log to standard output, showing previous settings/games
- Allows user to save that game log to a file
- Editor mode: allows for the user to change the settings, such as dimensions of
               the board and the number in a row to win
- Secret mode: takes away the option to print the gamelog to a file, but still
               allowing to view the game log.

Tested On:
Windows 10 Education
Ubuntu Linux, Windows Sub System

Bugs/Memory Leaks:
- When selecting 'View the current logs', a conditional jump/move that depends
  on uninitialised value is detected, in line 186 of linked_list.c which
  is a while loop with the condition that the node doesnt equal null. A solution
  to this issue hasn't been found.
- When selecting 'Save the logs to a file', the same issue regarding a
  conditional jump/move is detected, in line 91 of linked_list.c regarding
  another while loop that has the if not null condition.
- When exiting the program, a 3rd instance of the issue stated prior occurs,
  this time in linked_list.c line 224, in an attempt to free the list before
  closing the program. A solution to all three of these memory leaks has not
  been found.
