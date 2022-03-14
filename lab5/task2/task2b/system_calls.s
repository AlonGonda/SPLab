section .text
	
	global read
	global write
	global open
	global close

read:
	push    ebp
	mov ebp, esp
	sub esp,4
	pushad
	mov eax, 3 ; system call number for read 
	mov ebx, [ebp+8] ; file descriptor
	mov ecx, [ebp+12] ; pointer to input buffer
	mov edx, [ebp+16] ; buffer size
	int 80h
	mov [ebp-4],eax
	popad
	mov eax, [ebp-4]
	add esp,4
	pop ebp
	ret

write:
	push	ebp
	mov	ebp, esp
    push ebx
	push ecx
	push edx
    mov eax, 0x04 ; system call number for write
	mov ebx, [ebp+8]; file descriptor
	mov ecx, [ebp+12]; pointer to output buffer
    mov edx, [ebp+16] ; count of bytes to send
    int 0x80
	pop edx
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret

open:
	push	ebp
	mov	ebp, esp
    push ebx
	push ecx
	push edx
    mov eax, 0x05 ; system call number for open
	mov ebx, [ebp+8]; file name
    mov ecx, [ebp+12] ; file access
	mov edx, 0000700
    int 0x80
	pop edx
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret

close:
	push	ebp 
	mov	ebp, esp
    push ebx
	push ecx
	push edx
    mov eax, 0x06 ; system call number for close
	mov ebx, [ebp+8]; file descriptor
    int 0x80
	pop edx
	pop ecx
	pop ebx
	mov esp, ebp
	pop ebp
	ret

