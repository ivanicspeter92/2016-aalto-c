#include <stdlib.h>
#include "source.h"

int* join_arrays(unsigned int numbers1, int* pointer1, unsigned int numbers2, int* pointer2, unsigned int numbers3, int* pointer3) {
    int totalelements = numbers1 + numbers2 + numbers3;
    int* result = malloc(totalelements * sizeof(int));
    if (result != NULL) {
        int count = 0;
        
        for (int i = 0; i < numbers1; i++) {
            result[count] = pointer1[i];
            count++;
        }
        for (int i = 0; i < numbers2; i++) {
            result[count] = pointer2[i];
            count++;
        }
        for (int i = 0; i < numbers3; i++) {
            result[count] = pointer3[i];
            count++;
        }
        
        return result;
    }
    
    return NULL;
}