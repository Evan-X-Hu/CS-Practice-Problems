#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "linkedlist.h"

int* convertToIntArr(char* str, int size);
int findMissingNum(int* numArr, int len);
void printArray(int* arr, int n);
Node* findMissingNums(int* numArr, int len);

int main(void) {
    // Initialize input fields
    char* buffer = NULL;
    size_t bufsize;
    ssize_t nread;
    int len; // The actual amount of characters read, easier than deleting the new line in buffer
    int* numArr; // Where we will store the nums array

    fprintf(stdout, "Enter numbers (##...): ");

    // Retrieve input with getline
    while((nread = getline(&buffer, &bufsize, stdin)) != -1) {
        len = nread - 1;
        break;
    }

    // Convert the input to an array of numbers
    numArr = convertToIntArr(buffer, len);

    // Now perform the algorithm to find the missing number
    int missingNum = findMissingNum(numArr, len);

    fprintf(stdout, "Missing number: %d\n", missingNum);

    // Separate problem but similar so no need to make a new doc
    Node* missingNums = findMissingNums(numArr, len);

    fprintf(stdout, "Missing numbers:\n");
    //printArray(missingNums, len);
    printList(missingNums);

}

int* convertToIntArr(char* str, int size) {
    // Allocate an integer array of size size
    int* arr = malloc(size * sizeof(int));
    if (!arr) return NULL; // check malloc for failures or NULL returns

    // Iterate through all the characters in string
    int i = 0; // track index
    while(*str != '\0') { // While we are not at the NULL pointer terminator of the str
        //fprintf(stdout, "TEST\n");
        arr[i] = *str - 48; // Add it to the int array
        i++;
        str++;
    }
    // return the result int array
    return arr;
}

int findMissingNum(int* numArr, int len) {
    // First initialize an empty array of size len
    int numsMap[len];

    // Second iterate through all numbers in numArr and map a 1 to the index of that number
    // Something weird happens here when the numbers aren't sequenced
    // Im unsure what it is but I know that if I initialize everything to 0 it should solve the issue
    // Note: Come back to this to learn about the issue behind this
    for(int i=0; i<len; i++) {
        numsMap[i] = 0;
    }
    // printArray(numsMap, len);
    
    for(int i=0; i<len; i++) {
        //fprintf(stdout, "TEST: %d\n", numArr[i]);
        int curNum = numArr[i];
        numsMap[curNum] = 1;
    }

    // Print this array for testing
    // printArray(numsMap, len);

    // So this works, I just need to make a note that the right edge case is when all the values are mapped to 1
    // I mean this is a better and faster solution then sorting the array and looking for a jump

    // Iterate through the map and return the index with a 0, if all 1, then we return len
    for(int i=0; i<len; i++) {
        if(numsMap[i] == 0) {
            return i;
        }
    }

    return len;
}


Node* findMissingNums(int* numArr, int len) {
    // /fprintf(stdout, "TEST: %d\n", len);
    Node* resultLL; // we dont need to try to create a node with a null value
    // The append function handles when we aren't pointing to anything
    // First initialize an empty array of size len
    int numsMap[len+1];

    // Second iterate through all numbers in numArr and map a 1 to the index of that number
    // Something weird happens here when the numbers aren't sequenced
    // Im unsure what it is but I know that if I initialize everything to 0 it should solve the issue
    // Note: Come back to this to learn about the issue behind this
    for(int i=0; i<=len; i++) { // must be a size above len
        //fprintf(stdout, "TEST: %d\n", i);
        numsMap[i] = 0;
    }
    // printArray(numsMap, len+1);
    
    for(int i=0; i<len; i++) {
        // fprintf(stdout, "TEST i: %d\n", i);
        // fprintf(stdout, "TEST nums arr at i: %d\n", numArr[i]);
        int curNum = numArr[i];
        numsMap[curNum-1] = 1; // Subtract 1 from index to shift everything left 1
    }

    // Print this array for testing
    printArray(numsMap, len+1); // WORKS SO FAR

    // So this works, I just need to make a note that the right edge case is when all the values are mapped to 1
    // I mean this is a better and faster solution then sorting the array and looking for a jump

    // Iterate through the map and return the index with a 0, if all 1, then we return len
    for(int i=1; i<=len; i++) {
        fprintf(stdout, "TEST: %d\n", i);
        fprintf(stdout, "TEST numsmap[i]: %d\n", numsMap[i]);

        if(numsMap[i] == 0) {
            // This number was skipped so add to the result linked list
            // resultArr[i-1] = i;
            appendNode(&resultLL, i);
        }
        // The problem is we need a way to append numbers to the end of the resultArr
        // Basically have this function as a linked list
    }

    return resultLL;
    // In C we can't return pointers to local variables because once the function returns
    // That space used for the local variable will be cleared and then the pointer will point to nothing
}

// Code pasted from ChatGPT, I got lazy, it happens
void printArray(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}