all: clean atou 

atou: atou.o atou_s.o
	gcc -m32 -o atou atou.o atou_s.o 

atou.o: atou.c
	gcc -m32 -c -o atou.o atou.c
	
atou_s.o: atou_s.asm
		nasm -g -f elf atou_s.asm


clean:
	rm -rf *.o atou
