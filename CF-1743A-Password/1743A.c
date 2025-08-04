#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

/*----function prototypes----*/
char** gen_unique_perms(char* initStr, int* outCount);
void GUP_helper(struct pydict* dict, 
                char* curPath, 
                int index,
                int totalLen,
                char*** permsList,
                int* count);
int cmpchar(const void *a, const void *b);
static void append_to_list(char ***list, int *count, const char *path);


int cmpchar(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

/**
 * gen_unique_perms: given an initial string of characters, generates all unique permutations (which means we account for repeat characters)
 */
char** gen_unique_perms(char* initStr, int* outCount) {
    struct pydict* dct = pydict_new();

    // 1. From the initStr, populate a Dict with each unique character and its count
    qsort(initStr, strlen(initStr), sizeof(char), cmpchar);
    char *p = initStr;
    while(*p != '\0') {
        // Find char in dict, if found add 1 to value and put, else initialize value at 1
        char key[2] = {*p, '\0'};
        int value = pydict_get(dct, key);
        if(value == -1) {
            pydict_put(dct, key, 1);
        } else {
            pydict_put(dct, key, value + 1);
        }
        p++;
    }

    // 2. Pass the populated Dict, an empty string as the curPath, and an empty list as the permsList to the recursive helper function
    int totalLen = pydict_sum(dct);
    char** permsList = NULL;
    char* curPath = malloc(totalLen + 1);
    if (!curPath) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    };
    int count = 0;

    // 3. Invoke the recursive helper method. It should populate the newly created list with all permutations of our initStr
    GUP_helper(dct, curPath, 0, totalLen, &permsList, &count);

    free(curPath);
    pydict_del(dct);
    // 4. Return the list
    *outCount = count;
    return permsList;
}

/* Helper function to append a string to a dynamic list 
   VIA CHATGPT */
static void append_to_list(char ***list, int *count, const char *path) {
    *list = realloc(*list, (*count + 1) * sizeof(char *));
    if (!*list) {
        perror("realloc failed");
        exit(EXIT_FAILURE);
    }
    (*list)[*count] = strdup(path);
    if (!(*list)[*count]) {
        perror("strdup failed");
        exit(EXIT_FAILURE);
    }
    (*count)++;
}

void GUP_helper(struct pydict* dict, 
                char* curPath, 
                int index,
                int totalLen,
                char*** permsList,
                int* count) {
    // Base case: if all characters are used (sum == 0)
    if(pydict_sum(dict) == 0) {
        curPath[index] = '\0';
        append_to_list(permsList, count, curPath);
        return;
    }

    // Recursive case: iterate over dictionary nodes
    struct dnode* cur = dict->head;
    while(cur != NULL) {
        if(cur->value > 0) {
            // choose current character
            cur->value--; // reduce count for the current value
            curPath[index] = cur->key[0]; // add to path

            // recurse to next position
            GUP_helper(dict, curPath, index + 1, totalLen, permsList, count);

            // backtrack
            cur->value++;
        }
        cur = cur->next;
    }
}

int main(void) {
    char initStr[] = "aabbcc";
    int count = 0;

    char **permsList = gen_unique_perms(initStr, &count);

    printf("Count: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", permsList[i]);
        free(permsList[i]); // free each string
    }
    free(permsList); // free the array

    return 0;
}

