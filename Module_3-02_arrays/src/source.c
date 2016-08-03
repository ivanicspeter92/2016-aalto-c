#include <stdlib.h>
#include "source.h"


/* Dynamic Array Reader */
/* Parameters:
 * n: Number of values to be read
 * 
 * Returns: pointer to the dynamically allocated array
 */
int *dyn_reader(unsigned int n) {
    int *address = malloc(n * sizeof(int));
    
    if (address != NULL) {
        int array[n];
        for(int i = 0; i < n; ++i) {
            scanf("%d", (address + i));
        }

        return address;
    }
}

/* Add to array */
/* Parameters:
 * arr: Existing array of integers
 * num: number of integers in the array before the call
 * newval: new value to be added
 * 
 * Returns: pointer to the allocated array
 */
int *add_to_array(int *arr, unsigned int num, int newval)
{
    return NULL;  // replace this
}
