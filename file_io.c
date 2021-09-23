/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "file_io.h"
#include "linked_list.h"

/*
FUNCTION: processFile
PURPOSE: imports a file based on the string input, splitting it into separate
settings of the game of tic-tac-toe
*/
Settings processFile(char* fileName)
{
    FILE* inFile;
    char line[20];
    char setting[10];
    Settings settings;
    int* numberCheck;

    inFile = fopen(fileName,"r");

    if(inFile == NULL)
    {
        /*throw an error message if the file could not be opened*/
        perror("Error: File could not be opened\nClosing Program...\n");
    }
    else
    {
        if(ferror(inFile)) /*if there is an error reading the file*/
        {
            /*throw error msg*/
            perror("Error: Error reading from the file\nClosing Program...\n");
        }
        else
        {
            /*loop until null is detected*/
            while(fgets(line, sizeof(line), inFile))
            {
                numberCheck = (int*)malloc(sizeof(int)*3);
                sscanf(line, "%c=%d", setting, numberCheck);

                if(*numberCheck < 1)
                {
                    printf("ERROR in file, numerical value cannot be less than 1\nClosing Program...\n");
                    exit(1);
                }
                else
                {
                    /* if the first letter of the line is any of the accepted
                    cases, it will import the setting into the Setting struct*/
                    if(*setting == 'M' || *setting == 'm')
                    {
                        settings.row = *numberCheck;
                        printf("Setting Rows: %d\n", *numberCheck);
                    }
                    else if(*setting == 'N' || *setting == 'n')
                    {
                        settings.column = *numberCheck;
                        printf("Setting Columns: %d\n", *numberCheck);
                    }
                    else if(*setting == 'K' || *setting == 'k')
                    {
                        settings.win = *numberCheck;
                        printf("%d in a row to win\n", *numberCheck);
                    }
                    /* if a character that is not compatible is detected then
                    the program will exit to terminal*/
                    else
                    {
                        printf("ERROR in file, invalid line detected\nClosing Program...\n");
                        exit(1);
                    }
                }
            }
        }
    }
    /* if the amount needed to win is larger than the row or height of the board
    then the program will exit to terminal*/
    if(settings.win > settings.column || settings.win > settings.row)
    {
        printf("Amount in a row to win cannot be greater than the board size\nClosing Program...\n");
        exit(1);
    }
    fclose(inFile);
    return settings;
    }

/*
FUNCTION: writeLogs
PURPOSE: prints the game log of the session into a log file, with a strict
format for the name of the log based on current time, and settings of the game
*/
void writeLogs(LinkedList* gameLog, int rowValue, int columnValue, int winLength)
{
    int i, hours, minutes, day, month;
    char fileName[92];
    FILE* outFile;
    void* logLine;
    char* logString;

    /* using the time.h package to assign real time values to variables used
    to create the name of the log file*/
    time_t now;
    time(&now);
    ctime(&now);
    local = localtime(&now);
    hours = local->tm_hour;
    minutes = local->tm_min;
    day = local->tm_mday;
    month = local->tm_mon + 1;

    sprintf(fileName, "MNK_%d-%d-%d_%d-%d_%d-%d.log", rowValue, columnValue, winLength, hours, minutes, day, month);
    outFile = fopen(fileName, "w");
    /* if the file could not be opened and returns null*/
    if (outFile == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    else
    {
        /* for loop that prints each string from the game log linked list to the
        output log file, starting from the head of the list*/
        for(i = 1; i <= getCount(gameLog); i++)
        {
            logLine = getItem(gameLog, i);
            logString = (char*)logLine;
            fprintf(outFile, "%s\n", logString);
        }
        printf("Saved to file successfully!\n");
    }
    fclose(outFile);
}
