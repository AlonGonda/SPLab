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

    /* get a pointer to the section header table */
    Elf32_Shdr *sectionHeader = (Elf32_Shdr *)(mapPointer + header->e_shoff);

    /* get the number of section header entries */
    int sectionNumber = header->e_shnum;

    /* get a pointer to the line that holds the details about the names section table in the section header table */
    Elf32_Shdr * namesSection = sectionHeader + header->e_shstrndx;

    /* get a pointer to the name section table */
    char *sectionNamePointer = mapPointer + namesSection->sh_offset;

    /* iterate over the section header table and check every one of them if they are symbols*/
    for (int i = 0; i < sectionNumber; i++) {
        if ((sectionHeader[i].sh_type == SHT_SYMTAB) || (sectionHeader[i].sh_type == SHT_DYNSYM)) { // if it is a symbol table
            Elf32_Sym *symbolsTable = (Elf32_Sym *)(mapPointer + sectionHeader[i].sh_offset); // get a pointer to the table
            Elf32_Shdr *symbolsTableName = sectionHeader + sectionHeader[i].sh_link; // get the name of the symbol

            /* check how many symbols are they in this entry*/
            int symbolsNumber = sectionHeader[i].sh_size / sizeof(Elf32_Sym);

            printf("\nSymbol table '%s' contains %d entries:\n", sectionNamePointer + sectionHeader[i].sh_name, symbolsNumber);
            printf("Num\t \t   Value\t \t  Ndx\t  \t Section Name\t  \t \t Symbol Name\n");

            for (int j = 0; j < symbolsNumber; j++) {
            
                char * sectionName = "\0";

                /* if the entry number is valid and smaller then the total entries - get the section name from the table*/
                if (symbolsTable[j].st_shndx < header->e_shnum) {
                    sectionName = mapPointer + namesSection->sh_offset + sectionHeader[symbolsTable[j].st_shndx].sh_name;
                }

                if (symbolsTable[j].st_shndx == 65521) {
                    printf("%2d: \t \t   %08x\t \t %4s\t \t %-20s\t \t %-20s\n", j, symbolsTable[j].st_value, "ABS", sectionName, (char*) (mapPointer + symbolsTableName->sh_offset + symbolsTable[j].st_name));
                }
                
                else if(symbolsTable[j].st_shndx == 0) {
                    printf("%2d \t \t   %08x\t \t %4s\t \t %-20s\t \t %-20s\n", j, symbolsTable[j].st_value, "UND", sectionName, (char*) (mapPointer + symbolsTableName->sh_offset + symbolsTable[j].st_name));
                }
                
                else {
                    printf("%2d \t \t   %08x\t \t %4d\t \t %-20s\t \t %-20s\n", j, symbolsTable[j].st_value, symbolsTable[j].st_shndx, sectionName,(char*) (mapPointer + symbolsTableName->sh_offset + symbolsTable[j].st_name));
                }
            }
        }
    }
    
    /* free the memory */
    munmap(mapPointer, fileStatus.st_size);

    return 0;
}