#include <stdio.h>
#include <string.h>
#include "source.h"

int main()
{
    char orig[4][200] = { "yksi auto valui itsekseen ilman kuljettajaa makea alas",
        "kaks",
        "sleeping now zzzz tststs good night"};
    
    char ref[4][200] = { "yxi auto valui niinku izexeen totanoin ilman kuljettajaa niinku makea alas",
        "kax",
        "sleeping now zzzz niinku zzz totanoin good night"};
    
    int count = 3;
    
    
    char *buffer = malloc(200);
    for (int i = 0; i < count; i++) {
        memset(buffer, '#', 200);
        buffer[0] = 0;
        printf("%s\n", orig[i]);
        korsoroi(buffer, orig[i]);
        printf("%s\n", buffer);
        buffer[199] = 0;
    }
    free(buffer);
    
    return 0;
}
