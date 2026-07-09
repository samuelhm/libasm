default rel
global ft_list_remove_if

extern free

section .text

ft_list_remove_if:
	cmp	rdi, 0
	je	.end
	cmp	rdx, 0
	je	.end
	cmp	rcx, 0
	je	.end

	push	r12
	push	r13
	push	r14
	push	r15
	push	rbp					;Un push extra para alinear stack
	
	mov	r12, rdi
	mov	r13, rsi
	mov	r14, rdx
	mov	r15, rcx

.loop:
	mov	rbp, [r12]				;rbp = t_list *curr
	cmp	rbp, 0
	je	.cleanup_end	

	mov	rdi, [rbp]
	mov	rsi, r13
	call	r14					;*(cmp)

	cmp	eax, 0
	jne	.skip_node

	mov	rbx, [rbp + 8]			;rbx = curr->next

	mov	rdi, [rbp]
	call	r15					;*(free_fct)
	mov	rdi, rbp
	call	free wrt ..plt		;free

	mov	[r12], rbx
	jmp	.loop

.skip_node:
	lea	r12, [rbp + 8]			;r12 = curr->next
	jmp	.loop

.cleanup_end:
	pop	rbp
	pop	r15
	pop	r14
	pop	r13
	pop	r12
.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
