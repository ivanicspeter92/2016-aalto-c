#include "base64.h"
#include <stdio.h>
#include <string.h>

/* The set of base64-encoded characters. You may use this table if you want.
 * (The last character is not part of the actual base64 set, but used for
 * padding). 
 */
const char *encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int index_in_base64(char c) {
    for(unsigned int i = 0; i < strlen(encoding); i++) {
        if(c == encoding[i]) {
            return i;
        } 
    }
    return -1;
}

/* Open file named <src_file> for reading, and convert it to Base64 format,
 * which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int to_base64(const char *dst_file, const char *src_file) {
    FILE* source_filestream = fopen(src_file, "r");
    FILE* output_filestream = fopen(dst_file, "w");
    int count = 0;
    
    if (source_filestream != NULL && output_filestream != NULL) {
        char buffer[3 + 1];
        while (fgets(buffer, sizeof(buffer), source_filestream) != NULL) {
            count += strlen(buffer);
                int index = (buffer[0] & 0xFC) >> 2;
                fputc(encoding[index], output_filestream);
                
                index = (buffer[0] & 0x03) << 4;
                index = index | ((buffer[1] & 0xF0) >> 4); 
                fputc(encoding[index], output_filestream);
                
                if(strlen(buffer) > 1) {
                    index = ((buffer[1] & 0x0F) << 2);
                    index = index | (buffer[2] >> 6); 
                    fputc(encoding[index], output_filestream);
                    
                    if(strlen(buffer) > 2) {
                        index = (buffer[2] & 0x3F); 
                        fputc(encoding[index], output_filestream);
                    } else {
                        fputc('=', output_filestream);
                    }
                } else {
                    fputc('=', output_filestream);
                    fputc('=', output_filestream);
                }
        }
        
        fclose(source_filestream);
        fclose(output_filestream);
        return count;
    }
    return -1;
}

/* Open Base64-encoded file named <src_file> for reading, and convert it
 * to regular binary format, which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int from_base64(const char *dst_file, const char *src_file) {
    (void) dst_file;
    (void) src_file;
    return -1;
}
