#include<stdio.h>
#include<stdlib.h>

int plateau(int s_t, int* t) {
    int max = 0, akt = 1;
    for(int i = 0; i < s_t - 1 ; i++ ) {
        if(t[i] == t[i+1]) {
            akt++;
        } else {
            if(akt > max) {
               max = akt;
            }
            akt = 1;
        }
    }
    if(akt > max) {
       max = akt;
    }
    return max;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int* tab = malloc((unsigned int) a * sizeof(int));
    for(int i = 0; i < a; i++) {
        if(scanf("%d", tab + i) != 1) {
            return -1;
        }
    }
    printf("%d",plateau(a,tab));
    free(tab);
    return 0;
}
