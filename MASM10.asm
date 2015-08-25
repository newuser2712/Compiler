	section .bss
main resd 1
avar resd 1
bvar resd 1
section .text
		global _start
_start:
mov eax,1
mov [avar], eax
mov eax,2
mov [bvar], eax
mov eax,1
cmp [avar],eax
JNE L7
mov eax, 48
add [avar], eax
mov eax, 4
mov ebx, 1
mov ecx, avar
mov edx, 5
int 80h
mov eax, 48
sub [avar], eax
L7:	mov eax, 48
add [bvar], eax
mov eax, 4
mov ebx, 1
mov ecx, bvar
mov edx, 5
int 80h
mov eax, 48
sub [bvar], eax
mov eax, 1
 mov ebx, 0
int 80h
