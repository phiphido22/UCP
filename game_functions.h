/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 *****************************************************************************/
#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

char** createBoard(int rowValue, int columnValue);
char** resetBoard(int rowValue, int columnValue, char** board);
void freeBoard(int columnValue, char** board);
void displayBoard(int rowValue, int columnValue, char** board);
LinkedList* gameStart(LinkedList* gameLog, int gameCount, int rowValue, int columnValue, char** board, int winLength);
LinkedList* playerTwoMove(LinkedList* gameLog, int rowValue, int columnValue, char** board, int count);
LinkedList* playerOneMove(LinkedList* gameLog, int rowValue, int columnValue, char** board, int count);
char check(char done, int rowValue, int columnValue, char** board, int winLength);

#endif
