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


int segment(int s, int* t) {
    de_lejka ind = stworz_de_lejka(s);
    int l = 0, p = 1;
    push_back(&ind, 0);
    int res = 0;
    while(p < s) {
        if(l == p || t[look_front(&ind)] >= p - l) {
            if(p - l > res) {
                res = p - l;
            }
            while(!czy_pusta(&ind)) {
                if(t[p] < t[look_back(&ind)]) {
                    pop_back(&ind);
                } else {
                    break;
                }
            }
            push_back(&ind, p);
            p++;
        } else {
            if(l++ == look_front(&ind)) {
                pop_front(&ind);
            }
        }
    }
    if(t[look_front(&ind)] >= p - l) {
        if(p - l > res) {
            res = p - l;
        }
    }
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
    printf("%d", segment(a, b));
    free(b);
    return 0;
}
