#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdint.h>


int main(int argc, char const *argv[]) {

    int sfd, dfd; // initiate the file descriptor for both files
    void *src, *dest; // initiate pointers for the mapped files in the memory
    size_t copySize = (long) atoi(argv[3]);
    off_t offSrc = (long) atoi(argv[2]);
    off_t offDest = (long) atoi(argv[5]);

    if ((sfd = open(argv[1], O_RDWR)<0)) {  // open the source file and get the file descriptor
        printf("can't open the source file");
        return 0;
    }

    src = mmap(0, copySize, PROT_READ, MAP_SHARED, sfd, offSrc); // mapping the source file into the memory 

    if ((dfd = open(argv[4], O_RDWR | O_CREAT, 0666)) < 0) { // open the dest file and get the file descriptor
        printf("can't open the dest file");
        return 0;
    }

    dest = mmap(0, copySize, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, offDest); // mapping the source file into the memory 

    memcpy(dest, src, copySize);

    munmap(src, copySize);

    munmap(dest, copySize);

    close(sfd);
    close(dfd);
    

    return 0;
}

