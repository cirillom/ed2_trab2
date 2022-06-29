#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "linkedList.h"

typedef struct _node
{
    NODEDATATYPE data;
    struct _node* next;
}Node;

Node* createNode(NODEDATATYPE data){
    Node* new_node;
    new_node = malloc(sizeof(Node));

    new_node->data = data;

    return new_node;
}

void printList(Node **head, FILE* fp){
    Node *mover = *head;

    while(mover != NULL){
            fprintf(fp, "%s ", mover->data);
        mover = mover->next;
    }
}

void insert(Node** sorted, NODEDATATYPE data){
    Node* new_node = createNode(data);

    if (*sorted == NULL || strcmp((*sorted)->data, new_node->data) >= 0) {
        new_node->next = *sorted;
        *sorted = new_node;
    }
    else {
        Node* current = *sorted;

        while (current->next != NULL
                && strcmp(current->next->data, new_node->data) < 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

NODEDATATYPE findInList(Node **head, string str){
    Node *mover = *head;

    while(mover != NULL){
        if(strcmp(mover->data, str) == 0){
            return mover->data;
        }
        mover = mover->next;
    }
    return NULL;
}

void freeList(Node **head){
    Node *mover = *head;
    
    while(mover != NULL){
        Node *tmp = mover;
        mover = mover->next;
        free(tmp);
    }
}