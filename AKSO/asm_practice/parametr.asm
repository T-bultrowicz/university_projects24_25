%include "MACRO_PRINT_ASM.asm"
global _start
section .data
SYS_EXIT equ 60
CORRECT_EXIT equ 0
SYS_WRITE equ 1

section .text
    _start:
        mov rcx, [rsp]
        mov rax, [rsp + 8 * rcx]
        xor rcx, rcx
        xor rdx, rdx
        .POCZ_PETLI:
            mov byte dl, [rax + rcx]
            cmp dl, 0
            je .KONIEC_PETLI
            inc rcx
            jmp .POCZ_PETLI
        .KONIEC_PETLI:
        print "rcx = ", rcx
        mov rax, SYS_EXIT
        mov rdi, CORRECT_EXIT
        syscall