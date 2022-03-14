# All Targets
all:  clean task1


task1: task1.o 
	gcc -g -m32 -Wall -o task1 task1.o 

# Depends on the source and header files
task1.o: task1.c 
	gcc -m32 -g -Wall -c -o task1.o task1.c 

#tell the shell that "clean" is not a file name
.PHONY: clean

#Clean files
clean: 
	rm -f *.o task1