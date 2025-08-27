#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

// Then define the list (C doesn't have classes, so we just return a pointer to the head)
struct Node* createNode(int value) {
    // The problem with this is that we can't create a null value entry
    // First we need to create a space in memory for this node
    Node* node = malloc(sizeof(Node));
    // Then we need to set the data in that node
    node->num = value;
    // Then we need to set the pointer of that node to null
    node->next = NULL;
    return node;
}

// Then define the method to add to the list (add to the head)
// This is actually a prepend method. An append would be O(n) time complexity
// Because we would have to use a loop to get to the last node in the list
// And we can't just store a pointer to the tail because C isn't class based so
// there is no linked list class (the data structure is built on a single node)
void appendNode(struct Node** head, int value) {
    // Why is this a pointer to a pointer to head?
    // Well we will create a node and then have that nodes next point to the pointer to head
    // Because C is pass by value we must do a pointer to a pointer this way we
    // Are now able to affect the pointer that points to head, else it would just be a pointer to head

    // 2 cases: 1. head is null (pointing to null) or 2. the list has at least 1 item

    Node* curNode = createNode(value);
    // If head is null
    if(*head == NULL) {
        // set the head to point to the pointer for the new node
        *head = curNode;
    } else { // Else we have at least 1 element in the lsit
        // Set the curNode's next to point to what head is pointing to
        curNode->next = *head;
        // Set head to point to the curNode
        *head = curNode;
    }
    return;
}
// Then define the method to return the iterator of the list
void printList(struct Node* head) {
    // Print in order from first to last
    // First print the value at head
    // Then while there exists a next node, go to that next node and print its value
    while(head) {
        fprintf(stdout, "%d", head->num);
        head = head->next;
    }
    return;
}
// THen define the method to destory the linked list
void freeList(struct Node* head) {
    // Iterate through each Node and free the Node
    // This is because we had used malloc to create memory for Node* objects
    while (head) { // I took this from ChatGPT
        struct Node *tmp = head; // It seems we create a temporary pointer to point to head
        head = head->next; // Then we can still use head to set the next node
        free(tmp); // then we free the value where tmp points, which is the head node
    }
    return;
}