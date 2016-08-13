#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strarray.h"

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_array(void) {
    char** pointer = malloc(sizeof(char*));
    
    if (pointer != NULL){
        pointer[0] = NULL;
        return pointer;
    }
}

/* Releases the memory used by the strings.
 */
void free_strings(char **array) {
    int count = 0;
    while(array[count] != NULL) {
        free(array[count]);
        count++;
    }
    free(array[count]);
    free(array);
}

int get_length(char** array) {
    if (array[0] == NULL)
        return 0;
    
    int cnt = 1;
    
    while (array[cnt] != NULL) {
        cnt++;
    }
    
    return cnt;
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **add_string(char **array, const char *string) {
    int count = 0;
    
    while (array[count] != NULL){
        count++;
    }
    
    char** new_pointer = realloc(array, sizeof(char*) * (count + 2));
    
    if (new_pointer != NULL) {
        new_pointer[count] = malloc((strlen(string) + 1) * sizeof(char));
        
        if (new_pointer[count] != NULL) {
            strcpy(new_pointer[count], string);
            new_pointer[count + 1] = NULL;
            
            return new_pointer;
        }
    }
}

/* Exercise c: Convert letters of all strings in <array> to lower case.
 */
void make_lower(char **array) {
    int i = 0;
    
    while(array[i] != NULL) {
        for(int j = 0; j < strlen(array[i]); j++) {
            array[i][j] = tolower(array[i][j]);
        }
        i++;
    }
}


/* Exercise d: reorder strings in <array> to lexicographical order */
void sort_strings(char **array)
{
    (void) array;
}

/* You can use this function to check what your array looks like.
 */
void print_strings(char **array)
{
    if (!array)
        return;
    while (*array) {
        printf("%s  ", *array);
        array++;
    }
    printf("\n");
}
