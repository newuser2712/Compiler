section .text
		global _start
_start:
lea si,[string1]                           ;ds:si points to first string
lea di,[string2]                           ;ds:di points to second string
dec di                                    
 
lab1:
inc di                                       ;ds:di -> next character in string2
lodsb       
                                ;load al with next char from string 1
                                               ;note: lodsb increments si automatically
cmp [di], al                               ;compare characters
jg NotEqual                             ;jump out of loop if they are not the same
 
cmp al, 0                                  ;they are the same, but end of string?
jne lab1                                    ;no - so go round loop again
 
;-----------------------------------------------------------------------------
;end of string, and the "jne NotEqual" instruction hasn't been executed so they're equal
;-----------------------------------------------------------------------------

mov eax,0					;assign here for equal

jmp final 

NotEqual:

mov eax,1					;assign here for not equal
 
final:

section	.data
 
string1 db 'Strings are equal$',0xa
len1 equ $ - string1    

string2 db 'Strings are not equal$',0xa
len2 equ $ - string2


