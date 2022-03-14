section .text
	global cmpstr
	
cmpstr:
	push ebp
	mov	ebp, esp
	mov edx, ebx
	mov	eax,-1

Loop:
	add eax, 1 ; the location in the strings

	mov ebx, eax ; how many chars to pass from the beginning of string 1
    mov ecx, eax ; how many chars to pass from the beginning of string 2

	add ebx, [ebp+8]
    add ecx, [ebp+12]
	movzx	ebx, BYTE [ebx]
    movzx   ecx, BYTE [ecx]

compare:
	cmp ebx, ecx ;compare between both chars
    jnz Dif ; enter if there is a difference 

    ;loop condtion
    or bl,cl ; cheack if at least one string is not over, put the value of or operation in bl
    test bl,bl ; cheack if both strings are over. enter to equal if yes, move to loop is not. 
	je Equal ; if both strings are over jump to Equal

    jmp Loop ;contiue the loop
    
Dif:
	sub ebx,ecx ; the gap between both ascii values
	mov eax, ebx ; put the value in the return register
	jmp FINISH

Equal:
    mov eax, 0 ; return value is 0 because both strings are equal.
    jmp FINISH

FINISH:
	mov esp, ebp ;stack maintenance
    mov ebx, edx; take back original ebx value
	pop ebp ;stack maintenance
	ret



	

	
