#include "fileread.h"
#include <stdio.h>
#include <ctype.h>

/* Prints the given file as text on the screen.
 * Only printable characters are shown. Non-printable characters are printed
 * as '?'. <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int textdump(const char *filename) {
    FILE* filestream = fopen(filename, "r");
    
    if (filestream != NULL) {
        char next_character_in_file;
        int count = 0;
        
        while((next_character_in_file = fgetc(filestream)) != EOF) {
            if (isprint(next_character_in_file)) {
                printf("%c", next_character_in_file);
            } else {
                printf("?");
            }
            count++;
        }
        
        fclose(filestream);
        return count;
    }
    return -1;
}


/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int hexdump(const char *filename)
{
    (void) filename;
    return 0;
}
