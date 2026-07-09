default rel
global ft_strlen

section .text

ft_strlen:
	xor rax, rax

.bucle:
	cmp byte [rdi + rax], 0
	je .fin
	inc rax
	jmp .bucle

.fin:
	ret

stdout		equ 1

section .note.GNU-stack noalloc noexec nowrite progbits
