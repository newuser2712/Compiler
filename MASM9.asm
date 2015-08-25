	section .bss
main resd 1
a1 resd 1
a2 resd 1
b1 resd 1
b2 resd 1
section .text
		global _start
_start:
mov eax,1
mov [a1],eax
mov eax,2
mov [a2],eax
mov eax,1
mov [b1],eax
mov eax,2
mov [b2],eax
mov eax,[b1];11
add [a2],eax
mov eax,[a2]
mov [a1], eax
mov eax, 1
 mov ebx, 0
int 80h
