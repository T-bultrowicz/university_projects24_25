global counter
section .data
counterd: dq 0
section .text
    counter:
        mov rax, [rel counterd]
        inc rax
        mov [rel counterd], rax
        ret