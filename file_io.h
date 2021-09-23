/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 *****************************************************************************/
#ifndef FILE_IO_H
#define FILE_IO_H
#include "linked_list.h"

/* a struct that takes 3 int values, a row column and win and is typedef to be
a new type 'Settings'*/
typedef struct {
    int row;
    int column;
    int win;
} Settings;

struct tm *local;
Settings processFile(char* fileName);
void writeLogs(LinkedList* gameLog, int rowValue, int columnValue, int winLength);

#endif
