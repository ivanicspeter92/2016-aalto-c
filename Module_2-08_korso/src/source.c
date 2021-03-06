#include <string.h>
#include "source.h"


/* Korsoraattori
 * 
 * ks -> x
 * ts -> z
 * after 3 words -> niinku
 * after 4 words -> totanoin
 */
void korsoroi(char *dest, const char *src) {
    const char* niinku = "niinku ";
    const char* totanoin = "totanoin ";
    int destination_length = 0, wordcound = 0;
    for(int i = 0; i < strlen(src); i++) {
        if (*(src + i) == 't' && *(src + i + 1) == 's') {
            *(dest + destination_length) = 'z';
            i++;
        } else if (*(src + i) == 'k' && *(src + i + 1) == 's') {
            *(dest + destination_length) = 'x';
            i++;
        } else {
            *(dest + destination_length) = *(src + i);
        }
        destination_length++;
        
        if (*(src + i) == ' ') {
            wordcound++;
        
            if (wordcound > 0 && wordcound % 3 == 0) {
                strcpy(dest + destination_length, niinku);
                destination_length += strlen(niinku);
            } else if (wordcound > 0 && wordcound % 4 == 0) {
                strcpy(dest + destination_length, totanoin);
                destination_length += strlen(totanoin);
            }
        }
    }
    *(dest + destination_length) = '\0'; 
}