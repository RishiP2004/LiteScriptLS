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
    mov dword [a], 5
    mov dword [b], 10
    mov eax, [a]
    add eax, [b]
    mov dword [c], eax
    mov eax, [c]
    push eax
    push output_format
    call printf
    add esp, 8
    mov eax, 1
    xor ebx, ebx
    int 0x80
