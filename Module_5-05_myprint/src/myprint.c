#include "myprint.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int count_format_specifiers(char* string, char format_specifier) {
    int count = 0;
    
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == format_specifier)
            count++;
    }
    
    return count;
}

int myprint(char* format, ...) {
    char format_specifier = '&';
    va_list args;
    
    int format_specifiers_count = count_format_specifiers(format, format_specifier);
    va_start(args, format_specifiers_count);
    
    for(int i = 0; i < strlen(format); i++) {
        if(format[i] != format_specifier)
            fputc(format[i], stdout);
        else
            fprintf(stdout, "%d", va_arg(args, int));
        
    }
    va_end(args);
    return format_specifiers_count;
}