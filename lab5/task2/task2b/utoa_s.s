section .text
	global utoa_s
	extern strlen

section .data
	var2 TIMES 11 db 0  ; initializing the string length

	
utoa_s:
	;maintaince of the stack and the used registers 
	push	ebp
	mov	ebp, esp
	push ebx
	push ecx
	push edx

	mov ecx, var2 ; pointer to var2, where the number is going to be written 
	mov eax, [ebp+8] ; the int givven as an argument
	mov ebx, 10 ; divide by 10 

L2:
	mov edx, 0 
	div ebx ; divide eax value by ebx value (10) and puts the value in edx
	add edx, 48 ; add 48 to the division value. now it hold a number represent the asscii value 
	mov [ecx], edx ; add the current number to the start of the string 
	inc ecx ; increment ecx by 1 for the next iteration
	test al, al ; check if the whole int has been converted 
	jne L2 ; if not, return to loop
	

	;reverse the string so it represent the right value
	push var2 ;it is the argument for the function strlen who is going to be called next 
    call strlen ; eax holds the return length
	;maintaince of the registers so it can be used again and the length won't be in the stack 
	mov ecx, eax
	pop eax
	mov eax, ecx
	
    
    mov edx, var2 ; edx is the pointer for the iteration. iteratre over the string from beginning

l1:
	;all chars from var2 are going to be enterd to the stack 
    movzx ebx, BYTE [edx] ;get the current char 
    push  ebx ; push it to the stack
    add edx, 1 ;move forward on the string 
    loop l1 ;iteratre until counter is zero (it is the end of the string)

    mov ecx, eax  ;initializing the counter again
    mov edx, var2 ; initializing the pointer again

l2:
	;all chars are going to be enter into the string varible (var2)
    pop   ebx ;pop out from the stack the current char
    mov [edx], ebx ;add it to the string who is going to be return 
    add edx, 1 ;move forward the pointer
    loop l2 ;continue the loop until the counter is zero

	
	mov eax, var2 ;return ver2
	
	;maintaince of the stack
	pop edx
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret

	