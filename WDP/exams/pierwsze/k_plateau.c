#include<stdio.h>
#include<stdlib.h>

int maxi(int a, int b) {
    return(a > b) ? a : b;
}

int k_plateau(int *t, int s, int k) {
    if(s == 0) {
        return 0;
    }
    int maximum = 1; //szukamy maksa
    int i = 0, j = 1; //indeksy gasienica
    int ilosc_zmian = 0; //zmiany plateau
    while(j < s) {
        if(t[j] != t[j - 1]) {
            ilosc_zmian++;
            if(ilosc_zmian == k) {
                ilosc_zmian--;
                maximum = maxi(maximum, j - i);
                while(t[i] == t[i + 1]) {
                    i++;
                }
                i++;
            }
            j++;
        } else {
            j++;
        }
    }
    maximum = maxi(maximum, j - i - 1);
    return maximum;
}


int main() {
    int a, b;
    if(scanf("%d%d",&a, &b) != 2) {
        return -1;
    }
    int *tab = malloc((unsigned) a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d", tab + i) != 1) {
            return -1;
        }
    }
    printf("%d", k_plateau(tab, a, b));
    free(tab);
    return 0;
}
