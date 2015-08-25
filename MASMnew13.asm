	section .bss
main resd 1
b1 resd 1
section .text
		global _start
_start:
mov ecx,0
mov edx,0
b7:
mov al,[S2+(1*ecx)]
mov bl,[S1+(1*edx)]
inc ecx
inc edx
cmp bl, al
jg NotEqual
cmp al, 0
jne b7
mov eax,0
mov [b1], eax
jmp final
NotEqual:
mov eax,1
mov [b1], eax
final:
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
S2 db 'Old_String$', 0xa
len1 equ $ - S2
high TIMES 1 dd 0
low TIMES 1 dd 0
