#include <stdio.h>
#include <stdlib.h>
#include "ships.h"
#include <stdbool.h>

const unsigned int xsize = 10;
const unsigned int ysize = 10;
const unsigned int shiplen = 3;

int get_random_x() {
    return rand() % xsize;
}

int get_random_y() {
    return rand() % ysize;
}


bool is_correct_x(int x) {
    return x >= 0 && x < xsize;
}

bool is_correct_y(int y) {
    return y >= 0 && y < ysize;
}

/* implement these functions */

/* Task a: Place <num> ships on the game map.
 */
void set_ships(unsigned int num) {
    create_field();
    while (num > 0) {
        int x = get_random_x(), y = get_random_y();
        
        if (place_ship(x, y, 0) == 1) { // attempting to place the ship horizontally 
            num--;
        } else if (place_ship(x, y, 1) == 1) { // attempting to place the ship vertically 
            num--;
        }
    }
}

/* Task b: print the game field
 */
void print_field(void) {
    for(int i = 0; i < ysize; i++) {
        for (int j = 0; j < xsize; j++) {
            if (is_visible(j, i) == 0) {
                printf("?");
            } else {
                printf("%c", is_ship(j, i));
            }
        }
        printf("\n");
    }
}


/* Task c: Ask coordinates (two integers) from user, and shoot the location.
 * Returns -1 if user gave invalid input or coordinates, 0 if there was no ship
 * at the given location; and 1 if there was a ship hit at the location.
 */
int shoot(void) {
    int x, y;
   
    if (scanf("%d %d", &x, &y) != 0 && is_correct_x(x) && is_correct_y(y)) { // checking for valid user input
        checked(x, y);
        if (is_ship(x, y) == '.') {
            return 0;
        } else {
            hit_ship(x, y);
            return 1;
        }
    }
    
    return -1;
}

/* Task d: Returns 1 if game is over (all ships are sunk), or 0 if there
 * still are locations that have not yet been hit. <num> is the number of
 * ships on the game map. It is assumed to be the same as in the call to
 * set_ships function.
 */
int game_over(unsigned int num) {
    int sunkenshipfields = 0;
    
    for(int i = 0; i < ysize; i++) {
        for (int j = 0; j < xsize; j++) {
            if (is_ship(j, i) == '#') { // checking if a ship is sunken
                sunkenshipfields++;
            }
        }
    }
    
    if (sunkenshipfields / shiplen == num) { // checking if the sunken fields sum up to the number of ships
        return 1;
    }
    return 0;
}
