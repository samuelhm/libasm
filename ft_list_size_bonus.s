default rel
global ft_list_size

section .text

ft_list_size:
	xor	eax, eax

.loop:
	cmp	rdi, 0
	je	.end
	inc	eax
	mov	rdi, [rdi + 8]
	jmp	.loop

.end:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
