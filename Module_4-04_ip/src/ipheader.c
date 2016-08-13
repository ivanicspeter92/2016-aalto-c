#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include "ipheader.h"

void parse_character_array_to_ip(struct ipHeader *ip, const unsigned char *buffer) {
    ip->version = buffer[0] >> 4;
    ip->ihl = (buffer[0] & 0x0f) * 4; // multiplied by 4 in order to convert value to bytes
    ip->dscp = (buffer[1] >> 2);
    ip->ecn = (buffer[1] & 0x03);
    ip->length = (buffer[2] >> 4) * 16 * 16 * 16 + ((buffer[2] & 0x0f) * 16 * 16) + buffer[3];
    
    ip->identification = (buffer[4] >> 4) * 16 * 16 * 16 + ((buffer[4] & 0x0f) * 16 * 16) + buffer[5];
    ip->flags = ((buffer[6] & 0xE0) >> 5);
    ip->fragment_offset = (buffer[6] & 0x1f) * 16 * 16 + buffer[7];
    ip->time_to_live = buffer[8];
    ip->protocol = buffer[9];
    ip->header_checksum = (buffer[10] >> 4) * 16 * 16 * 16 + ((buffer[10] & 0x0f) * 16 * 16) + buffer[11];
    
    ip->source_ip[0] = buffer[12];
    ip->source_ip[1] = buffer[13];
    ip->source_ip[2] = buffer[14];
    ip->source_ip[3] = buffer[15];
    
    ip->destination_ip[0] = buffer[16];
    ip->destination_ip[1] = buffer[17];
    ip->destination_ip[2] = buffer[18];
    ip->destination_ip[3] = buffer[19];
}

/* Parses the given buffer into an IP header structure.
 * 
 * Parameters:
 * ip: pointer to the IP header structure that will be filled based
 *      on the data in the buffer
 * buffer: buffer of 20 bytes that contain the IP header. */
void parseIp(struct ipHeader *ip, const void *buffer) {
    unsigned char* char_buffer = buffer;
    if (char_buffer != NULL) {
        parse_character_array_to_ip(ip, char_buffer);
    }
}

void send_ip_to_character_buffer(char *buffer, const struct ipHeader *ip) {
    char version = ip->version << 4;
    char ihl = (ip->ihl / 4);
    buffer[0] = version ^ ihl;
    
    buffer[1] = ((char)ip->dscp << 2) ^ ((char)ip->ecn & 0x03);
    buffer[2] = (ip->length >> 8) & 0xff;
    buffer[3] = ip->length;
    buffer[4] = (ip->identification >> 8) & 0xff;
    buffer[5] = ip->identification;
    
    buffer[6] = (ip->flags << 5) ^ ((ip->fragment_offset >> 8) & 0xff);
    buffer[7] = ip->fragment_offset;
    
    buffer[8] = ip->time_to_live;
    buffer[9] = ip->protocol;
    
    buffer[10] = (ip->header_checksum >> 8) & 0xff;
    buffer[11] = ip->header_checksum;
    
    buffer[12] = ip->source_ip[0];
    buffer[13] = ip->source_ip[1];
    buffer[14] = ip->source_ip[2];
    buffer[15] = ip->source_ip[3];
    
    buffer[16] = ip->destination_ip[0];
    buffer[17] = ip->destination_ip[1];
    buffer[18] = ip->destination_ip[2];
    buffer[19] = ip->destination_ip[3];
}

/* Builds a 20-byte byte stream based on the given IP header structure
 * 
 * Parameters:
 * buffer: pointer to the 20-byte buffer to which the header is constructed
 * ip: IP header structure that will be packed to the buffer */
void sendIp(void *buffer, const struct ipHeader *ip) {
    unsigned char* char_buffer = buffer;
    if (char_buffer != NULL) {
        send_ip_to_character_buffer(char_buffer, ip);
    }
}


/* Prints the given IP header structure */
void printIp(const struct ipHeader *ip) {
    /* Note: ntohs below is for converting numbers from network byte order
     to host byte order. You can ignore them for now
     To be discussed further in Network Programming course... */
    printf("version: %d   ihl: %d   dscp: %d   ecn: %d\n",
            ip->version, ip->ihl, ip->dscp, ip->ecn);
    printf("length: %d   id: %d   flags: %d   offset: %d\n",
            ntohs(ip->length), ntohs(ip->identification), ip->flags, ip->fragment_offset);
    printf("time to live: %d   protocol: %d   checksum: 0x%04x\n",
            ip->time_to_live, ip->protocol, ntohs(ip->header_checksum));
    printf("source ip: %d.%d.%d.%d\n", ip->source_ip[0], ip->source_ip[1],
            ip->source_ip[2], ip->source_ip[3]);
    printf("destination ip: %d.%d.%d.%d\n", ip->destination_ip[0],
            ip->destination_ip[1],
            ip->destination_ip[2], ip->destination_ip[3]);    
}

/* Shows hexdump of given data buffer */
void hexdump(const void *buffer, unsigned int length) {
    const unsigned char *cbuf = buffer;
    unsigned int i;
    for (i = 0; i < length; ) {
        printf("%02x ", cbuf[i]);
        i++;
        if (!(i % 4))
            printf("\n");
    }
}
