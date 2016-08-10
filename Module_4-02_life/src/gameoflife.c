#include <stdlib.h>
#include <string.h>
#include "gameoflife.h"
#include <stdbool.h>

State** create_dead_cells(unsigned int xsize, unsigned int ysize) {
    State** cells_pointer = malloc(ysize * sizeof(State *));
    if (cells_pointer != NULL) {

        for(int i = 0; i < ysize; i++) {
            cells_pointer[i] = malloc(xsize * sizeof(State));

            if (cells_pointer[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(cells_pointer[j]);
                }
                free(cells_pointer);
                return NULL;
            }
            for(int j = 0; j < xsize; j++) {    
                cells_pointer[i][j] = DEAD;
            }
        }

        return cells_pointer;
    }
    
    return NULL;
}

/* Exercise a: Allocates needed memory for the field structure and
 * the actual game field. 'xsize' and 'ysize' indicate the horizontal and
 * vertical dimensions of the field.
 * 
 * Returns: pointer to the Field structure allocated by this function.
 */
Field *createField(unsigned int xsize, unsigned int ysize) {
    Field* result = malloc(sizeof(Field));
    result->cells = create_dead_cells(xsize, ysize);
    
    if (result != NULL && result->cells != NULL) {
        result->xsize = xsize;
        result->ysize = ysize;
        
        return result;
    }
    free(result);
}

/* Free memory allocated for field <f>.
 */
void releaseField(Field *f) {
    for(int i = 0; i < f->ysize; i++) {
        free(f->cells[i]);
    }
    
    free(f->cells);
    free(f);
}

/* Exercise b: Initialize game field by setting exactly <n> cells into
 * ALIVE state in the game field <f>.
 */
void initField(Field *f, unsigned int n) {
    int coord_x, coord_y;
    while (n > 0) {
        coord_y = rand() % f->ysize;
        coord_x = rand() % f->xsize;
        
        if (f->cells[coord_y][coord_x] == DEAD) {
            f->cells[coord_y][coord_x] = ALIVE;
            n--;
        }
    }
}

/* Exercise c: Output the current state of field <f>.
 */
void printField(const Field *f) {
    char dead_cell = '.', alive_cell = '*';
    
    for(int i = 0; i < f->ysize; i++) {
        for(int j = 0; j < f->xsize; j++) {
            switch (f->cells[i][j]) { 
                case DEAD:
                    printf("%c", dead_cell);
                    break;
                case ALIVE: 
                    printf("%c", alive_cell);
                    break;
            }
        }
        printf("\n");
    }
}

void copy_states(State** source, State** destination, unsigned int xsize, unsigned int ysize) {
    for(int i = 0; i < ysize; i++) {
        for(int j = 0; j < xsize; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

/// Creates a deep copy of the Field object at the provided original pointer.
/// \param original The pointer to the Field object to be copied.
/// \return The pointer to the new Field object or NULL if the copy failed.
Field* deep_copy_field(Field* original) {
    Field* result = createField(original->xsize, original->ysize);
    
    if (result != NULL) {
        copy_states(original->cells, result->cells, original->xsize, original->ysize);
        return result;
    }
    
    releaseField(result);
}

bool is_top_row(int i) {
    if (i == 0) 
        return true;
    return false;
}

bool is_bottom_row(int i, Field* of_field) {
    if (i == of_field->ysize - 1)
        return true;
    return false;
}

bool is_left_column(int j) {
    if (j == 0) 
        return true;
    return false;
}

bool is_right_column(int j, Field* of_field) {
    if (j == of_field->xsize - 1)
        return true;
    return false;
}

int get_increment_if_alive(State cell) {
    if (cell == ALIVE) 
        return 1;
    return 0;
}

int count_live_neighbors(Field* field, int i, int j) {
    int cnt = 0;
    bool left = is_left_column(j), right = is_right_column(j, field), top = is_top_row(i), bottom = is_bottom_row(i, field);
    
    // horizontal
    if(!left)
        cnt += get_increment_if_alive(field->cells[i][j - 1]);
    if(!right)
        cnt += get_increment_if_alive(field->cells[i][j + 1]);
    // vertical
    if(!top)
        cnt += get_increment_if_alive(field->cells[i - 1][j]);
    if(!bottom)
        cnt += get_increment_if_alive(field->cells[i + 1][j]);
    
    //diagonal
    if(!left && !top) 
        cnt += get_increment_if_alive(field->cells[i - 1][j - 1]);
    if(!left && !bottom) 
        cnt += get_increment_if_alive(field->cells[i + 1][j - 1]);
    if(!right && !top) 
        cnt += get_increment_if_alive(field->cells[i - 1][j + 1]);
    if(!right && !bottom) 
        cnt += get_increment_if_alive(field->cells[i + 1][j + 1]);
    
    return cnt;
}

/* Exercise d: Advance field <f> by one generation.
 */
void tick(Field *f) {
    Field* temporary_field = deep_copy_field(f); // conditions should investigate this object and release the memory when the function is done
    
    if (temporary_field != NULL) {
        int number_of_live_neighbours;
        
        for(int i = 0; i < f->ysize; i++) {
            for(int j = 0; j < f->xsize; j++) {
                number_of_live_neighbours = count_live_neighbors(temporary_field, i, j);
                
                switch(temporary_field->cells[i][j]) {
                    case ALIVE:
                        if (number_of_live_neighbours < 2) {
                            f->cells[i][j] = DEAD;
                        } else if (number_of_live_neighbours == 2 || number_of_live_neighbours == 3) {
                            f->cells[i][j] = ALIVE;
                        } else if (number_of_live_neighbours > 3) {
                            f->cells[i][j] = DEAD;
                        }
                        
                        break;
                    case DEAD:
                        if (number_of_live_neighbours == 3) {
                            f->cells[i][j] = ALIVE;
                        }
                        break;
                }
            }
        }
        
        releaseField(temporary_field);
    }
}
