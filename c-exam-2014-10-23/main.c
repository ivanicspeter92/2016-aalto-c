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
    if (elements > 0) {
        float sum_of_numbers = sum(array, elements);
//        printf("Sum: %f\n", sum_of_numbers);
        return(sum_of_numbers / elements);
    }
    return 0;
}

void print_result(const float average) {
    printf("%f", average);
}

void calculate_averages(int argc, char* argv[]) {
    float array[argc - 1];
//    printf("Count: %d\n", argc);
    for(int i = 0; i < argc; i++) {
        array[i] = atof(argv[i]);
    }
    
    print_result(average(array, argc));
}

void output_of_a_program() {
    char s[] = "Alexander Graham Bell";
     char* p=(char*)0;
     int x = 45;
     int *px=(int *)0;
     int *sx=&x;
     p=s;     
     *p='F';
     printf ("%s\n", s); // Flexander Graham Bell
     p += 17; *p ='D';
     printf ("%s\n", s); // Flexander Graham Dell
     printf ("%d\n", *sx+5); // 50
     px = sx;
     printf("%d\n", *px); // 45
     *px = 83;
     printf("%d %d %d"/*\n*/, *px, x, *sx); // 83 83 83
}

/*
 * Calculate the average of floating-point values entered as argument at the command line and prints out the result with 2 significant decimal digits. 
 * If no values were given, inform the user. Do not assume a fixed number of input values. 
 * Your program should work with any number of arguments.
 */
int main(int argc, char* argv[]) {
    // task 1
    if(argc == 1) {
        char* arguments[4] = { "./program", "2.0", "2.0", "1.5"};
        calculate_averages(3, arguments + 1);
    } else {
        calculate_averages(argc, argv);
    }
}

