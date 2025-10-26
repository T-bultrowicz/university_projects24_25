%include "MACRO_PRINT_ASM.asm"
global mac2
section .text
    ;wyniki w r9 i r10, potem przenoszone odpowiednio
    mac2:
        ;przeniesienie pointera
        mov r8, rdx
        ;wczytanie mnozenia male*male
        mov rax, [r8]
        mov rdx, [rsi]
        mul rdx
        mov r10, rdx
        mov r9, rax
        ;wczytanie mnozenia male*duze
        mov rax, [r8 + 8]
        mov rdx, [rsi]
        mul rdx
        add r10, rax
        ;wczytanie mnozenia duze*male
        mov rax, [r8]
        mov rdx, [rsi + 8]
        mul rdx
        add r10, rax
        ;dodanie   
        add r9, [rdi]
        adc r10, [rdi + 8]
        ;przenoszenie wyniku
        mov [rdi], r9
        mov [rdi + 8], r10
        ret


