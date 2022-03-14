all: clean utoa 

utoa: utoa.o utoa_s.o atou_s.o
	gcc -m32 -o utoa utoa.o utoa_s.o atou_s.o

utoa.o: utoa.c
	gcc -m32 -c -o utoa.o utoa.c
	
utoa_s.o: utoa_s.asm
		nasm -g -f elf utoa_s.asm

atou_s.o: atou_s.asm
		nasm -g -f elf atou_s.asm

clean:
	rm -rf *.o utoa
