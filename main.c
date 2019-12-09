#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include "main.h"
#include "encode.h"
#include "decode.h"


int main(int argc, char* argv[]){	
  
    setlocale(LC_ALL, "en_US.UTF-8");

    if(argc == 2){
        wprintf(L"Message: %s \n", decode(argv[1]));
    } else if (argc == 3){
        wprintf(L"Encoding: %s \n", encode(argv[1],argv[2]));
    } else{
        char* decoded;
        char* encoded;
        encoded = encode("A", "decoy");
        decoded = decode(encoded);
        wprintf(L"This is the encoded message : %s \n\n", encoded);

        wprintf(L"This is the decoded message: %s\n", decoded);
    //     wprintf(L"Usage: \n\
    //                 Encoding: ./zwe <message> <decoy> \n\
    //                 Decoding: ./zwe <ciphertext>\n");

    }
}
