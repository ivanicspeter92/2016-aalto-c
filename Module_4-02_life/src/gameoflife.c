#include <stdlib.h>
#include "gameoflife.h"


/* Exercise a: Allocates needed memory for the field structure and
 * the actual game field. 'xsize' and 'ysize' indicate the horizontal and
 * vertical dimensions of the field.
 * 
 * Returns: pointer to the Field structure allocated by this function.
 */
Field *createField(unsigned int xsize, unsigned int ysize) {
    Field* result = malloc(sizeof(Field));
    
    if (result != NULL) {
        
        result->cells = malloc(ysize * sizeof(State *));
        if (result->cells != NULL) {
            result->xsize = xsize;
            result->ysize = ysize;
            
            for(int i = 0; i < ysize; i++) {
                result->cells[i] = malloc(xsize * sizeof(State));
                
                if (result->cells[i] == NULL) {
                    for (int j = 0; j < i; j++) {
                        free(result->cells[j]);
                    }
                    free(result->cells);
                    free(result);
                    return NULL;
                }
                for(int j = 0; j < xsize; j++) {    
                    result->cells[i][j] = DEAD;
                }
            }

            return result;
        }
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
void printField(const Field *f)
{
    (void) f;
}


/* Exercise d: Advance field <f> by one generation.
 */
void tick(Field *f)
{
    (void) f;
}
