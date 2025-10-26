#include<stdlib.h>
#include<stdio.h>

int znajdz(int** tab, int x, int y, int f) {
    int sum = 0, i = 0, j = 0;
    while(i < x && j < y) {
        if(tab[i][j] < f) {
            j++;
        } else if(tab[i][j] > f) {
            i++;
        } else {
            sum++;
            i++;
            j++;
        }
    }
    return sum;
}


int main() {
    int a, b, v;
    if(scanf("%d %d %d", &a, &b, &v) != 3) {
        return -1;
    }
    int** t = (int**) malloc((unsigned) a * sizeof(int*));
    for(int j = 0;j < a; j++) {
        t[j] = malloc((unsigned) b * sizeof(int));
        for(int k = 0;k < b; k++) {
            if(scanf("%d", &t[j][k]) != 1) {
                return -1;
            }
        }
    }
    printf("%d", znajdz(t, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
    }
    free(t);
    return 0;
}
