#ifndef _PAD_H
#define _PAD_H

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

#endif