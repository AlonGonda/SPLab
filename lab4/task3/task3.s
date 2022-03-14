%define X 'A'
%define STR string1

section .rodata
    print_format db '"%c" appears in "%s" %d times', 10, 0
	string1 db 'ABBA', 0
    string2 db 'BBA', 0
    string3 db 'BB', 0
    string4 db '', 0

section .data
	extern printf

section .text
	global _start
	
_start: ;initiating the values for the loop over the string 
	mov ecx, -1 ; current position
	mov	eax, 0  ; return value - number of chars 

Loop:
	inc ecx ;move forward
	mov ebx, ecx
	add ebx, STR ; move to the current postion 
	movzx ebx, BYTE[ebx]
	test bl, bl ; test if the string is not over 
	jne Check ; enter if there is a char to check
	jmp Print ; end of string. print the result

Check:
	cmp ebx, X ; compare between the givven char and current char 
	jnz Loop ; if they are different go back to loop 
	inc eax ; if they are the same, add one to the counter
	jmp Loop

Print:
	sub esp,4 ; allocate sapce in the stack for the print result
	push eax ; push the 4th argument for the printf AKA number of chars 
	push STR ; push the 3th argument for the printf AKA the givven string 
	push X ;push the second argument for the printf AKA the givven char 
	push print_format ;push the first argument for the printf AKA the format 
	call printf
	add esp, 16 ;bring back the stack pointer to where it was 

FINISH:
	mov ebx, 0 
    mov eax, 1
    int 80h
	



	

	
