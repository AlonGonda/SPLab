all: clean  bcmp


bcmp: bcmp.o 
	gcc -g -m32 -Wall -o bcmp bcmp.o 

	
bcmp.o: bcmp.c
	gcc -m32 -g -Wall -ansi -c -o bcmp.o bcmp.c 

	
.PHONY: clean


clean: 
	rm -f *.o  bcmp
