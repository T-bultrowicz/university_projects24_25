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

int jeziora(int s, int* t) {
    int res = -1;
    stos gory = stworz_stos(s);
    stos indeksy = stworz_stos(s);
    for(int i = 0;i < s; i++) {
        while(gory.akt_rozmiar > 1) {
            if(t[i] >= top(&gory)) {
                pop(&gory);
                pop(&indeksy);
            } else {
                break;
            }
        }
        if(gory.akt_rozmiar >= 1) {
            if(t[i] != top(&gory)) {
                if(res < i - top(&indeksy)) {
                    res = i - top(&indeksy);
                }
            }
        }
        while(!czy_pusty(&gory)) {
            if(t[i] > top(&gory)) {
                pop(&gory);
                pop(&indeksy);
            } else {
                break;
            }
        }
        push(&gory,t[i]);
        push(&indeksy,i);
        for(int k = 0;k <= gory.akt_rozmiar; k++) {
            printf("%d ", gory.elem[k]);
        }
        printf("\n");
    }
    destroy(&gory);
    destroy(&indeksy);
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int* b = malloc((unsigned) a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d", b + i) != 1) {
            return -1;
        }
    }
    printf("%d", jeziora(a, b));
    free(b);
    return 0;
}
