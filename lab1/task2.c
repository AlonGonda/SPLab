#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv) {

   int str[100];
   int i=0;
   int a[10],n,k,j;
   
   //1 - b flag. 2- c flag. 3-i flag. 4- o flag;
   int options[4];
   
   for(int m = 0; m<4; m++){
       options[m] =0;
   }
   for(int t=0; t<argc; t++){
       if (strcmp("-b", argv[t]) == 0){
           options[0] = t;
       }
       if (strcmp("-c", argv[t]) == 0){
           options[1] = t;
       }
       if (strcmp("-i", argv[t]) == 0){
           options[2] = t;
       }
       if (strcmp("-o", argv[t]) == 0){
           options[3] = t;
       }
   }
   
   FILE *input;
   FILE *output;
   
   //checks if input is from keyboard or from file
   if (options[2] == 0){
       input = stdin;
   }
   else{
       input = fopen(argv[options[2]+1], "r");
   }
   
   if (options[3] == 0){
       output = stdout;
   }
   else{
       output = fopen(argv[options[3]+1], "w");
   }
   
   //read input (no matter where it comes from
    int flag = 0;
    while(flag == 0){
        str[i]  = fgetc(input);
        if (str[i] == 10 || str[i] == 0){
            flag = 1;
        }
        else{
            i++;
        }
    }
    
    if (options[0] != 0 || options[1] != 0){
        // print every value
        if (options[0] != 0){
            for(j =0; j<i; j++){
                n=str[j];
                for(k=0; n>0; k++){
                    a[k]=n%2;
                    n=n/2;
                }
            for(k=k-1; k>=0; k--){
                fprintf(output, "%d",a[k]);
            }
            fprintf(output, " ");
            }
        }
        if (options[1] != 0){
            for(j =0; j<i; j++){
                char c;
                if (str[j] >= 97 && str[j] <= 122){
                    c = str[j]-32;
                }
                else if (str[j] >= 65 && str[j] <= 90){
                    c = str[j]+32;  
                }
                else{
                    c = str[j];
                }
                fprintf(output, "%c",c);
            }
        }
    }
    else{
        for(j =0; j<i; j++){
            fprintf(output, "%d ",str[j]);
        }
    }
   // file closing
   if (options[2] == 0){
       fclose(input);
   }
   if (options[3] == 0){
       fclose(output);
   }
   return 0;
}
