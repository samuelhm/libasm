default rel
global ft_atoi_base

section .text

ft_atoi_base:
	cmp	rsi, 0
	je	.error_exit
	cmp	rdi, 0
	je	.error_exit
	sub	rsp, 256
	xor	rcx, rcx

.clear_stack_loop:
	mov	byte [rsp + rcx], 0
	inc	rcx
	cmp	rcx, 256
	jne	.clear_stack_loop
	xor	rcx, rcx

.check_base_loop:
	movzx	rdx, byte [rsi + rcx]
	cmp	dl, 0
	je	.check_base_end
	cmp	dl, '+'
	je	.error_cleanup
	cmp	dl, '-'
	je	.error_cleanup
	cmp	dl, 32
	je	.error_cleanup
	cmp	dl, 9
	jl	.not_low_space
	cmp	dl, 13
	jle	.error_cleanup

.not_low_space:
	movzx	rax, byte [rsp + rdx]
	cmp	al, 1
	je	.error_cleanup
	mov	byte [rsp + rdx], 1
	inc	rcx
	jmp	.check_base_loop

.check_base_end:
	cmp	rcx, 2
	jl	.error_cleanup
	mov	r8, rcx
	add	rsp, 256
	xor	rcx, rcx

.skip_spaces:
	movzx	rdx, byte [rdi + rcx]
	cmp	dl, 32
	je	.inc_space
	cmp	dl, 9
	jl	.check_signs
	cmp	dl, 13
	jle	.inc_space
	jmp	.check_signs

.inc_space:
	inc	rcx
	jmp	.skip_spaces

.check_signs:
	mov	r9, 1
	movzx	rdx, byte [rdi + rcx]
	cmp	dl, '+'
	je	.is_plus
	cmp	dl, '-'
	je	.is_minus
	jmp	.conversion_init

.is_minus:
	mov	r9, -1

.is_plus:
	inc	rcx
	jmp	.conversion_init

.conversion_init:
	xor	rax, rax

.conversion_loop:
	movzx	rdx, byte [rdi + rcx]
	cmp	dl, 0
	je	.end
	xor	r10, r10

.find_in_base_loop:
	movzx	r11, byte [rsi + r10]
	cmp	r11b, 0
	je	.end
	cmp	r11b, dl
	je	.found_in_base
	inc	r10
	jmp	.find_in_base_loop

.found_in_base:
	imul	rax, r8
	add	rax, r10
	inc	rcx
	jmp	.conversion_loop

.end:
	imul	rax, r9
	ret

.error_cleanup:
	add	rsp, 256

.error_exit:
	xor	rax, rax
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
