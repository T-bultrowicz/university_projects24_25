#include<stdio.h>
#include<stdlib.h>

int find(int* t, int s, int target) {
    if(target == 0) {
        for(int i = 0; i < s; i++) {
            if(t[i] == 0) {
                return i;
            }
        }
        return -1;
    }
    int suma = 0, l = 0, p = 0;
    while(p < s) {
        if(suma < target) {
            suma += t[p++];
        } else if(suma > target) {
            suma -= t[l++];
        } else {
            return l;
        }
    }
    while(suma >= target && l < s) {
        if(suma == target) {
            return l;
        } else {
            suma -= t[l++];
        }
    }
    return -1;
}

int main() {
    int n, x;
    if(scanf("%d %d", &n, &x) != 2) {
        return -1;
    }
    int* a = malloc((unsigned) n * sizeof(int));
    for(int i = 0; i < n; i++) {
        if(scanf("%d", a + i) != 1) {
            return -1;
        }
    }
    printf("%d", find(a, n, x));
    free(a);
    return 0;
}
