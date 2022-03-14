#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "LineParser.h"
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>

void execute(cmdLine *pCmdLine){
    int status;
    int cpid = fork();
    /* Fork failed, terminate everything */
    if (cpid == -1){
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }
    /* if the forking worked and we moved to the child process, we need to execute. If failed, we need to close this process */
    if (cpid == 0){
        int result = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        if (result == -1){
            _exit((long)getpid);
        }
    }
    /* This is the Father. If the child succeed, do nothing. If failed, print error message */
    else{
        if (pCmdLine->blocking == 1){
            waitpid(cpid, &status, 0);
            if (!WIFEXITED(status)){
                printf("Execvp Failed by Child");
            }  
        }
    }
    
}

int main(int argc, char **argv) {
    char cwdBuff[PATH_MAX];
    char input[2048];
    int dirstatus;

    while(1){
        getcwd(cwdBuff, PATH_MAX);
        printf("%s\n",cwdBuff);

        fgets(input, 2048, stdin);

        if (strcmp(input, "quit\n") == 0){
            exit(0);
        }

        cmdLine *pCmdLine;
        pCmdLine = parseCmdLines(input);
        
        if (strcmp(pCmdLine->arguments[0], "cd") == 0){
            dirstatus = chdir(pCmdLine->arguments[1]);
            if (dirstatus == -1){
                fprintf(stderr, "cd Failed\n");
            }
        }
        else{
            execute(pCmdLine);
        }

        freeCmdLines(pCmdLine);
    }
    return(0);
}