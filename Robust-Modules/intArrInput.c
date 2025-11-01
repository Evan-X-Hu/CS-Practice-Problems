#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/**Iterating from the back to the front, we can do something like 10^x multiplied by our
 * current digit then add that to the current value. Then, we would reset x everytime we
 * hit a ',' and also add that value. Note, that we would also have to add the current value
 * at the end of the loop since there is no ','.
 * 
 * How does this work with the null terminator
 * Our input array will be:
 * "aaaa" with size of 4
 */
void intArrInput(int** buffer, char* input, int size) {
    int count = 0;
    for(int i=0; i<size; i++) {
        if(input[i] == ",") {count++;}
    }
    count++; // Account for the extra integer
    int *result = (int *)malloc(count);

    char* token;
    char* rest = input;
    while((token = ))

}