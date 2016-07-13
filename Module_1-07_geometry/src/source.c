#include <stdio.h>
#include <math.h>
#include "source.h"
#include <stdbool.h>

void multi_table(unsigned int xsize, unsigned int ysize) {
    for(int i = 1; i <= ysize; i++) {
        for(int j = 1; j <= xsize; j++) {
            printf("%4d", j * i);
        }
        
        printf("\n");
    }
}

void draw_triangle(unsigned int size) {
    int dotCount;
    for (int i = 1; i <= size; i++) {
        dotCount = size - i;
        for (int j = 1; j <= size; j++) {
            if (dotCount > 0) {
                printf(".");
                dotCount--;
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

double distance(int x, int y) {
    return sqrt(x * x + y * y);
}

bool is_in_circle(int x, int y, int radius) {
    if (distance(x,y) <= radius) {
        return true;
    }
    return false;
}

void draw_ball(unsigned int radius) {
}
