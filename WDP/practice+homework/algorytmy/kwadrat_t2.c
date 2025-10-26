#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

int maxi(int a, int b) {
    return (a > b) ? a : b;
}


int** Preprocess(int ** tab, int x, int y) {
    int** res = (int **) malloc((unsigned) x * sizeof(int*));
    for(int j = 0;j < x; j++) {
        res[j] = malloc((unsigned) y * sizeof(int));
        for(int k = 0; k < y; k++) {
            if(j == 0 && k == 0) {
                res[0][0] = tab[0][0];
            } else if(j == 0) {
                res[0][k] = res[0][k - 1] + tab[0][k];
            } else if(k == 0) {
                res[j][0] = res[j - 1][0] + tab[j][0];
            } else {
                res[j][k] = res[j - 1][k] + res[j][k - 1] - res[j - 1][k - 1] + tab[j][k];
            }
        }
    }
    return res;
}

int kwadrat(int** t, int a, int b, int p) {
    int maximum = 0;
    int x_d, y_d; //dolne el gasienicy
    int x_g, y_g; //gorne el gasienicy
    int suma;
    for(int i = 0; i < b; i++) {
        x_d = x_g = a - 1;
        y_d = y_g = i;
        suma = 0;
        while(x_g >= 0 && y_g >= 0 && x_d >= 0 && y_d >= 0) {
            if(suma < p) {
                suma = t[x_d][y_d];
                if(x_g > 0) {
                    suma -= t[x_g - 1][y_d];
                }
                if(y_g > 0) {
                    suma -= t[x_d][y_g - 1];
                }
                if(x_g > 0 && y_g > 0) {
                    suma += t[x_g - 1][y_g - 1];
                }
                maximum = maxi(maximum, x_d - x_g);
                x_g--;
                y_g--;
            } else {
                if(x_d > 0 && y_d > 0) {
                    suma = t[x_d - 1][y_d - 1];
                    if(x_g > 0) {
                        suma -= t[x_g - 1][y_d - 1];
                    }
                    if(y_g > 0) {
                        suma -= t[x_d - 1][y_g - 1];
                    }
                    if(x_g > 0 && y_g > 0) {
                        suma += t[x_g - 1][y_g - 1];
                    }
                }
                x_d--;
                y_d--;
            }
        }
        if(suma < p) {
            maximum = maxi(maximum, x_d - x_g);
        }
    }
    for(int j = 0;j < a - 1; j++) {
        x_d = x_g = j;
        y_d = y_g = b - 1;
        suma = 0;
        while(x_g >= 0 && y_g >= 0 && x_d >= 0 && y_d >= 0) {
            if(suma < p) {
                suma = t[x_d][y_d];
                if(x_g > 0) {
                    suma -= t[x_g - 1][y_d];
                }
                if(y_g > 0) {
                    suma -= t[x_d][y_g - 1];
                }
                if(x_g > 0 && y_g > 0) {
                    suma += t[x_g - 1][y_g - 1];
                }
                maximum = maxi(maximum, x_d - x_g);
                x_g--;
                y_g--;
            } else {
                if(x_d > 0 && y_d > 0) {
                    suma = t[x_d - 1][y_d - 1];
                    if(x_g > 0) {
                        suma -= t[x_g - 1][y_d - 1];
                    }
                    if(y_g > 0) {
                        suma -= t[x_d - 1][y_g - 1];
                    }
                    if(x_g > 0 && y_g > 0) {
                        suma += t[x_g - 1][y_g - 1];
                    }
                }
                x_d --;
                y_d --;
            }
        }
        if(suma < p) {
            maximum = maxi(maximum, x_d - x_g);
        }
    }
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
    int** pom = Preprocess(t, a, b);
    printf("\n%d", kwadrat(pom, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
        free(pom[l]);
    }
    free(pom);
    free(t);
    return 0;
}
