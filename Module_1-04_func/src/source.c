#include <math.h>

/**
 * Calculates the length of 3 dimensional Euclidean vector based on the three given parameters.
 * 
 * @param a
 * @param b
 * @param c
 * @return The length of the vector as a double value. 
 */
double vectorlength(double a, double b, double c) {
    double result = sqrt(a * a + b * b + c * c);
    
    return result; 
}