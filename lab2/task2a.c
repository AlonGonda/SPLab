#include <stdio.h>
#include <string.h>

void echo_printer(char c) {
    printf("%c", c);
}


void ascii_printer(char c) {
    printf("%d", c);
}


void binary_printer(char c) {
    int bits [8] = {0,0,0,0,0,0,0,0};
    int i;
    for (i = 0 ; c>0 ; i=i+1) {
        bits[i] = c%2;
        c= c>>1;
    }
    while (i<8) {
        bits[i] = 0; 
        i=i+1;
    }
    for (i = 7; i>=0 ; i=i-1) {
        printf("%d" , bits[i]);
    }
    printf(" ");
}


void lower_to_upper_printer(char c) {
    if (c>='a' && c<='z') 
        printf("%c" ,  c-32);
}


int main(int argc, char **argv) {
    char a;
    a = fgetc(stdin);
    echo_printer(a);
    printf("\n");
    ascii_printer(a);
    printf("\n");
    binary_printer(a);
    printf("\n");
    lower_to_upper_printer(a);
    printf("\n");
    return 1;
}
