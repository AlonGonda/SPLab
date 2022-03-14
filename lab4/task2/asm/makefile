all: scmp2

scmp2: scmp.o cmpstr.o
	gcc -m32 -o scmp2 scmp.o cmpstr.o

scmp.o: scmp.c
	gcc -m32 -c -o scmp.o scmp.c

cmpstr.o: cmpstr.s
		nasm -g -f elf cmpstr.s

.PHONY: clean

clean:
	rm -rf *.o scmp2-*