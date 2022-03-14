#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int cmpstr(char *s1, char *s2){
    int dis = 0;
    int i = 0;
    int c1; 
    int c2;
    while (s1[i]!='\0' && s2[i]!='\0'){
        if (s1[i] < s2[i] || s1[i] > s2[i]) {
            c1 = s1[i];
            c2 = s2[i];
            dis = c1 - c2;
            return dis;
        }   
        i = i + 1;
    }    

    if (s1[i]!='\0' && s2[i]=='\0') {
        c1 = s1[i];
        c2 = s2[i];
        dis = c1 - c2;
        return dis;
    }

    if (s1[i]=='\0' && s2[i]!='\0') {
        c1 = s1[i];
        c2 = s2[i];
        dis = c1 - c2;
        return dis;
    }
    
    return dis;
}