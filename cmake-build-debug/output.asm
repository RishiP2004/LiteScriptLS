section .data
output_format db "Result: %d", 0
section .bss
a resd 1
b resd 1
c resd 1
section .text
extern printf
global _start
_start:
    mov eax, 5
    mov dword [a], eax
    mov eax, 10
    mov dword [b], eax
    mov eax, dword [a]
    add eax, dword [b]
    mov dword [c], eax
    mov eax, dword [c]
    push eax
    push output_format
    call printf
    add esp, 8
    mov eax, 1
    xor ebx, ebx
    int 0x80
