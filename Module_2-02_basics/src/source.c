#include <stdio.h>
#include "source.h"


/* Number swap
 * Swap the content of integers add addresses a and b
 */
void number_swap(int *a, int *b) {
    int temp = *a;
    *a = *b; 
    *b = temp;
}

/* Array Sum
 * Calculate the sum of integers in array starting at address <array>.
 * There will be <count> elements in array. Return the sum as return value.
 */
int array_sum(int *array, int count) {
    int sum = 0;
    
    for(int i = 0; i < count; i++) {
        int value = *(array + i);
        sum += value;
    }
    
    return sum;
}

/* Array Reader */
/* Parameters:
 * vals: array to be filled 
 * n: maximum size of array
 * returns: number of values read */
int array_reader(int *vals, int n) {
    int count = 0;
    int value;
    
    while (n > 0 && scanf("%d", &value) != 0) {
        *(vals + count) = value;
        n--;
        count++;
    }
    
    return count;
}
