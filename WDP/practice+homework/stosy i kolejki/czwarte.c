#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
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

int pora(int s, int* t) {
    int res = INT_MAX;
    bool bara;
    bool pory[4];
    int roku[4];
    for(int kaka = 0; kaka < 4; kaka ++) {
        pory[kaka] = false;
        roku[kaka] = 0;
    }
    int i = 0, j = 0;
    while(j < s) {
        if(pory[0] && pory[1] && pory[2] && pory[3] && i < s) {
            if(j - i < res) {
                res = j - i;
            }
            i++;
            while(i < s && t[i]) {
                if(roku[t[i]] == i) {
                    pory[t[i]] = false;
                } 
                i++;
            }
            roku[0] = i;
            if(!pory[1]) {
                pory[2] = false;
                pory[3] = false;
                j = i + 1;
            }
        } else {
            bara = true;
            for(int l = 0; l < t[j]; l++) {
                bara = bara && pory[l];
            }
            if(t[j] == 3 && bara) {
                pory[t[j]] = true;
                roku[t[j]] = j;
            } else if(!pory[t[j] + 1] && bara) {
                pory[t[j]] = true;
                roku[t[j]] = j;                
            }
            j++;
        }
        printf("%d   %d   %d   %d   %d   %d\n", pory[0], pory[1], pory[2], pory[3], i, j);
    }
    while(pory[0] && pory[1] && pory[2] && pory[3] && i < s) {
        if(j - i < res) {
            res = j - i;
        }
        if(roku[t[i]] == i) {
            pory[t[i]] = false;
        } 
        i++;
    }
    if(res == INT_MAX) {
        res = -1;
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
    printf("%d", pora(a, b));
    return 0;
}
