section .text
	global utoa_s
	extern strlen

section .data
	var2 TIMES 11 db 0  ; the string length

	
utoa_s:
	push	ebp
	mov	ebp, esp
	push ebx
	push ecx
	push edx
	mov ecx, var2 ; pointer to var2
	mov eax, [ebp+8] ; the int givven as argument
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
	push var2
    call strlen ; eax holds the length
	mov ecx, eax
	pop eax
	mov eax, ecx
	
    
    mov edx, var2 ; edx is the pointer for the interation

l1:
    movzx ebx, BYTE [edx]
    push  ebx
    add edx, 1
    loop l1

    mov ecx, eax 
    mov edx, var2

l2:
    pop   ebx 
    mov [edx], ebx
    add edx, 1
    loop l2
	mov eax, var2 
	

	pop edx
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret

	