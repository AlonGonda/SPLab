#include <stdio.h>

extern int funcA(char * string);

int main(int argc, char **argv) {
    
    if (argc != 2){
        printf("Enter one string.\n");
        return -1;
    }
    int len;
    char * string  = argv[1];
    len = funcA(string);
    printf("%d\n", len); 
    return 0;
}