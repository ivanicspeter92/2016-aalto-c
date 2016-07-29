#include <stdio.h>
#include "source.h"
#include <stdbool.h>

#ifndef MAWKKE

/* 03-mastermind
 */
bool contains(int *array, int number, unsigned int length) {
    for (int i = 0; i < length; i++) {
        if (*(array + i) == number) {
            return true;
        }
    }

    return false;
}

void mastermind(const int *solution, const int *guess, char *result, unsigned int len) {
    int next_guess;
    for (int i = 0; i < len; i++) {
        next_guess = *(guess + i);
        
        if (*(solution + i) == next_guess)
            *(result + i) = '+';
        else if (contains(solution, next_guess, len))
            *(result + i) = '*';
        else
            *(result + i) = '-';
    }
}
#endif
