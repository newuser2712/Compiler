	section .bss
main resd 1
arr resd 1
i resd 1
revarr resd 1
section .text
		global _start
_start:
mov eax,0
mov [i], eax
mov ecx,10
L2:
mov eax,1
add [i],eax
mov eax,[i]
mov [i], eax
mov ecx,10
mov edx,[i]
cmp edx,ecx
JL L2
mov ecx,10
L9:
mov eax, 48
add [(null)], eax
mov eax, 4
mov ebx, 1
mov ecx, (null)
mov edx, 5
int 80h
mov eax, 48
sub [(null)], eax
mov eax,1
add [i],eax
mov eax,[i]
mov [i], eax
mov ecx,10
mov edx,[arr]
cmp edx,ecx
JL L9
mov eax, 1
 mov ebx, 0
int 80h
