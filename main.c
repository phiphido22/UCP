/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"
#include "game_functions.h"
#include "file_io.h"
#include "main.h"

int main(int argc, char* argv[])
{
    int rowValue, columnValue, winLength, choice;
    int gameCount = 1;
    int exit = 0;
    char convert[20];
    char rowString[256];
    char columnString[256];
    char winString[256];
    LinkedList* gameLog;
    char** board;

    /* in the instance that the the command line prompt is not in a valid format
    the program will ignore the creation of the game and close*/
    if(argc != 2)
    {
        printf("Error: invalid arguments\nExiting..\n");
    }
    else
    {
        Settings settings = processFile(argv[1]);
        rowValue = settings.row;
        columnValue = settings.column;
        winLength = settings.win;
        board = createBoard(rowValue, columnValue);
        displayBoard(rowValue, columnValue, board);
        gameLog = createLinkedList();
        /* creating the strings used to display and later print the settings*/
        sprintf(rowString, "Number of rows: %d", rowValue);
        sprintf(columnString, "Number of columns: %d", columnValue);
        sprintf(winString, "%d in a row to win\n", winLength);
        /* inserts the current settings of the game into the linkedlist
        'gameLog' */
        insertLast(gameLog, rowString);
        insertLast(gameLog, columnString);
        insertLast(gameLog, winString);

        while(exit != 1)
        {
            printf("Select an option with the corresponding number:\n");
            printf("1. Start a new game\n");
            printf("2. View the settings of the game\n");
            printf("3. View the current logs\n");
            /*conditional compilation of secret mode
            when -DSECRET is used in the makefile, creates a version of
            TicTacToe which does not have the option to save the logs to a file
            If SECRET is not defined then the option to save to file is
            available*/
            #ifndef SECRET
            printf("4. Save the logs to a file\n");
            #endif
            /*if -DEDITOR is defined then an option to change the settings of
            the game is enabled and shown in the menu prompt*/
            #ifdef EDITOR
            printf("5. Change the settings of the game\n");
            #endif
            printf("0. Exit the application\n");
            fgets(convert, 20, stdin);
            choice = strtol(convert, NULL, 0);

            /* switch case to loop if standard input does not equal any of the
            cases, between 0 and 4(5 if in editor mode)*/
            switch(choice)
            {
                case 0:
                    /*before exiting, make sure to free the board and the linked
                    list due to both being created before the menu prompt
                    appears*/
                    freeBoard(columnValue, board);
                    freeLinkedList(gameLog);
                    exit = 1;
                    break;
                case 1:
                    gameStart(gameLog, gameCount, rowValue, columnValue, board, winLength);
                    break;
                case 2:
                    viewSettings(rowValue, columnValue, winLength);
                    break;
                case 3:
                    printList(gameLog, printString);
                    break;
                /* as stated above, the case option for writing logs will not
                be enabled if secret is defined in the make file/gcc command*/
                #ifndef SECRET
                case 4:
                    writeLogs(gameLog, rowValue, columnValue, winLength);
                    break;
                #endif
                /* as stated above, the case option for changing the settings
                be enabled if editor is defined in the make file/gcc command*/
                #ifdef EDITOR
                case 5:
                    /*must free the board before recreating the board with the
                    new dimensions*/
                    freeBoard(columnValue, board);
                    settings = changeSettings(settings, rowValue, columnValue, winLength);
                    rowValue = settings.row;
                    columnValue = settings.column;
                    winLength = settings.win;
                    board = createBoard(rowValue, columnValue);
                    displayBoard(rowValue, columnValue, board);
                    /*add to game log the new settings to indicate the change in
                     new settings in the case only the gamelog is viewed*/
                    sprintf(rowString, "Number of rows: %d", rowValue);
                    sprintf(columnString, "Number of columns: %d", columnValue);
                    sprintf(winString, "%d in a row to win\n", winLength);
                    insertLast(gameLog, rowString);
                    insertLast(gameLog, columnString);
                    insertLast(gameLog, winString);
                    break;
                #endif
                default:
                    printf("Selection must be between 1 and 5\nPlease try again\n\n");
                    break;
            }

        }
    }
    return 0;
}

/*
FUNCTION: processFile
PURPOSE: imports a file based on the string input, splitting it into separate
settings of the game of tic-tac-toe
*/
void viewSettings(int rowValue, int columnValue, int winLength)
{
    printf("\nNumber of rows: %d\n", rowValue);
    printf("Number of columns: %d\n", columnValue);
    printf("Number of X/O's in a row to win: %d\n\n", winLength);
}

/*
FUNCTION: processFile
PURPOSE: imports a file based on the string input, splitting it into separate
settings of the game of tic-tac-toe
*/
Settings changeSettings(Settings settings, int rowValue, int columnValue, int winLength)
{
    char input[256];
    int rowInput, columnInput, winInput;
    /*Settings settings;*/

    printf("How many rows will the table be?\n");
    fgets(input, sizeof(input), stdin);
    /* if any of the 3 inputs are invalid the function will return to the menu
    and keep the same settings previously set */
    /* using rowInput, columnInput and winInput as temporary values to keep
    the inputs, only changing the settings if all 3 values were valid*/
    if(sscanf(input, "%d", &rowInput) == 1)
    {
        printf("How many columns will the table be?\n");
        fgets(input, sizeof(input), stdin);
        if(sscanf(input, "%d", &columnInput) == 1)
        {
              printf("How many in a row to win?\n");
              fgets(input, sizeof(input), stdin);
              if(sscanf(input, "%d", &winInput) == 1)
              {
                  /*program will return original settings if the win length is
                  longer than the board dimensions, as this would always lead
                  to a draw in every match*/
                  if(winInput > rowInput  || winInput > columnInput)
                  {
                      printf("Win length cannot be longer than row/column length, back to menu.\n");
                  }
                  else
                  {
                  settings.row = rowInput;
                  settings.column = columnInput;
                  settings.win = winInput;
                  }
              }
              else
              {
                  printf("Invalid format, back to menu.\n");
              }
        }
        else
        {
            printf("Invalid format, back to menu.\n");
        }
    }
    else
    {
        printf("Invalid format, back to menu.\n");
    }
    return settings;
}



/*
FUNCTION: processFile
PURPOSE: imports a file based on the string input, splitting it into separate
settings of the game of tic-tac-toe
*/
void printString(void *s)
{
   printf("%s\n", (char *)s);
}
