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
mov eax,9
mov ebx,0
mov edx,0
cmp eax,ebx
jge h1
mov [high],ebx
mov [low],eax
mov eax,[high]
mov ecx,[low]
less1:
mov ebx,[revarr+(4*ecx)]
mov [arr+(4*edx)],ebx
inc ecx
inc edx
cmp ecx,eax
jl less1
jmp h2
h1:
mov [high],eax
mov [low],ebx
mov ecx,[high]
mov eax,[low]
less2:
mov ebx,[revarr + (4*ecx)]
mov [arr+(4*edx)],ebx
dec ecx
inc edx
add ax,1
cmp eax,ecx
jl less2
h2:
mov eax, 1
 mov ebx, 0
int 80h
section .data
arr TIMES 10 dd 0
revarr TIMES 10 dd 0
high TIMES 1 dd 0
low TIMES 1 dd 0
