/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "game_functions.h"

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
char** createBoard(int rowValue, int columnValue)
{
    int i, j;
    char** board;
    board = (char**)malloc(sizeof(char*)* columnValue);
    for(i = 0; i < columnValue; i++)
    {
        board[i] = (char*)malloc(rowValue*sizeof(char));
    }
    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            board[i][j] = ' ';
        }
    }
    return board;
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
char** resetBoard(int rowValue, int columnValue, char** board)
{
    int i, j;

    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            board[i][j] = ' ';
        }
    }
    return board;
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
void freeBoard(int columnValue, char** board)
{
    int i;
    for(i = 0; i < columnValue; i++)
    {
        free(board[i]);
    }
    free(board);
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
void displayBoard(int rowValue, int columnValue, char** board)
{
    int ii, jj, kk;

    printf("+");
    for(kk = 0; kk < columnValue; kk++)
    {
        printf("---+");
    }
    printf("\n");
    for(ii = 0; ii < rowValue; ii++)
    {
        printf("|");
        for(jj = 0; jj < columnValue; jj++)
        {
            printf(" %c |", board[jj][ii]);
        }
        printf("\n+");
        for(kk = 0; kk < columnValue; kk++)
        {
            printf("---+");
        }
        printf("\n");
    }
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
LinkedList* gameStart(LinkedList* gameLog, int gameCount, int rowValue, int columnValue, char** board, int winLength)
{
    char done = ' ';
    char gameString[1000];
    int count = 0;

    sprintf(gameString, "GAME: %d\n", gameCount);
    insertLast(gameLog, gameString);
    do{
        count++;
        gameLog = playerOneMove(gameLog, rowValue, columnValue, board, count);
        done = check(done, rowValue, columnValue, board, winLength);
        if(done!= ' ')
        {
            printf("Player One Wins!\n");
            insertLast(gameLog, "Player One Wins!\n");
            break;
        }
        count++;
        gameLog = playerTwoMove(gameLog, rowValue, columnValue, board, count);
        done = check(done, rowValue, columnValue, board, winLength);
        if(done!= ' ')
        {
            printf("Player Two Wins!\n");
            insertLast(gameLog, "Player Two Wins!\n");
        }
    }while(done == ' ');
    displayBoard(rowValue, columnValue, board);
    board = resetBoard(rowValue, columnValue, board);
    count = 0;
    gameCount = gameCount + 1;
    return gameLog;
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
LinkedList* playerOneMove(LinkedList* gameLog, int rowValue, int columnValue, char** board, int count)
{
    int columnCoord, rowCoord;
    char input[256];
    char turnString[256];
    char coordString[256];
    char playerOne[] = "Player: X";

    displayBoard(rowValue, columnValue, board);
    printf("User 1 (X) input coordinates: (in the form of (x,y))\n");
    fgets(input, sizeof(input), stdin);
    {
        if(sscanf(input, "%d%*c%d", &rowCoord, &columnCoord) == 2)
        {
            if((rowCoord > rowValue-1) || (columnCoord > columnValue-1))
            {
                 printf("Invalid coordinate, try again.\n");
                 playerOneMove(gameLog, rowValue, columnValue, board, count);
            }
            else if(board[columnCoord][rowCoord] != ' ')
            {
                 printf("Invalid move (X/O already allocated), try again.\n");
                 playerOneMove(gameLog, rowValue, columnValue, board, count);
            }
            else
            {
                 board[columnCoord][rowCoord] = 'X';
                 sprintf(turnString, "Turn: %d", count);
                 sprintf(coordString, "Location: %d,%d\n", rowCoord, columnCoord);
                 insertLast(gameLog, turnString);
                 insertLast(gameLog, playerOne);
                 insertLast(gameLog, coordString);
            }
        }
        else
        {
            printf("Invalid format, try again.\n");
            playerOneMove(gameLog, rowValue, columnValue, board, count);
        }
     }
     return gameLog;
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
LinkedList* playerTwoMove(LinkedList* gameLog, int rowValue, int columnValue, char** board, int count)
{
    int columnCoord, rowCoord;
    char input[256];
    char turnString[256];
    char coordString[256];
    char playerTwo[] = "Player: O";

    displayBoard(rowValue, columnValue, board);
    printf("User 2 (O) input coordinates: (in the form of (x,y))\n");
    fgets(input, sizeof(input), stdin);
        if(sscanf(input, "%d%*c%d", &rowCoord, &columnCoord) == 2)
        {
            if((rowCoord > rowValue-1) || (columnCoord > columnValue-1))
            {
                 printf("Invalid coordinate, try again.\n");
                 playerTwoMove(gameLog, rowValue, columnValue, board, count);
            }
            else if(board[columnCoord][rowCoord] != ' ')
            {
                 printf("Invalid move (X/O already allocated), try again.\n");
                 playerTwoMove(gameLog, rowValue, columnValue, board, count);
            }
            else
            {
                 board[columnCoord][rowCoord] = 'O';
                 sprintf(turnString, "Turn: %d", count);
                 sprintf(coordString, "Location: %d,%d\n", rowCoord, columnCoord);
                 insertLast(gameLog, turnString);
                 insertLast(gameLog, playerTwo);
                 insertLast(gameLog, coordString);
            }
        }
        else
        {
            printf("Invalid format, try again.\n");
            playerTwoMove(gameLog, rowValue, columnValue, board, count);
        }
    return gameLog;
}

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
char check(char done, int rowValue, int columnValue, char** board, int winLength)
{
    int i, j, k, counter;
    done = ' ';
    counter = 0;

    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            if(board[i][j] == ' ')
            {
                  done = ' ';
            }
        }
    }

    /*checking vertical wins*/
    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            for(k = 1; k < winLength; k++)
            {
                if(j+k < rowValue)
                {
                    if((board[i][j] == board[i][j+k]) && (board[i][j] != ' '))
                    {
                         counter = counter + 1;
                         printf("%d\n", counter);
                    }
                }
                if(counter == winLength-1)
                {
                    done = 'Y';
                }
            }
            counter = 0;
        }
    }

    /*checking horizontal wins*/
    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            for(k = 1; k < winLength; k++)
            {
                if(i+k < columnValue)
                {
                    if((board[i][j] == board[i+k][j]) && (board[i][j] != ' '))
                    {
                         counter++;
                    }
                }
                if(counter == winLength-1)
                {
                    done = 'Y';
                }
            }
            counter = 0;
        }
    }

    /*checking diagonal wins*/
    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            for(k = 1; k < winLength; k++)
            {
                if((j+k < rowValue) && (i+k < columnValue))
                {
                    if((board[i][j] == board[i+k][j+k]) && (board[i][j] != ' '))
                    {
                         counter++;
                    }
                }
                if(counter == winLength-1)
                {
                    done = 'Y';
                }
            }
            counter = 0;
        }
    }

    /*checking reverse diagonal wins*/
    for(i = 0; i < columnValue; i++)
    {
        for(j = 0; j < rowValue; j++)
        {
            for(k = 1; k < winLength; k++)
            {
                if((j+k < rowValue) && (i-k >= 0))
                {
                    if((board[i][j] == board[i-k][j+k]) && (board[i][j] != ' '))
                    {
                         counter++;
                    }
                }
                if(counter == winLength-1)
                {
                    done = 'Y';
                }
            }
            counter = 0;
        }
    }
    return done;
}
