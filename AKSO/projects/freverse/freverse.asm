; --- DEKLARACJE STAŁYCH ---
SYS_OPEN   equ  2    ; FUNKCJE SYSTEMOWE
SYS_CLOSE  equ  3 
SYS_FSTAT  equ  5
SYS_MMAP   equ  9
SYS_MUNMAP equ  11
SYS_MSYNC  equ  26
SYS_EXIT   equ  60
PG_SHARED  equ  1    ; KODY FLAG I OPCJI
OPEN_RW    equ  2
PG_RW      equ  3
OFF_FTYPE  equ  24   ; POLA STRUCT STAT
OFF_FSIZE  equ  48
QWRD_I_PG  equ  512  ; STAŁE ROZMIARU STRON
PG_SIZE    equ  4096
PG_2SIZE   equ  8192
; --- KONIEC DEKLARACJI  ---

section .text
; ----- MAKRA -----
; Analogiczne do memcpy z C, ale ma stale ustawiony ostatni parametr na 4096.
; Czyli przenosi 4096 bajtów z %1 do %2. Modyfikuje: rsi, rdi, rcx
%macro memcpy 2
    cld                                  ; for(int i = 0; i < 512; i++)
    lea     rsi, %1                      ;    (uint64_t) dest[i]      
    lea     rdi, %2                      ;          = (uint64_t) src[i];            
    mov     rcx, 512                     ;                  
    rep     movsq                        ;               
%endmacro
; -- KONIEC MAKR

global _start
; Funkcja odwracająca plik. Poza wywołaniami systemowymi 
;                                    rejestry używane są następująco:
; ----
; r8, r9 - brzeg lewy i prawy odwracania pliku
; r12, r13, r14 - informacje o pliku i adresy !CONST! wewnątrz programu
; r10, rdi - iteracje po pętlach (rcx zabiera memcpy)
; rsi, rcx, rdx - tymczasowe pomocnicze
; ----
; Oznaczenia na rejestry w komentarzach:
; l := r8, r := r9, fd := r12, f_size := r13, f_ptr := r14, i := r10, j := rdi
; rcx := tmp_a, rdx := tmp_b, rax := res
_start:                                  ; Komentarze w C/pseudokodzie:
    push    r12                          ; Prolog, zapisujemy na stosie
    push    r13                          ;      rejestry callee saved.
    push    r14                          ;
    sub     rsp, 8                       ;
          
    mov     rax, [rsp + 32]              ; Spradzamy il. argumentów.
    cmp     rax, 2                       ; if (argc != 2) return 1;
    jne     .one_exit                    ; 
    mov     rax, SYS_OPEN                ; Następnie otwieramy plik:
    mov     rdi, [rsp + 48]              ; res = open(argv[1], O_RDWR);                       
    mov     rsi, OPEN_RW                 ;                      
    syscall                              ; if (res <= -1 && res >= -4096)
    cmp     rax, -4096                   ;     return 1;
    ja      .one_exit                    ; fd = res;     
    mov     r12, rax                     ;

    sub     rsp, 144                     ; Sprawdzamy rozmiar i typ pliku.
    mov     rax, SYS_FSTAT               ; res = fstat(fd, &rsp);                       
    mov     rdi, r12                     ;                  
    mov     rsi, rsp                     ;                  
    syscall                              ; if (res < 0) {
    test    rax, rax                     ;    close(fd);
    js      .one_fclose                  ;    return 1;                 
    mov     rax, [rsp + OFF_FTYPE]       ; }                                                      
    and     rax, 0xF000                  ; Badamy typ pliku, nie klasyczny,
    cmp     rax, 0x8000                  ; powoduje błąd. Wykonujemy close() i
    jne     .one_fclose                  ; zwracamy 1. Nast. badamy rozmiar:
    mov     r13, [rsp + OFF_FSIZE]       ; f_size = rsp.st_size;              
    cmp     r13, 2                       ; if (f_size < 2) {
    jb      .zero_fclose                 ;    close(fd);     
    add     rsp, 144                     ;    return 1;    
                                         ; }
    mov     rax, SYS_MMAP                ; Mapujemy plik do pamięci wirtualnej.
    xor     rdi, rdi                     ; res = mmap(NULL, f_size, PROT_READ
    mov     rsi, r13                     ;  | PROT_WRITE, MAP_SHARED, fd, 0);
    mov     rdx, PG_RW                   ;                    
    mov     r10, PG_SHARED               ;                        
    mov     r8, r12                      ;                 
    xor     r9, r9                       ; if (res <= -1 && res >= -4096) { 
    syscall                              ;    close(fd);
    cmp     rax, -4096                   ;    return 1;
    ja      .one_fclose                  ; }       
    mov     r14, rax                     ; f_ptr = res;     
    
    xor     rdi, rdi                     ; Robimy prefetch, aby zminimalizować
    lea     r10, [r13 - 1]               ;    major page faults. Ładujemy do i
    shr     r10, 12                      ; ilość str programu - 1.
