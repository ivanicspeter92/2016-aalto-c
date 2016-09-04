#include "machdr.h"

/* a) Implement all get_* functions. <header> points to the start of the
 * MAC header. The functions return the value of the respective field.
 * For flags, any non-zero return value indicates that flag is set, and zero
 * means it is not set.
 */

const unsigned int frame_length = 36;

int is_bit_set(unsigned char value, unsigned int bit_number) {
    switch(bit_number) {
        case 1: return ((value & 0x80));
        case 2: return ((value & 0x40));
        case 3: return ((value & 0x20));
        case 4: return ((value & 0x10));
        case 5: return ((value & 0x08));
        case 6: return ((value & 0x04));
        case 7: return ((value & 0x02));
        case 8: return ((value & 0x01));
        default: return 0;
    }
}

int get_proto_version(const unsigned char *header) {
    int result = header[0] >> 6;
    
    return result;
}

int get_type(const unsigned char *header) {
    int result = (header[0] & 0x30) >> 4;
    
    return result;
}

int get_subtype(const unsigned char *header) {
    int result = header[0] & 0x0F;
    
    return result;
}

int get_to_ds(const unsigned char *header) {
    return is_bit_set(header[1], 1);
}

int get_from_ds(const unsigned char *header) {
    return is_bit_set(header[1], 2);
}

int get_retry(const unsigned char *header) {
    return is_bit_set(header[1], 4);
}

int get_more_data(const unsigned char *header) {
    return is_bit_set(header[1], 6);
}

/* b) Implement all set_* functions that set the values of respective
 * fields in the MAC header. <header> points to the start of the header,
 * and the second parameter indicates the value to be set.
 */

void set_proto_version(unsigned char *header, int version) {
    header[0] = header[0] | (version << 6);
}

void set_type(unsigned char *header, int type) {
    header[0] = header[0] | (type << 4);
}

void set_subtype(unsigned char *header, int subtype) {
    header[0] = header[0] | subtype;
}

void set_to_ds(unsigned char *header, int flag) {
    header[1] = header[1] | (flag << 7);
}

void set_from_ds(unsigned char *header, int flag) {
    header[1] = header[1] | (flag << 6);
}

void set_retry(unsigned char *header, int flag) { 
    header[1] = header[1] | (flag << 4);
}

void set_more_data(unsigned char *header, int flag) {
    header[1] = header[1] | (flag << 2);
}
