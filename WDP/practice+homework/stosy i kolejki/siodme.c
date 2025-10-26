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

int manhattan_skyline(int s, int* t) {
    int res = 0;
    int* pom = malloc((unsigned) s * sizeof(int));
    stos indeksy = stworz_stos(s + 1);
    stos wartosci = stworz_stos(s + 1);
    push(&wartosci, -1);
    push(&indeksy, -1);
    for(int i = 0;i < s; i++) {
        while(t[i] < top(&wartosci)) {
            pop(&wartosci);
            pop(&indeksy);
            pom[i] = i - top(&indeksy);
        }
        if(t[i] != top(&wartosci)) {
            push(&wartosci, t[i]);
            push(&indeksy, i);
        } else {
            pom[i] = i - top(&indeksy) + 1;
        }
        if(!pom[i]) {
            pom[i] = 1;
        }
    }
    destroy(&indeksy);
    destroy(&wartosci);
    indeksy = stworz_stos(s + 1);
    wartosci = stworz_stos(s + 1);
    int meanwhile;
    push(&wartosci, -1);
    push(&indeksy, -1);    
    for(int j = s - 1; j >= 0; j--) {
        meanwhile = 0;
        while(t[j] < top(&wartosci)) {
            pop(&wartosci);
            pop(&indeksy);
            meanwhile = top(&indeksy) - j - 1;
        }
        if(t[j] != top(&wartosci)) {
            push(&wartosci, t[j]);
            push(&indeksy, j);
            pom[j] += meanwhile;
        } else {
            pom[j] += top(&indeksy) - j;       
        }
        if(pom[j] * t[j] > res) {
            res = pom[j] * t[j];
        }       
    }
    destroy(&wartosci);
    destroy(&indeksy);
    free(pom);
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
    printf("%d", manhattan_skyline(a, b));
    free(b);
    return 0;
}
