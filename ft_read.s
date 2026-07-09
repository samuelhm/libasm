default rel
global ft_read
extern __errno_location
section .text


ft_read:
	mov	rax,	0
	syscall
	cmp	rax,	0
	jl	.exit_error
	ret

.exit_error:
	neg 	rax
	mov 	rdi, rax
	push	rdi							;guardamos rdi porque al ser volatil no sabemos si errno_location lo borra.
	call	__errno_location wrt ..plt
	pop		rdi
	mov		[rax], rdi
	mov		rax, -1
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
