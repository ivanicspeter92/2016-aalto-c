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

int remove_comment_lines(char* input) {
    char startswith[2] = "//";
    char endswith = '\n'; 
    
    for (int i = 1; i < strlen(input); i++) {
       if(input[i - 1] == startswith[0] && input[i] == startswith[1]) {
           printf("Comment line starting at: [%d]\n", i - 1);
           
           for(int j = i + 1; j < strlen(input); j++) { 
               if(input[j] == endswith) {
                   printf("Comment line ending at: [%d]\n", j);
                   break;
               }
           }
       } 
    }
}

int remove_comment_blocks(char* input) {
    char startswith[2] = "/*";
    char endswith[2] = "*/"; 
    
    
    for (int i = 1; i < strlen(input); i++) {
       if(input[i - 1] == startswith[0] && input[i] == startswith[1]) {
           printf("Comment block starting at: [%d]\n", i - 1);
           
           for(int j = i + 1; j < strlen(input); j++) { 
               if(input[j - 1] == endswith[0] && input[j] == endswith[1]) {
                   printf("Comment block ending at: [%d]\n", j);
                   break;
               }
           }
       } 
    }
}

/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input) {
    remove_comment_lines(input);
    remove_comment_blocks(input);
    
    return input;
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
