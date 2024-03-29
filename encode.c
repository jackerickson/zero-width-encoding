
#include <string.h>
#include <stdlib.h>

#include "encode.h"
#include "pad.h"

char* char_to_bin(unsigned char character, char* buffer){

    //printf("%c: %d >> ", character, (unsigned int)character);

    for(int j = 0; j < 7;j++){
        
        //BIG END_unicodeIAN IN the Encoding
        strcat(buffer,((unsigned int)character & (64>>j) ?/* 1*/ ONE_unicode :/* 0*/ ZERO_unicode
));
    }
    
    return buffer + 6;
}

//TODO: mix encoding into the decoy better
char* encode(char* secret, char* decoy){
    unsigned char character;
    //each char of the secret needs 7 unicode points per char + 1 word bytes, and each unicode point is 3 bytes, then add terminator
    char* cyphertext_buffer = malloc(26*strlen(secret)+strlen(decoy));
    char* ct_index;
    int i = 0;
    int decoy_i = 1;
    cyphertext_buffer[0] = '\0';

    //copy the first letter of the decoy so our zero width chars are contained within the decoy string 
    strncat(cyphertext_buffer, &decoy[0],1);

    ct_index = cyphertext_buffer + 1;
    
    //iterate through the secret encoding each character into our zero width characters
    while( secret[i] != '\0'){
        character = (unsigned char) secret[i];
        ct_index = char_to_bin(secret[i], ct_index);
        //append the encoded word 
        strcat(ct_index, WORD_unicode);
        ct_index = ct_index + 6;
        i++;
        //every 3 secret characters put a character of the decoy to spread the secret a little bit
        if(i%3 == 0 && decoy_i < strlen(decoy)-1){
            strncat(ct_index, &decoy[decoy_i++],1);
        }
    }

    strcat(ct_index, END_unicode);
   
    return strcat(cyphertext_buffer, (decoy + decoy_i));
}