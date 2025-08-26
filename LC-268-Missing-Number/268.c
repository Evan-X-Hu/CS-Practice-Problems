#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int* convertToIntArr(char* str, int size);
int findMissingNum(int* numArr, int len);


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
    
}