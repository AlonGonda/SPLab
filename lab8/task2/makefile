# All Targets
all: clean task2


task2: task2.o 
	gcc -g -m32 -Wall -o task2 task2.o 

# Depends on the source and header files
task2.o: task2.c 
	gcc -m32 -g -Wall -c -o task2.o task2.c 

#tell the shell that "clean" is not a file name
.PHONY: clean

#Clean files
clean: 
	rm -f *.o task2