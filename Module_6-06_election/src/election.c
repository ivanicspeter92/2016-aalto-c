#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "election.h"

void replace_endline_with_end_of_string(char* string) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == '\n') {
            string[i] = '\0';
            return;
        }
    }
}

int contains(char* name, struct votes* votes, int length) {
    for(int i = 0; i < length; i++) {
        if(strcmp(name, votes[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

struct votes *read_votes(const char *filename) {
    FILE* file = fopen(filename, "r");
    
    if (file != NULL) {
        
            int buffer_length = 40, length = 0, index = -1;
            char* buffer[buffer_length];
            struct votes* result; 
            
            while(fgets(buffer, buffer_length, file) != NULL) {
                if (length == 0) {
                    result = malloc(sizeof(struct votes));
                } else {
                    result = realloc(result, sizeof(struct votes) * (length + 1));
                }
                
                if (result == NULL) {
                    free(result);
                    break;
                }
                
                replace_endline_with_end_of_string(buffer);
                
                if (length > 0 && (index = contains(buffer, result, length)) != -1) {
                    result[index].votes += 1;
                } else {
                    strcpy(result[length].name, buffer);
                    result[length].votes = 1;
                    length++;
                }
            }
        
        fclose(file);
        return result;
    }
    return NULL;
}

void results(struct votes *vlist) {
    (void) vlist;
}