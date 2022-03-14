#include <elf.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char const *argv[]) {

    int fd; 
    void * mapPointer; // this will be the pointer to the start of the mapped file in the memory
    struct stat fileStatus; // this will hold information about the file using the stst structure 
    Elf32_Ehdr * header; // a pointer to the structure that will hold the deatails about the header

    if ((fd = open(argv[1], O_RDWR)) < 0) { // open the elf file. if it fails - exit.
        perror("Faild to open the fail");
        exit(EXIT_FAILURE);
    }

    fstat(fd, &fileStatus); //use the fstat function to get deatails about the opened file and put it in the fileStatus. 

    /* mapping the file using the mmap function.
    The arguments for the function are: preffered starting address for mapping, file's size, protect keys, proccess flags, file descriptor, offset */
    if ((mapPointer = mmap(0, fileStatus.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap failed"); 
        exit(EXIT_FAILURE);
    }

    header = (Elf32_Ehdr *)mapPointer; // a pointer to the beggining of the mapped file

    if (header->e_machine != 3) { // check if the file is a 32 bit 
        perror("non ELF 32 bit file");
        exit(1);
    }

    /* check if the first 3 bytes from the magic numbers are valid */
    if ((header->e_ident[1] != 'E') | (header->e_ident[2] != 'L') | (header->e_ident[3] != 'F')) {
        perror("This is not an ELF file");
        exit(1);
    }

    /* get a pointer to the section header table. we need to add the start poionter the value of the offset of the table */
    Elf32_Shdr *sectionHeader = (Elf32_Shdr *)(mapPointer + header->e_shoff);

    /* get the number of section table entries*/
    int entryNum = header->e_shnum;

    /* get a pointer to the shstrtab in order to get the section names*/
    Elf32_Shdr * sectionNames = sectionHeader+header->e_shstrndx;
    char * sectionNamePointer = mapPointer + sectionNames->sh_offset;

    /* print all the sections in the givven format */
    printf("[Nr]\t \t Name\t \t Addr\t \t Off\t \t Size\n");
    for (int i = 0; i < entryNum; i++){
        printf("[%2d] %20s\t%08x\t%08x\t%06x\t\n",i, sectionNamePointer + sectionHeader[i].sh_name, sectionHeader[i].sh_addr, sectionHeader[i].sh_offset, sectionHeader[i].sh_size);
    }

    /* free the memory */
    munmap(mapPointer, fileStatus.st_size);

    return 0;
}