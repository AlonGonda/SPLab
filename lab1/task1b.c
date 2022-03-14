#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {

   int str[100];
   // set every value in array to be ""
   int i=0;
   int a[10],n,k,j;
   
   // get data from keyboard
   int flag = 0;
   while(flag == 0){
       str[i]  = fgetc(stdin);
       if (str[i] == 10 || str[i] == 0){
           flag = 1;
       }
       else{
          i++; 
       }
   }
   
   if (argc == 1){
       // print every value
       for(j =0; j<i; j++){
           printf("%d ",str[j]);
       }
       
   }
   
   else if (argc == 2){
       if (strcmp("-b", argv[1]) == 0){
           // print every value
           for(j =0; j<i; j++){
               n=str[j];
               for(k=0; n>0; k++){
                   a[k]=n%2;
                   n=n/2;
               }
               for(k=k-1; k>=0; k--){
                   printf("%d",a[k]);
               }
               printf(" ");
           }
       }
   }
   return 0;
}
