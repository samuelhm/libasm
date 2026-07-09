default rel
global ft_strcpy

%define dst rdi
%define src rsi
%define return rax

section .text

ft_strcpy:
	mov return, dst


.bucle:
	mov dl, byte [src]
	mov byte [dst], dl
	cmp dl, 0
	je .fin  
	inc src
	inc dst
	jmp .bucle

.fin:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
