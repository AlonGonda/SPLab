#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define maxHistorySize 10

int main(int argc, char **argv) {

    int pipefd[2]; //file descriptor array for the pipe function
    int status;

    char dflag = 0;
    int i;
    for (i = 0; i< argc; i++){
        if (strcmp(argv[i], "-d") == 0){
            dflag =1;
        }
    }

    char *command1[3];
    char *command2[4];

    command1[0] = "ls"; command1[1] = "-l"; command1[2] = 0;
    command2[0] = "tail"; command2[1] = "-n"; command2[2] = "2"; command2[3] = 0;

    //in case the pipe has faild - print error and exit 
    if (pipe(pipefd) == -1) { 
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t cpid1, cpid2;

    //before first fork debug
    if (dflag == 1){
        fprintf(stderr, "(parent_process>forking...)\n");
    }
    //first fork
    cpid1 = fork();
    //after first fork debug
    if (dflag == 1){
        fprintf(stderr, "(parent_process>created process with id: %d)\n", cpid1);
    }

    //in case the fork has faild - print error and exit 
    if (cpid1 == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0){
        //before redirecting stdout to the write end of the pipe
        if (dflag == 1){
            fprintf(stderr, "(child1>redirecting stdout to the write end of the pipe...)\n");
        }
        close(STDOUT_FILENO); //close the stdout stream
        dup(pipefd[1]);
        close(pipefd[1]);
        //before executing the cmd
        if (dflag == 1){
            fprintf(stderr, "(child1>going to execute cmd: ...)\n");
        }
        execvp(command1[0], command1);
        _exit(EXIT_FAILURE);
    }

    else{
        //before closing the write-end of the pipe debug
        if (dflag == 1){
            fprintf(stderr, "(parent_process>closing the write-end of the pipe...)\n");
        }
        close(pipefd[1]);
    }

    //second fork
    cpid2 = fork();

    //in case the fork has faild - print error and exit 
    if (cpid2 == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (cpid2 == 0){
        //before redirecting stdin to the read end of the pipe
        if (dflag == 1){
            fprintf(stderr, "(child2>redirecting stdin to the read end of the pipe...)\n");
        }
        close(STDIN_FILENO); //close the stdout stream
        dup(pipefd[0]);
        close(pipefd[0]);
        //before executing the cmd
        if (dflag == 1){
            fprintf(stderr, "(child2>going to execute cmd: ...)\n");
        }
        execvp(command2[0], command2);
        _exit(EXIT_FAILURE);
    }

    else{
        //before closing the read-end of the pipe debug
        if (dflag == 1){
            fprintf(stderr, "(parent_process>closing the read-end of the pipe...)\n");
        }
        close(pipefd[0]);
    }

    //before waiting for the child processes to terminate
    if (dflag == 1){
        fprintf(stderr, "(parent_process>waiting for the child processes to terminate...)\n");
    }
    waitpid(cpid1, &status, 0);
    waitpid(cpid2, &status, 0);


    //before exiting
    if (dflag == 1){
        fprintf(stderr, "(parent_process>exiting...)\n");
    }
    return 0;

}