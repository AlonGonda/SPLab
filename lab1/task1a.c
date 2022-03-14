#include <stdio.h>
#include <string.h>
int main( ) {

   int str[100];
   // set every value in array to be ""
   int i=0;
   
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
   
   // print every value
   for(int j =0; j<i; j++){
       printf("%d ",str[j]);
   }
   return 0;
}
