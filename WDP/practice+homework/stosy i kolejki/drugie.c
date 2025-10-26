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

int main() {
    stos in = stworz_stos(500), out = stworz_stos(500);
    int choice, num;
    while(true) {
        printf("Jaka operacja wariacie?\n");
        if(scanf("%d", &choice) != 1) {
            return -1;
        }
        switch (choice) 
        {
        case 0:
            printf("Podaj liczbe do kolejki wariacie!\n");
            if(scanf("%d", &num) != 1) {
                return -1;
            }
            push(&in, num);
            break;
        case 1:
            if(!czy_pusty(&out)) {
                printf("Liczba z przodu to: %d\n",top(&out));
            } else {
                while(!czy_pusty(&in)) {
                    push(&out, top(&in));
                    pop(&in);
                }
                printf("Liczba z przodu to: %d\n",top(&out));
            }
            break;
        case 2:
            printf("Usuwam pierwszy fragment\n");
            if(!czy_pusty(&out)) {
                pop(&out);
            } else {
                while(!czy_pusty(&in)) {
                    push(&out, top(&in));
                    pop(&in);
                }
                pop(&out);
            }
            break;            
        default:
            return 0;
        }
    }
    destroy(&in);
    destroy(&out);
    return 0;
}
