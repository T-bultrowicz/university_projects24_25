#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

typedef struct kolejka {
    int max_rozmiar;
    int d_kol;
    int g_kol;
    int* elem;
} kolejka;

kolejka stworz_kolejka(int n) {
    kolejka a;
    a.max_rozmiar = n + 1;
    a.d_kol = 0;
    a.g_kol = -1;
    a.elem = (int*) malloc((unsigned) (n + 1) * sizeof(int));
    return a;
}

bool czy_pusta(kolejka* a) {
    return a->d_kol == a->g_kol + 1;
}

int look(kolejka* a) {
    assert(!czy_pusta(a));
    return a->elem[a->d_kol];
}

void mov(kolejka* a) {
    assert(!czy_pusta(a));
    a->d_kol++;
    a->d_kol %= a->max_rozmiar;
    return;
}
void push(kolejka* a, int b) {
    assert(a->g_kol + 1 != a->d_kol + a->max_rozmiar);
    a->elem[(++a->g_kol) % a->max_rozmiar] = b;
    if(a->g_kol >= a->max_rozmiar) {
        a->g_kol -= a->max_rozmiar;
    }
    return;
}
void destroy(kolejka* a) {
    free(a->elem);
    return;
}

int main() {
    kolejka a = stworz_kolejka(250);
    for(int i = 0; i < 10; i++) {
        if(i % 3 == 0 || i%3 == 1) {
            push(&a, i);
        } else {
            mov(&a);
        }
        if(!czy_pusta(&a)) {
            printf("%d\n", look(&a));
        }
    }
    return 0;
}
