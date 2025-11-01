#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// First define the node
// This LL will be for integer type data
typedef struct Node {
    int num;
    struct Node* next;
} Node;

//typedef struct Node Node;

// Then define the list (C doesn't have classes, so we just return a pointer to the head)
struct Node* createNode(int value);

// Then define the method to add to the list (add to the head)
void appendNode(struct Node** head, int value);
// Then define the method to return the iterator of the list
void printList(struct Node* head);
// THen define the method to destory the linked list
void freeList(struct Node* head);

#endif