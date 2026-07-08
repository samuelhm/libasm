stdout		equ 1
sys_write	equ 1
sys_exit	equ 60
success		equ 0
error		equ 1
endline		equ 10

%macro write 3
	mov eax, sys_write
	mov edi, %1
	mov rsi, %2
	mov edx, %3
	syscall
%endmacro
%macro exit 1
	mov eax, sys_exit
	mov edi, %1
	syscall
%endmacro

global _start

section .rodata
	msg db "Hola Mundo!!!", endline
	msg_len equ $ - msg	

section .text

_start:
	write stdout, msg, msg_len
	cmp eax, 0
	jl .exit_error
	exit success

.exit_error:
	exit error
