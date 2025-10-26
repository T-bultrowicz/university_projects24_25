//JEDNAK SIE NIE DA ZROBIC W ZALOZONEJ PRZEZE MNIE LINEAR MEMORY OPACITY I CZASIE SQRT(V) * A * b
//WTEDY WYMAGA CZASU V * A * B

// ALBO QUADRATIC MEMORY OPACITY I CZAS LOG(V) * A * B DLA WIEKSZOSCI, PESYMISTYCZNIE V^(1/3) * A * B

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

int maxi(int a, int b) {
    return(a < b) ? b : a;
}

int orzechy(int** t, int a, int b, int pole) {
    int* pom = malloc((unsigned) b * sizeof(int));
    int maximum = INT_MIN; //aktualizowany wynik koncowy
    int suma = 0; // do zapisu tymczasowego wyniku
    for(int g = 0;g < a; g++) { //gora
        for(int i = 0; i < a; i++) { //wyzerowanie pom
            pom[i] = 0;
        }
        for(int x = 1; x * x <= pole && x + g - 1 < a; x++) { //szerokosc pionowa pola cukierkow
            for(int j = 0;j < b; j++) {
                pom[j] += t[x + g - 1][j];
            }
            suma = 0;
            if(pole % x == 0 && (pole / x) <= b) { //sprawdzanie gdy wlasciwy

                for(int l = 0; l < pole / x; l++) { //startowy prostokat
                    suma += pom[l];
                }
                if(suma > maximum) {
                    maximum = suma;
                }
                for(int p = 0; p + (pole / x) < b; p++) {
                    suma -= pom[p];
                    suma += pom[p + (pole / x)];
                    if(suma > maximum) {
                        maximum = suma;
                    }
                }
            }
        }
    }
    if(pole <= b) {
        for(int g = 0; g < b; g++) {
            suma = 0;
            for(int l = 0; l < pole; l++) { //obliczenie pierwszego
                suma += t[l][g];
            }
            if(suma > maximum) {
                maximum = suma;
            }
            for(int p = 0; p + pole < a; p++) {
                suma -= t[p][g];
                suma += t[p + pole][g];
                if(suma > maximum) {
                    maximum = suma;
                }
            }
        }
    }
    free(pom);
    return maximum;
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
    printf("\n%d", orzechy(t, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
    }
    free(t);
    return 0;
}
