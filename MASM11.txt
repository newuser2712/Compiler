	section .bss
main resd 1
i resd 1
section .text
		global _start
_start:
mov eax,0
mov [i], eax
mov ecx,10
L1:
mov eax, 48
add [i], eax
mov eax, 4
mov ebx, 1
mov ecx, i
mov edx, 5
int 80h
mov eax, 48
sub [i], eax
mov eax,1
add [i],eax
mov eax,[i]
mov [i], eax
mov ecx,10
mov edx,[i]
cmp edx,ecx
JL L1
mov eax, 1
 mov ebx, 0
int 80h
