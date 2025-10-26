#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

typedef struct stos {
    int max_rozmiar;
    int akt_rozmiar;
    int* elem;
} stos;

stos stworz_stos(int n) {
    stos a;
    a.max_rozmiar = n;
    a.akt_rozmiar = -1;
    a.elem = (int*) malloc((unsigned) n * sizeof(int));
    return a;
}

bool czy_pusty(stos* a) {
    return a->akt_rozmiar == -1;
}

int top(stos* a) {
    assert(!czy_pusty(a));
    return a->elem[a->akt_rozmiar];
}

void pop(stos* a) {
    assert(!czy_pusty(a));
    a->akt_rozmiar--;
    return;
}
void push(stos* a, int b) {
    assert(a->akt_rozmiar < a->max_rozmiar - 1);
    a->elem[++a->akt_rozmiar] = b;
    return;
}
void destroy(stos* a) {
    free(a->elem);
}

int* katastrofy_lotnicze(int s, int* t) {
    int* res = malloc((unsigned) s * sizeof(int));
    stos wysokie = stworz_stos(s + 1);
    stos indeksy = stworz_stos(s + 1);
    int meanwhile;
    push(&wysokie, __INT_MAX__);
    push(&indeksy, -1);
    for(int i = 0;i < s; i++) {
        while(t[i] > top(&wysokie)) {
            pop(&wysokie);
            pop(&indeksy);
        }
        res[i] = i - top(&indeksy);
        if(t[i] != top(&wysokie)) {
            push(&wysokie, t[i]);
            push(&indeksy, i);
        }
    }
    destroy(&wysokie);
    destroy(&indeksy);
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int* b = malloc((unsigned) a * sizeof(int));
    int* b_res = malloc((unsigned) a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d", b + i) != 1) {
            return -1;
        }
    }
    b_res = katastrofy_lotnicze(a, b);
    for(int i = 0; i < a; i++) {
        printf("%d ", b_res[i]);
    }
    free(b);
    free(b_res);
    return 0;    
}
