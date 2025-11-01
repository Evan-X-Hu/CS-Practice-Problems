#include <stdlib.h>
#include <stdio.h>

/** Simple function leveraging C's formatted strings to print the integers
 *  in an integer array
 */
void printIntArr(int* arr, int size) {
    int i=0;
    while(i<size - 1) {
        fprintf(stdout, "%d, ", arr[i]);
        i++;
    }
    fprintf(stdout, "%d\n", arr[i]);
}