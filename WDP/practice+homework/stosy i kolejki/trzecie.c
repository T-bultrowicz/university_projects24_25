#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>


int abs(int a) {
    return (a > 0) ? a : a * (-1);
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

int* sadzawka(int s, int* t, int* res) {
    stos a = stworz_stos(s);
    stos b = stworz_stos(s);
    int hold_amount, acc_amount;
    for(int i = 0;i < s; i++) {
        if(czy_pusty(&a)) {
            if(t[i] < 0) {
                push(&a, t[i]);
            }
        } else {
            hold_amount = t[i];
            acc_amount = t[i];
            while(!czy_pusty(&a) && hold_amount != 0) {
                if(acc_amount * top(&a) > 0) {
                    acc_amount += top(&a);
                    pop(&a);
                } else if(abs(hold_amount) >= abs(top(&a))) {
                    hold_amount += top(&a);
                    pop(&a);
                } else {
                    a.elem[a.akt_rozmiar] += hold_amount;
                    hold_amount = 0;
                }
            }
            if((acc_amount < 0 || !czy_pusty(&a)) && acc_amount != 0) {
                push(&a, acc_amount);
            }
        }
    }
    while(!czy_pusty(&a)) {
        push(&b, top(&a));
        pop(&a);
    }
    int j = 0;
    while(!czy_pusty(&b)) {
        res[j] = top(&b);
        pop(&b);
        j++;
    }
    destroy(&a);
    destroy(&b);
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int* tab = malloc((unsigned) a * sizeof(int));
    int* tab_res = malloc((unsigned) a * sizeof(int));
    for(int i = 0 ; i < a ; i++) {
        if(scanf("%d", tab + i) != 1) {
            return -1;
        }
        tab_res[i] = 0;
    }
    tab_res = sadzawka(a, tab, tab_res);
    for(int k = 0; k < a; k++) {
        if(tab_res[k] == 0) {
            break;
        }
        printf("%d \n", tab_res[k]);
    }
    free(tab);
    free(tab_res);
    return 0;
}
