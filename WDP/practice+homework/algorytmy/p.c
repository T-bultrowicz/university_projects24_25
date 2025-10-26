#include<stdlib.h>
#include<stdio.h>

int max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}


// ALGORYTM KADANE'A

int p(int* t, int n) {
    int mal = t[0];
    int obecny = t[0];
    for(int i = 1; i < n; i++) {
        obecny = max(obecny + t[i], t[i]);
        if(obecny > mal) {
            mal = obecny;
        }
    }
    return mal;
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
    printf("%d", p(n,a));
    free(n);
    return 0;
}
