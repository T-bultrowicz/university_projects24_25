#include<stdlib.h>
#include<stdio.h>

int minimum(int* tab, int n) {
    int lewo = 0, prawo = n - 2, s;
    if(tab[n - 1] - tab[n - 2] <= 0) {
        return tab[n-1];
    } else if(tab[1] - tab[0] >= 0) {
        return tab[0];
    } else {
        while(prawo - lewo != 1) {
            s = prawo + lewo;
            s /= 2;
            if(tab[s + 1] - tab[s] > 0) {
                prawo = s;
            } else if(tab[s + 1] - tab[s] < 0) {
                lewo = s;
            } else {
                return s;
            }
        }
        if(tab[prawo] - tab[lewo] > 0) {
            return tab[lewo];
        } else {
            return tab[prawo];
        }
    }
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int* n = malloc((unsigned) a * sizeof(int));
    for(int i = 0; i < a; i++) {
        if(scanf("%d", n + i) != 1) {
            return -1;
        }
    }
    printf("%d", minimum(n,a));
    free(n);
    return 0;
}
