#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "main.h"
#include "encode.h"
#include "decode.h"


int main(int argc, char* argv[]){	
  
    setlocale(LC_ALL, "en_US.UTF-8");

    if(argc == 2){
        wprintf(L"Secret: %s \n", decode(argv[1]));
    } else if (argc == 3){
        wprintf(L"Encoded: %s \n", encode(argv[1],argv[2]));
    } else{
        
         wprintf(L"Usage: \n\
                     Encoding: ./zwe <message> <decoy> \n\
                     Decoding: ./zwe <ciphertext>\n");

    }
}
