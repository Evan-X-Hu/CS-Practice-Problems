#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // This is for ssize_t to work
// ssize_t is the signed version of size_t, which is used by most system calls for return values
// We are using size_t since it is guaranteed to be large enough to hold the largest possible object
int* convertToIntArr(char* str, int size);
void printArray(int* arr, int n);
int containsDuplicates(int* arr, int n);


int main(void) {
    // Start with getting input for the array of integers
    // What is the best, most consistent way to input a unknown length String in C
    // Strings are not mutatble in C like other languages so it is a little tricky

    // When you don't know the size beforehand --> Must use dynamic allocation
    char* buffer = NULL; // Must set the location to NULL
    size_t bufsize = 0; // buffer capacity
    ssize_t nread; // This will be the number of characters read
    
    int len;
    int* numsArr; // Initialize where we will store the nums array

    fprintf(stdout, "Enter numbers (##...): ");
    
    // Retrieve input
    while((nread = getline(&buffer, &bufsize, stdin)) != -1) {
        // fprintf(stdout, "num read: %d\n", nread);
        // Must adjust for the line break, decrement the nread by 1, actually safer to store
        // the size in a new variable
        len = nread - 1;
        // This way we don't need to delete the line break from the buffer
        break;
    }

    // Convert input String into array of numbers, or we can treat the String as an array
    // Except ascii from 0-9 is 48-57
    // I'll just do this myself
    numsArr = convertToIntArr(buffer, len);

    //fprintf(stderr, "TEST1: Printing the int array\n");
    //printArray(numsArr, len);

    // Now peform the algorith to check for duplicate numbers given the array and the len
    int containsDups = containsDuplicates(numsArr, len);
    //fprintf(stdout,"TEST containsDups: %d\n", containsDups);

    if(containsDups == 1) {
        fprintf(stdout, "Duplicates found\n");
    } else {
        fprintf(stdout, "Duplicates not found\n");
    }

    free(buffer); // Must free buffer since getline allocates this in the background
    free(numsArr);
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

// Code pasted from ChatGPT, I got lazy, it happens
void printArray(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Returns 1 for true and 0 for false
int containsDuplicates(int* arr, int n) {
    // First lets initialize our short 16 bit data structure
    short checker = 0; // Starts at 0000 0000 0000 0000
    // Now iterate through each element in the arr
    for(int i=0; i < n; i++) {
        // Shift a 1 over 0-9 times depending on our value
        short cur = 1 << arr[i];
        // fprintf(stdout, "TEST CHECKER: %d\n", checker);
        // fprintf(stdout, "TEST CUR: %d\n", cur);
        // fprintf(stdout, "TEST CUR & CHECKER: %d\n", cur & checker);
       
        // Now check with the checker if that value is already a 1
        // Do this by using a logical & and if it isn't 0 then that means there was a duplicate
        if((checker & cur) != 0) { 
            // fprintf(stdout,"TEST\n");
            return 1;}
        // Now update the checker
        checker = checker | cur;
    }
    // fprintf(stdout,"TEST\n");
    return 0; // we didn't find a duplicate
}