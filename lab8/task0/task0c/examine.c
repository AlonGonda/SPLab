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

Elf32_Shdr * getSectionHeaders (Elf32_Ehdr * header, char * mapPointer) {
	
    Elf32_Shdr * sectionHeaders = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * header->e_shnum);
	
	int i;
	int currentOffset;
	for (i = 0; i < header->e_shnum; i++) {
	    currentOffset = header->e_shoff + i * sizeof(Elf32_Shdr);
	    sectionHeaders[i] = *(Elf32_Shdr *)(mapPointer + currentOffset);
	}
	return sectionHeaders;
}
	
void printSectionHeaderSizes(Elf32_Shdr * sectionHeaders, int number) {
	
    int i;
	for (i = 0; i < number; i++)
	    printf("%-40s Section #[%d] size: [%d Bytes]\t\n", "" ,i, sectionHeaders[i].sh_size);
}

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

    printf("ELF Header:\n"); 

    /* print the first 3 bytes from the magic numbers */
    printf("%-40s %d  ,  %d   ,   %d\t\t\n","Magic:", header->e_ident[1], header->e_ident[2], header->e_ident[3]); 

    /* check if the first 3 bytes from the magic numbers are valid */
    if ((header->e_ident[1] != 'E') | (header->e_ident[2] != 'L') | (header->e_ident[3] != 'F')) {
        perror("This is not an ELF file");
        exit(1);
    }

    /* print the data encoding scheme */
    switch (header->e_ident[5]) {

    case ELFDATA2LSB:
        printf("%-40s 2's complement, little endian\t\n","Data: ");
        break;
    
    case ELFDATA2MSB:
        printf("%-40s 2's complement, big endian\t\n","Data: ");
        break;

    default:
        printf("%-40s \t\n","Data: Unknown format");
        break;
    } 

    /* print the entry point address */
    printf("%-40s %x\t\n","Entry point address:", header->e_entry);

    /* print the section header table address */
    printf("%-40s %d\t\n","Start of section header:", header->e_shoff);

    /* print the number of section headrer entries */
    printf("%-40s %d\t\n","Number of section headers:", header->e_shnum);

    /* print the size of each section header entry */
    printf("The size of each section header entry:\n");
    Elf32_Shdr *sectionHeaders = getSectionHeaders(header, mapPointer);
	printSectionHeaderSizes(sectionHeaders, header->e_shnum);

    /* print the string table index */
    printf("%-40s %d\t\n","Section header string table index:", header->e_shstrndx);

    /* free the memory */
    free(sectionHeaders); 
    munmap(mapPointer,fileStatus.st_size);

    return 0;
}