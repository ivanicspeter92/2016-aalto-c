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

char* remove_characters(char* from_string, int from_index, int until_index) {
//    printf("String before removal: %s", from_string);
    int comment_length = until_index - from_index, new_string_length = 0, from_string_length = strlen(from_string);
    char* new_string = malloc(sizeof(char) * (strlen(from_string) - comment_length)); 
    
    if (new_string != NULL) {
        for(int i = 0; i < from_string_length; i++) {
            if (i < from_index || i > until_index) { 
                new_string[new_string_length] = from_string[i];
                new_string_length++;
            }
        }
//        printf("String after removal: %s", new_string);
        new_string[new_string_length] = '\0';
        free(from_string);
        return new_string;
    }
    return NULL;
}

char* remove_comment_lines(char* input) {
    char startswith[2] = "//";
    char endswith = '\n';
    
    for (int i = 1; i < strlen(input); i++) {
       if(input[i - 1] == startswith[0] && input[i] == startswith[1]) {
//           printf("Comment line starting at: [%d]\n", i - 1);
           
           for(int j = i + 1; j < strlen(input); j++) { 
               if(input[j] == endswith) {
//                   printf("Comment line ending at: [%d]\n", j);
                   int remove_from = i - 1;
                   int remove_until = j;
                   
                   input = remove_characters(input, remove_from, remove_until); 
                   break;
               }
           }
       } 
    }
    
    return input;
}

char* remove_comment_blocks(char* input) {
    char startswith[2] = "/*";
    char endswith[2] = "*/"; 
    
    for (int i = 1; i < strlen(input); i++) {
       if(input[i - 1] == startswith[0] && input[i] == startswith[1]) {
//           printf("Comment block starting at: [%d]\n", i - 1);
           
           for(int j = i + 1; j < strlen(input); j++) { 
               if(input[j - 1] == endswith[0] && input[j] == endswith[1]) {
//                   printf("Comment block ending at: [%d]\n", j);
                   int remove_from = i - 1;
                   int remove_until = j;
                   
                   input = remove_characters(input, remove_from, remove_until); 
                   break;
               }
           }
       } 
    }
    
    return input;
}

/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input) {
    input = remove_comment_lines(input);
    input = remove_comment_blocks(input);
    
    return input;
}

int count_given_characters_in_string(char c, char* string) {
    int count = 0;
    for (int i = 0; i < strlen(string); i++) {
        if(string[i] == c) {
            count++;
        }
    }
    return count;
}

int line_count(const char* string) {
    if(strlen(string) == 0)
        return 0;
    return count_given_characters_in_string('\n', string) + 1;
}

int* sum_indents_for_lines(char *input, int number_of_lines) {
    int indent_level = 0, line_number = 0;
    int result[number_of_lines];
    
    result[0] = 0;
    for(int i = 0; i < strlen(input); i++) {
        switch(input[i]) {
            case '{':
                indent_level++;
                break;
            case '}':
                indent_level--;
                break;
            case '\n': 
                line_number++; 
                result[line_number] = indent_level;
                break;
        }
    }
    return result;
}

int sum_indents(char *input) {
    int line_number = 0, indent_level = 0, count = 0;
    
    printf("Line %d @ Indent: %d\n", line_number, indent_level);
    for(int i = 0; i < strlen(input); i++) {
        switch(input[i]) {
            case '{':
                indent_level++;
                break;
            case '}':
                indent_level--;
                break;
            case '\n': 
                line_number++; 
                count += indent_level;
                printf("Line %d @ Indent: %d\n", line_number, indent_level);
                break;
        }
    }
    printf("In total %d indentations to be done\n", count);
    return count;
}

/* Indent the C-code at memory block <indent>. String <pad> represents
 * one block of indentation. Only opening curly braces '{' increase the
 * indentation level, and closing curly braces '}' decrease the indentation level.
 * Return the pointer to the code after modification.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *indent(char *input, const char *pad) {
    int indents_to_be_applied = sum_indents(input), lines_in_file = line_count(input);
    char* new_pointer = realloc(input, sizeof(input) + (sizeof(pad) * indents_to_be_applied));
    
    if (new_pointer != NULL) {
        int* indent_levels = sum_indents_for_lines(input, lines_in_file);
        
    }
}
