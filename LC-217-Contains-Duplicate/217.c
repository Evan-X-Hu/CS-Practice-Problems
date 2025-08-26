#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // This is for ssize_t to work
// ssize_t is the signed version of size_t, which is used by most system calls for return values
// We are using size_t since it is guaranteed to be large enough to hold the largest possible object

int main(void) {
    // Start with getting input for the array of integers
    // What is the best, most consistent way to input a unknown length String in C
    // Strings are not mutatble in C like other languages so it is a little tricky

    // When you don't know the size beforehand --> Must use dynamic allocation
    char* buffer = NULL; // Must set the location to NULL
    size_t bufsize = 0; // buffer capacity
    ssize_t nread; // This will be the number of characters read
    
    int* numsArr; // Initialize where we will store the nums array

    fprintf(stdout, "Enter numbers (#,#,...): ");
    
    // Retrieve input
    while((nread = getline(&buffer, &bufsize, stdin)) != -1) {
        
    }


    free(buffer); // Must free buffer since getline allocates this in the background
}