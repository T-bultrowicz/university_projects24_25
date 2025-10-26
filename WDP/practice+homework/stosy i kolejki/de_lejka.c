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

int main() {
    int x;
    bool trwa = true;
    de_lejka list = stworz_de_lejka(200);
    de_lejka max_finder = stworz_de_lejka(200);
    de_lejka indeksy = stworz_de_lejka(200);
    while(trwa) {
        printf("Podaj dzialanie na liscie!\n");
        if(scanf("%d", &x) != 1) {
            return -1;
        }
        switch(x) {
            case 0:
                printf("Dolaczamy element do listy!\n");
                if(scanf("%d", &x) != 1) {
                    return -1;
                }
                push_back(&list, x);
                while(!czy_pusta(&max_finder)) {
                    if(look_back(&max_finder) > x) {
                        break;
                    } else {
                        pop_back(&max_finder);
                        pop_back(&indeksy);
                    }
                }
                push_back(&max_finder, x);
                push_back(&indeksy, list.g_kol);
                break;
            case 1:
                printf("Wyrzucamy element z listy!\n");
                printf("     %d  %d\n", look_front(&indeksy), list.d_kol);
                if(look_front(&indeksy) == list.d_kol) {
                    pop_front(&indeksy);
                    pop_front(&max_finder);       
                }
                pop_front(&list);
                break;
            case 2:
                printf("Przedni element w liscie to: %d\n", look_front(&list));
                break;
            case 3:
                if(czy_pusta(&max_finder)) {
                    printf("Aktualny maksymalny el. w liscie to: 0\n");
                } else {
                    printf("Aktualny maksymalny el. w liscie to: %d\n", look_front(&max_finder));
                }
                break;
            default:
                trwa = false;
                break;
        }   
    }
    destroy(&list);
    destroy(&max_finder);
    destroy(&indeksy);
    return 0;
}