.prefetch_loop:                          ; j = 0, i = (f_size - 1) >> 12;
    mov     cl, [r14 + rdi]              ; while (i >= 0) { 
    add     rdi, PG_SIZE                 ;     tmpA = (char) f_ptr[j];     
    dec     r10                          ;     j += PG_SIZE; i--;
    jns     .prefetch_loop               ; } 
                          
    mov     r9, r13                      ; Pętla wczytująca z pliku do buforów,
    xor     r8, r8                       ; char buff1[4096], buff2[4096] (stos)
    lea     r10, [r13 - PG_2SIZE]        ; l = 0, r = f_size,
    test    r10, r10                     ;               i = f_size - PG_SIZE
    js      .small_loop                  ; Jeśli i < 0 skaczemy do pętli 
    shr     r10, 13                      ;    obracającej pojedynczymi bajtami.
    sub     rsp, PG_2SIZE                ; i >>= 13; (i / 8192) - uzyskujemy
.big_loop:                               ; wymaganą ilość obrotów buforem.
    sub     r9, PG_SIZE                  ; while (i >= 0) {       
    memcpy  [r14 + r8], [rsp]            ;     r -= PG_SIZE;           
    memcpy  [r14 + r9], [rsp + PG_SIZE]  ;     memcpy(f_ptr + l, buff1, 4096);                
    mov     rdi, 4095                    ;     memcpy(f_ptr + r, buff2, 4096);
    xor     rsi, rsi                     ;    
.rvrs_loop:                              ;     for (int k = 0; k < 4096; k++) {
    mov     cl, [rsp + rdi + PG_SIZE]    ;        tmpA = buff2[4096 - k - 1];             
    mov     dl, [rsp + rsi]              ;        tmpB = buff1[k];
    mov     [rsp + rdi + PG_SIZE], dl    ;        buff2[4096 - k - 1] = tmpB;           
    mov     [rsp + rsi], cl              ;        buff1[k] = tmpA;
    inc     rsi                          ;     }
    dec     rdi                          ;            
    jns     .rvrs_loop                   ;                    
    memcpy  [rsp], [r14 + r8]            ;    memcpy(buff1, f_ptr + l, 4096);                     
    memcpy  [rsp + PG_SIZE], [r14 + r9]  ;    memcpy(buff2, f_ptr + r, 4096);  
    add     r8, PG_SIZE                  ;    l += PG_SIZE;          
    dec     r10                          ;    i--;
    jns     .big_loop                    ; }            
    add     rsp, PG_2SIZE                ; Gdy l == r, nie obracamy bajt                     
                                         ;               za bajt.
    cmp     r8, r9                       ; if (l == r) {
    je      .zero_fclose                 ;     close(fd);
.small_loop:                             ;     return 0;       
    dec     r9                           ; }         
    mov     cl, [r14 + r8]               ; Obracamy pozostałe bajty.                       
    mov     dl, [r14 + r9]               ; while(l <= r) {                          
    mov     [r14 + r8], dl               ;      tmpA = f_ptr[l];   
    mov     [r14 + r9], cl               ;      tmpB = f_ptr[r];   
    inc     r8                           ;      f_ptr[l++] = tmpB;
    cmp     r8, r9                       ;      f_ptr[r++] = tmpA;         
    jb      .small_loop                  ; }     

    mov     rax, SYS_MUNMAP              ;  Kończymy procedurę - munmap                      
    mov     rdi, r14                     ;  res = munmap(f_ptr, f_size);
    mov     rsi, r13                     ;  if(res < 0) {
    syscall                              ;      close(fd);
    test    rax, rax                     ;      return 1;  
    js      .one_fclose                  ;  }      
.zero_fclose:                            ;           
    mov     rax, SYS_CLOSE               ;  close(fd);                     
    mov     rdi, r12                     ;  Fragmenty kodu odpowiedzialne    
    syscall                              ;  za zamykanie programu. Skok do nich
    test    rax, rax                     ;  naprawdę wykonuje się w miejscach,
    js      .one_exit                    ;  gdzie opisany jest return/close.
    xor     rdi, rdi                     ;  Działają analogicznie do tych
    jmp     .exit                        ;              funkcji z C.
.one_fclose:                             ; 
    mov     rax, SYS_CLOSE               ;                        
    mov     rdi, r12                     ;                  
    syscall                              ;         
.one_exit:                               ;        
    mov     rdi, 1                       ;                
.exit:                                   ; Epilog - przyracanie wartości
    add     rsp, 8                       ;     rejestrów callee saved.  
    pop     r14
    pop     r13
    pop     r12
    mov     rax, SYS_EXIT
    syscall


