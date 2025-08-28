#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int* convertToIntArr(char* str, int size);
void sortArr(int* arr, int size);
void smallerNums1(int* intArr, int size);
void printArray(int* arr, int n);

int main(void) {
    // First lets practice getting input
    char* buffer = NULL; // Must set uninitialized pointers to NULL (AKA, always initialize pointers)
    size_t bufsize;
    ssize_t nread;
    int len;
    int* numArr = NULL;

    fprintf(stdout, "Enter numbers (##...): ");

    // Retrieve input with getline
    while((nread = getline(&buffer, &bufsize, stdin)) != -1) {
        len = nread - 1;
        break;
    }

    numArr = convertToIntArr(buffer, len);

    // Apply the algorithm on numArr
    smallerNums1(numArr, len);
}

void smallerNums1(int* intArr, int size) {
    // For now lets just sort and print to test the sorting algorithm
    sortArr(intArr, size);

    printArray(intArr, size); // WORKS!!!

    typedef struct entry { // each entry must have the occ and the res string
        int occs;
        char* resStr;
    } entry;

    entry map[size];
    char res[size];

    for (int i=0; i<size; i++) {
        map[i].occs = 0;
        map[i].resStr = NULL;
    }

    for (int i=0; i<size; i++) {
        int val = intArr[i];
        map[val].occs += 1;
        if (map[val].resStr == NULL) { // String not set
            map[val].resStr = malloc(size * 2);
            sprintf(map[val].resStr, "%s,", res);
        }
        // Append the number to the res
        res[i] = val;
    }

    // Now we have our answer, loop through the map and print it all out
    for (int i=0; i<size; i++) {
        if(map[i].occs > 0) { //only print numbers that had others less
            fprintf(stdout, "Num: %d #Less: %d (%s)\n", i, map[i].occs, map[i].resStr);
        }
    }

    return;
}

/* Apply an O(nlogn) sorting function to sort an integer array
   Actually, we could make an O(n) sorting function but the tradeoff is space complexity
   Using a mapping we could map the cur int value as an index and increment the count in the
   map for the number of occurances.
   Then, we would loop through the map and add each digit for the number of occurences
   This would require a nested loop but it is not O(n^2) because we only hit each element
   of the originial array twice

   NOTE: this sort only works for numbers 0-9 for largers numbers we would need a larger map
 */
void sortArr(int* arr, int size) {
    int map[10]; // since there are 10 digits 0-9
    for (int i=0; i<10; i++) {
        map[i] = 0;
    }

    for (int i=0; i<size; i++) { // map the numbers
        map[arr[i] - 1] += 1;
    }

    // Note: we can reuse the arr integer array because the result is the same size we will overwrite every value
    // I will not do this because I want to return an int array, semantic purposes
    int k = 0;
    for (int i=0; i<size; i++) { // loop through the map to return the sorted array
        int occs = map[i];
        for(int j=0; j<occs; j++) { // this will skip if a 0 has been mapped
            arr[k] = i + 1;
            k++;
        }
    }
    return;
}

// NOTE: the convertToIntArr is only converting single digit ints.
// I will make functions to improve this after solving this problem
int* convertToIntArr(char* str, int size) {
    int* arr = malloc(size * sizeof(int));
    if (!arr) return NULL; // check malloc for failures or NULL returns
    // ASCII for digits 0-9 is 48-57 so we subtract 48 from each char
    // int res[size];
    // My orginial function had malloc and also used a while loop until the null terminator
    // We actually don't need to do this because we are passing the size of the array, so
    // the size of the new array is known in the parameters
    
    for(int i=0; i<size; i++) {
        arr[i] = *str - 48;
        str = str + 1;
    }

    return arr;
}

// Code pasted from ChatGPT, I got lazy, it happens
void printArray(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}