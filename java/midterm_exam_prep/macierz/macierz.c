#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double** mnozenieMacierzy(double** macierz1, double** macierz2, int r1, int r2, int rW) {
    double** res = malloc(sizeof(double*) * (unsigned) r1);
    for(int i = 0; i < r1; i++) {
        res[i] = malloc(sizeof(double) * (unsigned) r2);
        for(int j = 0; j < r2; j++) {
            res[i][j] = 0;
            for(int k = 0; k < rW; k++) {
                res[i][j] += macierz1[i][k] * macierz2[k][j];
            }
        }
    }
    return res;
}

int main() {
    int rozmiar1, rozmiar2, rozmiarWspolny, x;
    x = scanf("%d %d %d", &rozmiar1, &rozmiar2, &rozmiarWspolny);
    double** macierz1 = malloc(sizeof(double*) * rozmiar1);
    double** macierz2 = malloc(sizeof(double*) * rozmiarWspolny);
    for(int i = 0; i < rozmiar1; i++) {
        macierz1[i] = malloc(sizeof(double) * rozmiarWspolny);
        for(int j = 0; j < rozmiarWspolny; j++) {
            x = scanf("%lf", &macierz1[i][j]);
        }
    }
    for(int i = 0; i < rozmiarWspolny; i++) {
        macierz2[i] = malloc(sizeof(double) * rozmiar2);
        for(int j = 0; j < rozmiar2; j++) {
            x = scanf("%lf", &macierz2[i][j]);
        }
    }
    clock_t start = clock();
    double** macierzWyjsciowa = mnozenieMacierzy(macierz1, macierz2, rozmiar1, rozmiar2, rozmiarWspolny);
    clock_t end = clock();

    for(int i = 0; i < rozmiar1; i++) {
        for(int j = 0; j < rozmiar2; j++) {
            printf("%lf ", macierzWyjsciowa[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < rozmiar1; i++) {
        free(macierz1[i]);
        free(macierzWyjsciowa[i]);
    }
    free(macierz1);
    free(macierzWyjsciowa);
    for(int i = 0; i < rozmiarWspolny; i++) {
        free(macierz2[i]);
    }
    free(macierz2);   
    double czas_w_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%d    Czas wykonia to %f milisekund", x, czas_w_ms);
    return 0;
}
