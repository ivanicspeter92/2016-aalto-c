#include "source.h"

/* Number swap
 * Swap the content of integers add addresses a and b
 */
void number_swap(int *a, int *b) {
    int temp = *a;
    *a = *b; 
    *b = temp;
}

/* Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void sort(int *start, int size) {
    int numbers_in_place = 0;
    int next_smallest_number; // the next number to be put in place in the array
    int next_smallest_number_index;
    int temp;
    
    while (numbers_in_place < size) {
        next_smallest_number = *(start + numbers_in_place); // putting the first item as the smallest
        next_smallest_number_index = numbers_in_place; // storing the index of the first item in this iteration
        
        for (int i = numbers_in_place + 1; i < size; i++) {
            if (*(start + i) < next_smallest_number) { // checking if any numbers are smaller than the first
                next_smallest_number = *(start + i);
                next_smallest_number_index = i;
            }
        }
        
        // swapping the element at the next index with the smallest found
//        number_swap(*(start + next_smallest_number_index), *(start + numbers_in_place));
        temp = *(start + next_smallest_number_index);
        *(start + next_smallest_number_index) = *(start + numbers_in_place);
        *(start + numbers_in_place) = temp;
        
        numbers_in_place++;
    }
}
