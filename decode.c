
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#include "pad.h"
#include "decode.h"


void strip_decoy(wchar_t* wide_message, wchar_t* buffer){
    wchar_t wideKey[wcslen(wide_message)];
    int isKeyTerminated = 0;
    for(int i = 0; i < wcslen(wide_message); i++){
        if(wide_message[i] == ONE || wide_message[i] == ZERO || wide_message[i] == WORD || wide_message[i] == END){
            buffer[i] = wide_message[i];
            wcsncat(buffer, &wide_message[i],1);
            // wprintf(L"adding char %x\n", buffer[i]);
        }
        //wprintf(L"%ld => %ld\n", buffer[i], wide_message[i]);
        if(wide_message[i]==0xfeff){
            isKeyTerminated=1;
            break;
        }
    }
    if(!isKeyTerminated){wprintf(L"Invalid Key");exit(EXIT_FAILURE);}
    //wprintf(L"stripped message %s => %ld\n", buffer[i], wide_message[i]);

    return;
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
        if(bits[i] == 1){
            val += 1 << (wordSize-1 - i);
        }
    }
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
                strncat(plainText, &insert, 1);
                memset(buff, 0, 32*sizeof(int));
                wordSize = 0;
                j=0;
                break;
            case END:
                return;
        }
    }
}
char* decode(char* message){

    wchar_t* wide_message = malloc(strlen(message)*sizeof(wchar_t));
    convertWide(message, wide_message);
    wchar_t* stripped_message = malloc(strlen(message)*sizeof(wchar_t));
    strip_decoy(wide_message,stripped_message);
  

    // the plain text will be far to big, but we know no matter the encoding it will fit.
    char* plainText = malloc(wcslen(stripped_message));
    deserialize(stripped_message, plainText);
    
    //printf("Message in decode: %s", message);
    free(wide_message);
    free(stripped_message);

    return plainText;
}