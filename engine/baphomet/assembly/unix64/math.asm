; rdi rsi rdx rcx r8 r9
;
; nasm -f macho64 math.asm 
;

section .data
rad_degs:	dq		57.29577
deg_rads:	dq		0.017453

global _deg_to_rad
global _rad_to_deg

_deg_to_rad:
	push	rbp ; Push stack pointer

	movq	xmm1,	qword [rad_degs]
	mulsd	xmm0,	xmm1

	pop		rbp ; Pop stack pointer
	ret			; Return rax as the return value

_rad_to_deg:
	push	rbp ; Push stack pointer

	movq	xmm1,	qword [deg_rads]
	mulsd	xmm0,	xmm1

	pop		rbp ; Pop stack pointer
	ret			; Return rax as the return value