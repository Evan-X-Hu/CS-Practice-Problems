#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int* convertToIntArr(char* str, int size);
int findMissingNum(int* numArr, int len);
void printArray(int* arr, int n);

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

// Code pasted from ChatGPT, I got lazy, it happens
void printArray(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}