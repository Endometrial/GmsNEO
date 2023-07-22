; rdi rsi rdx rcx r8 r9
;
; nasm -f macho64 math.asm 
;

global _add_numbers
global _add_one

_add_numbers:
	push	rbp ; Push stack pointer

	mov		rax,	rdi;
	add 	rax,	rsi;

	pop		rbp ; Pop stack pointer
	ret			; Return rax as the return value

_add_one:
	push 	rbp

	mov		rax,	rdi;
	add 	rax,	1;

	pop		rbp
	ret