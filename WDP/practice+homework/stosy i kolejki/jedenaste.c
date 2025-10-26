#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

typedef struct de_lejka {
    int max_rozmiar;
    int d_kol;
    int g_kol;
    int* elem;
} de_lejka;

de_lejka stworz_de_lejka(int n) {
    de_lejka a;
    a.max_rozmiar = n + 1;
    a.d_kol = 1;
    a.g_kol = 0;
    a.elem = (int*) malloc((unsigned) (n + 1) * sizeof(int));
    return a;
}

bool czy_pusta(de_lejka* a) {
    return a->g_kol == a->d_kol - 1;
}

void push_front(de_lejka* a, int b) {
    assert(a->g_kol != a->d_kol + a->max_rozmiar - 1);
    if((--a->d_kol) < 0) {
        a->d_kol += a->max_rozmiar;
        a->g_kol += a->max_rozmiar;
    }
    a->elem[a->d_kol] = b;
    return;
}

void push_back(de_lejka* a, int b) {
    assert(a->g_kol != a->d_kol + a->max_rozmiar - 1);
    if((++a->g_kol) >= 2 * a->max_rozmiar) {
        a -= a->max_rozmiar;
    }
    a->elem[a->g_kol % a->max_rozmiar] = b;
    return;  
}

int look_front(de_lejka* a) {
    assert(!czy_pusta(a));
    return a->elem[a->d_kol];
} 

int look_back(de_lejka* a) {
    assert(!czy_pusta(a));
    return a->elem[a->g_kol % a->max_rozmiar];
}

void pop_front(de_lejka* a) {
    assert(!czy_pusta(a));
    if((++a->d_kol) == a->max_rozmiar) {
        a->d_kol -= a->max_rozmiar;
        a->g_kol -= a->max_rozmiar;
    }
    return;
}

void pop_back(de_lejka* a) {
    assert(!czy_pusta(a));
    a->g_kol--;
    return;
}

void destroy(de_lejka* a) {
    free(a->elem);
    return;
}

int robakolaki(int s, int* t) {
    int lewy = 0, prawy = s - 1;
    int pierwszy = 0;
    int drugi = 0;
    int rowny_counter = 0;
    de_lejka po_walce = stworz_de_lejka(s);
    while(po_walce.g_kol - po_walce.d_kol + prawy - lewy > -1) {
        //wybor najmniejszego
        if(czy_pusta(&po_walce)) {
            pierwszy = t[lewy++];
        } else if(lewy > prawy) {
            pierwszy = look_front(&po_walce);
            pop_front(&po_walce);
        } else {
            if(look_front(&po_walce) < t[lewy]) {
                pierwszy = look_front(&po_walce);
                pop_front(&po_walce);                
            } else {
                pierwszy = t[lewy++];
            }
        }
        //wybor najwiekszego
        if(czy_pusta(&po_walce)) {
            drugi = t[prawy--];
        } else if(lewy > prawy) {
            drugi = look_back(&po_walce);
            pop_back(&po_walce);
        } else {
            if(look_back(&po_walce) < t[lewy]) {
                drugi = look_back(&po_walce);
                pop_back(&po_walce);               
            } else {
                drugi = t[prawy--];
            }
        }
        if(pierwszy != drugi) {
            rowny_counter = 0;
            push_front(&po_walce, drugi - pierwszy);
        } else {
            rowny_counter += 2;
        }
    }
    if(po_walce.g_kol - po_walce.d_kol + prawy - lewy == -1) {
        rowny_counter++;
    }
    destroy(&po_walce);
    return rowny_counter;
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
