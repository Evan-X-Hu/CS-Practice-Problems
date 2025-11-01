#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "printIntArr.h"
#include "printStrArr.h"
#include "intArrInput.h"

int main(void) {
    /** First use getline to retrieve input as a string
     *  Then, I will test my modules base on this
     */

    //1. Get an array of integers
    char* buffer = NULL; // Must set uninitialized pointers to NULL (AKA, always initialize pointers)
    size_t bufsize;
    ssize_t nread;
    int len;
    int* numArr = NULL;

    fprintf(stdout, "Enter numbers (#,#,#,...): ");

    // Retrieve input with getline
    while((nread = getline(&buffer, &bufsize, stdin)) != -1) {
        len = nread - 1;
        break;
    }
    
    intArrInput(&numArr, buffer, len);
    printIntArr(numArr, len);
}