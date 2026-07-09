default rel
global ft_list_sort

section .text

ft_list_sort:
	cmp	rdi, 0
	je	.end
	cmp	rsi, 0
	je	.end
	mov	rax, [rdi]					; rax = *begin_list
	cmp	rax, 0
	je	.end
	cmp	qword [rax + 8], 0
	je	.end

	push	r12						; preservar registros callee-saved
	push	r13
	push	r14
	push	r15
	push	rbp						; ultimo push para alinear stack a 16

	mov	r12, rdi					; r12 = begin_list (t_list **)
	mov	r13, rsi					; r13 = cmp (funcion de comparacion)

.outer_loop:
	mov	r14, [r12]					; r14 = curr = *begin_list
	xor	r15d, r15d					; r15 = swapped = 0
	xor	ebp, ebp					; rbp = prev = NULL

.inner_loop:
	cmp	r14, 0						; fin de lista
	je	.check_swap
	mov	rbx, [r14 + 8]				; rbx = curr->next
	cmp	rbx, 0
	je	.check_swap

	mov	rdi, [r14]					; arg1: curr->data
	mov	rsi, [rbx]					; arg2: curr->next->data
	push	rbx						; salvar volatiles antes del call
	push	r10						; push extra para alinear stack
	call	r13						; cmp(curr->data, curr->next->data)
	pop	r10
	pop	rbx

	cmp	eax, 0						; cmp retorna > 0 ?
	jle	.no_swap					; no, siguiente par

	mov	rax, [r14]					; swap de data entre nodos
	mov	rdx, [rbx]
	mov	[r14], rdx
	mov	[rbx], rax
	mov	r15d, 1						; swapped = 1

.no_swap:
	mov	rbp, r14					; prev = curr
	mov	r14, rbx					; curr = curr->next
	jmp	.inner_loop

.check_swap:
	cmp	r15d, 0						; hubo algun swap?
	jne	.outer_loop					; si, otra pasada completa

	pop	rbp						; restaurar registros
	pop	r15
	pop	r14
	pop	r13
	pop	r12

.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
