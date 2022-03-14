section .text
	global atou_s
	
atou_s:
	;maintaince of the stack and the used registers
	push	ebp
	mov	ebp, esp
	push ebx
	push ecx
	push edx

	mov eax,0 ; initializing the return value of the int 
	mov ebx, [ebp+8] ; a pointer to the beginning of the string givven as an argument

convert:
	movzx ecx, byte[ebx] ;get the current char
	test ecx,ecx ;test if the char is \n
	je done ; if it is, this is the end of the string - finish 

	;checking if the current char represents a valid number 
	cmp ecx,48 ; if it lower then 0 in asscii values return error
	jl error

	cmp ecx,57 ;if it is greater then 9 in asscii values return error 
	jg error

	sub ecx,48 ;get the current value of the char in a number 
	imul eax,10 ;multiply the current return int by 10 
	add eax,ecx ;add the current vakue to the current return int 

	inc ebx ;move the pointer to the next char of ther string 
	jmp convert ;return the loop 

error:
	mov eax,-1 ;return -1 if the string does not represent a valid number 

done:
	;maintaince of the stack
	pop edx
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret
	

	



	