#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "polisher.h"

long get_file_size(FILE* file_pointer) {
    fseek(file_pointer, 0, SEEK_END);
    long file_size = ftell(file_pointer);
    fseek(file_pointer, 0, SEEK_SET); 
    
    return file_size;
}

/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename) {
    FILE *file_pointer = fopen(filename, "r");
    if (file_pointer != NULL) {
        long file_size = get_file_size(file_pointer); 
        char *string = malloc(file_size + 1);

        if (string != NULL) {
            fread(string, file_size, 1, file_pointer);
            fclose(file_pointer);
            string[file_size] = '\0';

            return string;
        }
        fclose(file_pointer);
    }
}

/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input) {
    (void) input;
    return NULL;
}

/* Indent the C-code at memory block <indent>. String <pad> represents
 * one block of indentation. Only opening curly braces '{' increase the
 * indentation level, and closing curly braces '}' decrease the indentation level.
 * Return the pointer to the code after modification.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *indent(char *input, const char *pad) {
    (void) input;
    (void) pad;
    return NULL;
}
