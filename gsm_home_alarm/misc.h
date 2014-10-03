#ifndef _MISC_H_
#define _MISC_H_

unsigned char swap_nibble(unsigned char c);
void hex_to_ascii(unsigned char c, unsigned char buffer[], unsigned char pos);
//void hex_to string(unsigned char inputBuffer[],unsigned char length,  unsigned char outputBuffer[]);
void ascii_to_decsemioct(unsigned char inputBuffer[],unsigned char length, unsigned char *outputBuffer);
void decsemioct_to_ascii(unsigned char inputBuffer[],unsigned char length, unsigned char *outputBuffer);
unsigned int septet_encoding(unsigned char inputBuffer[],unsigned int length, unsigned char *outputBuffer);
unsigned int septet_decoding(unsigned char inputBuffer[],unsigned int length, unsigned char *outputBuffer);

#endif
