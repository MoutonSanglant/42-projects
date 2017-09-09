bits 32

;extern puts

section .data
	chaine	db "Hello world !", 0

section .text
	global _start

	_start:

;	syscall write()
	mov eax, 4
	mov ebx, 1
	mov ecx, chaine
	mov edx, 14
	int 0x80		; syscall

;	push dword chaine
;	call puts
;	add esp, 4

	mov eax, 1
	int 0x80		; syscall
