#include <stdio.h>
#include <math.h>
#include "source.h"

void multi_table(unsigned int xsize, unsigned int ysize) {
    for(int i = 1; i <= ysize; i++) {
        for(int j = 1; j <= xsize; j++) {
            printf("%4d", j * i);
        }
        
        printf("\n");
    }
}


void draw_triangle(unsigned int size)
{
}

double distance(int x, int y)
{
    return sqrt(x * x + y * y);
}


void draw_ball(unsigned int radius)
{
}
