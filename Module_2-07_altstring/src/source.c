#include <string.h>

#include "source.h"


/* Print string */
/* Parameters:
 * s: string to be printed */
void es_print(const char *s) {
    for (int i = 0; i < strlen(s) && *(s + i) != '#'; i++) {
        printf("%c", *(s + i));
    }
}

/* String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int es_length(const char *s)
{
    (void) s;
    return 0; // replace this
}

/* String copy */
/* Parameters:
 * dst: buffer to which the new string is copied
 * src: original string
 * Returns: Number of characters copied
 */
int es_copy(char *dst, const char *src)
{
    (void) dst;
    (void) src;
    return 0; // replace this
}

/* String tokenizer */
/* Parameters:
 * s: string to be processed
 * c: character to be replaced by '#'
 * Returns: pointer to the character following the replaced character,
 *          NULL if end of string reached */
char *es_token(char *s, char c)
{
    (void) s;
    (void) c;
    return NULL; // replace this
}
