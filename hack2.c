#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>

#define DEBUG 0

#if DEBUG 
    #define ZERO_unicode  "ZERO_unicode  "
    #define ONE_unicode   "ONE_unicode   "
    #define WORD_unicode  "WORD_unicode  "
    #define END_unicode   "END_unicode   "
#else
    #define ONE_unicode  "\u200B"
    #define ZERO_unicode "\u200C"
    #define WORD_unicode "\u200D"
    #define END_unicode  "\uFEFF"
#endif

#define ONE 0x200b
#define ZERO 0x200c
#define WORD 0x200D
#define END 0xfeff

char* char_to_bin(unsigned char character, char* buffer){

    //printf("%c: %d >> ", character, (unsigned int)character);

    for(int j = 0; j < 7;j++){
        
        //BIG END_unicodeIAN IN the Encoding
        strcat(buffer,((unsigned int)character & (64>>j) ?/* 1*/ ONE_unicode :/* 0*/ ZERO_unicode
));
        //printf("%c", ((unsigned int)character & (64>>j) ?/* 1*/ '1' :/* 0*/ '0'));       
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
    //seperate each word_unicode with a zero_unicode width char, and put it all in cyphertext_buffer moving the ct_index pointer along as we insert chars.
    //need functions to convert char to binary and vica versa. Could use the logive from below with bitwise operations. 
    while( secret[i] != '\0'){
        //now we have the character
        character = (unsigned char) secret[i];
        ct_index = char_to_bin(character, ct_index);
        //index++;
        strcat(ct_index, WORD_unicode
);
        ct_index = ct_index + 6;
        i++;
    }

    strcat(ct_index, END_unicode);
   
    //printf("\n %s \n \n", cyphertext_buffer);
    return strcat(cyphertext_buffer, decoy);

}



char* strip_decoy(wchar_t* wide_message, wchar_t* buffer){
    wchar_t wideKey[wcslen(wide_message)];
    int isKeyTerminated = 0;
    for(int i = 0; i < wcslen(wide_message); i++){
        buffer[i] = wide_message[i];
        //wprintf(L"%ld => %ld\n", buffer[i], wide_message[i]);
        if(buffer[i]==0xfeff){
            isKeyTerminated=1;
            break;
        }
    }
    if(!isKeyTerminated){wprintf(L"Invalid Key");exit(EXIT_FAILURE);}
    
}

void convertWide(char* bytes, wchar_t* buffer){
    mbtowc(NULL, 0, 0); // reset the conversion state
    const char* end_unicode = bytes + strlen(bytes);
    int ret;
    int i = 0;
    for (wchar_t wc; (ret = mbtowc(&wc, bytes, end_unicode-bytes)) > 0; bytes+=ret) {
        buffer[i++] = wc; 
    }
    return;
}

//by having wordsize we make it easier to port the code to bigger data encoding sizes.
char bitsToChar(int bits[], int wordSize){
    int val = 0;
    for(int i = 0; i < wordSize; i++){
        int bit;
        wprintf(L"%d",bits[i]);
        if(bits[i] == 1){
            val += 1 << (wordSize-1 - i);
        }
        //printf("adding %d to val: %d\n",bit << (6 - i), val);
    }
    wprintf(L"==> %c\n",val);

    return (char)val;
}


/*we gonna:
-iterate through the encoding
since encoding is highest bit first and for functionality do not assume value size...
must store, then iterate through the buffer 

*/
void deserialize(wchar_t* stripped_message, char* plainText){
    int buff[32];
    plainText[0] = '\0';
    int wordSize = 0;
    char insert;
    int j  = 0;
    //iterate through the key
    for(int i = 0; i < wcslen(stripped_message); i++){
        switch(stripped_message[i]){
            case ZERO:
                buff[j++] = 0;
                wordSize++;
                break;
            case ONE:
                buff[j++] = 1;
                wordSize++;
                break;
            case WORD:
                insert = bitsToChar(buff, wordSize);
                strcat(plainText, &insert);
                wprintf(L"Found an encoded character! : %c\n",insert);
                memset(buff, 0, 32*sizeof(int));
                wordSize = 0;
                j=0;
                break;
            case END:
                wprintf(L"reached break line at character %d \n", i);
                return;
        }
    }
}
char* decode(char* message){

    wchar_t* wide_message = malloc(strlen(message)*sizeof(wchar_t));
    convertWide(message, wide_message);
    wchar_t* stripped_message = malloc(strlen(message)*sizeof(wchar_t));
    wprintf(L"The wide char: %ls \n", wide_message);
    strip_decoy(wide_message,stripped_message);
    // the plain text will be far to big, but we know no matter the encoding it will fit.
    char* plainText = malloc(wcslen(stripped_message));
    deserialize(stripped_message, plainText);
    
    //printf("Message in decode: %s", message);
    free(wide_message);
    free(stripped_message);

    return plainText;
}
int main(int argc, char* argv[]){	
    //printf("H\u200BE\u200CL\u200DL\uFEFFO\n");
    //printf("%d \t %d\t%d\n", sizeof("\u200B"), sizeof(ZERO_unicode),sizeof("text string"));
    
    //printf("%s\n", encode("A", "decoy"));
    //printf("\n%s \n \n", decode(encode(argv[1], "decoy")));
    setlocale(LC_ALL, "en_US.UTF-8");
    char* decoded;
    char* encoded;
    encoded = encode("THIS IS ENCODED", "decoy");
    decoded = decode(encoded);
    wprintf(L"This is the decoded message : %s \n\n", encoded);

    wprintf(L"This is the decoded message: %s\n", decoded);

}
