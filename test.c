#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <errno.h>
#include <string.h>

char* function(){
    char* hello= "Hello";
    return hello;
}

int main(int argc, char* argv[])
{
    int val = 0;
    char hello[] = {'1','0','0','0','0','0','1'};
    for(int i = 0; i < sizeof(hello); i++){
        int bit;
        switch(hello[i]){
            case '1':
                bit = 1;
                break;
            case '0':
                bit = 0;
                break;
        }
        printf("adding %d to val: %d\n",bit << (6 - i), val);
        val += bit << (6 - i);

    }

    printf("%d\n",sizeof(hello));
    printf("%c\n",(char)val);
    
    
    
    // setlocale(LC_ALL, "en_US.utf8");
    // //printf("%d\n", 0xfeff);
    // char* buff = argv[1];
    // wchar_t wideString[strlen(buff)];
    // memset(wideString,0,sizeof(wideString));
    // mbtowc(NULL, 0, 0); // reset the conversion state
    // const char* end = buff + strlen(buff);
    // int ret;
    // int i = 0;
    // for (wchar_t wc; (ret = mbtowc(&wc, buff, end-buff)) > 0; buff+=ret) {
    //     wideString[i++] = wc; 
    //     wprintf(L"%ld\n",wc);
    //     if(wc == 0xfeff){
    //         wprintf(L"HERE");
    //     }
    // }
    // wprintf(L"-----------------------\n");
    // wprintf(L"%ls : length: %d \n", wideString, wcslen(wideString));
    // wprintf(L"-----------------------\n");

    // wchar_t wideKey[wcslen(wideString)];
    // i = 0;
    // int flag = 0;
    // wprintf(L"%d", i);
    // for(; i < wcslen(wideString); i++){
    //     wideKey[i] = wideString[i];
    //     wprintf(L"%ld => %ld\n", wideKey[i], wideString[i]);
    //     if(wideKey[i]==0xfeff){
    //         flag=1;
    //         break;
    //     }
    // }
    // if(!flag){wprintf(L"Invalid Key");exit(EXIT_FAILURE);}


    // // wchar_t wc;
    // // mbtowc(&wc, buff,end-buff);
    // // wideString[i++] = wc; 

    // //printf("\n");
    // //wideString[i] = 'WEOF';
    // //wprintf(wideKey);
    // return 0;






}