#include <string.h>

#include "source.h"
#include "ctype.h"

/* Count Alpha
 * Count number of alphabetic characters in the given string <str>,
 * and return the count
 */
int count_alpha(const char *str) {
    int count = 0;
    
    for (int i = 0; i < strlen(str); i++) {
        if (isalpha(*(str + i)) != 0) {
            count++;
        }
    }
    
    return count;
}


/* Count Substring
 * Count number of occurances of substring <sub> in string <str>,
 * and return the count.
 */
int count_substr(const char *str, const char *sub) {
    int count = 0;
    int substring_pointer = 0;
    char next_in_str, next_in_sub;
    for (int i = 0; i < strlen(str); i++) {
        next_in_str = *(str + i);
        next_in_sub = *(sub + substring_pointer);
        if (next_in_str == next_in_sub) {
            substring_pointer++;
            if (substring_pointer == strlen(sub)) {
                count++;
                substring_pointer = 0;
            }  
        } else 
            substring_pointer = 0;
    }
    
    return count;
}