	section .bss
a resd 1
first resd 1
y resd 1
b resd 1
second resd 1
z resd 1
a resd 1
b resd 1
main resd 1
c resd 1
section .text
		global _start
_start:
mov eax,1
mov [a], eax
mov eax,2
mov [b], eax
mov eax,2
mov [a], eax
mov eax, 48
add [a], eax
mov eax, 4
mov ebx, 1
mov ecx, a
mov edx, 5
int 80h
mov eax, 48
sub [a], eax
mov eax, 1
 mov ebx, 0
int 80h
