	section .bss
main resd 1
a1 resd 1
a2 resd 1
b1 resd 1
b2 resd 1
avar resd 1
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
mov eax,0
cmp [avar],eax
JNE L7
mov eax,0
cmp [bvar],eax
JNE L7
