#include <stdio.h>
#include <math.h>
#include "source.h"

void simple_sum(void) {
   int a, b;
   
   scanf("%d %d", &a, &b);
   
   print_sum(a, b);
}

/**
 * Sums up the two given integers and prints them to the console in the defined format. 
 * 
 * @param a
 * @param b
 */
void print_sum(int a, int b) {
    int result = a + b;
    printf("%d + %d = %d\n", a, b, result);
}

void simple_math(void) {
    float a, b;
    char operator;
    
    if (scanf("%f %c %f", &a, &operator, &b) == 3) { // checking if scanning both numbers and the operator succeeded
        print_result(a, b, operator);
    } else {
        printf("ERR");
    }
}

/**
 * Performs the operation on the given parameters and prints the result on the console. Prints 'ERR' on the console if the operator is incorrect.
 * 
 * @param a
 * @param b
 * @param operator The character of the operator to be performed. Should be '+', '-', '/' or '*' character.
 */
void print_result(float a, float b, char operator) {
    char* format = "%.1f";
    switch (operator) {
        case '+': printf(format, a + b); break;
        case '-': printf(format, a - b); break;
        case '*': printf(format, a * b); break;
        case '/': printf(format, a / b); break;
        default: printf("ERR");
    }
}
