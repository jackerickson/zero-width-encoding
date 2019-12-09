
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

//TODO: rewrite encoding so it uses wchars
//TODO: mix encoding into the decoy better
char* encode(char* secret, char* decoy){
    unsigned char character;
    //each char of the secret needs 7 unicode points per char + 1 word bytes, and each unicode point is 3 bytes, then add terminator
    char* cyphertext_buffer = malloc(26*strlen(secret)+strlen(decoy));
    char* ct_index;
    int i = 0;
    int decoy_i = 1;
    cyphertext_buffer[0] = '\0';
    strncat(cyphertext_buffer, &decoy[0],1);

    ct_index = cyphertext_buffer + 1;

    //possibly in this while, we put the call to char_to_bits, which converts the char into a char array of bits,
    //seperate each word_unicode with a zero_unicode width char, and put it all in cyphertext_buffer moving the ct_index pointer along as we insert chars.
    //need functions to convert char to binary and vica versa. Could use the logive from below with bitwise operations. 
    

    while( secret[i] != '\0'){
        //now we have the character
        character = (unsigned char) secret[i];
        ct_index = char_to_bin(secret[i], ct_index);
        //index++;
        strcat(ct_index, WORD_unicode);
        ct_index = ct_index + 6;
        i++;

        if(i%3 == 0 && decoy_i < strlen(decoy)-1){
            strncat(ct_index, &decoy[decoy_i++],1);
        }
        
    }

    strcat(ct_index, END_unicode);
   
    
    return strcat(cyphertext_buffer, (decoy + decoy_i));


    // unsigned char character;
    // //each char of the secret needs 7 unicode points per char + 1 word bytes, and each unicode point is 3 bytes, then add terminator
    // char* cyphertext_buffer = malloc(26*strlen(secret)+strlen(decoy));
    // char* ct_index;
    // int i = 0;

    // cyphertext_buffer[0] = '\0';
    // strncat(cyphertext_buffer, &decoy[0],1);

    // ct_index = cyphertext_buffer + 1;
    // //possibly in this while, we put the call to char_to_bits, which converts the char into a char array of bits,
    // //seperate each word_unicode with a zero_unicode width char, and put it all in cyphertext_buffer moving the ct_index pointer along as we insert chars.
    // //need functions to convert char to binary and vica versa. Could use the logive from below with bitwise operations. 
    

    // while( secret[i] != '\0'){
    //     //now we have the character
    //     character = (unsigned char) secret[i];
    //     ct_index = char_to_bin(secret[i], ct_index);
    //     //index++;
    //     strcat(ct_index, WORD_unicode
    //     );
    //     ct_index = ct_index + 6;
    //     i++;
        
    // }

    // strcat(ct_index, END_unicode);
   
    // //printf("\n %s \n \n", cyphertext_buffer);
    // return strcat(cyphertext_buffer, (decoy + 1));

}