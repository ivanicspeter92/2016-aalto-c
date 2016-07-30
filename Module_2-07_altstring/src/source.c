#include <string.h>
#include "source.h"
#include "ctype.h"

const char end_of_string_character = '#';

/* Print string */
/* Parameters:
 * s: string to be printed */
void es_print(const char *s) {
    for (int i = 0; i < strlen(s) && *(s + i) != end_of_string_character; i++) {
        printf("%c", *(s + i));
    }
}

/* String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int es_length(const char *s) {
    int length = 0;
    while (length < strlen(s) && *(s + length) != end_of_string_character) {
        length++;
    }
    
    return length;
}

/* String copy */
/* Parameters:
 * dst: buffer to which the new string is copied
 * src: original string
 * Returns: Number of characters copied
 */
int es_copy(char *dst, const char *src) {
    int copied = 0;
    
    while(copied < strlen(src) && *(src + copied) != end_of_string_character) {
        *(dst + copied) = *(src + copied);
        copied++;
    }
    *(dst + copied) = end_of_string_character;
    
    return copied;
}

/* String tokenizer */
/* Parameters:
 * s: string to be processed
 * c: character to be replaced by '#'
 * Returns: pointer to the character following the replaced character,
 *          NULL if end of string reached */
char *es_token(char *s, char c) {
    for (int i = 0; i < strlen(s) && *(s + i) != end_of_string_character; i++) {
        if (*(s + i) == c) {
            *(s + i) = end_of_string_character;
            return (s + i + 1);
        }
    }
    return NULL;
}
