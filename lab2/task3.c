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



void string_printer(char *str, void (*f)(char)) {
    int i;
    for (i = 0 ; i<strlen(str) ; i=i+1) {
        if (str[i]!='\n'){
            f(str[i]);
            printf(" ");
        }
    }
    printf("\n");
}


void string_reader(char *s) {
    fgets(s, 11, stdin);
}


void bitwise_or(char *s) {
    int i;
    int num = 0;
    for (i = 0 ; i < strlen(s) ; i=i+1) {
        if (s[i]!='\n') 
            num = num | s[i];
    }
    binary_printer(num);
    printf("\n");
}


struct fun_desc {
    char * name;
    void (*fun)(char);
};


int main(int argc, char **argv) {
    struct fun_desc menu[] = {{"echo printer", echo_printer}, {"ASCII printer", ascii_printer}, {"binary printer", binary_printer}, {"lower to upper", lower_to_upper_printer}};
    char inputArray[11];
    int i;
    int num;
    int valid; 
    printf("Please enter a string (0<size<=10):\n");
    string_reader(inputArray);
            
    while (1) {
        valid = 1;
        while (valid) {
            printf("Please choose printer type:\n");
            for(i=0 ; i<4 ; i=i+1) 
                printf("%d) %s\n" , i , menu[i].name);
            printf("4) bitwise or\n");
            
            if (scanf("%d",&num)==EOF) {
                printf ("DONE.\n");
                return 0;
            }
            
            if ((num < 0) || (num > 4)) 
                printf("please select 1-4 or CTRL-D to exit.\n");
            
            else {
                valid = 0;
                printf("option: %d\n",num);
                if (num == 4) 
                    bitwise_or(inputArray);
                else 
                    string_printer(inputArray , menu[num].fun);
            }
        }
    }
    return 0;
}
