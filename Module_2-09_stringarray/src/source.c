#include "source.h"
#include <stdlib.h>
#include <string.h>

/* Print string array, last element is NULL */
/* Parameters:
 * array: string array to be printed, each string on own line */
void print_strarray(char *array[]) {
    int i = 0;
    
    while (*(array + i) != NULL) {
        printf("%s\n", *(array + i));
        i++;
    }
}

/* Put strings from string separated by space to a string array */
/* Parameters:
 * string: string to be cut into parts and placed into the array, 
   remember to add ending zeros '\0' for strings and NULL to the end of the whole array!
 * arr: ready-made array that the strings will be put into */
void str_to_strarray(char* string, char** arr) {
    char delimiter = ' ';
    int i;
    int count = 0; 
    int j = 0;
    for(i = 0; i < strlen(string); i++) {
        if (*(string + i) == delimiter) {
            arr[count][j] = '\0';
            count++;
            j = 0;
        } else {
            arr[count][j] = *(string + i);
            j++;
        }
    }
    arr[count][j] = '\0';
    arr[count + 1] = NULL;
}
