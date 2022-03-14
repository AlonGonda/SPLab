#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int cmpstr(char *s1, char *s2){
    while (*s1 && *s2)
    {
        
        if (*s1 != *s2) {  // if the characters different, or the end of one of strings is reached
            break;
        }
 
        // move to the next pair of characters
        s1++;
        s2++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}