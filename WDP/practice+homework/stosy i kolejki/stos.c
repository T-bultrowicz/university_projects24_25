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

int main() {
    stos a = stworz_stos(250);
    for(int i = 100; i >= 0; i--) {
        push(&a, i);
        if(i % 10 == 0) {
            pop(&a);
        }
        if(i % 17 == 0) {
            printf("%d\n", top(&a));
        }
    }
    for(int j = 0; j <= a.akt_rozmiar; j++) {
        printf("%d  ",top(&a));
        pop(&a);
    }
    destroy(&a);
    return 0;
}
