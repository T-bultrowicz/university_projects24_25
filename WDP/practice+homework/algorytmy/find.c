#include<stdlib.h>
#include<stdio.h>

int findd(int* tab, int n) {
    int lewo = 0, prawo = n - 1, s;
    if(tab[prawo] > tab[0]) {
        return 0;
    }
    while(lewo != prawo) {
        s = lewo + prawo;
        s /= 2;
        if(tab[s] > tab[0]) {
            lewo  = s + 1;
        } else {
            prawo = s;
        }
    }
    return prawo;
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
    printf("%d", findd(n,a));
    free(n);
    return 0;
}
