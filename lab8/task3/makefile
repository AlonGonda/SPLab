# All Targetss
all: clean patch task3

task3: task3.o 
	gcc -g -fno-pie -m32 -Wall -o task3 task3.o 

# Depends on the source and header files
task3.o: task3.c 
	gcc -m32 -g -fno-pie -Wall -c -o task3.o task3.c 

patch: patch.o 
	gcc -g -fno-pie -m32 -Wall -o patch patch.o 

# Depends on the source and header files
patch.o: patch.c 
	gcc -m32 -g -fno-pie -Wall -c -o patch.o patch.c 

#tell the shell that "clean" is not a file name
.PHONY: clean

#Clean files
clean: 
	rm -f *.o patch task3