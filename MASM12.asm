	section .bss
main resd 1
S2 resd 1
section .text
		global _start
_start:
mov eax, 4
mov ebx, 1
mov ecx, S1
mov edx, len0
int 80h
mov eax, 1
 mov ebx, 0
int 80h
section .data
S1 db 'New_String$', 0xa
len0 equ $ - S1
