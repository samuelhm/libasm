default rel
global ft_strdup

extern ft_strlen
extern ft_strcpy
extern malloc
extern __errno_location

section .text

ft_strdup:
	call	ft_strlen
	inc	rax					;(para el '\0')

	push	rdi
	push	rax
	mov		rdi, rax
	call	malloc wrt ..plt

	pop	rcx					; rcx ahora tiene el tamaño
	pop	rsi					; Recuperamos la string original directo en 'rsi'

	cmp	rax, 0
	je	.malloc_error

	mov	rdi, rax
	call	ft_strcpy
	ret

.malloc_error:
	xor	rax, rax
	ret

section .note.GNU-stack noalloc noexec nowrite progbits