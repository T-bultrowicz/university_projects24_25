%include "MACRO_PRINT_ASM.asm"
section .rodata
strg: db `Hello world!\n`
section .data
pointerwypis: dq 1
SYSWRITE equ 1

section .text
    global wywolaj
    extern printf
    wywolaj:
        mov [rel pointerwypis], rdi
        xor rax, rax
        lea rdi, [rel strg]
        sub rsp, 8
        call [rel printf wrt ..got]
        add rsp, 8
        xor rcx, rcx
        mov rsi, [rel pointerwypis]

        .POCZ_PETLI:
            mov al, [rsi + rcx]
            cmp al, 0
            je .KONIEC_PETLI
            inc rcx
            jmp .POCZ_PETLI
        
        .KONIEC_PETLI:
        ;wywolanie syswrite hello world!
        mov rax, SYSWRITE
        mov rdi, SYSWRITE
        mov rsi, [rel pointerwypis]
        mov rdx, rcx
        syscall

        ret
        