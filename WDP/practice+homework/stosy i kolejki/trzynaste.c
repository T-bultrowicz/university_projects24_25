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

int nawiasy(int s, char* t) {
    int* tab_rozmiary = malloc((unsigned) s * sizeof(int));
    int* tab_indeksy = malloc((unsigned) s * sizeof(int));
    int res = 0;
    for(int i = 0; i < s; i++) {
        tab_indeksy[i] = -1;
    }
    stos naw = stworz_stos(s);
    for(int j = 0; j < s; j++) {
        if(czy_pusty(&naw)) {
            if(t[j] == '(') {
                push(&naw, 1);
            } else {
                push(&naw, 0);
            }
        } else if(top(&naw) == 0 && t[j] == ')') {
            pop(&naw);
        } else {
            if(t[j] == '(') {
                push(&naw, 1);
            } else {
                push(&naw, 0);
            }          
        }
        tab_rozmiary[j] = naw.akt_rozmiar + 1;
        for(int kol = 0; kol <= naw.akt_rozmiar; kol++) {
            printf("%d ", naw.elem[kol]);
        } 
        printf("\n");
    }
    printf("\n");
    for(int k = 0;k < s; k++) {
        if(tab_indeksy[tab_rozmiary[k]] == -1) {
            tab_indeksy[tab_rozmiary[k]] = k;
        } else {
            if(res < k - tab_indeksy[tab_rozmiary[k]]) {
                res = k - tab_indeksy[tab_rozmiary[k]];
            }
        }
    }
    for(int z = 0; z < s; z++) {
        printf("%d   %d   %d\n",z, tab_indeksy[z], tab_rozmiary[z]);
    }
    destroy(&naw);
    free(tab_indeksy);
    free(tab_rozmiary);
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    char* b = malloc((unsigned) a * sizeof(char));
    for(int i = 0;i < a; i++) {
        if(scanf("%c", b + i) != 1) {
            return -1;
        }
    }
    printf("%d", nawiasy(a, b));
    free(b);
    return 0;
}