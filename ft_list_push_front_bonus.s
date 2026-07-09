default rel
global ft_list_push_front

extern malloc

section .text

ft_list_push_front:
	cmp	rdi, 0					;Puntero  NULL
	je	.end
	push	rdi					;begin_list
	push	rsi					;data

	mov		rdi,	16			;8 bytes cada puntero de la struct
	call	malloc	wrt ..plt

	pop	rsi
	pop	rdi

	cmp	rax, 0					;Malloc error
	je	.end

	mov	[rax], rsi				;nuevo_nodo->data = data
	mov	rcx, [rdi]				;rcx = *begin_list
	mov	[rax + 8], rcx			;nuevo_nodo->next = *begin_list
	mov	[rdi], rax				;*begin_list = nuevo_nodo

.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
