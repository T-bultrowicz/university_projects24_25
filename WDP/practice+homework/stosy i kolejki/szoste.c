#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

int mini(int a,int b) {
    return (a < b) ? a : b;
}

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

int* widoczne(int s, int* t) {
    int* res = malloc((unsigned) s * sizeof(int));
    int acc;
    stos male = stworz_stos(s + 1);
    stos il_pow = stworz_stos(s + 1);
    push(&male, __INT_MAX__);
    push(&il_pow, 0);
    for(int i = 0;i < s; i++) {
        acc = 0;
        while(t[i] > top(&male)) {
            acc += top(&il_pow);
            pop(&il_pow);
            pop(&male);
        }
        if(t[i] == top(&male)) {
            acc += top(&il_pow);
            acc += mini(1, il_pow.elem[il_pow.akt_rozmiar - 1]);
            il_pow.elem[il_pow.akt_rozmiar]++;
        } else {
            acc += mini(1, top(&il_pow));
            push(&male,t[i]);
            push(&il_pow,1);
        }
        res[i] = acc;
    }
    destroy(&male);
    destroy(&il_pow);
    male = stworz_stos(s + 1);
    il_pow = stworz_stos(s + 1);
    push(&male, __INT_MAX__);
    push(&il_pow, 0);
    for(int j = s - 1; j >= 0; j--) {
        acc = 0;
        while(t[j] > top(&male)) {
            acc += top(&il_pow);
            pop(&il_pow);
            pop(&male);
        }
        if(t[j] == top(&male)) {
            acc += top(&il_pow);
            acc += mini(1, il_pow.elem[il_pow.akt_rozmiar - 1]);
            il_pow.elem[il_pow.akt_rozmiar]++;
        } else {
            acc += mini(1, top(&il_pow));
            push(&male,t[j]);
            push(&il_pow,1);
        }
        res[j] += acc;
    }
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
    b_res = widoczne(a, b);
    for(int i = 0; i < a; i++) {
        printf("%d ", b_res[i]);
    }
    free(b);
    free(b_res);
    return 0; 
}
