#include<stdlib.h>
#include<stdio.h>

int stala(int* t, int s) {
    int l = 0, r = s - 1, mid;
    while(l <= r) {
        mid = (l + r) / 2;
        if(t[mid] > mid) {
            l = mid + 1;
        } else if(t[mid] < mid) {
            r = mid - 1;
        } else {
            return mid;
        }
    }
    if(l != r) {
        return -1;
    } else {
        return l;
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
    printf("%d", stala(n,a));
    free(n);
    return 0;
}

