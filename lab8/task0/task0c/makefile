# All Targets
all: clean examine


examine: examine.o 
	gcc -g -m32 -Wall -o examine examine.o 

# Depends on the source and header files
examine.o: examine.c 
	gcc -m32 -g -Wall -c -o examine.o examine.c 

#tell the shell that "clean" is not a file name
.PHONY: clean

#Clean files
clean: 
	rm -f *.o examine