default rel
global ft_strcmp

%define s1 rdi
%define s2 rsi
%define return rax

section .text

ft_strcmp:
	xor return, return

.bucle:
	mov dl, byte [s1]
	mov cl, byte [s2]
	cmp dl, cl
	jne .fin  
	cmp cl, 0
	je .fin
	inc s1
	inc s2
	jmp .bucle

.fin:
	movzx eax, dl
	movzx ecx, cl
	sub eax, ecx          ; Restamos: EAX = EAX - ECX
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
