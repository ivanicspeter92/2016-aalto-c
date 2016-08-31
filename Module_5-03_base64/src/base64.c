#include "base64.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

char get_base64_character_from_buffer(int index, char buffer[4]) {
    int base64_index; 
    switch(index) {
        case 0:
            base64_index = (buffer[0] & 0xFC) >> 2;
            break;
        case 1:
            base64_index = (buffer[0] & 0x03) << 4;
            base64_index = base64_index | ((buffer[1] & 0xF0) >> 4); 
            break;
        case 2:
            base64_index = ((buffer[1] & 0x0F) << 2);
            base64_index = base64_index | (buffer[2] >> 6); 
            break;
        case 3:
            base64_index = (buffer[2] & 0x3F); 
            break;
        default: return -1;
    }
    char result = encoding[base64_index]; 
    return result;
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
    int count = 0, output_count = 0;
    
    if (source_filestream != NULL && output_filestream != NULL) {
        char buffer[4];
        char next_character;
        while (fgets(buffer, sizeof(buffer), source_filestream) != NULL) {
            count += 3;
            
            next_character = get_base64_character_from_buffer(0, buffer);
            fputc(next_character, output_filestream);
            output_count++;
             
            next_character = get_base64_character_from_buffer(1, buffer);
            fputc(next_character, output_filestream);
            output_count++;
            
            if(!feof(source_filestream)) {  
                next_character = get_base64_character_from_buffer(2, buffer);
                fputc(next_character, output_filestream);
                output_count++;
                 
                next_character = get_base64_character_from_buffer(3, buffer);
                fputc(next_character, output_filestream);
                output_count++;
            } 
            
            
            if(output_count % 64 == 0) {
                putc('\n', output_filestream);
            }
        }
        
        if(isprint(buffer[1]) == 0 && strlen(buffer) > 1) {  
            count -= 2;
            fputc('=', output_filestream);
            fputc('=', output_filestream);
            output_count++;
            output_count++;

        } else if((isprint(buffer[2]) == 0)) { 
            fputc(get_base64_character_from_buffer(2, buffer), output_filestream);
            count -= 1;
            fputc('=', output_filestream);
            output_count++;
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
