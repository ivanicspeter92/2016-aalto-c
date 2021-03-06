#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "spreadsheet.h"
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

const struct {
    char *name;
    double (*fptr)(Sheet *,Point, Point);
} functions[] = {
    { "sum", sumfunc },
    { "max", maxfunc },
    { "count", countfunc },
    { NULL, NULL }
};

void create_cells(Cell* cells, unsigned int how_many) {
    for(unsigned int i = 0; i < how_many; i++) {
        cells[i].type = UNSPEC;
    }
}

void free_cells(Cell** cells, unsigned int length) {
    for(unsigned int i = 0; i < length; i++) {
        free(cells[i]);
    }
    
    free(cells);
}

/* Creates a new spreadsheet with given dimensions.
 * Returns pointer to the allocated Sheet structure.
 */
Sheet *create_sheet(unsigned int xsize, unsigned int ysize) {
    Sheet* sheet_pointer = malloc(sizeof(Sheet));
    
    if (sheet_pointer != NULL) {
        sheet_pointer->xsize = xsize;
        sheet_pointer->ysize = ysize;
        sheet_pointer->cells = malloc(ysize * sizeof(Cell*));
        
        if (sheet_pointer->cells == NULL) {
            free(sheet_pointer);
            return NULL;
        }
        for(unsigned int i = 0; i < ysize; i++) {
            sheet_pointer->cells[i] = malloc(xsize * sizeof(Cell));
            
            if(sheet_pointer->cells[i] == NULL) {
                free_cells(sheet_pointer->cells, sheet_pointer->ysize);
                return NULL;
            }
            create_cells(sheet_pointer->cells[i], xsize);
        }
        
        return sheet_pointer;
    }
    
    return NULL;
}

/* Releases the memory allocated for sheet.
 */
void free_sheet(Sheet *sheet) {
    free_cells(sheet->cells, sheet->ysize);
    free(sheet);
}

/* Returns pointer to the Cell structure at given location <p>
 * in spreadsheet <sheet>.
 */
Cell *get_cell(Sheet *sheet, Point p) {
    if (p.x >= sheet->xsize || p.y >= sheet->ysize)// || p.y < 0 || p.x < 0 )
        return NULL;
    
    return &(sheet->cells[p.y][p.x]);
}

/* Convert two-letter user input into coordinates of type Point.
 */
Point get_point(char xc, char yc) {
    Point p;
    p.x = toupper(xc) - 'A';
    p.y = toupper(yc) - 'A';
    return p;
}

/* Parses user input in <command> and applies it in spreadsheet <sheet>.
 * Returns 1 if input was valid, or 0 if it was not.
 */
int parse_command(Sheet *sheet, const char *command) {
    double val;
    Point p;
    char xc, yc;
    int ret = sscanf(command, "%c%c %lf", &xc, &yc, &val);
    if (ret == 3) {
        p = get_point(xc, yc);
        set_value(sheet, p, val);
        return 1;
    }
    
    char func[10];
    Point ul, dr;
    char xc1, yc1, xc2, yc2;
    
    ret = sscanf(command, "%c%c %9s %c%c %c%c", &xc, &yc, func, &xc1, &yc1, &xc2, &yc2);
    if (ret == 7) {
        p = get_point(xc, yc);
        ul = get_point(xc1, yc1);
        dr = get_point(xc2, yc2);
        int i = 0;
        while (functions[i].name) {
            if (!strcmp(functions[i].name, func)) {
                set_func(sheet, p, functions[i].fptr, ul, dr);
                return 1;
            }
            i++;
        }
    }
    return 0;
}

/* Prints the content of given spreadsheet.
 */
void print_sheet(Sheet *sheet) {
    printf("%-8c", ' ');
    for (unsigned int x = 0; x < sheet->xsize; x++) {
        printf("%-8c", 'A' + x);
    }
    fputs("\n", stdout);
    
    for (unsigned int y = 0; y < sheet->ysize; y++) {
        printf("%-8c", 'A' + y);
        for (unsigned int x = 0; x < sheet->xsize; x++) {
            Point p;
            p.x = x;
            p.y = y;
            Cell *c = get_cell(sheet, p);
            switch(c->type) {
                case VALUE:
                case FUNC:
                    printf("%-8.1f", eval_cell(sheet, p));
                    break;
                    
                default:
                    printf("%-8c", '*');
                    break;                    
            }
        }
        fputs("\n", stdout);
    }
}

