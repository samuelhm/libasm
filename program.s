default rel

stdout		equ 1
sys_write	equ 1
sys_exit	equ 60
success		equ 0
error		equ 1
endline		equ 10


%macro write 3
	mov eax, sys_write
	mov edi, %1
	lea rsi, [%2]
	mov edx, %3
	syscall
%endmacro

global ft_hello

section .rodata
	msg db "Hola Mundo!!!", endline
	msg_len equ $ - msg	

section .text

ft_hello:
	write stdout, msg, msg_len
	cmp eax, 0
	jl .exit_error
	xor rax, rax
	ret

.exit_error:
	mov rax, -1
	ret

section .note.GNU-stack noalloc noexec nowrite progbits