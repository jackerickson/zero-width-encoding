#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <errno.h>
#include <string.h>


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "en_US.utf8");

    char* buff = argv[1];
    wchar_t wideString[strlen(buff)];
    memset(wideString,0,sizeof(wideString));
    mbtowc(NULL, 0, 0); // reset the conversion state
    const char* end = buff + strlen(buff);
    int ret;
    int i = 0;
    for (wchar_t wc; (ret = mbtowc(&wc, buff, end-buff)) > 0; buff+=ret) {
        wideString[i++] = wc; 
        wprintf(L"%lc",wc);
    }

    // wchar_t wc;
    // mbtowc(&wc, buff,end-buff);
    // wideString[i++] = wc; 

    //printf("\n");
    //wideString[i] = 'WEOF';
    wprintf(wideString);
    return 0;

    
}