#include <sys/types.h>
#include <sys/wait.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>

int main(int argc, char const *argv[]) {

    int pipefd[2]; //file descriptor array for the pipe function

    char * msg = "hello\n"; //the massage that child need to pass 

    //in case the pipe has faild - print error and exit 
    if (pipe(pipefd) == -1) { 
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    int cpid = fork();

    //in case the fork has faild - print error and exit 
    if (cpid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    //the child's code 
    if (cpid == 0) {
       close(pipefd[0]);  //close the read_end 
       write(pipefd[1] , msg , strlen(msg)); //write into the pipe the massage 
       close(pipefd[1]); //close the write_end 
       _exit(EXIT_SUCCESS); //end the child proccess 
    }

    //the parent's code 
    else {
       wait(NULL); //wait for the child to finish 
       close(pipefd[1]); //close the write_end 
       char toPrint[strlen(msg)]; //a buffer to save the massage from the child 
       read(pipefd[0] , toPrint ,strlen(msg)); //read from the pipe into the buffer 
       write(STDOUT_FILENO , &toPrint , strlen(toPrint)); //print from the buffer into the stdout 
       close(pipefd[0]); //close the read_end 
       exit(EXIT_SUCCESS); //end the proccess
    }  
    return 0;
}
