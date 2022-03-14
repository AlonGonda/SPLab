all: task2b

task2b: system_calls.o task2b.o utoa_s.o strlen.o cmpstr.o atou_s.o
	 ld  -melf_i386 -o $@ $^ 


%.o: %.s
	nasm -f elf  -o $@ $<
clean:
	rm -rf *.o task2b
