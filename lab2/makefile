all: task2a task2b task2c task3

task2a: task2a.o
	gcc -g -m32 -Wall -o task2a task2a.o
	rm task2a.o
	
task2b: task2b.o
	gcc -g -m32 -Wall -o task2b task2b.o
	rm task2b.o
	
task2c: task2c.o
	gcc -g -m32 -Wall -o task2c task2c.o
	rm task2c.o
	
task3: task3.o
	gcc -g -m32 -Wall -o task3 task3.o
	rm task3.o

	
task2a.o: task2a.c 
	gcc -m32 -g -Wall -ansi -c -o task2a.o task2a.c


task2b.o: task2b.c 
	gcc -m32 -g -Wall -ansi -c -o task2b.o task2b.c


task2c.o: task2c.c 
	gcc -m32 -g -Wall -ansi -c -o task2c.o task2c.c


task3.o: task3.c 
	gcc -m32 -g -Wall -ansi -c -o task3.o task3.c



.PHONY: clean

clean:
	rm -f *.o task2a task2b task2c task3


	


