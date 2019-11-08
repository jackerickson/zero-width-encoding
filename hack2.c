#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

#if DEBUG 
    #define ZERO  "ZERO  "
    #define ONE   "ONE   "
    #define WORD  "WORD  "
    #define END   "END   "
#else
    #define ZERO  "\u200B"
    #define ONE   "\u200C"
    #define WORD  "\u200D"
    #define END   "\uFEFF"
#endif

char* char_to_bin(unsigned char character, char* buffer){

    printf("%c: %d >> ", character, (unsigned int)character);

    for(int j = 0; j < 7;j++){
        
        //BIG ENDIAN IN the Encoding
        strcat(buffer,((unsigned int)character & (64>>j) ?/* 1*/ ONE :/* 0*/ ZERO));
        printf("%c", ((unsigned int)character & (64>>j) ?/* 1*/ '1' :/* 0*/ '0'));       
    }
    
    //printf("\n%s ", binary);    
    return buffer + 6;
}

char* encode(char* secret, char* decoy){
    
    unsigned char character;

    char* cyphertext_buffer = malloc(16384+sizeof(decoy));
    char* ct_index = cyphertext_buffer;
   
    int i = 0;

    //possibly in this while, we put the call to char_to_bits, which converts the char into a char array of bits,
    //seperate each word with a zero width char, and put it all in cyphertext_buffer moving the ct_index pointer along as we insert chars.
    //need functions to convert char to binary and vica versa. Could use the logive from below with bitwise operations. 
    while( secret[i] != '\0'){
        //now we have the character
        character = (unsigned char) secret[i];
        ct_index = char_to_bin(character, ct_index);
        //index++;
        strcat(ct_index, WORD);
        ct_index = ct_index + 6;
        i++;
    }

    strcat(ct_index, END);
   
    //printf("\n %s \n \n", cyphertext_buffer);
    return strcat(cyphertext_buffer, decoy);

}



char* decode(char* message){
    int i = 0;
    while(message[i] != '\0'){
        printf("Character %d => %d\n", i, message[i],message[i]);
        i++;
    }
    return message;
}


int main(int argc, char* argv[]){	

    printf("H\u200BE\u200CL\u200DL\uFEFFO\n");
    printf("%d \t %d\t%d\n", sizeof("\u200B"), sizeof(ZERO),sizeof("text string"));
    
    printf("\n%s \n \n", encode("A", "decoy"));
    printf("\n%s \n \n", decode(encode(argv[1], "decoy")));

    
    //printf("%s\n",encode("A"));

}
