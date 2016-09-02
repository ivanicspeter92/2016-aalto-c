/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: peter.ivanics
 *
 * Created on September 3, 2016, 1:12 AM
 */

#include <stdio.h>
#include <stdlib.h>

float sum(float* array, int elements) {
    float result = 0;
    
    for (int i = 0; i < elements; i++) {
        result += array[i];
    }
    
    return result;
}

/*
 * Accepts a 1-dimensional floating point array and its size as arguments and returns the average of the values in that array.
 */
float average(float* array, int elements) {
    if (elements > 0)
        return(sum(array, elements) / elements);
    return 0;
}

void print_result(const float average) {
    printf("%f.2", average);
}

/*
 * Calculate the average of floating-point values entered as argument at the command line and prints out the result with 2 significant decimal digits. 
 * If no values were given, inform the user. Do not assume a fixed number of input values. 
 * Your program should work with any number of arguments.
 */
int main(int argc, char** argv) {
    
}

