all: task2a

task2a: system_calls.o task2a.o 
	 ld  -melf_i386 -o $@ $^ 


%.o: %.s
	nasm -f elf  -o $@ $<
clean:
	rm -rf *.o task2a
