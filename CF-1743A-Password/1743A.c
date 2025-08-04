#include <stdio.h>
#include "dict.h"

/*----function prototypes----*/
char** gen_unique_perms(char* initStr);
void GUP_helper(struct pydict* curDict, char* curPath, char** permsList);

static int cmpstringp(const void *p1, const void *p2) {
    /* The actual arguments to this function are "pointers to
        pointers to char", but strcmp(3) arguments are "pointers
        to char", hence the following cast plus dereference. */

    return strcmp(*(const char **) p1, *(const char **) p2);
}

/**
 * gen_unique_perms: given an initial string of characters, generates all unique permutations (which means we account for repeat characters)
 */
char** gen_unique_perms(char* initStr) {
    struct pydict* dct = pydict_new();
    // 1. From the initStr, populate a Dict with each unique character and its count
    qsort(initStr, strlen(initStr), sizeof(char), cmpstringp);
    char *p = initStr;
    while(*p != '\0') {
        // Find char in dict, if found add 1 to value and put, else initialize value at 1
        int value = pydict_get(dct, *p);
        if(value == -1) {
            pydict_put(dct, *p, 1);
        } else {
            pydict_put(dct, *p, value + 1);
        }
        p++;
    }
    // 2. Pass the populated Dict, an empty string as the curPath, and an empty list as the permsList to the recursive helper function
    char** permsList = NULL;
    char* path;
    // 3. Invoke the recursive helper method. It should populate the newly created list with all permutations of our initStr
    GUP_helper(dct, path, permsList);
    // 4. Return the list
    return permsList;
}

void GUP_helper(struct pydict* dict, 
                char* curPath, 
                int index,
                int totalLen,
                char*** permsList,
                int* count) {
    // Base case: if all characters are used (sum == 0)
    if(pydict_sum(dict) == 0) {
        
        // add the curPath to the permsList
        // return up
    }
    // 2. Recursive case: iterate through curDict (take into account num for max loop)
    //    - If the value at the current position is 0 then go to the next position
    //        * also will go to the next position after a recursive return
    //    - After getting to the next position, add the character to a COPY of curPath and subtract 1 from the value of that char in dict
    //    - Pass the dict, permsList, and a copy of curPath to the next recursive call
    //    - increment the value of the current position in the dict
}

