global caller
section .text
    caller:
        mov rax, rdi
        mov edi, esi
        sub rsp, 8
        call rax
        add rsp, 8
        ret