#ifndef __LINKEDLIST_H__ 
#define __LINKEDLIST_H__

#include "utils.h"

#define NODEDATATYPE string

typedef struct _node Node;

//Prints all the data stored in the Linked List
void printList(Node **head, FILE* fp);

//Inserts a piece of data at the end of the List
void append(Node **head, NODEDATATYPE data);

//Inserts a piece of data in a sorted position in a list
void insert(Node **sorted, NODEDATATYPE data);

//Finds a value in a list using sequential search
NODEDATATYPE findInList(Node **head, string str);

//Frees the allocation for the list
void freeList(Node **head);

#endif