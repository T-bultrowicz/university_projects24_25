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

int robakolaki(int s, int* t) {
    kolejka po_walce = stworz_kolejka(s);
    int i = 0;
    int pierwszy, drugi;
    while(s - i + po_walce.g_kol - po_walce.d_kol + 1 > 1) {
        if(czy_pusta(&po_walce)) {
            pierwszy = t[i++];
        } else if(i < s){
            if(look(&po_walce) < t[i]) {
                pierwszy = look(&po_walce);
                mov(&po_walce);
            } else {
                pierwszy = t[i++];
            }
        } else {
                pierwszy = look(&po_walce);
                mov(&po_walce);            
        }
        if(czy_pusta(&po_walce)) {
            drugi = t[i++];
        } else if(i < s){
            if(look(&po_walce) < t[i]) {
                drugi = look(&po_walce);
                mov(&po_walce);
            } else {
                drugi = t[i++];
            }
        } else {
                drugi = look(&po_walce);
                mov(&po_walce);
        }
        if(pierwszy == drugi) {
            t[--i] = pierwszy - 1;
        } else if(pierwszy + drugi - 1) {
            push(&po_walce, pierwszy + drugi - 1);
        }
        for(int l = po_walce.d_kol; l <= po_walce.g_kol; l++) {
            printf("%d ", po_walce.elem[l]);
        }
        printf("\n");
    }
    destroy(&po_walce);
    if(i < s) {
        return t[i];
    } else {
        return look(&po_walce);
    }
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
    printf("%d", robakolaki(a, b));
    free(b);
    return 0;
}
