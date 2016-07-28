#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "source.h"

/* Don't touch the definition of msgs array! Checker uses this. */
char *msgs[10] = {
    "'6=*w+~)._", "J65+~5+~=0/*69,~+9;,9*~19++=79"
};


void ascii_chart(char min, char max) {
    int tabulators = 1;
    for (int i = min; i <= max; i++) {
        printf(" %d 0x%x", i, i);
        
        print_character_or_question_mark(i);
        
        if (tabulators % 4 == 0) {
            printf("\n");
            tabulators = 1;
        } else {
            tabulators++;
            printf("\t");
        }
    }
}

void print_character_or_question_mark(int i) {
    if (isprint(i) == 0) {
            printf(" ?");
        } else {
            printf(" %c", i);
        }
}

char get_character(int msg, unsigned int cc) {
    if (msg >= 10 || !msgs[msg])
        return 0;

    if (strlen(msgs[msg]) <= cc)
        return 0;
    
    return msgs[msg][cc];
}


void secret_msg(int msg) {
    int i = -1;
    
    char character;
    while (character = get_character(msg, ++i)) {
        if (character != 0) {
            printf("%c", 158 - character);
        }
    } 
}
