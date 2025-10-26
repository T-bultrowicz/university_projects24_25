#include<stdlib.h>
#include<stdio.h>

int mini(int a, int b) {
    return(a < b) ? a : b;
}

int gaz(int** t, int a, int b, int k) {
    int* pom = malloc((unsigned) a * sizeof(int));
    int g = 0, d = 0; //gora, dol
    int minimum = a * b; //aktualizowany wynik
    int suma = 0; // do gasienicy
    for(int l = 0;l < b; l++) { //lewo

        for(int i = 0;i < a; i++) { //wyzerowanie tablicy
            pom[i] = 0;
        }
        for(int p = l; p < b && p < l + minimum; p++) { //prawo
            for(int i = 0;i < a; i++) {
                pom[i] += t[i][p];
            }
            suma = 0, g = 0, d = 0; //wyzerowanie
            while(d < a) {
                if(suma < k) {
                    suma += pom[d++];
                } else {
                    minimum = mini(minimum, (p - l + 1) * (d - g));
                    suma -= pom[g++];
                }
            }
            while(suma >= k) {
                minimum = mini(minimum, (p - l + 1) * (d - g));
                suma -= pom[g++];
            }
        }
    }
    free(pom);
    return minimum;
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
    printf("\n%d", gaz(t, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
    }
    free(t);
    return 0;
}
