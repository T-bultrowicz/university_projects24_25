%ifndef MACRO_PRINT_ASM
%define MACRO_PRINT_ASM

%macro print 2
  jmp     %%begin
%%descr: db %1
%%begin:
  push    %2              ; Wartość do wypisania będzie na stosie. To działa również dla %2 = rsp.
  lea     rsp, [rsp - 16] ; Zrób miejsce na stosie na bufor. Nie modyfikuj znaczników.
  pushf
  push    rax
  push    rcx
  push    rdx
  push    rsi
  push    rdi
  push    r11

  mov     eax, 1                  ; SYS_WRITE
  mov     edi, eax                ; STDOUT
  lea     rsi, [rel %%descr]      ; Napis jest w sekcji .text.
  mov     edx, %%begin - %%descr  ; To jest długość napisu.
  syscall

  mov     rdx, [rsp + 72]         ; To jest wartość do wypisania.
  mov     ecx, 16                 ; Liczba 64-bitowa zawiera 16 cyfr szesnastkowych.
%%next_digit:
  mov al, dl;
  and al, 0xF;
  cmp al, 10;
  jge %%literaASCII
  add al, 48;
  jmp %%poWARUNKU
%%literaASCII:
  add al, 55;
%%poWARUNKU:
  mov     [rsp + rcx + 55], al    ; W al jest kod ASCII cyfry szesnastkowej.
  shr     rdx, 4                  ; Przesuń rdx w prawo o jedną cyfrę.
  loop    %%next_digit            ; Każda iteracja pętli przetwarza jedną cyfrę.

  mov     [rsp + 72], byte `\n`   ; Zakończ znakiem nowej linii. Intencjonalnie
                                  ; nadpisuje na stosie niepotrzebną już wartość.

  mov     eax, 1                  ; SYS_WRITE
  mov     edi, eax                ; STDOUT
  lea     rsi, [rsp + 56]         ; Bufor z napisem jest na stosie.
  mov     edx, 17                 ; Napis ma 17 znaków.
  syscall

  pop     r11
  pop     rdi
  pop     rsi
  pop     rdx
  pop     rcx
  pop     rax
  popf
  lea     rsp, [rsp + 24]
%endmacro

%endif