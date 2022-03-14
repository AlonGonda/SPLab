#include <stdlib.h>
#include <stdio.h>
#include "LineParser.h"
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>

void execute(cmdLine *pCmdLine){
    execvp(pCmdLine->arguments[0], pCmdLine->arguments); 
    perror("Execution Failed"); // if the execvp function has failed the process image won't change and we will get to print the error
}

int main(int argc, char **argv) {

     char cwdBuffer[PATH_MAX]; 
     char userInput[2048]; 

    while (1) {
    
        // get the current directory using the getcwd function and print it to the user
        getcwd(cwdBuffer,PATH_MAX); 
        printf("%s\n",cwdBuffer);
        
        // get the input line from the user  
        fgets(userInput,2048,stdin);

        // check the input and act respectively  
        if(strcmp(userInput,"quit\n") == 0)  
            exit(0); // if the input line was "quit" - end the prosses and clean all data using the exit function

        cmdLine* parsedInput;     
        parsedInput = parseCmdLines(userInput); // parse the user input line into a cmdLine structure 

        //execute the user input 
        execute(parsedInput); 

        // release the cmdLine resources   
        freeCmdLines(parsedInput);    
    }
  
    return 0;
}