default rel
global ft_list_sort

section .text

ft_list_sort:
	cmp	rdi, 0
	je	.end
	cmp	rsi, 0
	je	.end
	mov	rax, [rdi]
	cmp	rax, 0
	je	.end
	cmp	qword [rax + 8], 0
	je	.end

	push	r12
	push	r13
	push	r14
	push	r15
	push	rbp

	mov	r12, rdi
	mov	r13, rsi

.outer_loop:
	mov	r14, [r12]
	xor	r15d, r15d
	xor	ebp, ebp

.inner_loop:
	cmp	r14, 0
	je	.check_swap
	mov	rbx, [r14 + 8]
	cmp	rbx, 0
	je	.check_swap

	mov	rdi, [r14]
	mov	rsi, [rbx]
	push	rbx
	push	r10
	call	r13
	pop	r10
	pop	rbx

	cmp	eax, 0
	jle	.no_swap

	mov	rax, [r14]
	mov	rdx, [rbx]
	mov	[r14], rdx
	mov	[rbx], rax
	mov	r15d, 1

.no_swap:
	mov	rbp, r14
	mov	r14, rbx
	jmp	.inner_loop

.check_swap:
	cmp	r15d, 0
	jne	.outer_loop

	pop	rbp
	pop	r15
	pop	r14
	pop	r13
	pop	r12

.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
