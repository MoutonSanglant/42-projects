
global _start

extern printf

section .data

	fmt		db	"%i", 0xa, 0
	msg		db	"result:", 0xa, 0
	len		equ $ - msg

section .bss

default rel
sum:	resw 1

section .text

_start:

;	numbers
;	mov sum, rax

	; write (1, msg, len)
	mov		rax, 1 ; write
	mov		rdi, 1
	mov		rsi, msg
	mov		rdx, len
	syscall

number:

	mov rax, 47		; 47 litteral constant
	sub rax, 5

	mov		[sum], rax ; store rax to sum

print:

	push	rbp			; set up stack frame, must be aligned

	; write (fmt, sum)
	mov		rdi, fmt	; 1st param (fmt)
	mov		rsi, [sum]	; 2nd param (sum)
	xor		rax, rax	; printf is varargs

	call	printf		; printf(fmt, sum)

	pop		rbp


	; write (1, sum, 4)
;	mov		rax, 0x2000004 ; write
;	mov		rdi, 1
;	mov		rsi, sum
;	mov		rdx, 4
;	syscall

	; exit (0)
	mov		rax, 60 ; exit
	sub		rdi, 0
	syscall
