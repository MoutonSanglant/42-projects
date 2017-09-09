; 64

extern printf

section .data
	chaine	db	"Hello %i !", 0xa, 0


section .bss
	wordvar:	resw	1
	tableau:	resq	10


section .text
	global _start

	_start:

	push	rbx

	mov		ecx, 10
	xor		rax, rax


print:

	push	rax
	push	rcx

	mov		[wordvar], ecx
	mov		rax, [wordvar]

	mov		rdi, format
	mov		rsi, rax
	xor		rax, rax

	call	printf		; printf(format, ecx)

	pop		rcx
	pop		rax

	mov		rdx, rax

	dec		ecx

	jnz		print

	pop		rbx

;	ret

	mov		rax, 60
	mov		rdi, 0
	syscall		; syscall

format:
	db	"Hello %i !", 0xa, 0
