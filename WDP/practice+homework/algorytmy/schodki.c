#include<stdio.h>
#include<stdlib.h>


int schodki(int* t, int s) {
    int* pom = malloc((unsigned) (s + 1) * sizeof(int));
    int res = 0;
    for(int i = 0; i < s + 1 ; i++) {
        pom[i] = 0;
    }
    for(int j = 0; j < s; j++) {
        pom[t[j]]++;
        if(t[j] > 0) {
            if(pom[t[j] - 1] > 0) {
                pom[t[j] - 1]--;
            }
        }
    }
    for(int k = 0; k < s + 1; k++) {
        res += pom[k];
    }
    free(pom);
    return res;
}

int main() {
    int a;
    if(scanf("%d",&a) != 1) {
        return -1;
    }
    int *tab = malloc((unsigned) a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d", tab + i) != 1) {
            return -1;
        }
    }
    printf("%d", schodki(tab, a));
    free(tab);
    return 0;
}
