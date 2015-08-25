	section .bss
main resd 1
i resd 1
section .text
		global _start
_start:
mov eax,0
mov [i], eax
mov ecx,10
L2:
mov ebx,[i]
mov ecx,[i]
mov [arr+4*ecx],ebx
mov eax,1
add [i],eax
mov eax,[i]
mov [i], eax
mov ecx,10
mov edx,[i]
cmp edx,ecx
JL L2
mov eax, 1
 mov ebx, 0
int 80h
section .data
arr TIMES 10 dd 0
high TIMES 1 dd 0
low TIMES 1 dd 0
