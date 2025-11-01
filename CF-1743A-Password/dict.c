// Copied from Chuck Severance's python dict in C. I'm using his but also learning from his implementation
#include "dict.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dnode {
    char *key;
    int value;
    struct dnode *next;
};

struct pydict {
    struct dnode *head;
    struct dnode *tail;
    int count;
};

/* Constructor: dct = dict() */
struct pydict* pydict_new() {
    struct pydict *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

/* Deconstructor: del(dct)*/
void pydict_del(struct pydict* self) {
    struct dnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->key);
        //free(cur->value); unneeded for an int value
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void*)self);
}

/* len(dct) */
int pydict_len(const struct pydict* self) {
    return self->count;
}

/* print(lst) */
/* {'a': 1, 'b': 1, 'c': 1} */
void pydict_print(struct pydict* self) {
    struct dnode* cur = self->head; // Start at the head
    fprintf(stdout, "{");// print the first bracket
    while(cur != NULL) { // Iterate until cur reaches the null pointer
        fprintf(stdout, "'%s': '%d'", cur->key, cur->value); // print the cur node
        if(cur->next != NULL) {
            fprintf(stdout, ",");
        }
        cur = cur->next;
    }
    fprintf(stdout, "}\n");
}

/* get the total sum of all values in the dict */
int pydict_sum(struct pydict* self) {
    int sum = 0;
    struct dnode* cur = self->head;
    while(cur != NULL) {
        sum += cur->value;
        cur = cur->next;
    }
    return sum;
}

/* find the node with value of key, simple LL traversal */
struct dnode* pydict_find(struct pydict* self, char *key) {
    struct dnode* cur = self->head; // Start at the head
    while(cur != NULL) { // Iterate until the null pointer
        if(strcmp(cur->key, key) == 0) { // found the key
            return cur;
        } else {
            cur = cur->next;
        }
    }
    return NULL;
}

/* x.get(key): returns NULL if not found */
int pydict_get(struct pydict* self, char *key) {
    struct dnode* entry = pydict_find(self, key);
    if(entry == NULL) {
        return -1;
    } else {
        return entry->value;
    }
}

/* x[key] = value; Insert or replace the value associated with a key */
struct pydict* pydict_put(struct pydict* self, char* key, int value) {
    struct dnode *old = pydict_find(self, key);
    if(old != NULL) {
        old->value = value;
        return self;
    } else {
        struct dnode* new_node = malloc(sizeof(*new_node)); // create new node
        if(!new_node) {return NULL;} // if malloc fails

        size_t len = strlen(key) + 1;
        new_node->key = malloc(len);
        if (!new_node->key) {
            free(new_node);
            return NULL;
        }
        memcpy(new_node->key, key, len);

        new_node->value = value; // set the value
        new_node->next = NULL;   // set the pointer for next

        if (self->tail) { // if tail not empty, LL is not empty
            self->tail->next = new_node; // set the previous tail to point to new node
        } else { // if tail is empty, LL is empty
            self->head = new_node; // must set head
        }
        self->tail = new_node; // update the tail to be the new node
        self->count++;

        return self;
    }
}


/**EXAMPLE DEFINITION
 * struct pydict* dct = pydict_new();
 * pydict_put(dct, "z", "Catch phrase");
 */ 