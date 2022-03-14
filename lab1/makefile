#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task2 task1a task1b task1c

# Tool invocations
# Executables depends on the .o files
task2: task2.o
	gcc -m32 -g -Wall -o task2 task2.o

task1a: task1a.o
	gcc -m32 -g -Wall -o task1a task1a.o

task1b: task1b.o
	gcc -m32 -g -Wall -o task1b task1b.o

task1c: task1c.o
	gcc -m32 -g -Wall -o task1c task1c.o

# Depends on the source files
task2.o: task2.c
	gcc -g -Wall -m32  -c -o task2.o task2.c 

task1a.o: task1a.c
	gcc -g -Wall -m32  -c -o task1a.o task1a.c 

task1b.o: task1b.c
	gcc -g -Wall -m32  -c -o task1b.o task1b.c 	

task1c.o: task1c.c
	gcc -g -Wall -m32  -c -o task1c.o task1c.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o task2 task1a task1b task1c