/* Set the content of location <p> in spreadsheet to constant <value>
 */
void set_value(Sheet *sheet, Point p, double value) {
    Cell* cell = get_cell(sheet, p);
    
    if (cell != NULL) {
        cell->un.value = value;
        cell->type = VALUE;
    }
}

bool point_exist_in_sheet(Point point, Sheet* sheet) {
    if (point.x < sheet->xsize && point.y < sheet->ysize)
        return true;
    return false;
}

/* Set the content of location <p> in spreadsheet to given function.
 * <func> is pointer to the function. <ul> is the upper left corner and 
 * <dr> is the lower right corner of the area over which the function
 * is applied.
 */
void set_func(Sheet *sheet, Point p, double (*func)(Sheet *, Point, Point), Point ul, Point dr) {
    Cell* cell = get_cell(sheet, p);
    
    if (cell != NULL && point_exist_in_sheet(ul, sheet) && point_exist_in_sheet(dr, sheet)) {
        cell->un.func.upleft = ul;
        cell->un.func.downright = dr;
        cell->un.func.fptr = func;
        cell->type = FUNC;
    }
}

/* Evaluate the content of cell at location <p>.
 * If cell is constant value, that is returned.
 * If cell contains function, the function is evaluated and its result returned.
 * If cell is unspecified or location out of bounds, NAN is returned.
 */
double eval_cell(Sheet *sheet, Point p) {
    if(point_exist_in_sheet(p, sheet)) {
        Cell* cell = get_cell(sheet, p);
        
        switch (cell->type) {
            case VALUE:
                return cell->un.value;
            case FUNC:
                return cell->un.func.fptr(sheet, cell->un.func.upleft, cell->un.func.downright);
            case UNSPEC:
                return NAN;
        }
    }
    return NAN;
}

/* Calculate the maximum value within area with upper left corner <ul>
 * and lower right corner <dl>, and return it.
 */
double maxfunc(Sheet *sheet, Point ul, Point dr) {
    Point current_point;
    double max = DBL_MIN;
    double cell_value;
    
    for(unsigned int i = ul.y; i <= dr.y; i++) {
        for(unsigned int j = ul.x; j <= dr.x; j++) {
            current_point.y = i;
            current_point.x = j;
            cell_value = eval_cell(sheet, current_point);
                    
            if(max < cell_value)
                max = cell_value;
        }
    }
    
    return max;
}

/* Calculate the sum of values within upper left corner <ul> and
 * lower right corner <dr>, and return the result.
 */
double sumfunc(Sheet *sheet, Point ul, Point dr) {
    Point current_point;
    double sum = 0;
    double cell_value;
    
    for(unsigned int i = ul.y; i <= dr.y; i++) {
        for(unsigned int j = ul.x; j <= dr.x; j++) {
            current_point.y = i;
            current_point.x = j;
            cell_value = eval_cell(sheet, current_point);
            
            if (isnan(cell_value) == false)
                sum += cell_value;
        }
    }
    
    return sum;
}

bool has_content(Cell cell) {
    if (cell.type == UNSPEC)
        return false;
    return true;
}

/* Count the number of specified cells inside the area with upper left
 * corner <ul> and lower right corner <dr>.
 */
double countfunc(Sheet *sheet, Point ul, Point dr) {
    Point current_point;
    double count = 0;
    double cell_value;
    
    for(unsigned int i = ul.y; i <= dr.y; i++) {
        for(unsigned int j = ul.x; j <= dr.x; j++) {
            if (has_content(sheet->cells[i][j])) {
                current_point.y = i;
                current_point.x = j;
                cell_value = eval_cell(sheet, current_point);

                if (isnan(cell_value) == false)
                    count++;
            }
        }
    }
    
    return count;
}
