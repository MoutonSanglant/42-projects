; 64

section .data
	chaine	db "Hello world !", 0xa, 0

section .text
	global _start

	_start:

	; write (1, msg, len)
	mov		rax, 1
	mov		rdi, 1
	mov		rsi, chaine
	mov		rdx, 14		; length
	syscall

	; exit (0)
	mov		rax, 60
	mov		rdi, 0
	syscall		; syscall
