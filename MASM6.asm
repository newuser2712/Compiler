	section .bss
main resd 1
S2 resd 1
b1 resd 1
section .text
		global _start
_start:
lea si,[S2]
lea di,[S1]
b1:
inc di
lodsb
cmp [di], al
jg NotEqual
cmp al, 0
jne b1
mov eax,0
mov [b1], eax
jmp final
NotEqual:
mov eax,1
mov [b1], eax
final:
mov eax, 4
mov ebx, 1
mov ecx, S1
mov edx, len0
int 80h
mov eax, 48
add [S2], eax
mov eax, 4
mov ebx, 1
mov ecx, S2
mov edx, 5
int 80h
mov eax, 48
sub [S2], eax
mov eax, 48
add [b1], eax
mov eax, 4
mov ebx, 1
mov ecx, b1
mov edx, 5
int 80h
mov eax, 48
sub [b1], eax
mov eax, 1
 mov ebx, 0
int 80h
section .data
S1 db 'New_String$', 0xa
len0 equ $ - S1
