#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

int maxi(int a, int b) {
    return (a > b) ? a : b;
}
int mini(int a, int b) {
    return(a > b) ? b : a;
}

int kwadrat(int** t, int a, int b, int k) {
    int maximum = 0; //akt wynik
    int* pom = malloc((unsigned) a * sizeof(int));
    int suma = 0; // do gasienicy
    bool var;
    for(int l = 0;l < b; l++) { //lewo

        for(int i = 0;i < a; i++) { //wyzerowanie tablicy
            pom[i] = 0;
        }
        for(int z = l; z < l + maximum; z++) { //preprocess pom
            for(int i = 0; i < a; i++) {
                pom[i] += t[i][z];
            }
        }
        for(int p = l + maximum; p < b && p < l + mini(a,b); p++) { //prawo
            var = true;
            for(int i = 0; i < a; i++) {
                pom[i] += t[i][p];
            }
            suma = 0;
            for(int pierwszy = 0; pierwszy <= p - l; pierwszy++) {
                suma += pom[pierwszy];
            }
            if(suma < k) {
                maximum = maxi(maximum, p - l + 1);
                var = false;
            }
            if(var) {
                for(int gora = 1; gora < a - (p - l); gora++) {
                    suma -= pom[gora - 1];
                    suma += pom[gora + p - l];
                    if(suma < k) {
                        maximum = maxi(maximum, p - l + 1);
                        break;
                    } //wiekszy candidate
                } // gora for
            } // var if
        } //prawo for
    } // lewo for
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
    printf("\n%d", kwadrat(t, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
    }
    free(t);
    return 0;
}
