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

void inc_zekendorf(int s, bool* t) {
    de_lejka add = stworz_de_lejka(s), res = stworz_de_lejka(s + 1);
    int p, d;
    for(int i = 0;i < s; i++) {
        push_front(&add, (int) t[i]);
    }
    if(look_front(&add) == 1) {
        push_front(&res, 0);
        pop_front(&add);
        pop_front(&add);
        push_front(&add, 1);       
    } else {
        pop_front(&add);
        push_front(&add, 1);
    }
    while(!czy_pusta(&add)) {
        d = -1;
        p = look_front(&add);
        pop_front(&add);
        if(!czy_pusta(&add)) {
            d = look_front(&add);
            pop_front(&add);
        }
        if(p + d < 2) {
            push_front(&res, p);
            if(d != -1) {
                push_front(&res, d);
            }
        } else {
            push_front(&res, 0);
            push_front(&res, 0);
            pop_front(&add);
            push_front(&add, 1);
        }
    }
    int l = 0;
    while(!czy_pusta(&res)) {
        t[l++] = look_front(&res);
        pop_front(&res);
    }
    destroy(&add);
    destroy(&res);
    return;
}


int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    bool* b = malloc((unsigned) (a + 1) * sizeof(bool));
    int k;
    for(int i = 0;i < a; i++) {
        if(scanf("%d", &k) != 1) {
            return -1;
        }
        b[i] = k ? true : false;
    }
    inc_zekendorf(a, b);
    for(int i = 0; i < a; i++) {
        printf("%d ", b[i]);
    }
    free(b);
    return 0;
}
