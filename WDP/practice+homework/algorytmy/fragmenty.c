#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

int mini(int a, int b) {
    return (a > b) ? b : a;
}

int fragmenty(int *t, int s, int border) {
    int minimum = s;
    int suma = 0, l = 0, p = 0;
    while(p < s) {
        if(suma < border) {
            suma += t[p++];
        } else {
            minimum = mini(minimum, p - l);
            suma -= t[l++];
        }
    }
    return minimum - 1;
}


int main() {
    int a, x;
    if(scanf("%d %d", &a, &x) != 2) {
        return -1;
    }
    int* n = malloc((unsigned) a * sizeof(int));
    for(int i = 0; i < a; i++) {
        if(scanf("%d", n + i) != 1) {
            return -1;
        }
    }
    printf("%d", fragmenty(n, a, x));
    free(n);
    return 0;
}
