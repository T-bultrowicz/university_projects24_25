FIT_IN_RESZTA   equ 1
NFIT_IN_RESZTA  equ 0

section .bss
align 8
pointerT_n:     resq 8000

; Funkcje jakie pełnią rejestry wewnątrz całej sekcji .text,
;                      czyli funkcji nsqrt i makr pom. dla nsqrt:
; ---
; rds, rsi, rdx - !CONST! - parametry przekazane funkcji
; rcx - iteracja po głównej pętli,   r10 - iteracja po pętlach makr
; r8, r9 - zmienne tymczasowe zachowywane w makrach, rax, r11 - tymczasowe
; ---
; Oznaczenia na rejestry w komentarzach:
; i := rcx, j := r10, k := r9, ptrR := rsi, ptrT := r8, ptrQ := rdi, n := rdx
; ---  
section .text
global nsqrt

; --- MAKRA ---

%macro ustawObroty 1
    mov         %1, rdx                     ; res := %1
    shr         %1, 5                       ; Wykonuje operację:
    dec         %1                          ; res = (n >> 5) - 1;                                                             
%endmacro                                                  

; Porównuje dwie wielobajtowe liczby R_n, T_n. 
; Zwraca wynik do zmiennej wynikPorownuj, 1 gdy R_n >= T_n, 0 wpp.
; Modyfikuje: r10, r11      Wykorzystuje: rsi, r8
%macro porownujR_nT_n 0
    ustawObroty r10
%%petla:                                    ;  for ( ; j >= 0; j--) {
    mov         r11, [rsi + r10 * 8]        ;    if (ptrR[j] > ptrT[j]) {
    cmp         r11, [r8 + r10 * 8]         ;        wynikPorownuj = true;
    ja          %%aboveeq                   ;        return;
    jb          %%belov                     ;    } else if (ptrT[j] > ptrR[j]) {         
    dec         r10                         ;        wynikPorownuj = false;
    jns         %%petla                     ;        return;
%%aboveeq:                                  ;    } 
    mov         al, FIT_IN_RESZTA           ;  }
    jmp         %%end                       ;  wynikPorownuj = true;                      
%%belov:                                    ;  return;          
    mov         al, NFIT_IN_RESZTA          ;
%%end:
%endmacro

; Wykonuje shitf w prawo o 1 bit dla wielobajtowej liczby T_n
; Modyfikuje: r10      Wykorzystuje: r8
%macro shiftT_n 0
    ustawObroty r10
    clc
%%petla:                                    ; for ( ; j >= 0; j--)
    rcr         qword [r8 + r10 * 8], 1     ;    ptrT[j] >>*= 1;                     
    dec         r10                         ;    // gdzie >>* to rcr
    jns         %%petla                     ;
%endmacro

; Wykonuje odejmowanie wielobitowych liczb R_n, T_n, zakłada R_n >= T_n.
; Modyfikuje: r9 (wraca na 2*ecx), r10, r11     Wykorzystuje: rsi, r8
%macro odejmijR_nT_n 0
    ustawObroty r9                          ;                
    mov         r10, 0                      ;
    clc                                     ;
%%petla:                                    ; for ( j = 0; j <= k; j++) {
    mov         r11, [rsi + r10 * 8]        ;    ptrR[j] -= ptrT[j];
    sbb         r11, [r8 + r10 * 8]         ;    ptrR[j] -= borrow;
    mov         [rsi + r10 * 8], r11        ;
    inc         r10                         ;
    dec         r9                          ;    
    jns         %%petla                     ;                

    lea         r9, [ecx * 2]                      
%endmacro

; --- KONIEC MAKR ---      

; Właściwa funkcja licząca zadane Q - pierwiastek X
; Wykorzystuje X (czyli R_n po iteracjach) oraz T jako pamięć roboczą,
; jest to pamięć w adresach rsi oraz pointerT_n
; Modyfikuje: rax, rcx, r8, r9, r10, r11    Wykorzystuje: rdi, rsi, rdx
nsqrt:
    test        rdi, rdi                    ; Sprawdza dane wejsciowe                          
    jz          .bledne_arg                 ; if (ptrQ == null || ptrR == null       
    test        rsi, rsi                    ;                 || n > 256000)             
    jz          .bledne_arg                 ;    return EINVAL;
    mov         edx, edx                    ;     
    cmp         edx, 256000                 ;                               
    ja          .bledne_arg                 ;                               

    ustawObroty rcx                         ;                  
    lea         r8, [rel pointerT_n]        ; Wyczyszcza statyczne dane                                       
.petla_zeruj:                               ;            między wywołaniami
    mov         qword [r8 + rcx * 8], 0     ; for ( ; i >= 0; i--)                                          
    dec         rcx                         ;    ptrT[i] = 0;   
    jns         .petla_zeruj                ;                                
                                            ;    
    mov         ecx, edx                    ;                        
    dec         ecx                         ;                       
                                            ;
.petla:                                     ; Pętla obliczająca wynik iter. -
    lea         r9, [ecx * 2]               ;    schemat w C - pseudokodzie:                     
    bts         [rel pointerT_n], r9        ; for ( ; i >= 0; i--) {                                
                                            ;    ustawBit(T_n, 2*i, 1);
    porownujR_nT_n                          ;    bool x = (R_n >= T_n) ? 1 : 0;    
    cmp         al, FIT_IN_RESZTA           ;    if (x) { ....                                                
    je          .fit_in_reszta              ;                          
                                            ;       
    btr         [rdi], ecx                  ;        ustawBit(Q, i, 0);                        
    jmp         .dalszyciag                 ;    } else { ....                        
.fit_in_reszta:
    bts         [rdi], ecx                  ;        ustawBit(Q, i, 1);    
    odejmijR_nT_n                           ;        R_n -= T_n;                   
.dalszyciag:                                ;    }        
    shiftT_n                                ;    T_n >>= 1;         
    cmp         al, NFIT_IN_RESZTA          ;    if (x)                                                        
    je          .dalej                      ;        ustawBit(T_n, 2*i, 1);                      
                                            ;     
    bts         [r8], r9                    ;                            
.dalej:                                     ;    
    dec         r9                          ;    ustawBit(T_n, 2*i - 1, 0);                     
    btr         [r8], r9                    ;                            
                                            ; }  
    dec         ecx                         ;                       
    jns         .petla                      ; 
.wyjscie_kod0:                              ; Poprawne wyjście.                                 
    mov         rax, 0                         
    ret          
.bledne_arg:                                ; Wyjście z błędem einval.
    mov         rax, -22                        
    ret
        