/*****************************************************************************
 * Author: Phi Do                                                            *
 * Creation Date: 07/10/2019                                                 *
 * Date Last Modified: 20/10/2019                                            *
 * This linked list implementation is largely based of what I had done for   *
 * the practical session in COMP1000 Prac7.                                  *
 *****************************************************************************/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

    /* next and previous within the node makes the linked list, as well as the
    linkedlist having a head and tail makes the linked list a double ended
    doubly linked linked list*/
    typedef struct LinkedListNode {
        void* data;
        void* copy;
        struct LinkedListNode* next;
        struct LinkedListNode* previous;
    } LinkedListNode;

    typedef struct{
        int length;
        LinkedListNode* head;
        LinkedListNode* tail;
    } LinkedList;

    LinkedList* createLinkedList();
    void insertFirst(LinkedList* list, void* data);
    void insertLast(LinkedList* list, void* data);
    void* removeFirst(LinkedList* list);
    void* removeLast(LinkedList* list);
    void* getItem(LinkedList* list, int index);
    int getCount(LinkedList* list);
    void printList(LinkedList* list, void (*fptr)(void *));
    void writeList(LinkedList* list, void (*fptr)(FILE* outFile, void *), FILE* outFile);
    void freeLinkedList(LinkedList* list);
    void freeNode(LinkedListNode* node);

#endif
