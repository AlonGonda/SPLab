#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "LineParser.h"
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define maxHistorySize 10

void execute(cmdLine *pCmdLine, int *pipefd){
    int status;
    pid_t cpid = fork();

    /* Fork failed, terminate everything */
    if (cpid == -1){
        close(pipefd[0]);
        close(pipefd[1]);
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }

    /* if the fork operation worked - this is the child process who execute the givven operation. If it failed,there will be an exit operation */
    if (cpid == 0){
        
        if ((pCmdLine->next != NULL) & (pCmdLine->idx == 0)){
            close(STDOUT_FILENO);
            dup(pipefd[1]);
            close(pipefd[1]);
        }
        else if ((pCmdLine->next == NULL) & (pCmdLine->idx == 1)){
            close(STDIN_FILENO);
            dup(pipefd[0]);
            close(pipefd[0]);
        }

        /* if input redirection is needed */
        if (pCmdLine->inputRedirect != NULL) { 
            close(STDIN_FILENO); //close the stdin stream
            int openfd = open(pCmdLine->inputRedirect,0); //open the givven file for reading only 
            if (openfd == -1) { //if the open function has failed - print error and exit 
                perror("opening the input file has filed");
                _exit(EXIT_FAILURE);
            }
        }

        /* if output redirection is needed */
        if (pCmdLine->outputRedirect != NULL) {
            close(STDOUT_FILENO); //close the stdout stream
            int openfd = open(pCmdLine->outputRedirect, O_CREAT|O_RDWR , S_IRUSR|S_IWUSR); //Creates file if doesnt exist 
            if (openfd == -1) { //if the open function has failed - print error and exit 
                perror("opening the output file has filed");
                _exit(EXIT_FAILURE);
            }
        }
        
        int result = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        if (result == -1){
            close(0);
            close(1);
            _exit((long)getpid);
        }
    }
    /* This is the Father code who waits for the child to finish. If the child process succeed, do nothing. If failed, print error message */
    else{
        if (pCmdLine->idx == 0){
            close(pipefd[1]);
        }
        if (pCmdLine->blocking == 1){
            waitpid(cpid, &status, 0);
            if (!WIFEXITED(status)){
                printf("Execvp Failed by Child");
            }  
        }
    }
    
}

/* free all history before the program terminates */
void freeHistory (char ** historyBuff, int historySize) {
    if (historySize >= maxHistorySize) { //if the histiry is full - free everything
        for (int i = 0 ; i < maxHistorySize ; i++){
            free(historyBuff[i]);
        }
    }
    else {
        for (int i = 0 ; i < historySize ; i++){ //if the history is not full - free just the allocates spaces
            free(historyBuff[i]);
        }
    }
}

int main(int argc, char **argv) {
    char cwdBuff[PATH_MAX];
    char *historyBuff[maxHistorySize];
    char num[10];
    int operation;
    int historySize;
    historySize = 0;
    char input[2048];
    int dirstatus;
    int error = 0;
    int pipefd[2]; //file descriptor array for the pipe function

    while(1){
        //in case the pipe has faild - print error and exit 
        if (pipe(pipefd) == -1) { 
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }

        getcwd(cwdBuff, PATH_MAX); //get the current path 
        printf("%s\n",cwdBuff); //prints the path 

        fgets(input, 2048, stdin); //get an input from the user

        if (strcmp(input, "quit\n") == 0){ //the input is quit - end the program 
            freeHistory(historyBuff,historySize); //free the history array 
            exit(0);
        }


        if (input[0] == '!'){ //the input is a operation from the history 
            for(int i=1; i<strlen(input); i++){ //get the operation number 
                num[i-1] = input[i];
            }
            operation = atoi(num);
            if (operation < 0 || operation >= historySize || operation >= maxHistorySize){ //check if the operation number is valid 
                printf("Non existing log index is invoked\n"); //if it is not - print error
                error = 1; //a flag to know not to do anything in the rest of the loop 
            }
            else{ // the number is valid 
                if (historySize<maxHistorySize){ //if the history array is not full 
                    strcpy(input, historyBuff[operation]); //get the operation from the same number in history 
                }
                else if (operation < maxHistorySize - (historySize%maxHistorySize)) { //if the history is full get the relevent operation 
                    strcpy(input, historyBuff[operation + (historySize%maxHistorySize)]);
                }
                else {
                    strcpy(input, historyBuff[(operation + (historySize%maxHistorySize))%maxHistorySize]);
                }

            }
        }

        cmdLine *pCmdLine; 
        pCmdLine = parseCmdLines(input); //parsing the input to a pCmdLine object 

        if (error == 0){ //there is no error in the givven input 
            if (historySize < maxHistorySize){ //if the history is not full
                historyBuff[historySize] = malloc(2048); //allocate new space in the history 
                strcpy(historyBuff[historySize], input); //add the current input to the history 
                historySize++;
            }
            else { //the history is full
                free(historyBuff[historySize%maxHistorySize]); //free the oldest operation in the history array
                historyBuff[historySize%maxHistorySize] = malloc(2048); //allocate a new space 
                strcpy(historyBuff[historySize%maxHistorySize], input); //add the new operation 
                historySize++;
            }
            if (strcmp(pCmdLine->arguments[0], "cd") == 0){ //the command is cd 
                dirstatus = chdir(pCmdLine->arguments[1]);
                if (dirstatus == -1){
                    fprintf(stderr, "cd Failed\n");
                }
            }
            else if (strcmp(pCmdLine->arguments[0], "history") == 0){ //the command is to print the history 
                if (historySize < maxHistorySize) { //if the history array is not full - print it 
                    for(int i = 0; i<historySize; i++){
                        printf("#%d   %s", i, historyBuff[i]);
                    }
                }
                else { // the histiry array is full and had changes  - print it in the order of entrence and not the order of the array 
                    int i;
                    for(i = historySize%maxHistorySize; i < maxHistorySize; i++){
                        printf("#%d   %s", i - (historySize%maxHistorySize) , historyBuff[i]);
                    }
                    for(int j = 0; j < historySize%maxHistorySize ; j++){
                        printf("#%d   %s", j + i - historySize%maxHistorySize , historyBuff[j]);
                    }
                }
            }
            else{ //a different operation
                while(pCmdLine != NULL){
                    execute(pCmdLine, pipefd); // execute it by a child process
                    pCmdLine = pCmdLine->next;
                }

                close(pipefd[0]);
                
            }

            freeCmdLines(pCmdLine); //free the parsed input 
        }
        
        else{
            error = 0;
        }
    }
    return(0);
}