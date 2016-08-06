#include <stdlib.h>
#include "source.h"

void join_array(unsigned int number_of_elements, int* pointer_to_array, int* pointer_to_result) {
    for (int i = 0; i < number_of_elements; i++) {
        pointer_to_result[i] = pointer_to_array[i];
    }
}

int* join_arrays(unsigned int numbers1, int* pointer1, unsigned int numbers2, int* pointer2, unsigned int numbers3, int* pointer3) {
    int totalelements = numbers1 + numbers2 + numbers3;
    int* result = (int*)malloc(totalelements * sizeof(int));
    if (result != NULL) {
        join_array(numbers1, pointer1, result + 0);
        join_array(numbers2, pointer2, result + numbers1);
        join_array(numbers3, pointer3, result + numbers1 + numbers2);
        
//        int count = 0;
//        for (int i = 0; i < numbers1; i++) {
//            result[count] = pointer1[i];
//            count++;
//        }
//        for (int i = 0; i < numbers2; i++) {
//            result[count] = pointer2[i];
//            count++;
//        }
//        for (int i = 0; i < numbers3; i++) {
//            result[count] = pointer3[i];
//            count++;
//        }
        
        return result;
    }
    
    return NULL;
}