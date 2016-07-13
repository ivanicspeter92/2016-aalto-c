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
    
}
