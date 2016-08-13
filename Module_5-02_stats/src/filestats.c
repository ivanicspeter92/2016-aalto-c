#include "filestats.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
int line_count(const char *filename) {
    FILE* filestream = fopen(filename, "r");
    
    if (filestream != NULL) {
        char next_character_in_file;
        int line_count = 1, character_count = 0;
        bool is_last_line_empty = true;
        
        while((next_character_in_file = fgetc(filestream)) != EOF) {
            character_count++;
            if (isprint(next_character_in_file)) 
                is_last_line_empty = false;
            if (next_character_in_file == '\n') {
                line_count++;
                is_last_line_empty = true;
            } 
        }
        fclose(filestream);
        
        if (character_count == 0)
            return 0;
        else {
            if (isprint(next_character_in_file) || is_last_line_empty == false) {
                return line_count;
            } else 
                return line_count - 1;
        }
    }
    return -1;
}


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
int word_count(const char *filename)
{
    (void) filename;
    return 0;
}
