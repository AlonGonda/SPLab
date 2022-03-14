section .text
    global _start

section	.data
    extern open
    extern close
    extern read
    extern write

section .rodata
    print_format db 'Error occured\n', 0

_start:
    ;opening the file for reading 
	mov edx, [esp+8] ; get the file's name that has been givven as an argument 
    mov ebx,0x0000
    push ebx ; push secont argument for the open call - read only
    push edx ; push first argument for the open call - file name
    call open ;opens the file for reading and returns the file descriptor
    mov edx, eax ; keep the file descriptor in the edx register 

.Loop:
    ;read from the file till the file has ended or the there is no longer space in the buffer 
    mov ebx,50
    push ebx ; push third argument for the read call - bytes to read
    push buffer ;push second argument for the read call - pointer for the buffer 
    push edx ;push the first argument for the read call - file descriptor
	call read 

    ;write the bytes that has been read from the file 
    push eax ; push third argument for the write call - bytes to write 
    push buffer ;push second argument for the write call - pointer to the buffer
    push 1 ; push first argument for the write call - file descriptor of stdout 
    call write

    ;check if all the file have been read 
    test al, al ;if it will return 0 go out of loop 
    jne .Loop
    
    ;close the program 
    push edx ;push argument for the close call
    call close
	mov	eax,1
	int 0x80


section .bss
buffer:  resb 50







