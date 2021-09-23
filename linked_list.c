/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 * This linked list implementation is largely based of what I had done for   *
 * the practical session in COMP1000 Prac7.                                  *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/*
FUNCTION: createLinkedList
PURPOSE: create a pointer to a linked list and then return the pointer to that
         linked list
*/
LinkedList* createLinkedList()
{
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

/*
FUNCTION: insertFirst
PURPOSE: insert a node at the beggining of the linked list
*/
void insertFirst(LinkedList* list, void* data)
{
    LinkedListNode* inNode;
    inNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    inNode->data = data;
    if(list->head == NULL)
    {
        list->head = inNode;
        list->tail = inNode;
        list->length ++;
    }
    else
    {
        list->head->previous = inNode;
        inNode->next = list->head;
        list->head = inNode;
        list->length ++;
    }
}

/*
FUNCTION: insertLast
PURPOSE: insert a node at the end of the linked list
*/
void insertLast(LinkedList* list, void* data)
{
    LinkedListNode* inNode;
    inNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    if(list->head == NULL)
    {
        /* void pointer copy is used to point to data in the instance when data
        is always changing, pointing to a copy of the data is a method to
        circumvent the issue of all nodes pointing to the data value*/
        void *copy = malloc((strlen(data)+1)*1);
        strcpy(copy, data);
        inNode->data = copy;
        list->head = inNode;
        list->tail = inNode;
        list->length ++;
    }
    else
    {
        void *copy = malloc((strlen(data)+1)*1);
        strcpy(copy, data);
        inNode->data = copy;
        list->tail->next = inNode;
        inNode->previous = list->tail;
        list->tail = inNode;
        list->length ++;
    }
}

/*
FUNCTION: getCount
PURPOSE: returns an int representing the number of nodes within the list
*/
int getCount(LinkedList* list)
{
    int count = 0;
    LinkedListNode *node = list->head;
    while (node != NULL)
    {
        count++;
        node = node->next;
    }
    return count;
}

/*
FUNCTION: removeFirst
PURPOSE: remove a node from the beggining of the linked list
*/
void* removeFirst(LinkedList* list)
{
    void* nodeValue;
    if(list->head == NULL)
    {
        printf("Error: Empty List\nReturning NULL value");
    }
    else
    {
        nodeValue = list->head->data;
        list->head = list->head->next;
        list->head->previous = NULL;
        list->length --;
    }
    return nodeValue;
}

/*
FUNCTION: removeLast
PURPOSE: remove a node from the end of the linked list
*/
void* removeLast(LinkedList* list)
{
    void* nodeValue;
    if(list->head == NULL)
    {
        printf("Error: Empty List\nReturning NULL value");
    }
    else
    {
        nodeValue = list->tail->data;
        list->tail = list->tail->previous;
        list->tail->next = NULL;
        list->length --;
    }
    return nodeValue;
}

/*
FUNCTION: getItem
PURPOSE: get the data from a node specified by an index
*/
void* getItem(LinkedList* list, int index)
{
    void* item;
    LinkedListNode *currNode, *tempNode;
    int i;
    if(index <= list->length && index >= 0)
    {
        if(index == 1)
        {
            currNode = list->head;
            item = currNode->data;
        }
        else
        {
            currNode = list->head;
            item = currNode->data;
            for(i = 1; i < index; i++)
            {
                tempNode = currNode;
                currNode = tempNode->next;
                item = currNode->data;
            }
        }
    }
    else
    {
        printf("Error: Empty List\nReturning NULL value");
    }
    return item;
}

/*
FUNCTION: printList
PURPOSE: generic method to print the linked list, using a function pointer
to specify what type of data will be printed
*/
void printList(LinkedList* list, void (*fptr)(void *))
{
    LinkedListNode *node, *nextNode;

    node = list->head;
    while(node != NULL)
    {
        nextNode = node->next;
        (*fptr)(node->data);
        node = nextNode;
    }
}

/*
FUNCTION: writeList
PURPOSE: generic method to print all the nodes of linkedlist to a file, by
including the import of a file pointer, and importing that into the function
pointer that would be printing out to file
*/
void writeList(LinkedList* list, void (*fptr)(FILE* outFile, void *), FILE* outFile)
{
    LinkedListNode *node, *nextNode;

    node = list->head;
    while(node != NULL)
    {
        nextNode = node->next;
        (*fptr)(outFile, node->data);
        node = nextNode;
    }
}

/*
FUNCTION: freeLinkedList
PURPOSE: iterates through the list by the head, and frees the data of the
node/head, then freeing the node itself before iterating to nextNode, a temp
node that becomes the head->next before head is freed
*/
void freeLinkedList(LinkedList* list)
{
    LinkedListNode *node, *nextNode;
    nextNode = NULL;
    node = list->head;
    while(node != NULL)
    {
        nextNode = node->next;
        free(node->data);
        free(node);
        node = nextNode;
    }
    list->head = NULL;
    free(list);
}
