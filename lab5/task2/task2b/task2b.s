section .text
    global _start

section .bss
    buffer:  resb  50

section	.data
    extern utoa_s
    extern atou_s
    extern open
    extern close
    extern read
    extern write
    extern strlen
    extern cmpstr
    fileErrorPrint db "Error: open call failed",10,0
    fileErrorLength: equ $-fileErrorPrint ;get the length of the string 
    argsErrorPrint db "Error: arguments are not valid",10,0
    argsErrorLength: equ $-argsErrorPrint    
    flagErrorPrint db "Error - flag is not valid",10,0
    flagErrorLength: equ $-flagErrorPrint     


extern main

_start:
    mov ecx, [esp] ;get a pointer to argv
    cmp ecx,3 ;check if there are 3 arguments in argv
    jl regular ; there is no additional flag  
    je flag ; there is additional flag
    ;jg argsError ; there is too many arguments
    
flag:
    mov eax, [esp+8] ; get the flag velue
    cmp byte [eax], 45 ; check that the flag starts with '-'
    jne flagError ; if it is a different char return error
    cmp byte [eax+1],119 ; check that the flag starts with 'w'
    jne flagError ; reutrn error if it's not
    cmp byte [eax+2],115 ; check that the flag includes 's' after the 'w'
    jmp countWords ; else count all the words

regular:
    cmp ecx, 2 ;check that there is a file name
    jl argsError ; if there are less then 2 arguments go to error
	mov edx, [esp+8] ; get the file name
    mov ebx,0x0000
    push ebx ; push secont argument for the open call - read only
    push edx ; push first argument for the open call - file name
    call open
    cmp eax, 0 ; check if the call has succeeded 
    jl fileError ; if it returned -1 go to error
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
    jmp exit

countWords:
    mov edx, [esp+12] ; get the file name
    mov ebx,0x0000
    push ebx ; push secont argument for the open call - read only
    push edx ; push first argument for the open call - file name
    call open
    cmp eax, 0 ; check if the call has succeeded 
    jl fileError ; if it returned -1 go to error
    mov edx, eax ; keep the file descriptor in the edx register
    mov ecx,0


.LoopCount:
    ;read from the file till the file has ended or there is no longer space in the buffer 
    push 1 ; push third argument for the read call - bytes to read
    push buffer ;push second argument for the read call - pointer for the buffer 
    push edx ;push the first argument for the read call - file descriptor
	call read 
    cmp eax,0   ; if it is zero then there is nothing to read - out of loop
    je print

    cmp byte [buffer],9 ;the char is tab
    je .test
    cmp byte [buffer], 10 ;the char is \n (new line)
    je .test
    cmp byte [buffer], 32 ;the char is space
    je .test
    
    mov ebx,1
    
    ;check if all the file have been read 
    test al, al ;if it will return 0 go out of loop 
    jne .LoopCount
    jmp print

.test:
    cmp ebx,0
    jz .LoopCount
    add ecx,1
    mov ebx,0
    jmp .LoopCount

print:
    cmp ebx,0 
    je print2
    inc ecx ;add the last word to the counter

print2:
    push ecx ; argument for utoa_s - number of words
    call utoa_s ; return the number as a string 
    push 11 ;third argument for write - number of bytes   
    push eax ; second argument for write - value to print
    push 1 ; first argument for write - print to stdout
    call write
    jmp exit

exit:
    push edx ;push argument for the close call 
    call close
	mov	eax,1
	int 0x80

fileError:
    push fileErrorLength
    push fileErrorPrint
    push 1
    call write
    mov eax,1
    int 0x80

argsError:
    push argsErrorLength
    push argsErrorPrint
    push 1
    call write
    mov eax,1
    int 0x80

flagError:
    push flagErrorLength
    push flagErrorPrint
    push 1
    call write
    mov eax,1
    int 0x80
